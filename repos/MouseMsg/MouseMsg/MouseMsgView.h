
// MouseMsgView.h : interface of the CMouseMsgView class
//

#pragma once


class CMouseMsgView : public CView
{
protected: // create from serialization only
	CMouseMsgView() noexcept;
	DECLARE_DYNCREATE(CMouseMsgView)

// Attributes
public:
	CMouseMsgDoc* GetDocument() const;

// Operations
public:
	CPoint	m_ptMouse;	// ���콺 �������� ��ǥ
	CPoint	m_ptLeft;	// ���콺 ���� ��ư�� ���� ��ǥ
	CPoint	m_ptRight;	// ���콺 ���� ��ư�� ���� ��ǥ

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
	virtual ~CMouseMsgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in MouseMsgView.cpp
inline CMouseMsgDoc* CMouseMsgView::GetDocument() const
   { return reinterpret_cast<CMouseMsgDoc*>(m_pDocument); }
#endif

