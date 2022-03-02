#include "stdafx.h"
#include "2DGraph.h"

C2DGraph::C2DGraph()
{
	m_nGraphAxisX_height = 20;		// 20 : 글꼴 대략의 높이
	m_nGraphAxisY_width = 30;		// 50 : 5자릿수 커버
	m_bGridOnoff = true;
	m_bAxisReverse = false;
}

C2DGraph::~C2DGraph()
{
	//if(m_dcMem)
	//	ReleaseDC(&m_dcMem);				// 에러발생 - 이미 해제된듯?
}

void C2DGraph::SetProperty(CDC* pDC, int pixelW, int pixelH, int penWidth, int GridW, int GridH, int GraphPixelW, int GraphPixelH, int AxisWidth ,bool IsFFT)
{
	m_PenWidth = penWidth;
	m_nGridNumX = GridW;
	m_nGridNumY = GridH;
	m_PixelMax.x = GraphPixelW;
	m_PixelMax.y = GraphPixelH;
	m_pDC = pDC;
	CreateMemDC(m_pDC);
	m_nGraphAxisY_width = AxisWidth;
	m_bIsFFT = IsFFT;
	SetWindowPixel(pixelW, pixelH);
	SetGraphPixel(m_PixelMax.x, m_PixelMax.y);
}

void C2DGraph::SetAxisReverse(bool isreverse)				// Height축 반전 (좌우만 해당)
{
	m_bAxisReverse = isreverse;
}

void C2DGraph::SetWindowPixel(int x, int y)
{
	m_WindowRect.left = m_nGraphAxisY_width;
	m_WindowRect.right = x;
	m_WindowRect.top = 0;
	m_WindowRect.bottom = y - m_nGraphAxisX_height;

	SetGraphAxisX();
	SetGraphAxisY();
}

void C2DGraph::SetGraphPixel(int x, int y)
{
	m_DynamicRect.left = 0;
	m_DynamicRect.right = x;
	m_DynamicRect.top = 0;
	m_DynamicRect.bottom = y;
}


void C2DGraph::SetWidth(int widthMin, int widthMax)
{
	m_DynamicRect.left = widthMin;
	m_DynamicRect.right = widthMax;
}

void C2DGraph::SetHeight(int heightMin,int heightMax)
{	
	if (m_bAxisReverse)			// Height축 반전 (좌우만 해당)
	{
		heightMin *= -1;
		heightMax *= -1;
	}
	m_DynamicRect.top = heightMin;
	m_DynamicRect.bottom = heightMax;
}

void C2DGraph::SetPenWidth(int width)
{
	if (5 < width) width = 5;
	m_PenWidth = width;
}

void C2DGraph::SetGraphAxisX()
{
	m_nGraphAxisX_width = m_WindowRect.Width();
}

void C2DGraph::SetGraphAxisY()
{
	m_nGraphAxisY_height = m_WindowRect.Height();
}

void C2DGraph::SetGridNumber(int numX, int numY)
{
	m_nGridNumX = numX;
	m_nGridNumY = numY;
}

void C2DGraph::DrawGraphAxis()
{
	CRect rect;
	rect.left = 0; rect.top = 0; rect.right = m_nGraphAxisX_width+m_nGraphAxisY_width; rect.bottom = m_nGraphAxisX_height+m_nGraphAxisY_height;
	m_pDC->FillSolidRect(rect, RGB(70, 70, 70));								// dc 초기화 

	SetBkMode(m_pDC->m_hDC, 1);
	SetTextColor(m_pDC->m_hDC, RGB(220, 220, 220));
	CString cstr;
	for (int i = 0; i < m_nGridNumX; ++i)
	{
		int nValue = m_DynamicRect.left + (float)(m_DynamicRect.right - m_DynamicRect.left) / m_nGridNumX *i;
		cstr.Format("%d", nValue);
		TextOut(m_pDC->m_hDC, m_nGraphAxisY_width-10 + (m_nGraphAxisX_width-15)/ m_nGridNumX*i, m_nGraphAxisY_height, cstr, cstr.GetLength());
	}
	cstr.Format("%d", m_DynamicRect.right);
	TextOut(m_pDC->m_hDC, m_nGraphAxisY_width+m_nGraphAxisX_width - 30, m_nGraphAxisY_height, cstr, cstr.GetLength());

	for (int i = 0; i < m_nGridNumY; ++i)
	{
		int nValue = m_DynamicRect.top + (float)(m_DynamicRect.bottom - m_DynamicRect.top) / m_nGridNumY *i;
		cstr.Format("%d", nValue);
		if(i==0)	TextOut(m_pDC->m_hDC, m_nGraphAxisY_width - 6 * cstr.GetLength() -10,  m_nGraphAxisY_height - m_nGraphAxisX_height - (m_nGraphAxisY_height) / m_nGridNumY*i, cstr, cstr.GetLength());
		else		TextOut(m_pDC->m_hDC, m_nGraphAxisY_width - 6 * cstr.GetLength() - 10, 10 + m_nGraphAxisY_height - m_nGraphAxisX_height - (m_nGraphAxisY_height) / m_nGridNumY*i, cstr, cstr.GetLength());
	}
	cstr.Format("%d", m_DynamicRect.bottom);
	TextOut(m_pDC->m_hDC, m_nGraphAxisY_width - 6 * cstr.GetLength() - 10, 0, cstr, cstr.GetLength());

}

void C2DGraph::DrawFFTAxis()
{
	CRect rect;
	rect.left = 0; rect.top = 0; rect.right = m_nGraphAxisX_width + m_nGraphAxisY_width; rect.bottom = m_nGraphAxisX_height + m_nGraphAxisY_height;
	m_pDC->FillSolidRect(rect, RGB(70, 70, 70));								// dc 초기화 

	SetBkMode(m_pDC->m_hDC, 1);
	SetTextColor(m_pDC->m_hDC, RGB(220, 220, 220));
	CString cstr;
	for (int i = 0; i < m_nGridNumX; ++i)
	{
		int nValue = m_DynamicRect.left + (float)(m_DynamicRect.right - m_DynamicRect.left) / m_nGridNumX *i;
		cstr.Format("%d", nValue);
		TextOut(m_pDC->m_hDC, m_nGraphAxisY_width - 10 + (m_nGraphAxisX_width - 15) / m_nGridNumX*i, m_nGraphAxisY_height, cstr, cstr.GetLength());
	}
	cstr.Format("%d", m_DynamicRect.right);
	TextOut(m_pDC->m_hDC, m_nGraphAxisY_width + m_nGraphAxisX_width - 30, m_nGraphAxisY_height, cstr, cstr.GetLength());

	for (int i = 0; i < m_nGridNumY; ++i)
	{
		int nValue = m_DynamicRect.top + (float)(m_DynamicRect.bottom - m_DynamicRect.top) / m_nGridNumY *i;
		cstr.Format("%d", nValue);
		if(i==0)	TextOut(m_pDC->m_hDC, m_nGraphAxisY_width - 10 * cstr.GetLength() + 2, 5 + m_nGraphAxisY_height - m_nGraphAxisX_height - (m_nGraphAxisY_height) / m_nGridNumY*i, cstr, cstr.GetLength());
		else		TextOut(m_pDC->m_hDC, m_nGraphAxisY_width - 10 * cstr.GetLength() + 1, 12 + m_nGraphAxisY_height - m_nGraphAxisX_height - (m_nGraphAxisY_height) / m_nGridNumY*i, cstr, cstr.GetLength());
	}
	cstr.Format("%d", m_DynamicRect.bottom);
	TextOut(m_pDC->m_hDC, m_nGraphAxisY_width - 10 * cstr.GetLength() +1, 0, cstr, cstr.GetLength());
}

void C2DGraph::DrawGraphGrid()
{
	if(m_bGridOnoff)
	{
		CRect rect;
		rect.left = 0; rect.top = 0, rect.right = m_PixelMax.x; rect.bottom = m_PixelMax.y;
		m_dcMem.FillSolidRect(rect, RGB(0, 0, 0));								// dc 초기화 

		{
			CPen PenGray;
			if(m_bIsFFT)
				PenGray.CreatePen(PS_SOLID, 3/*두께*/, RGB(100, 100, 100));
			else
				PenGray.CreatePen(PS_SOLID, 1/*두께*/, RGB(100, 100, 100));
			CPen* pOldPen = m_dcMem.SelectObject(&PenGray);
			for (int i = 1; i < m_nGridNumX; ++i)
			{
				POINT move = { rect.Width() / m_nGridNumX*i , 0 };
				POINT line = { move.x , rect.Height() };

				m_dcMem.MoveTo(move);
				m_dcMem.LineTo(line);
			}
			m_dcMem.SelectObject(pOldPen);
		}
		
		{
			CPen PenGray;
			PenGray.CreatePen(PS_SOLID, 1/*두께*/, RGB(100, 100, 100));
			CPen* pOldPen = m_dcMem.SelectObject(&PenGray);
			for (int i = 1; i < m_nGridNumY; ++i)
			{
				POINT move = { 0  , rect.Height() / m_nGridNumY *i };
				POINT line = { rect.Width() , move.y };

				m_dcMem.MoveTo(move);
				m_dcMem.LineTo(line);
			}
			m_dcMem.SelectObject(pOldPen);
		}
	}
	else
	{
		CRect rect;
		rect.left = 0; rect.top = 0, rect.right = m_PixelMax.x; rect.bottom = m_PixelMax.y;
		m_dcMem.FillSolidRect(rect, RGB(0, 0, 0));								// dc 초기화 
	}
}

void C2DGraph::CreateMemDC(CDC* pdc)
{
	CBitmap bitOff;
	
	m_dcMem.CreateCompatibleDC(pdc);

	bitOff.CreateCompatibleBitmap(pdc, m_PixelMax.x, m_PixelMax.y);			// 가상DC -> 1:1 픽셀로 비트맵 생성 (최대값으로 그림)

	m_pOldBitmap = m_dcMem.SelectObject(&bitOff);
}


void C2DGraph::PlotXY(double* x, double* y, int nCnt)
{
	m_ScaleX = abs(m_PixelMax.x / (float)(m_DynamicRect.Width()));
	m_ScaleY = abs(m_PixelMax.y / (float)(m_DynamicRect.Height()));

	DrawGraphGrid();

	{
		CPen PenRed;
		PenRed.CreatePen(PS_SOLID, m_PenWidth/*두께*/, RGB(255, 0, 0));
		CPen* pOldPen = m_dcMem.SelectObject(&PenRed);

		POINT cr = { 0, m_PixelMax.y - RoundOff(Nomalization(m_DynamicRect.top, m_DynamicRect.bottom, 0, m_PixelMax.y)) };
		
		for (int cnt = 0; cnt < nCnt; ++cnt)
		{
			//if (x[cnt] != 0 && y[cnt] != 0)
			{
				m_dcMem.MoveTo(cr);
				float ValueY = Nomalization(m_DynamicRect.top, m_DynamicRect.bottom, y[cnt], m_DynamicRect.Height());
				float ValueX = x[cnt];
			
				POINT pt = { RoundOff(ValueX*m_ScaleX),m_PixelMax.y - RoundOff(ValueY*m_ScaleY) };
			
				m_dcMem.LineTo(pt);
				cr = pt;
			}
		}
		m_dcMem.SelectObject(pOldPen);
	}
}

void C2DGraph::PlotXY(double* x1, double* y1, double* x2, double* y2, int nCnt)
{
	m_ScaleX = abs(m_PixelMax.x / (float)(m_DynamicRect.Width()));
	m_ScaleY = abs(m_PixelMax.y / (float)(m_DynamicRect.Height()));

	DrawGraphGrid();

	if (!m_bAxisReverse)
	{
		{
			CPen PenRed;
			PenRed.CreatePen(PS_SOLID, m_PenWidth/*두께*/, RGB(255, 0, 0));
			CPen* pOldPen = m_dcMem.SelectObject(&PenRed);

			POINT cr = { 0, m_PixelMax.y - RoundOff(Nomalization(m_DynamicRect.top, m_DynamicRect.bottom, 0, m_PixelMax.y)) };
			
			for (int cnt = 0; cnt < nCnt; ++cnt)
			{
				//if (x1[cnt] != 0 && y1[cnt] != 0)
				{
					m_dcMem.MoveTo(cr);
					float ValueY = Nomalization(m_DynamicRect.top, m_DynamicRect.bottom, y1[cnt], m_DynamicRect.Height());
					float ValueX = x1[cnt];
				
					POINT pt = { RoundOff(ValueX*m_ScaleX),m_PixelMax.y - RoundOff(ValueY*m_ScaleY) };
					m_dcMem.LineTo(pt);
					cr = pt;
				}
			}
			m_dcMem.SelectObject(pOldPen);
		}

		{
			CPen PenGreen;
			PenGreen.CreatePen(PS_SOLID, 1/*두께*/, RGB(0, 255, 0));
			CPen* pOldPen = m_dcMem.SelectObject(&PenGreen);

			POINT cr = { 0, m_PixelMax.y - RoundOff(Nomalization(m_DynamicRect.top, m_DynamicRect.bottom, 0, m_PixelMax.y)) };
			for (int cnt = 0; cnt < nCnt; ++cnt)
			{
				//if (x2[cnt] != 0 && y2[cnt] != 0)
				{
					m_dcMem.MoveTo(cr);
					float ValueY = Nomalization(m_DynamicRect.top, m_DynamicRect.bottom, y2[cnt], m_DynamicRect.Height());
					float ValueX = x2[cnt];
					POINT pt = { RoundOff(ValueX*m_ScaleX),m_PixelMax.y - RoundOff(ValueY*m_ScaleY) };
					m_dcMem.LineTo(pt);
					cr = pt;
				}
			}
			m_dcMem.SelectObject(pOldPen);
		}
	}
	
}

void C2DGraph::DrawGraphOffScreen()				// 그래프를 그릴 DC와 DC의 크기
{
	if(m_bIsFFT)
		DrawFFTAxis();
	else
		DrawGraphAxis();

	if (m_dcMem)
	{
		//Blt the memory device context to the screen.
		m_pDC->StretchBlt(
			m_nGraphAxisY_width,
			5,
			m_WindowRect.Width()-10,
			m_WindowRect.Height()-5,
			&m_dcMem,
			0,
			0,
			m_PixelMax.x,
			m_PixelMax.y,
			SRCCOPY);
	}
}

void C2DGraph::DrawGraphOffScreen(CDC* pDC, CRect rectin, CRect rectout)
{
	DrawGraphOffScreen();

	if (m_pDC)
	{
		//Blt the memory device context to the screen.
		pDC->StretchBlt(
			0,
			0,
			rectout.Width(),
			rectout.Height(),
			m_pDC,
			0,
			0,
			rectin.Width(),
			rectin.Height(),
			SRCCOPY);
	}
}

float C2DGraph::Nomalization(int Min, int Max, float Value, int Scale)
{
	Scale = abs(Scale);
	float Range = Max - Min;
	float Result = (float)(Value - Min) / Range * Scale;
	if (Scale < Result) Result = Scale+1;
	if (Result < -1) Result = -1;
	return Result;
}

int C2DGraph::RoundOff(float value)
{
	int result = value;
	if (0.5 <= value - result)
		return (result + 1);
	return result;
}
