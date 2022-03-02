#pragma once

#include <list>

#define SPECTROGRAM_X 260
#define INDEX_32 512
#define INDEX_4 64
#define AMPMAX 46340		// short 최댓값 32768*루트2

class CSpectrogram : public CWnd
{
protected:

public:
	CSpectrogram(CDC* pDC);
	~CSpectrogram();
	
	void SetGraphPixel(int x, int y);
	void Clear();
	void PlotGraph(unsigned short* Data);		// 메모리DC에 우선 그림
	void PlotGraph(unsigned short* Data, int Ballindex);		// 메모리DC에 우선 그림
	void DrawGraphOffScreen();	// 실제로 그래프에 그림 (OnPaint)
	void SetEditValue(unsigned short ampMin, unsigned short ampMax);
	void UpdateGraph(bool IsTrigger);

private:
	void CreateMemDC(CDC* pdc);
	bool MakeRefColors();
	COLORREF GetRefColor(unsigned short nValue);
	void ArrayPushBack(unsigned short* ampdata, int index, int cnt);

public:
	unsigned short m_nMinSpectrumDisplay;
	unsigned short m_nMaxSpectrumDisplay;
	unsigned short m_aCurrentAmp[SPECTROGRAM_X][INDEX_32];
	int m_aCurrentIndex[INDEX_32];
	POINT m_cr;

private:
	CRect m_WindowRect;			// 실제 그래프 크기
	int m_nMinRefColor;
	int m_nMaxRefColor;
	
	COLORREF m_aColorREF[255+1];	// 범위 넘어서면 black으로
	CDC m_dcMem;
	CDC* m_pDC;
	CBitmap* m_pOldBitmap;

	bool m_bIs4ms;
};

