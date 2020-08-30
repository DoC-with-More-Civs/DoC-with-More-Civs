//  $Header:
//------------------------------------------------------------------------------------------------
//
//  FILE:    CvGameObject.cpp
//
//  PURPOSE: Wrapper classes for Civ4 game objects
//
//------------------------------------------------------------------------------------------------

#include "CvGameCoreDLL.h"
#include "CvGameObject.h"
#include <boost/bind.hpp>
#include "CyGame.h"
#include "CyTeam.h"
#include "CyPlayer.h"
#include "CyUnit.h"
#include "CyPlot.h"
#include "CvGameAI.h"
#include "CvTeamAI.h"
#include "CvPlayerAI.h"
#include "CvCity.h"
#include "CvUnit.h"
#include "CvPlot.h"
#include "CvMap.h"
#include "CvGameCoreUtils.h"
#include "CvDLLPythonIFaceBase.h"

CvProperties * CvGameObjectGame::getProperties() const
{
	return GC.getGameINLINE().getProperties();
}

CvProperties * CvGameObjectGame::getPropertiesConst() const
{
	return GC.getGameINLINE().getPropertiesConst();
}

// helper function to call foreach on the object
void callForeach(CvGameObject* pObject, GameObjectTypes eType, boost::function<void(CvGameObject*)> func)
{
	pObject->foreach(eType, func);
}

void CvGameObjectGame::foreach(GameObjectTypes eType, boost::function<void(CvGameObject*)> func)
{
	switch (eType)
	{
	case GAMEOBJECT_TEAM:
		for (int iI = 0; iI < MAX_TEAMS; iI++)
		{
			if (GET_TEAM((TeamTypes)iI).isAlive())
			{
				func(GET_TEAM((TeamTypes)iI).getGameObject());
			}
		}
		break;
	case GAMEOBJECT_PLAYER:
		for (int iPlayer = 0; iPlayer < MAX_PLAYERS; ++iPlayer)
		{
			CvPlayer& kLoopPlayer = GET_PLAYER((PlayerTypes)iPlayer);
			if (kLoopPlayer.isAlive())
			{
				func(kLoopPlayer.getGameObject());
			}
		}
		break;
	case GAMEOBJECT_CITY:
		foreach(GAMEOBJECT_PLAYER, boost::bind(callForeach, _1, GAMEOBJECT_CITY, func));
		break;
	case GAMEOBJECT_UNIT:
		foreach(GAMEOBJECT_PLAYER, boost::bind(callForeach, _1, GAMEOBJECT_UNIT, func));
		break;
	case GAMEOBJECT_PLOT:
		for (int iI = 0; iI < GC.getMapINLINE().numPlotsINLINE(); iI++)
		{
			func(GC.getMapINLINE().plotByIndexINLINE(iI)->getGameObject());
		}
		break;
	case GAMEOBJECT_GAME:
		func(this);
		break;
	}
}

void CvGameObjectTeam::foreach(GameObjectTypes eType, boost::function<void(CvGameObject*)> func)
{
	switch (eType)
	{
	case GAMEOBJECT_GAME:
		func(GC.getGameINLINE().getGameObject());
		break;
	case GAMEOBJECT_PLAYER:
		for (intt iPlayer = 0; iPlayer < MAX_PLAYERS; ++iPlayer)
		{

		}
		break;
	}
}
