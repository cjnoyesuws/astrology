#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include <assert.h>
#include <stdarg.h>

#define APPNAME "ASTROW.INI"

LPVOID logdata;
LOGPROC logto;
YIELDPROC yieldto;

char buf[500];
int len;

void __declspec(dllexport) SetupLog(LPVOID data)
{
 logdata = data;
}

void __declspec(dllexport) SetupLogProc(LOGPROC proc)
{
 logto = proc;
}


int __declspec(dllexport) LogOutput( LPCSTR text )
{
 assert( logto != NULL && logdata != NULL );
 strcat( buf + len, text );
 len = 0;
 return( logto( logdata, buf ) );
}


int __declspec(dllexport) LogPrintf( LPCSTR fmt, ...  )
{
 va_list marker;

 va_start( marker, fmt );
 vsprintf( buf+len, fmt, marker );
 va_end( marker );
 assert( logto != NULL && logdata != NULL );
 len = 0;
 return( logto( logdata, buf ) );
}


int __declspec(dllexport) LogPutc(char c)
{
 buf[len++] = c;
 if ( c == '\n' ) {
    buf[len++] = '\0';;
    len = 0;
    logto( logdata, buf ); 
    }
 return( 1 );
}

void __declspec(dllexport) SetYieldProc( YIELDPROC p )
{
 yieldto = p;
}

void dllYield()
{
 if ( yieldto )
    yieldto(0);
}


void __declspec(dllexport) getConvertTextSettings( int &src, int &edit, int &dst, int &cvt )
{
 src = (int) GetPrivateProfileInt( "TBTOptions", "SourceAnsi", src, APPNAME );
 edit = (int) GetPrivateProfileInt( "TBTOptions", "EditAnsi", edit, APPNAME );
 edit = (int) GetPrivateProfileInt( "TBTOptions", "cvtAnsi", edit, APPNAME );
 dst = (int) GetPrivateProfileInt( "Misc", "AnsiText", dst, APPNAME );
}

void __declspec(dllexport) doConvertText( char *buf, int stype, int dtype, int dstx )
{
 static int src=-1, edit, dst, cvt;
 if ( src == -1 || stype == -1 )
    getConvertTextSettings( src, edit, dst, cvt );
 switch( stype ) {
    case _OEM_T_ :
	 stype = 0;
    case _SRC_T_ :
	 stype = src;
	 break;
    case _EDT_T_ :
	 stype = edit;
	 break;
    case _DST_T_ :
	 stype = dst;
	 break;
    case _CVT_T_ :
	 stype = cvt;
	 break;
    case _ANS_T_ :
	 stype = 1;
	 break;
    case _INI_T_:
	return;
    default :
	break;
    }
 switch( dtype ) {
    case _OEM_T_ :
	 dtype = 0;
	 break;
    case _SRC_T_ :
	 dtype = src;
	 break;
    case _EDT_T_ :
	 dtype = edit;
	 break;
    case _DST_T_ :
	 dtype = dst;
	 break;
    case _CVT_T_ :
	 dtype = cvt;
	 break;
    case _ANS_T_ :
	 dtype = 1;
    case _INI_T_ :
	return;
    default:
	break;
    }
 if ( dstx != -1 )
    dtype = dstx;
 if ( stype == dtype )
    return;
 else if ( stype && !dtype )
    AnsiToOem( buf, buf );
 else
    OemToAnsi( buf, buf );
}
