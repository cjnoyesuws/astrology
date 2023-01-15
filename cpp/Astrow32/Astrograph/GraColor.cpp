// GraColor.cpp : implementation file
//

#include "stdafx.h"
#ifndef GRAVIEWER
#include "Astrow.h"
#else
#include "Astrograph.h"
#endif
#include "asdrawbs.hpp"
#include "gracolor.hpp"
#include "GraColor.h"
#include "inifile.hpp"
#include <afxpriv.h>
//#include ".\gracolor.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraColor dialog


CGraColor::CGraColor(CWnd* pParent /*=NULL*/)
	: CDialog(CGraColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraColor)
	m_RevBack = FALSE;
	//}}AFX_DATA_INIT
}


void CGraColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraColor)
	DDX_Check(pDX, IDC_REVCOLOR, m_RevBack);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraColor, CDialog)
	//{{AFX_MSG_MAP(CGraColor)
	ON_BN_CLICKED(ID_GCASCEND, OnGcascend)
	ON_BN_CLICKED(ID_GCBACK, OnGcback)
	ON_BN_CLICKED(ID_GCBHOUSE, OnGcbhouse)
	ON_BN_CLICKED(ID_GCBPLAN, OnGcbplan)
	ON_BN_CLICKED(ID_GCBSIGN, OnGcbsign)
	ON_BN_CLICKED(ID_GCCIRC, OnGccirc)
	ON_BN_CLICKED(ID_GCHOUSE, OnGchouse)
	ON_BN_CLICKED(ID_GCSIGN, OnGcsign)
	ON_BN_CLICKED(IDC_GCPLAN, OnGcplan)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_REVBACK, OnBnClickedRevback)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraColor message handlers
/*
#define BR 8
#define RISE 6
#define PLAN 7
#define SIGN 2
#define HOUS 4
#define CIRC 8
#define ASPECTBR  16
#define SIGNCRBR  17
*/


void CGraColor::OnGcascend() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(RISE);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(RISE) = cdd.GetColor();
}

void CGraColor::OnGcback() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(0);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(0) = cdd.GetColor();	
}

void CGraColor::OnGcbhouse() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(HOUS+BR);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(HOUS+BR) = cdd.GetColor();
	
}

void CGraColor::OnGcbplan() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(PLAN+BR);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(PLAN+BR) = cdd.GetColor();
	
}

void CGraColor::OnGcbsign() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(SIGN+BR);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(SIGN+BR) = cdd.GetColor();
	
}

void CGraColor::OnGccirc() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(CIRC);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(CIRC) = cdd.GetColor();
	
}

void CGraColor::OnGchouse() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(HOUS);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(HOUS) = cdd.GetColor();
	
}

void CGraColor::OnGcsign() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(SIGN);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(SIGN) = cdd.GetColor();
	
}

void CGraColor::OnGcplan() 
{
	// TODO: Add your control notification handler code here
	COLORREF color = pgc->getColor(PLAN);
	CColorDialog cdd(color);
	if ( cdd.DoModal() == IDOK )
	   pgc->getColor(PLAN) = cdd.GetColor();
	
}

void CGraColor::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CGraColor::SetGraphicColors(GraphicColors *p)
{
 pgc = p;
}

void CGraColor::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}

void CGraColor::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	
}

void CGraColor::OnBnClickedRevback()
{
	// TODO: Add your control notification handler code here
}
