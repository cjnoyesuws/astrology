// GraFont.cpp : implementation file
//

#include "stdafx.h"
#ifndef GRAVIEWER
#include "Astrow.h"
#else
#include "Astrograph.h"
#endif
#include "grafont.hpp"
#include "GraFont.h"
#include "inifile.hpp"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraFont dialog


CGraFont::CGraFont(CWnd* pParent /*=NULL*/)
	: CDialog(CGraFont::IDD, pParent)
{
 	//{{AFX_DATA_INIT(CGraFont)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGraFont::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraFont)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraFont, CDialog)
	//{{AFX_MSG_MAP(CGraFont)
	ON_BN_CLICKED(ID_DATAFNT, OnDatafnt)
	ON_BN_CLICKED(ID_GLYPHFNT, OnGlyphfnt)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraFont message handlers

void CGraFont::OnDatafnt() 
{
	// TODO: Add your control notification handler code here
	LPLOGFONT pfs;
	pfs = (LPLOGFONT) new char[sizeof(LOGFONT)+100];
	pfs->lfHeight=20;
	pfs->lfWidth=0;
	pfs->lfEscapement=0;
	pfs->lfOrientation=0;
	pfs->lfWeight=FW_NORMAL;
	pfs->lfItalic=FALSE;
	pfs->lfUnderline=FALSE;
	pfs->lfStrikeOut=FALSE;
	pfs->lfCharSet=ANSI_CHARSET;
	pfs->lfOutPrecision=OUT_DEFAULT_PRECIS;
	pfs->lfClipPrecision=CLIP_DEFAULT_PRECIS;
	pfs->lfQuality=DEFAULT_QUALITY;
	pfs->lfPitchAndFamily=FF_DONTCARE|VARIABLE_PITCH;
	strcpy( pfs->lfFaceName,pgf->getDataFont());
	CFontDialog cfd(pfs);
	if ( cfd.DoModal() == IDOK )
	   pgf->getDataFont() = cfd.GetFaceName();
	delete pfs;
}

void CGraFont::OnGlyphfnt() 
{
	// TODO: Add your control notification handler code here
	LPLOGFONT pfs;
	pfs = (LPLOGFONT) new char[sizeof(LOGFONT)+100];
	pfs->lfHeight=20;
	pfs->lfWidth=0;
	pfs->lfEscapement=0;
	pfs->lfOrientation=0;
	pfs->lfWeight=FW_NORMAL;
	pfs->lfItalic=FALSE;
	pfs->lfUnderline=FALSE;
	pfs->lfStrikeOut=FALSE;
	pfs->lfCharSet=SYMBOL_CHARSET;
	pfs->lfOutPrecision=OUT_DEFAULT_PRECIS;
	pfs->lfClipPrecision=CLIP_DEFAULT_PRECIS;
	pfs->lfQuality=DEFAULT_QUALITY;
	pfs->lfPitchAndFamily=FF_DECORATIVE|VARIABLE_PITCH;
	strcpy( pfs->lfFaceName,pgf->getGlyphFont());
	CFontDialog cfd(pfs);
	if ( cfd.DoModal() == IDOK )
	   pgf->getGlyphFont() = cfd.GetFaceName();
	delete pfs;
}

void CGraFont::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}


void CGraFont::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
