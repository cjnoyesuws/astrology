#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <io.h>
#include "errors.fns"
//#include "report.h"
//#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"

SexCodes::~SexCodes()
{
 if ( buf1 != NULL )
    delete buf1;
 if ( buf2 != NULL )
    delete buf2;
 if ( style_buf != NULL )
    delete style_buf;
}

int SexCodes::output( FILE *stream, int sex, int sexno, int table )
{
 return( 0 );
}

/* Style code File format
int count;      number of chunks
int first;      0 based index
int len[count]  length of each chunk
char data[]     actual chunks
*/

int SexCodes::readStyle( char *name )
{
 return( 1 );
}


char *SexCodes::read( FILE *stream, char *buf, char **ar )
{
 int i = 0;
 char *bp = buf;
 unsigned char c, del = fgetc(stream);

 while ( i < 16 ) {
       ar[i] = bp;
       do {
	  c = fgetc(stream);
	  if ( c == del ) {
	     *bp++= '\0';
	     break;
	     }
	  *bp++ = c;
	  } while ( c != del );
       i++;
       }
 return( buf );
}

char *SexCodes::doACode( int p, int code, char **outbuf, int *sz )
{
 int l;
 char *pt;

 if ( p > 0 ) {
    pt = sex2_ptrs[code];
    }
 else if ( p < 0 ) {
    pt = style_ptrs[code];
    if ( style_buf != NULL && pt != NULL && style_len[code] ) {
       memcpy( *outbuf, pt, style_len[code] );
       *sz += style_len[code];
       *outbuf += style_len[code];
       }
    return( *outbuf );
    }
 else
    pt = sex1_ptrs[code];
 strcpy( *outbuf, pt );
 l = strlen( pt )-1;
 *sz += l;
 *outbuf += l;
 return( *outbuf );
}

char *SexCodes::doCodes( FILE *stream, char **outbuf, int *sz, Tabs *t )
{
 int i;
 static char trn[] = { "\x08\x09\x0b\x0c\x0e\x0f\x10"
       "\x11\x12\x13\x14\x15\x16\x17\x18" };
 char *p;
 unsigned char c;

 c = fgetc(stream);
 c = toupper( c );

 if ( c == '@' )
    return( t->read( stream ) );
 else if ( c > '2' && c <= '9' ) {
   doACode( 0, c - '3', outbuf, sz );
   return( *outbuf );
   }
 else if ( c >= 'A' && c <= 'I' ) {
   doACode( 0, c - 'A' + 7, outbuf, sz );
   return( *outbuf );
   }
 else if ( c >= 'J' && c <= 'Y' ) {
   doACode( 1, c - 'J', outbuf, sz );
   return( *outbuf );
   }
 else if ( c == '1' ) {
    if ( buf1 != NULL )
       delete buf1;
    buf1 = new char[500];
    if ( buf1 == NULL ) {
       do_mem_error( 0 );
       for ( i = 0; i < 17; i++ )
	   sex1_ptrs[i] = nul;
       return( NULL );
       }
    return( read( stream, buf1, sex1_ptrs ) );
    }
 else if ( c == '2' ) {
    if ( buf2 != NULL )
       delete buf2;
    buf2 = new char[500];
    if ( buf2 == NULL ) {
       do_mem_error( 0 );
       for ( i = 0; i < 17; i++ )
	   sex2_ptrs[i] = nul;
       return( NULL );
       }
    return( read( stream, buf2, sex2_ptrs ) );
    }
 else if ( c >= '!' && c <= '/' ) {
   p = *outbuf;          /* style code types */
   *p = trn[c-'!'];
   *outbuf++;
   *sz++;
   return( *outbuf );
   }
 else
   return( *outbuf );
}
