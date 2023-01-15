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

extern VLST variables[];
extern int num_var;

static int _cdecl matchvar( const void *s1, const void *s2 )
{
 int r;
 LST *l1, *l2;

 l1 = (LST *)s1;
 l2 = (LST *)s2;
 if ( !( r = strcmpi( l1->symbol, l2->symbol )) )
    return( l1->type_code - l2->type_code );
 else
    return( r );
}


extern "C" {

int __declspec(dllexport) WINAPI _MKVBSR( int argc, char **argv )
{
 int x = 0, test;
 char buf2[250];
 char buf[100];
 char *src, *dst, *p;

 if ( argc > 2 )
    src = argv[2];
 else
    src = "VAR.SYM";
 if ( argc > 1 )
    dst = argv[1];
 else
    dst = "VAR.BSM";
 ifstream istream( src, ios::in|ios::nocreate );
 if ( istream.bad() || istream.fail() ) {
    alert_box( "MKVBSR", "Can't Open \"%s\" For Reading!", src );
    return( 1 );
    }
 do {
    test = istream.get();
    if ( istream.fail() || istream.eof() ) {
       istream.close();
       num_var = x;
       break;
       }
    else if ( test == '#' ) {
       istream.getline( buf, 99 );
       continue;
       }
    else
       istream.putback( test );
    istream >> variables[x].symbol >> variables[x].value >> variables[x].type_code;
    istream.getline( buf, 99 );
    if ( istream.eof() ) {
       istream.close();
       num_var = x;
       break;
       }
    else if ( istream.bad() || istream.fail() ) {
       alert_box( "MKVBSR", "Error Reading Variable Symbols!" );
       istream.close();
       return( 2 );
       }
    else
       ++x;
 } while ( !istream.bad() && !istream.fail() && !istream.eof() );
 istream.close();
 num_var = x;
 qsort( variables, num_var, sizeof( VLST ), matchvar );
 ofstream ostream(dst, ios::out | ios::binary );
 if ( ostream.bad()||ostream.fail() ) {
    alert_box( "MKVBSR", "Can't Open \"%s\" For Writing!", dst );
    return( 1 );
    }
 ostream.write((unsigned char *) &num_var, 2);
 ostream.write((unsigned char *) variables, sizeof( VLST ) * num_var );
 ostream.close();
 return( 0 );
}

}
