
// ThreadEXDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ThreadEX.h"
#include "ThreadEXDlg.h"
#include "afxdialogex.h"

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <ctime>

void print_time(struct tm* now, int tail);

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


// CThreadEXDlg dialog



CThreadEXDlg::CThreadEXDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THREADEX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadEXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadEXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CThreadEXDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CThreadEXDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CThreadEXDlg message handlers

BOOL CThreadEXDlg::OnInitDialog()
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
	p1 = NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThreadEXDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CThreadEXDlg::OnPaint()
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
HCURSOR CThreadEXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CThreadEXDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	p1 = AfxBeginThread(TimeThread, this);

	if (p1 == NULL) {
		AfxMessageBox(L"Error!");
	}
}


void CThreadEXDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	// thread 중지
	if (NULL != p1) {
		::SuspendThread(p1->m_hThread);
	}
}

/*
CThreadEXDlg* fir = (CThreadEXDlg*)_mothod;
while (1) {
	CTime cTime = CTime::GetCurrentTime();
	fir->m_staticDisp.Format(_T("%d년 %d월 %d일\n%d시 %d분 %d초"),
		cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(),
		cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	fir->SetDlgItemText(IDC_STATIC_DIS, fir->m_staticDisp);
	Sleep(1000);
}
return 0;
*/

UINT CThreadEXDlg::TimeThread(LPVOID _mothod)
{
	CThreadEXDlg* fir = (CThreadEXDlg*)_mothod;
	
	clock_t sclock, nclock;
	time_t seconds;
	struct tm now;
	int tail = 0;

	sclock = clock();
	time(&seconds);
	localtime_s(&now, &seconds);
	print_time(&now, tail);

	while (1) {

		/*fir->m_staticDisp.Format(_T("%2d시 %2d분 %2d초 %2d\n", now->tm_hour, now->tm_min, now->tm_sec, tail));
		fir->SetDlgItemTextW(IDC_STATIC_DISP, fir->m_staticDisp);
		Sleep(100);*/

		if (_kbhit())
		{
			break;
		}
		nclock = clock();

		if (nclock - sclock >= (CLOCKS_PER_SEC / 100))
		{
			tail++;
			if (tail == 100)//1초가 지나면
			{
				tail = 0;
				sclock = clock();
				time(&seconds);
				localtime_s(&now, &seconds);
			}
			print_time(&now, tail);
		}
	}
	return 0;
}

void print_time(struct tm* now, int tail)
{
	//COORD CursorPostion = { 0,1 };
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPostion);

	printf("%2d시 %2d분 %2d초 %2d\n", now->tm_hour, now->tm_min, now->tm_sec, tail);
}