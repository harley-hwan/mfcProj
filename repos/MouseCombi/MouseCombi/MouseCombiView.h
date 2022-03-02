
// MouseCombiView.h : interface of the CMouseCombiView class
//

#pragma once
#include "TrackWnd.h"

class CMouseCombiView : public CView
{
protected: // create from serialization only
	CMouseCombiView() noexcept;
	DECLARE_DYNCREATE(CMouseCombiView)

// Attributes
public:
	CMouseCombiDoc* GetDocument() const;

// Operations
public:

	CPoint		m_ptItemText;		// Ư�� ������ �ؽ�Ʈ�� �·�
	bool		m_bDragFlag;		// �巡�װ� ���۵��� �˸��� �÷���
	CTrackWnd	m_wndTrack;			// ���콺 �̺�Ʈ�� ������ ���ϵ� ������

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
	virtual ~CMouseCombiView();
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in MouseCombiView.cpp
inline CMouseCombiDoc* CMouseCombiView::GetDocument() const
   { return reinterpret_cast<CMouseCombiDoc*>(m_pDocument); }
#endif

