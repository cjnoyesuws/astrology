// astrpgraphView.h : interface of the CAstrpgraphView class
//
/////////////////////////////////////////////////////////////////////////////

class CAstrpgraphView : public CView
{
protected: // create from serialization only
	CAstrpgraphView();
	DECLARE_DYNCREATE(CAstrpgraphView)

// Attributes
public:
	CAstrpgraphDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrpgraphView)
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
	virtual ~CAstrpgraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstrpgraphView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in astrpgraphView.cpp
inline CAstrpgraphDoc* CAstrpgraphView::GetDocument()
   { return (CAstrpgraphDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
