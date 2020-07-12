# Rhye's and Fall of Civilization - AI Wars

from CvPythonExtensions import *
import CvUtil
import PyHelpers	# LOQ
import Popup
#import cPickle as pickle
from Consts import *
import Areas
import Resources
from RFCUtils import utils
import UniquePowers
from StoredData import data # edead
import Stability as sta

# globals
gc = CyGlobalContext()
PyPlayer = PyHelpers.PyPlayer	# LOQ
up = UniquePowers.UniquePowers()

### Constants ###


iMinIntervalEarly = 10
iMaxIntervalEarly = 20
iMinIntervalLate = 40
iMaxIntervalLate = 60
iThreshold = 100
iMinValue = 30

iRomeCarthageYear = -220
tRomeCarthageTL = (61, 45)
tRomeCarthageBR = (71, 49)

iRomeGreeceYear = -150
tRomeGreeceTL = (74, 50)
tRomeGreeceBR = (81, 55)

iRomeMesopotamiaYear = -100
tRomeMesopotamiaTL = (82, 44)
tRomeMesopotamiaBR = (91, 55)

iRomeAnatoliaYear = -100
tRomeAnatoliaTL = (82, 44)
tRomeAnatoliaBR = (86, 55)

iRomeCeltiaYear = -50
tRomeCeltiaTL = (57, 53)
tRomeCeltiaBR = (68, 62)

iRomeEgyptYear = 0
tRomeEgyptTL = (75, 38)
tRomeEgyptBR = (82, 45)

# following setup: iPlayer, iPreferredTarget, TL, BR, iNumTargets, iStartYear, iTurnInterval
tConquestRomeCarthage = (0, iRome, iCarthage, tRomeCarthageTL, tRomeCarthageBR, 3, iRomeCarthageYear, 10)
tConquestRomeGreece = (1, iRome, iGreece, tRomeGreeceTL, tRomeGreeceBR, 3, iRomeGreeceYear, 10)
tConquestRomeAnatolia = (2, iRome, iGreece, tRomeAnatoliaTL, tRomeAnatoliaBR, 5, iRomeAnatoliaYear, 10)
tConquestRomeCelts = (3, iRome, iCeltia, tRomeCeltiaTL, tRomeCeltiaBR, 5, iRomeCeltiaYear, 10)
tConquestRomeEgypt = (4, iRome, iEgypt, tRomeEgyptTL, tRomeEgyptBR, 4, iRomeEgyptYear, 10)

iAlexanderYear = -340
tGreeceMesopotamiaTL = (82, 44)
tGreeceMesopotamiaBR = (91, 55)
tGreeceEgyptTL = (75, 38)
tGreeceEgyptBR = (82, 45)
tGreecePersiaTL = (92, 43)
tGreecePersiaBR = (98, 51)

tConquestGreeceMesopotamia = (5, iGreece, iBabylonia, tGreeceMesopotamiaTL, tGreeceMesopotamiaBR, 6, iAlexanderYear, 20)
tConquestGreeceEgypt = (6, iGreece, iEgypt, tGreeceEgyptTL, tGreeceEgyptBR, 4, iAlexanderYear, 20)
tConquestGreecePersia = (7, iGreece, iPersia, tGreecePersiaTL, tGreecePersiaBR, 5, iAlexanderYear, 20)

iCholaSumatraYear = 1030
tCholaSumatraTL = (117, 26)
tCholaSumatraBR = (121, 29)

tConquestCholaSumatra = (8, iTamils, iIndonesia, tCholaSumatraTL, tCholaSumatraBR, 1, iCholaSumatraYear, 10)

iChinaVietnamYear1 = 50
iChinaVietnamYear2 = 1400
tChinaVietnamTL = (120, 40)
tChinaVietnamBR = (125, 44)

tConquestChinaVietnam1 = (9, iChina, iVietnam, tChinaVietnamTL, tChinaVietnamBR, 1, iChinaVietnamYear1, 10)
tConquestChinaVietnam2 = (10, iChina, iVietnam, tChinaVietnamTL, tChinaVietnamBR, 1, iChinaVietnamYear2, 10)

iSpainMoorsYear = 1180
tSpainMoorsTL = (56, 48)
tSpainMoorsBR = (61, 50)

iSpainIncaYear = 1520
tSpainIncaTL = (31, 21)
tSpainIncaBR = (32, 25)

iSpainTiwanakuYear = 1520
tSpainTiwanakuTL = (31, 19)
tSpainTiwanakuBR = (35, 22)

iSpainMayaYear = 1520
tSpainMayaTL = (16, 42)
tSpainMayaBR = (18, 44)

tConquestSpainMoors = (11, iSpain, iMoors, tSpainMoorsTL, tSpainMoorsBR, 1, iSpainMoorsYear, 10)
tConquestSpainInca = (12, iSpain, iInca, tSpainIncaTL, tSpainIncaBR, 1, iSpainIncaYear, 10)
tConquestSpainTiwanaku = (13, iSpain, iTiwanaku, tSpainTiwanakuTL, tSpainTiwanakuBR, 1, iSpainTiwanakuYear, 10)
tConquestSpainMaya = (14, iSpain, iMaya, tSpainMayaTL, tSpainMayaBR, 1, iSpainMayaYear, 10)

iTurksPersiaYear = 1000
tTurksPersiaTL = (91, 43)
tTurksPersiaBR = (98, 51)

iTurksAnatoliaYear = 1030
tTurksAnatoliaTL = (82, 51)
tTurksAnatoliaBR = (87, 55)

tConquestTurksPersia = (15, iTurks, iArabia, tTurksPersiaTL, tTurksPersiaBR, 4, iTurksPersiaYear, 20)
tConquestTurksAnatolia = (16, iTurks, iByzantium, tTurksAnatoliaTL, tTurksAnatoliaBR, 5, iTurksAnatoliaYear, 20)


iMongolsTurksYear = 1210
tMongolsTurksTL = (96, 52)
tMongolsTurksBR = (109, 59)

iMongolsPersiaYear = 1220
tMongolsPersiaTL = (87, 45)
tMongolsPersiaBR = (98, 50)

tConquestMongolsTurks = (17, iMongolia, iTurks, tMongolsTurksTL, tMongolsTurksBR, 10, iMongolsTurksYear, 10)
tConquestMongolsPersia = (18, iMongolia, iTurks, tMongolsPersiaTL, tMongolsPersiaBR, 10, iMongolsPersiaYear, 10)


iRussiaNovgorodYear = 1480
tRussiaNovgorodTL = (80, 66)
tRussiaNovgorodBR = (84, 70)

iRussiaTatarYear = 1500
tRussiaTatarTL = (79, 59)
tRussiaTatarBR = (95, 70)

tConquestRussiaNovgorod = (19, iRussia, iNovgorod, tRussiaNovgorodTL, tRussiaNovgorodBR, 1, iRussiaNovgorodYear, 10)
tConquestRussiaTatar = (20, iRussia, iTatar, tRussiaTatarTL, tRussiaTatarBR, 5, iRussiaTatarYear, 10)

iTatarKievanRusYear = 1220
tTatarKievanRusTL = (79, 59)
tTatarKievanRusBR = (83, 62)

tConquestTatarKievanRus = (21, iTatar, iKievanRus, tTatarKievanRusTL, tTatarKievanRusBR, 1, iTatarKievanRusYear, 10)


iYuezhiTurkestanYear = 30
tYuezhiTurkestanTL = (99, 48)
tYuezhiTurkestanBR = (102, 55)

tConquestYuezhiTurkestan = (22, iYuezhi, iPersia, tYuezhiTurkestanTL, tYuezhiTurkestanBR, 3, iYuezhiTurkestanYear, 10)

iConquestEnglandIrelandYear = 1150
tConquestEnglandIrelandTL = (52, 64)
tConquestEnglandIrelandBR = (59, 71)

tConquestEnglandIreland = (23, iEngland, iCeltia, tConquestEnglandIrelandTL, tConquestEnglandIrelandBR, 2, iConquestEnglandIrelandYear, 10)




lConquests = [
tConquestRomeCarthage, #0
tConquestRomeGreece, #1
tConquestRomeAnatolia, #2
tConquestRomeCelts, #3
tConquestRomeEgypt, #4
tConquestGreeceMesopotamia, #5
tConquestGreeceEgypt, #6
tConquestGreecePersia, #7
tConquestCholaSumatra, #8
tConquestChinaVietnam1, #9
tConquestChinaVietnam2, #10
tConquestSpainMoors, #11
tConquestSpainInca, #16
tConquestSpainTiwanaku, #17
tConquestSpainMaya, #18
tConquestTurksPersia, #12
tConquestTurksAnatolia, #13
tConquestMongolsTurks, #14
tConquestMongolsPersia, #15
tConquestRussiaNovgorod, #19
tConquestRussiaTatar, #20
tConquestTatarKievanRus, #21
tConquestYuezhiTurkestan, #22
tConquestEnglandIreland #23
]

class AIWars:


	def __init__(self, resources):
		self.res = resources

	def setup(self):
		iTurn = getTurnForYear(-600)
		if utils.getScenario() == i600AD:  #late start condition
			iTurn = getTurnForYear(900)
		elif utils.getScenario() == i1700AD:
			iTurn = getTurnForYear(1720)
		data.iNextTurnAIWar = iTurn + gc.getGame().getSorenRandNum(iMaxIntervalEarly-iMinIntervalEarly, 'random turn')


	def checkTurn(self, iGameTurn):

		#turn automatically peace on between independent cities and all the major civs
		if iGameTurn % 20 == 7:
			utils.restorePeaceHuman(iIndependent2, False)
		elif iGameTurn % 20 == 14:
			utils.restorePeaceHuman(iIndependent, False)
		if iGameTurn % 60 == 55 and iGameTurn > utils.getTurns(50):
			utils.restorePeaceAI(iIndependent, False)
		elif iGameTurn % 60 == 30 and iGameTurn > utils.getTurns(50):
			utils.restorePeaceAI(iIndependent2, False)
		#turn automatically war on between independent cities and some AI major civs
		if iGameTurn % 13 == 6 and iGameTurn > utils.getTurns(50): #1 turn after restorePeace()
			utils.minorWars(iIndependent)
		elif iGameTurn % 13 == 11 and iGameTurn > utils.getTurns(50): #1 turn after restorePeace()
			utils.minorWars(iIndependent2)
		if iGameTurn % 50 == 24 and iGameTurn > utils.getTurns(50):
			utils.minorWars(iCeltia)
			
		for tConquest in lConquests:
			self.checkConquest(tConquest)
		
		if iGameTurn == data.iNextTurnAIWar:
			self.planWars(iGameTurn)
			
		for iLoopPlayer in range(iNumPlayers):
			data.players[iLoopPlayer].iAggressionLevel = tAggressionLevel[iLoopPlayer] + gc.getGame().getSorenRandNum(2, "Random aggression")
			
	def checkConquest(self, tConquest, tPrereqConquest = (), iWarPlan = WarPlanTypes.WARPLAN_TOTAL):
		iID, iPlayer, iPreferredTarget, tTL, tBR, iNumTargets, iYear, iIntervalTurns = tConquest
	
		if utils.getHumanID() == iPlayer: return
		if not gc.getPlayer(iPlayer).isAlive() and iPlayer != iTurks: return
		if data.lConquest[iID]: return
		if iPreferredTarget >= 0 and gc.getPlayer(iPreferredTarget).isAlive() and gc.getTeam(iPreferredTarget).isVassal(iPlayer): return
		
		iGameTurn = gc.getGame().getGameTurn()
		iStartTurn = getTurnForYear(iYear) - 5 + (data.iSeed % 10)
		
		if iGameTurn <= getTurnForYear(tBirth[iPlayer])+3: return
		if not (iStartTurn <= iGameTurn <= iStartTurn + iIntervalTurns): return
		if tPrereqConquest and not self.isConquered(tPrereqConquest): return
		
		# Only Chinsesd conquerors for human Vietnam 1SDAN: Disabled
		# if iPreferredTarget == iVietnam and utils.getHumanID() != iVietnam: return
		
		self.spawnConquerors(iPlayer, iPreferredTarget, tTL, tBR, iNumTargets, iYear, iIntervalTurns, iWarPlan)
		data.lConquest[iID] = True
		
	def isConquered(self, tConquest):
		iID, iPlayer, iPreferredTarget, tTL, tBR, iNumTargets, iYear, iIntervalTurns = tConquest
	
		iNumMinorCities = 0
		lAreaCities = utils.getAreaCities(utils.getPlotList(tTL, tBR))
		for city in lAreaCities:
			if city.getOwner() in [iIndependent, iIndependent2, iBarbarian, iNative]: iNumMinorCities += 1
			elif city.getOwner() != iPlayer: return False
			
		if 2 * iNumMinorCities > len(lAreaCities): return False
		
		return True
		
	def declareWar(self, iPlayer, iTarget, iWarPlan):
		if gc.getTeam(iPlayer).isVassal(iTarget):
			gc.getTeam(iPlayer).setVassal(iTarget, False, False)
			
		gc.getTeam(iPlayer).declareWar(iTarget, True, iWarPlan)
			
	def spawnConquerors(self, iPlayer, iPreferredTarget, tTL, tBR, iNumTargets, iYear, iIntervalTurns, iWarPlan = WarPlanTypes.WARPLAN_TOTAL):
		if not gc.getPlayer(iPlayer).isAlive():
			for iTech in sta.getResurrectionTechs(iPlayer):
				gc.getTeam(gc.getPlayer(iPlayer).getTeam()).setHasTech(iTech, True, iPlayer, False, False)
	
		if iPlayer == iRome and iPreferredTarget == iCeltia:
			self.res.doRomanPigs()
			data.iRomanPigs = 0
		
		lCities = []
		for city in utils.getAreaCities(utils.getPlotList(tTL, tBR)):
			if city.getOwner() != iPlayer and not gc.getTeam(city.getOwner()).isVassal(iPlayer):
				lCities.append(city)
				
		capital = gc.getPlayer(iPlayer).getCapitalCity()
		
		lTargetCities = []
		for i in range(iNumTargets):
			if len(lCities) == 0: break
			
			targetCity = utils.getHighestEntry(lCities, lambda x: -utils.calculateDistance(x.getX(), x.getY(), capital.getX(), capital.getY()) + int(x.getOwner() == iPreferredTarget) * 1000)
			lTargetCities.append(targetCity)
			lCities.remove(targetCity)
			
		lOwners = []
		for city in lTargetCities:
			if city.getOwner() not in lOwners:
				lOwners.append(city.getOwner())
				
		if iPreferredTarget >= 0 and iPreferredTarget not in lOwners and gc.getPlayer(iPreferredTarget).isAlive():
			self.declareWar(iPlayer, iPreferredTarget, iWarPlan)
				
		for iOwner in lOwners:
			self.declareWar(iPlayer, iOwner, iWarPlan)
			CyInterface().addMessage(iOwner, False, iDuration, CyTranslator().getText("TXT_KEY_UP_CONQUESTS_TARGET", (gc.getPlayer(iPlayer).getCivilizationShortDescription(0),)), "", 0, "", ColorTypes(iWhite), -1, -1, True, True)
			
		for city in lTargetCities:
			iExtra = 0
			if utils.getHumanID() not in [iPlayer, city.getOwner()]: 
				iExtra += 1 #max(1, gc.getPlayer(iPlayer).getCurrentEra())
				
			if iPlayer == iMongolia and utils.getHumanID() != iPlayer:
				iExtra += 1
			
			tPlot = utils.findNearestLandPlot((city.getX(), city.getY()), iPlayer)
			
			iBestInfantry = utils.getBestInfantry(iPlayer)
			iBestSiege = utils.getBestSiege(iPlayer)

			if iPlayer == iEngland:
				iBestInfantry = iLongbowman

			
			if iPlayer == iGreece:
				iBestInfantry = iHoplite
				iBestSiege = iCatapult
			
			utils.makeUnitAI(iBestInfantry, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 2 + iExtra)
			utils.makeUnitAI(iBestSiege, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 1 + 2*iExtra)

			if iPlayer == iGreece:
				utils.makeUnitAI(iCompanion, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 1)
			
			if iPlayer == iTamils:
				utils.makeUnitAI(iWarElephant, iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 1)
				
			if iPlayer == iSpain:
				utils.makeUnitAI(utils.getBestCavalry(iPlayer), iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 2 * iExtra)
				
			if iPlayer == iTurks:
				utils.makeUnitAI(utils.getBestCavalry(iPlayer), iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 2 + iExtra)

			if iPlayer == iEngland:
				utils.makeUnitAI(utils.getBestCavalry(iPlayer), iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 2 * iExtra)

			if iPlayer == iRussia:
				utils.makeUnitAI(utils.getBestCavalry(iPlayer), iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 2 * iExtra)

			if iPlayer == iTatar:
				utils.makeUnitAI(utils.getBestCavalry(iPlayer), iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 2 * iExtra)

			if iPlayer == iYuezhi:
				utils.makeUnitAI(utils.getBestCavalry(iPlayer), iPlayer, tPlot, UnitAITypes.UNITAI_ATTACK_CITY, 2 + iExtra)
				
	def forgetMemory(self, iTech, iPlayer):
		if iTech in [iPsychology, iTelevision]:
			pPlayer = gc.getPlayer(iPlayer)
			for iLoopCiv in range(iNumPlayers):
				if iPlayer == iLoopCiv: continue
				if pPlayer.AI_getMemoryCount(iLoopCiv, MemoryTypes.MEMORY_DECLARED_WAR) > 0:
					pPlayer.AI_changeMemoryCount(iLoopCiv, MemoryTypes.MEMORY_DECLARED_WAR, -1)
				if pPlayer.AI_getMemoryCount(iLoopCiv, MemoryTypes.MEMORY_DECLARED_WAR_ON_FRIEND) > 0:
					pPlayer.AI_changeMemoryCount(iLoopCiv, MemoryTypes.MEMORY_DECLARED_WAR_ON_FRIEND, -1)
					
	def getNextInterval(self, iGameTurn):
		if iGameTurn > getTurnForYear(1600):
			iMinInterval = iMinIntervalLate
			iMaxInterval = iMaxIntervalLate
		else:
			iMinInterval = iMinIntervalEarly
			iMaxInterval = iMaxIntervalEarly
			
		iMinInterval = utils.getTurns(iMinInterval)
		iMaxInterval = utils.getTurns(iMaxInterval)
		
		return iMinInterval + gc.getGame().getSorenRandNum(iMaxInterval-iMinInterval, 'random turn')
					
	def planWars(self, iGameTurn):
	
		# skip if there is a world war
		if iGameTurn > getTurnForYear(1500):
			iCivsAtWar = 0
			for iLoopPlayer in range(iNumPlayers):
				tLoopPlayer = gc.getTeam(gc.getPlayer(iLoopPlayer).getTeam())
				if tLoopPlayer.getAtWarCount(True) > 0:
					iCivsAtWar += 1
			if 100 * iCivsAtWar / gc.getGame().countCivPlayersAlive() > 50:
				data.iNextTurnAIWar = iGameTurn + self.getNextInterval(iGameTurn)
				return
	
		iAttackingPlayer = self.determineAttackingPlayer()
		iTargetPlayer = self.determineTargetPlayer(iAttackingPlayer)
		
		data.players[iAttackingPlayer].iAggressionLevel = 0
		
		if iTargetPlayer == -1:
			return
			
		if gc.getTeam(iAttackingPlayer).canDeclareWar(iTargetPlayer):
			gc.getTeam(iAttackingPlayer).AI_setWarPlan(iTargetPlayer, WarPlanTypes.WARPLAN_PREPARING_LIMITED)
		
		data.iNextTurnAIWar = iGameTurn + self.getNextInterval(iGameTurn)
		
	def determineAttackingPlayer(self):
		lAggressionLevels = [data.players[i].iAggressionLevel for i in range(iNumPlayers) if self.possibleTargets(i)]
		iHighestEntry = utils.getHighestEntry(lAggressionLevels)
		
		return lAggressionLevels.index(iHighestEntry)
		
	def possibleTargets(self, iPlayer):
		return [iLoopPlayer for iLoopPlayer in range(iNumPlayers) if iPlayer != iLoopPlayer and gc.getTeam(gc.getPlayer(iPlayer).getTeam()).canDeclareWar(gc.getPlayer(iLoopPlayer).getTeam())]
		
	def determineTargetPlayer(self, iPlayer):
		pPlayer = gc.getPlayer(iPlayer)
		tPlayer = gc.getTeam(pPlayer.getTeam())
		lPotentialTargets = []
		lTargetValues = [0 for i in range(iNumPlayers)]

		# determine potential targets
		for iLoopPlayer in self.possibleTargets(iPlayer):
			pLoopPlayer = gc.getPlayer(iLoopPlayer)
			tLoopPlayer = gc.getTeam(pLoopPlayer.getTeam())
			
			if iLoopPlayer == iPlayer: continue
			
			# requires live civ and past contact
			if not pLoopPlayer.isAlive(): continue
			if not tPlayer.isHasMet(iLoopPlayer): continue
			
			# no masters or vassals
			if tPlayer.isVassal(iLoopPlayer): continue
			if tLoopPlayer.isVassal(iPlayer): continue
			
			# not already at war
			if tPlayer.isAtWar(iLoopPlayer): continue
			
			lPotentialTargets.append(iLoopPlayer)
			
		if not lPotentialTargets: return -1
			
		# iterate the map for all potential targets
		for i in range(iWorldX):
			for j in range(iWorldY):
				iOwner = gc.getMap().plot(i,j).getOwner()
				if iOwner in lPotentialTargets:
					lTargetValues[iOwner] += pPlayer.getWarValue(i, j)
					
		# hard to attack with lost contact
		for iLoopPlayer in lPotentialTargets:
			lTargetValues[iLoopPlayer] /= 8
			
		# normalization
		iMaxValue = utils.getHighestEntry(lTargetValues)
		if iMaxValue == 0: return -1
		
		for iLoopPlayer in lPotentialTargets:
			lTargetValues[iLoopPlayer] *= 500
			lTargetValues[iLoopPlayer] /= iMaxValue
			
		for iLoopPlayer in lPotentialTargets:
		
			# randomization
			if lTargetValues[iLoopPlayer] <= iThreshold:
				lTargetValues[iLoopPlayer] += gc.getGame().getSorenRandNum(100, 'random modifier')
			else:
				lTargetValues[iLoopPlayer] += gc.getGame().getSorenRandNum(300, 'random modifier')
			
			# balanced by attitude
			iAttitude = pPlayer.AI_getAttitude(iLoopPlayer) - 2
			if iAttitude > 0:
				lTargetValues[iLoopPlayer] /= 2 * iAttitude
				
			# exploit plague
			if data.players[iLoopPlayer].iPlagueCountdown > 0 or data.players[iLoopPlayer].iPlagueCountdown < -10:
				if gc.getGame().getGameTurn() > getTurnForYear(tBirth[iLoopPlayer]) + utils.getTurns(20):
					lTargetValues[iLoopPlayer] *= 3
					lTargetValues[iLoopPlayer] /= 2
		
			# determine master
			iMaster = -1
			for iLoopMaster in range(iNumPlayers):
				if tLoopPlayer.isVassal(iLoopMaster):
					iMaster = iLoopMaster
					break
					
			# master attitudes
			if iMaster >= 0:
				iAttitude = gc.getPlayer(iMaster).AI_getAttitude(iLoopPlayer)
				if iAttitude > 0:
					lTargetValues[iLoopPlayer] /= 2 * iAttitude
			
			# peace counter
			if not tPlayer.isAtWar(iLoopPlayer):
				iCounter = min(7, max(1, tPlayer.AI_getAtPeaceCounter(iLoopPlayer)))
				if iCounter <= 7:
					lTargetValues[iLoopPlayer] *= 20 + 10 * iCounter
					lTargetValues[iLoopPlayer] /= 100
					
			# defensive pact
			if tPlayer.isDefensivePact(iLoopPlayer):
				lTargetValues[iLoopPlayer] /= 4
				
			# consider power
			iOurPower = tPlayer.getPower(True)
			iTheirPower = gc.getTeam(iLoopPlayer).getPower(True)
			if iOurPower > 2 * iTheirPower:
				lTargetValues[iLoopPlayer] *= 2
			elif 2 * iOurPower < iTheirPower:
				lTargetValues[iLoopPlayer] /= 2
				
			# spare smallish civs
			if iLoopPlayer in [iNetherlands, iPortugal, iItaly]:
				lTargetValues[iLoopPlayer] *= 4
				lTargetValues[iLoopPlayer] /= 5
				
			# no suicide
			if iPlayer == iNetherlands:
				if iLoopPlayer in [iFrance, iHolyRome, iGermany]:
					lTargetValues[iLoopPlayer] /= 2
			elif iPlayer == iPortugal:
				if iLoopPlayer == iSpain:
					lTargetValues[iLoopPlayer] /= 2
			elif iPlayer == iItaly:
				if iLoopPlayer in [iFrance, iHolyRome, iGermany]:
					lTargetValues[iLoopPlayer] /= 2
					
		return utils.getHighestIndex(lTargetValues)