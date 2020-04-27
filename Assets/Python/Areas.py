from Consts import *				
				
# Peak that change to hills during the game, like Bogota				
lPeakExceptions = [(31, 13), (32, 19), (27, 29), (88, 47), (40, 66)]				
				
def isReborn(iPlayer):				
	return gc.getPlayer(iPlayer).isReborn()			
				
def getOrElse(dDictionary, key, default):				
	if key in dDictionary: return dDictionary[key]			
	return default			
				
def getArea(iPlayer, tRectangle, dExceptions, bReborn=None, dChangedRectangle={}, dChangedExceptions={}):				
	if bReborn is None: bReborn = isReborn(iPlayer)			
	tBL, tTR = tRectangle[iPlayer]			
	lExceptions = getOrElse(dExceptions, iPlayer, [])			
				
	if bReborn:			
		if iPlayer in dChangedRectangle:		
			tBL, tTR = dChangedRectangle[iPlayer]	
			lExceptions = getOrElse(dChangedExceptions, iPlayer, [])	
				
	left, bottom = tBL			
	right, top = tTR			
	return [(x, y) for x in range(left, right+1) for y in range(bottom, top+1) if (x, y) not in lExceptions]			
				
def getCapital(iPlayer, bReborn=None):				
	if bReborn is None: bReborn = isReborn(iPlayer)			
	if bReborn and iPlayer in dChangedCapitals:			
		return dChangedCapitals[iPlayer]		
	return tCapitals[iPlayer]			
				
def getRespawnCapital(iPlayer, bReborn=None):				
	if iPlayer in dRespawnCapitals: return dRespawnCapitals[iPlayer]			
	return getCapital(iPlayer, bReborn)			
				
def getNewCapital(iPlayer, bReborn=None):				
	if iPlayer in dNewCapitals: return dNewCapitals[iPlayer]			
	return getRespawnCapital(iPlayer, bReborn)			
				
def getBirthArea(iPlayer):				
	return getArea(iPlayer, tBirthArea, dBirthAreaExceptions)			
				
def getBirthRectangle(iPlayer, bExtended = None):				
	if bExtended is None: bExtended = isExtendedBirth(iPlayer)			
	if iPlayer in dChangedBirthArea and bExtended:			
		return dChangedBirthArea[iPlayer]		
	return tBirthArea[iPlayer]			
				
def getBirthExceptions(iPlayer):				
	if iPlayer in dBirthAreaExceptions: return dBirthAreaExceptions[iPlayer]			
	return []			
				
def getCoreArea(iPlayer, bReborn=None):				
	return getArea(iPlayer, tCoreArea, dCoreAreaExceptions, bReborn, dChangedCoreArea, dChangedCoreAreaExceptions)			
				
def getNormalArea(iPlayer, bReborn=None):				
	return getArea(iPlayer, tNormalArea, dNormalAreaExceptions, bReborn, dChangedNormalArea, dChangedNormalAreaExceptions)			
				
def getBroaderArea(iPlayer, bReborn=None):				
	return getArea(iPlayer, tBroaderArea, {}, dChangedBroaderArea)			
				
def getRespawnArea(iPlayer):				
	if iPlayer in dRespawnArea: return getArea(iPlayer, dRespawnArea, {})			
	return getNormalArea(iPlayer)			
				
def getRebirthArea(iPlayer):				
	if iPlayer in dRebirthArea: return getArea(iPlayer, dRebirthArea, dRebirthAreaExceptions)			
	return getBirthArea(iPlayer)			
				
def updateCore(iPlayer):				
	lCore = getCoreArea(iPlayer)			
	for x in range(iWorldX):			
		for y in range(iWorldY):		
			plot = gc.getMap().plot(x, y)	
			if plot.isWater() or (plot.isPeak() and (x, y) not in lPeakExceptions): continue	
			plot.setCore(iPlayer, (x, y) in lCore)	
				
def isForeignCore(iPlayer, tPlot):				
	x, y = tPlot			
	plot = gc.getMap().plot(x, y)			
	for iLoopPlayer in range(iNumPlayers):			
		if iLoopPlayer == iPlayer: continue		
		if plot.isCore(iLoopPlayer):		
			return True	
	return False			
				
def isExtendedBirth(iPlayer):				
	if gc.getGame().getActivePlayer() == iPlayer: return False			
				
	# add special conditions for extended AI flip zones here			
	if iPlayer == iOttomans and pByzantium.isAlive(): return False			
				
	return True			
				
def init():				
	for iPlayer in range(iNumPlayers):			
		updateCore(iPlayer)		
				
### Capitals ###				
				
tCapitals = (				
(79, 43), # Memphis/Cairo				
(89, 47), # Babylon				
(102, 47), # Harappa
(28, 24), # Caral				
(78, 37), # Kerma				
(88, 50), # Assyria				
(124, 52), # Chang'an				
(76, 51), # Athens				
(110, 44), # Pataliputra				
(84, 47), # Sur
(67, 60), # Hallstatt				
(3, 20), # Tonga				
(94, 45), # Persepolis				
(68, 53), # Rome				
(22, 41), # Tikal				
(106, 33), # Thanjavur				
(84, 35), # Aksum				
(121, 42), # Co Loa (Hanoi)				
(17, 43), # Tenotihuacan (Tollan)				
(89, 53), # Armenia				
(131, 54), # Seoul
(34, 22), # Tiwanaku				
(79, 55), # Constantinople
(31, 24), # Cerro Pátapo				
(137, 53), # Kyoto				
(68, 67), # Oslo				
(104, 58), # Orduqent				
(86, 39), # Mecca				
(113, 48), # Lhasa				
(120, 27), # Palembang				
(117, 42), # Pagan (Ava, Mandalay)				
(90, 58), # Balanjar				
(72, 34), # Njimi				
(57, 49), # Cordoba				
(58, 52), # Madrid				
(61, 60), # Paris				
(96, 40), # Muscat				
(128, 61), # ChangchunKhitay				
(122, 36), # Angkor				
(88, 35), # Sana'a				
(58, 64), # London				
(65, 62), # Koln				
(81, 62), # Kiev				
(74, 59), # Buda				
(130, 38), # Tondo (Manila)				
(83, 24), # Kilwa				
(79, 43), # Cairo				
(58, 35), # Djenne				
(74, 62), # Krakow				
(79, 18), # Great Zimbabwe				
(54, 50), # Lisboa # (54, 51)				
(31, 24), # Cuzco				
(66, 57), # Mailand				
(66, 32), # Benin City				
(118, 62), # Karakorum				
(17, 43), # Tenochtitlan				
(105, 46), # Delhi				
(82, 53), # Sogut/Ankara				
(85, 65), # Moskow				
(119, 36), # Ayutthaya				
(71, 25), # Mbanza Kongo				
(73, 71), # Stockholm				
(62, 64), # Amsterdam				
(128, 61), # Changchun				
(69, 64), # Berlin				
(29, 54), # Washington				
(38, 13), # Buenos Aires				
(46, 21), # Rio de Janeiro				
(142, 12),# Sydney				
(78, 15), # Johannesburg				
(31, 61), # Montreal # Ottawa				
(84, 45), # Jerusalem				
)				
				
dChangedCapitals = {				
iNubia : (81, 35),	# Sennar			
iChina : (124, 56),	# Beijing			
iIndia : (105, 46),	# Delhi			
iCarthage : (67, 48),	# Carthage			
iPersia : (93, 48),	# Esfahan (Iran)			
iNorteChico : (27, 28),	# Chimu			
iCeltia : (57, 69),	# Scottish			
iMaya : (29, 34),	# Bogota (Colombia)				
iHarappa : (104, 37),	# Chalukya	
iTamils : (105, 36),	# Vijayanagara			
iChad : (71, 34),     #N'Djamena				
iKhmer : (121, 41),	# Hanoi			
iHolyRome : (71, 59),	# Vienna			
}				
				
# new capital locations if changed during the game				
dNewCapitals = {				
iJapan : (140, 54),	# Tokyo			
iHolyRome : (71, 59),	# Vienna			
iItaly : (68, 53),	# Rome			
iMongolia : (125, 56),	# Khanbaliq			
iOttomans : (79, 55),	# Istanbul			
iManchuria : (125, 56),	# Beijing			
}				
				
# new capital locations on respawn				
dRespawnCapitals = {				
iEgypt : (79, 43),	# Cairo			
iNubia : (81, 35),	# Dongola			
iChina :  (124, 56),	# Beijing			
iIndia : (105, 46),	# Delhi			
iPersia : (93, 48),	# Esfahan			
iEthiopia : (83, 32),	# Addis Ababa # (84, 32)?			
iKazakh : (105, 58), # Almaty				
iJapan : (140, 54),	# Tokyo			
iTurks : (100, 54), # Samarkand				
iIndonesia : (123, 25),	# Jakarta			
iChad : (74, 34),	#Ngazargamu			
iMoors : (57, 44),	# Marrakesh			
iHolyRome : (71, 59),	# Vienna			
iInca : (28, 25),	# Lima			
iItaly : (68, 53),	# Rome			
iMughals : (100, 42),	# Karachi			
iOttomans : (79, 55),	# Istanbul			
}				
				
### Birth Area ###				
				
tBirthArea = (				
((77, 37),	(82, 45)),	# Egypt		
((88, 44),	(91, 48)),	# Babylonia		
((99, 45),	(103, 49)),	# Harappa
((28, 24), (28, 24)), 	# Norte Chico		
((77, 36), 	(80, 38)), 	# Nubia		
((87, 49),	(89, 52)),	# Assyria		
((119, 49),	(129, 56)),	# China		
((74, 48),	(80, 55)),	# Greece		
((101, 42),	(114, 48)),	# India		
((83, 47),	(85, 49)),	# Carthage
((62, 58),	(67, 61)),	# Celtia		
((2, 19),	(6, 24)),	# Polynesia		
((91, 43),	(98, 52)),	# Persia		
((64, 50),	(72, 57)),	# Rome		
((20, 41),	(23, 44)),	# Maya		
((105, 29),	(109, 36)),	# Tamils		
((82, 32),	(86, 36)),	# Ethiopia		
((120, 40),	(122, 43)),	# Vietnam		
((16, 42),	(18, 47)), 	# Teotihuacan		
((87, 53),	(91, 55)),	# Armenia		
((129, 52),	(133, 59)),	# Korea
((32, 17), (34, 22)),	# Tiwanaku		
((74, 44),	(86, 57)),	# Byzantium
((28, 22),	(32, 25)),	# Wari		
((134, 49),	(140, 59)),	# Japan		
((65, 66),	(70, 76)),	# Vikings		
((95, 52),	(113, 60)),	# Turkestan		
((77, 35),	(90, 50)),	# Arabia		
((107, 47),	(115, 52)),	# Tibet		
((115, 24),	(128, 33)),	# Indonesia		
((116, 38),	(118, 43)),	# Burma		
((86, 58),	(92, 61)),	# Khazars		
((71, 33), 	(75, 36)),	# Chad		
((56, 43),	(59, 51)),	# Moors		
((54, 51),	(59, 54)),	# Spain		
((56, 55),	(64, 61)),	# France		
((94, 37),	(96, 41)),	# Oman		
((125, 58),	(132, 65)),	# Khitan		
((118, 34),	(123, 38)),	# Khmer		
((88, 35),	(90, 36)),	# Yemen		
((55, 61),	(59, 68)),	# England		
((64, 59),	(71, 66)),	# Holy Rome		
((79, 59),	(83, 62)),	# Kievan Rus		
((73, 57),	(77, 59)),	# Hungary		
((129, 36),	(131, 40)),	# Philippines		
((82, 21),	(84, 27)),	# Swahili		
((77, 39),	(82, 45)),	# Mamluks		
((54, 31),	(65, 39)),	# Mali		
((73, 60),	(79, 67)),	# Poland		
((75, 18),	(79, 20)),	# Zimbabwe		
((48, 49),	(55, 52)),	# Portugal		
((28, 23),	(33, 25)),	# Inca		
((65, 55),	(71, 58)),	# Italy		
((62, 31),	(69, 33)),	# Nigeria		
((111, 53),	(131, 65)),	# Mongolia		
((13, 41),	(19, 47)),	# Aztecs		
((99, 43),	(106, 50)),	# Mughals		
((79, 51),	(87, 55)),	# Ottomans		
((82, 62),	(92, 69)),	# Russia		
((118, 34),	(120, 40)),	# Thailand		
((69, 24),	(74, 27)),	# Congo		
((71, 68),	(77, 75)),	# Sweden		
((61, 62),	(64, 66)),	# Netherlands		
((125, 58),	(132, 65)),	# Manchuria		
((65, 59),	(76, 66)),	# Germany		
((25, 50),	(33, 59)),	# America		
((35, 3),	(39, 17)),	# Argentina		
((40, 16),	(49, 32)),	# Brazil		
((137, 9),	(143, 19)),	# Australia		
((76, 11),	(81, 16)),	# Boer		
((18, 59),	(37, 71)),	# Canada		
((83, 44), 	(85, 46)), 	# Israel		
)				
				
dChangedBirthArea = {				
#iCarthage : ((63, 45), (69, 48)),				
iPersia :	((80, 43), 	(98, 55)), 	# includes Assyria and Anatolia	
iArabia :	((74, 35),	(90, 50)),	# Arabia	
iSpain : 	((54, 51), 	(61, 54)), 	# includes Catalonia	
iItaly :	((65, 53),	(71, 58)),	# includes Rome
iMongolia :   ((105, 53),(131, 65)),	# Mongolia			
iInca :   ((27, 21),(35, 26)),	# Inca			
}				
				
dBirthAreaExceptions = {				
iBabylonia : [(91, 47), (91, 48)],				
iHarappa : [(99, 49), (102, 45), (103, 45)],				
iGreece : [(74, 55), (75, 55), (76, 55), (77, 55)],				
iIndia : [(110, 48), (111, 48), (112, 47), (112, 48), (113, 47), (113, 48), (114, 47), (114, 48)],				
iPersia : [(82, 48), (83, 49), (84, 46), (84, 47), (85, 46), (85, 47), (85, 48), (85, 49), (85, 50), (86, 47), (86, 48), (86, 49), (89, 47)],								
iRome : [(72, 56), (72, 57)],				
iArabia : [(74, 50), (75, 49), (75, 50), (77, 48), (78, 35), (78, 36), (78, 37), (78, 38), (78, 48), (78, 49), (78, 50), (79, 35), (79, 36), (79, 37), (79, 38), (79, 48), (79, 49), (79, 50), (80, 35), (80, 36), (80, 37), (80, 38), (80, 48), (80, 49), (80, 50), (81, 35), (81, 36), (81, 37), (81, 38), (81, 48), (81, 49), (81, 50), (82, 35), (82, 36), (82, 37), (82, 38), (82, 48), (82, 49), (82, 50), (83, 35), (83, 36), (83, 37), (83, 38), (83, 49), (83, 50), (84, 35), (84, 36), (84, 37), (84, 38), (84, 49), (84, 50), (85, 35), (85, 36), (85, 37), (85, 49), (85, 50), (86, 35), (86, 49), (86, 50)],				
iTibet : [(107, 47), (108, 47)],				
iSpain : [(54, 51), (54, 52), (55, 51), (55, 52)],				
iFrance : [(56, 61), (57, 61), (58, 61)],				
iEngland : [(58, 61), (59, 61)],				
iHolyRome : [(63, 58), (63, 59), (63, 60), (63, 61), (63, 62), (64, 58), (64, 59), (64, 60), (64, 61), (64, 62), (65, 58), (65, 59), (72, 63), (72, 64), (72, 65), (73, 62), (73, 63), (73, 64), (73, 65)],				
iPoland : [(73, 60), (73, 61)],				
iItaly : [(70, 58), (71, 57), (71, 58)],				
iMongolia : [(120, 53), (121, 53), (121, 54), (122, 53), (122, 54), (123, 53), (123, 54), (123, 55), (123, 56), (124, 53), (124, 54), (124, 55), (124, 56), (125, 53), (125, 54), (125, 55), (125, 56), (126, 53), (126, 54), (126, 55), (126, 56), (127, 53), (127, 54), (127, 55), (127, 56), (128, 53), (128, 54), (128, 55), (128, 56), (129, 53), (129, 54), (129, 55), (129, 56), (130, 53), (130, 54), (130, 55), (130, 56), (130, 57), (131, 53), (131, 54), (131, 55), (131, 56), (131, 57), (131, 58)],				
iOttomans : [(79, 54), (79, 55), (80, 54), (80, 55), (81, 55), (82, 55)],				
iNetherlands : [(61, 62), (64, 62), (64, 63)],				
iGermany : [(69, 59), (69, 60), (69, 61), (69, 62), (70, 59), (70, 60), (70, 61), (70, 62), (71, 59), (71, 60), (71, 61), (71, 62), (72, 59), (72, 60), (72, 61), (72, 62), (73, 59), (73, 60), (73, 61), (73, 62), (74, 59), (74, 60), (74, 61), (74, 62), (74, 63), (74, 64), (75, 59), (75, 60), (75, 61), (75, 62), (75, 63), (75, 64), (76, 59), (76, 60), (76, 61), (76, 62), (76, 63), (76, 64)],				
iAmerica : [(25, 59), (26, 59), (27, 59), (28, 59), (29, 59)],				
iBrazil : [(36, 15), (36, 16)],				
iCanada : [(18, 59), (18, 60), (18, 61), (19, 59), (19, 60), (19, 61), (20, 59), (20, 60), (20, 61), (21, 59), (21, 60), (21, 61), (22, 59), (22, 60), (23, 59), (23, 60), (24, 59), (24, 60), (30, 59), (31, 59), (32, 59), (33, 59), (33, 60), (34, 59), (34, 60)],				
}				
				
### Core Area ###				
				
tCoreArea = (				
((77, 39),	(80, 45)),	# Egypt		
((88, 44),	(91, 48)),	# Babylonia		
((99, 45),	(103, 49)),	# Harappa
((28, 24), (28, 24)), 	# Norte Chico		
((77, 35),	(81, 37)),	# Nubia		
((86, 48),	(89, 52)),	# Assyria		
((120, 49),	(129, 56)),	# China		
((74, 48),	(80, 55)),	# Greece		
((105, 42),	(113, 47)),	# India		
((84, 46),	(86, 50)),	# Phoenicia
((65, 58),	(71, 61)),	# Celtia		
((3, 20),	(5, 23)),	# Polynesia		
((91, 43),	(97, 52)),	# Persia		
((64, 48),	(73, 57)),	# Rome		
((20, 41),	(23, 44)),	# Maya		
((105, 29),	(109, 36)),	# Tamils		
((82, 32),	(86, 36)),	# Ethiopia		
((120, 39),	(123, 43)),	# Vietnam		
((16, 42),	(18, 44)),	# Teotihuacan		
((87, 53),	(91, 55)),	# Armenia			
((130, 52),	(133, 58)),	# Korea
((32, 17), (34, 22)),	# Tiwanaku		
((74, 49),	(84, 55)),	# Byzantium
((28, 22),	(32, 25)),	# Wari		
((135, 52),	(140, 55)),	# Japan		
((66, 67),	(72, 73)),	# Vikings		
((96, 52),	(113, 61)),	# Turks		
((84, 39),	(87, 48)),	# Arabia		
((107, 47),	(115, 52)),	# Tibet		
((115, 24),	(128, 31)),	# Indonesia		
((115, 38),	(118, 43)),	# Burma		
((86, 58),	(92, 60)),	# Khazars		
((70, 34), 	(74, 39)),    # Chad			
((56, 43),	(59, 50)),	# Moors		
((54, 51),	(59, 54)),	# Spain		
((56, 55),	(64, 62)),	# France		
((93, 37),	(96, 41)),	# Oman		
((125, 56),	(129, 63)),	# Khitan		
((120, 33),	(124, 37)),	# Khmer		
((87, 34),	(92, 37)),	# Yemen		
((55, 62),	(59, 71)),	# England		
((64, 58),	(72, 62)),	# Holy Rome		
((79, 60),	(83, 62)),	# Kievan Rus		
((71, 56),	(76, 59)),	# Hungary		
((128, 35),	(133, 40)),	# Philippines		
((82, 18),	(85, 25)),	# Swahili		
((77, 39),	(81, 45)),	# Mamluks		
((57, 34),	(65, 39)),	# Mali		
((73, 61),	(77, 65)),	# Poland		
((76, 17),	(79, 20)),	# Zimbabwe		
((48, 49),	(55, 52)),	# Portugal		
((28, 22),	(32, 25)),	# Inca		
((65, 55),	(70, 57)),	# Italy		
((65, 31),	(70, 35)),	# Nigeria		
((113, 56),	(126, 63)),	# Mongolia		
((14, 41),	(19, 44)),	# Aztecs		
((99, 44),	(106, 50)),	# Mughals		
((79, 51),	(85, 55)),	# Ottomans		
((80, 60),	(89, 69)),	# Russia		
((118, 35),	(120, 40)),	# Thailand		
((69, 24),	(74, 27)),	# Congo		
((69, 68),	(75, 75)),	# Sweden		
((62, 63),	(64, 65)),	# Netherlands		
((125, 56),	(131, 65)),	# Manchuria		
((65, 59),	(75, 66)),	# Germany		
((22, 53),	(34, 60)),	# America		
((35, 9),	(39, 17)),	# Argentina		
((41, 19),	(48, 27)),	# Brazil		
((137, 9),	(143, 20)),	# Australia		
((75, 11),	(81, 16)),	# Boer		
((26, 59),	(37, 63)),	# Canada		
((83, 44), 	(84, 47)), 	# Israel		
)				
				
dChangedCoreArea = {			
iNorteChico :	((26, 26),	(27, 32)),	# Chimu			
iHarappa :	((103, 35),	(105, 40)),	# Chalukya				
iChina : ((119, 47),	(129, 56)),			
iGreece :	((75, 49),	(79, 52)),		
iIndia :	((103, 37),	(106, 41)),		
iPhoenicia : ((62, 45),	(69, 48)),	
iCeltia:	((52, 60), (57, 71)), # Ireland, Scotland, Wales and Bretagne
iPersia : ((89, 43),	(97, 54)),			
iMaya :	((26, 30),	(35, 38)),	# Colombia	
iByzantium :	((79, 54),	(81, 56)),		
iJapan : ((134, 49),	(140, 59)),			
iTurks : ((91, 43),	(97, 52)),			
iArabia :	((83, 44),	(91, 48)),		
iKazakh :	((99, 58), (107, 62)),			
iMoors : ((56, 43),	(65, 48)),			
iSpain : ((54, 48),	(62, 54)),			
iKhmer : ((120, 34),	(124, 43)),			
iHolyRome : ((69, 58),	(75, 62)),			
iItaly : ((65, 48),	(72, 57)),			
iMongolia :	((113, 55),	(128, 63)),	# Mongolia	
iAztecs :	((14, 41),	(21, 47)),	# Mexico	
#iMughals :	((99, 44),	(108, 50)),		
iOttomans :	((78, 50),	(87, 55)),				
iGermany :	((64, 59),	(74, 66)),		
}				
				
dCoreAreaExceptions = {				
iBabylonia : [(91, 47), (91, 48)],				
iHarappa : [(99, 49), (102, 45), (103, 45)],				
iChina : [(120, 49), (120, 50), (120, 54), (120, 56), (121, 49), (121, 55), (121, 56), (122, 55), (122, 56), (128, 56)],				
iGreece : [(74, 55), (75, 55), (76, 55)],				
iIndia : [(105, 42), (106, 42), (107, 42), (112, 47), (113, 47)],				
iPersia : [(96, 52), (97, 52)],				
iRome : [(64, 48), (65, 48), (66, 48), (67, 48), (72, 57), (73, 56), (73, 57)],				
iKorea : [(130, 58)],				
iByzantium : [(74, 54), (74, 55), (75, 55), (76, 55)],				
iTurks : [(96, 61), (111, 52), (112, 53), (113, 54)],				
iTibet : [(107, 47), (108, 47)],				
iIndonesia : [(119, 31), (120, 30), (120, 31), (123, 30), (124, 30), (125, 31), (127, 30), (127, 31)],				
iMoors : [(59, 43)],				
iSpain : [(54, 51), (54, 52), (55, 51), (55, 52)],				
iFrance : [(56, 62), (57, 62), (58, 62), (62, 62), (63, 62), (64, 60), (64, 61), (64, 62)],				
iHolyRome : [(64, 58), (64, 59), (72, 62)],
iHungary : [(71, 59), (71, 58), (73, 56), (74, 56), (75, 56), (76, 56)],				
iRussia : [(87, 69), (88, 68), (88, 69), (89, 68), (89, 69)],				
iPoland : [(72, 60), (72, 61), (72, 62)],				
iMongolia : [(123, 56), (123, 63), (124, 56), (124, 63), (125, 56), (125, 62), (126, 56), (126, 62), (126, 63)],				
iOttomans : [(79, 55), (84, 51), (85, 51)],
iSweden : [(69, 75)],				
iNetherlands : [(64, 62), (64, 63)],
iManchuria : [(130, 56), (130, 57), (131, 56), (131, 57)],				
iGermany : [(65, 59), (65, 60), (65, 64), (65, 65), (69, 61), (69, 62), (70, 59), (70, 60), (70, 61), (70, 62), (71, 59), (71, 60), (71, 61), (71, 62), (72, 59), (72, 60), (72, 61), (72, 62), (73, 59), (73, 60), (73, 61), (73, 62), (74, 59), (74, 61), (74, 62), (74, 63), (74, 64), (75, 59), (75, 60), (75, 61), (75, 62), (75, 63), (75, 64)],				
iAmerica : [(22, 53), (22, 54), (22, 55), (22, 56), (22, 59), (22, 60), (23, 53), (23, 54), (23, 55), (23, 60), (24, 53), (24, 54), (24, 60), (25, 53), (26, 59), (27, 59), (27, 60), (28, 60), (29, 60), (30, 60), (31, 60), (32, 60)],				
iCanada : [(26, 63), (27, 63), (28, 63), (29, 63), (30, 59), (31, 59), (32, 59), (33, 59), (33, 60), (34, 60)],				
}				
				
dChangedCoreAreaExceptions = {				
iChina : [(119, 54), (119, 55), (119, 56), (120, 54), (120, 56), (121, 55), (121, 56), (122, 55), (122, 56), (128, 56)],				
iIndia : [(105, 37), (106, 37), (106, 38)],				
iCeltia : [(57, 68), (57, 67), (57, 66), (57, 65), (57, 64), (57, 63)],				
iPersia : [(89, 43), (89, 44), (89, 45), (89, 46), (89, 47), (89, 48), (89, 49), (89, 50), (89, 54), (90, 43), (90, 44), (90, 45), (90, 46), (90, 47), (90, 48), (94, 53), (94, 54), (95, 53), (95, 54), (96, 51), (96, 52), (96, 53), (96, 54), (97, 51), (97, 52), (97, 53), (97, 54)],				
iMaya : [(31, 30), (32, 30), (33, 30), (34, 30), (35, 30), (32, 31), (33, 31), (34, 31), (35, 31), (32, 32), (33, 32), (34, 32), (35, 32), (32, 33), (33, 33), (34, 33)], # Colombia				
iTurks : [(96, 52), (97, 52)],				
iArabia : [(82, 34), (91, 47)],				
iKhmer : [(120, 36), (120, 37), (120, 38), (120, 39), (120, 40), (121, 35), (121, 37), (121, 38), (121, 39), (122, 36), (122, 37), (122, 38), (124, 41), (124, 43)],				
iMoors : [(57, 48)],				
iSpain : [(54, 50), (54, 51), (54, 52), (55, 49), (55, 50), (55, 51), (55, 52), (62, 48)],				
iHolyRome : [(73, 61), (73, 62), (74, 60), (74, 61), (74, 62), (75, 61), (75, 62)],				
iItaly : [(65, 48), (66, 48), (67, 48), (71, 57), (72, 55), (72, 56), (72, 57)],				
#iMughals : [(99, 40), (100, 40), (101, 40), (99, 49), (100, 50), (107, 50), (108, 50)],				
iOttomans : [(86, 50), (87, 50), (87, 51)],				
iGermany : [(64, 59), (64, 64), (64, 65), (69, 59), (69, 60), (69, 61), (69, 62), (70, 59), (70, 60), (70, 61), (70, 62), (71, 59), (71, 60), (71, 61), (71, 62), (71, 63), (71, 64), (71, 65), (72, 59), (72, 60), (72, 61), (72, 62), (72, 63), (72, 64), (72, 65), (73, 59), (73, 61), (73, 62), (73, 63), (73, 64), (73, 65), (74, 59), (74, 61), (74, 62), (74, 63), (74, 64), (74, 65)],				
}				
				
				
### Normal Area ###				
				
tNormalArea = (				
((75, 37),	(82, 45)),	# Egypt		
((87, 44),	(91, 51)),	# Babylonia		
((98, 42),	(103, 50)), # Harappa	
((28, 24), (28, 24)), 	# Norte Chico		
((76, 31), 	(79, 37)), 	# Nubia		
((86, 48),	(89, 52)),	# Assyria		
((117, 43),	(130, 59)),	# China		
((75, 49),	(79, 54)),	# Greece		
((104, 42),	(114, 48)),	# India		
((83, 46),	(86, 49)),	# Carthage
((52, 64),	(58, 71)), # Ireland			
((3, 20),	(11, 24)),	# Polynesia		
((91, 43),	(100, 54)),	# Persia		
((64, 49),	(74, 59)),	# Rome		
((20, 37),	(25, 44)),	# Maya		
((105, 30),	(109, 38)),	# Tamils		
((81, 29),	(90, 36)),	# Ethiopia		
((120, 39), 	(123, 43)), 	# Vietnam		
((15, 42), 	(18, 45)), 	# Teotihuacan		
((87, 53),	(91, 55)),	# Armenia			
((130, 53),	(132, 57)),	# Korea
((32, 17), (34, 22)),	# Tiwanaku		
((75, 49),	(84, 56)),	# Byzantium
((28, 22),	(32, 25)),	# Wari		
((133, 49),	(139, 62)),	# Japan		
((65, 67),	(79, 77)),	# Vikings		
((94, 52),	(104, 58)),	# Turks		
((84, 35),	(96, 46)),	# Arabia		
((108, 48),	(115, 54)),	# Tibet		
((116, 25),	(136, 33)),	# Indonesia		
((115, 38),	(118, 43)),	# Burma		
((86, 58),	(92, 60)),	# Khazars		
((70, 34), 	(74, 39)),    # Chad				
((57, 43),	(68, 51)),	# Moors		
((55, 48),	(64, 54)),	# Spain		
((57, 55),	(65, 61)),	# France		
((93, 37),	(96, 41)),	# Oman		
((125, 56),	(131, 65)),	# Khitan		
((120, 33),	(124, 37)),	# Khmer		
((87, 34),	(92, 37)),	# Yemen		
((56, 62),	(60, 70)),	# England		
((65, 58),	(73, 62)),	# HolyRome		
((79, 59),	(83, 62)),	# Kievan Rus		
((73, 57),	(77, 59)),	# Hungary		
((128, 35),	(133, 40)),	# Philippines		
((82, 18),	(85, 25)),	# Swahili		
((74, 39),	(81, 45)),	# Mamluks		
((54, 31),	(68, 38)),	# Mali		
((73, 60),	(82, 66)),	# Poland		
((75, 17),	(79, 22)),	# Zimbabwe		
((49, 49),	(56, 52)),	# Portugal		
((26, 13),	(34, 34)),	# Inca		
((66, 49),	(73, 57)),	# Italy		
((65, 31),	(70, 35)),	# Nigeria		
((113, 56),	(129, 66)),	# Mongolia		
((12, 41),	(21, 47)),	# Aztecs		
((99, 44),	(108, 50)),	# Mughals		
((79, 49),	(91, 59)),	# Ottomans		
((80, 58),	(100, 77)),	# Russia		
((118, 34),	(122, 41)),	# Thailand		
((69, 24),	(74, 27)),	# Congo		
((70, 68), 	(77, 75)), 	# Sweden		
((63, 62),	(65, 65)),	# Netherlands		
((125, 56),	(131, 65)),	# Manchuria		
((65, 58),	(75, 66)),	# Germany		
((8, 49),	(33, 59)),	# America		
((34, 3),	(39, 17)),	# Argentina		
((36, 16),	(49, 36)),	# Brazil		
((137, 9),	(143, 20)),	# Australia		
((75, 11),	(81, 16)),	# Boer		
((26, 59),	(37, 63)),	# Canada		
((83, 44), 	(84, 47)), 	# Israel		
)				
				
dChangedNormalArea = {	
iNorteChico : 	((26, 26),	(27, 32)),	# Chimu		
iHarappa :	((103, 35),	(105, 40)),	# Chalukya					
iIndia : 	((96, 42),	(97, 42)),		
iCarthage :	((63, 45),	(70, 48)),		
iMaya : 	((26, 30),	(35, 38)),	# Colombia		
iCeltia : 	((53, 65),	(57, 71)),	# Scottish	
iNorteChico : 	((26, 26),	(27, 32)),	# Chimu	
iArabia : 	((84, 35),	(91, 48)),		
iKhmer : 	((121, 35),	(124, 43)),		
iHolyRome : ((69, 56),	(78, 62)),			
}				
				
dNormalAreaExceptions = {				
iBabylonia : [(90, 50), (90, 51), (91, 50), (91, 51)],				
iHarappa : [(98, 47), (98, 48), (99, 49), (102, 42), (102, 43), (102, 44), (103, 42), (103, 43), (103, 44), (103, 45)],				
iChina : [(117, 43), (117, 44), (117, 45), (118, 43), (119, 43), (120, 43), (121, 43), (122, 43), (123, 43), (130, 55), (130, 56), (130, 57), (130, 58), (130, 59), (117, 59), (118, 59), (119, 59), (120, 59)],				
iGreece : [(75, 54)],				
iIndia : [(105, 42), (106, 42), (107, 42), (112, 47), (113, 47)],				
iPolynesia : [(10, 24)],					
iCeltia : [(56, 65), (57, 65), (57, 66), (57, 67)],			
iPersia : [(91, 53), (91, 54), (99, 43), (99, 44), (99, 45), (99, 46), (100, 43), (100, 44), (100, 45), (100, 46), (100, 47), (100, 48)],				
iRome : [(64, 51), (64, 57), (74, 57)],				
iEthiopia : [(81, 34), (81, 35), (81, 36), (88, 35), (88, 36), (89, 35), (90, 36)],				
iByzantium : [(83, 49), (75, 55), (76, 55), (75, 56), (76, 56), (77, 56), (78, 56)],				
iJapan : [(133, 60), (134, 60), (133, 61), (134, 61), (133, 62), (134, 62)],				
iVikings : [(75, 67), (77, 67), (78, 67), (77, 68), (78, 68), (79, 68)],				
iArabia : [(84, 35), (84, 36), (84, 37), (85, 35), (88, 45), (88, 46), (89, 45), (89, 46), (90, 44), (90, 45), (90, 46), (91, 45), (91, 46), (92, 45), (92, 46), (93, 44), (93, 45), (94, 43), (94, 44), (94, 45), (94, 46), (95, 43), (95, 45), (95, 46), (96, 43), (96, 44), (96, 45), (96, 46)],iSpain : [(49, 44), (49, 43), (49, 42), (49, 41)],				
iTibet : [(107, 47), (108, 47), (107, 53), (108, 53), (107, 54), (108, 54), (109, 54), (110, 54)],				
iIndonesia : [(131, 33)],				
iMoors : [(64, 51), (67, 51)],				
iSpain : [(63, 48), (64, 48)],				
iFrance : [(65, 60), (65, 61)],				
iKhmer:	[(121, 41), (122, 40), (123, 39)],			
iHolyRome : [(65, 58), (65, 59), (73, 62)],				
iRussia : [(80, 58), (80, 59), (93, 58), (93, 60), (93, 61), (94, 58), (94, 59), (94, 60), (94, 61), (94, 77), (95, 58), (95, 60), (95, 61), (95, 76), (95, 77), (96, 60), (96, 61), (96, 76), (97, 60), (97, 61), (97, 62), (98, 58), (98, 59), (98, 60), (98, 61), (98, 62), (99, 58), (99, 59), (99, 60), (99, 61), (99, 62), (99, 63), (100, 58), (100, 59), (100, 60), (100, 61), (100, 62), (100, 63), (100, 64), (100, 65)],				
iPoland : [(73, 60), (73, 61), (75, 60), (81, 66), (82, 66)],				
iInca : [(28, 29), (30, 27), (30, 28), (30, 29), (30, 30), (30, 31), (31, 27), (31, 28), (31, 29), (31, 30), (31, 31), (31, 32), (31, 33), (32, 25), (32, 27), (32, 28), (32, 29), (32, 30), (32, 31), (32, 32), (32, 33), (32, 34), (33, 26), (33, 27), (33, 28), (33, 29), (33, 30), (33, 31), (33, 32), (33, 33), (33, 34), (34, 25), (34, 26), (34, 27), (34, 28), (34, 29), (34, 30), (34, 31), (34, 32), (34, 33)],				
iItaly : [(72, 56), (72, 57), (73, 55), (73, 56), (73, 57)],				
iMongolia : [(113, 65), (113, 66), (114, 66), (118, 56), (119, 56), (119, 57), (120, 56), (120, 57), (120, 58), (121, 56), (121, 57), (121, 58), (122, 56), (122, 57), (123, 56), (123, 57), (123, 66), (124, 56), (124, 57), (124, 63), (124, 64), (124, 65), (124, 66), (125, 56), (125, 57), (125, 62), (125, 64), (125, 65), (125, 66), (126, 56), (126, 62), (126, 63), (126, 64), (126, 65), (126, 66), (127, 61), (127, 63), (127, 64), (127, 65), (127, 66), (128, 61), (128, 62), (128, 63), (128, 64), (128, 65), (128, 66), (129, 60), (129, 61), (129, 62), (129, 63), (129, 64), (129, 65), (129, 66)],				
iMughals : [(99, 40), (100, 40), (101, 40), (99, 49), (100, 50), (107, 50), (108, 50)],				
iOttomans : [(79, 49), (80, 55), (83, 49), (87, 49), (87, 50), (87, 51), (88, 49), (88, 50), (88, 51), (89, 49), (89, 50), (89, 51), (90, 49), (90, 50), (90, 51), (91, 50), (91, 51)],				
iThailand : [(122, 39), (122, 40), (121, 40), (121, 41)],				
iNetherlands : [(65, 62)],				
iGermany : [(65, 58), (65, 59), (65, 64), (65, 65), (74, 58), (74, 59), (74, 61), (74, 62), (74, 63), (74, 64), (75, 58), (75, 59), (75, 60), (75, 61), (75, 62), (75, 63), (75, 64)],				
iAmerica : [(10, 49), (12, 49), (13, 49), (14, 49), (15, 49), (26, 49), (26, 59), (27, 59), (30, 59), (31, 59)],				
iArgentina : [(39, 5), (39, 14), (39, 15)],				
iBrazil : [(36, 17), (36, 18), (36, 19), (36, 20), (36, 21), (36, 22), (36, 23), (36, 24), (36, 25), (36, 36), (37, 16), (37, 17), (37, 18), (37, 19), (37, 20), (37, 21), (37, 22), (37, 23), (37, 24), (38, 16), (38, 17), (38, 18), (38, 19), (38, 20), (38, 21), (38, 22), (38, 23), (39, 16), (39, 17), (39, 18), (39, 19)],				
iCanada : [(8, 59), (8, 60), (9, 60), (9, 61), (10, 59), (10, 60), (11, 59), (12, 60), (12, 61), (13, 59), (14, 59), (14, 60), (14, 61), (15, 59), (15, 60), (15, 61), (16, 59), (16, 60), (16, 61), (17, 59), (17, 60), (17, 61), (18, 59), (18, 60), (18, 61), (19, 59), (19, 60), (19, 61), (20, 59), (20, 60), (20, 61), (21, 59), (21, 60), (21, 61), (22, 59), (22, 60), (23, 60), (24, 59), (24, 60), (30, 59), (31, 59), (32, 59), (33, 59), (33, 60), (34, 60), (39, 78), (40, 74), (40, 76)],				
}				
				
dChangedNormalAreaExceptions = {				
iMaya : [(31, 30), (32, 30), (33, 30), (34, 30), (35, 30), (32, 31), (33, 31), (34, 31), (35, 31), (32, 32), (33, 32), (34, 32), (35, 32), (32, 33), (33, 33), (34, 33)], # Colombia				
iArabia : [(84, 35), (84, 36), (84, 37), (85, 35), (91, 47), (91, 48)],				
iKhmer:	[(121, 35), (122, 35), (121, 36), (122, 36), (121, 37), (122, 37), (121, 38), (124, 41), (124, 43)],			
iHolyRome : [(69, 59), (69, 60), (73, 62), (74, 62), (75, 56), (75, 57), (75, 62), (76, 56), (76, 57), (76, 62), (77, 56), (77, 57), (77, 62), (78, 56), (78, 57), (78, 62)],				
}				
				
				
### Broader Area ###				
				
tBroaderArea = (				
((70, 32),	(85, 46)),	# Egypt		
((83, 44),	(91, 52)),	# Babylonia		
((97, 42),	(104, 51)),	# Harappa
((28, 24), (28, 24)), 	# Norte Chico		
((66, 27), 	(71, 31)), 	# Nubia		
((86, 48),	(89, 52)),	# Assyria		
((111, 41),	(130, 59)),	# China		
((71, 46),	(90, 55)),	# Greece		
((99, 30),	(114, 51)),	# India		
((83, 46),	(86, 49)),	# Carthage
((65, 58),	(71, 61)),	# Celtia		
((0, 17),	(20, 35)),	# Polynesia		
((82, 43),	(106, 59)),	# Persia		
((55, 43),	(85, 59)),	# Rome		
((19, 36),	(27, 44)),	# Maya		
((104, 26),	(121, 38)), # Tamils			
((79, 24),	(90, 37)),	# Ethiopia	
((120, 39), 	(123, 43)), 	# Vietnam		
((15, 42), 	(18, 45)), 	# Teotihuacan		
((87, 53),	(91, 55)),	# Armenia			
((128, 53),	(133, 61)),	# Korea
((32, 17), (34, 22)),	# Tiwanaku		
((67, 42),	(86, 56)),	# Byzantium
((28, 22),	(32, 25)),	# Wari		
((133, 46),	(139, 67)),	# Japan		
((65, 66),	(86, 77)),	# Vikings		
((79, 44),  (103, 52)),   # Turks				
((74, 35),	(98, 54)),	# Arabia		
((107, 47),	(115, 54)),	# Tibet		
((116, 25),	(136, 33)),	# Indonesia		
((115, 38),	(118, 43)),	# Burma		
((86, 58),	(92, 60)),	# Khazars		
((70, 34), 	(74, 39)),    # Chad			
((57, 43),	(68, 51)),	# Moors		
((55, 45),	(66, 54)),	# Spain		
((55, 53),	(70, 64)),	# France		
((93, 37),	(96, 41)),	# Oman		
((125, 56),	(131, 65)),	# Khitan		
((115, 34),	(124, 43)),	# Khmer		
((87, 34),	(92, 37)),	# Yemen		
((53, 62),	(60, 70)),	# England		
((63, 54),	(73, 65)),	# Holy Rome		
((79, 59),	(83, 62)),	# Kievan Rus		
((73, 57),	(77, 59)),	# Hungary		
((128, 35),	(133, 40)),	# Philippines		
((82, 18),	(85, 25)),	# Swahili		
((74, 39),	(81, 45)),	# Mamluks		
((54, 31),	(68, 38)),	# Mali		
((73, 60),	(82, 66)),	# Poland		
((75, 17),	(79, 22)),	# Zimbabwe		
((49, 48),	(58, 52)),	# Portugal		
((26, 13),	(34, 34)),	# Inca		
((66, 49),	(74, 57)),	# Italy		
((65, 31),	(70, 35)),	# Nigeria		
((86, 52),	(132, 68)),	# Mongolia		
((12, 37),	(25, 50)),	# Aztecs		
((99, 42),	(111, 51)),	# Mughals		
((75, 49),	(104, 59)),	# Ottomans		
((75, 57),	(110, 77)),	# Russia		
((115, 26),	(122, 44)),	# Thailand		
((69, 24),	(74, 27)),	# Congo		
((70, 68), 	(77, 75)), 	# Sweden		
((63, 62),	(65, 65)),	# Netherlands		
((125, 56),	(131, 65)),	# Manchuria		
((61, 58),	(77, 68)),	# Germany		
((7, 47),	(40, 64)),	# America		
((32, 3),	(41, 17)),	# Argentina		
((33, 15),	(49, 32)),	# Brazil		
((137, 9),	(143, 20)),	# Australia		
((75, 11),	(81, 16)),	# Boer		
((26, 59),	(37, 63)),	# Canada		
((83, 44), 	(84, 47)), 	# Israel		
)				
				
dChangedBroaderArea = {	
iNorteChico : 	((26, 26),	(27, 31)),	# Chimu		
iHarappa :	((103, 35),	(105, 40)),	# Chalukya				
iCarthage :	((57, 43),	(73, 54)), 	# Carthage	
iMaya :		((26, 27),	(38, 38)),	# Colombia
iByzantium :	((64, 38),	(74, 45)),		
iHolyRome :	((66, 54),	(79, 62)),		
iMughals :	((84, 37),	(94, 43)),		
}				
				
### Respawn area ###				
				
dRespawnArea = {				
iEgypt :	((75, 37), 	(82, 45)),		
iChina :	((117, 46),	(129, 56)),		
iIndia :	((103, 37),	(113, 47)),		
iByzantium :	((75, 49),	(81, 57)),	
iKazakh :	((99, 58),	(107, 62)),
iMoors :	((56, 42),	(68, 48)),
iKievanRus : ((78, 60),	(81, 62)),		
iInca :		((26, 17),	(38, 29)),	
iMughals :	((99, 43),	(104, 49)),		
}				
				
dRespawnAreaExceptions = {				
iIndia : [(112, 47), (113, 47)],				
iMoors : [(58, 48)],				
iInca : [(33, 27), (33, 28), (33, 29), (34, 27), (34, 28), (34, 29), (35, 27), (35, 28), (35, 29), (36, 17), (36, 18), (36, 19), (36, 26), (36, 27), (36, 28), (36, 29), (37, 17), (37, 18), (37, 19), (37, 25), (37, 26), (37, 27), (37, 28), (37, 29), (38, 17), (38, 18), (38, 19), (38, 24), (38, 25), (38, 26), (38, 27), (38, 28), (38, 29)],				
}				
				
### Rebirth area ###				
				
dRebirthPlot = {			
iNorteChico : (27, 28),	# Chimu			
iHarappa : (104, 37),	# Chalukya					
iPersia : (93, 48),	# Esfahan (Iran)					
iCeltia : (57, 69),	# Scottish			
iMaya : (29, 34),	# Bogota (Colombia)			
iAztecs : (17, 43),	# Mexico City (Mexico)			
}				
				
dRebirthArea = {	
iNorteChico : 	((26, 26),	(28, 30)),	# Chimu	
iHarappa :	((103, 35),	(105, 40)),	# Chalukya		
iCeltia : 	((53, 65),	(57, 71)),	# Scottish				
iPersia :	((90, 43),	(98, 53)),	# Iran	
iMaya : ((26, 30),	(36, 38)),	# Colombia		
iAztecs : ((7, 41),	(23, 55)),	# Mexico		
}				
				
dRebirthAreaExceptions = {				
iCeltia : [(56, 65), (57, 65), (57, 66), (57, 67)],				
iPersia : [(90, 43), (90, 44), (90, 45), (90, 46), (90, 47), (90, 48), (93, 53), (93, 54), (94, 53), (94, 54), (95, 52), (95, 53), (95, 54), (96, 52), (96, 53), (96, 54), (97, 52), (97, 53), (97, 54), (98, 43), (98, 44), (98, 45), (98, 46), (98, 47), (98, 52), (98, 53), (98, 54)],				
iAztecs : [(14, 54), (14, 55), (15, 54), (15, 55), (16, 54), (16, 55), (17, 52), (17, 53), (17, 54), (17, 55), (18, 52), (18, 53), (18, 54), (18, 55), (19, 52), (19, 53), (19, 54), (19, 55), (20, 47), (20, 48), (20, 49), (20, 50), (20, 51), (20, 52), (20, 53), (20, 54), (20, 55), (21, 47), (21, 48), (21, 49), (21, 50), (21, 51), (21, 52), (21, 53), (21, 54), (21, 55), (22, 41), (22, 42), (22, 47), (22, 48), (22, 49), (22, 50), (22, 51), (22, 52), (22, 53), (22, 54), (22, 55), (23, 41), (23, 42), (23, 47), (23, 48), (23, 49), (23, 50), (23, 51), (23, 52), (23, 53), (23, 54), (23, 55)],				
}				
