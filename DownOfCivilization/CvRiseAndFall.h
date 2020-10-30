#pragma once

#include "CvGameCoreDLL.h"
#include "config_pymodules.h"
#include "config_py2cpp.h"

class CvRiseAndFall 
{
	void setup(void);

	void initScenario(void);
	void updateExtraOptions(void);
	void invalidateUHVs(void);

	void updateGreatWall(void);
	void prepareColonists(void);

	void updateStartingPlots(void);

	// 文化
	void adjustCityCulture(void);
	void adjust1700ADculture(void);

	// 外交
	void init1700ADDiplomacy(void);
	void changeAttitudeExtra(PlayerTypes iPlayer1, PlayerTypes iPlayer2, int iValue);

	void foundCapitals(void);
	void flipStartingTerritory(void);
	void startingFlip(PlayerTypes iPlayer, std::vector<Regions>& lRegionList);

	// 奇观
	void adjust600ADWonders(void);
	void adjust1700ADWonders(void);
	void expireWonders(std::vector<BuildingTypes>& lWonders);
	// 伟人
	void adjust600ADGreatPeople(void);
	void adjust1700ADGreatPeople(void);

	void setupBirthTurnModifiers(void);
	void placeGoodyHuts(void);
	// 宗教
	void adjustReligionFoundingDates(void);
	void initStartingReligions(void);

	// 特殊处理：中华
	void prepareChina(void);
	// 特殊处理：阿拉伯
	void arabianSpwan(void);
	// 特殊处理：普鲁士
	void germanSpawn(void);
	// 特殊处理：神罗
	void holyRomanSpawn(void);
	// 诞生条件检测
	void determineEnablePlayers(void);

	void checkTurn(int iGameTurn);
	void endTurn(PlayerTypes iPlayer);

	void rebirthFirstTurn(PlayerTypes iCiv);
	void rebirthSecondTurn(PlayerTypes iCiv);

	void checkPlayerTurn(int iGameTurn, PlayerTypes iPlayer);

	void fragmentIndependents(void);
	void fragmentBarbarians(int iGameTurn);
	
	void secession(int iGameTurn);

	void initBirth(int iCurrentTurn, int iBirthYear, PlayerTypes iCiv);

	void moveOutInvaders(coord tTl, coord tBR);

	void deleteMode(PlayerTypes iCurrentPlayer);

	void birthInFreeRegion(PlayerTypes iCiv, coord tCapital, coord tTL, coord tBR);
	void birthInForeignBorders(PlayerTypes iCiv, coord tTL, coord tBR, coord tBorderTL, coord tBorderBR);
	void birthInCapital(PlayerTypes iCiv, PlayerTypes iPreviousOwner, coord tCapital, coord tTL, coord tBR);

	void getConvertedCities(PlayerTypes iPlayer, std::vector<coord >& lPlots);
	void convertSurroundingCities(PlayerTypes iPlayer, std::vector<coord >& lPlots);

	void warOnSpawn(PlayerTypes iPlayer, std::vector<PlayerTypes>& lEnemies);
	void spawnAdditionalUnits(PlayerTypes iPlayer);
	void convertSurroundingPlotCulture(PlayerTypes iCiv, std::vector<coord >& lPlots);
	
	void findSeaPlots(coord tCoords, int iRange, PlayerTypes iCiv);
	void giveRaiders(PlayerTypes iCiv, std::vector<coord >& lPlots);
	void giveEarlyColonists(PlayerTypes iCiv);
	void giveColonists(PlayerTypes iCiv);
	
	void onFirstContact(TeamTypes iTeamX, TeamTypes iHasMetTeamY);
	
	void lateTradingCompany(PlayerTypes iCiv);
	void earlyTradingCompany(PlayerTypes iCiv);

	void onRailroadDiscovered(PlayerTypes iCiv);

	void handleColonialAcquistion(PlayerTypes iPlayer);
	void handleColonialConquest(PlayerTypes iPlayer);

	void startWarsOnSpawn(PlayerTypes iCiv, bool bRespawn);

	void immuneMode(std::vector<CvUnit*>& pWinningUnit, std::vector<CvUnit*>& pLosingUnit);
	
	void initMinorBetrayal(PlayerTypes iCiv);
	void initBetrayal(void);
	void unitsBetrayal(PlayerTypes iNewOnwer, PlayerTypes iOldOwner, std::vector<coord >& lPlots, coord tPlot);

	void createAdditionalUnits(PlayerTypes iCiv, coord tPlot);
	void createStartingUnits(PlayerTypes iCiv, coord tPlot);
	void createRespawnUnits(PlayerTypes iCiv, coord tPlot);

	void findAreaReligion(PlayerTypes iPlayer, std::vector<coord >& lPlots);
	
	void createStartingWorkers(PlayerTypes iCiv, coord tPlot);

	void create1700ADStartingUnits(void);
	void create600ADStartingUnits(void);
	void create400BCStartingUnits(void);

	void assignTechs(PlayerTypes iPlayer);
	void placeHut(coord tTL, coord tBR);
	void setStateReligon(PlayerTypes iCiv);
};