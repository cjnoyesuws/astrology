// GraphOpts.cpp : implementation file
//

#include "stdafx.h"
#ifndef GRAVIEWER
#include "Astrow.h"
#else
#include "Astrograph.h"
#endif
#include "asgflags.h"
#include "asdrawbs.hpp"
#include "gracolor.hpp"
#include "grafont.hpp"
#include "gracolor.h"
#include "grafont.h"
#include "graopt.hpp"
#include "GraphOpts.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphOpts dialog


CGraphOpts::CGraphOpts(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphOpts::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphOpts)
	m_dectick = FALSE;
	m_degtick = FALSE;
	m_fontsize = 100;
	m_housedeg = FALSE;
	m_housenum = FALSE;
	m_hsnumouts = FALSE;
	m_plotclass = FALSE;
	m_showagrid = FALSE;
	m_showaspt = FALSE;
	m_showpdeg = FALSE;
	m_sigline = FALSE;
	m_signname = FALSE;
	m_signtick = FALSE;
	m_useglyphs = FALSE;
	//}}AFX_DATA_INIT
}


void CGraphOpts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphOpts)
	DDX_Check(pDX, ID_GODEC_TICK, m_dectick);
	DDX_Check(pDX, ID_GODEG_TICK, m_degtick);
	DDX_Text(pDX, ID_GOFONTSIZE, m_fontsize);
	DDX_Check(pDX, ID_GOHOUSE_DEG, m_housedeg);
	DDX_Check(pDX, ID_GOHOUSE_NUM, m_housenum);
	DDX_Check(pDX, ID_GOHSNUM_OUTS, m_hsnumouts);
	DDX_Check(pDX, ID_GOPLOT_CLASS, m_plotclass);
	DDX_Check(pDX, ID_GOSHOW_AGRID, m_showagrid);
	DDX_Check(pDX, ID_GOSHOW_ASPT, m_showaspt);
	DDX_Check(pDX, ID_GOSHOW_PDEG, m_showpdeg);
	DDX_Check(pDX, ID_GOSIGLINE, m_sigline);
	DDX_Check(pDX, ID_GOSIGN_NAME, m_signname);
	DDX_Check(pDX, ID_GOSIGN_TICK, m_signtick);
	DDX_Check(pDX, ID_GOUSE_GLYPHS, m_useglyphs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphOpts, CDialog)
	//{{AFX_MSG_MAP(CGraphOpts)
	ON_BN_CLICKED(ID_GOCOLORS, OnGocolors)
	ON_BN_CLICKED(ID_GOFONTS, OnGofonts)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphOpts message handlers

void CGraphOpts::OnGocolors() 
{
	// TODO: Add your control notification handler code here
	CGraColor gc;
	gc.SetGraphicColors(pgc);
	gc.DoModal();
}

void CGraphOpts::OnGofonts() 
{
	// TODO: Add your control notification handler code here
	CGraFont gf;
	gf.SetGraphicFonts(pgf);
	gf.DoModal();
}

void CGraphOpts::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CGraphOpts::SetGraphicColors( GraphicColors *p)
{
 pgc = p;
}

void CGraphOpts::SetGraphicFonts( GraphicFonts *p )
{
 pgf = p;
}

void CGraphOpts::GetData( unsigned short &flg, int &fs )
{
 unsigned short mode = 0;
 setOpt(HOUSE_DEG,m_housedeg,mode);
 setOpt(HOUSE_NUM,m_housenum,mode);
 setOpt(SHOW_SLIN,m_sigline,mode);
 setOpt(SHOW_ASPT,m_showaspt,mode);
 setOpt(USE_GLYPH,m_useglyphs,mode);
 setOpt(SIGN_TICK,m_signtick,mode);
 setOpt(DEC_TICK,m_dectick,mode);
 setOpt(DEG_TICK,m_degtick,mode);
 setOpt(SIGN_NAME,m_signname,mode);
 setOpt(PLOT_CLASSIC,m_plotclass,mode);
 setOpt(SHOW_PDEGS,m_showpdeg,mode);
 setOpt(HOUS_OUTS,m_hsnumouts,mode);
 setOpt(SHOW_AGRID,m_showagrid,mode);
 flg = mode;
 if ( m_fontsize == 0 )
	m_fontsize = 100;
 fs = m_fontsize;
}

void CGraphOpts::SetData( unsigned short flg, int fs )
{
 m_housedeg = getOpt(HOUSE_DEG,flg);
 m_housenum = getOpt(HOUSE_NUM,flg);
 m_sigline = getOpt(SHOW_SLIN,flg);
 m_showaspt = getOpt(SHOW_ASPT,flg);
 m_showagrid = getOpt(SHOW_AGRID,flg);
 m_useglyphs = getOpt(USE_GLYPH,flg);
 m_signtick = getOpt(SIGN_TICK,flg);
 m_dectick = getOpt(DEC_TICK,flg);
 m_degtick = getOpt(DEG_TICK,flg);
 m_signname = getOpt(SIGN_NAME,flg);
 m_plotclass = getOpt(PLOT_CLASSIC,flg);
 m_showpdeg = getOpt(SHOW_PDEGS,flg);
 m_hsnumouts = getOpt(HOUS_OUTS,flg);
 m_fontsize = fs;
}

void CGraphOpts::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
