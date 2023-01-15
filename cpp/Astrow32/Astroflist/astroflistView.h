// astroflistView.h : interface of the CAstroflistView class
//
/////////////////////////////////////////////////////////////////////////////

class CAstroflistView : public CView
{
protected: // create from serialization only
	CAstroflistView();
	DECLARE_DYNCREATE(CAstroflistView)

// Attributes
public:
	CAstroflistDoc* GetDocument();
	
// Operations
public:
    
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstroflistView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstroflistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_findPos;
	XPFILE_DB cut_buf, *editptr;
    int was_cut, was_copy, was_delete, edit_at;
    int can_undo, can_paste;
	int cxChar, cyChar, cxStart, cyStart;
    int cxWidName, cyDepth, cyRule, cxWid, cxClient, cyClient;
    int cxWidFlags, cxLeft, yCnt;
    LPLOGFONT pLogFont;
	CFont *pFnt;
    CPen *ppnNorm, *ppnSel;
    CBrush *pbrSel, *pbrNorm;
    CBitmap *pbmGra, *pbmTxt, *pbmChk, *pbmGrid;
    UINT clipFmt;
	int nTopItem, nCursor;
	int drawHeader(CDC *pDC);
    int drawItem(CDC *pDC, XPFILE_DB *i, int y, int mrk);
	BOOL bitmap( CDC *pdc, CBitmap *pb, int x, int y, DWORD rop=SRCCOPY );
	void DoBatchOfFiles(enum filetype ftype, UINT cmd, FileListArray *fla, int type);


// Generated message map functions
protected:
	//{{AFX_MSG(CAstroflistView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOptionsDirectories();
	afx_msg void OnUpdateOptionsDirectories(CCmdUI* pCmdUI);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnFileView();
	afx_msg void OnUpdateFileView(CCmdUI* pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
	afx_msg void OnFileKill();
	afx_msg void OnUpdateFileKill(CCmdUI* pCmdUI);
	afx_msg void OnOptionsAllcheck();
	afx_msg void OnUpdateOptionsAllcheck(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesClearselection();
	afx_msg void OnUpdateUtilitiesClearselection(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesEditentry();
	afx_msg void OnUpdateUtilitiesEditentry(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesSort();
	afx_msg void OnUpdateUtilitiesSort(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesreadfiledata();
	afx_msg void OnUpdateUtilitiesreadfiledata(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesRebuildflist();
	afx_msg void OnUpdateUtilitiesRebuildflist(CCmdUI* pCmdUI);
	afx_msg void OnFileNewCommentfile();
	afx_msg void OnUpdateFileNewCommentfile(CCmdUI* pCmdUI);
	afx_msg void OnFileNewCoverpage();
	afx_msg void OnUpdateFileNewCoverpage(CCmdUI* pCmdUI);
	afx_msg void OnFileOpenCommentfile();
	afx_msg void OnUpdateFileOpenCommentfile(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesArchivecharts();
	afx_msg void OnUpdateUtilitiesArchivecharts(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesUnarchivecharts();
	afx_msg void OnUpdateUtilitiesUnarchivecharts(CCmdUI* pCmdUI);
	afx_msg	void OnUpdateEditSearch(CCmdUI* pCmdUI); 	
	afx_msg	void OnUpdatePaste(CCmdUI* pCmdUI); 
	afx_msg	void OnEditPaste(); 
	afx_msg	void OnFileEdit(); 
	afx_msg	void OnUpdateFileEdit(CCmdUI* pCmdUI); 
	afx_msg	void OnEditSearch(); 	
	afx_msg	void OnEditSearchCont(); 
	afx_msg	void OnSelectAll(); 
	afx_msg	void OnUpdateSelectAll(CCmdUI* pCmdUI); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in astroflistView.cpp
inline CAstroflistDoc* CAstroflistView::GetDocument()
   { return (CAstroflistDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
