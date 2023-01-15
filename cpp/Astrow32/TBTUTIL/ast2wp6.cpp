#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")
#include <ctype.h>

#pragma pack(1)
// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static char WPFHON[] = "\xf2\2\xf2\xf2\xc\xf2";
static char WPFHOF[] = "\xf3\2\xf3\xf3\xc\xf3";
static char WPFBON[] = "\xf2\xc\xf2";
static char WPFBOF[] = "\xf3\xc\xf3";
static char WPFUON[] = "\xf2\xe\xf2";
static char WPFUOF[] = "\xf3\xe\xf3";



typedef struct WP6header {
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

static WP6header wph6 = {'\xff','W','P','C', 0x020eL, 1, 10, 2, 1, 0, 0x200, 5, 0, 0, 0L, "", 2, 0, 1, "" };

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

typedef struct fchar  {
       char use;
       char thechar;
       } fchar;

static fchar foreignc[33] = {-1,-1,1,'å',2,'Å',3,'æ',4,'Æ',5,'ä',6,'Ä',7,'á',8,'à',9,'â',
	10,'ã',11,'Ã',12,'ç',13,'Ç',14,'ë',15,'é',16,'É',17,'è',18,'ê',19,'í',20,'ñ',21,'Ñ',
	22,'ø',23,'Ø',24,'õ',25,'Õ',26,'ö',27,'Ö',28,'ü',29,'Ü',30,'ú',31,'ù',32,'ß' };


extern void setcrs( unsigned char scr, unsigned char hcr );
extern int text_wrap( char *string, int width );
static char *tbuf;
extern void wp5_code_page_update( unsigned short *wpcs );


#pragma pack()


static int wordperf6_foreign( FILE *stream, unsigned char c )
{
 int i;

 if ( c < ' ' )
    return( c );
 for ( i = 1; i < 32; i++ ) {
     if (foreignc[i].thechar==c) {
        fputc( foreignc[i].use, stream );
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
    fputc( i & 0xff, stream );
    return ( 0 );
    }
 if ( fputc( '\xf0', stream ) == EOF ||
      fputc( i & 0xff, stream ) == EOF ||
      fputc( i/256, stream ) == EOF ||
      fputc( '\xf0', stream ) == EOF )
    return( EOF );
 return( 0 );
}




static int write_word_perf_header(FILE *stream)
{
 int e;
 static struct WP6mrgn mgx = { 0xd2, 0, 12, 0, 2, 0, 12, 0xd2 };
 struct WP6mrgn mg = mgx;
 
 e = fwrite( &wph6, sizeof( struct WP6header ), 1, stream );
 if ( e ) {
    mg.subc = 1;
    mgx.margin=1200;
    mg.margin=1200;
    fwrite(&mg,sizeof(struct WP6mrgn), 1, stream );
    e = fwrite(&mgx,sizeof(struct WP6mrgn), 1, stream );
    }
 return( e );
}


extern "C" {

int __far __pascal __export _AST2WP6( int argc, char *argv[] )
{
 char buf[100], *p, *b;
 FILE *in, *out;
 int c;

 if ( argc < 2 ) {
    alert_box( "AST2WP6", "AST2WP6 INFILE OUTFILE\nConvert ASTRO Text Source file Format to WordPefect 6.x" );
    return( -1 );
    }
 if ( argc < 3 ) {
    strcpy( buf, argv[1] );
    p = strchr( buf, '.' );
    if ( p == NULL )
       strcat( buf, ".DOC" );
    else
       strcpy( p, ".DOC" );
    }
 else
    strcpy( buf, argv[2] );
 if ( ( in = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "AST2WP6", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wb" ) ) == NULL ) {
    alert_box( "AST2WP6", "Can't Open %s for Writing!", buf );
    return( -1 );
    }
 wp5_code_page_update( high_chars );
 if ( setvbuf( in, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( in, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( in, NULL, _IOFBF, 1024 ) )
	  setvbuf( in, NULL, _IOFBF, 256 );
       }
    }
 if ( setvbuf( out, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( out, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( out, NULL, _IOFBF, 1024 ) )
	  setvbuf( out, NULL, _IOFBF, 256 );
       }
    }
 tbuf = new char[10000];
 setcrs( '\xcf', '\xcc' );
 dllYield();
 write_word_perf_header( out );
 while ( ( p = fgets( tbuf, 9998, in ) ) != NULL ) {
       
       doConvertText( tbuf, _SRC_T_, _OEM_T_ );
       dllYield();
       for ( b = p; *b; b++ ) {
	   switch( *b ) {
	      case '\r' :
	      case '\n' :
	       break;
	      case '{' :
		   fwrite( "\xf2\xc\xf2", 1, 3, out );
		   break;
	      case '}' :
		   fwrite( "\xf3\xc\xf3", 1, 3, out );
		   break;
	      case '<' :
		   fwrite( "\xf2\x0e\xf2", 1, 3, out );
		   break;
	      case '>' :
		   fwrite( "\xf3\x0e\xf3", 1, 3, out );
		   break;
	      case ' ' :
	       putc( '\x80', out );
	       break;
	      case '~' :
		   b++;
		   if ( isascii( *b ) )
		      putc( *b, out );
		   else
		      wordperf6_foreign( out, *b );
		   break;
	      default :
		putc( *b, out );
		break;
	      }
	   }
       putc( '\xcc', out );
       }
 fclose( in );
 fflush(out);
 wph6.file_size = ftell(out);
 fseek( out, 0L, SEEK_SET );
 fwrite(&wph6,sizeof(struct WP6header),1,out);
 fclose( out );
 delete tbuf;
 return( 0 );
}

}

#pragma pack()

