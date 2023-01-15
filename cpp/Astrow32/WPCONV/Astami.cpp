#include "stdafx.h"
#include <io.h>
#include <share.h>
#include <stdlib.h>
#include <time.h>
#include "attrib.h"
#include "output.fns"
#include "errors.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"

static char AMIBON[] = "~<+!~>";
static char AMIBOF[] = "~<-!~>";
static char AMIUON[] = "~<+#~>";
static char AMIUOF[] = "~<-!~>";
static char AMIHON[] = "\n\n~<+B~>~<+!~>";
static char AMIHOF[] = "~<-!~>~<+@~>";
static char AMIJON[] = "~<+C~>";
static char AMILON[] = "~<+@~>";

static char slbuf[100];
static char shbuf[100];

static char *fntCodetotype( char code, char set )
{
 static char buf[5];

 buf[0] = code+0x20;
 buf[1] = '\0';
 if ( set == SYMBOL_CHARSET )
    return( "r" );
 return( buf );
}


int TextConvDriverAmi::foreign( unsigned char c )
{
 unsigned char bf[10];

 if ( ansi && toOem ) {
    bf[0] = c;
    bf[1] = '\0';
    CharToOemBuff( (char  *)bf, (char *)&bf[5], 1 );
    c = bf[5];
    }
 else if ( !ansi && !toOem ) {
    bf[0] = c;
    bf[1] = '\0';
    OemToCharBuff( (char *)bf, (char *)&bf[5], 1 );
    c = bf[5];
    }
 fputc( c, ostream );
 return( 1 );
}

void TextConvDriverAmi::initDriver( FIL_ATTRIB *a )
{
 pSxc->readStyle("AMIStyle.STY");
 setCrs((justify?"\n\n<+C>":"\n\n<+@>"), " \n");
}

void TextConvDriverAmi::initStringPrint( int left, int width, int version, int code )
{
static char head1[] = { "[ver]\n\t4\n[sty]\n\t\n[files]\n[charset]\n\t"
   "82\n\tANSI (Windows, IBM CP 1252)\n[revisions]\n\t0\n[toc]\n\tTOC "
   "1\n\tTOC 2\n\tTOC 3\n\t\n\t\n\t\n\t63\n[prn]\n\t%s\n[lang]\n\t1\n"
   "[desc]\n\tChart Compiled by ASTRO For Windows\n\t\n\t\n\t\n\t\n\t" };
static char head2[] = {
   "%lu\n\t2\n\t%lu\n\t3\n\t2\n\t0\n\t0\n\t0\n\t0\n\tAstrology \n\t\n\t\n"
   "\t\n\t\n\t\n\t0\n[fopts]\n\t4\n\t1\n\t2880\n\t0\n[lnopts]\n\t0\n\t" };
static char head3[] = {
   "Body Text\n\t1\n[docopts]\n\t5\n\t2\n[tag]\n\tTOC 3\n\t2\n\t"
   "[fnt]\n\t\tTimes New Roman\n\t\t240\n\t\t0\n\t\t32768\n\t[algn]\n\t\t"
   "0\n\t\t1\n\t\t0\n\t\t0\n\t\t0\n\t[spc]\n\t\t33\n\t\t273\n\t\t"
   "1\n\t\t0\n\t\t0\n\t\t1\n\t\t100\n\t[brk]\n\t\t4\n\t[line]\n\t\t"
   "8\n\t\t0\n\t\t1\n\t\t0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t"
   "10\n\t\t1\n\t[spec]\n\t\t0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t"
   "1\n\t\t0\n\t\t2\n\t\t0\n\t\t0\n\t[nfmt]\n\t\t272\n\t\t"
   "1\n\t\t2\n\t\t.\n\t\t,\n\t\t$\n\tTOC 3\n\t0\n\t0\n[tag]\n\t"
   "Body Text\n\t3\n\t[fnt]\n\t\tTimes New Roman\n\t\t240\n\t\t0\n\t\t"
   "32768\n\t[algn]\n\t\t0\n\t\t1\n\t\t0\n\t\t0\n\t\t0\n\t"
   "[spc]\n\t\t33\n\t\t273\n\t\t1\n\t\t0\n\t\t0\n\t\t1\n\t\t"
   "100\n\t[brk]\n\t\t4\n\t[line]\n\t\t8\n\t\t0\n\t\t1\n\t\t"
   "0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t10\n\t\t1\n\t[spec]\n\t\t"
   "0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t1\n\t\t0\n\t\t2\n\t\t"
   "0\n\t\t0\n\t[nfmt]\n\t\t272\n\t\t1\n\t\t2\n\t\t.\n\t\t"
   ",\n\t\t$\n\tBody Text\n\t0\n\t0\n[tag]\n\tTOC 1\n\t"
   "4\n\t[fnt]\n\t\tTimes New Roman\n\t\t240\n\t\t0\n\t\t32768\n\t"
   "[algn]\n\t\t0\n\t\t1\n\t\t0\n\t\t0\n\t\t0\n\t[spc]\n\t\t"
   "33\n\t\t273\n\t\t1\n\t\t0\n\t\t0\n\t\t1\n\t\t100\n\t[brk]\n\t\t"
   "4\n\t[line]\n\t\t8\n\t\t0\n\t\t1\n\t\t0\n\t\t1\n\t\t1\n\t\t"
   "1\n\t\t10\n\t\t10\n\t\t1\n\t[spec]\n\t\t0\n\t\t0\n\t\t\n\t\t"
   "0\n\t\t1\n\t\t1\n\t\t0\n\t\t2\n\t\t0\n\t\t0\n\t[nfmt]\n\t\t"
   "272\n\t\t1\n\t\t2\n\t\t.\n\t\t,\n\t\t$\n\tTOC 1\n\t0\n\t"
   "0\n[tag]\n\tTOC 2\n\t5\n\t[fnt]\n\t\tTimes New Roman\n\t\t240\n\t\t"
   "0\n\t\t32768\n\t[algn]\n\t\t0\n\t\t1\n\t\t0\n\t\t0\n\t\t"
   "0\n\t[spc]\n\t\t33\n\t\t273\n\t\t1\n\t\t0\n\t\t0\n\t\t"
   "1\n\t\t100\n\t[brk]\n\t\t4\n\t[line]\n\t\t8\n\t\t0\n\t\t"
   "1\n\t\t0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t10\n\t\t1\n\t"
   "[spec]\n\t\t0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t1\n\t\t"
   "0\n\t\t2\n\t\t0\n\t\t0\n\t[nfmt]\n\t\t272\n\t\t1\n\t\t"
   "2\n\t\t.\n\t\t,\n\t\t$\n\tTOC 2\n\t0\n\t0\n[tag]\n\t"
   "Body Text\n\t6\n\t[fnt]\n\t\tTimes New Roman\n\t\t240\n\t\t0\n\t\t"
   "49152\n\t[algn]\n\t\t1\n\t\t1\n\t\t0\n\t\t0\n\t\t0\n\t"
   "[spc]\n\t\t17\n\t\t0\n\t\t1\n\t\t0\n\t\t0\n\t\t1\n\t\t"
   "100\n\t[brk]\n\t\t4\n\t[line]\n\t\t8\n\t\t0\n\t\t1\n\t\t"
   "0\n\t\t1\n\t\t1\n\t\t1\n\t\t10\n\t\t10\n\t\t1\n\t[spec]\n\t\t"
   "0\n\t\t0\n\t\t\n\t\t0\n\t\t1\n\t\t1\n\t\t0\n\t\t0\n\t\t"
   "0\n\t\t0\n\t[nfmt]\n\t\t280\n\t\t1\n\t\t2\n\t\t.\n\t\t"
   ",\n\t\t$\n\tBody Text\n\t0\n\t0\n[lay]\n\tStandard\n\t" };
static char head4[] = {
   "513\n\t[rght]\n\t\t15840\n\t\t12240\n\t\t1\n\t\t%d\n\t\t"
   "1440\n\t\t1\n\t\t1440\n\t\t%d\n\t\t2\n\t\t1\n\t\t0\n\t\t"
   "1\n\t\t0\n\t\t2\n\t\t1\n\t\t%d\n\t\t%d\n\t\t10\n\t\t1\n\t\t"
   "720\n\t\t1\n\t\t1440\n\t\t1\n\t\t2160\n\t\t1\n\t\t2880\n\t\t"
   "1\n\t\t3600\n\t\t1\n\t\t4320\n\t\t1\n\t\t5040\n\t\t1\n\t\t"
   "5760\n\t\t1\n\t\t6480\n\t\t1\n\t\t7200\n\t[hrght]\n\t"
   "[lyfrm]\n\t\t1\n\t\t11200\n\t\t0\n\t\t0\n\t\t12240\n\t\t"
   "1440\n\t\t0\n\t\t1\n\t\t3\n\t\t1 0 0 0 0 0 0\n\t\t0\n\t\t"
   "0\n\t\t1\n\t[frmlay]\n\t\t1440\n\t\t12240\n\t\t1\n\t\t"
   "%d\n\t\t72\n\t\t1\n\t\t360\n\t\t%d\n\t\t0\n\t\t1\n\t\t"
   "0\n\t\t1\n\t\t1\n\t\t0\n\t\t1\n\t\t%d\n\t\t%d\n\t\t0\n\t" };

static char head5[] = {
   "[txt]\n>\n\t[frght]\n\t[lyfrm]\n\t\t1\n\t\t13248\n\t\t"
   "0\n\t\t14400\n\t\t12240\n\t\t15840\n\t\t0\n\t\t1\n\t\t"
   "3\n\t\t1 0 0 0 0 0 0\n\t\t0\n\t\t0\n\t\t2\n\t[frmlay]\n\t\t"
   "15840\n\t\t12240\n\t\t1\n\t\t%d\n\t\t360\n\t\t1\n\t\t"
   "14472\n\t\t%d\n\t\t0\n\t\t1\n\t\t0\n\t\t1\n\t\t1\n\t\t"
   "0\n\t\t1\n\t\t%d\n\t\t%d\n\t\t0\n\t[txt]\n>\n[elay]\n"
   "[l1]\n\t0\n[edoc]\n\x0\x0" };
 long t;
 int wdt, sp, rt;
 FILE *hs;
 char buf[200];

 sp = getStyles()->getRegFont()->lfHeight;
 if ( sp < 0 )
    sp = -sp;
 CDC *dc = new CDC;
 dc->CreateIC("DISPLAY",NULL,NULL,0);
 sp *= 72;
 sp += (dc->GetDeviceCaps(LOGPIXELSY)/2);
 sp /= dc->GetDeviceCaps(LOGPIXELSY);
 delete dc;
 sp *= 22;
 margin = "";
 if ( !code || code == -1 ) {
    if ( access( "ASTRODEF.AMI", 0 ) ) {
	   CPrintDialog pd(FALSE);
	   pd.CreatePrinterDC();
	   fprintf( ostream, head1, (LPCTSTR)pd.GetDeviceName() );
       time_t tm;
       tm = time(&tm);
       fprintf( ostream, (char *)head2, tm, tm );
       fputs( (char *)head3, ostream );
       wdt = width;
       if ( width+left > 850 )
	  rt = 100;
       else
	  rt = 850 - (width+left);
       t = rt;
       t *= 144L;
       rt = t / 10L;
       t = left;
       t *= 144L;
       left = t / 10L;
       t = wdt;
       t *= 144L;
       wdt = t / 10L;
       fprintf( ostream, (char *)head4, left, rt, left, wdt+left,
	    left, rt, left, wdt+left );
       fprintf( ostream, (char *)head5, left, rt, left, wdt+left );
       makeAttribs();
       par.Format( "\n\n<+%c><:#%d,%d>", (justify?'C':'@'), sp, wdt );
       setCrs( (char *)(LPCTSTR)par, " \n");
       fprintf( ostream, par );
       fprintf( ostream, reg );
       }
    else {
       if ( ( hs = fopen( "ASTRODEF.AMI", "rt" )) == NULL )  {
	  do_error( "ASTRODEF.AMI" );
	  }
       while ( fgets( buf, 199, hs ) != NULL )
	     fputs( buf, ostream );
       fclose( hs );
       }
    }
 else {
    wdt = width;
    t = wdt;
    t *= 144L;
    wdt = t / 10L;
    makeAttribs();
    par.Format( "\n\n<+%c><:#%d,%d>", (justify?'C':'@'), sp, wdt );
    setCrs( (char *)(LPCTSTR)par, " \n");
    fprintf( ostream, par );
    fprintf( ostream, reg );
    }
}

char *TextConvDriverAmi::tabSet( char *buf, int *sz )
{
 char lbuf[200], bf[15], *lbp;
 int i;

 if ( pTabs->getCount() )
    strcpy( lbuf, "<:R1," );
 else
    return( buf );
 lbp = &lbuf[5];
 sprintf( bf, "%d,", pTabs->getCount() );
 strcat( lbuf, bf );
 lbp = lbuf + strlen( lbuf );
 for ( i = 0; i < pTabs->getCount(); ++i ) {
     lbp += sprintf(lbp, "1,%d,", pTabs->getTab(i) * 144 );
     }
 strcat( lbp, ">" );
 strcpy( tabs, lbuf );
 if ( ( lbp = strstr( par, "<:R1" ) ) != NULL )
    strcpy( lbp, tabs );
 else
    par += tabs;
 setCrs( (char *)(LPCTSTR)par, " \n");
 return( buf );
}

/* Spits out a \\tab where appropriate and adjusts ptrs. */

char *TextConvDriverAmi::tabOut( char *buf, int *col, int *sz )
{
 int tb, tc;

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
 *buf++ = F_BINARY;
 *buf++ = '\1';
 strcpy( buf, "\t" );
 *sz += 6;
 *col = tb;
 pTabs->nextTab();
 if ( pTabs->getCurNo() >= pTabs->getCount() )
    pTabs->resetTab();
 return( buf+1 );
}

void TextConvDriverAmi::finishUpFile()
{
 fputs( "\n\n<:p>\n", ostream );
}

void TextConvDriverAmi::finishUpJob()
{
 fputs( "\n\n>\n\n", ostream );
}


void TextConvDriverAmi::makeAttrib(CString &buf, int i, LPLOGFONT f, int ctr,
							   int sz, COLORREF &c)
{
CString b; 
int size;

 if ( i == _HEAD_ )
    buf = "\n\n";
 if ( i == _REG_ ) {
    if ( f->lfItalic )
       buf += "<+\">";
    if ( f->lfUnderline )
       buf += "<+#>";
    if ( f->lfWeight > FW_NORMAL )
       buf += "<+!>";
    }
 else {
    if ( ctr )
       buf += "~<+B~>";
    else if ( i == _HEAD_ )
       buf += "~<+@~>";
    if ( f->lfItalic )
       buf += "~<+\"~>";
    if ( f->lfUnderline )
       buf += "~<+#~>"; 
    if ( f->lfWeight > FW_NORMAL )
       buf += "~<+!~>";
   }
 size = f->lfHeight;
 if ( size < 0 )
    size = -size;
// fix this 
 CDC *dc = new CDC;
 dc->CreateIC("DISPLAY",NULL,NULL,0);
 size *= 72;
 size += (dc->GetDeviceCaps(LOGPIXELSY)/2);
 size /= dc->GetDeviceCaps(LOGPIXELSY);
 delete dc;
 size *= 20;
 if ( i == _REG_ ) {
    b.Format( "<:f%d,%s%s,%d,%d,%d>", size,
	fntCodetotype(f->lfPitchAndFamily, f->lfCharSet), f->lfFaceName,
	(int)GetRValue(c), (int)GetGValue(c), (int)GetBValue(c) );
    buf += b;
    }
 else {
    b.Format( "~<:f%d,%s%s,%d,%d,%d~>", size,
	fntCodetotype(f->lfPitchAndFamily, f->lfCharSet), f->lfFaceName,
	(int)GetRValue(c), (int)GetGValue(c), (int)GetBValue(c) );
    buf += b;
    }
}

void TextConvDriverAmi::makeAttribOff(CString &buf, int i, LPLOGFONT f,
				  int ctr, int sz, LPLOGFONT o, COLORREF &c )
{
CString b; 
int size;

 if ( f->lfItalic ) {
    buf +=  "~<-\"~>";
    }
 if ( f->lfUnderline ) {
    buf += "~<-#~>";
    }
 if ( f->lfWeight > FW_NORMAL ) {
    buf += "~<-!~>";
    }
 size = o->lfHeight;
 if ( size < 0 )
    size = -size;
// fix this 
 CDC *dc = new CDC;
 dc->CreateIC("DISPLAY",NULL,NULL,0);
 size *= 72;
 size += (dc->GetDeviceCaps(LOGPIXELSY)/2);
 size /= dc->GetDeviceCaps(LOGPIXELSY);
 delete dc;
 size *= 20;
 b.Format( "~<:f%d,%s%s,%d,%d,%d~>", size,
	fntCodetotype(f->lfPitchAndFamily, f->lfCharSet), f->lfFaceName,
	(int)GetRValue(c), (int)GetGValue(c), (int)GetBValue(c) );
 buf += b;
 if ( ctr )
    buf += "~<+@~>";
}


void TextConvDriverAmi::makeAttribs()
{
 int sz;

 sz = (getStyles()->getRegFont())->lfHeight;
 makeAttrib(reg, _REG_, getStyles()->getRegFont(), 0, 0, getStyles()->getRegColor());
 makeAttrib(atrb.head_on, _HEAD_, getStyles()->getHeadFont(),
      center, sz, getStyles()->getHeadColor());
 makeAttrib(atrb.bold_on, _BOLD_, getStyles()->getBoldFont(), 0, sz,
      getStyles()->getBoldColor());
 makeAttrib(atrb.uscore_on, _UITAL_, getStyles()->getItalFont(), 0, sz,
      getStyles()->getItalColor());
 makeAttribOff(atrb.head_off, _HEAD_, getStyles()->getHeadFont(),
      center, sz, getStyles()->getRegFont(), getStyles()->getRegColor() );
 makeAttribOff(atrb.bold_off, _BOLD_, getStyles()->getBoldFont(),
      0, sz, getStyles()->getRegFont(), getStyles()->getRegColor() );
 makeAttribOff(atrb.uscore_off, _UITAL_, getStyles()->getItalFont(),
      0, sz, getStyles()->getRegFont(), getStyles()->getRegColor() );
}

