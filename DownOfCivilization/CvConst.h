// CvConsts.h
#pragma once
#ifndef _CvConst_H_
#define _CvConst_H_

#include "CvEnums.h"
//#include "CvString.h"

#include "config_py2cpp.h"

#define NUM_PLAYERS 		((int)iNumPlayers)

#define iWorldX 	(150)
#define iWorldY		(80)

// initialize player variables to player IDs from WBS

#define iHolland 		iNetherlands
#define iDelhi			iMughals
#define iSiam			iThailand
#define iPhoenicia		iCarthage
#define iTunisia		iCarthage
#define iHRE			iHolyRome
#define iAustria		iHolyRome
#define iPrussia		iGermany
#define iSouthAfrica	iBoers
#define iMyanmar		iBurma
#define iSudan			iNubia
#define iKazakh			iKhazars

// civilizations, not players
	
#define iCivCongo 			iCivKongo
#define iCivAztecs 			iCivAztec
#define iCivCeltia 			iCivCelt
#define iCivSouthAfrica		iCivBoers
#define iCivKazakhs			iCivKhazars

#define iNumMajorPlayers	iNumPlayers
#define iNumActivePlayers	iNumPlayers

// for Victory and the handler
#define tAmericasTL 		std::make_pair(3, 0)
#define tAmericasBR 		std::make_pair(43, 63)

// Colombian UP
#define tSouthCentralAmericaTL	std::make_pair(13, 3)
#define tSouthCentralAmericaBR  std::make_pair(43, 39)

// English colonists
#define tCanadaTL  			std::make_pair(10, 49)
#define tCanadaBR			std::make_pair(37, 58)
#define tAustraliaTL 		std::make_pair(103, 5)
#define tAustraliaBR 		std::make_pair(123, 22)

// new capital locations
#define tVienna				std::make_pair(62, 49)
#define tWarsaw 			std::make_pair(65, 52)
#define tStockholm 			std::make_pair(73, 70)
#define tIstanbul 			std::make_pair(80, 55)
#define tBeijing 			std::make_pair(102, 47)
#define tEsfahan 			std::make_pair(81, 41)
#define tHamburg 			std::make_pair(59, 53)
#define tMilan 				std::make_pair(59, 47)
#define tBaghdad 			std::make_pair(77, 40)
#define tMumbai 			std::make_pair(88, 34)
#define tMysore 			std::make_pair(90, 31)

#define tJerusalem			std::make_pair(73, 38)

// for messages
#define iDuration			(14)
#define iWhite				(0)
#define iRed 				(7)
#define iGreen				(8)
#define iBlue				(9)
#define iLightBlue			(10)
#define iYellow				(11)
#define iDarkPink			(12)
#define iLightRed			(20)
#define iPurple				(25)
#define iCyan				(44)
#define iBrown				(55)
#define iOrange				(88)
#define iTan				(90)
#define iLime				(100)

// independent cities
#define iNumMinorCities		(65)

#define lSecondaryCivsSize	(9)
#define lCivBioNewWorldSize	(11)
#define lMongolCivsSize		(4)
#define lGreatPeopleUnitsSize (6)

// scripted conquerors		
#define iNumConquests		(24)

// initialize religion variables to religion indices from XML

// corporations

// initialize tech variables to unit indices from XML

// initialize unit variables to unit indices from XML

// generic
#define iMissionary  		iJewishMissionary 

// initialize bonuses variables to bonuses IDs from WBS

#define iNumBonusVarieties 		(18)
enum VaritiesBonusTypes {
	NO_VARITIES_BONUS = (((int)iNumBonuses) - 1),
	iDyeMurex, iDyeHenna, iSpacesCinnamon, iSpicesNutmeg, iSpicesSaffron,
	iSpicesVanilla, iGemsTurquoise, iGemsDiamonds, iGemsRuby, iGemsSapphire, 
	iGemsEmeralds, iSheepLlama, iSheepBlack, iCowBrown, iPigFurry, 
	iIvoryAfrican, iCitrusOranges, iCrabShrimp 
	// iNumBonuses + iNumBonusVarieties
};

// Buildings

// different from DLL constant because that includes national wonders
#define iBeginWonders  		iGreatSphinx 

 // generic
#define iTemple  			iJewishTemple 
#define iCathedral			iJewishCathedral 
#define iMonastery 			iJewishMonastery 
#define iShrine 			iJewishShrine 

#define iFirstWonder 		iGreatSphinx

#define iPlague 			iNumBuildings
#define iNumBuildingsPlague (iNumBuildings+1)

// Civics

// Specialists

// Stability Levels
enum StabilityLevels 
{
	NO_STABILITY_LEVEL = -1,
	iStabilityCollapsing, iStabilityUnstable, iStabilityShaky, 
	iStabilityStable, iStabilitySolid,
	iNumStabilityLevels // = 5
} ;

// Stability Types
enum StabilityTypes 
{
	NO_STABILITY_TYPE = -1,
	iStabilityExpansion, iStabilityEconomy, iStabilityDomestic, 
	iStabilityForeign, iStabilityMilitary,
	iNumStabilityTypes // = 5
} ;

// Stability Parameters

// regions
enum RegionTypes  {
	NO_REGION = -1,
	rBritain, rIberia, rItaly, rBalkans, rEurope, 
	rScandinavia, rRussia, rAnatolia, rMesopotamia, rArabia, 
	rEgypt, rMaghreb, rPersia, rIndia, rDeccan, 
	rIndochina, rIndonesia, rChina, rKorea, rJapan, 
	rManchuria, rTibet, rCentralAsia, rSiberia, rAustralia, 
	rOceania, rEthiopia, rWestAfrica, rSouthAfrica, rCanada, 
	rAlaska, rUnitedStates, rCaribbean, rMesoamerica, rBrazil, 
	rArgentina, rPeru, rColombia,
	iNumRegions // = 38
};

#define iArea_Europe		(1000)
#define iArea_MiddleEast	(1001)
#define iArea_India			(1002)
#define iArea_EastAsia		(1003)
#define iArea_Africa		(1004)
#define iArea_SouthAmerica	(1005)
#define iArea_NorthAmerica	(1006)

// Projects

// Eras

#define iGrass  			(0)
#define iPlains				(1)
#define iDesert 			(2)
#define iTundra 			(3)
#define iSnow 				(4)
#define iCoast 				(5)
#define iOcean				(6)
#define iTerrainPeak		(7)
#define iTerrainHills		(8)
#define iMarsh				(9)

// Improvements

// feature & terrain

// Plague
#define iImmunity 				(20)

// Victory
#define iVictoryPaganism 		(10)
#define iVictorySecularism 		(11)

// leaders

#define i3000BC			(0) 
#define i600AD			(1)
#define i1700AD			(2)

// Stability overlay and editor
enum PlotStabilityTypes 
{
	NO_PLOT_STABILITY_TYPE = -1,
	iCore, iHistorical, iContest, iForeignCore, iAIForbidden,
	iNumPlotStabilityTypes // = 5
};
	
#define iMaxWarValue 	(12)

enum SpawnTypes 
{
	NO_SPAWN = -1,
	iForcedSpawn, iNoSpawn, iConditionalSpawn,
	iNumSpawnTypes //= 3
};


#define lCivGroups			(CvConst::getInstance().m_lCivGroups)
#define lCivStabilityGruops	(CvConst::getInstance().m_lCivStabilityGruops)
#define lTechGroups			(CvConst::getInstance().m_lTechGroups)
#define lCivBioOldWorld		(CvConst::getInstance().m_lCivBioOldWorld)
#define lCivBioNewWorld		(CvConst::getInstance().m_lCivBioNewWorld)
#define lNeighbours			(CvConst::getInstance().m_lNeighbours)
#define lOlderNeighbours	(CvConst::getInstance().m_lOlderNeighbours)
#define tBirth				(CvConst::getInstance().m_tBirth)
#define tFall				(CvConst::getInstance().m_tFall)
#define dVictoryYears		(CvConst::getInstance().m_dVictoryYears)
#define dRebirth			(CvConst::getInstance().m_dRebirth)
#define dRebirthCiv			(CvConst::getInstance().m_dRebirthCiv)
#define tResurrectionIntervals	(CvConst::getInstance().m_tResurrectionIntervals)
#define lEnemyCivsOnSpawn	(CvConst::getInstance().m_lEnemyCivsOnSpawn)
#define dEnemyCivsOnRespawn (CvConst::getInstance().m_dEnemyCivsOnRespawn)
#define tAggressionLevel 	(CvConst::getInstance().m_tAggressionLevel)
#define tAIStopBirthThreshold 	(CvConst::getInstance().m_tAIStopBirthThreshold)
#define tResurrectionProb 	(CvConst::getInstance().m_tResurrectionProb)
#define tPatienceThreshold 	(CvConst::getInstance().m_tPatienceThreshold)
#define dMaxColonists 		(CvConst::getInstance().m_dMaxColonists)
#define tPersecutionPreference 	(CvConst::getInstance().m_tPersecutionPreference)
#define lCatholicStart 		(CvConst::getInstance().m_lCatholicStart)
#define lGreatPeopleUnits 	(CvConst::getInstance().m_lGreatPeopleUnits)
#define dFemaleGreatPeople 	(CvConst::getInstance().m_dFemaleGreatPeople)
#define StabilityLevelTexts (CvConst::getInstance().m_StabilityLevelTexts)
#define StabilityTypesTexts (CvConst::getInstance().m_StabilityTypesTexts)
#define lNewWorld 			(CvConst::getInstance().m_lNewWorld)
#define lEurope 			(CvConst::getInstance().m_lEurope)
#define lMiddleEast 		(CvConst::getInstance().m_lMiddleEast)
#define lIndia 				(CvConst::getInstance().m_lIndia)
#define lEastAsia 			(CvConst::getInstance().m_lEastAsia)
#define lNorthAfrica 		(CvConst::getInstance().m_lNorthAfrica)
#define lSubSaharanAfrica 	(CvConst::getInstance().m_lSubSaharanAfrica)
#define lOceania 			(CvConst::getInstance().m_lOceania)
#define lAfrica 			(CvConst::getInstance().m_lAfrica)
#define lAsia 				(CvConst::getInstance().m_lAsia)
#define lAmericas 			(CvConst::getInstance().m_lAmericas)
#define mercRegions 		(CvConst::getInstance().m_mercRegions)
#define resurrectionLeaders (CvConst::getInstance().m_resurrectionLeaders)
#define rebirthLeaders 		(CvConst::getInstance().m_rebirthLeaders)
#define tTradingCompanyPlotLists 	(CvConst::getInstance().m_tTradingCompanyPlotLists)
#define lSecondaryCivs 		(CvConst::getInstance().m_lSecondaryCivs)
#define lMongolCivs 		(CvConst::getInstance().m_lMongolCivs)
#define lStabilityColors 	(CvConst::getInstance().m_lStabilityColors)
#define lPresetValues 		(CvConst::getInstance().m_lPresetValues)
#define lWarMapColors	 	(CvConst::getInstance().m_lWarMapColors)
#define lReligionMapColors 	(CvConst::getInstance().m_lReligionMapColors)
#define lReligionMapTexts 	(CvConst::getInstance().m_lReligionMapTexts)
#define lNetworkEvents	 	(CvConst::getInstance().m_lNetworkEvents)
#define lCapitalStart 		(CvConst::getInstance().m_lCapitalStart)


class CvConst
{
public:
	static CvConst& getInstance() {
		static CvConst m_Inst;
		return m_Inst;
	}
	
	~CvConst() { }
	
public:
	std::vector<std::vector<PlayerTypes> >			m_lCivGroups;
	std::vector<std::vector<PlayerTypes> >			m_lCivStabilityGruops;
	std::vector<std::vector<PlayerTypes> >			m_lTechGroups;
	std::vector<PlayerTypes> 						m_lCivBioOldWorld;
	std::vector<PlayerTypes> 						m_lCivBioNewWorld;
	std::vector<std::vector<PlayerTypes> >			m_lNeighbours;
	std::vector<std::vector<PlayerTypes> >			m_lOlderNeighbours;
	std::vector<int>								m_tBirth;
	std::vector<int>								m_tFall;
	std::map<CivilizationTypes, std::vector<int> > m_dVictoryYears;
	std::map<PlayerTypes, int>						m_dRebirth;
	std::map<PlayerTypes, CivilizationTypes>		m_dRebirthCiv;
	std::vector<std::vector<coord > >				m_tResurrectionIntervals;
	std::vector<std::vector<PlayerTypes> > 			m_lEnemyCivsOnSpawn;
	std::map<PlayerTypes, std::vector<PlayerTypes> > 	m_dEnemyCivsOnRespawn;
	std::vector<std::vector<PlayerTypes> > 			m_lTotalWarOnSpawn;
	std::vector<int> 								m_tAggressionLevel;
	std::vector<int>								m_tAIStopBirthThreshold;
	std::vector<int>								m_tResurrectionProb;
	std::vector<int>								m_tPatienceThreshold;
	std::map<PlayerTypes, int>						m_dMaxColonists;
	std::vector<std::vector<ReligionTypes> > 		m_tPersecutionPreference;
	std::vector<PlayerTypes> 						m_lCatholicStart;
	std::vector<PlayerTypes> 						m_lProtestantStart;
	std::vector<UnitTypes>							m_lGreatPeopleUnits;
	std::map<UnitTypes, UnitTypes> 					m_dFemaleGreatPeople;
	std::vector<std::string> 						m_StabilityLevelTexts;
	std::vector<std::string> 						m_StabilityTypesTexts;
	std::vector<RegionTypes> 						m_lNewWorld;
	std::vector<RegionTypes> 						m_lEurope;
	std::vector<RegionTypes>		 				m_lMiddleEast;
	std::vector<RegionTypes> 						m_lIndia;
	std::vector<RegionTypes> 						m_lEastAsia;
	std::vector<RegionTypes> 						m_lNorthAfrica;
	std::vector<RegionTypes> 						m_lSubSaharanAfrica;
	std::vector<RegionTypes> 						m_lSouthAmerica;		
	std::vector<RegionTypes> 						m_lNorthAmerica;
	std::vector<RegionTypes> 						m_lOceania;
	std::vector<RegionTypes> 						m_lAfrica;
	std::vector<RegionTypes> 						m_lAsia;
	std::vector<RegionTypes> 						m_lAmericas;
	std::map<int, std::set<RegionTypes> > 			m_mercRegions;
	std::map<PlayerTypes, LeaderHeadTypes>			m_resurrectionLeaders;
	std::map<PlayerTypes, LeaderHeadTypes> 			m_rebirthLeaders;
	std::vector<std::vector<coord > >				m_tTradingCompanyPlotLists;
	std::vector<PlayerTypes>						m_lSecondaryCivs;
	std::vector<PlayerTypes>						m_lMongolCivs;
	std::vector<CvString> 							m_lStabilityColors;
	std::vector<int>								m_lPresetValues;
	std::vector<std::string>						m_lWarMapColors;
	std::vector<std::string>						m_lReligionMapColors;
	std::vector<std::string>						m_lReligionMapTexts;
	std::map<CvString, int>							m_lNetworkEvents;
	std::vector<PlayerTypes> 						m_lCapitalStart;
	
private:
	CvConst();
};

#endif