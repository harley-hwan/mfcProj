#pragma once

#include <list>

#define SPECTROGRAM_X 260
#define INDEX_32 512
#define INDEX_4 64
#define AMPMAX 46340		// short �ִ� 32768*��Ʈ2

class CSpectrogram : public CWnd
{
protected:

public:
	CSpectrogram(CDC* pDC);
	~CSpectrogram();
	
	void SetGraphPixel(int x, int y);
	void Clear();
	void PlotGraph(unsigned short* Data);		// �޸�DC�� �켱 �׸�
	void PlotGraph(unsigned short* Data, int Ballindex);		// �޸�DC�� �켱 �׸�
	void DrawGraphOffScreen();	// ������ �׷����� �׸� (OnPaint)
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
	CRect m_WindowRect;			// ���� �׷��� ũ��
	int m_nMinRefColor;
	int m_nMaxRefColor;
	
	COLORREF m_aColorREF[255+1];	// ���� �Ѿ�� black����
	CDC m_dcMem;
	CDC* m_pDC;
	CBitmap* m_pOldBitmap;

	bool m_bIs4ms;
};

