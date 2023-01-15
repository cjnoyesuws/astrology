#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")
#include <iostream.h>
#include <fstream.h>

// 7/8/94   CJN   complete Conversion
// 10/24/94 CJN   Setup For 1 DLL approach

RLST rsymbols[240];
extern int num_symbols;
 
typedef int (__far __cdecl *matchfunc)(const void __far *,const void __far *); 

extern "C" {
 
int __far __pascal __export _MKRBSR( int argc, char *argv[] )
{
 int x = 0, test;
 char buf2[250];
 char buf[100];
 char *src, *dst, *p;

 if ( argc > 2 )
    src = argv[2];
 else
    src = "REPORT.SYM";
 if ( argc > 1 )
    dst = argv[1];
 else
    dst = "REPORT.BSM";
 ifstream istream(src, ios::in|ios::nocreate);
 if ( istream.bad()||istream.fail() ) {
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
    istream >> rsymbols[x].symbol >> rsymbols[x].value;
    istream.getline(buf,99);
    if ( istream.eof() ) {
       istream.close();
       num_symbols = x;
       break;
       }
    else if ( istream.bad() || istream.fail() ) {
       alert_box( "MKBSR", "Error Reading Report Symbols" );
       istream.close();
       return( 2 );
       }
    else
       ++x;
 } while ( !istream.bad() && !istream.fail() && !istream.eof() );
 istream.close();
 num_symbols = x;
 qsort( rsymbols, num_symbols, sizeof( RLST ), (matchfunc)strcmpi );
 ofstream ostream(dst, ios::out | ios::binary);
 if ( ostream.bad()||ostream.fail() ) {
    alert_box( "MKBSR", "Can't Open \"%s\" for Writing!", dst );
    return( 1 );
    }
 ostream.write((unsigned char *) &num_symbols, 2 );
 ostream.write((unsigned char *)rsymbols, sizeof( RLST ) * num_symbols );
 ostream.close();
 return( 0 );
}

}
