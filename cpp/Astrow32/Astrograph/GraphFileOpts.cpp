// GraphFileOpts.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "grafilop.hpp"
#include "GraphFileOpts.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static char hd[] = "&Height (Dots):";
static char hi[] = "&Height (Inch):";
static char hm[] = "&Height (mm):";
static char wd[] = "&Width (Dots):";
static char wi[] = "&Width (Inch):";
static char wm[] = "&Width (mm):";
static char *hdims[] = {hd,hi,hm,0 };
static char *wdims[] = {wd,wi,wm,0 };


/////////////////////////////////////////////////////////////////////////////
// CGraphFileOpts dialog


CGraphFileOpts::CGraphFileOpts(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphFileOpts::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphFileOpts)
	m_format = -1;
	m_height = 0.0f;
	m_units = -1;
	m_resolution = -1;
	m_reversgra = FALSE;
	m_width = 0.0f;
	//}}AFX_DATA_INIT
}


void CGraphFileOpts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphFileOpts)
	DDX_CBIndex(pDX, ID_GFFORMAT, m_format);
	DDX_Text(pDX, ID_GFHEIGHT, m_height);
	DDX_CBIndex(pDX, ID_GFUNITS, m_units);
	DDX_CBIndex(pDX, ID_GFRES, m_resolution);
	DDX_Check(pDX, ID_GFREVGRA, m_reversgra);
	DDX_Text(pDX, ID_GFWIDTH, m_width);
	//}}AFX_DATA_MAP
}								   

								 
BEGIN_MESSAGE_MAP(CGraphFileOpts, CDialog)
	//{{AFX_MSG_MAP(CGraphFileOpts)
	ON_CBN_SELCHANGE(ID_GFUNITS, OnSelchangeGfunits)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphFileOpts message handlers

void CGraphFileOpts::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}


void CGraphFileOpts::OnSelchangeGfunits() 
{					  
	// TODO: Add your control notification handler code here
 
 CComboBox *pc = (CComboBox *)GetDlgItem(ID_GFUNITS);
 if ( pc != NULL ) {
	if ( pc->GetCurSel() != -1 ) {
 	   int i = 	pc->GetCurSel();
 	   CWnd *st =GetDlgItem(ID_GFWDU);
       st->SetWindowText(wdims[i]);		  
	   CWnd *st2 = GetDlgItem(ID_GFHTU);
	   st2->SetWindowText(hdims[i]);
	   }
	}
}



void CGraphFileOpts::GetData( GraphFileData &p )
{
 p.getFormat() = m_format;
 p.getHeight() = m_height;
 p.getUnits() = m_units;
 p.getResolution() = m_resolution;
 p.getReverse() = m_reversgra;
 p.getWidth() = m_width;
}


void CGraphFileOpts::SetData( GraphFileData &p )
{
 m_format = p.getFormat();
 m_height = p.getHeight();
 m_units = p.getUnits();
 m_resolution = p.getResolution();
 m_reversgra = p.getReverse();
 m_width = p.getWidth();
}
void CGraphFileOpts::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
