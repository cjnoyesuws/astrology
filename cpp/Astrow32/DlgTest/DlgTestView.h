// DlgTestView.h : interface of the CDlgTestView class
//
/////////////////////////////////////////////////////////////////////////////

class CDlgTestView : public CView
{
protected: // create from serialization only
	CDlgTestView();
	DECLARE_DYNCREATE(CDlgTestView)

// Attributes
public:
	CDlgTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDlgTestView)
	afx_msg void OnDialogsArchivefiles();
	afx_msg void OnUpdateDialogsArchivefiles(CCmdUI* pCmdUI);
	afx_msg void OnDialogsCoverpagedata();
	afx_msg void OnUpdateDialogsCoverpagedata(CCmdUI* pCmdUI);
	afx_msg void OnDialogsCustomize();
	afx_msg void OnUpdateDialogsCustomize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDialogsFiledataedit(CCmdUI* pCmdUI);
	afx_msg void OnDialogsFiledataedit();
	afx_msg void OnUpdateDialogsFilename(CCmdUI* pCmdUI);
	afx_msg void OnDialogsFilename();
	afx_msg void OnDialogsKillafile();
	afx_msg void OnUpdateDialogsKillafile(CCmdUI* pCmdUI);
	afx_msg void OnDialogsOptions();
	afx_msg void OnUpdateDialogsOptions(CCmdUI* pCmdUI);
	afx_msg void OnDialogsOrbedit();
	afx_msg void OnUpdateDialogsOrbedit(CCmdUI* pCmdUI);
	afx_msg void OnDialogsPrintoptions();
	afx_msg void OnUpdateDialogsPrintoptions(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDialogsProgressdata(CCmdUI* pCmdUI);
	afx_msg void OnDialogsProgressdata();
	afx_msg void OnDialogsQdtoptions();
	afx_msg void OnUpdateDialogsQdtoptions(CCmdUI* pCmdUI);
	afx_msg void OnDialogsRectification();
	afx_msg void OnUpdateDialogsRectification(CCmdUI* pCmdUI);
	afx_msg void OnDialogsReturndata();
	afx_msg void OnUpdateDialogsReturndata(CCmdUI* pCmdUI);
	afx_msg void OnDialogsTransitdata();
	afx_msg void OnUpdateDialogsTransitdata(CCmdUI* pCmdUI);
	afx_msg void OnDialogsDirectories();
	afx_msg void OnUpdateDialogsDirectories(CCmdUI* pCmdUI);
	afx_msg void OnDatarelocation();
	afx_msg void OnUpdateDatarelocation(CCmdUI* pCmdUI);
	afx_msg void OnDataBirthinfo();
	afx_msg void OnUpdateDataBirthinfo(CCmdUI* pCmdUI);
	afx_msg void OnDataTransitinfo();
	afx_msg void OnUpdateDataTransitinfo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DlgTestView.cpp
inline CDlgTestDoc* CDlgTestView::GetDocument()
   { return (CDlgTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
