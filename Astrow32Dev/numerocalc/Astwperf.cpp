#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <share.h>
#include "attrib.h"
#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"
#include "errors.fns"

#pragma pack(1)
static void update_wpcs( unsigned *wpcs, struct WPI *wpi, int count );
extern void wp5_code_page_update( unsigned *wpcs );

static char WPFintHON[] = "{H";
static char WPFintHOF[] = "}H";
static char WPFintBON[] = "{B";
static char WPFintBOF[] = "}B";
static char WPFintUON[] = "{U";
static char WPFintUOF[] = "}U";

static char WPFCTON[] = "\xc1\xe0<0><0><0><0><0><0>\xc1";
static char WPFCTOFF[] = "\x83";
static char WPFJTON[] = "\x81";
static char WPFJTOFF[] = "\x82";
static char WPFHON[] = "\xc3\2\xc3\xc3\xc\xc3";
static char WPFHOF[] = "\xc4\2\xc4\xc4\xc\xc4";
static char WPFBON[] = "\xc3\xc\xc3";
static char WPFBOF[] = "\xc4\xc\xc4";
static char WPFUON[] = "\xc3\xe\xc3";
static char WPFUOF[] = "\xc4\xe\xc4";



struct WPheader {
       char id[4];
       long ptr;
       char product;
       char type;
       char maj_v;
       char min_v;
       short  key;
       short  res;
       } WPheader;

struct WP5tab {
       unsigned char code;
       unsigned char subc;
       unsigned short length;
       unsigned short opos[40];
       unsigned char otype[20];
       unsigned short npos[40];
       unsigned char ntype[20];
       unsigned short elength;
       unsigned char esubc;
       unsigned char ecode;
       } WP5tab;

struct WP5mrgn {
       unsigned char code;
       unsigned char subc;
       unsigned short length;
       short oleft;
       short oright;
       short left;
       short right;
       unsigned short elength;
       unsigned char esubc;
       unsigned char ecode;
       } WP5mrgn;

struct WPheader wph = {'\xff','W','P','C', 76L, 1, 10, 0, 0, 0, 0 };
unsigned char ext_data[60] = { 0xfb, 0xff, 5, 0, 0x32, 0, 0, 0,
	0, 0, 6, 0, 8, 0, 0, 0, 0x42, 0, 0, 0, 8, 0, 2, 0, 0, 0, 0x4a,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 8, 0, 0x7c, 0, 0x78, 0, 0, 0, 0, 0 };

#define c(s,c) ((s*256)+(c))

#define NCHR (sizeof(high_chars)/sizeof(short))

static unsigned short high_chars[] = {
  c(1,28), c(1,61), c(1,41), c(1,29), c(1,31), c(1,33), c(1,35),
  c(1,29), c(1,43), c(1,44), c(1,47), c(1,53), c(1,53), c(1,55),
  c(1,30), c(1,34), c(1,40), c(1,37), c(1,36), c(1,61), c(1,63),
  c(1,64), c(1,68), c(1,72), c(1,74), c(1,63), c(1,70), c(4,19),
  c(4,10), c(4,11), c(1,12), c(1,13), c(1,27), c(1,49), c(1,59),
  c(1,67), c(1,57), c(1,56), 0,       0,       c(4,8),  c(3,10),
  c(3,11), c(4,17), c(4,18), c(4,7),  c(4,9),  c(4,10), c(3,0),
  c(3,1),  c(3,2),  0,       c(3,9),  c(3,16), c(3,40), c(3,44),
  c(3,35), c(3,11), c(3,13), c(3,17), c(3,15), c(3,14), c(3,8),
  c(3,18), c(3,38), c(3,42), c(3,24), c(3,21), c(3,28), c(3,26),
  c(3,25), c(3,19), c(3,29), c(3,45), c(3,41), c(3,43), c(3,39),
  c(3,37), c(3,33), c(3,30), c(3,34), c(3,46), c(3,47), c(3,12),
  c(3,10), c(3,3),  c(3,7),  c(3,4),  c(3,6),  c(3,5) };



void TextConvDriverWPint::initDriver( FIL_ATTRIB *a )
{
 strcpy( atrb.head_on, WPFintHON );
 strcpy( atrb.head_off, WPFintHOF );
 strcpy( atrb.bold_on, WPFintBON );
 strcpy( atrb.bold_off, WPFintBOF );
 strcpy( atrb.uscore_on, WPFintUON );
 strcpy( atrb.uscore_off, WPFintUOF );
 setCrs("\n", " ");
}

void TextConvDriverWPint::finishUpJob()
{
 fflush(ostream);
}





void TextConvDriverWP5::initDriver( FIL_ATTRIB *a )
{
 atrb.head_on[0] = '\0';
 atrb.head_off[0] = '\0';
 if ( justify )
    strcat( atrb.head_on, WPFJTOFF );
 if ( center ) {
    strcat( atrb.head_on, WPFCTON );
    strcat( atrb.head_off, WPFCTOFF );
    }
 strcat( atrb.head_on, WPFHON );
 strcat( atrb.head_off, WPFHOF );
 if ( justify )
    strcat( atrb.head_off, WPFJTON );
 strcpy( atrb.bold_on, WPFBON );
 strcpy( atrb.bold_off, WPFBOF );
 strcpy( atrb.uscore_on, WPFUON );
 strcpy( atrb.uscore_off, WPFUOF );
 setCrs("\n", "\r");
}



int TextConvDriverWP5::foreign( unsigned char c )
{
 int i;
 unsigned char bf[10];

 if ( ansi ) {
    bf[0] = c;
    bf[1] = '\0';
    AnsiToOemBuff( (char *)bf, (char *)&bf[5], 1 );
    c = bf[5];
    }
 if ( c < ' ' )
    return( c );
 if ( c >= NCHR + 128 )
    return( c );
 i =  high_chars[c-128];
 if ( i == 0 )
    return( c );
 if (!( i & 0xff00 )) {
    fputc( i & 0xff, ostream );
    return ( 0 );
    }
 if ( fputc( '\xc0', ostream ) == EOF ||
      fputc( i & 0xff, ostream ) == EOF ||
      fputc( i/256, ostream ) == EOF ||
      fputc( '\xc0', ostream ) == EOF )
    return( EOF );
 return( 0 );
}



int TextConvDriverWPint::foreign( unsigned char c )
{
 char bf[10];

 if ( ansi ) {
    AnsiToOemBuff( bf, &bf[5], 1 );
    c = bf[5];
    }
 fputc( c, ostream );
 return( 0 );
}

void TextConvDriverWP5::initStringPrint( int left, int width )
{
 FILE *hs;
 char buf[202];
 int e = 1, l;
 static struct WP5mrgn mgx = { 0xd0, 1, 12, 0, 0, 0, 0, 12, 1, 0xd0 };
 struct WP5mrgn mg = mgx;
 
 if ( access( "ASTRODEF.WP5", 0 ) ) {
    fwrite(&wph, sizeof(struct WPheader), 1, ostream);
    fwrite( &ext_data, 60, 1, ostream );
    mg.left=1200;
    mg.right = 100*12;
    fwrite(&mg,sizeof(struct WP5mrgn), 1, ostream );
    }
 else {
    if ( ( hs = fopen( "ASTRODEF.WP5", "rb")) == NULL )  {
	   do_error( "ASTRODEF.WP5" );
	   }
    while ( ( l = fread( buf, 1, 200, hs ) ) != 0 )
	   fwrite( buf, 1, l, ostream );
       fclose( hs );
    }
 margin = "";
 wp5_code_page_update( (unsigned *)high_chars );
 pTabs->setLeft(left/10);
 if ( !justify )
    fputs(WPFJTOFF, ostream);
 else
    fputs(WPFJTON, ostream);
}




char *TextConvDriverWP5::tabSet( char *buf, int *sz )
{
 struct WP5tab tb;
 unsigned char bit;
 int i, l;

 memset( &tb, 0xff, sizeof( WP5tab ) );
 tb.code = 0xd0;
 tb.subc = 4;
 tb.length = 204;
 tb.ecode = 0xd0;
 tb.esubc = 4;
 tb.elength = 204;
 memset( tb.otype, 0, 20 );
 memset( tb.ntype, 0, 20 );
 for ( i = 0; i < pTabs->getCount(); ++i ) {
     tb.npos[i] = (pTabs->getTab(i) + pTabs->getLeft()) * 120;
     if ( pTabs->getFill(i) ) {
	if ( i % 2 )
	   tb.ntype[i] |= 2;
	else
	   tb.ntype[i] |= 32;
	}
     };
 *buf++ = F_BINARY;
 *buf++ = (unsigned char)sizeof(WP5tab);
 l = sizeof(WP5tab);
 memcpy ( buf, &tb, l );
 *sz += l + 2;
 return( buf + l );
}

void TextConvDriverWPint::initStringPrint( int left, int width )
{
margin = ""; 
fwrite( fonts, 4, sizeof(FONT), ostream );
fwrite( colors, 4, sizeof(COLORREF), ostream );
}

char *TextConvDriverWPint::tabSet( char *buf, int *sz )
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

/* Spits out a <c0> record where appropriate and adjusts ptrs. */

char *TextConvDriverWP5::tabOut( char *buf, int *col, int *sz )
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
 *buf++ = F_BINARY;
 *buf++ = '\x9';
 memset( tx, 0, 9 );

 
 tx[0] = '\xc1';
 tx[8] = '\xc1';
 memcpy( buf, tx, 9 );
 *sz += 11;
 *col = tb;
 pTabs->nextTab();
 if ( pTabs->getCurNo() >= pTabs->getCount() )
       pTabs->resetTab();
 return( buf+9 );
}

char *TextConvDriverWPint::tabOut( char *buf, int *col, int *sz )
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