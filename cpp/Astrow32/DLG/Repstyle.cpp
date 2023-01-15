#include "stdafx.h"
#include "repstyle.hpp"
#include "inifile.hpp"
 
#define setuplf(v,h,we,i,u,s,fm,fn) \
   v->lfHeight=h;\
   v->lfWidth=0;\
   v->lfEscapement=0;\
   v->lfOrientation=0;\
   v->lfWeight=we;\
   v->lfItalic=i;\
   v->lfUnderline=u;\
   v->lfStrikeOut=s;\
   v->lfCharSet=ANSI_CHARSET;\
   v->lfOutPrecision=OUT_DEFAULT_PRECIS;\
   v->lfClipPrecision=CLIP_DEFAULT_PRECIS;\
   v->lfQuality=DEFAULT_QUALITY;\
   v->lfPitchAndFamily=fm|VARIABLE_PITCH;\
   strcpy(v->lfFaceName, fn)


ReportStyles::ReportStyles(CDC *d, int viewer, int grid)
{
dc = d;
char * fname = "Times New Roman";
int style = FF_ROMAN;
if ( !grid ) {
   regpointsize = 120;
   boldpointsize = 120;
   italpointsize = 120;
   headpointsize = 150;
}
else {
   regpointsize = 90;
   boldpointsize = 90;
   italpointsize = 90;
   headpointsize = 150;
   fname = "Arial Narrow";
   style = FF_SWISS;
}
	
float cy =(float)d->GetDeviceCaps(LOGPIXELSY) / 720.0;
regfont = (LOGFONT *) new char[sizeof(LOGFONT)+100];
setuplf(regfont,(int)regpointsize*cy,FW_NORMAL,FALSE,FALSE,FALSE,style,fname);
boldfont = (LOGFONT *) new char[sizeof(LOGFONT)+100];
setuplf(boldfont,(int)boldpointsize*cy,FW_BOLD,FALSE,FALSE,FALSE,style,fname);	 
headfont = (LOGFONT *) new char[sizeof(LOGFONT)+100];
setuplf(headfont,(int)headpointsize*cy,FW_BOLD,FALSE,FALSE,FALSE,FF_SWISS,"Arial");	 
italfont = (LOGFONT *) new char[sizeof(LOGFONT)+100];
setuplf(italfont,(int)italpointsize*cy,FW_NORMAL,TRUE,TRUE,FALSE,style,fname);	 	 

 if ( viewer ) {
    headcolor = checkColor(RGB( 0, 0, 0xff ));
    boldcolor = checkColor(RGB( 0xff, 0, 0 ));
    italcolor = checkColor(RGB( 0, 0xff, 0 ));
    regcolor = checkColor(RGB(0,0,0));
    }
else {
    headcolor = RGB( 0, 0, 0xff );
    boldcolor = RGB( 0xff, 0, 0 );
    italcolor = RGB( 0, 0xff, 0 );
    regcolor =  RGB(0,0,0);
    }
}

void ReportStyles::Update( ReportStyles &r)
{
regpointsize = r.regpointsize;
boldpointsize = r.boldpointsize;
italpointsize = r.italpointsize;
headpointsize = r.headpointsize;
headcolor = r.headcolor;
boldcolor = r.boldcolor;
italcolor = r.italcolor;
regcolor = 	r.regcolor;
*regfont = *r.regfont;
*boldfont = *r.boldfont;
*headfont = *r.headfont;
*italfont = *r.italfont;
}

int ReportStyles::adjustSize( int s )
{
  float cy =(float)dc->GetDeviceCaps(LOGPIXELSY) / 720.0;   
  cy *= (float) s;
  s = (int)cy;
  return s;
}


COLORREF ReportStyles::checkColor( COLORREF c )
{
 COLORREF bk = GetSysColor(COLOR_WINDOW);
 BYTE r, g, b;
 
 if ( GetRValue(c) == GetRValue(bk) &&
      GetBValue(c) == GetBValue(bk) &&
      GetGValue(c) == GetGValue(bk) ) {
    r = GetRValue(c);
    b = GetBValue(c);
    g = GetGValue(c);
    r ^= 0xff;
	b ^= 0xff;
	g ^= 0xff;
	c = RGB(r,g,b);
	return( c );
    }
 else
    return( c );
}

int ReportStyles::getFromIni( char *sec )
{
 
 if ( !readFontColorFromIni(sec, "Reg", regfont, regcolor, regpointsize ) )
    return( 0 );
 regfont->lfHeight = adjustSize(regpointsize);
 
 if ( !readFontColorFromIni(sec, "Bold", boldfont, boldcolor, boldpointsize ) )
    return( 0 );
 boldfont->lfHeight = adjustSize(boldpointsize);
 if ( !readFontColorFromIni(sec, "Head", headfont, headcolor, headpointsize ) )
    return( 0 );
 headfont->lfHeight = adjustSize(headpointsize);
 if ( !readFontColorFromIni(sec, "Ital", italfont, italcolor, italpointsize ) )
    return( 0 );
 italfont->lfHeight = adjustSize(italpointsize);
 return( 1 );
}

int ReportStyles::saveToIni( char *sec )
{
 regfont->lfHeight = adjustSize(regpointsize);
 if ( !saveFontColorToIni(sec, "Reg", regfont, regcolor, regpointsize ) )
    return( 0 );
 boldfont->lfHeight = adjustSize(boldpointsize);
 if ( !saveFontColorToIni(sec, "Bold", boldfont, boldcolor, regpointsize ) )
    return( 0 );
 headfont->lfHeight = adjustSize(headpointsize);
 if ( !saveFontColorToIni(sec, "Head", headfont, headcolor, headpointsize ) )
    return( 0 );
 italfont->lfHeight = adjustSize(italpointsize);
 if ( !saveFontColorToIni(sec, "Ital", italfont, italcolor, italpointsize ) )
    return( 0 );
 return( 1 );
}

/*ReportStylesDlgf::ReportStylesDlgf(zWindow *par, ReportStyles *f, zDisplay *d) : FormDlgf(par,zResId("REP_STYLES"), HELPID_DLG_STYLE )
{
 data = f;
 dsp = d;
 run();
}

int ReportStylesDlgf::doStyle(zColor &c, zFontSpec *pfs )
{
 if ( dsp->type() == WinDisp )
    dsp->lock();
 zFontSelForm *fsf = new zFontSelForm(this, c, pfs, dsp );
 if ( dsp->type() == WinDisp )
    dsp->unlock();
  if ( fsf->completed() ) {
     c = fsf->color();
     *pfs = *fsf->fontSpec();
     }
  delete fsf;
  return( 1 );
}


int ReportStylesDlgf::command(zCommandEvt *e)
{
 zFontSpec fs;
 zColor c;
 switch( e->cmd() ) {
      case IDC_RCREG :
	   doStyle( data->getRegColor(), data->getRegFont() );
	   return( 1 );
	   break;
      case IDC_RCBOLD :
	   doStyle( data->getBoldColor(), data->getBoldFont() );
	   return( 1 );
	   break;
      case IDC_RCHEAD :
	   doStyle( data->getHeadColor(), data->getHeadFont() );
	   return( 1 );
	   break;
      case IDC_RCITAL :
	   doStyle( data->getItalColor(), data->getItalFont() );
	   return( 1 );
	   break;
      default :
	   return( 0 );
	   break;
      }
 return( 0 );
}

*/


