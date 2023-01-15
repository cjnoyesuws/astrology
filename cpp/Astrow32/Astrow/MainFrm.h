// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
   void DoOptions( struct OPTIONS &op, char *cap );
   void DoQdt();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateFileOpenBirth(CCmdUI* pCmdUI);
	afx_msg void OnFileOpenBirth();
	afx_msg void OnFileSavebirth();
	afx_msg void OnUpdateFileSavebirth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePageSetup(CCmdUI* pCmdUI);
	afx_msg void OnFilePageSetup();
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg void OnChartBsha();
	afx_msg void OnUpdateChartBsha(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChartBso(CCmdUI* pCmdUI);
	afx_msg void OnChartBso();
	afx_msg void OnChartCompat();
	afx_msg void OnUpdateChartCompat(CCmdUI* pCmdUI);
	afx_msg void OnChartComplete();
	afx_msg void OnUpdateChartComplete(CCmdUI* pCmdUI);
	afx_msg void OnChartCompletebasmid();
	afx_msg void OnUpdateChartCompletebasmid(CCmdUI* pCmdUI);
	afx_msg void OnChartCompletefullmid();
	afx_msg void OnUpdateChartCompletefullmid(CCmdUI* pCmdUI);
	afx_msg void OnChartCompos();
	afx_msg void OnUpdateChartCompos(CCmdUI* pCmdUI);
	afx_msg void OnChartDefault();
	afx_msg void OnUpdateChartDefault(CCmdUI* pCmdUI);
	afx_msg void OnChartNumeric();
	afx_msg void OnUpdateChartNumeric(CCmdUI* pCmdUI);
	afx_msg void OnChartProgress();
	afx_msg void OnUpdateChartProgress(CCmdUI* pCmdUI);
	afx_msg void OnChartReloc();
	afx_msg void OnUpdateChartReloc(CCmdUI* pCmdUI);
	afx_msg void OnChartReturn();
	afx_msg void OnUpdateChartReturn(CCmdUI* pCmdUI);
	afx_msg void OnChartSignhouse();
	afx_msg void OnUpdateChartSignhouse(CCmdUI* pCmdUI);
	afx_msg void OnChartTrans();
	afx_msg void OnUpdateChartTrans(CCmdUI* pCmdUI);
	afx_msg void OnDataBirthinfo();
	afx_msg void OnUpdateDataBirthinfo(CCmdUI* pCmdUI);
	afx_msg void OnDataBirthrect();
	afx_msg void OnUpdateDataBirthrect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDataCompatinfo(CCmdUI* pCmdUI);
	afx_msg void OnDataCompatinfo();
	afx_msg void OnUpdateDataCompatrect(CCmdUI* pCmdUI);
	afx_msg void OnDataCompatrect();
	afx_msg void OnUpdateDataProgress(CCmdUI* pCmdUI);
	afx_msg void OnDataProgress();
	afx_msg void OnDataReloc();
	afx_msg void OnUpdateDataReloc(CCmdUI* pCmdUI);
	afx_msg void OnDataReturndata();
	afx_msg void OnUpdateDataReturndata(CCmdUI* pCmdUI);
	afx_msg void OnDataTransitsdata();
	afx_msg void OnUpdateDataTransitsdata(CCmdUI* pCmdUI);
	afx_msg void OnDataTransitsinfo();
	afx_msg void OnUpdateDataTransitsinfo(CCmdUI* pCmdUI);
	afx_msg void OnHelpAstrology();
	afx_msg void OnUpdateHelpAstrology(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsAllcheck(CCmdUI* pCmdUI);
	afx_msg void OnOptionsAllcheck();
	afx_msg void OnUpdateOptionsBirth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsCompatibility(CCmdUI* pCmdUI);
	afx_msg void OnOptionsCompatibility();
	afx_msg void OnOptionsBirth();
	afx_msg void OnUpdateOptionsComposite(CCmdUI* pCmdUI);
	afx_msg void OnOptionsComposite();
	afx_msg void OnOptionsDirectories();
	afx_msg void OnUpdateOptionsDirectories(CCmdUI* pCmdUI);
	afx_msg void OnOptionsGraphicoptions();
	afx_msg void OnUpdateOptionsGraphicoptions(CCmdUI* pCmdUI);
	afx_msg void OnOptionsNumeric();
	afx_msg void OnUpdateOptionsNumeric(CCmdUI* pCmdUI);
	afx_msg void OnOptionsPrinting();
	afx_msg void OnUpdateOptionsPrinting(CCmdUI* pCmdUI);
	afx_msg void OnOptionsProg();
	afx_msg void OnUpdateOptionsProg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsQdt(CCmdUI* pCmdUI);
	afx_msg void OnOptionsQdt();
	afx_msg void OnUpdateOptionsReloc(CCmdUI* pCmdUI);
	afx_msg void OnOptionsReloc();
	afx_msg void OnOptionsText();
	afx_msg void OnUpdateOptionsText(CCmdUI* pCmdUI);
	afx_msg void OnOptionsTransits();
	afx_msg void OnUpdateOptionsTransits(CCmdUI* pCmdUI);
	afx_msg void OnUtilitiesRebuildflist();
	afx_msg void OnUpdateUtilitiesRebuildflist(CCmdUI* pCmdUI);
	afx_msg void OnOptionsViewer();
	afx_msg void OnUpdateOptionsViewer(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnChartOtherchartsCompositetransits();
	afx_msg void OnUpdateChartOtherchartsCompositetransits(CCmdUI* pCmdUI);
	afx_msg void OnChartSpecialtychartsArabicpoints();
	afx_msg void OnUpdateChartSpecialtychartsArabicpoints(CCmdUI* pCmdUI);
	afx_msg void OnChartSpecialtychartsFixedstar();
	afx_msg void OnUpdateChartSpecialtychartsFixedstar(CCmdUI* pCmdUI);
	afx_msg void OnChartSpecialtychartsHeliocentric();
	afx_msg void OnUpdateChartSpecialtychartsHeliocentric(CCmdUI* pCmdUI);
	afx_msg void OnChartSpecialtychartsProblem();
	afx_msg void OnUpdateChartSpecialtychartsProblem(CCmdUI* pCmdUI);
	afx_msg void OnOptionsChartoptionsArabicpointsoptions();
	afx_msg void OnUpdateOptionsChartoptionsArabicpointsoptions(CCmdUI* pCmdUI);
	afx_msg void OnOptionsChartoptionsCompositetransits();
	afx_msg void OnUpdateOptionsChartoptionsCompositetransits(CCmdUI* pCmdUI);
	afx_msg void OnOptionsChartoptionsFixedstar();
	afx_msg void OnUpdateOptionsChartoptionsFixedstar(CCmdUI* pCmdUI);
	afx_msg void OnOptionsGraphicfileconversionoptions();
	afx_msg void OnUpdateOptionsGraphicfileconversionoptions(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditorbs();
	afx_msg void OnUpdateOptionsEditorbs(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEditorsetup();
	afx_msg void OnUpdateOptionsEditorsetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNewUserfilelist(CCmdUI* pCmdUI);
	afx_msg void OnFileNewUserfilelist();
	afx_msg void OnFileOpenUserfilelist();
	afx_msg void OnUpdateFileOpenUserfilelist(CCmdUI* pCmdUI);
	afx_msg void OnHelpCjnoyessw();
	afx_msg void OnUpdateHelpCjnoyessw(CCmdUI* pCmdUI);
	afx_msg void OnHelpOrder();
	afx_msg void OnUpdateHelpOrder(CCmdUI* pCmdUI);
	afx_msg void OnHelpTechsupp();
	afx_msg void OnUpdateHelpTechsupp(CCmdUI* pCmdUI);
	afx_msg void OnHelpVersions();
	afx_msg void OnUpdateHelpVersions(CCmdUI* pCmdUI);
	afx_msg void OnSolararcchart();
	afx_msg void OnUpdateSolararcchart(CCmdUI* pCmdUI);
	afx_msg void OnSolararcdata();
	afx_msg void OnUpdateSolararcdata(CCmdUI* pCmdUI);
	afx_msg void OnSolararcopt();
	afx_msg void OnUpdateSolararcopt(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHarmonicData();
	afx_msg void OnUpdateHarmonicData(CCmdUI *pCmdUI);
	afx_msg void OnHarmonicChart();
	afx_msg void OnUpdateHarmonicChart(CCmdUI *pCmdUI);
	afx_msg void OnHarmonicOptions();
	afx_msg void OnUpdateHarmonicOptions(CCmdUI *pCmdUI);
	afx_msg void OnCreateFolder();
	afx_msg void OnUpdateCreateFolder(CCmdUI *pCmdUI);
	afx_msg void OnChangeFolder();
	afx_msg void OnUpdateChangeFolder(CCmdUI *pCmdUI);
	afx_msg void OnRenameFolder();
	afx_msg void OnUpdateRenameFolder(CCmdUI *pCmdUI);
	afx_msg void OnAdvancedOpt();
	afx_msg void OnUpdateAdvancedOpt(CCmdUI *pCmdUI);
    afx_msg void OnCompressDb();
	afx_msg void OnUpdateCompressDb(CCmdUI *pCmdUI);
    afx_msg void OnToday();
	afx_msg void OnUpdateToday(CCmdUI *pCmdUI);
    afx_msg void OnEphemeris();
	afx_msg void OnUpdateEphemeris(CCmdUI *pCmdUI);
    afx_msg void OnRefMaps();
	afx_msg void OnUpdateRefMaps(CCmdUI *pCmdUI);
    afx_msg void OnBackupDb();
	afx_msg void OnUpdateBackupDb(CCmdUI *pCmdUI);

	afx_msg void OnOptionsSetcurrentlanguage();
	afx_msg void OnUpdateOptionsSetcurrentlanguage(CCmdUI *pCmdUI);
	afx_msg void OnChartwizard();
	afx_msg void OnUpdateChartwizard(CCmdUI *pCmdUI);
	afx_msg void OnFileOpenNew();
	afx_msg void OnUpdateFileOpenNew(CCmdUI *pCmdUI);
	afx_msg void OnReturnWReloc();
	afx_msg void OnUpdateReturnWReloc(CCmdUI *pCmdUI);
	afx_msg void OnReturnWTransits();
	afx_msg void OnUpdateReturnWTransits(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////
