#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include <fcntl.h>
#include <conio.h>
#include "strtab.h"
#include <iostream.h>
#include <fstream.h>

// 7/8/94   CJN   complete Conversion
// 10/24/94 CJN   Setup For 1 DLL approach

extern CHREP char_table[];
extern STR_TAB string_table[];
extern int string_table_count;

extern int translate_string_chrs( char *rbuf, unsigned char *tbuf );

static int load_string_table( char *fil )
{
 char buf[150];
 static char rbuf[100];
 static char tbuf[100];
 static char srbuf[100];
 static char stbuf[100];
 int num, last = 0, dummy;
 char *sptr;
 char *rptr;

 ifstream stream(fil,ios::in|ios::nocreate);
 if ( stream.bad()||stream.fail() ) {
    alert_box( "MKSTRB", "Can't find table %s to Read!", fil );
    return( 1 );
    }
 while ( !stream.eof() && !stream.bad() && !stream.fail() ) {
       stream >> num;
       stream.ignore(3,'|');
       stream.getline(srbuf,99);
       stream.getline(rbuf,99);
       translate_string_chrs( rbuf, (unsigned char *)tbuf );
       translate_string_chrs( srbuf, (unsigned char *)stbuf );
       num--;
       if ( !strlen(stbuf) )
	  continue;
       if ( num > 200 ) {
	  alert_box("MKSTRB","Member %d of file %s Exceeds 200 for table!", num, fil );
	  return( 2 );
	  }
       if ( strlen( tbuf ) > 59 ) {
	  alert_box("MKSTRB","Translation string %d of file %s is too long max is 59!", num, fil );
	  return( 2 );
	  }
       if ( strlen( stbuf ) > 59 ) {
	  alert_box("MKSTRB","Search string %d of file %s is too long max is 59!", num, fil );
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
 stream.close();
 return( 0 );
}

static int load_char_table( char *fil )
{
 char buf[100];
 static char rbuf[52];
 static char tbuf[52];
 int num, l;
 char *ptr;

 ifstream stream(fil,ios::in|ios::nocreate);
 if ( stream.bad()||stream.fail() ) {
    alert_box( "MKSTRB","Can't find table %s to Read!", fil );
    return( 1 );
    }
 while ( !stream.eof() && !stream.bad() && !stream.fail() ) {
       stream >> num;
       stream.ignore(3,'|');
       stream.getline(buf,49);
       translate_string_chrs( rbuf, (unsigned char *)tbuf );
       if ( num > 256 ) {
	  alert_box("MKSTRB","Member %d of file %s Exceeds 256!", num, fil );
	  return( 2 );
	  }
       if (( l = strlen( tbuf ) ) > 9 ) {
	  alert_box( "MKSTRB","Translation for char %d too long max is 9", num );
	  return( 3 );
	  }
       else {
	  strcpy( char_table[num].ch, tbuf );
	  char_table[num].len = l;
	  }
       }
 stream.close();
 return( 0 );
}

static int init_default_char_table( void )
{
 int i;
 char buf[25];
 char *ptr;

 for ( i = 0; i < 255; ++i ) {
     char_table[i].ch[0] = i;
     char_table[i].ch[1] = '\0';
     char_table[i].len = 1;
     }
 return( 1 );
}

static int string_table_cmp( const void *x1, const void *x2 )
{
 STR_TAB *s1 = ((struct STR_TAB *)x1),
 *s2 = ((struct STR_TAB *)x2);

 return( (int)s2->slen - s1->slen );
}

static void sort_string_table(void)
{
 qsort( string_table, string_table_count, sizeof( STR_TAB ), string_table_cmp );
}

extern "C" {

int __declspec(dllexport) WINAPI _MKSTRB(int argc, char *argv[])
{
 init_default_char_table();
 if ( load_char_table( "char.tab" ) )
    return( 1 );
 if ( load_string_table( "string.tab" ) )
    return( 2 );
 sort_string_table();
 ofstream stream( "STRTABLE.BSM", ios::out | ios::binary );
 if ( stream.bad()||stream.fail() ) {
    alert_box( "MKSTRB","Can't Open STRTABLE.BSM!" );
    return( 3 );
    }
 stream.write((unsigned char *)char_table, sizeof(CHREP) * 256 );
 stream.write((unsigned char *)&string_table_count, 2 );
 stream.write((unsigned char *)string_table,
      sizeof(STR_TAB) * string_table_count );
 stream.close();
 return( 0 );
}

}