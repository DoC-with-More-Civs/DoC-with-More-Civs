#pragma once
#ifndef _CLock_h_
#define _CLock_h_

#include <WinBase.h>

class CMutexLock
{
public:
	CMutexLock() { InitializeCriticalSection(&m_Lock); }
	~CMutexLock() { DeleteCriticalSection(&m_Lock); }
public:
	void Lock() { EnterCriticalSection(&m_Lock); }
	void Unlock() { LeaveCriticalSection(&m_Lock); }
private:
	CRITICAL_SECTION m_Lock;
};

class CMint
{
public:
	CMint() {}
	~CMint() {}
public:
	void Set(int nValue) { m_Lock.Lock(); m_nValue = nValue; m_Lock.Unlock(); }
	int  Get(void) { int nRet; m_Lock.Lock(); nRet = m_nValue; m_Lock.Unlock(); return nRet; }
	void Add(int nValue = 1) { m_Lock.Lock(); m_nValue += nValue; m_Lock.Unlock(); }
	void Dec(int nValue = 1) { m_Lock.Lock(); m_nValue -= nValue; m_Lock.Unlock(); }
private:
	int m_nValue;
	CMutexLock m_Lock;
};

class CMbool
{
public:
	CMbool() {}
	~CMbool() {}
public:
	void Set(bool bValue) { m_Lock.Lock(); m_bValue = bValue; m_Lock.Unlock(); }
	int  Get(void) { int bRet; m_Lock.Lock(); bRet = m_bValue; m_Lock.Unlock(); return bRet; }
private:
	bool m_bValue;
	CMutexLock m_Lock;
};

#endif // !_CLock_h_

