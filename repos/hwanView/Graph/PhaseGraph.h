#pragma once

#include <list>
#include "2DGraph.h"
#define GRAPH_X 200
#define GRAPH_Y 100
#define DATA_MAX 260		// SPECTROGRAM_X ¿Í °øÀ¯
#define AVRNUM 20

class CPhaseGraph : public C2DGraph
{
public:
	CPhaseGraph(CDC* pDC, int windowW, int windowH);
	~CPhaseGraph();
	
	void Clear();
	void Plot(float phase);
	void Plot(float phase1, float phase2);
	void Update();
public:
	int m_nDataCnt;
private:
	double m_aCurrentPhase[DATA_MAX];
	double m_aCurrentPhaseRevision[DATA_MAX];
	double m_aCurrentX[DATA_MAX];
	double m_CurrentGraphData[2][DATA_MAX];
	POINT m_cr;
};

