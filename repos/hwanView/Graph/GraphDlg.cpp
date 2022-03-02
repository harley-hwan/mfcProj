
// GraphDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Graph.h"
#include "GraphDlg.h"
#include "afxdialogex.h"
#include "Spectrogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGraphDlg 대화 상자



CGraphDlg::CGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GRAPH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	loopCnt = 0;
	loopTimeMax = 0;
	m_nCnt = 1;
	m_nCntMax = 250;
	m_crX = 0;
	m_crY = 0;

	m_nMaxRefColor = 127;
	m_nMinRefColor = -128;
	m_nMaxSpectrumDisplay = 40000;
	m_nMinSpectrumDisplay = 0;


}


CGraphDlg::~CGraphDlg()
{

	// Clean up.
	m_dcMem.SelectObject(m_pOldBitmap);
	ReleaseDC(m_pDC);

}


void CGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGraphDlg 메시지 처리기

BOOL CGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	//RECT rect;
	//GetDlgItem(IDC_SPECTROGRAM)->GetWindowRect(&rect);
	//GetDlgItem(IDC_SPECTROGRAM)->SetWindowPos(NULL, rect.left, rect.top, 690, 300, SWP_NOMOVE);
	GetDlgItem(IDC_SPECTROGRAM)->GetWindowRect(&m_WindowRect);

	m_pDC = GetDlgItem(IDC_SPECTROGRAM)->GetDC();
	CDC* pDC = GetDlgItem(IDC_FFT)->GetDC();
	GetDlgItem(IDC_FFT)->GetWindowRect(m_WindowFFTRect);
	m_FFT = new CFFTGraph(pDC, 0, AMPMAX);
	m_FFT->SetGraphPixel(m_WindowFFTRect.Width(),m_WindowFFTRect.Height());
	ScreenToClient(&m_WindowFFTRect);
	
	CreateMemDC(m_pDC);

	MakeRefColors();
	
	SetTimer(1, 2, 0);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGraphDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGraphDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGraphDlg::OnTimer(UINT_PTR nIDEvent)
{	
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startingTime);
	if (m_nCnt <= 10000)
		m_nCnt++;
	else
		m_nCnt = 0;
	DummyData(m_nCnt);
	DrawGraphOffScreen(m_pDC, m_WindowRect, m_nAmpData);

	m_FFT->PlotFFT(m_nAmpData);
	m_FFT->DrawGraphOffScreen();
	


	CDialogEx::OnTimer(nIDEvent);

	QueryPerformanceCounter(&endingTime);
	elapsed.QuadPart = endingTime.QuadPart - startingTime.QuadPart;
	elapsed.QuadPart *= 1000;
	elapsed.QuadPart /= frequency.QuadPart;

	loop_time = elapsed.QuadPart;
	

	if (loopCnt < 10)
	{
		if (loopTimeMax <= loop_time)
			loopTimeMax = loop_time;
		loopCnt++;
	}
	else
	{
		loopCnt = 0;
		CString str;
		str.Format("loop time %dms", loopTimeMax);
		loopTimeMax = 0;
		SetWindowText(str);
	}
	
}


void CGraphDlg::DummyData(int i)
{
	int indexMax;
	//if (2 < i) i = 0;
	i < 50 ? indexMax = INDEX/8 : indexMax = INDEX;
	memset(m_nAmpData, 0, sizeof(short)*INDEX);
	int cnt = 1;

	for (int index = 0; index < indexMax; ++index)
	{
		if (index % 5 == 0)
		{
			m_nAmpData[index] = i + cnt;
			cnt += 8000;
		}
		else
			m_nAmpData[index] = 0;
	}	
}


void CGraphDlg::PlotGraph(unsigned short* Data, CDC* pDC)
{
	int Width = m_nCntMax;
	int Height = INDEX;
	int indexMax, Pixel_w, Pixel_h;
	
	Data[100] == 0 ? indexMax = INDEX/8 : indexMax = INDEX;
	
	Pixel_w = Width / m_nCntMax;
	Pixel_h = Height / indexMax;

	if (m_crX <= Width)
	{
		for (int index = 0; index < indexMax; ++index)
		{
			COLORREF color = GetRefColor(Data[index]);
			pDC->FillSolidRect(m_crX, m_crY, Pixel_w, Pixel_h, color);
			m_crY += Pixel_h;
		}
		m_crX += Pixel_w;
		m_crY = 0;
	}
	else
	{
		BitBlt(*pDC, 0, 0, Width - Pixel_w, Height, *pDC, Pixel_w, 0, SRCCOPY);
		for (int index = 0; index < indexMax; ++index)
		{
			COLORREF color = GetRefColor(Data[index]);
			pDC->FillSolidRect(m_crX - 2*Pixel_w, m_crY, Pixel_w, Pixel_h, color);
			m_crY += Pixel_h;		
		}
		m_crY = 0;
	}
}

void CGraphDlg::CreateMemDC(CDC* pdc)
{
	m_GraphRect = m_WindowRect;			// Rect 받아오는법 찾아야함

	CBitmap bitOff;
	m_rcBoundsDP = m_GraphRect;

	// Create a DC that is compatible with the screen.
	m_dcMem.CreateCompatibleDC(pdc);

	bitOff.CreateCompatibleBitmap(pdc, m_nCntMax, INDEX);			// 가상DC -> 1:1 픽셀로 비트맵 생성

	// Select the bitmap into the memory DC.
	m_pOldBitmap = m_dcMem.SelectObject(&bitOff);
}

void CGraphDlg::DrawGraphOffScreen(CDC* pdc, const CRect& rcBounds, unsigned short* Data)				// 그래프를 그릴 DC와 DC의 크기
{
	// Draw our control on the memory DC.
	PlotGraph(Data, &m_dcMem);

	//Blt the memory device context to the screen.
	pdc->StretchBlt(
		0,
		0,
		m_rcBoundsDP.Width(),
		m_rcBoundsDP.Height(),
		&m_dcMem,
		0,
		0,
		m_nCntMax,
		INDEX,
		SRCCOPY);
}

bool CGraphDlg::MakeRefColors()
{
	int nMinValue = m_nMinRefColor;
	int nMaxValue = m_nMaxRefColor;

	std::map<short, COLORREF>& stmRefColors = m_stmRefColors;
	if (stmRefColors.empty() == false)
	{
		std::map<short, COLORREF> stm;
		stm.swap(stmRefColors);
	}
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
			stmRefColors[i] = col;
		}
	}
	//CreateSpectrumBMPFile("Spectrum.bmp");
	return true;
}



COLORREF CGraphDlg::GetRefColor(unsigned short nValue)
{
	COLORREF retColor = 0;
	if (m_stmRefColors.empty() == true)
		return retColor;

	//Spectrum 변화 
	//double dMul = (double)(m_nMaxRefColor - m_nMinRefColor) / (double)(e_nMaxAmplitude - e_nMinAmplitude);
	//double dColor = (nValue-e_nMinAmplitude) * dMul + m_nMinRefColor;
	double dMul = (double)(m_nMaxRefColor - m_nMinRefColor) / (double)(m_nMaxSpectrumDisplay - m_nMinSpectrumDisplay);
	double dColor = (nValue - m_nMinSpectrumDisplay) * dMul + m_nMinRefColor;
	nValue = dColor < m_nMinRefColor ? m_nMinRefColor : (dColor > m_nMaxRefColor ? m_nMaxRefColor : dColor);
	std::map<short, COLORREF>::iterator itFind;
	itFind = m_stmRefColors.find(nValue);
	if (itFind != m_stmRefColors.end())
	{
		retColor = itFind->second;
	}

	return retColor;
}