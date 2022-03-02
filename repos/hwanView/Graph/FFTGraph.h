#pragma once

#include <list>
#include "2DGraph.h"
#define INDEX_32 512
#define INDEX_4 64
#define AMPMAX 46340		// short �ִ� 32768*��Ʈ2
#define GRAPH_X 512
#define GRAPH_Y 200
class CFFTGraph : public C2DGraph
{
protected:

public:
	CFFTGraph(CDC* pDC, int windowW, int windowH, int GraphHeightMin = 0, int GraphHeightMax = AMPMAX, int GraphWidthMin = 0, int GraphWidthMax = INDEX_32);
	~CFFTGraph();
	
	void Init();
	void Clear();
	void SetGraphPixel(int x, int y);
	void Plot(unsigned short* fftData);
	void Update();

	double m_CurrentData[INDEX_32];
	double m_CurrentGraphData[2][INDEX_32+1];		// �׷��� �̻ڰ� �ϱ����� �۾� - ������ ������ 512,0 �߰�
};

