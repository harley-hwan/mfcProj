
// HelloClientDlg.h : header file
//

#pragma once
#include "afxwin.h"

// CHelloClientDlg dialog
class CHelloClientDlg : public CDialogEx
{
// Construction
public:
	CHelloClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELLOCLIENT_DIALOG };
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
//	CString m_static_status;
public:
	afx_msg void OnBnClickedButtonConnect();
	//CString m_static_status;
	CStatic m_static_status;
};
