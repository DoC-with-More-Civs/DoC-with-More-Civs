//  $Header:
//------------------------------------------------------------------------------------------------
//
//  FILE:    CvPropertySource.cpp
//
//  PURPOSE: Source of generic properties for Civ4 classes
//
//------------------------------------------------------------------------------------------------

#include "CvGameCoreDLL.h"
#include "CvPropertySource.h"
#include "CvGameObject.h"
#include "CvXMLLoadUtilityModTools.h"
#include "CvXMLLoadUtility.h"
#include "CvDLLXMLIFaceBase.h"
#include "CvGameTextMgr.h"
#include "CvPropertySolver.h"
#include "CvEnums.h"
//#include "BoolExpr.h"
//#include "IntExpr.h"
#include "FDataStreamBase.h"


CvPropertySource::CvPropertySource() :
	m_eProperty(NO_PROPERTY),
	m_eObjectType(NO_GAMEOBJECT),
	m_eRelation(NO_RELATION),
	m_iRelationData(0),
	m_pExprActive(NULL)
{
}

CvPropertySource::CvPropertySource(PropertyTypes eProperty) :
	m_eProperty(eProperty),
	m_eObjectType(NO_GAMEOBJECT),
	m_eRelation(NO_RELATION),
	m_iRelationData(0),
	m_pExprActive(NULL)
{
}

CvPropertySource::~CvPropertySource()
{
	GC.removeDelayedResolution((int*)&m_eProperty);
	SAFE_DELETE(m_pExprActive);
}

PropertyTypes CvPropertySource::getProperty()
{
	return m_eProperty;
}

void CvPropertySource::setProperty(PropertyTypes eProperty)
{
	m_eProperty = eProperty
}

GameObjectTypes CvPropertySource::getObjectType() const
{
	return m_eObjectType;
}

void CvPropertySource::setObjectType(GameObjectTypes eObjectType)
{
	m_eObjectType = eObjectType;
}

RelationTypes CvPropertySource::getRelation() const
{
	return m_eRelation;
}

void CvPropertySource::setRelation(RelationTypes eRelation)
{
	m_eRelation = eRelation;
}

int CvPropertySource::getRelationData() const
{
	return m_iRelationData;
}

void CvPropertySource::setRelationData(int iRelationData)
{
	m_iRelationData = iRelationData;
}

bool CvPropertySource::isActive(CvGameObject * pObject)
{
	if ((m_eObjectType == NO_GAMEOBJECT) || m_eObjectType == pObject->getGameObjectType())
	{
		if (m_pExprActive)
			return m_pExprActive->evaluate(pObject);
		else
			return true;
	}
	return false;
}

void CvPropertySource::buildDisplayString(CvWStringBuffer & szBuffer) const
{
	if ((m_eRelation != NO_RELATION) || (m_pExprActive))
	{
		szBuffer.append(" (");
		if (m_eRelation != NO_RELATION)
		{
			GAMETEXT.buildGameObjectRealtionString(szBuffer, m_eObjectType, m_eRelation, m_iRelationData);
		}
		if (m_pExprActive)
		{
			if (m_eRelation != NO_RELATION)
				szBuffer.append(", ");
			szBuffer.append(gDLL->getText("TXT_KEY_PROPERTY_ACTIVE"));
			m_pExprActive->buildDispalyString(szBuffer);
		}
		szBuffer.append(")");
	}
}

void CvPropertySource::read(FDataStreamBase * pStream)
{
	pStream->Read((int*)&m_eProperty);
	pStream->Read((int*)&m_eObjectType);
	pStream->Read((int*)&m_eRelation);
	pStream->Read(&m_iRelationData);
	bool bExpr = false;
	pStream->Read(&bExpr);
	if (bExpr)
		m_pExprActive = BoolExpr::readExpression(pStream);
}

void CvPropertySource::write(FDataStreamBase * pStream)
{
	pStream->Write(m_eProperty);
	pStream->Write(m_eObjectType);
	pStream->Write(m_eRelation);
	pStream->Write(m_iRelationData);
	if (m_pExprActive)
	{
		pStream->Write(true);
		m_pExprActive->Write(pStream);
	}
	else
	{
		pStream->Write(false);
	}
}

bool CvPropertySource::read(CvXMLLoadUtility * pXML)
{
	CvString szTextVal;
	pXML->GetChildXmlValByName(szTextVal, "PropertyType");
	GC.addDelayedResolution((int*)&m_eProperty, szTextVal);
	pXML->GetChildXmlValByName(szTextVal, "GameObjectType");
	m_eObjectType = (GameObjectTypes)pXML->FindInInfoClass(szTextVal);
	pXML->GetChildXmlValByName(szTextVal, "RelationType");
	m_eRelation = (RelationTypes)pXML->FindInInfoClass(szTextVal);
	if (m_eRelation == RELATION_NEAR)
		pXML->GetChildXmlValByName(&m_iRelationData, "iDistance");
	if (GETXML->SetToChildTagName(pXML->GetXML(), "Active");
	{
		m_pExprActive = BoolExpr::read(pXML);
		GETXML->SetToParent(pXML->GetXML());
	}
	return true;
}

void CvPropertySource::copyNonDefaults(CvPropertySource * pProp, CvXMLLoadUtility * pXML)
{
	GC.copyNonDefaultDelayedResolution((int*)&m_eProperty, (int*)&(pProp->m_eProperty));

	if (m_eObjectType == NO_GAMEOBJECT)
		m_eObjectType = pProp->getObjectType();
	if (m_eRelation == NO_RELATION)
		m_eRelation = pProp->getRelation();
	if (m_iRelationData == 0)
		m_iRelationData = pProp->getRelationData();
	if (m_pExprActive == NULL)
	{
		m_pExprActive = pProp->m_pExprActive;
		pProp->m_pExprActive = NULL;
	}
}

void CvPropertySource::getCheckSum(unsigned int & iSum)
{
	CheckSum(iSum, m_eProperty);
}

CvPropertySourceConstant::CvPropertySourceConstant() :
	CvPropertySource(), m_pAmountPerTurn(NULL)
{
}

CvPropertySourceConstant::CvPropertySourceConstant(PropertyTypes eProperty) :
	CvPropertySource(eProperty), m_pAmountPerTurn(NULL)
{
}

CvPropertySourceConstant::CvPropertySourceConstant(PropertyTypes eProperty, IntExpr * pAmountPerTurn) :
	CvPropertySource(eProperty), m_pAmountPerTurn(pAmountPerTurn)
{

}

int CvPropertySourceConstant::getAmountPerTurn(const CvGameObject * pObject)
{
	return m_pAmountPerTurn->evaluate(const_cast<CvGameObject*>(pObject));
}

PropertySourceTypes CvPropertySourceConstant::getType()
{
	return PROPERTYSOURCE_CONSTANT;
}

int CvPropertySourceConstant::getSourcePredict(const CvGameObject * pObject, int iCurrentAmount, PropertySourceContext * pContext)
{
	// We store the expression result in thr property source context to make sure it stay constant in between prediction and correction
	int iAmountPerTurn = getAmountPerTurn(pObject);
	if (pContext)
		pContext->setData1(iAmountPerTurn);
	return iAmountPerTurn;
}

int CvPropertySourceConstant::getSourceCorrect(const CvGameObject * pObject, int iCurrentAmmont, int iPredictedAmount, PropertySourceContext * pContext)
{
	int iAmounPerTurn;
	if (pContext)
		iAmounPerTurn = pContext->getData1();
	else
		iAmounPerTurn = getAmountPerTurn(pObject);
	return iAmounPerTurn;
}

void CvPropertySourceConstant::buildDisplayString(CvWStringBuffer & szBuffer) const
{
	m_pAmountPerTurn->buildDisplayString(szBuffer);
	szBuffer.append(" ");
	szBuffer.append(GC.getPropertyInfo(getProperty()).getChar());
	szBuffer.append(" ");
	szBuffer.append(gDLL->getText("TXT_KEY_PROPERTY_PER_TURN"));
	CvPropertySource::buildDisplayString(szBuffer);
}

void CvPropertySourceConstant::read(FDataStreamBase * pStream)
{
	CvPropertySource::read(pStream);
	m_pAmountPerTurn = IntExpr::readExpression(pStream);
}

void CvPropertySourceConstant::write(FDataStreamBase * pStream)
{
	CvPropertySource::write(pStream);
	m_pAmountPerTurn->write(pStream);
}

bool CvPropertySourceConstant::read(CvXMLLoadUtility * pXML)
{
	CvPropertySource::read(pXML);
	if (GETXML->SetChilidByTagName(pXML->GetXML(), "iAmountPerTurn"))
	{
		m_pAmountPerTurn = IntExpr::read(pXML);
		GETXML->SetToParent(pXML->GetXML());
	}
	return true;
}

void CvPropertySourceConstant::copyNonDefaults(CvPropertySource * pProp, CvXMLLoadUtility * pXML)
{
	CvPropertySource::copyNonDefaults(pProp, pXML);
	CvPropertySourceConstant* pOther = static_cast<CvPropertySourceConstant*>(pProp);
	if (m_pAmountPerTurn == NULL)
	{
		m_pAmountPerTurn = pOther->m_pAmountPerTurn;
		pOther->m_pAmountPerTurn = NULL;
	}
}

void CvPropertySourceConstant::getCheckSum(unsigned int & iSum)
{
	CvPropertySource::getCheckSum(iSum);
	m_pAmountPerTurn->getCheckSum(iSum);
}

CvPropertySourceConstantLimited::CvPropertySourceConstantLimited() :
	CvPropertySource(), m_iAmountPerTurn(0), m_iLimit(0)
{
}
