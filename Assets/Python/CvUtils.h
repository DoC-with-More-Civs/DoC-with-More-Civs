// CvUtils.h

class CvUtils {
	
public:
	static int getTurns(int turns);
	static void getCitiesInCore(PlayerTypes iPlayer, bool bReborn);
	static void getOwnedCoreCities(PlayerTypes iPlayer, bool bReborn);
	
	static void getAreaCities(std::vector<CvPlot*>& lPlots, std::vecotr<CvCity*> lCities);
	static void getAreaCitiesCiv(PlayerTypes iCiv, std::vector<CvPlot*>& lPlots, std::vector<CvCity*>& lCities);
	
	static void clearPlague(PlayerTypes iCiv);
	
	void flipOrRelocateGarrison(CvCity* city, int iNumDefenders std::vector<CvUnit*>& lFlippedUnits, std::vector<CvUnit*>& lRelocatedUnits);
};

int CvUtils::getTurns(int turns) // edead
{
	// Returns the amount of turns modified adequately for the game's speed.
	//	Values are based on CIV4GameSpeedInfos.xml. Use this only for durations,  intervals etc.; 
	//	for year->turn conversions, use the DLL function getTurnForYear(int year).
	int iGameSpeed = GC.getGameINLINE().getGameSpeed();
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
void CvUtils::getCitiesInCore(PlayerTypes iPlayer, bool bReborn, std::vecotr<CvCity*>& lCities)
{
	lCities.clear();
	std::vector<CvPlot*> lPlot;
	
	CvArea::getCoreArea(iPlayer, bReborn, lPlot);
	for (int i = 0; i < lPlot.size(); i++)
	{
		CvPlot* plot = lPlot[i];
		if (plot->isCity())
			lCities.append(plot->getPlotCity());
	}
}

// Leoreth
void CvUtils::getOwnedCoreCities(PlayerTypes iPlayer, bool bReborn, std::vector<CvCity*>& lCities)
{
	lCities.clear();
	std::vector<CvCity*> cities;
	
	getCitiesInCore(iPlayer, bReborn, cities);
	for (int i = 0; i < cities.size(); i++)
	{
		CvCity* pCity = cities[i];
		if (pCity->getOwnerINLINE() == iPlayer)
			lCities.append(pCity);
	}
}

void CvUtils::getAreaCities(std::vector<CvPlot*>& lPlots, std::vecotr<CvCity*> lCities)
{
	lCities.clear();
	for (int i = 0; i < lPlots.size(); i++)
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
	for (int i = 0; i < lCity.size(); i++)
	{
		CvCity* pCity = lCity[i];
		if (pCity->getOnwer() == iCiv)
			lCities.append(pCity);
	}
}

void CvUtils::clearPlague(PlayerTypes iCiv)
{
	CvPlayer& pPlayer = GET_PLAYER(iCiv);
	int iLoop = 0;
	for (CvCity* pCity = pPlayer.firstCity(&iLoop); pCity != NULL; pCity = pPlayer.nextCity(&iLoop)
	{
		if (pCity->isHasBuilding(iPlague))
			pCity->setHasRealBuilding(iPlague, false);
	}
}

void CvUitls::flipOrRelocateGarrison(CvCity* city, int iNumDefenders std::vector<CvUnit*>& lFlippedUnits, std::vector<CvUnit*>& lRelocatedUnits)
{
	int x = city->getX();
	int y = city->getY();
	
	lRelocatedUnits.clear();
	lFlippedUnits.clear();
	
	std::vector<
	
	
}

void surroundingPlots(std::pair<int, int> tPlot, int iRaiuds = 1, std::vector<CvPlot*> lPlots, boost:function<bool(int, int)> filter)
{
	int x = tPlot.first();
	int y = tPlot.second();
	
	for 
}
