#pragma component (mintypeinfo, on)

#include "CvGameCoreDLL.h"
#include "CyGameCoreUtils.h"
#include "CyPlot.h"
#include "CyCity.h"
#include "CyUnit.h"

//
// Python interface for CvgameCoreUtils.h.
//

void CyGameCoreUtilsPythonInterface()
{
	OutputDebugString("Python Extension Module - CyGameCoreUtilsPythonInterface\n");

	boost::python::def("cyIntRange", cyIntRange,"int (int iNum, int iLow, int iHigh)");
	boost::python::def("cyFloatRange", cyFloatRange,"float (float fNum, float fLow, float fHigh)");
	boost::python::def("dxWrap", cyDxWrap,"int (int iDX)");
	boost::python::def("dyWrap", cyDyWrap,"int (int iDY)");
	boost::python::def("plotDistance", cyPlotDistance,"int (int iX1, int iY1, int iX2, int iY2)");
	boost::python::def("stepDistance", cyStepDistance,"int (int iX1, int iY1, int iX2, int iY2)");
	boost::python::def("plotDirection", cyPlotDirection, boost::python::return_value_policy<boost::python::manage_new_object>(), "CyPlot* (int iX, int iY, DirectionTypes eDirection)");
	boost::python::def("plotCardinalDirection", cyPlotCardinalDirection, boost::python::return_value_policy<boost::python::manage_new_object>(), "CyPlot* (int iX, int iY, CardinalDirectionTypes eCardDirection)");
	boost::python::def("splotCardinalDirection", cysPlotCardinalDirection, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CyPlot* (int iX, int iY, CardinalDirectionTypes eCardDirection)");
	boost::python::def("plotXY", cyPlotXY, boost::python::return_value_policy<boost::python::manage_new_object>(), "CyPlot* (int iX, int iY, int iDX, int iDY)");
	boost::python::def("splotXY", cysPlotXY, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CyPlot* (int iX, int iY, int iDX, int iDY)");
	boost::python::def("directionXY", cyDirectionXYFromInt,"DirectionTypes (int iDX, int iDY)");
	boost::python::def("directionXYFromPlot", cyDirectionXYFromPlot,"DirectionTypes (CyPlot* pFromPlot, CyPlot* pToPlot)");
	boost::python::def("plotCity", cyPlotCity, boost::python::return_value_policy<boost::python::manage_new_object>(), "CyPlot* (int iX, int iY, int iIndex)");
	boost::python::def("plotCityXY", cyPlotCityXYFromInt,"int (int iDX, int iDY)");
	boost::python::def("plotCityXYFromCity", cyPlotCityXYFromCity,"int (CyCity* pCity, CyPlot* pPlot)");
	boost::python::def("getOppositeCardinalDirection", cyGetOppositeCardinalDirection,"CardinalDirectionTypes (CardinalDirectionTypes eDir)");
	boost::python::def("cardinalDirectionToDirection", cyCardinalDirectionToDirection, "DirectionTypes (CardinalDirectionTypes eDir) - converts a CardinalDirectionType to the corresponding DirectionType");

	boost::python::def("isCardinalDirection", cyIsCardinalDirection,"bool (DirectionTypes eDirection)");
	boost::python::def("estimateDirection", cyEstimateDirection, "DirectionTypes (int iDX, int iDY)");

	boost::python::def("atWar", cyAtWar,"bool (int eTeamA, int eTeamB)");
	boost::python::def("isPotentialEnemy", cyIsPotentialEnemy,"bool (int eOurTeam, int eTheirTeam)");

	boost::python::def("getCity", cyGetCity, boost::python::return_value_policy<boost::python::manage_new_object>(), "CyPlot* (IDInfo city)");
	boost::python::def("getUnit", cyGetUnit, boost::python::return_value_policy<boost::python::manage_new_object>(), "CyUnit* (IDInfo unit)");

	boost::python::def("isPromotionValid", cyIsPromotionValid, "bool (int /*PromotionTypes*/ ePromotion, int /*UnitTypes*/ eUnit, bool bLeader)");
	boost::python::def("getPopulationAsset", cyGetPopulationAsset, "int (int iPopulation)");
	boost::python::def("getLandPlotsAsset", cyGetLandPlotsAsset, "int (int iLandPlots)");
	boost::python::def("getPopulationPower", cyGetPopulationPower, "int (int iPopulation)");
	boost::python::def("getPopulationScore", cyGetPopulationScore, "int (int iPopulation)");
	boost::python::def("getLandPlotsScore", cyGetLandPlotsScore, "int (int iPopulation)");
	boost::python::def("getTechScore", cyGetTechScore, "int (int /*TechTypes*/ eTech)");
	boost::python::def("getWonderScore", cyGetWonderScore, "int (int /*BuildingClassTypes*/ eWonderClass)");
	boost::python::def("finalImprovementUpgrade", cyFinalImprovementUpgrade, "int /*ImprovementTypes*/ (int /*ImprovementTypes*/ eImprovement, int iCount)");

	boost::python::def("getWorldSizeMaxConscript", cyGetWorldSizeMaxConscript, "int (int /*CivicTypes*/ eCivic)");
	boost::python::def("isReligionTech", cyIsReligionTech, "int (int /*TechTypes*/ eTech)");

	boost::python::def("isTechRequiredForUnit", cyIsTechRequiredForUnit, "bool (int /*TechTypes*/ eTech, int /*UnitTypes*/ eUnit)");
	boost::python::def("isTechRequiredForBuilding", cyIsTechRequiredForBuilding, "bool (int /*TechTypes*/ eTech, int /*BuildingTypes*/ eBuilding)");
	boost::python::def("isTechRequiredForProject", cyIsTechRequiredForProject, "bool (int /*TechTypes*/ eTech, int /*ProjectTypes*/ eProject)");
	boost::python::def("isWorldUnitClass", cyIsWorldUnitClass, "bool (int /*UnitClassTypes*/ eUnitClass)");
	boost::python::def("isTeamUnitClass", cyIsTeamUnitClass, "bool (int /*UnitClassTypes*/ eUnitClass)");
	boost::python::def("isNationalUnitClass", cyIsNationalUnitClass, "bool (int /*UnitClassTypes*/ eUnitClass)");
	boost::python::def("isLimitedUnitClass", cyIsLimitedUnitClass, "bool (int /*UnitClassTypes*/ eUnitClass)");
	boost::python::def("isWorldWonderClass", cyIsWorldWonderClass, "bool (int /*BuildingClassTypes*/ eBuildingClass)");
	boost::python::def("isTeamWonderClass", cyIsTeamWonderClass, "bool (int /*BuildingClassTypes*/ eBuildingClass)");
	boost::python::def("isNationalWonderClass", cyIsNationalWonderClass, "bool (int /*BuildingClassTypes*/ eBuildingClass)");
	boost::python::def("isLimitedWonderClass", cyIsLimitedWonderClass, "bool (int /*BuildingClassTypes*/ eBuildingClass)");
	boost::python::def("isWorldProject", cyIsWorldProject, "bool (int /*ProjectTypes*/ eProject)");
	boost::python::def("isTeamProject", cyIsTeamProject, "bool (int /*ProjectTypes*/ eProject)");
	boost::python::def("isLimitedProject", cyIsLimitedProject, "bool (int /*ProjectTypes*/ eProject)");
	boost::python::def("getCombatOdds", cyGetCombatOdds, "int (CyUnit* pAttacker, CyUnit* pDefender)");
	boost::python::def("getEspionageModifier", cyGetEspionageModifier, "int (int /*TeamTypes*/ iOurTeam, int /*TeamTypes*/ iTargetTeam)");

// BUG - Unit Experience - start
	boost::python::def("calculateExperience", cyCalculateExperience, "int (int iLevel, int /*PlayerTypes*/ iPlayer)");
	boost::python::def("calculateLevel", cyCalculateLevel, "int (int iExperience, int /*PlayerTypes*/ iPlayer)");
// BUG - Unit Experience - end
	
	// edead: start
	boost::python::def("getTurnForYear", cyGetTurnForYear, "int (int iTurnYear)");
	boost::python::def("getGameTurnForYear", cyGetGameTurnForYear, "int (int iTurnYear, int iStartYear, int /*CalendarTypes*/ eCalendar, int /*GameSpeedTypes*/ eSpeed)");
	boost::python::def("getGameTurnForMonth", cyGetGameTurnForMonth, "int (int iTurnMonth, int iStartYear, int /*CalendarTypes*/ eCalendar, int /*GameSpeedTypes*/ eSpeed)");
	boost::python::def("getTurnYearForGame", cyGetTurnYearForGame, "int (int iGameTurn, int iStartYear, int /*CalendarTypes*/ eCalendar, int /*GameSpeedTypes*/ eSpeed)");
	boost::python::def("getTurnMonthForGame", cyGetTurnMonthForGame, "int (int iGameTurn, int iStartYear, int /*CalendarTypes*/ eCalendar, int /*GameSpeedTypes*/ eSpeed)");
	// edead: end

	boost::python::def("getSettlerValue", cyGetSettlerValue, "int (int iPlayer, int x, int y)");
	boost::python::def("log", cyLog, "void (string logfile, string message)");
	boost::python::def("setDirty", cySetDirty, "void (int iDirtyBit, bool bNewValue)");
}
