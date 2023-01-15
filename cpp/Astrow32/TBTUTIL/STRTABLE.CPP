#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include "strtab.h"


char *ibuf;
char *obuf;

int accent = 0;
CHREP char_table[256];
STR_TAB string_table[205];
int string_table_count;
static int in_len;
/*
int translate_string_chrs( char *rbuf, char *tbuf );

int load_string_table( char *fil )
{
 static char rbuf[100];
 static char tbuf[100];
 static char srbuf[100];
 static char stbuf[100];
 int num, last = 0, dummy;
 char *sptr;
 char *rptr;
 FILE *stream;

 if ( ( stream = fopen( fil, "rt" ) ) == NULL ) {
    alert_box( "RTFTOAST", "Can't find table %s!", fil );
    return( 1 );
    }
 while ( !feof( stream ) && !ferror( stream ) ) {
       fscanf( stream, "%d|%99[^\n]", &num, srbuf );
       fgetc( stream );
       fscanf( stream, "%99[^\n]", rbuf );
       fgetc( stream );
       translate_string_chrs( rbuf, tbuf );
       translate_string_chrs( srbuf, stbuf );
       num--;
       if ( !strlen(stbuf) )
	  continue;
       if ( num > 200 ) {
	  alert_box( "RTFTOAST","Member %d of file %s Exceeds 200 for table!", num, fil );
	  return( 2 );
	  }
       if ( strlen( tbuf ) > 59 ) {
	  alert_box( "RTFTOAST","Translation string %d of file %s is too long max is 59!", num, fil );
	  return( 2 );
	  }
       if ( strlen( stbuf ) > 59 ) {
	  alert_box( "RTFTOAST","Search string %d of file %s is too long max is 59!", num, fil );
	  return( 2 );
	  }
       strcpy( string_table[num].search, stbuf );
       string_table[num].slen = strlen( stbuf );
       strcpy( string_table[num].replace, tbuf );
       string_table[num].rlen = strlen( tbuf );
       if ( num > last )
	  last = num;
       }
 if ( last > string_table_count )
    string_table_count = last;
 fclose( stream );
 return( 0 );
}

int load_char_table( char *fil )
{
 static char rbuf[52];
 static char tbuf[52];
 int num, l;
 char *ptr;
 FILE *stream;

 if ( ( stream = fopen( fil, "rt" ) ) == NULL ) {
    alert_box( "RTFTOAST", "Can't find table %s!", fil );
    return( 1 );
    }
 while ( !feof( stream ) && !ferror( stream ) ) {
       fscanf( stream, "%d|%50[^\n]", &num, rbuf );
       fgetc(stream);
       translate_string_chrs( rbuf, tbuf );
       if ( num > 256 ) {
	  alert_box( "RTFTOAST","Member %d of file %s Exceeds 256!", num, fil );
	  return( 2 );
	  }
       if (( l = strlen( tbuf ) ) > 9 ) {
	  alert_box( "RTFTOAST", "Translation for char %d too long max is 9!", num );
	  return( 3 );
	  }
       else {
	  strcpy( char_table[num].ch, tbuf );
	  char_table[num].len = l;
	  }
       }
 fclose( stream );
 return( 0 );
}

int init_default_char_table( void )
{
 int i;
 char buf[25];
 char *ptr;

 for ( i = 0; i < 255; ++i ) {
     char_table[i].ch[0] = i;
     char_table[i].ch[1] = '\0';
     char_table[i].len = 1;
     }
}

int _cdecl string_table_cmp( void *x1, void *x2 )
{
 STR_TAB *s1 = ((struct STR_TAB *)x1),
 *s2 = ((struct STR_TAB *)x2);

 return( (int)s2->slen - s1->slen );
}

void sort_string_table(void)
{
 qsort( string_table, string_table_count, sizeof( STR_TAB ), string_table_cmp );
}
*/

int char_replace_string( char *ins, char *outs)
{
 char *o = outs, *i = ins;
 int l = 0, len = 0;
 CHREP *r;

 while ( *i ) {
       r = &char_table[ (unsigned char) *i++];
       if ( r->len == 1 ) {
	  *o++ = r->ch[0];
	  l++;
	  }
       else {
	  strcpy( o, r->ch );
	  o += r->len;
	  len += r->len;
	  }
       }
 *o++ = '\0';
 return( len );
}


int string_replace_string( char *ins, char *outs )
{
 char *o = outs, *i = ins;
 int l = 0, len = 0, x, fnd = 0;
 char buf[3];
 STR_TAB *f;

 if ( !string_table_count )
    return( 0 );
 while ( *i ) {
       for ( x = 0, f = string_table, fnd = 0; x < string_table_count; x++, f++ ) {
	   if ( f->search[0] == *i &&
		  !strncmp( i, f->search, f->slen ) ) {
	      i += f->slen;
	      strcpy( o, f->replace );
	      o += f->rlen;
	      len += f->rlen;
	      fnd = 1;
	      break;
	      }
	   }
	if ( !fnd ) {
	  *o++ = *i++;
	  len++;
	  }
       }
 *o++ = '\0';
 return( len );
}

extern "C" {

int __far __pascal __export _STRTABLE( int argc, char *argv[] )
{
 FILE *istream, *ostream, *xstream;

 if ( argc > 1 ) {
    istream = fopen( argv[1], "rb" );
    if ( ostream == NULL ) {
       alert_box( "RTFTOAST", "Can't Open %s!", argv[1] );
       return( 2 );
       }
    }
 if ( argc > 2 ) {
    ostream = fopen( argv[2], "wb" );
    if ( ostream == NULL ) {
       alert_box( "RTFTOAST", "Can't Open %s!", argv[2] );
       return( 2 );
       }
    }
 ibuf = new char[10000];
 obuf = new char[16000];
 if ( setvbuf( istream, NULL, _IOFBF, 8192 ) ) {
    if ( setvbuf( istream, NULL, _IOFBF, 4096 ) ) {
       if ( setvbuf( istream, NULL, _IOFBF, 2048 ) )
	  setvbuf( istream, NULL, _IOFBF, 1024 );
       }
    }
 if ( setvbuf( ostream, NULL, _IOFBF, 8192 ) ) {
    if ( setvbuf( ostream, NULL, _IOFBF, 4096 ) ) {
       if ( setvbuf( ostream, NULL, _IOFBF, 2048 ) )
	  setvbuf( ostream, NULL, _IOFBF, 1024 );
       }
    }
 xstream = fopen( "STRTABLE.BSM", "rb" );
 if ( xstream == NULL ) {
    alert_box( "RTFTOAST", "Can't Open STRTABLE.BSM!" );
    delete ibuf;
    delete obuf;
    return( 3 );
    }
 fread(char_table, sizeof(CHREP), 256, xstream );
 fread(&string_table_count, 2, 1, xstream );
 fread(string_table, sizeof(STR_TAB), string_table_count, xstream );
 fclose( xstream );
 dllYield();
 /*
 init_default_char_table();
 if ( load_char_table( "char.tab" ) )
    return( 1 );
 if ( load_string_table( "string.tab" ) )
    return( 2 );
 sort_string_table();
 */
 while ( fgets( ibuf, 8192, istream ) != NULL ) {
       char_replace_string( ibuf, obuf );
       string_replace_string( obuf, ibuf );
       fputs( ibuf, ostream );
       dllYield();
       }
 fclose( ostream );
 fclose( istream );
 delete ibuf;
 delete obuf;
 return( 0 );
}

}
