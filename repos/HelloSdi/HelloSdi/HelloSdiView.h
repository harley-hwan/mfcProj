
// HelloSdiView.h : interface of the CHelloSdiView class
//

#pragma once


class CHelloSdiView : public CEditView
{
protected: // create from serialization only
	CHelloSdiView() noexcept;
	DECLARE_DYNCREATE(CHelloSdiView)

// Attributes
public:
	CHelloSdiDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CHelloSdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HelloSdiView.cpp
inline CHelloSdiDoc* CHelloSdiView::GetDocument() const
   { return reinterpret_cast<CHelloSdiDoc*>(m_pDocument); }
#endif

