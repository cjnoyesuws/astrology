// Customize.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "inifile.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "setup.hpp"
#include "chartoptions.h"
#include "Customize.h"
#include "flags.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomize dialog
int textset;

CCustomize::CCustomize(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomize)
	textset = 0;
	m_reloc = FALSE;
	m_text = FALSE;
	m_progress = FALSE;
	m_progr_cusps = FALSE;
	m_graph = FALSE;
	m_datafile = FALSE;
	m_datafiletype = -1;
	m_gridfile = FALSE;
	m_interpret = FALSE;
	//}}AFX_DATA_INIT
	cap = NULL;
}


void CCustomize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomize)
	DDX_Check(pDX, ID_CS_RELOC, m_reloc);
	DDX_Check(pDX, ID_CSTEXT, m_text);
	DDX_Check(pDX, ID_CSPROGR, m_progress);
	DDX_Check(pDX, ID_CSPRGCUSP, m_progr_cusps);
	DDX_Check(pDX, ID_CSGRAPH, m_graph);
	DDX_Check(pDX, ID_CSDATAFILE, m_datafile);
	DDX_Check(pDX, IDC_GRIDFILE, m_gridfile);
	DDX_Check(pDX, IDC_INTERPRETED, m_interpret);
	DDX_CBIndex(pDX, ID_CSDFTYPE, m_datafiletype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomize, CDialog)
	//{{AFX_MSG_MAP(CCustomize)
	ON_BN_CLICKED(ID_CSCUSTOM, OnCscustom)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomize message handlers

void CCustomize::OnCscustom() 
{
	// TODO: Add your control notification handler code here
	CChartOptions cco;
	UpdateData(TRUE);
	if ( m_interpret == FALSE && op.flags&TEXT)
       op.flags &= (0xffff^TEXT);
	cco.SetData(op);
	if ( cap != NULL )
	   cco.SetCaption(cap);
	if ( cco.DoModal() == IDOK )
	   cco.GetData(op);
    if ( m_interpret == FALSE && op.flags&TEXT)
		textset = 1;
}



void CCustomize::SetData(OPTIONS &o)
{
 op = o;
 m_reloc = is_set( o.chart_code, RELOC_CH );
 m_progress = is_set( o.chart_code, PROGR_CH );
 m_progr_cusps = is_set( o.chart_code, PRGCS_CH );
 m_text = is_set( o.charts, TEXTF );
 m_graph = is_set( o.charts, GRAPH );
 m_gridfile = is_set(o.charts, GRIDF );
 m_interpret = is_set(o.charts,INTRP );
 if ( o.datafile != -1 )
	m_datafile = TRUE;
 else
    m_datafile = is_set( o.charts, DATAF );
 
 m_datafiletype = o.datafile;
}

void CCustomize::GetData(OPTIONS &o)
{
 op.chart_code = 0;
 set_it(op.chart_code,RELOC_CH,m_reloc);
 set_it(op.chart_code,PROGR_CH,m_progress);
 set_it(op.chart_code,PRGCS_CH,m_progr_cusps);
 op.charts = 0;
 set_it(op.charts,GRAPH,m_graph);
 set_it(op.charts,TEXTF,m_text);
 set_it(op.charts,GRIDF,m_gridfile);
 set_it(op.charts,INTRP,m_interpret);
 if ( m_datafile && m_datafiletype != -1 )
    set_it(op.charts,DATAF,m_datafile);
 op.datafile = m_datafiletype;
 if ( m_interpret == FALSE && op.flags&TEXT && !textset)
       op.flags &= (0xffff^TEXT);
 o = op;
}

 

BOOL CCustomize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( cap != NULL )
	   SetWindowText(cap);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomize::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(CCustomize::IDD, HELP_CONTEXT);
}
