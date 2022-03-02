#include "stdafx.h"
#include "DistanceGraph.h"

CDistanceGraph::CDistanceGraph(CDC* pDC, int windowW, int windowH)
{
	Clear();
	SetProperty(pDC, windowW, windowH, 2, 10, 4, GRAPH_X, GRAPH_Y, 30, false);
}

CDistanceGraph::~CDistanceGraph()
{
	//if(m_dcMem)
	//	ReleaseDC(&m_dcMem);				// 에러발생 - 이미 해제된듯?
}

void CDistanceGraph::Clear()
{
	memset(m_aCurrentXY, 0, sizeof(double) * 2 * DATA_MAX);
	memset(m_aCurrentXYrevision, 0, sizeof(double) * 2 * DATA_MAX);
	m_nDataCnt = 0;
}

void CDistanceGraph::Plot(float x,float y)
{	
	if (x *y != 0)
	{
		m_aCurrentXY[0][m_nDataCnt] = x;
		m_aCurrentXY[1][m_nDataCnt] = y;

		if (AVRNUM - 1 <= m_nDataCnt)
		{
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < AVRNUM; ++j)
					m_aCurrentXYrevision[i][m_nDataCnt] += m_aCurrentXY[i][m_nDataCnt - j];
				m_aCurrentXYrevision[i][m_nDataCnt] /= AVRNUM;
			}
		}
		else
		{
			m_aCurrentXYrevision[0][m_nDataCnt] = x;
			m_aCurrentXYrevision[1][m_nDataCnt] = y;
		}
		m_nDataCnt++;
		Update();
	}
}

void CDistanceGraph::Update()
{
	//PlotXY(m_aCurrentXY[0], m_aCurrentXY[1], m_aCurrentXYrevision[0], m_aCurrentXYrevision[1], m_nDataCnt);
	PlotXY(m_aCurrentXY[0], m_aCurrentXY[1], m_nDataCnt);
}