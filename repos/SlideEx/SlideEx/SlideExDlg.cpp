
// SlideExDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SlideEx.h"
#include "SlideExDlg.h"
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


// CSlideExDlg dialog



CSlideExDlg::CSlideExDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SLIDEEX_DIALOG, pParent)
	, m_nH(0)
	, m_nV(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSlideExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_HORIZONTAL, m_sldH);
	DDX_Control(pDX, IDC_SLIDER_VERTICAL, m_sldV);
	DDX_Text(pDX, IDC_EDIT_HORIZONTAL, m_nH);
	DDX_Text(pDX, IDC_EDIT_VERTICAL, m_nV);
}

BEGIN_MESSAGE_MAP(CSlideExDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CSlideExDlg message handlers

BOOL CSlideExDlg::OnInitDialog()
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

	m_sldH.SetRange(0, 100);
	m_sldV.SetRange(-100, 100);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSlideExDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSlideExDlg::OnPaint()
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
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSlideExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSlideExDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;
	GetDlgItem(IDC_EDIT_HORIZONTAL)->GetWindowRect(&rect);
	
	int nH = m_sldH.GetPos();
	

	if ((pScrollBar == (CScrollBar*)&m_sldH))
	{
		int nPosH = m_sldH.GetPos();
		
		m_nH = nPosH;

		UpdateData(FALSE);
		InvalidateRect(&rect);
	}
	else
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSlideExDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetDlgItem(IDC_EDIT_VERTICAL)->GetWindowRect(&rect);
	int nV = m_sldV.GetPos();
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);

	if ((pScrollBar == (CScrollBar*)&m_sldV))
	{
		int nPosV = m_sldV.GetPos();

		m_nV = nPosV;

		UpdateData(FALSE);
		InvalidateRect(&rect);
	}
	else
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

