//
//	FILE:	 CvMapExternal.cpp
//	AUTHOR:  Steve Draper
//	PURPOSE: Game map externals class
//

#include "CvGameCoreDLL.h"
#include "CvMapInterfaceBase.h"
#include "CvMapExternal.h"
#include "CvMap.h"
#include "FProfiler.h"

CvMapExternal::CvMapExternal(CvMapInterfaceBase* proxiedMap) : 
	m_proxiedMap(NULL), m_bMapCoordinates(false);
{
}

CvMapExternal::CvMapExternal(CvMapInterfaceBase* proxiedMap) :
	m_proxiedMap(proxiedMap), m_bMapCoordinates(false);
{
}

// FUNCTION: init()
// Initializes the map.
// Parameters:
//	pInitData					- Optional init structure (used for WB load)
// Returns:
//	nothing.
void CvMapExternal::init(CvMapInitData* pInitData)
{
	m_proxiedMap->init(pInitData);
}

//////////////////////////////////////
// graphical only setup
//////////////////////////////////////
void CvMapExternal::setupGraphical()
{
	m_proxiedMap->setupGraphical();
}

// FUNCTION: reset()
// Initializes data members that are serialized.
void CvMapExternal::reset(CvMapInitData* pInitData)
{
	m_proxiedMap->reset(pInitData);
}

void CvMapExternal::earsePlots()
{
	m_proxiedMap->erasePlots();
}

void CvMapExternal::updateFlagSymbols()
{
	m_proxiedMap->updateFlagSymbols();
}

void CvMapExternal::updateFog()
{
	m_proxiedMap->updateFog();
}

void CvMapExternal::updateVisibility()
{
	m_proxiedMap->updateVisibility();
}

void CvMapExternal::updateSymbolVisibility()
{
	m_proxiedMap->updateSymbolVisibility();
}

void CvMapExternal::updateMinimapColor()
{
	m_proxiedMap->updateMinimapColor();
}

void CvMapExternal::updateCenterUnit()
{
	m_proxiedMap->updateCenterUnit();
}

CvCity * CvMapExternal::findCity(int iX, int iY, PlayerTypes eOwner, TeamTypes eTeam, bool bSameArea, bool bCoastalOnly, TeamTypes eTeamAtWarWith, DirectionTypes eDirection, CvCity * pSkipCity)
{
	return m_proxiedMap->findCity(iX, iY, eOwner, eTeam, bSameArea, bCoastalOnly, eTeamAtWarWith, eDirection, pSkipCity);
}

CvSelectionGroup * CvMapExternal::findSelectionGroup(int iX, int iY, PlayerTypes eOwner, bool bReadyToSelect, bool bWorkers)
{
	return m_proxiedMap->findSelectionGroup(iX, iY, eOwner, bReadyToSelect, bWorkers);
}

bool CvMapExternal::isPlot(int iX, int iY) const
{
	return m_proxiedMap->isPlot(iX, iY);
}

int CvMapExternal::numPlots() const
{
	return m_proxiedMap->numPlots();
}

int CvMapExternal::plotNum(int iX, int iY) const
{
	return m_proxiedMap->plotNum(iX, iY);
}

int CvMapExternal::pointXToPlotX(float fX)
{
	return m_proxiedMap->pointXToPlotX(fX);
}

float CvMapExternal::plotXToPointX(int iX)
{
	return m_proxiedMap->plotXToPointX(iX);
}

int CvMapExternal::pointYToPlotY(int iY)
{
	return m_proxiedMap->pointYToPlotY(iY);
}

float CvMapExternal::plotYToPointY(int iY)
{
	return m_proxiedMap->plotYToPointY(iY);
}

int CvMapExternal::getGridWidth() const
{
	return m_proxiedMap->getGridWidth();
}

int CvMapExternal::getGridHeight() const
{
	return m_proxiedMap->getGridHeight();
}

int CvMapExternal::getLandPlots()
{
	return m_proxiedMap->getLandPlots();
}

int CvMapExternal::getOwnedPlots()
{
	return m_proxiedMap->getOwnedPlots();
}

bool CvMapExternal::isWrapX()
{
	return m_proxiedMap->isWrapX();
}

bool CvMapExternal::isWrapY()
{
	return m_proxiedMap->isWrapY();
}

WorldSizeTypes CvMapExternal::getWorldSize()
{
	return  m_proxiedMap->getWorldSize();
}

ClimatTypes CvMapExternal::getClimate()
{
	return m_proxiedMap->getClimate();
}

SeaLevelTypes CvMapExternal::getSeaLevel()
{
	return m_proxiedMap->getSeaLevel();
}

int CvMapExternal::getNumCustomMapOptions()
{
	return m_proxiedMap->getNumCustomMapOptions();
}

CustomMapOptionTypes CvMapExternal::getCustomMapOption(int iOption)
{
	return m_proxiedMap->getCustomMapOption();
}

// Serialization:
void CvMapExternal::read(FDataStreamBase * pStream)
{
	PROFILE_FUNC();

	CvTaggedSaveFormatWrapper& wrapper = CvTaggedSaveFormatWrapper::getSaveFormatWrapper();

	wrapper.AttachToStream(pStream);

	bool bInitialized = false;
	bool bMultiMapFormat = false;

	WRAPPER_READ(wrapper, "CvMapExternal", &bMultiMapFormat);

	if (bMultiMapFormat)
	{
		for (int i = 0; i < GC.getNumMapInfos(); i++)
		{
			WRAPPER_READ(wrapper, "CvMapExternal", &bInitialized);

			if (bInitialized)
			{
				// If this is a load straight from the startup menus then only map 0 will
				// have been initialized, so any others in the save must be initialized too before
				// they can be loaded
				if (!GC.mapInitialized((MapTypes)i)) 
				{
					GC.initializeMap((MapTypes)i);
				}

				// Cast to the internal class
				CvMap& map = GC.getMapByIndex((MapTypes)i);

				map.read(pStream);
			}
		}
	}
	else
	{
		GC.getMapINLINE().read(pStream);
	}

	GC.getCurrentViewport()->setActionState(VIEW_ACTION_STATE_LOADING);
}

void CvMapExternal::write(FDataStreamBase * pStream)
{
	PROFILE_FUNC();
	
	CvTaggedSaveFormatWrapper& wrapper = CvTaggedSaveFormatWrapper::getSaveFormatWrapper();

	wrapper.AttachToStream(pStream);

	bool bMultiMapFormat = true;	// Always save in multimap foramt

	WRAPPER_WRITE(wrapper, "CvMapExternal", bMultiMapFormat);

	for (int iI = 0; iI < GC.getNumMapInfos(); iI++)
	{
		bool bInitialized = GC.mapInitialized((MapTypes)iI);

		WRAPPER_WRITE(wrapper, "CvMapExternal", bInitialized);

		if (bInitialized)
		{
			// Cast to the internal class
			CvMap& map = GC.getMapByIndex((MapType)iI);

			map.write(pStream);
		}
	}
}

CvPlot * CvMapExternal::plotByIndex(int iIndex) const
{
	FAssert(0 <= iIndex && iIndex < numPlots());
	CvPlot* result = m_proxiedMap->plotByIndex(iIndex);

	if (result == NULL)
	{
		OutputDebugString(CvString::format("	Plot at index [%d]: NULL\n", iIndex).c_str());
	}
	return result;
}

CvPlot * CvMapExternal::plot(int iX, int iY)
{
	CvPlot* result;

	if (!m_bMapCoordinates)
	{
		result = m_proxiedMap->getUnderlyingMap()->plot(iX, iY);
	}
	else
	{
		result = m_proxiedMap->plot(iX, iY);
	}
	return result;
}

CvPlot * CvMapExternal::pointToPlot(float fX, float fY)
{
	return m_proxiedMap->pointToPlot(fX, fY);
}

int CvMapExternal::getNumAreas()
{
	return m_proxiedMap->getNumAreas();
}

int CvMapExternal::getNumLandAreas()
{
	return m_proxiedMap->getNumLandAreas();
}
