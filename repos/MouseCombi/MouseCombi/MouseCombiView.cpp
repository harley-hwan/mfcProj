
// MouseCombiView.cpp : implementation of the CMouseCombiView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MouseCombi.h"
#endif

#include "MouseCombiDoc.h"
#include "MouseCombiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseCombiView

IMPLEMENT_DYNCREATE(CMouseCombiView, CView)

BEGIN_MESSAGE_MAP(CMouseCombiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMouseCombiView construction/destruction

CMouseCombiView::CMouseCombiView() noexcept
{
	// TODO: add construction code here
	m_ptItemText = CPoint(10, 30);
	m_bDragFlag = false;		// 드래그 중이 아님.

}

CMouseCombiView::~CMouseCombiView()
{
}

BOOL CMouseCombiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMouseCombiView drawing

void CMouseCombiView::OnDraw(CDC* /*pDC*/)
{
	CMouseCombiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMouseCombiView printing

BOOL CMouseCombiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMouseCombiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMouseCombiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMouseCombiView diagnostics

#ifdef _DEBUG
void CMouseCombiView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseCombiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseCombiDoc* CMouseCombiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseCombiDoc)));
	return (CMouseCombiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseCombiView message handlers


void CMouseCombiView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CView::OnPaint() for painting messages
	if (m_bDragFlag)	dc.TextOutW(10, 10, TEXT("DRAG"));
	else				dc.TextOutW(10, 10, TEXT("----"));

	dc.TextOutW(m_ptItemText.x, m_ptItemText.y, TEXT("내 컴퓨터"));

}


void CMouseCombiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
 
	// m_ptItemText 값을 기준으로 64픽셀 내에서
	// 마우스 왼쪽 버튼이 클릭된 것인가?

	if (point.x >= m_ptItemText.x - 32 && point.x <= m_ptItemText.x + 32 &&
		point.y >= m_ptItemText.y - 32 && point.y <= m_ptItemText.y + 32)
	{
		// 드래그가 시작되었으므로 마우스를 캡쳐함
		SetCapture();
		m_bDragFlag = true;
		RedrawWindow();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMouseCombiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	// 드래그 중이었는가?
	if (m_bDragFlag)
	{
		// 버튼에서 손을 뗐으므로 드래그가 끝났다고 판단한다.
		m_bDragFlag = false;

		// 드래그가 끝난 이 좌표가 드롭된 좌표이다.
		m_ptItemText = point;
		RedrawWindow();

		// 캡쳐한 마우스를 풀어 준다.
		ReleaseCapture();
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMouseCombiView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDragFlag) {
		// 드래그 중인 좌표로 아이템 텍스트를 이동시켜 출력한다.
		m_ptItemText = point;
		RedrawWindow();
	}
	CView::OnMouseMove(nFlags, point);
}


int CMouseCombiView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// SS_NOTIFY 스타일을 추가한다.
	m_wndTrack.Create(TEXT("STATIC"), TEXT("TRACK TEST"), 
		WS_CHILD | WS_VISIBLE | WS_BORDER | SS_NOTIFY, 
		CRect(100, 10, 250, 160), this, 1234);

	return 0;
}
