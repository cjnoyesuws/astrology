#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include <iostream.h>
#include <fstream.h>

// 7/8/94   CJN   complete Conversion
// 10/24/94 CJN   Setup For 1 DLL approach

extern LST symbols[];
extern int num_symbols;

static int matchsym( const void *s1, const void *s2 )
{
 int r;
 LST *l1, *l2;

 l1 = (LST *)s1;
 l2 = (LST *)s2;
 if ( !( r = strcmpi( l1->symbol, l2->symbol )) )
    return( l1->col_used - l2->col_used );
 else
    return( r );
}


extern "C" {

int __declspec(dllexport) WINAPI _MKBSR( int argc, char **argv )
{
 int x = 0, test;
 char buf2[250];
 char buf[100];
 char *src, *dst, *p;

 if ( argc > 2 )
    src = argv[2];
 else
    src = "TEXT.SYM";
 if ( argc > 1 )
    dst = argv[1];
 else
    dst = "TEXT.BSM";
 ifstream istream( src, ios::in|ios::nocreate );
 if ( istream.bad() || istream.fail() ) {
    alert_box( "MKBSR", "Can't Open \"%s\" For Reading!", src );
    return( 1 );
    }
 do {
    test = istream.get();
    if ( istream.fail() || istream.eof() ) {
       istream.close();
       num_symbols = x;
       break;
       }
    else if ( test == '#' ) {
       istream.getline( buf, 99 );
       continue;
       }
    else
       istream.putback( test );
    istream >> symbols[x].symbol >> symbols[x].value >> symbols[x].col_used;
    istream.getline( buf, 99 );
    if ( istream.eof() ) {
       istream.close();
       num_symbols = x;
       break;
       }
    else if ( istream.bad() || istream.fail() ) {
       alert_box( "MKBSR", "Error Reading Text Symbols!" );
       istream.close();
       return( 2 );
       }
    else
       ++x;
 } while ( !istream.bad() && !istream.fail() && !istream.eof() );
 istream.close();
 num_symbols = x;
 qsort( symbols, num_symbols, sizeof( LST ), matchsym );
 ofstream ostream(dst, ios::out | ios::binary );
 if ( ostream.bad()||ostream.fail() ) {
    alert_box( "MKBSR", "Can't Open \"%s\" For Writing!", dst );
    return( 1 );
    }
 ostream.write((unsigned char *) &num_symbols, 2);
 ostream.write((unsigned char *) symbols, sizeof( LST ) * num_symbols );
 ostream.close();
 return( 0 );
}

}
