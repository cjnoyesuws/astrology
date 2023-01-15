// AstrowView.h : interface of the CAstrowView class
//
/////////////////////////////////////////////////////////////////////////////

class CAstrowView : public CView
{
protected: // create from serialization only
	CAstrowView();
	DECLARE_DYNCREATE(CAstrowView)

// Attributes
public:
	CAstrowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrowView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstrowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstrowView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AstrowView.cpp
inline CAstrowDoc* CAstrowView::GetDocument()
   { return (CAstrowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
