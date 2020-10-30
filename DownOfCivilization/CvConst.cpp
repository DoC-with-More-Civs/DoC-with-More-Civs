#include "DownOfCivilization.h"
#include "config_pymodules.h"
#include "config_py2cpp.h"

CvConst::CvConst() {

	// for empty Player list
	std::vector<PlayerTypes> _empty_;

	// for congresses and Victory 

	m_lCivGroups = (list_of
	((list_of(iGreece), iRome, iByzantium, iVikings, iMoors, iSpain, iFrance, iEngland, iHolyRome, iRussia, iKhazars, iKievanRus, iNetherlands, iItaly, iPoland, iPortugal, iGermany, iSweden, iHungary, iNovgorod, iCeltia, iLithuania)), // Europeans
		(list_of(iIndia), iChina, iHarappa, iPolynesia, iPersia, iJapan, iTamils, iKorea, iByzantium, iTibet, iKhmer, iIndonesia, iRussia, iKievanRus, iMongolia, iMughals, iThailand, iTurks, iKhazars, iVietnam, iManchuria, iKhitan, iPhilippines, iBurma, iYuezhi, iXiongnu), // Asian
		(list_of(iEgypt), iBabylonia, iAssyria, iHittites, iPersia, iByzantium, iArabia, iTatar, iOttomans, iCarthage, iTurks, iKhazars, iMamluks, iIsrael, iOman, iYemen), // Middle Eastern
		(list_of(iEgypt), iCarthage, iEthiopia, iMali, iCongo, iSwahili, iZimbabwe, iNigeria, iBoers, iNubia, iChad), // African
		(list_of(iNorteChico), iOlmecs, iMississippi, iInuit, iTiwanaku, iWari, iMuisca, iMaya, iTeotihuacan, iInca, iAztecs, iAmerica, iArgentina, iBrazil, iAustralia, iCanada) // American
		);

	m_lCivStabilityGruops = (list_of
	((list_of(iVikings), iSpain, iFrance, iEngland, iHolyRome, iRussia, iNovgorod, iKievanRus, iNetherlands, iPoland, iPortugal, iItaly, iGermany, iSweden, iHungary, iCeltia, iLithuania)), // Europeans
		(list_of(iIndia), iChina, iHarappa, iPolynesia, iJapan, iKorea, iTibet, iKhmer, iIndonesia, iMongolia, iThailand, iTamils, iVietnam, iManchuria, iKhitan, iPhilippines, iBurma, iYuezhi, iXiongnu), // Asian
		(list_of(iBabylonia), iAssyria, iHittites, iPersia, iArabia, iOttomans, iTatar, iMughals, iTurks, iKhazars, iMamluks, iIsrael, iOman, iYemen), // Middle Eastern
		(list_of(iEgypt), iGreece, iCarthage, iRome, iEthiopia, iArmenia, iByzantium, iMoors, iMali, iCongo, iZimbabwe, iNigeria, iSwahili, iBoers, iNubia, iChad), // Mediterranean
		(list_of(iNorteChico), iOlmecs, iMississippi, iInuit, iTiwanaku, iWari, iMuisca, iMaya, iTeotihuacan, iInca, iAztecs, iAmerica, iArgentina, iBrazil, iAustralia, iCanada) // American
		);

	m_lTechGroups = (list_of
	((list_of(iRome), iGreece, iByzantium, iVikings, iSpain, iFrance, iEngland, iHolyRome, iRussia, iNovgorod, iKievanRus, iNetherlands, iPoland, iPortugal, iItaly, iGermany, iAmerica, iArgentina, iBrazil, iCanada, iSweden, iAustralia, iBoers, iHungary, iIsrael, iCeltia, iLithuania)), // Europe and NA
		(list_of(iEgypt), iBabylonia, iHarappa, iAssyria, iHittites, iIndia, iCarthage, iPersia, iEthiopia, iArmenia, iArabia, iMoors, iMali, iOttomans, iMughals, iTatar, iTamils, iCongo, iTurks, iKhazars, iMamluks, iNigeria, iSwahili, iZimbabwe, iOman, iYemen, iNubia, iChad), // Middle East
		(list_of(iChina), iKorea, iJapan, iTibet, iKhmer, iIndonesia, iMongolia, iThailand, iManchuria, iKhitan, iVietnam, iPhilippines, iBurma, iYuezhi, iXiongnu), // Far East
		(list_of(iNorteChico), iOlmecs, iMississippi, iInuit, iTiwanaku, iWari, iMuisca, iPolynesia, iMaya, iTeotihuacan, iInca, iAztecs) // Native America
		);

	m_lCivBioOldWorld = (
		list_of(iEgypt), iIndia, iChina, iBabylonia, iHarappa, iGreece, iPolynesia, iPersia, iCarthage, iRome, iJapan, iTamils, iAssyria,
		iHittites, iArmenia, iEthiopia, iKorea, iByzantium, iVikings, iTurks, iArabia, iTibet, iKhmer, iIndonesia, iMoors, iSpain, iFrance,
		iEngland, iHolyRome, iRussia, iKievanRus, iNetherlands, iMali, iOttomans, iPoland, iPortugal, iItaly, iMongolia, iAmerica, iMughals,
		iThailand, iCongo, iGermany, iSweden, iAustralia, iBoers, iMamluks, iManchuria, iNigeria, iPhilippines, iSwahili, iVietnam, iZimbabwe,
		iBurma, iHungary, iOman, iKhitan, iYemen, iKhazars, iNubia, iChad, iNovgorod, iTatar, iYuezhi, iXiongnu, iLithuania, iIndependent,
		iIndependent2, iCeltia, iBarbarian
		);

	m_lCivBioNewWorld = (
		list_of(iNorteChico), iOlmecs, iMississippi, iInuit, iTiwanaku, iWari, iMuisca, iMaya, iTeotihuacan, iInca, iAztecs
		);

	// neighbors
	push_back(m_lNeighbours) // 空项初始化 : 第一项要双括号
		((list_of(iBabylonia), iNubia, iAssyria, iHittites, iGreece, iPersia, iCarthage, iRome, iEthiopia, iByzantium, iArabia, iMoors, iOttomans, iMamluks, iOman, iYemen, iNubia, iChad)), // Egypt
		(list_of(iEgypt), iAssyria, iHittites, iGreece, iCarthage, iPersia, iArmenia, iTurks, iOttomans, iMongolia, iCarthage, iByzantium, iOman), // Babylonia
		(list_of(iIndia), iPersia, iTamils, iTibet, iMughals), // Harappa
		(list_of(iTiwanaku), iWari, iMuisca, iInca), // Norte Chico 
		(list_of(iEgypt), iEthiopia, iArabia, iOman, iYemen, iMamluks, iMali, iZimbabwe, iNigeria, iCongo, iChad), // Nubia
		(list_of(iEgypt), iBabylonia, iHittites, iGreece, iCarthage, iPersia, iArmenia), //  Assyria
		(list_of(iIndia), iJapan, iKorea, iTurks, iTibet, iKhmer, iMongolia, iThailand, iManchuria, iPhilippines, iKhitan, iBurma, iYuezhi, iXiongnu), // China 
		(list_of(iEgypt), iBabylonia, iAssyria, iGreece, iCarthage, iPersia, iArmenia), //  Hittites
		(list_of(iAssyria), iHittites, iPersia, iCarthage, iRome, iByzantium, iHolyRome, iRussia, iKievanRus, iOttomans, iItaly, iKhazars), // Greece
		(list_of(iTeotihuacan), iMaya, iAztecs), // Olmecs
		(list_of(iChina), iHarappa, iPersia, iTamils, iTibet, iKhmer, iMongolia, iMughals, iThailand, iVietnam, iBurma, iYuezhi), // India
		(list_of(iEgypt), iBabylonia, iAssyria, iHittites, iGreece, iRome, iSpain, iMali, iPortugal, iBabylonia, iPersia, iArabia, iMoors, iOttomans, iItaly, iMamluks), // Carthage
		(list_of(iRome), iVikings, iFrance, iHolyRome, iNetherlands), // Celtia
		(_empty_), //  Polynesia
		(list_of(iIndia), iBabylonia, iHarappa, iAssyria, iHittites, iGreece, iArmenia, iTurks, iByzantium, iOttomans, iMongolia, iCarthage, iMughals, iMamluks, iOman, iYemen, iKhazars, iYuezhi), // Persia
		(list_of(iIndia), iBabylonia, iHarappa, iAssyria, iHittites, iGreece, iArmenia, iTurks, iByzantium, iOttomans, iMongolia, iCarthage, iMughals, iMamluks, iOman, iYemen, iKhazars, iYuezhi), // Rome
		(list_of(iEgypt), iBabylonia, iGreece, iCarthage, iCeltia, iSpain, iFrance, iHolyRome, iPortugal, iItaly, iGermany, iHungary, iXiongnu),
		(list_of(iIndia), iTurks, iXiongnu, iChina, iPersia), // Yuezhi
		(list_of(iOlmecs), iSpain, iTeotihuacan, iInca, iAztecs, iAmerica), // Maya
		(list_of(iHarappa), iIndia, iKhmer, iIndonesia, iMughals, iThailand, iVietnam, iPhilippines), // Tamils
		(list_of(iChina), iKorea, iMongolia, iYuezhi, iRome), // Xiongnu
		(list_of(iEgypt), iNubia, iArabia, iMali, iCongo, iMamluks, iNigeria, iSwahili, iZimbabwe, iOman, iYemen, iNubia), // Ethiopia
		(list_of(iChina), iKhmer, iThailand, iTamils, iIndia, iIndonesia, iTibet, iPhilippines, iBurma), // Vietnam
		(list_of(iOlmecs), iSpain, iMaya, iInca, iAztecs, iAmerica), // Teotihuacan
		(list_of(iBabylonia), iAssyria, iHittites, iPersia, iByzantium, iOttomans, iKhazars), //  Armenia
		(list_of(iCanada), iAmerica), //  Inuit
		(list_of(iCanada), iAmerica), //  Mississippi
		(list_of(iChina), iJapan, iKhitan, iMongolia, iManchuria, iXiongnu), // Korea
		(list_of(iNorteChico), iWari, iInca), // Tiwanaku
		(list_of(iEgypt), iBabylonia, iGreece, iPersia, iArmenia, iArabia, iRussia, iKievanRus, iOttomans, iTurks, iMamluks, iHungary, iKhazars), // Byzantium
		(list_of(iNorteChico), iTiwanaku, iMuisca, iInca), // Wari
		(list_of(iChina), iKorea, iKhmer, iMongolia, iThailand, iManchuria, iPhilippines), // Japan
		(list_of(iCeltia), iFrance, iEngland, iHolyRome, iRussia, iKievanRus, iPoland, iNetherlands, iGermany, iNovgorod, iKhazars), // Vikings
		(list_of(iChina), iBabylonia, iPersia, iMughals, iOttomans, iByzantium, iMongolia, iTibet, iMamluks, iOman, iYemen, iKhazars, iYuezhi), //  Turks
		(list_of(iEgypt), iNubia, iBabylonia, iPersia, iEthiopia, iByzantium, iOttomans, iCarthage, iMamluks, iIsrael, iOman, iYemen, iKhazars, iNubia, iChad), // Arabia
		(list_of(iChina), iHarappa, iIndia, iMongolia, iMughals, iTurks, iVietnam), // Tibet
		(list_of(iIndia), iJapan, iKhmer, iThailand, iTamils, iPhilippines, iVietnam, iBurma), // Indonesia
		(list_of(iChina), iKhmer, iThailand, iTamils, iIndia, iIndonesia, iTibet, iPhilippines, iVietnam), // Burma
		(list_of(iGreece), iPersia, iArmenia, iTurks, iKievanRus, iHungary, iByzantium, iMongolia, iArabia, iRussia, iOttomans, iVikings, iNovgorod, iTatar, iSweden), // Khazars
		(list_of(iEgypt), iNubia, iNigeria, iArabia, iOttomans, iMamluks, iMali, iCongo), // Chad
		(list_of(iEgypt), iSpain, iPortugal, iMali, iMamluks), // Moors
		(list_of(iCarthage), iRome, iMoors, iFrance, iEngland, iPortugal), // Spain
		(list_of(iCeltia), iRome, iVikings, iSpain, iEngland, iHolyRome, iNetherlands, iPortugal, iItaly, iGermany), // France
		(list_of(iEgypt), iBabylonia, iPersia, iTurks, iArabia, iMamluks, iIsrael, iSwahili, iEthiopia, iOttomans, iYemen, iNubia), // Oman
		(list_of(iChina), iKorea, iMongolia, iManchuria), // Khitan
		(list_of(iIndia), iChina, iTamils, iJapan, iIndonesia, iThailand, iPhilippines, iVietnam, iBurma), // Khmer
		(list_of(iNorteChico), iWari, iInca), // Muisca
		(list_of(iEgypt), iBabylonia, iPersia, iTurks, iArabia, iMamluks, iIsrael, iSwahili, iEthiopia, iOttomans, iOman, iNubia), // Yemen
		(list_of(iCeltia), iRome, iVikings, iSpain, iFrance, iHolyRome, iNetherlands, iGermany), // England
		(list_of(iCeltia), iRome, iVikings, iFrance, iEngland, iNetherlands, iItaly, iPoland, iLithuania, iSweden, iGermany, iHungary), // Holy Rome
		(list_of(iVikings), iPoland, iLithuania, iSweden, iRussia, iKievanRus, iHungary, iTatar, iKhazars), //  Novgorod
		(list_of(iPersia), iByzantium, iVikings, iPoland, iLithuania, iOttomans, iMongolia, iSweden, iGermany, iRussia, iHungary, iNovgorod, iTatar, iKhazars), // Kievan Rus
		(list_of(iHolyRome), iRussia, iKievanRus, iGermany, iPoland, iLithuania, iOttomans, iByzantium, iMongolia, iNovgorod, iTatar, iKhazars), // Hungary
		(list_of(iChina), iTamils, iJapan, iIndonesia, iKhmer, iThailand, iVietnam, iBurma), // Philippines
		(list_of(iEthiopia), iMali, iCongo, iNigeria, iZimbabwe, iOman, iYemen), //  Swahili
		(list_of(iPersia), iCarthage, iEthiopia, iByzantium, iArabia, iMoors, iOttomans, iEgypt, iOman, iYemen, iNubia, iChad), // Mamluks
		(list_of(iEgypt), iCarthage, iEthiopia, iMoors, iCongo, iNigeria, iSwahili, iZimbabwe, iNubia, iChad), // Mali
		(list_of(iVikings), iHolyRome, iRussia, iKievanRus, iSweden, iGermany, iNovgorod, iTatar, iLithuania, iHungary), // Poland
		(list_of(iEthiopia), iMali, iCongo, iNigeria, iSwahili, iNubia), // Zimbabwe
		(list_of(iCarthage), iRome, iSpain, iFrance), // Portugal
		(list_of(iSpain), iTiwanaku, iWari, iMuisca, iAztecs, iAmerica, iArgentina, iBrazil), // Inca
		(list_of(iGreece), iCarthage, iRome, iFrance, iHolyRome), // Italy
		(list_of(iMali), iCongo, iEthiopia, iSwahili, iZimbabwe, iNubia, iChad), // Nigeria
		(list_of(iHolyRome), iRussia, iKievanRus, iNovgorod, iSweden, iGermany, iHungary, iPoland), // Lithuania
		(list_of(iIndia), iChina, iPersia, iJapan, iKorea, iTibet, iRussia, iKievanRus, iOttomans, iTurks, iKhitan, iManchuria, iHungary, iTatar, iKhazars, iXiongnu), // Mongolia
		(list_of(iOlmecs), iSpain, iTeotihuacan, iInca, iAmerica), // Aztec
		(list_of(iHarappa), iIndia, iPersia, iTamils, iTibet, iTurks), // Mughals
		(list_of(iPoland), iOttomans, iMongolia, iSweden, iRussia, iKievanRus, iHungary, iNovgorod, iKhazars), //  Tatar
		(list_of(iBabylonia), iGreece, iPersia, iArmenia, iByzantium, iRussia, iKievanRus, iMongolia, iCarthage, iTurks, iMamluks, iHungary, iIsrael, iOman, iYemen, iTatar, iKhazars, iChad), // Ottomans
		(list_of(iPersia), iByzantium, iVikings, iPoland, iLithuania, iOttomans, iMongolia, iSweden, iGermany, iKievanRus, iHungary, iNovgorod, iTatar, iKhazars), // Russia
		(list_of(iIndia), iChina, iJapan, iIndonesia, iKhmer, iTamils, iPhilippines, iVietnam), // Thailand
		(list_of(iEthiopia), iMali, iSwahili, iNigeria, iZimbabwe, iNubia, iChad), // Congo
		(list_of(iVikings), iHolyRome, iRussia, iKievanRus, iPoland, iLithuania, iGermany, iNovgorod, iTatar, iKhazars), //  Sweden
		(list_of(iCeltia), iVikings, iFrance, iEngland, iHolyRome, iGermany), // Netherlands
		(list_of(iRome), iVikings, iFrance, iEngland, iHolyRome, iRussia, iKievanRus, iPoland, iLithuania, iSweden, iNetherlands, iHungary), // Germany
		(list_of(iChina), iKorea, iJapan, iKhitan, iMongolia), // Manchuria
		(list_of(iJapan), iSpain, iFrance, iEngland, iRussia, iKievanRus, iInca, iAztecs, iMississippi, iInuit), // America
		(list_of(iSpain), iPortugal, iInca, iBrazil), // Argentina
		(list_of(iSpain), iPortugal, iInca, iArgentina), // Brazil
		(list_of(iJapan), iIndonesia, iEngland, iNetherlands, iAmerica), // Australia
		(list_of(iCongo), iEngland, iNetherlands, iPortugal, iEthiopia), // Boers
		(list_of(iAmerica), iMississippi, iInuit), // Canada
		(list_of(iEgypt), iArabia, iOttomans, iOman, iYemen) // Israel
		;

	// for stability hit on spawn
	push_back(m_lOlderNeighbours)
		((_empty_)), // Egypt
		(_empty_), // Babylonia
		(_empty_), // Harappa
		(_empty_), // Norte Chico
		(list_of(iEgypt)), // Nubia
		(list_of(iEgypt), iBabylonia), //  Assyria
		(_empty_), // China
		(_empty_), // Hittites
		(list_of(iEgypt), iBabylonia), // Greece
		(_empty_), // Olmecs
		(list_of(iHarappa)), // India
		(list_of(iEgypt), iBabylonia), // Carthage
		(_empty_), // Celtia
		(_empty_), //  Polynesia
		(list_of(iEgypt), iBabylonia, iAssyria, iHarappa, iGreece), // Persia
		(list_of(iEgypt), iGreece, iCarthage), // Rome
		(_empty_), //  Yuezhi
		(list_of(iOlmecs)), // Maya
		(list_of(iHarappa), iIndia), // Tamils
		(list_of(iChina), iYuezhi), // Xiongnu
		(list_of(iEgypt), iNubia), // Ethiopia
		(_empty_), // Vietnam
		(list_of(iMaya)), // Teotihuacan
		(list_of(iBabylonia), iAssyria, iGreece), //  Armenia
		(_empty_), // Inuit
		(_empty_), //  Mississippi
		(list_of(iChina), iXiongnu), // Korea
		(list_of(iNorteChico)), // Tiwanaku
		(list_of(iGreece)), // Byzantium
		(list_of(iNorteChico), iTiwanaku), // Wari
		(list_of(iKorea)), // Japan
		(list_of(iCeltia)), // Vikings
		(list_of(iChina), iPersia, iYuezhi), //  Turks
		(list_of(iEgypt), iPersia, iByzantium, iNubia), // Arabia
		(list_of(iChina), iHarappa, iIndia, iVietnam), // Tibet
		(list_of(iKhmer), iVietnam), // Indonesia
		(list_of(iIndia), iVietnam, iKhmer), // Burma
		(list_of(iGreece), iPersia, iArabia, iTurks, iVikings), // Khazars
		(list_of(iEgypt), iNubia, iArabia), // Chad
		(_empty_), // Moors
		(list_of(iCarthage), iRome), // Spain
		(list_of(iRome)), // France
		(list_of(iEgypt), iBabylonia, iPersia, iTurks, iEthiopia, iNubia), // Oman
		(_empty_), // Khitan
		(list_of(iIndia), iVietnam), // Khmer
		(list_of(iNorteChico), iWari), // Muisca
		(list_of(iEgypt), iBabylonia, iPersia, iTurks, iEthiopia, iOman, iNubia), // Yemen
		(_empty_), // England
		(list_of(iGreece), iRome, iVikings), // Holy Rome
		(_empty_), //  Novgorod
		(list_of(iPersia), iGreece, iByzantium, iKhazars), // Kievan Rus
		(list_of(iByzantium), iKievanRus, iHolyRome, iKhazars), //  Hungary
		(list_of(iIndonesia), iKhmer), //  Philippines
		(list_of(iEthiopia), iOman, iYemen, iNubia), // Swahili
		(list_of(iByzantium), iEthiopia, iArabia, iOman, iYemen, iNubia, iChad), // Mamluks
		(list_of(iCarthage), iEthiopia, iArabia, iMoors, iNubia, iChad), // Mali
		(list_of(iVikings), iHolyRome, iHungary), // Poland
		(list_of(iNubia)), // Zimbabwe
		(list_of(iCarthage), iRome), // Portugal
		(list_of(iNorteChico), iTiwanaku, iWari, iMuisca), // Inca
		(list_of(iByzantium), iHolyRome), // Italy
		(list_of(iMali), iNubia, iChad), // Nigeria
		(list_of(iHolyRome), iHungary, iPoland), // Lithuania
		(list_of(iChina), iJapan, iKorea, iArabia, iTibet, iKhmer, iTurks, iKhazars, iXiongnu), // Mongolia
		(list_of(iMaya), iTeotihuacan), // Aztec
		(list_of(iHarappa), iIndia, iPersia, iArabia, iTibet, iTurks), // Mughals
		(list_of(iNovgorod), iKievanRus, iHungary, iPoland), //  Tatar
		(list_of(iBabylonia), iGreece, iPersia, iByzantium, iArabia, iTurks, iMamluks, iHungary, iOman, iYemen, iKhazars, iChad), // Ottomans
		(list_of(iPersia), iGreece, iByzantium, iKievanRus, iHungary, iNovgorod, iTatar, iKhazars), // Russia
		(list_of(iIndia), iChina, iJapan, iKhmer, iIndonesia, iVietnam, iPhilippines, iBurma), // Thailand
		(list_of(iNigeria), iNubia, iChad), // Congo
		(list_of(iVikings), iKhazars), // Sweden
		(list_of(iRome), iHolyRome), // Netherlands
		(list_of(iChina), iMongolia), // Manchuria
		(list_of(iHolyRome), iPoland, iLithuania, iHungary), // Germany
		(list_of(iSpain), iFrance, iEngland, iNetherlands, iPortugal, iAztecs, iMaya, iMississippi, iInuit), // America
		(list_of(iSpain), iPortugal, iInca), // Argentina
		(list_of(iSpain), iPortugal, iInca), // Brazil
		(list_of(iEngland), iNetherlands), //  Australia
		(list_of(iEngland), iNetherlands), // Boers
		(list_of(iAmerica), iMississippi, iInuit), // Canada
		(list_of(iEgypt), iArabia, iOttomans, iOman, iYemen) // Israel
		;

	// civ birth dates
	m_tBirth = (
		list_of(-3000), // 0, // 3000BC	// Egypt
		-3000, // 0, // 3000BC	// Babylonia
		-3000,					// Harappa
		-3000,					// Norte Chico
		-2500,					// Nubia
		-2100,					// Assyria
		-2100,					// China
		-1900,					// Hittites
		-1600, // 50, //1600BC	// Greece
		-1600, 					// Olmecs
		-1500, // 0, // 3000BC	// India
		-1200, // 66, // 814BC  // Leoreth: 1200 BC	// Carthage
		-1200, 					// Celtia
		-1000,					// Polynesia
		-850, // 84, // 844BC	// Persia
		-753, // 90, // 753BC	// Rome
		-650,					// Yuezhi
		-400, 					// Maya
		-300,					// Tamils
		-300,					// Xiongnu
		-290, // 121, // 300BC	// Ethiopia
		-257,					// Vietnam
		-200, 					// Teotihuacan
		-200, 					// Armenia
		-200,					// Inuit
		-100,					// Mississippi
		-50,					// Korea
		110,					// Tiwanaku
		330,					// Byzantium
		400,					// Wari
		525, // 97, // 660BC	// Japan
		551, // 177, // 551AD	// Vikings
		552,					// Turks
		620, // 183, // 622AD	// Arabia
		630,					// Tibet
		650,					// Indonesia
		650, 		// 849AD	// Burma
		650, 					// Khazars
		700,					// Chad
		711,					// Moors
		722, // 193, // 718AD	// Spain
		750, // 196, // 751AD	// France
		751,					// Oman
		760,                    // Khitan
		800, // 187, // 657AD	// Khmer
		800,					// Muisca
		819,					// Yemen
		820, // 203, // 829AD	// England
		840, // 205, //843AD	// Holy Rome
		860, // 205, //843AD	// Novgorod
		882,					// Kievan Rus
		895,					// Hungary
		900,					// Philippines
		960, // 218				// Swahili
		969,					// Mamluks
		989, // 220, // 989AD	// Mali
		1025,					// Poland
		1075,					// Zimbabwe
		1130, // 234, // 1128AD	// Portugal
		1150, // 236, // 1150AD	// Inca
		1167, // Italy			// Italy
		1180,					// Nigeria
		1180,					// Lithuania
		1190, // 240, // 1190AD	// Mongolia
		1195, // 241, // 1195AD	// Aztecs
		1206,					// Mughals
		1210,					// Tatar
		1280, // 249, // 1280AD (1071AD)	// Turkey
		1283, // previously 860AD			// Russia
		1350,					// Thailand
		1390,					// Congo
		1523,					// Sweden
		1580, // 281, // 922AD  // Leoreth: 1500 AD	// Netherlands
		1636,					// Manchuria
		1700,					// Germany
		1775, // 346, // 1775AD // 332 for 1733AD	// America
		1810,					// Argentina
		1822,					// Brazil
		1850,					// Australia
		1852,					// Boers
		1867,					// Canada
		1948,					// Israel
		-3000, // 0,
		-3000, // 0,
		-3000, // 0,
		-3000, // 0,
		-3000, // 0,
		-3000
		);

	// Leoreth: stability penalty from this date on
	m_tFall = (
		list_of(-343),					// Egypt
		-539,					// Babylonia
		-1700,					// Harappa
		-1800,					// Norte Chico
		-1500,					// Nubia
		-600,					// Assyria
		1127,					// China
		-700,					// Hittites
		-146,					// Greece
		-400,					// Olmecs
		600, // end of Gupta Empire		// India
		-146,					// Phoenicia
		100,					// Celtia
		1200,					// Polynesia
		651,					// Persia
		235, // crisis of the third century	// Rome
		374,					// Yuezhi
		900,					// Maya
		1000,					// Tamils
		480,					// Xiongnu
		960,					// Ethiopia
		602,					// Vietnam
		550, //fall of Teotihuacan // Teotihuacan
		430,					// Armenia
		1650,							// Inuit
		1540,							// Mississippi
		1255, // Mongol invasion		// Korea
		900,							// Tiwanaku
		1204, // fourth crusade			// Byzantium
		1100,					// Wari
		2020,					// Japan
		1300,					// Vikings
		1507,					// Turks
		900,					// Arabia
		1500,					// Tibet
		1500,					// Indonesia
		1824,					// Burma
		1241,					// Khazars
		1897,					// Chad
		1500,					// Moors
		2020,					// Spain
		2020,					// France
		1856,					// Oman
		1260,                                                          //Khitan
		1200, // earlier so that the Thai can spawn // Khmer
		1540,					// Muisca
		1517,					// Yemen
		2020,					// England
		2020, // 1648,			// Holy Rome
		1478,					// Novgorod
		2020,					// Hungary
		1240,					// Kievan Rus
		1570,					// Philippines
		1600,					// Swahili
		1517,					// Mamluks
		1600,					// Mali
		1650,					// Poland
		1760,					// Zimbabwe
		2020,					// Portugal
		1533,					// Inca
		2020,					// Italy
		1897,					// Nigeria
		2020,					// Lithuania
		1368,					// Mongolia
		1521,					// Aztecs
		1640,					// Mughals
		1480,					// Tatar
		2020,					// Turkey
		2020,					// Russia
		2020,					// Thailand
		1800,					// Congo
		2020,					// Sweden
		2020,					// Netherlands
		1912,					// Manchuria
		2020,					// Germany
		2020,					// America
		2020,					// Argentina
		2020,					// Brazil
		2020,					// Australia
		2020,					// Boers
		2020,					// Canada
		2020					// Israel
		);

	m_dVictoryYears = map_list_of
	(iCivEgypt, (list_of(-850), -100, 170))
		(iCivBabylonia, (list_of(-1), -850, -700))
		(iCivHarappa, (list_of(-1600), -1500, -800))
		(iCivNorteChico, (list_of(-1), -1, -1))
		(iCivNubia, (list_of(-656), 1365, 1821))
		(iCivAssyria, (list_of(-1), -1, -1))
		(iCivChina, (list_of(1000), -1, 1800))
		(iCivHittites, (list_of(-1), -1, -1))
		(iCivGreece, (list_of(-1), -330, -250))
		(iCivOlmecs, (list_of(-400), -400, -1))
		(iCivIndia, (list_of(-100), 700, 1200))
		(iCivCarthage, (list_of(-300), -100, 200))
		(iCivCeltia, (list_of(-270), -280, 800))
		(iCivPolynesia, (list_of(800), 1000, 1200))
		(iCivPersia, (list_of(140), 350, 350))
		(iCivRome, (list_of(100), 320, -1))
		(iCivYuezhi, (list_of(30), 200, 400))
		(iCivMaya, (list_of(200), 900, -1))
		(iCivTamils, (list_of(800), 1000, 1200))
		(iCivXiongnu, (list_of(210), 210, 560))
		(iCivEthiopia, (list_of(400), 1200, 1500))
		(iCivVietnam, (list_of(-1), 1500, 1950))
		(iCivTeotihuacan, (list_of(550), 550, 1000))
		(iCivArmenia, (list_of(-1), -1, -1))
		(iCivInuit, (list_of(900), -1, -1))
		(iCivMississippi, (list_of(500), 1070, 1400))
		(iCivKorea, (list_of(1200), -1, -1))
		(iCivTiwanaku, (list_of(900), 1000, 1100))
		(iCivByzantium, (list_of(1000), 1200, 1450))
		(iCivWari, (list_of(900), 1000, 1100))
		(iCivJapan, (list_of(1600), 1940, -1))
		(iCivChalukya, (list_of(-1), -1, -1))
		(iCivVikings, (list_of(1050), 1100, 1500))
		(iCivTurks, (list_of(900), 1100, 1400))
		(iCivArabia, (list_of(1300), 1300, -1))
		(iCivTibet, (list_of(1000), 1400, 1700))
		(iCivIndonesia, (list_of(1300), 1500, 1940))
		(iCivBurma, (list_of(1000), 1211, 1850))
		(iCivKhazars, (list_of(1031), 1031, 1241))
		(iCivChad, (list_of(1259), 1380, 1603))
		(iCivMoors, (list_of(1200), 1300, 1650))
		(iCivSpain, (list_of(-1), 1650, 1650))
		(iCivFrance, (list_of(1700), 1800, 1900))
		(iCivOman, (list_of(-1), -1, -1))
		(iCivKhitan, (list_of(-1), -1, -1))
		(iCivKhmer, (list_of(1200), 1450, 1450))
		(iCivMuisca, (list_of(-1), -1, -1))
		(iCivYemen, (list_of(1229), 1265, -1))
		(iCivEngland, (list_of(1730), 1800, -1))
		(iCivScotland, (list_of(-1), -1, -1))
		(iCivHolyRome, (list_of(1550), 1650, 1850))
		(iCivNovgorod, (list_of(-1), -1, -1))
		(iCivKievanRus, (list_of(1327), -1, 1327))
		(iCivHungary, (list_of(1301), 1867, -1))
		(iCivPhilippines, (list_of(1400), 1500, 1600))
		(iCivChimu, (list_of(1300), 1475, 1500))
		(iCivSwahili, (list_of(1500), 1500, 1650))
		(iCivMamluks, (list_of(1300), 1380, 1500))
		(iCivMali, (list_of(1350), 1500, 1700))
		(iCivPoland, (list_of(1400), -1, 1600))
		(iCivZimbabwe, (list_of(1400), 1500, 1700))
		(iCivPortugal, (list_of(1550), 1650, 1700))
		(iCivInca, (list_of(1500), 1550, 1700))
		(iCivItaly, (list_of(1500), 1600, 1930))
		(iCivNigeria, (list_of(1600), 1750, 1950))
		(iCivLithuania, (list_of(1500), 1600, 1950))
		(iCivMongols, (list_of(1300), -1, 1500))
		(iCivAztec, (list_of(1520), 1650, -1))
		(iCivMughals, (list_of(1500), 1660, 1750))
		(iCivTatar, (list_of(-1), -1, -1))
		(iCivOttomans, (list_of(1550), 1700, 1800))
		(iCivRussia, (list_of(1920), -1, 1950))
		(iCivThailand, (list_of(1650), 1700, 1900))
		(iCivCongo, (list_of(1650), 1800, -1))
		(iCivIran, (list_of(1650), 1750, 1800))
		(iCivSweden, (list_of(1700), 1800, 1970))
		(iCivNetherlands, (list_of(1745), 1745, 1775))
		(iCivManchuria, (list_of(1800), 1850, -1))
		(iCivGermany, (list_of(1900), 1940, -1))
		(iCivAmerica, (list_of(1900), 1950, 2000))
		(iCivMexico, (list_of(1880), 1940, 1960))
		(iCivArgentina, (list_of(1930), 1960, 2000))
		(iCivColombia, (list_of(1870), 1920, 1950))
		(iCivBrazil, (list_of(1880), -1, 1950))
		(iCivAustralia, (list_of(1950), 1950, -1))
		(iCivBoers, (list_of(1920), 1950, 1980))
		(iCivCanada, (list_of(1920), 1950, 2000))
		(iCivIsrael, (list_of(1980), 2000, -1))
		;

	// Leoreth: date-triggered respawn for certain civs
	m_dRebirth = map_list_of
	(iHarappa, 530)		// Chalukya
		(iNorteChico, 900)	// Chimu
		(iCeltia, 820)		// Scotland
		(iPersia, 1501)		// Iran
		(iMaya, 1814)		// Colombia
		(iAztecs, 1810)		// Mexico
		;

	m_dRebirthCiv = map_list_of
	(iHarappa, iCivChalukya)
		(iNorteChico, iCivChimu)
		(iCeltia, iCivScotland)
		(iPersia, iCivIran)
		(iMaya, iCivColombia)
		(iAztecs, iCivMexico)
		;

	push_back(m_tResurrectionIntervals)
		((map_list_of(664, -343))), // Egypt
		(map_list_of(-3000, -900)), // Babylonia
		(std::vector<coord >()),		//  Harappa
		(std::vector<coord >()),		//  Norte Chico
		(map_list_of(-785, 350)(350, 1365)(1504, 2020)), // Nubia
		(std::vector<coord >()),		//  Assyria
		(map_list_of(-300, 2020)), // China
		(map_list_of(-300, 50)), // Hittites
		(map_list_of(1800, 2020)), // Greece
		(std::vector<coord >()), // Olmecs
		(map_list_of(1600, 1800)(1900, 2020)), // India
		(map_list_of(-1000, -150)(1200, 1400)(1956, 2020)), // Carthage
		(map_list_of(1910, 2020)), // Celtia
		(map_list_of(700, 2020)),		//  Polynesia
		(map_list_of(220, 650)(1500, 2020)), // Persia
		(map_list_of(-750, 450)), // Rome
		(map_list_of(-600, 250)), // Yuezhi
		(map_list_of(0, 800)), // Maya
		(map_list_of(-300, 600)(1300, 1650)(1940, 2020)), // Tamils
		(std::vector<coord >()), // Xiongnu
		(map_list_of(1270, 1520)(1850, 2020)), // Ethiopia
		(map_list_of(950, 1400)(1400, 1800)(1940, 2020)), // Vietnam
		(map_list_of(-100, 1000)), // Teotihuacan
		(map_list_of(-100, 350)(870, 1400)(1900, 2020)),		//  Armenia
		(map_list_of(100, 1400)), // Inuit
		(std::vector<coord >()), // Mississippi
		(map_list_of(1380, 1522)(1700, 1800)(1940, 2020)), // Korea
		(std::vector<coord >()), // Tiwanaku
		(map_list_of(1100, 1280)), // Byzantium
		(std::vector<coord >()), // Wari
		(map_list_of(1800, 2020)), // Japan
		(map_list_of(1520, 2020)), // Vikings
		(map_list_of(1350, 1500)(1700, 1800)(1940, 2020)), // Turks
		(map_list_of(1900, 2020)), // Arabia
		(map_list_of(700, 1600)),   // Tibet
		(map_list_of(900, 1600)(1900, 2020)), // Indonesia
		(map_list_of(900, 1700)(1948, 2020)), // Burma
		(map_list_of(1465, 1781)(1990, 2020)), // Khazars
		(map_list_of(1380, 1522)(1800, 2020)), // Chad
		(map_list_of(1000, 2020)),	// Moors
		(map_list_of(1700, 2020)), // Spain
		(map_list_of(1700, 2020)), // France
		(map_list_of(1340, 1690)(1850, 2020)), // Oman
		(std::vector<coord >()),		//  Khitan
		(map_list_of(900, 1200)(1950, 2020)), // Khmer
		(std::vector<coord >()), // Muisca
		(map_list_of(1636, 1849)(1918, 2020)), // Yemen
		(map_list_of(1700, 2020)), // England
		(map_list_of(1800, 2020)), // Holy Rome
		(map_list_of(900, 1400)), // Novgorod
		(map_list_of(1649, 1764)(1917, 2020)), // Kievan Rus
		(map_list_of(1200, 1690)(1918, 2020)),	// Hungary
		(map_list_of(1200, 1500)(1900, 2020)),	// Philippines
		(map_list_of(1850, 2020)),	// Swahili
		(map_list_of(1800, 2020)), // Mamluks
		(map_list_of(1340, 1590)(1900, 2020)), // Mali
		(map_list_of(1340, 1690)(1920, 2020)), // Poland
		(map_list_of(1649, 1764)(1917, 2020)),		//  Zimbabwe
		(map_list_of(1700, 2020)), // Portugal
		(map_list_of(1800, 2020)), // Inca
		(map_list_of(1520, 2020)), // Italy
		(map_list_of(1340, 1690)(1900, 2020)),		//  Nigeria
		(map_list_of(1910, 2020)),		// Lithuania
		(map_list_of(1340, 1690)(1910, 2020)), // Mongolia
		(std::vector<coord >()), 		// Aztec
		(map_list_of(1940, 2020)), // Mughals
		(map_list_of(1280, 1650)), // Tatar
		(map_list_of(1700, 2020)), // Ottomans
		(map_list_of(1480, 1550)(1700, 2020)), // Russia
		(map_list_of(1700, 2020)), // Thailand
		(map_list_of(1700, 2020)),		// Congo
		(map_list_of(1700, 2020)), // Sweden
		(map_list_of(1700, 2020)), // Netherlands
		(std::vector<coord >()),	// Manchuria
		(map_list_of(1840, 2020)), // Germany
		(map_list_of(1770, 2020)), // America
		(map_list_of(1810, 2020)), // Argentina
		(map_list_of(1820, 2020)), // Brazil
		(map_list_of(1850, 2020)), // Australia
		(map_list_of(1852, 2020)), // Boers
		(map_list_of(1867, 2020)), // Canada
		(map_list_of(1948, 2020)) // Israel
		;

	// rnf. Some civs have a double entry, for a higher chance
	push_back(m_lEnemyCivsOnSpawn)
		(((list_of(iNubia), iHittites))), // Egypt
		(list_of(iIndependent), iIndependent2, iAssyria), // Babylonia
		(_empty_), // Norte Chico
		(_empty_), // Harappa
		(list_of(iEgypt), iEgypt), // Nubia
		(list_of(iBabylonia)), // Assyria
		(list_of(iIndependent), iIndependent2, iIndependent2), // China
		(list_of(iEgypt), iAssyria), // Hittites
		(list_of(iIndependent), iIndependent2, iBabylonia), // Greece
		(_empty_), // Olmecs
		(list_of(iTamils)), // India
		(_empty_), // Carthage
		(_empty_), // Celtia
		(_empty_), // Polynesia
		(list_of(iBabylonia), iBabylonia, iBabylonia, iAssyria, iAssyria, iAssyria, iGreece, iCarthage, iCarthage), // Persia
		(_empty_), // Rome
		(_empty_), // Yuezhi
		(_empty_), // Maya
		(list_of(iIndia)), // Tamils
		(list_of(iChina), iYuezhi, iYuezhi), // Xiongnu
		(_empty_), // Ethiopia
		(list_of(iChina)),	// Vietnam
		(list_of(iMaya)), // Teotihuacan
		(_empty_),	// Armenia
		(_empty_), // Inuit
		(_empty_), // Mississippi
		(_empty_), // Korea
		(_empty_), // Tiwanaku
		(list_of(iGreece), iPersia), // Byzantium
		(_empty_), // Wari
		(_empty_), // Japan
		(list_of(iCeltia), iCeltia, iEngland, iEngland, iFrance, iIndependent, iIndependent2), // Vikings
		(list_of(iChina), iChina, iPersia, iPersia, iArmenia, iIndependent, iIndependent, iIndependent2, iIndependent2, iOman, iOman), //  Turks
		(list_of(iEgypt), iEgypt, iEgypt, iBabylonia, iBabylonia, iGreece, iPersia, iPersia, iPersia, iCarthage, iRome, iByzantium, iByzantium, iArmenia, iSpain, iFrance, iCeltia, iCeltia, iIndependent, iIndependent2), // Arabia
		(_empty_), // Tibet
		(list_of(iKhmer), iKhmer), // Indonesia
		(list_of(iKhmer), iKhmer), // Burma
		(list_of(iKievanRus), iKievanRus, iHungary), // Khazars
		(list_of(iNigeria)), // Chad
		(_empty_), // Moors
		(_empty_), // Spain
		(_empty_), // France
		(_empty_), // Oman
		(list_of(iChina), iChina, iChina, iKorea, iKorea),		//  Khitan
		(_empty_), // Khmer
		(_empty_), // Muisca
		(_empty_), // Yemen
		(list_of(iCeltia), iCeltia, iCeltia), // England
		(list_of(iRome), iArabia, iArabia), // Holy Rome
		(_empty_), // Novgorod
		(list_of(iKhazars), iKhazars), // Kievan Rus
		(list_of(iKhazars)),	// Hungary
		(_empty_),	// Philippines
		(_empty_),	// Swahili
		(list_of(iByzantium), iByzantium, iYemen),	// Mamluks
		(_empty_), // Mali
		(_empty_), // Poland
		(_empty_),	// Zimbabwe
		(_empty_), // Portugal
		(list_of(iNorteChico), iNorteChico, iTiwanaku, iTiwanaku, iTiwanaku, iWari, iWari, iWari), // Inca
		(_empty_), // Italy
		(list_of(iChad)),	// Nigeria
		(_empty_),	// Lithuania
		(list_of(iChina), iChina, iChina, iKorea, iKorea, iTurks, iTurks, iTurks, iKhitan, iKhitan, iIndependent, iIndependent, iIndependent2, iIndependent2), // Mongolia
		(list_of(iMaya), iTeotihuacan), // Aztec
		(list_of(iIndia), iIndia), // Mughals
		(list_of(iKhazars), iKhazars, iKhazars, iKievanRus, iKievanRus, iKievanRus, iNovgorod, iIndependent, iIndependent, iIndependent2, iIndependent2), // Tatar
		(list_of(iEgypt), iEgypt, iMamluks, iMamluks, iBabylonia, iGreece, iGreece, iArabia, iArabia, iArabia, iByzantium, iByzantium, iByzantium, iOman, iOman), // Ottomans
		(list_of(iKhazars), iKhazars, iKhazars, iKievanRus, iKievanRus, iKievanRus, iNovgorod, iNovgorod, iNovgorod, iTatar, iTatar, iTatar), // Russia
		(list_of(iKhmer), iKhmer, iKhmer, iBurma, iBurma), // Thailand
		(_empty_), // Congo
		(_empty_), // Sweden
		(_empty_), // Netherlands
		(list_of(iChina), iChina, iChina, iKorea, iMongolia), // Manchu
		(list_of(iHolyRome), iPoland), // Germany
		(list_of(iIndependent), iIndependent2), // America
		(list_of(iSpain), iSpain, iIndependent, iIndependent2), // Argentina
		(list_of(iIndependent), iIndependent2), // Brazil
		(_empty_), // Australia
		(list_of(iEngland), iNetherlands), // Boers
		(_empty_), // Canada
		(list_of(iEgypt), iEgypt, iEgypt, iPersia, iArabia, iArabia, iArabia, iMoors, iOttomans, iOttomans) // Israel
		;

	// Leoreth: date-triggered respawn for certain civs
	insert(m_dEnemyCivsOnRespawn)
		(iPersia, (list_of(iOttomans), iRussia, iOman, iOman))		//  Iran
		(iNorteChico, (list_of(iTiwanaku), iWari))		//  Chimu
		(iHarappa, (list_of(iIndia), iTamils))		//  Chalukya
		(iCeltia, (_empty_))		//  Scotland
		(iMaya, (_empty_))		//  Colombia
		(iAztecs, (list_of(iAmerica)))	//  Mexico
		;

	// Leoreth
	push_back(m_lTotalWarOnSpawn)
		((list_of(iNubia), iHittites)), // Egypt
		(_empty_), // Babylonia
		(_empty_), // Harappa
		(_empty_), // Norte Chico
		(_empty_), // Nubia
		(list_of(iEgypt), iBabylonia), // Assyria
		(_empty_), // China
		(_empty_), // Hittites
		(_empty_), // Greece
		(_empty_), // Olmecs
		(_empty_), // India
		(_empty_), // Phoenicia
		(list_of(iEngland)), // Celtia
		(_empty_), // Polynesia
		(list_of(iBabylonia), iCarthage, iArabia), // Persia
		(list_of(iCeltia), iCeltia, iGreece), // Rome
		(_empty_), // Yuezhi
		(_empty_), // Maya
		(_empty_), // Tamils
		(list_of(iChina), iYuezhi, iYuezhi), // Xiongnu
		(_empty_), // Ethiopia
		(_empty_),	// Vietnam
		(_empty_), // Teotihuacan
		(_empty_), // Armenia
		(_empty_), // Inuit
		(_empty_), // Mississippi
		(_empty_), // Korea
		(_empty_), // Tiwanaku
		(list_of(iGreece)), // Byzantium
		(_empty_), // Wari
		(_empty_), // Japan
		(_empty_), // Vikings
		(_empty_), // Turks
		(list_of(iEgypt), iBabylonia, iCarthage, iPersia), // Arabia
		(_empty_), // Tibet
		(_empty_), // Indonesia
		(_empty_), // Burma
		(list_of(iKievanRus), iKievanRus, iHungary), // Khazars
		(_empty_), // Chad
		(_empty_), // Moors
		(list_of(iMoors)), // Spain
		(_empty_), // France
		(list_of(iTurks), iTurks), // Oman
		(list_of(iChina)),		//  Khitan
		(_empty_), // Khmer
		(_empty_), // Muisca
		(_empty_), // Yemen
		(_empty_), // England
		(list_of(iRome)), // Holy Rome
		(_empty_), // Novgorod
		(_empty_), // Kievan Rus
		(_empty_),	// Hungary
		(_empty_),	// Philippines
		(_empty_),	// Swahili
		(_empty_),	// Mamluks
		(_empty_), // Mali
		(_empty_), // Poland
		(_empty_),	// Zimbabwe
		(_empty_), // Portugal
		(list_of(iNorteChico), iTiwanaku, iWari), // Inca
		(_empty_), // Italy
		(_empty_),	// Nigeria
		(_empty_),	// Lithuania
		(list_of(iChina)), // Mongolia
		(list_of(iMaya)), // Aztec
		(list_of(iIndia)), // Mughals
		(list_of(iKievanRus), iKhazars), // Tatar
		(list_of(iArabia), iEgypt, iMamluks), // Ottomans
		(list_of(iKievanRus), iKhazars, iNovgorod, iTatar), // Russia
		(list_of(iKhmer)), // Thailand
		(_empty_), // Congo
		(_empty_), // Sweden
		(_empty_), // Netherlands
		(list_of(iChina), iMongolia),	// Manchuria
		(_empty_), // Germany
		(_empty_), // America
		(_empty_), // Argentina
		(_empty_), // Brazil
		(_empty_),	// Australia
		(_empty_),	// Boers
		(_empty_), // Canada
		(_empty_) // Israel
		;

	// AIWars
	m_tAggressionLevel = (
		list_of(0), // Egypt
		1, // Babylonia
		0, // Harappa
		0, // Norte Chico
		1, // Nubia
		3, // Assyria
		1, // China
		1, // Hittites
		2, // Greece
		0, // Olmecs
		0, // India
		0, // Carthage
		2, // Celtia
		0, // Polynesia
		3, // Persia
		3, // Rome
		2, // Yuezhi
		1, // Maya
		1, // Tamils
		2, // Xiongnu
		0, // Ethiopia
		0, // Vietnam
		1, // Teotihuacan
		1, // Armenia
		0, // Inuit
		0, // Mississippi
		0, // Korea
		0, // Tiwanaku
		1, // Byzantium
		2, // Wari
		1, // Japan
		2, // Viking
		2, // Turks
		2, // Arabia
		1, // Tibet
		1, // Indonesia
		2, // Burma
		2, // Khazars
		2, // Chad
		1, // Moors
		2, // Spain
		1, // France
		2, // Oman
		2, // Khitan
		2, // Khmer
		0, // Muisca
		2, // Yemen
		1, // England
		2, // Holy Rome
		0, // Novgorod
		0, // Kievan Rus
		2, // Hungary
		0, // Philippines
		0, // Swahili
		1, // Mamluks
		0, // Mali
		1, // Poland
		0, // Zimbabwe
		0, // Portugal
		3, // Inca
		0, // Italy
		0, // Nigeria
		2, // Lithuania
		2, // Mongolia
		1, // Aztec
		1, // Mughals
		2, // Tatar
		2, // Ottomans
		1, // Russia
		0, // Thailand
		0, // Congo
		1, // Sweden
		0, // Holland
		1, // Manchuria
		2, // Germany
		2, // America
		0, // Argentina
		0, // Brazil
		0, // Australia
		0, // Boers
		0, // Canada
		1, // Israel
		0  // Barbs
		);

	// war during rise of new civs
	m_tAIStopBirthThreshold = (
		list_of(80), // Egypt
		50, // Babylonia
		50, // Harappa
		50, // Norte Chico
		80, // Nubia
		50, // Assyria
		60, // China
		60, // Hittites
		50, // Greece // would be 80 but with Turks must be lower
		80, // Olmecs
		80, // India
		80, // Carthage
		30, // Celtia
		80, // Polynesia
		70, // Persia
		80, // Rome
		30, // Yuezhi
		80, // Maya
		80, // Tamils
		30, // Xiongnu
		80, // Ethiopia
		80,	// Vietnam
		80, // Teotihuacan
		80, // Armenia
		30, // Inuit
		80, // Mississippi
		80, // Korea
		80, // Tiwanaku
		80, // Byzantium
		80, // Wari
		80, // Japan
		80, // Viking
		50, // Turks
		80, // Arabia
		80, // Tibet
		80, // Indonesia
		80, // Burma
		50, // Khazars
		80, // Chad
		80, // Moors
		80, // Spain  // 60 in vanilla and Warlords
		80, // France // 60 in vanilla and Warlords
		50, // Oman
		80, // Khitan
		80, // Khmer
		80, // Muisca
		50, // Yemen
		50, // England
		80, // Holy Rome // 70 in vanilla and Warlords
		80, // Novgorod
		80, // Kievan Rus
		70,	// Hungary
		70,	// Philippines
		70, // Swahili
		80,	// Mamluks
		70, // Mali
		40, // Poland
		80,	// Zimbabwe
		40, // Portugal
		70, // Inca
		60, // Italy
		80,	// Nigeria
		40, // Lithuania
		70, // Mongolia
		50, // Aztec
		70, // Mughals
		70, // Tatar
		70, // Turkey
		50, // Russia
		80, // Thailand
		80, // Congo
		70, // Sweden
		40, // Holland
		70, // Manchuria
		80, // Germany
		50, // America
		60, // Argentina
		60, // Brazil
		60,	// Australia
		60,	// Boers
		60, // Canada
		60, // Israel
		100,
		100,
		100,
		100,
		100
		);

	// RiseAndFall
	m_tResurrectionProb = (
		list_of(80), // Egypt
		95, // Babylonia
		0, // Harappa
		0, // Norte Chico
		60, // Nubia
		0, // Assyria
		100, // China
		50, // Hittites
		60, // Greece
		50, // Olmecs
		50, // India
		70, // Carthage
		50, // Celtia
		40, // Polynesia
		90, // Persia
		75, // Rome
		0, // Yuezhi
		30, // Maya
		50, // Tamils
		0, // Xiongnu
		80, // Ethopia
		80,	// Vietnam
		30, // Teotihuacan
		60, // Armenia
		70, // Inuit
		0, 	// Mississippi
		80, // Korea
		0, // Tiwanaku
		75, // Byzantium
		0, // Wari
		100, // Japan
		60, // Viking
		50, // Turks
		100, // Arabia
		60, // Tibet
		80, // Indonesia
		60, // Burma
		30, // Khazars
		30, // Chad
		70, // Moors
		100, // Spain
		100, // France
		100, // Oman
		0, // Khitan
		60, // Khmer
		0,  // Muisca
		100, // Yemen
		100, // England
		80, // Holy Rome
		80, // Novgorod
		65, // Kievan Rus
		30,	// Hungary
		60,	// Philippines
		60,	// Swahili
		60,	// Mamluks
		60, // Mali
		65, // Poland
		60,	// Zimbabwe
		100, // Portugal
		70, // Inca
		100, // Italy
		60,	// Nigeria
		45, // Lithuania
		80, // Mongolia
		70, // Aztec
		80, // Mughals
		60, // Tatar
		100, // Ottomans
		100, // Russia
		100, // Thailand
		60, // Congo
		100, // Sweden
		100, // Holland
		0, // Manchuria
		100, // Germany
		100, // America
		100, // Argentina
		100, // Brazil
		100, // Australia
		100, // Boers
		100, // Canada
		100, // Israel
		//     100, // Holland
		//     100, // Portugal
		100	// Barbs
		);

	// Congresses.
	m_tPatienceThreshold = (
		list_of(30), // Egypt
		30, // Babylonia
		30, // Harappa
		30, // Norte Chico
		30, // Nubia
		30, // Assyria
		30, // China
		30, // Hittites
		35, // Greece
		30, // Olmecs
		50, // India
		35, // Carthage
		30, // Celtia
		50, // Polynesia
		30, // Persia
		25, // Rome
		30, // Yuezhi
		35, // Maya
		45, // Tamils
		30, // Xiongnu
		20, // Ethopia
		25,	// Vietnam
		35, // Teotihuacan
		25, // Armenia
		40, // Inuit
		30, // Mississippi
		25, // Korea
		30, // Tiwanaku
		25, // Byzantium
		20, // Wari
		25, // Japan
		30, // Viking
		30, // Turks
		30, // Arabia
		50, // Tibet
		30, // Indonesia
		20, // Burma
		30, // Khazars
		20, // Chad
		20, // Moors
		20, // Spain
		20, // France
		20, // Oman
		30, // Khitan
		30, // Khmer
		20, // Muisca
		20, // Yemen
		20, // England
		20, // Holy Rome
		35, // Novgorod
		35, // Kievan Rus
		20,	// Hungary
		30,	// Philipinnes
		30,	// Swahili
		20,	// Mamluks
		35, // Mali
		20, // Poland
		20,	// Zimbabwe
		30, // Portugal
		35, // Inca
		25, // Italy
		20,	// Nigeria
		20, // Lithuania
		20, // Mongolia
		30, // Aztec
		35, // Mughals
		35, // Tatar
		35, // Ottomans
		30, // Russia
		30, // Thailand
		20, // Congo
		30, // Sweden
		30, // Holland
		20,	// Manchuria
		20, // Germany
		30, // America
		40, // Argentina
		40, // Brazil
		40,	// Australia
		40,	// Boers
		40, // Canada
		40, // Israel
		100	// Barbs
		);

	m_dMaxColonists = map_list_of
	(iVikings, 1)
		(iSpain, 7)
		(iFrance, 5)
		(iEngland, 6)
		(iPortugal, 7)
		(iSweden, 2)
		(iNetherlands, 6)
		(iGermany, 2)
		;

	// Persecution preference
	m_tPersecutionPreference = (list_of
	((list_of(iHinduism), iBuddhism, iTaoism, iConfucianism, iZoroastrianism, iIslam, iProtestantism, iCatholicism, iOrthodoxy)), // Judaism
		(list_of(iIslam), iProtestantism, iCatholicism, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iTaoism, iConfucianism), // Orthodoxy
		(list_of(iIslam), iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iTaoism, iConfucianism), // Catholicism
		(list_of(iIslam), iCatholicism, iOrthodoxy, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iTaoism, iConfucianism), // Protestantism
		(list_of(iHinduism), iProtestantism, iCatholicism, iOrthodoxy, iJudaism, iTaoism, iConfucianism, iZoroastrianism, iBuddhism), // Islam
		(list_of(iIslam), iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iTaoism, iConfucianism, iBuddhism), // Hinduism
		(list_of(iCatholicism), iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iTaoism, iIslam, iConfucianism, iHinduism), // Buddhism
		(list_of(iIslam), iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iTaoism), // Confucianism
		(list_of(iIslam), iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iConfucianism), // Taoism
		(list_of(iIslam), iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iBuddhism, iHinduism, iTaoism, iConfucianism) // Zoroastrianism
		);

	m_lCatholicStart = (
		list_of(iSpain), iFrance, iEngland, iHolyRome, iPoland, iPortugal, iItaly, iNetherlands, iSweden, iGermany, iAmerica, iArgentina, iBrazil, iBoers, iAustralia, iCanada
		);

	m_lProtestantStart = (
		list_of(iSweden), iNetherlands, iGermany, iAmerica, iAustralia, iBoers
		);

	m_lGreatPeopleUnits = (
		list_of(iGreatProphet), iGreatArtist, iGreatScientist, iGreatMerchant, iGreatEngineer, iGreatStatesman
		);

	m_dFemaleGreatPeople = map_list_of
	(iGreatProphet, iFemaleGreatProphet)
		(iGreatArtist, iFemaleGreatArtist)
		(iGreatScientist, iFemaleGreatScientist)
		(iGreatMerchant, iFemaleGreatMerchant)
		(iGreatEngineer, iFemaleGreatEngineer)
		(iGreatStatesman, iFemaleGreatStatesman)
		(iGreatGeneral, iFemaleGreatGeneral)
		(iGreatSpy, iFemaleGreatSpy)
		;

	m_StabilityLevelTexts = (
		list_of("TXT_KEY_STABILITY_COLLAPSING"), "TXT_KEY_STABILITY_UNSTABLE",
		"TXT_KEY_STABILITY_SHAKY", "TXT_KEY_STABILITY_STABLE",
		"TXT_KEY_STABILITY_SOLID"
		);

	m_StabilityTypesTexts = (
		list_of("TXT_KEY_STABILITY_CATEGORY_EXPANSION"), "TXT_KEY_STABILITY_CATEGORY_ECONOMY",
		"TXT_KEY_STABILITY_CATEGORY_DOMESTIC", "TXT_KEY_STABILITY_CATEGORY_FOREIGN",
		"TXT_KEY_STABILITY_CATEGORY_MILITARY"
		);

	m_lNewWorld = (
		list_of(rAustralia), rOceania, rCanada, rAlaska, rUnitedStates, rCaribbean, rMesoamerica, rBrazil, rArgentina, rPeru, rColombia
		);

	m_lEurope = (
		list_of(rBritain), rIberia, rItaly, rBalkans, rEurope, rScandinavia, rRussia
		);

	m_lMiddleEast = (
		list_of(rAnatolia), rMesopotamia, rArabia, rPersia, rCentralAsia
		);

	m_lIndia = (
		list_of(rIndia), rDeccan
		);

	m_lEastAsia = (
		list_of(rIndochina), rIndonesia, rChina, rKorea, rJapan, rManchuria, rTibet
		);

	m_lNorthAfrica = (
		list_of(rEgypt), rMaghreb
		);

	m_lSubSaharanAfrica = (
		list_of(rEthiopia), rSouthAfrica, rWestAfrica
		);

	m_lSouthAmerica = (
		list_of(rCaribbean), rMesoamerica, rBrazil, rArgentina, rPeru, rColombia
		);

	m_lNorthAmerica = (
		list_of(rCanada), rAlaska, rUnitedStates
		);

	m_lOceania = (
		list_of(rAustralia), rOceania
		);

	m_lAfrica = m_lNorthAfrica;
	m_lAfrica.insert(m_lAfrica.end(), m_lSubSaharanAfrica.begin(), m_lSubSaharanAfrica.end());

	m_lAsia = m_lMiddleEast;
	m_lAsia.insert(m_lAsia.end(), m_lIndia.begin(), m_lIndia.end());
	m_lAsia.insert(m_lAsia.end(), m_lEastAsia.begin(), m_lEastAsia.end());

	m_lAmericas = m_lNorthAmerica;
	m_lAmericas.insert(m_lAmericas.end(), m_lSouthAmerica.begin(), m_lSouthAmerica.end());

	m_mercRegions = map_list_of
	(iArea_Europe, (list_of(rBritain), rIberia, rItaly, rBalkans, rEurope, rScandinavia, rRussia))
		(iArea_MiddleEast, (list_of(rAnatolia), rMesopotamia, rArabia, rEgypt, rMaghreb, rPersia, rCentralAsia))
		(iArea_India, (list_of(rIndia), rDeccan))
		(iArea_EastAsia, (list_of(rIndochina), rIndonesia, rChina, rKorea, rJapan, rManchuria, rTibet))
		(iArea_Africa, (list_of(rEgypt), rMaghreb, rEthiopia, rSouthAfrica, rWestAfrica))
		(iArea_SouthAmerica, (list_of(rCaribbean), rMesoamerica, rBrazil, rArgentina, rPeru, rColombia))
		(iArea_NorthAmerica, (list_of(rCanada), rAlaska, rUnitedStates))
		;

	m_resurrectionLeaders = map_list_of
	(iChina, iHongwu)
		(iIndia, iShahuji)
		(iEgypt, iBaibars)
		;

	m_rebirthLeaders = map_list_of
	(iHarappa, iPulakesi)
		(iNorteChico, iTacaynamo)
		(iCeltia, iRobert)
		(iMaya, iBolivar)
		(iPersia, iAbbas)
		(iAztecs, iJuarez)
		;

	m_tTradingCompanyPlotLists = (
		list_of((map_list_of(128, 35)(129, 36)(130, 38)(130, 39)(130, 33)(131, 34)(131, 36)(131, 38)(131, 39)(131, 40)(132, 33)(132, 34)(132, 37)(133, 36))), // Spain
		(map_list_of(122, 42)(121, 41)(121, 40)(121, 42)(122, 40)(122, 39)(123, 39)(123, 38)(124, 38)(123, 37)(124, 37)(123, 36)(124, 36)(124, 35)(124, 34)(124, 39) (125, 36)(125, 35)(125, 37)(125, 38)(123, 35)(123, 34)), // France
		(map_list_of(113, 42)(112, 42)(111, 42)(111, 41)(111, 40)(110, 40)(110, 39)(109, 39)(109, 38)(108, 38)(108, 37)(107, 37)(107, 36)(107, 35)(107, 34)(103, 39)(103, 38)(103, 37)(103, 36)(125, 43)), // England
		(map_list_of(62, 31)(70, 24)(79, 17)(83, 20)(96, 40)(96, 39)(104, 34)(108, 30)(108, 31)(120, 30)), // Portugal
		(map_list_of(119, 28)(120, 28)(120, 27)(121, 27)(120, 26)(121, 26)(123, 25)(124, 25)(125, 25)(126, 25)(123, 29)(124, 29)(125, 29)(126, 29)(127, 29)(124, 28)(125, 28)(126, 28)(132, 28)(134, 28)(134, 29)) // Netherlands
		);

	m_lSecondaryCivs = (
		list_of(iHarappa), iPolynesia, iTamils, iTibet, iMoors, iPoland, iCongo, iArgentina, iBrazil
		);

	m_lMongolCivs = (
		list_of(iPersia), iByzantium, iArabia, iArmenia
		);

	m_lStabilityColors = (
		list_of("COLOR_CYAN"), "COLOR_GREEN", "COLOR_YELLOW", "COLOR_RED", "COLOR_PLAYER_LIGHT_PURPLE"
		);

	m_lPresetValues = (
		list_of(3), 20, 90, 200, 500, 700
		);

	m_lWarMapColors = (
		list_of("COLOR_RED"), "COLOR_PLAYER_ORANGE", "COLOR_YELLOW", "COLOR_GREEN", "COLOR_PLAYER_DARK_GREEN", "COLOR_BLUE"
		);

	m_lReligionMapColors = (
		list_of("COLOR_PLAYER_ORANGE"), "COLOR_YELLOW", "COLOR_GREEN", "COLOR_CYAN"
		);

	m_lReligionMapTexts = (
		list_of("TXT_KEY_CULTURELEVEL_NONE"), "TXT_KEY_WB_RELIGIONMAP_MINORITY", "TXT_KEY_WB_RELIGIONMAP_PERIPHERY", "TXT_KEY_WB_RELIGIONMAP_HISTORICAL", "TXT_KEY_WB_RELIGIONMAP_CORE"
		);

	m_lNetworkEvents = map_list_of
	("CHANGE_COMMERCE_PERCENT", 1200)
		;

	m_lCapitalStart = (
		list_of(iAssyria), iChina, iYemen, iBurma, iOttomans
		);

};