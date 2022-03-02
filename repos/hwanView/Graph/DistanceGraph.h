#pragma once

#include <list>
#include "2DGraph.h"
#define GRAPH_X 200
#define GRAPH_Y 100
#define DATA_MAX 500		// xyz 데이터 최대 개수
#define AVRNUM 20

class CDistanceGraph : public C2DGraph
{
public:
	CDistanceGraph(CDC* pDC, int windowW, int windowH);
	~CDistanceGraph();
	
	void Clear();
	void Plot(float x, float y);
	void Update();
public:
	int m_nDataCnt;
private:
	double m_aCurrentXY[2][DATA_MAX];
	double m_aCurrentXYrevision[2][DATA_MAX];
};

