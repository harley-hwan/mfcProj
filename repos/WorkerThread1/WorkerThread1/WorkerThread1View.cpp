
// WorkerThread1View.cpp : implementation of the CWorkerThread1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "WorkerThread1.h"
#endif

#include "WorkerThread1Doc.h"
#include "WorkerThread1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWorkerThread1View

IMPLEMENT_DYNCREATE(CWorkerThread1View, CView)

BEGIN_MESSAGE_MAP(CWorkerThread1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CWorkerThread1View construction/destruction

CWorkerThread1View::CWorkerThread1View() noexcept
{
	// TODO: add construction code here

}

CWorkerThread1View::~CWorkerThread1View()
{
}

BOOL CWorkerThread1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CWorkerThread1View drawing

void CWorkerThread1View::OnDraw(CDC* /*pDC*/)
{
	CWorkerThread1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CWorkerThread1View printing

BOOL CWorkerThread1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWorkerThread1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWorkerThread1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CWorkerThread1View diagnostics

#ifdef _DEBUG
void CWorkerThread1View::AssertValid() const
{
	CView::AssertValid();
}

void CWorkerThread1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWorkerThread1Doc* CWorkerThread1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkerThread1Doc)));
	return (CWorkerThread1Doc*)m_pDocument;
}
#endif //_DEBUG


UINT CalcIt(LPVOID arg)
{
	// LPVOID를 int형으로 타입 캐스팅한다.
	int val = (int)arg;

	// 1부터 val까지 1씩 증가하면서 더한다.
	int result = 0;
	for (int i = 1; i < val; i++) {
		result += i;
		Sleep(10);	// 테스트를 위해 계산 속도를 늦춘다.
	}

	// 계산 결과를 표시한다.
	CString str;
	str.Format(_T("계산 결과 = %d"), result);
	AfxMessageBox(str);

	return 0;
}


// CWorkerThread1View message handlers


void CWorkerThread1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int val = 600;

	// 스레드를 사용하지 않은 경우
	//CalcIt((LPVOID)val);

	// 스레드를 사용한 경우
	AfxBeginThread(CalcIt, (LPVOID)val);
	//CView::OnLButtonDown(nFlags, point);
}
