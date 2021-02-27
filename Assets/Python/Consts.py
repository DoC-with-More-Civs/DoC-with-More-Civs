# Rhye's and Fall of Civilization - Constants
# globals

from CvPythonExtensions import *
gc = CyGlobalContext()

iWorldX = 150
iWorldY = 80

# initialise player variables to player IDs from WBS
iNumPlayers = 82
(iEgypt, iBabylonia, iHarappa, iNorteChico, iNubia, iAssyria, iChina, iHittites, iGreece, iOlmecs, iIndia, iCarthage, iCeltia, iPolynesia, iPersia, iRome, 
iYuezhi, iMaya, iTamils, iXiongnu, iEthiopia, iVietnam, iTeotihuacan, iArmenia, iInuit, iMississippi, iKorea, iTiwanaku, iByzantium, iWari, iJapan, iVikings, iTurks, iArabia, iTibet, 
iIndonesia, iBurma, iKhazars, iChad, iMoors, iSpain, iFrance, iOman, iKhitan, iKhmer, iMuisca, iYemen, iEngland, iHolyRome, iNovgorod, iKievanRus, iHungary, iPhilippines, iSwahili, iMamluks, iMali, iPoland, iZimbabwe, 
iPortugal, iInca, iItaly, iNigeria, iLithuania, iMongolia, iAztecs, iMughals, iTatar, iOttomans, iRussia, iThailand, iCongo, iSweden, iNetherlands, iManchuria,
iGermany, iAmerica, iArgentina, iBrazil, iAustralia, iBoers, iCanada, iIsrael) = range(iNumPlayers)

(pEgypt, pBabylonia, pHarappa, pNorteChico, pNubia, pAssyria,pChina, pHittites, pGreece, pOlmecs, pIndia, pCarthage, pCeltia, pPolynesia, pPersia, pRome, 
pYuezhi, pMaya, pTamils, pXiongnu, pEthiopia, pVietnam, pTeotihuacan, pArmenia, pInuit, pMississippi, pKorea, pTiwanaku, pByzantium, pWari, pJapan, pVikings, pTurks, pArabia, pTibet, 
pIndonesia, pBurma, pKhazars, pChad, pMoors, pSpain, pFrance, pOman, pKhitan, pKhmer, pMuisca, pYemen, pEngland, pHolyRome, pNovgorod, pKievanRus, pHungary, pPhilippines, pSwahili, pMamluks, pMali, pPoland, pZimbabwe, 
pPortugal, pInca, pItaly, pNigeria, pLithuania, pMongolia, pAztecs, pMughals, pTatar, pOttomans, pRussia, pThailand, pCongo, pSweden, pNetherlands, pManchuria, 
pGermany, pAmerica, pArgentina, pBrazil, pAustralia, pBoers, pCanada, pIsrael) = [gc.getPlayer(i) for i in range(iNumPlayers)]

(teamEgypt, teamBabylonia, teamHarappa, teamNorteChico, teamNubia, teamAssyria, teamChina, teamHittites, teamGreece, teamOlmecs, teamIndia, teamCarthage, teamCeltia, teamPolynesia, teamPersia, teamRome, 
teamYuezhi, teamMaya, teamTamils, teamXiongnu, teamEthiopia, teamVietnam, teamTeotihuacan, teamArmenia, teamInuit, teamMississippi, teamKorea, teamTiwanaku, teamByzantium, teamWari, teamJapan, teamVikings, teamTurks, teamArabia, teamTibet, 
teamIndonesia, teamBurma, teamKhazars, teamChad, teamMoors, teamSpain, teamFrance, teamOman, teamKhitan, teamKhmer, teamMuisca, teamYemen, teamEngland, teamHolyRome, teamNovgorod, teamKievanRus, teamHungary, teamPhilippines, teamSwahili, teamMamluks, teamMali, teamPoland, teamZimbabwe, 
teamPortugal, teamInca, teamItaly, teamNigeria, teamLithuania, teamMongolia, teamAztecs, teamMughals, teamTatar, teamOttomans, teamRussia, teamThailand, teamCongo, teamSweden, teamNetherlands, teamManchuria, 
teamGermany, teamAmerica, teamArgentina, teamBrazil, teamAustralia, teamBoers, teamCanada, teamIsrael) = [gc.getTeam(i) for i in range(iNumPlayers)]

iHolland = iNetherlands
iDelhi = iMughals
iSiam = iThailand
iPhoenicia = iCarthage
iTunisia = iCarthage
iHRE = iHolyRome
iAustria = iHolyRome
iPrussia = iGermany
iSouthAfrica = iBoers
iMyanmar = iBurma
iSudan = iNubia
iKazakh = iKhazars

iNumMajorPlayers = iNumPlayers
iNumActivePlayers = iNumPlayers

iIndependent = iNumPlayers
iIndependent2 = iNumPlayers+1
iNative = iNumPlayers+2
iNumTotalPlayers = iNumPlayers+3
iBarbarian = iNumPlayers+3
iNumTotalPlayersB = iBarbarian+1

(pIndependent, pIndependent2, pNative, pBarbarian) = [gc.getPlayer(i) for i in range(iIndependent, iNumTotalPlayersB)]
(teamIndependent, teamIndependent2, teamNative, teamBarbarian) = [gc.getTeam(i) for i in range(iIndependent, iNumTotalPlayersB)]

l0Array =       [0 for i in range(iNumPlayers)]
l0ArrayActive = [0 for i in range(iNumPlayers)]
l0ArrayTotal =  [0 for i in range(iNumTotalPlayers)]

lm1Array =      [-1 for i in range(iNumPlayers)]

# civilizations, not players
iNumCivilizations = 96
(iCivAmerica, iCivArabia, iCivArgentina, iCivArmenia, iCivAssyria, iCivAustralia, iCivAztec, iCivBabylonia, iCivBoers, iCivBrazil, iCivBurma, iCivByzantium, iCivCanada, iCivCarthage, iCivCelt, 
iCivChad, iCivChalukya, iCivChimu, iCivChina, iCivColombia, iCivEgypt, iCivEngland, iCivEthiopia, iCivFrance, iCivGermany, iCivGreece, iCivHarappa, iCivHittites, iCivHolyRome, iCivHungary, 
iCivInca, iCivIndia, iCivIndonesia, iCivInuit, iCivIran, iCivIsrael, iCivItaly, iCivJapan, iCivKhazars, iCivKhitan, iCivKhmer, iCivKievanRus, iCivKongo, iCivKorea, iCivLithuania, iCivMali, iCivMamluks, iCivManchuria,
iCivMaya, iCivMexico, iCivMississippi, iCivMongols, iCivMoors, iCivMughals, iCivMuisca, iCivNativeAmericans, iCivNetherlands, iCivNigeria, iCivNorteChico, iCivNovgorod, iCivNubia, iCivOlmecs, iCivOman, iCivOttomans, iCivPersia, iCivPhilippines, iCivPoland, 
iCivPolynesia, iCivPortugal, iCivRome, iCivRussia, iCivScotland, iCivSpain, iCivSumeria, iCivSwahili, iCivSweden, iCivTamils, iCivTatar, iCivTeotihuacan, iCivThailand, iCivTibet, iCivTiwanaku, iCivTurks, iCivVietnam,
iCivVikings, iCivWari, iCivXiongnu, iCivYemen, iCivYuezhi, iCivZimbabwe, iCivZulu, iCivIndependent, iCivIndependent2, iCivNative, iCivMinor, iCivBarbarian) = range(iNumCivilizations)

iCivCongo = iCivKongo
iCivAztecs = iCivAztec
iCivCeltia = iCivCelt
iCivSouthAfrica = iCivBoers
iCivKazakhs = iCivKhazars

#for Congresses and Victory
lCivGroups = [[iGreece, iRome, iByzantium, iVikings, iMoors, iSpain, iFrance, iEngland, iHolyRome, iRussia, iKhazars, iKievanRus, iNetherlands, iItaly, iPoland, iPortugal, iGermany, iSweden, iHungary, iNovgorod, iCeltia, iLithuania],  #Euros
		[iIndia, iChina, iHarappa, iPolynesia, iPersia, iJapan, iTamils, iKorea, iByzantium, iTibet, iKhmer, iIndonesia, iRussia, iKievanRus, iMongolia, iMughals, iThailand, iTurks, iKhazars, iVietnam, iManchuria, iKhitan, iPhilippines, iBurma, iYuezhi, iXiongnu], #Asian
		[iEgypt, iBabylonia, iAssyria, iHittites, iPersia, iByzantium, iArabia, iTatar, iOttomans, iCarthage, iTurks, iKhazars, iMamluks, iIsrael, iOman, iYemen], #MiddleEastern
		[iEgypt, iGreece, iCarthage, iRome, iArmenia, iByzantium, iMoors], #Mediterranean
		[iEgypt, iCarthage, iEthiopia, iMali, iCongo, iSwahili, iZimbabwe, iNigeria, iBoers, iNubia, iChad], #African
		[iNorteChico, iOlmecs, iMississippi, iInuit, iTiwanaku, iWari, iMuisca, iMaya, iTeotihuacan, iInca, iAztecs, iAmerica, iArgentina, iBrazil, iAustralia, iCanada]] #American

lCivStabilityGroups = [[iVikings, iSpain, iFrance, iEngland, iHolyRome, iRussia, iNovgorod, iKievanRus, iNetherlands, iPoland, iPortugal, iItaly, iGermany, iSweden, iHungary, iCeltia, iLithuania],  #Euros
		[iIndia, iChina, iHarappa, iPolynesia, iJapan, iKorea, iTibet, iKhmer, iIndonesia, iMongolia, iThailand, iTamils, iVietnam, iManchuria, iKhitan, iPhilippines, iBurma, iYuezhi, iXiongnu], #Asian
		[iBabylonia, iAssyria, iHittites, iPersia, iArabia, iOttomans, iTatar, iMughals, iTurks, iKhazars, iMamluks, iIsrael, iOman, iYemen], #MiddleEastern
		[iEgypt, iGreece, iCarthage, iRome, iEthiopia, iArmenia, iByzantium, iMoors, iMali, iCongo, iZimbabwe, iNigeria, iSwahili, iBoers, iNubia, iChad], #Mediterranean
		[iNorteChico, iOlmecs, iMississippi, iInuit, iTiwanaku, iWari, iMuisca, iMaya, iTeotihuacan, iInca, iAztecs, iAmerica, iArgentina, iBrazil, iAustralia, iCanada]] #American
		
lTechGroups = [[iRome, iGreece, iByzantium, iVikings, iSpain, iFrance, iEngland, iHolyRome, iRussia, iNovgorod, iKievanRus, iNetherlands, iPoland, iPortugal, iItaly, iGermany, iAmerica, iArgentina, iBrazil, iCanada, iSweden, iAustralia, iBoers, iHungary, iIsrael, iCeltia, iLithuania], #Europe and NA
	       [iEgypt, iBabylonia, iHarappa, iAssyria, iHittites, iIndia, iCarthage, iPersia, iEthiopia, iArmenia, iArabia, iMoors, iMali, iOttomans, iMughals, iTatar, iTamils, iCongo, iTurks, iKhazars, iMamluks, iNigeria, iSwahili, iZimbabwe, iOman, iYemen, iNubia, iChad], #Middle East
	       [iChina, iKorea, iJapan, iTibet, iKhmer, iIndonesia, iMongolia, iThailand, iManchuria, iKhitan, iVietnam, iPhilippines, iBurma, iYuezhi, iXiongnu], #Far East
	       [iNorteChico, iOlmecs, iMississippi, iInuit, iTiwanaku, iWari, iMuisca, iPolynesia, iMaya, iTeotihuacan, iInca, iAztecs]] #Native America

lCivBioOldWorld = [iEgypt, iIndia, iChina, iBabylonia, iHarappa, iGreece, iPolynesia, iPersia, iCarthage, iRome, iJapan, iTamils, iAssyria, iHittites, iArmenia, 
		   iEthiopia, iKorea, iByzantium, iVikings, iTurks, iArabia, iTibet, iKhmer, iIndonesia, iMoors, iSpain, iFrance, iEngland, iHolyRome, 
		   iRussia, iKievanRus, iNetherlands, iMali, iOttomans, iPoland, iPortugal, iItaly, iMongolia, iAmerica, iMughals, iThailand, iCongo, iGermany, iSweden,
		   iAustralia, iBoers, iMamluks, iManchuria, iNigeria, iPhilippines, iSwahili, iVietnam, iZimbabwe, iBurma, iHungary, iOman, iKhitan, iYemen, iKhazars, iNubia,
		   iChad, iNovgorod, iTatar, iYuezhi, iXiongnu, iLithuania, 
		   iIndependent, iIndependent2, iCeltia, iBarbarian]
lCivBioNewWorld = [iNorteChico, iOlmecs, iMississippi, iInuit, iTiwanaku, iWari, iMuisca, iMaya, iTeotihuacan, iInca, iAztecs] #, iNative]


#for Victory and the handler
tAmericasTL = (3, 0)
tAmericasBR = (43, 63)

# Colombian UP
tSouthCentralAmericaTL = (13, 3)
tSouthCentralAmericaBR = (43, 39)

# English colonists
tCanadaTL = (10, 49)
tCanadaBR = (37, 58)
tAustraliaTL = (103, 5)
tAustraliaBR = (123, 22)

# new capital locations
tVienna = (62, 49)
tWarsaw = (65, 52)
tStockholm = (73, 70)
tIstanbul = (80, 55)
tBeijing = (102, 47)
tEsfahan = (81, 41)
tHamburg = (59, 53)
tMilan = (59, 47)
tBaghdad = (77, 40)
tMumbai = (88, 34)
tMysore = (90, 31)

#for messages
iDuration = 14
iWhite = 0
iRed = 7
iGreen = 8
iBlue = 9
iLightBlue = 10
iYellow = 11
iDarkPink = 12
iLightRed = 20
iPurple = 25
iCyan = 44
iBrown = 55
iOrange = 88
iTan = 90
iLime = 100

# independent cities
iNumMinorCities = 65

# scripted conquerors
iNumConquests = 24

#neighbours
lNeighbours = [
[iBabylonia, iNubia, iAssyria, iHittites, iGreece, iPersia, iCarthage, iRome, iEthiopia, iByzantium, iArabia, iMoors, iOttomans, iMamluks, iOman, iYemen, iNubia, iChad], #Egypt
[iEgypt, iAssyria, iHittites, iGreece, iCarthage, iPersia, iArmenia, iTurks, iOttomans, iMongolia, iCarthage, iByzantium, iOman], #Babylonia
[iIndia, iPersia, iTamils, iTibet, iMughals], #Harappa
[iTiwanaku, iWari, iMuisca, iInca], #Norte Chico
[iEgypt, iEthiopia, iArabia, iOman, iYemen, iMamluks, iMali, iZimbabwe, iNigeria, iCongo, iChad], #Nubia
[iEgypt, iBabylonia, iHittites, iGreece, iCarthage, iPersia, iArmenia], # Assyria
[iIndia, iJapan, iKorea, iTurks, iTibet, iKhmer, iMongolia, iThailand, iManchuria, iPhilippines, iKhitan, iBurma, iYuezhi, iXiongnu], #China
[iEgypt, iBabylonia, iAssyria, iGreece, iCarthage, iPersia, iArmenia], # Hittites
[iAssyria, iHittites, iPersia, iCarthage, iRome, iByzantium, iHolyRome, iRussia, iKievanRus, iOttomans, iItaly, iKhazars], #Greece
[iTeotihuacan, iMaya, iAztecs], #Olmecs
[iChina, iHarappa, iPersia, iTamils, iTibet, iKhmer, iMongolia, iMughals, iThailand, iVietnam, iBurma, iYuezhi], #India
[iEgypt, iBabylonia, iAssyria, iHittites, iGreece, iRome, iSpain, iMali, iPortugal, iBabylonia, iPersia, iArabia, iMoors, iOttomans, iItaly, iMamluks], #Carthage
[iRome, iVikings, iFrance, iHolyRome, iNetherlands], #Celtia
[], # Polynesia
[iIndia, iBabylonia, iHarappa, iAssyria, iHittites, iGreece, iArmenia, iTurks, iByzantium, iOttomans, iMongolia, iCarthage, iMughals, iMamluks, iOman, iYemen, iKhazars, iYuezhi], #Persia
[iEgypt, iBabylonia, iGreece, iCarthage, iCeltia, iSpain, iFrance, iHolyRome, iPortugal, iItaly, iGermany, iHungary, iXiongnu], #Rome
[iIndia, iTurks, iXiongnu, iChina, iPersia], #Yuezhi
[iOlmecs, iSpain, iTeotihuacan, iInca, iAztecs, iAmerica], #Maya
[iHarappa, iIndia, iKhmer, iIndonesia, iMughals, iThailand, iVietnam, iPhilippines], #Tamils
[iChina, iKorea, iMongolia, iYuezhi, iRome], #Xiongnu
[iEgypt, iNubia, iArabia, iMali, iCongo, iMamluks, iNigeria, iSwahili, iZimbabwe, iOman, iYemen, iNubia], #Ethiopia
[iChina, iKhmer, iThailand, iTamils, iIndia, iIndonesia, iTibet, iPhilippines, iBurma], #Vietnam
[iOlmecs, iSpain, iMaya, iInca, iAztecs, iAmerica], #Teotihuacan
[iBabylonia, iAssyria, iHittites, iPersia, iByzantium, iOttomans, iKhazars], # Armenia
[iCanada, iAmerica], # Inuit
[iCanada, iAmerica], # Mississippi
[iChina, iJapan, iKhitan, iMongolia, iManchuria, iXiongnu], #Korea
[iNorteChico, iWari, iInca], #Tiwanaku
[iEgypt, iBabylonia, iGreece, iPersia, iArmenia, iArabia, iRussia, iKievanRus, iOttomans, iTurks, iMamluks, iHungary, iKhazars], #Byzantium
[iNorteChico, iTiwanaku, iMuisca, iInca], #Wari
[iChina, iKorea, iKhmer, iMongolia, iThailand, iManchuria, iPhilippines], #Japan
[iCeltia, iFrance, iEngland, iHolyRome, iRussia, iKievanRus, iPoland, iNetherlands, iGermany, iNovgorod, iKhazars], #Vikings
[iChina, iBabylonia, iPersia, iMughals, iOttomans, iByzantium, iMongolia, iTibet, iMamluks, iOman, iYemen, iKhazars, iYuezhi], # Turks
[iEgypt, iNubia, iBabylonia, iPersia, iEthiopia, iByzantium, iOttomans, iCarthage, iMamluks, iIsrael, iOman, iYemen, iKhazars, iNubia, iChad], #Arabia
[iChina, iHarappa, iIndia, iMongolia, iMughals, iTurks, iVietnam], #Tibet
[iIndia, iJapan, iKhmer, iThailand, iTamils, iPhilippines, iVietnam, iBurma], #Indonesia
[iChina, iKhmer, iThailand, iTamils, iIndia, iIndonesia, iTibet, iPhilippines, iVietnam], #Burma
[iGreece, iPersia, iArmenia, iTurks, iKievanRus, iHungary, iByzantium, iMongolia, iArabia, iRussia, iOttomans, iVikings, iNovgorod, iTatar, iSweden], #Khazars
[iEgypt, iNubia, iNigeria, iArabia, iOttomans, iMamluks, iMali, iCongo], #Chad
[iEgypt, iSpain, iPortugal, iMali, iMamluks], #Moors
[iCarthage, iRome, iMoors, iFrance, iEngland, iPortugal], #Spain
[iCeltia, iRome, iVikings, iSpain, iEngland, iHolyRome, iNetherlands, iPortugal, iItaly, iGermany], #France
[iEgypt, iBabylonia, iPersia, iTurks, iArabia, iMamluks, iIsrael, iSwahili, iEthiopia, iOttomans, iYemen, iNubia], #Oman
[iChina, iKorea, iMongolia, iManchuria, ], #Khitan
[iIndia, iChina, iTamils, iJapan, iIndonesia, iThailand, iPhilippines, iVietnam, iBurma], #Khmer
[iNorteChico, iWari, iInca], #Muisca
[iEgypt, iBabylonia, iPersia, iTurks, iArabia, iMamluks, iIsrael, iSwahili, iEthiopia, iOttomans, iOman, iNubia], #Yemen
[iCeltia, iRome, iVikings, iSpain, iFrance, iHolyRome, iNetherlands, iGermany], #England
[iCeltia, iRome, iVikings, iFrance, iEngland, iNetherlands, iItaly, iPoland, iLithuania, iSweden,  iGermany, iHungary], #Holy Rome
[iVikings, iPoland, iLithuania, iSweden, iRussia, iKievanRus, iHungary, iTatar, iKhazars], # Novgorod
[iPersia, iByzantium, iVikings, iPoland, iLithuania, iOttomans, iMongolia, iSweden, iGermany, iRussia, iHungary, iNovgorod, iTatar, iKhazars], #Kievan Rus
[iHolyRome, iRussia, iKievanRus, iGermany, iPoland, iLithuania, iOttomans, iByzantium, iMongolia, iNovgorod, iTatar, iKhazars], #Hungary
[iChina, iTamils, iJapan, iIndonesia, iKhmer, iThailand, iVietnam, iBurma], #Philippines
[iEthiopia, iMali, iCongo, iNigeria, iZimbabwe, iOman, iYemen], # Swahili
[iPersia, iCarthage, iEthiopia, iByzantium, iArabia, iMoors, iOttomans, iEgypt, iOman, iYemen, iNubia, iChad], #Mamluks
[iEgypt, iCarthage, iEthiopia, iMoors, iCongo, iNigeria, iSwahili, iZimbabwe, iNubia, iChad], #Mali
[iVikings, iHolyRome, iRussia, iKievanRus, iSweden, iGermany, iNovgorod, iTatar, iLithuania, iHungary], #Poland
[iEthiopia, iMali, iCongo, iNigeria, iSwahili, iNubia], #Zimbabwe
[iCarthage, iRome, iSpain, iFrance], #Portugal
[iSpain, iTiwanaku, iWari, iMuisca, iAztecs, iAmerica, iArgentina, iBrazil], #Inca
[iGreece, iCarthage, iRome, iFrance, iHolyRome], #Italy
[iMali, iCongo, iEthiopia, iSwahili, iZimbabwe, iNubia, iChad], #Nigeria
[iHolyRome, iRussia, iKievanRus, iNovgorod, iSweden, iGermany, iHungary, iPoland], #Lithuania
[iIndia, iChina, iPersia, iJapan, iKorea, iTibet, iRussia, iKievanRus, iOttomans, iTurks, iKhitan, iManchuria, iHungary, iTatar, iKhazars, iXiongnu], #Mongolia
[iOlmecs, iSpain, iTeotihuacan, iInca, iAmerica], #Aztec
[iHarappa, iIndia, iPersia, iTamils, iTibet, iTurks], #Mughals
[iPoland, iOttomans, iMongolia, iSweden, iRussia, iKievanRus, iHungary, iNovgorod, iKhazars], # Tatar
[iBabylonia, iGreece, iPersia, iArmenia, iByzantium, iRussia, iKievanRus, iMongolia, iCarthage, iTurks, iMamluks, iHungary, iIsrael, iOman, iYemen, iTatar, iKhazars, iChad], #Ottomans
[iPersia, iByzantium, iVikings, iPoland, iLithuania, iOttomans, iMongolia, iSweden, iGermany, iKievanRus, iHungary, iNovgorod, iTatar, iKhazars], #Russia
[iIndia, iChina, iJapan, iIndonesia, iKhmer, iTamils, iPhilippines, iVietnam], #Thailand
[iEthiopia, iMali, iSwahili, iNigeria, iZimbabwe, iNubia, iChad], #Congo
[iVikings, iHolyRome, iRussia, iKievanRus, iPoland, iLithuania, iGermany, iNovgorod, iTatar, iKhazars], # Sweden
[iCeltia, iVikings, iFrance, iEngland, iHolyRome, iGermany], #Netherlands
[iRome, iVikings, iFrance, iEngland, iHolyRome, iRussia, iKievanRus, iPoland, iLithuania, iSweden, iNetherlands, iHungary], #Germany
[iChina, iKorea, iJapan, iKhitan, iMongolia], #Manchuria
[iJapan, iSpain, iFrance, iEngland, iRussia, iKievanRus, iInca, iAztecs, iMississippi, iInuit], #America
[iSpain, iPortugal, iInca, iBrazil], #Argentina
[iSpain, iPortugal, iInca, iArgentina], #Brazil
[iJapan, iIndonesia, iEngland, iNetherlands, iAmerica], #Australia
[iCongo, iEngland, iNetherlands, iPortugal, iEthiopia], #Boers
[iAmerica, iMississippi, iInuit], #Canada
[iEgypt, iArabia, iOttomans, iOman, iYemen], #Israel
]

#for stability hit on spawn
lOlderNeighbours = [
[], #Egypt
[], #Babylonia
[], #Harappa
[], #Norte Chico
[iEgypt], #Nubia
[iEgypt, iBabylonia], # Assyria
[], #China
[], #Hittites
[iEgypt, iBabylonia], #Greece
[], #Olmecs
[iHarappa], #India
[iEgypt, iBabylonia], #Carthage
[], #Celtia
[], # Polynesia
[iEgypt, iBabylonia, iAssyria, iHarappa, iGreece], #Persia
[iEgypt, iGreece, iCarthage], #Rome
[], # Yuezhi
[iOlmecs], #Maya
[iHarappa, iIndia], #Tamils
[iChina, iYuezhi], #Xiongnu
[iEgypt, iNubia], #Ethiopia
[], #Vietnam
[iMaya], #Teotihuacan
[iBabylonia, iAssyria, iGreece], # Armenia
[], #Inuit
[], # Mississippi
[iChina, iXiongnu], #Korea
[iNorteChico], #Tiwanaku
[iGreece], #Byzantium
[iNorteChico, iTiwanaku], #Wari
[iKorea], #Japan
[iCeltia], #Vikings
[iChina, iPersia, iYuezhi], # Turks
[iEgypt, iPersia, iByzantium, iNubia], #Arabia
[iChina, iHarappa, iIndia, iVietnam], #Tibet
[iKhmer, iVietnam], #Indonesia
[iIndia, iVietnam, iKhmer], #Burma
[iGreece, iPersia, iArabia, iTurks, iVikings], #Khazars
[iEgypt, iNubia, iArabia], #Chad
[], #Moors
[iCarthage, iRome], #Spain
[iRome], #France
[iEgypt, iBabylonia, iPersia, iTurks, iEthiopia, iNubia], #Oman
[], #Khitan
[iIndia, iVietnam], #Khmer
[iNorteChico, iWari], #Muisca
[iEgypt, iBabylonia, iPersia, iTurks, iEthiopia, iOman, iNubia], #Yemen
[], #England
[iGreece, iRome, iVikings], #Holy Rome
[], # Novgorod
[iPersia, iGreece, iByzantium, iKhazars], #Kievan Rus
[iByzantium, iKievanRus, iHolyRome, iKhazars], # Hungary
[iIndonesia, iKhmer], # Philippines
[iEthiopia, iOman, iYemen, iNubia], #Swahili
[iByzantium, iEthiopia, iArabia, iOman, iYemen, iNubia, iChad], #Mamluks
[iCarthage, iEthiopia, iArabia, iMoors, iNubia, iChad], #Mali
[iVikings, iHolyRome, iHungary], #Poland
[iNubia], #Zimbabwe
[iCarthage, iRome], #Portugal
[iNorteChico, iTiwanaku, iWari, iMuisca], #Inca
[iByzantium, iHolyRome], #Italy
[iMali, iNubia, iChad], #Nigeria
[iHolyRome, iHungary, iPoland], #Lithuania
[iChina, iJapan, iKorea, iArabia, iTibet, iKhmer, iTurks, iKhazars, iXiongnu], #Mongolia
[iMaya, iTeotihuacan], #Aztec
[iHarappa, iIndia, iPersia, iArabia, iTibet, iTurks], #Mughals
[iNovgorod, iKievanRus, iHungary, iPoland], # Tatar
[iBabylonia, iGreece, iPersia, iByzantium, iArabia, iTurks, iMamluks, iHungary, iOman, iYemen, iKhazars, iChad], #Ottomans
[iPersia, iGreece, iByzantium, iKievanRus, iHungary, iNovgorod, iTatar, iKhazars], #Russia
[iIndia, iChina, iJapan, iKhmer, iIndonesia, iVietnam, iPhilippines, iBurma], #Thailand
[iNigeria, iNubia, iChad], #Congo
[iVikings, iKhazars], #Sweden
[iRome, iHolyRome], #Netherlands
[iChina, iMongolia], #Manchuria
[iHolyRome, iPoland, iLithuania, iHungary], #Germany
[iSpain, iFrance, iEngland, iNetherlands, iPortugal, iAztecs, iMaya, iMississippi, iInuit], #America
[iSpain, iPortugal, iInca], #Argentina
[iSpain, iPortugal, iInca], #Brazil
[iEngland, iNetherlands], # Australia
[iEngland, iNetherlands], #Boers
[iAmerica, iMississippi, iInuit], #Canada
[iEgypt, iArabia, iOttomans, iOman, iYemen], #Israel
]

# civ birth dates

# converted to years - edead
tBirth = (
-3000, # 0, #3000BC			# Egypt
-3000, # 0, #3000BC			# Babylonia
-3000,					# Harappa
-3000,					# Norte Chico
-2500,					# Nubia
-2100,					# Assyria
-2100,					# China
-1900,					# Hittites
-1600, # 50, #1600BC			# Greece
-1600, 					# Olmecs
-1500, # 0, #3000BC			# India
-1200, # 66, #814BC # Leoreth: 1200 BC	# Carthage
-1200, 						# Celtia
-1000,					# Polynesia
-850, # 84, #844BC			# Persia
-753, # 90, #753BC			# Rome
-650,					# Yuezhi
-400, 					# Maya
-300,					# Tamils
-300,					# Xiongnu
-290, # 121, #300BC			# Ethiopia
-257,					# Vietnam
-200, 					# Teotihuacan
-200, 					# Armenia
-200,					# Inuit
-100,					# Mississippi
-50,					# Korea
110,					# Tiwanaku
330,					# Byzantium
400,					# Wari
525, # 97, #660BC			# Japan
551, # 177, #551AD			# Vikings
552,					# Turks
620, # 183, #622AD			# Arabia
630,					# Tibet
650,					# Indonesia
650, 		#849AD			# Burma
650, 						# Khazars
700,					#Chad
711,					# Moors
722, # 193, #718AD			# Spain
750, # 196, #751AD			# France
751,						# Oman
760,                                                          #Khitan
800, # 187, #657AD			# Khmer
800,						# Muisca
819,						# Yemen
820, # 203, #829AD			# England
840, # 205, #843AD			# Holy Rome
860, # 205, #843AD			# Novgorod
882,						# Kievan Rus
895,						# Hungary
900,						# Philippines
960, # 218					# Swahili
969,						# Mamluks
989, # 220, #989AD			# Mali
1025,					# Poland
1075,					# Zimbabwe
1130, # 234, #1128AD			# Portugal
1150, # 236, #1150AD			# Inca
1167, # Italy				# Italy
1180,						# Nigeria
1180,						# Lithuania
1190, # 240, #1190AD			# Mongolia
1195, # 241, #1195AD			# Aztecs
1206,					# Mughals
1210,					# Tatar
1280, # 249, #1280AD (1071AD)		# Turkey
1283, #previously 860AD			# Russia
1350,					# Thailand
1390,					# Congo
1523,					# Sweden
1580, # 281, #922AD # Leoreth: 1500 AD	# Netherlands
1636,					# Manchuria
1700,					# Germany
1775, # 346, #1775AD #332 for 1733AD	# America
1810,					# Argentina
1822,					# Brazil
1850,					# Australia
1852,					# Boers
1867,					# Canada
1948,					#Israel
-3000, # 0,
-3000, # 0,
-3000, # 0,
-3000, # 0,
-3000, # 0,
-3000
)

# Leoreth: stability penalty from this date on
tFall = (
-343,					# Egypt
-539,					# Babylonia
-1700,					# Harappa
-1800,					# Norte Chico
-1500,					# Nubia
-600,					# Assyria
1127,					# China
-700,					# Hittites
-146,					# Greece
-400,					# Olmecs
600, # end of Gupta Empire		# India
-146,					# Phoenicia
100,					# Celtia
1200,					# Polynesia
651,					# Persia
235, # crisis of the third century	# Rome
374,					# Yuezhi
900,					# Maya
1000,					# Tamils
480,					# Xiongnu
960,					# Ethiopia
602,					# Vietnam
550, #fall of Teotihuacan # Teotihuacan
430,					# Armenia
1650,							# Inuit
1540,							# Mississippi
1255, #Mongol invasion			# Korea
900,							# Tiwanaku
1204, #fourth crusade			# Byzantium
1100,					# Wari
2020,					# Japan
1300,					# Vikings
1507,					# Turks
900,					# Arabia
1500,					# Tibet
1500,					# Indonesia
1824,					# Burma
1241,					# Khazars
1897,					# Chad
1500,					# Moors
2020,					# Spain
2020,					# France
1856,					# Oman
1260,                                                          #Khitan
1200, # earlier so that the Thai can spawn # Khmer
1540,					# Muisca
1517,					# Yemen
2020,					# England
2020, #1648,			# Holy Rome
1478,					# Novgorod
2020,					# Hungary
1240,					# Kievan Rus
1570,					# Philippines
1600,					# Swahili
1517,					# Mamluks
1600,					# Mali
1650,					# Poland
1760,					# Zimbabwe
2020,					# Portugal
1533,					# Inca
2020,					# Italy
1897,					# Nigeria
2020,					# Lithuania
1368,					# Mongolia
1521,					# Aztecs
1640,					# Mughals
1480,					# Tatar
2020,					# Turkey
2020,					# Russia
2020,					# Thailand
1800,					# Congo
2020,					# Sweden
2020,					# Netherlands
1912,					# Manchuria
2020,					# Germany
2020,					# America
2020,					# Argentina
2020,					# Brazil
2020,					# Australia
2020,					# Boers
2020,					# Canada
2020					# Israel
)

dVictoryYears = {
iCivEgypt : (-850, -100, 170),
iCivBabylonia : (-1, -850, -700),
iCivHarappa : (-1600, -1500, -800),
iCivNorteChico : (-1, -1, -1),
iCivNubia : (-656, 1365, 1821),
iCivAssyria : (-1, -1, -1),
iCivChina : (1000, -1, 1800),
iCivHittites : (-1, -1, -1),
iCivGreece : (-1, -330, -250),
iCivOlmecs : (-400, -400, -1),
iCivIndia : (-100, 700, 1200),
iCivCarthage : (-300, -100, 200),
iCivCeltia : (-270, -280, 800),
iCivPolynesia : (800, 1000, 1200),
iCivPersia : (140, 350, 350),
iCivRome : (100, 320, -1),
iCivYuezhi : (30, 200, 400),
iCivMaya : (200, 900, -1),
iCivTamils : (800, 1000, 1200),
iCivXiongnu : (210, 210, 560),
iCivEthiopia : (400, 1200, 1500),
iCivVietnam : (-1, 1500, 1950),
iCivTeotihuacan : (550, 550, 1000),
iCivArmenia : (-1, -1, -1),
iCivInuit : (900, -1, -1),
iCivMississippi : (500, 1070, 1400),
iCivKorea : (1200, -1, -1),
iCivTiwanaku : (900, 1000, 1100),
iCivByzantium : (1000, 1200, 1450),
iCivWari : (900, 1000, 1100),
iCivJapan : (1600, 1940, -1),
iCivChalukya : (-1, -1, -1),
iCivVikings : (1050, 1100, 1500),
iCivTurks : (900, 1100, 1400),
iCivArabia : (1300, 1300, -1),
iCivTibet : (1000, 1400, 1700),
iCivIndonesia : (1300, 1500, 1940),
iCivBurma : (1000, 1211, 1850),
iCivKhazars : (1031, 1031, 1241),
iCivChad : (1259, 1380, 1603),
iCivMoors : (1200, 1300, 1650),
iCivSpain : (-1, 1650, 1650),
iCivFrance : (1700, 1800, 1900),
iCivOman : (-1, -1, -1),
iCivKhitan : (-1, -1, -1),
iCivKhmer : (1200, 1450, 1450),
iCivMuisca : (-1, -1, -1),
iCivYemen : (1229, 1265, -1),
iCivEngland : (1730, 1800, -1),
iCivScotland : (-1, -1, -1),
iCivHolyRome : (1550, 1650, 1850),
iCivNovgorod : (-1, -1, -1),
iCivKievanRus : (1327, -1, 1327),
iCivHungary : (1301, 1867, -1),
iCivPhilippines : (1400, 1500, 1600),
iCivChimu : (1300, 1475, 1500),
iCivSwahili : (1500, 1500, 1650),
iCivMamluks : (1300, 1380, 1500),
iCivMali : (1350, 1500, 1700),
iCivPoland : (1400, -1, 1600),
iCivZimbabwe : (1400, 1500, 1700),
iCivPortugal : (1550, 1650, 1700),
iCivInca : (1500, 1550, 1700),
iCivItaly : (1500, 1600, 1930),
iCivNigeria : (1600, 1750, 1950),
iCivLithuania : (1500, 1600, 1950),
iCivMongols : (1300, -1, 1500),
iCivAztec : (1520, 1650, -1),
iCivMughals : (1500, 1660, 1750),
iCivTatar : (-1, -1, -1),
iCivOttomans : (1550, 1700, 1800),
iCivRussia : (1920, -1, 1950),
iCivThailand : (1650, 1700, 1900),
iCivCongo : (1650, 1800, -1),
iCivIran : (1650, 1750, 1800),
iCivSweden : (1700, 1800, 1970),
iCivNetherlands : (1745, 1745, 1775),
iCivManchuria : (1800, 1850, -1),
iCivGermany : (1900, 1940, -1),
iCivAmerica : (1900, 1950, 2000),
iCivMexico : (1880, 1940, 1960),
iCivArgentina : (1930, 1960, 2000),
iCivColombia : (1870, 1920, 1950),
iCivBrazil : (1880, -1, 1950),
iCivAustralia : (1950, 1950, -1),
iCivBoers : (1920, 1950, 1980),
iCivCanada : (1920, 1950, 2000),
iCivIsrael : (1980, 2000, -1),
}

# Leoreth: date-triggered respawn for certain civs
dRebirth = {
iHarappa : 530,		# Chalukya
iNorteChico : 900,		# Chimu
iCeltia : 820,		# Scotland
iPersia : 1501,		# Iran
iMaya : 1814,		# Colombia
iAztecs : 1810,		# Mexico
}

dRebirthCiv = {
iHarappa : iCivChalukya,
iNorteChico : iCivChimu,
iCeltia : iCivScotland,
iPersia : iCivIran,
iMaya : iCivColombia,
iAztecs : iCivMexico,
}

tResurrectionIntervals = (
[(664, -343)], #Egypt
[(-3000, -900)], #Babylonia
[],		# Harappa
[],		# Norte Chico
[(-785, 350), (350, 1365), (1504, 2020)], #Nubia
[],		# Assyria
[(-300, 2020)], #China
[(-300, 50)], #Hittites
[(1800, 2020)], #Greece
[], #Olmecs
[(1600, 1800), (1900, 2020)], #India
[(-1000, -150), (1200, 1400), (1956, 2020)], #Carthage
[(1910, 2020)], #Celtia
[(700, 2020)],		# Polynesia
[(220, 650), (1500, 2020)], #Persia
[(-750, 450)], #Rome
[(-600, 250)], #Yuezhi
[(0, 800)], #Maya
[(-300, 600), (1300, 1650), (1940, 2020)], #Tamils
[], #Xiongnu
[(1270, 1520), (1850, 2020)], #Ethiopia
[(950, 1400), (1400, 1800), (1940, 2020)], #Vietnam
[(-100, 1000)], #Teotihuacan
[(-100, 350), (870, 1400), (1900, 2020)],		# Armenia
[(100, 1400)], #Inuit
[], #Mississippi
[(1380, 1522), (1700, 1800), (1940, 2020)], #Korea
[], #Tiwanaku
[(1100, 1280)], #Byzantium
[], #Wari
[(1800, 2020)], #Japan
[(1520, 2020)], #Vikings
[(1350, 1500), (1700, 1800), (1940, 2020)], #Turks
[(1900, 2020)], #Arabia
[(700, 1600)],   #Tibet
[(900, 1600), (1900, 2020)], #Indonesia
[(900, 1700), (1948, 2020)], #Burma
[(1465, 1781), (1990, 2020)], #Khazars
[(1380, 1522), (1800, 2020)], #Chad
[(1000, 2020)],	#Moors
[(1700, 2020)], #Spain
[(1700, 2020)], #France
[(1340, 1690), (1850, 2020)], #Oman
[],		# Khitan
[(900, 1200), (1950, 2020)], #Khmer
[], #Muisca
[(1636, 1849), (1918, 2020)], #Yemen
[(1700, 2020)], #England
[(1800, 2020)], #Holy Rome
[(900, 1400)], #Novgorod
[(1649, 1764), (1917, 2020)], #Kievan Rus
[(1200, 1690), (1918, 2020)],	#Hungary
[(1200, 1500), (1900, 2020)],	#Philippines
[(1850, 2020)],	#Swahili
[(1800, 2020)], #Mamluks
[(1340, 1590), (1900, 2020)], #Mali
[(1340, 1690), (1920, 2020)], #Poland
[(1649, 1764), (1917, 2020)],		# Zimbabwe
[(1700, 2020)], #Portugal
[(1800, 2020)], #Inca
[(1520, 2020)], #Italy
[(1340, 1690), (1900, 2020)],		# Nigeria
[(1910, 2020)],		#Lithuania
[(1340, 1690), (1910, 2020)], #Mongolia
[], 		#Aztec
[(1940, 2020)], #Mughals
[(1280, 1650)], #Tatar
[(1700, 2020)], #Ottomans
[(1480, 1550), (1700, 2020)], #Russia
[(1700, 2020)], #Thailand
[(1700, 2020)],		#Congo
[(1700, 2020)], #Sweden
[(1700, 2020)], #Netherlands
[],	#Manchuria
[(1840, 2020)], #Germany
[(1770, 2020)], #America
[(1810, 2020)], #Argentina
[(1820, 2020)], #Brazil
[(1850, 2020)], #Australia
[(1852, 2020)], #Boers
[(1867, 2020)], #Canada
[(1948, 2020)], #Israel
)

#rnf. Some civs have a double entry, for a higher chance
lEnemyCivsOnSpawn = [
[iNubia, iHittites], #Egypt
[iIndependent, iIndependent2, iAssyria], #Babylonia
[], #Norte Chico
[], #Harappa
[iEgypt, iEgypt], #Nubia
[iBabylonia], #Assyria
[iIndependent, iIndependent2, iIndependent2], #China
[iEgypt, iAssyria], #Hittites
[iIndependent, iIndependent2, iBabylonia], #Greece
[], #Olmecs
[iTamils], #India
[], #Carthage
[], #Celtia
[], #Polynesia
[iBabylonia, iBabylonia, iBabylonia, iAssyria, iAssyria, iAssyria, iGreece, iCarthage, iCarthage], #Persia
[], #Rome
[], #Yuezhi
[], #Maya
[iIndia], #Tamils
[iChina, iYuezhi, iYuezhi], #Xiongnu
[], #Ethiopia
[iChina],	#Vietnam
[iMaya], #Teotihuacan
[],	#Armenia
[], #Inuit
[], #Mississippi
[], #Korea
[], #Tiwanaku
[iGreece, iPersia], #Byzantium
[], #Wari
[], #Japan
[iCeltia, iCeltia, iEngland, iEngland, iFrance, iIndependent, iIndependent2], #Vikings
[iChina, iChina, iPersia, iPersia, iArmenia, iIndependent, iIndependent, iIndependent2, iIndependent2, iOman, iOman], # Turks
[iEgypt, iEgypt, iEgypt, iBabylonia, iBabylonia, iGreece, iPersia, iPersia, iPersia, iCarthage, iRome, iByzantium, iByzantium, iArmenia, iSpain, iFrance, iCeltia, iCeltia, iIndependent, iIndependent2], #Arabia
[], #Tibet
[iKhmer, iKhmer], #Indonesia
[iKhmer, iKhmer], #Burma
[iKievanRus, iKievanRus, iHungary], #Khazars
[iNigeria], #Chad
[], #Moors
[], #Spain
[], #France
[], #Oman
[iChina, iChina, iChina, iKorea, iKorea],		# Khitan
[], #Khmer
[], #Muisca
[], #Yemen
[iCeltia, iCeltia, iCeltia], #England
[iRome, iArabia, iArabia], #Holy Rome
[], #Novgorod
[iKhazars, iKhazars], #Kievan Rus
[iKhazars],	#Hungary
[],	#Philippines
[],	#Swahili
[iByzantium, iByzantium, iYemen],	#Mamluks
[], #Mali
[], #Poland
[],	#Zimbabwe
[], #Portugal
[iNorteChico, iNorteChico, iTiwanaku, iTiwanaku, iTiwanaku, iWari, iWari, iWari], #Inca
[], #Italy
[iChad],	#Nigeria
[],	#Lithuania
[iChina, iChina, iChina, iKorea, iKorea, iTurks, iTurks, iTurks, iKhitan, iKhitan, iIndependent, iIndependent, iIndependent2, iIndependent2], #Mongolia
[iMaya, iTeotihuacan], #Aztec
[iIndia, iIndia], #Mughals
[iKhazars, iKhazars, iKhazars, iKievanRus, iKievanRus, iKievanRus, iNovgorod, iIndependent, iIndependent, iIndependent2, iIndependent2], #Tatar
[iEgypt, iEgypt, iMamluks, iMamluks, iBabylonia, iGreece, iGreece, iArabia, iArabia, iArabia, iByzantium, iByzantium, iByzantium, iOman, iOman], #Ottomans
[iKhazars, iKhazars, iKhazars, iKievanRus, iKievanRus, iKievanRus, iNovgorod, iNovgorod, iNovgorod, iTatar, iTatar, iTatar ], #Russia
[iKhmer, iKhmer, iKhmer, iBurma, iBurma], #Thailand
[], #Congo
[], #Sweden
[], #Netherlands
[iChina, iChina, iChina, iKorea, iMongolia], #Manchu
[iHolyRome, iPoland], #Germany
[iIndependent, iIndependent2], #America
[iSpain, iSpain, iIndependent, iIndependent2], #Argentina
[iIndependent, iIndependent2], #Brazil
[], #Australia
[iEngland, iNetherlands], #Boers
[], #Canada
[iEgypt, iEgypt, iEgypt, iPersia, iArabia, iArabia, iArabia, iMoors, iOttomans, iOttomans], #Israel
]

# Leoreth: date-triggered respawn for certain civs
lEnemyCivsOnRespawn = {
iPersia : [iOttomans, iRussia, iOman, iOman],		# Iran
iNorteChico : [iTiwanaku, iWari],		# Chimu
iHarappa : [iIndia, iTamils],		# Chalukya
iCeltia : [],		# Scotland
iMaya : [],		# Colombia
iAztecs : [iAmerica],		# Mexico
}

# Leoreth
lTotalWarOnSpawn = [
[iNubia, iHittites], #Egypt
[], #Babylonia
[], #Harappa
[], #Norte Chico
[], #Nubia
[iEgypt, iBabylonia], #Assyria
[], #China
[], #Hittites
[], #Greece
[], #Olmecs
[], #India
[], #Phoenicia
[iEngland], #Celtia
[], #Polynesia
[iBabylonia, iCarthage, iArabia], #Persia
[iCeltia, iCeltia, iGreece], #Rome
[], #Yuezhi
[], #Maya
[], #Tamils
[iChina, iYuezhi, iYuezhi], #Xiongnu
[], #Ethiopia
[],	#Vietnam
[], #Teotihuacan
[], #Armenia
[], #Inuit
[], #Mississippi
[], #Korea
[], #Tiwanaku
[iGreece], #Byzantium
[], #Wari
[], #Japan
[], #Vikings
[], #Turks
[iEgypt, iBabylonia, iCarthage, iPersia], #Arabia
[], #Tibet
[], #Indonesia
[], #Burma
[iKievanRus, iKievanRus, iHungary], #Khazars
[], #Chad
[], #Moors
[iMoors], #Spain
[], #France
[iTurks, iTurks], #Oman
[iChina],		# Khitan
[], #Khmer
[], #Muisca
[], #Yemen
[], #England
[iRome], #Holy Rome
[], #Novgorod
[], #Kievan Rus
[],	#Hungary
[],	#Philippines
[],	#Swahili
[],	#Mamluks
[], #Mali
[], #Poland
[],	#Zimbabwe
[], #Portugal
[iNorteChico, iTiwanaku, iWari], #Inca
[], #Italy
[],	#Nigeria
[],	#Lithuania
[iChina], #Mongolia
[iMaya], #Aztec
[iIndia], #Mughals
[iKievanRus, iKhazars], #Tatar
[iArabia, iEgypt, iMamluks], #Ottomans
[iKievanRus, iKhazars, iNovgorod, iTatar], #Russia
[iKhmer], #Thailand
[], #Congo
[], #Sweden
[], #Netherlands
[iChina, iMongolia],	#Manchuria
[], #Germany
[], #America
[], #Argentina
[], #Brazil
[],	#Australia
[],	#Boers
[], #Canada
[], #Israel
]


#AIWars
tAggressionLevel = (
0, #Egypt
1, #Babylonia
0, #Harappa
0, #Norte Chico
1, #Nubia
3, #Assyria
1, #China
1, #Hittites
2, #Greece
0, #Olmecs
0, #India
0, #Carthage
2, #Celtia
0, #Polynesia
3, #Persia
3, #Rome
2, #Yuezhi
1, #Maya
1, #Tamils
2, #Xiongnu
0, #Ethiopia
0, #Vietnam
1, #Teotihuacan
1, #Armenia
0, #Inuit
0, #Mississippi
0, #Korea
0, #Tiwanaku
1, #Byzantium
2, #Wari
1, #Japan
2, #Viking
2, #Turks
2, #Arabia
1, #Tibet
1, #Indonesia
2, #Burma
2, #Khazars
2, #Chad
1, #Moors
2, #Spain
1, #France
2, #Oman
2, #Khitan
2, #Khmer
0, #Muisca
2, #Yemen
1, #England
2, #Holy Rome
0, #Novgorod
0, #Kievan Rus
2, #Hungary
0, #Philippines
0, #Swahili
1, #Mamluks
0, #Mali
1, #Poland
0, #Zimbabwe
0, #Portugal
3, #Inca
0, #Italy
0, #Nigeria
2, #Lithuania
2, #Mongolia
1, #Aztec
1, #Mughals
2, #Tatar
2, #Ottomans
1, #Russia
0, #Thailand
0, #Congo
1, #Sweden
0, #Holland
1, #Manchuria
2, #Germany
2, #America
0, #Argentina
0, #Brazil
0, #Australia
0, #Boers
0, #Canada
1, #Israel
0) #Barbs


#war during rise of new civs
tAIStopBirthThreshold = (
    80, #Egypt
    50, #Babylonia
    50, #Harappa
    50, #Norte Chico
    80, #Nubia
    50, #Assyria
    60, #China
    60, #Hittites
    50, #Greece #would be 80 but with Turks must be lower
    80, #Olmecs
    80, #India
    80, #Carthage
    30, #Celtia
    80, #Polynesia
    70, #Persia
    80, #Rome
    30, #Yuezhi
    80, #Maya
    80, #Tamils
    30, #Xiongnu
    80, #Ethiopia
    80,	#Vietnam
    80, #Teotihuacan
    80, #Armenia
    30, #Inuit
    80, #Mississippi
    80, #Korea
    80, #Tiwanaku
    80, #Byzantium
    80, #Wari
    80, #Japan
    80, #Viking
    50, #Turks
    80, #Arabia
    80, #Tibet
    80, #Indonesia
	80, #Burma
	50, #Khazars
	80, #Chad
    80, #Moors
    80, #Spain  #60 in vanilla and Warlords
    80, #France #60 in vanilla and Warlords
	50, #Oman
    80, #Khitan
    80, #Khmer
	80, #Muisca
	50, #Yemen
    50, #England
    80, #Holy Rome #70 in vanilla and Warlords
    80, #Novgorod
    80, #Kievan Rus
	70,	#Hungary
	70,	#Philippines
	70, #Swahili
	80,	#Mamluks
    70, #Mali
    40, #Poland
	80,	#Zimbabwe
    40, #Portugal
    70, #Inca
    60, #Italy
	80,	#Nigeria
    40, #Lithuania
    70, #Mongolia
    50, #Aztec
    70, #Mughals
    70, #Tatar
    70, #Turkey
    50, #Russia
    80, #Thailand
    80, #Congo
    70, #Sweden
    40, #Holland
    70, #Manchuria
    80, #Germany
    50, #America
    60, #Argentina
    60, #Brazil
    60,	#Australia
	60,	#Boers
    60, #Canada
	60, #Israel
    100,
    100,
    100,
    100,
    100)


#RiseAndFall
tResurrectionProb = (
80, #Egypt
95, #Babylonia
0, #Harappa
0, #Norte Chico
60, #Nubia
0, #Assyria
100, #China
50, #Hittites
60, #Greece
50, #Olmecs
50, #India
70, #Carthage
50, #Celtia
40, #Polynesia
90, #Persia
75, #Rome
0, #Yuezhi
30, #Maya
50, #Tamils
0, #Xiongnu
80, #Ethopia
80,	#Vietnam
30, #Teotihuacan
60, #Armenia
70, #Inuit
0, 	#Mississippi
80, #Korea
0, #Tiwanaku
75, #Byzantium
0, #Wari
100, #Japan
60, #Viking
50, #Turks
100, #Arabia
60, #Tibet
80, #Indonesia
60, #Burma
30, #Khazars
30, #Chad
70, #Moors
100, #Spain
100, #France
100, #Oman
0, #Khitan
60, #Khmer
0,  #Muisca
100, #Yemen
100, #England
80, #Holy Rome
80, #Novgorod
65, #Kievan Rus
30,	#Hungary
60,	#Philippines
60,	#Swahili
60,	#Mamluks
60, #Mali
65, #Poland
60,	#Zimbabwe
100, #Portugal
70, #Inca
100, #Italy
60,	#Nigeria
45, #Lithuania
80, #Mongolia
70, #Aztec
80, #Mughals
60, #Tatar
100, #Ottomans
100, #Russia
100, #Thailand
60, #Congo
100, #Sweden
100, #Holland
0, #Manchuria
100, #Germany
100, #America
100, #Argentina
100, #Brazil
100, #Australia
100, #Boers
100, #Canada
100, #Israel
#    100, #Holland
#    100, #Portugal
100) #Barbs 


#Congresses.
tPatienceThreshold = (
30, #Egypt
30, #Babylonia
30, #Harappa
30, #Norte Chico
30, #Nubia
30, #Assyria
30, #China
30, #Hittites
35, #Greece
30, #Olmecs
50, #India
35, #Carthage
30, #Celtia
50, #Polynesia
30, #Persia
25, #Rome
30, #Yuezhi
35, #Maya
45, #Tamils
30, #Xiongnu
20, #Ethopia
25,	#Vietnam
35, #Teotihuacan
25, #Armenia
40, #Inuit
30, #Mississippi
25, #Korea
30, #Tiwanaku
25, #Byzantium
20, #Wari
25, #Japan
30, #Viking
30, #Turks
30, #Arabia
50, #Tibet
30, #Indonesia
20, #Burma
30, #Khazars
20, #Chad
20, #Moors
20, #Spain
20, #France
20, #Oman
30, #Khitan
30, #Khmer
20, #Muisca
20, #Yemen
20, #England
20, #Holy Rome
35, #Novgorod
35, #Kievan Rus
20,	#Hungary
30,	#Philipinnes
30,	#Swahili
20,	#Mamluks
35, #Mali
20, #Poland
20,	#Zimbabwe
30, #Portugal
35, #Inca
25, #Italy
20,	#Nigeria
20, #Lithuania
20, #Mongolia
30, #Aztec
35, #Mughals
35, #Tatar
35, #Ottomans
30, #Russia
30, #Thailand
20, #Congo
30, #Sweden
30, #Holland
20,	#Manchuria
20, #Germany
30, #America
40, #Argentina
40, #Brazil
40,	#Australia
40,	#Boers
40, #Canada
40, #Israel
100) #Barbs

dMaxColonists = {
iVikings : 1,
iSpain : 7,
iFrance : 5,
iEngland : 6,
iPortugal : 7, 
iSweden: 2,
iNetherlands : 6,
iGermany : 2
}

# initialise religion variables to religion indices from XML
iNumReligions = 10
(iJudaism, iOrthodoxy, iCatholicism, iProtestantism, iIslam, iHinduism, iBuddhism, iConfucianism, iTaoism, iZoroastrianism) = range(iNumReligions)

#Persecution preference
tPersecutionPreference = (
(iHinduism, iBuddhism, iTaoism, iConfucianism, iZoroastrianism, iIslam, iProtestantism, iCatholicism, iOrthodoxy), # Judaism
(iIslam, iProtestantism, iCatholicism, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iTaoism, iConfucianism), # Orthodoxy
(iIslam, iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iTaoism, iConfucianism), # Catholicism
(iIslam, iCatholicism, iOrthodoxy, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iTaoism, iConfucianism), # Protestantism
(iHinduism, iProtestantism, iCatholicism, iOrthodoxy, iJudaism, iTaoism, iConfucianism, iZoroastrianism, iBuddhism), # Islam
(iIslam, iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iTaoism, iConfucianism, iBuddhism), # Hinduism
(iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iTaoism, iIslam, iConfucianism, iHinduism), # Buddhism
(iIslam, iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iTaoism), # Confucianism
(iIslam, iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iZoroastrianism, iHinduism, iBuddhism, iConfucianism), # Taoism
(iIslam, iCatholicism, iProtestantism, iOrthodoxy, iJudaism, iBuddhism, iHinduism, iTaoism, iConfucianism), # Zoroastrianism
)

lCatholicStart = [iSpain, iFrance, iEngland, iHolyRome, iPoland, iPortugal, iItaly, iNetherlands, iSweden, iGermany, iAmerica, iArgentina, iBrazil, iBoers, iAustralia, iCanada]
lProtestantStart = [iSweden, iNetherlands, iGermany, iAmerica, iAustralia, iBoers]

# corporations
iNumCorporations = 11
(iTransSaharanRoute, iSpiceRoute, iSilkRoute, iTradingCompany, iCerealIndustry, iFishingIndustry, iTextileIndustry, iSteelIndustry, iOilIndustry, iLuxuryIndustry, iComputerIndustry) = range(iNumCorporations)

# initialise tech variables to unit indices from XML

iNumTechs = 141
(iTanning, iMining, iPottery, iPastoralism, iAgriculture, iMythology, iSailing,
iSmelting, iMasonry, iLeverage, iProperty, iCeremony, iDivination, iSeafaring,
iAlloys, iConstruction, iRiding, iArithmetics, iWriting, iCalendar, iShipbuilding,
iBloomery, iCement, iMathematics, iContract, iLiterature, iPriesthood, iNavigation,
iGeneralship, iEngineering, iAesthetics, iCurrency, iLaw, iPhilosophy, iMedicine,
iNobility, iSteel, iArchitecture, iArtisanry, iPolitics, iScholarship, iEthics,
iFeudalism, iFortification, iMachinery, iAlchemy, iGuilds, iCivilService, iTheology,
iCommune, iCropRotation, iPaper, iCompass, iPatronage, iEducation, iDoctrine,
iGunpowder, iCompanies, iFinance, iCartography, iHumanities, iPrinting, iJudiciary,
iFirearms, iLogistics, iExploration, iOptics, iAcademia, iStatecraft, iHeritage,
iCombinedArms, iEconomics, iGeography, iScientificMethod, iUrbanPlanning, iCivilLiberties, iHorticulture,
iReplaceableParts, iHydraulics, iPhysics, iGeology, iMeasurement, iSociology, iSocialContract,
iMachineTools, iThermodynamics, iMetallurgy, iChemistry, iBiology, iRepresentation, iNationalism,
iBallistics, iEngine, iRailroad, iElectricity, iRefrigeration, iLabourUnions, iJournalism,
iPneumatics, iAssemblyLine, iRefining, iFilm, iMicrobiology, iConsumerism, iCivilRights,
iInfrastructure, iFlight, iSynthetics, iRadio, iPsychology, iMacroeconomics, iSocialServices,
iAviation, iRocketry, iFission, iElectronics, iTelevision, iPowerProjection, iGlobalism,
iRadar, iSpaceflight, iNuclearPower, iLaser, iComputers, iTourism, iEcology,
iAerodynamics, iSatellites, iSuperconductors, iRobotics, iTelecommunications, iRenewableEnergy, iGenetics,
iSupermaterials, iFusion, iNanotechnology, iAutomation, iBiotechnology,
iUnifiedTheory, iArtificialIntelligence,
iTranshumanism) = range(iNumTechs)

# initialise unit variables to unit indices from XML

iNumUnits = 288
(iLion, iTiger, iBear, iPolarBear, iPanther, iJaguarAnimal, iWolf, iHyena, iRabbit, iSettler, iCityBuilder, iPioneer, iKhagan, iDogSled, iWorker, iArtisan, iPunjabiWorker, iArchitect, iAyllu, iLabourer, 
iMadeireiro, iScout, iExplorer, iCaravan, iBandeirante, iSpy, iSisqeno, iReligiousPersecutor, iJewishMissionary, iOrthodoxMissionary, iCatholicMissionary, iProtestantMissionary, 
iIslamicMissionary, iHinduMissionary, iBuddhistMissionary, iConfucianMissionary, iTaoistMissionary, iZoroastrianMissionary, iWarrior, iMilitia, iCityGuard, iKoa, iFalconDancer, iAxeman, iLightSwordsman, 
iVulture, iDogSoldier, iKhopesh,  iSwordsman, iJaguar, iLegion, iGallicWarrior, iAucac, iShotelai, iHeavySwordsman, iUshkuinik, iVishap, iSamurai, 
iHuscarl, iGhazi, iPombos, iDoppelSoldner, iKallarani, iSpearman, iHoplite, iSacredBand, iImmortal, iEagle, iHolkans, iImpi, iHeavySpearman, iSheltron, iKyundaw, iBambooRuncing, iPhakak, iDruzhina, iPikeman, 
iLandsknecht, iTagmata, iAshigaru, iDobDob, iRozwiWarrior, iArquebusier, iFirelancer, iTercio, iStrelets, iJanissary, iOromoWarrior, iQizilbash, iMohawk, iMusketeer, iBandeirantes, 
iRedcoat, iKarolin, iFusilier, iMinuteman, iIronHelmet, iRifleman, iMehalSefari, iMahardlek, iGrenadier, iRocketeer, iGrenzer, iAlbionLegion, iGardist, iNaffatun, iAntiTank, 
iInfantry, iBersagliere, iPatricios, iEjercito, iSepoy, iDigger, iSamInfantry, iMobileSam, iMarine, iNavySeal, iGuardaNacional, iParatrooper, iMechanizedInfantry, iArcher, iAsharittuBowman, iMedjay, iPictaAucac,
iSkirmisher, iHolkan, iKelebolo, iChimuSuchucChiquiAucac, iGuechaWarrior, iLongbowman, iPatiyodha, iNgolo, iSlinger, iRattanArcher, iCrossbowman, iChokonu, iBalestriere, iChariot, iWarChariot, 
iHuluganni, iCidainh, iScythedChariot, iHorseman, iCompanion, iNumidianCavalry, iAsvaka, iGuli, iCamelRider, iHorseArcher, iMangudai, iKhampa, 
iOghuz, iBerber, iCamelArcher, iArabianCamelArcher, iLancer, iIronpagoda, iVaru, iSavaran, iMobileGuard, iKeshik, iCataphract, iChangSuek, iRoyalMamluk, iYanLifida, iHuszar, iFarari, iChevalier, iGhulamWarrior, iVytis, 
iPistolier, iMountedBrave, iSavannaHunter, iCamelGunner, iMoorsCamelGunner, iCuirassier, iTatarNoyan, iEightBanner, iGendarme, iConquistador, iWingedHussar, iCondotierro, iHussar, iCossack, iLlanero, 
iDragoon, iGuard, iGrenadierCavalry, iCavalry, iRural, iKommando, iWarElephant, iBallistaElephant, iAtlasElephant, iMahout, iTank, iPanzer, iMainBattleTank, iMerkava, 
iGunship, iCatapult, iRam, iBallista, iTrebuchet, iFirelance, iSiegeEngineer, iBombard, iHwacha, iTabor, iSiegeElephant, iGreatBombard, iCannon, iHeavyCannon, iArtillery, 
iMachineGun, iHowitzer, iHeavyHowitzer, iMobileArtillery, iWorkboat, iGalley, iWaka, iBireme, iBalangay, iWarGalley, iHeavyGalley, iDromon, 
iLongship, iCog, iDharani, iDhow, iGalleass, iDjong, iKobukson, iLanternas, iCaravel, iCarrack, iBaghlah, iGalleon, 
iEastIndiaman, iPrivateer, iCorsair, iFrigate, iShipOfTheLine, iManOfWar, iSteamship, iIronclad, iTorpedoBoat, iCruiser, 
iTransport, iDestroyer, iCorvette, iBattleship, iMissileCruiser, iStealthDestroyer, iSubmarine, iNuclearSubmarine, iCarrier, iBiplane, 
iFighter, iZero, iJetFighter, iArrow, iBomber, iStealthBomber, iGuidedMissile, iDrone, iNuclearBomber, iICBM, iSatellite, 
iGreatProphet, iGreatArtist, iGreatScientist, iGreatMerchant, iGreatEngineer, iGreatStatesman, iGreatGeneral, iArgentineGreatGeneral, iGreatSpy, iFemaleGreatProphet, 
iFemaleGreatArtist, iFemaleGreatScientist, iFemaleGreatMerchant, iFemaleGreatEngineer, iFemaleGreatStatesman, iFemaleGreatGeneral, iFemaleGreatSpy, iSlave, iAztecSlave) = range(iNumUnits)

iMissionary = iJewishMissionary # generic

lGreatPeopleUnits = [iGreatProphet, iGreatArtist, iGreatScientist, iGreatMerchant, iGreatEngineer, iGreatStatesman]

dFemaleGreatPeople = {
iGreatProphet : iFemaleGreatProphet,
iGreatArtist : iFemaleGreatArtist,
iGreatScientist : iFemaleGreatScientist,
iGreatMerchant : iFemaleGreatMerchant,
iGreatEngineer : iFemaleGreatEngineer,
iGreatStatesman : iFemaleGreatStatesman,
iGreatGeneral : iFemaleGreatGeneral,
iGreatSpy : iFemaleGreatSpy,
}

# initialise bonuses variables to bonuses IDs from WBS
iNumBonuses = 54
(iAluminium, iAmber, iCamel, iCitrus, iCoal, iCopper, iDates, iHorse, iIron, iMarble,
iOil, iStone, iUranium, iBanana, iClam, iCorn, iCow, iCrab, iDeer, iFish,
iPig, iPotato, iRice, iSheep, iWheat, iCocoa, iCoffee, iCotton, iDye, iFur,
iGems, iGold, iIncense, iIvory, iJade, iMillet, iObsidian, iOlives, iOpium, iPearls,
iRareEarths, iRubber, iSalt, iSilk, iSilver, iSpices, iSugar, iTea, iTobacco, iWine,
iWhales, iSoccer, iSongs, iMovies) = range(iNumBonuses)

iNumBonusVarieties = 18
(iDyeMurex, iDyeHenna, iSpacesCinnamon, iSpicesNutmeg, iSpicesSaffron, iSpicesVanilla, iGemsTurquoise, iGemsDiamonds, iGemsRuby, iGemsSapphire, 
iGemsEmeralds, iSheepLlama, iSheepBlack, iCowBrown, iPigFurry, iIvoryAfrican, iCitrusOranges, iCrabShrimp) = range(iNumBonuses, iNumBonuses + iNumBonusVarieties)

# Buildings

iNumBuildings = 404
(iPalace, iBarracks, iEkal, iIkhanda, iCastra, iGranary, iTerrace, iColcas, iIgloo, iSmokehouse, iShieling, iKraal, iSaltovo, iPaganTemple, iMonument, iKhachkar, iObelisk, iStele,
iCandi, iEdict, iMalae, iTotemPole, iZiara, iStatue, iDeffufas, iShicra, iColossalHead, iWalls, iIya, iDun, iKasbah, iStable, iGer, iEstancia, iBullring, iGerTereg, iLibrary, iEdubba,
iTaixue, iHoTrai, iSangam, iPaya, iGandharaSchool, iHarbor, iCothon, iFishery, iPort, iMina, iAqueduct, iBaray, iNoria, iStepwell, iChinampa, iAbAnbar, iDam, iTheatre, iOdeon,
iHippodrome, iOpera, iArena, iBallCourt, iCharreadaArena, iGarden, iBasilica, iLighthouse, iTradingPost, iZango, iWeaver, iMbwadi,
iMarket, iForum, iGlassmaker, iAgora, iBazaar, iSouq, iJail, iSacrificialAltar, iDivan, iBath, iReservoir, iTemazcal, iHammam, iForge, iIronForge,
iMint, iArtStudio, iDutchMill, iStoneCutter, iGoldsmith, iCastle, iCitadel, iMountainFortress, iVegvar, iKancha, iPharmacy, iApothecary, iAlchemist, iPostOffice, iTambo, iShreni, iYam, iCaravanserai,
iWharf, iCoffeehouse, iSalon, iPavilion, iPublicHouse, iTeahouse, iPagoda, iMeadhall, iBank, iRoyalExchange, iSaltMine, iRiksbank, iPiaohao, iConstabulary, iMountedPolice, iCustomsHouse, iFeitoria, iCollegantia, iTradeGuild, iImmigrationOffice, iUniversity,
iSeowon, iGompa, iPublicUniversity, iNizamiyya, iCivicSquare, iRathaus, iSejmik, iSambadrome, iWene, iPendopo, iDinh, iKalasasaya, iSewer, iEarlySewer, iStarFort, iQila, iKremlin, iPlaas, iEstate, iMausoleum, iFazenda, 
iHacienda, iChateau, iFolwark, iColonyAdministration, iDrydock, iLevee, iDike, iFLoatingMarket, iObservatory, iKushitePyramid, iKatun, iWarehouse, iKonets, iCourthouse, iTatarOrda,iXeer, iSatrapCourt, iVeche, iSeimelis, iFactory, iAssemblyPlant, iZaibatsu, 
iDistillery, iPark, iKibbutz, iEffigyMound, iCoalPlant, iRailwayStation, iLaboratory, iResearchInstitute, iNewsPress, iIndustrialPark, iCinema, iHospital, iMendicantOrder, 
iSupermarket, iColdStoragePlant, iPublicTransportation, iDepartmentStore, iMall, iBroadcastTower, iMicrowaveStation, iIntelligenceAgency, iElectricalGrid, iAirport, iBunker, iPillbox, 
iBombShelters, iHydroPlant, iSecurityBureau, iStadium, iContainerTerminal, iNuclearPlant, iSupercomputer, iHotel, iResort, iRecyclingCenter, iLogisticsCenter, 
iSolarPlant, iFiberNetwork, iAutomatedFactory, iVerticalFarm, iJewishTemple, iJewishCathedral, iJewishMonastery, iJewishShrine, iOrthodoxTemple, iOrthodoxCathedral, 
iOrthodoxMonastery, iOrthodoxShrine, iCatholicChurch, iCatholicCathedral, iCatholicMonastery, iCatholicShrine, iProtestantTemple, iProtestantCathedral, iProtestantMonastery, iProtestantShrine, 
iIslamicTemple, iIslamicCathedral, iIslamicMonastery, iIslamicShrine, iHinduTemple, iHinduCathedral, iHinduMonastery, iHinduShrine, iBuddhistTemple, iBuddhistCathedral, 
iBuddhistMonastery, iBuddhistShrine, iConfucianTemple, iConfucianCathedral, iConfucianMonastery, iConfucianShrine, iTaoistTemple, iTaoistCathedral, iTaoistMonastery, iTaoistShrine, 
iZoroastrianTemple, iZoroastrianCathedral, iZoroastrianMonastery, iZoroastrianShrine, iAcademy, iAdministrativeCenter, iManufactory, iArmoury, iMuseum, iStockExchange, 
iTradingCompanyBuilding, iIberianTradingCompanyBuilding, iNationalMonument, iNationalTheatre, iNationalGallery, iNationalCollege, iMilitaryAcademy, iSecretService, iIronworks, iRedCross, 
iNationalPark, iCentralBank, iSpaceport, iGreatSphinx, iPyramids, iPyramidOfTheSun, iOracle, iGreatWall, iIshtarGate, iTerracottaArmy, iHangingGardens, 
iGreatCothon, iDujiangyan, iApadanaPalace, iColossus, iStatueOfZeus, iGreatMausoleum, iParthenon, iTempleOfArtemis, iGreatLighthouse, iMoaiStatues, 
iFlavianAmphitheatre, iAquaAppia, iAlKhazneh, iTempleOfKukulkan, iMachuPicchu, iGreatLibrary, iFloatingGardens, iGondeshapur, iJetavanaramaya, iNalanda, 
iTheodosianWalls, iHagiaSophia, iBorobudur, iMezquita, iShwedagonPaya, iMountAthos, iIronPillar, iPrambanan, iSalsalBuddha, iCheomseongdae, 
iHimejiCastle, iGrandCanal, iWatPreahPisnulok, iKhajuraho, iSpiralMinaret, iDomeOfTheRock, iHouseOfWisdom, iKrakDesChevaliers, iMonolithicChurch, iUniversityOfSankore, 
iNotreDame, iOldSynagogue, iSaintSophia, iSilverTreeFountain, iSantaMariaDelFiore, iAlamut, iSanMarcoBasilica, iSistineChapel, iPorcelainTower, iTopkapiPalace, 
iKremlin, iSaintThomasChurch, iVijayaStambha, iGurEAmir, iRedFort, iTajMahal, iForbiddenPalace, iVersailles, iBlueMosque, iEscorial, 
iTorreDeBelem, iPotalaPalace, iOxfordUniversity, iHarmandirSahib, iSaintBasilsCathedral, iBourse, iItsukushimaShrine, iImageOfTheWorldSquare, iLouvre, iEmeraldBuddha, 
iShalimarGardens, iTrafalgarSquare, iHermitage, iGuadalupeBasilica, iSaltCathedral, iAmberRoom, iStatueOfLiberty, iBrandenburgGate, iAbbeyMills, iBellRockLighthouse, 
iChapultepecCastle, iEiffelTower, iWestminsterPalace, iTriumphalArch, iMenloPark, iCrystalPalace, iTsukijiFishMarket, iBrooklynBridge, iHollywood, iEmpireStateBuilding, 
iLasLajasSanctuary, iPalaceOfNations, iMoleAntonelliana, iNeuschwanstein, iFrontenac, iWembley, iLubyanka, iCristoRedentor, iMetropolitain, iNobelPrize, 
iGoldenGateBridge, iBletchleyPark, iSagradaFamilia, iCERN, iItaipuDam, iGraceland, iCNTower, iPentagon, iUnitedNations, iCrystalCathedral, 
iMotherlandCalls, iBerlaymont, iWorldTradeCenter, iAtomium, iIronDome, iHarbourOpera, iGreatZimbabwe, iLotusTemple, iGlobalSeedVault, iGardensByTheBay, iBurjKhalifa, 
iHubbleSpaceTelescope, iChannelTunnel, iSkytree, iOrientalPearlTower, iDeltaWorks, iSpaceElevator, iLargeHadronCollider, iITER, iGateOfTheSun, iSerpentMound) = range(iNumBuildings)

iBeginWonders = iGreatSphinx # different from DLL constant because that includes national wonders

iTemple = iJewishTemple #generic
iCathedral = iJewishCathedral #generic
iMonastery = iJewishMonastery #generic
iShrine = iJewishShrine #generic

iFirstWonder = iGreatSphinx

iPlague = iNumBuildings
iNumBuildingsPlague = iNumBuildings+1

#Civics
iNumCivics = 42
(iChiefdom, iDespotism, iMonarchy, iRepublic, iElective, iStateParty, iDemocracy,
iAuthority, iCitizenship, iVassalage, iMeritocracy, iCentralism, iRevolutionism, iConstitution,
iTraditionalism, iSlavery, iManorialism, iCasteSystem, iIndividualism, iTotalitarianism, iEgalitarianism,
iReciprocity, iRedistribution, iMerchantTrade, iRegulatedTrade, iFreeEnterprise, iCentralPlanning, iPublicWelfare,
iAnimism, iDeification, iClergy, iMonasticism, iTheocracy, iTolerance, iSecularism,
iSovereignty, iConquest, iTributaries, iIsolationism, iColonialism, iNationhood, iMultilateralism) = range(iNumCivics)

iNumCivicCategories = 6
(iCivicsGovernment, iCivicsLegitimacy, iCivicsSociety, iCivicsEconomy, iCivicsReligion, iCivicsTerritory) = range(iNumCivicCategories)

#Specialists
iNumSpecialists = 19
(iSpecialistCitizen, iSpecialistPriest, iSpecialistArtist, iSpecialistScientist, iSpecialistMerchant, iSpecialistEngineer, iSpecialistStatesman,
iSpecialistGreatProphet, iSpecialistGreatArtist, iSpecialistGreatScientist, iSpecialistGreatMerchant, iSpecialistGreatEngineer, iSpecialistGreatStatesman, iSpecialistGreatGeneral, iSpecialistGreatSpy, iSpecialistResearchSatellite, iSpecialistCommercialSatellite, iSpecialistMilitarySatellite, iSpecialistSlave) = range(iNumSpecialists)

#Stability Levels
iNumStabilityLevels = 5
(iStabilityCollapsing, iStabilityUnstable, iStabilityShaky, iStabilityStable, iStabilitySolid) = range(iNumStabilityLevels)
StabilityLevelTexts = ["TXT_KEY_STABILITY_COLLAPSING", "TXT_KEY_STABILITY_UNSTABLE", "TXT_KEY_STABILITY_SHAKY", "TXT_KEY_STABILITY_STABLE", "TXT_KEY_STABILITY_SOLID"]

#Stability Types
iNumStabilityTypes = 5
(iStabilityExpansion, iStabilityEconomy, iStabilityDomestic, iStabilityForeign, iStabilityMilitary) = range(iNumStabilityTypes)
StabilityTypesTexts = ["TXT_KEY_STABILITY_CATEGORY_EXPANSION", "TXT_KEY_STABILITY_CATEGORY_ECONOMY", "TXT_KEY_STABILITY_CATEGORY_DOMESTIC", "TXT_KEY_STABILITY_CATEGORY_FOREIGN", "TXT_KEY_STABILITY_CATEGORY_MILITARY"]

#Stability Parameters
iNumStabilityParameters = 23
(iParameterCorePeriphery, iParameterCoreScore, iParameterPeripheryScore, iParameterRecentExpansion, iParameterRazedCities, iParameterIsolationism,	# Expansion
iParameterEconomicGrowth, iParameterTrade, iParameterMercantilism, iParameterCentralPlanning,								# Economy
iParameterHappiness, iParameterCivicCombinations, iParameterCivicsEraTech, iParameterReligion,								# Domestic
iParameterVassals, iParameterDefensivePacts, iParameterRelations, iParameterNationhood, iParameterTheocracy, iParameterMultilateralism,			# Foreign
iParameterWarSuccess, iParameterWarWeariness, iParameterBarbarianLosses) = range(iNumStabilityParameters)						# Military

#Regions
iNumRegions = 38
(rBritain, rIberia, rItaly, rBalkans, rEurope, rScandinavia, rRussia, rAnatolia, rMesopotamia, rArabia, rEgypt, rMaghreb,
rPersia, rIndia, rDeccan, rIndochina, rIndonesia, rChina, rKorea, rJapan, rManchuria, rTibet, rCentralAsia, rSiberia,
rAustralia, rOceania, rEthiopia, rWestAfrica, rSouthAfrica, rCanada, rAlaska, rUnitedStates, rCaribbean, rMesoamerica,
rBrazil, rArgentina, rPeru, rColombia) = range(iNumRegions)

lNewWorld = [rAustralia, rOceania, rCanada, rAlaska, rUnitedStates, rCaribbean, rMesoamerica, rBrazil, rArgentina, rPeru, rColombia]

lEurope = [rBritain, rIberia, rItaly, rBalkans, rEurope, rScandinavia, rRussia]
lMiddleEast = [rAnatolia, rMesopotamia, rArabia, rPersia, rCentralAsia]
lIndia = [rIndia, rDeccan]
lEastAsia = [rIndochina, rIndonesia, rChina, rKorea, rJapan, rManchuria, rTibet]
lNorthAfrica = [rEgypt, rMaghreb]
lSubSaharanAfrica = [rEthiopia, rSouthAfrica, rWestAfrica]
lSouthAmerica = [rCaribbean, rMesoamerica, rBrazil, rArgentina, rPeru, rColombia]
lNorthAmerica = [rCanada, rAlaska, rUnitedStates]
lOceania = [rAustralia, rOceania]

lAfrica = lNorthAfrica + lSubSaharanAfrica
lAsia = lMiddleEast + lIndia + lEastAsia
lAmericas = lNorthAmerica + lSouthAmerica

iArea_Europe = 1000
iArea_MiddleEast = 1001
iArea_India = 1002
iArea_EastAsia = 1003
iArea_Africa = 1004
iArea_SouthAmerica = 1005
iArea_NorthAmerica = 1006

mercRegions = {
	iArea_Europe : set([rBritain, rIberia, rItaly, rBalkans, rEurope, rScandinavia, rRussia]),
	iArea_MiddleEast : set([rAnatolia, rMesopotamia, rArabia, rEgypt, rMaghreb, rPersia, rCentralAsia]),
	iArea_India : set([rIndia, rDeccan]),
	iArea_EastAsia : set([rIndochina, rIndonesia, rChina, rKorea, rJapan, rManchuria, rTibet]),
	iArea_Africa : set([rEgypt, rMaghreb, rEthiopia, rSouthAfrica, rWestAfrica]),
	iArea_SouthAmerica : set([rCaribbean, rMesoamerica, rBrazil, rArgentina, rPeru, rColombia]),
	iArea_NorthAmerica : set([rCanada, rAlaska, rUnitedStates]),
}

#Projects

iNumProjects = 21
(iManhattanProject, iTheInternet, iHumanGenome, iSDI, iGPS, iISS, iBallisticMissile, iFirstSatellite, iManInSpace, iLunarLanding,
iGoldenRecord, iMarsMission, iLunarColony, iInterstellarProbe, iMarsFraming, iMarsPowerSource, iMarsExtractor, iMarsHabitat, iMarsHydroponics, iMarsLaboratory, iMarsControlCenter) = range(iNumProjects)

lMarsBaseComponents = [iMarsFraming, iMarsPowerSource, iMarsExtractor, iMarsHabitat, iMarsHydroponics, iMarsLaboratory, iMarsControlCenter]

#Eras

iNumEras = 7
(iAncient, iClassical, iMedieval, iRenaissance, iIndustrial, iGlobal, iDigital) = range (iNumEras)


#Improvements

iNumImprovements = 30
(iLandWorked, iWaterWorked, iCityRuins, iHut, iFarm, iPaddyField, iFishingBoats, iOceanFishery, iWhalingBoats, iMine, 
iWorkshop, iLumbermill, iWindmill, iWatermill, iPlantation, iSlavePlantation, iQuarry, iPasture, iCamp, iWell, 
iOffshorePlatform, iWinery, iCottage, iHamlet, iVillage, iTown, iFort, iForestPreserve, iMarinePreserve, iSolarCollector) = range(iNumImprovements)

iNumRoutes = 4
(iRouteRoad, iRouteRailroad, iRouteRomanRoad, iRouteHighway) = range(iNumRoutes)

#feature & terrain

iNumFeatures = 10
(iSeaIce, iJungle, iOasis, iFloodPlains, iForest, iMud, iCape, iIslands, iRainforest, iFallout) = range(iNumFeatures)

iGrass = 0
iPlains = 1
iDesert = 2
iTundra = 3
iSnow = 4
iCoast = 5
iOcean = 6
iTerrainPeak = 7
iTerrainHills = 8
iMarsh = 9

#Plague
iImmunity = 20

# Victory
iVictoryPaganism = 10
iVictorySecularism = 11


#leaders

iNumLeaders = 182
(iLeaderBarbarian, iNativeLeader, iIndependentLeader, iAlexanderTheGreat, iAsoka, iAugustus, iBismarck, iBoudica, iBrennus, iCatherine, 
iCharlemagne, iChurchill, iCyrus, iDarius, iDeGaulle, iElizabeth, iFrederick, iGandhi, iGenghisKhan, iSargon, 
iHammurabi, iHannibal, iCleopatra, iHuaynaCapac, iIsabella, iJoao, iJuliusCaesar, iJustinian, iKublaiKhan, iLincoln, 
iLouis, iMansaMusa, iMao, iMehmed, iMontezuma, iNapoleon, iPacal, iPericles, iPeter, iQinShiHuang, 
iRamesses, iRagnar, iRoosevelt, iSaladin, iSittingBull, iStalin, iSuleiman, iSuryavarman, iOdaNobunaga, iVictoria, 
iWangKon, iWashington, iWillemVanOranje, iZaraYaqob, iKammu, iMeiji, iAkbar, iHiram, iMenelik, iGustav, 
iMongkut, iPhilip, iBarbarossa, iCharles, iFrancis, iIvan, iAfonso, iAtaturk, iMaria, iHitler,
iFranco, iAlexanderII, iCavour, iAbbas, iKhomeini, iTaizong, iHongwu, iDharmasetu, iHayamWuruk, iSuharto, 
iShahuji, iNaresuan, iAlpArslan, iBaibars, iNasser, iAlfred, iTrudeau, iChandragupta, iTughluq, iBasil, 
iRahman, iRajendra, iLobsangGyatso, iSobieski, iVatavelli, iMbemba, iHarun, iSongtsen, iCasimir, iYaqub, 
iLorenzo, iSantaAnna, iJuarez, iCardenas, iPedro, iSanMartin, iPeron, iBolivar, iAhoeitu, iKrishnaDevaRaya, 
iMussolini, iSejong, iBhutto, iPilsudski, iWalesa, iGerhardsen, iVargas, iMacDonald, iCastilla, iWilliam,
iGeorge, iKhosrow, iBumin, iTamerlane, iEzana, iChristian, iGustavVasa, iKarl, iCurtin, iMenzies, iMustasim, iKangxi, iCixi, iOduduwa, iEwuare,
iAminatu, iLapuLapu, iKruger, iMandela, iShirazi, iDawud, iBarghash, iTrung, iChieuHoang, iHoChiMinh, iRusvingo, iMutota,
iAnawrahta, iShinSawbu, iBayinnuang, iBohdan, iYaroslav, iIstvan, iKossuth, iAtlatlCauac, iBenGurion, iSaif, iArwa, iBulan, iPiye, iDunama, 
iRobert, iCollins, iWiracocha, iAbaoji, iMalkuHuyustus, iWariCapac, iAshur, iTacaynamo, iAshot, iPulakesi, iRedHorn, iAua, iSacuamanchica, iRurik, iUzbeg, iTezcatlipoca, iKanishka, iModuChanyu, 
iMindaugas, iSuppi, iDeganawida) = range(iNumLeaders)

resurrectionLeaders = {
	iChina : iHongwu,
	iIndia : iShahuji,
	iEgypt : iBaibars,
}

rebirthLeaders = {
	iHarappa : iPulakesi,
	iNorteChico : iTacaynamo,
	iCeltia : iRobert,
	iMaya : iBolivar,
	iPersia : iAbbas,
	iAztecs : iJuarez,
}

tTradingCompanyPlotLists = (
[(128, 35), (129, 36), (130, 38), (130, 39), (130, 33), (131, 34), (131, 36), (131, 38), (131, 39), (131, 40), (132, 33), (132, 34), (132, 37), (133, 36)], #Spain
[(122, 42), (121, 41), (121, 40), (121, 42), (122, 40), (122, 39), (123, 39), (123, 38), (124, 38), (123, 37), (124, 37), (123, 36), (124, 36), (124, 35), (124, 34), (124, 39),  (125, 36), (125, 35), (125, 37), (125, 38), (123, 35), (123, 34)], #France
[(113, 42), (112, 42), (111, 42), (111, 41), (111, 40), (110, 40), (110, 39), (109, 39), (109, 38), (108, 38), (108, 37), (107, 37), (107, 36), (107, 35), (107, 34), (103, 39), (103, 38), (103, 37), (103, 36), (125, 43)], #England
[(62, 31), (70, 24), (79, 17), (83, 20), (96, 40), (96, 39), (104, 34), (108, 30), (108, 31), (120, 30)], #Portugal
[(119, 28), (120, 28), (120, 27), (121, 27), (120, 26), (121, 26), (123, 25), (124, 25), (125, 25), (126, 25), (123, 29), (124, 29), (125, 29), (126, 29), (127, 29), (124, 28), (125, 28), (126, 28), (132, 28), (134, 28), (134, 29)] #Netherlands
)

lSecondaryCivs = [iHarappa, iPolynesia, iTamils, iTibet, iMoors, iPoland, iCongo, iArgentina, iBrazil]

lMongolCivs = [iPersia, iByzantium, iArabia, iArmenia]

(i3000BC, i600AD, i1700AD) = range(3)

# Stability overlay and editor
iNumPlotStabilityTypes = 5
(iCore, iHistorical, iContest, iForeignCore, iAIForbidden) = range(iNumPlotStabilityTypes)
lStabilityColors = ["COLOR_CYAN", "COLOR_GREEN", "COLOR_YELLOW", "COLOR_RED", "COLOR_PLAYER_LIGHT_PURPLE"]
lPresetValues = [3, 20, 90, 200, 500, 700]

iMaxWarValue = 12
lWarMapColors = ["COLOR_RED", "COLOR_PLAYER_ORANGE", "COLOR_YELLOW", "COLOR_GREEN", "COLOR_PLAYER_DARK_GREEN", "COLOR_BLUE"]

lReligionMapColors = ["COLOR_PLAYER_ORANGE", "COLOR_YELLOW", "COLOR_GREEN", "COLOR_CYAN"]
lReligionMapTexts = ["TXT_KEY_CULTURELEVEL_NONE", "TXT_KEY_WB_RELIGIONMAP_MINORITY", "TXT_KEY_WB_RELIGIONMAP_PERIPHERY", "TXT_KEY_WB_RELIGIONMAP_HISTORICAL", "TXT_KEY_WB_RELIGIONMAP_CORE"]

lNetworkEvents = {
	"CHANGE_COMMERCE_PERCENT" :	1200,
}

lCapitalStart = [iAssyria, iChina, iYemen, iBurma, iOttomans]

iNumSpawnTypes = 3
(iForcedSpawn, iNoSpawn, iConditionalSpawn) = range(iNumSpawnTypes)