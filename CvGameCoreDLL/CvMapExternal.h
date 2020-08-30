#pragma once

#ifndef CIV4_MAP_EXTERNAL_H
#define CIV4_MAP_EXTERNAL_H

//
//	FILE:	 CvMapExternal.h
//	AUTHOR:  Steve Draper
//	PURPOSE: Game map externals class
//

//#include "CvArea.h"
//#include "CvPlot.h"
//#include "CvMapInterfaceBase.h"
#include <map>

struct CvMapInitData;
class CvCity;
class CvPlot;
class FAStar;
class CvPlotGroup;
class CvSelectionGroup;
class CvMapInterfaceBase;
//
// CvMap
//
class CvMapExternal
{
	friend class CyMap;

public:

	CvMapExternal(CvMapInterfaceBase* proxiedMap);

	void mapCoordiantes(bool bNewValue) { m_bMapCoordinates = bNewValue; }

	DllExport CvMapExternal();
	DllExport virtual ~CvMapExternal() {}

	DllExport void init(CvMapInitData* pInitData = NULL);
	DllExport void setupGraphical();
	DllExport void reset(CvMapInitData* pInitData);

	DllExport void earsePlots();
	DllExport void updateFlagSymbols();

	DllExport void updateFog();
	DllExport void updateVisibility();
	DllExport void updateSymbolVisibility();
	DllExport void updateMinimapColor();
	DllExport void updateCenterUnit();
	DllExport CvCity* findCity(int iX, int iY, PlayerTypes eOwner = NO_PLAYER, TeamTypes eTeam = NO_TEAM, bool bSameArea = true, bool bCoastalOnly = false, TeamTypes eTeamAtWarWith = NO_TEAM, DirectionTypes eDirection = NO_DIRECTION, CvCity* pSkipCity = NULL);
	DllExport CvSelectionGroup* findSelectionGroup(int iX, int iY, PlayerTypes eOwner = NO_PLAYER, bool bReadyToSelect = false, bool bWorkers = false);
	DllExport bool isPlot(int iX, int iY) const;
	DllExport int numPlots() const;
	DllExport int plotNum(int iX, int iY) const;
	DllExport int pointXToPlotX(float fX);
	DllExport float plotXToPointX(int iX);
	DllExport int  pointYToPlotY(int iY);
	DllExport float plotYToPointY(int iY);
	DllExport int getGridWidth() const;
	DllExport int getGridHeight() const;
	DllExport int getLandPlots();
	DllExport int getOwnedPlots();
	DllExport bool isWrapX();
	DllExport bool isWrapY();
	DllExport WorldSizeTypes getWorldSize();
	DllExport ClimatTypes getClimate();
	DllExport SeaLevelTypes getSeaLevel();

	DllExport int getNumCustomMapOptions();
	DllExport CustomMapOptionTypes getCustomMapOption(int iOption);
	DllExport CvPlot* plotByIndex(int iIndex) const;
	DllExport CvPlot* plot(int iX, int iY);
	DllExport CvPlot* pointToPlot(float fX, float fY);
	DllExport int getNumAreas();
	DllExport int getNumLandAreas();
	// Serialization:
	DllExport virtual void read(FDataStreamBase* pStream);
	DllExport virtual void write(FDataStreamBase* pStream);

private:
	CvMapInterfaceBase* m_proxiedMap;
	mutable std::map<int, CvPlot*> m_psuedoPlots;
	bool m_bMapCoordinates;
};

#endif
