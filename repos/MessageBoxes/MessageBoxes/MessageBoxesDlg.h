
// MessageBoxesDlg.h : header file
//

#pragma once


// CMessageBoxesDlg dialog
class CMessageBoxesDlg : public CDialogEx
{
// Construction
public:
	CMessageBoxesDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESSAGEBOXES_DIALOG };
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
	afx_msg void OnClickedButtonYnc();
	afx_msg void OnClickedButtonYn();
	afx_msg void OnClickedButtonRc();
	afx_msg void OnClickedButtonOk();
	afx_msg void OnClickedButtonOc();
	afx_msg void OnClickedButtonMfc();
	afx_msg void OnClickedButtonExit();
	afx_msg void OnClickedButtonAri();
	CString m_strResult;
};
