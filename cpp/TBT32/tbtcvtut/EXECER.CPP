#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include <assert.h>

HINSTANCE hInstance;
#define TBTDLLNAME "TBTCVTUT.DLL"

typedef int (WINAPI *CALLTYPE)(int argc, char **);


class InstName {
    HINSTANCE hInst;
    int argc;
    char *argv[10];
    CALLTYPE fnc;
    protected:
    public:
    InstName() { hInst = hInstance; }
    ~InstName() {}
    CALLTYPE getFnc( char *f );
    int MakeCallList( char *name, char *p1, char *p2, char *p3, char *p4, char *p5, char *p6, char *p7, char *p8 );
    int Call();
    };


int InstName::MakeCallList( char *name, char *p1, char *p2, char *p3, char *p4, char *p5, char *p6, char *p7, char *p8 )
{
 assert( name != NULL );
 argv[0] = name;
 argv[1] = p1;
 argv[2] = p2;
 argv[3] = p3;
 argv[4] = p4;
 argv[5] = p5;
 argv[6] = p6;
 argv[7] = p7;
 argv[8] = p8;
 argv[9] = NULL;
 for ( argc = 0; argc < 9; argc++ ) {
     if ( argv[argc] == NULL )
	break;
     }
 return( argc );
}

int InstName::Call()
{
 int r;

 dllYield();
 r = fnc(argc,argv );
 dllYield();
 return( r );
}

CALLTYPE InstName::getFnc( char *func )
{
 char buf[50];
 
 buf[0] = '_';
 strcpy( &buf[1],func );
 _strupr(buf);
 fnc = (CALLTYPE) GetProcAddress( hInst, buf );
 return( fnc );
}

static int ret_val;

int __declspec(dllexport) getFunctionRet()
{
 return ret_val;
}

int __declspec(dllexport)  execFunction(char *lib, char *func, char *p1, char *p2, char *p3, char *p4, char *p5, char *p6, char *p7, char *p8 )
{
 InstName dllfnc;
 CALLTYPE c;

 dllfnc.MakeCallList(func,p1,p2,p3,p4,p5,p6,p7,p8);
 c = dllfnc.getFnc(func);
 if ( c == NULL ) {
    alert_box( "EXEC", "Can't Find Function %s!", func );
    return( 0 );
    }
 ret_val = dllfnc.Call();
 return( 1 );
}

void __declspec(dllexport) setHinstance( HINSTANCE h )
{
 hInstance = h;
}
