// OpenFilesView.h : interface of the COpenFilesView class
//


#pragma once


class COpenFilesView : public CView
{
protected: // create from serialization only
	COpenFilesView();
	DECLARE_DYNCREATE(COpenFilesView)

// Attributes
public:
	COpenFilesDoc* GetDocument() const;

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
	virtual ~COpenFilesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OpenFilesView.cpp
inline COpenFilesDoc* COpenFilesView::GetDocument() const
   { return reinterpret_cast<COpenFilesDoc*>(m_pDocument); }
#endif

