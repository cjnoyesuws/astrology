#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <share.h>
#include "attrib.h"
#include "output.fns"
#include "errors.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"

static char RTFBON[] = "{\\b ";
static char RTFBOF[] = "}";
static char RTFUON[] = "{\\ul ";
static char RTFUOF[] = "}";
static char RTFCON[] = "{\\qc\\b\\ul ";
static char RTFLON[] = "{\\ql\\b\\ul ";
static char RTFHON[] = "{\\keepn\\qc\\b\\ul ";
static char RTFHOF[] = "\\par}\\keepn";


static char slbuf[100];
static char shbuf[100];

char *fntCodetotype( int code )
{
 static char *tps[] = {"fnil", "froman", "fswiss",
    "fmodern", "fscript", "fdecor", "ftech" };
 code /= 16;
 return( tps[code] );  
}

int TextConvDriverRTF::foreign( unsigned char c )
{
 char buf[10];
 unsigned char bf[10];

 if ( ansi && toOem ) {
    bf[0] = c;
    bf[1] = '\0';
    AnsiToOemBuff( (LPSTR)bf, (LPSTR)&bf[5], 1 );
    c = bf[5];
    }
 else if ( !ansi && !toOem ) {
    bf[0] = c;
    bf[1] = '\0';
    OemToAnsiBuff( (LPSTR)bf, (LPSTR)&bf[5], 1 );
    c = bf[5];
    }
 sprintf( buf, "\\" "\'" "%2x", c );
 return( fputs( buf, ostream ) );
}

void TextConvDriverRTF::initDriver( FIL_ATTRIB *a )
{
 setCrs("\\keep\\par\r\n", " \r\n");
}

void TextConvDriverRTF::initStringPrint( int left, int width )
{
 static char fmt2[] = { "{\\stylesheet {\\s0%s"
     " Normal;}}\r\n{\\s0%s{\\s0%s" };				  //\\margl%d\\margr%d
 static char fmt3[] = { " {\\s0%s{" };
 static char fmt4[] = {  "\\keep\\par\r\n" };
 long t;
 int w, fc, hc;
 FILE *hs;
 char buf[202], *fn, *hn;

 margin = "";
 if ( width+left > 850 )
    width = 100;
 else
    width = 850 - (width+left);
 t = width;
 t *= 144L;
 width = t / 10L;
 t = left;
 t *= 144L;
 left = t / 10L;
 if ( !toOem )
    fputs( "{\\rtf0\\ansi", ostream );
 else
    fputs( "{\\rtf0\\pc", ostream );
 makeAttribs(1);
 sprintf( par, "\\keep\\par\r\n%s", reg );
 setCrs( par, " \r\n");
 fprintf( ostream, (LPSTR)fmt2, reg, reg, reg );	  // left, width, 
}

char *TextConvDriverRTF::tabSet( char *buf, int *sz )
{
 char lbuf[200], *lbp;
 int l, i;

 if ( pTabs->getCount() )
    strcpy( lbuf, "}{" );
 else
    return( buf );

 lbp = &lbuf[2];
 for ( i = 0; i < pTabs->getCount(); ++i ) {
     if ( pTabs->getFill(i) )
	lbp += sprintf(lbp, "\\tldot" );
     lbp += sprintf(lbp, "\\tx%d", pTabs->getTab(i) * 144 );
     }
 strcat( lbp+1, " " );
 *buf++ = F_BINARY;
 l = strlen(lbuf);
 *buf++ = (unsigned char) l;
 strcpy( buf, lbuf );
 *sz += l + 2;
 return( buf + l );
}

/* Spits out a \\tab where appropriate and adjusts ptrs. */

char *TextConvDriverRTF::tabOut( char *buf, int *col, int *sz )
{
 int tb, tc, l;

 tc = pTabs->getCount();
 tb = pTabs->getTab(pTabs->getCurNo());
 if ( !tc || !tb ) {
    *buf++ = ' ';
    *buf = '\0';
    (*col)++;
    (*sz)++;
    pTabs->nextTab();
    if ( pTabs->getCurNo() >= pTabs->getCount() ) {
       pTabs->resetTab();
       return( buf );
       }
    }
 *buf++ = F_BINARY;
 *buf++ = '\5';
 strcpy( buf, "\\tab " );
 *sz += 6;
 *col = tb;
 pTabs->nextTab();
 if ( pTabs->getCurNo() >= pTabs->getCount() )
    pTabs->resetTab();
 return( buf+5 );
}

void TextConvDriverRTF::finishUpFile()
{
 static char fmt1[] = "\\sect\\page}}\x0d\x0a";
 fputs( fmt1, ostream );
}

void TextConvDriverRTF::finishUpJob()
{
 static char fmt1[] = "\\par}}}\x0d\x0a";
 fputs( fmt1, ostream );
}

void TextConvDriverRTF::makeColorTable(int doTable)
{
 int cnt = 0, i;
 COLORREF reg;
 COLORREF *ptrs[4];

 memcpy(&reg, &colors[0], 4 );
 ptrs[cnt]= &colors[_REG_];
 iColors[_REG_]=0;
 if ( memcmp(&colors[_BOLD_], &reg, 4 ) ) {
    ptrs[cnt]= &colors[_BOLD_];
    cnt++;
	iColors[_BOLD_]=cnt;
    }
 else
    iColors[_BOLD_]=0;
 if ( memcmp(&colors[_HEAD_], &reg, 4 ) ) {			   
    ptrs[cnt]= &colors[_HEAD_];
    cnt++;
    iColors[_HEAD_]=cnt;
    }
 else
    iColors[_HEAD_]=0;
 if ( memcmp(&colors[_UITAL_], &reg, 4 ) ) {
    ptrs[cnt]= &colors[_UITAL_];
    cnt++;
	iColors[_UITAL_]=cnt;
    }
 else
    iColors[_UITAL_]=0;
 if ( doTable ) {
    if ( cnt ) {
       fprintf( ostream, "{\\colortbl;" );
       for ( i = 0; i < cnt; i++ ) {
	   fprintf( ostream, "\\red%d\\green%d\\blue%d;",
	      GetRValue(*ptrs[i]), GetGValue(*ptrs[i]), GetBValue(*ptrs[i]) );
	   }
       fprintf( ostream, "}" );
       }
    }
}

void TextConvDriverRTF::makeFontTable(int doTable)
{
 int cnt = 0, i;
 char regName[50];
 FONT *ptrs[4];

 
 strcpy( regName, fonts[_REG_].lfFaceName );
 ptrs[cnt]= &fonts[_REG_];
 iFonts[_REG_]=0;
 cnt++;
 if ( strcmp( fonts[_BOLD_].lfFaceName, regName ) ) {
    ptrs[cnt]= &fonts[_BOLD_];
    iFonts[_BOLD_]=cnt;
    cnt++;
    }
 else
    iFonts[_BOLD_]=0;
 if ( strcmp( fonts[_HEAD_].lfFaceName, regName ) ) {
    ptrs[cnt]= &fonts[_HEAD_];
    iFonts[_HEAD_]=cnt;
    cnt++;
    }
 else
    iFonts[_HEAD_]=0;
 if ( strcmp( fonts[_UITAL_].lfFaceName, regName ) ) {
    ptrs[cnt]= &fonts[_UITAL_];
    iFonts[_UITAL_]=cnt;
    cnt++;
    }
 else
    iFonts[_UITAL_]=0;
 if ( doTable ) {
    if ( cnt ) {
       fprintf( ostream, "{\\fonttbl{\\f0\\froman Times New Roman;}" );
       for ( i = 0; i < cnt; i++ ) {
	   fprintf( ostream, "{\\f%d\\%s %s;}",
	      i, fntCodetotype(ptrs[i]->lfPitchAndFamily),
	      ptrs[i]->lfFaceName );
	   }
       fprintf( ostream, "}" );
       }
    }
}


void TextConvDriverRTF::makeAttrib(char *buf, int i, FONT *f, int ctr, int sz)
{
 int size;

 if ( i )
    strcpy( buf, "{" );
 else
    *buf = '\0';
 if ( iColors[i] ) {
    sprintf( buf+strlen(buf), "\\cf%d\\cb", iColors[i] );
    }
 else
    sprintf( buf+strlen(buf), "\\cf\\cb" );
 if ( iFonts[i] || i == _REG_ ) {
    sprintf( buf+strlen(buf), "\\f%d", iFonts[i] );
    }
 if ( f->lfItalic ) {
    strcat( buf, "\\i" );
    }
 if ( f->lfUnderline ) {
    strcat( buf, "\\ul" );
    }
 if ( f->lfWeight > FW_NORMAL ) {
    strcat( buf, "\\b" );
    }
 if ( i == _REG_ || i == _HEAD_ ) {
    if ( ctr ) {
       strcat( buf, "\\keepn\\qc" );
       }
    else if (justify && i != _HEAD_ ) {
       strcat( buf, "\\keepn\\qj" );
       }
    else  {
       strcat( buf, "\\keepn\\ql" );
       }
    }
 if ( sz != f->lfHeight ) {
    size = f->lfHeight;
    sprintf( buf+strlen(buf), "\\fs%d", size );
    }
 strcat( buf, " " );
}


void TextConvDriverRTF::makeAttribs(int doTable)
{
 char clr[10];
 int sz;

 makeFontTable(doTable);
 makeColorTable(doTable);
 strcpy( atrb.head_off, RTFHOF );
 strcpy( atrb.bold_off, RTFBOF );
 strcpy( atrb.uscore_off, RTFUOF );
 sz = fonts[_REG_].lfHeight;
 makeAttrib(reg, _REG_, &fonts[_REG_], 0, 0);
 makeAttrib(atrb.head_on, _HEAD_, &fonts[_HEAD_], center, sz);
 makeAttrib(atrb.bold_on, _BOLD_, &fonts[_BOLD_], 0, sz);
 makeAttrib(atrb.uscore_on, _UITAL_, &fonts[_UITAL_], 0, sz);
}

