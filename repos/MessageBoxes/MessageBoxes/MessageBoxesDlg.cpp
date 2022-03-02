
// MessageBoxesDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MessageBoxes.h"
#include "MessageBoxesDlg.h"
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


// CMessageBoxesDlg dialog



CMessageBoxesDlg::CMessageBoxesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MESSAGEBOXES_DIALOG, pParent)
	, m_strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMessageBoxesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
}

BEGIN_MESSAGE_MAP(CMessageBoxesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_YNC, &CMessageBoxesDlg::OnClickedButtonYnc)
	ON_BN_CLICKED(IDC_BUTTON_YN, &CMessageBoxesDlg::OnClickedButtonYn)
	ON_BN_CLICKED(IDC_BUTTON_RC, &CMessageBoxesDlg::OnClickedButtonRc)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CMessageBoxesDlg::OnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_OC, &CMessageBoxesDlg::OnClickedButtonOc)
	ON_BN_CLICKED(IDC_BUTTON_MFC, &CMessageBoxesDlg::OnClickedButtonMfc)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMessageBoxesDlg::OnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_ARI, &CMessageBoxesDlg::OnClickedButtonAri)
END_MESSAGE_MAP()


// CMessageBoxesDlg message handlers

BOOL CMessageBoxesDlg::OnInitDialog()
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

void CMessageBoxesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMessageBoxesDlg::OnPaint()
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
HCURSOR CMessageBoxesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMessageBoxesDlg::OnClickedButtonYnc()
{
	// TODO: Add your control notification handler code here
	int iResults;
	m_strResult = _T("YES/NO/CANCEL 버튼을 눌렀습니다.");
	UpdateData(FALSE);
	iResults = AfxMessageBox(_T("YES/NO/CANCEL 버튼을 눌렀습니다."), (MB_YESNOCANCEL | MB_ICONINFORMATION));

	if (iResults == IDYES)
	{
		m_strResult = _T("OK 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
	if (iResults == IDNO)
	{
		m_strResult = _T("NO 버튼을 눌렀습니다1");
		UpdateData(FALSE);
	}
	if (iResults == IDCANCEL)
	{
		m_strResult = _T("CANCEL 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
}


void CMessageBoxesDlg::OnClickedButtonYn()
{
	// TODO: Add your control notification handler code here
	int iResults;
	m_strResult = _T("YES/NO 버튼을 눌렀습니다.");
	UpdateData(FALSE);
	iResults = AfxMessageBox(_T("YES/NO 버튼을 눌렀습니다."), (MB_YESNO | MB_ICONWARNING));

	if (iResults == IDYES)
	{
		m_strResult = _T("YES 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
	if (iResults == IDNO)
	{
		m_strResult = _T("NO 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
}


void CMessageBoxesDlg::OnClickedButtonRc()
{
	// TODO: Add your control notification handler code here
	int iResults;
	m_strResult = _T("RETRY/CANCEL 버튼을 눌렀습니다.");
	UpdateData(FALSE);
	iResults = AfxMessageBox(_T("RETRY/CANCEL 버튼을 눌렀습니다."), (MB_RETRYCANCEL | MB_ICONQUESTION));

	if (iResults == IDRETRY)
	{
		m_strResult = _T("RETRY 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
	if (iResults == IDCANCEL)
	{
		m_strResult = _T("CANCEL 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
}


void CMessageBoxesDlg::OnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	int iResults{};
	m_strResult = _T("OK 버튼을 눌렀습니다!");
	UpdateData(FALSE);

	AfxMessageBox(_T("OK 버튼을 눌렀습니다."), MB_ICONERROR);
}


void CMessageBoxesDlg::OnClickedButtonOc()
{
	// TODO: Add your control notification handler code here
	int iResults;
	m_strResult = _T("OK/CANCEL 버튼을 눌렀습니다.");
	UpdateData(FALSE);
	iResults = AfxMessageBox(_T("OK/CANCEL 버튼을 눌렀습니다."), (MB_OKCANCEL | MB_ICONSTOP));

	if (iResults == IDOK)
	{
		m_strResult = _T("OK 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
	if (iResults == IDCANCEL)
	{
		m_strResult = _T("CANCEL 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
}


void CMessageBoxesDlg::OnClickedButtonMfc()
{
	// TODO: Add your control notification handler code here
	m_strResult = _T("MFC 버튼을 눌렀습니다!");
	UpdateData(FALSE);

	MessageBox(_T("Microsoft Foundation Class 입니다."));
}


void CMessageBoxesDlg::OnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	OnOK();
}


void CMessageBoxesDlg::OnClickedButtonAri()
{
	// TODO: Add your control notification handler code here
	int iResults;
	m_strResult = _T("ABORT/RETRY/IGNORE 버튼을 눌렀습니다!");
	UpdateData(FALSE);
	iResults = AfxMessageBox(_T("ABORT/RETRY/IGNORE 버튼을 눌렀습니다."), (MB_ABORTRETRYIGNORE | MB_ICONINFORMATION));
	
	if (iResults == IDABORT)
	{
		m_strResult = _T("ABORT 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
	if (iResults == IDRETRY)
	{
		m_strResult = _T("RETRY 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
	if (iResults == IDIGNORE)
	{
		m_strResult = _T("IGNORE 버튼을 눌렀습니다!");
		UpdateData(FALSE);
	}
}
