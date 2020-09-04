//  $Header:
//------------------------------------------------------------------------------------------------
//
//  FILE:    CvPropertySolver.cpp
//
//  PURPOSE: Singleton class for solving the system of property manipulators
//
//------------------------------------------------------------------------------------------------

#include "CvGameCoreDLL.h"
#include "CvPropertySolver.h"

#include <boost/bind.hpp>

#include "CvGameAI.h"

int PropertySolverMap::getPredictValue(CvGameObject * pObject, PropertyTypes eProperty)
{
	return 0;
}

PropertySourceContext::PropertySourceContext(CvPropertySource * pSource, CvGameObject * pObject)
{
	m_iCurrentAmount = pObject->getPropertiesConst()->getValueByProperty(pSource->getProperty());
}

CvPropertySource * PropertySourceContext::getSource()
{
	return m_pSource;
}

CvGameObject * PropertySourceContext::getObject()
{
	return m_pObject;
}

int PropertySourceContext::getData1()
{
	return m_iData1;
}

int PropertySourceContext::getData2()
{
	return m_iData2;
}

void PropertySourceContext::setData1(int iData)
{
	m_iData1 = iData;
}

void PropertySourceContext::setData2(int iData)
{
	m_iData2 = iData;
}

void PropertySourceContext::doPredict(CvPropertySolver * pSolver)
{
	int iChange = m_pSource->getSourcePredict(m_pObject, m_iCurrentAmount, this);
	pSolver->addChange(m_pObject， m_pSource->getProperty(), iChange);
}

void PropertySourceContext::doCorrect(CvPropertySolver * pSolver)
{
	PropertyTypes eProperty = m_pSource->getProperty();
	int iPredicted = pSolver->getPredictValue(m_pObject, eProperty);
	int iChange = m_pSource->getSourceCorrect(m_pObject, m_iCurrentAmount, iPredicted, this);
	pSolver->addChange(m_pObject, eProperty, iChange);
}



