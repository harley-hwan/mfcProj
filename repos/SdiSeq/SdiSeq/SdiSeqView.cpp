
// SdiSeqView.cpp : implementation of the CSdiSeqView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SdiSeq.h"
#endif

#include "SdiSeqDoc.h"
#include "SdiSeqView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdiSeqView

IMPLEMENT_DYNCREATE(CSdiSeqView, CView)

BEGIN_MESSAGE_MAP(CSdiSeqView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSdiSeqView construction/destruction

CSdiSeqView::CSdiSeqView() noexcept
{
	// TODO: add construction code here

}

CSdiSeqView::~CSdiSeqView()
{
}

BOOL CSdiSeqView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSdiSeqView drawing

void CSdiSeqView::OnDraw(CDC* /*pDC*/)
{
	CSdiSeqDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CSdiSeqView printing

BOOL CSdiSeqView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSdiSeqView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSdiSeqView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSdiSeqView diagnostics

#ifdef _DEBUG
void CSdiSeqView::AssertValid() const
{
	CView::AssertValid();
}

void CSdiSeqView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSdiSeqDoc* CSdiSeqView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSdiSeqDoc)));
	return (CSdiSeqDoc*)m_pDocument;
}
#endif //_DEBUG


// CSdiSeqView message handlers
