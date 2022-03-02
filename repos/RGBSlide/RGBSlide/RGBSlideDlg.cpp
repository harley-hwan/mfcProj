
// RGBSlideDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "RGBSlide.h"
#include "RGBSlideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CRGBSlideDlg dialog



CRGBSlideDlg::CRGBSlideDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RGBSLIDE_DIALOG, pParent)
	, m_nR(0)
	, m_nG(0)
	, m_nB(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRGBSlideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_SLIDER_R, m_sldR);
	DDX_Control(pDX, IDC_SLIDER_G, m_sldG);
	DDX_Control(pDX, IDC_SLIDER_B, m_sldB);

	DDX_Text(pDX, IDC_EDIT_R, m_nR);
	DDX_Text(pDX, IDC_EDIT_G, m_nG);
	DDX_Text(pDX, IDC_EDIT_B, m_nB);
	DDX_Control(pDX, IDC_SLIDER_R, m_sldR);
}

BEGIN_MESSAGE_MAP(CRGBSlideDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CRGBSlideDlg::OnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CRGBSlideDlg::OnClickedButtonExit)
END_MESSAGE_MAP()


// CRGBSlideDlg message handlers

BOOL CRGBSlideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// 컨트롤 범위 설정 256 컬러 지정
	m_sldB.SetRange(0, 255);
	m_sldR.SetRange(0, 255);
	m_sldG.SetRange(0, 255);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRGBSlideDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRGBSlideDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		CRect rect;
		CClientDC rgbdc(GetDlgItem(IDC_STATIC_RGB));
		CStatic* pSRGB = (CStatic*)GetDlgItem(IDC_STATIC_RGB);
		pSRGB->GetClientRect(rect);
		rgbdc.FillSolidRect(rect, m_cRGB);
		pSRGB->ValidateRect(rect);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRGBSlideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRGBSlideDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;
	GetDlgItem(IDC_STATIC_RGB)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	int nR = m_sldR.GetPos();
	int nG = m_sldG.GetPos();
	int nB = m_sldB.GetPos();

	if ((pScrollBar == (CScrollBar*)&m_sldR) || 
		(pScrollBar == (CScrollBar*)&m_sldG) || 
		(pScrollBar == (CScrollBar*)&m_sldB))
	{
		// 슬라이더 위치를 검사
		int nPosR = m_sldR.GetPos();
		int nPosG = m_sldG.GetPos();
		int nPosB = m_sldB.GetPos();

		m_nR = nPosR;
		m_nG = nPosG;
		m_nB = nPosB;

		m_cRGB = RGB(m_nR, m_nG, m_nB);
		UpdateData(FALSE);
		InvalidateRect(&rect);
	}
	else
	{
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	}
	
}


void CRGBSlideDlg::OnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	Clear();
}


void CRGBSlideDlg::OnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CRGBSlideDlg::Clear()
{
	// TODO: Add your implementation code here.
	UpdateData(TRUE);

	CRect rect;
	GetDlgItem(IDC_STATIC_RGB)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	InvalidateRect(&rect);

	m_cRGB = RGB(0, 0, 0);

	m_sldR.SetPos(0);
	m_sldG.SetPos(0);
	m_sldB.SetPos(0);

	m_nR = 0;
	m_nG = 0;
	m_nB = 0;

	m_cRGB = RGB(0, 0, 0);
	UpdateData(FALSE);
}
