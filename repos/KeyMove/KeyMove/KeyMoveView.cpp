
// KeyMoveView.cpp : implementation of the CKeyMoveView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "KeyMove.h"
#endif

#include "KeyMoveDoc.h"
#include "KeyMoveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyMoveView

IMPLEMENT_DYNCREATE(CKeyMoveView, CView)

BEGIN_MESSAGE_MAP(CKeyMoveView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
END_MESSAGE_MAP()

// CKeyMoveView construction/destruction

CKeyMoveView::CKeyMoveView() noexcept
{
	// TODO: add construction code here

}

CKeyMoveView::~CKeyMoveView()
{
}

BOOL CKeyMoveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKeyMoveView drawing

void CKeyMoveView::OnDraw(CDC* /*pDC*/)
{
	CKeyMoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CKeyMoveView printing

BOOL CKeyMoveView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKeyMoveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKeyMoveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKeyMoveView diagnostics

#ifdef _DEBUG
void CKeyMoveView::AssertValid() const
{
	CView::AssertValid();
}

void CKeyMoveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKeyMoveDoc* CKeyMoveView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyMoveDoc)));
	return (CKeyMoveDoc*)m_pDocument;
}
#endif //_DEBUG


// CKeyMoveView message handlers


int CKeyMoveView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_wndChild.Create(TEXT("STATIC"), TEXT("KeyMove"),
					WS_CHILD | WS_VISIBLE | WS_BORDER,
					CRect(100, 100, 200, 200), this, 1234);
	return 0;
}


void CKeyMoveView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CPoint ptChild;	// child window의 좌표
	CRect Rect;		// cgukd window의 좌표 및 크기

	// child window의 두 좌표 정보(스크린 기준)를 알아 온다.
	m_wndChild.GetWindowRect(&Rect);
	ptChild.x = Rect.left;
	ptChild.y = Rect.top;

	// 스크린 기준 좌표를 클라이언트 뷰 기준의 좌표로 환산한다.
	ScreenToClient(&ptChild);

	switch (nChar) {
	case VK_LEFT:			// 왼쪽 화살표 누른 경우.
		ptChild.x -= 10;	// 10픽셀 x좌표 감소
		break;

	case VK_RIGHT:			// 오른쪽 화살표 누른 경우.
		ptChild.x += 10;	// 10픽셀 x좌표 증가
		break;

	case VK_UP:
		ptChild.y -= 10;
		break;

	case VK_DOWN:
		ptChild.y += 10;
		break;
	}


	// 변경된 새 좌표로 child window를 이동.
	m_wndChild.SetWindowPos(&CWnd::wndTop, ptChild.x, ptChild.y, 0, 0,
		SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


// 눌려진 문자키 정보를 자식 윈도우(m_wndChild)에 출력.
void CKeyMoveView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CString strText = TEXT("");
	strText.Format(TEXT("%c"), nChar);

	// 입력한 키가 Enter, Back space, ESC 키가 아니면
	// 해당 ASCII 문자로 Child Window 텍스트를 변경한다.
	if (nChar != VK_RETURN && nChar != VK_BACK && nChar != VK_ESCAPE) {
		m_wndChild.SetWindowText(strText);
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CKeyMoveView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CString strMessage = TEXT("");

	// Space 키에 대한 상태 정보를 수집
	WORD wResult = ::GetKeyState(VK_SPACE);
	BYTE byHigh = HIBYTE(wResult);

	// 상위 바이트의 1번 비트가 1이면 키가 눌려진 상태
	if (byHigh & 0x01)
	{
		strMessage += TEXT("Alt + Space, ");

		// 같은 방법으로 Caps Lock 키의 상태를 검사
		wResult = ::GetKeyState(VK_CAPITAL);
		// 하위 바이트의 1번 비트가 1이면 토글 키가 켜진 상태
		BYTE byLow = LOBYTE(wResult);

		if (byLow & 0x01)	strMessage += TEXT("CAPS LOCK ON");
		else				strMessage += TEXT("CAPS LOCK OFF");

		AfxMessageBox(strMessage);
	}

	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}


void CKeyMoveView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_RETURN)					AfxMessageBox(TEXT("Alt + Enter"));
	else if (nChar == 's' || nChar == 'S')	AfxMessageBox(TEXT("Alt + S"));
	else if (nChar == 'x' || nChar == 'X') {
		//AfxMessageBox(TEXT("Alt + X"));
		::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	}
	CView::OnSysChar(nChar, nRepCnt, nFlags);
}
