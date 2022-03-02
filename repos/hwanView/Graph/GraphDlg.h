
// GraphDlg.h : 헤더 파일
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


// CGraphDlg 대화 상자
class CGraphDlg : public CDialogEx
{
// 생성입니다.
public:
	CGraphDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CGraphDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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


	void PlotGraph(unsigned short* Data, CDC* pDC);										// 가상 메모리에 그래프 그림 (1:1)
	void DrawGraphOffScreen(CDC* pdc, const CRect& rcBounds, unsigned short* Data);		// 실제 그래프 크기에 맞춰 Strech
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
