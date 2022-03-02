#include "stdafx.h"
#include "FFTGraph.h"

CFFTGraph::CFFTGraph(CDC* pDC, int windowW, int windowH, int GraphHeightMin /* = 0 */, int GraphHeightMax /* = AMPMAX */, int GraphWidthMin /* = 0 */, int GraphWidthMax /* = INDEX_32 */)
{
	Init();
	Clear();
	SetProperty(pDC, windowW, windowH, 3, 8, 10, GRAPH_X, GRAPH_Y, 50, true);
}

CFFTGraph::~CFFTGraph()
{
	//if(m_dcMem)
	//	ReleaseDC(&m_dcMem);				// 에러발생 - 이미 해제된듯?
}

void CFFTGraph::Init()
{
	m_CurrentGraphData[0][INDEX_32 + 1] = INDEX_32 + 1;
	m_CurrentGraphData[1][INDEX_32 + 1] = 0;
}

void CFFTGraph::Clear()
{
	memset(m_CurrentData, 0, sizeof(double)*INDEX_32);
	memset(m_CurrentGraphData[1], 0, sizeof(double)*INDEX_32);
}

void CFFTGraph::SetGraphPixel(int x, int y)
{
	m_WindowRect.left = m_nGraphAxisY_width;
	m_WindowRect.right = x;
	m_WindowRect.top = 0;
	m_WindowRect.bottom = y - m_nGraphAxisX_height;

	SetGraphAxisX();
	SetGraphAxisY();
}


void CFFTGraph::Plot(unsigned short* fftData)
{
	for (int i = 0; i<INDEX_32; ++i)						// 현재 FFT 데이터는 들고 있어야 그래프 범위 변경에 따른 재구성 가능
		m_CurrentData[i] = fftData[i];

	Update();
}

void CFFTGraph::Update()
{
	memset(m_CurrentGraphData, 0, sizeof(double)*INDEX_32 * 2);
	int cnt = 0;

	for (int i = m_DynamicRect.left; i < m_DynamicRect.right + 1; ++i, ++cnt)
	{
		m_CurrentGraphData[0][cnt] = cnt;
		if(i != INDEX_32+1)
		m_CurrentGraphData[1][cnt] = m_CurrentData[i];
	}
	PlotXY(m_CurrentGraphData[0], m_CurrentGraphData[1], cnt);
}