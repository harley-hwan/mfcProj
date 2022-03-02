#pragma once

#include <list>

class C2DGraph
{
public:
	C2DGraph();
	~C2DGraph();

	void SetProperty(CDC* pDC, int pixelW, int pixelH, int penWidth, int GridW, int GridH, int GraphPixelW, int GraphPixelH, int AxisWidth, bool);
	void SetAxisReverse(bool isreverse);
	void SetWindowPixel(int x, int y);
	void SetGraphPixel(int x, int y);
	void SetGridNumber(int numX, int numY);
	void SetWidth(int widthMin, int widthMax);
	void SetHeight(int heightMin, int heightMax);
	void SetPenWidth(int width);
	void SetGraphAxisX();
	void SetGraphAxisY();
	void PlotXY(double* x, double* y, int nCnt);		// 메모리DC에 우선 그림
	void PlotXY(double* x1, double* y1, double* x2, double* y2, int nCnt);
	void DrawGraphOffScreen();	// 실제로 그래프에 그림 (OnPaint)
	void DrawGraphOffScreen(CDC* pDC, CRect rectin, CRect rectout);
	void CreateMemDC(CDC* pdc);
	float Nomalization(int Min, int Max, float Value, int Scale);		// 값을 MinMax 대비 스케일로 정규화
	int RoundOff(float value);
	
	void DrawGraphAxis();
	void DrawFFTAxis();
	void DrawGraphGrid();

	virtual void Update() = 0;
//private:
	CPoint m_PixelMax;				// 그래프 최대 크기
	CRect m_DynamicRect;			// 동적 그래프 범위  
	CRect m_WindowRect;				// 실제 Window 크기
	int m_PenWidth;
	CDC m_dcMem;
	CDC* m_pDC;
	CBitmap* m_pOldBitmap;

	int m_nGraphAxisX_width;
	int m_nGraphAxisX_height;		// 20 : 글꼴 대략의 높이
	int m_nGraphAxisY_width;		// 50 : 5자릿수 커버	30 : 3자릿수 커버
	int m_nGraphAxisY_height;
	int m_nGridNumX;
	int m_nGridNumY;

	bool m_bGridOnoff;
	bool m_bIsFFT;
	float m_ScaleX;
	float m_ScaleY;
	bool m_bAxisReverse;
};

