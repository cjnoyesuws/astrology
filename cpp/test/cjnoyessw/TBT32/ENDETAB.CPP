#include "stdafx.h"
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

char *space_out( int *space_cnt, int col, int *len, char *buf )
{
 int sc;
 char *dst = buf;

 sc = *space_cnt;
 if ( sc > 1 && (col%5==0) ) {
    *dst++ = '\t';
    (*len)++;
    }
 else {
    while ( sc-- ) {
	  *dst++ = ' ';
	  (*len)++;
	  }
    }
 *space_cnt = 0;
 return( dst );
}

/* A Function to put tabs into a buffer where they would be, using
   5 char tab stops. Works on a buffer and returns the new length.
   Also replaces ASTRO {} <> [] coding with $b $u $h notation. */

int entab_buf( const char *buf, char *out, int max_len )
{
 int col = 0, space_cnt = 0, len = 0;
 const char *src = buf;
 char *dst = out;

 while ( *src ) {
       switch( *src ) {
	     case ' ' :
		  space_cnt++;
		  col++;
		  if ( col%5==0 )
		     dst = space_out( &space_cnt, col, &len, dst );
		  break;
	     case '~' :
		  dst = space_out( &space_cnt, col, &len, dst );
		  src++;
		  if ( strchr("^[]{}<>~", *src) != NULL )  {
		     *dst++ = '~';
		     *dst++ = *src;
		     }
		  else
		     *dst++ = *src;
		  col++;
		  len++;
		  break;
	     case '\n':
		  dst = space_out( &space_cnt, col, &len, dst );
		  len++;
		  *dst++ = *src;
		  col = 0;
		  break;
	     default :
		  dst = space_out( &space_cnt, col, &len, dst );
		  *dst++ = *src;
		  len++;
		  col++;
		  break;
	     }
       assert( len < max_len );
       if ( len >= max_len ) {
	  *dst++ = '\0';
	  *dst++ = '\0';
	  return( len );
	  }
       src++;
       }
 if ( *(dst-1) != '\n' )
    *dst++ = '\n';
 *dst++ = '\0';
 *dst++ = '\0';
 return( strlen(out) );
}

/* A Function to replace tabs with spaces, tab stops are at every 5
   characters, also quotes any non ascii character. Note buffer must be
   at least 30% larger than strlen(buffer) to accomodate quoting and
   tabs. Also replaces $b $u $h notation with ASTRO style coding. */


int detab_buf( const char *buffer, int max_len, char *nbuf )
{
 int col = 1, ts, b = 0, u = 0, h = 0;
 int len = strlen( buffer );
 const char *src = buffer;
 char *dst = nbuf;

 len = 0;
 while ( *src ) {
       switch( *src ) {
	     case '\n' :
		  *dst++ = *src;
		  len++;
		  col = 0;
		  break;
	     case '\t' :
		  ts = 5-(col % 5);
		  while ( ts-- ) {
			*dst++ = ' ';
			col++;
			len++;
			}
		  break;
	     default :
		  if ( !isascii( *src ) ) {
		     *dst++ = '~';
		     *dst++ = *src;
		     col++;
		     len++;
		     len++;
		     if ( *(src+1) == ' ' ) {
			*dst++ = '~';
			*dst++ = ' ';
			src++;
			col++;
			len++;
			len++;
			}
		     }
		  else {
		     *dst++ = *src;
		     col++;
		     len++;
		     }
		  break;
	     }
       src++;
       assert( len < max_len );
       }
 if ( *(dst-1) != '\n' )
    *dst++ = '\n';
 *dst++ = '\0';
 *dst++ = '\0';
 len = strlen( nbuf );
 return( len );
}
