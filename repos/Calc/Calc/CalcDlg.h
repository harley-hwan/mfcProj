
// CalcDlg.h : header file
//

#pragma once


// CCalcDlg dialog
class CCalcDlg : public CDialogEx
{
// Construction
public:
	CCalcDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALC_DIALOG };
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
	int m_nOption;
	afx_msg void OnClickedButtonAdd();
	afx_msg void OnClickedButtonClear();
	afx_msg void OnClickedButtonDiv();
	afx_msg void OnClickedButtonEqu();
	afx_msg void OnClickedButtonExit();
	afx_msg void OnClickedButtonMul();
	afx_msg void OnClickedButtonSub();
	CString m_nNum1;
	CString m_nNum2;
	CString m_nResult;
};
