#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <io.h>
#include <share.h>
#include "attrib.h"
#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "asfrmdlg.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "errors.fns"

#pragma pack(1)
static char WPFintHON[] = "{H";
static char WPFintHOF[] = "}H";
static char WPFintBON[] = "{B";
static char WPFintBOF[] = "}B";
static char WPFintUON[] = "{U";
static char WPFintUOF[] = "}U";

void TextConvDriverWPi::initDriver( FIL_ATTRIB *a )
{
 strcpy( atrb.head_on, WPFintHON );
 strcpy( atrb.head_off, WPFintHOF );
 strcpy( atrb.bold_on, WPFintBON );
 strcpy( atrb.bold_off, WPFintBOF );
 strcpy( atrb.uscore_on, WPFintUON );
 strcpy( atrb.uscore_off, WPFintUOF );
 setCrs("\n", " ");
}

void TextConvDriverWPi::finishUpJob()
{
 fflush(ostream);
}

void TextConvDriverWPi::finishUpFile()
{
 fflush(ostream);
}


int TextConvDriverWPi::foreign( unsigned char c )
{
 char bf[10];

 if ( ansi ) {
    AnsiToOemBuff( bf, &bf[5], 1 );
    c = bf[5];
    }
 fputc( c, ostream );
 return( 0 );
}


void TextConvDriverWPi::cvtFontSize(FONT &f)
{
 int size = f.lfHeight;
 if ( size < 0 )
 size = -size;
 zSystemInfo *si = new zSystemInfo();
 size *= 72;
 size += (si->pixPerInchY()/2);
 size /= si->pixPerInchY();
 delete si;
 f.lfHeight = size;
}

void TextConvDriverWPi::cvtFont(FONT &f, zFontSpec &fs)
{
 strcpy(f.lfFaceName,fs.faceName());
 f.lfItalic=((LPLOGFONT)(fs))->lfItalic;
 f.lfHeight=((LPLOGFONT)(fs))->lfHeight;
 cvtFontSize(f);
 f.lfWeight=((LPLOGFONT)(fs))->lfWeight;
 f.lfUnderline=((LPLOGFONT)(fs))->lfUnderline;
}

void TextConvDriverWPi::cvtFonts()
{
 colors[_REG_] = (COLORREF)getStyles()->getRegColor();
 colors[_BOLD_] = (COLORREF)getStyles()->getBoldColor();
 colors[_HEAD_] = (COLORREF)getStyles()->getHeadColor();
 colors[_UITAL_] = (COLORREF)getStyles()->getItalColor();
 cvtFont(fonts[_REG_],  *getStyles()->getRegFont() );
 cvtFont(fonts[_BOLD_], *getStyles()->getBoldFont() );
 cvtFont(fonts[_HEAD_], *getStyles()->getHeadFont() ); 
 cvtFont(fonts[_UITAL_], *getStyles()->getItalFont() );
}


void TextConvDriverWPi::initStringPrint( int left, int width, int version, int code  )
{
 cvtFonts();
 margin = ""; 
 if ( code == -1 || !code ) {   		
    fwrite( fonts, 4, sizeof(FONT), ostream );
    fwrite( colors, 4, sizeof(COLORREF), ostream );
    }
}

char *TextConvDriverWPi::tabSet( char *buf, int *sz )
{
 char lbuf[45];
 int i, by, bit;

 memset( lbuf, 0, 40 );
 for ( i = 0; i < pTabs->getCount(); i+=2 ) {
     lbuf[i] = pTabs->getTab(i) + pTabs->getLeft();
     }
 *buf++ = '{';
 *buf++ = 'S';
 *buf++ = F_BINARY;
 *buf++ = (unsigned char) (pTabs->getCount())*2;
 *buf++ = (unsigned char) (pTabs->getCount());
 memcpy(buf,lbuf,(pTabs->getCount())*2);
 *sz += (pTabs->getCount()*2)+2;
 return( buf + (pTabs->getCount()*2) );
}


char *TextConvDriverWPi::tabOut( char *buf, int *col, int *sz )
{
 unsigned char tx[9];
 int tb, tc, l;

 tc = pTabs->getCount();
 tb = pTabs->getTab(pTabs->getCurNo());
 if ( !tc || !tb ) {
    *buf++ = ' ';
    *buf = '\0';
    (*col)++;
    (*sz)++;
    pTabs->nextTab();
    if ( pTabs->getCurNo() >= pTabs->getCount() )
       pTabs->resetTab();
    return( buf );
    }
 else if ( tb <= *col ) {
    pTabs->nextTab();
    if ( pTabs->getCurNo() >= pTabs->getCount() ) {
       pTabs->resetTab();
       return( buf );
       }
    }
 *buf++ = '{';
 *buf++ = 'T';
 *sz += 2;
 *col = tb;
 pTabs->nextTab();
 if ( pTabs->getCurNo() >= pTabs->getCount() )
       pTabs->resetTab();
 return( buf );
}

#pragma pack()