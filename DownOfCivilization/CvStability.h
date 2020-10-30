// CvStatbility.h
/*
// addMessage写法

	gDLL->getInterfaceIFace()->addMessage(eIndex, false, iDuration, gDLL-getText( "TXT_KEY_STABILITY_COLLAPSING_WARNING"), "", 0, "", ColorTypes(iRed), -1, -1, true, true);
*/
#pragma once
#ifndef _CvStability_H_
#define _CvStability_H_

#include "config_pymodules.h"
#include "config_py2cpp.h"

#define HISTORICAL_VALUE 	(90)

//const char* tCrisisLevels[] = {
//	"TXT_KEY_STABILITY_CRISIS_LEVEL_TERMINAL",
//	"TXT_KEY_STABILITY_CRISIS_LEVEL_SEVERE",
//	"TXT_KEY_STABILITY_CRISIS_LEVEL_MODERATE",
//	"TXT_KEY_STABILITY_CRISIS_LEVEL_MINOR",
//	"TXT_KEY_STABILITY_CRISIS_LEVEL_MINOR",
//};
//
//const char* tCrisisTypes[] = {
//	"TXT_KEY_STABILITY_CRISIS_TYPE_EXPANSION",
//	"TXT_KEY_STABILITY_CRISIS_TYPE_ECONOMY",
//	"TXT_KEY_STABILITY_CRISIS_TYPE_DOMESTIC",
//	"TXT_KEY_STABILITY_CRISIS_TYPE_FOREIGN",
//	"TXT_KEY_STABILITY_CRISIS_TYPE_MILITARY",
//};


class CvCity;
class CvStatbility
{
public:
	class Civics
	{
	public:
		Civics(std::vector<CivicTypes>& lActiveCivics) 
		{ 
			for (unsigned int i = 0; i < lActiveCivics.size(); i++)
				m_activeCivics.insert(lActiveCivics[i]);
		}
		~Civics() {}
		
		bool contains(CivicTypes civic)
		{ 
			return (bool)m_activeCivics.count(civic); 
		}
		
		bool any(std::vector<CivicTypes>& lCivics)
		{
			for (unsigned int i = 0; i < lCivics.size(); i++)
			{
				if (contains(lCivics[i])) return true;
			}
			return false;
		}
		
		bool no(CivicTypes civic)
		{
			int type = GC.getCivicInfo(civic).getCivicOptionType();
			bool bNotIn = true;
			std::set<CivicTypes>::const_iterator it;
			for (it = m_activeCivics.begin(); it != m_activeCivics.end(); ++it)
			{
				if (type == GC.getCivicInfo(*it).getCivicOptionType())
					bNotIn = false;
			}
			if (bNotIn) return false;
			
			return !contains(civic);
		}
		
	private:
		std::set<CivicTypes> m_activeCivics;
	};
	
public:
	static CvStatbility& getInstance() 
	{
		static CvStatbility m_Instance;
		return m_Instance;
	}
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

	void checkResurrection(int iGameTurn);
	
	StabilityLevels getStabilityLevel(PlayerTypes eIndex);
	void setStabilityLevel(PlayerTypes eIndex, StabilityLevels eStabilityLevel);
	StabilityLevels determineStabilityLevel(StabilityLevels eCurrentLevel, int iStability, bool bFall =false);
	int determineCrisisType(std::vector<StabilityLevels>& lStabilityTypes);

	void incrementStability(PlayerTypes eIndex);
	void decrementStability(PlayerTypes eIndex);

	// 核心函数 
	void checkStability(PlayerTypes eIndex, bool bPositive = false, int iMaster = -1); // Exposed to Python
	// 核心函数 
	void calculateStability(PlayerTypes eIndex, int& iStability, std::vector<int>& lStabilityTypes, std::vector<int>& lParameters);
	
	int getCivicStability(PlayerTypes eIndex, std::vector<CivicTypes>& lCivics);
	void balanceStability(PlayerTypes eIndex, StabilityLevels eNewStabilityLevel); // Exposed to Python
	
	void relocateCapital(PlayerTypes eIndex, bool bResurrenction = false);
	void setStateReligion(PlayerTypes iCiv);
	void switchCivics(PlayerTypes eIndex);
	void convertBackCulture(PlayerTypes iCiv);
	void downgradeCottages(PlayerTypes eIndex);
	
	int calculateEconomicGrowth(PlayerTypes eIndex, int iNumTurns);
	int calculateEconomicGrowthNeighbors(PlayerTypes eIndex, int iNumTurns);

	void getPossibleMinors(PlayerTypes eIndex, std::vector<PlayerTypes>& lCivs);
	void secession(PlayerTypes eIndex, std::vector<CvCity*>& lCities);
	void secedeCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities, bool bRazeMinorCities = false);
	void secedeCity(CvCity* city, PlayerTypes iNewOwner, bool bRelocate);
	
	void startWar(PlayerTypes iPlayer, PlayerTypes iEnemy);
	
	void resurrectionFromCollapse(PlayerTypes eIndex, std::vector<CvCity*>& lCityList);
	void doResurrection(PlayerTypes eIndex, std::vector<CvCity*>& lCityList, bool AskFilp = true);
	void getResurrectionTechs(PlayerTypes eIndex, std::vector<int>& lTechList);
	void getResurrectionCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities, bool bFromCollapse = false);

	int getUnionPop(PlayerTypes eIndex, int iCorePopulationModifier);
	
	bool isImmune(PlayerTypes eIndex);
	bool isDecline(PlayerTypes eIndex);
	bool isTolerated(PlayerTypes eIndex, ReligionTypes iReligion);
	
	int calculateAttitude(PlayerTypes iFromPlayer, PlayerTypes iToPlayer);
	int calculateTrendScore(std::list<int>& lTrend);
	int calculateSumScore(std::vector<int>& lScores, int iThreshold  = 1);

	int calculatePowerRank(PlayerTypes eIndex, int iTurn);
	void CvStatbility::calculateRankedAttitudes(PlayerTypes eIndex, std::vector<PlayerTypes>& lContacts,
		std::vector<int>& lStronger,
		std::vector<int>& lEqual,
		std::vector<int>& lWeaker);
	
public:
	int getTurnsToCollapse(PlayerTypes eIndex); 
	void changeTurnsToCollapse(PlayerTypes eIndex, int iChange);
	void setTurnsToCollapse(PlayerTypes eIndex, int iNewValue);
	
	int getCrisisCountdown(PlayerTypes eIndex);
	void changeCrisisCountdown(PlayerTypes eIndex, int iChange);
	
	int getHumanRazePenalty(void); 
	void changeHumanRazePenalty(int iChange);
	
	int getBarbarianLosses(PlayerTypes eIndex);
	void changeBarbarianLosses(PlayerTypes eIndex, int iChange);
	
	void setHumanStability(int iNewValue);
	
	void getSecedingCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities);
	void setSecedingCities(PlayerTypes eIndex, std::vector<CvCity*>& lCities);
	
	int getRomanPigs(void);
	void setRomanPigs(int iNewValue);
	
	int getNumPreviousCities(PlayerTypes eIndex);
	void setNumPreviousCities(PlayerTypes eIndex, int iNewValue);
	
	int getLastStability(PlayerTypes eIndex);
	void setLastStability(PlayerTypes eIndex, int iNewValue);

	int getLastStabilityTurn(PlayerTypes eIndex);
	void setLastStabilityTurn(PlayerTypes eIndex, int iNewTurn);
	
	std::list<int>& getEconomyTrend(PlayerTypes eIndex);
	std::list<int>& getHappinessTrend(PlayerTypes eIndex);
	
	int getPreviousCommerce(PlayerTypes eIndex);
	void setPreviousCommerce(PlayerTypes eIndex, int iNewValue);
	
	// reset war, economy and happiness trends to give them a breather
	void resetEconomyTrend(PlayerTypes eIndex);
	void resetHappinessTrend(PlayerTypes eIndex);
	void resetWarTrends(PlayerTypes eIndex);
	void resetWarTrends(PlayerTypes eIndex, PlayerTypes iEnemy);

	void pushEconomyTrend(PlayerTypes eIndex, int iCurrentTrend);
	void pushHappinessTrend(PlayerTypes eIndex, int iCurrentTrend);
	void pushWarTrend(PlayerTypes eIndex, PlayerTypes iEnemy, int iCurrentTrend);

	std::list<int>& getWarTrend(PlayerTypes eIndex, PlayerTypes iEnemy);

	int getWarStartTurn(PlayerTypes eIndex, PlayerTypes iEnemy);

	int getLastTurnAlive(PlayerTypes eIndex);
	void setLastTurnAlive(PlayerTypes eIndex, int iNewTurn);

	void setLastWarSuccess(PlayerTypes eIndex, PlayerTypes iEnemy, int iValue);

public: // On Events : MUST BE Exposed to Python
	void onCityAcquired(CvCity* city, PlayerTypes iOwner, PlayerTypes iPlayer);
	void onCityRazed(PlayerTypes iPlayer, CvCity* city);
	void onTechAcquired(PlayerTypes iPlayer, int iTech);
	void onVassalState(PlayerTypes iMaster, PlayerTypes iVassal);
	void onChangeWar(bool bWar, PlayerTypes iTeam, PlayerTypes iOtherTeam);
	void onRevolution(PlayerTypes iPlayer);
	void onPlayerChangeStateReligion(PlayerTypes iPlayer);
	void onPalaceMoved(PlayerTypes iPlayer);
	void onWonderBuilt(PlayerTypes iPlayer, int iBuildingType);
	void onGoldenAge(PlayerTypes iPlayer);
	void onGreatPersonBorn(PlayerTypes iPlayer);
	void onCombatResult(PlayerTypes iWinningPlayer, PlayerTypes iLosingPlayer, int iLostPower);
	void onCivSpawn(PlayerTypes iPlayer);

public:
	
	
	template<typename T>
	int	index(std::vector<T>& lList, T val);

	int				getCorePopulationModifier(int iEra);
	double			sigmoid(double x);
	int				sign(int x);
	int				getTurns(int turns);
	PlayerTypes		getHumanID();

protected:
	int* m_iTurnsToCollapse;
	int* m_iBarbarianLosses;
	int* m_iCrisisCountdown;
	int* m_iNumPreviousCities;
	int* m_iLastStabilityTurn;
	int* m_iPreviousCommerce;
	int* m_iLastStability;
	int* m_iLastTurnAlive;
	int m_iLastExpansionStability[MAX_PLAYERS];
	int m_iPlagueCountdown[MAX_PLAYERS];

	bool m_bSpawned[MAX_PLAYERS];
	int m_iResurrections[MAX_PLAYERS];

	int m_iRomanPigs;
	int m_iCivsWithNationalism;
	
	PlayerTypes m_iRebelCiv;
	PlayerTypes m_iHumanID;
	int m_iHumanRazePenalty;
	int m_iHumanStability;
	
	std::list<int> m_lEconomyTrend[MAX_PLAYERS];
	std::list<int> m_lHappinessTrend[MAX_PLAYERS];
	std::list<int> m_lWarTrend[MAX_PLAYERS][MAX_PLAYERS];
	int m_lWarStartTurn[MAX_PLAYERS][MAX_PLAYERS];
	int m_lLastWarSuccess[MAX_PLAYERS][MAX_PLAYERS];
	
	StabilityLevels m_eStabilityLevel[MAX_PLAYERS];
	
	std::vector<CvCity*> m_lSecedingCities[MAX_PLAYERS];
	
	std::vector<int> m_tEraCorePopulationModifiers;

	int m_lStabilityCategoryValues[MAX_PLAYERS][iNumStabilityLevels];
};

#define getStability		CvStatbility::getInstance()

#endif
