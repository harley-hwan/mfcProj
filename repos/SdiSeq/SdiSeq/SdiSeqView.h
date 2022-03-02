
// SdiSeqView.h : interface of the CSdiSeqView class
//

#pragma once


class CSdiSeqView : public CView
{
protected: // create from serialization only
	CSdiSeqView() noexcept;
	DECLARE_DYNCREATE(CSdiSeqView)

// Attributes
public:
	CSdiSeqDoc* GetDocument() const;

// Operations
public:

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
	virtual ~CSdiSeqView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SdiSeqView.cpp
inline CSdiSeqDoc* CSdiSeqView::GetDocument() const
   { return reinterpret_cast<CSdiSeqDoc*>(m_pDocument); }
#endif

