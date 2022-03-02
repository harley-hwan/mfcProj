
// MClockDlg.h : header file
//

#pragma once


// CMClockDlg dialog
class CMClockDlg : public CDialogEx
{
// Construction
public:
	CMClockDlg(CWnd* pParent = nullptr);	// standard constructor

	CRect screen;		// 화면 크기 저장 변수
	int vsize, hsize;	// 폭과 높이 변수

	UINT htimer;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MCLOCK_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClose();
};
