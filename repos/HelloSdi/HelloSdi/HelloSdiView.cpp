
// HelloSdiView.cpp : implementation of the CHelloSdiView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HelloSdi.h"
#endif

#include "HelloSdiDoc.h"
#include "HelloSdiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelloSdiView

IMPLEMENT_DYNCREATE(CHelloSdiView, CEditView)

BEGIN_MESSAGE_MAP(CHelloSdiView, CEditView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CHelloSdiView construction/destruction

CHelloSdiView::CHelloSdiView() noexcept
{
	// TODO: add construction code here

}

CHelloSdiView::~CHelloSdiView()
{
}

BOOL CHelloSdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}


// CHelloSdiView printing

BOOL CHelloSdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CHelloSdiView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CHelloSdiView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CHelloSdiView diagnostics

#ifdef _DEBUG
void CHelloSdiView::AssertValid() const
{
	CEditView::AssertValid();
}

void CHelloSdiView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CHelloSdiDoc* CHelloSdiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelloSdiDoc)));
	return (CHelloSdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CHelloSdiView message handlers
