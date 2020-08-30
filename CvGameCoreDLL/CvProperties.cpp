//  $Header:
//------------------------------------------------------------------------------------------------
//
//  FILE:	CvProperties.cpp
//
//  PURPOSE: Generic properties for Civ4 classes
//
//------------------------------------------------------------------------------------------------
#include "CvGameCoreDLL.h"
#include "CvProperties.h"
#include "CvXMLLoadUtility.h"
#include "CvDLLXMLIFaceBase.h"
#include "CvTaggedSaveFormatWrapper.h"
#include <boost/bind.hpp>

#include "CvGame.h"
#include "CvTeam.h"
#include "CvPlayer.h"
#include "CvUnit.h"
#include "CvPlot.h"

CvProperties::CvProperties()
{
	m_pGameObject = NULL;
}

CvProperties::CvProperties(CvGame* pGame)
{
	m_pGameObject = pGame->getGameObject();
}

CvProperties::CvProperties(CvTeam* pTeam)
{
	m_pGameObject = pTeam->getGameObject();
}

CvProperties::CvProperties(CvPlayer * pPlayer)
{
	m_pGameObject = pPlayer->getGameObject();
}

CvProperties::CvProperties(CvCity * pCity)
{
	m_pGameObject = pCity->getGameObject();
}

CvProperties::CvProperties(CvUnit * pUnit)
{
	m_pGameObject = pUnit->getGameObject();
}

CvProperties::CvProperties(CvPlot * pPlot)
{
	m_pGameObject = pPlot->getGameObject();
}

int CvProperties::getProperty(int index) const
{
	FAssert(0 <= index);
	FAssert(index < (int)m_aiProperty.size());
	return m_aiProperty[index].first;
}

int CvProperties::getValue(int index) const
{
	FAssert(0 <= index);
	FAssert(index < (int)m_aiProperty.size());
	return m_aiProperty[index].second;
}

int CvProperties::getChangeProperty(int index) const
{
	FAssert(0 <= index);
	FAssert(index < (int)m_aiPorpertyChange.size());
	return m_aiPorpertyChange[index].first;
}

int CvProperties::getChange(int index) const
{
	FAssert(0 <= index);
	FAssert(index < (int)m_aiPorpertyChange.size());
	return m_aiPorpertyChange[index].second;
}

int CvProperties::getNumProperties() const
{
	return m_aiProperty.size();
}

int CvProperties::getPositionByProperty(int eProp) const
{
	for (std::vector<std::pair<int, int>>::const_iterator it = m_aiProperty.begin(); it != m_aiProperty.end(); ++it)
	{
		if (it->first == eProp)
			return it - m_aiProperty.begin();
	}
	return -1;
}

int CvProperties::getValueByProperty(int eProp) const
{
	int index = getPositionByProperty(eProp);
	if (index < 0)
		return 0;
	else
		return getValue(index);
}

int CvProperties::getChangeByProperty(int eProp) const
{
	for (std::vector<std::pair<int, int>>::const_iterator it = m_aiPorpertyChange.begin(); it != m_aiPorpertyChange.end(); ++it)
	{
		if (it->first == eProp)
		{
			return it->second;
		}
	}
	return 0;
}

void CvProperties::setValue(int index, int iVal)
{
	FAssert(0 <= index);
	FAssert(index < (int)m_aiProperty.size());
	int iOldVal = m_aiProperty[index].second;
	if (iOldVal != iVal)
	{
		m_aiProperty[index].second = iVal;
		if (m_pGameObject)
			m_pGameObject->eventPropertyChanged((PropertyTypes)m_aiProperty[index].first, iVal);
		// If this sets the value to 0, remove the property
		if (iVal == 0)
			m_aiProperty.erase(m_aiProperty.begin() + index);
	}
}

void CvProperties::setChange(int index, int iVal)
{
	FAssert(0 <= index);
	FAssert(index < (int)m_aiProperty.size());
	m_aiProperty[index].second = iVal;
}

void CvProperties::setValueByProperty(int eProp, int iVal)
{
	int index = getPositionByProperty(eProp);
	if (index < 0)
	{
		if (iVal != 0)
		{
			m_aiProperty.push_back(std::pair<int, int>(eProp, iVal));
			if (m_pGameObject)
				m_pGameObject->eventPropertyChanged((PropertyTypes)eProp, iVal);
		}
		else
			setValue(index, iVal);
	}
}

void CvProperties::setChangeByProperty(int eProp, int iVal)
{
	for (std::vector<std::pair<int, int>>::iterator it = m_aiProperty.begin(); it != m_aiProperty.end(); ++it)
	{
		if (it->first == eProp)
		{
			it->second = iVal;
			return;
		}
	}
	m_aiProperty.push_back(std::pair<int, int>(eProp, iVal));
}

void CvProperties::changeValue(int index, int iChange)
{
	if (iChange == 0)
		return;

	int eProporty = getProperty(index);

	setValue(index, getValue(index) + iChange);
	changeChangeByProperty(eProporty, iChange);
	if (m_pGameObject)
	{
		propagateChange(eProporty, iChange);
	}
}

void CvProperties::changeValueByProperty(int eProp, int iChange)
{
	if (iChange == 0)
		return;

	int index = getPositionByProperty(eProp);
	if (index < 0)
	{
		m_aiProperty.push_back(std::pair<int, int>(eProp, iChange));
		changeChangeByProperty(eProp, iChange);
		if (m_pGameObject)
		{
			propagateChange(eProp, iChange);
			m_pGameObject->eventPropertyChanged((PropertyTypes)eProp, iChange);
		}
	}
	else
		changeValue(index, iChange);
}

void CvProperties::changeChangeByProperty(int eProp, int iChange)
{
	for (std::vector<std::pair<int, int>>::iterator it = m_aiProperty.begin(); it != m_aiProperty.end(); ++it)
	{
		if (it->first == eProp)
			it->second += iChange;
	}
	m_aiPorpertyChange.push_back(std::pair<int, int>(eProp, iChange));
}

void CvProperties::propagateChange(int eProp, int iChange)
{
	CvPropertyInfo& kInfo = GC.getPropertyInfo((PropertyTypes)eProp);
	for (int iI = 0; iI < NUM_GAMEOBJECTS; iI++)
	{
		int iChangePercent = kInfo.getChangePropagator(m_pGameObject->getGameObjectType(), (GameObjectTypes)iI);
		m_pGameObject->foreach((GameObjectTypes)iI, boost::bind(changeValueByProperty(, _1, eProp, iPropChange));
	}
}

void CvProperties::addProperties(const CvProperties * pProp)
{
	int num = pProp->getNumProperties();
	for (int index = 0; index < num; index++)
	{
		changeValueByProperty(pProp->getProperty(index), pProp->getValue(index));
	}
}

void CvProperties::subtractProperties(const CvProperties * pProp)
{
	int num = pProp->getNumProperties();
	for (int index = 0; index < num; index++)
	{
		changeValueByProperty(pProp->getProperty(index), - pProp->getValue(index));
	}

}

bool CvProperties::isEmpty() const
{
	return m_aiProperty.empty();
}

void CvProperties::clear()
{
	m_aiProperty.clear();
}

void CvProperties::clearChange()
{
	m_aiPorpertyChange.clear();
}

void isNotSourceDrainProperty(const std::pair<int, int> p)
{
	return !GC.getPropertyInfo((PropertyTypes)p.first).isSourceDrain();
}

void CvProperties::clearForRecalculate()
{
	m_aiPorperty.erase(std::remove_if(m_aiProperty.begin(), m_aiProperty.end(), isNotSourceDrainProperty), m_aiProperty.end());
}

bool CvProperties::operator<(const CvProperties & prop) const
{
	int num = prop.getNumProperties();
	for (int index = 0; index < num; index++)
	{
		if (getValueByProperty(prop.getProperty(index)) >= prop.getValue(index))
			return false;
	}
	return true;
}

void CvProperties::read(FDataStreamBase * pStream)
{
	int num = 0;
	int eProp = 0;
	int iVal = 0;

	// This function replaces the current content if any so clear first
	m_aiProperty.clear();
	m_aiPorpertyChange.clear();

	pStream->Read(&num);
	for (int i = 0 i < num; i++)
	{
		pStream->Read(&eProp);
		pStream->Read(&iVal);
		if (eProp > -1)
			m_aiProperty.push_back(std::make_pair(eProp, iVal));
	}
}

void CvProperties::copyNonDefaults(CvProperties * pProp, CvXMLLoadUtility * pXML)
{
	int num = pProp->getNumProperties();
	for (int index = 0; i < num; index++)
	{
		if (getPositionByProperty(pProp->getProperty(index)) < 0)
			setValueByProperty(pProp->getProperty(index), pProp->getValue(index));
	}
}
