
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
	CPoint ptChild;	// child window�� ��ǥ
	CRect Rect;		// cgukd window�� ��ǥ �� ũ��

	// child window�� �� ��ǥ ����(��ũ�� ����)�� �˾� �´�.
	m_wndChild.GetWindowRect(&Rect);
	ptChild.x = Rect.left;
	ptChild.y = Rect.top;

	// ��ũ�� ���� ��ǥ�� Ŭ���̾�Ʈ �� ������ ��ǥ�� ȯ���Ѵ�.
	ScreenToClient(&ptChild);

	switch (nChar) {
	case VK_LEFT:			// ���� ȭ��ǥ ���� ���.
		ptChild.x -= 10;	// 10�ȼ� x��ǥ ����
		break;

	case VK_RIGHT:			// ������ ȭ��ǥ ���� ���.
		ptChild.x += 10;	// 10�ȼ� x��ǥ ����
		break;

	case VK_UP:
		ptChild.y -= 10;
		break;

	case VK_DOWN:
		ptChild.y += 10;
		break;
	}


	// ����� �� ��ǥ�� child window�� �̵�.
	m_wndChild.SetWindowPos(&CWnd::wndTop, ptChild.x, ptChild.y, 0, 0,
		SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


// ������ ����Ű ������ �ڽ� ������(m_wndChild)�� ���.
void CKeyMoveView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CString strText = TEXT("");
	strText.Format(TEXT("%c"), nChar);

	// �Է��� Ű�� Enter, Back space, ESC Ű�� �ƴϸ�
	// �ش� ASCII ���ڷ� Child Window �ؽ�Ʈ�� �����Ѵ�.
	if (nChar != VK_RETURN && nChar != VK_BACK && nChar != VK_ESCAPE) {
		m_wndChild.SetWindowText(strText);
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CKeyMoveView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CString strMessage = TEXT("");

	// Space Ű�� ���� ���� ������ ����
	WORD wResult = ::GetKeyState(VK_SPACE);
	BYTE byHigh = HIBYTE(wResult);

	// ���� ����Ʈ�� 1�� ��Ʈ�� 1�̸� Ű�� ������ ����
	if (byHigh & 0x01)
	{
		strMessage += TEXT("Alt + Space, ");

		// ���� ������� Caps Lock Ű�� ���¸� �˻�
		wResult = ::GetKeyState(VK_CAPITAL);
		// ���� ����Ʈ�� 1�� ��Ʈ�� 1�̸� ��� Ű�� ���� ����
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
