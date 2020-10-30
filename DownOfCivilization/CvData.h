#pragma once

#ifndef _CvData_H_
#define _CvData_H_

#include "config_pymodules.h"
#include "config_py2cpp.h"

// Rhye's and Fall of Civilization - Stored Data

//import Popup
//import cPickle as pickle

#define NegaitiveOnes(v)			for (uint i = 0; i < len(v); i++) v[i] = -1;
#define Zeors(v)					for (uint i = 0; i < len(v); i++) v[i] = 0;

class PlayerData
{
public:
	PlayerTypes m_iPlayer;

	// Rise and Fall
	bool	m_bSpawned;
	int		m_iColonistsAlreadyGiven;
	int		m_iSpawnDelay;
	int		m_iFlipsDelay;
	int		m_iBirthTurnModifier;
	int		m_iAnarchyTurns;
	int		m_iResurrections;
	int		m_iLastTurnAlive;
	int		m_iExplorationTurn;
	int		m_iSpawnType;

	// Religions

	int		m_iReformationDecision;

	// AI Wars
	int		m_iAggressionLevel;

	// Plague
	int		m_iPlagueCountdown;
	int		m_bFirstContactPlague;

	// Victory
	bool	m_bHistoricalGoldenAge;
	boost::array<int, 3>	m_lGoals;
	boost::array<int, 3>	m_lGoalTurns;
	
	// Stability
	StabilityLevels		m_iStabilityLevel;

	int		m_iTurnsToCollapse;
	int		m_iCrisisCountdown;
	int		m_iLastStabilityTurn;
	int		m_iLastStability;
	int		m_iLastDifference;
	int		m_iNumPreviousCities;
	int		m_iBarbarianLosses;
	int		m_iPreviousCommerce;
	int		m_iLastExpansionStability;

	std::list<int>	m_lEconomyTrend;
	std::list<int>	m_lHappinessTrend;
	std::vector<std::list<int> >	m_lWarTrend;
	std::vector<int>	m_lWarStartTurn;
	std::vector<int>	m_lLastWarSuccess;

	boost::array<int, 5>	m_lStabilityCategoryValues;

	// Tech Log
	int		m_iTechColumn;

public:
	PlayerData(void)
	{
	}

	PlayerData(PlayerTypes iPlayer)
	{
		m_iPlayer = iPlayer;
		init();
	}

	~PlayerData() { }

	void init(void)
	{
		// Rise and Fall

		m_bSpawned = False;
		m_iColonistsAlreadyGiven = 0;
		m_iSpawnDelay = 0;
		m_iFlipsDelay = 0;
		m_iBirthTurnModifier = 0;
		m_iAnarchyTurns = 0;
		m_iResurrections = 0;
		m_iLastTurnAlive = 0;
		m_iExplorationTurn = 1500;
		m_iSpawnType = 0;

		// Religions

		m_iReformationDecision = -1;

		// AI Wars

		m_iAggressionLevel = 0;

		// Plague

		m_iPlagueCountdown = 0;
		m_bFirstContactPlague = False;

		// Victory

		m_lGoals.assign(-1);
		m_lGoalTurns.assign(-1);
		m_bHistoricalGoldenAge = False;

		// Stability

		resetStability();

		// Tech Log

		m_iTechColumn = 0;
	}

	void resetStability(void)
	{
		m_iStabilityLevel = iStabilityShaky;

		m_iTurnsToCollapse = -1;

		m_iCrisisCountdown = 0;
		m_iLastStabilityTurn = 0;
		m_iLastStability = 0;
		m_iLastDifference = 0;
		m_iNumPreviousCities = 0;
		m_iBarbarianLosses = 0;
		m_iPreviousCommerce = 0;
		m_iLastExpansionStability = 0;

		m_lEconomyTrend.clear();
		m_lHappinessTrend.clear();

		for (int i = 0; i < (int)iNumTotalPlayersB; i++)
		{
			m_lWarTrend.append(std::list<int>());
		}
		m_lWarStartTurn = std::vector<int>((int)iNumTotalPlayersB, 0);
		m_lLastWarSuccess = std::vector<int>((int)iNumTotalPlayersB, 0);

		m_lStabilityCategoryValues = (list_of(0), 0, 0, 0, 0);
	}

	void resetEconomyTrend(void)
	{
		m_lEconomyTrend.clear();
	}

	void resetHappinessTrend(void)
	{
		m_lHappinessTrend.clear();
	}

	void resetWarTrend(PlayerTypes iEnemy)
	{
		m_lWarTrend[iEnemy].clear();
	}

	void resetWarTrends(void)
	{
		for (int iEnemy = 0; iEnemy < NUM_PLAYERS; iEnemy++)
			resetWarTrend((PlayerTypes)iEnemy);
	}

	void pushEconomyTrend(int iValue)
	{
		m_lEconomyTrend.append(iValue);
		if (len(m_lEconomyTrend) > 10u)
			m_lEconomyTrend.pop_front();
	}

	void pushHappinessTrend(int iValue)
	{
		m_lHappinessTrend.append(iValue);
		if (len(m_lHappinessTrend) > 10u)
			m_lHappinessTrend.pop_front();
	}

	void pushWarTrend(PlayerTypes iEnemy, int iValue)
	{
		m_lWarTrend[iEnemy].append(iValue);
		if (len(m_lWarTrend[iEnemy]) > 10u)
			m_lWarTrend[iEnemy].pop_front(); // pop(10)?
	}

	int getLastDifference(void)
	{
		return -m_iLastDifference;
	}

	int getLastWarTrend(PlayerTypes iEnemy)
	{
		std::list<int>& lTrend = m_lWarTrend[iEnemy];
		// 找到最后一个非0值并返回
		return *std::find_if_not(lTrend.rbegin(), lTrend.rend(), boost::bind(std::equal_to<int>(), _1, 0));
	}
	
	int getGoal(int iGoal)
	{
		return m_lGoals[iGoal];
	}

	void setGoal(int iGoal, int iNewValue)
	{
		if (iNewValue == 1 and getGoal(iGoal) == 0) return;
		m_lGoals[iGoal] = iNewValue;
	}
};

class GameData
{
public:

	boost::array<PlayerData, iNumTotalPlayersB>		m_players;

	std::vector<int>							m_lTempEvents;
	std::vector<PlayerTypes>					m_lNewCivs;
	std::vector<coord >							m_lTempPlots;

	std::vector<std::pair<PlayerTypes, coord > > m_lTimedConquests;

	boost::array<bool, lSecondaryCivsSize>	    m_lPlayerEnabled;
	boost::array<bool, iNumMinorCities>			m_lMinorCityFounded;

	boost::array<int, 3>						m_lDeleteMode;
	boost::array<bool, lCivBioNewWorldSize>		m_lFirstContactConquerors;
	boost::array<bool, lMongolCivsSize>			m_lFirstContactMongols;
	boost::array<std::vector<int>, 5>			m_lTradingCompanyConquerorsTargets;

	std::pair<int, int>			m_lCheatersCheck;

	int		m_iRespawnCiv;
	int		m_iNewCivFlip;
	int		m_iOldCivFlip;
	int		m_iOttomanSpawnTurn;

	int		m_iSpawnWar;
	int		m_iBetrayalTurns;
	int		m_iRebelCiv;

	std::vector<UnitTypes>	m_lFlippingUnits;

	bool	m_bAlreadySwitched;
	bool	m_bUnlimitedSwitching;
	bool	m_bCheatMode;

	int		m_iRomanPigs;
	bool	m_bMississippiCollapse;

	// Religions
	int		m_iSeed;

	// Unique Powers
	int m_iImmigrationTimer;
	int m_iRomanVictories;
	std::vector<PlayerTypes>				m_lPhilippineEmbassies;
	std::vector<std::pair<CvUnit*, int> >	m_lByzantineBribes;
	boost::array<int, 5>					m_lLatestRazeData;

	// AI Wars

	int									m_iNextTurnAIWar;
	boost::array<bool, iNumConquests>	m_lConquest;

	// Congresses
	int				m_iGlobalWarAttacker;
	int				m_iGlobalWarDefender;
	int				m_iCongressTurns;
	int				m_iCivsWithNationalism;
	boost::tribool	m_currentCongress;
	bool			m_bNoCongressOption;

	// Plague
	boost::array<int, 4>	m_lGenericPlagueDates;
	bool					m_bNoPlagues;

	// Victories

	bool	m_bIgnoreAI;
	bool	m_bEthiopiaConverted;

	boost::array<PlayerTypes, (iNumBuildings - iBeginWonders)>	m_lWonderBuilder;
	boost::array<int, iNumReligions>							m_lReligionFounder;
	boost::array<int, iNumTechs>								m_lFirstDiscovered;
	boost::array<int, iNumEras>									m_lFirstEntered;
	boost::array<int, iNumEras>									m_lFirstCompleted;
	boost::array<int, lGreatPeopleUnitsSize>					m_lFirstGreatPeople;

	int				m_iFirstNewWorldColony;
	int				m_iChineseGoldenAgeTurns;
	int				m_iTeotihuacanGoldenAgeTurns;
	int				m_iKoreanSinks;
	float			m_iTamilTradeGold;
	int				m_iKievanRusMissions;
	int				m_iColombianTradeGold;
	int				m_iNigeriaTradeGold;
	int				m_iVikingGold;
	int				m_iTurkicPillages;
	int				m_iMoorishGold;
	int				m_iEnglishSinks;
	int				m_iSwahiliTradeGold;
	int				m_iMongolRazes;
	int				m_iAztecSlaves;
	int				m_iCongoSlaveCounter;
	int				m_iSwedenHappinessTurns;
	int				m_iDutchColonies;
	int				m_iMexicanGreatGenerals;
	int				m_iVietnamGreatGenerals;
	int				m_iArgentineGoldenAgeTurns;
	int				m_iCanadianPeaceDeals;
	int				m_iAustraliaGifts;
	int				m_iAustraliaHappinessTurns;
	int				m_iHungaryGlobalWars;
	bool			m_bHungaryTolerance;
	int				m_iIsraeliResearchTurns;
	int				m_iOmaniCities;
	int				m_iOmaniTradeGold;
	int				m_iNubiaEgyptYears;
	int				m_iChadTradeMissions;
	int				m_iChadDiplomacyMissions;
	int				m_iChadSlaves;
	int				m_iChadStrategicBonuses;
	int				m_iCeltiaRazedCapitals;
	int				m_iTiwanakuGoldenAgeTurns;
	int				m_iMuiscaTradeGold;
	int				m_iXiongnuDemands;
	int				m_iXiongnuCityTernary; // 0 = None, 1 = Europe, 2 = India
	int				m_iLithuaniaGifts;

	boost::array<bool, 3>		m_lHolyRomanShrines;
	std::vector<PlayerTypes>	m_lXiongnuCivs;
	std::vector<CvCity*>		m_lCeltiaConqueredCapitals;
	std::vector<TeamTypes>		m_lOmaniEnemies;
	std::vector<int>			m_lAustralianGiftReceivers;
	boost::tribool				m_tFirstTurkicCapital;
	boost::tribool				m_tSecondTurkicCapital;

	int		m_iPopeTurns;
	int		m_iHinduGoldenAgeTurns;
	int		m_iBuddhistPeaceTurns;
	int		m_iBuddhistHappinessTurns;
	int		m_iTaoistHealthTurns;
	int		m_iVedicHappiness;
	int		m_iTeotlSacrifices;
	bool	m_bPolytheismNeverReligion;

	// Stability

	int		m_iHumanStability;
	int		m_iHumanRazePenalty;

	bool	m_bCrisisImminent;

	std::map<PlayerTypes, std::vector<int> > m_dSecedingCities;

public:
	static GameData& getInstance(void) {
		static GameData m_Instance;
		return m_Instance;
	}

	~GameData() {}
private:

	GameData(void)
	{
		setup();
	}

	void setup(void)
	{
		for (uint i = 0; i < len(m_players); i++)
			m_players[i] = PlayerData((PlayerTypes)i);

		// Rise and Fall

		m_lTempEvents.clear();
		m_lNewCivs.clear();
		m_lTempPlots.clear();
		m_lTimedConquests.clear();

		m_lPlayerEnabled.assign(True);
		m_lMinorCityFounded.assign(False);

		m_lDeleteMode.assign(-1);
		m_lFirstContactConquerors.assign(False);
		m_lFirstContactMongols.assign(True);

		for (int i = 0; i < 5; i++) {
			m_lTradingCompanyConquerorsTargets[i].clear();
		}
		
		m_lCheatersCheck = std::make_pair(0, -1);

		m_iRespawnCiv = -1;
		m_iNewCivFlip = -1;
		m_iOldCivFlip = -1;
		m_iOttomanSpawnTurn = -1;

		m_iSpawnWar = 0;
		m_iBetrayalTurns = 0;
		m_iRebelCiv = 0;

		m_lFlippingUnits.clear();

		m_bAlreadySwitched = False;
		m_bUnlimitedSwitching = False;
		m_bCheatMode = False;

		m_iRomanPigs = -1;
		m_bMississippiCollapse = False;

		// Religions
		m_iSeed = GC.getGameINLINE().getSorenRandNum(100, "Random delay");

		// Unique Powers
		m_iImmigrationTimer = 0;
		m_iRomanVictories = 0;
		m_lPhilippineEmbassies.clear();
		m_lByzantineBribes.clear();
		m_lLatestRazeData.assign(-1);

		// AI Wars
		m_iNextTurnAIWar = -1;
		m_lConquest.assign(False);

		// Congresses
		m_iGlobalWarAttacker = -1;
		m_iGlobalWarDefender = -1;
		m_iCongressTurns = 8;
		m_iCivsWithNationalism = 0;
		m_currentCongress = None;
		m_bNoCongressOption = False;

		// Plague
		m_lGenericPlagueDates.assign(-1);
		m_bNoPlagues = False;

		// Victories
		m_bIgnoreAI = True;
		m_bEthiopiaConverted = False;

		m_lWonderBuilder.assign(NO_PLAYER);
		m_lReligionFounder.assign(-1);
		m_lFirstDiscovered.assign(-1);
		m_lFirstEntered.assign(-1);
		m_lFirstCompleted.assign(-1);
		m_lFirstGreatPeople.assign(-1);
		m_iFirstNewWorldColony = -1;

		m_iChineseGoldenAgeTurns = 0;
		m_iTeotihuacanGoldenAgeTurns = 0;
		m_iKoreanSinks = 0;
		m_iTamilTradeGold = 0.0;
		m_iKievanRusMissions = 0;
		m_iColombianTradeGold = 0;
		m_iNigeriaTradeGold = 0;
		m_iVikingGold = 0;
		m_iTurkicPillages = 0;
		m_iMoorishGold = 0;
		m_lHolyRomanShrines.assign(False);
		m_iEnglishSinks = 0;
		m_iSwahiliTradeGold = 0;
		m_iMongolRazes = 0;
		m_iAztecSlaves = 0;
		m_iCongoSlaveCounter = 0;
		m_iSwedenHappinessTurns = 0;
		m_iDutchColonies = 0;
		m_iMexicanGreatGenerals = 0;
		m_iVietnamGreatGenerals = 0;
		m_iArgentineGoldenAgeTurns = 0;
		m_iCanadianPeaceDeals = 0;
		m_iAustraliaGifts = 0;
		m_lAustralianGiftReceivers.clear();
		m_iAustraliaHappinessTurns = 0;
		m_iHungaryGlobalWars = 0;
		m_bHungaryTolerance = False;
		m_iIsraeliResearchTurns = 0;
		m_lOmaniEnemies.clear();
		m_iOmaniCities = 0;
		m_iOmaniTradeGold = 0;
		m_iNubiaEgyptYears = 0;
		m_iChadTradeMissions = 0;
		m_iChadDiplomacyMissions = 0;
		m_iChadSlaves = 0;
		m_iChadStrategicBonuses = 0;
		m_iCeltiaRazedCapitals = 0;
		m_lCeltiaConqueredCapitals.clear();
		m_iTiwanakuGoldenAgeTurns = 0;
		m_iMuiscaTradeGold = 0;
		m_iXiongnuDemands = 0;
		m_iXiongnuCityTernary = 0; // 0 = None, 1 = Europe, 2 = India
		m_lXiongnuCivs.clear();
		m_iLithuaniaGifts = 0;

		m_tFirstTurkicCapital = None;
		m_tSecondTurkicCapital = None;

		m_iPopeTurns = 0;
		m_iHinduGoldenAgeTurns = 0;
		m_iBuddhistPeaceTurns = 0;
		m_iBuddhistHappinessTurns = 0;
		m_iTaoistHealthTurns = 0;
		m_iVedicHappiness = 0;
		m_iTeotlSacrifices = 0;
		m_bPolytheismNeverReligion = True;

		// Stability

		m_iHumanStability = 0;
		m_iHumanRazePenalty = 0;

		m_bCrisisImminent = False;

		m_dSecedingCities.clear();
	}
public:
	void timedConquest(PlayerTypes iPlayer, coord tPlot)
	{
		m_lTimedConquests.append(std::make_pair(iPlayer, tPlot));
	}

	void setPlayerEnabled(PlayerTypes iPlayer, bool bNewValue)
	{
		m_lPlayerEnabled[INDEX(lSecondaryCivs, iPlayer)] = bNewValue;
	}

	bool isPlayerEnabled(PlayerTypes iPlayer)
	{
		if (GC.getGameINLINE().getActivePlayer() == iPlayer) return True;
		return m_lPlayerEnabled[INDEX(lSecondaryCivs, iPlayer)];
	}

	void resetStability(PlayerTypes iPlayer)
	{
		m_players[iPlayer].resetStability();
		for (int i = 0; i < (int)m_players.size(); i++) {
			if (iPlayer != (PlayerTypes)i)
				m_players[i].resetWarTrend(iPlayer);
		}			
	}

	void resetHumanStability(void)
	{
		m_bCrisisImminent = False;
		m_iHumanStability = 0;
		m_iHumanRazePenalty = 0;
	}

	void getSecedingCities(PlayerTypes iPlayer, std::vector<CvCity*> lCities)
	{
		if (not m_dSecedingCities.count(iPlayer)) {
			lCities.clear();
			return;
		}
		for (int i = 0; i < len(m_dSecedingCities[iPlayer]); i++) {
			CvCity* city = GET_PLAYER(iPlayer).getCity(m_dSecedingCities[iPlayer][i]);
			if (city->getX() != -1 and city->getY() != -1)
				lCities.append(city);
		}
	}

	void setSecedingCities(PlayerTypes iPlayer, std::vector<CvCity*>& lCities) {
		for (int i = 0; i < len(lCities); i++) {
			m_dSecedingCities[iPlayer].append(lCities[i]->getID());
		}
	}

	PlayerTypes getNewCiv(void)
	{
		return m_lNewCivs.back();
	}

	void addNewCiv(PlayerTypes iCiv)
	{
		m_lNewCivs.append(iCiv);
	}

	bool isFirstContactMongols(PlayerTypes iPlayer)
	{
		return m_lFirstContactMongols[INDEX(lMongolCivs, iPlayer)];
	}

	void setFirstContactMongols(PlayerTypes iPlayer, bool bValue)
	{
		m_lFirstContactMongols[INDEX(lMongolCivs, iPlayer)] = bValue;
	}

	StabilityLevels getStabilityLevel(PlayerTypes iPlayer)
	{
		return m_players[iPlayer].m_iStabilityLevel;
	}
	// gDLL->getInterfaceIFace()->addMessage(GC.getGame().getActivePlayer(), true, GC.getEVENT_MESSAGE_TIME(), 
	// gDLL->getText("TXT_KEY_OVERFLOW", getX(), getY(), "processSpecialist()"), "", MESSAGE_TYPE_MAJOR_EVENT, 
	// ARTFILEMGR.getInterfaceArtInfo("WORLDBUILDER_CITY_EDIT")->getPath(), (ColorTypes)GC.getInfoTypeForString("COLOR_RED"), 
	// getX_INLINE(), getY_INLINE(), true, true);
	void setStabilityLevel(PlayerTypes iPlayer, StabilityLevels iValue) {
		if (GC.getGameINLINE().getActivePlayer() == iPlayer) { // if utils.getHumanID() == iPlayer
			StabilityLevels iOldStabilityLevel = getStabilityLevel(iPlayer);
			CvWStringBuffer szTempBuffer;
#ifdef append
#undef append
			if (iValue == iStabilityCollapsing) szTempBuffer.append(gDLL->getText("TXT_KEY_STABILITY_COLLAPSING"));
			else if (iValue == iStabilityUnstable) szTempBuffer.append(gDLL->getText("TXT_KEY_STABILITY_UNSTABLE"));
			else if (iValue == iStabilityShaky) szTempBuffer.append(gDLL->getText("TXT_KEY_STABILITY_SHAKY"));
			else if (iValue == iStabilityStable) szTempBuffer.append(gDLL->getText("TXT_KEY_STABILITY_STABLE"));
			else if (iValue == iStabilitySolid) szTempBuffer.append(gDLL->getText("TXT_KEY_STABILITY_SOLID"));
#define append push_back
#endif
			/*if (iValue > iOldStabilityLevel)
				gDLL->getInterfaceIFace()->addMessage(GC.getGameINLINE().getActivePlayer(), True, iDuration, (CvWString(gDLL->getText("TXT_KEY_STABILITY_IMPROVING")) + " " + szTempBuffer.getCString()).GetCString(), "", 0, "", ColorTypes(iWhite), -1, -1, True, True);
			else if (iValue < iOldStabilityLevel)
				gDLL->getInterfaceIFace()->addMessage(GC.getGame().getActivePlayer(), True, iDuration, (CvWString(gDLL->getText("TXT_KEY_STABILITY_WORSENING")) + " " + szTempBuffer.getCString()).GetCString(), "", 0, "", ColorTypes(iWhite), -1, -1, True, True);
		*/}
		m_players[iPlayer].m_iStabilityLevel = iValue;
	}

	PlayerTypes getWonderBuilder(BuildingTypes iWonder)
	{
		if (iWonder < iBeginWonders) return NO_PLAYER;
		else iWonder = (BuildingTypes)((int)iWonder - (int)iBeginWonders);
		return m_lWonderBuilder[iWonder];
	}

	void setWonderBuilder(BuildingTypes iWonder, PlayerTypes iPlayer) {
		if (iWonder >= iBeginWonders) {
			iWonder = (BuildingTypes)((int)iWonder - (int)iBeginWonders);
			m_lWonderBuilder[iWonder] = iPlayer;
		}
	}

	bool isFirstWorldColonized(void)
	{
		return (m_iFirstNewWorldColony != -1);
	}

};

#define data	GameData::getInstance()

#endif _CvData_H_
