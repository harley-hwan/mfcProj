
// GraphDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Graph.h"
#include "GraphDlg.h"
#include "afxdialogex.h"
#include "Spectrogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CGraphDlg ��ȭ ����



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


// CGraphDlg �޽��� ó����

BOOL CGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CGraphDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	m_GraphRect = m_WindowRect;			// Rect �޾ƿ��¹� ã�ƾ���

	CBitmap bitOff;
	m_rcBoundsDP = m_GraphRect;

	// Create a DC that is compatible with the screen.
	m_dcMem.CreateCompatibleDC(pdc);

	bitOff.CreateCompatibleBitmap(pdc, m_nCntMax, INDEX);			// ����DC -> 1:1 �ȼ��� ��Ʈ�� ����

	// Select the bitmap into the memory DC.
	m_pOldBitmap = m_dcMem.SelectObject(&bitOff);
}

void CGraphDlg::DrawGraphOffScreen(CDC* pdc, const CRect& rcBounds, unsigned short* Data)				// �׷����� �׸� DC�� DC�� ũ��
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
			col = RGB(chB, chG, chR);		//2017-11-21 �̽��� : R,B ���� �ٲ�
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

	//Spectrum ��ȭ 
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