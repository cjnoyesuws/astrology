#include "stdafx.h"
#include <stdlib.h>
#include <io.h>
#include <share.h>
#include "attrib.h"
#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "errors.fns"

// Note need new outfunc to map space to 0x80

#pragma pack(1)

static void update_wpcs( unsigned short *wpcs, struct WPI *wpi, int count );
extern void wp5_code_page_update( unsigned short *wpcs );


static char WPFHON[] = "\xf2\2\xf2\xf2\xc\xf2";
static char WPFHOF[] = "\xf3\2\xf3\xf3\xc\xf3";
static char WPFBON[] = "\xf2\xc\xf2";
static char WPFBOF[] = "\xf3\xc\xf3";
static char WPFUON[] = "\xf2\xe\xf2";
static char WPFUOF[] = "\xf3\xe\xf3";



struct WP6header {
       char id[4];
       long ptr;
       char product;
       char type;
       char maj_v;
       char min_v;
       short enc;
       short indptr;
       unsigned char rs1;
       unsigned char rs2;
       short  res;
       long file_size;
       unsigned char ext[488];
       unsigned char two;
       unsigned char rs4;
       short indexno;
       unsigned char res10[10];
       } WP6header;

struct WP6header wph6 = {'\xff','W','P','C', 0x020eL, 1, 10, 2, 1, 0, 0x200, 5, 0, 0, 0L, "", 2, 0, 1, "" };

struct WP6tabset1 {
       unsigned char code;
       unsigned char subc;
       unsigned short length;
       char flg;
       short size_nd;
       char flg_zero;
       short lm_zero;
       char ntab;
       } WP6tabset1;

#define wp6tsndel(nt) (((nt)*3)+4)
#define wp6tssize(nt) (sizeof(struct WP6tabset1)+((nt)*3)+sizeof(struct WP6tabset2))

struct WP6tabset1 wpts1 = {0xd3,4,0,0,0,0,0,0};

// array of below struct size ntab

struct WP6tabsetpos {
       char zero;
       short pos;
       } WP6tabsetpos;

// finish up with below struct

struct WP6tabset2 {
       unsigned short length;
       unsigned char code;
       } WP6tabset2;

struct WP6tabset2 wpts2 = {0,0xd3};

struct WP6tab {
       unsigned char code;
       unsigned char def;
       unsigned short length;
       unsigned char flg;
       unsigned short zero;
       unsigned short elength;
       unsigned char ecode;
       } WP6tab;


struct WP6tab ctrmgn= {0xe0, 64, 10, 0, 0, 10, 0xe0};
struct WP6tab thetab= {0xe0, 16, 10, 0, 0, 10, 0xe0};

struct WP6mrgn {
       unsigned char code;
       unsigned char subc;
       unsigned short size;
       unsigned char flag;
       short two;
       short margin;
       unsigned short elength;
       unsigned char ecode;
       } WP6mrgn;

struct WP6jmode {
       unsigned char code;
       unsigned char subc;
       short size;
       char flag;
       short one;
       char mode;
       short esize;
       char ecode;
       } WP6jmode;


struct WP6jmode thejmode_lft = {0xd3, 5, 11, 0, 1, 0, 11, 0xd3 };
struct WP6jmode thejmode_ful = {0xd3, 5, 11, 0, 1, 1, 11, 0xd3 };
struct WP6jmode thejmode_ctr = {0xd3, 5, 11, 0, 1, 2, 11, 0xd3 };
struct WP6jmode thejmode_rt = {0xd3, 5, 11, 0, 1, 3, 11, 0xd3 };





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

struct fchar  {
       char use;
       char thechar;
       } fchar;

struct fchar foreignc[33] = {-1,-1,1,'å',2,'Å',3,'æ',4,'Æ',5,'ä',6,'Ä',7,'á',8,'à',9,'â',
	10,'ã',11,'Ã',12,'ç',13,'Ç',14,'ë',15,'é',16,'É',17,'è',18,'ê',19,'í',20,'ñ',21,'Ñ',
	22,'ø',23,'Ø',24,'õ',25,'Õ',26,'ö',27,'Ö',28,'ü',29,'Ü',30,'ú',31,'ù',32,'ß' };




void TextConvDriverWP6::HeadOn()
{
 fputs(WPFHON,ostream);
 if (center )
    fwrite(&ctrmgn, sizeof(struct WP6tab), 1, ostream );
}


void TextConvDriverWP6::HeadOff()
{
 fputs(WPFHOF,ostream);
 if ( center ) 
    fputc('\x89',ostream);
    
}


void TextConvDriverWP6::initDriver( FIL_ATTRIB *a )
{

 atrb.head_on = "";
 atrb.head_off = "";
 atrb.bold_on = WPFBON;
 atrb.bold_off = WPFBOF;
 atrb.uscore_on = WPFUON;
 atrb.uscore_off = WPFUOF;
 setCrs("\xcc", "\xcf");
}


int TextConvDriverWP6::foreign( unsigned char c )
{
 int i;
 unsigned char bf[10];

 if ( ansi ) {
    bf[0] = c;
    bf[1] = '\0';
    CharToOemBuff( (char *)bf, (char *)&bf[5], 1 );
    c = bf[5];
    }
 if ( c < ' ' )
    return( c );
 for ( i = 1; i < 32; i++ ) {
     if (foreignc[i].thechar==c) {
        fputc( foreignc[i].use, ostream );
        return( 0 );
        break;
        }
     }
 if ( c >= NCHR + 128 )
    return( c );
 i =  high_chars[c-128];
 if ( i == 0 )
    return( c );
 if (!( i & 0xff00 )) {
    fputc( i & 0xff, ostream );
    return ( 0 );
    }
 if ( fputc( '\xf0', ostream ) == EOF ||
      fputc( i & 0xff, ostream ) == EOF ||
      fputc( i/256, ostream ) == EOF ||
      fputc( '\xf0', ostream ) == EOF )
    return( EOF );
 return( 0 );
}

void TextConvDriverWP6::finishUpJob()
{
 fflush(ostream);
 wph6.file_size = ftell(ostream);
 fseek( ostream, 0L, SEEK_SET );
 fwrite(&wph6,sizeof(struct WP6header),1,ostream);
}



void TextConvDriverWP6::initStringPrint( int left, int width, int version, int code )
{
 FILE *hs;
 char buf[202];
 int e = 1, l;
 static struct WP6mrgn mgx = { 0xd2, 0, 12, 0, 2, 0, 12, 0xd2 };
 struct WP6mrgn mg = mgx;
 
 if ( code == -1 || !code ) {
    if ( access( "ASTRODEF.WP6", 0 ) ) {
       mg.subc = 1;
       fwrite(&wph6, sizeof(struct WP6header), 1, ostream);
       mgx.margin=1200;
       mg.margin=1200;
       fwrite(&mg,sizeof(struct WP6mrgn), 1, ostream );
       fwrite(&mgx,sizeof(struct WP6mrgn), 1, ostream );
       }
    else {
       if ( ( hs = fopen( "ASTRODEF.WP6", "rb" )) == NULL )  {
	      do_error( "ASTRODEF.WP6" );
	      }
       while ( ( l = fread( buf, 1, 200, hs ) ) != 0 )
	      fwrite( buf, 1, l, ostream );
          fclose( hs );
       }
    } 
 margin = "";
 wp5_code_page_update( (unsigned short *)high_chars );
 pTabs->setLeft(10);
 if ( !justify )
    fwrite(&thejmode_lft, sizeof(struct WP6jmode), 1, ostream);
 else
    fwrite(&thejmode_ful, sizeof(struct WP6jmode), 1, ostream);
}


char *TextConvDriverWP6::tabSet( char *buf, int *sz )
{
 struct WP6tabsetpos pos[10];
 int i;

 for ( i = 0; i < pTabs->getCount(); ++i ) {
     pos[i].zero = 0;
     pos[i].pos = (pTabs->getTab(i) + pTabs->getLeft()) * 120;
     }
 *buf++ = F_BINARY;
 *buf++ = (unsigned char) wp6tssize(pTabs->getCount());
 wpts1.length = wp6tssize(pTabs->getCount());
 wpts1.ntab = (char)pTabs->getCount();
 wpts1.size_nd = wp6tsndel(pTabs->getCount());
 memcpy( buf, &wpts1, sizeof(struct WP6tabset1) );
 buf+= sizeof(struct WP6tabset1);
 memcpy( buf, pos, pTabs->getCount()*3  );
 buf+= pTabs->getCount()*3;
 wpts2.length = wp6tssize(pTabs->getCount());
 memcpy( buf, &wpts2, sizeof(struct WP6tabset2) );
 buf+= sizeof(struct WP6tabset2);
 *sz += wp6tssize(pTabs->getCount()) + 2;
 return( buf );
}



/* Spits out a <c0> record where appropriate and adjusts ptrs. */

char *TextConvDriverWP6::tabOut( char *buf, int *col, int *sz )
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
 memcpy( buf, &thetab, sizeof(WP6tab) );
 *sz += sizeof(WP6tab)+2;
 *col = tb;
 pTabs->nextTab();
 if ( pTabs->getCurNo() >= pTabs->getCount() )
       pTabs->resetTab();
 return( buf+sizeof(WP6tab) );
}

#pragma pack()




