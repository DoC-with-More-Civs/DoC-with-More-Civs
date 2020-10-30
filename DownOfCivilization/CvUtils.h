// CvUtils.h

#ifndef _CvUtils_H_
#define _CvUtils_H_

#include "config_pymodules.h"
#include "config_py2cpp.h"

// Forward declare
class CvPlot;
class CvCity;
class CvUnit;

class CvUtils {

public:
	// RiseAndFall, Religions, Congresses
	static PlayerTypes getHumanID(void);

	static int getTurns(int turns);
	static void getCitiesInCore(PlayerTypes iPlayer, std::vector<CvCity*>& lCities, boost::tribool bReborn = None);
	static void getOwnedCoreCities(PlayerTypes iPlayer, std::vector<CvCity*>& lCities, boost::tribool bReborn = None);

	static void getAreaCities(std::vector<CvPlot*>& lPlots, std::vector<CvCity*>& lCities);
	static void getAreaCitiesCiv(PlayerTypes iCiv, std::vector<CvPlot*>& lPlots, std::vector<CvCity*>& lCities);

	static void clearPlague(PlayerTypes iCiv);

	static void flipOrRelocateGarrison(CvCity* city, int iNumDefenders, std::vector<CvUnit*>& lFlippedUnits, std::vector<CvUnit*>& lRelocatedUnits);
	static void flipOrCreateDefenders(PlayerTypes iNewOwner, std::vector<CvUnit*>& lUnits, int x, int y, int iNumDefenders);
	static void relocateSeaGarrisons(coord tCityPlot, PlayerTypes iOldOwner);

	static void getCityList(PlayerTypes iCiv, std::vector<CvCity*>& lCities);
	static void getUnitList(CvPlot* tPlot, std::vector<CvUnit*>& lUnits);

	static void flipUnits(std::vector<CvUnit*>& lUnits, PlayerTypes iNewOwner, int x, int y);
	static void makeUnit(UnitTypes iUnit, PlayerTypes iPlayer, int x, int y, int iNum, CvWString sAdj = L"", int iExp = 0);
	static void killUnits(std::vector<CvUnit*> lUnits);

	static void relocateUnitsToCore(PlayerTypes iPlayer, std::vector<CvUnit*>& lUnits);
	static void flipUnitsInCityBefore(coord tCityPlot, PlayerTypes iNewOwner, PlayerTypes iOldOwner);
	static void flipUnitsInCityAfter(coord tCityPlot, PlayerTypes iCiv);
	
	static void completeCityFlip(int x, int y, PlayerTypes iCiv, PlayerTypes iOwner, int iCultureChange,
		bool bBarbarianDecay = true, bool bBarbarianConversion = false, bool bAlwaysOwnPlots = false,
		bool bFlipUnits = false, bool bPermanentCultureChange = true);

	static void cultureManager(int x, int y, int iCulturePercent, PlayerTypes iNewOwner, PlayerTypes iOldOwner,
		bool bBarbarian2x2Decay, bool bBarbarian2x2Conversion, bool bAlwaysOwnPlots);

	static void resetUHV(PlayerTypes iCiv);

	static void surroundingPlots(coord tPlot, std::vector<CvPlot*>& lPlots, int iRaiuds = 1);

	static void linreg(std::vector<coord >& lHistory, double &a, double &b);

	static bool canRespawn(PlayerTypes iCiv);

	static bool isUniqueBuilding(BuildingTypes iBuilding);

	static bool isNeighbor(PlayerTypes iPlayer, PlayerTypes other);

	static UnitTypes getUniqueUnitType(PlayerTypes iPlayer, UnitClassTypes iUnitClass);

	static UnitTypes getBestInfantry(PlayerTypes iPlayer);
	static UnitTypes getBestCavalry(PlayerTypes iPlayer);
	static UnitTypes getBestSiege(PlayerTypes iPlayer);
	static UnitTypes getBestCounter(PlayerTypes iPlayer);
	static UnitTypes getBestDefender(PlayerTypes iPlayer);
	static UnitTypes getBaseUnit(UnitTypes iUnit);

	static int calculateDistance(int x1, int y1, int x2, int y2);

	static void removeReligionByArea(std::vector<coord > lPlotList, ReligionTypes iReligion);

	static void pushOutGarrisons(coord tCityPlot, PlayerTypes iOldOwner);
	static void createGarrisons(coord tCityPlot, PlayerTypes iNewOwner, int iNumUnits);
};

#endif