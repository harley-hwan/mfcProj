
// CalcDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Calc.h"
#include "CalcDlg.h"
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


// CCalcDlg dialog



CCalcDlg::CCalcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALC_DIALOG, pParent)
	, m_nNum1(_T(""))
	, m_nNum2(_T(""))
	, m_nResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_nNum1);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_nNum2);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_nResult);
}

BEGIN_MESSAGE_MAP(CCalcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalcDlg::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalcDlg::OnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalcDlg::OnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_EQU, &CCalcDlg::OnClickedButtonEqu)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CCalcDlg::OnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalcDlg::OnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CCalcDlg::OnClickedButtonSub)
END_MESSAGE_MAP()


// CCalcDlg message handlers

BOOL CCalcDlg::OnInitDialog()
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

void CCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalcDlg::OnPaint()
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
HCURSOR CCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalcDlg::OnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	m_nOption = 1;
}

void CCalcDlg::OnClickedButtonSub()
{
	// TODO: Add your control notification handler code here
	m_nOption = 2;
}

void CCalcDlg::OnClickedButtonMul()
{
	// TODO: Add your control notification handler code here
	m_nOption = 3;
}

void CCalcDlg::OnClickedButtonDiv()
{
	// TODO: Add your control notification handler code here
	m_nOption = 4;
}

void CCalcDlg::OnClickedButtonEqu()
{
	// TODO: Add your control notification handler code here
	char temp[10];
	double tmpResult;

	UpdateData(TRUE);

	switch (m_nOption)
	{
		case 1:
			tmpResult = atof(m_nNum1) + atof(m_nNum2);	// [프로젝트 속성]-[구성 속성]-[고급]-[문자 집합]-[멀티바이트 문자 집합 사용] 안하면 에러뜸.
			break;
		case 2:
			tmpResult = atof(m_nNum1) - atof(m_nNum2);
			break;
		case 3:
			tmpResult = atof(m_nNum1) * atof(m_nNum2);
			break;
		case 4:
			tmpResult = atof(m_nNum1) / atof(m_nNum2);
			break;
		default:
			tmpResult = 0.00;
			break;
	}

	sprintf_s(temp, "%2.f", tmpResult);
	m_nResult = temp;
	UpdateData(FALSE);
}

void CCalcDlg::OnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nNum1 = L"";
	m_nNum2 = _T("");
	m_nResult = _T("");
	UpdateData(FALSE);
}

void CCalcDlg::OnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
}