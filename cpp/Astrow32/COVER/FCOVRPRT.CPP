#include "stdafx.h"
#include <stdlib.h>
#include <io.h>
#include "astro.h"
#include "useri.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "coverdat.hpp"
#include "fcovrprt.hpp"
#include "paths.hpp"
#include "inifile.hpp"


/* need to integrate this class into CAstroviewView class */

char agmap[] = {"abcdefghijklwxyz{|}~\x7f\x80\x81\x82" };
char wdmap[] = {"^_`abcdefghi" };
char apmap[] = {"YZ[\\]^_`abcdABCDEFGHIJKLefgh"};
char aprmap[] ={"ijklmnopqrstMNOPQRSTUVWXuvwx"};
char byline[] = { "Produced by\n{ASTRO}--The Program for Astrological"
      " Analysis.\n(C) 1988 - 1999 by Christopher J. Noyes\n" };

char *maps[] = {agmap, apmap, aprmap, wdmap};

CBitmap *loadBitmap( char *file, CDC *dsp );

CoverPagePrinter::CoverPagePrinter(CoverPageData *d)
{
 data = d;
 pfGlyph = NULL;
 pBmUser = NULL;
}

CoverPagePrinter::~CoverPagePrinter()
{
 if ( pfGlyph != NULL )
    delete pfGlyph;
 if ( pBmUser != NULL )
    delete pBmUser;
}


int CoverPagePrinter::printSetup(CDC *pdc, CPrintInfo *pi)
{
 char fbuf[100], chrs[70], fnt[50], stl[4], set[4];
 int sz;
 char *ptr;
 LPLOGFONT lf;
 char *fnames[] = { "AstGlyphs", "AstPi1", "AstPi1", "WingDings" };
 
 if ( pfGlyph != NULL )
    delete pfGlyph;
 if ( data->getFont() == USER_FNT ) {
    strcpy( fbuf, (char *) (LPCTSTR)data->getFile() );
    sscanf( fbuf, "%[^\\]\\%d\\%[^\\]\\%[^\\]\\%s", fnt, &sz, stl, set, chrs );
    pfGlyph = new CFont();
	ptr = new char[sizeof(LOGFONT)+100];
	lf = (LPLOGFONT)ptr;
	strcpy( lf->lfFaceName, fnt );
	lf->lfWeight=(stl[0]=='B'||stl[1]=='B'?FW_BOLD:FW_NORMAL);
    lf->lfItalic = (stl[0]=='I'||stl[1]=='I'?TRUE:FALSE);
    lf->lfUnderline = 0;
	lf->lfStrikeOut = 0;
    lf->lfEscapement = 0;
	lf->lfOrientation = 0;
	lf->lfCharSet =(stl[0]=='A'||stl[1]=='A'?ANSI_CHARSET:SYMBOL_CHARSET);
	lf->lfPitchAndFamily = FF_DONTCARE|VARIABLE_PITCH;
    lf->lfHeight = sz * 10;
    lf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf->lfOutPrecision = OUT_TT_PRECIS;
    lf->lfQuality = DEFAULT_QUALITY;     
 pfGlyph->CreatePointFontIndirect(lf,pdc);	
 }
 else if ( data->getFont() == USER_BMP ) {
    pBmUser = loadBitmap( (char *)(LPCTSTR) data->getFile(), pdc );
    }
 else {
    pfGlyph = new CFont();
	delete lf;	
	ptr = new char[sizeof(LOGFONT)+100];
	lf = (LPLOGFONT)ptr;
	strcpy( lf->lfFaceName, fnames[data->getFont()] );
	lf->lfWidth = 0;
	lf->lfHeight = 1440;
	lf->lfWeight=FW_NORMAL;
    lf->lfItalic = 0;
    lf->lfUnderline = 0;
	lf->lfStrikeOut = 0;
    lf->lfEscapement = 0;
	lf->lfOrientation = 0;
	lf->lfCharSet =SYMBOL_CHARSET;
	lf->lfPitchAndFamily = FF_DONTCARE|VARIABLE_PITCH;
	lf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf->lfOutPrecision = OUT_TT_PRECIS;
    lf->lfQuality = DEFAULT_QUALITY;     
	pfGlyph->CreatePointFontIndirect(lf,pdc)		;
	delete lf;   
 }
 return(1);
}

/* need to work out positioning and translate zLoEnglish into logical positioning */

int CoverPagePrinter::print(CDC *pdc, CPrintInfo *pi)
{
 int wid;
 char buf[150], name[100], *map;
 char fnt[50], stl[4], set[4];
 int sz;
 int fl;
 int ofs;
 char *byline;
 CFont *fold;

 if (pfGlyph != NULL) {
    fold = pdc->SelectObject(pfGlyph);
    if ( data->getFont() == USER_FNT ) {
       strcpy( name, (char *)(LPCTSTR) data->getFile() );
       sscanf( name, "%[^\\]\\%d\\%[^\\]\\%[^\\]\\%s", fnt, &sz, stl, set, buf );
       }
    else {
       map = maps[data->getFont()];
       buf[0] = map[data->getImage()];
       buf[1] = '\0';
       }
    pdc->SetTextColor(ctHead);
    pdc->TextOut(cxStart, cyTop, buf);
    pdc->SelectObject(fold);
    }
 if ( pBmUser != NULL ) {
    zLoEnglish led(200, 175, pd);
        
	CDC *tmp = new CDC();
	tmp->CreateCompatibleDC(pdc);
	BITMAP b;
	
	tmp->SelectObject(pb);
	tmp->SetMapMode(pdc->GetMapMode());
	
	pBmUser->GetObject(sizeof(BITMAP),(LPSTR)&b);
	CPoint si(b.bmWidth,b.bmHeight);
	CPoint org(0,0);

	pdc->DPtoLP(&si,1);
	tmp->DPtoLP(&org,1);
	
	ret = pdc->BitBlt(x,y,si.x,si.y,tmp,org.x,org.y,SRC_COPY);
	delete tmp;
    }
 fold = pdc->SelectObject(pfHead);
 pdc->SetTextColor(ctHead);
 wid = pd->GetTextExtent((char *)(LPCTSTR)data->getTitle()).cx;
 pdc->text(cxStart+((cxClient-wid)/2),zLoEnglish(0,225,pd).y()+cyTop,
     (char *)(LPCTSTR)data->getTitle() );
 pdc->SelectObject(fold);
 cyCur = zLoEnglish(0,325,pd).y()+cyTop;
 
 sprintf( buf, fmt1, (char _far *)(LPCTSTR)data->getName() );
 fl = 0;
 ofs = 0;
 drawPara( buf, strlen(buf), fl, ofs );
 fl = 0;
 ofs = 0;
 drawPara( (char *)(LPCTSTR)data->getComments(), data->getComments().GetLength(), fl, ofs );
 cyCur = cyBottom - zLoEnglish(0,200,pd).y();
 fl = 0;
 ofs = 0;
 sprintf( buf, fmt3, (char _far *)(LPCTSTR)data->getAstName() );
 drawPara( buf, strlen(buf), fl, ofs );
 fl = 0;
 ofs = 0;
 cyCur = cyBottom - zLoEnglish(0,100,pd).y();
 drawPara( byline, strlen(byline), fl, ofs );
 return( 1 );
}

