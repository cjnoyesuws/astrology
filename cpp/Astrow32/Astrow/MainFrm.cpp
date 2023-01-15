// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "databaseodbc.hpp"
#include "birthinfo.h"
#include "progrdata.h"
#include "rectifydata.h"
#include "relocscr.h"
#include "returndata.h"
#include "transdata.h"
#include "transinfo.h"
#include "pageopt.hpp"
#include "pagesetp.h"
#include "charcons.h"
#include "inifile.hpp"
#include "utlduad.h"
#include "setup.hpp"
#include "attrib.h"
#include "procmsg.h"
#include "compile.hpp"
#include "direc.hpp"
#include "directories.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "DHelpTxt.h"
#include "asthlper.hpp"
#include "astrohelper.h"
#include "customize.h"
#include "chartoptions.h"
#include "output.fns"
#include "compute.fns"
#include "repstyle.hpp"
#include "reportstyles.h"
#include "qdtopt.hpp"
#include "QdtOptions.h"
#include "convopt.hpp"
#include "convertdata.h"
#include "asgflags.h"
#include "asdrawbs.hpp"
#include "graopt.hpp"
#include "gracolor.hpp"
#include "grafont.hpp"
#include "gracolor.h"
#include "grafont.h"
#include "graphopts.h"
#include <io.h>
#include "orbedit.h"
#include "grafilop.hpp"
#include "graphfileopts.h"
#include "edit.hpp"
#include "editdata.h"
#include "solararc.h"
#include "harmonicx.h"
#include "MainFrm.h"
#include "folders.h"
#include "foldername.h"
#include "SelectFolder.h"
#include "AdvancedOpt.h"
#include "setlanguage.h"
#ifdef WIZ
#include "chartwizard.h"
#include "dastfileopen.h"
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int m_harmonic;
extern int read_birth_data(char *file);
extern int do_load_birth_data( CWnd *pPar );
extern int do_save_birth_data( CWnd *pPar );
//extern void index_db( char * );
//extern void make_pop( char * );
//extern void merge_index_db( char * );
extern int write_birth_data(char *file);
void kill_txptps(void);
CString RelocationPersonal;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_FILE_OPENBIRTH, OnUpdateFileOpenBirth)
	ON_COMMAND(ID_FILE_OPENBIRTH, OnFileOpenBirth)
	ON_COMMAND(ID_FILE_SAVEBIRTH, OnFileSavebirth)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVEBIRTH, OnUpdateFileSavebirth)
	ON_UPDATE_COMMAND_UI(ID_FILE_PAGE_SETUP, OnUpdateFilePageSetup)
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
	ON_WM_ENDSESSION()
	ON_COMMAND(ID_CHART_BSHA, OnChartBsha)
	ON_UPDATE_COMMAND_UI(ID_CHART_BSHA, OnUpdateChartBsha)
	ON_UPDATE_COMMAND_UI(ID_CHART_BSO, OnUpdateChartBso)
	ON_COMMAND(ID_CHART_BSO, OnChartBso)
	ON_COMMAND(ID_CHART_COMPAT, OnChartCompat)
	ON_UPDATE_COMMAND_UI(ID_CHART_COMPAT, OnUpdateChartCompat)
	ON_COMMAND(ID_CHART_COMPLETE, OnChartComplete)
	ON_UPDATE_COMMAND_UI(ID_CHART_COMPLETE, OnUpdateChartComplete)
	ON_COMMAND(ID_CHART_COMPLETEBASMID, OnChartCompletebasmid)
	ON_UPDATE_COMMAND_UI(ID_CHART_COMPLETEBASMID, OnUpdateChartCompletebasmid)
	ON_COMMAND(ID_CHART_COMPLETEFULLMID, OnChartCompletefullmid)
	ON_UPDATE_COMMAND_UI(ID_CHART_COMPLETEFULLMID, OnUpdateChartCompletefullmid)
	ON_COMMAND(ID_CHART_COMPOS, OnChartCompos)
	ON_UPDATE_COMMAND_UI(ID_CHART_COMPOS, OnUpdateChartCompos)
	ON_COMMAND(ID_CHART_DEFAULT, OnChartDefault)
	ON_UPDATE_COMMAND_UI(ID_CHART_DEFAULT, OnUpdateChartDefault)
	ON_COMMAND(ID_CHART_NUMERIC, OnChartNumeric)
	ON_UPDATE_COMMAND_UI(ID_CHART_NUMERIC, OnUpdateChartNumeric)
	ON_COMMAND(ID_CHART_PROGRESS, OnChartProgress)
	ON_UPDATE_COMMAND_UI(ID_CHART_PROGRESS, OnUpdateChartProgress)
	ON_COMMAND(ID_CHART_RELOC, OnChartReloc)
	ON_UPDATE_COMMAND_UI(ID_CHART_RELOC, OnUpdateChartReloc)
	ON_COMMAND(ID_CHART_RETURN, OnChartReturn)
	ON_UPDATE_COMMAND_UI(ID_CHART_RETURN, OnUpdateChartReturn)
	ON_COMMAND(ID_CHART_SIGNHOUSE, OnChartSignhouse)
	ON_UPDATE_COMMAND_UI(ID_CHART_SIGNHOUSE, OnUpdateChartSignhouse)
	ON_COMMAND(ID_CHART_TRANS, OnChartTrans)
	ON_UPDATE_COMMAND_UI(ID_CHART_TRANS, OnUpdateChartTrans)
	ON_COMMAND(ID_DATA_BIRTHINFO, OnDataBirthinfo)
	ON_UPDATE_COMMAND_UI(ID_DATA_BIRTHINFO, OnUpdateDataBirthinfo)
	ON_COMMAND(ID_DATA_BIRTHRECT, OnDataBirthrect)
	ON_UPDATE_COMMAND_UI(ID_DATA_BIRTHRECT, OnUpdateDataBirthrect)
	ON_UPDATE_COMMAND_UI(ID_DATA_COMPATINFO, OnUpdateDataCompatinfo)
	ON_COMMAND(ID_DATA_COMPATINFO, OnDataCompatinfo)
	ON_UPDATE_COMMAND_UI(ID_DATA_COMPATRECT, OnUpdateDataCompatrect)
	ON_COMMAND(ID_DATA_COMPATRECT, OnDataCompatrect)
	ON_UPDATE_COMMAND_UI(ID_DATA_PROGRESS, OnUpdateDataProgress)
	ON_COMMAND(ID_DATA_PROGRESS, OnDataProgress)
	ON_COMMAND(ID_DATA_RELOC, OnDataReloc)
	ON_UPDATE_COMMAND_UI(ID_DATA_RELOC, OnUpdateDataReloc)
	ON_COMMAND(ID_DATA_RETURNDATA, OnDataReturndata)
	ON_UPDATE_COMMAND_UI(ID_DATA_RETURNDATA, OnUpdateDataReturndata)
	ON_COMMAND(ID_DATA_TRANSITSDATA, OnDataTransitsdata)
	ON_UPDATE_COMMAND_UI(ID_DATA_TRANSITSDATA, OnUpdateDataTransitsdata)
	ON_COMMAND(ID_DATA_TRANSITSINFO, OnDataTransitsinfo)
	ON_UPDATE_COMMAND_UI(ID_DATA_TRANSITSINFO, OnUpdateDataTransitsinfo)
	ON_COMMAND(ID_HELP_ASTROLOGY, OnHelpAstrology)
	ON_UPDATE_COMMAND_UI(ID_HELP_ASTROLOGY, OnUpdateHelpAstrology)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ALLCHECK, OnUpdateOptionsAllcheck)
	ON_COMMAND(ID_OPTIONS_ALLCHECK, OnOptionsAllcheck)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_BIRTH, OnUpdateOptionsBirth)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_COMPATIBILITY, OnUpdateOptionsCompatibility)
	ON_COMMAND(ID_OPTIONS_COMPATIBILITY, OnOptionsCompatibility)
	ON_COMMAND(ID_OPTIONS_BIRTH, OnOptionsBirth)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_COMPOSITE, OnUpdateOptionsComposite)
	ON_COMMAND(ID_OPTIONS_COMPOSITE, OnOptionsComposite)
	ON_COMMAND(ID_OPTIONS_DIRECTORIES, OnOptionsDirectories)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DIRECTORIES, OnUpdateOptionsDirectories)
	ON_COMMAND(ID_OPTIONS_GRAPHICOPTIONS, OnOptionsGraphicoptions)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_GRAPHICOPTIONS, OnUpdateOptionsGraphicoptions)
	ON_COMMAND(ID_OPTIONS_NUMERIC, OnOptionsNumeric)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_NUMERIC, OnUpdateOptionsNumeric)
	ON_COMMAND(ID_OPTIONS_PRINTING, OnOptionsPrinting)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRINTING, OnUpdateOptionsPrinting)
	ON_COMMAND(ID_OPTIONS_PROG, OnOptionsProg)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_PROG, OnUpdateOptionsProg)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_QDT, OnUpdateOptionsQdt)
	ON_COMMAND(ID_OPTIONS_QDT, OnOptionsQdt)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_RELOC, OnUpdateOptionsReloc)
	ON_COMMAND(ID_OPTIONS_RELOC, OnOptionsReloc)
	ON_COMMAND(ID_OPTIONS_TEXT, OnOptionsText)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_TEXT, OnUpdateOptionsText)
	ON_COMMAND(ID_OPTIONS_TRANSITS, OnOptionsTransits)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_TRANSITS, OnUpdateOptionsTransits)
	ON_COMMAND(ID_UTILITIES_REBUILDFLIST, OnUtilitiesRebuildflist)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_REBUILDFLIST, OnUpdateUtilitiesRebuildflist)
	ON_COMMAND(ID_OPTIONS_VIEWER, OnOptionsViewer)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEWER, OnUpdateOptionsViewer)
	ON_WM_CLOSE()
	ON_COMMAND(ID_CHART_OTHERCHARTS_COMPOSITETRANSITS, OnChartOtherchartsCompositetransits)
	ON_UPDATE_COMMAND_UI(ID_CHART_OTHERCHARTS_COMPOSITETRANSITS, OnUpdateChartOtherchartsCompositetransits)
	ON_COMMAND(ID_CHART_SPECIALTYCHARTS_ARABICPOINTS, OnChartSpecialtychartsArabicpoints)
	ON_UPDATE_COMMAND_UI(ID_CHART_SPECIALTYCHARTS_ARABICPOINTS, OnUpdateChartSpecialtychartsArabicpoints)
	ON_COMMAND(ID_CHART_SPECIALTYCHARTS_FIXEDSTAR, OnChartSpecialtychartsFixedstar)
	ON_UPDATE_COMMAND_UI(ID_CHART_SPECIALTYCHARTS_FIXEDSTAR, OnUpdateChartSpecialtychartsFixedstar)
	ON_COMMAND(ID_CHART_SPECIALTYCHARTS_HELIOCENTRIC, OnChartSpecialtychartsHeliocentric)
	ON_UPDATE_COMMAND_UI(ID_CHART_SPECIALTYCHARTS_HELIOCENTRIC, OnUpdateChartSpecialtychartsHeliocentric)
	ON_COMMAND(ID_CHART_SPECIALTYCHARTS_PROBLEM, OnChartSpecialtychartsProblem)
	ON_UPDATE_COMMAND_UI(ID_CHART_SPECIALTYCHARTS_PROBLEM, OnUpdateChartSpecialtychartsProblem)
	ON_COMMAND(ID_OPTIONS_CHARTOPTIONS_ARABICPOINTSOPTIONS, OnOptionsChartoptionsArabicpointsoptions)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_CHARTOPTIONS_ARABICPOINTSOPTIONS, OnUpdateOptionsChartoptionsArabicpointsoptions)
	ON_COMMAND(ID_OPTIONS_CHARTOPTIONS_COMPOSITETRANSITS, OnOptionsChartoptionsCompositetransits)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_CHARTOPTIONS_COMPOSITETRANSITS, OnUpdateOptionsChartoptionsCompositetransits)
	ON_COMMAND(ID_OPTIONS_CHARTOPTIONS_FIXEDSTAR, OnOptionsChartoptionsFixedstar)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_CHARTOPTIONS_FIXEDSTAR, OnUpdateOptionsChartoptionsFixedstar)
	ON_COMMAND(ID_OPTIONS_GRAPHICFILECONVERSIONOPTIONS, OnOptionsGraphicfileconversionoptions)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_GRAPHICFILECONVERSIONOPTIONS, OnUpdateOptionsGraphicfileconversionoptions)
	ON_COMMAND(ID_OPTIONS_EDITORBS, OnOptionsEditorbs)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_EDITORBS, OnUpdateOptionsEditorbs)
	ON_COMMAND(ID_OPTIONS_EDITORSETUP, OnOptionsEditorsetup)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_EDITORSETUP, OnUpdateOptionsEditorsetup)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW_USERFILELIST, OnUpdateFileNewUserfilelist)
	ON_COMMAND(ID_FILE_NEW_USERFILELIST, OnFileNewUserfilelist)
	ON_COMMAND(ID_FILE_OPEN_USERFILELIST, OnFileOpenUserfilelist)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_USERFILELIST, OnUpdateFileOpenUserfilelist)
	ON_COMMAND(ID_HELP_CJNOYESSW, OnHelpCjnoyessw)
	ON_UPDATE_COMMAND_UI(ID_HELP_CJNOYESSW, OnUpdateHelpCjnoyessw)
	ON_COMMAND(ID_HELP_ORDER, OnHelpOrder)
	ON_UPDATE_COMMAND_UI(ID_HELP_ORDER, OnUpdateHelpOrder)
	ON_COMMAND(ID_HELP_TECHSUPP, OnHelpTechsupp)
	ON_UPDATE_COMMAND_UI(ID_HELP_TECHSUPP, OnUpdateHelpTechsupp)
	ON_COMMAND(ID_HELP_VERSIONS, OnHelpVersions)
	ON_UPDATE_COMMAND_UI(ID_HELP_VERSIONS, OnUpdateHelpVersions)
	ON_COMMAND(ID_SOLARARCCHART, OnSolararcchart)
	ON_UPDATE_COMMAND_UI(ID_SOLARARCCHART, OnUpdateSolararcchart)
	ON_COMMAND(ID_SOLARARCDATA, OnSolararcdata)
	ON_UPDATE_COMMAND_UI(ID_SOLARARCDATA, OnUpdateSolararcdata)
	ON_COMMAND(ID_SOLARARCOPT, OnSolararcopt)
	ON_UPDATE_COMMAND_UI(ID_SOLARARCOPT, OnUpdateSolararcopt)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_DATA_HARMONICDATA, OnHarmonicData)
	ON_UPDATE_COMMAND_UI(ID_DATA_HARMONICDATA, OnUpdateHarmonicData)
	ON_COMMAND(ID_OTHERCHARTS_HARMONIC, OnHarmonicChart)
	ON_UPDATE_COMMAND_UI(ID_OTHERCHARTS_HARMONIC, OnUpdateHarmonicChart)
	ON_COMMAND(ID_HARMONIC_OPTIONS, OnHarmonicOptions)
	ON_UPDATE_COMMAND_UI(ID_HARMONIC_OPTIONS, OnUpdateHarmonicOptions)
	ON_COMMAND(ID_FOLDERS_CREATEFOLDER, OnCreateFolder)
	ON_UPDATE_COMMAND_UI(ID_FOLDERS_CREATEFOLDER, OnUpdateCreateFolder)
	ON_COMMAND(ID_FOLDERS_CHANGE, OnChangeFolder)
	ON_UPDATE_COMMAND_UI(ID_FOLDERS_CHANGE, OnUpdateChangeFolder)
	ON_COMMAND(ID_FOLDERS_RENAME, OnRenameFolder)
	ON_UPDATE_COMMAND_UI(ID_FOLDERS_RENAME, OnUpdateRenameFolder)
	ON_COMMAND(ID_OPTIONS_ADVANCED, OnAdvancedOpt)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ADVANCED, OnUpdateAdvancedOpt)
    ON_COMMAND(ID_BACKUP, OnBackupDb)
	ON_UPDATE_COMMAND_UI(ID_BACKUP, OnUpdateBackupDb)
    ON_COMMAND(ID_COMPRESSDATABASE, OnCompressDb)
	ON_UPDATE_COMMAND_UI(ID_COMPRESSDATABASE, OnUpdateCompressDb)
    ON_COMMAND(ID_TODAY, OnToday)
	ON_UPDATE_COMMAND_UI(ID_TODAY, OnUpdateToday)
    ON_COMMAND(ID_EPHEMERIS, OnEphemeris)
	ON_UPDATE_COMMAND_UI(ID_EPHEMERIS, OnUpdateEphemeris)
    ON_COMMAND(ID_REFMAPS, OnRefMaps)
	ON_UPDATE_COMMAND_UI(ID_REFMAPS, OnUpdateRefMaps)
	ON_COMMAND(ID_OPTIONS_SETCURRENTLANGUAGE, OnOptionsSetcurrentlanguage)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SETCURRENTLANGUAGE, OnUpdateOptionsSetcurrentlanguage)
	ON_WM_PAINT()
	ON_COMMAND(ID_CHARTWIZARD, OnChartwizard)
	ON_UPDATE_COMMAND_UI(ID_CHARTWIZARD, OnUpdateChartwizard)
	ON_COMMAND(ID_FILE_OPEN_NEW, OnFileOpenNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_NEW, OnUpdateFileOpenNew)
	ON_COMMAND(ID_RETURN_W_RELOC, OnReturnWReloc)
	ON_UPDATE_COMMAND_UI(ID_RETURN_W_RELOC, OnUpdateReturnWReloc)
	ON_COMMAND(ID_RETURN_W_TRANSITS, OnReturnWTransits)
	ON_UPDATE_COMMAND_UI(ID_RETURN_W_TRANSITS, OnUpdateReturnWTransits)
	END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int fAllChecked = 1;
int fIsQuitting = 0;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
CMDIFrameWnd::OnCreate(lpCreateStruct);
#ifdef WIZ
    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
#endif
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
#ifdef WIZ
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
#endif
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	CDC *pDC = new CDC();
	pDC->CreateIC("DISPLAY", 0, 0, 0);
	cs.x = 0;
	cs.y = 0;
	cs.cx = pDC->GetDeviceCaps(HORZRES);
	cs.cy = pDC->GetDeviceCaps(VERTRES);
	delete pDC;
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateFileOpenBirth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnFileOpenBirth() 
{
	// TODO: Add your command handler code here
	do_load_birth_data( this );
}

void CMainFrame::OnFileSavebirth() 
{
	// TODO: Add your command handler code here
	do_save_birth_data( this );
}

void CMainFrame::OnUpdateFileSavebirth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateFilePageSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnFilePageSetup() 
{
	// TODO: Add your command handler code here
	PageData pd;
	pd.getFromIni(PageOpt_SEC);
	CPageSetp cps;
	cps.SetData(pd);
	if ( cps.DoModal() == IDOK ) {
	   cps.GetData(pd);
	   pd.saveToIni(PageOpt_SEC);
	   }
}

void CMainFrame::OnEndSession(BOOL bEnding) 
{
	CMDIFrameWnd::OnEndSession(bEnding);
	
	// TODO: Add your message handler code here
 
 }

void CMainFrame::OnChartBsha() 
{
	// TODO: Add your command handler code here
	ChartCompiler *cc;
    enum ChartType ct;
	ct = SgnHseAsp;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
}

void CMainFrame::OnUpdateChartBsha(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateChartBso(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnChartBso() 
{
	// TODO: Add your command handler code here
	ChartCompiler *cc;
    enum ChartType ct;
	ct = BirthSgnOnly;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
}

void CMainFrame::OnChartCompat() 
{
	// TODO: Add your command handler code here
	ChartCompiler *cc;
    enum ChartType ct;
	ct = Compatibility;
	cc = new CompChartCompiler( this, ct );
	cc->runChart();
    delete cc;
}

void CMainFrame::OnUpdateChartCompat(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnChartComplete() 
{
	// TODO: Add your command handler code here
	ChartCompiler *cc;
    enum ChartType ct;
	ct = Complete;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
}

void CMainFrame::OnUpdateChartComplete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnChartCompletebasmid() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE
	ChartCompiler *cc;
    enum ChartType ct;
	ct = CompleteBMid;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif
}

void CMainFrame::OnUpdateChartCompletebasmid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartCompletefullmid() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE
	ChartCompiler *cc;
    enum ChartType ct;
	ct = CompleteFMid;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif
}

void CMainFrame::OnUpdateChartCompletefullmid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE
	pCmdUI->Enable(TRUE);
#endif
}


void CMainFrame::OnChartCompos() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	ChartCompiler *cc;
    enum ChartType ct;

	ct = Compos;
    cc = new CompChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif
}

void CMainFrame::OnUpdateChartCompos(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartDefault() 
{
	// TODO: Add your command handler code here
	ChartCompiler *cc;
    enum ChartType ct;
	ct = DefaultChart;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
}

void CMainFrame::OnUpdateChartDefault(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnChartNumeric() 
{
	// TODO: Add your command handler code here
	ChartCompiler *cc;
    enum ChartType ct;
	ct = Numeric;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
}

void CMainFrame::OnUpdateChartNumeric(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnChartProgress() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	ChartCompiler *cc;
    enum ChartType ct;
	
	ct = Progress;
	cc = new ProgChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif
}

void CMainFrame::OnUpdateChartProgress(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE	
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartReloc() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	ChartCompiler *cc;
    enum ChartType ct;

	ct = Reloc;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif
}

void CMainFrame::OnUpdateChartReloc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE	
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartReturn() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	ChartCompiler *cc;
    enum ChartType ct;
	
	ct = CReturn;
	cc = new ReturnChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif
}

void CMainFrame::OnUpdateChartReturn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE	
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartSignhouse() 
{
	// TODO: Add your command handler code here
	ChartCompiler *cc;
    enum ChartType ct;
	ct = BirthSgnHse;
	cc = new NatalChartCompiler( this, ct );
	cc->runChart();
    delete cc;
}

void CMainFrame::OnUpdateChartSignhouse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnChartTrans() 
{
	// TODO: Add your command handler code here
	ChartCompiler *cc;
    enum ChartType ct;

	ct = Transits;
	cc = new TransChartCompiler( this, ct );
	cc->runChart();
    delete cc;
}

void CMainFrame::OnUpdateChartTrans(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnDataBirthinfo() 
{
	// TODO: Add your command handler code here
	CBirthInfo cbi;
	cbi.SetData( birth_rec, birth_rectd );
	if ( cbi.DoModal() == IDOK )
	   cbi.GetData( birth_rec, birth_rectd );
}

void CMainFrame::OnUpdateDataBirthinfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnDataBirthrect() 
{
	// TODO: Add your command handler code here
	CRectifyData crd;
	crd.SetData( birth_rectd, birth_rec.birth_data.birth_time, birth_rec.am_pm  );
	if ( crd.DoModal() == IDOK )
	   crd.GetData( birth_rectd );
}

void CMainFrame::OnUpdateDataBirthrect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateDataCompatinfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnDataCompatinfo() 
{
	// TODO: Add your command handler code here
	CBirthInfo cbi;
	cbi.SetData( comp_rec, comp_rectd );
	if ( cbi.DoModal() == IDOK )
	   cbi.GetData( comp_rec, comp_rectd );
}

void CMainFrame::OnUpdateDataCompatrect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnDataCompatrect() 
{
	// TODO: Add your command handler code here
	CRectifyData crd;
	crd.SetData( comp_rectd, comp_rec.birth_data.birth_time, comp_rec.am_pm );
	if ( crd.DoModal() == IDOK )
	   crd.GetData( comp_rectd );
}

void CMainFrame::OnUpdateDataProgress(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE	
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnDataProgress() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE		
	CProgrData cpd;
	cpd.SetData( progress_data );
	if ( cpd.DoModal() == IDOK )
	   cpd.GetData( progress_data );
#endif
}

void CMainFrame::OnDataReloc() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE		
	CRelocScr crs;
   crs.m_personal=RelocationPersonal;
	crs.SetData( reloc_data );
   if ( crs.DoModal() == IDOK ) {
	   crs.GetData( reloc_data );
      RelocationPersonal = crs.m_personal;
      }

#endif
}

void CMainFrame::OnUpdateDataReloc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE		
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnDataReturndata() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE		
	CReturnData crd;
	crd.SetData( return_data );
	if ( crd.DoModal() == IDOK )
	   crd.GetData( return_data );
#endif
}

void CMainFrame::OnUpdateDataReturndata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE		
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnDataTransitsdata() 
{
	// TODO: Add your command handler code here
	CTransData ctd;
	ctd.SetData( transit_data );
	if ( ctd.DoModal() == IDOK )
	   ctd.GetData( transit_data );
}

void CMainFrame::OnUpdateDataTransitsdata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnDataTransitsinfo() 
{
	// TODO: Add your command handler code here
	CTransInfo cti;
	cti.SetData( trans_rec );
	if ( cti.DoModal() == IDOK )
	   cti.GetData( trans_rec );
}

void CMainFrame::OnUpdateDataTransitsinfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnHelpAstrology() 
{
	// TODO: Add your command handler code here
	CAstroHelper *pcah = new CAstroHelper(this);
	pcah->Create(IDD_AST_HELP, this);
}

void CMainFrame::OnUpdateHelpAstrology(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateOptionsAllcheck(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(fAllChecked);
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnOptionsAllcheck() 
{
	// TODO: Add your command handler code here

  fAllChecked ^= 1;
   
}

void CMainFrame::OnUpdateOptionsBirth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateOptionsCompatibility(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnOptionsCompatibility() 
{
	// TODO: Add your command handler code here

	DoOptions(setup_dat.getCompatOpt().getOpt(),"Compatibility Options");
}

void CMainFrame::OnOptionsBirth() 
{
	// TODO: Add your command handler code here
	
	DoOptions(setup_dat.getBirthOpt().getOpt(),"Natal/Birth Options");
}

void CMainFrame::OnUpdateOptionsComposite(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE	
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnOptionsComposite() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	DoOptions(setup_dat.getComposOpt().getOpt(),"Composite Options");
#endif
}

void CMainFrame::OnOptionsDirectories() 
{
	// TODO: Add your command handler code here
	CDirectories cd;
	cd.SetData(theDirectories);
	if ( cd.DoModal() == IDOK ) {
	   cd.GetData(theDirectories);
	   theDirectories.saveToIni();
	   }
}

void CMainFrame::OnUpdateOptionsDirectories(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnOptionsGraphicoptions() 
{
	// TODO: Add your command handler code here
	unsigned short dm;
	int	fs;
    GraphOptions go;
    go.getFromIni(GraphicsOptions_SEC);
    GraphicColors gc(GetDC());
    gc.getFromIni(GraphicsOptions_SEC);
    GraphicFonts gf;
    gf.getFromIni(GraphicsOptions_SEC);
    CGraphOpts god;
    god.SetGraphicFonts(&gf);
    god.SetGraphicColors(&gc);
    dm = go.getDrawMode();
	fs = go.getFontSize();
	god.SetData(dm,fs); 
    if ( god.DoModal() == IDOK ) {
	   god.GetData(dm,fs); 
	   go.getDrawMode() = dm;
	   go.getFontSize() = fs;
	   go.saveToIni(GraphicsOptions_SEC);
       gc.saveToIni(GraphicsOptions_SEC);
       gf.saveToIni(GraphicsOptions_SEC);
       }
}

void CMainFrame::OnUpdateOptionsGraphicoptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnOptionsNumeric() 
{
	// TODO: Add your command handler code here
	DoOptions(setup_dat.getNumerOpt().getOpt(),"Natal Numeric Options");
}

void CMainFrame::OnUpdateOptionsNumeric(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnOptionsPrinting() 
{
	// TODO: Add your command handler code here
	CDC *dc;
	dc = GetDC();
	ReportStyles rs(dc);
    rs.getFromIni(PrintData_SEC);
    CReportStyles crs(this);
    crs.SetData(&rs);
    if ( crs.DoModal() == IDOK ) {
       rs.saveToIni(PrintData_SEC);
      }
	ReleaseDC(dc);
}

void CMainFrame::OnUpdateOptionsPrinting(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnOptionsProg() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE		
	DoOptions(setup_dat.getProgrOpt().getOpt(),"Progressions Options");
#endif
}

void CMainFrame::OnUpdateOptionsProg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE		
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnUpdateOptionsQdt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnOptionsQdt() 
{
	// TODO: Add your command handler code here
	QdtData qd;
	qd.getFromIni();
	CQdtOptions cqo;
	cqo.SetData(qd);
	if ( cqo.DoModal() == IDOK ) {
	   cqo.GetData(qd);
	   qd.saveToIni();
	   }
}

void CMainFrame::OnUpdateOptionsReloc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE		
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnOptionsReloc() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE	     
	DoOptions(setup_dat.getRelocOpt().getOpt(),"Relocation Options");
#endif
}

void CMainFrame::OnOptionsText() 
{
	// TODO: Add your command handler code here
	CConvertData ccd;
	ConvData cd;
	cd.getFromIni();
	ReportStyles rs(GetDC());
	ccd.SetData(cd,rs);
	if ( ccd.DoModal() == IDOK ) {
	   ccd.GetData(cd);
	   cd.saveToIni();
	   }
}

void CMainFrame::OnUpdateOptionsText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnOptionsTransits() 
{
	// TODO: Add your command handler code here
     	
 DoOptions(setup_dat.getTransOpt().getOpt(),"Transits Options");
}

void CMainFrame::OnUpdateOptionsTransits(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}
/*
void CMainFrame::OnUtilitesReindexbirth() 
{
	// TODO: Add your command handler code here
	index_db( "BIRTH" );
}

void CMainFrame::OnUpdateUtilitesReindexbirth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUtilitiesMakepopupall() 
{
	// TODO: Add your command handler code here
	make_pop( "ALL" );
}

void CMainFrame::OnUpdateUtilitiesMakepopupall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUtilitiesMakepopuplocation() 
{
	// TODO: Add your command handler code here
	make_pop( "LOC" );
}

void CMainFrame::OnUpdateUtilitiesMakepopuplocation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateUtilitiesMakepopupsbirth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUtilitiesMakepopupsbirth() 
{
	// TODO: Add your command handler code here
	make_pop( "BIRTH" );
}

void CMainFrame::OnUtilitiesMergedbbirth() 
{
	// TODO: Add your command handler code here
	merge_index_db( "BIRTH" );
}

void CMainFrame::OnUpdateUtilitiesMergedbbirth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateUtilitiesMergedblocation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUtilitiesMergedblocation() 
{
	// TODO: Add your command handler code here
	merge_index_db( "LOC" );
}

void CMainFrame::OnUtilitiesReindexall() 
{
	// TODO: Add your command handler code here
	index_db( "ALL" );
}

void CMainFrame::OnUpdateUtilitiesReindexall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}
     

void CMainFrame::OnUpdateUtilitiesReindexlocation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUtilitiesReindexlocation() 
{
	// TODO: Add your command handler code here
	index_db( "LOC" );
}
*/
void CMainFrame::OnUtilitiesRebuildflist() 
{
	// TODO: Add your command handler code here

 AstFileList.scanFiles();
	    	
}

void CMainFrame::OnUpdateUtilitiesRebuildflist(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}


void CMainFrame::DoOptions( struct OPTIONS &op, char *cap )
{
#ifdef PRO
 CCustomize cco;
 cco.SetData(op);
 cco.SetCaption(cap);
 if ( cco.DoModal() == IDOK ) {
	cco.GetData(op);
    setup_dat.saveToIni();
    }
return;
#else
 CChartOptions cco;
 cco.SetData(op);
 cco.SetCaption(cap);
if ( cco.DoModal() == IDOK ) {
   cco.GetData(op);
   setup_dat.saveToIni();
   }
return;
#endif
}

void CMainFrame::OnOptionsViewer() 
{
	// TODO: Add your command handler code here
		CDC *dc = GetDC();
	ReportStyles rs(dc, 1);
	rs.getFromIni(ViewerData_SEC);
	CReportStyles crs;
	crs.SetData(&rs);
	if ( crs.DoModal()==IDOK )
	   rs.saveToIni(ViewerData_SEC);

}

void CMainFrame::OnUpdateOptionsViewer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	fIsQuitting = 1;
	CMDIFrameWnd::OnClose();
}

void CMainFrame::DoQdt() 
{
 char buf[300];
 char file[250];
 QdtData qdt;
 SYSTEMTIME tm;

 GetSystemTime(&tm);
 qdt.getFromIni();
 strcpy(birth_rec.name,(const char *)qdt.getName());
 strcpy(trans_rec.name,(const char *)qdt.getEvent());
 DaoBirthDatabase *pbdb = new DaoBirthDatabase();
 pbdb->setBirth(birth_rec);
 pbdb->setRect(birth_rectd);
 if ( pbdb->find() ) {
    birth_rec =pbdb->getBirth();
    RECT_DATA *pr;
	pr = pbdb->getRect();
    birth_rectd = *pr;
    delete pbdb;
    DaoTransitDatabase *ptdb = new DaoTransitDatabase();
    ptdb->setBirth(birth_rec);
    ptdb->setTrans(trans_rec);
    if ( ptdb->find() ) 
       trans_rec = ptdb->getTrans();
    delete ptdb;
    }
 else
    delete pbdb;
 trans_rec.birth_data.birth_date.day = tm.wDay;
 trans_rec.birth_data.birth_date.month = tm.wMonth;
 trans_rec.birth_data.birth_date.year = tm.wYear;
 trans_rec.birth_data.birth_time.hours=tm.wHour;
 trans_rec.birth_data.birth_time.minutes=tm.wMinute;
 if ( tm.wHour > 12 ) {
    trans_rec.am_pm=1;
    trans_rec.birth_data.birth_time.hours-=12;
    }
 transit_data.num_transits = 1;
 qdt.getLastMonth() = tm.wMonth;
 qdt.getLastDay() = tm.wDay;
 qdt.saveToIni();
 ChartCompiler *cc = new TransChartCompiler( this, Transits );
 cc->runChart();
 write_birth_data( set_path( "QDTRADAT.HIS", USER_F ) );
 if ( cc->getOutFp() != NULL ) {
	   strcpy( buf, set_path( cc->getOutFp()->file_name, cc->getOutFp()->folder ) );
       AfxGetApp()->OpenDocumentFile(buf);
	   }
	if ( cc->getGraphFp() != NULL ) {
	   strcpy( buf, set_path( cc->getGraphFp()->file_name, cc->getOutFp()->folder ) );
       AfxGetApp()->OpenDocumentFile(buf);
	   }
 delete cc;
 strcpy( file, set_path( "QDTRADAT.2nd", USER_F ) ); 
 if ( !access( file, 04 ) ) {
    read_birth_data( set_path( "QDTRADAT.2nd", USER_F ) );
    trans_rec.birth_data.birth_date.day = tm.wDay;
    trans_rec.birth_data.birth_date.month = tm.wMonth;
    trans_rec.birth_data.birth_date.year = tm.wYear;
    transit_data.num_transits = 1;
    ChartCompiler *cc = new TransChartCompiler( this, Transits );
    cc->runChart();
    write_birth_data( set_path( "QDTRADAT.HIS", USER_F ) );
    if ( cc->getOutFp() != NULL ) {
	   strcpy( buf, set_path( cc->getOutFp()->file_name, cc->getOutFp()->folder ) );
       AfxGetApp()->OpenDocumentFile(buf);
	   }
	if ( cc->getGraphFp() != NULL ) {
	   strcpy( buf, set_path( cc->getGraphFp()->file_name, cc->getGraphFp()->folder) );
       AfxGetApp()->OpenDocumentFile(buf);
	   }
	if ( cc->getGridFp() != NULL ) {
	   strcpy( buf, set_path( cc->getGridFp()->file_name, cc->getGridFp()->folder) );
       AfxGetApp()->OpenDocumentFile(buf);
	   }
	delete cc;
    }
 read_birth_data( set_path( "ASTRODAT.HIS", USER_F ) );
}



void CMainFrame::OnChartOtherchartsCompositetransits() 
{
	// TODO: Add your command handler code here
#ifdef PRO
	ChartCompiler *cc;
    enum ChartType ct;
	
	ct = ComposTrans;
	cc = new ComTrnChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif	
}

void CMainFrame::OnUpdateChartOtherchartsCompositetransits(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartSpecialtychartsArabicpoints() 
{
	// TODO: Add your command handler code here
#ifdef PRO
    ChartCompiler *cc;
    enum ChartType ct;
	
	ct = Arabic;
	cc = new OtherChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif	
	
}

void CMainFrame::OnUpdateChartSpecialtychartsArabicpoints(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartSpecialtychartsFixedstar() 
{
	// TODO: Add your command handler code here
#ifdef PRO
    ChartCompiler *cc;
    enum ChartType ct;
	
	ct = Fixed;
	cc = new OtherChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif	
	
}

void CMainFrame::OnUpdateChartSpecialtychartsFixedstar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartSpecialtychartsHeliocentric() 
{
	// TODO: Add your command handler code here
#ifdef PRO
    ChartCompiler *cc;
    enum ChartType ct;
	
	ct = Helio;
	cc = new OtherChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif	
	
}

void CMainFrame::OnUpdateChartSpecialtychartsHeliocentric(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnChartSpecialtychartsProblem() 
{
	// TODO: Add your command handler code here
#ifdef PRO
    ChartCompiler *cc;
    enum ChartType ct;
	
	ct = Problem;
	cc = new OtherChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif	
}

void CMainFrame::OnUpdateChartSpecialtychartsProblem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnOptionsChartoptionsArabicpointsoptions() 
{
	// TODO: Add your command handler code here
#ifdef PRO
	DoOptions(setup_dat.getArabptOpt().getOpt(),"Arabic Points Options");
#endif	
	
}

void CMainFrame::OnUpdateOptionsChartoptionsArabicpointsoptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnOptionsChartoptionsCompositetransits() 
{
	// TODO: Add your command handler code here
#ifdef PRO
	DoOptions(setup_dat.getComptrOpt().getOpt(),"Composite Transits Options");
#endif	
	
}

void CMainFrame::OnUpdateOptionsChartoptionsCompositetransits(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnOptionsChartoptionsFixedstar() 
{
	// TODO: Add your command handler code here
#ifdef PRO
	DoOptions(setup_dat.getFixstarOpt().getOpt(),"Fixed Star Options");
#endif	
	
}

void CMainFrame::OnUpdateOptionsChartoptionsFixedstar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnOptionsGraphicfileconversionoptions() 
{
	// TODO: Add your command handler code here
#ifdef PRO
    CGraphFileOpts gfo;
	GraphFileData gfd;
	gfd.getFromIni();
	gfo.SetData(gfd);
	if ( gfo.DoModal() == IDOK ) {
	   gfo.GetData(gfd);
	   gfd.saveToIni();
	   }
#endif	
	
}

void CMainFrame::OnUpdateOptionsGraphicfileconversionoptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnOptionsEditorbs() 
{
	// TODO: Add your command handler code here
#ifdef PRO
    COrbEdit coe;
	coe.DoModal();
#endif	
	
}

void CMainFrame::OnUpdateOptionsEditorbs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnOptionsEditorsetup() 
{
	// TODO: Add your command handler code here
#ifdef PRO
 CEditData edit;
 EditSetup setup;
 setup.getFromIni();
 edit.m_options = setup.getOpt();
 edit.m_path = setup.getPath();
 edit.m_useext = setup.UseShell();
 if ( edit.DoModal()== IDOK ) {
	setup.getOpt() = edit.m_options;
    setup.getPath() = edit.m_path;
    setup.UseShell() = edit.m_useext;
 	setup.saveToIni();
	}
#endif	
}

void CMainFrame::OnUpdateOptionsEditorsetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnUpdateFileNewUserfilelist(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
	
}

void CMainFrame::OnFileNewUserfilelist() 
{
	// TODO: Add your command handler code here
	((CAstrowApp *)AfxGetApp())->NewUserFileList();
}

void CMainFrame::OnFileOpenUserfilelist() 
{
	// TODO: Add your command handler code here
    CFileDialog cfo(TRUE, ".AFL", "ASTRO.AFL", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"ASTRO File List (*.AFL)|*.AFL|All Files (*.*)|*.*||");
	cfo.m_ofn.lpstrTitle="User File List File To Open:";
	if ( cfo.DoModal() == IDOK ) 
	   AfxGetApp()->OpenDocumentFile(cfo.GetPathName()); 				
}

void CMainFrame::OnUpdateFileOpenUserfilelist(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::OnHelpCjnoyessw() 
{
	// TODO: Add your command handler code here
	ShellExecute(m_hWndMDIClient,"open", "http://www.cjnoyessw.com", NULL, NULL, SW_SHOW );
}

void CMainFrame::OnUpdateHelpCjnoyessw(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnHelpOrder() 
{
	// TODO: Add your command handler code here
ShellExecute(m_hWndMDIClient,"open", "http://www.cjnoyessw.com/order.htm", NULL, NULL, SW_SHOW );	
}

void CMainFrame::OnUpdateHelpOrder(CCmdUI* pCmdUI) 
{
#ifdef LITE
	pCmdUI->Enable(TRUE);
#endif	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnHelpTechsupp() 
{
	// TODO: Add your command handler code here
ShellExecute(m_hWndMDIClient,"open", "http://www.cjnoyessw.com/techsupp.htm", NULL, NULL, SW_SHOW );	
	
}

void CMainFrame::OnUpdateHelpTechsupp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);

}

void CMainFrame::OnHelpVersions() 
{
	// TODO: Add your command handler code here
 ShellExecute(m_hWndMDIClient,"open", "http://www.cjnoyessw.com/versions.htm", NULL, NULL, SW_SHOW );
}

void CMainFrame::OnUpdateHelpVersions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef LITE
	pCmdUI->Enable(TRUE);
#endif	
}

void CMainFrame::OnSolararcchart() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE
    ChartCompiler *cc;
    enum ChartType ct;
	
	ct = SolarArc;
	cc = new SolarChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif
}

void CMainFrame::OnUpdateSolararcchart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE
	pCmdUI->Enable();
#endif
}

void CMainFrame::OnSolararcdata() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	CSolarArc sod(this);
	sod.SetData(solar_data);
	if ( sod.DoModal() == IDOK )
		sod.GetData(solar_data);
#endif
}

void CMainFrame::OnUpdateSolararcdata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE	
	pCmdUI->Enable();
#endif
}

void CMainFrame::OnSolararcopt() 
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	DoOptions(setup_dat.getSolarOpt().getOpt(),"Solar Arc Options");
#endif
}

void CMainFrame::OnUpdateSolararcopt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE	
	pCmdUI->Enable();
#endif
}

void CMainFrame::OnHarmonicData()
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	CHarmonic hrm(this);
	hrm.SetValue(m_harmonic);
	if ( hrm.DoModal() == IDOK )
		m_harmonic = hrm.GetValue();
#endif
}

void CMainFrame::OnUpdateHarmonicData(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE
	pCmdUI->Enable();
#endif
}

void CMainFrame::OnHarmonicChart()
{
	// TODO: Add your command handler code here
#ifdef DELUXE  	
	ChartCompiler *cc;
    enum ChartType ct;
	
	ct = Harmonic;
	cc = new HarmonicChartCompiler( this, ct );
	cc->runChart();
    delete cc;
#endif 
}

void CMainFrame::OnUpdateHarmonicChart(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE	
	pCmdUI->Enable();
#endif
}

void CMainFrame::OnHarmonicOptions()
{
	// TODO: Add your command handler code here
#ifdef DELUXE	
	DoOptions(setup_dat.getHarmonicOpt().getOpt(),"Harmonic Options");
#endif
}

void CMainFrame::OnUpdateHarmonicOptions(CCmdUI *pCmdUI)
{
#ifdef DELUXE
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
#endif
}

void CMainFrame::OnCreateFolder()
{
	// TODO: Add your command handler code here
   CFolderName fld(this);
   fld.m_newmode = 1;
   fld.DoModal();
}

void CMainFrame::OnUpdateCreateFolder(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnChangeFolder()
{
	// TODO: Add your command handler code here
	CSelectFolder sel(this);
	sel.DoModal();
}

void CMainFrame::OnUpdateChangeFolder(CCmdUI *pCmdUI)
{
 pCmdUI->Enable();
}

void CMainFrame::OnRenameFolder()
{
	// TODO: Add your command handler code here
	CFolderName fld(this);
	fld.m_newmode = 0;
	fld.DoModal();
}

void CMainFrame::OnUpdateRenameFolder(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnAdvancedOpt()
{
	// TODO: Add your command handler code here
	CAdvancedOpt adopt(this);
	adopt.DoModal();
}

void CMainFrame::OnUpdateAdvancedOpt(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void Backup( CString &db )
{
  CString dstDb = db;
  int pos = db.Find('.');
  dstDb = db.Left(pos-1);
  dstDb += "Backup.mdb";
  //pWs->RepairDatabase(db);
  theDirectories.m_workspace.CompactDatabase(db,dstDb);
}

void Compress( CString &db )
{
  CString dstDb = db;
  int pos = db.Find('.');
  dstDb = db.Left(pos-1);
  dstDb += "xxxx.mdb";
  //pWs->RepairDatabase(db);
  theDirectories.m_workspace.CompactDatabase(db,dstDb);
  unlink(db);
  rename(dstDb,db);
}

void CMainFrame::OnCompressDb()
{
  theDirectories.CloseDb();
  CString main = theDirectories.getDB();
  if ( main.Right(1) != "\\") 
	  main += "\\";
  main += theDirectories.getDbName();
  CString text = theDirectories.getDB();
  if ( text.Right(1) != "\\") 
	  text += "\\";
  text += theDirectories.getTxtDbName();
  Compress(main);
  if ( main != text )
	  Compress(text);
  theDirectories.ReopenDb();
}

void CMainFrame::OnUpdateCompressDb(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnToday()
{
  WinExec(set_path("Todaycalc.exe",PROGRAM_F),SW_SHOW);
}

void CMainFrame::OnUpdateToday(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnEphemeris()
{
   WinExec(set_path("ephemeris.exe",PROGRAM_F),SW_SHOW);
}

void CMainFrame::OnUpdateEphemeris(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnRefMaps()
{
  ShellExecute(m_hWndMDIClient,"open", "http://www.cjnoyessw.com/maps", NULL, NULL, SW_SHOW );
}

void CMainFrame::OnUpdateRefMaps(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnBackupDb()
{
  theDirectories.CloseDb();
  CString main = theDirectories.getDB();
  if ( main.Right(1) != "\\") 
	  main += "\\";
  main += theDirectories.getDbName();
  CString text = theDirectories.getDB();
  if ( text.Right(1) != "\\") 
	  text += "\\";
  text += theDirectories.getTxtDbName();
  Backup(main);
  if ( main != text )
	 Backup(text);
  theDirectories.ReopenDb();
}

void CMainFrame::OnUpdateBackupDb(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnOptionsSetcurrentlanguage()
{
	// TODO: Add your command handler code here
#ifdef _UNICODEVER	
	CSetLanguage sl(this);
	sl.DoModal();
#endif
}

void CMainFrame::OnUpdateOptionsSetcurrentlanguage(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef _UNICODEVER	
	try {
        CDaoTableDefInfo info;
	    theDirectories.m_pDatabase->GetTableDefInfo("Languages", info );
	    pCmdUI->Enable();
	}
	catch ( CDaoException *e ) {
		pCmdUI->Enable(FALSE); 
	   }
#else
    pCmdUI->Enable(FALSE);
#endif
}

void CMainFrame::OnChartwizard()
{
#ifdef WIZ
	XPFILE_DB fileinfo;
 DATA_PACKET_EXT chart_data = {0,&birth_rectd,&transit_data,&progress_data,&return_data, 
  &solar_data, &reloc_data,&comp_rectd,&m_harmonic,NULL,&birth_rec, &comp_rec, &trans_rec,
  &birth_rectd, &comp_rectd, &trans_rectd,&reloc_data, &RelocationPersonal };

 memset(&fileinfo, 0, sizeof(XPFILE_DB));
 CChartWizard *pWizard = new CChartWizard("Setup Chart Data", this, 0 );
 pWizard->SetChartDataPtrs(chart_data);
 pWizard->SetFileDb(&fileinfo);
 pWizard->DefaultRectMethod()=0;
 pWizard->InitializeSheet();
 if ( pWizard->DoModal() == ID_WIZFINISH ) {
      CPtrArray ReturnPtrs;
	  ChartCompiler *pCompiler;
	  enum ChartType type = DefaultChart;
	  switch ( pWizard->GetFileType() ) {
		  case NATAL_FILE:
		  case RELOCATION_FILE:
              pCompiler = (ChartCompiler *)new NatalChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case COMPATIBILITY_FILE:
		  case COMPOSITE_FILE:
			  pCompiler = (ChartCompiler *)new CompChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case TRANSITS_FILE:
			  pCompiler = (ChartCompiler *)new TransChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
#ifdef DELUXE
		  case PROGRESSED_FILE:
			  pCompiler = (ChartCompiler *)new ProgChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case SOLAR_RETURN_FILE:
		  case RETURN_W_RELOC:
		  case RETURN_W_TRANS:
			  {
			    type = pWizard->GetChartTypeEnum();
			    BIRTH_DB *p = NULL;
			    if ( type == CReturnReloc )
				    p = &birth_rec;
			    else if ( type == CReturnTrans )
				    p = &trans_rec;
			    pCompiler = (ChartCompiler *)new ReturnChartCompiler(this,CReturn,TRUE,p);
			    pCompiler->SetPtrDataArray(&ReturnPtrs);
			  }
			  break;
		  case SOLARARC_FILE:
			  pCompiler = (ChartCompiler *)new SolarChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case HARMONIC_FILE:
			  pCompiler = (ChartCompiler *)new HarmonicChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
#endif
#ifdef PRO
		  case COMPOTRAN_FILE:
			  pCompiler = (ChartCompiler *)new ComTrnChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
		  case FIXED_FILE:
		  case ARABIC_FILE:
		  case HELIO_FILE:
		  case PROBLEM_FILE:
			  pCompiler = (ChartCompiler *)new OtherChartCompiler(this,pWizard->GetChartTypeEnum(),TRUE);
			  break;
#endif
		  default: 
			  break;
	  }
      pCompiler->SetWizFileInfo(fileinfo);
	  if ( pCompiler->runChart() ) {
		  XPFILE_DB *pFile;
		  char buf[250];
          BIRTH_DB *pWith;
		  pFile = pCompiler->getOutFp();
		  if ( pFile != NULL ) {
			strcpy( buf, set_path(pFile->file_name,pFile->folder));
			((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf);
		  }
		  pFile = pCompiler->getGraphFp();
          if ( pFile != NULL ) {
		    strcpy( buf, set_path(pFile->file_name,pFile->folder));
			((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf);
		  }
		  pFile = pCompiler->getGridFp();
		  if ( pFile != NULL ) {
		    strcpy( buf, set_path(pFile->file_name,pFile->folder));
			((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf);
		  }
	      if (( type == CReturnReloc || type==CReturnTrans ) &&
			  ReturnPtrs.GetSize() > 0  ) {
				  for ( int i = 0; i <= ReturnPtrs.GetUpperBound(); i++ ) {
		             pWith = (BIRTH_DB *)ReturnPtrs.GetAt(i);
					 switch ( type ) {
			         case CReturnReloc:
				        delete pCompiler;
                        pCompiler = (ChartCompiler *)new NatalChartCompiler(this,Reloc,TRUE,pWith);
				        break;
			        case CReturnTrans:
				        delete pCompiler;
						pCompiler = (ChartCompiler *)new TransChartCompiler(this,Transits,TRUE,pWith);
				        break;
				    default:
					    break;
				   }
			
			  if ( pCompiler->runChart() ) {
		         XPFILE_DB *pFile2;
		         char buf2[250];
		         pFile2 = pCompiler->getOutFp();
		         if ( pFile2 != NULL ) {
			        strcpy( buf2, set_path(pFile2->file_name,pFile2->folder));
			        ((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf2);
		            }
		         pFile2 = pCompiler->getGraphFp();
                 if ( pFile2 != NULL ) {
		            strcpy( buf2, set_path(pFile2->file_name,pFile2->folder));
			        ((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf2);
		            }
		         pFile2 = pCompiler->getGridFp();
		         if ( pFile2 != NULL ) {
		            strcpy( buf2, set_path(pFile2->file_name,pFile2->folder));
			        ((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf2);
		            }
			     }
			  delete pWith;
			  delete pCompiler;
		      pCompiler = NULL;
			  }
	       }
	   }
	    if ( pCompiler != NULL )
	       delete pCompiler;
 }
 delete pWizard;
#endif
}

void CMainFrame::OnUpdateChartwizard(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef WIZ
	pCmdUI->Enable();
#endif

}

void CMainFrame::OnFileOpenNew()
{
 char buf[250];
	// TODO: Add your command handler code here
#ifdef WIZ
   CDAstFileOpen dafo(this);
   if ( dafo.DoModal() == IDOK ) {
	   CStringArray &ar = dafo.GetSelection();
	   int fld = dafo.m_folderno;
	   for ( int i = 0; i <= ar.GetUpperBound(); i++ ) {
		   strcpy(buf,set_path((char *)(LPCTSTR)ar.GetAt(i),fld));	
           ((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf); 
		  }
   }
#endif
}

void CMainFrame::OnUpdateFileOpenNew(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef WIZ
	pCmdUI->Enable();
#endif
}

void CMainFrame::OnReturnWReloc()
{
	// TODO: Add your command handler code here
#ifdef DELUXE
    ChartCompiler *cc;
    enum ChartType ct;
	ct = CReturn;
	CPtrArray ReturnPtrs;
	BIRTH_DB *p = &birth_rec;
	cc = (ChartCompiler *)new ReturnChartCompiler(this,ct,FALSE,p);
	cc->SetPtrDataArray(&ReturnPtrs);
	if ( cc->runChart() ) {
          BIRTH_DB *pWith;
	      if ( ReturnPtrs.GetSize() > 0  ) {
			for ( int i = 0; i <= ReturnPtrs.GetUpperBound(); i++ ) {
		        pWith = (BIRTH_DB *)ReturnPtrs.GetAt(i);
				ChartCompiler *pCompiler = (ChartCompiler *)new NatalChartCompiler(this,Reloc,FALSE,pWith);
		        pCompiler->runChart();
			    delete pWith;
			    delete pCompiler;
			   }
	       }
       delete cc;
	   }
	else
	   delete cc;
#endif
}

void CMainFrame::OnUpdateReturnWReloc(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE
	pCmdUI->Enable();
#endif

}

void CMainFrame::OnReturnWTransits()
{
	// TODO: Add your command handler code here
#ifdef DELUXE
    ChartCompiler *cc;
    enum ChartType ct;
	ct = CReturn;
	CPtrArray ReturnPtrs;
	BIRTH_DB *p = &trans_rec;
	cc = (ChartCompiler *)new ReturnChartCompiler(this,ct,FALSE,p);
	cc->SetPtrDataArray(&ReturnPtrs);
    if ( cc->runChart() ) {
       BIRTH_DB *pWith;
	   if ( ReturnPtrs.GetSize() > 0  ) {
	      for ( int i = 0; i <= ReturnPtrs.GetUpperBound(); i++ ) {
		      pWith = (BIRTH_DB *)ReturnPtrs.GetAt(i);
			  ChartCompiler *pCompiler = (ChartCompiler *)new TransChartCompiler(this,Transits,FALSE,pWith);
		      pCompiler->runChart();
			  delete pWith;
			  delete pCompiler;
			  }
	       }
		delete cc;
	   }
	else
	   delete cc;


#endif
}

void CMainFrame::OnUpdateReturnWTransits(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef DELUXE
	pCmdUI->Enable();
#endif

}
