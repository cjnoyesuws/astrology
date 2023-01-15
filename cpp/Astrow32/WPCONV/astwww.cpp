#include "stdafx.h"
#ifndef CHARTVIEW
#include "astrow.h"
#else
#include "chartview.h"
#endif
#include <io.h>
#include "astro.h"
#include <share.h>
#include "attrib.h"
#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "errors.fns"

static int codepage=0;

static char *accents[128] = {"&iexcl;","&cent;","&pound;","&curren;","&yen;","&brvbar;","&sect;","&uml;","&COPY;","&ordf;","&laquo;","&SHY;",
"&REG;","&hibar;","&deg;","&plusmn;","&sup2;","&sup3;","&acute;","&micro;","&para;","&cedil;","&sup1;","&ordm;","&raquo;",
"&frac14;","&frac12;","&frac34;","&iquest;","&Agrave;","&Aacute;","&Acirc;","&Atilde;","&Auml;","&Aring;","&AElig;","&Ccedil;",
"&Egrave;","&Eacute;","&Ecirc;","&Euml;","&Igrave;","&Iacute;","&Icirc;","&Iuml;","&ETH;","&Ntilde;","&Ograve;","&Oacute;",
"&Ocirc;","&Otilde;","&Ouml;","&times;","&Oslash;","&Ugrave;","&Uacute;","&Ucirc;","&Uuml;","&Yacute;","&THORN;","&szlig;",
"&agrave;","&aacute;","&acirc;","&atilde;","&auml;","&aring;","&aelig;","&ccedil;","&egrave;","&eacute;","&ecirc;","&euml;",
"&igrave;","&iacute;","&icirc;","&iuml;","&eth;","&ntilde;","&ograve;","&oacute;","&ocirc;","&otilde;","&ouml;","&divide;",
"&oslash;","&ugrave;","&uacute;","&ucirc;","&uuml;","&yacute;","&thorn;","&yuml;" };
static char *gifPl[] = {"SUN","MOON","MERCURY","VENUS","MARS","JUPITER","SATURN","URANUS","NEPTUNE","PLUTO","NORTH","SOUTH"};
static char *gifSig[] = {"ARI","TAU","GEM","CAN","LEO","VIR","LIB","SCO","SAG","CAP","AQU","PIS"};
static char *glfont[] = {"AstGlyphs","AstPi1","AstPi1"};
static char *fontstart = "<font face=\"%s\" font-size=\"36pt\">";
static char *endfont = "</font>";
static char *imgtag= "<img src=\"%c%s.GIF\">";


int TextConvDriverHTML::foreign( unsigned char c )
{
 if ( !codepage ) {
#ifdef _UNICODEVER
	 CPINFOEX info;
	 GetCPInfoEx(CP_THREAD_ACP,0,&info);
	 codepage = info.CodePage;
#else
	 codepage = 1252;
#endif
 }
 if ( c == 32 )
	 fputc(' ', ostream );
 else if ( c < 255 && c > 160 && codepage == 1252 )
	 fprintf( ostream, "%s", accents[c-163] );
 else
     fprintf( ostream, "&#%x;", (int) c );
 return( 0 );
}

void toUtf8( wchar_t c, char *buf )
{
 int low, high, xlow;

 low = ((int)c &0xff7f);
 xlow = ((int) c)>> 7;
 high = 0x0060;
 high |= xlow;
 sprintf(buf,"&#%2x%2x;", high,low );
}


void TextConvDriverHTML::mbforeign( char *c )
{
#ifdef _UNICODEVER
  wchar_t bf[2];
  char buf[10];
  mbtowc(bf,c,1);
  toUtf8(bf[0],buf);
  fputs(buf,ostream);
#else
  foreign( (unsigned char) *c );
#endif

}


void TextConvDriverHTML::finishUpJob()
{
 fprintf(ostream,"</p></div>");
 CString trailer = AfxGetApp()->GetProfileString( "wwwconvert", "trailer", "" );
 if ( !trailer.IsEmpty() ) {
     char *buf = new char[1010];
	   FILE *stream = fopen( trailer, "rt" );
	   if ( stream == NULL )
		   do_error( (LPCSTR)trailer );
	   else {
		   int len;
		   do {
			   len= fread(buf, 1, 1000, stream );
			   fwrite(buf, 1, len, ostream );
		   } while ( len == 1000 );
		   fclose( stream );
	   }

	}
fprintf(ostream,"</p></body>\n</html>\n" );
}


void TextConvDriverHTML::initDriver( FIL_ATTRIB *a )
{
 atrb.head_on = "";
 atrb.head_off= "";
 atrb.head_on = "<60>/p<62><60>/div<62><60>center<62><60>h2<62>";
 atrb.head_off = "<60>/h2<62><60>/center<62><60>div<62><60>p<62>";
 atrb.bold_on = "<60>b<62>";
 atrb.bold_off = "<60>/b<62>";
 atrb.uscore_on = "<60>u<62>";
 atrb.uscore_off = "<60>/u<62>";
 setCrs("</p><p>", "<br/>");
}




void TextConvDriverHTML::initStringPrint( int left, int width, int version, int code   )
{
 margin = "";
 char buf[5];
 if ( code == -1 || !code ) {
    fprintf(ostream,"<html>\n<head><title>An ASTRO for Windows Report</title>\n");
    writestyles(ostream);
	fprintf(ostream,"</head><body>" );
	CString header = AfxGetApp()->GetProfileString( "wwwconvert", "header", "" );
	if ( !header.IsEmpty() ) {
       char *buf = new char[1010];
	   FILE *stream = fopen( header, "rt" );
	   if ( stream == NULL )
		   do_error( (LPCSTR)header );
	   else {
		   int len;
		   do {
			   len= fread(buf, 1, 1000, stream );
			   fwrite(buf, 1, len, ostream );
		   } while ( len == 1000 );
		   fclose( stream );
	   }

	}
	fprintf( ostream, "<DIV><p>" );
 }
}


char *TextConvDriverHTML::tabOut( char *buf, int *col, int *sz )
{
if ( bTableMode == FALSE )
   return( tab_out_buf( pTabs, buf, col, sz ) );
else {
   *buf++ = F_BINARY;
   *buf++ = 9;
   strcpy(buf, "</td><td>");
   *sz += 11;
   *col +=3;
   return ( buf + 9 );
   }
}

char *TextConvDriverHTML::TableCode(char *buf, int *sz )
{
 char *p;
 if ( bTableMode==FALSE )
	 bTableMode=TRUE;
 else
	 bTableMode=FALSE;
 if ( bTableMode == TRUE )
	p = "<table width=\"100%\" border=\"1\"><tr><td>";
 else {
	p = "</td></tr></table><p>\n";
    percent = -1;
 }
 sz += strlen(p)+2;
 *buf++ = F_BINARY;
 *buf++ = strlen(p);
 strcpy(buf,p);
 return(buf+strlen(p));
}
char *TextConvDriverHTML::TableRow(char *buf, int *sz )
{
 *buf++ = F_BINARY;
 *buf++ = 19;
 *sz += 21;
 strcpy(buf, "\n</td></tr><tr><td>" );
 return( buf + 19 );
}

void TextConvDriverHTML::PlanetGlyph(int n)
{
 static char gst[] = {0x61,0x69,0x59};
 if (!doGlyph)
	 return;
 if ( n==0 || n > SOUTH_NODE )
	 return;
 if ( glyphFont > 2 ) {
   fprintf(ostream,imgtag,((glyphFont-3)+'A'),gifPl[n-1]);
 }
 else {
   fprintf(ostream,fontstart,glfont[glyphFont]);
   fprintf(ostream,"%c%s",gst[glyphFont]+n-1, endfont );
 }
}

void TextConvDriverHTML::SignGlyph(int n)
{
 static char gst[] = {0x77,0x41,0x4d};
 if (!doGlyph)
	return;
 if ( glyphFont > 2 ) {
   fprintf(ostream,imgtag,((glyphFont-3)+'A'),gifSig[n-1]);
 }
 else {
   fprintf(ostream,fontstart,glfont[glyphFont]);
   fprintf(ostream,"%c%s",gst[glyphFont]+n-1, endfont );
 }
}

char *TextConvDriverHTML::Nbsp(char *buf, int *sz)
{
 *buf++ = F_BINARY;
 *buf++ = 6;
 strcpy( buf,"&nbsp;");
 *sz+= 8;
 return( buf + 6 );
}

int fixSize( int size,  CDC *dc )
{
	size = abs(size);
	size *= 72;
    size += (dc->GetDeviceCaps(LOGPIXELSY)/2);
    size /= dc->GetDeviceCaps(LOGPIXELSY);
    return size;
}

void TextConvDriverHTML::writestyles(FILE *stream )
{
 char buf[5];
 COLORREF color;
 LOGFONT *pFnt;
 CDC *cdc = new CDC;
 cdc->CreateIC("DISPLAY",NULL,NULL,0);
 fputs("<style type=\"text/css\">\n", stream );
 color = pRs->getRegColor();
 fprintf(stream,"body {background-color:white; color:rgb(%d,%d,%d);}\n", GetRValue(color),GetGValue(color),GetBValue(color) );
 pFnt = pRs->getRegFont();
 writestyle(stream,"div",pFnt->lfFaceName,lftowt(pFnt),lftofs(pFnt),color, fixSize(pFnt->lfHeight,cdc) );
 writestyle(stream,"td",pFnt->lfFaceName,lftowt(pFnt),lftofs(pFnt),color, fixSize(pFnt->lfHeight,cdc) );
 pFnt = pRs->getBoldFont();
 color = pRs->getBoldColor();
 writestyle(stream,"b",pFnt->lfFaceName,lftowt(pFnt),lftofs(pFnt),color, fixSize(pFnt->lfHeight,cdc) );
 pFnt = pRs->getItalFont();
 color = pRs->getItalColor();
 writestyle(stream,"u",pFnt->lfFaceName,lftowt(pFnt),lftofs(pFnt),color, fixSize(pFnt->lfHeight,cdc) );
 pFnt = pRs->getHeadFont();
 color = pRs->getHeadColor();
 for ( int i = 0; i < 6; i++ ) {
   sprintf(buf,"h%d",i);
   writestyle(stream,buf,pFnt->lfFaceName,lftowt(pFnt),lftofs(pFnt),color, fixSize(pFnt->lfHeight,cdc) );
   }
 fputs("</style>\n", stream );
  delete cdc;
}

const char *TextConvDriverHTML::lftofs( LOGFONT *fnt )
{
	if ( fnt->lfItalic )
		return("italic");
	else if ( fnt->lfUnderline )
		return( "underline" );
	else
		return("normal");
}

const char *TextConvDriverHTML::lftowt( LOGFONT *fnt )
{
	if ( fnt->lfWeight > FW_MEDIUM && fnt->lfWeight <= FW_BOLD )
       return( "bold" );
	else if ( fnt->lfWeight > FW_BOLD )
	   return( "bolder" );
	else
	   return( "normal" );
}

char *TextConvDriverHTML::TablePct(int pct, char *buf, int *sz )
{
 return buf;
}

void TextConvDriverHTML::writestyle(FILE *stream, const char *tag, const char *font, const char *weight, const char *style, COLORREF &color, int size )
{
	fprintf(stream, "%s { font-family:\"%s\"; font-style:%s; font-weight: %s; font-size: %dpt; color:rgb(%d,%d,%d);}\n",
	 tag, font, style, weight, size, GetRValue(color),GetGValue(color),GetBValue(color) );
}