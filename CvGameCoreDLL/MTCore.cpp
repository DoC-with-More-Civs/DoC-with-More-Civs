#include "CvGameCoreDLL.h"
#include "CvGlobals.h"
#include "MTCore.h"
#include "CvGameCoreDLLUndefNew.h"

MTCore::MTCore()
{
	m_nThreadCount.Set(0);
	m_nThreadContinue.Set(true);
	m_nMapThread1Ready.Set(false);
	m_nMapThread2Ready.Set(false);
	m_nMapThread3Ready.Set(false);
	m_nMapThread4Ready.Set(false);
}

MTCore::~MTCore()
{
	Stop();
}

MTCore& MTCore::getInstance()
{
	static MTCore instance;
	return instance;
}

void MTCore::Start()
{
	unsigned id;
	HANDLE   handle;
	m_nThreadCount.Add();
	handle = (HANDLE)_beginthreadex(NULL, 0, MapThread1, this, 0, &id); Sleep(250);
	m_nThreadCount.Add();
	handle = (HANDLE)_beginthreadex(NULL, 0, MapThread2, this, 0, &id); Sleep(250);
	m_nThreadCount.Add();
	handle = (HANDLE)_beginthreadex(NULL, 0, MapThread3, this, 0, &id); Sleep(250);
	m_nThreadCount.Add();
	handle = (HANDLE)_beginthreadex(NULL, 0, MapThread4, this, 0, &id); Sleep(250);
}

void MTCore::Stop()
{
	m_nThreadContinue.Set(false);
	while (m_nThreadCount.Get())
		Sleep(1);
}

void MTCore::StartMapLogic() 
{ 
	m_nMapThread1Ready.Set(true); 
	m_nMapThread2Ready.Set(true); 
	m_nMapThread3Ready.Set(true);
	m_nMapThread4Ready.Set(true);
}

bool MTCore::WaitMapLogoc() 
{ 
	return m_nMapThread1Ready.Get() &&
		m_nMapThread2Ready.Get() &&
		m_nMapThread3Ready.Get() &&
		m_nMapThread4Ready.Get();
}

unsigned MTCore::MapThread1(void* args)
{
	MTCore* pThis = (MTCore*)args;
	while (pThis->m_nThreadContinue.Get())
	{
		if (pThis->m_nMapThread1Ready.Get())
		{
			for (int iI = 0; iI < GC.getMap().numPlotsINLINE() / 4; iI++)
			{
				GC.getMap().plotByIndexINLINE(iI)->doTurn();
			}
			pThis->m_nMapThread1Ready.Set(false);
		}
		Sleep(1);
	}
	pThis->m_nThreadCount.Dec();
	return 0;
}

unsigned MTCore::MapThread2(void* args)
{
	MTCore* pThis = (MTCore*)args;
	while (pThis->m_nThreadContinue.Get())
	{
		if (pThis->m_nMapThread2Ready.Get())
		{
			for (int iI = GC.getMap().numPlotsINLINE() / 4; iI < GC.getMap().numPlotsINLINE() / 2; iI++)
			{
				GC.getMap().plotByIndexINLINE(iI)->doTurn();
			}
			pThis->m_nMapThread2Ready.Set(false);
		}
		Sleep(1);
	}
	pThis->m_nThreadCount.Dec();
	return 0;
}

unsigned MTCore::MapThread3(void* args)
{
	MTCore* pThis = (MTCore*)args;
	while (pThis->m_nThreadContinue.Get())
	{
		if (pThis->m_nMapThread3Ready.Get())
		{
			for (int iI = GC.getMap().numPlotsINLINE() / 2; iI < GC.getMap().numPlotsINLINE() *3 / 4; iI++)
			{
				GC.getMap().plotByIndexINLINE(iI)->doTurn();
			}
			pThis->m_nMapThread3Ready.Set(false);
		}
		Sleep(1);
	}
	pThis->m_nThreadCount.Dec();
	return 0;
}

unsigned MTCore::MapThread4(void* args)
{
	MTCore* pThis = (MTCore*)args;
	while (pThis->m_nThreadContinue.Get())
	{
		if (pThis->m_nMapThread4Ready.Get())
		{
			for (int iI = GC.getMap().numPlotsINLINE() * 3 / 4; iI < GC.getMap().numPlotsINLINE(); iI++)
			{
				GC.getMap().plotByIndexINLINE(iI)->doTurn();
			}
			pThis->m_nMapThread4Ready.Set(false);
		}
		Sleep(1);
	}
	pThis->m_nThreadCount.Dec();
	return 0;
}

