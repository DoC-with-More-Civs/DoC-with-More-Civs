// CvStatbility.h
/*
// 城市遍历写法
	int iLoop = 0;
	for (CvCity* pLoopCity = pPlayer.firstCity(&iLoop); pLoopCity != NULL; pLoopCity = pPlayer.nextCity(&pLoopCity))
	{
		if (pLoopCity.getOriginalOwner() == eIndex)
			iLostCities++;
	}
*/

/*
// addMessage写法

	gDLL->getInterfaceIFace()->addMessage(eIndex, false, iDuration, gDLL-getText( "TXT_KEY_STABILITY_COLLAPSING_WARNING"), "", 0, "", ColorTypes(iRed), -1, -1, true, true);
*/

#include "CvConst.h"

#include <vector>
#include <set>
#include <algorithm>

#define NUM_PLAYERS 		iNumPlayers
#define HISTORICAL_VALUE 	(90)

#define VAL_IN(item,v) std::count(v.begin(), v.end(), item)

#define EPS 	(1e-8)
#define ZERO(x) (((x)>0?(x):-(x))<EPS)

typedef enum{
	"TXT_KEY_STABILITY_CRISIS_LEVEL_TERMINAL",
	"TXT_KEY_STABILITY_CRISIS_LEVEL_SEVERE",
	"TXT_KEY_STABILITY_CRISIS_LEVEL_MODERATE",
	"TXT_KEY_STABILITY_CRISIS_LEVEL_MINOR",
	"TXT_KEY_STABILITY_CRISIS_LEVEL_MINOR",
} tCrisisLevels;

typedef enum {
	"TXT_KEY_STABILITY_CRISIS_TYPE_EXPANSION",
	"TXT_KEY_STABILITY_CRISIS_TYPE_ECONOMY",
	"TXT_KEY_STABILITY_CRISIS_TYPE_DOMESTIC",
	"TXT_KEY_STABILITY_CRISIS_TYPE_FOREIGN",
	"TXT_KEY_STABILITY_CRISIS_TYPE_MILITARY",
} tCrisisTypes;

// Stability Levels
typedef enum {
	NO_STABILITY_LEVEL = -1,
	iStabilityCollapsing, iStabilityUnstable, iStabilityShaky, iStabilityStable, iStabilitySolid,
	iNumStabilityLevels // = 5
} STABILITY_LEVELS;


class CvStatbility
{
public:
	class Civics
	{
	public:
		Civics(std::vector<int>& lActiveCivics) 
		{ 
			for (int i = 0; i < lActiveCivics.size(); i++)
				m_activeCivics.insert(lActiveCivics[i]);
		}
		~Civics() {}
		
		bool contains(int civic) 
		{ 
			return (bool)m_activeCivics.count(civic); 
		}
		
		bool any(std::vector<int>& lCivics)
		{
			for (int i = 0; i < lCivics.size(); i++)
			{
				if (contains(lCivics[i])) return true;
			}
			return false;
		}
		
		bool no(int civic)
		{
			int type = GC.getCivicInfo(civic).getCivicOptionType();
			bool bNotIn = true;
			std::set<int>::const_iterator it;
			for (it = m_activeCivics.begin(); it != m_activeCivics.end(); ++it)
			{
				if (type == GC.getCivicInfo(*it).getCivicOptionType())
					bNotIn = false;
			}
			if (bNotIn) return false;
			
			return !contains(civic);
		}
		
	private:
		std::set<int> m_activeCivics;
	}
	
public:
	CvStatbility();
	virtual ~CvStatbility();
	
	void doTurn(int iGameTurn);
	void endTurn(PlayerTypes iPlayer);
	
	void triggerCollapse(PlayerTypes eIndex);
	void scheduleCollapse(PlayerTypes eIndex);
	void collapseToCore(PlayerTypes eIndex);
	void completeCollapse(PlayerTypes eIndex);
	
	void updateEconomyTrend(PlayerTypes eIndex);
	void updateHappinessTrend(PlayerTypes eIndex);
	void updateWarTrend(PlayerTypes eIndex, PlayerTypes eEnemyIndex);
	
	void checkLostCitiesCollapse(PlayerTypes eIndex);
	void checkLostCoreCollapse(PlayerTypes eIndex);  // Exposed to Python
	void checkBarbarianCollapse(PlayerTypes eIndex); // Exposed to Python
	
	int getStabilityLevel(PlayerTypes eIndex);
	void setStabilityLevel(PlayerTypes eIndex, int eStabilityLevel);
	int determineStabilityLevel(int eCurrentLevel, int iStability, bool bFall =false);
	
	void incrementStability(PlayerTypes eIndex);
	void decrementStability(PlayerTypes eIndex);
	
	void checkStability(PlayerTypes eIndex); // Exposed to Python
	// 核心函数 
	void checkStability(PlayerTypes eIndex, bool bPositive = false, int iMaster = -1); 
	// 核心函数 
	void calculateStability(PlayerTypes eIndex);
	
	int getCivicStability(PlayerTypes eIndex, std::vector<int>& lCivics);
	
	void balanceStability(PlayerTypes eIndex, int eNewStabilityLevel); // Exposed to Python
	
	void relocateCapital(PlayerTypes eIndex, bool bResurrenction = false);
	void setStateReligion(PlayerTypes iCiv);
	void switchCivics(PlayerTypes eIndex);
	void convertBackCulture(PlayerTypes iCiv);
	void downgradeCottages(PlayerTypes eIndex);
	
	int calculateEconomicGrowth(PlayerTypes eIndex, int iNumTurns);
	int calculateEconomicGrowthNeighbors(PlayerTypes eIndex, int iNumTurns);
	
	void getPossibleMinors(PlayerTypes eIndex，std::vector<PlayerTypes>& lCivs);
	void secession(PlayerTypes eIndex, std::vector<CvCity*>& lCities);
	void secedeCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities, bool bRazeMinorCities = false);
	void secedeCity(CvCity* city, PlayerTypes iNewOwner, bool bRelocate);
	
	void startWar(PlayerTypes iPlayer, PlayerTypes iEnemy);
	
	void resurrectionFromCollapse(PlayerTypes eIndex, std::vector<CvCity*>& lCityList);
	void doResurrection(PlayerTypes eIndex, std::vector<CvCity*>& lCityList, bool AskFilp = true);
	void getResurrectionTechs(PlayerTypes eIndex, std::vector<int>& lTechList);
	
	int getUnionPop(PlayerTypes eIndex, int iCorePopulationModifier);
	
	bool isImmune(PlayerTypes eIndex);
	bool isDecline(PlayerTypes eIndex);
	bool isTolerated(PlayerTypes eIndex, ReligionTypes iReligion);
	
	int calculateAttitude(PlayerTypes iFromPlayer, PlayerTypes iToPlayer);
	int calculateTrendScore(std::vector<int>& lTrend);
	int calculateSumScore(std::vector<int>& lScores, int iThreshold  = 1);
	
public:
	int getTurnsToCollapse(PlayerTypes eIndex); 
	void changeTurnsToCollapse(PlayerTypes eIndex, int iChange);
	
	int getCrisisCountdown(PlayerTypes eIndex);
	void changeCrisisCountdown(PlayerTypes eIndex, int iChange);
	
	int getHumanRazePenalty(void); 
	void changeHumanRazePenalty(int iChange);
	
	int getBarbarianLosses(PlayerTypes eIndex);
	void changeBarbarianLosses(PlayerTypes eIndex, int iChange);
	
	void setHumanStability(int iNewValue);
	
	void getSecedingCities(PlayerTypes eIndex, std::vector<CvCity*> lCities);
	void setSecedingCities(PlayerTypes eIndex, std::vector<CvCity*> lCities);
	
	int getRomanPigs(void);
	void setRomanPigs(int iNewValue);
	
	int getNumPreviousCities(PlayerTypes eIndex);
	void setNumPrevoiusCities(PlayerTypes eIndex, int iNewValue);
	
	int getLastStabilityTurn(PlayerTypes eIndex);
	void setLastStabilityTurn(PlayerTypes eIndex, int iNewTurn);
	
	std::vector<int>& getEconomyTrend(PlayerTypes eIndex);
	std::vector<int>& getHappinessTrend(PlayerTypes eIndex);
	
	void setPreviousCommerce(PlayerTypes eIndex, int iNewValue);
	
	// reset war, economy and happiness trends to give them a breather
	void resetEconomyTrend(PlayerTypes eIndex);
	void resetHappinessTrend(PlayerTypes eIndex);
	void resetWarTrends(PlayerTypes eIndex);

public: // On Events : MUST BE Exposed to Python
	void onCityAcquired(CvCity* city, PlayerTypes iOwner, PlayerTypes iPlayer);
	void onCityRazed(PlayerTypes iPlayer, CvCity* city);
	void onTechAcquired(PlayerTypes iPlayer, int iTech);
	void onVassalState(PlayerTypes iMaster, PlayerTypes iVassal);
	void onChangeWar(bool bWar, int iTeam, int iOtherTeam);
	void onRevolution(PlayerTypes iPlayer);
	void onPlayerChangeStateReligion(PlayerTypes iPlayer);
	void onPalaceMoved(PlayerTypes iPlayer);
	void onWonderBuilt(PlayerTypes iPlayer, int iBuildingType);
	void onGoldenAge(PlayerTypes iPlayer);
	void onGreatPersonBorn(PlayerTypes iPlayer);
	void onCombatResult(PlayerTypes iWinningPlayer, PlayerTypes iLosingPlayer, int iLostPower);
	void onCivSpawn(PlayerTypes iPlayer);
	
protected:
	int m_iTurnsToCollapse[MAX_PLAYERS];
	int m_iBarbarianLosses[MAX_PLAYERS];
	int m_iCrisisCountdown[MAX_PLAYERS];
	int m_iNumPreviousCities[MAX_PLAYERS];
	int m_iLastStabilityTurn[MAX_PLAYERS];
	int m_iPreviousCommerce[MAX_PLAYERS];
	int m_iLastStability[MAX_PLAYERS];
	int m_iLastTurnAlive[MAX_PLAYERS];
	int m_iLastExpansionStability[MAX_PLAYERS];
	int m_iPlagueCountdown[MAX_PLAYERS];
	
	int m_iRomanPigs;
	int m_iCivWithNationalism;
	
	PlayerTypes m_iRebelCiv;
	PlayerTypes m_iHumanID;
	int m_iHumanRazePenalty;
	int m_iHumanStability;
	
	std::vector<int> m_lEconomyTrend[MAX_PLAYERS];
	std::vector<int> m_lHappinessTrend[MAX_PLAYERS];
	std::vector<int> m_lWarTrend[MAX_PLAYERS][MAX_PLAYERS];
	int m_lWarStartTurn[MAX_PLAYERS][MAX_PLAYERS];
	int m_lLastWarSuccess[MAX_PLAYERS][MAX_PLAYERS];
	
	StabilityLevelTypes m_eStabilityLevel[MAX_PLAYERS];
	
	std::vector<CvCity*> m_lSecedingCities[MAX_PLAYERS];
	
	std::vector<int> m_tEraCorePopulationModifiers;
}

// getter & Setter

int CvStatbility::getTurnsToCollapse(PlayerTypes eIndex)
{ 
	return m_iTurnsToCollapse[eIndex]; 
}

void CvStatbility::changeTurnsToCollapse(PlayerTypes eIndex, int iChange)
{
	m_iTurnsToCollapse[eIndex] += iChange;
}

int CvStatbility::getCrisisCountdown(PlayerTypes eIndex)
{
	return m_iCrisisCountdown[eIndex];
}

void CvStatbility::changeCrisisCountdown(PlayerTypes eIndex, int iChange)
{
	m_iCrisisCountdown[eIndex] += iChange;
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
	return m_iBarbarianLosses[eIndex];
}

void CvStatbility::changeBarbarianLosses(PlayerTypes eIndex, int iChange)
{
	m_iBarbarianLosses[eIndex] += iChange;
}

void CvStatbility::setHumanStability(int iNewValue)
{
	m_iHumanStability = iNewValue;
}

void CvStatbility::getSecedingCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities)
{	// error : 引用传递？
	lCities = m_lSecedingCities[eIndex];
}

void CvStatbility::setSecedingCities(PlayerTypes eIndex, std::vector<CvCity*> lCities)
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
	return m_iNumPreviousCities[eIndex];
}

void CvStatbility::setNumPrevoiusCities(PlayerTypes eIndex, int iNewValue)
{
	m_iNumPreviousCities[eIndex] = iNewValue;
}

int CvStatbility::getLastStabilityTurn(PlayerTypes eIndex)
{
	return m_iLastStabilityTurn[eIndex];
}

void CvStatbility::setLastStabilityTurn(PlayerTypes eIndex, int iNewTurn)
{
	m_iLastStabilityTurn[eIndex] = iNewTurn;
}

std::vector<int>& CvStatbility::getEconomyTrend(PlayerTypes eIndex)
{
	return m_lEconomyTrend[eIndex];
}

std::vector<int>& CvStatbility::getHappinessTrend(PlayerTypes eIndex)
{
	return m_lHappinessTrend[eIndex];
}

void CvStatbility::setPreviousCommerce(PlayerTypes eIndex, int iNewValue)
{
	m_iPreviousCommerce = iNewValue;
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

#include "CvGameCoreDLL.h"
#include "CvUtils.h"
#include <cmath>
#include "CvAreaUtils.h"
// from StoredData import data # edead


//import DynamicCivs as dc

import RegionMap
import Victory as vic

import PyHelpers
PyPlayer = PyHelpers.PyPlayer

import BugPath
from datetime import date



/*
	PlayerTypes getHumanID(void);
	void setHumanID(void);
	void getOwnedCoreCities(PlayerTypes eIndex, std::vector<CvCity*> &lCities);
	void resetUHV(PlayerTypes eIndex);
	void clearPlague(PlayerTypes eIndex);
	void linreg(std::vector<pair<int, int>>& lHistory, int &a, int &b);
	int getHighestEntry(std::vector<int> lReligions);
	bool isUniqueBuilding(int iBuilding);
	bool canRespawn(PlayerTypes iCiv);
	//bool isReborn(PlayerTypes eIndex);  to do: replace by pPlayer.isReborn()
	template<typename T>
	void getSortedList(std::vector<T>& lList, boost::function<bool(T, T)> bool bReverse = false);
	template<typename T>
	int getHighestEntry(std::vector<T>& lList, boost::function<bool(T, T)> fn);
	
template<typename T>
void getSortedList(std::vector<T>& lList, boost::function<bool(T, T)> fn, bool bReverse)
{
	std::sort(lList.begin(), lList.end(), fn);
	if (bReverse) std::reverse(lList.begin, lList.end());
}

template<typename T>
int getHighestEntry(std::vector<T>& lList, boost::function<bool(T, T)> fn)
{
	if (lList.empty()) return -1;
	std::vector<T> tList = lList;
	getSortedList(tList, fn, true);
	return tList[0];
}
*/

void CvStatbility::doTurn(int iGameTurn)
{
	//int iGameTurn = GC.getGameINLINE().getGameTurn();
	int iPlayer;
	
	for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++)
	{
		if (getTurnsToCollapse(iPlayer) == 0)
		{
			changeTurnsToCollapse(iPlayer, -1);
			completeCollapse(iPlayer);
		}
		else if (getTurnsToCollapse(iPlayer) > 0)
			changeTurnsToCollapse(iPlayer, -1);
		
		if (getCrisisCountdown(iPlayer) > 0)
			changeCrisisCountdown(iPlayer, -1);
	}
	
	if (iGameTurn % CvUtils::getTurns(3) == 0)
	{
		// calculate economic and happiness stability
		for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++)
		{
			updateEconomyTrend(iPlayer);
			updateHappinessTrend(iPlayer);
		}
		// calculate war stability
		for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++)
		{
			for (int iEnemy = 0; iEnemy < NUM_PLAYERS; iEnemy++)
			{
				if (GET_TEAM(iPlayer.getTeam()).isAtWar(iEnemy.getTeam()))
				{
					updateWarTrend(iPlayer, iEnemy);
					m_lLastWarSuccess[iPlayer][iEnemy] = GET_TEAM(
						iPlayer.getTeam()).AI_getWarSuccess(iEnemy.getTeam());
				}
				else
				{
					m_lLastWarSuccess[iPlayer][iEnemy] = 0;
				}
			}
		}
	}
	
	// decay penalties from razing cities and losing to barbarians
	if (iGameTurn % CvUtils::getTurns(5) == 0)
	{
		if (getHumanRazePenalty() < 0)
			changeHumanRazePenalty(2);
		
		for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++)
		{
			if (getBarbarianLosses(iPlayer) > 0)
				changeBarbarianLosses(iPlayer, -1);
		}
	}
	
	if (iGameTurn % CvUtils::getTurns(12) == 0)
	{
		for (iPlayer = 0; iPlayer < NUM_PLAYERS; iPlayer++)
		{
			checkLostCitiesCollapse(iPlayer);
		}
	}
	
	if (iGameTurn >= getTurnForYear(tBirth[CvUtils::getHumanID()])) 
		setHumanStability(calculateStability(CvUtils::getHumanID()));
}

void CvStatbility::endTurn(PlayerTypes eIndex)
{
	std::vector<CvCity*> lSecedingCities;
	getSecedingCities(eIndex, lSecedingCities);
	
	if (lSecedingCities.size())
	{
		secedeCities(eIndex, lSecedingCities);
		setSecedingCities(eIndex, lSecedingCities.clear());
	}
}

void CvStatbility::triggerCollapse(PlayerTypes eIndex)
{
	// help overexpanding AI: collapse to core, unless fall date
	if (CvUtils::getHumanID() != eIndex)
	{
		if (GC.getGameINLINE().getGameTurnYear() < tFall[eIndex])
		{
			std::vector<CvCity*> lCities;
			CvUtils::getOwnedCoreCities(eIndex, lCities);
			if lCities.size() < GET_PLAYER(eIndex).getNumCities())
				collapseToCore(eIndex); return;
		}
	}
	
	// Spread Roman pigs on Celtia's complete collapse
	if (getRomanPigs() < 0 && eIndex == iCeltia) setRomanPigs(1);
	
	scheduleCollapse(eIndex);
}

void CvStatbility::scheduleCollapse(PlayerTypes eIndex)
{
	iTrunsToCollapse[iPlayer] = 1;
	// save collapse file 有文明崩溃时存档
	CvStringBuffer epoch = "BC";
	if (GC.getGameINLINE().getGameTurnYear() > 0) epoch = "AD";
	{
		//
	}
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
	
	if (CvUtils::getHumanID() == iPlayer && iPlayer != iMongolia)
	{
		int iRazePenalty = -10;
		if (city->getHighestPopulation() < 5 && !city->isCapital())
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
void CvStatbility::onChangeWar(bool bWar, int iTeam, int iOtherTeam)
{
	if (iTeam < NUM_PLAYERS && iOtherTeam < NUM_PLAYERS)
	{
		checkStability(iTeam, !bWar);
		checkStability(iOtherTeam, !bWar);
		
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
[
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
	if (iWinningPlayer == iBarbarian && iLosingPlayer < NUM_PLAYERS)
		changeBarbarianLosses(iLosingPlayer, 1);
}

void CvStatbility::onCivSpawn(PlayerTypes iPlayer)
{
	for (int i = 0; i < lOlderNeighbours.size(); i++)
	{
		int iOlderNeighbor = lOlderNeighbours[i];
		if (GET_PLAYER(iOlderNeighbor).isAlive() && 
			getStabilityLevel(iOlderNeighbor) > iStabilityShaky)
			decrementStability(iOlderNeighbor);
	}
}

StabilityLevelTypes CvStatbility::getStabilityLevel(PlayerTypes eIndex)
{
	return m_eStabilityLevel[eIndex];
}

void CvStatbility::setStabilityLevel(PlayerTypes eIndex, StabilityLevelTypes eStabilityLevel)
{
	m_eStabilityLevel[eIndex] = eStabilityLevel;
	
	if (eStabilityLevel == iStabilityCollapsing)
	{
		gDLL->getInterfaceIFace()->addMessage(eIndex, false, iDuration, gDLL-getText("TXT_KEY_STABILITY_COLLAPSING_WARNING"), "", 0, "", ColorTypes(iRed), -1, -1, true, true);
	}
}

void CvStatbility::incrementStability(PlayerTypes eIndex)
{
	setStabilityLevel(eIndex, std::min(iStabilitySolid, getStabilityLevel(eIndex) + 1));
}

void CvStatbility::decrementStability(PlayerTypes eIndex)
{
	setStabilityLevel(eIndex, std::max(iStabilityCollapsing, getStabilityLevel(eIndex) - 1));
}

bool CvStatbility::isImmune(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iGameTurn = GC.getGameINLINE().getGameTurn();
	
	// must not be dead
	if (!pPlayer.isAlive() || pPlayer.getNumCities() == 0)
		return true;
	
	// only for major civs
	if (eIndex >= NUM_PLAYERS)
		return true;
	
	// immune right after scenario start
	if (iGameTurn - getScenarioStartTurn() < CvUtils::getTurns(20)) 
		return true;

	// immune right after birth
	if ((iGameTurn - getTurnForYear(tBirth[eIndex])) < CvUtils::getTurns(20)) 
		return true;

	// immune right after resurrection
	if ((iGameTurn - pPlayer.getLatestRebellionTurn()) < CvUtils::getTurns(10))
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
	for (CvCity* pLoopCity = pPlayer.firstCity(&iLoop); pLoopCity != NULL; pLoopCity = pPlayer.nextCity(&pLoopCity))
		if (pLoopCity.getOriginalOwner() == eIndex)
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
	if (iNumPreviousCities > 2 && (2 * iNumCurrentCities <= iNumPreviousCities))
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
	
	std::vector<CvPlot*> lPlots;
	CvArea::getCoreArea(eIndex, lPlots);
	
	std::vector<CvCity*> lCities;
	CvUtils::getAreaCitiesCiv(eIndex, lPlots, lCities);
	
	// completely pushed out of core: collapse
	if (lCities.size() == 0)
	{
		if ((eIndex == iPhoenicia || eIndex == iKhmer) && !pPlayer.isReborn()))
		{
			pPlayer.setReborn(true); 
		}
		// debugTextPopup
		scheduleCollapse(eIndex);
	}
}

int CvStatbility::determineStabilityLevel(int eCurrentLevel, int iStability, bool bFall)
{
	int iThreshold = 10 * eCurrentLevel - 10;
	
	if (bFall) iThreshold += 10;
	
	if (iStability >= iThreshold) return std::min(iStabilitySolid, eCurrentLevel + 1);
	else if (bFall) return std::max(iStabilityCollapsing, eCurrentLevel - (iThreshold - iStability) / 10);
	else if (iStability < (iThreshold - 10)) return std::max(iStabilityCollapsing, eCurrentLevel - 1);
	
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
	if (GET_TEAM(pPlayer.getTeam()).isAVassal() && !bVassal) return;
	
	if (isImmune(eIndex)) return;
	
	// immune to negative stability checks in golden ages
	if (pPlayer.isGoldenAge()) bPositive = true; 
	
	// immune during anarchy
	if (pPlayer.isAnarchy()) return;
	
	// no repeated stability checks
	if (getLastStabilityTurn(eIndex) == iGameTurn) return;
	
	setLastStabilityTurn(eIndex ,iGameTurn);
	
	// error
	int iStability, 
	int lStabilityTypes[]
	int iStabilityLevel = getStabilityLevel(eIndex);
	bool bHuman = (CvUtils::getHumanID() == eIndex);
	bool bFall = isDecline(eIndex);
	
	int iNewStabilityLevel = determineStabilityLevel(iStabilityLevel, iStability, bFall);
	
	if (iNewStabilityLevel > iStabilityLevel)
		setStabilityLevel(eIndex, iNewStabilityLevel)
	else if (!bPositive)
	{
		if (iNewStabilityLevel == iStabilityCollapsing)
			if (iStability < m_iLastStability[eIndex])
				triggerCollapse(eIndex);
		
		if (iNewStabilityLevel < iStabilityLevel)
			setStabilityLevel(eIndex, iNewStabilityLevel);
	}
	
	// update stability information
	m_iLastStability[eIndex] = iStability;
	for (int i = 0; i < iNumStabilityLevels; i++)
		m_lStabilityCategoryValues[eIndex][i] = lStabilityTypes[i]; // error
	
	for (int i = 0; i < iNumStabilityParameters; i++)
		pPlayer.setStabilityParameter(i, lParameters[i]);
		
	// check vassals
	for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
		if (GET_TEAM(GET_PLAYER(iLoopPlayer).getTeam()).isVassal(GET_PLAYER(eIndex).getTeam()))
			checkStability(iLoopPlayer, bPositive, eIndex);
}

void CvStatbility::getPossibleMinors(PlayerTypes eIndex，std::vector<PlayerTypes>& lCivs)
{
	// 硬编码 : 马里， iEthiopia，刚果
	if (GC.getGameINLINE().countKnownTechNumTeams(iNationalism) == 0 &&
		(eIndex == iMali || eIndex == iEthiopia || eIndex == iCongo) ||
		 VAL_IN(eIndex, lCivBioNewWorld))
	{
		lCivs.append(iNative);	 
		return;
	}
	
	if (GC.getGameINLINE().gerCurrentEra() <= iMedieval)
	{
		lCivs.append(iBarbarian);
		lCivs.append(iIndependent);
		lCivs(iIndependent2);
		return;
	}
	
	lCivs.append(iIndependent);
	lCivs.append(iIndependent2);
	return;
}

void CvStatbility::secession(PlayerTypes eIndex, std::vector<CvCity*>& lCities)
{
	setSecedingCities(eIndex, lCities);
}

void CvStatbility::secedeCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities, bool bRazeMinorCities)
{
	std::vector<PlayerTypes> lPossibleMirrors;
	getPossibleMinors(eIndex, lPossibleMirrors);

	std::map<int, std::vector<CvCity*>> dPossibleResurrections;
	
	bool bComplete = (lCities.size() == GET_PLAYER(eIndex).getNumCities());
	
	CvUtils::clearPlague(eIndex);
	
	// if smaller cities are supposed to be destoryed, do that first
	std::vector<CvCity*> lCededCities;
	std::vector<CvCity*> lRemoveCities;
	std::vector<CvCity*> lRelocatedUnits;
	
	for (int iI = 0; iI < lCities.size(); iI++)
	{
		CvCity* pCity = lCities[iI];
		
		if (bRazeMinorCities)
		{
			bool bMaxPopulation = (pCity->getPopulaiton() < 10);
			bool bMaxCulture = (pCity->getCultureLevel() < 3);
			bool bNoHolyCities = (!pCity->isHolyCity());
			bool bNoCaptials =  (!pCity->isCapital());
			// 硬编码 : 耶路撒冷
			bool bNotJerusalem = (!(pCity->getX() == tJerusalem.first() && pCity->getU() == tJerusalem.second()));
			
			if (bMaxPopulation && bMaxCulture && bNoHolyCities && bNoCaptials && bNotJerusalem)
			{
				CvCity* pClosestCity = GC.getMapINLINE().findcity(pCity->getX(), pCity->getY(), eIndex, -1, true, false, -1, -1, pCity);
			
				if (pClosestCity)
				{
					if (plotDistance(pCity->getX(), pCity->getY(), 
						pClosestCity->getX(), pClosestCity->getY()) < = 2)
					{
						bool bCulture = (pCity->getCultureLevel() <= pClosestCity->getCultureLevel())
						bool bPopulation = (pCity->getPopulaiton() < pClosestCity->getPopulaiton())
						if (bCulture && bPopulation)
						{
							lRemoveCities.append(city);
							continue;
						}
					}
				}
			}
			
			// 硬编码 : 摧毁早期文明城市
			// always raze iHarappa, iNorteChico, iMississippi cities 
			if ((eIndex == iHarappa || 
				 eIndex == iNorteChico || 
				 eIndex == iMississippi) && 
				 CvUtils::getHumanID() != eIndex)
				{
					lRemoveCities.append(pCity);
				}
			
		}
		lCededCities.append(pCity);
	}
	
	for (int iI = 0; iI < lRemoveCities.size(); iI++)
	{
		CvCity* pCity = lRemoveCities[iI];
		CvPlot* plot = pCity->plot();
		GET_PLAYER(iBarbarian).disband(pCity);
		plot->setCulture(eIndex, 0, true);
		// 硬编码 
		if (eIndex == iMississippi || eIndex == iNorteChico)
		{
			if (eIndex == iMississippi)
			{
				if (plot->getImprovementType() >= iCityRuins &&
					!(plot->isPeak() && plot->isWater() && 
					(plot->getTerrainType() == iDesert || 
					 plot->getTerrainType() == iSnow ||
					 plot->getTerrainType() == iMarsh)))
					if (plot->getFeatureType() == -1) plot->setFeatureType(iForest, 0);
				
				if (!(plot->getImprovementType() == iCityRuins ||
					  plot->getImprovementType() == iHut))
					plot->setImprovementType(-1);
					
				if (plot->getImprovementType() == iCityRuins)
					plot->setImprovementType(iHut);
			}
			else
			{
				plot->setImprovementType(-1);
			}
			
			plot->setRouteType(-1);
		}
	}
	
	for (int iI = 0; iI < lCededCities.size(); iI++)
	{
		CvPlot* cityPlot = GC.getMapINLINE().plot(pCity->getX(), pCity->getY());
		int iGameTurnYear = GC.getGameINLINE().getGameTurnYear();
		
		// three possible behaviors: if living civ has a claim, assign it to them
		// claim based on core territory
		int iClaim = -1;
		for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
		{
			if (iLoopPlayer == eIndex) continue;
			if (CvUtils::getHumanID() == eIndex) continue;
			if (iGameTurnYear < tBirth[iLoopPlayer]) continue;
			if (iGameTurnYear > tFall[iLoopPlayer]) continue;
			if (cityPlot->isCore(iLoopPlayer) && GET_PLAYER(iLoopPlayer).isAlive())
			{
				iClaim = iLoopPlayer;
				// debugTextPopup
				break;
			}
		}
		
		// claim based on original owner
		if (iClaim == -1)
		{
			PlayerTypes iOriginalOwner = pCity->getOriginalOwner();
			
			std::vector<CvPlot*> lPlots;
			CvArea::getBirthArea(eIndex, lPlots);
			bool bCityPlot = VAL_IN(cityPlot, lPlots);
			
			if (cityPlot->getSettlerValue(iOriginalOwner) >= HISTORICAL_VALUE &&
				!cityPlot->isCore(eIndex) && 
				!bCityPlot &&
				GET_PLAYER(iOriginalOwner).isAlive() &&
				iOriginalOwner != eIndex &&
				CvUtils::getHumanID() != iOriginalOwner)
			{
				if (iOriginalOwner < NUM_PLAYERS && iGameTurnYear < tFall[iOriginalOwner])
				{
					// cities lost too long age don't return
					// 硬编码: 25
					if (pCity->getGameTurnPlayerLost(iOriginalOwner) >= 
						GC.getGameINLINE().getGameTurn() - CvUtils::getTurns(25))
					{
						iClaim = iOriginalOwner;
						// debugTextPopup
					}
				}
			}
		}
		
		// claim based on culture
		if (iClaim == -1)
		{
			for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
			{
				if (iLoopPlayer == eIndex) return;
				if (CvUtils::getHumanID() == iLoopPlayer) continue;
				if (iGameTurnYear < tBirth[iLoopPlayer]) continue;
				if (iGameTurnYear > tFall[iLoopPlayer]) continue;
				if (GET_PLAYER(iLoopPlayer).isAlive())
				{
					int iTotalCulture = cityPlot->countTotalCulture();
					if (iTotalCulture > 0)
					{
						int iCulturePercent = 100 * cityPlot->getCulture(iLoopPlayer) / cityPlot->countTotalCulture();
						if (iCulturePercent >= 75)
						{
							iClaim = iLoopPlayer;
							// debugTextPopup
						}
					}
				}
			}
		}
		
		// claim based on target (needs to be winning the war based on war success)
		if (iClaim == -1)
		{
			CvTeam& tPlayer = GET_TEAM(GET_PLAYER(eIndex).getTeam());
			for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++) 
			{
				CvPlayer& pLoopPlayer = GET_PLAYER(iLoopPlayer);
				if (pLoopPlayer.isAlive() && 
					tPlayer.isAtWar(pLoopPlayer.getTeam()) &&
					CvUtils::getHumanID() != iLoopPlayer &&
					iGameTurnYear < tFall[iLoopPlayer])
				{
					if (pLoopPlayer.getWarValue(pCity->getX(), pCity->getY()) >= 8 &&
						GET_TEAM(pLoopPlayer.getTeam()).AI_getWarSuccess(tPlayer.getID()) > tPlayer.AI_getWarSuccess(pLoopPlayer.getTeam()))
						// anthoer enemy with closer city: don't claim the city
					{
						CvCity* pClosestCity = GC.getMapINLINE().findCity(pCity->getX(), pCity->getY(), NO_PLAYER, NO_TEAM, true,
						false, NO_TEAM, NO_DIRECTION, pCity);
						if (pClosestCity->getOwner() != iLoopPlayer &&
							tPlayer.isAtWar(GET_PLAYER(pClosestCity->getOnwer()).getTeam()))
							continue;
						iClaim = iLoopPlayer; 
						// debugTextPopup
					}
				}		
			}
		}
		
		if (iClaim != -1)
		{
			secedeCity(pCity, iClaim, (eIndex < NUM_PLAYERS && !bComplete));
			continue;
		}
		
		// if part of the core / resurrection area of a dead civ -> possible
		bool bResurrenctionFound = false;
		for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
		{
			if (iLoopPlayer == eIndex) return;
			if (GET_PLAYER(iLoopPlayer).isAlive()) continue;
			if (!m_bSpawned[iLoopPlayer]) continue;
			if (GC.getGameINLINE().getGameTurn() - m_iLastTurnAlive[iLoopPlayer] < CvUtils::getTurns(20)) continue;
			
			// Leoreth: Egyptian respawn on Arabian collapse hurts Ottoman expansion 硬编码
			if (eIndex == iArabia && (iLoopPlayer == iEgypt || iLoopPlayer == iMamluks)) continue;
			
			std::vector<CvPlot*> lCityPlot;
			CvArea::getRespawnArea(iLoopPlayer, lCityPlot);
			if (VAL_IN(cityPlot, lCityPlot))
			{
				bool bPossible = false;
				
				for (int i = 0; i < tResurrectionIntervals[iLoopPlayer].size(); i++)
				{
					std::pair<int, int> tInterval = tResurrectionIntervals[iLoopPlayer];
					int iStart = tInterval.first();
					int iEnd = tInterval.second();
					if (iStart < GC.getGameINLINE().getGameTurnYear() <= iEnd)
					{
						bPossible = true;
						break;
					}
				}
				
				// make respawns on collapse more likely
				if (tBirth[iLoopPlayer] <= GC.getGameINLINE().getGameTurnYera() <= tFall[iLoopPlayer])
					bPossible = true;
				
				if (bPossible)
				{
					if (VAL_IN(iLoopPlayer, dPossibleResurrections))
					{
						dPossibleResurrections[iLoopPlayer].append(pCity);
					}
					else
					{
						dPossibleResurrections[iLoopPlayer].clear();
						dPossibleResurrections[iLoopPlayer].append(pCity);
					}
					bResurrenctionFound = true;
					// debugTextPopup
				}
			}
		}
		
		if (bResurrenctionFound) continue;
		
		// assign randomly to possible minors
		secedeCity(pCity, lPossibleMirrors[pCity.getID() %lPossibleMirrors.size()],
			eIndex < NUM_PLAYERS && !bComplete);
	}
	
	// notify for partial secessions
	if (!bComplete)
	{
		if (GET_PLAYER(CvUtils::getHumanID()).canContact(eIndex))
			// addMessage
	}
	
	// collect additional cities that can be part of the resurrection
	std::map<int, std::vector<CvCity*>::iterator it;
	for (it = dPossibleResurrections.begin(); it != dPossibleResurrections.end(); ++it)
	{
		int iResurrrectionPlayer = it.first();
		
		std::vector<CvCity*> lCity;
		getResurrectionCities(iResurrrectionPlayer, lCity, true);
		for (int i = 0; i < lCity.size(); i++）
		{
			CvCity* city = lCity[i];
			if (!VAL_IN(city, lCededCities))
				dPossibleResurrections[iResurrrectionPlayer].append(city);
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
	
	CvUtils::completeCityFlip(city->getX(), city->getY(), iNewOwner, city->getOnwer(), 50, false, true, true);
	
	CvUtils::flipOrCreateDefenders(iNewOwner, lFlippedUnits, city->getX(), city->getY(), iNumDefenders);
	
	if (city->getOnwer() == CvUtils::getHumanID())
	{
		if (iNewOwner == iIndependent || iNewOwner == iIndependent2 ||
			iNewOwner == iNative || iNewOwner == iBarbarian)
			// addMessage
		else
			// addMessage
	}
	
	if (CvUtils::getHumanID == iNewOwner)
		// addMessage
	
}

void CvStatbility::completeCollapse(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	std::vector<CvCity*> lCities; 
	pPlayer.getCityList(lCities);
	
	// help lategame ai not collapse so regularly
	if (CvUtils::getHumanID() != eIndex)
	{	
		if (GET_TEAM(pPlayer.getTeam()).isHasTech(iNationalism))
		{
			if (GC.getGameINLINE().getGameTurnYear() < tFall[eIndex])
			{
				std::vector<CvCity*> lOwnedCoreCities;
				CvUtils::getOwnedCoreCities(eIndex, lOwnedCoreCities);
				if (lOwnedCoreCities.size() > 0 && lOwnedCoreCities.size() < lCities.size())
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
	
	// secede all cities, destory close and less important ones
	bool bRazeMinorCities = (pPlayer.getCurrentEra() <= iMedieval);
	secedeCities(eIndex, lCities, bRazeMinorCities);
	
	// take care of the remants of the civ
	pPlayer.killUnits();
	CvUtils::resetUHV(eIndex);
	m_iLastTurnAlive[eIndex] = GC.getGameINLINE().getGameTurn();
	
	// 拜占庭硬编码
	// special case: remove Christians in the Turkish core
	if (eIndex == iByzantium)
		CvUtils::removeReligionByArea(CvArea::getCoreArea(iOttomans), iOrthodoxy);
	
	// 中国硬编码
	// Chines collapse: Mongolia's core moves south
	if (eIndex == iChina)
		GET_PLAYER(iMongolia).setReborn(true);
	
	// debugTextPopup
	
	// addMessage
	CvWString szText = gDLL->getText("TXT_KEY_STABILITY_COMPLETE_COLLAPSE", pPlayer.getCivilizationAdjective());
	gDLL->getInterfaceIFace()->addMessage(CvUtils::getHumanID(), false, iDuration, szText, "", 0, "", ColorTypes(iWhite), -1, -1, true, true);
}

void CvStatbility::collapseToCore(PlayerTypes eIndex)
{
	std::vector<CvCity*> lAhistoricalCities;
	std::vector<CvCity*> lNonCoreCities;
	
	// vic.onCollapse(eIndex, false);
	
	// Spread Roman pigs on Celtia's complete collapse
	if (getRomanPigs() < 0 && eIndex == iCeltia)
		setRomanPigs(1);
	
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iLoop = 0;
	for (CvCity* city = pPlayer.firstCity(&iLoop); city != NULL; city = pPlayer.nextCity(&iLoop))
	{
		CvPlot* plot = city->plot();
		if (!plot->isCore(eIndex))
		{
			lNonCoreCities.append(city);
			if (plot->getSettlerValue(eIndex) < HISTORICAL_VALUE)
				lAhistoricalCities.append(city);
		}
	}
	
	// more than half ahistorical, only secede ahistorical cities
	if (2 * lAhistoricalCities.size() > lNonCoreCities().size())
	{
		// notify owner
		if (CvUtils::getHumanID() == eIndex)
		{
			// addMessage
		}
		
		// secede all foreign cities
		secession(eIndex, lAhistoricalCities);
	}
	else if (lNonCoreCities.size())
	{
		// notify owner
		if (CvUtils::getHumanID() == eIndex)
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
		if (plot->getOnwer() == eIndex)
		{
			int iImprovement = plot->getImprovementType();
			int iRoute = plot->getRouteType();
			
			if (iImprovement == iTown) plot->setImprovementType(iHamlet);
			else if (iImprovement == iVillage) plot->setImprovementType(iCottage);
			else if (iImprovement == iHamlet) plot->setImprovementType(iCottage);
			else if (iImprovement == iCottage) plot->setImprovementType(-1);
			
			// Destory all Harappan improments and routes 
			// 硬编码 : 删除早期文明的痕迹
			if ((eIndex == iCeltia || 
				eIndex == iHarappa || 
				eIndex == iNorteChico || 
				eIndex == iMississippi) && 
				CvUtils::getHumanID() != eIndex)
			{
				if (iImprovement >= 0)
					plot->setImprovementType(-1);
				if (iRoute >= 0)
					plot->setRouteType(-1);
			}
		}			
	}
	
	if (CvUtils::getHumanID() == eIndex)
		// addMessage
}

void CvStatbility::calculateStability(PlayerTypes eIndex)
{
	int iGameTurn = GC.getGameINLINE().getGameTurn();
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	CvTeam& tPlayer = GET_TEAM(pPlayer.getTeam());
	
	int iExpansionStability = 0;
	int iEconomyStatility = 0;
	int iDomesticStability = 0;
	int iForeignStability = 0;
	int iMilitaryStability = 0;
	
	std::vector<int> lParameters(iNumStabilityParameters, 0);
	
	// Collect required data
	int iReborn = pPlayer.getReborn();
	int iStateReligion = pPlayer.getStateReligion();
	int iCurrentEra = pPlayer.getCurrentEra();
	int iTotalPopualtion = pPlayer.getTotalPopulation();
	int iPlayerScore = pPlayer.getScoreHistory();
	
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
	
	int iStartReligionPopulation = 0;
	int iOnlyStateReligionPopulation = 0;
	int iDifferentReligionPopulaiton = 0;
	int iNoReligionPopulation = 0;
	
	bool bTotalitarianism = (iCivicSociety == iTotalitarianism);
	bool bFreeEnterprise = (iCivicEconomy == iFreeEnterprise);
	bool bPublicWelfare = (iCivicEconomy == iPublicWelfare);
	bool bTheocracy = (iCivicReligion == iTheocracy);
	bool bTolerance = (iCivicReligion == iTolerance);
	bool bConquest = (iCivicTerritory == iConquest);
	bool bTributaries = (iCivicTerritory == iTributaries);
	bool bIsolationism = (iCivicTerritory == iIsolatonism);
	bool bColonialism = (iCivicTerritory == iColonialism);
	bool bNationhood = (iCivicTerritory ==  iNationhood);
	bool bMultilateralism = (iCivicTerritory == iMultilateralism);
	
	bool bSingleCoreCity = false;
	bool bUnion = false;
	
	// 波兰立陶宛
	CvPlayer& pPoland = GET_PLAYER(iPoland);
	CvPlayer& pLithuania = GET_PLAYER(iLithuania);
	CvTeam& teamLithuania = GET_TEAM(pLithuania.getTeam());
	CvTeam& teamPoland = GET_TEAM(pPoland.getTeam());
	
	if (eIndex == iLithuania && 
		pPoland.isAlive() && 
		( teamPoland.isDefensivePact(teamLithuania.getID()) ||
		  teamPoland.isVassal(teamLithuania.getID())) )
	{
		bSingleCoreCity = false;
		bUnion = true;
	}
	else if (eIndex == iPoland &&
		pLithuania.isAlive() &&
		( teamLithuania.isDefensivePact(teamPoland.getID()) ||
		  teamLithuania.isVassal(teamPoland.getID()) )
	{
		bSingleCoreCity = false;
		bUnion = true;
	}
	
	// 奥匈联邦
	CvPlayer& pHolyRome = GET_PLAYER(iHolyRome);
	CvPlayer& pHungary = GET_PLAYER(iHungary);
	CvTeam& teamHolyRome = GET_TEAM(pHoleRome.getTeam());
	CvTeam& teamHungary = GET_TEAM(pHungary.getTeam());
	
	if (iPlayer == iHolyRome &&
		pHoleRome.isReborn() &&
		pHungary.isAlive() &&
		( teamHungary.isDefensivePact(teamHolyRome.getID()) ||
		  teamHungary.isVassal(teamHungary.getID()))
	{
		bSingleCoreCity = false;
		bUnion = true;
	}
	else if (iPlayer == iHungary &&
			 pHoleRome.isAlive() &&
			 ( teamHolyRome.isDefensivePact(teamHungary.getID()) ||
			   teamHolyRome.isVassal(teamHungary.getID()))
	{
		bSingleCoreCity = false;
		bUnion = true;
	}	
		
	bSingleCoreCity = (CvUtils::getOwnedCoreCities(eIndex).size() == 1);
	
	int iCorePopulationModifier = getCorePopulationModifier(iCurrentEra);
	
	// 联邦
	if (bUnion)
	{
		if (eIndex == iLithuania) iCorePopulation += getUnionPop(iPoland, iCorePopulationModifier);
		else if (eIndex == iPoland) iCorePopulation += getUnionPop(iLithuania, iCorePopulationModifier);
		else if (eIndex == iHolyRome) iCorePopulation += getUnionPop(iHungary, iCorePopulationModifier);
		else if (eIndex == iHungary) iCorePopulation += getUnionPop(iHolyRome, iCorePopulationModifier);
	}
	
	int iMostPopularReligion = -1;
	int iMostPopularReligionPopulation = 0;
	
	for (int iI = 0; iI < GC.getNumReligionInfos(); iI++)
	{
		if (pPlayer.getReligionPopulation(iI) > iMostPopularReligionPopulation)
		{
			iMostPopularReligion = iI;
			iMostPopularReligionPopulation = pPlayer.getReligionPopulation(iI);
		}
	}
	
	// 立陶宛UP
	bool bLithuaniaUP = (eIndex == iLithuania &&
		pLithuania.isStateReligion() &&
		pLithuania.getStateReligion() == -1)
		
	int iLoop = 0;
	for (CvCity* pCity = GET_PLAYER(eIndex).firstCity(&iLoop); 
		pCity != NULL; pCity = GET_PLAYER(eIndex).nextCity(&iLoop))
	{
		int iPopulation = pCity->getPopulaiton();
		int iModifier = 0;
		CvPlot* plot = pCity->plot();
		
		bHistorical = (plot->getSettlerValue(eIndex) >= HISTORICAL_VALUE);
		
		int iTotalCulture = 0;
		
		// Expansion
		if (plot->isCore(eIndex))
		{
			int iStabilityPopulation = iCorePopulationModifier * iPopulation / 100;
			if (bSingleCoreCity && iCurrentEra > iAncient)
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
				int iTempCulture = plot->getCulture(iLoopPlayer);
				if (plot->isCore(iLoopPlayer))
					iTempCulture *= 2;
				iTotalCulture += iTempCulture;
			}
			
			if (iTotalCulture)
				iCulturePercent = 100 * iOwnCulture / iTotalCulture;
			else
				iCulturePercent = 100;
			
			// iMongolia 蒙古
			bool bExpansionExceptions = ((bHistorical && eIndex == iMongolia) || bTotalitarianism)
			
			// ahistorical tiles
			if (!bHistorical) iModifier += 2;
			
			// colonies with Totalitarianism
			if (pCity->isColony() && bHistorical && bTotalitarianism) iModifier += 1;
			
			// 硬编码 : 25
			// not original owner
			if (!bExpansionExceptions)
				if (pCity->getOriginalOwner() != eIndex &&
					iGameTurn - pCity->getGameTurnAcquired() < 25)
					iModifier += 1;
			
			// 波斯UP
			// not majority culture (includes foreign core and Persian UP
			if (eIndex == iPersia || GET_PLAYER(iPersia).isReborn())
			{
				if (iCulturePercent < 50) iModifier += 1;
				if (iCulturePercent < 20) iModifier += 1;
			}
			
			// Courthouse : 法庭 - 建筑效果
			if (pCity->isHasBuilding(getUniqueBuilding(eIndex, iCourthouse)))
				iModifier -= 1;
			
			// Jail : 监狱 - 建筑效果
			if (pCity->isHasBuilding(getUniqueBuilding(eIndex, iJail)))
				iModifier -= 1;
			
			// 葡萄牙UP
			// Portuguese UP : reduced instability from overseas colonies
			if (pCity->isColony())
			{
				if (eIndex == iPortugal) iModifier -= 2;
				if (bColonialism && bHistorical) iModifier -= 1;
			}
			
			// cap
			if (iModifier < -1) iModifier = -1;
			
			iStabilityPopulation = (100 + iModifier * 50) * iPopulation / 100;
			
			iPeripheryPopulation += iStabilityPopulation;
			pCity->setStabilityPopulation(-iStabilityPopulation);
		}
		
		// 硬编码 : 20
		// Recent conquests
		if (bHistorical && (iGameTurn - pCity->getGameTurnAcquired() < CvUtils::getTurns(20)))
		{
			if (pCity->getPreviousOwner() < 0) iRecentlyFounded += 1;
			else iRecentlyConquered += 1;
		}
		
		// Religions
		if (pCity->getReligionCount() == 0)
			iNoReligionPopulation += iPopulation
		else
		{
			bool bNonStateReligion = false;
			for (int iReligion = 0; iReligion < GC.getNumReligionInfos(); iReligion++)
			{
				if (iReligion != iStateReligion && pCity->isHasReligion(iReligion))
				{
					if (!(iMostPopularReligion == iReligion && bLithuaniaUP) &&
						!isTolerated(eIndex, iReligion) && 
						!GC.getReligionInfo(iReligion).isLocal())
					{
						bNonStateReligion = true;
						break;
					}	
				}
				
				if (iStateReligion >= 0 && pCity->isHasReligion(iStateReligion))
				{
					iStabilityPopulation += iPopulation;
					if (!bNonStateReligion) iOnlyStateReligionPopulation += iPopulation;
				}
				
				if (bNonStateReligion)
				{
					if (iStateReligion >= 0 && pCity->isHasReligion(iStateReligion))
						iDifferentReligionPopulaiton += iPopulation / 2;
					else
						iDifferentReligionPopulaiton += iPopulation;
				}
			}
		}
	}
	
	int iPopulationImprovements = 0;
	
	std::vector<CvPlot*> lPlot;
	CvArea::getCoreArea(eIndex, lPlot);
	for (int i = 0; i < lPlot.size(); i++)
	{
		CvPlot* plot = lPlot[i];
		if (plot->getOwner() == eIndex && plot->getWorkingCity())
			if (plot->getImprovementType() == iVillage ||
				plot->getImprovementType() == iTown)
				iPopulationImprovements += 1;
	}	
	
	iCorePopulation += iCorePopulationModifier * iPopulationImprovements / 100;
	
	int iCurrentPower = pPlayer.getPower();
	int iPreviousPower = pPlayer.getPowerHistory(iGameTurn - CvUtils::getTurns(10));
	
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
		iCorePeripheryStability -= int(25 * sigmoid(1.0 * iPeripheryExcess / 100));
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
	// Persian UP 波斯UP
	if (eIndex == iPersia && !GET_PLAYER(iPersia).isReborn()) iConquestModifier += 1;
	
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
	
	if (bIsolationism && iPeripheryPopulation <= 10) iIsolatonismStability = 10;

	lParameters[iParameterIsolationism] = iIsolatonismStability;
	
	iExpansionStability += iIsolatonismStability;
	
	// ECONOMY
	iEconomyStatility = 0;
	
	// Economic Grwoth
	int iEconomicGrowthModifer = 3;
	if (bFreeEnterprise) iEconomicGrowthModifer = 4;
	
	int iEconomicGrowthStability = iEconomicGrowthModifer * calculateTrendScore(getEconomyTrend(eIndex));
	if (iEconomicGrowthStability < 0 && bPublicWelfare) iEconomicGrowthModifer /= 2;

	lParameters[iParameterEconomicGrowth] = iEconomicGrowthStability;
	iEconomyStatility += iEconomicGrowthStability;
	
	int iTradeStability = 0;

	lParameters[iParameterTrade] = iTradeStability;
	iEconomyStatility += iTradeStability;
	
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
	std::vector<int> civics = { iCivicGovernment, iCivicLegitimacy, iCivicEconomy, iCivicReligion, iCivicTerritory };
	int iCivicCombinationStability = getCivicStability(eIndex, civics);
	
	if (CvUtils::getHumanID() != eIndex && iCivicCombinationStability < 0)
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
		
	}
	// to do : ...
	
	// Religion
	int iReligionStability = 0;
	
	if (iTotalPopualtion > 0)
	{
		// to do : ...
	}
}
// 制度稳定
int CvStatbility::getCivicStability(PlayerTypes eIndex, std::vector<int> &lCivics)
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
		if (civics.contains(iSecularims)) iStability += 2;
		if (civics.any(std::vector<int>(iTolerance, iMonasticism)) iStability -= 3;
	}
	
	if (civic.contains(iCentralPlanning))
	{
		if (civics.contains(iEgalitarianism)) iStability += 2;
		if (civics.contains(iStateParty)) iStability += 2;
		if (civics.contains(iCentralism)) iStability += 2;
	}
	
	if (civics.contains(iEgalitarianism))
	{
		if (civics.contains(iDemocracy)) iStability += 2;
		if (civics.contains(iConstitution)) iStability += 2;
		if (civics.no(iSecularims) && civics.no(iTolerance)) iStability -= 3;
	}
	
	if ((civics.contains(iIndividualism))
	{
		if (civics.any(std::vector<int>(iRepulic, iDemocracy))) iStability += 2;
		if (civics.contains(iFreeEnterprise)) iStability += 3;
		if (civics.contains(iCentralPlanning)) iStability -= 5;
		if (civics.any(std::vector<int>(iRegulatedTrade, iPublicWelfare))) iStability -= 2;
		if (civics.contains(iTolerance)) iStability += 2;
	}
	
	if (civics.contains(iTheocracy))
		if (civics.any(std::vector<int>(iIndividualism, iEgalitarianism))) iStability -= 3;
	
	if (civics.contains(iDeification))
	{
		if (civics.any(std::vector<int>(iRepulic, iDemocracy))) iStability -=3;
		
		if (iCurrentEra <= iClassical)
		{
			if (civics.contains(iRedistribution)) iStability +=2;
			if (civics.contains(iSlavery)) iStability += 2;
		}
	}
	
	if (civics.contains(iVassalage))
	{
		if (civics.any(std::vector<int>(iIndividualism, iEgalitarianism))) iStability -= 5;
		if (civics.any(std::vector<int>(iFreeEnterprise, iCentralPlanning, iPublicWelfare))) iStability -= 3;
		if (civics.contains(iTributaries)) iStability += 5;
		
		if (iCurrentEra == iMedieval)
		{
			if (civics.contains(iMonarchy)) iStability += 2;
			if (civics.contains(iManorialism)) iStability += 3;
		}
	}
	
	if (civics.contains(iRepulic))
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
		if (civics.contains(iSecularims)) iStability -= 3;
	}

	if (civics.contains(iMultilateralism))
	{
		if (civics.contains(iDespotism)) iStability -= 3;
		if (civics.contains(iTotalitarianism)) iStability -= 3;
		if (civics.contains(iEgalitarianism)) iStability += 2;
		if (civics.contains(iTheocracy)) iStability -= 3;
	}
	
	if (civics.contains(iMonarchy))
		if (civics.any(std::vector<int>(iClergy, iMonasticism))) iStability += 2;
	
	if (civics.contains(iElective))
		if (civics.contains(iCentralism)) iStability -= 5;
	
	if (civics.contains(iConstitution))
		if (civics.contains(iDemocracy)) iStability += 2;
	
	if (civics.contains(iRevolutionism))
		if (civics.no(iSecularims) && civics.no(iTolerance)) iStability -= 3;
	
	if (civics.contains(iRegulatedTrade))
	{
		if (civics.contains(iManorialism)) iStability += 2;
		if (civics.contains(iMeritocracy)) iStability += 3;
	}
		
	if (civics.contains(iIsolatonism))
	{
		if (civics.any(std::vector<int>(iMerchantTrade, iFreeEnterprise))) iStability -= 4;
		if (civics.any(std::vector<int>(iRegulatedTrade, iCentralPlanning))) iStability += 3;
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

double sigmoid(double x)
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

int CvStatbility::calculateTrendScore(std::vector<int>& lTrend)
{
	int iPositive = 0;
	int iNeutral = 0;
	int iNegative = 0;
	
	for (int iEntry = 0; iEntry < lTrend.size(); iEntry++)
	{
		if (iEntry > 0) iPositive += 1;
		else if (iEntry < 0) iNegative += 1；
		else iNeutral += 1;
	}
	
	if (iPositive > iNegative) return std::max(0, iPositive - iNegative - iNeutral / 2);
	
	if (iNegative > iPositive) return std::min(0, iPositive - iNegative + iNeutral / 2);
	
	return 0;
}

int CvStatbility::calculateSumScore(std::vector<int>& lScores, int iThreshold)
{
	std::vector<int> lThresholdScores;
	for (int iScore = 0; iScore < lScores.size(); iScore++)
	{
		if (std::abs(iScore) >= iThreshold)
			lThresholdScores.append(sign(iScore));
	}
	
	int iSum = 0;
	for  (int i = 0; i < lThresholdScores.size(); i++)
		iSum += lThresholdScores[i];
	
	int iCap = lScores.size() / 2;
	
	return iSum;
}

void CvStatbility::updateEconomyTrend(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	
	if (!pPlayer.isAlive()) return;
	
	int iPreviousCommerce = m_iPreviousCommerce[eIndex];
	int iCurrentCommerce = pPlayer.calculateTotalCommerce();
	
	if (iPreviousCommerce == 0)
	{
		iPreviousCommerce[eIndex] = iCurrentCommerce;
		return;
	}
	
	int iCivicEconomy = pPlayer.getCivics(3);
	
	// 硬编码
	int iPositiveThreshold = 5;
	int iNegativeThreshold = 0;
	
	if (isDecline(eIndex)) iNegativeThreshold = 2;
	
	if (iCivicEconomy == iCentralPlanning) iNegativeThreshold = 0;
	
	int iPercentChange = 100 * iCurrentCommerce / iPreviousCommerce - 100;
	// error : pushEconomyTrend(PlayerTypes eIndex, int iCurrentTrend);
	if (iPercentChange > iPositiveThreshold) pushEconomyTrend(eIndex, 1);
	else if (iPercentChange < iNegativeThreshold) pushEconomyTrend(eIndex, -1);
	else pushEconomyTrend(eIndex, 0);
	
	m_iPreviousCommerce[eIndex] = iCurrentCommerce;
}

void CvStatbility::updateHappinessTrend(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	
	if (!pPlayer.isAlive()) return;
	
	int iNumCities = pPlayer.getNumCities();
	
	if (iNumCities == 0) return;
	
	int iHappyCities = 0
	int iUnhappyCities = 0;
	
	int iAveragePopulation = pPlayer.getAveragePopulation();
	
	int iLoop = 0;
	for (CvCity* city = pPlayer.firstCity(&iLoop); city != NULL; city = pPlayer.nextCity(&iLoop))
	{
		int iPopulation = city->getPopulaiton();
		int iHappiness = city->happyLevel();
		int iUnhappiness = city->unhappyLevel(0);
		int iOvercrowding = city->getOvercrowdingPercentAnger(0) * city->getPopulaiton();
		// 硬编码
		if (city->isWeLoveTheKingDay() || 
			(iPopulation >= iAveragePopulation && 
			 iHappiness - iUnhappiness >= iAveragePopulation / 4))
			iHappyCities += 1;
		else if (iUnhappiness - iOvercrowding > iPopulation / 5 ||
				 iUnhappiness - iHappiness > 0)
			iUnhappiness += 1;
	}
	
	int iCurrentTrend = 0;
	
	if (iHappyCities - iUnhappyCities > std::ceil(iNumCities / 5.0)) iCurrentTrend = 1;
	else if (iUnhappyCities - iHappiness > std::ceil(iNumCities / 5.0)) iCurrentTrend = -1;
	
	// error : pushHappinessTrend(PlayerTypes eIndex, int iCurrentTrend);
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
	
	// error : pushWarThend(PlayerTypes iEnemy, int iCurrentTrend);
	pushWarThend(iEnemy, iCurrentTrend);
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
	std::vector<pair<int, int>> lHistory;
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iCurrentTurn = GC.getGameINLINE().getGameTurn();
	
	int start = iCurrentTurn - iNumTurns;
	int end = iCurrentTurn;
	for (int i = start; i < end; i++)
	{
		int iHistory = pPlayer.getEconomyHistory(iTurn);
		if (iHistory > 1)
			lHistory.append(std::make_pair(iTurn - iCurrentTurn + iNumTurns, iHistory));
	}
	
	lHistory.append(std::make_pair(iNumTurns, pPlayer.calculateTotalCommerce()));
	
	// error : CvUtils::linreg(std::vector<pair<int, int>>& lHistory, int &a, int &b);
	int a, b;
	CvUtils::linreg(lHistory, a, b);
	
	double iNormalizedStartTurn = b;
	double iNormalizedCurrentTurn = a * iNumTurns + b;

	if (ZERO(iNormalizedStartTurn)) return 0;
	
	int iGrowth = int(100 * (iNormalizedCurrentTurn - iNormalizedStartTurn) / iNormalizedStartTurn);
	
	return iGrowth;
}

int CvStatbility::calculateEconomicGrowthNeighbors(PlayerTypes eIndex, int iNumTurns)
{
	std::vector<pair<int, int>> lHistory;
	std::vector<int> lContacts;
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int iCurrentTurn = GC.getGameINLINE().getGameTurn();
	
	for (int iLoopPlayer = 0; iLoopPlayer < NUM_PLAYERS; iLoopPlayer++)
		if (pPlayer.canContact(iLoopPlayer)) lContacts.append(iLoopPlayer);
	
	int start = iCurrentTurn - iNumTurns;
	int end = iCurrentTurn;
	for (int i = start; i < end; i++)
	{
		int iHistory = pPlayer.getEconomyHistory(iTurn);
		for (int iLoopPlayer = 0; iLoopPlayer < lContacts.size(); iLoopPlayer++)
			iHistory += GET_PLAYER(lContacts[iLoopPlayer]).getEconomyHistory(iTurn);
		if (iHistory > 1)
			lHistory.append(std::make_pair(iTurn - iCurrentTurn + iNumTurns, iHistory));
	}
	
	int iHistory = pPlayer.calculateTotalCommerce();
	for (int iLoopPlayer = 0; iLoopPlayer < lContacts.size(); iLoopPlayer++)
		iHistory += GET_PLAYER(lContacts[iLoopPlayer]).calculateTotalCommerce();
	
	double a, b;
	CvUtils::linreg(lHistory, a, b);
	
	double iNormalizedStartTurn = b;
	double iNormalizedCurrentTurn = a * iNumTurns + b;
	
	int iGrowth = int(100 * (iNormalizedCurrentTurn = iNormalizedStartTurn) / iNormalizedStartTurn);
	
	return iGrowth;
}

// error
int determinCrisisType(std::vector<int>& lStabilityTypes)
{
	int iLowestEntry = CvUtils::getHighestEntry(lStabilityTypes, 
}

void calculatePowerRank(PlayerTypes eIndex, int iTurn)
{
	std::vector<int> lPowerValues;
	
	bool fn(int i, int j) { return (GET_PLAYER(i).getPowerHistory(iTurn) < GET_PLAYER(j).getPowerHistory(iTurn)); }
	
	CvUtils::getSortedList<int>(lPowerValues, fn, true);
	
	return index<int>(lPowerValues, eIndex);
}

template<typename T>
int index(std::vector<T>& lList, T val)
{
	std::vecotr<T>::const_iterator it;
	for (it = lList.begin(); it != lList.end(); ++it)
		if (*it == val) 
			return (it - lList.begin());
	return -1;
}
	
void calculateRankedAttiudes(PlayerTypes eIndex, std::vector<int>& lContacts)
{
	lContacts.append(eIndex);
	// error
	int iPlayerIndex = 
	// to do : ...
}

// AI态度
int CvStatbility::calculateAttitude(PlayerTypes iFromPlayer, PlayerTypes iToPlayer)
{
	CvPlayer& pPlayer = GET_PLAYER(iFromPlayer);
	
	int iAttitude = pPlayer.AI_getAttitudeVal(iToPlayer);
	iAttitude -= pPlayer.AI_getSameReligionAttitude(iToPlayer);
	iAttitude -= pPlayer.AI_getDifferentReligionAttitude(iToPlayer);
	iAttitude -= pPlayer.AI_getFirstImpressionAttitude(iToPlayer);
	
	return iAttitude;
}
// 宗教容忍
bool CvStatbility::isTolerated(PlayerTypes eIndex, ReligionTypes iReligion)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	ReligionTypes iStateReligion = pPlayer.getStateReligion();
	
	// should not be asked, but still check
	if (iStateReligion == iReligion) return true;
	
	// civics
	if (pPlayer.getCivics(4) == iTolerance || pPlayer.getCivics(4) == iSecularism) return true;
	
	// Exceptions
	// 儒学和道教
	if (iStateReligion == iConfucianism && iReligion == iTaoism) return true;
	if (iStateReligion == iTaoism && iReligion == iConfucianism) return true;
	// 印度教和佛教
	if (iStateReligion == iHinduism && iReligion == iBuddhism) return true;
	if (iStateReligion == iBuddhism &7 iReligion == iHinduism) return true;
	
	// Poland 波兰
	std::vector<ReligionTypes> lChristianity = { iOrthodoxy, iCatholicism, iProtestantism };
	if (eIndex == iPoland && 
		VAL_IN(iStateReligion, lChristianity) && 
		VAL_IN(iReligion, lChristianity))
		return true;
		
	return false;
}

void checkResurrection()
{
	// error : m_iCivWithNationalism
	int iNationalismModifier = std::min(20, 4 * m_iCivWithNationalism);
	
	std::vector<int> lPossibleResurrections;
	bool bDeadCivFound = false;
	
	// iterate all civs starting with a random civ
	for (int iLoopCiv = 0; iLoopCiv < NUM_PLAYERS; iLoopCiv++)
		if (CvUtils::canRespawn(iLoopCiv))
			lPossibleResurrections.append(iLoopCiv);
		
	// higher respawn chance for civs whose entrie core is controlled by minor civs
	
	// to do : ...
}

void getResurrectionCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities, bool bFromCollapse = false)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	int teamPlayer = pPlayer.getTeam();
	std::vector<CvCity*> lPotentialCities;
	std::vector<CvCity*> lFlippingCities;
	
	CvPlot* tCapital = CvArea::getRespawnArea(eIndex);
	// to do : ...
}

void CvStatbility::resurrectionFromCollapse(PlayerTypes eIndex, std::vector<CvCity*>& lCityList)
{
	if (!lCityList.empty()) doResurrection(eIndex, lCityList);
}

void CvStatbility::doResurrection(PlayerTypes eIndex, std::vector<CvCity*>& lCityList, bool AskFilp)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	CvTeam& teamPlayer = GET_TEAM(pPlayer.getTeam());
	
	pPlayer.setAlive(true);
	
	m_iRebelCiv = eIndex;
	
	for (int iOtherCiv = 0; iOtherCiv < NUM_PLAYERS; iOtherCiv++)
	{
		CvPlayer& pOtherCiv = GET_PLAYER(iOtherCiv)
		CvTeam& tOtherCiv = GET_TEAM(pOtherCiv.getTeam())
		
		if (eIndex == iOtherCiv) continue;
			
		teamPlayer.makePeace(pOtherCiv.getTeam());
		
		if (teamPlayer.isVassal(pOtherCiv.getTeam()))
			tOtherCiv.freeVassal(pPlayer.getTeam());
		
		if (tOtherCiv.isVassal(pPlayer.getTeam()))
			teamPlayer.freeVassal(pOtherCiv.getTeam());
	}
	
	setNumPreviousCities(eIndex, 0);
	
	pPlayer.AI_reset();
	
	int iHuman = CvUtils::getHumanID();
	
	// retset player espionage weight
	GET_PLAYER(GC.getGameINLINE().getActivePlayer()).setEspionageSpendingWeightAgainst(pPlayer.getTeam(), 0);
	
	// assign technologies
	std::vector<int> lTechs;
	getResurrectionTechs(eIndex, lTechs);
	for (int iTech = 0; i < lTechs.size(); i++)
		teamPlayer.setHasTech(iTech, true, eIndex, false, false);
	
	// determine army size
	int iNumCities = lCityList.size();
	int iGarrison = 2;
	int iArmySize = pPlayer.gerCurrentEra();

	pPlayer.setLatestRebellionTurn(GC.getGameINLINE().getGameTurn());
	
	// add former colonies that are still free , including barbarians
	for (int iMinor = NUM_PLAYERS; iMinor < MAX_PLAYERS; iMinor++)
	{
		CvPlayer& pPlayer = GET_PLAYER(iMinor);
		if (pPlayer.isAlive())
		{
			int iLoop = 0;
			for (CvCity* city = pPlayer.firstCity(&iLoop); city != NULL; city = pPlayer.nextcity(&iLoop))
			{
				if (city->getOriginalOwenr() == eIndex)
					if (pPlayer.getSettlerValue(city->getX(), city->getY()) >= HISTORICAL_VALUE)
						if (!VAL_IN(city, lCityList))
							lCityList.append(city);
			}
		}
	}
	
	std::vector<int> lOwners;
	std::map<int, CvUnit*> dRelocatedUnits;
	
	for  (int i = 0; i < lCityList.size(); i++)
	{
		CvCity* city = lCityList[i];
		
		int iOwner = city->getOwnerINLINE();
		CvPlayer& pOwner = GET_PLAYER(iOwner);
		
		int x = city->getX();
		int y = city->getY();
		
		bool bCapital = city->isCapital();
		
		int iNumDefenders = std::max(2, GET_PLAYER(eIndex).getCurrentEra() - 1);

		std::vector<CvUnit*> lFlippedUnits;
		std::vector<CvUnit*> lRelocatedUnits;
		CvUtils::flipOrRelocateGarrsion(city, iNumDefenders, lFlippedUnits, lRelocatedUnits);
	
		if (VAL_IN(iOwner, dRelocatedUnits))
			dRelocatedUnits[iOwner].insert(dRelocatedUnits.end(), lRelocatedUnits.begin(), lRelocatedUnits.end());
		else
			dRelocatedUnits[iOwner] = lRelocatedUnits;
		// error : CvUtils::completeCityFlip(x, y, eIndex, iOwner, 100, false, true, true, true);
		if (pOwner.isBarbarian() || pOwner.isMinorCiv())
			CvUtils::completeCityFlip(x, y, eIndex, iOwner, 100, false, true, true, true);
		else
			CvUtils::completeCityFlip(x, y, eIndex, iOwner, 75, false, true, true, true);
		// error : CvUtils::filpOrCreateDefenders(eIndex, lFlippedUnits, x, y, iNumDefenders);
		CvUtils::filpOrCreateDefenders(eIndex, lFlippedUnits, x, y, iNumDefenders);
		
		CvCity* newCity = city; // 是否多此一举？

		// Leoreth: rebuild some city infrastructure
		for (int iBuilding = 0; iBuilding < iNumBuildings; iBuilding++)
		{
			if (pPlayer.canConstruct(iBuilding, true, false, false) &&
				newCity->canConstruct(iBuilding, true, false, false) &&
				pPlayer.getCurrentEra() >= GC.getBuildingInfo(iBuilding).getFreeStartEra() &&
				!CvUtils::isUniqueBuilding(iBuilding) &&
				GC.getBuildingInfo(iBuilding).getPrereqReligion() == -1)
				newCity->setHasRealBuilding(iBuilding, true);
		}
		
		if (bCapital && iOwner < NUM_PLAYERS) relocateCapital(iOwner);
		
		if (!VAL_IN(iOwner, lOwners)) lOwners.append(iOwner);
	}
	
	// error : relocateUnitsToCore, killUnits
	std::map<int, CvUnit*>::const_iterator it;
	for (it = dRelocatedUnits.begin(); it != dRelocatedUnits.end(); ++it)
	{
		int iOwner = it->first();
		if (iOwner < NUM_PLAYERS)
			CvUtils::relocateUnitsToCore(iOwner, dRelocatedUnits[iOwner]);
		else
			CvUtils::killUnits(dRelocatedUnits[iOwner]);
	}
	
	for (int i = 0; i < lOwners.size(); i++)
	{
		int iOwner = lOwners[i];
		int teamOwner = GET_PLAYER(iOwner).getTeam();
		bool bOwnerHumanVassal = GET_TEAM(teamOwner).isVassal(GET_PLAYER(iHuman).getTeam());
		
		if (iOwner == iHuman && iOwner != eIndex && iOwner != iBarbarian)
		{
			int iRand = GC.getGameINLINE().getSorenRandNum(100, "Stop birth");
			
			if (iRand >= tAIStopBirthThreshold[iOwner] && !bOwnerHumanVassal)
				GET_TEAM(teamOwner).declareWar(GET_TEAM(GET_PLAYER(eIndex).getTeam(), false, -1);
			else
				GET_TEAM(teamOwner).makePeace(GET_PLAYER(eIndex).getTeam());
		}
	}
	
	if (GET_PLAYER(eIndex).getNumCities() == 0) ;
		// debugTextPopup
	
	if (m_iResurrections == 1)
		if (eIndex == iNubia || eIndex == iChad || eIndex == iKazakh)
			GET_PLAYER(eIndex).setReborn(true);
	
	relocateCapital(eIndex, true);
	
	// give the new civ a starting army
	CvCity* capital = pPlayer.getCapitalCity();
	int x = capital->getX();
	int y = capital->getY();
	// error : CvUtils::makeUnit(CvUtils::getBestInfantry(eIndex), eIndex, x, y, 2 * iArmySize + iNumCities);
	// CvUtils::getBestInfantry(eIndex)
	// CvUtils::getBestCounter(eIndex)
	// CvUtils::getBestSiege(eIndex)
	CvUtils::makeUnit(CvUtils::getBestInfantry(eIndex), eIndex, x, y, 2 * iArmySize + iNumCities);
	CvUtils::makeUnit(CvUtils::getBestCavalry(eIndex), eIndex, x, y, iArmySize);
	CvUtils::makeUnit(CvUtils::getBestCounter(eIndex), eIndex, x, y, iArmySize);
	CvUtils::makeUnit(CvUtils::getBestSiege(eIndex), eIndex, x, y, iArmySize + iNumCities);
	
	// set state religion based on religions in the area
	setStateReligion(eIndex);
	
	switchCivics(eIndex);
	
	// error : iGreen
	gDLL->getInterfaceIFace()->addMessage(iHuman, true, iDuration, gDLL->getText(
		"TXT_KEY_INDEPENDENCE_TEXT", pPlayer.getCivilizationAdjectiveKey()), "", 0,
		"", ColorTypes(iGreen), -1, -1, true, true);
	
	if (VAL_IN(bAskFlip, lOwners) && VAL_IN(iHuman, lOwners)) rebellionPopup(eIndex);
	
	setStabilityLevel(eIndex, iStabilityStable);
	
	m_iPlagueCountdown[eIndex] -= 10;
	CvUtils::clearPlague(eIndex);
	convertBackCulture(eIndex);
	
	// 硬编码
	int iGameTurn = GC.getGameINLINE().getGameTurn();
	// change the cores of some civs on respawn
	if (eIndex == iGreece) GET_PLAYER(iGreece).setReborn(true);
	else if (eIndex == iChina) 
		if (iGameTurn > getTurnForYear(tBirth[iMongolia]))
			GET_PLAYER(iChina).(, true);
	else if (eIndex == iIndia) GET_PLAYER(iIndia).setReborn(iGameTurn < getTurnForYear(1900));
	else if (eIndex == iArabia) GET_PLAYER(iArabia).setReborn(true);
	else if (eIndex == iVikings) GET_PLAYER(iVikings).setReborn(true);
	else if (eIndex == iPhilippines) GET_PLAYER(iPhilippines).setReborn(true); // For Spanish CNM
	
	// others revert to their old cores instead 硬编码 : 蒙古，阿拉伯
	if (eIndex == IArabia || eIndex == iMongolia) GET_PLAYER(eIndex).setReborn(false);
	
	// resurrection leaders
	if (VAL_IN(eIndex, resurrectionLeaders))
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
	for (int i = 0; i < lTechGroups.size(); i++)
	{
		std::vector<int> lRegionList = lTechGroups[i];
		if (VAL_IN(eIndex, lRegionList))
		{
			for (int j = 0; j < lRegionList.size(); j++)
			{
				int iPeer = lRegionList[j];
				if (iPeer != eIndex && GET_PLAYER(iPeer).isAlive())
					lSourceCivs.append(iPeer);
			}
		}
	}
	
	// direct neighbors (India can benefit from England etc)
	for (int iPeer = 0; iPeer < NUM_PLAYERS; iPeer++)
	{
		if (iPeer != eIndex && 
			!VAL_IN(iPeer, lSourceCivs) && 
			GET_PLAYER(iPeer).isAlive())
		{
			// error : isNeighbor()
			if (isNeighbor(eIndex, iPeer)) lSourceCivs.append(iPeer);
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
		for (int iOtherCiv = 0; iOtherCiv < lSourceCivs.size(); iOtherCiv++)
		{
			if (GET_TEAM(GET_PLAYER(iOtherCiv).getTeam()).isHasTech(iTech))
				iCount += 1;
		}
		
		if (2 * iCount >= lSourceCivs.size())
			lTechList.append(iTech);
	}
}

void CvStatbility::relocateCapital(PlayerTypes eIndex, bool bResurrenction)
{
	if (eIndex < NUM_PLAYERS) return;
	if (GET_PLAYER(eIndex).getNumCities() == 0) return;
	
	// error : CvPlot* CvArea::getCapital(PlayerTypes eIndex);
	CvPlot* tCapital = CvArea::getCapital(eIndex)
	CvCity* oldCapital = GET_PLAYER(eIndex).getCapitalCity();
	CvCity* newCpaital;
	// error : CvPlot* CvArea::getRespawnCapital(PlayerTypes eIndex);
	if (bResurrenction) tCapital = CvArea::getRespawnCapital(eIndex);
	
	if (plot->isCity() && plot->getPloyCity()->getOnwerINLINE() == eIndex)
		newCpaital = plot->getPlotCity();
	else
	{	
		std::vector<CvCity*> lCities;
		CvUtils::getCityList(eIndex, lCities);
		bool capitalCompare(CvCity* iCity, CvCity* jCity) 
		{
			int iI = std::max(0, CvUtils::getTurns(500) - iCity->getGameTurnFounded()) + iCity->getPopulaiton() * 5;
			int iJ = std::max(0, CvUtils::getTurns(500) - jCity->getGameTurnFounded()) + jCity->getPopulaiton() * 5;
			return (iI < iJ);
		}
		newCpaital = CvUtils::getHighestEntry<CvCity*>(lCities, capitalCompare);
	}
	
	oldCapital.setHasRealBuilding(iPalace, false);
	newCpaital.setHasRealBuilding(iPalace, true);
}

//文化值计算
void CvStatbility::convertBackCulture(PlayerTypes iCiv)
{
	std::vector<CvPlot*> lPlot;
	// error : CvArea::getRespawnArea(PlayerTypes iCiv, std::vector<CvPlot*>& lPlot);
	CvArea::getRespawnArea(iCiv, lPlot);
	
	for (int i = 0; i < lPlot.size(); i++)
	{
		CvPlot* plot = lPlot[i];
		if (plot->isCity())
		{
			CvCity* city = plot->getPlotCity();
			if (city->getOwnerINLINE() == iCiv)
			{
				int iCulture = 0;
				for  (int iMinor = NUM_PLAYERS; iMinor < MAX_PLAYERS; iMinor++)
				{
					iCulture += city->getCulture(iMinor);
					city->setCulture(iCiv, 0, true);
				}
				city->changeCulture(iCiv, iCulture, true);
			}
		}
		else if (plot->isCityRadius() && plot->getOwnerINLINE() == iCiv)
		{
			int iCulture = 0;
			for  (int iMinor = NUM_PLAYERS; iMinor < MAX_PLAYERS; iMinor++)
			{
				iCulture += city->getCulture(iMinor);
				city->setCulture(iCiv, 0, true);
			}
			plot->changeCulture(iCiv, iCulture, true);
		}
	}
}

void CvStatbility::setStateReligion(PlayerTypes iCiv)
{
	std::vector<CvCity*> lCities;
	// error : CvArea::getAreaCities(PlayerTypes iCiv, std::vector<CvCity*>& lCities);
	CvArea::getAreaCities(getCoreArea(iCiv), lCities);
	
	int iNumReligions = GC.getNumReligionInfos();
	std::vector<int> lReligions(iNumReligions, 0);
	
	for (int iCity = 0; iCity < lCities.size(); iCity++)
	{
		for (int iReligion = 0; iReligion < iNumReligions; iReligion++)
		{
			if (GC.getReligionInfo(iReligion).isLocal() &&
				lCities[iCity]->plot()->getSpreadFactor(iReligion) != REGION_SPREAD_CORE)
				continue;
			if lCities[iCity].isHasReligion(iReligion)
				lReligions[iReligion] += 1;
		}
	}
	
	// error : int CvUtils::getHighestEntry(std::vector<int> lReligions);
	int iHighestEntry = CvUtils::getHighestEntry(lReligions);
	
	if (iHighestEntry > 0)
		GET_PLAYER(iCiv).setLastStateReligion(lReligions[iHighestEntry]);
}

void CvStatbility::switchCivics(PlayerTypes eIndex)
{
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	
	for (int i = iCategory = 0; i < iNumCivicCategories; i++)
	{
		int iBestCivic = pPlayer.AI_bestCivic(iCategory);
		
		if (iBestCivic >= 0) pPlayer.setCivics(iCategory, iBestCivic);
	}
	
	pPlayer.setRevolutionTimer(GC.getDefineINT("MIN_REVOLUTION_TURNS"));
}

// error
void rebellionPopup(int iRebelCiv)
{
	// showPopup
}

int sign(int x)
{
	if (x == 0) return x;
	return (x > 0) ? 1 : -1;
}

void getCorePopulationModifier(int iEra)
{	// error : 初始化代码的写法?
	static bool bInit;
	if (bInit) return m_tEraCorePopualitonModifiers[iEra];
	
	m_tEraCorePopualitonModifiers.clear();
	
	m_tEraCorePopulationModifiers = { 
		100, // ancient
		200, // classical
		200, // medieval
		250, // renaissance
		300, // industrial
		350, // modern
		400, // future
	};
	
	bInit = true;
}

int CvStatbility::getUnionPop(PlayerTypes eIndex, int iCorePopulationModifier)
{
	int iUnionPop = 0;
	
	int iLoop = 0;
	CvPlayer& pPlayer = GET_PLAYER(eIndex);
	
	for (CvCity* pCity = pPlayer.firstCity(&iLoop); pCity != NULL; pCity = pPlayer.nextCity(&iLoop))
	{
		if (pCity->plot()->isCore(eIndex))
			iUnionPop += iCorePopulationModifier * pCity->getPopulaiton() / 100
	}
	
	return iUnionPop;
}

void CvStatbility::balanceStability(PlayerTypes eIndex, StabilityLevelTypes eNewStabilityLevel)
{
	// debugTextPopup
	
	// set stability to at least the specified level
	setStabilityLevel(eIndex, std::max(eNewStabilityLevel, getStabilityLevel(eIndex));
	
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
	return (CvUtils::getHumanID() != eIndex && GET_PLAYER(eIndex).isReborn() &&
	GC.getGameINLINE().getGameTurn() >= getTurnForYear(tFall[eIndex]));
}
// error : popup 怎么调用和创建
void CvUtils::showPopup(int popupID, CvWString title, CvWString message, std::vector<CvWString> labels)
{
	CvPopop* pPopop = 
	gDLL->getInterfaceIFace()->popupSetHeaderString(pPopup, title);
	gDLL->getInterfaceIFace()->popupSetBodyString(pPopup, message);
	for (int i = 0; i < labels.size(); i++)
	{
		gDLL->getInterfaceIFace()->popupAddGenericButton(pPopop, labels[i]);
	}
	gDLL->getInterfaceIFace()->popupLaunch(pPopup, false, POPUPSTATE_IMMEDIATE);
}
