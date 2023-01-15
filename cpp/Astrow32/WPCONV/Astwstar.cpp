#include "stdafx.h"
#include "attrib.h"
#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"

/*  necessary routines to do file conversion to wordstar 3.? and 4.? files.
   Actually there are two different conversions which use the same
   core routines. */


#define WS_SOFTCR '\x8d'
#define WSB      "\2"
#define WSU      "\x13"

void TextConvDriverWStar::initDriver( FIL_ATTRIB *a )
{
 atrb.head_on = WSB WSU;
 atrb.head_off = WSU WSB;
 atrb.bold_on = WSB;
 atrb.bold_off = WSB;
 atrb.uscore_on = WSU;
 atrb.uscore_off = WSU;
 setCrs(" \x8d\n","\r\n");
}

int TextConvDriverWStar::foreign( unsigned char the_char )
{
 unsigned char bf[10];

 if ( ansi ) {
    bf[0] = the_char;
    bf[1] = '\0';
    CharToOemBuff( (char  *)bf, (char  *)&bf[5], 1 );
    the_char = bf[5];
    }
 if ( fputc( '\x1b', ostream ) == EOF )
    return( -1 );
 if ( fputc( the_char, ostream ) == EOF )
    return( -1 );
 if ( fputc( '\x1c', ostream ) == EOF )
    return( -1 );
 return( 0 );
}

char *TextConvDriverWStar3::tabSet( char *buf, int *sz )
{
 char lbuf[170], *bp;
 int i, tb;

 strcpy( lbuf, "..\rL" );
 bp = &lbuf[4];
 for ( i = 0, tb = 0; i < pTabs->getTotalWidth(); ++i ) {
     if ( i == pTabs->getTab(tb) && tb < pTabs->getCount() ) {
	*bp++ = '!';
	tb++;
	}
     else
	*bp++ = '-';
     }
 *bp++ = 'R';
 strcpy( bp, hard_crs );
 *buf++ = F_BINARY;
 tb = strlen( lbuf );
 *buf++ = (char)tb;
 strcpy( buf, lbuf );
 *sz += ( tb + 2 );
 return( buf + tb );
}



char *TextConvDriverWStar4::tabSet( char *buf, int *sz )
{
 char lbuf[170], *bp;
 int i, tb;

 strcpy( lbuf, ".RR \rL" );
 bp = &lbuf[6];
 for ( i = 0, tb = 0; i < pTabs->getTotalWidth(); ++i ) {
     if ( i == pTabs->getTab(tb) && tb < pTabs->getCount() ) {
	*bp++ = '!';
	tb++;
	}
     else
	*bp++ = '-';
     }
 *bp++ = 'R';
 strcpy( bp, hard_crs );
 *buf++ = F_BINARY;
 tb = strlen( lbuf );
 *buf++ = (char)tb;
 strcpy( buf, lbuf );
 *sz += ( tb + 2 );
 return( buf + tb );
}


void TextConvDriverWStar::initStringPrint( int left, int width, int version, int code )
{
 int i;

 pSxc->readStyle("WSStyle.STY");
 left /= 10;
 width /= 10;
 pTabs->setLeft( left );
 margin = "";
 if ( !code || code == -1 ) {
    fprintf( ostream, ".PO %d\r\n..\r", left );
    fprintf( ostream, "L----!" );
    for ( i = 6; i < width-1; ++i )
	fputc( '-', ostream );
    fprintf( ostream, "R%s", hard_crs );
    }
}

void TextConvDriverWStar4::initStringPrint( int left, int width, int version, int code )
{
static char fmt1[] = ".MT 6\r\n.MB 6\r\n.PL 66\r\n";

 if ( !code || code == -1 ) {
    fprintf( ostream, (char  *)fmt1 );
    }
 TextConvDriverWStar::initStringPrint( left, width, version, code );
}

void TextConvDriverWStar3::initStringPrint( int left, int width, int version, int code )
{
 static char fmt1[] = ".MT 6\r\n.MB 6\r\n.PL 66\r\n";
 
 if ( !code || code == -1 ) {
    fprintf( ostream, (char  *)fmt1 );
    }
TextConvDriverWStar::initStringPrint( left, width, version, code );
}
