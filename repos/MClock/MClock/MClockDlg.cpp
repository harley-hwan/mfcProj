
// MClockDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MClock.h"
#include "MClockDlg.h"
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


// CMClockDlg dialog



CMClockDlg::CMClockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCLOCK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMClockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMClockDlg message handlers

BOOL CMClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	CRect rect;
	screen.top = 0;
	screen.left = 0;
	screen.bottom = ::GetSystemMetrics(SM_CYSCREEN);
	screen.right = ::GetSystemMetrics(SM_CXSCREEN);		// 화면 크기

	/*	1 : 타이머의 식별자
		1000 : 타이머를 일으키는 시간
		NULL : CallBack 함수가 존재하지 않음	*/
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

void CMClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMClockDlg::OnPaint()
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
HCURSOR CMClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMClockDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CTime gct = CTime::GetCurrentTime();

	CString strDate;
	CString strTime;

	strDate.Format(_T("%d 년 %d 월 %d 일 "), gct.GetYear(), gct.GetMonth(), gct.GetDay());
	GetDlgItem(IDC_STATIC_DATE)->SetWindowText((LPCTSTR)strDate);

	strTime.Format(_T("%d 시 %d 분 %d 초 "), gct.GetHour(), gct.GetMinute(), gct.GetSecond());
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText((LPCTSTR)strTime);

	Invalidate();

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CMClockDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	RECT winpos;
	int x = rand() % (screen.right - vsize);	// rand() : 0~32767 사이의 임의의 숫자 발생
	int y = rand() % (screen.bottom - hsize);	// 화면내 이동
	winpos.top = y;
	winpos.bottom = y + hsize;
	winpos.left = x;
	winpos.right = x + vsize;
	MoveWindow(&winpos, TRUE);	// 윈도우 이동

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CMClockDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(htimer);

	CDialogEx::OnClose();
}
