#include "DownOfCivilization.h"
#define CV_DOC_LIB extern "C" _declspec(dllexport)
#include "config_py2cpp.h"
#include "config_pymodules.h"

// from StoredData import data # edead

//import DynamicCivs as dc

//import RegionMap
//import Victory as vic

//import BugPath
//from datetime import date

// getter & Setter

int CvStatbility::getTurnsToCollapse(PlayerTypes eIndex) {
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_iTurnsToCollapse[pos];
}

void CvStatbility::changeTurnsToCollapse(PlayerTypes eIndex, int iChange) {
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iTurnsToCollapse[pos] += iChange;
}

void CvStatbility::setTurnsToCollapse(PlayerTypes eIndex, int iNewValue) {
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iTurnsToCollapse[pos] = iNewValue;
}

int CvStatbility::getCrisisCountdown(PlayerTypes eIndex) {
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_iCrisisCountdown[pos];
}

void CvStatbility::changeCrisisCountdown(PlayerTypes eIndex, int iChange)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iCrisisCountdown[pos] += iChange;
}

int CvStatbility::getHumanRazePenalty(void)
{
	return m_iHumanRazePenalty;
}

void CvStatbility::changeHumanRazePenalty(int iChange)
{
	m_iHumanRazePenalty += iChange;
}

int CvStatbility::getBarbarianLosses(PlayerTypes eIndex)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_iBarbarianLosses[pos];
}

void CvStatbility::changeBarbarianLosses(PlayerTypes eIndex, int iChange)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iBarbarianLosses[pos] += iChange;
}

void CvStatbility::setHumanStability(int iNewValue)
{
	m_iHumanStability = iNewValue;
}

void CvStatbility::getSecedingCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities)
{	
	lCities = m_lSecedingCities[eIndex];
}

void CvStatbility::setSecedingCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities)
{
	m_lSecedingCities[eIndex] = lCities;
}

int CvStatbility::getRomanPigs(void)
{
	return m_iRomanPigs;
}

void CvStatbility::setRomanPigs(int iNewValue)
{
	m_iRomanPigs = iNewValue;
}

int CvStatbility::getNumPreviousCities(PlayerTypes eIndex)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_iNumPreviousCities[pos];
}

void CvStatbility::setNumPreviousCities(PlayerTypes eIndex, int iNewValue)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iNumPreviousCities[pos] = iNewValue;
}

int CvStatbility::getLastStability(PlayerTypes eIndex) {
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_iLastStability[pos];
}

void CvStatbility::setLastStability(PlayerTypes eIndex, int iNewValue) {
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iLastStability[pos] = iNewValue;
}

int CvStatbility::getLastStabilityTurn(PlayerTypes eIndex)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_iLastStabilityTurn[pos];
}

void CvStatbility::setLastStabilityTurn(PlayerTypes eIndex, int iNewTurn)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iLastStabilityTurn[pos] = iNewTurn;
}

std::list<int>& CvStatbility::getEconomyTrend(PlayerTypes eIndex)
{
	return m_lEconomyTrend[eIndex];
}

std::list<int>& CvStatbility::getHappinessTrend(PlayerTypes eIndex)
{
	return m_lHappinessTrend[eIndex];
}

int CvStatbility::getPreviousCommerce(PlayerTypes eIndex) {
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_iPreviousCommerce[pos];
}

void CvStatbility::setPreviousCommerce(PlayerTypes eIndex, int iNewValue) {
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iPreviousCommerce[pos] = iNewValue;
}

void CvStatbility::resetEconomyTrend(PlayerTypes eIndex)
{
	m_lEconomyTrend[eIndex].clear();
}

void CvStatbility::resetHappinessTrend(PlayerTypes eIndex)
{
	m_lHappinessTrend[eIndex].clear();
}

void CvStatbility::resetWarTrends(PlayerTypes eIndex)
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_lWarTrend[eIndex][i].clear();
	}
}

void CvStatbility::resetWarTrends(PlayerTypes eIndex, PlayerTypes iEnemy)
{
	m_lWarTrend[eIndex][iEnemy].clear();
}

void CvStatbility::pushEconomyTrend(PlayerTypes eIndex, int iValue)
{
	m_lEconomyTrend[eIndex].push_back(iValue);
	if (m_lEconomyTrend[eIndex].size() > 10)
		m_lEconomyTrend[eIndex].pop_front();
}

void CvStatbility::pushHappinessTrend(PlayerTypes eIndex, int iValue)
{
	m_lHappinessTrend[eIndex].push_back(iValue);
	if (m_lHappinessTrend[eIndex].size() > 10)
		m_lHappinessTrend[eIndex].pop_front();
}

void CvStatbility::pushWarTrend(PlayerTypes eIndex, PlayerTypes iEnemy, int iValue)
{
	m_lWarTrend[eIndex][iEnemy].push_back(iValue);
	if (m_lWarTrend[eIndex][iEnemy].size() > 10)
	{
		m_lWarTrend[eIndex][iEnemy].pop_front();
	}
}

std::list<int>& CvStatbility::getWarTrend(PlayerTypes eIndex, PlayerTypes iEnemy)
{
	return m_lWarTrend[eIndex][iEnemy];
}

int CvStatbility::getWarStartTurn(PlayerTypes eIndex, PlayerTypes iEnemy)
{
	return m_lWarStartTurn[eIndex][iEnemy];
}


int CvStatbility::getLastTurnAlive(PlayerTypes eIndex)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_iLastTurnAlive[pos];
}

void CvStatbility::setLastTurnAlive(PlayerTypes eIndex, int iNewTurn)
{
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	m_iLastTurnAlive[pos] = iNewTurn;
}

void CvStatbility::setLastWarSuccess(PlayerTypes eIndex, PlayerTypes iEnemy, int iValue)
{
	m_lLastWarSuccess[eIndex][iEnemy] = iValue;
}

//

CvStatbility::CvStatbility(void) {
	m_tEraCorePopulationModifiers = (
		list_of(100), // ancient
		200, // classical
		200, // medieval
		250, // renaissance
		300, // industrial
		350, // modern
		400  // future
	);

	m_iTurnsToCollapse = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_iBarbarianLosses = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_iCrisisCountdown = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_iNumPreviousCities = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_iLastStabilityTurn = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_iPreviousCommerce = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_iLastStability = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_iLastTurnAlive = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
}

CvStatbility::~CvStatbility(void) {
	free(m_iTurnsToCollapse);
	free(m_iBarbarianLosses);
	free(m_iCrisisCountdown);
	free(m_iNumPreviousCities);
	free(m_iLastStabilityTurn);
	free(m_iPreviousCommerce);
	free(m_iLastStability);
	free(m_iLastTurnAlive);
}

void CvStatbility::doTurn(int iGameTurn) {

	int iPlayer;
	#pragma omp parallel for
	for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++) {
		if (getTurnsToCollapse((PlayerTypes)iPlayer) == 0) {
			changeTurnsToCollapse(((PlayerTypes)iPlayer), -1);
			completeCollapse((PlayerTypes)iPlayer); // ÐèÒª¸ÄÔì
		}
		else if (getTurnsToCollapse((PlayerTypes)iPlayer) > 0) {
			changeTurnsToCollapse(((PlayerTypes)iPlayer), -1);
		}
		if (getCrisisCountdown((PlayerTypes)iPlayer) > 0)
			changeCrisisCountdown(((PlayerTypes)iPlayer), -1);
	}

	if (iGameTurn % getTurns(3) == 0) {
		int iPlayer;
		#pragma omp parallel for
		for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++) {
			// calculate economic and happiness stability
			updateEconomyTrend((PlayerTypes)iPlayer);
			updateHappinessTrend((PlayerTypes)iPlayer);

			// calculate war stability
			for (int iEnemy = 0; iEnemy < NUM_PLAYERS; iEnemy++) {
				if (GET_TEAM(GET_PLAYER((PlayerTypes)iPlayer).getTeam()).isAtWar(GET_PLAYER((PlayerTypes)iEnemy).getTeam())) {
					updateWarTrend((PlayerTypes)iPlayer, (PlayerTypes)iEnemy);
					setLastWarSuccess((PlayerTypes)iPlayer, (PlayerTypes)iEnemy, GET_TEAM(
						GET_PLAYER((PlayerTypes)iPlayer).getTeam()).AI_getWarSuccess(GET_PLAYER((PlayerTypes)iEnemy).getTeam()));
				}
				else {
					setLastWarSuccess((PlayerTypes)iPlayer, (PlayerTypes)iEnemy, 0);
				}
			}
		}
	}

	// decay penalties from razing cities and losing to barbarians
	if (iGameTurn % getTurns(5) == 0) {
		if (getHumanRazePenalty() < 0)
			changeHumanRazePenalty(2);
		int iPlayer;
		#pragma omp parallel for
		for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++) {
			if (getBarbarianLosses((PlayerTypes)iPlayer) > 0)
				changeBarbarianLosses((PlayerTypes(iPlayer)), -1);
		}
	}

	if (iGameTurn % getTurns(12) == 0) {
		int iPlayer;
		#pragma omp parallel for
		for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++) {
			checkLostCitiesCollapse((PlayerTypes)iPlayer);
		}
	}

	if (iGameTurn >= getTurnForYear(tBirth[getHumanID()])) {
		int iStability;
		std::vector<int> lStabilityTypes;
		std::vector<int> lParameters;

		calculateStability(getHumanID(), iStability, lStabilityTypes, lParameters);
		setHumanStability(iStability);
	}
}

void CvStatbility::endTurn(PlayerTypes eIndex)
{
	std::vector<CvCity*> lSecedingCities;
	getSecedingCities(eIndex, lSecedingCities);

	if (lSecedingCities.size()) {
		secedeCities(eIndex, lSecedingCities);
		setSecedingCities(eIndex, std::vector<CvCity*>());
	}
}

void CvStatbility::triggerCollapse(PlayerTypes eIndex)
{
	// help over expanding AI: collapse to core, unless fall date
	if (getHumanID() != eIndex) {
		if (GC.getGameINLINE().getGameTurnYear() < tFall[eIndex]) {
			std::vector<CvCity*> lCities;
			CvUtils::getOwnedCoreCities(eIndex, lCities);
			if (lCities.size() < (uint)GET_PLAYER(eIndex).getNumCities()) {
				collapseToCore(eIndex); 
				return;
			}
		}
	}

	// Spread Roman pigs on Celtia's complete collapse
	if (getRomanPigs() < 0 and eIndex == iCeltia) setRomanPigs(1);

	scheduleCollapse(eIndex);
}

void CvStatbility::scheduleCollapse(PlayerTypes eIndex)
{
	setTurnsToCollapse(eIndex, 1);
	// save collapse file ÓÐÎÄÃ÷±ÀÀ£Ê±´æµµ
	//CvWStringBuffer epoch = L"BC";
	//if (GC.getGameINLINE().getGameTurnYear() > 0) epoch = L"AD";
	//{
	//	;//
	//}
}

void CvStatbility::onCityAcquired(CvCity* city, PlayerTypes iOwner, PlayerTypes iPlayer)
{
	checkStability(iOwner);

	checkLostCoreCollapse(iOwner);

	if (iPlayer == iBarbarian)
		checkBarbarianCollapse(iOwner);
}

void CvStatbility::onCityRazed(PlayerTypes iPlayer, CvCity* city)
{
	int iOwner = city->getPreviousOwner();

	if (iOwner == iBarbarian) return;

	if (getHumanID() == iPlayer and iPlayer != iMongolia)
	{
		int iRazePenalty = -10;
		if (city->getHighestPopulation() < 5 and not city->isCapital())
			iRazePenalty = -2 * city->getHighestPopulation();

		if (iOwner >= NUM_PLAYERS) iRazePenalty /= 2;

		changeHumanRazePenalty(iRazePenalty);

		checkStability(iPlayer);
	}
}

void CvStatbility::onTechAcquired(PlayerTypes iPlayer, int iTech)
{
	checkStability(iPlayer);
}

void CvStatbility::onVassalState(PlayerTypes iMaster, PlayerTypes iVassal)
{
	checkStability(iMaster, true);

	balanceStability(iVassal, iStabilityShaky);
}
// error : teamID != playerID
void CvStatbility::onChangeWar(bool bWar, PlayerTypes iTeam, PlayerTypes iOtherTeam)
{
	if (iTeam < NUM_PLAYERS and iOtherTeam < NUM_PLAYERS)
	{
		checkStability(iTeam, not bWar);
		checkStability(iOtherTeam, not bWar);

		if (bWar)
		{
			startWar(iTeam, iOtherTeam);
			startWar(iOtherTeam, iTeam);
		}
	}
}

void CvStatbility::onRevolution(PlayerTypes iPlayer)
{
	checkStability(iPlayer);
}

void CvStatbility::onPlayerChangeStateReligion(PlayerTypes iPlayer)
{
	checkStability(iPlayer);
}

void CvStatbility::onPalaceMoved(PlayerTypes iPlayer)
{
	checkStability(iPlayer);
}

void CvStatbility::onWonderBuilt(PlayerTypes iPlayer, int iBuildingType)
{
	checkStability(iPlayer);
}

void CvStatbility::onGoldenAge(PlayerTypes iPlayer)
{
	checkStability(iPlayer);
}

void CvStatbility::onGreatPersonBorn(PlayerTypes iPlayer)
{
	checkStability(iPlayer);
}

void CvStatbility::onCombatResult(PlayerTypes iWinningPlayer, PlayerTypes iLosingPlayer, int iLostPower)
{
	if (iWinningPlayer == iBarbarian and iLosingPlayer < NUM_PLAYERS)
		changeBarbarianLosses(iLosingPlayer, 1);
}

void CvStatbility::onCivSpawn(PlayerTypes iPlayer)
{
	for (unsigned int i = 0; i < lOlderNeighbours[iPlayer].size(); i++)
	{
		PlayerTypes iOlderNeighbor = lOlderNeighbours[iPlayer][i];
		if (GET_PLAYER(iOlderNeighbor).isAlive() and
			getStabilityLevel(iOlderNeighbor) > iStabilityShaky)
			decrementStability(iOlderNeighbor);
	}
}

PlayerTypes CvStatbility::getHumanID()
{
	return GC.getGameINLINE().getActivePlayer();
}

int CvStatbility::getTurns(int turns)
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

StabilityLevels CvStatbility::getStabilityLevel(PlayerTypes eIndex)
{
	return m_eStabilityLevel[eIndex];
}

void CvStatbility::setStabilityLevel(PlayerTypes eIndex, StabilityLevels eStabilityLevel)
{
	m_eStabilityLevel[eIndex] = eStabilityLevel;

	if (eStabilityLevel == iStabilityCollapsing)
	{
		//gDLL->getInterfaceIFace()->addMessage(eIndex, false, iDuration, gDLL->getText("TXT_KEY_STABILITY_COLLAPSING_WARNING"), "", 0, "", ColorTypes(iRed), -1, -1, true, true);
	}
}

void CvStatbility::incrementStability(PlayerTypes eIndex)
{
	setStabilityLevel(eIndex, std::min(iStabilitySolid, (StabilityLevels)(getStabilityLevel(eIndex) + 1)));
}

void CvStatbility::decrementStability(PlayerTypes eIndex)
{
	setStabilityLevel(eIndex, std::max(iStabilityCollapsing, (StabilityLevels)(getStabilityLevel(eIndex) - 1)));
}

bool CvStatbility::isImmune(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iGameTurn = GC.getGameINLINE().getGameTurn();

	// must not be dead
	if (not pPlayer.isAlive() or pPlayer.getNumCities() == 0)
		return true;

	// only for major civs
	if (eIndex >= NUM_PLAYERS)
		return true;

	// immune right after scenario start
	if (iGameTurn - getScenarioStartTurn() < getTurns(20))
		return true;

	// immune right after birth
	if ((iGameTurn - getTurnForYear(tBirth[eIndex])) < getTurns(20))
		return true;

	// immune right after resurrection
	if ((iGameTurn - pPlayer.getLatestRebellionTurn()) < getTurns(10))
		return true;

	return false;
}

void CvStatbility::checkBarbarianCollapse(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iGameTurn = GC.getGameINLINE().getGameTurn();

	if (isImmune(eIndex)) return;

	int iNumCities = pPlayer.getNumCities();
	int iLostCities = 0;

	int iLoop = 0;
	for (CvCity* pLoopCity = pPlayer.firstCity(&iLoop); pLoopCity != NULL; pLoopCity = pPlayer.nextCity(&iLoop))
		if (pLoopCity->getOriginalOwner() == eIndex)
			iLostCities += 1;

	// lost more than half of your cities to barbarians: collapse
	if (iLostCities > iNumCities)
	{
		// debugTextPopup
		completeCollapse(eIndex);
	}
	else if (iLostCities >= 2)
	{
		// debugTextPopup
		decrementStability(eIndex);
	}
}

void CvStatbility::checkLostCitiesCollapse(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iGameTurn = GC.getGameINLINE().getGameTurn();

	if (isImmune(eIndex)) return;

	int iNumCurrentCities = pPlayer.getNumCities();
	int iNumPreviousCities = getNumPreviousCities(eIndex);

	// half or less cities than 12 turns ago: collapse (exceptions for civs with
	// very little cities to begin with -> use lost core collapse
	if (iNumPreviousCities > 2 and (2 * iNumCurrentCities <= iNumPreviousCities))
	{
		if (getStabilityLevel(eIndex) == iStabilityCollapsing)
		{
			// debugTextPopup
			scheduleCollapse(eIndex);
		}
		else
		{
			// debugTextPopup
			setStabilityLevel(eIndex, iStabilityCollapsing);
			collapseToCore(eIndex);
		}
	}
		
	setNumPreviousCities(eIndex, iNumCurrentCities);
}

void CvStatbility::checkLostCoreCollapse(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iGameTurn = GC.getGameINLINE().getGameTurn();

	if (isImmune(eIndex)) return;

	std::vector<coord > tPlots;
	Areas.getCoreArea(eIndex, tPlots);

	std::vector<CvPlot*> lPlots;
	for (unsigned int i = 0; i < tPlots.size(); i++)
		lPlots.push_back(GC.getMapINLINE().plot(tPlots[i].first, tPlots[i].second));

	std::vector<CvCity*> lCities;
	CvUtils::getAreaCitiesCiv(eIndex, lPlots, lCities);

	// completely pushed out of core: collapse
	if (len(lCities) == 0)
	{
		if ((eIndex == iPhoenicia or eIndex == iKhmer) and not pPlayer.isReborn())
		{
		pPlayer.setReborn(true);
		}
		// debugTextPopup
		scheduleCollapse(eIndex);
	}
}

StabilityLevels CvStatbility::determineStabilityLevel(StabilityLevels eCurrentLevel, int iStability, bool bFall)
{
	int iThreshold = 10 * eCurrentLevel - 10;

	if (bFall) iThreshold += 10;

	if (iStability >= iThreshold) return std::min(iStabilitySolid, StabilityLevels(eCurrentLevel + 1));
	else if (bFall) return std::max(iStabilityCollapsing, StabilityLevels(eCurrentLevel - (iThreshold - iStability) / 10));
	else if (iStability < (iThreshold - 10)) return std::max(iStabilityCollapsing, StabilityLevels(eCurrentLevel - 1));

	return eCurrentLevel;
}

void CvStatbility::checkStability(PlayerTypes eIndex, bool bPositive, int iMaster)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iGameTurn = GC.getGameINLINE().getGameTurn();

	bool bVassal = (iMaster != -1);

	// no check if already scheduled for collapse
	if (getTurnsToCollapse(eIndex) >= 0) return;

	// vassal checks are made for triggers of their master civs
	if (GET_TEAM(pPlayer.getTeam()).isAVassal() and not bVassal) return;

	if (isImmune(eIndex)) return;

	// immune to negative stability checks in golden ages
	if (pPlayer.isGoldenAge()) bPositive = true;

	// immune during anarchy
	if (pPlayer.isAnarchy()) return;

	// no repeated stability checks
	if (getLastStabilityTurn(eIndex) == iGameTurn) return;

	setLastStabilityTurn(eIndex, iGameTurn);

	int iStability;
	std::vector<int> lStabilityTypes;
	std::vector<int> lParameters(iNumStabilityParameters, 0);

	calculateStability(eIndex, iStability, lStabilityTypes, lParameters);

	StabilityLevels iStabilityLevel = getStabilityLevel(eIndex);
	bool bHuman = (getHumanID() == eIndex);
	bool bFall = isDecline(eIndex);

	StabilityLevels iNewStabilityLevel = determineStabilityLevel(iStabilityLevel, iStability, bFall);

	if (iNewStabilityLevel > iStabilityLevel)
		setStabilityLevel(eIndex, iNewStabilityLevel);
	else if (not bPositive) {
		if (iNewStabilityLevel == iStabilityCollapsing)
			if (iStability < getLastStability(eIndex))
				triggerCollapse(eIndex);

		if (iNewStabilityLevel < iStabilityLevel)
			setStabilityLevel(eIndex, iNewStabilityLevel);
	}
	
	// update stability information
	setLastStability(eIndex, iStability);
	for (int i = 0; i < iNumStabilityLevels; i++)
		m_lStabilityCategoryValues[eIndex][i] = lStabilityTypes[i];

	for (int i = 0; i < iNumStabilityParameters; i++)
		pPlayer.setStabilityParameter((ParameterTypes)i, lParameters[i]);

	// check vassals
	int iLoopPlayer;
	#pragma omp parallel for
	for (iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
		if (GET_TEAM(GET_PLAYER((PlayerTypes)iLoopPlayer).getTeam()).isVassal(GET_PLAYER(eIndex).getTeam()))
			checkStability((PlayerTypes)iLoopPlayer, bPositive, eIndex);
}

void CvStatbility::getPossibleMinors(PlayerTypes eIndex, std::vector<PlayerTypes>& lCivs)
{
	// Ó²±àÂë : ÂíÀï£¬ iEthiopia£¬¸Õ¹û
	if (GC.getGameINLINE().countKnownTechNumTeams(iNationalism) == 0 and
		(eIndex == iMali or eIndex == iEthiopia or eIndex == iCongo) or
		VAL_IN(eIndex, lCivBioNewWorld))
	{
		lCivs.push_back(iNative);
		return;
	}

	if (GC.getGameINLINE().getCurrentEra() <= iMedieval)
	{
		lCivs.push_back(iBarbarian);
		lCivs.push_back(iIndependent);
		lCivs.push_back(iIndependent2);
		return;
	}

	lCivs.push_back(iIndependent);
	lCivs.push_back(iIndependent2);
}

void CvStatbility::secession(PlayerTypes eIndex, std::vector<CvCity*>& lCities)
{
	setSecedingCities(eIndex, lCities);
}

void CvStatbility::secedeCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities, bool bRazeMinorCities)
{
	int iGameTurnYear = GC.getGameINLINE().getGameTurnYear();

	std::vector<PlayerTypes> lPossibleMirrors;
	getPossibleMinors(eIndex, lPossibleMirrors);

	std::map<PlayerTypes, std::vector<CvCity*> > dPossibleResurrections;

	bool bComplete = (lCities.size() == GET_PLAYER(eIndex).getNumCities());

	CvUtils::clearPlague(eIndex);

	// if smaller cities are supposed to be destroyed, do that first
	std::vector<CvCity*> lCededCities;
	std::vector<CvCity*> lRemoveCities;
	std::vector<CvCity*> lRelocatedUnits;

	#pragma omp parallel for
	for (int iI = 0; iI < (int)lCities.size(); iI++) {
		CvCity* pCity = lCities[iI];

		if (bRazeMinorCities)
		{
			bool bMaxPopulation = (pCity->getPopulation() < 10);
			bool bMaxCulture = (pCity->getCultureLevel() < 3);
			bool bNoHolyCities = (not pCity->isHolyCity());
			bool bNoCaptials = (not pCity->isCapital());
			// Ó²±àÂë : Ò®Â·ÈöÀä
			bool bNotJerusalem = (not(pCity->getX() == tJerusalem.first and pCity->getY() == tJerusalem.second));

			if (bMaxPopulation and bMaxCulture and bNoHolyCities and bNoCaptials and bNotJerusalem)
			{
				CvCity* pClosestCity = GC.getMapINLINE().findCity(pCity->getX(), pCity->getY(), eIndex, NO_TEAM, true, false, NO_TEAM, NO_DIRECTION, pCity);

				if (pClosestCity)
				{
					if (plotDistance(pCity->getX(), pCity->getY(),
						pClosestCity->getX(), pClosestCity->getY()) <= 2)
					{
						bool bCulture = (pCity->getCultureLevel() <= pClosestCity->getCultureLevel());
						bool bPopulation = (pCity->getPopulation() < pClosestCity->getPopulation());
						if (bCulture and bPopulation)
						{
							lRemoveCities.push_back(pCity);
							continue;
						}
					}
				}
			}

			// Ó²±àÂë : ´Ý»ÙÔçÆÚÎÄÃ÷³ÇÊÐ
			// always raze iHarappa, iNorteChico, iMississippi cities 
			if ((eIndex == iHarappa or
				eIndex == iNorteChico or
				eIndex == iMississippi) and
				getHumanID() != eIndex)
			{
				lRemoveCities.push_back(pCity);
			}

		}
		lCededCities.push_back(pCity);
	}

	for (unsigned int iI = 0; iI < lRemoveCities.size(); iI++)
	{
		CvCity* pCity = lRemoveCities[iI];
		CvPlot* plot = pCity->plot();
		GET_PLAYER(iBarbarian).disband(pCity);
		plot->setCulture(eIndex, 0, true, true);
		// Ó²±àÂë 
		if (eIndex == iMississippi or eIndex == iNorteChico)
		{
			if (eIndex == iMississippi)
			{
				if (plot->getImprovementType() >= iCityRuins and
					not (plot->isPeak() and plot->isWater() and
					(plot->getTerrainType() == iDesert or
						plot->getTerrainType() == iSnow or
						plot->getTerrainType() == iMarsh)))
					if (plot->getFeatureType() == NO_FEATURE) 
						plot->setFeatureType(iForest, 0);

				if (not (plot->getImprovementType() == iCityRuins or
					plot->getImprovementType() == iHut))
					plot->setImprovementType(NO_IMPROVEMENT);

				if (plot->getImprovementType() == iCityRuins)
					plot->setImprovementType(iHut);
			}
			else
			{
				plot->setImprovementType(NO_IMPROVEMENT);
			}

			plot->setRouteType(NO_ROUTE, true);
		}
	}

	for (unsigned int iI = 0; iI < lCededCities.size(); iI++)
	{
		CvCity* pCity = lCededCities[iI];
		CvPlot* cityPlot = GC.getMapINLINE().plot(pCity->getX(), pCity->getY());
		int iGameTurnYear = GC.getGameINLINE().getGameTurnYear();

		// three possible behaviors: if living civ has a claim, assign it to them
		// claim based on core territory
		PlayerTypes iClaim = NO_PLAYER;
		for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
		{
			if (iLoopPlayer == eIndex) continue;
			if (getHumanID() == eIndex) continue;
			if (iGameTurnYear < tBirth[iLoopPlayer]) continue;
			if (iGameTurnYear > tFall[iLoopPlayer]) continue;
			if (cityPlot->isCore((PlayerTypes)iLoopPlayer) and GET_PLAYER((PlayerTypes)iLoopPlayer).isAlive())
			{
				iClaim = (PlayerTypes)iLoopPlayer;
				// debugTextPopup
				break;
			}
		}

		// claim based on original owner
		if (iClaim == NO_PLAYER)
		{
			PlayerTypes iOriginalOwner = pCity->getOriginalOwner();

			std::vector<coord > tPlots;
			Areas.getBirthArea(eIndex, tPlots);

			std::vector<CvPlot*> lPlots;
			for (unsigned int i = 0; i < lPlots.size(); i++)
				lPlots.push_back(GC.getMapINLINE().plot(tPlots[i].first, tPlots[i].second));

			bool bCityPlot = VAL_IN(cityPlot, lPlots);

			if (cityPlot->getSettlerValue(iOriginalOwner) >= HISTORICAL_VALUE and
				not cityPlot->isCore(eIndex) and
				not bCityPlot and
				GET_PLAYER(iOriginalOwner).isAlive() and
				iOriginalOwner != eIndex and
				getHumanID() != iOriginalOwner)
			{
				if (iOriginalOwner < NUM_PLAYERS and iGameTurnYear < tFall[iOriginalOwner])
				{
					// cities lost too long age don't return
					// Ó²±àÂë: 25
					if (pCity->getGameTurnPlayerLost(iOriginalOwner) >=
						GC.getGameINLINE().getGameTurn() - getTurns(25))
					{
						iClaim = iOriginalOwner;
						// debugTextPopup
					}
				}
			}
		}

		// claim based on culture
		if (iClaim == NO_PLAYER)
		{
			for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
			{
				if (iLoopPlayer == eIndex) return;
				if (getHumanID() == iLoopPlayer) continue;
				if (iGameTurnYear < tBirth[iLoopPlayer]) continue;
				if (iGameTurnYear > tFall[iLoopPlayer]) continue;
				if (GET_PLAYER((PlayerTypes)iLoopPlayer).isAlive())
				{
					int iTotalCulture = cityPlot->countTotalCulture();
					if (iTotalCulture > 0)
					{
						int iCulturePercent = 100 * cityPlot->getCulture((PlayerTypes)iLoopPlayer) / cityPlot->countTotalCulture();
						if (iCulturePercent >= 75)
						{
							iClaim = (PlayerTypes)iLoopPlayer;
							// debugTextPopup
						}
					}
				}
			}
		}

		// claim based on target (needs to be winning the war based on war success)
		if (iClaim == NO_PLAYER)
		{
			CvTeam& tPlayer = GET_TEAM(GET_PLAYER(eIndex).getTeam());
			for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
			{
				CvPlayer& pLoopPlayer = GET_PLAYER((PlayerTypes)iLoopPlayer);
				if (pLoopPlayer.isAlive() and
					tPlayer.isAtWar(pLoopPlayer.getTeam()) and
					getHumanID() != iLoopPlayer and
					iGameTurnYear < tFall[iLoopPlayer])
				{
					if (pLoopPlayer.getWarValue(pCity->getX(), pCity->getY()) >= 8 and
						GET_TEAM(pLoopPlayer.getTeam()).AI_getWarSuccess(tPlayer.getID()) > tPlayer.AI_getWarSuccess(pLoopPlayer.getTeam()))
						// anthoer enemy with closer city: don't claim the city
					{
						CvCity* pClosestCity = GC.getMapINLINE().findCity(pCity->getX(), pCity->getY(), NO_PLAYER, NO_TEAM, true,
							false, NO_TEAM, NO_DIRECTION, pCity);
						if (pClosestCity->getOwnerINLINE() != iLoopPlayer and
							tPlayer.isAtWar(GET_PLAYER(pClosestCity->getOwnerINLINE()).getTeam()))
							continue;
						iClaim = (PlayerTypes)iLoopPlayer;
						// debugTextPopup
					}
				}
			}
		}

		if (iClaim != -1)
		{
			secedeCity(pCity, (PlayerTypes)iClaim, (eIndex < NUM_PLAYERS and not bComplete));
			continue;
		}

		// if part of the core / resurrection area of a dead civ -> possible
		bool bResurrenctionFound = false;
		for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
		{
			if (iLoopPlayer == eIndex) return;
			if (GET_PLAYER((PlayerTypes)iLoopPlayer).isAlive()) continue;
			if (not m_bSpawned[iLoopPlayer]) continue;
			if (GC.getGameINLINE().getGameTurn() - getLastTurnAlive((PlayerTypes)iLoopPlayer) < getTurns(20)) continue;

			// Leoreth: Egyptian respawn on Arabian collapse hurts Ottoman expansion Ó²±àÂë
			if (eIndex == iArabia and (iLoopPlayer == iEgypt or iLoopPlayer == iMamluks)) continue;

			
			std::vector<coord > tCityPlot;
			Areas.getRespawnArea((PlayerTypes)iLoopPlayer, tCityPlot);

			std::vector<CvPlot*> lCityPlot;
			for (unsigned int i = 0; i < tCityPlot.size(); i++)
				lCityPlot.push_back(GC.getMapINLINE().plot(tCityPlot[i].first, tCityPlot[i].second));

			if (VAL_IN(cityPlot, lCityPlot))
			{
				bool bPossible = false;

				for (unsigned int i = 0; i < tResurrectionIntervals[iLoopPlayer].size(); i++)
				{
					std::pair<int, int> tInterval = tResurrectionIntervals[iLoopPlayer][i];
					int iStart = tInterval.first;
					int iEnd = tInterval.second;
					if (iStart <= iGameTurnYear and iGameTurnYear <= iEnd)
					{
						bPossible = true;
						break;
					}
				}

				// make respawns on collapse more likely
				if (tBirth[iLoopPlayer] <= iGameTurnYear and iGameTurnYear <= tFall[iLoopPlayer])
					bPossible = true;

				if (bPossible)
				{
					if (dPossibleResurrections.count((PlayerTypes)iLoopPlayer))
					{
						dPossibleResurrections[(PlayerTypes)iLoopPlayer].push_back(pCity);
					}
					else
					{
						dPossibleResurrections[(PlayerTypes)iLoopPlayer].clear();
						dPossibleResurrections[(PlayerTypes)iLoopPlayer].push_back(pCity);
					}
					bResurrenctionFound = true;
					// debugTextPopup
				}
			}
		}

		if (bResurrenctionFound) continue;

		// assign randomly to possible minors
		secedeCity(pCity, lPossibleMirrors[pCity->getID() % lPossibleMirrors.size()],
			eIndex < NUM_PLAYERS and not bComplete);
	}

	// notify for partial secessions
	if (not bComplete)
	{
		if (GET_PLAYER(getHumanID()).canContact(eIndex)) 
			NULL;
			// addMessage
	}

	// collect additional cities that can be part of the resurrection
	std::map<PlayerTypes, std::vector<CvCity*> >::iterator it;
	for (it = dPossibleResurrections.begin(); it != dPossibleResurrections.end(); ++it)
	{
		PlayerTypes iResurrrectionPlayer = it->first;

		std::vector<CvCity*> lCity;
		getResurrectionCities(iResurrrectionPlayer, lCity, true);
		for (unsigned int i = 0; i < lCity.size(); i++)
		{
			CvCity* city = lCity[i];
			if (not VAL_IN(city, lCededCities))
				dPossibleResurrections[iResurrrectionPlayer].push_back(city);
		}
		// execute possible resurrections
		// debugTextPopup
	}

	if (lCities.size() > 1)
		balanceStability(eIndex, iStabilityUnstable);
}

void CvStatbility::secedeCity(CvCity* city, PlayerTypes iNewOwner, bool bRelocate)
{
	if (city == NULL) return;
	CvWString sName = city->getName();

	int iNumDefenders = std::max(2, GET_PLAYER(iNewOwner).getCurrentEra() - 1);

	std::vector<CvUnit*> lRelocatedUnits;
	std::vector<CvUnit*> lFlippedUnits;
	CvUtils::flipOrRelocateGarrison(city, iNumDefenders, lFlippedUnits, lRelocatedUnits);

	if (bRelocate)
		CvUtils::relocateUnitsToCore(city->getOwner(), lRelocatedUnits);
	else
		CvUtils::killUnits(lRelocatedUnits);

	CvUtils::completeCityFlip(city->getX(), city->getY(), iNewOwner, city->getOwner(), 50, false, true, true);

	CvUtils::flipOrCreateDefenders(iNewOwner, lFlippedUnits, city->getX(), city->getY(), iNumDefenders);

	if (city->getOwner() == getHumanID())
	{
		if (iNewOwner == iIndependent or iNewOwner == iIndependent2 or
			iNewOwner == iNative or iNewOwner == iBarbarian)
			NULL;// addMessage
		else
			NULL;// addMessage
	}

	if (getHumanID() == iNewOwner)
		NULL;
		// addMessage

}

void CvStatbility::completeCollapse(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	std::vector<CvCity*> lCities;
	CvUtils::getCityList(eIndex, lCities);

	// help lategame ai not collapse so regularly
	if (getHumanID() != eIndex)
	{
		if (GET_TEAM(pPlayer.getTeam()).isHasTech(iNationalism))
		{
			if (GC.getGameINLINE().getGameTurnYear() < tFall[eIndex])
			{
				std::vector<CvCity*> lOwnedCoreCities;
				CvUtils::getOwnedCoreCities(eIndex, lOwnedCoreCities);
				if (lOwnedCoreCities.size() > 0 and lOwnedCoreCities.size() < lCities.size())
				{
					collapseToCore(eIndex);
					return;
				}
			}
		}
	}
	// error : vic.onCollapse(eIndex, false);

	// before cities are secede, downgrade their cottages
	downgradeCottages(eIndex);

	// secede all cities, destroy close and less important ones
	bool bRazeMinorCities = (pPlayer.getCurrentEra() <= iMedieval);
	secedeCities(eIndex, lCities, bRazeMinorCities);

	// take care of the remants of the civ
	pPlayer.killUnits();
	CvUtils::resetUHV(eIndex);

	setLastTurnAlive(eIndex, GC.getGameINLINE().getGameTurn());

	// °ÝÕ¼Í¥Ó²±àÂë
	// special case: remove Christians in the Turkish core	
	if (eIndex == iByzantium)
	{
		std::vector<coord > tPlotList;
		Areas.getCoreArea(iOttomans, tPlotList);
		CvUtils::removeReligionByArea(tPlotList, iOrthodoxy);
	}

	// ÖÐ¹úÓ²±àÂë
	// Chines collapse: Mongolia's core moves south
	if (eIndex == iChina)
		GET_PLAYER(iMongolia).setReborn(true);

	// debugTextPopup

	// addMessage
	CvWString szText = gDLL->getText("TXT_KEY_STABILITY_COMPLETE_COLLAPSE", pPlayer.getCivilizationAdjective());
	//gDLL->getInterfaceIFace()->addMessage(getHumanID(), false, iDuration, szText, "", 0, "", ColorTypes(iWhite), -1, -1, true, true);
}

void CvStatbility::collapseToCore(PlayerTypes eIndex)
{
	std::vector<CvCity*> lAhistoricalCities;
	std::vector<CvCity*> lNonCoreCities;

	// vic.onCollapse(eIndex, false);

	// Spread Roman pigs on Celtia's complete collapse
	if (getRomanPigs() < 0 and eIndex == iCeltia)
		setRomanPigs(1);

	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iLoop = 0;
	for (CvCity* city = pPlayer.firstCity(&iLoop); city != NULL; city = pPlayer.nextCity(&iLoop))
	{
		CvPlot* plot = city->plot();
		if (not plot->isCore(eIndex))
		{
			lNonCoreCities.push_back(city);
			if (plot->getSettlerValue(eIndex) < HISTORICAL_VALUE)
				lAhistoricalCities.push_back(city);
		}
	}

	// more than half ahistorical, only secede ahistorical cities
	if (2 * lAhistoricalCities.size() > lNonCoreCities.size())
	{
		// notify owner
		if (getHumanID() == eIndex)
		{
			NULL;
			// addMessage
		}

		// secede all foreign cities
		secession(eIndex, lAhistoricalCities);
	}
	else if (lNonCoreCities.size())
	{
		// notify owner
		if (getHumanID() == eIndex)
		{
			// addMessage
		}
		// secede all non-core cities
		secession(eIndex, lNonCoreCities);
	}
}

void CvStatbility::downgradeCottages(PlayerTypes eIndex)
{
	for (int iI = 0; iI < GC.getMapINLINE().numPlotsINLINE(); iI++)
	{
		CvPlot* plot = GC.getMapINLINE().plotByIndexINLINE(iI);
		if (plot->getOwner() == eIndex)
		{
			int iImprovement = plot->getImprovementType();
			int iRoute = plot->getRouteType();

			if (iImprovement == iTown) plot->setImprovementType(iHamlet);
			else if (iImprovement == iVillage) plot->setImprovementType(iCottage);
			else if (iImprovement == iHamlet) plot->setImprovementType(iCottage);
			else if (iImprovement == iCottage) plot->setImprovementType(NO_IMPROVEMENT);

			// Destory all Harappan improments and routes 
			// Ó²±àÂë : É¾³ýÔçÆÚÎÄÃ÷µÄºÛ¼£
			if ((eIndex == iCeltia or eIndex == iHarappa or eIndex == iNorteChico or eIndex == iMississippi) and
				getHumanID() != eIndex)
			{
				if (iImprovement >= 0)
					plot->setImprovementType(NO_IMPROVEMENT);
				if (iRoute >= 0)
					plot->setRouteType(NO_ROUTE, true);
			}
		}
	}

	if (getHumanID() == eIndex)
		NULL;
		// addMessage
}

void CvStatbility::calculateStability(PlayerTypes eIndex, int& iStability, std::vector<int>& lStabilityTypes, std::vector<int>& lParameters)
{
	int iGameTurn = GC.getGameINLINE().getGameTurn();
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	CvTeam& tPlayer = GET_TEAM(pPlayer.getTeam());

	// Collect required data
	int iReborn = pPlayer.getReborn();
	int iStateReligion = pPlayer.getStateReligion();
	int iCurrentEra = pPlayer.getCurrentEra();
	int iTotalPopulation = pPlayer.getTotalPopulation();
	int iPlayerScore = pPlayer.getScoreHistory(iGameTurn);

	CivicTypes iCivicGovernment = pPlayer.getCivics((CivicOptionTypes)0);
	CivicTypes iCivicLegitimacy = pPlayer.getCivics((CivicOptionTypes)1);
	CivicTypes iCivicSociety = pPlayer.getCivics((CivicOptionTypes)2);
	CivicTypes iCivicEconomy = pPlayer.getCivics((CivicOptionTypes)3);
	CivicTypes iCivicReligion = pPlayer.getCivics((CivicOptionTypes)4);
	CivicTypes iCivicTerritory = pPlayer.getCivics((CivicOptionTypes)5);

	int iCorePopulation = 10;
	int iPeripheryPopulation = 10;
	int iTotalCities = 0;
	int iOccupiedCoreCities = 0;

	int iRecentlyFounded = 0;
	int iRecentlyConquered = 0;

	int iStateReligionPopulation = 0;
	int iOnlyStateReligionPopulation = 0;
	int iDifferentReligionPopulation = 0;
	int iNoReligionPopulation = 0;

	bool bTotalitarianism = (iCivicSociety == iTotalitarianism);
	bool bFreeEnterprise = (iCivicEconomy == iFreeEnterprise);
	bool bPublicWelfare = (iCivicEconomy == iPublicWelfare);
	bool bTheocracy = (iCivicReligion == iTheocracy);
	bool bTolerance = (iCivicReligion == iTolerance);
	bool bConquest = (iCivicTerritory == iConquest);
	bool bTributaries = (iCivicTerritory == iTributaries);
	bool bIsolationism = (iCivicTerritory == iIsolationism);
	bool bColonialism = (iCivicTerritory == iColonialism);
	bool bNationhood = (iCivicTerritory == iNationhood);
	bool bMultilateralism = (iCivicTerritory == iMultilateralism);

	bool bSingleCoreCity = false;
	bool bUnion = false;

	// ²¨À¼Á¢ÌÕÍð
	CvPlayer& pPoland = GET_PLAYER(iPoland);
	CvPlayer& pLithuania = GET_PLAYER(iLithuania);
	CvTeam& teamLithuania = GET_TEAM(pLithuania.getTeam());
	CvTeam& teamPoland = GET_TEAM(pPoland.getTeam());

	if (eIndex == iLithuania and
		pPoland.isAlive() and
		(teamPoland.isDefensivePact(teamLithuania.getID()) or
			teamPoland.isVassal(teamLithuania.getID())))
	{
		bSingleCoreCity = false;
		bUnion = true;
	}
	else if (eIndex == iPoland and
		pLithuania.isAlive() and
		(teamLithuania.isDefensivePact(teamPoland.getID()) or
			teamLithuania.isVassal(teamPoland.getID())))
	{
		bSingleCoreCity = false;
			bUnion = true;
	}

	// °ÂÐÙÁª°î
	CvPlayer& pHolyRome = GET_PLAYER(iHolyRome);
	CvPlayer& pHungary = GET_PLAYER(iHungary);
	CvTeam& teamHolyRome = GET_TEAM(pHolyRome.getTeam());
	CvTeam& teamHungary = GET_TEAM(pHungary.getTeam());

	if (eIndex == iHolyRome and pHolyRome.isReborn() and pHungary.isAlive() and
		(teamHungary.isDefensivePact(teamHolyRome.getID()) or teamHungary.isVassal(teamHungary.getID())))
	{
		bSingleCoreCity = false;
		bUnion = true;
	}
	else if (eIndex == iHungary and
		pHolyRome.isAlive() and
		(teamHolyRome.isDefensivePact(teamHungary.getID()) or
			teamHolyRome.isVassal(teamHungary.getID())))
	{
		bSingleCoreCity = false;
		bUnion = true;
	}

	std::vector<CvCity*> lCities;
	CvUtils::getOwnedCoreCities(eIndex, lCities);
	bSingleCoreCity = (lCities.size() == 1u);

	int iCorePopulationModifier = getCorePopulationModifier(iCurrentEra);

	// Áª°î
	if (bUnion)
	{
		if (eIndex == iLithuania) iCorePopulation += getUnionPop(iPoland, iCorePopulationModifier);
		else if (eIndex == iPoland) iCorePopulation += getUnionPop(iLithuania, iCorePopulationModifier);
		else if (eIndex == iHolyRome) iCorePopulation += getUnionPop(iHungary, iCorePopulationModifier);
		else if (eIndex == iHungary) iCorePopulation += getUnionPop(iHolyRome, iCorePopulationModifier);
	}

	ReligionTypes iMostPopularReligion = NO_RELIGION;
	int iMostPopularReligionPopulation = 0;

	for (int iI = 0; iI < GC.getNumReligionInfos(); iI++)
	{
		if (pPlayer.getReligionPopulation((ReligionTypes)iI) > iMostPopularReligionPopulation)
		{
			iMostPopularReligion = (ReligionTypes)iI;
			iMostPopularReligionPopulation = pPlayer.getReligionPopulation((ReligionTypes)iI);
		}
	}

	// Á¢ÌÕÍðUP
	bool bLithuaniaUP = (eIndex == iLithuania and
		pLithuania.isStateReligion() and
		pLithuania.getStateReligion() == -1);

	int iLoop = 0;
	for (CvCity* pCity = GET_PLAYER(eIndex).firstCity(&iLoop);
		pCity != NULL; pCity = GET_PLAYER(eIndex).nextCity(&iLoop))
	{
		int iPopulation = pCity->getPopulation();
		int iModifier = 0;
		CvPlot* plot = pCity->plot();

		bool bHistorical = (plot->getSettlerValue(eIndex) >= HISTORICAL_VALUE);

		int iTotalCulture = 0;

		// Expansion
		if (plot->isCore(eIndex))
		{
			int iStabilityPopulation = iCorePopulationModifier * iPopulation / 100;
			if (bSingleCoreCity and iCurrentEra > iAncient)
				iStabilityPopulation += iCorePopulationModifier * iPopulation / 100;

			iCorePopulation += iStabilityPopulation;
			pCity->setStabilityPopulation(iStabilityPopulation);
		}
		else
		{
			int iOwnCulture = plot->getCulture(eIndex);
			int iCulturePercent = 0;

			for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
			{
				int iTempCulture = plot->getCulture((PlayerTypes)iLoopPlayer);
				if (plot->isCore((PlayerTypes)iLoopPlayer))
					iTempCulture *= 2;
				iTotalCulture += iTempCulture;
			}

			if (iTotalCulture)
				iCulturePercent = 100 * iOwnCulture / iTotalCulture;
			else
				iCulturePercent = 100;

			// iMongolia ÃÉ¹Å
			bool bExpansionExceptions = ((bHistorical and eIndex == iMongolia) or bTotalitarianism);

			// ahistorical tiles
			if (not bHistorical) iModifier += 2;

			// colonies with Totalitarianism
			if (pCity->isColony() and bHistorical and bTotalitarianism) iModifier += 1;

			// Ó²±àÂë : 25
			// not original owner
			if (not bExpansionExceptions)
				if (pCity->getOriginalOwner() != eIndex and
					iGameTurn - pCity->getGameTurnAcquired() < 25)
					iModifier += 1;

			// ²¨Ë¹UP
			// not majority culture (includes foreign core and Persian UP
			if (eIndex == iPersia or GET_PLAYER(iPersia).isReborn())
			{
				if (iCulturePercent < 50) iModifier += 1;
				if (iCulturePercent < 20) iModifier += 1;
			}

			// Courthouse : ·¨Í¥ - ½¨ÖþÐ§¹û
			if (pCity->hasBuilding(getUniqueBuilding((CivilizationTypes)eIndex, iCourthouse)))
				iModifier -= 1;

			// Jail : ¼àÓü - ½¨ÖþÐ§¹û
			if (pCity->hasBuilding(getUniqueBuilding((CivilizationTypes)eIndex, iJail)))
				iModifier -= 1;

			// ÆÏÌÑÑÀUP
			// Portuguese UP : reduced instability from overseas colonies
			if (pCity->isColony())
			{
				if (eIndex == iPortugal) iModifier -= 2;
				if (bColonialism and bHistorical) iModifier -= 1;
			}

			// cap
			if (iModifier < -1) iModifier = -1;

			int iStabilityPopulation = (100 + iModifier * 50) * iPopulation / 100;

			iPeripheryPopulation += iStabilityPopulation;
			pCity->setStabilityPopulation(-iStabilityPopulation);
		}

		// Ó²±àÂë : 20
		// Recent conquests
		if (bHistorical and (iGameTurn - pCity->getGameTurnAcquired() < getTurns(20)))
		{
			if (pCity->getPreviousOwner() < 0) iRecentlyFounded += 1;
			else iRecentlyConquered += 1;
		}

		// Religions
		if (pCity->getReligionCount() == 0)
			iNoReligionPopulation += iPopulation;
		else
		{
			bool bNonStateReligion = false;
			for (int iReligion = 0; iReligion < GC.getNumReligionInfos(); iReligion++)
			{
				if (iReligion != iStateReligion and pCity->isHasReligion((ReligionTypes)iReligion))
				{
					if (not (iMostPopularReligion == iReligion and bLithuaniaUP) and
						not isTolerated(eIndex, (ReligionTypes)iReligion) and
						not GC.getReligionInfo((ReligionTypes)iReligion).isLocal())
					{
						bNonStateReligion = true;
						break;
					}
				}

				if (iStateReligion >= 0 and pCity->isHasReligion((ReligionTypes)iStateReligion))
				{
					iStateReligionPopulation += iPopulation;
					if (not bNonStateReligion) iOnlyStateReligionPopulation += iPopulation;
				}

				if (bNonStateReligion)
				{
					if (iStateReligion >= 0 and pCity->isHasReligion((ReligionTypes)iStateReligion))
						iDifferentReligionPopulation += iPopulation / 2;
					else
						iDifferentReligionPopulation += iPopulation;
				}
			}
		}
	}

	int iPopulationImprovements = 0;

	std::vector<coord > lPlot;
	Areas.getCoreArea(eIndex, lPlot);
	for (unsigned int i = 0; i < lPlot.size(); i++)
	{
		coord tPlot = lPlot[i];
		CvPlot* plot = GC.getMapINLINE().plot(tPlot.first, tPlot.second);
		if (plot->getOwner() == eIndex and plot->getWorkingCity())
			if (plot->getImprovementType() == iVillage or
				plot->getImprovementType() == iTown)
				iPopulationImprovements += 1;
	}

	iCorePopulation += iCorePopulationModifier * iPopulationImprovements / 100;

	int iCurrentPower = pPlayer.getPower();
	int iPreviousPower = pPlayer.getPowerHistory(iGameTurn - getTurns(10));

	// EXPANSION
	int iExpansionStability = 0;

	int iCorePeripheryStability = 0;
	int iRecentExpansionStability = 0;
	int iRazeCityStability = 0;

	int iPeripheryExcess = 0;

	// Core vs. Periphery Populations
	if (iCorePopulation == 0) iPeripheryExcess = 200;
	else iPeripheryExcess = 100 * iPeripheryPopulation / iCorePopulation - 100;

	if (iPeripheryExcess > 200) iPeripheryExcess = 200;

	if (iPeripheryExcess > 0)
	{
		iCorePeripheryStability -= (int)(25 * sigmoid(1.0 * iPeripheryExcess / 100));
		m_iLastExpansionStability[eIndex] = iCorePeripheryStability;
		// debugTextPopup
	}

	lParameters[iParameterCorePeriphery] = iCorePeripheryStability;
	lParameters[iParameterCoreScore] = iCorePopulation;
	lParameters[iParameterPeripheryScore] = iPeripheryPopulation;

	iExpansionStability += iCorePeripheryStability;

	// recent expansion stability
	int iConquestModifier = 1;
	if (bConquest) iConquestModifier += 1;
	// Persian UP ²¨Ë¹UP
	if (eIndex == iPersia and not GET_PLAYER(iPersia).isReborn()) iConquestModifier += 1;

	iRecentExpansionStability += iRecentlyFounded;
	iRecentExpansionStability += iConquestModifier * iRecentlyConquered;

	lParameters[iParameterRecentExpansion] = iRecentExpansionStability;

	iExpansionStability += iRecentExpansionStability;

	// apply raze city penalty
	iRazeCityStability = getHumanRazePenalty();

	lParameters[iParameterRazedCities] = iRazeCityStability;

	iExpansionStability += iRazeCityStability;

	// stability if not expanded beyond core with isolatonism
	int iIsolatonismStability = 0;

	if (bIsolationism and iPeripheryPopulation <= 10) iIsolatonismStability = 10;

	lParameters[iParameterIsolationism] = iIsolatonismStability;

	iExpansionStability += iIsolatonismStability;

	// ECONOMY
	int iEconomyStability = 0;

	// Economic Grwoth
	int iEconomicGrowthModifer = 3;
	if (bFreeEnterprise) iEconomicGrowthModifer = 4;

	int iEconomicGrowthStability = iEconomicGrowthModifer * calculateTrendScore(getEconomyTrend(eIndex));
	if (iEconomicGrowthStability < 0 and bPublicWelfare) iEconomicGrowthModifer /= 2;

	lParameters[iParameterEconomicGrowth] = iEconomicGrowthStability;
	iEconomyStability += iEconomicGrowthStability;

	int iTradeStability = 0;

	lParameters[iParameterTrade] = iTradeStability;
	iEconomyStability += iTradeStability;

	int iTotalCommerce = pPlayer.calculateTotalCommerce();

	// DOMESTIC
	int iDomesticStability = 0;

	// Happiness
	int iHappinessStability = calculateTrendScore(getHappinessTrend(eIndex));

	if (iHappinessStability > 5) iHappinessStability = 5;
	if (iHappinessStability < -5) iHappinessStability = -5;

	lParameters[iParameterHappiness] = iHappinessStability;

	iDomesticStability += iHappinessStability;

	// Civics (combinations)
	std::vector<CivicTypes> civics =  (list_of(iCivicGovernment), iCivicLegitimacy, iCivicEconomy, iCivicReligion, iCivicTerritory );
	int iCivicCombinationStability = getCivicStability(eIndex, civics);

	if (getHumanID() != eIndex and iCivicCombinationStability < 0)
		iCivicCombinationStability /= 2;

	lParameters[iParameterCivicCombinations] = iCivicCombinationStability;

	int iCivicEraTechStability = 0;

	// Civics (eras and techs and religions)
	if (iCivicLegitimacy == iVassalage)
	{
		if (iCurrentEra == iMedieval) iCivicEraTechStability += 2;
		else if (iCurrentEra >= iIndustrial) iCivicEraTechStability -= 5;
	}

	if (iCivicReligion == iDeification)
	{
		if (iCurrentEra <= iClassical) iCivicEraTechStability += 2;
		else iCivicEraTechStability -= 2 * (iCurrentEra - iClassical);
	}

	if (iCivicGovernment == iRepublic)
	{
		if (iCurrentEra <= iClassical) iCivicEraTechStability += 2;
		else if (iCurrentEra >= iIndustrial) iCivicEraTechStability -= 5;
	}

	if (iCivicTerritory == iIsolationism)
	{
		if (iCurrentEra >= iIndustrial) iCivicEraTechStability -= (iCurrentEra - iRenaissance) * 3;
	}

	if (tPlayer.isHasTech(iRepresentation))
	{
		if (iCivicGovernment != iRepublic and iCivicGovernment != iDemocracy and
			iCivicLegitimacy != iRevolutionism and iCivicLegitimacy != iConstitution)
			iCivicEraTechStability -= 5;
	}
			

	if (tPlayer.isHasTech(iCivilRights))
	{
		std::vector<CivicTypes> t = (list_of(iSlavery), iManorialism, iCasteSystem);
		if (VAL_IN(iCivicSociety, t)) iCivicEraTechStability -= 5;
	}
		
	if (tPlayer.isHasTech(iEconomics))
	{
		std::vector<CivicTypes> t = (list_of(iReciprocity), iRedistribution, iMerchantTrade);
		if (VAL_IN(iCivicEconomy, t)) iCivicEraTechStability -= 5;
	}
	
	if (tPlayer.isHasTech(iNationalism))
	{
		std::vector<CivicTypes> t = (list_of(iConquest), iTributaries);
		if (VAL_IN(iCivicTerritory, t)) iCivicEraTechStability -= 5;
	}

	if (tPlayer.isHasTech(iTheology))
	{
		std::vector<CivicTypes> t = (list_of(iAnimism), iDeification);
		if (VAL_IN(iCivicReligion, t)) iCivicEraTechStability -= 5;
	}

	if (iStateReligion == iHinduism)
	{
		if (iCivicSociety == iCasteSystem) iCivicEraTechStability += 3;
	}
	else if (iStateReligion == iConfucianism)
	{
		if (iCivicLegitimacy == iMeritocracy) iCivicEraTechStability += 3;
	}

	else if (iStateReligion == iZoroastrianism or
			iStateReligion == iOrthodoxy or
			iStateReligion == iCatholicism or
			iStateReligion == iProtestantism)
	{
		if (iCivicSociety == iSlavery) iCivicEraTechStability -= 3;
	}
	else if (iStateReligion == iIslam)
	{
		if (iCivicSociety == iSlavery) iCivicEraTechStability += 2;
	}
	else if (iStateReligion == iBuddhism)
	{
		if (iCivicReligion == iMonasticism) iCivicEraTechStability += 2;
	}
	else if (iStateReligion == iConfucianism)
	{
		if (iCivicTerritory == iIsolationism) iCivicEraTechStability += 3;
	}
	
	if (getHumanID() != eIndex and iCivicEraTechStability < 0) iCivicEraTechStability /= 2;

	lParameters[iParameterCivicsEraTech] = iCivicEraTechStability;

	iDomesticStability += iCivicCombinationStability + iCivicEraTechStability;

	// Religion
	int iReligionStability = 0;

	if (iTotalPopulation > 0)
	{
		int iHeathenRatio = 100 * iDifferentReligionPopulation / iTotalPopulation;
		int iHeathenThreshold = 30;
		int iBelieverThreshold = 75;

		if (iHeathenRatio > iHeathenThreshold)
			iReligionStability -= (iHeathenRatio - iHeathenThreshold) / 10;
	
		if (iStateReligion >= 0)
		{
			int iStateReligionRatio = 100 * iStateReligionPopulation / iTotalPopulation;
			int iNoReligionRatio = 100 * iNoReligionPopulation / iTotalPopulation;

			int iBelieverRatio = iStateReligionRatio - iBelieverThreshold;
			if (iBelieverRatio < 0) iBelieverRatio = std::min(0, iBelieverRatio + iNoReligionRatio);
			int iBelieverStability = iBelieverRatio / 5;

			// cap at -10 for threshold = 75
			int iCap = 2 * (iBelieverThreshold - 100) / 5;
			if (iBelieverStability < iCap) iBelieverStability = iCap;

			if (iBelieverStability > 0 and bTolerance) iBelieverStability /= 2;

			iReligionStability += iBelieverStability;

			if (bTheocracy)
			{
				int iOnlyStateReligionRatio = 100 * iOnlyStateReligionPopulation / iTotalPopulation;
				iReligionStability += iOnlyStateReligionRatio / 20;
			}	
		}
	}		

	if (eIndex == iYuezhi and iReligionStability < 0) iReligionStability /= 2;

	lParameters[iParameterReligion] = iReligionStability;

	iDomesticStability += iReligionStability;

	
	// FOREIGN
	int iForeignStability = 0;
	int iVassalStability = 0;
	int iDefensivePactStability = 0;
	int iRelationStability = 0;
	int iNationhoodStability = 0;
	int iTheocracyStability = 0;
	int iMultilateralismStability = 0;

	int iNumContacts = 0;
	int iFriendlyRelations = 0;
	int iFuriousRelations = 0;

	// error : 
	std::vector<PlayerTypes> lContacts;

	for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
	{
		CvPlayer& pLoopPlayer = GET_PLAYER((PlayerTypes)iLoopPlayer);
		TeamTypes tLoopPlayer = pLoopPlayer.getTeam();
		int iLoopScore = pLoopPlayer.getScoreHistory(iGameTurn);

		if (iLoopPlayer == eIndex) continue;
		if (not pLoopPlayer.isAlive()) continue;

		// master stability
		if (tPlayer.isVassal(tLoopPlayer))
			if (getStabilityLevel(eIndex) > getStabilityLevel((PlayerTypes)iLoopPlayer))
				iVassalStability += 4 * (getStabilityLevel(eIndex) - getStabilityLevel((PlayerTypes)iLoopPlayer));

		// vassal stability
		if (GET_TEAM(tLoopPlayer).isVassal(GET_PLAYER(eIndex).getTeam()))
		{
			if (getStabilityLevel(eIndex) == iStabilityCollapsing) iVassalStability -= 3;
			else if (getStabilityLevel((PlayerTypes)iLoopPlayer) == iStabilityUnstable) iVassalStability -= 1;
			else if (getStabilityLevel((PlayerTypes)iLoopPlayer) == iStabilitySolid) iVassalStability += 2;

			if (bTributaries) iVassalStability += 2;
		}
			
		// relations
		if (tPlayer.canContact(tLoopPlayer))
			lContacts.append((PlayerTypes)iLoopPlayer);

		// defensive pacts
		if (tPlayer.isDefensivePact(tLoopPlayer))
		{
			if (iLoopScore > iPlayerScore) iDefensivePactStability += 3;
			if (bMultilateralism) iDefensivePactStability += 3;
		}
			

		// worst enemies
		if (pLoopPlayer.getWorstEnemy() == eIndex)
			if (iLoopScore > iPlayerScore) iRelationStability -= 3;

		// wars
		if (tPlayer.isAtWar(tLoopPlayer))
		{
			if (bMultilateralism) iMultilateralismStability -= 2;

			if (CvUtils::isNeighbor(eIndex, (PlayerTypes)iLoopPlayer))
			{
				if (bNationhood) iNationhoodStability += 2;

				if (bTheocracy)
					if (pLoopPlayer.getStateReligion() != iStateReligion) iTheocracyStability += 3;
					else iTheocracyStability -= 2;
			}
		}
			
	}

	// attitude stability
	std::vector<int> lStrongerAttitudes;
	std::vector<int> lEqualAttitudes;
	std::vector<int> lWeakerAttitudes;
	calculateRankedAttitudes(eIndex, lContacts, lStrongerAttitudes, lEqualAttitudes, lWeakerAttitudes);

	int iAttitudeThresholdModifier = pPlayer.getCurrentEra() / 2;

	int iRelationStronger = 0;

	uint iPositiveStronger = std::count_if(lStrongerAttitudes.begin(), lStrongerAttitudes.end(), boost::bind(std::greater_equal<int>(), _1, 4 + iAttitudeThresholdModifier * 2));
	
	if (iPositiveStronger > lStrongerAttitudes.size() / 2)
	{
		iRelationStronger = 5 * iPositiveStronger / std::max(1, len(lStrongerAttitudes));
		iRelationStronger = std::min(iRelationStronger, len(lStrongerAttitudes));
	}

	int iRelationWeaker = 0;
	int iNegativeWeaker = std::max(0, (int)(std::count_if(lWeakerAttitudes.begin(), lWeakerAttitudes.end(), boost::bind(std::less<int>(), _1, -1)) -
		std::count_if(lWeakerAttitudes.begin(), lWeakerAttitudes.end(), boost::bind(std::greater_equal<int>(), _1, 3 + iAttitudeThresholdModifier))));
	
	if (iNegativeWeaker > 0)
	{
		iRelationWeaker = -8 * std::min(iNegativeWeaker, len(lWeakerAttitudes) / 2) / std::max(1, len(lWeakerAttitudes) / 2);
		iRelationWeaker = std::max((int)iRelationWeaker, -((int)len(lWeakerAttitudes)));
	}

	int iRelationEqual = 0;
	for (uint i = 0; i < len(lEqualAttitudes); i++)
	{
		int iAttitude = lEqualAttitudes[i];
		if (std::abs(iAttitude) > 2)
			iRelationEqual += sign(iAttitude) * std::min(25, std::abs(iAttitude) / 5);
	}

	iRelationStability = iRelationStronger + iRelationEqual + iRelationWeaker;

	if (bIsolationism)
	{
		if (iRelationStability < 0) iRelationStability = 0;
		if (iRelationStability > 0) iRelationStability /= 2;
	}
		

	lParameters[iParameterVassals] = iVassalStability;
	lParameters[iParameterDefensivePacts] = iDefensivePactStability;
	lParameters[iParameterRelations] = iRelationStability;
	lParameters[iParameterNationhood] = iNationhoodStability;
	lParameters[iParameterTheocracy] = iTheocracyStability;
	lParameters[iParameterMultilateralism] = iMultilateralismStability;

	iForeignStability += iVassalStability + iDefensivePactStability + iRelationStability + iNationhoodStability + iTheocracyStability + iMultilateralismStability;

	// MILITARY

	int iMilitaryStability = 0;

	int iMilitaryStrengthStability = 0;

	int iWarSuccessStability = 0; // war success (conquering cities and defeating units)
	int iWarWearinessStability = 0; // war weariness in comparison to war length
	int iBarbarianLossesStability = 0; // like previously
	
	// iterate ongoing wars
	for (int iEnemy = 0; iEnemy < NUM_PLAYERS; iEnemy++)
	{
		CvPlayer& pEnemy = GET_PLAYER((PlayerTypes)iEnemy);
		TeamTypes tPlayer = GET_PLAYER(eIndex).getTeam();
		TeamTypes tEnemy = pEnemy.getTeam();
		if (pEnemy.isAlive() and GET_TEAM(tPlayer).isAtWar(tEnemy))
		{
			int iTempWarSuccessStability = calculateTrendScore(getWarTrend((PlayerTypes)eIndex, (PlayerTypes)iEnemy));

			int iOurSuccess = GET_TEAM(tPlayer).AI_getWarSuccess(tEnemy);
			int iTheirSuccess = GET_TEAM(tEnemy).AI_getWarSuccess(tPlayer);

			if (iTempWarSuccessStability > 0 and iTheirSuccess > iOurSuccess) iTempWarSuccessStability /= 2;
			else if (iTempWarSuccessStability < 0 and iOurSuccess > iTheirSuccess) iTempWarSuccessStability /= 2;

			if (iTempWarSuccessStability > 0) iTempWarSuccessStability /= 2;

			iWarSuccessStability += iTempWarSuccessStability;

			int iOurWarWeariness = GET_TEAM(tPlayer).getWarWeariness(tEnemy);
			int iTheirWarWeariness = GET_TEAM(tEnemy).getWarWeariness(tPlayer);

			int iWarTurns = iGameTurn - getWarStartTurn((PlayerTypes)eIndex, (PlayerTypes)iEnemy);

			int iDurationModifier = 0;

			if (iWarTurns > getTurns(20))
				iDurationModifier = std::min(9, (iWarTurns - getTurns(20)) / getTurns(10));

			int iTempWarWearinessStability = (iTheirWarWeariness - iOurWarWeariness) / (4000 * (iDurationModifier + 1));
			if (iTempWarWearinessStability > 0) iTempWarWearinessStability = 0;

			iWarWearinessStability += iTempWarWearinessStability;

			//utils.debugTextPopup(pPlayer.getCivilizationAdjective(0) + ' war against ' + pEnemy.getCivilizationShortDescription(0) + '\nWar Success Stability: ' + str(iTempWarSuccessStability) + '\nWar Weariness: ' + str(iTempWarWearinessStability))
		}
	}
	
	lParameters[iParameterWarSuccess] = iWarSuccessStability;
	lParameters[iParameterWarWeariness] = iWarWearinessStability;

	iMilitaryStability = iWarSuccessStability + iWarWearinessStability;

	// apply barbarian losses
	iBarbarianLossesStability = -getBarbarianLosses(eIndex);

	lParameters[iParameterBarbarianLosses] = iBarbarianLossesStability;

	iMilitaryStability += iBarbarianLossesStability;

	iStability = iExpansionStability + iEconomyStability + iDomesticStability + iForeignStability + iMilitaryStability;
	

}
// ÖÆ¶ÈÎÈ¶¨
int CvStatbility::getCivicStability(PlayerTypes eIndex, std::vector<CivicTypes> &lCivics)
{
	Civics civics = Civics(lCivics);

	int iCurrentEra = GET_PLAYER(eIndex).getCurrentEra();
	int iStability = 0;

	if (civics.contains(iTotalitarianism))
	{
		if (civics.contains(iStateParty)) iStability += 5;
		if (civics.contains(iDespotism)) iStability += 3;
		if (civics.contains(iRevolutionism)) iStability += 3;
		if (civics.contains(iCentralPlanning)) iStability += 3;
		if (civics.contains(iDemocracy)) iStability -= 3;
		if (civics.contains(iConstitution)) iStability -= 5;
		if (civics.contains(iSecularism)) iStability += 2;
		std::vector<CivicTypes> t = (list_of(iTolerance), iMonasticism);
		if (civics.any(t)) iStability -= 3;
	}

	if (civics.contains(iCentralPlanning))
	{
		if (civics.contains(iEgalitarianism)) iStability += 2;
		if (civics.contains(iStateParty)) iStability += 2;
		if (civics.contains(iCentralism)) iStability += 2;
	}

	if (civics.contains(iEgalitarianism))
	{
		if (civics.contains(iDemocracy)) iStability += 2;
		if (civics.contains(iConstitution)) iStability += 2;
		if (civics.no(iSecularism) and civics.no(iTolerance)) iStability -= 3;
	}

	if (civics.contains(iIndividualism))
	{
		std::vector<CivicTypes> t1 = (list_of(iRepublic), iDemocracy);
		if (civics.any(t1)) iStability += 2;
		if (civics.contains(iFreeEnterprise)) iStability += 3;
		if (civics.contains(iCentralPlanning)) iStability -= 5;
		std::vector<CivicTypes> t2 = (list_of(iRegulatedTrade), iPublicWelfare);
		if (civics.any(t2)) iStability -= 2;
		if (civics.contains(iTolerance)) iStability += 2;
	}

	if (civics.contains(iTheocracy))
	{
		std::vector<CivicTypes> t = (list_of(iIndividualism), iEgalitarianism);
		if (civics.any(t)) iStability -= 3;
	}
		

	if (civics.contains(iDeification))
	{
		std::vector<CivicTypes> t = (list_of(iRepublic), iDemocracy);
		if (civics.any(t)) iStability -= 3;

		if (iCurrentEra <= iClassical)
		{
			if (civics.contains(iRedistribution)) iStability += 2;
			if (civics.contains(iSlavery)) iStability += 2;
		}
	}

	if (civics.contains(iVassalage))
	{
		std::vector<CivicTypes> t1 = (list_of(iIndividualism), iEgalitarianism);
		std::vector<CivicTypes> t2 = (list_of(iFreeEnterprise), iCentralPlanning, iPublicWelfare);
		if (civics.any(t1)) iStability -= 5;
		if (civics.any(t2)) iStability -= 3;
		if (civics.contains(iTributaries)) iStability += 5;

		if (iCurrentEra == iMedieval)
		{
			if (civics.contains(iMonarchy)) iStability += 2;
			if (civics.contains(iManorialism)) iStability += 3;
		}
	}

	if (civics.contains(iRepublic))
	{
		if (civics.contains(iCitizenship)) iStability += 2;
		if (civics.contains(iVassalage)) iStability -= 3;
		if (civics.contains(iMerchantTrade)) iStability += 2;
	}

	if (civics.contains(iCentralism))
	{
		if (civics.contains(iDemocracy)) iStability -= 5;
		if (civics.contains(iRegulatedTrade)) iStability += 3;
		if (civics.contains(iClergy)) iStability += 2;

		if (iCurrentEra == iRenaissance)
			if (civics.contains(iMonarchy)) iStability += 2;
	}

	if (civics.contains(iDespotism))
	{
		if (civics.contains(iSlavery)) iStability += 2;
		if (civics.contains(iNationhood)) iStability += 3;
	}

	if (civics.contains(iCasteSystem))
	{
		if (civics.contains(iCitizenship)) iStability -= 4;
		if (civics.contains(iClergy)) iStability += 2;
		if (civics.contains(iSecularism)) iStability -= 3;
	}

	if (civics.contains(iMultilateralism))
	{
		if (civics.contains(iDespotism)) iStability -= 3;
		if (civics.contains(iTotalitarianism)) iStability -= 3;
		if (civics.contains(iEgalitarianism)) iStability += 2;
		if (civics.contains(iTheocracy)) iStability -= 3;
	}

	if (civics.contains(iMonarchy))
	{
		std::vector<CivicTypes> t = (list_of(iClergy), iMonasticism);
		if (civics.any(t)) iStability += 2;
	}
		

	if (civics.contains(iElective))
		if (civics.contains(iCentralism)) iStability -= 5;

	if (civics.contains(iConstitution))
		if (civics.contains(iDemocracy)) iStability += 2;

	if (civics.contains(iRevolutionism))
		if (civics.no(iSecularism) and civics.no(iTolerance)) iStability -= 3;

	if (civics.contains(iRegulatedTrade))
	{
		if (civics.contains(iManorialism)) iStability += 2;
		if (civics.contains(iMeritocracy)) iStability += 3;
	}

	if (civics.contains(iIsolationism))
	{
		std::vector<CivicTypes> t1 = (list_of(iMerchantTrade), iFreeEnterprise);
		std::vector<CivicTypes> t2 = (list_of(iRegulatedTrade), iCentralPlanning);
		if (civics.any(t1)) iStability -= 4;
		if (civics.any(t2)) iStability += 3;
		if (civics.contains(iMeritocracy)) iStability += 3;
	}

	return iStability;
}

void only()
{
}

void other()
{
}

double CvStatbility::sigmoid(double x)
{
	return std::tanh(5 * x / 2);
}
// iPositiveStronger = count(lStrongerAttitudes, lambda x: x >= 4 + iAttitudeThresholdModifier * 2)

// bool fn(int x) { return (x >= 4+ iAttitudeThresholdModifier * 2); }
// int iPositiveStronger = std::count_if(lStrongerAttitudes.begin(), lStrongerAttitudes.end(), fn);

// int iPositiveStronger = count<int>(lStrongerAttitudes, 
template<typename T>
int count(std::vector<T>& iterable, boost::function<bool(T)> fn)
{
	return std::count_if(iterable.begin(), iterable.end(), fn);
}

int CvStatbility::calculateTrendScore(std::list<int>& lTrend)
{
	int iPositive = 0;
	int iNeutral = 0;
	int iNegative = 0;

	std::list<int>::iterator it;
	for (it = lTrend.begin(); it != lTrend.end(); it++)
	{
		int iEntry = *it;
		if (iEntry > 0) iPositive += 1;
		else if (iEntry < 0) iNegative += 1;
		else iNeutral += 1;
	}

	if (iPositive > iNegative) return std::max(0, iPositive - iNegative - iNeutral / 2);

	if (iNegative > iPositive) return std::min(0, iPositive - iNegative + iNeutral / 2);

	return 0;
}

int CvStatbility::calculateSumScore(std::vector<int>& lScores, int iThreshold)
{
	std::vector<int> lThresholdScores;
	for (unsigned int iScore = 0; iScore < lScores.size(); iScore++)
	{
		if (std::abs((int)iScore) >= iThreshold)
			lThresholdScores.push_back(sign(iScore));
	}

	int iSum = 0;
	for (unsigned int i = 0; i < lThresholdScores.size(); i++)
		iSum += lThresholdScores[i];

	int iCap = lScores.size() / 2;

	return iSum;
}

void CvStatbility::updateEconomyTrend(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);

	if (not pPlayer.isAlive()) return;

	int iPreviousCommerce = getPreviousCommerce(eIndex);
	int iCurrentCommerce = pPlayer.calculateTotalCommerce();

	if (iPreviousCommerce == 0)
	{
		setPreviousCommerce(eIndex, iCurrentCommerce);
		return;
	}

	int iCivicEconomy = pPlayer.getCivics(CIVICOPTION_ECONOMY);

	// Ó²±àÂë
	int iPositiveThreshold = 5;
	int iNegativeThreshold = 0;

	if (isDecline(eIndex)) iNegativeThreshold = 2;

	if (iCivicEconomy == iCentralPlanning) iNegativeThreshold = 0;

	int iPercentChange = 100 * iCurrentCommerce / iPreviousCommerce - 100;

	if (iPercentChange > iPositiveThreshold) pushEconomyTrend(eIndex, 1);
	else if (iPercentChange < iNegativeThreshold) pushEconomyTrend(eIndex, -1);
	else pushEconomyTrend(eIndex, 0);

	setPreviousCommerce(eIndex, iCurrentCommerce);
}

void CvStatbility::updateHappinessTrend(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);

	if (not pPlayer.isAlive()) return;

	int iNumCities = pPlayer.getNumCities();

	if (iNumCities == 0) return;

	int iHappyCities = 0;
	int iUnhappyCities = 0;

	int iAveragePopulation = pPlayer.getAveragePopulation();

	int iLoop = 0;
	for (CvCity* city = pPlayer.firstCity(&iLoop); city != NULL; city = pPlayer.nextCity(&iLoop))
	{
		int iPopulation = city->getPopulation();
		int iHappiness = city->happyLevel();
		int iUnhappiness = city->unhappyLevel(0);
		int iOvercrowding = city->getOvercrowdingPercentAnger(0) * city->getPopulation();
		// Ó²±àÂë
		if (city->isWeLoveTheKingDay() or
			(iPopulation >= iAveragePopulation and
				iHappiness - iUnhappiness >= iAveragePopulation / 4))
			iHappyCities += 1;
		else if (iUnhappiness - iOvercrowding > iPopulation / 5 or
			iUnhappiness - iHappiness > 0)
			iUnhappiness += 1;
	}

	int iCurrentTrend = 0;

	if (iHappyCities - iUnhappyCities > std::ceil(iNumCities / 5.0)) iCurrentTrend = 1;
	else if (iUnhappyCities - iHappyCities > std::ceil(iNumCities / 5.0)) iCurrentTrend = -1;

	pushHappinessTrend(eIndex, iCurrentTrend);
}

void CvStatbility::updateWarTrend(PlayerTypes eIndex, PlayerTypes iEnemy)
{
	int iOurCurrentSuccess = GET_TEAM(GET_PLAYER(eIndex).getTeam()).AI_getWarSuccess(GET_PLAYER(iEnemy).getTeam());
	int iTheirCurrentSucess = GET_TEAM(GET_PLAYER(iEnemy).getTeam()).AI_getWarSuccess(GET_PLAYER(eIndex).getTeam());

	int iOurLastSucess = m_lLastWarSuccess[eIndex][iEnemy];
	int iTheirLastSuccess = m_lLastWarSuccess[iEnemy][eIndex];

	int iOurGain = std::max(0, iOurCurrentSuccess - iOurLastSucess);
	int iTheirGain = std::max(0, iTheirCurrentSucess - iTheirLastSuccess);

	int iCurrentTrend = 0;

	if (iOurGain - iTheirGain > 0) iCurrentTrend = 1;
	else if (iOurGain - iTheirGain < 0) iCurrentTrend = -1;
	else if (std::abs(iOurCurrentSuccess = iTheirCurrentSucess) >=
		std::max(iOurCurrentSuccess, iTheirCurrentSucess) / 5)
		iCurrentTrend = sign(iOurCurrentSuccess - iTheirCurrentSucess);

	pushWarTrend(eIndex, iEnemy, iCurrentTrend);
}

void CvStatbility::startWar(PlayerTypes iPlayer, PlayerTypes iEnemy)
{
	m_lWarTrend[iPlayer][iEnemy].clear();
	m_lWarTrend[iEnemy][iPlayer].clear();

	int iGameTurn = GC.getGameINLINE().getGameTurn();

	m_lWarStartTurn[iPlayer][iEnemy] = iGameTurn;
	m_lWarStartTurn[iEnemy][iPlayer] = iGameTurn;
}

int CvStatbility::calculateEconomicGrowth(PlayerTypes eIndex, int iNumTurns)
{
	std::vector<coord> lHistory;
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iCurrentTurn = GC.getGameINLINE().getGameTurn();

	int start = iCurrentTurn - iNumTurns;
	int end = iCurrentTurn;
	for (int iTurn = start; iTurn < end; iTurn++)
	{
		int iHistory = pPlayer.getEconomyHistory(iTurn);
		if (iHistory > 1)
			lHistory.push_back(std::make_pair(iTurn - iCurrentTurn + iNumTurns, iHistory));
	}

	lHistory.push_back(std::make_pair(iNumTurns, pPlayer.calculateTotalCommerce()));

	double a, b;
	CvUtils::linreg(lHistory, a, b);

	double iNormalizedStartTurn = b;
	double iNormalizedCurrentTurn = a * iNumTurns + b;

	if (ZERO(iNormalizedStartTurn)) return 0;

	int iGrowth = int(100 * (iNormalizedCurrentTurn - iNormalizedStartTurn) / iNormalizedStartTurn);

	return iGrowth;
}

int CvStatbility::calculateEconomicGrowthNeighbors(PlayerTypes eIndex, int iNumTurns)
{
	std::vector<coord > lHistory;
	std::vector<PlayerTypes> lContacts;
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iCurrentTurn = GC.getGameINLINE().getGameTurn();

	for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
		if (pPlayer.canContact((PlayerTypes)iLoopPlayer)) lContacts.push_back((PlayerTypes)iLoopPlayer);

	int start = iCurrentTurn - iNumTurns;
	int end = iCurrentTurn;
	for (int iTurn = start; iTurn < end; iTurn++)
	{
		int iHistory = pPlayer.getEconomyHistory(iTurn);
		for (unsigned int iLoopPlayer = 0; iLoopPlayer < lContacts.size(); iLoopPlayer++)
			iHistory += GET_PLAYER(lContacts[iLoopPlayer]).getEconomyHistory(iTurn);
		if (iHistory > 1)
			lHistory.push_back(std::make_pair(iTurn - iCurrentTurn + iNumTurns, iHistory));
	}

	int iHistory = pPlayer.calculateTotalCommerce();
	for (unsigned int iLoopPlayer = 0; iLoopPlayer < lContacts.size(); iLoopPlayer++)
		iHistory += GET_PLAYER(lContacts[iLoopPlayer]).calculateTotalCommerce();

	double a, b;
	CvUtils::linreg(lHistory, a, b);

	double iNormalizedStartTurn = b;
	double iNormalizedCurrentTurn = a * iNumTurns + b;

	int iGrowth = int(100 * (iNormalizedCurrentTurn = iNormalizedStartTurn) / iNormalizedStartTurn);

	return iGrowth;
}


bool lStabilityTypesCmp(StabilityLevels a, StabilityLevels b)
{
	return (-a) < (-b);
}

int CvStatbility::determineCrisisType(std::vector<StabilityLevels>& lStabilityTypes)
{
	StabilityLevels iLowestEntry = *std::max_element(lStabilityTypes.begin(), lStabilityTypes.end(), lStabilityTypesCmp);
	return std::find(lStabilityTypes.begin(), lStabilityTypes.end(), iLowestEntry) - lStabilityTypes.begin();
}

int calculateCommerceRank(PlayerTypes eIndex, int iTurn)
{
	return 0;
}

typedef struct calculatePowerRankCmp
{

	calculatePowerRankCmp(PlayerTypes iPlayer, int iTurn)
	{
		m_iTurn = iTurn;
		m_iPlayer = iPlayer;
	}
	// Reverse
	bool operator<(const calculatePowerRankCmp& other)
	{
		return (GET_PLAYER(this->m_iPlayer).getPowerHistory(this->m_iTurn) > 
			GET_PLAYER(other.m_iPlayer).getPowerHistory(other.m_iTurn));
	}
	// for std::find
	bool operator==(const PlayerTypes other)
	{
		return (this->m_iPlayer == other);
	}

	int m_iTurn;
	PlayerTypes m_iPlayer;
} calculatePowerRankCmp;

int CvStatbility::calculatePowerRank(PlayerTypes eIndex, int iTurn)
{
	std::vector<calculatePowerRankCmp> lPowerValues;
	for (int i = 0; i < NUM_PLAYERS; i++)
		lPowerValues.push_back(calculatePowerRankCmp((PlayerTypes)i, iTurn));
	std::sort(lPowerValues.begin(), lPowerValues.end());
	return std::find(lPowerValues.begin(), lPowerValues.end(), eIndex) - lPowerValues.begin();
}


bool calculateRankedAttitudesCmp(PlayerTypes &a, PlayerTypes &b)
{
	return GC.getGameINLINE().getPlayerScore(a) > GC.getGameINLINE().getPlayerScore(b);
}

void CvStatbility::calculateRankedAttitudes(PlayerTypes eIndex, std::vector<PlayerTypes>& lContacts, 
	std::vector<int>& lStronger, 
	std::vector<int>& lEqual,
	std::vector<int>& lWeaker)
{
	lContacts.push_back(eIndex);
	std::sort(lContacts.begin(), lContacts.end(), calculateRankedAttitudesCmp);
	uint iPlayerIndex = std::find(lContacts.begin(), lContacts.end(), eIndex) - lContacts.begin();
	
	uint iRangeSize = 4;
	if (iPlayerIndex <= lContacts.size() / 5)
		iRangeSize = 3;

	uint iRange = lContacts.size() / iRangeSize;
	uint iLeft = std::max(0u, iPlayerIndex - iRange / 2);
	uint iRight = std::min(iLeft + iRange, lContacts.size() - 1);

	for (uint i = 0; i < iLeft; i++)
	{
		if ((PlayerTypes)i != eIndex)
			lStronger.push_back(calculateAttitude(lContacts[i], eIndex));
	}

	for (uint i = iLeft; i < iRight; i++)
	{
		if ((PlayerTypes)i != eIndex)
			lEqual.push_back(calculateAttitude(lContacts[i], eIndex));
	}

	for (uint i = iRight; i < lContacts.size(); i++)
	{
		if ((PlayerTypes)i != eIndex)
			lWeaker.push_back(calculateAttitude(lContacts[i], eIndex));
	}

}

// AIÌ¬¶È
int CvStatbility::calculateAttitude(PlayerTypes iFromPlayer, PlayerTypes iToPlayer)
{
	CvPlayerAI* pPlayer = GET_PLAYER(iFromPlayer).AI();

	int iAttitude = pPlayer->AI_getAttitudeVal(iToPlayer);
	iAttitude -= pPlayer->AI_getSameReligionAttitude(iToPlayer);
	iAttitude -= pPlayer->AI_getDifferentReligionAttitude(iToPlayer);
	iAttitude -= pPlayer->AI_getFirstImpressionAttitude(iToPlayer);

	return iAttitude;
}
// ×Ú½ÌÈÝÈÌ
bool CvStatbility::isTolerated(PlayerTypes eIndex, ReligionTypes iReligion)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	ReligionTypes iStateReligion = pPlayer.getStateReligion();

	// should not be asked, but still check
	if (iStateReligion == iReligion) return true;

	// civics
	if (pPlayer.getCivics((CivicOptionTypes)4) == iTolerance or pPlayer.getCivics((CivicOptionTypes)4) == iSecularism) return true;

	// Exceptions
	// ÈåÑ§ºÍµÀ½Ì
	if (iStateReligion == iConfucianism and iReligion == iTaoism) return true;
	if (iStateReligion == iTaoism and iReligion == iConfucianism) return true;
	// Ó¡¶È½ÌºÍ·ð½Ì
	if (iStateReligion == iHinduism and iReligion == iBuddhism) return true;
	if (iStateReligion == iBuddhism and iReligion == iHinduism) return true;

	// Poland ²¨À¼
	std::vector<ReligionTypes> lChristianity = (list_of(iOrthodoxy), iCatholicism, iProtestantism );
	if (eIndex == iPoland and
		VAL_IN(iStateReligion, lChristianity) and
		VAL_IN(iReligion, lChristianity))
		return true;

	return false;
}

void CvStatbility::checkResurrection(int iGameTurn)
{
	int iNationalismModifier = std::min(20, 4 * m_iCivsWithNationalism); // data.m_iCivsWithNationalism

	std::vector<PlayerTypes> lPossibleResurrections;
	bool bDeadCivFound = false;

	// iterate all civs starting with a random civ
	for (int iLoopCiv = 0; iLoopCiv < NUM_PLAYERS; iLoopCiv++)
		if (CvUtils::canRespawn((PlayerTypes)iLoopCiv))
			lPossibleResurrections.push_back((PlayerTypes)iLoopCiv);

	// utils.getSortedList(lPossibleResurrections, lambda x: data.players[x].iLastTurnAlive):
	std::sort(lPossibleResurrections.begin(), lPossibleResurrections.end(), boost::bind(std::less<int>(), 
		boost::bind(&CvStatbility::getLastTurnAlive, this,  _1), boost::bind(&CvStatbility::getLastTurnAlive, this, _2)));
	
	// higher respawn chance for civs whose entire core is controlled by minor civs
	for (uint i = 0; i < len(lPossibleResurrections); i++)
	{
		PlayerTypes iLoopCiv = lPossibleResurrections[i];
	
		if (GC.getGameINLINE().getGameTurn() - getLastTurnAlive(iLoopCiv) < getTurns(15))
			continue;

		std::vector<coord > tPlots;
		std::vector<CvCity*> lCities;

		Areas.getRespawnArea(iLoopCiv, tPlots);
		for (uint m = 0; m < len(tPlots); m++)
			lCities.append(GC.getMapINLINE().plot(tPlots[m].first, tPlots[m].second)->getPlotCity());

		for (uint j = 0; j < len(lCities); j++)
		{   
			CvCity* city = lCities[j];
			std::vector<PlayerTypes> tP = (list_of(iIndependent), iIndependent2, iNative, iBarbarian);
			if (not VAL_IN(city->getOwner(), tP))
			{
				break;
			}
			else
			{
				std::vector<CvCity*> lCityList;
				getResurrectionCities(iLoopCiv, lCityList);
				if (len(lCityList))
				{
					doResurrection(iLoopCiv, lCityList);
					return;
				}
			}
		}
	}

	// utils.getSortedList(lPossibleResurrections, lambda x: data.players[x].iLastTurnAlive)
	//std::sort(lPossibleResurrections.begin(), lPossibleResurrections.end(), boost::bind(std::less<bool>(), 
	//	boost::bind(&CvStatbility::getLastTurnAlive, this, _1), boost::bind(&CvStatbility::getLastTurnAlive, this, _2)));
	std::sort(lPossibleResurrections.begin(), lPossibleResurrections.end(), boost::bind(std::less<int>(),
		boost::bind(&CvStatbility::getLastTurnAlive, this, _1), boost::bind(&CvStatbility::getLastTurnAlive, this, _2)));

	/*
	template<class R> struct apply
{
	typedef R result_type;

	template<class F> result_type operator()(F & f) const
	{
		return f();
	}
	*/
	/*
	template<class _Ty>
	struct less
		: public binary_function<_Ty, _Ty, bool>
	{	// functor for operator<
	bool operator()(const _Ty& _Left, const _Ty& _Right) const
		{	// apply operator< to operands
		return (_Left < _Right);
		}
	};
	*/
	for (uint i = 0; i < len(lPossibleResurrections); i++)
	{
		PlayerTypes iLoopCiv = lPossibleResurrections[i];
		uint iMinNumCities = 2;

		// special case Netherlands: need only one city to re spawn (Amsterdam)
		if (iLoopCiv == iNetherlands)
			iMinNumCities = 1;

		int iRespawnRoll = GC.getGameINLINE().getSorenRandNum(100, "Respawn Roll");
		if (iRespawnRoll - iNationalismModifier + 10 < tResurrectionProb[iLoopCiv])
		{
			std::vector<CvCity*> lCityList;
			getResurrectionCities(iLoopCiv, lCityList);
			if (len(lCityList) >= iMinNumCities)
			{
				doResurrection(iLoopCiv, lCityList);
				return;
			}
		}
	}
}

void CvStatbility::getResurrectionCities(PlayerTypes iPlayer, std::vector<CvCity*>& lCities, bool bFromCollapse)
{
	CvPlayer& pPlayer = GET_PLAYER(iPlayer);
	int teamPlayer = pPlayer.getTeam();
	std::vector<CvCity*> lPotentialCities;
	std::vector<CvCity*> lFlippingCities;

	CvPlot* tCapital = Areas.getRespawnCapital(iPlayer);

	std::vector<coord > tPlots;
	Areas.getRespawnArea(iPlayer, tPlots);
	for (uint i = 0; i < len(tPlots); i++)
	{
		CvPlot* plot = GC.getMapINLINE().plot(tPlots[i].first, tPlots[i].second);
		if (plot->isCity())
		{
			CvCity* city = plot->getPlotCity();
			// for humans: exclude recently conquered cities to avoid annoying reflips
			if (city->getOwner() != getHumanID() or city->getGameTurnAcquired() < GC.getGameINLINE().getGameTurn() - getTurns(5))
				lPotentialCities.append(city);
		}
	}
	for (uint i = 0; i < len(lPotentialCities); i++)
	{
		CvCity* city = lPotentialCities[i];
		PlayerTypes iOwner = city->getOwner();
		int iMinNumCitiesOwner = 3;

		// barbarian and minor cities always flip
		if (iOwner >= iNumPlayers)
		{
			lFlippingCities.append(city);
			continue;
		}

		int iOwnerStability = getStabilityLevel(iOwner);
		bool bCapital = (city->getX() == tCapital->getX() and city->getY() == tCapital->getY());

		// flips are less likely before Nationalism
		if (m_iCivsWithNationalism == 0)
			iOwnerStability += 1;

		if (getHumanID() != iOwner)
		{
			iMinNumCitiesOwner = 2;
			iOwnerStability -= 1;
		}

		if (GET_PLAYER(iOwner).getNumCities() >= iMinNumCitiesOwner)
		{
			// special case for civs returning from collapse: be more strict
			if (bFromCollapse)
			{
				if (iOwnerStability < iStabilityShaky) lFlippingCities.append(city);
				continue;
			}

			// owner stability below shaky: city always flips
			// 1SDAN: Requires below stable for China rising within AI Manchuria
			if (iOwnerStability < iStabilityStable or (iOwnerStability < iStabilityShaky and (getHumanID() == iManchuria or iOwner != iManchuria or iPlayer != iChina)))
				lFlippingCities.append(city);

			// owner stability below stable: city flips if far away from their capital, or is capital spot of the dead civ
			// 1SDAN: Requires below solid for China rising within AI Manchuria
			else if (iOwnerStability < iStabilitySolid or (iOwnerStability < iStabilityStable and (getHumanID() == iManchuria or iOwner != iManchuria or iPlayer != iChina)))
			{
				CvCity* ownerCapital = GET_PLAYER(iOwner).getCapitalCity();
				int iDistance = CvUtils::calculateDistance(city->getX(), city->getY(), ownerCapital->getX(), ownerCapital->getY());
				if (bCapital or iDistance >= 8)
					lFlippingCities.append(city);
			}

			// owner stability below solid: only capital spot flips
			// 1SDAN: Does not happen for China rising within AI Manchuria
			else if (iOwnerStability < iStabilitySolid and (getHumanID() == iManchuria or iOwner != iManchuria or iPlayer != iChina))
				if (bCapital) lFlippingCities.append(city);
		}
	}

	// if capital exists and does not flip, the respawn fails
	if (tCapital->isCity())
	{
		CvCity* fCity = tCapital->getPlotCity();
		if (not VAL_IN(fCity, lFlippingCities))
			lCities.clear();
	}
	// if only up to two cities wouldn't flip, they flip as well (but at least one city has to flip already, else the respawn fails)
	if (len(lFlippingCities) + 2 >= len(lPotentialCities) and len(lFlippingCities) > 0 and len(lFlippingCities) * 2 >= len(lPotentialCities) and not bFromCollapse)
	{
		// cities in core are not affected by this
		for (uint i = 0; i < len(lPotentialCities); i++)
		{
			CvCity* city = lPotentialCities[i];
			if (not city->plot()->isCore(city->getOwner()) and not VAL_IN(city, lFlippingCities))
				lFlippingCities.append(city);
		}
	}
	lCities = lFlippingCities;
}

void CvStatbility::resurrectionFromCollapse(PlayerTypes eIndex, std::vector<CvCity*>& lCityList)
{
	if (len(lCityList)) doResurrection(eIndex, lCityList);
}

void CvStatbility::doResurrection(PlayerTypes eIndex, std::vector<CvCity*>& lCityList, bool AskFilp)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	CvTeam& teamPlayer = GET_TEAM(pPlayer.getTeam());

	pPlayer.setAlive(true);

	m_iRebelCiv = eIndex;

	for (int iOtherCiv = 0; iOtherCiv < NUM_PLAYERS; iOtherCiv++)
	{
		CvPlayer& pOtherCiv = GET_PLAYER((PlayerTypes)iOtherCiv);
		CvTeam& tOtherCiv = GET_TEAM(pOtherCiv.getTeam());

		if (eIndex == iOtherCiv) continue;

		teamPlayer.makePeace(pOtherCiv.getTeam());

		if (teamPlayer.isVassal(pOtherCiv.getTeam()))
			tOtherCiv.freeVassal(pPlayer.getTeam());

		if (tOtherCiv.isVassal(pPlayer.getTeam()))
			teamPlayer.freeVassal(pOtherCiv.getTeam());
	}

	setNumPreviousCities(eIndex, 0);

	pPlayer.AI_reset(false);

	PlayerTypes iHuman = getHumanID();

	// reset player espionage weight
	GET_PLAYER(GC.getGameINLINE().getActivePlayer()).setEspionageSpendingWeightAgainstTeam(pPlayer.getTeam(), 0);
	
	// assign technologies
	std::vector<int> lTechs;
	getResurrectionTechs(eIndex, lTechs);
	for (uint iTech = 0; iTech < lTechs.size(); iTech++)
		teamPlayer.setHasTech((TechTypes)iTech, true, eIndex, false, false);

	// determine army size
	int iNumCities = lCityList.size();
	int iGarrison = 2;
	int iArmySize = pPlayer.getCurrentEra();

	pPlayer.setLatestRebellionTurn(GC.getGameINLINE().getGameTurn());

	// add former colonies that are still free , including barbarians
	for (int iMinor = NUM_PLAYERS; iMinor < MAX_PLAYERS; iMinor++)
	{
		CvPlayer& pPlayer = GET_PLAYER((PlayerTypes)iMinor);
		if (pPlayer.isAlive())
		{
			int iLoop = 0;
			for (CvCity* city = pPlayer.firstCity(&iLoop); city != NULL; city = pPlayer.nextCity(&iLoop))
			{
				if (city->getOriginalOwner() == eIndex)
					if (pPlayer.getSettlerValue(city->getX(), city->getY()) >= HISTORICAL_VALUE)
						if (not VAL_IN(city, lCityList))
							lCityList.push_back(city);
			}
		}
	}

	std::vector<PlayerTypes> lOwners;
	std::map<PlayerTypes, std::vector<CvUnit*> > dRelocatedUnits;

	for (unsigned int i = 0; i < lCityList.size(); i++)
	{
		CvCity* city = lCityList[i];

		PlayerTypes iOwner = city->getOwnerINLINE();
		CvPlayer& pOwner = GET_PLAYER(iOwner);

		int x = city->getX();
		int y = city->getY();

		bool bCapital = city->isCapital();

		int iNumDefenders = std::max(2, GET_PLAYER(eIndex).getCurrentEra() - 1);

		std::vector<CvUnit*> lFlippedUnits;
		std::vector<CvUnit*> lRelocatedUnits;
		CvUtils::flipOrRelocateGarrison(city, iNumDefenders, lFlippedUnits, lRelocatedUnits);

		if (dRelocatedUnits.count(iOwner))
			dRelocatedUnits[iOwner].insert(dRelocatedUnits[iOwner].end(), lRelocatedUnits.begin(), lRelocatedUnits.end());
		else
			dRelocatedUnits[iOwner] = lRelocatedUnits;
		
		if (pOwner.isBarbarian() or pOwner.isMinorCiv())
			CvUtils::completeCityFlip(x, y, eIndex, iOwner, 100, false, true, true, true);
		else
			CvUtils::completeCityFlip(x, y, eIndex, iOwner, 75, false, true, true, true);

		CvUtils::flipOrCreateDefenders(eIndex, lFlippedUnits, x, y, iNumDefenders);

		CvCity* newCity = city; // ÊÇ·ñ¶à´ËÒ»¾Ù£¿

		// Leoreth: rebuild some city infrastructure
		for (int iBuilding = 0; iBuilding < iNumBuildings; iBuilding++)
		{
			if (pPlayer.canConstruct((BuildingTypes)iBuilding, true, false, false) and
				newCity->canConstruct((BuildingTypes)iBuilding, true, false, false) and
				pPlayer.getCurrentEra() >= GC.getBuildingInfo((BuildingTypes)iBuilding).getFreeStartEra() and
				not CvUtils::isUniqueBuilding((BuildingTypes)iBuilding) and
				GC.getBuildingInfo((BuildingTypes)iBuilding).getPrereqReligion() == NO_RELIGION)
				newCity->setHasRealBuilding((BuildingTypes)iBuilding, true);
		}

		if (bCapital and iOwner < NUM_PLAYERS) relocateCapital(iOwner);

		if (not VAL_IN(iOwner, lOwners)) lOwners.push_back(iOwner);
	}

	std::map<PlayerTypes, std::vector<CvUnit*> >::const_iterator it;
	for (it = dRelocatedUnits.begin(); it != dRelocatedUnits.end(); ++it)
	{
		PlayerTypes iOwner = it->first;
		if (iOwner < NUM_PLAYERS)
			CvUtils::relocateUnitsToCore(iOwner, dRelocatedUnits[iOwner]);
		else
			CvUtils::killUnits(dRelocatedUnits[iOwner]);
	}

	for (unsigned int i = 0; i < lOwners.size(); i++)
	{
		PlayerTypes iOwner = lOwners[i];
		TeamTypes teamOwner = GET_PLAYER(iOwner).getTeam();
		bool bOwnerHumanVassal = GET_TEAM(teamOwner).isVassal(GET_PLAYER(iHuman).getTeam());

		if (iOwner == iHuman and iOwner != eIndex and iOwner != iBarbarian)
		{
			int iRand = GC.getGameINLINE().getSorenRandNum(100, "Stop birth");

			if (iRand >= tAIStopBirthThreshold[iOwner] and not bOwnerHumanVassal)
				GET_TEAM(teamOwner).declareWar(GET_PLAYER(eIndex).getTeam(), false, NO_WARPLAN);
			else
				GET_TEAM(teamOwner).makePeace(GET_PLAYER(eIndex).getTeam());
		}
	}

	if (GET_PLAYER(eIndex).getNumCities() == 0)
		NULL;// debugTextPopup
	

	if (m_iResurrections[eIndex] == 1)
		if (eIndex == iNubia or eIndex == iChad or eIndex == iKazakh)
			GET_PLAYER(eIndex).setReborn(true);

	relocateCapital(eIndex, true);

	// give the new civ a starting army
	CvCity* capital = pPlayer.getCapitalCity();
	int x = capital->getX();
	int y = capital->getY();

	CvUtils::makeUnit(CvUtils::getBestInfantry(eIndex), eIndex, x, y, 2 * iArmySize + iNumCities);
	CvUtils::makeUnit(CvUtils::getBestCavalry(eIndex), eIndex, x, y, iArmySize);
	CvUtils::makeUnit(CvUtils::getBestCounter(eIndex), eIndex, x, y, iArmySize);
	CvUtils::makeUnit(CvUtils::getBestSiege(eIndex), eIndex, x, y, iArmySize + iNumCities);

	// set state religion based on religions in the area
	setStateReligion(eIndex);

	switchCivics(eIndex);

	/*gDLL->getInterfaceIFace()->addMessage(iHuman, true, iDuration, gDLL->getText(
		"TXT_KEY_INDEPENDENCE_TEXT", pPlayer.getCivilizationAdjectiveKey()), "", 0,
		"", ColorTypes(iGreen), -1, -1, true, true);*/

	// if (VAL_IN(bAskFlip, lOwners) and VAL_IN(iHuman, lOwners)) rebellionPopup(eIndex);

	setStabilityLevel(eIndex, iStabilityStable);

	m_iPlagueCountdown[eIndex] -= 10;
	CvUtils::clearPlague(eIndex);
	convertBackCulture(eIndex);

	// Ó²±àÂë
	int iGameTurn = GC.getGameINLINE().getGameTurn();
	// change the cores of some civs on respawn
	if (eIndex == iGreece) GET_PLAYER(iGreece).setReborn(true);
	else if (eIndex == iChina)
		if (iGameTurn > getTurnForYear(tBirth[iMongolia]))
			GET_PLAYER(iChina).setReborn(true);
		else if (eIndex == iIndia) GET_PLAYER(iIndia).setReborn(iGameTurn < getTurnForYear(1900));
		else if (eIndex == iArabia) GET_PLAYER(iArabia).setReborn(true);
		else if (eIndex == iVikings) GET_PLAYER(iVikings).setReborn(true);
		else if (eIndex == iPhilippines) GET_PLAYER(iPhilippines).setReborn(true); // For Spanish CNM

		// others revert to their old cores instead Ó²±àÂë : ÃÉ¹Å£¬°¢À­²®
	if (eIndex == iArabia or eIndex == iMongolia) GET_PLAYER(eIndex).setReborn(false);

	// resurrection leaders
	if (resurrectionLeaders.count(eIndex))
		if (pPlayer.getLeader() != resurrectionLeaders[eIndex])
			pPlayer.setLeader(resurrectionLeaders[eIndex]);

	// Leoreth: report dynamic civs
	// error : dc.onCivRespawn(eIndex, lOwners);
}

void CvStatbility::getResurrectionTechs(PlayerTypes eIndex, std::vector<int>& lTechList)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	std::vector<PlayerTypes> lSourceCivs;

	// same tech group
	for (uint i = 0; i < lTechGroups.size(); i++)
	{
		std::vector<PlayerTypes> lRegionList = lTechGroups[i];
		if (VAL_IN(eIndex, lRegionList))
		{
			for (uint j = 0; j < lRegionList.size(); j++)
			{
				PlayerTypes iPeer = lRegionList[j];
				if (iPeer != eIndex and GET_PLAYER(iPeer).isAlive())
					lSourceCivs.push_back(iPeer);
			}
		}
	}

	// direct neighbors (India can benefit from England etc)
	for (int iPeer = 0; iPeer < NUM_PLAYERS; iPeer++)
	{
		if (iPeer != eIndex and
			not VAL_IN(iPeer, lSourceCivs) and
			GET_PLAYER((PlayerTypes)iPeer).isAlive())
		{
			if (pPlayer.isNeighbor((PlayerTypes)iPeer)) 
				lSourceCivs.append((PlayerTypes)iPeer);
		}
	}

	// use independents as source civs in case no other can be found
	if (lSourceCivs.empty())
	{
		lSourceCivs.append(iIndependent);
		lSourceCivs.append(iIndependent2);
	}

	for (int iTech = 0; iTech < GC.getNumTechInfos(); iTech++)
	{
		// at least half of the source civs know this technology
		int iCount = 0;
		for (uint iOtherCiv = 0; iOtherCiv < lSourceCivs.size(); iOtherCiv++)
		{
			if (GET_TEAM(GET_PLAYER((PlayerTypes)iOtherCiv).getTeam()).isHasTech((TechTypes)iTech))
				iCount += 1;
		}

		if (2u * iCount >= lSourceCivs.size())
			lTechList.append(iTech);
	}
}

bool capitalCompare(CvCity* iCity, CvCity* jCity)
{
	int iI = std::max(0, getTurns(500) - iCity->getGameTurnFounded()) + iCity->getPopulation() * 5;
	int iJ = std::max(0, getTurns(500) - jCity->getGameTurnFounded()) + jCity->getPopulation() * 5;
	return (iI < iJ);
};

void CvStatbility::relocateCapital(PlayerTypes eIndex, bool bResurrenction)
{
	if (eIndex < NUM_PLAYERS) return;
	if (GET_PLAYER(eIndex).getNumCities() == 0) return;

	CvPlot* tCapital = Areas.getCapital(eIndex);
	CvCity* oldCapital = GET_PLAYER(eIndex).getCapitalCity();
	CvCity* newCpaital = NULL;

	if (bResurrenction) tCapital = Areas.getRespawnCapital(eIndex);

	if (tCapital->isCity() and tCapital->getPlotCity()->getOwnerINLINE() == eIndex)
		newCpaital = tCapital->getPlotCity();
	else
	{
		std::vector<CvCity*> lCities;
		CvUtils::getCityList(eIndex, lCities);
		std::sort(lCities.begin(), lCities.end(), capitalCompare);
		/*std::sort(lCities.begin(), lCities.end(), boost::bind(std::greater<CvCity*>(), 
			boost::bind(std::max(0, getTurns(500) - _1->getGameTurnFounded()) + _1->getPopulation() * 5, _1),
			boost::bind(std::max(0, getTurns(500) - _2->getGameTurnFounded()) + _2->getPopulation() * 5, _2));*/
		newCpaital = lCities.front();
	}

	oldCapital->setHasRealBuilding(iPalace, false);
	newCpaital->setHasRealBuilding(iPalace, true);
}

//ÎÄ»¯Öµ¼ÆËã
void CvStatbility::convertBackCulture(PlayerTypes iCiv)
{
	std::vector<coord > tPlot;
	Areas.getRespawnArea(iCiv, tPlot);

	for (uint i = 0; i < tPlot.size(); i++)
	{
		CvPlot* plot = GC.getMapINLINE().plot(tPlot[i].first, tPlot[i].second);
		CvCity* city = plot->getPlotCity();
		if (plot->isCity())
		{
			if (city->getOwnerINLINE() == iCiv)
			{
				int iCulture = 0;
				for (int iMinor = NUM_PLAYERS; iMinor < MAX_PLAYERS; iMinor++)
				{
					iCulture += city->getCulture((PlayerTypes)iMinor);
					city->setCulture(iCiv, 0, true, true);
				}
				city->changeCulture(iCiv, iCulture, true, true);
			}
		}
		else if (plot->isCityRadius() and plot->getOwnerINLINE() == iCiv)
		{
			int iCulture = 0;
			for (int iMinor = NUM_PLAYERS; iMinor < MAX_PLAYERS; iMinor++)
			{
				iCulture += city->getCulture((PlayerTypes)iMinor);
				city->setCulture(iCiv, 0, true, true);
			}
			plot->changeCulture(iCiv, iCulture, true);
		}
	}
}

void CvStatbility::setStateReligion(PlayerTypes iCiv)
{
	std::vector<coord > tPlots;
	Areas.getCoreArea(iCiv, tPlots);

	std::vector<CvPlot*> lPlots;
	for (uint i = 0; i < tPlots.size(); i++)
		lPlots.push_back(GC.getMapINLINE().plot(tPlots[i].first, tPlots[i].second));

	std::vector<CvCity*> lCities;
	CvUtils::getAreaCities(lPlots, lCities);

	int iNumReligions = GC.getNumReligionInfos();
	std::vector<int> lReligions(iNumReligions, 0);

	for (uint iCity = 0; iCity < lCities.size(); iCity++)
	{
		for (int iReligion = 0; iReligion < iNumReligions; iReligion++)
		{
			if (GC.getReligionInfo((ReligionTypes)iReligion).isLocal() and
				lCities[iCity]->plot()->getSpreadFactor((ReligionTypes)iReligion) != REGION_SPREAD_CORE)
				continue;
			if (lCities[iCity]->isHasReligion((ReligionTypes)iReligion))
				lReligions[iReligion] += 1;
		}
	}

	int iHighestEntry = *std::max_element(lReligions.begin(), lReligions.end());

	if (iHighestEntry > 0)
		GET_PLAYER(iCiv).setLastStateReligion((ReligionTypes)lReligions[iHighestEntry]);
}

void CvStatbility::switchCivics(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);

	for (int iCategory = 0; iCategory < iNumCivicCategories; iCategory++)
	{
		int iBestCivic = pPlayer.AI()->AI_bestCivic((CivicOptionTypes)iCategory);

		if (iBestCivic >= 0) pPlayer.setCivics((CivicOptionTypes)iCategory, (CivicTypes)iBestCivic);
	}

	pPlayer.setRevolutionTimer(GC.getDefineINT("MIN_REVOLUTION_TURNS"));
}

// error
//void rebellionPopup(int iRebelCiv)
//{
//	// showPopup
//}

int CvStatbility::sign(int x)
{
	if (x == 0) return x;
	return (x > 0) ? 1 : -1;
}

int CvStatbility::getCorePopulationModifier(int iEra)
{	
	return m_tEraCorePopulationModifiers[iEra];
}

int CvStatbility::getUnionPop(PlayerTypes eIndex, int iCorePopulationModifier)
{
	int iUnionPop = 0;

	int iLoop = 0;
	CvPlayer& pPlayer = GET_PLAYER(eIndex);

	for (CvCity* pCity = pPlayer.firstCity(&iLoop); pCity != NULL; pCity = pPlayer.nextCity(&iLoop))
	{
		if (pCity->plot()->isCore(eIndex))
			iUnionPop += iCorePopulationModifier * pCity->getPopulation() / 100;
	}

	return iUnionPop;
}

void CvStatbility::balanceStability(PlayerTypes eIndex, StabilityLevels eNewStabilityLevel)
{
	// debugTextPopup

	// set stability to at least the specified level
	setStabilityLevel(eIndex, std::max(eNewStabilityLevel, getStabilityLevel(eIndex)));

	// prevent collapse if they were going to
	changeTurnsToCollapse(eIndex, -1);

	// update number of cities so vassals survive losing cities
	setNumPreviousCities(eIndex, GET_PLAYER(eIndex).getNumCities());

	// reset previous commerce
	setPreviousCommerce(eIndex, 0);

	// reset war, economy and happiness trends to give them a breather
	resetEconomyTrend(eIndex);
	resetHappinessTrend(eIndex);
	resetWarTrends(eIndex);
}

bool CvStatbility::isDecline(PlayerTypes eIndex)
{
	return (getHumanID() != eIndex and GET_PLAYER(eIndex).isReborn() and
		GC.getGameINLINE().getGameTurn() >= getTurnForYear(tFall[eIndex]));
}
