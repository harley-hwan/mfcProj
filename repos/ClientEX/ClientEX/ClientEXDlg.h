
// ClientEXDlg.h : header file
//

#pragma once


// CClientEXDlg dialog
class CClientEXDlg : public CDialogEx
{
// Construction
public:
	CClientEXDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENTEX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnStnClickedStaticStatus();
	CStatic m_static_status;
public:
	afx_msg void OnBnClickedButtonConnect();
};
