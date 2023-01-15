// AstroeditView.h : interface of the CAstroeditView class
//
/////////////////////////////////////////////////////////////////////////////

class CAstroeditView : public CRichEditView 
{
protected: // create from serialization only
	CAstroeditView();
	DECLARE_DYNCREATE(CAstroeditView)

// Attributes
public:
	BOOL wholeWord;
	BOOL matchCase;
	CString textToFind;
	void SetupCharFormat( CHARFORMAT &cf, COLORREF &cr, LOGFONT *lf );
	ReportStyles *styles;
	CAstroeditDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstroeditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstroeditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstroeditView)
	afx_msg void OnOptionsTextfileconversions();
	afx_msg void OnUpdateEditBoldtext(CCmdUI* pCmdUI);
	afx_msg void OnEditBoldtext();
	afx_msg void OnUpdateEditHeadlinetext(CCmdUI* pCmdUI);
	afx_msg void OnEditHeadlinetext();
	afx_msg void OnUpdateEditItalicunderscoretext(CCmdUI* pCmdUI);
	afx_msg void OnEditItalicunderscoretext();
	afx_msg void OnUpdateEditRegulartext(CCmdUI* pCmdUI);
	afx_msg void OnEditRegulartext();
	afx_msg void OnEditFind();
	afx_msg void OnEditFindcont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AstroeditView.cpp
inline CAstroeditDoc* CAstroeditView::GetDocument()
   { return (CAstroeditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
