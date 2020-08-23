#pragma once
#ifndef _MTCore_h_
#define _MTCore_h_

#include "CLock.h"
#include <process.h>

class MTCore
{
public:
	static MTCore& getInstance();
private:
	MTCore();
public:
	~MTCore();
public:
	void Start();
	void Stop();
	void StartMapLogic();
	bool WaitMapLogoc();
private:
	CMint m_nThreadCount;
	CMbool m_nThreadContinue;
	CMbool m_nMapThread1Ready;
	CMbool m_nMapThread2Ready;
	CMbool m_nMapThread3Ready;
	CMbool m_nMapThread4Ready;
private:
	static unsigned _stdcall MapThread1(void* args);
	static unsigned _stdcall MapThread2(void* args);
	static unsigned _stdcall MapThread3(void* args);
	static unsigned _stdcall MapThread4(void* args);
};

#endif // !_MTCore_h_