#include "stdafx.h"
#include "PhaseGraph.h"

CPhaseGraph::CPhaseGraph(CDC* pDC, int windowW, int windowH)
{
	Clear();
	SetProperty(pDC, windowW, windowH, 2, 10, 4, GRAPH_X, GRAPH_Y, 40, false);
	for (int i = 0; i < DATA_MAX; ++i)
		m_aCurrentX[i] = i;
}

CPhaseGraph::~CPhaseGraph()
{
	//if(m_dcMem)
	//	ReleaseDC(&m_dcMem);				// 에러발생 - 이미 해제된듯?
}

void CPhaseGraph::Clear()
{
	memset(m_aCurrentPhase, 0, sizeof(double) * DATA_MAX);
	memset(m_aCurrentPhaseRevision, 0, sizeof(double) * DATA_MAX);
	m_nDataCnt = 0;
}

void CPhaseGraph::Plot(float phase)
{	
	if (m_nDataCnt < DATA_MAX)
	{
		m_aCurrentPhase[m_nDataCnt] = phase;

		if (AVRNUM - 1 <= m_nDataCnt)
		{
			for (int j = 0; j < AVRNUM; ++j)
				m_aCurrentPhaseRevision[m_nDataCnt] += m_aCurrentPhase[m_nDataCnt - j];
			m_aCurrentPhaseRevision[m_nDataCnt] /= AVRNUM;
		}
		else
		{
			m_aCurrentPhaseRevision[m_nDataCnt] = phase;
		}
		m_nDataCnt++;
	}

	Update();
}

void CPhaseGraph::Plot(float phase1, float phase2)
{
	if (m_nDataCnt < DATA_MAX)
	{
		m_aCurrentPhase[m_nDataCnt] = phase1;
		m_aCurrentPhaseRevision[m_nDataCnt] = phase2;
		m_nDataCnt++;
	}
	
	Update();
}

void CPhaseGraph::Update()
{
	int cnt = 0;

	for (int i = m_DynamicRect.left; i < m_DynamicRect.right + 1; ++i, ++cnt)
	{
		if (i != DATA_MAX + 1)
		{
			m_CurrentGraphData[0][cnt] = m_aCurrentPhase[i];
			m_CurrentGraphData[1][cnt] = m_aCurrentPhaseRevision[i];
		}
	}
	//PlotXY(m_aCurrentX, m_aCurrentPhase, m_aCurrentX, m_aCurrentPhaseRevision, m_nDataCnt);
	PlotXY(m_aCurrentX, m_CurrentGraphData[0], m_aCurrentX, m_CurrentGraphData[1], m_nDataCnt);
}