// ChartOptions.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "inifile.hpp"
#include "flags.h"
#include "setup.hpp"
#include "ChartOptions.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CChartOptions dialog


CChartOptions::CChartOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CChartOptions::IDD, pParent)
	, m_def_rectmethod(0)
{
	//{{AFX_DATA_INIT(CChartOptions)
	m_aspects = FALSE;
	m_extaspects = FALSE;
	m_extmisc = FALSE;
	m_houseproc = -1;
	m_houses = FALSE;
	m_fullmid = FALSE;
	m_halfmid = FALSE;
	m_misc = FALSE;
	m_aspmid = FALSE;
	m_summary = FALSE;
	m_text = FALSE;
	m_verteast = FALSE;
	m_basemid = FALSE;
	m_swap = FALSE;
	m_keep = FALSE;
	//}}AFX_DATA_INIT
	cap = NULL;
}


void CChartOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartOptions)
	DDX_Check(pDX, ID_OPASPECTS, m_aspects);
	DDX_Check(pDX, ID_OPEXTASP, m_extaspects);
	DDX_Check(pDX, ID_OPEXTMISC, m_extmisc);
	DDX_CBIndex(pDX, ID_OPHOUSEPROC, m_houseproc);
	DDX_Check(pDX, ID_OPHOUSES, m_houses);
	DDX_Check(pDX, ID_OPMFULL, m_fullmid);
	DDX_Check(pDX, ID_OPMHALF, m_halfmid);
	DDX_Check(pDX, ID_OPMISC, m_misc);
	DDX_Check(pDX, ID_OPMMIDASP, m_aspmid);
	DDX_Check(pDX, ID_OPSUMMARY, m_summary);
	DDX_Check(pDX, ID_OPTEXT, m_text);
	DDX_Check(pDX, ID_OPVERTEAST, m_verteast);
	DDX_Check(pDX, IDOPMBASE, m_basemid);
	DDX_Check(pDX, IDC_ASTEROID, m_asteroids);
	//DDX_Check(pDX, IDC_KEEPSIGNPOLAR, m_keep);
	DDX_Check(pDX, IDC_SWAPSIGNPOLAR, m_swap);
	//}}AFX_DATA_MAP
	DDX_CBIndex(pDX, IDC_DEFRECT, m_def_rectmethod);
}


BEGIN_MESSAGE_MAP(CChartOptions, CDialog)
	//{{AFX_MSG_MAP(CChartOptions)
	ON_BN_CLICKED(ID_OPSIDEREAL, OnOpsidereal)
	ON_BN_CLICKED(ID_OPTROPICAL, OnOptropical)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartOptions message handlers

void CChartOptions::SetData(OPTIONS &o)
{
 if ( o.flags & SIDEREAL ) {
	m_tropical = 0;
	m_sidereal = 1;
	}
 else {
	m_tropical = 1;
	m_sidereal = 0;
	}
 m_houseproc = o.house_mode & 0xf;
 m_swap = is_set( o.house_mode, POLARSWAP );
 m_houses = is_set( o.flags, HOUSES );
 m_aspects = is_set( o.flags, ASPECTS );
 m_extaspects = is_set( o.flags, EXT_ASPECTS );
 m_summary = is_set( o.flags, SUMMARY );
 m_misc = is_set( o.flags, MISCELL );
 m_extmisc = is_set( o.flags, EXT_CALCS );
 m_verteast = is_set( o.flags, VERT_EAST );
 m_text = is_set( o.flags, TEXT );
#ifdef DELUXE
 m_basemid = is_set( o.flags, BASE_MID );
 m_halfmid = is_set( o.flags, HALF_MID );
 m_fullmid = is_set( o.flags, FULL_MID );
 m_aspmid = is_set( o.flags, MID_ASPECT );
 m_asteroids = is_set(o.flags, ASTEROID );
#endif
}

void CChartOptions::GetData(OPTIONS &o)
{
 o.flags = 0;
 if ( m_sidereal )
    o.flags = 1;
 o.house_mode = m_houseproc; 
 set_it( o.house_mode, POLARSWAP, m_swap );
 set_it( o.flags, HOUSES, m_houses );
 set_it( o.flags, ASPECTS, m_aspects );
 set_it( o.flags, EXT_ASPECTS, m_extaspects );
 set_it( o.flags, SUMMARY, m_summary );
 set_it( o.flags, MISCELL, m_misc );
 set_it( o.flags, EXT_CALCS, m_extmisc );
 set_it( o.flags, VERT_EAST, m_verteast );
 set_it( o.flags, TEXT, m_text );
#ifdef DELUXE
 set_it( o.flags, BASE_MID, m_basemid );
 set_it( o.flags, HALF_MID, m_halfmid );
 set_it( o.flags, FULL_MID, m_fullmid );
 set_it( o.flags, MID_ASPECT, m_aspmid );
 set_it( o.flags, ASTEROID, m_asteroids );
#endif
}


void CChartOptions::OnOpsidereal() 
{
	// TODO: Add your control notification handler code here
m_sidereal = 1;
m_tropical = 0;	
}

void CChartOptions::OnOptropical() 
{
	// TODO: Add your control notification handler code here
m_sidereal = 0;
m_tropical = 1;	
}

BOOL CChartOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if ( cap != NULL )
	   SetWindowText(cap);
	if ( m_tropical ) {
        CButton *ptr =(CButton *) GetDlgItem(ID_OPTROPICAL);
	    ptr->SetCheck(1);
	   }
	else {
	    CButton *ptr =(CButton *) GetDlgItem(ID_OPSIDEREAL);
	    ptr->SetCheck(1);
	   }

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartOptions::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
