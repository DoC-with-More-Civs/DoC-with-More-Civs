//
// published python interface for CyGlobalContext
//

#include "CvGameCoreDLL.h"
#include "CyMap.h"
#include "CyPlayer.h"
#include "CyGame.h"
#include "CyGlobalContext.h"
#include "CvRandom.h"
//#include "CvStructs.h"
#include "CvInfos.h"
#include "CyTeam.h"

void CyGlobalContextPythonInterface3(boost::python::class_<CyGlobalContext>& x)
{
	OutputDebugString("Python Extension Module - CyGlobalContextPythonInterface3\n");

	x
		.def("getAttitudeInfo", &CyGlobalContext::getAttitudeInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "AttitudeInfo (int id)")
		.def("getMemoryInfo", &CyGlobalContext::getMemoryInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "MemoryInfo (int id)")

		.def("getNumPlayerOptionInfos", &CyGlobalContext::getNumPlayerOptionInfos)
		.def("getPlayerOptionsInfo", &CyGlobalContext::getPlayerOptionsInfoByIndex, boost::python::return_value_policy<boost::python::reference_existing_object>(), "(PlayerOptionsInfoID) - PlayerOptionsInfo for PlayerOptionsInfo")
		.def("getPlayerOptionsInfoByIndex", &CyGlobalContext::getPlayerOptionsInfoByIndex, boost::python::return_value_policy<boost::python::reference_existing_object>(), "(PlayerOptionsInfoID) - PlayerOptionsInfo for PlayerOptionsInfo")

		.def("getGraphicOptionsInfo", &CyGlobalContext::getGraphicOptionsInfoByIndex, boost::python::return_value_policy<boost::python::reference_existing_object>(), "(GraphicOptionsInfoID) - GraphicOptionsInfo for GraphicOptionsInfo")
		.def("getGraphicOptionsInfoByIndex", &CyGlobalContext::getGraphicOptionsInfoByIndex, boost::python::return_value_policy<boost::python::reference_existing_object>(), "(GraphicOptionsInfoID) - GraphicOptionsInfo for GraphicOptionsInfo")

		.def("getNumHurryInfos", &CyGlobalContext::getNumHurryInfos, "() - Total Hurry Infos")

		.def("getNumConceptInfos", &CyGlobalContext::getNumConceptInfos, "int () - NumConceptInfos")
		.def("getConceptInfo", &CyGlobalContext::getConceptInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "Concept Info () - Returns info object")

		.def("getNumNewConceptInfos", &CyGlobalContext::getNumNewConceptInfos, "int () - NumNewConceptInfos")
		.def("getNewConceptInfo", &CyGlobalContext::getNewConceptInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "New Concept Info () - Returns info object")

		.def("getNumCityTabInfos", &CyGlobalContext::getNumCityTabInfos, "int () - Returns NumCityTabInfos")
		.def("getCityTabInfo", &CyGlobalContext::getCityTabInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CityTabInfo - () - Returns Info object")

		.def("getNumCalendarInfos", &CyGlobalContext::getNumCalendarInfos, "int () - Returns NumCalendarInfos")
		.def("getCalendarInfo", &CyGlobalContext::getCalendarInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "CalendarInfo () - Returns Info object")
		 
		.def("getNumGameOptionInfos", &CyGlobalContext::getNumGameOptionInfos, "int () - Returns NumGameOptionInfos")
		.def("getGameOptionInfo", &CyGlobalContext::getGameOptionInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "GameOptionInfo () - Returns Info object")

		.def("getNumMPOptionInfos", &CyGlobalContext::getNumMPOptionInfos, "int () - Returns NumMPOptionInfos")
		.def("getMPOptionInfo", &CyGlobalContext::getMPOptionInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "MPOptionInfo () - Returns Info object")

		.def("getNumForceControlInfos", &CyGlobalContext::getNumForceControlInfos, "int () - Returns NumForceControlInfos")
		.def("getForceControlInfo", &CyGlobalContext::getForceControlInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "ForceControlInfo () - Returns Info object")

		.def("getNumSeasonInfos", &CyGlobalContext::getNumSeasonInfos, "int () - Returns NumSeasonInfos")
		.def("getSeasonInfo", &CyGlobalContext::getSeasonInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "SeasonInfo () - Returns Info object")

		.def("getNumMonthInfos", &CyGlobalContext::getNumMonthInfos, "int () - Returns NumMonthInfos")
		.def("getMonthInfo", &CyGlobalContext::getMonthInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "MonthInfo () - Returns Info object")

		.def("getNumDenialInfos", &CyGlobalContext::getNumDenialInfos, "int () - Returns NumDenialInfos")
		.def("getDenialInfo", &CyGlobalContext::getDenialInfo, boost::python::return_value_policy<boost::python::reference_existing_object>(), "DenialInfo () - Returns Info object")
		;
}
