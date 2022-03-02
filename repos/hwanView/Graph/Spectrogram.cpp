#include "stdafx.h"
#include "Spectrogram.h"

CSpectrogram::CSpectrogram(CDC* pDC)
{
	SetGraphPixel(690,340);
	m_cr.x = 0;
	m_cr.y = 0;
	m_nMinRefColor = -128;
	m_nMaxRefColor = 127;
	m_nMinSpectrumDisplay = 0;
	m_nMaxSpectrumDisplay = 6000;
	m_pDC = pDC;

	CreateMemDC(pDC);
	MakeRefColors();
	memset(m_aCurrentAmp, 0, sizeof(short)*SPECTROGRAM_X*INDEX_32);
	memset(m_aCurrentIndex, 0, sizeof(int)*INDEX_32);
}

CSpectrogram::~CSpectrogram()
{
	//if(m_dcMem)
	//	ReleaseDC(&m_dcMem);				// 에러발생 - 이미 해제된듯?
}

void CSpectrogram::SetGraphPixel(int x, int y)
{
	m_WindowRect.left = 0;
	m_WindowRect.right = x;
	m_WindowRect.top = 0;
	m_WindowRect.bottom = y;
}

void CSpectrogram::Clear()
{
	m_cr.x = 0;
	m_cr.y = 0;
	memset(m_aCurrentAmp, 0, sizeof(short)*SPECTROGRAM_X*INDEX_32);
	memset(m_aCurrentIndex, 0, sizeof(int)*INDEX_32);

	CRect rect;
	rect.left = 0; rect.top = 0; rect.right = SPECTROGRAM_X; rect.bottom = INDEX_32;

	m_dcMem.FillSolidRect(rect, RGB(0, 0, 0));
}

void CSpectrogram::SetEditValue(unsigned short ampMin, unsigned short ampMax)
{
	m_nMinSpectrumDisplay = ampMin;
	m_nMaxSpectrumDisplay = ampMax;
}

void CSpectrogram::CreateMemDC(CDC* pdc)
{
	
	CBitmap bitOff;

	// Create a DC that is compatible with the screen.
	m_dcMem.CreateCompatibleDC(pdc);

	bitOff.CreateCompatibleBitmap(pdc, SPECTROGRAM_X, INDEX_32);			// 가상DC -> 1:1 픽셀로 비트맵 생성

																	// Select the bitmap into the memory DC.
	m_pOldBitmap = m_dcMem.SelectObject(&bitOff);
}


bool CSpectrogram::MakeRefColors()
{
	int nMinValue = m_nMinRefColor;
	int nMaxValue = m_nMaxRefColor;
	
	short Value[5] = { nMinValue, (nMaxValue - nMinValue) / 4 + nMinValue, (nMinValue + nMaxValue) / 2, (nMaxValue - nMinValue) / 4 * 3 + nMinValue, nMaxValue };

	float fR[5] = { 1, 1, 0, 0, 0 };
	float fG[5] = { 0, 1, 1, 1, 0 };
	float fB[5] = { 0, 0, 0, 1, 1 };
	float fResultR, fResultG, fResultB;
	int i, j;

	float fScale = 0.0f;
	float fFactor = 0.0f;
	short chR, chG, chB;
	COLORREF col;
	for (j = 0; j < 4; ++j)
	{
		fScale = 1.0f / (Value[j + 1] - Value[j]);
		fFactor = 0.0f;
		for (i = Value[j]; i < Value[j + 1]; ++i, fFactor += fScale)
		{
			fResultR = fR[j] * (1.0f - fFactor) + fR[j + 1] * fFactor;
			fResultG = fG[j] * (1.0f - fFactor) + fG[j + 1] * fFactor;
			fResultB = fB[j] * (1.0f - fFactor) + fB[j + 1] * fFactor;
			fResultR = fResultR < 0.0f ? 0.0f : (fResultR > 1.0f ? 1.0f : fResultR);
			fResultG = fResultG < 0.0f ? 0.0f : (fResultG > 1.0f ? 1.0f : fResultG);
			fResultB = fResultB < 0.0f ? 0.0f : (fResultB > 1.0f ? 1.0f : fResultB);
			chR = fResultR * 255.0f;
			chG = fResultG * 255.0f;
			chB = fResultB * 255.0f;
			col = RGB(chB, chG, chR);		//2017-11-21 이승훈 : R,B 순서 바꿈
			m_aColorREF[i + 128] = col;
		}
	}
	col = RGB(0, 0, 0);
	m_aColorREF[255] = col;		// 넘어선 범위 black 추가
	//CreateSpectrumBMPFile("Spectrum.bmp");
	return true;
}

void CSpectrogram::PlotGraph(unsigned short* Data)
{
	int Width = SPECTROGRAM_X;
	int Height = INDEX_32;
	int indexMax, Pixel_w, Pixel_h;
	indexMax = INDEX_32;

	if (Data[100] == 0 && Data[101] == 0 && Data[102] == 0)
	{
		indexMax = INDEX_4;
		m_bIs4ms = true;
	}
	else
		m_bIs4ms = false;

	Pixel_w = 1;
	Pixel_h = INDEX_32 / indexMax;
	
	ArrayPushBack(Data, -1, indexMax);						// 현재 그래프 상의 데이터 저장
	m_cr.y = Pixel_h;

	if (m_cr.x < Width)
	{
		for (int index = 0; index < indexMax; ++index)
		{
			COLORREF color = GetRefColor(Data[index]);
			m_dcMem.FillSolidRect(m_cr.x, Height - m_cr.y, Pixel_w, Pixel_h, color);
			m_cr.y += Pixel_h;
		}
		m_cr.x += Pixel_w;
		m_cr.y = Pixel_h;
		
	}
	else
	{
		m_dcMem.BitBlt(0, 0, Width - Pixel_w, Height, &m_dcMem, Pixel_w, 0, SRCCOPY);
		for (int index = 0; index < indexMax; ++index)
		{
			COLORREF color = GetRefColor(Data[index]);
			m_dcMem.FillSolidRect(m_cr.x - 2 * Pixel_w, Height - m_cr.y, Pixel_w, Pixel_h, color);
			m_cr.y += Pixel_h;
		}
		m_cr.y = Pixel_h;
	}
}

void CSpectrogram::PlotGraph(unsigned short* Data, int Ballindex)
{
	int Width = SPECTROGRAM_X;
	int Height = INDEX_32;
	int indexMax, Pixel_w, Pixel_h;
	indexMax = INDEX_32;

	if (Data[100] == 0 && Data[101] == 0 && Data[102] == 0)
	{
		indexMax = INDEX_4;
		m_bIs4ms = true;
	}
	else
		m_bIs4ms = false;

	Pixel_w = 1;
	Pixel_h = INDEX_32 / indexMax;

	ArrayPushBack(Data, Ballindex, indexMax);						// 현재 그래프 상의 데이터 저장
	m_cr.y = Pixel_h;

	if (m_cr.x < Width)
	{
		for (int index = 0; index < indexMax; ++index)
		{
			COLORREF color = GetRefColor(Data[index]);

			if(m_bIs4ms && index == Ballindex)
				color = RGB(255, 0, 255);
			if(!m_bIs4ms && Ballindex-2 <= index && index <= Ballindex + 2)
				color = RGB(255, 0, 255);
			m_dcMem.FillSolidRect(m_cr.x, Height - m_cr.y, Pixel_w, Pixel_h, color);
			m_cr.y += Pixel_h;
		}
		m_cr.x += Pixel_w;
		m_cr.y = Pixel_h;

	}
	else
	{
		m_dcMem.BitBlt(0, 0, Width - Pixel_w, Height, &m_dcMem, Pixel_w, 0, SRCCOPY);
		for (int index = 0; index < indexMax; ++index)
		{
			COLORREF color = GetRefColor(Data[index]);

			if (m_bIs4ms && index == Ballindex)
				color = RGB(255, 0, 255);
			if (!m_bIs4ms && Ballindex - 2 <= index && index <= Ballindex + 2)
				color = RGB(255, 0, 255);
			m_dcMem.FillSolidRect(m_cr.x - 2 * Pixel_w, Height - m_cr.y, Pixel_w, Pixel_h, color);
			m_cr.y += Pixel_h;
		}
		m_cr.y = Pixel_h;
	}
}


COLORREF CSpectrogram::GetRefColor(unsigned short nValue)
{
	COLORREF retColor = 0;

	//Spectrum 변화 
	//double dMul = (double)(m_nMaxRefColor - m_nMinRefColor) / (double)(e_nMaxAmplitude - e_nMinAmplitude);
	//double dColor = (nValue-e_nMinAmplitude) * dMul + m_nMinRefColor;
	double dMul = (double)(m_nMaxRefColor - m_nMinRefColor) / (double)(m_nMaxSpectrumDisplay - m_nMinSpectrumDisplay);
	double dColor = (nValue - m_nMinSpectrumDisplay) * dMul + m_nMinRefColor;
	short signedValue = dColor < m_nMinRefColor ? m_nMinRefColor : (dColor > m_nMaxRefColor ? m_nMaxRefColor : dColor);
	nValue = signedValue;

	retColor = m_aColorREF[(int)(signedValue + 128)];

	return retColor;
}

void CSpectrogram::DrawGraphOffScreen()				// 그래프를 그릴 DC와 DC의 크기
{
	if (m_dcMem)
	{
		//Blt the memory device context to the screen.
		m_pDC->StretchBlt(
			0,
			0,
			m_WindowRect.Width(),
			m_WindowRect.Height(),
			&m_dcMem,
			0,
			0,
			SPECTROGRAM_X,
			INDEX_32,
			SRCCOPY);
	}
}

void CSpectrogram::ArrayPushBack(unsigned short* ampdata, int index, int cnt)
{
	
	if (m_cr.x < SPECTROGRAM_X)		// 아직 끝까지 안채워짐 - 그냥 Push
	{
		for (int i = 0; i < cnt; ++i)
			m_aCurrentAmp[m_cr.x][i] = ampdata[i];
		m_aCurrentIndex[m_cr.x] = index;
	}
	else											// LIFO - Last In First Out
	{
		for(int i = 0; i < SPECTROGRAM_X -1; ++i)
		{
			for (int j = 0; j < INDEX_32; ++j)
			{
				m_aCurrentAmp[i][j] = m_aCurrentAmp[i + 1][j];
			}
			m_aCurrentIndex[i] = m_aCurrentIndex[i + 1];
		}
		memset(m_aCurrentAmp[SPECTROGRAM_X - 1], 0, sizeof(short)*INDEX_32);
		for (int j = 0; j < cnt; ++j)
			m_aCurrentAmp[SPECTROGRAM_X -1][j] = ampdata[j];
		m_aCurrentIndex[SPECTROGRAM_X - 1] = index;
	}
}

void CSpectrogram::UpdateGraph(bool IsTrigger)
{
	int MaxGraphX = (SPECTROGRAM_X <= m_cr.x ? SPECTROGRAM_X : m_cr.x);
	int Pixel_w = 1;
	int Pixel_h = 1;
	int Width = SPECTROGRAM_X;
	int Height = INDEX_32;
	int CurrentX = 0;
	int CurrentY = 0;

	for (int i = 0; i < MaxGraphX; ++i)
	{	
		Pixel_h = (m_aCurrentAmp[i][70] == 0 ? INDEX_32 / INDEX_4 : 1);
		CurrentY = Pixel_h;
		for (int j = 0; j < INDEX_32/ Pixel_h; ++j)
		{
			COLORREF color = GetRefColor(m_aCurrentAmp[i][j]);
			if (IsTrigger && Pixel_h == 8 && j == m_aCurrentIndex[i])
				color = RGB(255, 0, 255);
			if (IsTrigger && Pixel_h == 1&& m_aCurrentIndex[i] - 2 <= j && j <= m_aCurrentIndex[i] + 2)
				color = RGB(255, 0, 255);
			m_dcMem.FillSolidRect(CurrentX, Height - CurrentY, Pixel_w, Pixel_h, color);
			CurrentY += Pixel_h;
		}
		CurrentX += Pixel_w;
	}
}