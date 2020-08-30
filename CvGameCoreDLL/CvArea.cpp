// area.cpp

#include "CvGameCoreDLL.h"
#include "CvArea.h"
#include "CvMap.h"
#include "CvPlot.h"
#include "CvGlobals.h"
#include "CvGameAI.h"
#include "CvPlayerAI.h"
#include "CvTeamAI.h"
#include "CvGameCoreUtils.h"
#include "CvInfos.h"

#include "CvDLLInterfaceIFaceBase.h"

#include "CvRhyes.h" //Rhye

// Public Functions...

CvArea::CvArea()
{
	// wunshare
	InitializeCriticalSectionAndSpinCount(&m_cPlotTypeCacheSection, 4000);

	m_aiUnitsPerPlayer = new int[MAX_PLAYERS];
	m_aiAnimalsPerPlayer = new int[MAX_PLAYERS];
	m_aiCitiesPerPlayer = new int[MAX_PLAYERS];
	m_aiPopulationPerPlayer = new int[MAX_PLAYERS];
	m_aiBuildingGoodHealth = new int[MAX_PLAYERS];
	m_aiBuildingBadHealth = new int[MAX_PLAYERS];
	m_aiBuildingHappiness = new int[MAX_PLAYERS];
	m_aiFreeSpecialist = new int[MAX_PLAYERS];
	m_aiPower = new int[MAX_PLAYERS];
	m_aiBestFoundValue = new int[MAX_PLAYERS];
	//DPII < Maintenance Modifiers >
	m_aiMaintenanceModifier = new int[MAX_PLAYERS];
	m_aiHomeAreaMaintenanceModifier = new int[MAX_PLAYERS];
	m_aiOtherAreaMaintenanceModifier = new int[MAX_PLAYERS];
	m_abHomeArea = new bool[MAX_PLAYERS];
	//DPII < Maintenance Modifiers >
	m_aiNumRevealedTiles = new int[MAX_TEAMS];
	m_aiCleanPowerCount = new int[MAX_TEAMS];
	m_aiBorderObstacleCount = new int[MAX_TEAMS];

	m_aeAreaAIType = new AreaAITypes[MAX_TEAMS];

	m_aTargetCities = new IDInfo[MAX_PLAYERS];

	m_aaiYieldRateModifier = new int*[MAX_PLAYERS];
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_aaiYieldRateModifier[i] = new int[NUM_YIELD_TYPES];
	}
	m_aaiNumTrainAIUnits = new int*[MAX_PLAYERS];
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_aaiNumTrainAIUnits[i] = new int[NUM_UNITAI_TYPES];
	}
	m_aaiNumAIUnits = new int*[MAX_PLAYERS];
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_aaiNumAIUnits[i] = new int[NUM_UNITAI_TYPES];
	}

	m_paiNumBonuses = NULL;
	m_paiNumImprovements = NULL;


	reset(0, false, true);
}


CvArea::~CvArea()
{
	uninit();

	SAFE_DELETE_ARRAY(m_aiUnitsPerPlayer);
	SAFE_DELETE_ARRAY(m_aiAnimalsPerPlayer);
	SAFE_DELETE_ARRAY(m_aiCitiesPerPlayer);
	SAFE_DELETE_ARRAY(m_aiPopulationPerPlayer);
	SAFE_DELETE_ARRAY(m_aiBuildingGoodHealth);
	SAFE_DELETE_ARRAY(m_aiBuildingBadHealth);
	SAFE_DELETE_ARRAY(m_aiBuildingHappiness);
	SAFE_DELETE_ARRAY(m_aiFreeSpecialist);
	SAFE_DELETE_ARRAY(m_aiPower);
	SAFE_DELETE_ARRAY(m_aiBestFoundValue);
	//DPII < Maintenance Modifiers >
	SAFE_DELETE_ARRAY(m_aiMaintenanceModifier);
	SAFE_DELETE_ARRAY(m_aiHomeAreaMaintenanceModifier);
	SAFE_DELETE_ARRAY(m_aiOtherAreaMaintenanceModifier);
	SAFE_DELETE_ARRAY(m_abHomeArea);
	//DPII < Maintenance Modifiers > 
	SAFE_DELETE_ARRAY(m_aiNumRevealedTiles);
	SAFE_DELETE_ARRAY(m_aiCleanPowerCount);
	SAFE_DELETE_ARRAY(m_aiBorderObstacleCount);
	SAFE_DELETE_ARRAY(m_aeAreaAIType);
	SAFE_DELETE_ARRAY(m_aTargetCities);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		SAFE_DELETE_ARRAY(m_aaiYieldRateModifier[i]);
	}
	SAFE_DELETE_ARRAY(m_aaiYieldRateModifier);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		SAFE_DELETE_ARRAY(m_aaiNumTrainAIUnits[i]);
	}
	SAFE_DELETE_ARRAY(m_aaiNumTrainAIUnits);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		SAFE_DELETE_ARRAY(m_aaiNumAIUnits[i]);
	}
	SAFE_DELETE_ARRAY(m_aaiNumAIUnits);
}


void CvArea::init(int iID, bool bWater)
{
	//--------------------------------
	// Init saved data
	reset(iID, bWater);

	//--------------------------------
	// Init non-saved data

	//--------------------------------
	// Init other game data
}


void CvArea::uninit()
{
	SAFE_DELETE_ARRAY(m_paiNumBonuses);
	SAFE_DELETE_ARRAY(m_paiNumImprovements);
}


// FUNCTION: reset()
// Initializes data members that are serialized.
void CvArea::reset(int iID, bool bWater, bool bConstructorCall)
{
	int iI, iJ;

	//--------------------------------
	// Uninit class
	uninit();

	m_iID = iID;
	m_iNumTiles = 0;
	m_iNumOwnedTiles = 0;
	m_iNumRiverEdges = 0;
	m_iNumUnits = 0;
	m_iNumCities = 0;
	m_iTotalPopulation = 0;
	m_iNumStartingPlots = 0;

	m_bWater = bWater;

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		m_aiUnitsPerPlayer[iI] = 0;
		m_aiAnimalsPerPlayer[iI] = 0;
		m_aiCitiesPerPlayer[iI] = 0;
		m_aiPopulationPerPlayer[iI] = 0;
		m_aiBuildingGoodHealth[iI] = 0;
		m_aiBuildingBadHealth[iI] = 0;
		m_aiBuildingHappiness[iI] = 0;
		m_aiFreeSpecialist[iI] = 0;
		m_aiPower[iI] = 0;
		m_aiBestFoundValue[iI] = 0;
		//DPII < Maintenance Modifiers >
		m_aiMaintenanceModifier[iI] = 0;
		m_aiHomeAreaMaintenanceModifier[iI] = 0;
		m_aiOtherAreaMaintenanceModifier[iI] = 0;
		m_abHomeArea[iI] = 0;
		//DPII < Maintenance Modifiers >
	}

	for (iI = 0; iI < MAX_TEAMS; iI++)
	{
		m_aiNumRevealedTiles[iI] = 0;
		m_aiCleanPowerCount[iI] = 0;
		m_aiBorderObstacleCount[iI] = 0;
	}

	for (iI = 0; iI < MAX_TEAMS; iI++)
	{
		m_aeAreaAIType[iI] = NO_AREAAI;
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		m_aTargetCities[iI].reset();
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		for (iJ = 0; iJ < NUM_YIELD_TYPES; iJ++)
		{
			m_aaiYieldRateModifier[iI][iJ] = 0;
		}

		for (iJ = 0; iJ < NUM_UNITAI_TYPES; iJ++)
		{
			m_aaiNumTrainAIUnits[iI][iJ] = 0;
			m_aaiNumAIUnits[iI][iJ] = 0;
		}
	}

	// wunshare: Empty combat record
	m_iLastGameTurnRecorded = -1;
	for (int i = 0; i < COMBAT_RECORD_LENGTH; i++)
	{
		m_combatRecord[i].clear();
	}

	if (!bConstructorCall)
	{
		FAssertMsg((0 < GC.getNumBonusInfos()) && "GC.getNumBonusInfos() is not greater than zero but an array is being allocated in CvArea::reset", "GC.getNumBonusInfos() is not greater than zero but an array is being allocated in CvArea::reset");
		m_paiNumBonuses = new int[GC.getNumBonusInfos()];
		for (iI = 0; iI < GC.getNumBonusInfos(); iI++)
		{
			m_paiNumBonuses[iI] = 0;
		}

		FAssertMsg((0 < GC.getNumImprovementInfos()) && "GC.getNumImprovementInfos() is not greater than zero but an array is being allocated in CvArea::reset", "GC.getNumImprovementInfos() is not greater than zero but an array is being allocated in CvArea::reset");
		m_paiNumImprovements = new int[GC.getNumImprovementInfos()];
		for (iI = 0; iI < GC.getNumImprovementInfos(); iI++)
		{
			m_paiNumImprovements[iI] = 0;
		}
	}

	// wunshare
	m_eCachedTeamPlotTypeCounts = NO_TEAM;
	m_iCachedTurnPlotTypeCounts = -1;
}


int CvArea::getID() const						
{
	return m_iID;
}


void CvArea::setID(int iID)														
{
	m_iID = iID;
}


int CvArea::calculateTotalBestNatureYield() const
{
	CvPlot* pLoopPlot;
	int iCount;
	int iI;

	iCount = 0;

	for (iI = 0; iI < GC.getMapINLINE().numPlotsINLINE(); iI++)
	{
		pLoopPlot = GC.getMapINLINE().plotByIndexINLINE(iI);

		if (pLoopPlot->getArea() == getID())
		{
			iCount += pLoopPlot->calculateTotalBestNatureYield(NO_TEAM);
		}
	}

	return iCount;
}


int CvArea::countCoastalLand() const
{
	CvPlot* pLoopPlot;
	int iCount;
	int iI;

	if (isWater())
	{
		return 0;
	}

	iCount = 0;

	for (iI = 0; iI < GC.getMapINLINE().numPlotsINLINE(); iI++)
	{
		pLoopPlot = GC.getMapINLINE().plotByIndexINLINE(iI);

		if (pLoopPlot->getArea() == getID())
		{
			if (pLoopPlot->isCoastalLand())
			{
				iCount++;
			}
		}
	}

	return iCount;
}


int CvArea::countNumUniqueBonusTypes() const
{
	int iCount;
	int iI;

	iCount = 0;

	for (iI = 0; iI < GC.getNumBonusInfos(); iI++)
	{
		if (getNumBonuses((BonusTypes)iI) > 0)
		{
			if (GC.getBonusInfo((BonusTypes)iI).isOneArea())
			{
				iCount++;
			}
		}
	}

	return iCount;
}


int CvArea::countHasReligion(ReligionTypes eReligion, PlayerTypes eOwner) const
{
	CvCity* pLoopCity;
	int iCount;
	int iLoop;
	int iI;

	iCount = 0;

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		if (GET_PLAYER((PlayerTypes)iI).isAlive())
		{
			if ((eOwner == NO_PLAYER) || (iI == eOwner))
			{
				for (pLoopCity = GET_PLAYER((PlayerTypes)iI).firstCity(&iLoop); pLoopCity != NULL; pLoopCity = GET_PLAYER((PlayerTypes)iI).nextCity(&iLoop))
				{
					if (pLoopCity->area()->getID() == getID())
					{
						if (pLoopCity->isHasReligion(eReligion))
						{
							iCount++;
						}
					}
				}
			}
		}
	}

	return iCount;
}

int CvArea::countCanSpread(ReligionTypes eReligion, PlayerTypes eOwner, bool bMissionary) const
{
	CvCity* pLoopCity;
	int iCount;
	int iLoop;
	int iI;

	iCount = 0;

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		if (GET_PLAYER((PlayerTypes)iI).isAlive())
		{
			if ((eOwner == NO_PLAYER) || (iI == eOwner))
			{
				for (pLoopCity = GET_PLAYER((PlayerTypes)iI).firstCity(&iLoop); pLoopCity != NULL; pLoopCity = GET_PLAYER((PlayerTypes)iI).nextCity(&iLoop))
				{
					if (pLoopCity->area()->getID() == getID())
					{
						if (pLoopCity->canSpread(eReligion, bMissionary))
						{
							iCount++;
						}
					}
				}
			}
		}
	}

	return iCount;
}

int CvArea::countHasCorporation(CorporationTypes eCorporation, PlayerTypes eOwner) const
{
	int iCount = 0;

	for (int iI = 0; iI < MAX_PLAYERS; ++iI)
	{
		if (GET_PLAYER((PlayerTypes)iI).isAlive())
		{
			if ((eOwner == NO_PLAYER) || (iI == eOwner))
			{
				int iLoop;
				for (CvCity* pLoopCity = GET_PLAYER((PlayerTypes)iI).firstCity(&iLoop); NULL != pLoopCity; pLoopCity = GET_PLAYER((PlayerTypes)iI).nextCity(&iLoop))
				{
					if (pLoopCity->area()->getID() == getID())
					{
						if (pLoopCity->isHasCorporation(eCorporation))
						{
							++iCount;
						}
					}
				}
			}
		}
	}

	return iCount;
}


int CvArea::getNumTiles() const
{
	return m_iNumTiles;
}


bool CvArea::isLake() const							
{
	return (isWater() && (getNumTiles() <= GC.getLAKE_MAX_AREA_SIZE()));
}


void CvArea::changeNumTiles(int iChange)
{
	bool bOldLake;

	if (iChange != 0)
	{
		bOldLake = isLake();

		m_iNumTiles = (m_iNumTiles + iChange);
		FAssert(getNumTiles() >= 0);

		if (bOldLake != isLake())
		{
			GC.getMapINLINE().updateIrrigated();
			GC.getMapINLINE().updateYield();
		}
	}
}


int CvArea::getNumOwnedTiles() const
{
	return m_iNumOwnedTiles;
}


int CvArea::getNumUnownedTiles() const
{
	return (getNumTiles() - getNumOwnedTiles());
}


void CvArea::changeNumOwnedTiles(int iChange)									
{
	m_iNumOwnedTiles = (m_iNumOwnedTiles + iChange);
	FAssert(getNumOwnedTiles() >= 0);
	FAssert(getNumUnownedTiles() >= 0);
}


int CvArea::getNumRiverEdges() const												
{
	return m_iNumRiverEdges;
}


void CvArea::changeNumRiverEdges(int iChange)									
{
	m_iNumRiverEdges = (m_iNumRiverEdges + iChange);
	FAssert(getNumRiverEdges() >= 0);
}


int CvArea::getNumUnits() const					
{
	return m_iNumUnits;
}


int CvArea::getNumCities() const					
{
	return m_iNumCities;
}


int CvArea::getTotalPopulation() const					
{
	return m_iTotalPopulation;
}


int CvArea::getNumStartingPlots() const
{
	return m_iNumStartingPlots;
}


void CvArea::changeNumStartingPlots(int iChange)
{
	m_iNumStartingPlots = m_iNumStartingPlots + iChange;
	FAssert(getNumStartingPlots() >= 0);
}


bool CvArea::isWater() const							
{
	return m_bWater;
}


int CvArea::getUnitsPerPlayer(PlayerTypes eIndex) const												
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiUnitsPerPlayer[eIndex];
}


void CvArea::changeUnitsPerPlayer(PlayerTypes eIndex, int iChange)							
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	m_iNumUnits = (m_iNumUnits + iChange);
	FAssert(getNumUnits() >= 0);
	m_aiUnitsPerPlayer[eIndex] = (m_aiUnitsPerPlayer[eIndex] + iChange);
	FAssert(getUnitsPerPlayer(eIndex) >= 0);
}


int CvArea::getAnimalsPerPlayer(PlayerTypes eIndex) const			
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiAnimalsPerPlayer[eIndex];
}


void CvArea::changeAnimalsPerPlayer(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	m_aiAnimalsPerPlayer[eIndex] = (m_aiAnimalsPerPlayer[eIndex] + iChange);
	FAssert(getAnimalsPerPlayer(eIndex) >= 0);
}


int CvArea::getCitiesPerPlayer(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiCitiesPerPlayer[eIndex];
}


void CvArea::changeCitiesPerPlayer(PlayerTypes eIndex, int iChange)							
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	m_iNumCities = (m_iNumCities + iChange);
	FAssert(getNumCities() >= 0);
	m_aiCitiesPerPlayer[eIndex] = (m_aiCitiesPerPlayer[eIndex] + iChange);
	FAssert(getCitiesPerPlayer(eIndex) >= 0);
}


int CvArea::getPopulationPerPlayer(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiPopulationPerPlayer[eIndex];
}


void CvArea::changePopulationPerPlayer(PlayerTypes eIndex, int iChange)							
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	m_iTotalPopulation = (m_iTotalPopulation + iChange);
	FAssert(getTotalPopulation() >= 0);
	m_aiPopulationPerPlayer[eIndex] = (m_aiPopulationPerPlayer[eIndex] + iChange);
	FAssert(getPopulationPerPlayer(eIndex) >= 0);
}


int CvArea::getBuildingGoodHealth(PlayerTypes eIndex) const 
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiBuildingGoodHealth[eIndex];
}


void CvArea::changeBuildingGoodHealth(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (iChange != 0)
	{
		m_aiBuildingGoodHealth[eIndex] = (m_aiBuildingGoodHealth[eIndex] + iChange);
		FAssert(getBuildingGoodHealth(eIndex) >= 0);

		GET_PLAYER(eIndex).AI_makeAssignWorkDirty();
	}
}


int CvArea::getBuildingBadHealth(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiBuildingBadHealth[eIndex];
}


void CvArea::changeBuildingBadHealth(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (iChange != 0)
	{
		m_aiBuildingBadHealth[eIndex] = (m_aiBuildingBadHealth[eIndex] + iChange);
		FAssert(getBuildingBadHealth(eIndex) >= 0);

		GET_PLAYER(eIndex).AI_makeAssignWorkDirty();
	}
}


int CvArea::getBuildingHappiness(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiBuildingHappiness[eIndex];
}


void CvArea::changeBuildingHappiness(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (iChange != 0)
	{
		m_aiBuildingHappiness[eIndex] = (m_aiBuildingHappiness[eIndex] + iChange);

		GET_PLAYER(eIndex).AI_makeAssignWorkDirty();
	}
}


int CvArea::getFreeSpecialist(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiFreeSpecialist[eIndex];
}


void CvArea::changeFreeSpecialist(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (iChange != 0)
	{
		m_aiFreeSpecialist[eIndex] = (m_aiFreeSpecialist[eIndex] + iChange);
		FAssert(getFreeSpecialist(eIndex) >= 0);

		GET_PLAYER(eIndex).AI_makeAssignWorkDirty();
	}
}


int CvArea::getPower(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	//Rhye - start
	if (eIndex == BARBARIAN)
		return m_aiPower[eIndex] /= 2;
	if (eIndex == INDEPENDENT || eIndex == INDEPENDENT2)
		return m_aiPower[eIndex] /= 8;
	if (eIndex >= NUM_MAJOR_PLAYERS)
		return m_aiPower[eIndex] /= 4;
	//Rhye - end
	return m_aiPower[eIndex];
}


void CvArea::changePower(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	int iOldValue;
	// (m_aiPower[eIndex] + iChange < 0) ? 0 : (m_aiPower[eIndex] + iChange)
	// Do this in a thread-safe manner 
	do
	{
		iOldValue = m_aiPower[eIndex];
	} while(InterlockedCompareExchange(
				(volatile LONG*)&m_aiPower[eIndex], 
				(iOldValue + iChange < 0) ? 0 : (iOldValue + iChange), 
				iOldValue) != iOldValue)
	//if (m_aiPower[eIndex] + iChange < 0) iChange = -m_aiPower[eIndex];
	//m_aiPower[eIndex] = (m_aiPower[eIndex] + iChange);
FAssert(getPower(eIndex) >= 0);
}


bool CvArea::hasBestFoundValue(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return (m_aiBestFoundValue[eIndex] != -1);
}

int CvArea::getBestFoundValue(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	iResult = m_aiBestFoundValue[eIndex];

	// wunshare: Calculate on demand
	if (iResult == -1)
	{
		GET_PLAYER(eIndex).AI_updateFoundValues(false, (CvAre*)this);
		iResult = m_aiBestFoundValue[eIndex] == -1;

		if (iResult == -1)
		{
			// No valid found spots in this area
			return 0;
		}
	}
	return iResult;
}


void CvArea::setBestFoundValue(PlayerTypes eIndex, int iNewValue)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	FAssert(iNewValue >= -1); // wunshare
	m_aiBestFoundValue[eIndex] = iNewValue;
	FAssert(getBestFoundValue(eIndex) >= 0);
}

//DPII < Maintenance Modifiers >
int CvArea::getMaintenanceModifier(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be <  MAX_PLAYERS");
	return m_aiMaintenanceModifier[eIndex];
}




int CvArea::getNumRevealedTiles(TeamTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return m_aiNumRevealedTiles[eIndex];
}


int CvArea::getNumUnrevealedTiles(TeamTypes eIndex) const
{
	return (getNumTiles() - getNumRevealedTiles(eIndex));
}


void CvArea::changeNumRevealedTiles(TeamTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	m_aiNumRevealedTiles[eIndex] = (m_aiNumRevealedTiles[eIndex] + iChange);
	FAssert(getNumRevealedTiles(eIndex) >= 0);
}

int CvArea::getNumRevealedFeatureTiles(TeamTypes eIndex, FeatureTypes eFeature) const
{
	EnterCriticalSection(&m_cPlotTypeCacheSection);

	if (m_iCachedTurnPlotTypeCounts != GC.getGameINLINE().getGameTurn() ||
		m_eCachedTeamPlotTypeCounts != eTeam)
	{
		m_plotFeatureCountCache.clear();
		m_plotTerrainCountCache.clear();
	}

	m_iCachedTurnPlotTypeCounts = GC.getGameINLINE().getGameTurn();
	m_eCachedTeamPlotTypeCounts = eTeam;

	std::map<FeatureTypes, int>::const_iterator it = m_plotFeatureCountCache.find(eFeature);

	bool bHaveCachedResult = (it == m_plotFeatureCountCache.end());

	LeaveCriticalSection(&m_cPlotTypeCacheSection);

	if (bHaveCachedResult)
	{
		int iResult = 0;

		for (int iI = 0; iI < GC.getMapINLINE().numPlotsINLINE(); iI++)
		{
			CvPlot* pPlot = GC.getMapINLINE().plotByIndexINLINE(iI);
			if (pPlot != NULL &&
				pPlot->area() == this &&
				pPlot->isRevealed(eTeam, false) &&
				pPlot->getFeatureType() == eFeature)
			{
				iResult++;
			}
		}	
		EnterCriticalSection(&m_cPlotTypeCacheSection);
		m_plotFeatureCountCache.insert(std::make_pair(eFeature, iResult));
		LeaveCriticalSection(&m_cPlotTypeCacheSection);
	}
	else
	{
		return it->second;
	}
	return 0;
}

int CvArea::getNumRevealedTerrainTiles(TeamTypes eIndex, TerrainTypes eTerrain) const
{
	int iResult = 0;

	EnterCriticalSection(&m_cPlotTypeCacheSection);

	if (m_iCachedTurnPlotTypeCounts != GC.getGameINLINE().getGameTurn() ||
		m_eCachedTeamPlotTypeCounts != eTeam)
	{
		m_plotFeatureCountCache.clear();
		m_plotTerrainCountCache.clear();
	}

	m_iCachedTurnPlotTypeCounts = GC.getGameINLINE().getGameTurn();
	m_eCachedTeamPlotTypeCounts = eTeam;

	std::map<TerrainTypes, int>::const_iterator it = m_plotTerrainCountCache.find(eTerrain);

	bool bHaveCachedResult = (it == m_plotTerrainCountCache.end());

	LeaveCriticalSection(&m_cPlotTypeCacheSection);

	if (bHaveCachedResult)
	{
		iResult = it->second;
	}
	else
	{
		iResult = 0;

		for (int iI = 0; iI < GC.getGameINLINE().numPlotsINLINE(); iI++)
		{
			CvPlot* pPlot = GC.getGameINLINE().plotByIndexINLINE(iI);
			if (pPlot != NULL &&
				pPlot->area() == this &&
				pPlot->isRevealed(eTerrain, false) &&
				pPlot->getTerrainType() == eTerrain)
			{
				iResult++
			}
		}

		EnterCriticalSection(&m_cPlotTypeCacheSection);
		m_plotTerrainCountCache.insert(std::make_pair(eTerrain, iResult));
		LeaveCriticalSection(&m_cPlotTypeCacheSection);
	}
	return iResult;
}


int CvArea::getCleanPowerCount(TeamTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");
	return m_aiCleanPowerCount[eIndex];
}


bool CvArea::isCleanPower(TeamTypes eIndex) const
{
	return (getCleanPowerCount(eIndex) > 0);
}


void CvArea::changeCleanPowerCount(TeamTypes eIndex, int iChange)
{
	bool bOldCleanPower;

	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");

	if (iChange != 0)
	{
		bOldCleanPower = isCleanPower(eIndex);

		m_aiCleanPowerCount[eIndex] = (m_aiCleanPowerCount[eIndex] + iChange);

		if (bOldCleanPower != isCleanPower(eIndex))
		{
			GET_TEAM(eIndex).updateCommerce();
			GET_TEAM(eIndex).updatePowerHealth();

			if (eIndex == GC.getGameINLINE().getActiveTeam())
			{
				gDLL->getInterfaceIFace()->setDirty(CityInfo_DIRTY_BIT, true);
			}
		}
	}
}


int CvArea::getBorderObstacleCount(TeamTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");
	return m_aiBorderObstacleCount[eIndex];
}

bool CvArea::isBorderObstacle(TeamTypes eIndex) const
{
	return (getBorderObstacleCount(eIndex) > 0);
}


void CvArea::changeBorderObstacleCount(TeamTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");

	m_aiBorderObstacleCount[eIndex] += iChange;

	if (iChange > 0 && m_aiBorderObstacleCount[eIndex] == iChange)
	{
		GC.getMapINLINE().verifyUnitValidPlot();
	}
}



AreaAITypes CvArea::getAreaAIType(TeamTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");
	return m_aeAreaAIType[eIndex];
}


void CvArea::setAreaAIType(TeamTypes eIndex, AreaAITypes eNewValue)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");
	m_aeAreaAIType[eIndex] = eNewValue;
}


CvCity* CvArea::getTargetCity(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	return getCity(m_aTargetCities[eIndex]);
}


void CvArea::setTargetCity(PlayerTypes eIndex, CvCity* pNewValue)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (pNewValue != NULL)
	{
		m_aTargetCities[eIndex] = pNewValue->getIDInfo();
	}
	else
	{
		m_aTargetCities[eIndex].reset();
	}
}


int CvArea::getYieldRateModifier(PlayerTypes eIndex1, YieldTypes eIndex2) const
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_YIELD_TYPES, "eIndex2 is expected to be < NUM_YIELD_TYPES");
	return m_aaiYieldRateModifier[eIndex1][eIndex2];
}


void CvArea::changeYieldRateModifier(PlayerTypes eIndex1, YieldTypes eIndex2, int iChange)
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_YIELD_TYPES, "eIndex2 is expected to be < NUM_YIELD_TYPES");

	if (iChange != 0)
	{
		m_aaiYieldRateModifier[eIndex1][eIndex2] = (m_aaiYieldRateModifier[eIndex1][eIndex2] + iChange);
		
		GET_PLAYER(eIndex1).invalidateYieldRankCache(eIndex2);

		if (eIndex2 == YIELD_COMMERCE)
		{
			GET_PLAYER(eIndex1).updateCommerce();
		}

		GET_PLAYER(eIndex1).AI_makeAssignWorkDirty();

		if (GET_PLAYER(eIndex1).getTeam() == GC.getGameINLINE().getActiveTeam())
		{
			gDLL->getInterfaceIFace()->setDirty(CityInfo_DIRTY_BIT, true);
		}
	}
}


int CvArea::getNumTrainAIUnits(PlayerTypes eIndex1, UnitAITypes eIndex2) const
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_UNITAI_TYPES, "eIndex2 is expected to be < NUM_UNITAI_TYPES");
	return m_aaiNumTrainAIUnits[eIndex1][eIndex2];
}


void CvArea::changeNumTrainAIUnits(PlayerTypes eIndex1, UnitAITypes eIndex2, int iChange)
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_UNITAI_TYPES, "eIndex2 is expected to be < NUM_UNITAI_TYPES");
	int iOldValue;

	// Do this in a thread-safe manner 
	InterlockedAdd((volatile LONG*)m_aaiNumTrainAIUnits[eIndex1][eIndex2], iChange);
	//m_aaiNumTrainAIUnits[eIndex1][eIndex2] = (m_aaiNumTrainAIUnits[eIndex1][eIndex2] + iChange);
	FAssert(getNumTrainAIUnits(eIndex1, eIndex2) >= 0);
}


int CvArea::getNumAIUnits(PlayerTypes eIndex1, UnitAITypes eIndex2) const
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_UNITAI_TYPES, "eIndex2 is expected to be < NUM_UNITAI_TYPES");
	return m_aaiNumAIUnits[eIndex1][eIndex2];
}


void CvArea::changeNumAIUnits(PlayerTypes eIndex1, UnitAITypes eIndex2, int iChange)
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_UNITAI_TYPES, "eIndex2 is expected to be < NUM_UNITAI_TYPES");
	m_aaiNumAIUnits[eIndex1][eIndex2] = (m_aaiNumAIUnits[eIndex1][eIndex2] + iChange);
	FAssert(getNumAIUnits(eIndex1, eIndex2) >= 0);
}


int CvArea::getNumBonuses(BonusTypes eBonus) const
{
	FAssertMsg(eBonus >= 0, "eBonus expected to be >= 0");
	FAssertMsg(eBonus < GC.getNumBonusInfos(), "eBonus expected to be < GC.getNumBonusInfos");
	return m_paiNumBonuses[eBonus];
}


int CvArea::getNumTotalBonuses() const
{
	int iTotal = 0;

	for (int iI = 0; iI < GC.getNumBonusInfos(); iI++)
	{
		iTotal += m_paiNumBonuses[iI];
	}

	return iTotal;
}


void CvArea::changeNumBonuses(BonusTypes eBonus, int iChange)					
{
	FAssertMsg(eBonus >= 0, "eBonus expected to be >= 0");
	FAssertMsg(eBonus < GC.getNumBonusInfos(), "eBonus expected to be < GC.getNumBonusInfos");
	m_paiNumBonuses[eBonus] = (m_paiNumBonuses[eBonus] + iChange);
	FAssert(getNumBonuses(eBonus) >= 0);
}


int CvArea::getNumImprovements(ImprovementTypes eImprovement) const
{
	FAssertMsg(eImprovement >= 0, "eImprovement expected to be >= 0");
	FAssertMsg(eImprovement < GC.getNumImprovementInfos(), "eImprovement expected to be < GC.getNumImprovementInfos");
	return m_paiNumImprovements[eImprovement];
}


void CvArea::changeNumImprovements(ImprovementTypes eImprovement, int iChange)	
{
	FAssertMsg(eImprovement >= 0, "eImprovement expected to be >= 0");
	FAssertMsg(eImprovement < GC.getNumImprovementInfos(), "eImprovement expected to be < GC.getNumImprovementInfos");
	m_paiNumImprovements[eImprovement] = (m_paiNumImprovements[eImprovement] + iChange);
	FAssert(getNumImprovements(eImprovement) >= 0);
}


int CvArea::getClosestAreaSize(int iSize) const
{
	if (getNumTiles() > iSize)
	{
		return getID();
	}

	int iCurrentDistance;
	CvPlot* pCurrentPlot;
	CvPlot* pLoopPlot;
	int iClosestArea = -1;
	int iClosestDistance = MAX_INT;
	
	for (int iI = 0; iI < GC.getMapINLINE().numPlotsINLINE(); iI++)
	{
		pCurrentPlot = GC.getMapINLINE().plotByIndex(iI);

		if (pCurrentPlot->getArea() == getID())
		{
			for (int iJ = 0; iJ < GC.getMapINLINE().numPlotsINLINE(); iJ++)
			{
				pLoopPlot = GC.getMapINLINE().plotByIndex(iJ);

				if (pLoopPlot->getArea() != getID() && !pLoopPlot->isWater() && GC.getMapINLINE().getArea(pLoopPlot->getArea())->getNumTiles() > iSize)
				{
					iCurrentDistance = stepDistance(pCurrentPlot->getX(), pCurrentPlot->getY(), pLoopPlot->getX(), pLoopPlot->getY());

					if (iCurrentDistance < iClosestDistance)
					{
						iClosestDistance = iCurrentDistance;
						iClosestArea = pLoopPlot->getArea();
					}
				}
			}
		}
	}

	return iClosestArea;
}

void CvArea::clearModifierTotals(void)
{
	int iI;

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		m_aiBuildingGoodHealth[iI] = 0;
		m_aiBuildingBadHealth[iI] = 0;
		m_aiBuildingHappiness[iI] = 0;
		m_aiFreeSpecialist[iI] = 0;
		m_aiPower[iI] = 0;
		//DPII < Maintenance Modifiers >
		m_aiMaintenanceModifier[iI] = 0;
		m_aiHomeAreaMaintenanceModifier[iI] = 0;
		m_aiOtherAreaMaintenanceModifier[iI] = 0;
		//DPII < Maintenance Modifiers >
	}

	for (iI = 0; iI < MAX_TEAMS; iI++)
	{
		m_aiCleanPowerCount[iI] = 0;
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		for (int iJ = 0; iJ < NUM_YIELD_TYPES; iJ++)
		{
			m_aaiYieldRateModifier[iI][iJ] = 0;
		}
	}
}


void CvArea::read(FDataStreamBase* pStream)
{
	int iI;

	CvTaggedSaveFormatWrapper& wrapper = CvTaggedSaveFormatWrapper::getSaveFormatWrapper();

	wrapper.AttachToStream(pStream);

	WRAPPER_READ_OBJECT_START(wrapper);

	// Init saved data
	reset();

	uint uiFlag=0;
	WRAPPER_READ(wrapper, "CvArea", &uiFlag);	// flags for expansion

	WRAPPER_READ(wrapper, "CvArea", &m_iID);
	WRAPPER_READ(wrapper, "CvArea", &m_iNumTiles);
	WRAPPER_READ(wrapper, "CvArea", &m_iNumOwnedTiles);
	WRAPPER_READ(wrapper, "CvArea", &m_iNumRiverEdges);
	WRAPPER_READ(wrapper, "CvArea", &m_iNumUnits);
	WRAPPER_READ(wrapper, "CvArea", &m_iNumCities);
	WRAPPER_READ(wrapper, "CvArea", &m_iTotalPopulation);
	WRAPPER_READ(wrapper, "CvArea", &m_iNumStartingPlots);

	WRAPPER_READ(wrapper, "CvArea", &m_bWater);

	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiUnitsPerPlayer);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiAnimalsPerPlayer);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiCitiesPerPlayer);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiPopulationPerPlayer);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiBuildingGoodHealth);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiBuildingBadHealth);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiBuildingHappiness);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiFreeSpecialist);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiPower);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiBestFoundValue);
	//DPII < Maintenance Modifiers >
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiMaintenanceModifier);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiHomeAreaMaintenanceModifier);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_aiOtherAreaMaintenanceModifier);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_PLAYERS, m_abHomeArea);
	//DPII < Maintenance Modifiers >
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_TEAMS, m_aiNumRevealedTiles);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_TEAMS, m_aiCleanPowerCount);
	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_TEAMS, m_aiBorderObstacleCount);

	WRAPPER_READ_ARRAY(wrapper, "CvArea", MAX_TEAMS, (int*)m_aeAreaAIType);

	for (iI=0;iI<MAX_PLAYERS;iI++)
	{
		WRAPPER_READ(wrapper, "CvArea", (int*)&m_aTargetCities[iI].eOwner);
		WRAPPER_READ(wrapper, "CvArea", &m_aTargetCities[iI].iID);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		WRAPPER_READ_ARRAY(wrapper, "CvArea", NUM_YIELD_TYPES, m_aaiYieldRateModifier[iI]);
	}
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		WRAPPER_READ_OPTIONAL_CLASS_ARRAY(wrapper, "CvArea", REMAPPED_CLASS_TYPE_UNITAIS, NUM_UNITAI_TYPES, m_aaiNumTrainAIUnits[iI]);
	}
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		WRAPPER_READ_OPTIONAL_CLASS_ARRAY(wrapper, "CvArea", REMAPPED_CLASS_TYPE_UNITAIS, NUM_UNITAI_TYPES, m_aaiNumAIUnits[iI]);
	}

	WRAPPER_READ_CLASS_ARRAY(wrapper, "CvArea", REMAPPED_CLASS_TYPE_BONUSES, GC.getNumBonusInfos(), m_paiNumBonuses);
	WRAPPER_READ_CLASS_ARRAY(wrapper, "CvArea", REMAPPED_CLASS_TYPE_IMPROVEMENTS, GC.getNumImprovementInfos(), m_paiNumImprovements);

	WRAPPER_READ(wrapper, "CvArea", &m_iLastGameTurnRecorded);
	for (int iI = 0; iI < COMBAT_RECORD_LENGTH; iI++)
	{
		TurnCombatResult& trunRecord = m_combatRecord[iI];
		int numRecords = 0;

		WRAPPER_READ(wrapper, "CvArea", &numRecords);

		for (int iJ = 0; iJ < numRecords; iJ++)
		{
			CombatResultRecord record;

			WRAPPER_READ(wrapper, "CvArea", (int*)&record.eLoser);
			WRAPPER_READ_CLASS_ENUM(wrapper, "CvArea", REMAPPED_CLASS_TYPE_UNITS, (int*)&record.eDefeatedUnitType);
			WRAPPER_READ_CLASS_ENUM(wrapper, "CvArea", REMAPPED_CLASS_TYPE_UNITS, (int*)&record.eVictoriousEnemyUnitType);
		
			trunRecord.push_back(record);
		}
	}

	WRAPPER_READ_OBJECT_END(wrapper);
}


void CvArea::write(FDataStreamBase* pStream)
{
	int iI;

	CvTaggedSaveFormatWrapper& wrapper = CvTaggedSaveFormatWrapper::getSaveFormatWrapper();

	wrapper.AttachToStream(pStream);

	WRAPPER_WRITE_OBJECT_START(wrapper);

	uint uiFlag=0;
	WRAPPER_WRITE(warpper, "CvArea", uiFlag);		// flag for expansion

	WRAPPER_WRITE(warpper, "CvArea", m_iID);
	WRAPPER_WRITE(warpper, "CvArea", m_iNumTiles);
	WRAPPER_WRITE(warpper, "CvArea", m_iNumOwnedTiles);
	WRAPPER_WRITE(warpper, "CvArea", m_iNumRiverEdges);
	WRAPPER_WRITE(warpper, "CvArea", m_iNumUnits);
	WRAPPER_WRITE(warpper, "CvArea", m_iNumCities);
	WRAPPER_WRITE(warpper, "CvArea", m_iTotalPopulation);
	WRAPPER_WRITE(warpper, "CvArea", m_iNumStartingPlots);

	WRAPPER_WRITE(warpper, "CvArea", m_bWater);

	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiUnitsPerPlayer);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiAnimalsPerPlayer);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiCitiesPerPlayer);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiPopulationPerPlayer);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiBuildingGoodHealth);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiBuildingBadHealth);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiBuildingHappiness);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiFreeSpecialist);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiPower);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiBestFoundValue);
	//DPII < Maintenance Modifiers >
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiMaintenanceModifier);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiHomeAreaMaintenanceModifier);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_aiOtherAreaMaintenanceModifier);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_PLAYERS, m_abHomeArea);
	//DPII < Maintenance Modifiers >
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_TEAMS, m_aiNumRevealedTiles);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_TEAMS, m_aiCleanPowerCount);
	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_TEAMS, m_aiBorderObstacleCount);

	WRAPPER_WRITE_ARRAY(warpper, "CvArea", MAX_TEAMS, (int*)m_aeAreaAIType);

	for (iI=0;iI<MAX_PLAYERS;iI++)
	{
		WRAPPER_WRITE(warpper, "CvArea", m_aTargetCities[iI].eOwner);
		WRAPPER_WRITE(warpper, "CvArea", m_aTargetCities[iI].iID);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		WRAPPER_WRITE_ARRAY(warpper, "CvArea", NUM_YIELD_TYPES, m_aaiYieldRateModifier[iI]);
	}
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		WRAPPER_WRITE_CLASS_ARRAY(warpper, "CvArea", REMAPPED_CLASS_TYPE_UNITAIS, NUM_UNITAI_TYPES, m_aaiNumTrainAIUnits[iI]);
	}
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		WRAPPER_WRITE_CLASS_ARRAY(warpper, "CvArea", REMAPPED_CLASS_TYPE_UNITAIS, NUM_UNITAI_TYPES, m_aaiNumAIUnits[iI]);
	}
	WRAPPER_WRITE_CLASS_ARRAY(warpper, "CvArea", REMAPPED_CLASS_TYPE_BONUSES, GC.getNumBonusInfos(), m_paiNumBonuses);
	WRAPPER_WRITE_CLASS_ARRAY(warpper, "CvArea", REMAPPED_CLASS_TYPE_IMPROVEMENTS, GC.getNumImprovementInfos(), m_paiNumImprovements);

	WRAPPER_WRITE(wrapper, "CvArea", m_iLastGameTurnRecorded);
	for (int iI = 0; iI < COMBAT_RECORD_LENGTH; iI++)
	{
		TurnCombatResult& turnRecord = m_combatRecord[iI];
		int numRecords = turnRecord.size();

		WRAPPER_WRITE(wrapper, "CvArea", numRecords);

		for (int iJ = 0; iJ < numRecords; iJ++)
		{
			CombatResultRecord& record = turnRecord[iJ];

			WRAPPER_WRITE(wrapper, "CvArea", record.eLoser);
			WRAPPER_WRITE_CLASS_ENUM(wrapper, "CvArea", REMAPPED_CLASS_TYPE_UNITS, record.eDefeatedUnitType);
			WRAPPER_WRITE_CLASS_ENUM(wrapper, "CvArea", REMAPPED_CLASS_TYPE_UNITS, record.eVictoriousEnemyUnitType);
		}
	}

	WRAPPER_WRITE_OBJECT_END(wrapper);
}

void CvArea::resync(bool bWrite, ByteBuffer * pBuffer)
{
	RESYNC_INT(bWrite, pBuffer, m_iID);
	RESYNC_INT(bWrite, pBuffer, m_iNumTiles);
	RESYNC_INT(bWrite, pBuffer, m_iNumOwnedTiles);
	RESYNC_INT(bWrite, pBuffer, m_iNumRiverEdges);
	RESYNC_INT(bWrite, pBuffer, m_iNumUnits);
	RESYNC_INT(bWrite, pBuffer, m_iNumCities);
	RESYNC_INT(bWrite, pBuffer, m_iTotalPopulation);
	RESYNC_INT(bWrite, pBuffer, m_iNumStartingPlots);

	RESYNC_BOOL(bWrite, pBuffer, m_bWater);

	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiUnitsPerPlayer);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiAnimalsPerPlayer);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiCitiesPerPlayer);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiPopulationPerPlayer);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiBuildingGoodHealth);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiBuildingBadHealth);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiBuildingHappiness);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiFreeSpecialist);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiPower);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiBestFoundValue);
	//DPII < Maintenance Modifiers >
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiMaintenanceModifier);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiHomeAreaMaintenanceModifier);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_aiOtherAreaMaintenanceModifier);
	RESYNC_BOOL_ARRAY(bWrite, pBuffer, MAX_PLAYERS, m_abHomeArea);
	//DPII < Maintenance Modifiers >
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_TEAMS, m_aiNumRevealedTiles);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_TEAMS, m_aiCleanPowerCount);
	RESYNC_INT_ARRAY(bWrite, pBuffer, MAX_TEAMS, m_aiBorderObstacleCount);

	RESYNC_INT_ARRAY_WITH_CAST(bWrite, pBuffer, MAX_TEAMS, m_aeAreaAIType, AreaAITypes);

for (int iI = 0; iI < MAX_PLAYERS; iI++)
{
	RESYNC_INT_ARRAY_WITH_CAST(bWrite, pBuffer, m_aTargetCities[iI].eOwner, PlayerTypes);
	RESYNC_INT(bWrite, pBuffer, m_aTargetCities[iI].iID);
}
for (int iI = 0; iI < MAX_PLAYERS; iI++)
{
	RESYNC_INT_ARRAY(bWrite, pBuffer, NUM_YIELD_TYPES, m_aaiYieldRateModifier[iI]);
}
for (int iI = 0; iI < MAX_PLAYERS; iI++)
{
	RESYNC_INT_ARRAY(bWrite, pBuffer, NUM_UNITAI_TYPES, m_aaiNumTrainAIUnits[iI]);
}
for (int iI = 0; iI < MAX_PLAYERS; iI++)
{
	RESYNC_INT_ARRAY(bWrite, pBuffer, NUM_UNITAI_TYPES, m_aaiNumAIUnits[iI]);
}
RESYNC_OPTIONAL_ARRAY(bWrite, pBuffer, GC.getNumBonusInfos(), m_paiNumBonuses, int);
RESYNC_OPTIONAL_ARRAY(bWrite, pBuffer, GC.getNumImprovementInfos(), m_paiNumImprovements, int);

RESYNC_INT(bWrite, pBuffer, m_iLastGameTurnRecorded);
for (int iI = 0; iI < COMBAT_RECORD_LENGTH; iI++)
{
TurnCombatResult& turnRecord = m_combatRecord[iI];
int numRecords;

if (bWrite)
{
	numRecords = turnRecord.size();
	pBuffer->putInf(numRecords);
}
else
{
	numRecords = pBuffer->getInt();
	turnRecord.clear();
}

for (int iJ = 0; iJ < numRecords; iJ++)
{
	if (bWrite)
	{
		CombatResultRecord& record = turnRecord[iJ];

		if (bWrite) pBuffer->putInt(record.eLoser);
		if (bWrite) pBuffer->putInt(record.eDefeatedUnitType);
		if (bWrite) pBuffer->putInt(record.eVictoriousEnemyUnitType);
	}
	else
	{
		CombatResultRecord record;

		record.eLoser = (PlayerTypes)pBuffer->getInt();
		record.eDefeatedUnitType = (UnitTypes)pBuffer->getInt();
		record.eVictoriousEnemyUnitType = (UnitTypes)pBuffer->getInt();
		turnRecord.push_back(record);
	}
}
}
}

// Protected Functions...

// Koshling - record rolling history of the last N turns of our combat losses and what we lost to
void CvArea::recordCombatDeath(PlayerTypes ePlayer, UnitTypes lostUnitType, UnitTypes lostToUnitTypes)
{
	MEMORY_TRACK_EXEMPT();

	CombatResultRecord record;

	record.eLoser = ePlayer;
	record.eDefeatedUnitType = lostUnitType;
	record.eVictoriousEnemyUnitType = lostToUnitTypes;

	if (m_iLastGameTurnRecorded == -1)
	{
		m_iLastGameTurnRecorded = GC.getGame().getGameTurn();
	}
	else
	{
		while (m_iLastGameTurnRecorded != GC.getGame().getGameTurn())
		{
			m_combatRecord[++m_iLastGameTurnRecorded % COMBAT_RECORD_LENGTH].clear();
		}
	}

	m_combatRecord[m_iLastGameTurnRecorded % COMBAT_RECORD_LENGTH].push_back(record);
}

// Return the number of units of the specified type recently lost per 100 tuns (normalized figure)
// If eUnit is NO_UNIT all types will be tallied
int CvArea::getRecentCombatDeathRate(PlayerTypes ePlayer, UnitTypes eUnit) const
{
	int totalDeaths = 0;

	for (int i = 0; i < COMBAT_RECORD_LENGTH; i++)
	{
		const TurnCombatResult& turnResults = m_combatRecord[i % COMBAT_RECORD_LENGTH];

		for (std::vector<CombatResultRecord>::const_iterator it = turnResults.begin(); it != turnResults.end(); ++it)
		{
			if ((*it).eLoser == ePlayer && (eUnit == NO_UNIT || (*it).eDefeatedUnitType == eUnit))
			{
				totalDeaths++;
			}
		}
	}
	return (100 * totalDeaths) / COMBAT_RECORD_LENGTH;
}

// Return the number of units the specified type recently lost per 100 turns (normalized figure)
// If eUnit is NO_UNIT all types will be tallied
int CvArea::getRecentCombatDeathRate(PlayerTypes ePlayer, UnitAITypes eUnitAIType) const
{
	int totalDeaths = 0;

	for (int i = 0 i < COMBAT_RECORD_LENGTH; i++)
	{
		const TurnCombatResult& turnResults = m_combatRecord[i % COMBAT_RECORD_LENGTH];

		for (std::vector<CombatResultRecord>::const_iterator it = turnResults.begin(); it != turnResults.end(); ++it)
		{
			if ((*it).eLoser == ePlayer && (eUnitAIType == NO_UNITAI || (*it).eDefeatedUnitType != NO_UNIT && GC.getUnitInfo((*it).eDefeatedUnitType).getDefaultUnitAIType() == eUnitAIType)))
			{
				totalDeaths++;
			}
		}
	}
	return (100*totalDeaths)/COMBAT_RECORD_LENGTH;
}

