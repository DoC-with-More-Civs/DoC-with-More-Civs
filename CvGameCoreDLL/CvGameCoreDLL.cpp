#include "CvGameCoreDLL.h"

#include "CvGameCoreDLLUndefNew.h"

#include <new>

#include "CvGlobals.h"
#include "FProfiler.h"
#include "CvDLLInterfaceIFaceBase.h"

// modified - wunshare
//	 - 宏定义 USE_INTERNAL_PROFILER	性能分析器
//	 - 宏定义 MEMORY_TRACKING		内存池跟踪

// wunshare start
#include <Psapi.h>	// PROCESS_MEMORY_COUNTERS, GetProcessMemoryInfo

#include "CvDLLPythonIFaceBase.h"
#include "CvGameCoreUtils.h"

#ifdef MEMORY_TRACKING
void	ProfileTrackAlloc(void* ptr, int size);
void	ProfileTrackDeAlloc(void* ptr);

// 内存使用情况
void DumpMemUsage(const char* fn, int line)
{
	PROCESS_MEMORY_COUNTERS pmc;

	if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
	{
		char buffer[200];
		sprintf(buffer, "memory (%s,%d): %d Kbytes, peak %d\n", fn, line, (int)(pmc.PeakWorkingSetSize / 1024), (int)(pmc.PeakWorkingSetSize / 1024));
		OutputDebugString(buffer);
	}
}

#define PROFILE_TRACK_ALLOC(x,n)	ProfileTrackAlloc(x,n);
#define PROFILE_TRACK_DEALLOC(x)	ProfileTrackDeAlloc(x);
#else
#define PROFILE_TRACK_ALLOC(x,n)
#define PROFILE_TRACK_DEALLOC(x)
#endif
// 全局锁
static int allocCount = 0;
static CRITICAL_SECTION cHeapAccessSection;
static CRITICAL_SECTION g_cPythonSection;
static CRITICAL_SECTION g_cDLLSection;
#ifdef USE_INTERNAL_PROFILER
static CRITICAL_SECTION cSampleSection;
#endif

//
// operator global new and delete override for gamecore DLL 
//
void *__cdecl operator new(size_t size)
{
	if (g_DLL)
	{
		void* result = NULL;
		EnterCriticalSection(&cHeapAccessSection);
		try
		{
			result = g_DLL->newMem(size, __FILE__, __LINE__);
			memset(result, 0, size);
			PROFILE_TRACK_ALLOC(result, size);
		}
		catch (std::exception&)
		{
			OutputDebugString("Allocation failure\n");
		}
		LeaveCriticalSection(&cHeapAccessSection);

		return result;
	}

	OutputDebugString("Alloc [unsafe]");
	::MessageBoxA(NULL, "Unsafe alloc", "CvGameCore", MB_OK);
	return malloc(size);
}

void __cdecl operator delete (void *p)
{
	if (g_DLL)
	{
		PROFILE_TRACK_DEALLOC(p);
		
		EnterCriticalSection(&cHeapAccessSection);
		g_DLL->delMem(p, __FILE__, __LINE__);
		LeaveCriticalSection(&cHeapAccessSection);
	}
	else
	{
		free(p);
	}
}

void* operator new[](size_t size)
{
	if (g_DLL)
	{
		EnterCriticalSection(&cHeapAccessSection);
		void* result = g_DLL->newMemArray(size, __FILE__, __LINE__);
		LeaveCriticalSection(&cHeapAccessSection);

		memset(result, 0, size);

		return result;
	}
		
	OutputDebugString("Alloc [unsafe]");
	::MessageBoxA(NULL, "Unsafe alloc", "CvGameCore", MB_OK);
	return malloc(size);
}

void operator delete[](void* pvMem)
{
	if (g_DLL)
	{
		EnterCriticalSection(&cHeapAccessSection);
		g_DLL->delMemArray(pvMem, __FILE__, __LINE__);
		LeaveCriticalSection(&cHeapAccessSection);
	}
	else
	{
		free(pvMem);
	}
}

void *__cdecl operator new(size_t size, char* pcFile, int iLine)
{
	EnterCriticalSection(&cHeapAccessSection);
	void* result = g_DLL->newMem(size, pcFile, iLine);
	LeaveCriticalSection(&cHeapAccessSection);

	memset(result, 0, size);
	return result;
}

void *__cdecl operator new[](size_t size, char* pcFile, int iLine)
{
	EnterCriticalSection(&cHeapAccessSection);
	void* result = g_DLL->newMem(size, pcFile, iLine);
	LeaveCriticalSection(&cHeapAccessSection);

	memset(result, 0, size);
	return result;
}

void __cdecl operator delete(void* pvMem, char* pcFile, int iLine)
{
	EnterCriticalSection(&cHeapAccessSection);
	g_DLL->delMem(pvMem, pcFile, iLine);
	LeaveCriticalSection(&cHeapAccessSection);
}

void __cdecl operator delete[](void* pvMem, char* pcFile, int iLine)
{
	EnterCriticalSection(&cHeapAccessSection);
	g_DLL->delMem(pvMem, pcFile, iLine);
	LeaveCriticalSection(&cHeapAccessSection);
	
}

void* reallocMem(void* a, unsigned int uiBytes, const char* pcFile, int iLine)
{
	void* result;
	EnterCriticalSection(&cHeapAccessSection);
	result = g_DLL->reallocMem(a, uiBytes, pcFile, iLine);
	LeaveCriticalSection(&cHeapAccessSection);
	return result;
}

unsigned int memSize(void* a)
{
	unsigned int result = g_DLL->memSize(a);

	return result;
}

// BUG - EXE/DLL Paths - start
HANDLE dllModule = NULL;
// BUG - EXE/DLL Paths - end

BOOL APIENTRY DllMain(HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved)
{
	switch( ul_reason_for_call ) {
	case DLL_PROCESS_ATTACH:
		{

// BUG - EXE/DLL Paths - start
		dllModule = hModule;

// BUG - EXE/DLL Paths - end

		// The DLL is being loaded into the virtual address space of the current process as a result of the process starting up 
		OutputDebugString("DLL_PROCESS_ATTACH\n");
		// 自旋初始化锁
		InitializeCriticalSectionAndSpinCount(&g_cDLLSection, 4000); 
		InitializeCriticalSectionAndSpinCount(&cHeapAccessSection, 4000); 
		InitializeCriticalSection(&g_cPythonSection);

#ifdef USE_INTERNAL_PFOFILER
		InitializeCriticalSectionAndSpinCount(&cSampleSection, 4000);
#endif // USE_INTERNAL_PFOFILER

		// set timer precision
		MMRESULT iTimeSet = timeBeginPeriod(1);		// set timeGetTime and sleep resolution to 1 ms, otherwise it's 10-16ms
		FAssertMsg(iTimeSet==TIMERR_NOERROR, "failed setting timer resolution to 1 ms");
		}
		break;
	case DLL_THREAD_ATTACH:
		OutputDebugString("DLL_THREAD_ATTACH\n");
		break;
	case DLL_THREAD_DETACH:
		OutputDebugString("DLL_THREAD_DETACH\n");
		break;
	case DLL_PROCESS_DETACH:

// BUG - EXE/DLL Paths - start
		dllModule = NULL;
// BUG - EXE/DLL Paths - end

		OutputDebugString("DLL_PROCESS_DETACH\n");
		timeEndPeriod(1);
		break;
	}
	
	return TRUE;	// success
}

#ifdef USE_INTERNAL_PROFILER
// Uncomment the following line to provide (very) detailed tracing to
// the debug stream (view with DbgView or a debugger)
#define DETAILED_TRACE

#define MAX_SAMPLES				1200
static __declspec(thread) ProfileLinkageInfo* _currentSample = NULL;
static __declspec(thread) bool bIsMainThread = false;
static __declspec(thread) int iThreadSlot = 1;
#define RESERVED_THREAD_SLOT	MAX_PROFILED_THREADS

static bool bMainThreadSeen = false;
static int numSmaples = 0;
static ProfileSample* sampleList[MAX_SAMPLES * MAX_PROFILED_THREADS];
bool g_bTraceBackgroundThreads = true;

volatile bool bThreadSlotOccupied[MAX_PROFILED_THREADS];

#ifdef DETAILED_TRACE
static ProfileSample* lastExit = NULL;
static int exitCount = 0;
static bool detailedTraceEnabled = false;

static void GenerateTabString(char* buffer, int n)
{
	while (n-- > 0)
	{
		*buffer++ = '\t';
	}

	*buffer = '\0';
}
#endif

void EnableDetailedTrace(bool enable)
{
#ifdef DETAILED_TRACE
	detailedTraceEnabled = enable;
#endif
}

bool IFPIsMainThread() { return bIsMainThread; }

void IFPProfileThread(void)
{
	if (iThreadSlot == -1 && (g_bTraceBackgroundThreads || bIsMainThread))
	{
		EnterCriticalSection(&cSampleSection);

		for (int iI = 0; iI < MAX_PROFILED_THREADS; iI++)
		{
			if (!bThreadSlotOccupied[iI])
			{
				iThreadSlot = iI;
				bThreadSlotOccupied[iI] = true;
				break;
			}
		}
		LeaveCriticalSection(&cSampleSection);
	}
}

void IFPBeginSample(ProfileLinkageInfo* linkageInfo, bool bAsConditional)
{
	ProfileSample*	sample = linkageInfo->sample;

	if (!bMainThreadSeen)
	{
		bMainThreadSeen = true;
		bIsMainThread = true;

		for (int iI = 0; iI < MAX_PROFILED_THREADS; iI++)
		{
			bThreadSlotOccupied[iI] == false;
		}

		IFPProfileThread();
	}

	if (iThreadSlot != -1)
	{
		if (sample->Id == -1)
		{
			EnterCriticalSection(&cSampleSection);

			if (numSmaples == MAX_SAMPLES)
			{
				dumpProfileStack();
				::MessageBox(NULL, "Profile sample limit exceeded", "CvGameCore", MB_OK);
				LeaveCriticalSection(&cSampleSection);
				return;
			}
			sample->Parent = -1;
			sample->IsInAlternateSet = (stricmp(sample->Name, GC.alternateProfileSmapleName()) == 0);
			sampleList[numSmaples++] = sample;
			sample->Id = numSmaples;

			for (int iI = 0; iI <= MAX_PROFILED_THREADS; iI++)
			{
				sample->ProfileInstance[iI] = 0;
				sample->EntryCount[iI] = 0;
				sample->Accumulator[iI].QuadPart = 0;
				sample->MainThreadAccumulator[iI].QuadPart = 0;
				sample->ChildrenSampleTime[iI].QuadPart = 0;
				sample->AlternateSampleSetTime[iI].QuadPart = 0;
			}

			LeaveCriticalSection(&cSampleSection);
		}

		linkageInfo->parent = _currentSample;
		sample->ProfileInstance[iThreadSlot]++;
		linkageInfo->bIsEntry = (sample->EntryCount[iThreadSlot]++ == 0);

		if (linkageInfo->bIsEntry)
		{
			if (_currentSample != NULL && sample->Parent == -1)
			{
				sample->Parent = _currentSample->sample->Id;
			}
			// 开始计时
			QueryPerformanceCounter(&linkageInfo->startTime);
		}

		if (!bAsConditional)
		{
			_currentSample = linkageInfo;
		}
	}
}

void IFPEndSample(ProfileLinkageInfo* linkageInfo, bool bAsConditional)
{
	if (iThreadSlot != -1)
	{
		if (!bAsConditional && _currentSample != linkageInfo && linkageInfo->sample->Parent != -1)
		{
			char buffer[200];
			sprintf(buffer, "Sample closure not matched: closing %s when %s was expected",
				linkageInfo->sample->Name, (_currentSample == NULL ? "NULL" : _currentSample->sample->Name));
			MessageBox(NULL, buffer, "CvGameCore", MB_OK);
		}

		if (!bAsConditional)
		{
			_currentSample = linkageInfo->parent;
		}

		ProfileSample* sample = linkageInfo->sample;
		sample->EntryCount[iThreadSlot]--;

		if (linkageInfo->bIsEntry)
		{
			LARGE_INTEGER now;
			LONGLONG ellapsed;
			// 结束时间
			QueryPerformanceCounter(&now);
			ellapsed = (now.QuadPart - linkageInfo->startTime.QuadPart);
			sample->Accumulator[iThreadSlot].QuadPart += ellapsed;

			if (bIsMainThread)
			{
				sample->MainThreadAccumulator[iThreadSlot].QuadPart += ellapsed;
			}

			if (_currentSample != NULL)
			{
				_currentSample->sample->ChildrenSampleTime[iThreadSlot].QuadPart += ellapsed;

				if (sample->IsInAlternateSet)
				{
					for (ProfileLinkageInfo* linkage = _currentSample; linkage != NULL; linkage->parent)
					{
						linkage->sample->AlternateSampleSetTime[iThreadSlot].QuadPart += ellapsed;
					}
				}
			}
			else
			{
				EnterCriticalSection(&cSampleSection);

				for (int iI = 0; iI < numSmaples; iI++)
				{
					ProfileSample* thisSample = sampleList[iI];

					thisSample->Accumulator[RESERVED_THREAD_SLOT].QuadPart += thisSample->Accumulator[iThreadSlot].QuadPart;
					thisSample->MainThreadAccumulator[RESERVED_THREAD_SLOT].QuadPart += thisSample->MainThreadAccumulator[iThreadSlot].QuadPart;
					thisSample->ChildrenSampleTime[RESERVED_THREAD_SLOT].QuadPart += thisSample->ChildrenSampleTime[iThreadSlot].QuadPart;
					thisSample->AlternateSampleSetTime[RESERVED_THREAD_SLOT].QuadPart += thisSample->AlternateSampleSetTime[iThreadSlot].QuadPart;
					thisSample->ProfileInstance[RESERVED_THREAD_SLOT] += thisSample->ProfileInstance[iThreadSlot];

					thisSample->EntryCount[iThreadSlot] = 0;
					thisSample->ProfileInstance[iThreadSlot] = 0;
					thisSample->Accumulator[iThreadSlot].QuadPart = 0;
					thisSample->MainThreadAccumulator[iThreadSlot].QuadPart = 0;
					thisSample->ChildrenSampleTime[iThreadSlot].QuadPart = 0;
					thisSample->AlternateSampleSetTime[iThreadSlot].QuadPart = 0;
				}

				if (!bIsMainThread)
				{
					bThreadSlotOccupied[iThreadSlot] = false;
					iThreadSlot = -1;
				}

				LeaveCriticalSection(&cSampleSection);
			}
		}
	}
}

void IFPCancelSample(ProfileLinkageInfo* linkageInfo)
{
	if (iThreadSlot != -1)
	{
		linkageInfo->sample->EntryCount[iThreadSlot]--;
		linkageInfo->sample->ProfileInstance[iThreadSlot]--;
	}
}

void IFPBegin(void)
{
	for (int i = 0; i < numSmaples; i++)
	{
		sampleList[i]->Accumulator[RESERVED_THREAD_SLOT].QuadPart = 0;
		sampleList[i]->MainThreadAccumulator[RESERVED_THREAD_SLOT].QuadPart = 0;
		sampleList[i]->AlternateSampleSetTime[RESERVED_THREAD_SLOT].QuadPart = 0;
		sampleList[i]->ChildrenSampleTime[RESERVED_THREAD_SLOT].QuadPart = 0;
		sampleList[i]->ProfileInstance[RESERVED_THREAD_SLOT] = 0;
	}
}

void IFPEnd(void)
{
	// Log the timings
	char buffer[300];
	LARGE_INTEGER freq;

	QueryPerformanceCounter(&freq);

	g_DLL->logMsg("IFP_log.txt", "Fn\tTime (mS)\tMain thread\tAvg time\t#calls\
					\tChild time\tSelf time\tParent\tAlternate Time\n");

	for (int i = 0; i < numSmaples; i++)
	{
		if (sampleList[i]->ProfileInstance[RESERVED_THREAD_SLOT] != 0)
		{
			sprintf(buffer,
				"%s\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%d\n",
				sampleList[i]->Name,
				(int)((1000 * sampleList[i]->Accumulator[RESERVED_THREAD_SLOT].QuadPart) / freq.QuadPart),
				(int)((1000 * sampleList[i]->MainThreadAccumulator[RESERVED_THREAD_SLOT].QuadPart) / 
					freq.QuadPart * sampleList[i]->ProfileInstance[RESERVED_THREAD_SLOT]),
				(int)((1000* sampleList[i]->Accumulator[RESERVED_THREAD_SLOT].QuadPart) / (freq.QuadPart)),
				sampleList[i]->ProfileInstance[RESERVED_THREAD_SLOT],
				(int)((1000 * sampleList[i]->ChildrenSampleTime[RESERVED_THREAD_SLOT].QuadPart) / freq.QuadPart),
				(int)((1000 * sampleList[i]->Accumulator[RESERVED_THREAD_SLOT].QuadPart) / freq.QuadPart) - 
					(int)((1000 * sampleList[i]->ChildrenSampleTime[RESERVED_THREAD_SLOT].QuadPart) / freq.QuadPart),
				sampleList[i]->Parent == -1 ? "" : sampleList[sampleList[i]->Parent]->Name,
				(int)((1000 * sampleList[i]->AlternateSampleSetTime[RESERVED_THREAD_SLOT].QuadPart) / freq.QuadPart)
			);
			g_DLL->logMsg("IFP_log.txt", buffer);
		}
	}
}

void IFPSetCount(ProfileSample* sample, int count)
{
	if (numSmaples == MAX_SAMPLES)
	{
		dumpProfileStack();
		::MessageBox(NULL, "Profile sample limt exceeded", "CvGameCore", MB_OK);
		return;
	}
	sample->Id = numSmaples;
	sample->EntryCount[RESERVED_THREAD_SLOT] = 0;
	sample->ProfileInstance[RESERVED_THREAD_SLOT] = count;
	sample->Accumulator[RESERVED_THREAD_SLOT] = 0;
	sample->ChildrenSampleTime[RESERVED_THREAD_SLOT].QuadPart = 0;
	sampleList[numSmaples++] = sample;

}

static bool isInLongLivedSection = false;
static bool longLivedSectionDumped = true;
static ProfileSample rootSample__("Root");
static ProfileLinkageInfo rootSampleLinkage;

void dumpProfileStack(void)
{

}

#endif // USE_INTERNAL_PROFILER

void IFPLockPythonAccess(void)
{

}

void IFPUnlockPythonAccess(void)
{

}

static int pythonDepth = 0;

bool IFPPythonCall(const char* callerFn, const char* moduleName, const char* fxnName, void* fxnArg)
{
	bool result;
	PROFILE("IFPPythonCall1");

#ifdef USE_INTERNAL_PROFILER
	FAssert(bIsMainThread || iThreadSlot == -1);
	if (!bIsMainThread)
	{
		::MessageBox(NULL, "Illegal use of Python on background thread", "CvGameCoreDLL", MB_OK);
	}
#endif
	result = gDLL->getPythonIFace()->callFunction(moduleName, fxnName, fxnArg);

	pythonDepth--;

	return result;
}

bool IFPPythonCall(const char* callerFn, const char* moduleName, const char* fxnName, void* fxnArg, long* result)
{
	PROFILE("IFPPythonCall2");
#ifdef USE_INTERNAL_PROFILER
	if (!bIsMainThread)
	{
		::MessageBox(NULL, "Illegal use of Python on background thread", "CvGameCoreDLL", MB_OK);
	}
#endif

#ifdef FP_PROFILE_ENABLE	// Turn Profiling On or Off .. 
#ifdef USE_INTERNAL_PROFILER
	static std::map<int, ProfileSample*>*	g_pythonProfiles = NULL;

	if (g_pythonProfiles == NULL)
	{
		g_pythonProfiles = new std::map<int, ProfileSample*>();
	}

	CvChecksum xSum;
	const char* ptr;
	ProfileSample* pSample;

	for (ptr = moduleName; *ptr != '\0'; ptr++)
	{
		xSum.add((byte)*ptr);
	}
	for (ptr = fxnName; *ptr != '\0'; ptr++)
	{
		xSum.add((byte)*ptr);
	}

	std::map<int, ProfileSample*>::const_iterator itr = g_pythonProfiles->find(xSum.get());

	if (itr == g_pythonProfiles->end())
	{
		char profileName[256];
		sprintf(profileName, "IFPPythonCall2.%s::%s", moduleName, fxnName);
		pSample = new ProfileSample(profileName);

		g_pythonProfiles->insert(std::make_pair(xSum.get(), pSample));
	}
	else
	{
		pSample = itr->second;
	}

	CProfileScope detailedScope(pSample);
#endif
#endif 

	bool bResult = gDLL->getPythonIFace()->callFunction(moduleName, fxnName, fxnArg, result);

	pythonDepth--;
	return bResult;
}

bool IFPPythonCall(const char* callerFn, const char* moduleName, const char* fxnName, void* fxnArg, CvString* result)
{
	PROFILE("IFPPYTHONCALL3");
#ifdef USE_INTERNAL_PROFILER
	FAssert(bIsMainThread || iThreadSlot == -1);
	if (!bIsMainThread) 
	{
		::MessageBox(NULL, "Illegal use of Python on background thread", "CvGameCoreDLL", MB_OK);
	}
#endif
	bool bResult = gDLL->getPythonIFace()->callFunction(moduleName, fxnName, fxnArg, result);

	pythonDepth--;
	return bResult;
}

bool IFPPythonCall(const char* callerFn, const char* moduleName, const char* fxnName, void* fxnArg, CvWString* result)
{
	PROFILE("IFPPythonCall4");
#ifdef USE_INTERNAL_PROFILER
	FAssert(bIsMainThread || iThreadSlot == -1);
	if (!bIsMainThread)
	{
		::MessageBox(NULL, "Illegal use of Python on background thread", "CvGameCoreDLL", MB_OK);
	}
#endif
	bool bResult = gDLL->getPythonIFace()->callFunction(moduleName, fxnName, fxnArg, result);
	
	pythonDepth--;
	return bResult;
}

bool IFPPythonCall(const char* callerFn, const char* moduleName, const char* fxnName, void* fxnArg, std::vector<byte>* pList)
{
	PROFILE("IFPPythonCall5");
#ifdef USE_INTERNAL_PROFILER
	FAssert(bIsMainThread || iThreadSlot == -1);
	if (!bIsMainThread)
	{
		::MessageBox(NULL, "Illegal use of Python on background thread", "CvGameCoreDLL", MB_OK);
	}
#endif
	bool result = gDLL->getPythonIFace()->callFunction(moduleName, fxnName, fxnArg, pList);

	pythonDepth--;
	return result;
}

bool IFPPythonCall(const char* callerFn, const char* moduleName, const char* fxnName, void* fxnArg, std::vector<int>* pIntList)
{
	PROFILE("IFPPythonCall6");
#ifdef USE_INTERNAL_PROFILER
	FAssert(bIsMainThread || iThreadSlot == -1);
	if (!bIsMainThread)
	{
		::MessageBox(NULL, "Illegal use of Python on background thread", "CvGameCoreDLL", MB_OK);
	}
#endif
	bool result = gDLL->getPythonIFace()->callFunction(moduleName, fxnName, fxnArg, pIntList);
	pythonDepth--;
	return result;
}

bool IFPPythonCall(const char* callerFn, const char* moduleName, const char* fxnName, void* fxnArg, int* pIntList, int* iListSize)
{
	PROFILE("IFPPythonCall7");
#ifdef USE_INTERNAL_PROFILER
	FAssert(bIsMainThread || iThreadSlot == -1);
	if (!bIsMainThread)
	{
		::MessageBox(NULL, "Illegal use of Python on background thread", "CvGameCoreDLL", MB_OK);
	}
#endif
	bool result = gDLL->getPythonIFace()->callFunction(moduleName, fxnName, fxnArg, pIntList, iListSize);
	
	pythonDepth--;
	return result;
}

bool IFPPythonCall(const char* callerFn, const char* moduleName, const char* fxnName, void* fxnArg, std::vector<float>* pFloatList)
{
	PROFILE("IFPPythonCall8");
#ifdef USE_INTERNAL_PROFILER
	FAssert(bIsMainThread || iThreadSlot == -1);
	if (!bIsMainThread)
	{
		::MessageBox(NULL, "Illegal use of Python on background thread", "CvGameCoreDLL", MB_OK);
	}
#endif
	bool result = gDLL->getPythonIFace()->callFunction(moduleName, fxnName, fxnArg, pFloatList);

	pythonDepth--;
	return result;
}

//
// enable dll profiler if necessary, clear history
//
void startProfilingDLL(bool longLived)
{
#ifdef USE_INTERNAL_PROFILER
	if (longLived)
	{
		isInLongLivedSection = true;
		longLivedSectionDumped = false;
	}
	else if (GC.isDLLProfilerEnabled() && !isInLongLivedSection && longLivedSectionDumped)
	{
		rootSampleLinkage.sample = &rootSample__;

		IFPBegin();
		IFPBeginSample(&rootSampleLinkage);
	}
#else
	if (GC.isDLLProfilerEnabled())
	{
		gDLL->ProfilerBegin();
	}
#endif
}

//
// dump profile stats on-screen
//
void stopProfilingDLL(bool longLived)
{
#ifdef USE_INTERNAL_PROFILER
	if (longLived)
	{
		isInLongLivedSection = true;
	}
	else if (GC.isDLLProfilerEnabled() && !isInLongLivedSection)
	{
		IFPEndSample(&rootSampleLinkage);
		IFPEnd();

		longLivedSectionDumped = true;
	}
#else
	if (GC.isDLLProfilerEnabled())
	{
		gDLL->ProfilerEnd();
	}
#endif
}

#ifdef MEMORY_TRACKING
CMemoryTrack*	CMemoryTrack::trackStack[MAX_TRACK_DEPTH];
int  CMemoryTrack::m_trackStackDepth = 0;

CMemoryTrack::CMemoryTrack(const char* name, bool valid)
{
	if (bIsMainThread)
	{
		m_highWater = 0;
		m_seq = 0;
		m_name = name;
		m_valid = valid;

		if (m_trackStackDepth < MAX_TRACK_DEPTH)
		{
			trackStack[m_trackStackDepth++] = this;
		}
	}
	else
	{
		m_valid = false;
	}
}

CMemoryTrack::~CMemoryTrack()
{
	if (IFPIsMainThread)
	{
		if (m_valid)
		{
			for (int i = 0; i < m_highWater; i++)
			{
				if (m_track[i] != NULL)
				{
					char buffer[200];
					sprintf(buffer, "Apparent memory leak (size %d) detected in %s (from %s:%d)\n",
						m_allocSize[i], m_name, m_trackName[i], m_allocSeq[i]);
					OutputDebugString(buffer);
				}
			}
		}

		if (trackStack[m_trackStackDepth - 1] == this)
		{
			m_trackStackDepth--;
		}
	}
}

void CMemoryTrack::NoteAlloc(void* ptr, int size) 
{
	if (m_valid)
	{
		for (int i = 0; i < m_highWater; i++)
		{
			if (m_track[i] == NULL)
			{
				if (i == m_highWater)
				{
					if (m_highWater < MAX_TRACKED_ALLOCS)
					{
						m_highWater++;
					}
					else
					{
						m_valid = false;
						return;
					}
				}

				m_track[i] = ptr;
				m_allocSeq[i] = m_seq++;
				m_allocSize[i] = size;
#ifdef USE_INTERNAL_PROFILER
				m_trackName[i] = _currentSample == NULL || _currentSample->sample == NULL ? 
					"<None>" : _currentSample->sample->Name;
#else
				m_trackName[i] = "";
#endif
			}
		}
	}
}

void CMemoryTrack::NoteDeAlloc(void* ptr)
{
	if (m_valid)
	{
		for (int i = 0; i < m_highWater; i++)
		{
			if (m_track[i] == ptr)
			{
				m_track[i] = NULL;
				break;
			}
		}
	}
}

CMemoryTrack* CMemoryTrack::GetCurrent(void)
{
	if (0 < m_trackStackDepth && m_trackStackDepth < MAX_TRACK_DEPTH)
	{
		return trackStack[m_trackStackDepth - 1];
	}
	else
	{
		return NULL;
	}
}

CMemoryTrace::CMemoryTrace(const char* name)
{
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

	m_name = name;
	m_start = pmc.WorkingSetSize;
}

CMemoryTrace::~CMemoryTrace()
{
	static PROCESS_MEMORY_COUNTERS lastPmc;
	PROCESS_MEMORY_COUNTERS pmc;

	if (bIsMainThread)
	{
		if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)) &&
			(pmc.WorkingSetSize != m_start || lastPmc.WorkingSetSize/1024 != pmc.WorkingSetSize/1024))
		{
			char buffer[200];
			sprintf(buffer, "function %s added %dK bytes, total now %uK\n",
				m_name, ((int)(pmc.WorkingSetSize - m_start))/1024, (unsigned int)pmc.WorkingSetSize/1024);
			OutputDebugString(buffer);
		}
		memcpy(&lastPmc, &pmc, sizeof(pmc));
	}
}

void ProfileTrackAlloc(void* ptr, int size)
{
	if (bIsMainThread)
	{
		CMemoryTrack* current = CMemoryTrack::GetCurrent();
		if (current != NULL)
		{
			current->NoteAlloc(ptr, size);
		}
	}
}

void ProfileTrackDeAlloc(void * ptr)
{
	if (bIsMainThread)
	{
		CMemoryTrack* current = CMemoryTrack::GetCurrent();
		if (current != NULL)
		{
			current->NoteDeAlloc(ptr);
		}
	}
}
#endif

// wunshare end