
// MsgBox2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MsgBox2.h"
#include "MsgBox2Dlg.h"
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


// CMsgBox2Dlg dialog



CMsgBox2Dlg::CMsgBox2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MSGBOX2_DIALOG, pParent)
	, m_strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMsgBox2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
}

BEGIN_MESSAGE_MAP(CMsgBox2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_YN, &CMsgBox2Dlg::OnClickedButtonYn)
	ON_BN_CLICKED(IDC_BUTTON_OC, &CMsgBox2Dlg::OnClickedButtonOc)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMsgBox2Dlg::OnClickedButtonExit)
END_MESSAGE_MAP()


// CMsgBox2Dlg message handlers

BOOL CMsgBox2Dlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMsgBox2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMsgBox2Dlg::OnPaint()
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
HCURSOR CMsgBox2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMsgBox2Dlg::OnClickedButtonYn()
{
	// TODO: Add your control notification handler code here
	int iResults;
	iResults = AfxMessageBox(_T("YES/NO 버튼을 누르셨습니다."), (MB_YESNO | MB_ICONEXCLAMATION));
	if (iResults == IDYES)
	{
		m_strResult = _T("YES 버튼을 누르셨습니다.");
		UpdateData(FALSE);
	}
	if (iResults == IDNO)
	{
		m_strResult = _T("NO 버튼을 누르셨습니다.");
		UpdateData(FALSE);
	}
}


void CMsgBox2Dlg::OnClickedButtonOc()
{
	// TODO: Add your control notification handler code here
	int iResults;
	iResults = AfxMessageBox(_T("OK/CANCEL 버튼을 누르셨습니다."), (MB_OKCANCEL | MB_ICONEXCLAMATION));
	if (iResults == IDOK)
	{
		m_strResult = _T("OK 버튼을 누르셨습니다.");
		UpdateData(FALSE);
	}
	if (iResults == IDCANCEL)
	{
		m_strResult = _T("CANCEL 버튼을 누르셨습니다.");
		UpdateData(FALSE);
	}
}


void CMsgBox2Dlg::OnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
