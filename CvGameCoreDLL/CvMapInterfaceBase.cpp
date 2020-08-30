#include "CvGameCoreDLL.h"
#include "CvMapInterfaceBase.h"
#include "CvMapExternal.h"

CvMapInterfaceBase::CvMapInterfaceBase()
{
	m_proxy = new CvMapExternal(this);
}

CvMapExternal * CvMapInterfaceBase::getProxy()
{
	return m_proxy;
}
