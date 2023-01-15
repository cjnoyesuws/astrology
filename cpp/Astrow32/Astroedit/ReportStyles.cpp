// ReportStyles.cpp : implementation file
//

#include "stdafx.h"
#ifdef CHARTVIEW
#include "chartview.h"
#else
#include "Astrow.h"
#endif
#include "repstyle.hpp"
#include "ReportStyles.h"
#include <string.h>
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportStyles dialog


CReportStyles::CReportStyles(CWnd* pParent /*=NULL*/)
	: CDialog(CReportStyles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportStyles)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReportStyles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportStyles)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportStyles, CDialog)
	//{{AFX_MSG_MAP(CReportStyles)
	ON_BN_CLICKED(ID_RSBOLD, OnRsbold)
	ON_BN_CLICKED(ID_RSHEAD, OnRshead)
	ON_BN_CLICKED(ID_RSREG, OnRsreg)
	ON_BN_CLICKED(ID_RSSCORE, OnRsscore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReportStyles message handlers

void CReportStyles::OnRsbold() 
{
	// TODO: Add your control notification handler code here
	CFontDialog cfd(styles->getBoldFont(),CF_EFFECTS|CF_SCREENFONTS,NULL,this );
	cfd.m_cf.iPointSize = styles->getBoldPointSize();
	cfd.m_cf.hDC=styles->getDC()->GetSafeHdc();	
	cfd.m_cf.rgbColors =styles->getBoldColor();
	if ( cfd.DoModal() == IDOK ) {
	   styles->getBoldColor()=cfd.GetColor();
	   styles->getBoldPointSize()=cfd.m_cf.iPointSize;
	   memcpy(styles->getBoldFont(),&cfd.m_lf,sizeof(LOGFONT)+strlen(cfd.m_lf.lfFaceName)+1);
	   }
}

void CReportStyles::OnRshead() 
{
	// TODO: Add your control notification handler code here
	CFontDialog cfd(styles->getHeadFont(),CF_EFFECTS|CF_SCREENFONTS,NULL,this );
	cfd.m_cf.hDC=styles->getDC()->GetSafeHdc();	
	cfd.m_cf.iPointSize = styles->getHeadPointSize();
	cfd.m_cf.rgbColors =styles->getHeadColor();
	if ( cfd.DoModal() == IDOK ) {
	   styles->getHeadColor()=cfd.GetColor();
	   styles->getHeadPointSize()=cfd.m_cf.iPointSize;
	   memcpy(styles->getHeadFont(),&cfd.m_lf,sizeof(LOGFONT)+strlen(cfd.m_lf.lfFaceName)+1);
	   }
}

void CReportStyles::OnRsreg() 
{
	
	// TODO: Add your control notification handler code here
	CFontDialog cfd(styles->getRegFont(),CF_EFFECTS|CF_SCREENFONTS,NULL,this);
	cfd.m_cf.iPointSize = styles->getRegPointSize();
	cfd.m_cf.hDC=styles->getDC()->GetSafeHdc();	
	cfd.m_cf.rgbColors =styles->getRegColor();
	if ( cfd.DoModal() == IDOK ) {
	   styles->getRegColor()=cfd.GetColor();
	   styles->getRegPointSize()=cfd.m_cf.iPointSize;
	   memcpy(styles->getRegFont(),&cfd.m_lf,sizeof(LOGFONT)+strlen(cfd.m_lf.lfFaceName)+1);
	   }
}

void CReportStyles::OnRsscore() 
{
	// TODO: Add your control notification handler code here
	CFontDialog cfd(styles->getItalFont(),CF_EFFECTS|CF_SCREENFONTS,NULL,this );
	cfd.m_cf.iPointSize = styles->getItalPointSize();
	cfd.m_cf.hDC=styles->getDC()->GetSafeHdc();	
	cfd.m_cf.rgbColors =styles->getItalColor();
	if ( cfd.DoModal() == IDOK ) {
	   styles->getItalColor()=cfd.GetColor();
	   styles->getItalPointSize()=cfd.m_cf.iPointSize;
	   memcpy(styles->getItalFont(),&cfd.m_lf,sizeof(LOGFONT)+strlen(cfd.m_lf.lfFaceName)+1);
	   }
}
