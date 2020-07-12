# Rhye's and Fall of Civilization - Barbarian units and cities

from CvPythonExtensions import *
import CvUtil
import PyHelpers	# LOQ
#import Popup
#import cPickle as pickle
from RFCUtils import utils
from Consts import *
from StoredData import data

# globals
gc = CyGlobalContext()
PyPlayer = PyHelpers.PyPlayer	# LOQ

# Spawning cities (Leoreth)
# Year, coordinates, owner, name, population, unit type, unit number, religions, forced spawn
tMinorCities = (
(-3000, (84, 45), iIndependent, 'Yerushalayim', 2, iArcher, 3),	# Jerusalem
(-3000, (124, 52), iIndependent2, 'Chengzhou', 2, iArcher, 1), 		# Luoyang
(-2700, (88, 50), iIndependent2, 'Nineveh', 2, iArcher, 1), 		# Assur
(-2000, (92, 46), iIndependent2, 'Shushan', 1, iArcher, 1), 		# Susa
(-2000, (100, 54), iIndependent, 'Afrasiyab', 1, iArcher, 1), 	# Samarkand
(-1600, (108, 45), iIndependent2, 'Varanasi', 1, iMilitia, 1), 	# Varanasi
(-1600, (105, 46), iIndependent2, 'Indraprastha', 1, iMilitia, 1),	# Delhi
(-1000, (124, 56), iIndependent, 'Ji', 2, iSpearman, 1),	# Beijing
(-1000, (82, 53), iIndependent, 'Ankuwash', 2, iArcher, 2),		# Ankara
(-850, (93, 51), iIndependent, 'Rag&#226;', 2, iArcher, 2),		# Ragha
(-760, (66, 57), iIndependent, 'Melpum', 2, iArcher, 2),				# Milan
(-500, (96, 56), iIndependent, 'Urganj', 1, iArcher, 2), 	# Urgench
(-500, (98, 54), iIndependent2, 'Numijkat', 2, iArcher, 2), 	# Bukhara
#(-350, (63, 58), iCeltia, 'Lugodunon', 2, -1, -1),				# Lyon
(-325, (107, 35), iIndependent, 'Kanchipuram', 2, iArcher, 1),	# Madras
(-300, (128, 58), iBarbarian, 'Simiyan hoton', 2, iChariot, 2),	# Shenyang
#(-300, (59, 56), iCeltia, 'Burdigala', 2, -1, -1),				# Bordeaux
(-300, (106, 33), iIndependent, 'Tanjapuri', 1, iWarElephant, 1),	# Thanjavur
#(-258, (121, 42), iIndependent, 'Co Loa', 2, iArcher, 3),			# Hanoi
(-250, (19, 41), iNative, 'Danib&#225;an', 2, iHolkan, 2),		# Monte Alban
(-214, (125, 43), iIndependent, 'Panyu', 2, iArcher, 2),	# Guangzhou
(-190, (89, 54), iIndependent2, 'Artashat', 1, -1, -1),			# Artaxata
(-130, (87, 51), iIndependent2, 'Urfa', 2, iArcher, 2),		# Edessa
(-100, (114, 57), iBarbarian, 'Dunhuang', 2, iArcher, 1),		# Dunhuang
(-100, (109, 56), iBarbarian, 'Kuqa', 2, iArcher, 1),			# Kuqa
(-75, (105, 55), iBarbarian, 'Kashgar', 2, iArcher, 1),			# Kashgar
#(-50, (61, 60), iCeltia, 'Lutetia', 2, -1, -1),					# Paris
(-75, (100, 50), iIndependent2, 'Bagram', 2, iArcher, 1),			# Bagram
(100, (17, 43), iBarbarian, 'Tolan', 2, iJaguar, 2),		# Teotihuacan
(100, (88, 36), iIndependent, "Sana'a", 2, -1, -1),				# Sana'a
(107, (117, 41), iIndependent2, 'Pugam', 2, -1, -1),			# Pagan
(200, (87, 33), iIndependent2, 'Barbara', 2, iArcher, 2),	# Berbera
(450, (54, 65), iIndependent, '&#193;th Cliath', 1, iArcher, 1),			# Dublin
(450, (57, 69), iIndependent2, 'D&#249;n &#200;ideann', 1, iArcher, 1),			# Edinburgh
(500, (123, 39), iIndependent, 'Indrapura', 2, iArcher, 1),		# Indrapura
(500, (73, 54), iIndependent, "Ragusa", 3, iCrossbowman, 3), # Ragusa
(500, (86, 39), iIndependent, 'Bakkah', 3, iArcher, 1),		# Mecca
(510, (104, 37), iIndependent, "Vatapi", 3, iCrossbowman, 2), # Vatapi
(520, (68, 72), iIndependent, 'Oslo', 2, iArcher, 1),		# Oslo
#(633, (113, 48), iBarbarian, 'Lhasa', 2, iKhampa, 1),			# Lhasa
(680, (57, 44), iIndependent, 'Murrakush', 3, iCrossbowman, 1),	# Marrakesh
#(700, (34, 22), iNative, 'Tiwanaku', 1, -1, -1),				# Tiahuanaco
(700, (67, 48), iIndependent2, 'Tunis', 3, iCrossbowman, 2),	# Tunis
(738, (118, 45), iIndependent2, 'Darllit', 2, iArcher, 1),		# Dali
(800, (71, 59), iIndependent, 'Vindobona', 1, iCrossbowman, 1),	# Wien
(800, (70, 61), iIndependent2, 'Praha', 1, iCrossbowman, 1),	# Prague
(800, (58, 67), iIndependent, 'York', 1, iCrossbowman, 1),	# York
#(800, (85, 69), iIndependent2, 'Beloozero', 1, iCrossbowman, 1),	# Beloozero
(830, (66, 65), iIndependent, 'Hamburg', 2, iCrossbowman, 1),	# Hamburg
(850, (66, 65), iIndependent, 'L&#252;beck', 2, iCrossbowman, 1),	# Lubeck
#(860, (82, 68), iIndependent, 'Novgorod', 3, iCrossbowman, 3),		# Novgorod
(870, (27, 28), iIndependent, 'Chan Chan', 2, iArcher, 2),			# Chan Chan
(870, (26, 31), iNative, 'Tucume', 2, iPictaAucac, 1),			# Tucume
(899, (92, 41), iIndependent, 'Bahrein', 2, iArcher, 2),			# Qarmatians (Abu Sa'id al-Jannabi)
(900, (28, 25), iNative, 'Pachakamaq', 1, iArcher, 2),			# Pachacamac
(900, (87, 30), iIndependent, 'Muqdisho', 3, iCrossbowman, 2),	# Mogadishu
(944, (63, 48), iIndependent, "Dzayer", 3, iCrossbowman, 2),	# Algiers
#(990, (130, 38), iIndependent, 'Maynila', 2, iArcher, 2),		# Manila
(1000, (68, 75), iIndependent2, 'Nidaros', 2, iHuscarl, 1),		# Trondheim
(1000, (87, 30), iNative, 'Muqdisho', 1, iImpi, 1),				# Mogadishu
(1050, (89, 54), iIndependent2, 'Dvin', 2, iCrossbowman, 1),		# Dvin
(1115, (131, 61), iIndependent, "Huining", 3, iHorseArcher, 3),		# Huining
(1154, (96, 40), iIndependent, "Masqat", 3, iCrossbowman, 3),	# Muscat
(1157, (69, 64), iIndependent, 'Brandenburg', 3, iCrossbowman, 2),		# Brandenburg
(1157, (67, 60), iIndependent, 'Ansach', 3, iCrossbowman, 2),		# Ansach
(1200, (92, 65), iBarbarian, 'Qazan', 2, iHorseArcher, 1),		# Kazan
(1200, (78, 68), iIndependent, 'Riga', 3, iCrossbowman, 2),		# Riga
#(1200, (89, 61), iBarbarian, 'Tsaritsyn', 3, iHorseArcher, 1),		# Tsaritsyn
#(1200, (131, 36), iIndependent2, 'Sugbo', 2, iArcher, 2),		# Cebu
(1252, (72, 71), iIndependent2, 'Stockholm', 3, iCrossbowman, 3),		# Stockholm
(1255, (75, 65), iIndependent, 'K&#246;nigsberg', 3, iCrossbowman, 3),		# Konigsberg
(1300, (120, 30), iIndependent2, 'Melaka', 5, iCrossbowman, 3),	# Malacca
(1300, (119, 40), iIndependent2, 'Chiang Mai', 3, iCrossbowman, 3),	# Thai Chiang Mai
(1300, (100, 67), iBarbarian, "Qasliq", 4, iCrossbowman, 3),	# Sibir (Tobolsk)
(1400, (123, 35), iIndependent, 'Sai Gon', 5, iCrossbowman, 3),	# Saigon
(1483, (70, 24), iNative, "M'banza-Kongo", 1, iPombos, 1),		# Mbanza Kongo
#(1515, (130, 33), iIndependent2, 'Maguindanao', 2, iCrossbowman, 2),		# Maguindanao
)

# do some research on dates here
tMinorStates = (
	(633, 1400, (113, 48), [iArcher, iSwordsman]),	# Tibet
	(-2500, -600, (88, 50), [iVulture]),		# Assyria
	(-75, 600, (105, 55), [iHorseman]),		# Kashgar early
	(600, 1600, (105, 55), [iHorseArcher]),		# Kashgar late
	(-75, 600, (100, 54), [iHorseman]),		# Samarkand early
	(600, 1600, (100, 54), [iHorseArcher, iCrossbowman]),		# Samarkand late
	(-300, 600, (106, 33), [iArcher, iSwordsman, iWarElephant]), # Chola
	(-300, 600, (107, 35), [iArcher, iSwordsman, iWarElephant]), # Chola
	(-300, 900, (128, 58), [iHorseArcher, iSwordsman]), # Jurchen
	(500, 1500, (68, 53), [iPikeman, iCrossbowman]), # Rome late
	(0, 1100, (68, 53), [iSpearman, iArcher]), # Rome early
	(860, 1380, (82, 68), [iCrossbowman, iHeavySpearman, iWorker]), # Novgorod
	(884, 1380, (80, 62), [iCrossbowman, iHeavySpearman, iWorker]), # Kiev
	(990, 1565, (130, 38), [iCrossbowman, iSwordsman, iWorker]), # Manila
	#(1010, 1380, (73, 58), [iCrossbowman, iHeavySpearman, iWorker]), # Yaroslavl
	(1200, 1570, (92, 65), [iCrossbowman, iKeshik]), # Kazan
	(1200, 1420, (89, 61), [iCrossbowman, iKeshik]), # Tsaritsyn
	(1300, 1581, (62, 64), [iCrossbowman, iHeavySpearman, iLancer]), # Amsterdam
)

#handicap level modifier
iHandicapOld = (gc.getGame().getHandicapType() - 1)

class Barbs:
		
	def checkTurn(self, iGameTurn):
		
		#handicap level modifier
		iHandicap = gc.getHandicapInfo(gc.getGame().getHandicapType()).getBarbarianSpawnModifier()
		
		# Leoreth: buff certain cities if independent / barbarian (imported from SoI)
		if iGameTurn % 20 == 10:
			for tMinorState in tMinorStates:
				iStartYear, iEndYear, tPlot, lUnitList = tMinorState
				if utils.isYearIn(iStartYear, iEndYear):
					x, y = tPlot
					plot = gc.getMap().plot(x, y)
					iOwner = plot.getOwner()
					if plot.isCity() and plot.getNumUnits() < 4 and iOwner >= iNumPlayers:
						iUnit = utils.getRandomEntry(lUnitList)
						utils.makeUnit(iUnit, iOwner, tPlot, 1)

		if utils.isYearIn(-100, 1600):
			# Brown Bear in Chukchi
			self.checkLimitedSpawn(iBarbarian, iPolarBear, 1, 5, (140, 65), (148, 76), self.spawnBears, iGameTurn, 10, 1)
			# Brown Bear and American Black Bear in Alaska and Western Canada
			self.checkLimitedSpawn(iBarbarian, iPolarBear, 1, 5,  (0, 67), (24, 77), self.spawnBears, iGameTurn, 5, 3)
			# Polar Bear in Greenland and Eastern Canada
			self.checkLimitedSpawn(iBarbarian, iPolarBear, 1, 5, (25, 63), (44, 77), self.spawnBears, iGameTurn, 5, 5)

		if utils.isYearIn(-3000, -850):
			if iHandicap >= 0:
				self.checkSpawn(iBarbarian, iWarrior, 1, (92, 53), (116, 62), self.spawnMinors, iGameTurn, 5, 0)

			# Wolves and Brown Bears in Russia and Siberia
			self.checkSpawn(iBarbarian, iWolf, 1, (89, 66), (125, 75), self.spawnNatives, iGameTurn, 5, 2)
			self.checkSpawn(iBarbarian, iBear, 1, (89, 66), (125, 75), self.spawnNatives, iGameTurn, 5, 4)

			# Panthers, Hyenas, and Lions in South Africa
			self.checkSpawn(iBarbarian, iLion, 1, (67, 12), (84, 34), self.spawnNatives, iGameTurn, 4, 1)
			self.checkSpawn(iBarbarian, iPanther, 1, (67, 12), (84, 34), self.spawnNatives, iGameTurn, 4, 3)
			self.checkLimitedSpawn(iBarbarian, iHyena, 1, 5, (67, 12), (84, 34), self.spawnNatives, iGameTurn, 5, 3)

			# Panthers and Tigers in India, South China, Indochina, and Indonesia
			self.checkLimitedSpawn(iBarbarian, iPanther, 1, 5, (101, 32), (130, 49), self.spawnNatives, iGameTurn, 5, 1)
			self.checkLimitedSpawn(iBarbarian, iTiger, 1, 5, (101, 32), (130, 49), self.spawnNatives, iGameTurn, 5, 1)

			#Asian Black Bears in China, Japan, Manchuria, Vietnam, and Korea
			self.checkLimitedSpawn(iBarbarian, iBear, 1, 5, (120, 35), (141, 66), self.spawnNatives, iGameTurn, 5, 3)

			# Jaguars in Brazil, Colombia, and Mesoamerica
			self.checkLimitedSpawn(iBarbarian, iJaguarAnimal, 1, 5, (34, 24), (49, 36), self.spawnNatives, iGameTurn, 5, 1)
			self.checkLimitedSpawn(iBarbarian, iJaguarAnimal, 1, 5, (26, 29), (40, 38), self.spawnNatives, iGameTurn, 5, 3)
			self.checkLimitedSpawn(iBarbarian, iJaguarAnimal, 1, 5, (19, 36), (30, 45), self.spawnNatives, iGameTurn, 5, 3)


		#celts
		if utils.isYearIn(-650, -110):
			self.checkSpawn(iBarbarian, iSwordsman, 1, (57, 56), (76, 61), self.spawnMinors, iGameTurn, 6, 0)
			if iHandicap >= 0:
				self.checkSpawn(iBarbarian, iAxeman, 1, (57, 56), (76, 61), self.spawnMinors, iGameTurn, 8, 5, ["TXT_KEY_ADJECTIVE_GAUL"])


		#norse
		if utils.isYearIn(-650, 550):
			self.checkSpawn(iBarbarian, iGalley, 1, (55, 59), (66, 68), self.spawnPirates, iGameTurn, 20, 0, ["TXT_KEY_ADJECTIVE_NORSE"])
			
		#mongolia
		if utils.isYearIn(-210, 400):
			self.checkSpawn(iBarbarian, iHorseArcher, 3 + iHandicap, (118, 55), (129, 58), self.spawnNomads, iGameTurn, 7-iHandicap, 0, ["TXT_KEY_ADJECTIVE_XIONGNU"])
		elif utils.isYearIn(-210, 400):
			self.checkSpawn(iBarbarian, iHorseArcher, 1 + iHandicap, (106, 54), (114, 59), self.spawnNomads, iGameTurn, 7-iHandicap, 0, ["TXT_KEY_ADJECTIVE_XIONGNU"])
		elif utils.isYearIn(-210, 400):
			self.checkSpawn(iBarbarian, iHorseArcher, 1 + iHandicap, (114, 60), (125, 65), self.spawnNomads, iGameTurn, 7-iHandicap, 0, ["TXT_KEY_ADJECTIVE_XIONGNU"])
		elif utils.isYearIn(400, 900):
			iNumUnits = 3 + iHandicap
			self.checkSpawn(iBarbarian, iHorseArcher, iNumUnits, (110, 58), (129, 65), self.spawnNomads, iGameTurn, 6-iHandicap, 0, ["TXT_KEY_ADJECTIVE_GOKTURK", "TXT_KEY_ADJECTIVE_UIGHUR"])
		elif utils.isYearIn(900, 1100):
			iNumUnits = 3 + iHandicap
			self.checkSpawn(iBarbarian, iKeshik, iNumUnits, (110, 58), (129, 65), self.spawnInvaders, iGameTurn, 6, 0, ["TXT_KEY_ADJECTIVE_JURCHEN", "TXT_KEY_ADJECTIVE_KHITAN"])
			
		#tibet
		if utils.isYearIn(-350, 200):
			self.checkSpawn(iBarbarian, iLightSwordsman, 1 + iHandicap, (107, 48), (116, 52), self.spawnMinors, iGameTurn, 10-iHandicap, 3, ["TXT_KEY_ADJECTIVE_TIBETAN"])
		elif utils.isYearIn(200, 1100):
			self.checkSpawn(iBarbarian, iSwordsman, 1 + iHandicap, (107, 48), (116, 52), self.spawnMinors, iGameTurn, 10-iHandicap, 3, ["TXT_KEY_ADJECTIVE_TIBETAN"])

		# Deccan barbarians
		if utils.isYearIn(-1000, 1200):
			iUnit = iArcher
			iStrength = iHandicap
			if iGameTurn >= getTurnForYear(-500): iUnit = iAxeman
			if iGameTurn >= getTurnForYear(0): iStrength += 1
			if iGameTurn >= getTurnForYear(200): iUnit = iSwordsman
			
			self.checkSpawn(iBarbarian, iUnit, iStrength, (101, 31), (111, 42), self.spawnInvaders, iGameTurn, 8-iHandicap, 0, ["Hindi"])
			
		# elephants in india pre-khmer
		if utils.isYearIn(-210, 700):
			self.checkSpawn(iBarbarian, iWarElephant, 1, (103, 35), (117, 45), self.spawnInvaders, iGameTurn, 8-iHandicap, 4)
			
		# elephants in africa
		if utils.isYearIn(1110, 1450):
			self.checkSpawn(iBarbarian, iWarElephant, 2, (75, 18), (83, 25), self.spawnInvaders, iGameTurn, 8-iHandicap, 4)
			
		# Longbowman in africa
		if utils.isYearIn(1450, 1600):
			self.checkSpawn(iBarbarian, iLongbowman, 2, (75, 18), (83, 25), self.spawnInvaders, iGameTurn, 8-iHandicap, 4)
			
		# OromoWarrior in africa
		if utils.isYearIn(1610, 1850):
			self.checkSpawn(iBarbarian, iOromoWarrior, 2, (75, 18), (83, 25), self.spawnInvaders, iGameTurn, 8-iHandicap, 4)

		#Indo-Scythians
		if utils.isYearIn(-200, 400):
			self.checkSpawn(iBarbarian, iHorseman, 2, (97, 47), (104, 51), self.spawnNomads, iGameTurn, 8-iHandicap, 4, ["TXT_KEY_ADJECTIVE_INDO_SCYTHIAN"])

		#Kushana
		if utils.isYearIn(30, 220):
			self.checkSpawn(iBarbarian, iHorseman, 3+iHandicap, (97, 47), (104, 51), self.spawnInvaders, iGameTurn, 8, 3, ["TXT_KEY_ADJECTIVE_KUSHANA"])

		#Hephtalites
		if utils.isYearIn(400, 550):
			self.checkSpawn(iBarbarian, iHorseArcher, 2+iHandicap, (97, 47), (104, 51), self.spawnInvaders, iGameTurn, 5-iHandicap, 2, ["TXT_KEY_ADJECTIVE_HEPHTHALITE"])

		# Holkans in classical Mesoamerica
		if utils.isYearIn(-200, 100):
			self.checkSpawn(iBarbarian, iHolkan, 1, (15, 36), (27, 44), self.spawnUprising, iGameTurn, 7, 5)
		if utils.isYearIn(100, 600):
			self.checkSpawn(iBarbarian, iHolkan, 1, (15, 36), (27, 44), self.spawnUprising, iGameTurn, 6, 4)
		elif utils.isYearIn(600, 1000):
			self.checkSpawn(iBarbarian, iHolkan, 1, (15, 36), (27, 44), self.spawnUprising, iGameTurn, 4, 2)
		
	               # Picta Aucacs in pre-Incan Andes
		if utils.isYearIn(800, 1100):
			 self.checkSpawn(iBarbarian, iPictaAucac, 1, (29, 17), (33, 24), self.spawnUprising, iGameTurn, 4, 2)

		# Jaguars in classical Mesoamerica
		if utils.isYearIn(150, 500):
			self.checkSpawn(iBarbarian, iJaguar, 1, (15, 36), (27, 44), self.spawnUprising, iGameTurn, 6, 4)	
		elif utils.isYearIn(500, 1150):
			self.checkSpawn(iBarbarian, iJaguar, 1, (15, 36), (27, 44), self.spawnUprising, iGameTurn, 4, 2)

		#pirates in Mediterranean
		if utils.isYearIn(-210, 50):
			self.checkSpawn(iBarbarian, iWarGalley, 1, (55, 44), (84, 54), self.spawnPirates, iGameTurn, 8, 0)

		#pirates in Barbary coast
		if not gc.getPlayer(iMoors).isAlive():
			if utils.isYearIn(-50, 700):
				self.checkSpawn(iBarbarian, iWarGalley, 1, (52, 41), (72, 49), self.spawnPirates, iGameTurn, 18, 0)
			elif utils.isYearIn(700, 1400):
				self.checkSpawn(iBarbarian, iWarGalley, 1, (52, 41), (72, 49), self.spawnPirates, iGameTurn, 8, 0)
		#pirates in Indian ocean
		if utils.isYearIn(-650, 700):
			self.checkSpawn(iBarbarian, iWarGalley, 1, (84, 24), (106, 42), self.spawnPirates, iGameTurn, 18, 0)
		elif utils.isYearIn(700, 1700):
			self.checkSpawn(iBarbarian, iHeavyGalley, 1, (84, 24), (106, 42), self.spawnPirates, iGameTurn, 10, 0)

		# Leoreth: Barbarians in Anatolia (Hittites), replace Hattusas spawn
		#if utils.isYearIn(-2000, -800):
			#self.checkSpawn(iBarbarian, iHuluganni, 1 + iHandicap, (81, 51), (86, 55), self.spawnInvaders, iGameTurn, 16, 0, ["TXT_KEY_ADJECTIVE_HITTITE"])
		if utils.isYearIn(-2000, -800):
			self.checkSpawn(iBarbarian, iChariot, 1 + iHandicap, (81, 51), (86, 55), self.spawnInvaders, iGameTurn, 16, 0)

		#barbarians in europe
		if utils.isYearIn(-210, 470):
			self.checkSpawn(iBarbarian, iAxeman, 3 + iHandicap, (57, 55), (74, 61), self.spawnInvaders, iGameTurn, 10, 0, ["TXT_KEY_ADJECTIVE_GERMANIC"])
			self.checkSpawn(iBarbarian, iAxeman, 2 + iHandicap, (74, 58), (81, 66), self.spawnInvaders, iGameTurn, 12, 2, ["TXT_KEY_ADJECTIVE_GERMANIC"])
		# Leoreth: begins 100 AD instead of 50 AD
		if utils.isYearIn(100, 470):
			self.checkSpawn(iBarbarian, iSwordsman, 4, (66, 55), (82, 66), self.spawnInvaders, iGameTurn, 8, 5, ["TXT_KEY_ADJECTIVE_GERMANIC"])
		if utils.isYearIn(300, 550):
			self.checkSpawn(iBarbarian, iAxeman, 4 + iHandicap, (55, 49), (63, 61), self.spawnInvaders, iGameTurn, 5, 4, ["TXT_KEY_ADJECTIVE_VISIGOTHIC"])
			self.checkSpawn(iBarbarian, iSwordsman, 4 + iHandicap, (55, 49), (63, 61), self.spawnInvaders, iGameTurn, 5, 2, ["TXT_KEY_ADJECTIVE_VISIGOTHIC"])
			self.checkSpawn(iBarbarian, iHorseArcher, 4, (62, 58), (76, 64), self.spawnInvaders, iGameTurn, 5, 0, ["TXT_KEY_ADJECTIVE_HUNNIC"])
		if utils.isYearIn(300, 700):
			self.checkSpawn(iBarbarian, iHorseArcher, 3 + iHandicap, (65, 60), (106, 63), self.spawnInvaders, iGameTurn, 3, 2, ["TXT_KEY_ADJECTIVE_HUNNIC"])

		#Leoreth: barbarians in Balkans / Black Sea until the High Middle Ages (Bulgarians, Cumans, Pechenegs)
		if utils.isYearIn(680, 1000):
			self.checkSpawn(iBarbarian, iHorseArcher, 3 + iHandicap, (73, 55), (81, 60), self.spawnInvaders, iGameTurn, 6, 2, ["TXT_KEY_ADJECTIVE_AVAR", "TXT_KEY_ADJECTIVE_BULGAR"])
		if utils.isYearIn(900, 1200):
			self.checkSpawn(iBarbarian, iHorseArcher, 3 + iHandicap, (79, 58), (92, 61), self.spawnInvaders, iGameTurn, 8, 5, ["TXT_KEY_ADJECTIVE_CUMAN"])

		#1SDAN: Qarmatians (Abu Tahir al-Jannabi)
		if utils.isYearIn(900, 1000):
			self.checkSpawn(iBarbarian, iHorseArcher, 1 + iHandicap, (91, 39), (95, 41), self.spawnInvaders, iGameTurn, 3, 2, ["TXT_KEY_ADJECTIVE_QARMATIAN"])

		#barbarians in central asia
		if utils.isYearIn(-1600, -850):
			self.checkLimitedSpawn(iBarbarian, iVulture, 1, 3, (84, 42), (90, 44), self.spawnNomads, iGameTurn, 8-iHandicap, 2, ["TXT_KEY_ADJECTIVE_ASSYRIAN"])
		elif utils.isYearIn(-850, -200):
			self.checkSpawn(iBarbarian, iHorseman, 1 + iHandicap, (80, 56), (90, 60), self.spawnInvaders, iGameTurn, 10-2*iHandicap, 3, ["TXT_KEY_ADJECTIVE_SCYTHIAN"])
		elif utils.isYearIn(-200, 600):
			self.checkSpawn(iBarbarian, iHorseman, 2 + iHandicap, (92, 49), (98, 59), self.spawnInvaders, iGameTurn, 7-iHandicap, 2, ["TXT_KEY_ADJECTIVE_PARTHIAN"])
		elif utils.isYearIn(600, 900):
			#if utils.getScenario() == i3000BC:  #late start condition
			self.checkSpawn(iBarbarian, iOghuz, 2 + iHandicap, (91, 50), (103, 58), self.spawnNomads, iGameTurn, 8-iHandicap, 2)
		elif utils.isYearIn(900, 1040):
			#if utils.getScenario() == i3000BC:  #late start condition
			self.checkSpawn(iBarbarian, iOghuz, 2 + iHandicap, (91, 50), (106, 62), self.spawnNomads, iGameTurn, 6-iHandicap, 2)

		# late Central Asian barbarians
		if utils.isYearIn(1200, 1600):
			if not utils.getAreaCitiesCiv(iMongolia, utils.getPlotList((82, 58), (95, 70))):
				self.checkSpawn(iBarbarian, iKeshik, 1 + iHandicap, (88, 57), (94, 61), self.spawnNomads, iGameTurn, 10-iHandicap, 5, ["TXT_KEY_ADJECTIVE_TATAR", "TXT_KEY_ADJECTIVE_NOGAI"])
		if utils.isYearIn(1400, 1700):
			if utils.getAreaCities(utils.getPlotList((91, 58), (106, 62))):
				self.checkSpawn(iBarbarian, iKeshik, 1 + iHandicap, (91, 58), (106, 62), self.spawnNomads, iGameTurn, 10-2*iHandicap, 2, ["TXT_KEY_ADJECTIVE_UZBEK", "TXT_KEY_ADJECTIVE_KAZAKH"])
	
		#barbarians in Elam
		if utils.isYearIn(-1600, -1000):
			self.checkSpawn(iBarbarian, iChariot, 1, (92, 43), (99, 50), self.spawnMinors, iGameTurn, 9-iHandicap, 0, ["TXT_KEY_ADJECTIVE_ELAMITE"])

		#barbarians in north africa
		if utils.isYearIn(-210, 50):
			self.checkSpawn(iBarbarian, iCamelRider, 1, (60, 38), (78, 42), self.spawnNomads, iGameTurn, 9-iHandicap, 3, ["TXT_KEY_ADJECTIVE_BERBER"])
		elif utils.isYearIn(50, 900):
			if utils.getScenario() == i3000BC:  #late start condition
				self.checkSpawn(iBarbarian, iCamelRider, 1 + iHandicap, (60, 38), (78, 42), self.spawnNomads, iGameTurn, 10-iHandicap, 5, ["TXT_KEY_ADJECTIVE_BERBER"])
		elif utils.isYearIn(900, 1800):
			self.checkSpawn(iBarbarian, iCamelArcher, 1, (60, 33), (78, 42), self.spawnNomads, iGameTurn, 10-iHandicap, 4, ["TXT_KEY_ADJECTIVE_BERBER"])
			
		#camels in arabia
		if utils.isYearIn(190, 550):
			self.checkSpawn(iBarbarian, iCamelArcher, 1, (85, 36), (96, 42), self.spawnNomads, iGameTurn, 9-iHandicap, 7, ["TXT_KEY_ADJECTIVE_BEDOUIN"])
		if utils.isYearIn(-800, 1300) and self.includesActiveHuman([iEgypt, iMamluks, iArabia]):
			iNumUnits = iHandicap
			if utils.getScenario() == i3000BC: iNumUnits += 1
			self.checkSpawn(iBarbarian, iMedjay, iNumUnits, (78, 33), (82, 41), self.spawnUprising, iGameTurn, 12, 4, ["TXT_KEY_ADJECTIVE_NUBIAN"])
		if utils.isYearIn(450, 1600):
			if utils.getScenario() == i3000BC:
				self.checkSpawn(iNative, iImpi, 2 + iHandicap, (68, 12), (85, 31), self.spawnNatives, iGameTurn, 10, 4)
			else:
				self.checkSpawn(iNative, iImpi, 2 + iHandicap, (68, 12), (85, 31), self.spawnNatives, iGameTurn, 15, 4)
		elif utils.isYearIn(1600, 1800):
			self.checkSpawn(iNative, iPombos, 2 + iHandicap, (68, 12), (85, 31), self.spawnNatives, iGameTurn, 10, 4)
			
		#west africa
		if utils.isYearIn(450, 1700):
			if iGameTurn < getTurnForYear(1300):
				sAdj = ["TXT_KEY_ADJECTIVE_GHANAIAN"]
			else:
				sAdj = ["TXT_KEY_ADJECTIVE_SONGHAI"]
			self.checkSpawn(iNative, iImpi, 2, (55, 28), (70, 34), self.spawnMinors, iGameTurn, 16, 10, sAdj)
			
		if utils.isYearIn(1200, 1700):
			self.checkSpawn(iBarbarian, iFarari, 2, (54, 31), (76, 43), self.spawnMinors, iGameTurn, 16, 4, sAdj)

		
		#bulala in Chad
		if utils.isYearIn(1210, 1571):
			self.checkSpawn(iNative, iLongbowman, 1, (70, 33), (75, 37), self.spawnNatives, iGameTurn, 5, 2, ["TXT_KEY_ADJECTIVE_BULALA"])

                              
		#American natives
		if utils.isYearIn(-100, 400):
			self.checkSpawn(iNative, iDogSoldier, 2 + iHandicap, (13, 46), (24, 56), self.spawnNatives, iGameTurn, 20, 0)
		if utils.isYearIn(400, 1100):
			self.checkSpawn(iNative, iDogSoldier, 1 + iHandicap, (13, 46), (24, 56), self.spawnNatives, iGameTurn, 20, 0)
			if utils.getScenario() == i3000BC:  #late start condition
				self.checkSpawn(iNative, iJaguar, 3, (12, 45), (24, 55), self.spawnNatives, iGameTurn, 16 - 2*iHandicap, 10)
			else:  #late start condition
				self.checkSpawn(iNative, iJaguar, 2, (12, 45), (24, 55), self.spawnNatives, iGameTurn, 16 - 2*iHandicap, 10)
		if utils.isYearIn(1300, 1600):
			self.checkSpawn(iNative, iDogSoldier, 2 + iHandicap, (12, 45), (24, 55), self.spawnNatives, iGameTurn, 8, 0)
		if utils.isYearIn(1400, 1800):
			self.checkSpawn(iNative, iDogSoldier, 1 + iHandicap, (8, 50), (34, 60), self.spawnUprising, iGameTurn, 12, 0)
			self.checkSpawn(iNative, iDogSoldier, 1 + iHandicap, (8, 50), (34, 60), self.spawnUprising, iGameTurn, 12, 6)
		if utils.isYearIn(1300, 1600):
			if iGameTurn % 18 == 0:
				if not gc.getMap().plot(28, 31).isUnit():
					utils.makeUnitAI(iChimuSuchucChiquiAucac, iNative, (28, 31), UnitAITypes.UNITAI_ATTACK, 2 + iHandicap)
			elif iGameTurn % 18 == 9:
				if not gc.getMap().plot(34, 20).isUnit():
					utils.makeUnitAI(iChimuSuchucChiquiAucac, iNative, (34, 20), UnitAITypes.UNITAI_ATTACK, 2 + iHandicap)
		
		if self.includesActiveHuman([iAmerica, iEngland, iFrance, iMississippi]):
			if utils.isYearIn(1700, 1900):
				self.checkSpawn(iNative, iMountedBrave, 1 + iHandicap, (14, 52), (23, 62), self.spawnNomads, iGameTurn, 12 - iHandicap, 2)
			
			if utils.isYearIn(1500, 1850):
				self.checkSpawn(iNative, iMohawk, 1, (24, 54), (31, 61), self.spawnUprising, iGameTurn, 8, 4)
				
		# if iGameTurn == getTurnForYear(-500):
		# 	gc.getMap().plot(19, 41).setImprovementType(iHut)
		# 	utils.makeUnitAI(iHolkan, iNative, (19, 41), UnitAITypes.UNITAI_ATTACK, 2)
			
		# Oromos in the Horn of Africa
		if utils.isYearIn(1500, 1700):
			iNumUnits = 1
			if pEthiopia.isAlive():
				iNumUnits += 1
				if utils.isYearIn(1650, 1800): iNumUnits += 1
			self.checkSpawn(iBarbarian, iOromoWarrior, iNumUnits, (80, 29), (85, 32), self.spawnInvaders, iGameTurn, 8, 3)
				
		#pirates in the Caribbean
		if utils.isYearIn(1600, 1800):
			self.checkSpawn(iNative, iPrivateer, 1, (25, 37), (38, 53), self.spawnPirates, iGameTurn, 5, 0)
		#pirates in Asia
		if utils.isYearIn(1500, 1900):
			self.checkSpawn(iNative, iPrivateer, 1, (83, 24), (133, 42), self.spawnPirates, iGameTurn, 8, 0)

		if iGameTurn < getTurnForYear(tMinorCities[len(tMinorCities)-1][0])+10:
			self.foundMinorCities(iGameTurn)


		
		if iGameTurn == getTurnForYear(-1200):	
			pJerusalem = gc.getGame().getHolyCity(iJudaism)
			if pJerusalem and pJerusalem.getOwner() >= iNumMajorPlayers:
				pJerusalem.setHasRealBuilding(iJewishShrine, True)

		#if iGameTurn == getTurnForYear(tBirth[iInca]):
			#if utils.getHumanID() == iInca:
				#utils.makeUnit(iAucac, iNative, (27, 28), 1)
				#utils.makeUnit(iAucac, iNative, (28, 25), 1)
				
	def foundMinorCities(self, iGameTurn):
		for i in range(len(tMinorCities)):
			iYear, tPlot, iPlayer, sName, iPopulation, iUnitType, iNumUnits = tMinorCities[i]
			if iGameTurn < getTurnForYear(iYear): return
			if iGameTurn > getTurnForYear(iYear)+10: continue
			
			if data.lMinorCityFounded[i]: continue
			
			x, y = tPlot
			plot = gc.getMap().plot(x, y)
			if plot.isCity(): continue
			
			# special cases
			if not self.canFoundCity(sName): continue
			
			lReligions = []
			bForceSpawn = True
			
			if sName == 'Kyiv': lReligions = [iOrthodoxy]
			if sName == 'Dvin': lReligions = [iOrthodoxy]
			if sName == 'Kilwa': lReligions = [iIslam]
			if sName == 'Vatapi': lReligions = [iIslam]
			if iPlayer == iCeltia and utils.getHumanID() == iCeltia: continue
			if iPlayer == iCeltia: iPlayer = iIndependent
			if sName in ['Vatapi', 'Dvin', 'Buda', 'Tucume', 'Chan Chan']: bForceSpawn = True
			if sName in ['Muqdisho', 'Bahrein']: lReligions = [iIslam]
			
			if not self.isFreePlot(tPlot, bForceSpawn): continue
			
			utils.evacuate(iPlayer, tPlot)
		
			if self.foundCity(iPlayer, tPlot, sName, iPopulation, iUnitType, iNumUnits, lReligions):
				data.lMinorCityFounded[i] = True
		
	def canFoundCity(self, sName):
		if sName == 'Kanchipuram' and utils.getHumanID() == iTamils: return False
		elif sName == 'Tanjapuri' and gc.getPlayer(iTamils).isAlive(): return False
		elif sName == 'Ji' and utils.getHumanID() == iChina: return False
		elif sName == 'Hamburg' and (utils.getHumanID() == iHolyRome or data.iSeed % 4 == 0): return False
		elif sName == 'L&#252;beck' and (utils.getHumanID() == iHolyRome or data.iSeed % 4 != 0): return False
		elif sName == 'Rasa' and gc.getPlayer(iTibet).isAlive(): return False
		#elif sName == 'Marrakus' and utils.getScenario() != i3000BC: return False
		
		return True
	
	def foundCity(self, iPlayer, tPlot, sName, iPopulation, iUnitType = -1, iNumUnits = -1, lReligions = []):
		pPlayer = gc.getPlayer(iPlayer)
		x, y = tPlot
		plot = gc.getMap().plot(x, y)
		plot.setOwner(iPlayer)
		pPlayer.found(x, y)
		
		if plot.isCity():
			city = gc.getMap().plot(x, y).getPlotCity()
			
			city.setName(sName, False)
			city.setPopulation(iPopulation)
			if sName in ['Tucume'] : 
				city.setHasRealBuilding(iGranary, True)
				plot.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)
				city.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)
				utils.makeUnit(iChimuSuchucChiquiAucac, iPlayer, tPlot, 2)

			elif sName == 'Vatapi':
				city.setHasRealBuilding(iGranary, True)
				city.setHasRealBuilding(iLighthouse, True)
				city.setHasRealBuilding(iBarracks, True)
				plot.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)
				city.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)

			elif sName == 'Dvin':
				city.setHasRealBuilding(iGranary, True)
				city.setHasRealBuilding(iLibrary, True)
				city.setHasRealBuilding(iBarracks, True)
				plot.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)
				city.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)

			elif sName == 'Chan Chan':
				city.setHasRealBuilding(iGranary, True)
				city.setHasRealBuilding(iLighthouse, True)
				city.setHasRealBuilding(iBarracks, True)
				plot.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)
				city.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)

			elif sName == 'Bahrein':
				city.setHasRealBuilding(iIslamicTemple, True)
				city.setHasRealBuilding(iLighthouse, True)
				city.setHasRealBuilding(iBarracks, True)
				plot.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)
				city.changeCulture(iPlayer, 20 * (gc.getGame().getCurrentEra() + 1), True)
			else:
			                plot.changeCulture(iPlayer, 10 * (gc.getGame().getCurrentEra() + 1), True)
			                city.changeCulture(iPlayer, 10 * (gc.getGame().getCurrentEra() + 1), True)
			
			if iNumUnits > 0 and iUnitType > 0:
				utils.makeUnit(iUnitType, iPlayer, tPlot, iNumUnits)
				
			for iReligion in lReligions:
				if gc.getGame().isReligionFounded(iReligion):
					city.setHasReligion(iReligion, True, False, False)
					
			return True
		
		return False
					
	def clearUnits(self, iPlayer, tPlot): # Unused
		lHumanUnits = []
		lOtherUnits = []
	
		for (x, y) in utils.surroundingPlots(tPlot):
			plot = gc.getMap().plot(x, y)
			
			for iUnit in range(plot.getNumUnits()):
				unit = plot.getUnit(iUnit)
				
				if unit.getOwner() == utils.getHumanID():
					lHumanUnits.append(unit)
				else:
					lOtherUnits.append(unit)
						
		capital = gc.getPlayer(utils.getHumanID()).getCapitalCity()
		for unit in lHumanUnits:
			unit.setXY(capital.getX(), capital.getY(), False, True, False)
			
		for unit in lOtherUnits:
			utils.makeUnit(unit.getUnitType(), iPlayer, tPlot, 1)
			unit.kill(False, iBarbarian)
				
	def isFreePlot(self, tPlot, bIgnoreCulture = False):
		x, y = tPlot
		plot = gc.getMap().plot(x, y)
		
		# no cultural control over the tile
		if plot.isOwned() and plot.getOwner() < iNumPlayers and not bIgnoreCulture:
			return False
				
		# no city in adjacent tiles
		for (i, j) in utils.surroundingPlots(tPlot):
			currentPlot = gc.getMap().plot(i, j)
			if currentPlot.isCity(): return False
						
		return True
			
	def checkRegion(self, tCity): # Unusued
		cityPlot = gc.getMap().plot(tCity[0], tCity[1])
		iNumUnitsInAPlot = cityPlot.getNumUnits()
##		print iNumUnitsInAPlot
		
		#checks if the plot already belongs to someone
		if cityPlot.isOwned():
			if cityPlot.getOwner() != iBarbarian:
				return (False, -1)
		
##		#checks if there's a unit on the plot
		if iNumUnitsInAPlot > 0:
			for i in range(iNumUnitsInAPlot):
				unit = cityPlot.getUnit(i)
				iOwner = unit.getOwner()
				if iOwner == iBarbarian:
					return (False, tCity[3]+1)

		#checks the surroundings and allows only AI units
		for (x, y) in utils.surroundingPlots(tCity[0], tCity[1]):
			currentPlot=gc.getMap().plot(x,y)
			if currentPlot.isCity():
				return (False, -1)
			iNumUnitsInAPlot = currentPlot.getNumUnits()
			if iNumUnitsInAPlot > 0:
				for i in range(iNumUnitsInAPlot):
					unit = currentPlot.getUnit(i)
					iOwner = unit.getOwner()
					pOwner = gc.getPlayer(iOwner)
					if pOwner.isHuman():
						return (False, tCity[3]+1)
		return (True, tCity[3])



	def killNeighbours(self, tCoords): # Unused
		'Kills all units in the neigbbouring tiles of plot (as well as plot itself) so late starters have some space.'
		for (x, y) in utils.surroundingPlots(tCoords):
			killPlot = CyMap().getPlot(x, y)
			for i in range(killPlot.getNumUnits()):
				unit = killPlot.getUnit(0)	# 0 instead of i because killing units changes the indices
				unit.kill(False, iBarbarian)
				
	# Leoreth: check region for number of units first
	def checkLimitedSpawn(self, iPlayer, iUnitType, iNumUnits, iMaxUnits, tTL, tBR, spawnFunction, iTurn, iPeriod, iRest, lAdj=[]):
		if iTurn % utils.getTurns(iPeriod) == iRest:
			lAreaUnits = utils.getAreaUnits(iPlayer, tTL, tBR)
			if len(lAreaUnits) < iMaxUnits:
				self.checkSpawn(iPlayer, iUnitType, iNumUnits, tTL, tBR, spawnFunction, iTurn, iPeriod, iRest, lAdj)
						
	# Leoreth: new ways to spawn barbarians
	def checkSpawn(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, spawnFunction, iTurn, iPeriod, iRest, lAdj=[]):
		if len(lAdj) == 0:
			sAdj = ""
		else:
			sAdj = utils.getRandomEntry(lAdj)
	
		if iTurn % utils.getTurns(iPeriod) == iRest:
			spawnFunction(iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj)
			
	def possibleTiles(self, tTL, tBR, bWater=False, bTerritory=False, bBorder=False, bImpassable=False, bNearCity=False):
		return [tPlot for tPlot in utils.getPlotList(tTL, tBR) if self.possibleTile(tPlot, bWater, bTerritory, bBorder, bImpassable, bNearCity)]
		
	def possibleTile(self, tPlot, bWater, bTerritory, bBorder, bImpassable, bNearCity):
		x, y = tPlot
		plot = gc.getMap().plot(x, y)
		lSurrounding = utils.surroundingPlots(tPlot)
		
		# never on peaks
		if plot.isPeak(): return False
		
		# only land or water
		if bWater != plot.isWater(): return False
		
		# only inside territory if specified
		if not bTerritory and plot.getOwner() >= 0: return False
		
		# never directly next to cities
		if [(i, j) for (i, j) in lSurrounding if gc.getMap().plot(i, j).isCity()]: return False
		
		# never on tiles with units
		if plot.isUnit(): return False
		
		# never in marsh (impassable)
		if plot.getFeatureType() == iMarsh: return False
		
		# allow other impassable terrain (ocean, jungle)
		if not bImpassable:
			if plot.getTerrainType() == iOcean: return False
			if plot.getFeatureType() == iJungle: return False
		
		# restrict to borders if specified
		if bBorder and not [(i, j) for (i, j) in lSurrounding if gc.getMap().plot(i, j).getOwner() != plot.getOwner()]: return False
		
		# near a city if specified (next to cities excluded above)
		if bNearCity and not [(i, j) for (i, j) in utils.surroundingPlots(tPlot, 2, lambda (a, b): not gc.getMap().plot(a, b).isCity())]: return False
		
		# not on landmasses without cities
		if not bWater and gc.getMap().getArea(plot.getArea()).getNumCities() == 0: return False
		
		return True

	def spawnPirates(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj=""):
		'''Leoreth: spawns all ships at the same coastal spot, out to pillage and disrupt trade, can spawn inside borders'''
		
		lPlots = self.possibleTiles(tTL, tBR, bWater=True, bTerritory=False)
		tPlot = utils.getRandomEntry(lPlots)
		
		if tPlot:
			utils.makeUnitAI(iUnitType, iPlayer, tPlot, UnitAITypes.UNITAI_PIRATE_SEA, iNumUnits, sAdj)
		
	def spawnNatives(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj=""):
		'''Leoreth: outside of territory, in jungles, all dispersed on several plots, out to pillage'''
		
		lPlots = self.possibleTiles(tTL, tBR, bTerritory=False, bImpassable=True)
		
		for i in range(iNumUnits):
			tPlot = utils.getRandomEntry(lPlots)
			if not tPlot: break
			
			lPlots.remove(tPlot)
			utils.makeUnitAI(iUnitType, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK, 1, sAdj)
			
	def spawnMinors(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj=""):
		'''Leoreth: represents minor states without ingame cities
			    outside of territory, not in jungles, in groups, passive'''
			    
		lPlots = self.possibleTiles(tTL, tBR, bTerritory=False)
		tPlot = utils.getRandomEntry(lPlots)
		
		if tPlot:
			utils.makeUnitAI(iUnitType, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK, iNumUnits, sAdj)
		
	def spawnNomads(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj=""):
		'''Leoreth: represents aggressive steppe nomads etc.
			    outside of territory, not in jungles, in small groups, target cities'''
		
		lPlots = self.possibleTiles(tTL, tBR, bTerritory=False)
		tPlot = utils.getRandomEntry(lPlots)
		
		if tPlot:
			utils.makeUnitAI(iUnitType, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK, iNumUnits, sAdj)
			
	def spawnInvaders(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj=""):
		'''Leoreth: represents large invasion forces and migration movements
			    inside of territory, not in jungles, in groups, target cities'''
			    
		lPlots = self.possibleTiles(tTL, tBR, bTerritory=True, bBorder=True)
		tPlot = utils.getRandomEntry(lPlots)
		
		if tPlot:
			utils.makeUnitAI(iUnitType, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK, iNumUnits, sAdj)
			
	def spawnUprising(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj=""):
		''' Leoreth: represents uprisings of Natives against colonial settlements, especially North America
			     spawns units in a free plot in the second ring of a random target city in the area
			     (also used for units from warring city states in classical Mesoamerica)'''
		
		lPlots = self.possibleTiles(tTL, tBR, bTerritory=True, bNearCity=True)
		tPlot = utils.getRandomEntry(lPlots)
		
		if tPlot:
			utils.makeUnitAI(iUnitType, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK, iNumUnits, sAdj)
			
	def includesActiveHuman(self, lPlayers):
		return utils.getHumanID() in lPlayers and tBirth[utils.getHumanID()] <= gc.getGame().getGameTurnYear()

	def spawnBears(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj=""):
		''' 1SDAN: inside territory, dispersed over several plots, attacking'''
		lPlots = self.possibleTiles(tTL, tBR, bTerritory=True, bNearCity=True)

		for i in range(iNumUnits):
			tPlot = utils.getRandomEntry(lPlots)
			if not tPlot: break

			lPlots.remove(tPlot)
			utils.makeUnitAI(iUnitType, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK, 1, sAdj)

	def spawnRabbits(self, iPlayer, iUnitType, iNumUnits, tTL, tBR, sAdj=""):
		''' Merijn: inside territory, dispersed over several plots, pillaging'''
		lPlots = self.possibleTiles(tTL, tBR, bTerritory=True, bNearCity=True)
		
		for i in range(iNumUnits):
			tPlot = utils.getRandomEntry(lPlots)
			if not tPlot: break
			
			lPlots.remove(tPlot)
			utils.makeUnitAI(iUnitType, iPlayer, tPlot, UnitAITypes.UNITAI_PILLAGE, 1, sAdj)