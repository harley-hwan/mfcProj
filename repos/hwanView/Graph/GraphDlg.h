
// GraphDlg.h : ��� ����
//
#pragma once
#include <map>
#include "FFTGraph.h"
#include "2dGraph.h"

#define CHANNEL 3
#define INDEX 512

class CFFTGraph;
typedef CFFTGraph* LPCFFTGraph;
class C2DGraph;
typedef C2DGraph* LPC2DGraph;


// CGraphDlg ��ȭ ����
class CGraphDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CGraphDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CGraphDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

public:
	std::map<short, COLORREF> m_stmRefColors;
	
	int loopCnt;
	long loopTimeMax;
	long loop_time;
	LARGE_INTEGER startingTime, endingTime, elapsed;
	LARGE_INTEGER frequency;


	void PlotGraph(unsigned short* Data, CDC* pDC);										// ���� �޸𸮿� �׷��� �׸� (1:1)
	void DrawGraphOffScreen(CDC* pdc, const CRect& rcBounds, unsigned short* Data);		// ���� �׷��� ũ�⿡ ���� Strech
	void DummyData(int i);
	bool MakeRefColors();
	COLORREF GetRefColor(unsigned short nValue);
	void CGraphDlg::CreateMemDC(CDC* pdc);

private:
	CDC m_dcMem;
	CBitmap* m_pOldBitmap;
	unsigned short m_nAmpData[INDEX];
	int m_nCnt;
	int m_nCntMax;
	RECT m_WindowRect;
	CRect m_GraphRect;
	CRect m_WindowFFTRect;
	CRect m_rcBoundsDP;
	CDC* m_pDC;
	int m_crX;
	int m_crY;
	int m_nMaxRefColor;
	int m_nMinRefColor;
	unsigned short m_nMaxSpectrumDisplay;
	unsigned short m_nMinSpectrumDisplay;

	LPCFFTGraph m_FFT;

};
