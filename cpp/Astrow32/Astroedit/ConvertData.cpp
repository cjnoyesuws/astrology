// ConvertData.cpp : implementation file
//

#include "stdafx.h"
#ifdef CHARTVIEW
#include "chartview.h"
#else
#include "Astrow.h"
#endif
#include "attrib.h"
#include "pseudostyle.h"
#include "repstyle.hpp"
#include "reportstyles.h"
#include "convopt.hpp"
#include "txtdrv.h"

#include "ConvertData.h"
#include <afxpriv.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvertData dialog


CConvertData::CConvertData(CWnd* pParent /*=NULL*/)
	: CDialog(CConvertData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvertData)
	m_cb4 = FALSE;
	m_cmt = FALSE;
	m_cpg = FALSE;
	m_format = -1;
	m_left = 0;
	m_width = 0;
	m_bGlyph = FALSE;
	m_glyphFont=-1;
	//}}AFX_DATA_INIT
}


void CConvertData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvertData)
	DDX_Check(pDX, ID_COCB4, m_cb4);
	DDX_Check(pDX, ID_COCMT, m_cmt);
	DDX_Check(pDX, ID_COCPG, m_cpg);
	DDX_CBIndex(pDX, ID_COFORMAT, m_format);
	DDX_Text(pDX, ID_COLEFT, m_left);
	DDV_MinMaxInt(pDX, m_left, 0, 300);
	DDX_Text(pDX, ID_COWIDTH, m_width);
	DDV_MinMaxInt(pDX, m_width, 100, 1600);
#ifdef DELUXE
#ifndef CHARTVIEW
	DDX_Check(pDX, IDC_GLYPH, m_bGlyph);
	DDX_CBIndex(pDX, IDC_GLYPHFONT, m_glyphFont);
#endif	
#endif
	//}}AFX_DATA_MAP
	if ( !pDX->m_bSaveAndValidate )
	   OnSelchangeCoformat(); 
}


BEGIN_MESSAGE_MAP(CConvertData, CDialog)
	//{{AFX_MSG_MAP(CConvertData)
	ON_CBN_SELCHANGE(ID_COFORMAT, OnSelchangeCoformat)
	ON_BN_CLICKED(ID_COPSEUDO, OnCopseudo)
	ON_BN_CLICKED(ID_COSTYLES, OnCostyles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvertData message handlers



void CConvertData::OnSelchangeCoformat() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pc = (CComboBox *)GetDlgItem(ID_COFORMAT);	   
    if ( pc != NULL ) {
	   if ( pc->GetCurSel() != -1 ) {
 	   int i = 	pc->GetCurSel();
 	   if ( i == MS_RTFDOS || i == MS_RTFANS || i == AMIPRO || i==WWW_HTML) {
	   	  CWnd *st =GetDlgItem(ID_COSTYLES);
	   	  st->EnableWindow(TRUE);
	      }
	   else{
	      CWnd *st2 = GetDlgItem(ID_COSTYLES);
	   	  st2->EnableWindow(FALSE);
	      }  
	   if ( i == ASCIITXDOS || i == ASCIITXANS || i == ASCIINBANS || i == ASCIINBDOS ) {
	   	  CWnd *st3 = GetDlgItem(ID_COPSEUDO);
	   	  st3->EnableWindow(TRUE);
	      }
	   else{
	      CWnd *st4 =GetDlgItem(ID_COPSEUDO);
	   	  st4->EnableWindow(FALSE);
	      }  
#ifdef DELUXE	   
	   if ( i != MS_RTFDOS && i != MS_RTFANS && i!=WWW_HTML ) {
	      CWnd *st5 =GetDlgItem(IDC_GLYPH);
	   	  st5->EnableWindow(FALSE);
		  CWnd *st6 =GetDlgItem(IDC_GLYPHFONT);
	   	  st6->EnableWindow(FALSE);
	      }
	   else {
	      CWnd *st7 =GetDlgItem(IDC_GLYPH);
	   	  st7->EnableWindow(TRUE);
		  CWnd *st8 =GetDlgItem(IDC_GLYPHFONT);
	   	  st8->EnableWindow(TRUE);
	      }

#endif
	   }  
  }

} 

void CConvertData::OnCopseudo() 
{
	// TODO: Add your control notification handler code here
	CPseudoStyle cps(this);
	cps.SetData(opts->getFileAttribs());
	if ( cps.DoModal() == IDOK )
	   cps.GetData(opts->getFileAttribs());
}

void CConvertData::OnCostyles() 
{
	// TODO: Add your control notification handler code here
	CReportStyles crs(this);
	crs.SetData(styles);
	crs.DoModal();
}


void CConvertData::SetData( ConvData &c, ReportStyles &r )
{
styles = &r;
opts = &c;
m_cb4 = c.getCmtFst();
m_cmt = c.getCmt();
m_cpg = c.getCpg();
m_format = c.getFmt();
m_left = c.getLeft();
m_width = c.getWidth();
m_bGlyph = (c.getGlyph()?TRUE:FALSE);
m_glyphFont = c.getGlyphFont();
}

void CConvertData::GetData( ConvData &c )
{
 c.getCmtFst() = m_cb4;
 c.getCmt() = m_cmt;
 c.getCpg() = m_cpg;
 c.getFmt() = m_format;
 c.getLeft() = m_left;
 c.getWidth() = m_width;
 if ( m_bGlyph == TRUE )
	 c.getGlyph() = 1;
 else
	 c.getGlyph() = 0;
 c.getGlyphFont() = m_glyphFont;
}

