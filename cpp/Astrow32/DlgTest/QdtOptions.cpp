// QdtOptions.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "qdtopt.hpp"
#include "QdtOptions.h"
#include <afxpriv.h>
#include "adbcombbox.hpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQdtOptions dialog


CQdtOptions::CQdtOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CQdtOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQdtOptions)
	m_fampm = -1;
	m_fhr = 0;
	m_fmin = 0;
	m_lampm = -1;
	m_lhr = 0;
	m_lmin = 0;
	m_once = FALSE;
	m_restrict = FALSE;
	//}}AFX_DATA_INIT
}


void CQdtOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQdtOptions)
	DDX_CBIndex(pDX, ID_QDFAMPM, m_fampm);
	DDX_Text(pDX, ID_QDFHR, m_fhr);
	DDV_MinMaxInt(pDX, m_fhr, 1, 12);
	DDX_Text(pDX, ID_QDFMIN, m_fmin);
	DDV_MinMaxInt(pDX, m_fmin, 0, 59);
	DDX_CBIndex(pDX, ID_QDLAMPM, m_lampm);
	DDX_Text(pDX, ID_QDLHR, m_lhr);
	DDV_MinMaxInt(pDX, m_lhr, 1, 12);
	DDX_Text(pDX, ID_QDLMIN, m_lmin);
	DDV_MinMaxInt(pDX, m_lmin, 0, 59);
	DDX_Check(pDX, ID_QDONCE, m_once);
	DDX_Check(pDX, ID_QDRESTRICTTIM, m_restrict);
	//}}AFX_DATA_MAP
	if ( !pDX->m_bSaveAndValidate )
	   OnQdrestricttim(); 
}


BEGIN_MESSAGE_MAP(CQdtOptions, CDialog)
	//{{AFX_MSG_MAP(CQdtOptions)
	ON_BN_CLICKED(ID_QDRESTRICTTIM, OnQdrestricttim)
	ON_BN_CLICKED(IDHELP, OnHelp)
    ON_CBN_SELCHANGE(IDC_NAME, OnSelchangeName)
    ON_CBN_SELCHANGE(IDC_EVENT, OnSelchangeEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQdtOptions message handlers


void CQdtOptions::OnQdrestricttim() 
{
	// TODO: Add your control notification handler code here
 	CWnd *p;
	CButton *b =(CButton *)GetDlgItem(ID_QDRESTRICTTIM);
	if (b->GetCheck()==1) {
	   p = GetDlgItem(ID_QDFAMPM);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_QDFHR);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_QDFMIN);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_QDLAMPM);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_QDLHR);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_QDLMIN);
	   p->EnableWindow(TRUE);
	   }
	else {
	   p = GetDlgItem(ID_QDFAMPM);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_QDFHR);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_QDFMIN);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_QDLAMPM);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_QDLHR);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_QDLMIN);
	   p->EnableWindow(FALSE);
	   }
}


void CQdtOptions::GetData(QdtData &d)
{
d.getRunOnce() = m_once;
d.getRestrictTime() = m_restrict;
if ( m_fampm==1 )
   d.getFirstHours() = m_fhr+12;
else if ( !m_fampm && m_fhr == 12 )
    d.getFirstHours() = 0;
 else
   d.getFirstHours() = m_fhr;
if ( m_lampm==1 )
   d.getLastHours() = m_lhr+12;
else if ( !m_lampm && m_lhr == 12 )
    d.getLastHours() = 0;
else
   d.getLastHours() = m_lhr;
d.getFirstMin() = m_fmin;
d.getLastMin() = m_lmin;
d.getEvent() = m_event;
d.getName() = m_name;
}

void CQdtOptions::SetData(QdtData &d)
{
m_once = d.getRunOnce();
m_restrict = d.getRestrictTime();
if ( d.getFirstHours() > 12 ) {
   m_fampm = 1;
   m_fhr = d.getFirstHours() - 12;
   }
else if ( d.getFirstHours() == 0 ) {
   m_fampm = 0;
   m_fhr = 12;
   }
else {
   m_fampm = 0;
   m_fhr = d.getFirstHours();
   }
if ( d.getLastHours() > 12 ) {
   m_lampm = 1;
   m_lhr = d.getLastHours() - 12;
   }
else if ( d.getLastHours() == 0 ) {
   m_lampm = 0;
   m_lhr = 12;
   }
else {
   m_lampm = 0;
   m_lhr = d.getLastHours();
   }
m_fmin = d.getFirstMin();
m_lmin = d.getLastMin();
m_name = d.getName();
m_event = d.getEvent();
}


void CQdtOptions::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}

void CQdtOptions::OnSelchangeName()
{
 CComboBox *pco = (CComboBox *)GetDlgItem(IDC_NAME);
 int  sel = pco->GetCurSel();
 if ( sel != CB_ERR ) {
	 pco->GetLBText(sel, m_name);
	 }
 else
    pco->GetWindowText(m_name);
 CTransitComboBox *ptr = new CTransitComboBox((CComboBox *)GetDlgItem(IDC_EVENT));
 ptr->loadList(m_name);
 delete ptr;
}


void CQdtOptions::OnSelchangeEvent()
{
 CComboBox *pco = (CComboBox *)GetDlgItem(IDC_EVENT);
 int sel = pco->GetCurSel();
 if ( sel != CB_ERR ) {
	 pco->GetLBText(sel, m_event);
	 }
 else
    pco->GetWindowText(m_event);
   
}


 BOOL CQdtOptions::OnInitDialog()
{
 CBirthComboBox *pnm = new CBirthComboBox((CComboBox *)GetDlgItem(IDC_NAME));
 pnm->loadList();
 if (pnm->SelectString(0,m_name)==LB_ERR )
	   pnm->SetWindowText(m_name);
 delete pnm;
 CTransitComboBox *ptr = new CTransitComboBox((CComboBox *)GetDlgItem(IDC_EVENT));
 ptr->loadList(m_name);
 if (ptr->SelectString(0,m_event)==LB_ERR )
	   ptr->SetWindowText(m_event);
 delete ptr;


   CDialog::OnInitDialog();
 	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}