
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
	m_bDragFlag = false;		// �巡�� ���� �ƴ�.

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

	dc.TextOutW(m_ptItemText.x, m_ptItemText.y, TEXT("�� ��ǻ��"));

}


void CMouseCombiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
 
	// m_ptItemText ���� �������� 64�ȼ� ������
	// ���콺 ���� ��ư�� Ŭ���� ���ΰ�?

	if (point.x >= m_ptItemText.x - 32 && point.x <= m_ptItemText.x + 32 &&
		point.y >= m_ptItemText.y - 32 && point.y <= m_ptItemText.y + 32)
	{
		// �巡�װ� ���۵Ǿ����Ƿ� ���콺�� ĸ����
		SetCapture();
		m_bDragFlag = true;
		RedrawWindow();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMouseCombiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	// �巡�� ���̾��°�?
	if (m_bDragFlag)
	{
		// ��ư���� ���� �����Ƿ� �巡�װ� �����ٰ� �Ǵ��Ѵ�.
		m_bDragFlag = false;

		// �巡�װ� ���� �� ��ǥ�� ��ӵ� ��ǥ�̴�.
		m_ptItemText = point;
		RedrawWindow();

		// ĸ���� ���콺�� Ǯ�� �ش�.
		ReleaseCapture();
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMouseCombiView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDragFlag) {
		// �巡�� ���� ��ǥ�� ������ �ؽ�Ʈ�� �̵����� ����Ѵ�.
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
	// SS_NOTIFY ��Ÿ���� �߰��Ѵ�.
	m_wndTrack.Create(TEXT("STATIC"), TEXT("TRACK TEST"), 
		WS_CHILD | WS_VISIBLE | WS_BORDER | SS_NOTIFY, 
		CRect(100, 10, 250, 160), this, 1234);

	return 0;
}
