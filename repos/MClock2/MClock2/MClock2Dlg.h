
// MClock2Dlg.h : header file
//

#pragma once


// CMClock2Dlg dialog
class CMClock2Dlg : public CDialogEx
{
// Construction
public:
	CMClock2Dlg(CWnd* pParent = nullptr);	// standard constructor

	CRect screen;
	int vsize, hsize;

	UINT htimer;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MCLOCK2_DIALOG };
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
};
