#pragma once
#include "afxwin.h"

#include "ListenSocket.h"
#include "ServiceSocket.h"

// CHelloServerDlg dialog
class CHelloServerDlg : public CDialogEx
{
	// Construction
public:
	CHelloServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELLOSERVER_DIALOG };
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
	CStatic m_static_status;
	CButton m_button_start;
public:
	CListenSocket* m_pListenSocket;
	CServiceSocket* m_pServiceSocket;

};