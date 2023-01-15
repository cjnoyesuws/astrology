// AsxView.h : interface of the CAsxView class
//


#pragma once


class CAsxView : public CView
{
protected: // create from serialization only
	CAsxView();
	DECLARE_DYNCREATE(CAsxView)

// Attributes
public:
	CAsxDoc* GetDocument() const;

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
	virtual ~CAsxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AsxView.cpp
inline CAsxDoc* CAsxView::GetDocument() const
   { return reinterpret_cast<CAsxDoc*>(m_pDocument); }
#endif

