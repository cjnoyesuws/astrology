// BirthInfo.cpp : implementation file
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
#include "BirthInfoPropPage.h"
#include <afxpriv.h>
#include "zipcodedlg.h"
#include "ChartWizard.h"

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

extern int LastSunday( int year, int month );
extern int IsInDaylightSavings( COleDateTime &dt );


#define TZ_OTHER 21
#define SC_OTHER 6

static char spec_vals[] = { 0, -1, -1, -2, -1, 1, 0 };
static char tim_vals[] = { 3, 4, 5, 6, 7, 8, 10, 0, -1, -2, -3, -8, -9, -7, -12,
		   -10, -8, -8, 5, 11, 12, 0, 0, 0,0,0,0 };


/////////////////////////////////////////////////////////////////////////////
// CBirthInfoPropPage dialog

IMPLEMENT_DYNAMIC(CBirthInfoPropPage, CPropertyPage)
CBirthInfoPropPage::CBirthInfoPropPage()
: CPropertyPage(CBirthInfoPropPage::IDD, 0)
, m_notsure(FALSE)
{
//{{AFX_DATA_INIT(CBirthInfoPropPage)
	m_country = _T("");
	m_eastwest = -1;
	m_gmthr = 0;
	m_gmtmin = 0;
	m_ladeg = 0;
	m_lamin = 0;
	m_location = _T("");
	m_lodeg = 0;
	m_ampm = -1;
	m_day = 0;
	m_hr = 0;
	m_min = 0;
	m_mo = 0;
	m_name = _T("");
	m_sex = -1;
	m_year = 0;
	m_lomin = 0;
	m_northsouth = -1;
	m_speccode = -1;
	m_state = _T("");
	m_timezone = -1;
	m_cdp = 0;
	m_bIsCompat = 0;
	//}}AFX_DATA_INIT
 pLocDb = new DaoLocDatabase();
 pMenu = NULL;
 pBirthDb = new DaoBirthDatabase();
 bRectDone = FALSE;
}

CBirthInfoPropPage::CBirthInfoPropPage(UINT nIdd)
: CPropertyPage(nIdd, 0)
{
	//{{AFX_DATA_INIT(CBirthInfoPropPage)
	m_country = _T("");
	m_eastwest = -1;
	m_gmthr = 0;
	m_gmtmin = 0;
	m_ladeg = 0;
	m_lamin = 0;
	m_location = _T("");
	m_lodeg = 0;
	m_ampm = -1;
	m_day = 0;
	m_hr = 0;
	m_min = 0;
	m_mo = 0;
	m_name = _T("");
	m_sex = -1;
	m_year = 0;
	m_lomin = 0;
	m_northsouth = -1;
	m_speccode = -1;
	m_state = _T("");
	m_timezone = -1;
	m_cdp = 0;
	m_bIsCompat = 1;
	//}}AFX_DATA_INIT
 pLocDb = new DaoLocDatabase();
 pMenu = NULL;
 pBirthDb = new DaoBirthDatabase();
 bRectDone = FALSE;
}


void CBirthInfoPropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBirthInfoPropPage)
	if ( !pDX->m_bSaveAndValidate )
		m_gmthr = tim_vals[m_timezone];
	showGmtCtl(1);
	DDX_CBString(pDX, ID_RLCOUNTRY, m_country);
	DDV_MaxChars(pDX, m_country, 29);
	DDX_CBIndex(pDX, ID_RLEASTWEST, m_eastwest);
	DDX_Text(pDX, ID_RLGMTHR, m_gmthr);
	DDV_MinMaxInt(pDX, m_gmthr, -12, 12);
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
	DDX_CBIndex(pDX, ID_BISEX, m_sex);
	DDX_Text(pDX, ID_BIYEAR, m_year);
	DDV_MinMaxInt(pDX, m_year, -3000,3000);
	DDX_Text(pDX, ID_RLLOMIN, m_lomin);
	DDV_MinMaxInt(pDX, m_lomin, 0, 59);
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
	DDX_Check(pDX, IDC_NOTSURE, m_notsure);
}


BEGIN_MESSAGE_MAP(CBirthInfoPropPage, CDialog)
	//{{AFX_MSG_MAP(CBirthInfoPropPage)
	ON_BN_CLICKED(ID_BIMENU, OnBimenu)
	ON_CBN_SELCHANGE(ID_BINAME, OnSelchangeBiname)
	ON_BN_CLICKED(ID_BIRECT, OnBirect)
	ON_CBN_EDITCHANGE(ID_RLCOUNTRY, OnEditchangeRlcountry)
	ON_CBN_KILLFOCUS(ID_RLCOUNTRY, OnKillfocusRlcountry)
	ON_CBN_EDITCHANGE(ID_RLLOCATION, OnEditchangeRllocation)
	ON_CBN_SELCHANGE(ID_RLLOCATION, OnSelchangeRllocation)
	ON_CBN_EDITCHANGE(ID_RLSTATE, OnEditchangeRlstate)
	ON_CBN_SELCHANGE(ID_RLSTATE, OnSelchangeRlstate)
	ON_CBN_SELCHANGE(ID_RLTIMEZONE, OnSelchangeRltimezone)
	ON_CBN_SELCHANGE(ID_RLSPECCODE, OnSelchangeRltimezone)
	ON_BN_CLICKED(ID_RLMENU, OnRlmenu)
	ON_CBN_EDITCHANGE(ID_BINAME, OnEditchangeBiname)
	ON_CBN_KILLFOCUS(ID_RLSTATE, OnKillfocusRlstate)
	ON_CBN_SELCHANGE(ID_RLCOUNTRY, OnSelchangeRlcountry)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBirthInfoPropPage message handlers

void CBirthInfoPropPage::OnBimenu()
{
	// TODO: Add your control notification handler code here
if ( pMenu != NULL )
   delete pMenu;
pMenu = new CMenu();
pMenu->LoadMenu("BIRTH");
 if ( m_name.GetLength() ) {
    pMenu->EnableMenuItem(ID_ADDBIRTH, MF_ENABLED );
    pMenu->EnableMenuItem(ID_GETBIRTH, MF_ENABLED );
	pMenu->EnableMenuItem(ID_DELETEBIRTH, MF_ENABLED );
    }
 else {
    pMenu->EnableMenuItem(ID_ADDBIRTH, MF_DISABLED );
    pMenu->EnableMenuItem(ID_GETBIRTH, MF_DISABLED );
	pMenu->EnableMenuItem(ID_DELETEBIRTH, MF_DISABLED );
    pMenu->EnableMenuItem(ID_ADDBIRTH, MF_GRAYED );
    pMenu->EnableMenuItem(ID_GETBIRTH, MF_GRAYED );
	pMenu->EnableMenuItem(ID_DELETEBIRTH, MF_GRAYED );
    }
CRect r;
GetWindowRect(r);
pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN|TPM_LEFTBUTTON, (r.right-r.left)/2, (r.bottom - r.top)/2, this, NULL);

}

void CBirthInfoPropPage::OnSelchangeBiname()
{
	// TODO: Add your control notification handler code here
	int sel;
	BIRTH_DB db;
	RECT_DATA rct;
	memset(&db, 0, sizeof(BIRTH_DB));
	memset(&rct, 0, sizeof(RECT_DATA));
	CComboBox *pnm = (CComboBox *)GetDlgItem(ID_BINAME);
	sel = pnm->GetCurSel();
	if ( sel != CB_ERR )
	   pnm->GetLBText(sel, m_name);
	m_name.TrimLeft();
	m_name.TrimRight();
	GetData(db,rct);
	pBirthDb->setBirth(db);
	if ( m_name.GetLength() ) {
	   if ( pBirthDb->find() ) {
          db=pBirthDb->getBirth();
		  RECT_DATA *pr;
		  pr=pBirthDb->getRect();
		  rct=*pr;
		  SetData(db,rct);
		  UpdateData(FALSE);
	      }
	   }
 bBirthModified=0;

}

void CBirthInfoPropPage::OnBirect()
{
	// TODO: Add your control notification handler code here
	TIM time;
	UpdateData(TRUE);
	time.hours = m_hr;
	time.minutes = m_min;
	CRectifyData crd;
	crd.SetData(rect, time, m_ampm);
	if ( crd.DoModal() == IDOK )
	   crd.GetData(rect);
	bBirthModified=1;
	bRectDone = TRUE;
}


void CBirthInfoPropPage::OnSelchangeRltimezone()
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
 bBirthModified =1;
}


void CBirthInfoPropPage::OnKillfocusRlstate()
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
	CLocationComboBox* plo = new CLocationComboBox((CComboBox *)GetDlgItem(ID_RLLOCATION));
	plo->loadList(m_country,m_state, m_cdp);
	if (plo->SelectString(0,m_location)==LB_ERR )
	   plo->SetWindowText(m_location);
	delete plo;
   bBirthModified=1;
}

void CBirthInfoPropPage::OnKillfocusRlcountry()
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
	bBirthModified=1;
}


void CBirthInfoPropPage::OnRlmenu()
{
	// TODO: Add your control notification handler code here
if ( pMenu != NULL )
   delete pMenu;
pMenu = new CMenu();
pMenu->LoadMenu("LOCAT");
 if ( m_country.GetLength() && m_state.GetLength() &&
      m_location.GetLength() ) {
    pMenu->EnableMenuItem(ID_ADDLOCAT, MF_ENABLED );
    pMenu->EnableMenuItem(ID_GETLOCAT, MF_ENABLED );
	pMenu->EnableMenuItem(ID_DELETELOCAT, MF_ENABLED );
    }
 else {
    pMenu->EnableMenuItem(ID_ADDLOCAT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_GETLOCAT, MF_DISABLED );
    pMenu->EnableMenuItem(ID_ADDLOCAT, MF_GRAYED );
    pMenu->EnableMenuItem(ID_GETLOCAT, MF_GRAYED );
    }
CRect r;
GetWindowRect(r);
pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN|TPM_LEFTBUTTON, (r.right-r.left)/2, (r.bottom - r.top)/2, this, NULL);
}


BOOL CBirthInfoPropPage::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
LOC_DB db;
BIRTH_DB bdb;
RECT_DATA rd;

switch (LOWORD(wParam)) {
case ID_RETURN :
  	return(1);
	break;
case ID_GETLOCAT :
	UpdateData(TRUE);
	GetData(db);
	pLocDb->setLoc(db);
	if ( pLocDb->find() ) {
       db = pLocDb->getLoc();
	   SetData(db);
	   UpdateData(FALSE);
	   }
	bLocModified=0;
	return(1);
	break;
case ID_ADDLOCAT :
   	UpdateData(TRUE);
	GetData(db);
	pLocDb->setLoc(db);
	pLocDb->dosave();
	bLocModified=0;
	return(1);
	break;
case ID_DELETELOCAT :
    GetData(db);
	pLocDb->setLoc(db);
	pLocDb->dodelete();
	bLocModified=0;
	return(1);
	break;
case ID_COPYLOCAT :
    UpdateData(TRUE);
	GetData(save_loc);
	loc_saved = 1;
	return(1);
	break;
case ID_PASTELOCAT :
	UpdateData(TRUE);
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
case ID_GETBIRTH :
	UpdateData(TRUE);
	GetData(bdb,rd);
	pBirthDb->setBirth(bdb);
	pBirthDb->setRect(rd);
	if ( pBirthDb->find() ) {
       bdb=pBirthDb->getBirth();
	   RECT_DATA *pr;
	   pr=pBirthDb->getRect();
	   rd = *pr;
	   SetData(bdb,rd);
	   UpdateData(FALSE);
	   }
	bBirthModified=0;
	return(1);
	break;
case ID_ADDBIRTH :
   	UpdateData(TRUE);
	GetData(bdb,rd);
	pBirthDb->setBirth(bdb);
	pBirthDb->setRect(rd);
	pBirthDb->dosave();
	preAdjustTime();
	bBirthModified=0;
	return(1);
	break;
case ID_DELETEBIRTH :
    m_name.TrimLeft();
	m_name.TrimRight();
	UpdateData(TRUE);
	GetData(bdb, rd);
	pBirthDb->setBirth(bdb);
   	pBirthDb->dodelete();
	bBirthModified=0;
	return(1);
	break;
case ID_COPYBIRTH :
    birth_saved = 1;
	UpdateData(TRUE);
	GetData(bdb,rd);
	save_birth = bdb;
	save_rect = rd;
	preAdjustTime();
	return(1);
	break;
case ID_PASTEBIRTH :
    return(1);
	SetData(save_birth,save_rect);
	UpdateData(FALSE);
	break;
case ID_CLEARBIRTH :
    memset(&bdb,0,sizeof(BIRTH_DB));
	SetData(bdb,rect);
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
	return( 1 );
	}
	break;
case ID_PASTEACS :
	doClipboard();
	break;
case ID_MINORCENSUS :
	m_cdp ^= 7;
	break;
default :
  return CPropertyPage::OnCommand(wParam, lParam);
  break;
  }
 return 0;
}

BOOL CBirthInfoPropPage::OnInitDialog()
{
 CLocationComboBox *pco = new CLocationComboBox((CComboBox *)GetDlgItem(ID_RLCOUNTRY));
 pco->loadList();
 delete pco;
 CBirthComboBox *pnm = new CBirthComboBox((CComboBox *)GetDlgItem(ID_BINAME));
 pnm->loadList();
 delete pnm;
 CPropertyPage::OnInitDialog();
 bBirthModified=0;
 bLocModified=0;

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBirthInfoPropPage::OnSelchangeRllocation()
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
	   loc_gotten =1;
	   bLocModified=0;
	   }
  bBirthModified = 1;
}


void CBirthInfoPropPage::SetData( LOC_DB &l )
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

void CBirthInfoPropPage::GetData( LOC_DB &l )
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


void CBirthInfoPropPage::OnEditchangeRlcountry()
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
int sel = pco->GetCurSel();
if ( sel != CB_ERR )
   pco->GetLBText(sel, m_country);
bLocModified = 1;
bBirthModified = 1;
}

void CBirthInfoPropPage::OnSelchangeRlcountry()
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLCOUNTRY);
int sel = pco->GetCurSel();
if ( sel != CB_ERR )
   pco->GetLBText(sel, m_country);
bBirthModified = 1;

}

void CBirthInfoPropPage::OnEditchangeRllocation()
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLLOCATION);
int sel = pco->GetCurSel();
if ( sel != CB_ERR )
   pco->GetLBText(sel, m_location );
bBirthModified = 1;
bLocModified = 1;
}

void CBirthInfoPropPage::OnSelchangeRlstate()
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLSTATE);
int sel = pco->GetCurSel();
if ( sel != CB_ERR )
   pco->GetLBText(sel, m_state);
bBirthModified=1;
}

void CBirthInfoPropPage::OnEditchangeRlstate()
{
	// TODO: Add your control notification handler code here
CComboBox *pco = (CComboBox *)GetDlgItem(ID_RLSTATE);
int sel = pco->GetCurSel();
if ( sel != CB_ERR )
   pco->GetLBText(sel, m_state);
bBirthModified=1;
bLocModified=1;
}

BOOL CBirthInfoPropPage::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	if( pMenu != NULL ) {
	  delete pMenu;
	  pMenu = NULL;
	}
	if ( pLocDb != NULL ) {
       delete pLocDb;
	   pLocDb = NULL;
       }
    if ( pBirthDb != NULL ) {
       delete pBirthDb;
	   pBirthDb = NULL;
       }

	return CPropertyPage::DestroyWindow();
}



void CBirthInfoPropPage::SetData( BIRTH_DB &b, RECT_DATA &r )
{
rect = r;
m_sex = b.sex;
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
rect = r;
preAdjustTime();
}

void CBirthInfoPropPage::GetData( BIRTH_DB &b, RECT_DATA &r )
{
 if (m_notsure) {
	 rect.birth_time_known = 0;
	 r.rect_system = -1;
   }
r = rect;
b.sex = m_sex;
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

void CBirthInfoPropPage::OnEditchangeBiname()
{
	// TODO: Add your control notification handler code here
	int sel;
	CComboBox *pco = (CComboBox *)GetDlgItem(ID_BINAME);
	sel = pco->GetCurSel();
	if ( sel != CB_ERR )
	   pco->GetLBText(sel, m_name);
	else
       pco->GetWindowText(m_name);
	bBirthModified=1;
}


void CBirthInfoPropPage::OnOK()
{
	// TODO: Add extra validation here
	LOC_DB loc;
	BIRTH_DB bdb;
	RECT_DATA rct;

	if ( !bLocModified ) {
		UpdateData(TRUE);
	    GetData(loc);
		pLocDb->setLoc(loc);
	    pLocDb->dosave();
	}
	if ( bBirthModified ) {
		UpdateData(TRUE);
		GetData(bdb,rct);
		pBirthDb->setBirth(bdb);
		pBirthDb->setRect(rct);
		pBirthDb->dosave();
	}
	if ( m_ladeg > 60 ) {
	   AfxMessageBox("Do Not Use the Placidus or Koch House System on this chart!");
	   ((CChartWizard *)GetParent())->NorthLatitude() = TRUE;
	   }
	COleDateTime thedate(m_year, m_mo, m_day, m_hr, m_min, 0 );
	int dst = IsInDaylightSavings(thedate);
	if ( m_country == "USA" && dst==2 && m_speccode != 2 )
	   AfxMessageBox("Daylight Savings May Have Been In Effect, Check the Records");
	else if ( m_country == "USA" && dst==1 && m_speccode != 2 )
	   AfxMessageBox("Daylight Savings Was Very Likely In Effect, Check the Records");
	else if ( m_country == "USA" && ((m_year >= 1941 &&
	     m_year < 1946 ) || (m_year >= 1914 && m_year <= 1918)) && m_speccode != 1 )
	   AfxMessageBox("War Time May Have Been In Effect, Please Check!");

	if ( m_day > days_to_month(m_mo, m_year) ) {
	   AfxMessageBox( "Illegal Day!");
	   CWnd *ed = (CWnd *)GetDlgItem(ID_BIDAY);
	   ed->SetFocus();
	   return;
	   }
	else
	   CPropertyPage::OnOK();
}

void CBirthInfoPropPage::preAdjustTime()
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
    CTime t;
	t.GetCurrentTime();
	m_day = t.GetDay();
    m_mo = t.GetMonth();
    m_year = t.GetYear();
    }
 }

void CBirthInfoPropPage::adjustTime()
{
 if ( m_ampm && m_hr != 12 )
    m_hr += 12;
 else if ( !m_ampm && m_hr == 12 )
    m_hr = 0;
}

void CBirthInfoPropPage::updateCombos()
{

}

void CBirthInfoPropPage::showGmtCtl(int bShow)
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


void CBirthInfoPropPage::doClipboard()
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
GetData(bdb,rect);
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
				  sscanf(ptrs[i], "%c %d %s %d", &plu, &locdb.hrs_offset, cod,  &locdb.min_offset );
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
	SetData(bdb,rect);
	SetData(locdb);
	UpdateData(FALSE);
  }
}

LRESULT CBirthInfoPropPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
    LOC_DB loc;
	BIRTH_DB bdb;
	RECT_DATA rct;

    UpdateData(TRUE);
	if ( !bLocModified ) {
	    GetData(loc);
		pLocDb->setLoc(loc);
	    pLocDb->dosave();
	}
	if ( bBirthModified ) {
		GetData(bdb,rct);
		pBirthDb->setBirth(bdb);
		pBirthDb->setRect(rct);
		pBirthDb->dosave();
	}
	if ( m_ladeg > 60 ) {
	   AfxMessageBox("Do Not Use the Placidus or Koch House System on this chart!");
	   ((CChartWizard *)GetParent())->NorthLatitude() = TRUE;
	   }
	COleDateTime thedate(m_year, m_mo, m_day, m_hr, m_min, 0 );
	int dst = IsInDaylightSavings(thedate);
	if ( m_country == "USA" && dst==2 && m_speccode != 2 )
	   AfxMessageBox("Daylight Savings May Have Been In Effect, Check the Records");
	else if ( m_country == "USA" && dst==1 && m_speccode != 2 )
	   AfxMessageBox("Daylight Savings Was Very Likely In Effect, Check the Records");
	else if ( m_country == "USA" && ((m_year >= 1941 &&
	     m_year < 1946 ) || (m_year >= 1914 && m_year <= 1918)) && m_speccode != 1 )
	   AfxMessageBox("War Time May Have Been In Effect, Please Check!");

	if ( m_day > days_to_month(m_mo, m_year) ) {
	   AfxMessageBox( "Illegal Day!");
	   CWnd *ed = (CWnd *)GetDlgItem(ID_BIDAY);
	   ed->SetFocus();
	   return( -1 );
	   }
	else {
      if ( m_bIsCompat )
		  GetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().compat), *(((CChartWizard *)GetParent())->GetChartDataPtrs().compatrc));
	  else
		  GetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().birth),*(((CChartWizard *)GetParent())->GetChartDataPtrs().birthrc));
		return CPropertyPage::OnWizardNext();
	}
}

BOOL CBirthInfoPropPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    if ( m_bIsCompat )
		GetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().compat), *(((CChartWizard *)GetParent())->GetChartDataPtrs().compatrc));
	else
		GetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().birth),*(((CChartWizard *)GetParent())->GetChartDataPtrs().birthrc));
    CPropertyPage::OnWizardFinish();
	DestroyWindow();
	return true;
}

LRESULT CBirthInfoPropPage::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

    return CPropertyPage::OnWizardBack();
}

BOOL CBirthInfoPropPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
    if ( m_bIsCompat )
		SetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().compat), *(((CChartWizard *)GetParent())->GetChartDataPtrs().compatrc));
    else
		SetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().birth), *(((CChartWizard *)GetParent())->GetChartDataPtrs().birthrc));
    UpdateData(FALSE);
    ((CChartWizard *)GetParent())->HandleButtons();
    return CPropertyPage::OnSetActive();
}

BOOL CBirthInfoPropPage::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

     return CPropertyPage::OnKillActive();
}
