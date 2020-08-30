//  $Header:
//------------------------------------------------------------------------------------------------
//
//  FILE:    CvPropertyPropagator.cpp
//
//  PURPOSE: Propagator of generic properties for Civ4 classes
//
//------------------------------------------------------------------------------------------------

#include "CvGameCoreDLL.h"
#include "CvPropertyPropagator.h"
#include "CvXMLLoadUtility.h"
#include "CvDLLXMLIFaceBase.h"
#include "CvGameTextMgr.h"
#include "CvGameObject.h"

CvPropertyPropagator::CvPropertyPropagator() :
	m_eProperty(NO_PROPERTY),
	m_eObjecType(NO_GAMEOBJECT),
	m_eRelation(NO_RELATION),
	m_iRelationData(0),
	m_eTargetRelation(NO_RELATION),
	m_eTargetObjectType(NO_GAMEOBJECT),
	m_iTargetRelationData(0),
	m_pExprActive(NULL),
	m_pExprTargetCondition(NULL)
{
}

CvPropertyPropagator::CvPropertyPropagator(PropertyTypes eProperty) :
	m_eProperty(NO_PROPERTY),
	m_eObjecType(NO_GAMEOBJECT),
	m_eRelation(NO_RELATION),
	m_iRelationData(0),
	m_eTargetRelation(NO_RELATION),
	m_eTargetObjectType(NO_GAMEOBJECT),
	m_iTargetRelationData(0),
	m_pExprActive(NULL),
	m_pExprTargetCondition(NULL)
{
}

CvPropertyPropagator::~CvPropertyPropagator()
{
	GC.removeDelayedresolution((int*)&m_eProperty);
	SAFE_DELETE(m_pExprActive);
}

PropertyTypes CvPropertyPropagator::getProperty() const
{
	return m_eProperty;
}

void CvPropertyPropagator::setProperty(PropertyTypes eProperty)
{
	m_eProperty = eProperty;
}
