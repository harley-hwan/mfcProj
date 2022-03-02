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
	//	ReleaseDC(&m_dcMem);				// �����߻� - �̹� �����ȵ�?
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
	else
	{
		for (int i = 0; i < DATA_MAX - 1; ++i)					//PushBack
		{
			m_aCurrentPhase[i] = m_aCurrentPhase[i+ 1];
			m_aCurrentPhaseRevision[i] = m_aCurrentPhaseRevision[i + 1];	
		}
		
		m_aCurrentPhase[DATA_MAX-1] = phase;
		for (int j = 0; j < AVRNUM; ++j)
			m_aCurrentPhaseRevision[DATA_MAX-1] += m_aCurrentPhase[m_nDataCnt - j];
		m_aCurrentPhaseRevision[DATA_MAX-1] /= AVRNUM;
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
	else
	{
		for (int i = 0; i < DATA_MAX - 1; ++i)					//PushBack
		{
			m_aCurrentPhase[i] = m_aCurrentPhase[i + 1];
			m_aCurrentPhaseRevision[i] = m_aCurrentPhaseRevision[i + 1];
		}

		m_aCurrentPhase[DATA_MAX - 1] = phase1;
		m_aCurrentPhaseRevision[DATA_MAX - 1] = phase2;
	}
	Update();
}

void CPhaseGraph::Update()
{
	PlotXY(m_aCurrentX, m_aCurrentPhase, m_aCurrentX, m_aCurrentPhaseRevision, m_nDataCnt);
}