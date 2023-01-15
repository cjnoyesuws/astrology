// OrbEdit.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "astro.h"
#include "aspect.h"
#include "OrbEdit.h"
#include <afxpriv.h>
#define _ORB_OTHER 13
#define _ORB_HOUSE 14

extern int load_orbs(int context);
extern int save_orbs(int context);



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrbEdit dialog


COrbEdit::COrbEdit(CWnd* pParent /*=NULL*/)
	: CDialog(COrbEdit::IDD, pParent)
{
	context = 0;
	//{{AFX_DATA_INIT(COrbEdit)
	m_dbiqui = _T("");
	m_dconjunct = _T("");
	m_ddecile = _T("");
	m_dhscusp = _T("");
	m_dnonplan = _T("");
	m_doppose = _T("");
	m_dquin = _T("");
	m_dquintile = _T("");
	m_dsesquiquq = _T("");
	m_dssext = _T("");
	m_dssquare = _T("");
	m_dtredec = _T("");
	m_dtrine = _T("");
	m_ibiquint = FALSE;
	m_iconjunct = FALSE;
	m_idecile = FALSE;
	m_ihscusp = FALSE;
	m_ioppose = FALSE;
	m_iquincunx = FALSE;
	m_iquint = FALSE;
	m_isext = FALSE;
	m_isquare = FALSE;
	m_issesquiq = FALSE;
	m_issext = FALSE;
	m_issquare = FALSE;
	m_itredec = FALSE;
	m_itrine = FALSE;
	m_dsextile = _T("");
	m_dsquare = _T("");
	//}}AFX_DATA_INIT
	GetData();
}


void COrbEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrbEdit)
	DDX_Text(pDX, ID_AODBIQUI, m_dbiqui);
	DDX_Text(pDX, ID_AODCONJUNCT, m_dconjunct);
	DDX_Text(pDX, ID_AODDECILE, m_ddecile);
	DDX_Text(pDX, ID_AODHSCUSP, m_dhscusp);
	DDX_Text(pDX, ID_AODNONPLAN, m_dnonplan);
	DDX_Text(pDX, ID_AODOPPOSE, m_doppose);
	DDX_Text(pDX, ID_AODQUIN, m_dquin);
	DDX_Text(pDX, ID_AODQUINTILE, m_dquintile);
	DDX_Text(pDX, ID_AODSSESQUIQ, m_dsesquiquq);
	DDX_Text(pDX, ID_AODSSEXT, m_dssext);
	DDX_Text(pDX, ID_AODSSQARE, m_dssquare);
	DDX_Text(pDX, ID_AODTREDEC, m_dtredec);
	DDX_Text(pDX, ID_AODTRINE, m_dtrine);
	DDX_Check(pDX, ID_AOIBQUINT, m_ibiquint);
	DDX_Check(pDX, ID_AOICONJUNCT, m_iconjunct);
	DDX_Check(pDX, ID_AOIDECILE, m_idecile);
	DDX_Check(pDX, ID_AOIHSCUSP, m_ihscusp);
	DDX_Check(pDX, ID_AOIOPPOSE, m_ioppose);
	DDX_Check(pDX, ID_AOIQUINCUNX, m_iquincunx);
	DDX_Check(pDX, ID_AOIQUINT, m_iquint);
	DDX_Check(pDX, ID_AOISEXT, m_isext);
	DDX_Check(pDX, ID_AOISQUARE, m_isquare);
	DDX_Check(pDX, ID_AOISSESQUIQ, m_issesquiq);
	DDX_Check(pDX, ID_AOISSEXT, m_issext);
	DDX_Check(pDX, ID_AOISSQUARE, m_issquare);
	DDX_Check(pDX, ID_AOITREDEC, m_itredec);
	DDX_Check(pDX, ID_AOITRINE, m_itrine);
	DDX_Text(pDX, ID_AODSEXTILE, m_dsextile);
	DDX_Text(pDX, ID_AODSQUARE, m_dsquare);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrbEdit, CDialog)
	//{{AFX_MSG_MAP(COrbEdit)
	ON_CBN_SELCHANGE(ID_AOCONTEXT, OnSelchangeAocontext)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrbEdit message handlers

void COrbEdit::OnSelchangeAocontext() 
{
	// TODO: Add your control notification handler code here
    CComboBox *pc = (CComboBox *)GetDlgItem(ID_AOCONTEXT);	   
    if ( pc != NULL ) {
	   if ( pc->GetCurSel() != -1 ) {
 	      int i = pc->GetCurSel();
	      UpdateData(TRUE);
		  SaveData();
	      context = i;
		  GetData();
	      UpdateData(FALSE);
	      }
	  }
}

void COrbEdit::SaveData()
{
BOOL b=0;

GetItem(m_dconjunct,m_iconjunct,CONJUNCT );    
GetItem(m_dsextile,m_isext,SEXTILE );         
GetItem(m_dtrine,m_itrine,TRINE );           
GetItem(m_doppose,m_ioppose,OPPOSITION );      
GetItem(m_dsquare,m_isquare,SQUARED );         
GetItem(m_dssext,m_issext,SEMISEXT );        
GetItem(m_dssquare,m_issquare,SEMISQUARE );      
GetItem(m_dsesquiquq,m_issesquiq,SEMISESQUAD );     
GetItem(m_dquin,m_iquincunx,QUINCUNX );        
GetItem(m_dbiqui,m_ibiquint,BIQUINTILE );      
GetItem(m_dquintile,m_iquint,QUINTILE );        
GetItem(m_dtredec,m_itredec,TREDECILE );       
GetItem(m_ddecile,m_idecile,DECILE );          
GetItem(m_dnonplan,b,_ORB_OTHER);
GetItem(m_dhscusp,m_ihscusp,_ORB_HOUSE);
save_orbs(context);
}

void COrbEdit::GetData()
{
 BOOL b=0;
 load_orbs(context);
 SetItem(m_dconjunct,m_iconjunct,CONJUNCT );    
 SetItem(m_dsextile,m_isext,SEXTILE );         
 SetItem(m_dtrine,m_itrine,TRINE );           
 SetItem(m_doppose,m_ioppose,OPPOSITION );      
 SetItem(m_dsquare,m_isquare,SQUARED );         
 SetItem(m_dssext,m_issext,SEMISEXT );        
 SetItem(m_dssquare,m_issquare,SEMISQUARE );      
 SetItem(m_dsesquiquq,m_issesquiq,SEMISESQUAD );     
 SetItem(m_dquin,m_iquincunx,QUINCUNX );        
 SetItem(m_dbiqui,m_ibiquint,BIQUINTILE );      
 SetItem(m_dquintile,m_iquint,QUINTILE );        
 SetItem(m_dtredec,m_itredec,TREDECILE );       
 SetItem(m_ddecile,m_idecile,DECILE );          
 SetItem(m_dnonplan,b,_ORB_OTHER);
 SetItem(m_dhscusp,m_ihscusp,_ORB_HOUSE);
}

void COrbEdit::GetItem( CString &s, BOOL b, int index )
{
int d = 0, m = 0;
if ( index == _ORB_OTHER ) {
   sscanf( s, "%d:%d", &d, &m );
    other_orb = (d*60)+m;
    }
 else if ( index == _ORB_HOUSE ) {
   sscanf( s, "%d:%d", &d, &m );
   hscsp_orb = (d*60)+m;
   inc_hscsp = b;
   }
 else {
    sscanf( s, "%d:%d", &d, &m );
    aspect_def[index].orb = (d*60)+m;
    asp_map[index] = b;
	}
}

void COrbEdit::SetItem( CString &s, BOOL &b, int index )
{
 if ( index == _ORB_OTHER ) {
	s.Format("%02d:%02d", (int)other_orb/60, (int)other_orb%60 );
    }
 else if ( index == _ORB_HOUSE ) {
	s.Format("%02d:%02d", (int)hscsp_orb/60, (int)hscsp_orb%60 );
    b = inc_hscsp;
    }
 else {
	s.Format("%02d:%02d", (int)aspect_def[index].orb/60, (int)aspect_def[index].orb%60 );
    b = (asp_map[index]?TRUE:FALSE);
 }
 
 }



void COrbEdit::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
	SaveData();

}
    
void COrbEdit::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
