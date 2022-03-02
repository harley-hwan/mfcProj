
// MClock2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MClock2.h"
#include "MClock2Dlg.h"
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


// CMClock2Dlg dialog



CMClock2Dlg::CMClock2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCLOCK2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMClock2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMClock2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMClock2Dlg message handlers

BOOL CMClock2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	CRect rect;
	screen.top = 0;
	screen.left = 0;
	screen.bottom = ::GetSystemMetrics(SM_CYSCREEN);
	screen.right = ::GetSystemMetrics(SM_CXSCREEN);		// 화면 크기

	htimer = SetTimer(1, 1000, NULL);

	GetWindowRect(rect);
	vsize = rect.Width();		// 프로그램의 가로 크기
	hsize = rect.Height();		// 프로그램의 세로 크기

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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMClock2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMClock2Dlg::OnPaint()
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
HCURSOR CMClock2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMClock2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CTime gct = CTime::GetCurrentTime();

	CString strYear;
	CString strMonth;
	CString strDay;
	CString strTime;
	CString strYoil;

	UINT DayOfWeek[] =
	{
	   LOCALE_SDAYNAME7,   // Sunday
	   LOCALE_SDAYNAME1,
	   LOCALE_SDAYNAME2,
	   LOCALE_SDAYNAME3,
	   LOCALE_SDAYNAME4,
	   LOCALE_SDAYNAME5,
	   LOCALE_SDAYNAME6   // Saturday
	};

	strYear.Format(_T("%d 년 "), gct.GetYear());
	GetDlgItem(IDC_STATIC_YEAR)->SetWindowText((LPCTSTR)strYear);

	strMonth.Format(_T("%d 월 "), gct.GetMonth());
	GetDlgItem(IDC_STATIC_MONTH)->SetWindowText((LPCTSTR)strMonth);

	strDay.Format(_T("%d 일 "), gct.GetDay());
	GetDlgItem(IDC_STATIC_DAY)->SetWindowText((LPCTSTR)strDay);

	if (gct.GetHour() > 12) 
	{
		strTime.Format(_T("오후"));
		GetDlgItem(IDC_STATIC_AMPM)->SetWindowTextW((LPCTSTR)strTime);

		strTime.Format(_T("%d 시 %d 분 %d 초 "), gct.GetHour()-12, gct.GetMinute(), gct.GetSecond());
		GetDlgItem(IDC_STATIC_TIME)->SetWindowText((LPCTSTR)strTime);
	}
	else
	{
		strTime.Format(_T("오전"));
		GetDlgItem(IDC_STATIC_AMPM)->SetWindowTextW((LPCTSTR)strTime);

		strTime.Format(_T("%d 시 %d 분 %d 초 "), gct.GetHour(), gct.GetMinute(), gct.GetSecond());
		GetDlgItem(IDC_STATIC_TIME)->SetWindowText((LPCTSTR)strTime);
	}

	TCHAR strWeekday[256];
	
	::GetLocaleInfo(LOCALE_USER_DEFAULT, DayOfWeek[gct.GetDayOfWeek() - 1], strWeekday, sizeof(strWeekday));

	strYoil.Format(_T("%s "), strWeekday);
	GetDlgItem(IDC_STATIC_YOIL)->SetWindowText((LPCTSTR)strYoil);

	Invalidate();

	CDialogEx::OnTimer(nIDEvent);
}
