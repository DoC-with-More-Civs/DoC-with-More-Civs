#pragma once

//  $Header:
//------------------------------------------------------------------------------------------------
//
//  FILE:    CvPropertySolver.h
//
//  PURPOSE: Singleton class for solving the system of property manipulators
//
//------------------------------------------------------------------------------------------------
#ifndef CV_PROPERTY_SOLVER_H
#define CV_PROPERTY_SOLVER_H

#include <vector>
#include <map>
#include "CvProperties.h"
//#include "CvPropertySource.h"
//#include "CvPropertyInteraction.h"
#include "CvPropertyPropagator.h"

#define BOOST_THREAD_NO_LIB
#define BOOST_THREAD_USE_LIB
#include <boost/thread/thread.hpp>

class CvPropertySource;
class CvPropertySolver;
class CvPropertyInteraction;
class CvMainPropertySolver;
class CvPropertyManipulators;

typedef std::map<CvGameObject*, CvProperties> PropertySolverMapType;

class PropertySolverMap
{
public:
	int getPredictValue(CvGameObject* pObject, PropertyTypes eProperty);
	void addChange(CvGameObject* pObject, PropertyTypes eProperty, int iChange, int iThread);

	void computePredictValues();
	void applyChanges();

protected:
	PropertySolverMapType m_mapProperties;
	PropertySolverMapType m_mapPropertyChanges[NUM_THREADS];
};

class PropertySourceContext
{
public:
	PropertySourceContext(CvPropertySource* pSource, CvGameObject* pObject);
	CvPropertySource* getSource();
	CvGameObject* getObject();
	int getData1();
	int getData2();
	void setData1(int iData);
	void setData2(int iData);

	void doPredict(CvPropertySolver* pSolver);
	void doCorrect(CvPropertySolver* pSolver);

protected:
	CvPropertySource*  m_pSource;
	CvGameObject* m_pObject;
	int m_iCurrentAmount;
	int m_iData1;
	int m_iData2;
};

class PropertyInteractionContext
{
public:
	PropertyInteractionContext(CvPropertyInteraction* pInteraction, CvGameObject* pObject);
	CvPropertyInteraction* getInteraction();
	CvGameObject* getGameObject();

	void doPredict(CvPropertySolver* pSolver);
	void doCorrect(CvPropertySolver* pSolver);

protected:
	CvPropertyInteraction* m_pInteraction;
	CvGameObject* m_pObject;
	int m_iCurrentAmountSource;
	int m_iCurrentAmountTarget;
};

class CvPropertySolver
{
public:
	void instantiateSource(CvGameObject* pObject, CvPropertySource* pSource);
	void instantiateInteraction(CvGameObject* pObject, CvPropertyInteraction* pInteraction);
	void instantiatePropagator(CvGameObject* pObject, CvPropertyPropagator* pPropagator);
	void instantiateManipulators(CvGameObject* pObject, CvPropertyManipulators* pMani);
	void instantiateGlobalManipulators(CvGameObject* pObject);
	void gatherActiveManipulators();
	void gatherActivemanipulatorsThreaded();

	void predictSources();
	void correctSources();
	void clearSources();

	void predictInteractions();
	void correctInteractions();
	void clearInteractions();

	void predictPropagators();
	void correctPropagators();
	void clearPropagators();

	void waitAndJoin();

	void resetPropertyChangesStart();
	void resetPropertyChanges();

	void gatherAndPredictStart();
	void gatherANdPredictThreaded();

	void correctStart();
	void correctThreaded();

	std::vector<int>& getCache1();
	std::vector<int>& getCache2();

	// passed on to the solver map
	void addChange(CvGameObject* pObject, PropertyTypes eProperty, int iChange);
	int getPredictValue(CvGameObject* pObject, PropertyTypes eProperty);

protected:
	std::vector<PropertySourceContext> m_aSourceContexts;
	std::vector<PropertyInteractionContext> m_aInteractionContexts;
	std::vector<PropertyPropagatorContext> m_aPropagatorContexts;
	CvMainPropertySolver* m_pManSolver;
	int m_iThread;
	boost::thread* m_thread;
	std::vector<int> m_aiCache1;
	std::vector<int> m_aiCache2;
};

class CvMainPropertySolver
{
public:
	CvMainPropertySolver();

	PropertySolverMap* getSolverMap();

	void addGlobalManipulators(CvPropertyManipulators* pMani);
	void gatherGlobalManipulators();
	int getNumGlobalManipulators();
	CvPropertyManipulators* getGlobalManipulator(int index);

	void resetPropertyChanges();
	void resetPropertyChangesThreaded();

	void gatherAndSolve();
	void gatherAndSovleThreaded();

	void doTurn();

protected:
	std::vector<CvPropertyManipulators*> m_apGlobalManipulators;
	CvPropertySolver m_Solvers[NUM_THREADS];
	PropertySolverMap m_mapProperties;
};

#endif