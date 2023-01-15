// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Wizard.h"

#include "MainFrm.h"
#include ".\mainfrm.h"
#include "chartwizard.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int harmonic;
CString Personal;
BIRTH_DB birth_rec, comp_rec, trans_rec;
LOC_DB reloc_data;
PROGR_DATA progress_data;
TRANS_DATA transit_data;
DIREC_DATA solar_data;
RECT_DATA birth_rectd, comp_rectd, trans_rectd;
RETURN_DATA return_data;
DATA_PACKET_EXT chart_data = {0,&birth_rectd,&transit_data,&progress_data,&return_data, 
  &solar_data, &reloc_data,&comp_rectd,&harmonic,NULL,&birth_rec, &comp_rec, &trans_rec,
  &birth_rectd, &comp_rectd, &trans_rectd,&reloc_data, &Personal };
XPFILE_DB fileinfo;

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TEST_TESTWIZARD, OnTestTestwizard)
	ON_UPDATE_COMMAND_UI(ID_TEST_TESTWIZARD, OnUpdateTestTestwizard)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	memset(&birth_rec,0,sizeof(birth_rec));
	memset(&birth_rectd,0,sizeof(birth_rectd));
	memset(&fileinfo,0,sizeof(fileinfo));
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers


void CMainFrame::OnTestTestwizard()
{
	// TODO: Add your command handler code here
    CChartWizard *pWizard = new CChartWizard("Setup Chart Data", this, 0 );
	pWizard->SetChartDataPtrs(chart_data);
	pWizard->SetFileDb(&fileinfo);
	pWizard->DefaultRectMethod()=0;
	pWizard->InitializeSheet();
	pWizard->DoModal();
	delete pWizard;

}

void CMainFrame::OnUpdateTestTestwizard(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}
