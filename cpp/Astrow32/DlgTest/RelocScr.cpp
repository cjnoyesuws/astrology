// RelocScr.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "charcons.h"
#include "databaseodbc.hpp"
#include "adbcombbox.hpp"
#include "RelocScr.h"
#include <afxpriv.h>
#include "zipcodedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static LOC_DB save_loc;
static int loc_saved = 0;
static int loc_gotten = 0;
static int in_update_data = 0;

#define TZ_OTHER 21
#define SC_OTHER 6

static char spec_vals[] = { 0, -1, -1, -2, -1, 1, 0 };
static char tim_vals[] = { 3, 4, 5, 6, 7, 8, 10, 0, -1, -2, -3, -8, -9, -7, -12,
		   -10, -8, -8, 5, 11, 12, 0, 0, 0, 0,0,0,0 };



/////////////////////////////////////////////////////////////////////////////
// CRelocScr dialog


CRelocScr::CRelocScr(CWnd* pParent /*=NULL*/)
	: CDialog(CRelocScr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRelocScr)
	m_country = _T("");
	m_eastwest = -1;
	m_location = _T("");
	m_speccode = -1;
	m_state = _T("");
	m_timezone = -1;
	m_northsouth = -1;
	m_lomin = 0;
	m_lodeg = 0;
	m_ladeg = 0;
	m_lamin = 0;
	m_gmthr = 0;
	m_gmtmin = 0;
	m_cdp = 0;
	//}}AFX_DATA_INIT
 pLocDb = new DaoLocDatabase();
 pRelocDb = new DaoRelocateDatabase();
 pMenu = NULL;
} 


void CRelocScr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	if ( !pDX->m_bSaveAndValidate )
		m_gmthr = tim_vals[m_timezone];
	//{{AFX_DATA_MAP(CRelocScr)
	DDX_CBString(pDX, IDC_RELOCS, m_personal);
	DDX_CBString(pDX, ID_RLCOUNTRY, m_country);
	DDV_MaxChars(pDX, m_country, 29);
	DDX_CBIndex(pDX, ID_RLEASTWEST, m_eastwest);
	DDX_CBString(pDX, ID_RLLOCATION, m_location);
	DDV_MaxChars(pDX, m_location, 39);
	//DDX_CBIndex(pDX, ID_RLSPECCODE, m_speccode);
	DDX_CBString(pDX, ID_RLSTATE, m_state);
	DDV_MaxChars(pDX, m_state, 30);
	DDX_CBIndex(pDX, ID_RLTIMEZONE, m_timezone);
	DDX_CBIndex(pDX, ID_RLNORTHSOUTH, m_northsouth);
	DDX_Text(pDX, ID_RLLOMIN, m_lomin);
	DDV_MinMaxInt(pDX, m_lomin, 0, 60);
	DDX_Text(pDX, ID_RLLODEG, m_lodeg);
	DDV_MinMaxInt(pDX, m_lodeg, 0, 180);
	DDX_Text(pDX, ID_RLLADEG, m_ladeg);
	DDV_MinMaxInt(pDX, m_ladeg, 0, 180);
	DDX_Text(pDX, ID_RLLAMIN, m_lamin);
	DDV_MinMaxInt(pDX, m_lamin, 0, 59);
	DDX_Text(pDX, ID_RLGMTHR, m_gmthr);
	DDV_MinMaxInt(pDX, m_gmthr, -12, 12);
	DDX_Text(pDX, ID_RLGMTMIN, m_gmtmin);
	DDV_MinMaxInt(pDX, m_gmtmin, 0, 60);
	//}}AFX_DATA_MAP
	if ( !pDX->m_bSaveAndValidate ) {
	   showGmtCtl(m_timezone==TZ_OTHER?1:0); 
	   OnKillfocusRlcountry();
	   OnKillfocusRlstate();
	   CComboBox *pWnd = (CComboBox *)GetDlgItem(ID_RLTIMEZONE);
	   if ( pWnd != NULL )
		   pWnd->SetCurSel(m_timezone);
       pWnd = (CComboBox *)GetDlgItem(ID_RLSPECCODE);
	   if ( pWnd != NULL )
		   pWnd->SetCurSel(m_speccode);
	}
	else {
	    in_update_data = 1;
		OnSelchangeRltimezone();
		in_update_data = 0;
	}

}
										

BEGIN_MESSAGE_MAP(CRelocScr, CDialog)
	//{{AFX_MSG_MAP(CRelocScr)
	ON_CBN_EDITCHANGE(IDC_RELOCS, OnEditchangeRlpersonal)
	ON_CBN_SELCHANGE(IDC_RELOCS, OnSelchangeRlpersonal)
	ON_CBN_SELCHANGE(ID_RLTIMEZONE, OnSelchangeRltimezone)
	ON_CBN_SELCHANGE(ID_RLSPECCODE, OnSelchangeRltimezone)
	ON_CBN_KILLFOCUS(ID_RLSTATE, OnKillfocusRlstate)
	ON_CBN_KILLFOCUS(ID_RLCOUNTRY, OnKillfocusRlcountry)
	ON_CBN_KILLFOCUS(IDC_RELOCS, OnKillfocusRllocation)
	ON_BN_CLICKED(ID_RLMENU, OnRlmenu)
	ON_CBN_SELCHANGE(ID_RLLOCATION, OnSelchangeRllocation)
	ON_CBN_EDITCHANGE(ID_RLCOUNTRY, OnEditchangeRlcountry)
	ON_CBN_SELCHANGE(ID_RLCOUNTRY, OnSelchangeRlcountry)
	ON_CBN_EDITCHANGE(ID_RLLOCATION, OnEditchangeRllocation)
	ON_CBN_SELCHANGE(ID_RLSTATE, OnSelchangeRlstate)
	ON_CBN_EDITCHANGE(ID_RLSTATE, OnEditchangeRlstate)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelocScr message handlers

void CRelocScr::OnSelchangeRltimezone() 
{
	// TODO: Add your control notification handler code here
CString txt;

if ( !in_update_data )
   UpdateData(TRUE);
CComboBox *pc = (CComboBox *)GetDlgItem(ID_RLSPECCODE);	   
if ( pc != NULL ) {
   if ( pc->GetCurSel() != -1 ) {
    m_speccode = pc->GetCurSel();
   }
pc = (CComboBox *)GetDlgItem(ID_RLTIMEZONE);	   
if ( pc != NULL ) {
   if ( pc->GetCurSel() != -1 ) {
   m_timezone = pc->GetCurSel();
   if (m_timezone != TZ_OTHER && m_speccode != SC_OTHER ) {
		  m_gmthr = tim_vals[m_timezone] + spec_vals[m_speccode];
          m_gmtmin = (( m_timezone == 16 || m_timezone == 18 ) ? 30 : 0 );
	      }
   }
   if (m_timezone == TZ_OTHER) {
	  showGmtCtl(1);
      }
   else {
	   showGmtCtl(0);	
       }	
    }  
   }
 if ( !in_update_data )
    UpdateData(FALSE);
 bRelocModified = 1;	
}

void CRelocScr::OnSelchangeRlpersonal() 
{
	// TODO: Add your control notification handler code here
  LOC_DB db;
  CComboBox *pco = (CComboBox *)GetDlgItem(IDC_RELOCS);
  int sel = pco->GetCurSel();
  if ( sel != CB_ERR ) 
     pco->GetLBText(sel, m_personal);	
  CString per = m_personal;
  UpdateData(TRUE);
  m_personal = per;
  pRelocDb->setBirth( birth_rec );
  pRelocDb->setReloc( db, m_personal );
  if ( pRelocDb->find() ) {
	  db = pRelocDb->getReloc();
	  m_personal = pRelocDb->getPersonal();
	  SetData( db );
	  UpdateData(FALSE);
  }
  bRelocModified = 1;	
}


void CRelocScr::OnEditchangeRlpersonal() 
{
	// TODO: Add your control notification handler code here
 CComboBox *pco = (CComboBox *)GetDlgItem(IDC_RELOCS);
 int sel = pco->GetCurSel();
 if ( sel != CB_ERR ) 
     pco->GetLBText(sel, m_personal);
 else
	 pco->GetWindowText(m_personal);
 bRelocModified=1;
}


void CRelocScr::OnSelchangeRlspeccode() 
{
	// TODO: Add your control notification handler code here
	
}

void CRelocScr::OnKillfocusRlstate() 
{
	// TODO: Add your control notification handler code here
	int sel;
	long lrec;
	CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
	sel = pco->GetCurSel();
	if ( sel != CB_ERR ) {
	   pco->GetLBText(sel, m_country);
	   }
	else 
	  m_country == "";
	m_country.TrimLeft();
	m_country.TrimRight();
	CComboBox *pst = (CComboBox *)GetDlgItem(ID_RLSTATE);
	sel = pst->GetCurSel();
	if ( sel != CB_ERR ) {
	   pst->GetLBText(sel, m_state);
	   }
	else 
	   m_state == "";
	m_state.TrimLeft();
	m_state.TrimRight();
    CLocationComboBox *plo = new CLocationComboBox((CComboBox *)GetDlgItem(ID_RLLOCATION));
	plo->loadList(m_country, m_state, m_cdp);
	plo->SelectString(0,m_location);
	delete plo;  
}

void CRelocScr::OnKillfocusRlcountry() 
{
	// TODO: Add your control notification handler code here
	int sel;
	long lrec;
	CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
	sel = pco->GetCurSel();
	if ( sel != CB_ERR ) {
	   pco->GetLBText(sel, m_country);
	   }
	else 
	  m_country = "";
	m_country.TrimLeft();
	m_country.TrimRight();
    CLocationComboBox *pst = new CLocationComboBox((CComboBox *)GetDlgItem(ID_RLSTATE));   
	pst->loadList(m_country);
	pst->SelectString(0,m_state);
    delete pst;
}

void CRelocScr::OnKillfocusRllocation() 
{
	// TODO: Add your control notification handler code here


}

void CRelocScr::OnRlmenu() 
{
	// TODO: Add your control notification handler code here
if ( pMenu != NULL )
   delete pMenu;
pMenu = new CMenu();
pMenu->LoadMenu("LOCAT"); 
if ( bLocModified ) {
    pMenu->EnableMenuItem(ID_DELETELOCAT, MF_ENABLED );
    pMenu->EnableMenuItem(ID_ADDLOCAT, MF_ENABLED );
    }
 else {
    pMenu->EnableMenuItem(ID_DELETELOCAT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_REPLACELOCAT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_DELETELOCAT, MF_GRAYED );
    pMenu->EnableMenuItem(ID_REPLACELOCAT, MF_GRAYED );
    }
 if ( m_country.GetLength() && m_state.GetLength() &&
      m_location.GetLength() ) {
    pMenu->EnableMenuItem(ID_ADDLOCAT, MF_ENABLED );
    pMenu->EnableMenuItem(ID_REPLACELOCAT, MF_ENABLED );
    pMenu->EnableMenuItem(ID_GETLOCAT, MF_ENABLED );
    }
 else {
    pMenu->EnableMenuItem(ID_ADDLOCAT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_REPLACELOCAT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_GETLOCAT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_ADDLOCAT, MF_GRAYED );
    pMenu->EnableMenuItem(ID_REPLACELOCAT, MF_GRAYED );
    pMenu->EnableMenuItem(ID_GETLOCAT, MF_GRAYED );
    }
 if ( m_personal.GetLength() || bRelocModified) {
	pMenu->EnableMenuItem(ID_SAVERELOC, MF_ENABLED );
    pMenu->EnableMenuItem(ID_DELETE_RELOC, MF_ENABLED );
    pMenu->EnableMenuItem(ID_GETRELOC, MF_ENABLED );
    }
else {
	pMenu->EnableMenuItem(ID_SAVERELOC, MF_DISABLED );
    pMenu->EnableMenuItem(ID_DELETE_RELOC, MF_DISABLED );
    pMenu->EnableMenuItem(ID_GETRELOC, MF_DISABLED );
}
CRect r;
GetWindowRect(r);
pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN|TPM_LEFTBUTTON, (r.right-r.left)/2, (r.bottom - r.top)/2, this, NULL);		
}

BOOL CRelocScr::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CRelocScr::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
LOC_DB db;
switch (LOWORD(wParam)) {
case ID_RETURN :
  	return(1);
	break;
case ID_GETLOCAT :    
	UpdateData(TRUE);
	GetData(db);
	pLocDb->setLoc(db);
	if ( pLocDb->find() ) {
	   db= pLocDb->getLoc();
	   SetData(db);
	   UpdateData(FALSE);
	   CComboBox *pco = (CComboBox *)GetDlgItem(IDC_RELOCS);
	   if ( pco->SelectString(0,(const char *)m_personal) == CB_ERR ) 
		   pco->SetWindowText((const char *)m_personal);
	   }
	return(1);
	break;
case ID_ADDLOCAT :    
   	UpdateData(TRUE);
	GetData(db);
	pLocDb->setLoc(db);
	pLocDb->dosave();
	return(1);
	break;
case ID_DELETELOCAT : 
    UpdateData(TRUE);
	GetData(db);
	pLocDb->setLoc(db);
	pLocDb->dodelete();
	return(1);
	break;
case ID_GETRELOC :    
	UpdateData(TRUE);
	GetData(db);
	pRelocDb->setBirth(birth_rec);
	pRelocDb->setReloc(db, m_personal);
	if ( pRelocDb->find() ) {
	   db= pRelocDb->getReloc();
	   m_personal=pRelocDb->getPersonal();
	   SetData(db);
	   UpdateData(FALSE);
	   CComboBox *pco = (CComboBox *)GetDlgItem(IDC_RELOCS);
	   if ( pco->SelectString(0,(const char *)m_personal) == CB_ERR ) 
		   pco->SetWindowText((const char *)m_personal);

	}
	return(1);
	break;
case ID_SAVERELOC :    
   	UpdateData(TRUE);
	GetData(db);
	pRelocDb->setBirth(birth_rec);
	pRelocDb->setReloc(db, m_personal);
	pRelocDb->dosave();
	return(1);
	break;
case ID_DELETE_RELOC : 
    UpdateData(TRUE);
	GetData(db);
	pRelocDb->setBirth(birth_rec);
	pRelocDb->setReloc(db, m_personal);
	pRelocDb->dodelete();
	return(1);
	break;
case ID_COPYLOCAT :   
    UpdateData(TRUE);
	GetData(save_loc);
	loc_saved = 1;
	return(1);
	break;
case ID_PASTELOCAT :  
    SetData(save_loc);
	UpdateData(FALSE);
	return(1);
	break;
case ID_CLEARLOCAT :  
    memset(&db,0,sizeof(LOC_DB));
	SetData(db);
	UpdateData(FALSE);
	return(1);
	break;
 case ID_LOOKUP_LONGLAT :
	{
	UpdateData(TRUE);
	GetData(db);
	ZipCodeDlg zdlg(this);
	zdlg.SetLocDB(&db);
    zdlg.DoModal();
    SetData(db);
    UpdateData(FALSE);
	return(1);
	}
	break;
case ID_PASTEACS :
	doClipboard();
	break;
case ID_MINORCENSUS :
	m_cdp ^= 7;
	break;
default :
  return CDialog::OnCommand(wParam, lParam);
  break;
  }
return( 0 ); 
}

BOOL CRelocScr::OnInitDialog() 
{
 CLocationComboBox *pco = new CLocationComboBox((CComboBox *)GetDlgItem(ID_RLCOUNTRY));
 pco->loadList();
 delete pco;
 CRelocateComboBox *prlo = new CRelocateComboBox((CComboBox *)GetDlgItem(IDC_RELOCS));
 prlo->loadList(CString(birth_rec.name) );
 delete prlo;
 CComboBox *pco2 = (CComboBox *)GetDlgItem(IDC_RELOCS);
 if ( pco2->SelectString(0,m_personal ) == CB_ERR)
	  pco2->SetWindowText(m_personal);
 CDialog::OnInitDialog();
 	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRelocScr::OnSelchangeRllocation() 
{
	// TODO: Add your control notification handler code here
	int sel;
	LOC_DB db;
	loc_gotten = 0;
	CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
	sel = pco->GetCurSel();
	if ( sel != CB_ERR ) {
	   pco->GetLBText(sel, m_country);
	   }
	else 
	  m_country = "";
	m_country.TrimLeft();
	m_country.TrimRight();
	CComboBox *pst = (CComboBox *)GetDlgItem(ID_RLSTATE);
	sel = pst->GetCurSel();
	if ( sel != CB_ERR ) {
	   pst->GetLBText(sel, m_state);
	   }
	else 
	   m_state = "";
	m_state.TrimLeft();
	m_state.TrimRight();
	CComboBox *plo = (CComboBox *)GetDlgItem(ID_RLLOCATION);
	sel = plo->GetCurSel();
	if ( sel != CB_ERR ) {
	   plo->GetLBText(sel, m_location);
	   }
	else 
	   m_location = "";
	m_location.TrimLeft();
	m_location.TrimRight();
	CString lo = m_location;
	UpdateData(TRUE);
	m_location = lo;
	GetData(db);
	pLocDb->setLoc(db);
	if ( pLocDb->find() ) {
	   db=pLocDb->getLoc();
	   SetData(db);
	   CString per = m_personal;
	   UpdateData(FALSE);
	   m_personal = per;
	   loc_gotten=1;
	   }
}


void CRelocScr::SetData( LOC_DB &l )
{
m_country = l.country;
m_state = l.state;
m_location = l.location;
m_timezone = l.time_zone;
m_speccode = l.special_code;
m_ladeg = l.latitude.degrees;
m_lodeg = l.longitude.degrees;
m_lamin = l.latitude.minutes;
m_lomin = l.longitude.minutes;
m_gmthr = l.hrs_offset;
m_gmtmin = l.min_offset;
m_eastwest = (l.longitude.dir =='E'?1:0);
m_northsouth = (l.latitude.dir=='S'?1:0);


}

void CRelocScr::GetData( LOC_DB &l )
{
strcpy(l.country,m_country);
strcpy(l.state,m_state);
strcpy(l.location,m_location);
l.time_zone = m_timezone;
l.special_code = m_speccode;
l.latitude.degrees = m_ladeg;
l.latitude.minutes = m_lamin;
l.latitude.dir = (m_northsouth?'S':'N');
l.longitude.degrees = m_lodeg;
l.longitude.minutes = m_lomin;
l.longitude.dir = (m_eastwest?'E':'W');
l.hrs_offset = m_gmthr;
l.min_offset = m_gmtmin;

}


void CRelocScr::OnEditchangeRlcountry() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_country);	
}

void CRelocScr::OnSelchangeRlcountry() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_country);	
	
}

void CRelocScr::OnEditchangeRllocation() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLLOCATION);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_location );
}

void CRelocScr::OnSelchangeRlstate() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLSTATE);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_state);	
	
}

void CRelocScr::OnEditchangeRlstate() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLSTATE);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_state);	
}										 

BOOL CRelocScr::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	if( pMenu != NULL )
	  delete pMenu;
	if ( pLocDb != NULL ) {
       delete pLocDb;
       }
    if ( pRelocDb != NULL ) {
       delete pRelocDb;
       }
  	return CDialog::DestroyWindow();
}

BOOL CRelocScr::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL r = CDialog::Create(IDD, pParentWnd);
	return r;
}

void CRelocScr::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::WinHelp(CRelocScr::IDD, HELP_CONTEXT);
}


void CRelocScr::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}

void CRelocScr::OnOK() 
{
	LOC_DB loc;
	// TODO: Add your control notification handler code here
	if ( m_ladeg > 60 ) {
	   MessageBox("Do Not Use the Placidus or Koch House System on this chart!", "Warning");
	   }
    if ( bLocModified ) {
       UpdateData(TRUE);
	   GetData(loc);
	   pLocDb->setLoc(loc);
	   pLocDb->dosave();
	}
	if ( bRelocModified ) {
       UpdateData(TRUE);
	   GetData(loc);
	   pRelocDb->setBirth(birth_rec);
	   pRelocDb->setReloc(loc, m_personal);
	   pRelocDb->dosave();
	}
   CDialog::OnOK();
}

void CRelocScr::showGmtCtl(int bShow)
{
  if ( bShow) {
	  CEdit *st = (CEdit *)GetDlgItem(ID_RLGMTHR);
	  st->SetReadOnly(0);
	  st = (CEdit *)GetDlgItem(ID_RLGMTMIN);    
   	  st->SetReadOnly( 0 );
      }
   else {
	  CEdit *st2 =(CEdit *)GetDlgItem(ID_RLGMTHR);
	  st2->SetReadOnly(1);
	  st2 =(CEdit *)GetDlgItem(ID_RLGMTMIN);   
	  st2->SetReadOnly(1);
	  }	
}

static void fixtzsc( int off, int scoff, short &tzcode, short &sccode )
{
	for ( int i = 0; i < sizeof tim_vals; i++ ) {
		if ( off == tim_vals[i] ) {
			tzcode = i;
		    break;
		}
	}
    for ( int i = 0; i < sizeof spec_vals; i++ ) {
		if ( scoff == spec_vals[i] ) {
			sccode = i;
		    break;
		}
	}
}


void CRelocScr::doClipboard()
{
LPSTR ptrs[11], aptr= NULL;
char state[100], country[100], cod[3];
int i, cnt;
LOC_DB locdb;
BIRTH_DB bdb;
int offset= 0;
char plu = 0;
UpdateData(TRUE);
GetData(locdb);
if ( OpenClipboard() ) {
    HANDLE hMem = GetClipboardData(CF_TEXT);
	if ( hMem != NULL ) {
	   LPSTR pdata = (char *)GlobalLock(hMem);
	   if (pdata != NULL ) {
	      memset( ptrs, 0, 11*sizeof(LPSTR));
          ptrs[0] = pdata;
		  aptr = pdata+1;
		  for ( i = 1, cnt = 0; i < 10; i++, cnt++ ) {
		    if ( aptr == NULL )
				break;
			aptr = strchr(aptr,'\x0d');
			if ( aptr != NULL ) {
			   *aptr = '\0';
			   aptr++;
			   aptr++;
			   ptrs[i] = aptr;
			   aptr++;
			   }
		    }
	      }
	   for ( int i = 0; i <= cnt; i++ ) {
		   switch ( i ) {
			  case 0 : 
				  sscanf( ptrs[i], "%d %d %d", &bdb.birth_data.birth_date.month,
					  &bdb.birth_data.birth_date.day,
					  &bdb.birth_data.birth_date.year);
				  break;
			  case 1 : 
				 break;
			  case 2 : 
				  strcpy( locdb.location, ptrs[i] );
				 break;
              case 3 : 
			     strcpy( state, ptrs[i] );
				 break;
              case 4 : 
			     strcpy( country, ptrs[i] );
				 break;
			  case 5 : 
				  sscanf( ptrs[i], "%d %s %d", &locdb.latitude.degrees,
					  cod, &locdb.latitude.minutes );
				  locdb.latitude.dir = toupper(cod[0]);
				 break;
			  case 6 : 
				  sscanf( ptrs[i], "%d %s %d", &locdb.longitude.degrees,
					  cod, &locdb.longitude.minutes );
				  locdb.longitude.dir = toupper(cod[0]);
				 break;
			  case 7 :
			     sscanf(ptrs[i], "%d ", &offset );
				 break;
			  case 8 : 
				 break;
		      case 9 :
				  sscanf(ptrs[i], "%c %d h  %d m", &plu, &locdb.hrs_offset, &locdb.min_offset );
				  if ( plu == '-' )
					  locdb.hrs_offset = -locdb.hrs_offset;
				  break;
		   }
	   }
	   fixtzsc( offset, locdb.hrs_offset - offset, locdb.time_zone, locdb.special_code );	     
	   if ( bdb.birth_data.birth_date.year > 1945 && locdb.special_code==1 )
		   locdb.special_code = 2;
	   if ( locdb.longitude.dir == 'W' && locdb.longitude.degrees > 60 &&
		      locdb.longitude.degrees <= 130 && strnicmp( country, "Mexico", 6 ) &&
			  strnicmp(country,"Canada", 6) && locdb.latitude.degrees >= 24 ) {
				  strcpy( locdb.country, "USA");
				  strcpy( locdb.state, state );
		  }
	   else {
		   if ( !strlen(state) )
		      strcpy( locdb.state, state );
		   else
		      strcpy( locdb.state, "General");
		   strcpy( locdb.country, country );
	   }
	}
    GlobalUnlock(hMem);
	CloseClipboard();
	SetData(locdb);
	UpdateData(FALSE);
  }
}
