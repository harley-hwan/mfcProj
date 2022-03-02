
// KeyMoveView.h : interface of the CKeyMoveView class
//

#pragma once


class CKeyMoveView : public CView
{
protected: // create from serialization only
	CKeyMoveView() noexcept;
	DECLARE_DYNCREATE(CKeyMoveView)

// Attributes
public:
	CKeyMoveDoc* GetDocument() const;

// Operations
public:
	CWnd	m_wndChild;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CKeyMoveView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in KeyMoveView.cpp
inline CKeyMoveDoc* CKeyMoveView::GetDocument() const
   { return reinterpret_cast<CKeyMoveDoc*>(m_pDocument); }
#endif

