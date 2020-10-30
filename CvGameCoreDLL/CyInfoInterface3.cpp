#include "CvGameCoreDLL.h"
#include "CvInfos.h"

//
// Python interface for info classes (formerly structs)
// These are simple enough to be exposed directly - no wrappers
//

void CyInfoPythonInterface3()
{
	OutputDebugString("Python Extension Module - CyInfoPythonInterface3\n");
	
	boost::python::class_<CvYieldInfo, boost::python::bases<CvInfoBase> >("CvYieldInfo")
		.def("getChar", &CvYieldInfo::getChar, "int ()")
		.def("getHillsChange", &CvYieldInfo::getHillsChange, "int ()")
		.def("getPeakChange", &CvYieldInfo::getPeakChange, "int ()")
		.def("getLakeChange", &CvYieldInfo::getLakeChange, "int ()")
		.def("getCityChange", &CvYieldInfo::getCityChange, "int ()")
		.def("getPopulationChangeOffset", &CvYieldInfo::getPopulationChangeOffset, "int ()")
		.def("getPopulationChangeDivisor", &CvYieldInfo::getPopulationChangeDivisor, "int ()")
		.def("getMinCity", &CvYieldInfo::getMinCity, "int ()")
		.def("getTradeModifier", &CvYieldInfo::getTradeModifier, "int ()")
		.def("getGoldenAgeYield", &CvYieldInfo::getGoldenAgeYield, "int ()")
		.def("getGoldenAgeYieldThreshold", &CvYieldInfo::getGoldenAgeYieldThreshold, "int ()")
		.def("getAIWeightPercent", &CvYieldInfo::getAIWeightPercent, "int ()")
		.def("getColorType", &CvYieldInfo::getColorType, "int ()")
		;

	boost::python::class_<CvTerrainInfo, boost::python::bases<CvInfoBase> >("CvTerrainInfo")

		.def("getMovementCost", &CvTerrainInfo::getMovementCost, "int ()")
		.def("getSeeFromLevel", &CvTerrainInfo::getSeeFromLevel, "int ()")
		.def("getSeeThroughLevel", &CvTerrainInfo::getSeeThroughLevel, "int ()")
		.def("getBuildModifier", &CvTerrainInfo::getBuildModifier, "int ()")
		.def("getDefenseModifier", &CvTerrainInfo::getDefenseModifier, "int ()")

		.def("isWater", &CvTerrainInfo::isWater, "bool ()")
		.def("isImpassable", &CvTerrainInfo::isImpassable, "bool ()")
		.def("isFound", &CvTerrainInfo::isFound, "bool ()")
		.def("isFoundCoast", &CvTerrainInfo::isFoundCoast, "bool ()")
		.def("isFoundFreshWater", &CvTerrainInfo::isFoundFreshWater, "bool ()")

		// Arrays

		.def("getYield", &CvTerrainInfo::getYield, "int (int i)")
		.def("getRiverYieldChange", &CvTerrainInfo::getRiverYieldChange, "int (int i)")
		.def("getHillsYieldChange", &CvTerrainInfo::getHillsYieldChange, "int (int i)")
		;

	// CvInterfaceModeInfo

	boost::python::class_<CvInterfaceModeInfo, boost::python::bases<CvInfoBase> >("CvInterfaceModeInfo")

		.def("getCursorIndex", &CvInterfaceModeInfo::getCursorIndex, "int ()")
		.def("getMissionType", &CvInterfaceModeInfo::getMissionType, "int ()")

		.def("getVisible", &CvInterfaceModeInfo::getVisible, "bool ()")
		.def("getGotoPlot", &CvInterfaceModeInfo::getGotoPlot, "bool ()")
		.def("getHighlightPlot", &CvInterfaceModeInfo::getHighlightPlot, "bool ()")
		.def("getSelectType", &CvInterfaceModeInfo::getSelectType, "bool ()")
		.def("getSelectAll", &CvInterfaceModeInfo::getSelectAll, "bool ()")

		.def("isAltDown", &CvInterfaceModeInfo::isAltDown, "bool ()")
		.def("isShiftDown", &CvInterfaceModeInfo::isShiftDown, "bool ()")
		.def("isCtrlDown", &CvInterfaceModeInfo::isCtrlDown, "bool ()")
		.def("isAltDownAlt", &CvInterfaceModeInfo::isAltDownAlt, "bool ()")
		.def("isShiftDownAlt", &CvInterfaceModeInfo::isShiftDownAlt, "bool ()")
		.def("isCtrlDownAlt", &CvInterfaceModeInfo::isCtrlDownAlt, "bool ()")
		;

	boost::python::class_<CvLeaderHeadInfo, boost::python::bases<CvInfoBase> >("CvLeaderHeadInfo")
		.def("getWonderConstructRand", &CvLeaderHeadInfo::getWonderConstructRand, "int ()")
		.def("getBaseAttitude", &CvLeaderHeadInfo::getBaseAttitude, "int ()")
		.def("getBasePeaceWeight", &CvLeaderHeadInfo::getBasePeaceWeight, "int ()")
		.def("getPeaceWeightRand", &CvLeaderHeadInfo::getPeaceWeightRand, "int ()")
		.def("getWarmongerRespect", &CvLeaderHeadInfo::getWarmongerRespect, "int ()")
		.def("getEspionageWeight", &CvLeaderHeadInfo::getEspionageWeight, "int ()")
		.def("getRefuseToTalkWarThreshold", &CvLeaderHeadInfo::getRefuseToTalkWarThreshold, "int ()")
		.def("getNoTechTradeThreshold", &CvLeaderHeadInfo::getNoTechTradeThreshold, "int ()")
		.def("getTechTradeKnownPercent", &CvLeaderHeadInfo::getTechTradeKnownPercent, "int ()")
		.def("getMaxGoldTradePercent", &CvLeaderHeadInfo::getMaxGoldTradePercent, "int ()")
		.def("getMaxGoldPerTurnTradePercent", &CvLeaderHeadInfo::getMaxGoldPerTurnTradePercent, "int ()")
		.def("getMaxWarRand", &CvLeaderHeadInfo::getMaxWarRand, "int ()")
		.def("getMaxWarNearbyPowerRatio", &CvLeaderHeadInfo::getMaxWarNearbyPowerRatio, "int ()")
		.def("getMaxWarDistantPowerRatio", &CvLeaderHeadInfo::getMaxWarDistantPowerRatio, "int ()")
		.def("getMaxWarMinAdjacentLandPercent", &CvLeaderHeadInfo::getMaxWarMinAdjacentLandPercent, "int ()")
		.def("getLimitedWarRand", &CvLeaderHeadInfo::getLimitedWarRand, "int ()")
		.def("getLimitedWarPowerRatio", &CvLeaderHeadInfo::getLimitedWarPowerRatio, "int ()")
		.def("getDogpileWarRand", &CvLeaderHeadInfo::getDogpileWarRand, "int ()")
		.def("getMakePeaceRand", &CvLeaderHeadInfo::getMakePeaceRand, "int ()")
		.def("getDeclareWarTradeRand", &CvLeaderHeadInfo::getDeclareWarTradeRand, "int ()")
		.def("getDemandRebukedSneakProb", &CvLeaderHeadInfo::getDemandRebukedSneakProb, "int ()")
		.def("getDemandRebukedWarProb", &CvLeaderHeadInfo::getDemandRebukedWarProb, "int ()")
		.def("getRazeCityProb", &CvLeaderHeadInfo::getRazeCityProb, "int ()")
		.def("getBuildUnitProb", &CvLeaderHeadInfo::getBuildUnitProb, "int ()")
		.def("getBaseAttackOddsChange", &CvLeaderHeadInfo::getBaseAttackOddsChange, "int ()")
		.def("getAttackOddsChangeRand", &CvLeaderHeadInfo::getAttackOddsChangeRand, "int ()")
		.def("getWorseRankDifferenceAttitudeChange", &CvLeaderHeadInfo::getWorseRankDifferenceAttitudeChange, "int ()")
		.def("getBetterRankDifferenceAttitudeChange", &CvLeaderHeadInfo::getBetterRankDifferenceAttitudeChange, "int ()")
		.def("getCloseBordersAttitudeChange", &CvLeaderHeadInfo::getCloseBordersAttitudeChange, "int ()")
		.def("getLostWarAttitudeChange", &CvLeaderHeadInfo::getLostWarAttitudeChange, "int ()")
		.def("getAtWarAttitudeDivisor", &CvLeaderHeadInfo::getAtWarAttitudeDivisor, "int ()")
		.def("getAtWarAttitudeChangeLimit", &CvLeaderHeadInfo::getAtWarAttitudeChangeLimit, "int ()")
		.def("getAtPeaceAttitudeDivisor", &CvLeaderHeadInfo::getAtPeaceAttitudeDivisor, "int ()")
		.def("getAtPeaceAttitudeChangeLimit", &CvLeaderHeadInfo::getAtPeaceAttitudeChangeLimit, "int ()")
		.def("getSameReligionAttitudeChange", &CvLeaderHeadInfo::getSameReligionAttitudeChange, "int ()")
		.def("getSameReligionAttitudeDivisor", &CvLeaderHeadInfo::getSameReligionAttitudeDivisor, "int ()")
		.def("getSameReligionAttitudeChangeLimit", &CvLeaderHeadInfo::getSameReligionAttitudeChangeLimit, "int ()")
		.def("getDifferentReligionAttitudeChange", &CvLeaderHeadInfo::getDifferentReligionAttitudeChange, "int ()")
		.def("getDifferentReligionAttitudeDivisor", &CvLeaderHeadInfo::getDifferentReligionAttitudeDivisor, "int ()")
		.def("getDifferentReligionAttitudeChangeLimit", &CvLeaderHeadInfo::getDifferentReligionAttitudeChangeLimit, "int ()")
		.def("getBonusTradeAttitudeDivisor", &CvLeaderHeadInfo::getBonusTradeAttitudeDivisor, "int ()")
		.def("getBonusTradeAttitudeChangeLimit", &CvLeaderHeadInfo::getBonusTradeAttitudeChangeLimit, "int ()")
		.def("getOpenBordersAttitudeDivisor", &CvLeaderHeadInfo::getOpenBordersAttitudeDivisor, "int ()")
		.def("getOpenBordersAttitudeChangeLimit", &CvLeaderHeadInfo::getOpenBordersAttitudeChangeLimit, "int ()")
		.def("getDefensivePactAttitudeDivisor", &CvLeaderHeadInfo::getDefensivePactAttitudeDivisor, "int ()")
		.def("getDefensivePactAttitudeChangeLimit", &CvLeaderHeadInfo::getDefensivePactAttitudeChangeLimit, "int ()")
		.def("getShareWarAttitudeChange", &CvLeaderHeadInfo::getShareWarAttitudeChange, "int ()")
		.def("getShareWarAttitudeDivisor", &CvLeaderHeadInfo::getShareWarAttitudeDivisor, "int ()")
		.def("getShareWarAttitudeChangeLimit", &CvLeaderHeadInfo::getShareWarAttitudeChangeLimit, "int ()")
		.def("getFavoriteCivicAttitudeChange", &CvLeaderHeadInfo::getFavoriteCivicAttitudeChange, "int ()")
		.def("getFavoriteCivicAttitudeDivisor", &CvLeaderHeadInfo::getFavoriteCivicAttitudeDivisor, "int ()")
		.def("getFavoriteCivicAttitudeChangeLimit", &CvLeaderHeadInfo::getFavoriteCivicAttitudeChangeLimit, "int ()")
		.def("getDemandTributeAttitudeThreshold", &CvLeaderHeadInfo::getDemandTributeAttitudeThreshold, "int ()")
		.def("getNoGiveHelpAttitudeThreshold", &CvLeaderHeadInfo::getNoGiveHelpAttitudeThreshold, "int ()")
		.def("getTechRefuseAttitudeThreshold", &CvLeaderHeadInfo::getTechRefuseAttitudeThreshold, "int ()")
		.def("getStrategicBonusRefuseAttitudeThreshold", &CvLeaderHeadInfo::getStrategicBonusRefuseAttitudeThreshold, "int ()")
		.def("getHappinessBonusRefuseAttitudeThreshold", &CvLeaderHeadInfo::getHappinessBonusRefuseAttitudeThreshold, "int ()")
		.def("getHealthBonusRefuseAttitudeThreshold", &CvLeaderHeadInfo::getHealthBonusRefuseAttitudeThreshold, "int ()")
		.def("getMapRefuseAttitudeThreshold", &CvLeaderHeadInfo::getMapRefuseAttitudeThreshold, "int ()")
		.def("getDeclareWarRefuseAttitudeThreshold", &CvLeaderHeadInfo::getDeclareWarRefuseAttitudeThreshold, "int ()")
		.def("getDeclareWarThemRefuseAttitudeThreshold", &CvLeaderHeadInfo::getDeclareWarThemRefuseAttitudeThreshold, "int ()")
		.def("getStopTradingRefuseAttitudeThreshold", &CvLeaderHeadInfo::getStopTradingRefuseAttitudeThreshold, "int ()")
		.def("getStopTradingThemRefuseAttitudeThreshold", &CvLeaderHeadInfo::getStopTradingThemRefuseAttitudeThreshold, "int ()")
		.def("getAdoptCivicRefuseAttitudeThreshold", &CvLeaderHeadInfo::getAdoptCivicRefuseAttitudeThreshold, "int ()")
		.def("getConvertReligionRefuseAttitudeThreshold", &CvLeaderHeadInfo::getConvertReligionRefuseAttitudeThreshold, "int ()")
		.def("getOpenBordersRefuseAttitudeThreshold", &CvLeaderHeadInfo::getOpenBordersRefuseAttitudeThreshold, "int ()")
		.def("getDefensivePactRefuseAttitudeThreshold", &CvLeaderHeadInfo::getDefensivePactRefuseAttitudeThreshold, "int ()")
		.def("getPermanentAllianceRefuseAttitudeThreshold", &CvLeaderHeadInfo::getPermanentAllianceRefuseAttitudeThreshold, "int ()")
		.def("getVassalRefuseAttitudeThreshold", &CvLeaderHeadInfo::getVassalRefuseAttitudeThreshold, "int ()")
		.def("getFavoriteCivic", &CvLeaderHeadInfo::getFavoriteCivic, "int ()")
		.def("getFavoriteReligion", &CvLeaderHeadInfo::getFavoriteReligion, "int ()")
		.def("getVassalPowerModifier", &CvLeaderHeadInfo::getVassalPowerModifier, "int ()")
		.def("getFreedomAppreciation", &CvLeaderHeadInfo::getFreedomAppreciation, "int ()")

		.def("getArtDefineTag", &CvLeaderHeadInfo::getArtDefineTag, "string ()")

		// Arrays

		.def("hasTrait", &CvLeaderHeadInfo::hasTrait, "bool (int i)")

		.def("getFlavorValue", &CvLeaderHeadInfo::getFlavorValue, "int (int i)")
		.def("getContactRand", &CvLeaderHeadInfo::getContactRand, "int (int i)")
		.def("getContactDelay", &CvLeaderHeadInfo::getContactDelay, "int (int i)")
		.def("getMemoryDecayRand", &CvLeaderHeadInfo::getMemoryDecayRand, "int (int i)")
		.def("getMemoryAttitudePercent", &CvLeaderHeadInfo::getMemoryAttitudePercent, "int (int i)")
		.def("getNoWarAttitudeProb", &CvLeaderHeadInfo::getNoWarAttitudeProb, "int (int i)")
		.def("getUnitAIWeightModifier", &CvLeaderHeadInfo::getUnitAIWeightModifier, "int (int i)")
		.def("getImprovementWeightModifier", &CvLeaderHeadInfo::getImprovementWeightModifier, "int (int i)")
		.def("getDiploPeaceIntroMusicScriptIds", &CvLeaderHeadInfo::getDiploPeaceIntroMusicScriptIds, "int (int i)")
		.def("getDiploPeaceMusicScriptIds", &CvLeaderHeadInfo::getDiploPeaceMusicScriptIds, "int (int i)")
		.def("getDiploWarIntroMusicScriptIds", &CvLeaderHeadInfo::getDiploWarIntroMusicScriptIds, "int (int i)")
		.def("getDiploWarMusicScriptIds", &CvLeaderHeadInfo::getDiploWarMusicScriptIds, "int (int i)")

		// Other

		.def("getLeaderHead", &CvLeaderHeadInfo::getLeaderHead, "string ()")
		.def("getButton", &CvLeaderHeadInfo::getButton, "string ()")
		;

	// CvProcessInfos
	boost::python::class_<CvProcessInfo, boost::python::bases<CvInfoBase> >("CvProcessInfo")
		.def("getTechPrereq", &CvProcessInfo::getTechPrereq, "int ()")

		// Arrays

		.def("getProductionToCommerceModifier", &CvProcessInfo::getProductionToCommerceModifier, "int (int i)")
		;

	boost::python::class_<CvVoteInfo, boost::python::bases<CvInfoBase> >("CvVoteInfo")
		.def("getPopulationThreshold", &CvVoteInfo::getPopulationThreshold, "int ()")
		.def("getStateReligionVotePercent", &CvVoteInfo::getStateReligionVotePercent, "int ()")
		.def("getTradeRoutes", &CvVoteInfo::getTradeRoutes, "int ()")
		.def("getMinVoters", &CvVoteInfo::getMinVoters, "int ()")

		.def("isSecretaryGeneral", &CvVoteInfo::isSecretaryGeneral, "bool ()")
		.def("isVictory", &CvVoteInfo::isVictory, "bool ()")
		.def("isFreeTrade", &CvVoteInfo::isFreeTrade, "bool ()")
		.def("isNoNukes", &CvVoteInfo::isNoNukes, "bool ()")
		.def("isCityVoting", &CvVoteInfo::isCityVoting, "bool ()")
		.def("isCivVoting", &CvVoteInfo::isCivVoting, "bool ()")
		.def("isDefensivePact", &CvVoteInfo::isDefensivePact, "bool ()")
		.def("isOpenBorders", &CvVoteInfo::isOpenBorders, "bool ()")
		.def("isForcePeace", &CvVoteInfo::isForcePeace, "bool ()")
		.def("isForceNoTrade", &CvVoteInfo::isForceNoTrade, "bool ()")
		.def("isForceWar", &CvVoteInfo::isForceWar, "bool ()")
		.def("isAssignCity", &CvVoteInfo::isAssignCity, "bool ()")

		// Arrays

		.def("isForceCivic", &CvVoteInfo::isForceCivic, "bool (int i)")
		.def("isVoteSourceType", &CvVoteInfo::isVoteSourceType, "bool (int i)")
		;

	boost::python::class_<CvProjectInfo, boost::python::bases<CvInfoBase> >("CvProjectInfo")
		.def("getVictoryPrereq", &CvProjectInfo::getVictoryPrereq, "int ()")
		.def("getTechPrereq", &CvProjectInfo::getTechPrereq, "int ()")
		.def("getAnyoneProjectPrereq", &CvProjectInfo::getAnyoneProjectPrereq, "int ()")
		.def("getMaxGlobalInstances", &CvProjectInfo::getMaxGlobalInstances, "int ()")
		.def("getMaxTeamInstances", &CvProjectInfo::getMaxTeamInstances, "int ()")
		.def("getProductionCost", &CvProjectInfo::getProductionCost, "int ()")
		.def("getNukeInterception", &CvProjectInfo::getNukeInterception, "int ()")
		.def("getTechShare", &CvProjectInfo::getTechShare, "int ()")
		.def("getEveryoneSpecialUnit", &CvProjectInfo::getEveryoneSpecialUnit, "int ()")
		.def("getEveryoneSpecialBuilding", &CvProjectInfo::getEveryoneSpecialBuilding, "int ()")

		.def("isSpaceship", &CvProjectInfo::isSpaceship, "bool ()")
		.def("isAllowsNukes", &CvProjectInfo::isAllowsNukes, "bool ()")

		.def("getMovieArtDef", &CvProjectInfo::getMovieArtDef, "string ()")
		.def("getCreateSound", &CvProjectInfo::getCreateSound, "string ()")

		// Arrays

		.def("getBonusProductionModifier", &CvProjectInfo::getBonusProductionModifier, "int (int i)")
		.def("getVictoryThreshold", &CvProjectInfo::getVictoryThreshold, "int (int i)")
		.def("getVictoryMinThreshold", &CvProjectInfo::getVictoryMinThreshold, "int (int i)")
		.def("getVictoryDelayPercent", &CvProjectInfo::getVictoryDelayPercent, "int ()")
		.def("getSuccessRate", &CvProjectInfo::getSuccessRate, "int ()")
		.def("getProjectsNeeded", &CvProjectInfo::getProjectsNeeded, "int (int i)")
		;

	boost::python::class_<CvReligionInfo, boost::python::bases<CvInfoBase> >("CvReligionInfo")
		.def("getChar", &CvReligionInfo::getChar, "int ()")
		.def("getHolyCityChar", &CvReligionInfo::getHolyCityChar, "int ()")
		.def("getTechPrereq", &CvReligionInfo::getTechPrereq, "int ()")
		.def("getFreeUnitClass", &CvReligionInfo::getFreeUnitClass, "int ()")
		.def("getNumFreeUnits", &CvReligionInfo::getNumFreeUnits, "int ()")
		.def("getSpreadFactor", &CvReligionInfo::getSpreadFactor, "int ()")
		.def("getMissionType", &CvReligionInfo::getMissionType, "int ()")

		.def("getTechButton", &CvReligionInfo::getTechButton, "string ()")
		.def("getGenericTechButton", &CvReligionInfo::getGenericTechButton, "string ()")
		.def("getMovieFile", &CvReligionInfo::getMovieFile, "string ()")
		.def("getMovieSound", &CvReligionInfo::getMovieSound, "string ()")
		.def("getSound", &CvReligionInfo::getSound, "string ()")
		.def("getButtonDisabled", &CvReligionInfo::getButtonDisabled, "string ()")
		.def("getAdjectiveKey", &CvReligionInfo::pyGetAdjectiveKey, "wstring ()")

		.def("isProselytizing", &CvReligionInfo::isProselytizing, "bool ()")
		.def("isLocal", &CvReligionInfo::isLocal, "bool ()")

		// Arrays

		.def("getGlobalReligionCommerce", &CvReligionInfo::getGlobalReligionCommerce, "int (int i)")
		.def("getHolyCityCommerce", &CvReligionInfo::getHolyCityCommerce, "int (int i)")
		.def("getStateReligionCommerce", &CvReligionInfo::getStateReligionCommerce, "int (int i)")
		;

	boost::python::class_<CvCorporationInfo, boost::python::bases<CvInfoBase> >("CvCorporationInfo")
		.def("getChar", &CvCorporationInfo::getChar, "int ()")
		.def("getHeadquarterChar", &CvCorporationInfo::getHeadquarterChar, "int ()")
		.def("getTechPrereq", &CvCorporationInfo::getTechPrereq, "int ()")
		.def("getFreeUnitClass", &CvCorporationInfo::getFreeUnitClass, "int ()")
		.def("getSpreadFactor", &CvCorporationInfo::getSpreadFactor, "int ()")
		.def("getSpreadCost", &CvCorporationInfo::getSpreadCost, "int ()")
		.def("getMaintenance", &CvCorporationInfo::getMaintenance, "int ()")
		.def("getMissionType", &CvCorporationInfo::getMissionType, "int ()")

		.def("getMovieFile", &CvCorporationInfo::getMovieFile, "string ()")
		.def("getMovieSound", &CvCorporationInfo::getMovieSound, "string ()")
		.def("getSound", &CvCorporationInfo::getSound, "string ()")

		// Arrays

		.def("getPrereqBonus", &CvCorporationInfo::getPrereqBonus, "int (int i)")
		.def("getHeadquarterCommerce", &CvCorporationInfo::getHeadquarterCommerce, "int (int i)")
		.def("getCommerceProduced", &CvCorporationInfo::getCommerceProduced, "int (int i)")
		.def("getYieldProduced", &CvCorporationInfo::getYieldProduced, "int (int i)")
		;

	boost::python::class_<CvTraitInfo, boost::python::bases<CvInfoBase> >("CvTraitInfo")
		.def("getHealth", &CvTraitInfo::getHealth, "int ()")
		.def("getHappiness", &CvTraitInfo::getHappiness, "int ()")
		.def("getMaxAnarchy", &CvTraitInfo::getMaxAnarchy, "int ()")
		.def("getUpkeepModifier", &CvTraitInfo::getUpkeepModifier, "int ()")
		.def("getLevelExperienceModifier", &CvTraitInfo::getLevelExperienceModifier, "int ()")
		.def("getGreatPeopleRateModifier", &CvTraitInfo::getGreatPeopleRateModifier, "int ()")
		.def("getGreatGeneralRateModifier", &CvTraitInfo::getGreatGeneralRateModifier, "int ()")
		.def("getDomesticGreatGeneralRateModifier", &CvTraitInfo::getDomesticGreatGeneralRateModifier, "int ()")
		.def("getMaxGlobalBuildingProductionModifier", &CvTraitInfo::getMaxGlobalBuildingProductionModifier, "int ()")
		.def("getMaxTeamBuildingProductionModifier", &CvTraitInfo::getMaxTeamBuildingProductionModifier, "int ()")
		.def("getMaxPlayerBuildingProductionModifier", &CvTraitInfo::getMaxPlayerBuildingProductionModifier, "int ()")

		.def("getShortDescription", &CvTraitInfo::getShortDescription, "int (int i)")
		.def("getExtraYieldThreshold", &CvTraitInfo::getExtraYieldThreshold, "int (int i)")
		.def("getTradeYieldModifier", &CvTraitInfo::getTradeYieldModifier, "int (int i)")
		.def("getCommerceChange", &CvTraitInfo::getCommerceChange, "int (int i)")
		.def("getCommerceModifier", &CvTraitInfo::getCommerceModifier, "int (int i)")

		.def("isFreePromotion", &CvTraitInfo::isFreePromotion, "int (int i)")
		;

	// CvWorldInfo
	boost::python::class_<CvWorldInfo, boost::python::bases<CvInfoBase> >("CvWorldInfo")
		.def("getDefaultPlayers", &CvWorldInfo::getDefaultPlayers, "int ()")
		.def("getUnitNameModifier", &CvWorldInfo::getUnitNameModifier, "int ()")
		.def("getTargetNumCities", &CvWorldInfo::getTargetNumCities, "int ()")
		.def("getNumFreeBuildingBonuses", &CvWorldInfo::getNumFreeBuildingBonuses, "int ()")
		.def("getBuildingClassPrereqModifier", &CvWorldInfo::getBuildingClassPrereqModifier, "int ()")
		.def("getMaxConscriptModifier", &CvWorldInfo::getMaxConscriptModifier, "int ()")
		.def("getWarWearinessModifier", &CvWorldInfo::getWarWearinessModifier, "int ()")
		.def("getGridWidth", &CvWorldInfo::getGridWidth, "int ()")
		.def("getGridHeight", &CvWorldInfo::getGridHeight, "int ()")
		.def("getTerrainGrainChange", &CvWorldInfo::getTerrainGrainChange, "int ()")
		.def("getFeatureGrainChange", &CvWorldInfo::getFeatureGrainChange, "int ()")
		.def("getResearchPercent", &CvWorldInfo::getResearchPercent, "int ()")
		.def("getTradeProfitPercent", &CvWorldInfo::getTradeProfitPercent, "int ()")
		.def("getDistanceMaintenancePercent", &CvWorldInfo::getDistanceMaintenancePercent, "int ()")
		.def("getNumCitiesMaintenancePercent", &CvWorldInfo::getNumCitiesMaintenancePercent, "int ()")
		.def("getColonyMaintenancePercent", &CvWorldInfo::getColonyMaintenancePercent, "int ()")
		.def("getCorporationMaintenancePercent", &CvWorldInfo::getCorporationMaintenancePercent, "int ()")
		.def("getNumCitiesAnarchyPercent", &CvWorldInfo::getNumCitiesAnarchyPercent, "int ()")
		;

	boost::python::class_<CvClimateInfo, boost::python::bases<CvInfoBase> >("CvClimateInfo")
		.def("getDesertPercentChange", &CvClimateInfo::getDesertPercentChange, "int ()")
		.def("getJungleLatitude", &CvClimateInfo::getJungleLatitude, "int ()")
		.def("getHillRange", &CvClimateInfo::getHillRange, "int ()")
		.def("getPeakPercent", &CvClimateInfo::getPeakPercent, "int ()")

		.def("getSnowLatitudeChange", &CvClimateInfo::getSnowLatitudeChange, "float ()")
		.def("getTundraLatitudeChange", &CvClimateInfo::getTundraLatitudeChange, "float ()")
		.def("getGrassLatitudeChange", &CvClimateInfo::getGrassLatitudeChange, "float ()")
		.def("getDesertBottomLatitudeChange", &CvClimateInfo::getDesertBottomLatitudeChange, "float ()")
		.def("getDesertTopLatitudeChange", &CvClimateInfo::getDesertTopLatitudeChange, "float ()")
		.def("getIceLatitude", &CvClimateInfo::getIceLatitude, "float ()")
		.def("getRandIceLatitude", &CvClimateInfo::getRandIceLatitude, "float ()")
		;

	boost::python::class_<CvSeaLevelInfo, boost::python::bases<CvInfoBase> >("CvSeaLevelInfo")
		.def("getSeaLevelChange", &CvSeaLevelInfo::getSeaLevelChange, "int ()")
		;

	boost::python::class_<CvAssetInfoBase>("CvAssetInfoBase")
		.def("setTag", &CvAssetInfoBase::setTag, "void (string)")
		.def("getTag", &CvAssetInfoBase::getTag, "string ()")
		.def("setPath", &CvAssetInfoBase::setPath, "void (string)")
		.def("getPath", &CvAssetInfoBase::getPath, "string ()")
		;

	boost::python::class_<CvArtInfoAsset, boost::python::bases<CvAssetInfoBase> >("CvArtInfoAsset")
		.def("getButton", &CvArtInfoAsset::getButton, "string ()")
		.def("setNIF", &CvArtInfoAsset::setNIF, "void (string)")
		.def("getNIF", &CvArtInfoAsset::getNIF, "string ()")
		.def("setKFM", &CvArtInfoAsset::setKFM, "void (string)")
		.def("getKFM", &CvArtInfoAsset::getKFM, "string ()")
		;

	boost::python::class_<CvArtInfoScalableAsset, boost::python::bases<CvArtInfoAsset, CvScalableInfo> >("CvArtInfoScalableAsset")
		;

	boost::python::class_<CvArtInfoInterface, boost::python::bases<CvArtInfoAsset> >("CvArtInfoInterface")
		;

	boost::python::class_<CvArtInfoMovie, boost::python::bases<CvArtInfoAsset> >("CvArtInfoMovie")
		;

	boost::python::class_<CvArtInfoMisc, boost::python::bases<CvArtInfoAsset> >("CvArtInfoMisc")
		;

	boost::python::class_<CvArtInfoUnit, boost::python::bases<CvArtInfoScalableAsset> >("CvArtInfoUnit")
		.def("getInterfaceScale", &CvArtInfoUnit::getInterfaceScale, "float ()")
		.def("getKFM", &CvArtInfoUnit::getKFM, "string ()")
		;

	boost::python::class_<CvArtInfoBuilding, boost::python::bases<CvArtInfoScalableAsset> >("CvArtInfoBuilding")
		.def("isAnimated", &CvArtInfoBuilding::isAnimated, "bool ()")
		;

	boost::python::class_<CvArtInfoCivilization, boost::python::bases<CvArtInfoAsset> >("CvArtInfoCivilization")
		.def("isWhiteFlag", &CvArtInfoCivilization::isWhiteFlag, "bool ()")
		;

	boost::python::class_<CvArtInfoLeaderhead, boost::python::bases<CvArtInfoAsset> >("CvArtInfoLeaderhead")
		;

	boost::python::class_<CvArtInfoBonus, boost::python::bases<CvArtInfoScalableAsset> >("CvArtInfoBonus")
		;

	boost::python::class_<CvArtInfoImprovement, boost::python::bases<CvArtInfoScalableAsset> >("CvArtInfoImprovement")
		.def("isExtraAnimations", &CvArtInfoImprovement::isExtraAnimations, "bool ()")
		;

	boost::python::class_<CvArtInfoTerrain, boost::python::bases<CvArtInfoAsset> >("CvArtInfoTerrain")
		;

	boost::python::class_<CvArtInfoFeature, boost::python::bases<CvArtInfoScalableAsset> >("CvArtInfoFeature")
		.def("isAnimated", &CvArtInfoFeature::isAnimated, "bool ()")
		.def("isRiverArt", &CvArtInfoFeature::isRiverArt, "bool ()")
		.def("getFeatureDummyNodeName", &CvArtInfoFeature::getFeatureDummyNodeName, "string (int variety, string tagName)")
		;

	boost::python::class_<CvEmphasizeInfo, boost::python::bases<CvInfoBase> >("CvEmphasizeInfo")
		.def("isAvoidGrowth", &CvEmphasizeInfo::isAvoidGrowth, "bool ()")
		.def("isGreatPeople", &CvEmphasizeInfo::isGreatPeople, "bool ()")

		// Arrays

		.def("getYieldChange", &CvEmphasizeInfo::getYieldChange, "int (int i)")
		.def("getCommerceChange", &CvEmphasizeInfo::getCommerceChange, "int (int i)")
		;

	boost::python::class_<CvUpkeepInfo, boost::python::bases<CvInfoBase> >("CvUpkeepInfo")
		.def("getPopulationPercent", &CvUpkeepInfo::getPopulationPercent, "int ()")
		.def("getCityPercent", &CvUpkeepInfo::getCityPercent, "int ()")
		;

	boost::python::class_<CvCultureLevelInfo, boost::python::bases<CvInfoBase> >("CvCultureLevelInfo")
		.def("getCityDefenseModifier", &CvCultureLevelInfo::getCityDefenseModifier, "int ()")
		.def("getWonderLimit", &CvCultureLevelInfo::getWonderLimit, "int ()")
		.def("getNationalWonderLimit", &CvCultureLevelInfo::getNationalWonderLimit, "int ()")

		.def("getSpeedThreshold", &CvCultureLevelInfo::getSpeedThreshold, "int ()")
		;

	boost::python::class_<CvEraInfo, boost::python::bases<CvInfoBase> >("CvEraInfo")
		.def("getStartingUnitMultiplier", &CvEraInfo::getStartingUnitMultiplier, "int () -")
		.def("getStartingDefenseUnits", &CvEraInfo::getStartingDefenseUnits, "int () -")
		.def("getStartingWorkerUnits", &CvEraInfo::getStartingWorkerUnits, "int () -")
		.def("getStartingExploreUnits", &CvEraInfo::getStartingExploreUnits, "int () -")
		.def("getStartingGold", &CvEraInfo::getStartingGold, "int () -")
		.def("getFreePopulation", &CvEraInfo::getFreePopulation, "int () -")
		.def("getStartPercent", &CvEraInfo::getStartPercent, "int () -")
		.def("getGrowthPercent", &CvEraInfo::getGrowthPercent, "int () -")
		.def("getTrainPercent", &CvEraInfo::getTrainPercent, "int () -")
		.def("getConstructPercent", &CvEraInfo::getConstructPercent, "int () -")
		.def("getCreatePercent", &CvEraInfo::getCreatePercent, "int () -")
		.def("getResearchPercent", &CvEraInfo::getResearchPercent, "int () -")
		.def("getBuildPercent", &CvEraInfo::getBuildPercent, "int () -")
		.def("getImprovementPercent", &CvEraInfo::getImprovementPercent, "int () -")
		.def("getGreatPeoplePercent", &CvEraInfo::getGreatPeoplePercent, "int () -")
		.def("getAnarchyPercent", &CvEraInfo::getAnarchyPercent, "int () -")
		.def("getEventChancePerTurn", &CvEraInfo::getEventChancePerTurn, "int () -")
		.def("getSoundtrackSpace", &CvEraInfo::getSoundtrackSpace, "int () -")
		.def("isFirstSoundtrackFirst", &CvEraInfo::isFirstSoundtrackFirst, "int () -")
		.def("getNumSoundtracks", &CvEraInfo::getNumSoundtracks, "int () -")
		.def("getAudioUnitVictoryScript", &CvEraInfo::getAudioUnitVictoryScript, "string () -")
		.def("getAudioUnitDefeatScript", &CvEraInfo::getAudioUnitDefeatScript, "string () -")

		.def("isNoGoodies", &CvEraInfo::isNoGoodies, "bool () -")
		.def("isNoAnimals", &CvEraInfo::isNoAnimals, "bool () -")
		.def("isNoBarbUnits", &CvEraInfo::isNoBarbUnits, "bool () -")
		.def("isNoBarbCities", &CvEraInfo::isNoBarbCities, "bool () -")

		// Arrays

		.def("getSoundtracks", &CvEraInfo::getSoundtracks, "int (int i) -")
		.def("getCitySoundscapeSciptId", &CvEraInfo::getCitySoundscapeSciptId, "int (int i) -")
		;

	boost::python::class_<CvColorInfo, boost::python::bases<CvInfoBase> >("CvColorInfo")
		.def("getColor", &CvColorInfo::getColor,  boost::python::return_value_policy<boost::python::reference_existing_object>())
		;

	boost::python::class_<CvPlayerColorInfo, boost::python::bases<CvInfoBase> >("CvPlayerColorInfo")
		.def("getColorTypePrimary", &CvPlayerColorInfo::getColorTypePrimary, "int ()")
		.def("getColorTypeSecondary", &CvPlayerColorInfo::getColorTypeSecondary, "int ()")
		.def("getTextColorType", &CvPlayerColorInfo::getTextColorType, "int ()")
		;

	boost::python::class_<CvGameText, boost::python::bases<CvInfoBase> >("CvGameText")
		.def("getText", &CvGameText::pyGetText, "wstring ()")
		.def("setText", &CvGameText::setText, "void (wstring)")
		.def("getNumLanguages", &CvGameText::getNumLanguages, "int ()")
		;

	boost::python::class_<CvDiplomacyTextInfo, boost::python::bases<CvInfoBase> >("CvDiplomacyTextInfo")
		.def("getResponse", &CvDiplomacyTextInfo::getResponse,  boost::python::return_value_policy<boost::python::reference_existing_object>(), "Response (int iNum)")
		.def("getNumResponses", &CvDiplomacyTextInfo::getNumResponses, "int ()")

		.def("getCivilizationTypes", &CvDiplomacyTextInfo::getCivilizationTypes, "bool (int i, int j)")
		.def("getLeaderHeadTypes", &CvDiplomacyTextInfo::getLeaderHeadTypes, "bool (int i, int j)")
		.def("getAttitudeTypes", &CvDiplomacyTextInfo::getAttitudeTypes, "bool (int i, int j)")
		.def("getDiplomacyPowerTypes", &CvDiplomacyTextInfo::getDiplomacyPowerTypes, "bool (int i, int j)")

		.def("getNumDiplomacyText", &CvDiplomacyTextInfo::getNumDiplomacyText, "int (int i)")

		.def("getDiplomacyText", &CvDiplomacyTextInfo::getDiplomacyText, "string (int i, int j)")
		;

	boost::python::class_<CvDiplomacyInfo, boost::python::bases<CvInfoBase> >("CvDiplomacyInfo")
		.def("getResponse", &CvDiplomacyInfo::getResponse,  boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvDiplomacyResponse (int iNum)")
		.def("getNumResponses", &CvDiplomacyInfo::getNumResponses, "int ()")

		.def("getCivilizationTypes", &CvDiplomacyInfo::getCivilizationTypes, "bool (int i, int j)")
		.def("getLeaderHeadTypes", &CvDiplomacyInfo::getLeaderHeadTypes, "bool (int i, int j)")
		.def("getAttitudeTypes", &CvDiplomacyInfo::getAttitudeTypes, "bool (int i, int j)")
		.def("getDiplomacyPowerTypes", &CvDiplomacyInfo::getDiplomacyPowerTypes, "bool (int i, int j)")

		.def("getNumDiplomacyText", &CvDiplomacyInfo::getNumDiplomacyText, "int (int i)")

		.def("getDiplomacyText", &CvDiplomacyInfo::getDiplomacyText, "string (int i, int j)")
		;

	boost::python::class_<CvEffectInfo, boost::python::bases<CvInfoBase, CvScalableInfo> >("CvEffectInfo")
		.def("getPath", &CvEffectInfo::getPath, "string ()")
		.def("setPath", &CvEffectInfo::setPath, "void (string)")
		;

	boost::python::class_<CvControlInfo, boost::python::bases<CvInfoBase> >("CvControlInfo")
		.def("getActionInfoIndex", &CvControlInfo::getActionInfoIndex, "int ()")
		;

	boost::python::class_<CvQuestInfo, boost::python::bases<CvInfoBase> >("CvQuestInfo")
		.def("getQuestMessages", &CvQuestInfo::getQuestMessages, "int ()")
		.def("getNumQuestLinks", &CvQuestInfo::getNumQuestLinks, "int ()")
		.def("getNumQuestSounds", &CvQuestInfo::getNumQuestSounds, "int ()")

		.def("getQuestObjective", &CvQuestInfo::getQuestObjective, "string ()")
		.def("getQuestBodyText", &CvQuestInfo::getQuestBodyText, "string ()")
		.def("getNumQuestMessages", &CvQuestInfo::getNumQuestMessages, "string ()")
		.def("getQuestLinkType", &CvQuestInfo::getQuestLinkType, "string ()")
		.def("getQuestLinkName", &CvQuestInfo::getQuestLinkName, "string ()")
		.def("getQuestSounds", &CvQuestInfo::getQuestSounds, "string ()")

		.def("setNumQuestMessages", &CvQuestInfo::setNumQuestMessages, "void (int)")

		.def("setQuestObjective", &CvQuestInfo::setQuestObjective, "void (string)")
		.def("setQuestBodyText", &CvQuestInfo::setQuestBodyText, "void (string)")
		.def("setQuestMessages", &CvQuestInfo::setQuestMessages, "void (int iIndex, string)")
		;

	boost::python::class_<CvTutorialMessage>("CvTutorialMessage")
		.def("getText", &CvTutorialMessage::getText, "string ()")
		.def("getImage", &CvTutorialMessage::getImage, "string ()")
		.def("getSound", &CvTutorialMessage::getSound, "string ()")

		.def("getNumTutorialScripts", &CvTutorialMessage::getNumTutorialScripts, "int ()")
		.def("getTutorialScriptByIndex", &CvTutorialMessage::getTutorialScriptByIndex, "int (int i)")
		;

	boost::python::class_<CvTutorialInfo, boost::python::bases<CvInfoBase> >("CvTutorialInfo")
		.def("getNextTutorialInfoType", &CvTutorialInfo::getNextTutorialInfoType, "string ()")

		.def("getNumTutorialMessages", &CvTutorialInfo::getNumTutorialMessages, "int ()")
		.def("getTutorialMessage", &CvTutorialInfo::getTutorialMessage,  boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvTutorialMessage* (int iIndex)")
		;

	boost::python::class_<CvAutomateInfo, boost::python::bases<CvInfoBase> >("CvAutomateInfo")
		;

	boost::python::class_<CvCommandInfo, boost::python::bases<CvInfoBase> >("CvCommandInfo")
		;

	boost::python::class_<CvGameOptionInfo, boost::python::bases<CvInfoBase> >("CvGameOptionInfo")
		.def("getDefault", &CvGameOptionInfo::getDefault, "bool ()")
		.def("getVisible", &CvGameOptionInfo::getVisible, "bool ()")
		;

	boost::python::class_<CvMPOptionInfo, boost::python::bases<CvInfoBase> >("CvMPOptionInfo")
		.def("getDefault", &CvMPOptionInfo::getDefault, "bool ()")
		;

	boost::python::class_<CvForceControlInfo, boost::python::bases<CvInfoBase> >("CvForceControlInfo")
		.def("getDefault", &CvForceControlInfo::getDefault, "bool ()")
		;

	boost::python::class_<CvPlayerOptionInfo, boost::python::bases<CvInfoBase> >("CvPlayerOptionInfo")
		.def("getDefault", &CvPlayerOptionInfo::getDefault, "bool ()")
		;

	boost::python::class_<CvGraphicOptionInfo, boost::python::bases<CvInfoBase> >("CvGraphicOptionInfo")
		.def("getDefault", &CvGraphicOptionInfo::getDefault, "bool ()")
		;

	boost::python::class_<CvEventTriggerInfo, boost::python::bases<CvInfoBase> >("CvEventTriggerInfo")
		.def("getPercentGamesActive", &CvEventTriggerInfo::getPercentGamesActive, "int ()")
		.def("getProbability", &CvEventTriggerInfo::getProbability, "int ()")
		.def("getNumUnits", &CvEventTriggerInfo::getNumUnits, "int ()")
		.def("getNumBuildings", &CvEventTriggerInfo::getNumBuildings, "int ()")
		.def("getNumUnitsGlobal", &CvEventTriggerInfo::getNumUnitsGlobal, "int ()")
		.def("getNumBuildingsGlobal", &CvEventTriggerInfo::getNumBuildingsGlobal, "int ()")
		.def("getNumPlotsRequired", &CvEventTriggerInfo::getNumPlotsRequired, "int ()")
		.def("getPlotsType", &CvEventTriggerInfo::getPlotType, "int ()")
		.def("getNumReligions", &CvEventTriggerInfo::getNumReligions, "int ()")
		.def("getNumCorporations", &CvEventTriggerInfo::getNumCorporations, "int ()")
		.def("getOtherPlayerShareBorders", &CvEventTriggerInfo::getOtherPlayerShareBorders, "int ()")
		.def("getOtherPlayerHasTech", &CvEventTriggerInfo::getOtherPlayerHasTech, "int ()")
		.def("getCityFoodWeight", &CvEventTriggerInfo::getCityFoodWeight, "int ()")
		.def("getCivic", &CvEventTriggerInfo::getCivic, "int ()")
		.def("getMinPopulation", &CvEventTriggerInfo::getMinPopulation, "int ()")
		.def("getMaxPopulation", &CvEventTriggerInfo::getMaxPopulation, "int ()")
		.def("getMinMapLandmass", &CvEventTriggerInfo::getMinMapLandmass, "int ()")
		.def("getMinOurLandmass", &CvEventTriggerInfo::getMinOurLandmass, "int ()")
		.def("getMaxOurLandmass", &CvEventTriggerInfo::getMaxOurLandmass, "int ()")
		.def("getMinDifficulty", &CvEventTriggerInfo::getMinDifficulty, "int ()")
		.def("getAngry", &CvEventTriggerInfo::getAngry, "int ()")
		.def("getUnhealthy", &CvEventTriggerInfo::getUnhealthy, "int ()")
		.def("getUnitDamagedWeight", &CvEventTriggerInfo::getUnitDamagedWeight, "int ()")
		.def("getUnitDistanceWeight", &CvEventTriggerInfo::getUnitDistanceWeight, "int ()")
		.def("getUnitExperienceWeight", &CvEventTriggerInfo::getUnitExperienceWeight, "int ()")
		.def("getMinTreasury", &CvEventTriggerInfo::getMinTreasury, "int ()")

		.def("getUnitRequired", &CvEventTriggerInfo::getUnitRequired, "int (int)")
		.def("getNumUnitsRequired", &CvEventTriggerInfo::getNumUnitsRequired, "int ()")
		.def("getBuildingRequired", &CvEventTriggerInfo::getBuildingRequired, "int (int)")
		.def("getNumBuildingsRequired", &CvEventTriggerInfo::getNumBuildingsRequired, "int ()")
		.def("getPrereqOrTechs", &CvEventTriggerInfo::getPrereqOrTechs, "int (int)")
		.def("getNumPrereqOrTechs", &CvEventTriggerInfo::getNumPrereqOrTechs, "int ()")
		.def("getPrereqAndTechs", &CvEventTriggerInfo::getPrereqAndTechs, "int (int)")
		.def("getNumPrereqAndTechs", &CvEventTriggerInfo::getNumPrereqAndTechs, "int ()")
		.def("getObsoleteTech", &CvEventTriggerInfo::getObsoleteTech, "int (int)")
		.def("getNumObsoleteTechs", &CvEventTriggerInfo::getNumObsoleteTechs, "int (int)")
		.def("getEvent", &CvEventTriggerInfo::getEvent, "int (int)")
		.def("getNumEvents", &CvEventTriggerInfo::getNumEvents, "int ()")
		.def("getPrereqEvent", &CvEventTriggerInfo::getPrereqEvent, "int (int)")
		.def("getNumPrereqEvents", &CvEventTriggerInfo::getNumPrereqEvents, "int ()")
		.def("getFeatureRequired", &CvEventTriggerInfo::getFeatureRequired, "int (int)")
		.def("getNumFeaturesRequired", &CvEventTriggerInfo::getNumFeaturesRequired, "int ()")
		.def("getTerrainRequired", &CvEventTriggerInfo::getTerrainRequired, "int (int)")
		.def("getNumTerrainsRequired", &CvEventTriggerInfo::getNumTerrainsRequired, "int ()")
		.def("getImprovementRequired", &CvEventTriggerInfo::getImprovementRequired, "int (int)")
		.def("getNumImprovementsRequired", &CvEventTriggerInfo::getNumImprovementsRequired, "int ()")
		.def("getBonusRequired", &CvEventTriggerInfo::getBonusRequired, "int (int)")
		.def("getNumBonusesRequired", &CvEventTriggerInfo::getNumBonusesRequired, "int ()")
		.def("getRouteRequired", &CvEventTriggerInfo::getRouteRequired, "int (int)")
		.def("getNumRoutesRequired", &CvEventTriggerInfo::getNumRoutesRequired, "int ()")
		.def("getReligionRequired", &CvEventTriggerInfo::getBonusRequired, "int (int)")
		.def("getNumReligionsRequired", &CvEventTriggerInfo::getNumReligionsRequired, "int ()")
		.def("getCorporationRequired", &CvEventTriggerInfo::getCorporationRequired, "int (int)")
		.def("getNumCorporationsRequired", &CvEventTriggerInfo::getNumCorporationsRequired, "int ()")

		.def("isSinglePlayer", &CvEventTriggerInfo::isSinglePlayer, "bool ()")
		.def("isTeam", &CvEventTriggerInfo::isTeam, "bool ()")
		.def("isRecurring", &CvEventTriggerInfo::isRecurring, "bool ()")
		.def("isGlobal", &CvEventTriggerInfo::isGlobal, "bool ()")
		.def("isPickPlayer", &CvEventTriggerInfo::isPickPlayer, "bool ()")
		.def("isOtherPlayerHasReligion", &CvEventTriggerInfo::isOtherPlayerHasReligion, "bool ()")
		.def("isOtherPlayerHasOtherReligion", &CvEventTriggerInfo::isOtherPlayerHasOtherReligion, "bool ()")
		.def("isOtherPlayerAI", &CvEventTriggerInfo::isOtherPlayerAI, "bool ()")
		.def("isPickCity", &CvEventTriggerInfo::isPickCity, "bool ()")
		.def("isPickOtherPlayerCity", &CvEventTriggerInfo::isPickCity, "bool ()")
		.def("isUnitsOnPlot", &CvEventTriggerInfo::isUnitsOnPlot, "bool ()")
		.def("isOwnPlot", &CvEventTriggerInfo::isOwnPlot, "bool ()")
		.def("isPickReligion", &CvEventTriggerInfo::isPickReligion, "bool ()")
		.def("isStateReligion", &CvEventTriggerInfo::isStateReligion, "bool ()")
		.def("isProbabilityUnitMultiply", &CvEventTriggerInfo::isProbabilityUnitMultiply, "bool ()")
		.def("isProbabilityBuildingMultiply", &CvEventTriggerInfo::isProbabilityBuildingMultiply, "bool ()")
		.def("isPrereqEventCity", &CvEventTriggerInfo::isPrereqEventCity, "bool ()")
		;

	boost::python::class_<CvEventInfo, boost::python::bases<CvInfoBase> >("CvEventInfo")
		.def("isQuest", &CvEventInfo::isQuest, "bool ()")
		.def("isGlobal", &CvEventInfo::isGlobal, "bool ()")
		.def("isTeam", &CvEventInfo::isTeam, "bool ()")
		.def("isCityEffect", &CvEventInfo::isCityEffect, "bool ()")
		.def("isOtherPlayerCityEffect", &CvEventInfo::isOtherPlayerCityEffect, "bool ()")
		.def("isGoldToPlayer", &CvEventInfo::isGoldToPlayer, "bool ()")
		.def("isGoldenAge", &CvEventInfo::isGoldenAge, "bool ()")
		.def("isDeclareWar", &CvEventInfo::isDeclareWar, "bool ()")
		.def("isDisbandUnit", &CvEventInfo::isDisbandUnit, "bool ()")
		.def("getGold", &CvEventInfo::getGold, "int ()")
		.def("getRandomGold", &CvEventInfo::getRandomGold, "int ()")
		.def("getCulture", &CvEventInfo::getCulture, "int ()")
		.def("getEspionagePoints", &CvEventInfo::getEspionagePoints, "int ()")
		.def("getTech", &CvEventInfo::getTech, "int ()")
		.def("getTechPercent", &CvEventInfo::getTechPercent, "int ()")
		.def("getTechCostPercent", &CvEventInfo::getTechCostPercent, "int ()")
		.def("getTechMinTurnsLeft", &CvEventInfo::getTechMinTurnsLeft, "int ()")
		.def("getPrereqTech", &CvEventInfo::getPrereqTech, "int ()")
		.def("getUnitClass", &CvEventInfo::getUnitClass, "int ()")
		.def("getNumUnits", &CvEventTriggerInfo::getNumUnits, "int ()")
		.def("getBuildingClass", &CvEventInfo::getBuildingClass, "int ()")
		.def("getBuildingChange", &CvEventInfo::getBuildingChange, "int ()")
		.def("getHappy", &CvEventInfo::getHappy, "int ()")
		.def("getHealth", &CvEventInfo::getHealth, "int ()")
		.def("getHurryAnger", &CvEventInfo::getHurryAnger, "int ()")
		.def("getHappyTurns", &CvEventInfo::getHappyTurns, "int ()")
		.def("getFood", &CvEventInfo::getFood, "int ()")
		.def("getFoodPercent", &CvEventInfo::getFoodPercent, "int ()")
		.def("getFeature", &CvEventInfo::getFeature, "int ()")
		.def("getFeatureChange", &CvEventInfo::getFeatureChange, "int ()")
		.def("getImprovement", &CvEventInfo::getImprovement, "int ()")
		.def("getImprovementChange", &CvEventInfo::getImprovementChange, "int ()")
		.def("getBonus", &CvEventInfo::getBonus, "int ()")
		.def("getBonusChange", &CvEventInfo::getBonusChange, "int ()")
		.def("getRoute", &CvEventInfo::getRoute, "int ()")
		.def("getRouteChange", &CvEventInfo::getRouteChange, "int ()")
		.def("getBonusRevealed", &CvEventInfo::getBonusRevealed, "int ()")
		.def("getBonusGift", &CvEventInfo::getBonusGift, "int ()")
		.def("getUnitExperience", &CvEventInfo::getUnitExperience, "int ()")
		.def("getUnitImmobileTurns", &CvEventInfo::getUnitImmobileTurns, "int ()")
		.def("getConvertOwnCities", &CvEventInfo::getConvertOwnCities, "int ()")
		.def("getConvertOtherCities", &CvEventInfo::getConvertOtherCities, "int ()")
		.def("getMaxNumReligions", &CvEventInfo::getMaxNumReligions, "int ()")
		.def("getOurAttitudeModifier", &CvEventInfo::getOurAttitudeModifier, "int ()")
		.def("getAttitudeModifier", &CvEventInfo::getAttitudeModifier, "int ()")
		.def("getTheirEnemyAttitudeModifier", &CvEventInfo::getTheirEnemyAttitudeModifier, "int ()")
		.def("getPopulationChange", &CvEventInfo::getPopulationChange, "int ()")
		.def("getRevoltTurns", &CvEventInfo::getRevoltTurns, "int ()")
		.def("getMinPillage", &CvEventInfo::getMinPillage, "int ()")
		.def("getMaxPillage", &CvEventInfo::getMaxPillage, "int ()")
		.def("getUnitPromotion", &CvEventInfo::getUnitPromotion, "int ()")
		.def("getFreeUnitSupport", &CvEventInfo::getFreeUnitSupport, "int ()")
		.def("getInflationModifier", &CvEventInfo::getInflationModifier, "int ()")
		.def("getSpaceProductionModifier", &CvEventInfo::getSpaceProductionModifier, "int ()")
		.def("getAIValue", &CvEventInfo::getAIValue, "int ()")

		.def("getAdditionalEventChance", &CvEventInfo::getAdditionalEventChance, "int (int)")
		.def("getAdditionalEventTime", &CvEventInfo::getAdditionalEventTime, "int (int)")
		.def("getClearEventChance", &CvEventInfo::getClearEventChance, "int (int)")
		.def("getTechFlavorValue", &CvEventInfo::getTechFlavorValue, "int (int)")
		.def("getPlotExtraYield", &CvEventInfo::getPlotExtraYield, "int (int)")
		.def("getFreeSpecialistCount", &CvEventInfo::getFreeSpecialistCount, "int (int)")
		.def("getUnitCombatPromotion", &CvEventInfo::getUnitCombatPromotion, "int (int)")
		.def("getUnitClassPromotion", &CvEventInfo::getUnitClassPromotion, "int (int)")

		.def("getBuildingYieldChange", &CvEventInfo::getBuildingYieldChange, "int (int /*BuildingClassTypes*/, int /*YieldTypes*/)")
		.def("getNumBuildingYieldChanges", &CvEventInfo::getNumBuildingYieldChanges, "int ()")
		.def("getBuildingCommerceChange", &CvEventInfo::getBuildingCommerceChange, "int (int /*BuildingClassTypes*/, int /*CommerceTypes*/)")
		.def("getNumBuildingCommerceChanges", &CvEventInfo::getNumBuildingCommerceChanges, "int ()")
		.def("getBuildingHappyChange", &CvEventInfo::getBuildingHappyChange, "int (int /*BuildingClassTypes*/)")
		.def("getNumBuildingHappyChanges", &CvEventInfo::getNumBuildingHappyChanges, "int ()")
		.def("getBuildingHealthChange", &CvEventInfo::getBuildingHealthChange, "int (int /*BuildingClassTypes*/)")
		.def("getNumBuildingHealthChanges", &CvEventInfo::getNumBuildingHealthChanges, "int ()")
		;

	boost::python::class_<CvEspionageMissionInfo, boost::python::bases<CvInfoBase> >("CvEspionageMissionInfo")
		.def("getCost", &CvEspionageMissionInfo::getCost, "int ()")
		.def("isPassive", &CvEspionageMissionInfo::isPassive, "bool ()")
		.def("isTwoPhases", &CvEspionageMissionInfo::isTwoPhases, "bool ()")
		.def("isTargetsCity", &CvEspionageMissionInfo::isTargetsCity, "bool ()")
		.def("isSelectPlot", &CvEspionageMissionInfo::isSelectPlot, "bool ()")
		.def("getTechPrereq", &CvEspionageMissionInfo::getTechPrereq, "int ()")
		.def("getVisibilityLevel", &CvEspionageMissionInfo::getVisibilityLevel, "int ()")
		.def("isInvestigateCity", &CvEspionageMissionInfo::isInvestigateCity, "bool ()")
		.def("isSeeDemographics", &CvEspionageMissionInfo::isSeeDemographics, "bool ()")
		.def("isNoActiveMissions", &CvEspionageMissionInfo::isNoActiveMissions, "bool ()")
		.def("isSeeResearch", &CvEspionageMissionInfo::isSeeResearch, "bool ()")
		.def("isDestroyImprovement", &CvEspionageMissionInfo::isDestroyImprovement, "bool ()")
		.def("getDestroyBuildingCostFactor", &CvEspionageMissionInfo::getDestroyBuildingCostFactor, "int ()")
		.def("getDestroyUnitCostFactor", &CvEspionageMissionInfo::getDestroyUnitCostFactor, "int ()")
		.def("getBuyUnitCostFactor", &CvEspionageMissionInfo::getBuyUnitCostFactor, "int ()")
		.def("getBuyCityCostFactor", &CvEspionageMissionInfo::getBuyCityCostFactor, "int ()")
		.def("getStealTreasuryTypes", &CvEspionageMissionInfo::getStealTreasuryTypes, "int ()")
		.def("getCityInsertCultureAmountFactor", &CvEspionageMissionInfo::getCityInsertCultureAmountFactor, "int ()")
		.def("getCityInsertCultureCostFactor", &CvEspionageMissionInfo::getCityInsertCultureCostFactor, "int ()")
		.def("getCityPoisonWaterCounter", &CvEspionageMissionInfo::getCityPoisonWaterCounter, "int ()")
		.def("getCityUnhappinessCounter", &CvEspionageMissionInfo::getCityUnhappinessCounter, "int ()")
		.def("getCityRevoltCounter", &CvEspionageMissionInfo::getCityRevoltCounter, "int ()")
		.def("getBuyTechCostFactor", &CvEspionageMissionInfo::getBuyTechCostFactor, "int ()")
		.def("getSwitchCivicCostFactor", &CvEspionageMissionInfo::getSwitchCivicCostFactor, "int ()")
		.def("getSwitchReligionCostFactor", &CvEspionageMissionInfo::getSwitchReligionCostFactor, "int ()")
		.def("getPlayerAnarchyCounter", &CvEspionageMissionInfo::getPlayerAnarchyCounter, "int ()")
		.def("getCounterespionageNumTurns", &CvEspionageMissionInfo::getCounterespionageNumTurns, "int ()")
		.def("getCounterespionageMod", &CvEspionageMissionInfo::getCounterespionageMod, "int ()")
		.def("getDifficultyMod", &CvEspionageMissionInfo::getDifficultyMod, "int ()")
		;

	boost::python::class_<CvVoteSourceInfo, boost::python::bases<CvInfoBase> >("CvVoteSourceInfo")
		.def("getVoteInterval", &CvVoteSourceInfo::getVoteInterval, "int ()")
		.def("getCivic", &CvVoteSourceInfo::getCivic, "int ()")
		.def("getFreeSpecialist", &CvVoteSourceInfo::getFreeSpecialist, "int ()")
		.def("getReligionYield", &CvVoteSourceInfo::getReligionYield, "int (int)")
		.def("getReligionCommerce", &CvVoteSourceInfo::getReligionCommerce, "int (int)")
		.def("getSecretaryGeneralText", &CvVoteSourceInfo::pyGetSecretaryGeneralText, "wstring ()")
		;

	boost::python::class_<CvMainMenuInfo, boost::python::bases<CvInfoBase> >("CvMainMenuInfo")
		.def("getScene", &CvMainMenuInfo::getScene, "string ()")
		.def("getSceneNoShader", &CvMainMenuInfo::getSceneNoShader, "string ()")
		.def("getSoundtrack", &CvMainMenuInfo::getSoundtrack, "string ()")
		.def("getLoading", &CvMainMenuInfo::getLoading, "string ()")
		.def("getLoadingSlideshow", &CvMainMenuInfo::getLoadingSlideshow, "string ()")
		;

}
