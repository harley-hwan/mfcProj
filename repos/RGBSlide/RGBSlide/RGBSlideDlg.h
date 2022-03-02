
// RGBSlideDlg.h : header file
//

#pragma once


// CRGBSlideDlg dialog
class CRGBSlideDlg : public CDialogEx
{
// Construction
public:
	CRGBSlideDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RGBSLIDE_DIALOG };
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
//	CSliderCtrl m_sldR;
	CSliderCtrl m_sldG;
	CSliderCtrl m_sldB;

	int m_nR;
	int m_nG;
	int m_nB;
	COLORREF m_cRGB;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_sldR;
	afx_msg void OnClickedButtonClear();
	afx_msg void OnClickedButtonExit();
	void Clear();
};
