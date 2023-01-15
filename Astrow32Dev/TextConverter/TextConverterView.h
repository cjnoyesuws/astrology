// TextConverterView.h : interface of the CTextConverterView class
//


#pragma once


class CTextConverterView : public CView
{
protected: // create from serialization only
	CTextConverterView();
	DECLARE_DYNCREATE(CTextConverterView)

// Attributes
public:
	CTextConverterDoc* GetDocument() const;

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
	virtual ~CTextConverterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TextConverterView.cpp
inline CTextConverterDoc* CTextConverterView::GetDocument() const
   { return reinterpret_cast<CTextConverterDoc*>(m_pDocument); }
#endif

