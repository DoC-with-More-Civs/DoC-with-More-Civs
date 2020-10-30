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

#ifdef _DAWN_OF_CIVILIZATION_H_
#include "CvAreaMPI.h" //∂ØÃ¨º”‘ÿdll
#endif

// Public Functions...

CvArea::CvArea()
{
#ifdef _DAWN_OF_CIVILIZATION_H_
	m_aiUnitsPerPlayer = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiAnimalsPerPlayer = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiCitiesPerPlayer = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiPopulationPerPlayer = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiBuildingGoodHealth = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiBuildingBadHealth = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiBuildingHappiness = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiFreeSpecialist = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiPower = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiBestFoundValue = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiNumRevealedTiles = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiCleanPowerCount = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));
	m_aiBorderObstacleCount = (int*)malloc(MAX_PLAYERS * (sizeof(int) + CACHE_LINE_LEN));

	m_aeAreaAIType = (AreaAITypes*)malloc(MAX_TEAMS * (sizeof(AreaAITypes) + CACHE_LINE_LEN));

	m_aTargetCities = (IDInfo*)malloc(MAX_PLAYERS * (sizeof(IDInfo) + CACHE_LINE_LEN));

	m_aaiYieldRateModifier = new int*[MAX_PLAYERS];
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_aaiYieldRateModifier[i] = (int*)malloc(NUM_YIELD_TYPES * (sizeof(int) + CACHE_LINE_LEN));
	}
	m_aaiNumTrainAIUnits = new int*[MAX_PLAYERS];
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_aaiNumTrainAIUnits[i] = (int*)malloc(NUM_UNITAI_TYPES * (sizeof(int) + CACHE_LINE_LEN));
	}
	m_aaiNumAIUnits = new int*[MAX_PLAYERS];
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		m_aaiNumAIUnits[i] = (int*)malloc(NUM_UNITAI_TYPES * (sizeof(int) + CACHE_LINE_LEN));
	}

	m_paiNumBonuses = NULL;
	m_paiNumImprovements = NULL;

	reset(0, false, true);

	m_pAreaMPI = new CvAreaMPI(this);
#else
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
#endif
}


CvArea::~CvArea()
{
	uninit();

#ifdef _DAWN_OF_CIVILIZATION_H_
	free(m_aiUnitsPerPlayer); m_aiUnitsPerPlayer = NULL;
	free(m_aiAnimalsPerPlayer); m_aiAnimalsPerPlayer = NULL;
	free(m_aiCitiesPerPlayer); m_aiCitiesPerPlayer = NULL;
	free(m_aiPopulationPerPlayer); m_aiPopulationPerPlayer = NULL;
	free(m_aiBuildingGoodHealth); m_aiBuildingGoodHealth = NULL;
	free(m_aiBuildingBadHealth); m_aiBuildingBadHealth = NULL;
	free(m_aiBuildingHappiness); m_aiBuildingHappiness = NULL;
	free(m_aiFreeSpecialist); m_aiFreeSpecialist = NULL;
	free(m_aiPower); m_aiPower = NULL;
	free(m_aiBestFoundValue); m_aiBestFoundValue = NULL;
	free(m_aiNumRevealedTiles); m_aiNumRevealedTiles = NULL;
	free(m_aiCleanPowerCount); m_aiCleanPowerCount = NULL;
	free(m_aiBorderObstacleCount); m_aiBorderObstacleCount = NULL;
	free(m_aeAreaAIType); m_aeAreaAIType = NULL;
	free(m_aTargetCities); m_aTargetCities = NULL;
	
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		free(m_aaiYieldRateModifier[i]);
	}
	SAFE_DELETE_ARRAY(m_aaiYieldRateModifier);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		free(m_aaiNumTrainAIUnits[i]);
	}
	SAFE_DELETE_ARRAY(m_aaiNumTrainAIUnits);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		free(m_aaiNumAIUnits[i]);
	}
	SAFE_DELETE_ARRAY(m_aaiNumAIUnits);

	delete(m_pAreaMPI); m_pAreaMPI = NULL;
#else
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

#endif
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
#ifdef _DAWN_OF_CIVILIZATION_H_
	free(m_paiNumBonuses); m_paiNumBonuses = NULL;
	free(m_paiNumImprovements); m_paiNumImprovements = NULL;
#else
	SAFE_DELETE_ARRAY(m_paiNumBonuses);
	SAFE_DELETE_ARRAY(m_paiNumImprovements);
#endif
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

#ifdef _DAWN_OF_CIVILIZATION_H_
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		int pos = iI * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
		m_aiUnitsPerPlayer[pos] = 0;
		m_aiAnimalsPerPlayer[pos] = 0;
		m_aiCitiesPerPlayer[pos] = 0;
		m_aiPopulationPerPlayer[pos] = 0;
		m_aiBuildingGoodHealth[pos] = 0;
		m_aiBuildingBadHealth[pos] = 0;
		m_aiBuildingHappiness[pos] = 0;
		m_aiFreeSpecialist[pos] = 0;
		m_aiPower[pos] = 0;
		m_aiBestFoundValue[pos] = 0;
	}

	for (iI = 0; iI < MAX_TEAMS; iI++)
	{
		int pos = iI * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
		m_aiNumRevealedTiles[pos] = 0;
		m_aiCleanPowerCount[pos] = 0;
		m_aiBorderObstacleCount[pos] = 0;
	}

	for (iI = 0; iI < MAX_TEAMS; iI++)
	{
		int pos = iI * (sizeof(AreaAITypes) + CACHE_LINE_LEN) / sizeof(AreaAITypes);
		m_aeAreaAIType[pos] = NO_AREAAI;
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		int pos = iI * (sizeof(IDInfo) + CACHE_LINE_LEN) / sizeof(IDInfo);
		m_aTargetCities[pos].reset();
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		for (iJ = 0; iJ < NUM_YIELD_TYPES; iJ++)
		{
			int pos = iI * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
			m_aaiYieldRateModifier[iI][pos] = 0;
		}

		for (iJ = 0; iJ < NUM_UNITAI_TYPES; iJ++)
		{
			int pos = iI * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
			m_aaiNumTrainAIUnits[iI][pos] = 0;
			m_aaiNumAIUnits[iI][pos] = 0;
		}
	}

	if (!bConstructorCall)
	{
		FAssertMsg((0 < GC.getNumBonusInfos()) && "GC.getNumBonusInfos() is not greater than zero but an array is being allocated in CvArea::reset", "GC.getNumBonusInfos() is not greater than zero but an array is being allocated in CvArea::reset");
		m_paiNumBonuses = (int*)malloc(GC.getNumBonusInfos() * (sizeof(int) + CACHE_LINE_LEN));
		for (iI = 0; iI < GC.getNumBonusInfos(); iI++)
		{
			int pos = iI * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
			m_paiNumBonuses[pos] = 0;
		}

		FAssertMsg((0 < GC.getNumImprovementInfos()) && "GC.getNumImprovementInfos() is not greater than zero but an array is being allocated in CvArea::reset", "GC.getNumImprovementInfos() is not greater than zero but an array is being allocated in CvArea::reset");
		m_paiNumImprovements = (int*)malloc(GC.getNumImprovementInfos() * (sizeof(int) + CACHE_LINE_LEN));
		for (iI = 0; iI < GC.getNumImprovementInfos(); iI++)
		{
			int pos = iI * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
			m_paiNumImprovements[pos] = 0;
		}
	}
#else

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
#endif
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
	int iCount = 0;
	
#ifdef _DAWN_OF_CIVILIZATION_H_
	iCount = m_pAreaMPI->calculateTotalBestNatureYield();
#else
	CvPlot* pLoopPlot;
	int iI;

	for (iI = 0; iI < GC.getMapINLINE().numPlotsINLINE(); iI++)
	{
		pLoopPlot = GC.getMapINLINE().plotByIndexINLINE(iI);

		if (pLoopPlot->getArea() == getID())
		{
			iCount += pLoopPlot->calculateTotalBestNatureYield(NO_TEAM);
		}
	}
#endif

	return iCount;
}


int CvArea::countCoastalLand() const
{
	if (isWater())
	{
		return 0;
	}

	int iCount = 0;

#ifdef _DAWN_OF_CIVILIZATION_H_
	iCount = m_pAreaMPI->countCoastalLand();
#else
	CvPlot* pLoopPlot;
	int iI;
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
#endif

	return iCount;
}


int CvArea::countNumUniqueBonusTypes() const
{
	int iCount = 0;
	
#ifdef _DAWN_OF_CIVILIZATION_H_
	iCount = m_pAreaMPI->countNumUniqueBonusTypes();
#else
	int iI;
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
#endif

	return iCount;
}


int CvArea::countHasReligion(ReligionTypes eReligion, PlayerTypes eOwner) const
{
	int iCount = 0;

#ifdef _DAWN_OF_CIVILIZATION_H_
	iCount = m_pAreaMPI->countHasReligion(eReligion, eOwner);
#else
	CvCity* pLoopCity;
	int iLoop;
	int iI;
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
#endif

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
#ifdef _DAWN_OF_CIVILIZATION_H_
	InterlockedExchangeAdd((long*)&m_iNumRiverEdges, iChange);
#else
	m_iNumRiverEdges = (m_iNumRiverEdges + iChange);
#endif
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
#ifdef _DAWN_OF_CIVILIZATION_H_
	InterlockedExchangeAdd((long*)&m_iNumStartingPlots, iChange);
#else
	m_iNumStartingPlots = m_iNumStartingPlots + iChange;
#endif
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
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiUnitsPerPlayer[pos];
#else
	return m_aiUnitsPerPlayer[eIndex];
#endif
}

void CvArea::changeUnitsPerPlayer(PlayerTypes eIndex, int iChange)							
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	InterlockedExchangeAdd((long*)&m_iNumUnits, iChange);
	FAssert(getNumUnits() >= 0);
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aiUnitsPerPlayer[pos], iChange);
	FAssert(getUnitsPerPlayer(eIndex) >= 0);
#else
	m_iNumUnits = (m_iNumUnits + iChange);
	FAssert(getNumUnits() >= 0);
	m_aiUnitsPerPlayer[eIndex] = (m_aiUnitsPerPlayer[eIndex] + iChange);
	FAssert(getUnitsPerPlayer(eIndex) >= 0);
#endif
}


int CvArea::getAnimalsPerPlayer(PlayerTypes eIndex) const			
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiAnimalsPerPlayer[pos];
#else
	return m_aiAnimalsPerPlayer[eIndex];
#endif
}


void CvArea::changeAnimalsPerPlayer(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aiAnimalsPerPlayer[pos], iChange);
#else
	m_aiAnimalsPerPlayer[eIndex] = (m_aiAnimalsPerPlayer[eIndex] + iChange);
#endif
	FAssert(getAnimalsPerPlayer(eIndex) >= 0);
}


int CvArea::getCitiesPerPlayer(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiCitiesPerPlayer[pos];
#else
	return m_aiCitiesPerPlayer[eIndex];
#endif
}


void CvArea::changeCitiesPerPlayer(PlayerTypes eIndex, int iChange)							
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	InterlockedExchangeAdd((long*)&m_iNumCities, iChange);
	FAssert(getNumCities() >= 0);
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aiCitiesPerPlayer[pos], iChange);
	FAssert(getCitiesPerPlayer(eIndex) >= 0);
#else
	m_iNumCities = (m_iNumCities + iChange);
	FAssert(getNumCities() >= 0);
	m_aiCitiesPerPlayer[eIndex] = (m_aiCitiesPerPlayer[eIndex] + iChange);
	FAssert(getCitiesPerPlayer(eIndex) >= 0);
#endif
}


int CvArea::getPopulationPerPlayer(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiPopulationPerPlayer[pos];
#else
	return m_aiPopulationPerPlayer[eIndex];
#endif
}


void CvArea::changePopulationPerPlayer(PlayerTypes eIndex, int iChange)							
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	InterlockedExchangeAdd((long*)&m_iTotalPopulation, iChange);
	FAssert(getTotalPopulation() >= 0);
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aiPopulationPerPlayer[pos], iChange);
	FAssert(getPopulationPerPlayer(eIndex) >= 0);
#else
	m_iTotalPopulation = (m_iTotalPopulation + iChange);
	FAssert(getTotalPopulation() >= 0);
	m_aiPopulationPerPlayer[eIndex] = (m_aiPopulationPerPlayer[eIndex] + iChange);
	FAssert(getPopulationPerPlayer(eIndex) >= 0);
#endif
}


int CvArea::getBuildingGoodHealth(PlayerTypes eIndex) const 
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiBuildingGoodHealth[pos];
#else
	return m_aiBuildingGoodHealth[eIndex];
#endif
}


void CvArea::changeBuildingGoodHealth(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (iChange != 0)
	{
#ifdef _DAWN_OF_CIVILIZATION_H_
		int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
		InterlockedExchangeAdd((long*)&m_aiBuildingGoodHealth[pos], iChange);
#else
		m_aiBuildingGoodHealth[eIndex] = (m_aiBuildingGoodHealth[eIndex] + iChange);
#endif
		FAssert(getBuildingGoodHealth(eIndex) >= 0);

		GET_PLAYER(eIndex).AI_makeAssignWorkDirty();
	}
}


int CvArea::getBuildingBadHealth(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiBuildingBadHealth[pos];
#else
	return m_aiBuildingBadHealth[eIndex];
#endif
}


void CvArea::changeBuildingBadHealth(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (iChange != 0)
	{
#ifdef _DAWN_OF_CIVILIZATION_H_
		int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
		InterlockedExchangeAdd((long*)&m_aiBuildingBadHealth[pos], iChange);
#else
		m_aiBuildingBadHealth[eIndex] = (m_aiBuildingBadHealth[eIndex] + iChange);
#endif
		FAssert(getBuildingBadHealth(eIndex) >= 0);

		GET_PLAYER(eIndex).AI_makeAssignWorkDirty();
	}
}


int CvArea::getBuildingHappiness(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiBuildingHappiness[pos];
#else
	return m_aiBuildingHappiness[eIndex];
#endif
}


void CvArea::changeBuildingHappiness(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (iChange != 0)
	{
#ifdef _DAWN_OF_CIVILIZATION_H_
		int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
		InterlockedExchangeAdd((long*)&m_aiBuildingHappiness[pos], iChange);
#else
		m_aiBuildingHappiness[eIndex] = (m_aiBuildingHappiness[eIndex] + iChange);
#endif
		GET_PLAYER(eIndex).AI_makeAssignWorkDirty();
	}
}


int CvArea::getFreeSpecialist(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiFreeSpecialist[pos];
#else
	return m_aiFreeSpecialist[eIndex];
#endif
}


void CvArea::changeFreeSpecialist(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");

	if (iChange != 0)
	{
#ifdef _DAWN_OF_CIVILIZATION_H_
		int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
		InterlockedExchangeAdd((long*)&m_aiFreeSpecialist[pos], iChange);
#else
		m_aiFreeSpecialist[eIndex] = (m_aiFreeSpecialist[eIndex] + iChange);
#endif
		FAssert(getFreeSpecialist(eIndex) >= 0);

		GET_PLAYER(eIndex).AI_makeAssignWorkDirty();
	}
}


int CvArea::getPower(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
	
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	if (eIndex == BARBARIAN)
		return m_aiPower[pos] / 2;
	if (eIndex == INDEPENDENT || eIndex == INDEPENDENT2)
		return m_aiPower[pos] /= 8;
	if (eIndex >= NUM_MAJOR_PLAYERS)
		return m_aiPower[pos] /= 4;
	return m_aiPower[pos];
#else
	//Rhye - start
	if (eIndex == BARBARIAN)
			return m_aiPower[eIndex] /= 2;
	if (eIndex == INDEPENDENT || eIndex == INDEPENDENT2)
			return m_aiPower[eIndex] /= 8;
	if (eIndex >= NUM_MAJOR_PLAYERS)
			return m_aiPower[eIndex] /= 4;
	//Rhye - end
	return m_aiPower[eIndex];
#endif
}


void CvArea::changePower(PlayerTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aiPower[pos], (m_aiPower[pos] + iChange < 0 ? -m_aiPower[pos] : iChange));
#else
	if (m_aiPower[eIndex] + iChange < 0) iChange = -m_aiPower[eIndex];
	m_aiPower[eIndex] = (m_aiPower[eIndex] + iChange);
#endif
	FAssert(getPower(eIndex) >= 0);
}


int CvArea::getBestFoundValue(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiBestFoundValue[pos];
#else
	return m_aiBestFoundValue[eIndex];
#endif
}


void CvArea::setBestFoundValue(PlayerTypes eIndex, int iNewValue)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchange((long*)&m_aiBestFoundValue[pos], iNewValue);
#else
	m_aiBestFoundValue[eIndex] = iNewValue;
#endif
	FAssert(getBestFoundValue(eIndex) >= 0);
}


int CvArea::getNumRevealedTiles(TeamTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiNumRevealedTiles[pos];
#else
	return m_aiNumRevealedTiles[eIndex];
#endif
}


int CvArea::getNumUnrevealedTiles(TeamTypes eIndex) const
{
	return (getNumTiles() - getNumRevealedTiles(eIndex));
}


void CvArea::changeNumRevealedTiles(TeamTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aiNumRevealedTiles[pos], iChange);
#else
	m_aiNumRevealedTiles[eIndex] = (m_aiNumRevealedTiles[eIndex] + iChange);
#endif
	FAssert(getNumRevealedTiles(eIndex) >= 0);
}


int CvArea::getCleanPowerCount(TeamTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiCleanPowerCount[pos];
#else
	return m_aiCleanPowerCount[eIndex];
#endif
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
#ifdef _DAWN_OF_CIVILIZATION_H_
		int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
		InterlockedExchangeAdd((long*)&m_aiCleanPowerCount[pos], iChange);
#else
		m_aiCleanPowerCount[eIndex] = (m_aiCleanPowerCount[eIndex] + iChange);
#endif
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
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aiBorderObstacleCount[pos];
#else
	return m_aiBorderObstacleCount[eIndex];
#endif
}

bool CvArea::isBorderObstacle(TeamTypes eIndex) const
{
	return (getBorderObstacleCount(eIndex) > 0);
}


void CvArea::changeBorderObstacleCount(TeamTypes eIndex, int iChange)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aiBorderObstacleCount[pos], iChange);

	if (iChange > 0 && m_aiBorderObstacleCount[pos] == iChange) {
		GC.getMapINLINE().verifyUnitValidPlot();
	}
#else
	m_aiBorderObstacleCount[eIndex] += iChange;

	if (iChange > 0 && m_aiBorderObstacleCount[eIndex] == iChange)
	{
		GC.getMapINLINE().verifyUnitValidPlot();
	}
#endif
}



AreaAITypes CvArea::getAreaAIType(TeamTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aeAreaAIType[pos];
#else
	return m_aeAreaAIType[eIndex];
#endif
}


void CvArea::setAreaAIType(TeamTypes eIndex, AreaAITypes eNewValue)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_TEAMS, "eIndex is expected to be < MAX_TEAMS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eNewValue * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchange((long*)&m_aeAreaAIType[pos], eNewValue);
#else
	m_aeAreaAIType[eIndex] = eNewValue;
#endif
}


CvCity* CvArea::getTargetCity(PlayerTypes eIndex) const
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return getCity(m_aTargetCities[pos]);
#else
	return getCity(m_aTargetCities[eIndex]);
#endif
}


void CvArea::setTargetCity(PlayerTypes eIndex, CvCity* pNewValue)
{
	FAssertMsg(eIndex >= 0, "eIndex is expected to be >= 0");
	FAssertMsg(eIndex < MAX_PLAYERS, "eIndex is expected to be < MAX_PLAYERS");
#ifdef _DAWN_OF_CIVILIZATION_H_
	IDInfo info;
	info.reset();
	int pos = eIndex * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangePointer(&m_aTargetCities[pos], (pNewValue ? &(pNewValue->getIDInfo()) : &info));
#else
	if (pNewValue != NULL)
	{
		m_aTargetCities[eIndex] = pNewValue->getIDInfo();
	}
	else
	{
		m_aTargetCities[eIndex].reset();
	}
#endif
}


int CvArea::getYieldRateModifier(PlayerTypes eIndex1, YieldTypes eIndex2) const
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_YIELD_TYPES, "eIndex2 is expected to be < NUM_YIELD_TYPES");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex2 * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aaiYieldRateModifier[eIndex1][pos];
#else
	return m_aaiYieldRateModifier[eIndex1][eIndex2];
#endif	
}


void CvArea::changeYieldRateModifier(PlayerTypes eIndex1, YieldTypes eIndex2, int iChange)
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_YIELD_TYPES, "eIndex2 is expected to be < NUM_YIELD_TYPES");

	if (iChange != 0)
	{
#ifdef _DAWN_OF_CIVILIZATION_H_
		int pos = eIndex2 * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
		InterlockedExchangeAdd((long*)&m_aaiYieldRateModifier[eIndex1][pos], iChange);
#else
		m_aaiYieldRateModifier[eIndex1][eIndex2] = (m_aaiYieldRateModifier[eIndex1][eIndex2] + iChange);
#endif	
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
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex2 * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aaiNumTrainAIUnits[eIndex1][pos];
#else
	return m_aaiNumTrainAIUnits[eIndex1][eIndex2];
#endif	
}


void CvArea::changeNumTrainAIUnits(PlayerTypes eIndex1, UnitAITypes eIndex2, int iChange)
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_UNITAI_TYPES, "eIndex2 is expected to be < NUM_UNITAI_TYPES");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex2 * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aaiNumTrainAIUnits[eIndex1][pos], iChange);
#else
	m_aaiNumTrainAIUnits[eIndex1][eIndex2] = (m_aaiNumTrainAIUnits[eIndex1][eIndex2] + iChange);
#endif
	FAssert(getNumTrainAIUnits(eIndex1, eIndex2) >= 0);
}


int CvArea::getNumAIUnits(PlayerTypes eIndex1, UnitAITypes eIndex2) const
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_UNITAI_TYPES, "eIndex2 is expected to be < NUM_UNITAI_TYPES");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex2 * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_aaiNumAIUnits[eIndex1][pos];
#else
	return m_aaiNumAIUnits[eIndex1][eIndex2];
#endif	
}


void CvArea::changeNumAIUnits(PlayerTypes eIndex1, UnitAITypes eIndex2, int iChange)
{
	FAssertMsg(eIndex1 >= 0, "eIndex1 is expected to be >= 0");
	FAssertMsg(eIndex1 < MAX_PLAYERS, "eIndex1 is expected to be < MAX_PLAYERS");
	FAssertMsg(eIndex2 >= 0, "eIndex2 is expected to be >= 0");
	FAssertMsg(eIndex2 < NUM_UNITAI_TYPES, "eIndex2 is expected to be < NUM_UNITAI_TYPES");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eIndex2 * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_aaiNumAIUnits[eIndex1][pos], iChange);
#else
	m_aaiNumAIUnits[eIndex1][eIndex2] = (m_aaiNumAIUnits[eIndex1][eIndex2] + iChange);
#endif
	FAssert(getNumAIUnits(eIndex1, eIndex2) >= 0);
}


int CvArea::getNumBonuses(BonusTypes eBonus) const
{
	FAssertMsg(eBonus >= 0, "eBonus expected to be >= 0");
	FAssertMsg(eBonus < GC.getNumBonusInfos(), "eBonus expected to be < GC.getNumBonusInfos");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eBonus * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_paiNumBonuses[pos];
#else
	return m_paiNumBonuses[eBonus];
#endif	
}


int CvArea::getNumTotalBonuses() const
{
	int iTotal = 0;

	for (int iI = 0; iI < GC.getNumBonusInfos(); iI++)
	{
#ifdef _DAWN_OF_CIVILIZATION_H_
		iTotal += getNumBonuses((BonusTypes)iI);
#else
		iTotal += m_paiNumBonuses[iI];
#endif
	}

	return iTotal;
}


void CvArea::changeNumBonuses(BonusTypes eBonus, int iChange)					
{
	FAssertMsg(eBonus >= 0, "eBonus expected to be >= 0");
	FAssertMsg(eBonus < GC.getNumBonusInfos(), "eBonus expected to be < GC.getNumBonusInfos");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eBonus * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_paiNumBonuses[pos], iChange);
#else
	m_paiNumBonuses[eBonus] = (m_paiNumBonuses[eBonus] + iChange);
#endif
	FAssert(getNumBonuses(eBonus) >= 0);
}


int CvArea::getNumImprovements(ImprovementTypes eImprovement) const
{
	FAssertMsg(eImprovement >= 0, "eImprovement expected to be >= 0");
	FAssertMsg(eImprovement < GC.getNumImprovementInfos(), "eImprovement expected to be < GC.getNumImprovementInfos");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eImprovement * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	return m_paiNumImprovements[pos];
#else
	return m_paiNumImprovements[eImprovement];
#endif	
}


void CvArea::changeNumImprovements(ImprovementTypes eImprovement, int iChange)	
{
	FAssertMsg(eImprovement >= 0, "eImprovement expected to be >= 0");
	FAssertMsg(eImprovement < GC.getNumImprovementInfos(), "eImprovement expected to be < GC.getNumImprovementInfos");
#ifdef _DAWN_OF_CIVILIZATION_H_
	int pos = eImprovement * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int);
	InterlockedExchangeAdd((long*)&m_paiNumImprovements[pos], iChange);
#else
	m_paiNumImprovements[eImprovement] = (m_paiNumImprovements[eImprovement] + iChange);
#endif
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


void CvArea::read(FDataStreamBase* pStream)
{
	int iI;

	// Init saved data
	reset();

	uint uiFlag=0;
	pStream->Read(&uiFlag);	// flags for expansion

	pStream->Read(&m_iID);
	pStream->Read(&m_iNumTiles);
	pStream->Read(&m_iNumOwnedTiles);
	pStream->Read(&m_iNumRiverEdges);
	pStream->Read(&m_iNumUnits);
	pStream->Read(&m_iNumCities);
	pStream->Read(&m_iTotalPopulation);
	pStream->Read(&m_iNumStartingPlots);

	pStream->Read(&m_bWater);

#ifdef _DAWN_OF_CIVILIZATION_H_
#define READ_STREAM_MPI(n, pai) \
for (int i = 0; i < n; i++) { \
	int pos = i * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int); \
	pStream->Read((int*)&pai[pos]); \
} 
	READ_STREAM_MPI(MAX_PLAYERS, m_aiUnitsPerPlayer);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiAnimalsPerPlayer);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiCitiesPerPlayer);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiPopulationPerPlayer);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiBuildingGoodHealth);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiBuildingBadHealth);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiBuildingHappiness);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiFreeSpecialist);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiPower);
	READ_STREAM_MPI(MAX_PLAYERS, m_aiBestFoundValue);
	READ_STREAM_MPI(MAX_TEAMS, m_aiNumRevealedTiles);
	READ_STREAM_MPI(MAX_TEAMS, m_aiCleanPowerCount);
	READ_STREAM_MPI(MAX_TEAMS, m_aiBorderObstacleCount);

	READ_STREAM_MPI(MAX_TEAMS, m_aeAreaAIType);

	for (iI = 0;iI < MAX_PLAYERS;iI++) {
		int pos = iI * (sizeof(IDInfo) + CACHE_LINE_LEN) / sizeof(IDInfo);
		pStream->Read((int*)&m_aTargetCities[pos].eOwner);
		pStream->Read(&m_aTargetCities[pos].iID);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++) {
		READ_STREAM_MPI(NUM_YIELD_TYPES, m_aaiYieldRateModifier[iI]);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++) {
		READ_STREAM_MPI(NUM_UNITAI_TYPES, m_aaiNumTrainAIUnits[iI]);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++) {
		READ_STREAM_MPI(NUM_UNITAI_TYPES, m_aaiNumAIUnits[iI]);
	}

	READ_STREAM_MPI(GC.getNumBonusInfos(), m_paiNumBonuses);
	READ_STREAM_MPI(GC.getNumImprovementInfos(), m_paiNumImprovements);

#else
	pStream->Read(MAX_PLAYERS, m_aiUnitsPerPlayer);
	pStream->Read(MAX_PLAYERS, m_aiAnimalsPerPlayer);
	pStream->Read(MAX_PLAYERS, m_aiCitiesPerPlayer);
	pStream->Read(MAX_PLAYERS, m_aiPopulationPerPlayer);
	pStream->Read(MAX_PLAYERS, m_aiBuildingGoodHealth);
	pStream->Read(MAX_PLAYERS, m_aiBuildingBadHealth);
	pStream->Read(MAX_PLAYERS, m_aiBuildingHappiness);
	pStream->Read(MAX_PLAYERS, m_aiFreeSpecialist);
	pStream->Read(MAX_PLAYERS, m_aiPower);
	pStream->Read(MAX_PLAYERS, m_aiBestFoundValue);
	pStream->Read(MAX_TEAMS, m_aiNumRevealedTiles);
	pStream->Read(MAX_TEAMS, m_aiCleanPowerCount);
	pStream->Read(MAX_TEAMS, m_aiBorderObstacleCount);

	pStream->Read(MAX_TEAMS, (int*)m_aeAreaAIType);

	for (iI=0;iI<MAX_PLAYERS;iI++)
	{
		pStream->Read((int*)&m_aTargetCities[iI].eOwner);
		pStream->Read(&m_aTargetCities[iI].iID);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		pStream->Read(NUM_YIELD_TYPES, m_aaiYieldRateModifier[iI]);
	}
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		pStream->Read(NUM_UNITAI_TYPES, m_aaiNumTrainAIUnits[iI]);
	}
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		pStream->Read(NUM_UNITAI_TYPES, m_aaiNumAIUnits[iI]);
	}

	pStream->Read(GC.getNumBonusInfos(), m_paiNumBonuses);
	pStream->Read(GC.getNumImprovementInfos(), m_paiNumImprovements);

#endif
}


void CvArea::write(FDataStreamBase* pStream)
{
	int iI;

	uint uiFlag=0;
	pStream->Write(uiFlag);		// flag for expansion

	pStream->Write(m_iID);
	pStream->Write(m_iNumTiles);
	pStream->Write(m_iNumOwnedTiles);
	pStream->Write(m_iNumRiverEdges);
	pStream->Write(m_iNumUnits);
	pStream->Write(m_iNumCities);
	pStream->Write(m_iTotalPopulation);
	pStream->Write(m_iNumStartingPlots);

	pStream->Write(m_bWater);

#ifdef _DAWN_OF_CIVILIZATION_H_
#define WRITE_STREAM_MPI(n, pai) \
for (int i = 0; i < n; i++) { \
	int pos = i * (sizeof(int) + CACHE_LINE_LEN) / sizeof(int); \
	pStream->Write(pai[pos]); \
} 

	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiUnitsPerPlayer);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiAnimalsPerPlayer);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiCitiesPerPlayer);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiPopulationPerPlayer);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiBuildingGoodHealth);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiBuildingBadHealth);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiBuildingHappiness);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiFreeSpecialist);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiPower);
	WRITE_STREAM_MPI(MAX_PLAYERS, m_aiBestFoundValue);
	WRITE_STREAM_MPI(MAX_TEAMS, m_aiNumRevealedTiles);
	WRITE_STREAM_MPI(MAX_TEAMS, m_aiCleanPowerCount);
	WRITE_STREAM_MPI(MAX_TEAMS, m_aiBorderObstacleCount);
	WRITE_STREAM_MPI(MAX_TEAMS, (int*)m_aeAreaAIType);

	for (iI = 0;iI < MAX_PLAYERS;iI++) {
		int pos = iI * (sizeof(IDInfo) + CACHE_LINE_LEN) / sizeof(IDInfo);
		pStream->Write(m_aTargetCities[pos].eOwner);
		pStream->Write(m_aTargetCities[pos].iID);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++) {
		WRITE_STREAM_MPI(NUM_YIELD_TYPES, m_aaiYieldRateModifier[iI]);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++) {
		WRITE_STREAM_MPI(NUM_UNITAI_TYPES, m_aaiNumTrainAIUnits[iI]);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++) {
		WRITE_STREAM_MPI(NUM_UNITAI_TYPES, m_aaiNumAIUnits[iI]);
	}

	WRITE_STREAM_MPI(GC.getNumBonusInfos(), m_paiNumBonuses);
	WRITE_STREAM_MPI(GC.getNumImprovementInfos(), m_paiNumImprovements);

#else
	pStream->Write(MAX_PLAYERS, m_aiUnitsPerPlayer);
	pStream->Write(MAX_PLAYERS, m_aiAnimalsPerPlayer);
	pStream->Write(MAX_PLAYERS, m_aiCitiesPerPlayer);
	pStream->Write(MAX_PLAYERS, m_aiPopulationPerPlayer);
	pStream->Write(MAX_PLAYERS, m_aiBuildingGoodHealth);
	pStream->Write(MAX_PLAYERS, m_aiBuildingBadHealth);
	pStream->Write(MAX_PLAYERS, m_aiBuildingHappiness);
	pStream->Write(MAX_PLAYERS, m_aiFreeSpecialist);
	pStream->Write(MAX_PLAYERS, m_aiPower);
	pStream->Write(MAX_PLAYERS, m_aiBestFoundValue);
	pStream->Write(MAX_TEAMS, m_aiNumRevealedTiles);
	pStream->Write(MAX_TEAMS, m_aiCleanPowerCount);
	pStream->Write(MAX_TEAMS, m_aiBorderObstacleCount);

	pStream->Write(MAX_TEAMS, (int*)m_aeAreaAIType);

	for (iI=0;iI<MAX_PLAYERS;iI++)
	{
		pStream->Write(m_aTargetCities[iI].eOwner);
		pStream->Write(m_aTargetCities[iI].iID);
	}

	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		pStream->Write(NUM_YIELD_TYPES, m_aaiYieldRateModifier[iI]);
	}
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		pStream->Write(NUM_UNITAI_TYPES, m_aaiNumTrainAIUnits[iI]);
	}
	for (iI = 0; iI < MAX_PLAYERS; iI++)
	{
		pStream->Write(NUM_UNITAI_TYPES, m_aaiNumAIUnits[iI]);
	}
	pStream->Write(GC.getNumBonusInfos(), m_paiNumBonuses);
	pStream->Write(GC.getNumImprovementInfos(), m_paiNumImprovements);

#endif
}

// Protected Functions...
