#include "CvGameCoreDLL.h"
#include "CyArtFileMgr.h"
#include "CvInfos.h"

//
// published python interface for CyArea
//

void CyArtFileMgrPythonInterface()
{
	OutputDebugString("Python Extension Module - CyArtFileMgrPythonInterface\n");

	boost::python::class_<CyArtFileMgr>("CyArtFileMgr")
		.def("isNone", &CyArtFileMgr::isNone, "bool () - Checks to see if pointer points to a real object")

		.def("Reset", &CyArtFileMgr::Reset, "void ()")
		.def("buildArtFileInfoMaps", &CyArtFileMgr::buildArtFileInfoMaps, "void ()")

		.def("getInterfaceArtInfo", &CyArtFileMgr::getInterfaceArtInfo,  boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoInterface ()")
		.def("getMovieArtInfo", &CyArtFileMgr::getMovieArtInfo,  boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoMovie ()")
		.def("getMiscArtInfo", &CyArtFileMgr::getMiscArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoMisc ()")
		.def("getUnitArtInfo", &CyArtFileMgr::getUnitArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoUnit ()")
		.def("getBuildingArtInfo", &CyArtFileMgr::getBuildingArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoBuilding ()")
		.def("getCivilizationArtInfo", &CyArtFileMgr::getCivilizationArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoCivilization ()")
		.def("getLeaderheadArtInfo", &CyArtFileMgr::getLeaderheadArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoLeaderhead ()")
		.def("getBonusArtInfo", &CyArtFileMgr::getBonusArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoBonus ()")
		.def("getImprovementArtInfo", &CyArtFileMgr::getImprovementArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoImprovement ()")
		.def("getTerrainArtInfo", &CyArtFileMgr::getTerrainArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoTerrain ()")
		.def("getFeatureArtInfo", &CyArtFileMgr::getFeatureArtInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CvArtInfoFeature ()")
	;
}

