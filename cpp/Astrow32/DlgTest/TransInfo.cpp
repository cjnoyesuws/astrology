// TransInfo.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include <dos.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "dataext.h"
#include "charcons.h"
#include "datetime.fns"
#include "databaseodbc.hpp"
#include "adbcombbox.hpp"
#include "rectifydata.h"
#include "TransInfo.h"
#include <afxpriv.h>
#include "zipcodedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static LOC_DB save_loc;
static int loc_saved = 0;
static BIRTH_DB save_birth;
static RECT_DATA save_rect;
static int birth_saved = 0;
static int loc_gotten = 0;
static int in_update_data = 0;

extern int IsInDaylightSavings( COleDateTime &dt );

#define TZ_OTHER 21
#define SC_OTHER 6

static char spec_vals[] = { 0, -1, -1, -2, -1, 1, 0 };
static char tim_vals[] = { 3, 4, 5, 6, 7, 8, 10, 0, -1, -2, -3, -8, -9, -7, -12,
		   -10, -8, -8, 5, 11, 12, 0, 0, 0, 0,0,0,0 };



/////////////////////////////////////////////////////////////////////////////
// CTransInfo dialog


CTransInfo::CTransInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CTransInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransInfo)
	m_ampm = -1;
	m_day = 0;
	m_hr = 0;
	m_min = 0;
	m_mo = 0;
	m_name = _T("");
	m_year = 0;
	m_country = _T("");
	m_eastwest = -1;
	m_gmthr = 0;
	m_gmtmin = 0;
	m_ladeg = 0;
	m_lamin = 0;
	m_location = _T("");
	m_lodeg = 0;
	m_lomin = 0;
	m_northsouth = -1;
	m_speccode = -1;
	m_state = _T("");
	m_timezone = -1;
	m_cdp = 0;
	//}}AFX_DATA_INIT
 pLocDb = new DaoLocDatabase();
 pMenu = NULL;
 pTransitDb = new DaoTransitDatabase();

}


void CTransInfo::DoDataExchange(CDataExchange* pDX)
{
	
	CDialog::DoDataExchange(pDX);
	if ( !pDX->m_bSaveAndValidate )
		m_gmthr = tim_vals[m_timezone];
	//{{AFX_DATA_MAP(CTransInfo)
	DDX_CBIndex(pDX, ID_BIAMPM, m_ampm);
	DDX_Text(pDX, ID_BIDAY, m_day);
	DDV_MinMaxInt(pDX, m_day, 0, 31);
	DDX_Text(pDX, ID_BIHR, m_hr);
	DDV_MinMaxInt(pDX, m_hr, 1, 12);
	DDX_Text(pDX, ID_BIMIN, m_min);
	DDV_MinMaxInt(pDX, m_min, 0, 59);
	DDX_Text(pDX, ID_BIMO, m_mo);
	DDV_MinMaxInt(pDX, m_mo, 1, 12);
	DDX_CBString(pDX, ID_BINAME, m_name);
	DDV_MaxChars(pDX, m_name, 49);
	DDX_Text(pDX, ID_BIYEAR, m_year);
	DDV_MinMaxInt(pDX, m_year, -3000, 3000);
	DDX_CBString(pDX, ID_RLCOUNTRY, m_country);
	DDX_CBIndex(pDX, ID_RLEASTWEST, m_eastwest);
	DDX_Text(pDX, ID_RLGMTHR, m_gmthr);
	DDX_Text(pDX, ID_RLGMTMIN, m_gmtmin);
	DDV_MinMaxInt(pDX, m_gmtmin, 0, 59);
	DDX_Text(pDX, ID_RLLADEG, m_ladeg);
	DDV_MinMaxInt(pDX, m_ladeg, 0, 120);
	DDX_Text(pDX, ID_RLLAMIN, m_lamin);
	DDV_MinMaxInt(pDX, m_lamin, 0, 59);
	DDX_CBString(pDX, ID_RLLOCATION, m_location);
	DDV_MaxChars(pDX, m_location, 39);
	DDX_Text(pDX, ID_RLLODEG, m_lodeg);
	DDV_MinMaxInt(pDX, m_lodeg, 0, 180);
	DDX_Text(pDX, ID_RLLOMIN, m_lomin);
	DDV_MinMaxInt(pDX, m_lomin, 0, 60);
	DDX_CBIndex(pDX, ID_RLNORTHSOUTH, m_northsouth);
	//DDX_CBIndex(pDX, ID_RLSPECCODE, m_speccode);
	DDX_CBString(pDX, ID_RLSTATE, m_state);
	DDV_MaxChars(pDX, m_state, 29);
	//DDX_CBIndex(pDX, ID_RLTIMEZONE, m_timezone);
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


BEGIN_MESSAGE_MAP(CTransInfo, CDialog)
	//{{AFX_MSG_MAP(CTransInfo)
	ON_CBN_EDITCHANGE(ID_BINAME, OnEditchangeBiname)
	ON_CBN_SELCHANGE(ID_BINAME, OnSelchangeBiname)
	ON_CBN_EDITCHANGE(ID_RLCOUNTRY, OnEditchangeRlcountry)
	ON_CBN_KILLFOCUS(ID_RLCOUNTRY, OnKillfocusRlcountry)
	ON_CBN_SELCHANGE(ID_RLCOUNTRY, OnSelchangeRlcountry)
	ON_CBN_EDITCHANGE(ID_RLLOCATION, OnEditchangeRllocation)
	ON_CBN_SELCHANGE(ID_RLLOCATION, OnSelchangeRllocation)
	ON_BN_CLICKED(ID_RLMENU, OnRlmenu)
	ON_CBN_EDITCHANGE(ID_RLSTATE, OnEditchangeRlstate)
	ON_CBN_KILLFOCUS(ID_RLSTATE, OnKillfocusRlstate)
	ON_CBN_SELCHANGE(ID_RLSTATE, OnSelchangeRlstate)
	ON_CBN_SELCHANGE(ID_RLTIMEZONE, OnSelchangeRltimezone)
	ON_CBN_SELCHANGE(ID_RLSPECCODE, OnSelchangeRltimezone)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransInfo message handlers

void CTransInfo::OnSelchangeBiname() 
{
	// TODO: Add your control notification handler code here
	int sel;
	BIRTH_DB  trans;	
	RECT_DATA rct;
	CComboBox *pnm = (CComboBox *)GetDlgItem(ID_BINAME);
	sel = pnm->GetCurSel();
	if ( sel != CB_ERR ) 
	   pnm->GetLBText(sel, m_name);
	m_name.TrimLeft();
	m_name.TrimRight();
	GetData(trans);
	pTransitDb->setBirth(birth_rec);
	pTransitDb->setTrans(trans);
	if ( m_name.GetLength() ) {
	   if ( pTransitDb->find() ) {
		  trans = pTransitDb->getTrans();
		  SetData(trans);
		  UpdateData(FALSE);
		  bLocModified = 0;
		  bTransModified = 0;
	      }
	   }
}


void CTransInfo::OnSelchangeRltimezone() 
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
 bTransModified = 1;
 bLocModified = 1;

}


void CTransInfo::OnKillfocusRlstate() 
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
	plo->loadList(m_country,m_state, m_cdp );
	if (plo->SelectString(0,m_location)==LB_ERR )
	   	  plo->SetWindowText(m_location);
    delete plo;
}

void CTransInfo::OnKillfocusRlcountry() 
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
	if ( pst->SelectString(0,m_state)==LB_ERR )
	   pst->SetWindowText(m_state);
    delete pst;
}


void CTransInfo::OnRlmenu() 
{
	// TODO: Add your control notification handler code here
if ( pMenu != NULL )
   delete pMenu;
pMenu = new CMenu();
pMenu->LoadMenu("TRANSIT"); 
if ( m_country.GetLength() && m_state.GetLength() && m_location.GetLength() ) {
    pMenu->EnableMenuItem(ID_ADDLOCAT, MF_ENABLED );
	pMenu->EnableMenuItem(ID_DELETELOCAT, MF_ENABLED );
    pMenu->EnableMenuItem(ID_GETLOCAT, MF_ENABLED );
    }
 else {
    pMenu->EnableMenuItem(ID_DELETELOCAT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_DELETELOCAT, MF_GRAYED );
    pMenu->EnableMenuItem(ID_REPLACELOCAT, MF_GRAYED );
    }
 if ( m_name.GetLength() ) {
    pMenu->EnableMenuItem(ID_ADDTRANSIT, MF_ENABLED );
    pMenu->EnableMenuItem(ID_GETTRANSIT, MF_ENABLED );
	pMenu->EnableMenuItem(ID_DELETE_TRANSIT, MF_ENABLED );
    }
 else {
    pMenu->EnableMenuItem(ID_ADDTRANSIT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_DELETE_TRANSIT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_GETTRANSIT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_ADDTRANSIT, MF_GRAYED );
    pMenu->EnableMenuItem(ID_GETTRANSIT, MF_GRAYED );
    }
CRect r;
GetWindowRect(r);
pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN|TPM_LEFTBUTTON, (r.right-r.left)/2, (r.bottom - r.top)/2, this, NULL);		
}


BOOL CTransInfo::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
LOC_DB db;
BIRTH_DB trans;

switch (LOWORD(wParam)) {
case ID_RETURN :
  	return(1);
	break;
case ID_GETLOCAT :
    GetData(db);
	pLocDb->setLoc(db);
	if ( pLocDb->find() ) {
	   db = pLocDb->getLoc();
	   SetData(db);
	   UpdateData(FALSE);
	   }
	bLocModified=0;
	bTransModified=1;
	return(1);
	break;
case ID_ADDLOCAT :    
   	UpdateData(TRUE);
	GetData(db);
	pLocDb->setLoc( db );
	pLocDb->dosave();
	bLocModified=0;
	return(1);
	break;
case ID_DELETELOCAT : 
    m_country.TrimLeft();
	m_state.TrimLeft();	
	m_location.TrimLeft();
	m_country.TrimRight();
	m_state.TrimRight();
	m_location.TrimRight();
	GetData(db);
	pLocDb->setLoc(db);
	pLocDb->dodelete();
	bLocModified = 0;
	return(1);
	break;
case ID_GETTRANSIT :    
	//UpdateData(TRUE);
	GetData(trans);
	pTransitDb->setBirth(birth_rec);
	pTransitDb->setTrans(trans);
	if ( pTransitDb->find() ) {
       trans=pTransitDb->getTrans();
	   SetData(trans);
	   UpdateData(FALSE);
	   }
	bTransModified=0;
	return(1);
	break;
case ID_ADDTRANSIT :    
   	UpdateData(TRUE);
	GetData(trans);
	pTransitDb->setBirth(birth_rec);
	pTransitDb->setTrans(trans);
	pTransitDb->dosave();
	preAdjustTime();
	bTransModified=0;
	return(1);
	break;
case ID_DELETE_TRANSIT : 
    m_name.TrimLeft();
	m_name.TrimRight();
	GetData(trans);
	pTransitDb->setBirth(birth_rec);
	pTransitDb->setTrans(trans);
   	pTransitDb->dodelete();
	bTransModified=0;
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
 return ( 0 );
}

BOOL CTransInfo::OnInitDialog() 
{
    CLocationComboBox *pco = new CLocationComboBox((CComboBox *)GetDlgItem(ID_RLCOUNTRY));
    pco->loadList();
    delete pco;
	CTransitComboBox *pnm = new CTransitComboBox((CComboBox *)GetDlgItem(ID_BINAME));
    pnm->loadList(CString(birth_rec.name));
 	delete pnm;
	CDialog::OnInitDialog();
  
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransInfo::OnSelchangeRllocation() 
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
	   UpdateData(FALSE);
	   loc_gotten=1;
	   CComboBox *pco = (CComboBox *)GetDlgItem(ID_BINAME);
	   if ( pco->SelectString(0,(const char *)m_name ) == CB_ERR)
	      pco->SetWindowText((const char *)m_name);
	   }
}


void CTransInfo::SetData( LOC_DB &l )
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

void CTransInfo::GetData( LOC_DB &l )
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


void CTransInfo::OnEditchangeRlcountry() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_country);
bLocModified=1;	
bTransModified=1;
}

void CTransInfo::OnSelchangeRlcountry() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_country);	
bTransModified=1;	
}

void CTransInfo::OnEditchangeRllocation() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLLOCATION);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_location );
bLocModified=1;
bTransModified=1;
}

void CTransInfo::OnSelchangeRlstate() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLSTATE);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_state);	
bTransModified=1;	
}

void CTransInfo::OnEditchangeRlstate() 
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLSTATE);
int sel = pco->GetCurSel();
if ( sel != CB_ERR ) 
   pco->GetLBText(sel, m_state);	
bLocModified=1;
bTransModified=1;
}

BOOL CTransInfo::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	if( pMenu != NULL )
	  delete pMenu;
    delete pLocDb;
    delete pTransitDb;

	return CDialog::DestroyWindow();
}



void CTransInfo::SetData( BIRTH_DB &b)
{
m_ampm =b.am_pm;
m_country = b.country;
m_name = b.name;
m_state = b.state;
m_location = b.location;
m_timezone = b.time_zone;
m_speccode = b.special_code;
m_ladeg = b.birth_data.latitude.degrees;
m_lodeg = b.birth_data.longitude.degrees;
m_lamin = b.birth_data.latitude.minutes;
m_lomin = b.birth_data.longitude.minutes;
m_gmthr = b.birth_data.hour_adjust;
m_gmtmin = b.birth_data.minutes_adjust;
m_eastwest = (b.birth_data.longitude.dir =='E'?1:0);
m_northsouth = (b.birth_data.latitude.dir=='S'?1:0);
m_mo = b.birth_data.birth_date.month;
m_day = b.birth_data.birth_date.day;
m_year = b.birth_data.birth_date.year;
m_hr = b.birth_data.birth_time.hours;
m_min = b.birth_data.birth_time.minutes;
preAdjustTime();
}

void CTransInfo::GetData( BIRTH_DB &b)
{
adjustTime();
b.am_pm = m_ampm;
strcpy(b.name,m_name);
strcpy(b.country,m_country);
strcpy(b.state,m_state);
strcpy(b.location,m_location);
b.time_zone = m_timezone;
b.special_code = m_speccode;
b.birth_data.latitude.degrees = m_ladeg;
b.birth_data.latitude.minutes = m_lamin;
b.birth_data.latitude.dir = (m_northsouth?'S':'N');
b.birth_data.longitude.degrees = m_lodeg;
b.birth_data.longitude.minutes = m_lomin;
b.birth_data.longitude.dir = (m_eastwest?'E':'W');
b.birth_data.hour_adjust = m_gmthr;
b.birth_data.minutes_adjust = m_gmtmin;
b.birth_data.local_adjust = m_gmthr;
b.birth_data.local_minutes = m_gmtmin;
b.birth_data.birth_date.month = m_mo;
b.birth_data.birth_date.day = m_day;
b.birth_data.birth_date.year = m_year;
b.birth_data.birth_time.hours = m_hr;
b.birth_data.birth_time.minutes = m_min;
}

void CTransInfo::OnEditchangeBiname() 
{
	// TODO: Add your control notification handler code here
	int sel;
	CComboBox *pco = (CComboBox *)GetDlgItem(ID_BINAME);
	sel = pco->GetCurSel();
	if ( sel != CB_ERR ) 
	   pco->GetLBText(sel, m_name);
	else
       pco->GetWindowText(m_name);
	bTransModified=1;
}


void CTransInfo::OnOK() 
{
	// TODO: Add extra validation here
	LOC_DB loc;
	BIRTH_DB trans;
	if ( m_ladeg > 60 ) {
	   MessageBox("Do Not Use the Placidus or Koch House System on this chart!", "Warning");
	   }
	if ( m_name.Trim().GetLength()==0) {
	   MessageBox("You Must Give the Transit Event a Name");
	   return;
	}
	COleDateTime thedate(m_year, m_mo, m_day, m_hr, m_min, 0 );
	int dst = IsInDaylightSavings(thedate);
	if ( m_country == "USA" && dst==2 ) 
	   MessageBox("Daylight Savings May Have Been In Effect, Check the Records", "Warning");
	else if ( m_country == "USA" && dst==1 ) 
	   MessageBox("Daylight Savings Was Very Likely In Effect, Check the Records", "Warning");
    else if ( m_country == "USA" && ((m_year >= 1941 &&
	     m_year < 1946 ) || (m_year >= 1914 && m_year <= 1918)) && m_speccode != 1 )
	   MessageBox("War Time May Have Been In Effect, Please Check!", "Warning");
	if ( bLocModified ) {
       UpdateData(TRUE);
	   GetData(loc);
	   pLocDb->setLoc(loc);
	   pLocDb->dosave();
	}
	if ( bTransModified ) {
	   UpdateData(TRUE);
	   GetData(trans);
	   pTransitDb->setBirth(birth_rec);
	   pTransitDb->setTrans(trans);
	   pTransitDb->dosave();
	}


	if ( m_day > days_to_month(m_mo, m_year) ) {
	   MessageBox( "Illegal Day!", "Error!!" );
	   CWnd *ed = (CWnd *)GetDlgItem(ID_BIDAY);
	   ed->SetFocus();
	   }
	else
	   CDialog::OnOK();
}

void CTransInfo::preAdjustTime()
{
 if ( !m_ampm ) {
    if ( m_hr == 12 )
       m_ampm = 1;
    else if ( m_hr == 0 )
       m_hr = 12;
    else {
       if ( m_hr > 12 ) {
          m_ampm = 1;
          m_hr -= 12;
          }
         }
    }
 else {
    if ( m_hr == 0 ) {
       m_hr = 12;
       m_ampm = 0;
       }
    else if ( m_hr > 12 ) 
       m_hr -= 12;
      }
 /* first startup of session load today's date into the structure so
    we can exit legally without entering data if cursor in one of date
    fields */
 if ( m_mo == 0 && m_day == 0 ) {
    SYSTEMTIME t;
	GetSystemTime(&t);
	m_day = t.wDay;
    m_mo = t.wMonth;
    m_year = t.wYear;
    }
 }

void CTransInfo::adjustTime()
{
 if ( m_ampm && m_hr != 12 )
    m_hr += 12;
 else if ( !m_ampm && m_hr == 12 )
    m_hr = 0;
}

void CTransInfo::updateCombos()
{

}


void CTransInfo::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}

void CTransInfo::showGmtCtl(int bShow)
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


void CTransInfo::doClipboard()
{
LPSTR ptrs[11], aptr= NULL;
char state[100], country[100], cod[3];
int i, cnt;
BIRTH_DB bdb;
LOC_DB locdb;
RECT_DATA rect;
int offset= 0;
char plu = 0;
UpdateData(TRUE);
GetData(bdb);
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
				  sscanf( ptrs[i], "%d %d", &bdb.birth_data.birth_time.hours,
					  &bdb.birth_data.birth_time.minutes );
				  if ( bdb.birth_data.birth_time.hours > 12 ) {
				     bdb.birth_data.birth_time.hours -= 12;
					 bdb.am_pm = 1;
				  }
                  else if ( bdb.birth_data.birth_time.hours == 12 ) {
					 bdb.am_pm = 1;
				  }
				  else
					  bdb.am_pm = 0;
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
	SetData(bdb);
	SetData(locdb);
	UpdateData(FALSE);
  }
}

