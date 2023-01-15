// AstrographView.h : interface of the CAstrographView class
//
/////////////////////////////////////////////////////////////////////////////

class CAstrographView : public CView
{
protected: // create from serialization only
	CAstrographView();
	DECLARE_DYNCREATE(CAstrographView)

// Attributes
public:
	int toDegrees( CPoint &p, int &rad );
	int doPop( CPoint &p, char *file);
	GR_ASPT *findAspect( CPoint &p );
	void setupGrfas();
	void updateGrfas();
	int fontSize(int div);
	void computeRadiusData();
	CAstrographDoc* GetDocument();
    void toWMF(char *name, int place, int color, int rev);
	void toDib( imgdes *image, int color, int rev, int dib );
    void DoPrint();
	void DoExport() { OnFileExport();}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrographView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAstrographView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAstrographView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnViewFitwin();
	afx_msg void OnUpdateViewFitwin(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnViewLargerfont();
	afx_msg void OnViewSmallerfont();
	afx_msg void OnGraphicsSigntickwheel();
	afx_msg void OnUpdateGraphicsSigntickwheel(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsDecantickwheel();
	afx_msg void OnUpdateGraphicsDecantickwheel(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsDegreetickwheel();
	afx_msg void OnUpdateGraphicsDegreetickwheel(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsPlotclassically();
	afx_msg void OnUpdateGraphicsPlotclassically(CCmdUI* pCmdUI);
	afx_msg void OnGraphShowhousedegrees();
	afx_msg void OnUpdateGraphShowhousedegrees(CCmdUI* pCmdUI);
	afx_msg void OnGraphShowhousenumbers();
	afx_msg void OnUpdateGraphShowhousenumbers(CCmdUI* pCmdUI);
	afx_msg void OnGraphShowsignlines();
	afx_msg void OnUpdateGraphShowsignlines(CCmdUI* pCmdUI);
	afx_msg void OnGraphShowsignname();
	afx_msg void OnUpdateGraphShowsignname(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsInnerouterhousecusps();
	afx_msg void OnUpdateGraphicsInnerouterhousecusps(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsHousenumbersoutside();
	afx_msg void OnUpdateGraphicsHousenumbersoutside(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsShowplanetdegrees();
	afx_msg void OnUpdateGraphicsShowplanetdegrees(CCmdUI* pCmdUI);
	afx_msg void OnGraphShowaspectgrid();
	afx_msg void OnUpdateGraphShowaspectgrid(CCmdUI* pCmdUI);
	afx_msg void OnGraphShowaspects();
	afx_msg void OnUpdateGraphShowaspects(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsDecreasehousecusps();
	afx_msg void OnGraphicsIncreasehousecusps();
	afx_msg void OnGraphicsNormalhousecusps();
	afx_msg void OnGraphUseglyphs();
	afx_msg void OnUpdateGraphUseglyphs(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsUsefirstchart();
	afx_msg void OnUpdateGraphicsUsefirstchart(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsUsenextchart();
	afx_msg void OnUpdateGraphicsUsenextchart(CCmdUI* pCmdUI);
	afx_msg void OnGraphicsUseprevchart();
	afx_msg void OnUpdateGraphicsUseprevchart(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnOptionsGraphicoptions();
	afx_msg void OnOptionsDirectories();
	afx_msg void OnEditCopy();
	afx_msg void OnOptionsGraphicfileconversionoptions();
	afx_msg void OnUpdateView(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsGraphicoptions(CCmdUI* pCmdUI);
	afx_msg void CAstrographView::OnFileExport();
    afx_msg void CAstrographView::OnUpdateFileExport(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSize defaultSize;
	CSize lineDelta;
	CSize pageDelta;
	int cxClient, cyClient, cxChar, cyChar;
	CRect rActive;
	int fToFit;
	int cxLeftOffset, cyTopOffset;
	int cxLeftMgn, cyTopMgn;
	float scale, fontScale;
	Radius radiusData;
	GraphicDataGroup *dataGroup, *compGroup;
	LOGFONT *pGlyphSpec, *pDegSpec, *pTickGlyphSpec;
    CFont *pDataFnt, *pGlyphFnt, *pDegFnt, *pTickGlyphFnt;
    CFont *pBdDataFnt;
    AstDrawBase *baseMetrics;
    CBrush *pbBack;
    unsigned short drawMode;
	short which_houses, asc_min, offset, old_asc_min;
	GR_CHART *pCurChart;
	PlanetPlotter *plot;
	PlanetPlotter *plot2;
	CFont *pGridFont;
	short gridMaxpt;
	GR_ASPT *gridAspts;
	short gridCnt;
	GraphData *data;
	short _type;
	CRect rOther;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in AstrographView.cpp
inline CAstrographDoc* CAstrographView::GetDocument()
   { return (CAstrographDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
