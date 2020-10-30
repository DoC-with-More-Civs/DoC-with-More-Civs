#include "DownOfCivilization.h"
#define CV_DOC_LIB extern "C" _declspec(dllexport)
#include "config_pymodules.h"
#include "config_py2cpp.h"


PlayerTypes CvUtils::getHumanID(void)
{
	return GC.getGameINLINE().getActivePlayer();
}

int CvUtils::getTurns(int turns) // edead
{
	// Returns the amount of turns modified adequately for the game's speed.
	//	Values are based on CIV4GameSpeedInfos.xml. Use this only for durations,  intervals etc.; 
	//	for year->turn conversions, use the DLL function getTurnForYear(int year).
	int iGameSpeed = GC.getGameINLINE().getGameSpeedType();
	if (iGameSpeed == 2) return turns;	// normal
	else if (iGameSpeed == 1)	// epic
	{
		if (turns == 3)	return 5;	// getTurns(6) must be a multiple of getTurns(3) for turn divisors in Stability.py
		else if (turns == 6) return 10;
		else return (turns * 3 / 2);
	}
	else if (iGameSpeed == 0) return (turns * 3);	// marathon
	//else if (iGameSpeed == 3) return (turns * 2 / 3); // quick
	return turns;
}

// Leoreth
void CvUtils::getCitiesInCore(PlayerTypes iPlayer, std::vector<CvCity*>& lCities, boost::tribool bReborn)
{
	lCities.clear();
	std::vector<coord > lPlot;

	Areas.getCoreArea(iPlayer, lPlot, bReborn);
	for (unsigned int i = 0; i < lPlot.size(); i++)
	{
		CvPlot* plot = GC.getMapINLINE().plot(lPlot[i].first, lPlot[i].second);
		if (plot->isCity())
			lCities.append(plot->getPlotCity());
	}
}

// Leoreth
void CvUtils::getOwnedCoreCities(PlayerTypes iPlayer, std::vector<CvCity*>& lCities, boost::tribool bReborn)
{
	lCities.clear();
	std::vector<CvCity*> cities;

	getCitiesInCore(iPlayer, cities, bReborn);
	for (unsigned int i = 0; i < cities.size(); i++)
	{
		CvCity* pCity = cities[i];
		if (pCity->getOwnerINLINE() == iPlayer)
			lCities.append(pCity);
	}
}

void CvUtils::getAreaCities(std::vector<CvPlot*>& lPlots, std::vector<CvCity*>& lCities)
{
	lCities.clear();
	for (unsigned int i = 0; i < lPlots.size(); i++)
	{
		CvPlot* plot = lPlots[i];
		if (plot->isCity())
			lCities.append(plot->getPlotCity());
	}
}

void CvUtils::getAreaCitiesCiv(PlayerTypes iCiv, std::vector<CvPlot*>& lPlots, std::vector<CvCity*>& lCities)
{
	std::vector<CvCity*> lCity;
	getAreaCities(lPlots, lCity);
	for (unsigned int i = 0; i < lCity.size(); i++)
	{
		CvCity* pCity = lCity[i];
		if (pCity->getOwner() == iCiv)
			lCities.append(pCity);
	}
}

void CvUtils::clearPlague(PlayerTypes iCiv)
{
	CvPlayer& pPlayer = GET_PLAYER(iCiv);
	int iLoop = 0;
	for (CvCity* pCity = pPlayer.firstCity(&iLoop); pCity != NULL; pCity = pPlayer.nextCity(&iLoop))
	{
		if (pCity->hasBuilding(iPlague))
			pCity->setHasRealBuilding(iPlague, false);
	}
}

void CvUtils::flipOrRelocateGarrison(CvCity * city, int iNumDefenders, std::vector<CvUnit*>& lFlippedUnits, std::vector<CvUnit*>& lRelocatedUnits)
{
	int x = city->getX();
	int y = city->getY();

	lRelocatedUnits.clear();
	lFlippedUnits.clear();

	std::vector<CvPlot*> lPlots;
	surroundingPlots(std::make_pair(x, y), lPlots, 2);
	for (unsigned int i = 0; i < lPlots.size(); i++)
	{
		CvPlot* tPlot = lPlots[i];
		std::vector<CvUnit*> lUnits;
		getUnitList(tPlot, lUnits);
		for (unsigned int j = 0; j < lUnits.size(); j++)
		{
			CvUnit* unit = lUnits[j];
			if ((not tPlot->isCity() or tPlot->getPlotCity() != city) and
				unit->getOwnerINLINE() == city->getOwnerINLINE() and
				unit->getDomainType() == DOMAIN_LAND)
				lFlippedUnits.append(unit);
			else
				lRelocatedUnits.append(unit);
		}
	}
}

void CvUtils::flipOrCreateDefenders(PlayerTypes iNewOwner, std::vector<CvUnit*>& lUnits, int x, int y, int iNumDefenders)
{
	flipUnits(lUnits, iNewOwner, x, y);

	if (lUnits.size() < (unsigned int)iNumDefenders and getHumanID() != iNewOwner)
	{
		UnitTypes iDefender = getBestDefender(iNewOwner);
		if (VAL_IN(GC.getMapINLINE().plot(x, y)->getRegionID(), lNewWorld))
			if (iDefender == iCrossbowman)
				if (not VAL_IN(true, data.m_lFirstContactConquerors))
					iDefender = iArcher;
		makeUnit(iDefender, iNewOwner, x, y, iNumDefenders - lUnits.size());
	}
}

void CvUtils::getCityList(PlayerTypes iCiv, std::vector<CvCity*>& lCities)
{
	if (iCiv <= -1 or iCiv >= MAX_PLAYERS) lCities.clear();
	int iLoop;
	CvPlayer& pPlayer = GET_PLAYER(iCiv);
	for (CvCity* pCity = pPlayer.firstCity(&iLoop); pCity != NULL; pCity = pPlayer.nextCity(&iLoop))
		lCities.append(pCity);
}

// Makes iNum units for player iPlayer of the type iUnit at tCoords.
void CvUtils::makeUnit(UnitTypes iUnit, PlayerTypes iPlayer, int x, int y, int iNum, CvWString sAdj, int iExp)
{
	for (int i = 0; i < iNum; i++)
	{
		CvPlayer& pPlayer = GET_PLAYER(iPlayer);
		CvUnit* unit = pPlayer.initUnit(iUnit, x, y, NO_UNITAI, DIRECTION_SOUTH);
		if (sAdj != L"")
		{
			CvWString szBuffer;
			szBuffer.Format(L"%s %s", gDLL->getText(sAdj), unit->getName());
			unit->setName(szBuffer.GetCString());
		}
		if (iExp > 0)
			unit->changeExperience(iExp, 100, false, false, false);
			
	}
}

void CvUtils::killUnits(std::vector<CvUnit*> lUnits)
{
	for (uint i = 0; i < len(lUnits); i++)
	{
		CvUnit* unit = lUnits[i];
		if (unit->getX() >= 0 and unit->getY() >= 0)
			unit->kill(false, iBarbarian);
	}
}

void CvUtils::relocateUnitsToCore(PlayerTypes iPlayer, std::vector<CvUnit*>& lUnits)
{
	std::vector<CvCity*> lCoreCities;
	getOwnedCoreCities(iPlayer, lCoreCities);
	std::map<UnitTypes, std::vector<CvUnit*> > dUnits;

	if (lCoreCities.empty())
	{
		killUnits(lUnits);
		return;
	}

	for (unsigned int i = 0; i < len(lUnits); i++)
	{
		CvUnit* unit = lUnits[i];
		if (unit->plot()->getOwner() == iPlayer or
			unit->plot()->getOwner() == NO_PLAYER)
			continue;

		UnitTypes iUnitType = unit->getUnitType();
		if (dUnits.count(iUnitType))
		{
			if (not VAL_IN(unit, dUnits[iUnitType]))
				dUnits[iUnitType].append(unit);
		}
		else
		{
			dUnits[iUnitType] = list_of(unit);
		}
	}

	std::map<UnitTypes, std::vector<CvUnit*> >::const_iterator it;
	for (it = dUnits.begin(); it != dUnits.end(); it++)
	{
		UnitTypes i = it->first;
		std::vector<CvUnit*> lUnits = it->second;
		for (uint j = 0; j < lUnits.size(); j++)
		{
			uint index = j % (lCoreCities.size() * 2);
			CvUnit* unit = lUnits[j];
			if (index < lCoreCities.size())
			{
				CvCity* city = lCoreCities[index];
				if (unit->getX() >= 0 and unit->getY() >= 0 and
					(unit->getX() != city->getX(), unit->getY() != city->getY()))
					unit->setXY(city->getX(), city->getY(), false, true, true);
			}
		}
	}
}

/*
Converts the culture of the city and of the surrounding plots to the new owner of a city.
iCulturePercent determine the percentage that goes to the new owner.
If old owner is barbarian, all the culture is converted
*/
void CvUtils::cultureManager(int x, int y, int iCulturePercent, PlayerTypes iNewOwner, PlayerTypes iOldOwner, bool bBarbarian2x2Decay, bool bBarbarian2x2Conversion, bool bAlwaysOwnPlots)
{
	// city
	if (GC.getMapINLINE().plot(x, y)->isCity())
	{
		CvCity* city = GC.getMap().plot(x, y)->getPlotCity();
		int iCurrentCityCulture = city->getCulture(iOldOwner);
		city->setCulture(iOldOwner, iCurrentCityCulture*(100 - iCulturePercent) / 100, false, true);

		if (iNewOwner != iBarbarian)
			city->setCulture(iBarbarian, 0, true, true);

		city->setCulture(iNewOwner, iCurrentCityCulture*iCulturePercent / 100, false, true);
		if (city->getCulture(iNewOwner) <= 10)
			city->setCulture(iNewOwner, 20, false, true);
	}
	
	// halve barbarian culture in a broader area
	if (bBarbarian2x2Decay or bBarbarian2x2Conversion)
	{
		if (iNewOwner != iBarbarian or iNewOwner != iIndependent or iNewOwner != iIndependent2)
		{
			std::vector<CvPlot*> lPlots;
			surroundingPlots(std::make_pair(x, y), lPlots, 2);
			for (unsigned int i = 0; i < lPlots.size(); i++)
			{
				CvPlot* tCityPlot = lPlots[i];
				bool bCity = (GC.getMapINLINE().plot(x, y)->getPlotCity() != NULL or (x == tCityPlot->getX(), y == tCityPlot->getY()));
				if (bCity)
				{
					std::vector<PlayerTypes> lMinor =  (list_of(iBarbarian), iIndependent, iIndependent2);
					for (unsigned int i = 0; i < lMinor.size(); i++)
					{
						PlayerTypes iMinor = lMinor[i];
						int iMinorCulture = GC.getMapINLINE().plot(x, y)->getCulture(iMinor);
						if (iMinorCulture > 0)
						{
							if (bBarbarian2x2Decay)
								GC.getMapINLINE().plot(x, y)->setCulture(iMinor, iMinorCulture / 4, true, true);
							if (bBarbarian2x2Conversion)
							{
								GC.getMapINLINE().plot(x, y)->setCulture(iMinor, 0, true, true);
								GC.getMapINLINE().plot(x, y)->setCulture(iNewOwner, iMinorCulture, true, true);
							}
						}
					}
				}

			}
		}

	}
			
	// plot
	std::vector<CvPlot*> lPlots;
	surroundingPlots(std::make_pair(x, y), lPlots);
	for (unsigned int i = 0; i < lPlots.size(); i++)
	{
		CvPlot* pPlot = lPlots[i];
		int iCurrentPlotCulture = pPlot->getCulture(iOldOwner);
		if (pPlot->isCity())
		{
			pPlot->setCulture(iNewOwner, iCurrentPlotCulture*iCulturePercent / 100, true, true);
			pPlot->setCulture(iOldOwner, iCurrentPlotCulture*(100 - iCulturePercent) / 100, true, true);
		}
		else
		{
			pPlot->setCulture(iNewOwner, iCurrentPlotCulture*iCulturePercent / 3 / 100, true, true);
			pPlot->setCulture(iOldOwner, iCurrentPlotCulture*(100 - iCulturePercent / 3) / 100, true, true);
		}

		if (bAlwaysOwnPlots)
			pPlot->setOwner(iNewOwner, false, true);
		else if (pPlot->getCulture(iNewOwner) * 4 > pPlot->getCulture(iOldOwner))
			pPlot->setOwner(iNewOwner, false, true);
	}
}

void CvUtils::completeCityFlip(int x, int y, PlayerTypes iCiv, PlayerTypes iOwner, int iCultureChange, bool bBarbarianDecay, bool bBarbarianConversion, bool bAlwaysOwnPlots, bool bFlipUnits, bool bPermanentCultureChange)
{
	CvPlot* tPlot = GC.getMapINLINE().plot(x, y);

	tPlot->setRevealed(GET_PLAYER(iCiv).getTeam(), false, true, NO_TEAM, true);

	if (bPermanentCultureChange)
		cultureManager(x, y, iCultureChange, iCiv, iOwner, bBarbarianDecay, bBarbarianConversion, bAlwaysOwnPlots);

	if (bFlipUnits)
		flipUnitsInCityBefore(std::make_pair(tPlot->getX(), tPlot->getY()), iCiv, iOwner);
	else
	{
		pushOutGarrisons(std::make_pair(tPlot->getX(), tPlot->getY()), iOwner);
		relocateSeaGarrisons(std::make_pair(tPlot->getX(), tPlot->getY()), iOwner);
	}
	
	// error
	//flipCity(tPlot, false, false, iCiv, [iOwner]);

	if (bFlipUnits)
		flipUnitsInCityAfter(std::make_pair(tPlot->getX(), tPlot->getY()), iCiv);
	else
		createGarrisons(std::make_pair(tPlot->getX(), tPlot->getY()), iCiv, 2);

	tPlot->setRevealed(GET_PLAYER(iCiv).getTeam(), true, true, NO_TEAM, true);
}

// Congresses, RiseAndFall
void CvUtils::pushOutGarrisons(coord tCityPlot, PlayerTypes iOldOwner) {
	int x = tCityPlot.first;
	int y = tCityPlot.second;
	coord tDestination = std::make_pair(-1, -1);

	std::vector<CvPlot*> lPlots;
	surroundingPlots(tCityPlot, lPlots, 2);
	// remove tPlot == tCityPlot
	for (int i = 0; i < len(lPlots); i++) {
		if (lPlots[i]->getX() == x && lPlots[i]->getY() == y) {
			lPlots.erase(lPlots.begin() + i);
			break;
		}
	}

	for (int k = 0; k < (int)lPlots.size(); k++) {
		CvPlot* pDestination = lPlots[k];
		int i = pDestination->getX();
		int j = pDestination->getY();
		if (pDestination->getOwner() == iOldOwner and not pDestination->isWater() and not pDestination->isImpassable()) {
			tDestination = std::make_pair(i, j);
			break;
		}
			
		if (tDestination.first != -1 and tDestination.second != -1) {
			CvPlot* plotCity = GC.getMapINLINE().plot(x, y);
			int iNumUnitsInAPlot = plotCity->getNumUnits();
			for (int iUnit = iNumUnitsInAPlot - 1; iUnit >= 0; iUnit--) {
				CvUnit* unit = plotCity->getUnitByIndex(iUnit);
				if (unit->getDomainType() == DOMAIN_LAND)
					unit->setXY(tDestination.first, tDestination.second, False, True, False);
			}
		}
	}
}

// Congresses, RiseAndFall
void CvUtils::relocateSeaGarrisons(coord tCityPlot, PlayerTypes iOldOwner) {
	int x = tCityPlot.first;
	int y = tCityPlot.second;
	coord tDestination = std::make_pair(-1, -1);
	std::vector<CvCity*> lCities;
	getCityList(iOldOwner, lCities);
	for (int i = 0; i < len(lCities); i++) {
		CvCity* city = lCities[i];
		if (city->isCoastalOld() and city->getX() != x and city->getY() != y)
			tDestination = std::make_pair(city->getX(), city->getY());
	}
	if (tDestination.first != -1 and tDestination.second != -1) {
		CvPlot* plotCity = GC.getMapINLINE().plot(x, y);
		int iNumUnitsInAPlot = plotCity->getNumUnits();
		for (int iUnit = iNumUnitsInAPlot - 1; iUnit >= 0; iUnit--) {
			CvUnit* unit = plotCity->getUnitByIndex(iUnit);
			if (unit->getOwner() == iOldOwner and unit->getDomainType() == DOMAIN_SEA)
				unit->setXY(tDestination.first, tDestination.second, False, True, False);
		}
	}
}

void CvUtils::flipUnitsInCityBefore(coord tCityPlot, PlayerTypes iNewOwner, PlayerTypes iOldOwner)
{
	CvPlot* plotCity = GC.getMapINLINE().plot(tCityPlot.first, tCityPlot.second);
	CvCity* city = plotCity->getPlotCity();
	int iNumUnitsInAPlot = plotCity->getNumUnits();
	std::vector<UnitTypes> lFlipUnits;
	int j = 0;
	for (int i = 0; i < iNumUnitsInAPlot; i++)
	{
		CvUnit* unit = plotCity->getUnitByIndex(j);
		UnitTypes unitType = unit->getUnitType();
		if (unit->getOwner() == iOldOwner)
		{
			unit->kill(False, iBarbarian);
			if (iNewOwner < iNumPlayers or unitType > iSettler)
				lFlipUnits.append(unitType);
		}
	}
	data.m_lFlippingUnits = lFlipUnits;
}

void CvUtils::flipUnitsInCityAfter(coord tCityPlot, PlayerTypes iCiv) {
	// moves new units back in their place
	// debug
	for (int i = 0; i < len(data.m_lFlippingUnits); i++) {
		UnitTypes iUnitType = data.m_lFlippingUnits[i];
		makeUnit(iUnitType, iCiv, tCityPlot.first, tCityPlot.second, 1);
	}
	data.m_lFlippingUnits.clear();
}

UnitTypes CvUtils::getBaseUnit(UnitTypes iUnit) {
	return (UnitTypes)GC.getUnitClassInfo((UnitClassTypes)GC.getUnitInfo(iUnit).getUnitClassType()).getDefaultUnitIndex();
}

// Congresses, RiseAndFall
void CvUtils::createGarrisons(coord tCityPlot, PlayerTypes iNewOwner, int iNumUnits) {
	int x = tCityPlot.first;
	int	y = tCityPlot.second;

	UnitTypes iUnitType = getBestDefender(iNewOwner);

	makeUnit(iUnitType, iNewOwner, x, y, iNumUnits);
}
	

void CvUtils::resetUHV(PlayerTypes iCiv)
{
	if (iCiv < NUM_PLAYERS)
		for (int i = 0; i < 3; i++)
			if (data.m_players[iCiv].getGoal(i) == -1)
				data.m_players[iCiv].setGoal(i, 0);
}

void CvUtils::getUnitList(CvPlot* tPlot, std::vector<CvUnit*>& lUnits)
{
	for (int i = 0; i < tPlot->getNumUnits(); i++)
	{
		lUnits.append(tPlot->getUnitByIndex(i));
	}
}

void CvUtils::surroundingPlots(coord tPlot, std::vector<CvPlot*>& lPlots, int iRaiuds)
{
	int x = tPlot.first;
	int y = tPlot.second;
	for (int i = x - iRaiuds; i < iRaiuds + 1; i++)
	{
		for (int j = y - iRaiuds; j < iRaiuds + 1; j++)
		{
			if (0 <= j and j < iWorldY)
				lPlots.append(GC.getMapINLINE().plot((i % iWorldX), j));
		}
	}
}

void CvUtils::linreg(std::vector<coord>& lHistory, double & a, double & b)
{
	int n = lHistory.size();
	if (n < 2) a = b = 0.0;
	double sx = 0.0; double sy = 0.0; 
	double sxx = 0.0; double syy = 0.0; double sxy = 0.0;
	for (int i = 0; i < n; i++)
	{
		int x = lHistory[i].first;
		int y = lHistory[i].second;
		sx += x;
		sy += y;
		sxx += x * x;
		syy += y * y;
		sxy += x * y;
	}
	double det = n * sxx - sx * sx;
	a = (n * sxy - sy * sx);
	b = (sxx * sy - sx * sxy);
}

bool CvUtils::isUniqueBuilding(BuildingTypes iBuilding)
{
	if (isWorldWonderClass((BuildingClassTypes)GC.getBuildingInfo(iBuilding).getBuildingClassType()))
		return true;

	if (isTeamWonderClass((BuildingClassTypes)GC.getBuildingInfo(iBuilding).getBuildingClassType()))
		return true;

	if (isNationalWonderClass((BuildingClassTypes)GC.getBuildingInfo(iBuilding).getBuildingClassType()))
		return true;

	// Regular building
	return false;
}

bool CvUtils::isNeighbor(PlayerTypes iPlayer, PlayerTypes other)
{
	return GET_PLAYER(iPlayer).isNeighbor(other);
}

UnitTypes CvUtils::getBestInfantry(PlayerTypes iPlayer)
{
	CvPlayer& pPlayer = GET_PLAYER(iPlayer);
	std::vector<UnitTypes> lInfantryList = (list_of(iInfantry), iRifleman, iMusketeer, iArquebusier, iPikeman, iHeavySwordsman, iCrossbowman, iSwordsman, iLightSwordsman, iMilitia);
	
	for (uint i = 0; i < lInfantryList.size(); i++)
	{
		UnitTypes iUnit = getUniqueUnitType(iPlayer, (UnitClassTypes)GC.getUnitInfo(lInfantryList[i]).getUnitClassType());
		if (pPlayer.canTrain(iUnit, false, false))
			return iUnit;
	}
	return iMilitia;
}

UnitTypes CvUtils::getBestCavalry(PlayerTypes iPlayer)
{
	CvPlayer& pPlayer = GET_PLAYER(iPlayer);
	std::vector<UnitTypes> lCavalryList = (list_of(iCavalry), iDragoon, iHussar, iCuirassier, iPistolier, iLancer, iHorseArcher, iHorseman, iChariot);
	
	for (uint i = 0; i < lCavalryList.size(); i++)
	{
		UnitTypes iUnit = getUniqueUnitType(iPlayer, (UnitClassTypes)GC.getUnitInfo(lCavalryList[i]).getUnitClassType());
		if (pPlayer.canTrain(iUnit, false, false))
			return iUnit;
	}
	return iMilitia;
}

UnitTypes CvUtils::getBestSiege(PlayerTypes iPlayer)
{
	CvPlayer& pPlayer = GET_PLAYER(iPlayer);
	std::vector<UnitTypes> lSiegeList = (list_of(iHowitzer), iArtillery, iCannon, iBombard, iTrebuchet, iCatapult);

	for (uint i = 0; i < lSiegeList.size(); i++)
	{
		UnitTypes iUnit = getUniqueUnitType(iPlayer, (UnitClassTypes)GC.getUnitInfo(lSiegeList[i]).getUnitClassType());
		if (pPlayer.canTrain(iUnit, false, false))
			return iUnit;
	}
	return iMilitia;
}

UnitTypes CvUtils::getBestCounter(PlayerTypes iPlayer)
{
	CvPlayer& pPlayer = GET_PLAYER(iPlayer);
	std::vector<UnitTypes> lCounterList = (list_of(iMarine), iGrenadier, iPikeman, iHeavySpearman, iSpearman);

	for (uint i = 0; i < lCounterList.size(); i++)
	{
		UnitTypes iUnit = getUniqueUnitType(iPlayer, (UnitClassTypes)GC.getUnitInfo(lCounterList[i]).getUnitClassType());
		if (pPlayer.canTrain(iUnit, false, false))
			return iUnit;
	}
	return iMilitia;
}

UnitTypes CvUtils::getBestDefender(PlayerTypes iPlayer)
{
	if (iPlayer == iBarbarian) iPlayer = iIndependent;
	CvPlayer& pPlayer = GET_PLAYER(iPlayer);
	std::vector<UnitTypes> lDefenderList = (list_of(iInfantry), iMachineGun, iRifleman, iMusketeer, iArquebusier, iCrossbowman, iArcher, iMilitia);

	for (uint i = 0; i < lDefenderList.size(); i++)
	{
		UnitTypes iUnit = getUniqueUnitType(iPlayer, (UnitClassTypes)GC.getUnitInfo(lDefenderList[i]).getUnitClassType());
		if (pPlayer.canTrain(iUnit, false, false))
			return iUnit;
	}
	return iMilitia;
}

int CvUtils::calculateDistance(int x1, int y1, int x2, int y2)
{
	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	return std::max(dx, dy);
}

void CvUtils::removeReligionByArea(std::vector<coord> lPlotList, ReligionTypes iReligion)
{
	std::vector<CvPlot*> lPlots;
	for (int i = 0; i < (int)lPlotList.size(); i++) {
		lPlots.push_back(GC.getMapINLINE().plot(lPlotList[i].first, lPlotList[i].second));
	}
	std::vector<CvCity*> lCityList;
	getAreaCities(lPlots, lCityList);

	for (uint i = 0; i < lCityList.size(); i++)
	{
		CvCity* city = lCityList[i];
		if (city->isHasReligion(iReligion) and not city->isHolyCity())
			city->setHasReligion(iReligion, false, false, false);
		if (city->hasBuilding((BuildingTypes)(iTemple + iReligion * 4)))
			city->setHasRealBuilding((BuildingTypes)(iTemple + iReligion * 4), false);
		if (city->hasBuilding((BuildingTypes)(iCathedral + iReligion * 4)))
			city->setHasRealBuilding((BuildingTypes)(iCathedral + iReligion * 4), false);
		if (city->hasBuilding((BuildingTypes)(iMonastery + iReligion * 4)))
			city->setHasRealBuilding((BuildingTypes)(iMonastery + iReligion * 4), false);
	}
}

UnitTypes CvUtils::getUniqueUnitType(PlayerTypes iPlayer, UnitClassTypes iUnitClass)
{
	CvPlayer& pPlayer = GET_PLAYER(iPlayer);
	return (UnitTypes)GC.getCivilizationInfo(pPlayer.getCivilizationType()).getCivilizationUnits(iUnitClass);
}

bool CvUtils::canRespawn(PlayerTypes iPlayer)
{
	int iGameTurn = GC.getGameINLINE().getGameTurn();

	// no re spawn before spawn
	if (iGameTurn < getGameTurnForYear(tBirth[iPlayer], GC.getGameINLINE().getStartYear(), GC.getGameINLINE().getCalendar(), GC.getGameINLINE().getGameSpeedType()) + 10)
		return false;
	
	// only dead civ need to check for resurrection
	if (GET_PLAYER(iPlayer).isAlive())
		return false;

	// check if only recently died
	if (iGameTurn - getStability.getLastTurnAlive(iPlayer) < getTurns(10))
		return false;

	//  check if the civ can be reborn at this date
	if (tResurrectionIntervals[iPlayer].size())
	{
		std::vector<coord >::const_iterator it;
		for (it = tResurrectionIntervals[iPlayer].begin(); it != tResurrectionIntervals[iPlayer].end(); it++)
		{
			int iStart = it->first;
			int iEnd = it->second;
			if (getTurnForYear(iStart) <= iGameTurn and
				iGameTurn <= getTurnForYear(iEnd))
				break;
			else
				return false;
		}
	}
	else return false;

	// Thailand can not re spawn when Khmer is alive and vice versa
	if (iPlayer == iThailand and GET_PLAYER(iKhmer).isAlive())
		return false;
	if (iPlayer == iKhmer and GET_PLAYER(iThailand).isAlive())
		return false;

	// Rome can not re spawn when Italy is alive an vice versa
	if (iPlayer == iRome and GET_PLAYER(iItaly).isAlive())
		return false;
	if (iPlayer == iItaly and GET_PLAYER(iRome).isAlive())
		return false;

	// Greece can not re spawn when Byzantium is alive an vice versa
	if (iPlayer == iGreece and GET_PLAYER(iByzantium).isAlive())
		return false;
	if (iPlayer == iByzantium and GET_PLAYER(iGreece).isAlive())
		return false;

	// India cannot respawn when Mughals are alive (not vice versa -> Pakistan)
	if (iPlayer == iIndia and GET_PLAYER(iMughals).isAlive())
		return false;

	// Egypt can not re spawn when Mamluks is alive an vice versa
	if (iPlayer == iEgypt and GET_PLAYER(iMamluks).isAlive())
		return false;
	if (iPlayer == iMamluks and GET_PLAYER(iEgypt).isAlive())
		return false;

	// Exception during Japanese UHV
	if (getHumanID() == iJapan and iGameTurn >= getTurnForYear(1920) and iGameTurn <= getTurnForYear(1945))
	{
		std::vector<PlayerTypes> lPlayer = (list_of(iChina), iManchuria, iKorea, iIndonesia, iThailand);
		if (VAL_IN(iPlayer, lPlayer))
			return false;
	}

	if (not GET_PLAYER(iPlayer).isAlive() and iGameTurn > getStability.getLastStabilityTurn(iPlayer) + getTurns(20))
	{
		if (not dRebirth.count(iPlayer) or iGameTurn > getTurnForYear(dRebirth[iPlayer]) + 10)
			return true;
	}
		
	return false;
}

void CvUtils::flipUnits(std::vector<CvUnit*>& lUnits, PlayerTypes iNewOwner, int x, int y)
{
	
}

// error : popup 怎么调用和创建
//void CvUtils::showPopup(int popupID, CvWString title, CvWString message, std::vector<CvWString> labels)
//{
//	CvPopop* pPopop = new CvPopop;
//	gDLL->getInterfaceIFace()->popupSetHeaderString(pPopup, title);
//	gDLL->getInterfaceIFace()->popupSetBodyString(pPopup, message);
//	for (int i = 0; i < labels.size(); i++)
//	{
//		gDLL->getInterfaceIFace()->popupAddGenericButton(pPopop, labels[i]);
//	}
//	gDLL->getInterfaceIFace()->popupLaunch(pPopup, false, POPUPSTATE_IMMEDIATE);
//}

/*
// RiseAndFall
void pushOutGarrisons(self, tCityPlot, iOldOwner)
{
	coord tDestination = std::make_pair(-1, -1);
	for x in range(tCityPlot[0]-2, tCityPlot[0]+3):
		for y in range(tCityPlot[1]-2, tCityPlot[1]+3):
			pDestination = gc.getMap().plot(x, y)
			if (pDestination.getOwner() == iOldOwner and (not pDestination.isWater()) and (not pDestination.isImpassable())):
				tDestination = (x, y)
				break
				break
	if (tDestination != (-1, -1)):
		plotCity = gc.getMap().plot(tCityPlot[0], tCityPlot[1])
		iNumUnitsInAPlot = plotCity.getNumUnits()
		j = 0;
		for i in range(iNumUnitsInAPlot):
			unit = plotCity.getUnit(j)
			if (unit.getDomainType() == 2): #land unit
				unit.setXY(tDestination[0], tDestination[1], False, False, False)
			else
				j = j + 1;
}
*/
