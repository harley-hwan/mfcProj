
// MouseMsgView.cpp : implementation of the CMouseMsgView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MouseMsg.h"
#endif

#include "MouseMsgDoc.h"
#include "MouseMsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseMsgView

IMPLEMENT_DYNCREATE(CMouseMsgView, CView)

BEGIN_MESSAGE_MAP(CMouseMsgView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
ON_WM_PAINT()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_MOUSEWHEEL()
ON_WM_MBUTTONDBLCLK()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMouseMsgView construction/destruction

CMouseMsgView::CMouseMsgView() noexcept
{
	// TODO: add construction code here
	m_ptMouse = CPoint(0, 0);
	m_ptLeft = CPoint(0, 0);
	m_ptRight = CPoint(0, 0);

}

CMouseMsgView::~CMouseMsgView()
{
}

BOOL CMouseMsgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMouseMsgView drawing

void CMouseMsgView::OnDraw(CDC* /*pDC*/)
{
	CMouseMsgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMouseMsgView printing

BOOL CMouseMsgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMouseMsgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMouseMsgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMouseMsgView diagnostics

#ifdef _DEBUG
void CMouseMsgView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseMsgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseMsgDoc* CMouseMsgView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseMsgDoc)));
	return (CMouseMsgDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseMsgView message handlers


void CMouseMsgView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CString strData = _T("");

	// WM_MOUSEMOVE
	strData.Format(_T("X:%03d, Y:%03d"), m_ptMouse.x, m_ptMouse.y);
	dc.TextOut(10, 10, strData);

	// WM_LBUTTONDOWN
	strData.Format(_T("WM_LBUTTONDOWN X:%03d, Y:%03d"), m_ptLeft.x, m_ptLeft.y);
	dc.TextOut(10, 30, strData);

	//WM_RBUTTONDOWN
	strData.Format(_T("WM_RBUTTONDOWN X:%03d, Y:%03d"), m_ptRight.x, m_ptRight.y);
	dc.TextOut(10, 50, strData);

	// Do not call CView::OnPaint() for painting messages
}


void CMouseMsgView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON &&
		(nFlags & MK_RBUTTON) == MK_RBUTTON)
	{
		m_ptMouse = point;
		RedrawWindow();
	}

	CView::OnMouseMove(nFlags, point);
}


void CMouseMsgView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_ptLeft = point;
	RedrawWindow();
	CView::OnLButtonDown(nFlags, point);
}


void CMouseMsgView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_ptRight = point;
	RedrawWindow();
	CView::OnRButtonDown(nFlags, point);
}


BOOL CMouseMsgView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	CString strTmp = _T("");
	strTmp.Format(TEXT("OnMouseWheel() zDelta : %d\n"), zDelta);
	TRACE(strTmp);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMouseMsgView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnMButtonDblClk(nFlags, point);
}


void CMouseMsgView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);
}
