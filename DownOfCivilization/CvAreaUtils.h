// CvAreaUtils.h
#pragma once
#ifndef _CvAreaUtils_h_
#define _CvAreaUtils_h_

#include "config_pymodules.h"
#include "config_py2cpp.h"

// Forward Declare
class CvPlot;


typedef struct CvRectangle {
	coord m_tBL;
	coord m_tTR;
	
	CvRectangle() {}
	CvRectangle(coord tBL, coord tTR) :
		m_tBL(tBL), m_tTR(tTR)
	{
	}
	
	CvRectangle(int left, int bottom, int right, int top) {
		m_tBL.first = left;
		m_tBL.second = bottom;
		m_tTR.first = right;
		m_tTR.second = top;
	}
	
	int left() { return m_tBL.first; }
	int bottom() { return m_tBL.second; }
	int right() { return m_tTR.first; }
	int top() { return m_tTR.second; }
	
	CvRectangle& operator=(const CvRectangle& rhs) {
		this->m_tBL = rhs.m_tBL;
		this->m_tTR = rhs.m_tTR;
		return *this;
	}		
} CvRectangle;

class CvAreaUtils
{
public:
	static CvAreaUtils& getInstance() {
		static CvAreaUtils m_Instance;
		return m_Instance;
	}
	
public:
	bool isReborn(PlayerTypes iPlayer);
	
	void CvAreaUtils::getOrElse(std::map<PlayerTypes, 
		std::vector<coord  > >& dDictionary, 
		PlayerTypes key, 
		std::vector<coord >& defaultVal, 
		std::vector<coord >& retVal);
	
	void getArea(PlayerTypes iPlayer, 
		CvRectangle& tRectangle, 
		std::map<PlayerTypes, std::vector<coord > >& dExceptions, 
		std::vector<coord >& tRet, 
		boost::tribool bReborn = None, 
		std::map<PlayerTypes, CvRectangle> dChangedRectangle = std::map<PlayerTypes, CvRectangle>(), 
		std::map<PlayerTypes, std::vector<coord > > dChangedExceptions = std::map<PlayerTypes, std::vector<coord > >());

	CvPlot* getCapital(PlayerTypes iPlayer, boost::tribool bReborn = None);
	CvPlot* getRespawnCapital(PlayerTypes iPlayer, boost::tribool bReborn = None);
	CvPlot* getNewCapital(PlayerTypes iPlayer, boost::tribool bReborn = None);
	
	void getBirthArea(PlayerTypes iPlayer, std::vector<coord >& tRet);
	void getBirthRectangle(PlayerTypes iPlayer, CvRectangle& birthRectangle,boost::tribool bExtended = None);
	void getBirthExceptions(PlayerTypes iPlayer, std::vector<coord >& tRet);
	
	void getCoreArea(PlayerTypes iPlayer, std::vector<coord >& tRet, boost::tribool bReborn = None);
	void getNormalArea(PlayerTypes iPlayer, std::vector<coord >& tRet, boost::tribool bReborn = None);
	void getBroaderArea(PlayerTypes iPlayer, std::vector<coord >& tRet, boost::tribool bReborn = None);
	void getRespawnArea(PlayerTypes iPlayer, std::vector<coord >& tRet);
	void getRebirthArea(PlayerTypes iPlayer, std::vector<coord >& tRet);
	
	void updateCore(PlayerTypes iPlayer);
	bool isForeignCore(PlayerTypes iPlayer, CvPlot* pPlot);
	bool isExtendedBirth(PlayerTypes iPlayer);
	void init(); // 什么时候调用？
	
public:
	std::vector<coord >								m_lPeakExceptions;
	
	// ### Capitals ###
	std::vector< coord >   							m_tCapitals;
	std::map<PlayerTypes, coord > 					m_dChangedCapitals;
	std::map<PlayerTypes, coord >					m_dNewCapitals;
	std::map<PlayerTypes, coord >					m_dRespawnCapitals;
	
	// ### Birth Area ###	
	std::vector<CvRectangle>						m_tBirthArea;
	std::map<PlayerTypes, CvRectangle>				m_dChangedBirthArea;
	std::map<PlayerTypes, std::vector<coord > >		m_dBirthAreaExceptions;
	
	// ### Core Area ###	
	std::vector<CvRectangle> 						m_tCoreArea;
	std::map<PlayerTypes, CvRectangle> 				m_dChangedCoreArea;
	std::map<PlayerTypes, std::vector<coord > >		m_dCoreAreaExceptions;
	std::map<PlayerTypes, std::vector<coord > >		m_dChangedCoreAreaExceptions;
	
	// ### Normal Area ###				
	std::vector<CvRectangle> 						m_tNormalArea;	
	std::map<PlayerTypes, CvRectangle> 				m_dChangedNormalArea;
	std::map<PlayerTypes, std::vector<coord > >		m_dNormalAreaExceptions;
	std::map<PlayerTypes, std::vector<coord > >		m_dChangedNormalAreaExceptions;
	
	// ### Broader Area ###		
	std::vector<CvRectangle> 						m_tBroaderArea;
	std::map<PlayerTypes, CvRectangle> 				m_dChangedBroaderArea;	
	
	// ### Respawn area ###	
	std::map<PlayerTypes, CvRectangle> 				m_dRespawnArea;	
	std::map<PlayerTypes, std::vector<coord > > 	m_dRespawnAreaExceptions;
	
	// ### Rebirth area ###	
	std::map<PlayerTypes, coord >					m_dRebirthPlot;
	std::map<PlayerTypes, CvRectangle>				m_dRebirthArea;
	std::map<PlayerTypes, std::vector<coord > >		m_dRebirthAreaExceptions;
private:
	CvAreaUtils();
};

#define Areas	CvAreaUtils::getInstance()

#endif
