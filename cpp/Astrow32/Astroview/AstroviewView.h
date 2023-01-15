// AstroviewView.h : interface of the CAstroviewView class
//
/////////////////////////////////////////////////////////////////////////////

class CAstroviewView : public CView
{
protected: // create from serialization only
	CAstroviewView();
	DECLARE_DYNCREATE(CAstroviewView)
	int getBreaks( char *pTxt, int len, unsigned char flags, int *array, unsigned char *flary, int nBrkMax );
    int getPrevBreak( char *pText, int len, int offset, unsigned char &flags );
    int getNextBreak( char *pText, int len, int offset, unsigned char &flags );
    int drawPara( char *pTxt, int len, unsigned char &flags, int &ofs, CDC *cv );
    int up1Page();
	void updateLineParaTrans(int ofs );
	void paginate(CDC *pDC, CPrintInfo *pInfo );
	void DrawPrint(CDC *pDC, CPrintInfo *pInfo );
#ifdef PRO
	int SetupPrintCover(CDC *pdc, CPrintInfo *pi, CoverPageData *data );
    int PrintCover(CDC *pdc, CPrintInfo *pi, CoverPageData *data);
#endif    
	void DoPrint();

// Attributes
public:
	void FontSize(LOGFONT *p);
	float fontScale;
	CAstroviewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstroviewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstroviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstroviewView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnViewLargerfonts();
	afx_msg void OnViewSmallerfonts();
	afx_msg void OnEditSearch();
	afx_msg void OnEditSearchcontinue();
	afx_msg void OnUpdateEditSearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSearchcontinue(CCmdUI* pCmdUI);
	afx_msg void OnOptionsViewersetup();
	afx_msg void OnFilePageSetup();
	afx_msg void OnOptionsConversionsetup();
	afx_msg void OnOptionsPrinting();
	afx_msg void OnFileSaveAs();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
	afx_msg void OnEditDel();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateViewLargerfonts(CCmdUI* pCmdUI); 
    afx_msg void OnUpdateViewSmallerfonts(CCmdUI* pCmdUI); 
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
VirtualTextBuffer *pVTBuf;
LOC top, bottom;
LOC xtop, xbottom;
int cxChar, cyChar, cxClient, cyClient;
CFont *pfReg, *pfBold, *pfItal, *pfHead;
CBrush *pbBack;
COLORREF ctReg, ctBold, ctItal, ctHead, ctSel;
COLORREF cbReg, cbSel, cbUsed;
int cyCur, cxCur, cyLines, cxStart, cxTab, cxCharTab;
int cyStart, cyHead;
CRect margins;
CRect rActive;
CString search;
int selPara, dirty;
int *pLineParaTrans;
CSize lineDelta;
CSize pageDelta;
int pageCount;
int *pageParas;
CFont *pfGlyph;
CBitmap *pBmUser;
FILE *stream;
int ok;
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in AstroviewView.cpp
inline CAstroviewDoc* CAstroviewView::GetDocument()
   { return (CAstroviewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
