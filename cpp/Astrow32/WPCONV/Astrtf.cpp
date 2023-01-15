#include "stdafx.h"
#include <io.h>
#include <share.h>
#include <stdlib.h>
#include "astro.h"
#include "attrib.h"
#include "output.fns"
#include "errors.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"

static char RTFBON[] = "{\\b ";
static char RTFBOF[] = "}";
static char RTFUON[] = "{\\ul ";
static char RTFUOF[] = "}";
static char RTFCON[] = "{\\qc\\b\\ul ";
static char RTFLON[] = "{\\ql\\b\\ul ";
static char RTFHON[] = "{\\qc\\b\\ul ";
static char RTFHOF[] = "\\par}";
static char GLFTAG[] = "{\\f%d\fs72 %c}";
static char *GLFFONT[] = {"AstGlyphs", "AstPi1", "AstPi1"};
static char slbuf[100];
static char shbuf[100];

char *fntCodetotype( int code )
{
 static char *tps[] = {"fnil", "froman", "fswiss",
    "fmodern", "fscript", "fdecor", "ftech" };
 code /= 16;
 return( tps[code] );
}

void TextConvDriverRTF::mbforeign( char *ptr ) 
{ 
#ifdef _UNICODEVER
  wchar_t wc[2];
  char buf[10];  
  mbtowc(wc,ptr,1);
  sprintf(buf,"\u%d ", (int)wc[0]);
  fputs( buf, ostream ); 
#else
  foreign((unsigned char)*ptr);
#endif
}

int TextConvDriverRTF::foreign( unsigned char c )
{
 char buf[10];
 unsigned char bf[10];

 if ( ansi && toOem ) {
    bf[0] = c;
    bf[1] = '\0';
    CharToOemBuff( (char *)bf, (char *)&bf[5], 1 );
    c = bf[5];
    }
 else if ( !ansi && !toOem ) {
    bf[0] = c;
    bf[1] = '\0';
    OemToCharBuff( (char *)bf, (char *)&bf[5], 1 );
    c = bf[5];
    }
 sprintf( buf, "\\" "\'" "%2x", c );
 return( fputs( buf, ostream ) );
}

void TextConvDriverRTF::initDriver( FIL_ATTRIB *a )
{
 pSxc->readStyle("RTFStyle.STY");
 setCrs("\\par\r\n", " \r\n");
}

void TextConvDriverRTF::initStringPrint( int left, int width, int version, int code )
{
 static char fmt2[] = { "{\\stylesheet {\\s0%s"
     " Normal;}}\r\n{\\s0%s\\margl%d\\margr%d{" };
 static char fmt3[] = { " {\\s0%s{" };
 static char fmt4[] = {  "\\par\r\n" };
 long t;
 FILE *hs;
 char buf[202];
#ifdef _UNICODEVER
 CPINFOEX info;
#endif

 margin = "";
 if ( !code || code == -1 ) {
    if ( access( "ASTRODEF.RTF", 0 ) ) {
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
#ifdef _UNICODEVER
	   GetCPInfoEx(CP_THREAD_ACP,0,&info);
	   fprintf(ostream,"\\ansicpg%d ", info.CodePage );
#endif
	   makeAttribs(1);
       par.Format( "\\par\r\n%s", reg );
       setCrs( (char *)(LPCTSTR)par, " \r\n");
       fprintf( ostream, (char *)fmt2, reg, reg, left, width );
       }
    else {
       if ( ( hs = fopen( "ASTRODEF.RTF", "rt" )) == NULL )  {
	      do_error( "ASTRODEF.RTF" );
	   }
       fgets( slbuf, 99, hs );
       fgets( shbuf, 99, hs );
       while ( fgets( buf, 200, hs ) != NULL )
	     fputs( buf, ostream );
       if ( strlen( shbuf ) )
	      atrb.head_on=shbuf;
       fclose( hs );
       }
    }
 else {
    makeAttribs(0);
    par.Format( "\\par\r\n%s", reg );
    setCrs( (char *)(LPCTSTR)par, " \r\n");
    fprintf( ostream, (char *)fmt3, reg);
    }
}

char *TextConvDriverRTF::tabSet( char *buf, int *sz )
{
 char lbuf[200], *lbp;
 int l, i;

 if ( pTabs->getCount() )
    strcpy( lbuf, "}{" );
 else {
     *buf++ = F_BINARY;
	 *buf++ = 5;
	 strcpy( buf, "\\tab " );
	 buf+= 5;
	 *sz+= 7;
	 return( buf );
 }
 lbp = &lbuf[2];
 for ( i = 0; i < pTabs->getCount(); ++i ) {
     if ( pTabs->getFill(i) )
	lbp += sprintf(lbp, "\\tldot" );
     lbp += sprintf(lbp, "\\tx%d", pTabs->getTab(i) * 144 );
     }
 strcpy( lbp+1, " " );
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
 int tb=0, tc;

 if ( bTableMode == FALSE ) {
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
    else if ( tb <= *col ) {
       pTabs->nextTab();
       if ( pTabs->getCurNo() >= pTabs->getCount() ) {
          pTabs->resetTab();
          return( buf );
          }
       }
 }
 int bufpos = 5;
 if ( bTableMode == TRUE ) {
   *buf++ = F_BINARY;
   *buf++ = '\6';
   strcpy( buf, "\\cell " );
   *sz += 7;
   bufpos++;
 }
 else {
  *buf++ = F_BINARY;
  *buf++ = '\5';
  strcpy( buf, "\\tab " );
  *sz += 6;
 }
 *col = tb;
 pTabs->nextTab();
 if ( pTabs->getCurNo() >= pTabs->getCount() )
    pTabs->resetTab();
 return( buf+bufpos );
}

void TextConvDriverRTF::finishUpFile()
{
 static char fmt1[] = "\\sect\\page}}\x0d\x0a";
 fputs( (char *)fmt1, ostream );
}

void TextConvDriverRTF::finishUpJob()
{
 static char fmt1[] = "\\par}}}\x0d\x0a";
 fputs( (char *)fmt1, ostream );
}

void TextConvDriverRTF::makeColorTable(int doTable)
{
 int cnt = 0, i;
 COLORREF Black = 0L;
 COLORREF crclrs[4];

 if ( getStyles()->getRegColor() != Black ) {
    crclrs[cnt]= getStyles()->getRegColor();
    cnt++;
    colors[_REG_]=cnt;
    }
 else
    colors[_REG_]=0;
 if ( getStyles()->getBoldColor() != Black ) {
    crclrs[cnt]= getStyles()->getBoldColor();
    cnt++;
    colors[_BOLD_]=cnt;
    }
 else
    colors[_BOLD_]=0;
 if ( getStyles()->getHeadColor() != Black ) {
    crclrs[cnt]= getStyles()->getHeadColor();
    cnt++;
    colors[_HEAD_]=cnt;
    }
 else
    colors[_HEAD_]=0;
 if ( getStyles()->getItalColor() != Black ) {
    crclrs[cnt]= getStyles()->getItalColor();
    cnt++;
    colors[_UITAL_]=cnt;
    }
 else
    colors[_UITAL_]=0;
 if ( doTable ) {
    if ( cnt ) {
       fprintf( ostream, "{\\colortbl;" );
       for ( i = 0; i < cnt; i++ ) {
	   fprintf( ostream, "\\red%d\\green%d\\blue%d;",
	      GetRValue(crclrs[i]), GetGValue(crclrs[i]), GetBValue(crclrs[i]) );
	   }
       fprintf( ostream, "}" );
       }
    }
}

void TextConvDriverRTF::makeFontTable(int doTable)
{
 int cnt = 0, i;
 CString regName;
 LPLOGFONT ptrs[4];

 regName = getStyles()->getRegFont()->lfFaceName;
 ptrs[cnt]= getStyles()->getRegFont();
 fonts[_REG_]=cnt;
 if ( getStyles()->getBoldFont()->lfFaceName != regName ) {
    cnt++;
	ptrs[cnt]= getStyles()->getBoldFont();
    fonts[_BOLD_]=cnt;
    }
 else
    fonts[_BOLD_]=0;
 if ( getStyles()->getHeadFont()->lfFaceName != regName ) {
    cnt++;
	ptrs[cnt]= getStyles()->getHeadFont();
    fonts[_HEAD_]=cnt;
    }
 else
    fonts[_HEAD_]=0;
 if ( getStyles()->getItalFont()->lfFaceName != regName ) {
    cnt++;
	ptrs[cnt]= getStyles()->getItalFont();
    fonts[_UITAL_]=cnt;
    }
 else
    fonts[_UITAL_]=0;
 if ( doGlyph )
    fonts[4] = ++cnt;
 cnt++;
 if ( doTable ) {
    if ( cnt ) {
       if ( doGlyph )
		   cnt--;
	   fprintf( ostream, "{\\fonttbl", fntCodetotype((ptrs[0])->lfPitchAndFamily), ptrs[0]->lfFaceName );
       for ( i = 0; i < cnt; i++ ) {
	   fprintf( ostream, "{\\f%d\\%s %s;}",
	      i, fntCodetotype((ptrs[i])->lfPitchAndFamily),
	      ptrs[i]->lfFaceName );
	   }
	   if ( doGlyph )
	      fprintf(ostream, "{\\f%d\\fnil\\fcharset2 %s;}", fonts[4],GLFFONT[glyphFont%3]);
       fprintf( ostream, "}" );
       }
    }
}


void TextConvDriverRTF::makeAttrib(CString &buf, int i, LPLOGFONT f, int ctr, int sz)
{
 CString b;
	
 int size;

 if ( i )
    buf = "{";
 else
    buf = "";
 if ( colors[i] ) {
    b.Format( "\\cf%d", colors[i] );
	buf += b;
    }
 if ( fonts[i] ) {
    b.Format( "\\f%d", fonts[i] );
	buf += b;
	}
 if ( f->lfItalic ) {
    buf +=  "\\i";
    }
 if ( f->lfUnderline ) {
    buf += "\\ul";
    }
 if ( f->lfWeight > FW_NORMAL ) {
    buf += "\\b"; 
    }
 if ( i == _REG_ || i == _HEAD_ ) {
    if ( ctr ) {
       buf += "\\qc";
       }
    else if (justify && i != _HEAD_ ) {
       buf += "\\qj";
       }
    else  {
       buf += "\\ql";
       }
    }
 if ( sz != f->lfHeight ) {
    size = f->lfHeight;
    if ( size < 0 )
       size = -size;
	CDC *dc = new CDC;
	dc->CreateIC("DISPLAY",NULL,NULL,0);
	size *= 72;
    size += (dc->GetDeviceCaps(LOGPIXELSY)/2);
    size /= dc->GetDeviceCaps(LOGPIXELSY);
    delete dc;
    size *= 2;
    b.Format( "\\fs%d", size );
	buf += b;
    }
 buf += " ";
}


void TextConvDriverRTF::makeAttribs(int doTable)
{
 int sz;

 makeFontTable(doTable);
 makeColorTable(doTable);
 atrb.head_off = RTFHOF;
 atrb.bold_off = RTFBOF;
 atrb.uscore_off = RTFUOF;
 sz = ((LPLOGFONT)getStyles()->getRegFont())->lfHeight;
 makeAttrib(reg, _REG_, (LPLOGFONT)getStyles()->getRegFont(), 0, 0);
 makeAttrib(atrb.head_on, _HEAD_, (LPLOGFONT)getStyles()->getHeadFont(), center, sz);
 makeAttrib(atrb.bold_on, _BOLD_, (LPLOGFONT)getStyles()->getBoldFont(), 0, sz);
 makeAttrib(atrb.uscore_on, _UITAL_, (LPLOGFONT)getStyles()->getItalFont(), 0, sz);
}

char *TextConvDriverRTF::TableCode(char *buf, int *sz )
{
	return buf;
	int len = 0, l;
	char *p, *p2;
	if ( bTableMode == TRUE ) {
	   bTableMode = FALSE;
	   p = "\\pard\\par\n";
	   p2 = NULL;
	}
	else {
	   bTableMode = TRUE;
	   p ="\\trowd\\trgaph180\\trleft-180\\trrh294\\trpaddl180\\trpaddr180\\trpaddfl3\\trpaddfr3";
	   p2 ="\\pard\\intbl\\nowidctlpar\\sl240\\slmult1";
	}
 *buf++ = F_BINARY;
 l = strlen(p);
 *buf++ = l;
 len += l + 2;
 strcpy(buf,p);
 buf += l;
 if ( p2 != NULL ) {
    *buf++ = F_BINARY;
    l = strlen(p2);
    *buf++ = l;
    len += l + 2;
    strcpy(buf,p2);
    buf += l;
 }
*sz += len;
return( buf );
}


char * TextConvDriverRTF::TableRow(char *buf, int *sz )
{
 return( buf );
 char *p ="\\row\n\\pard\\intbl\\nowidctlpar\\sl240\\slmult1";
 *buf++ = F_BINARY;
 int l = strlen(p);
 *buf++ = l;
 strcpy(buf,p);
 buf+= l;
 *sz += l + 2;
 return( buf );

}

void TextConvDriverRTF::PlanetGlyph(int n)
{
 static char gst[] = {0x61,0x69,0x59};
 if (!doGlyph)
	 return;
 if ( n==0 || n > SOUTH_NODE )
	 return;
 fprintf(ostream,GLFTAG,fonts[4],(gst[glyphFont]-1+n) );
}

void TextConvDriverRTF::SignGlyph(int n)
{
  static char gst[] = {0x77,0x41,0x4d};
  if (!doGlyph)
	return;
  fprintf(ostream,GLFTAG,fonts[4],(gst[glyphFont]-1+n) );
}