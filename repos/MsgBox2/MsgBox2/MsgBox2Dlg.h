
// MsgBox2Dlg.h : header file
//

#pragma once


// CMsgBox2Dlg dialog
class CMsgBox2Dlg : public CDialogEx
{
// Construction
public:
	CMsgBox2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSGBOX2_DIALOG };
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
	CString m_strResult;
	afx_msg void OnClickedButtonYn();
	afx_msg void OnClickedButtonOc();
	afx_msg void OnClickedButtonExit();
};
