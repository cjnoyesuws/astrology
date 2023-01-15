#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "dataext.h"
#include "errors.fns"
#include "arabpt.h"
#include "fixstar.h"
#include "output.fns"
#include "charcons.h"
#include <io.h>

#define APPNAME "ASTROW.INI"
static HINSTANCE hLibrary;

FARPROC get_custom_func( char *func )
{
 char buf[100];

 GetPrivateProfileString( "Export", "ExportDLL", "CUSTOM.DLL", buf, 99, APPNAME );
 hLibrary = LoadLibrary(buf);
 if ( hLibrary < 32 ) {
    ExecError( buf, hLibrary );
    return( NULL );
    }
 return( GetProcAddress( hLibrary, func ) );
}



char *get_custom_file( char *name )
{
 char *p;
 char fname[150];
 char type[50];
 char ext[5];
 char prompt[100];
 char *types[] = {type, ext, 0, 0 };

 memset( fname, 0, 150 );
 GetPrivateProfileString( "Export", "ExportType", "Text File (*.TXT)", type, 50 );
 GetPrivateProfileString( "Export", "ExportExt", ".TXT", ext, 5 );
 GetPrivateProfileString( "Export", "ExportPrompt", "File To Export To:", buf, 99 );
 zFileOpenForm *fof = new zFileOpenForm(app->rootWindow(),
     prompt, name, types );
 if ( fof->completed() ) {
    strcpy( name, fof->name() );
    delete fof;
    }
 else {
    delete fof;
    return( NULL );
    }
 return( name );
}



void write_cust_natal( BIRTH_DB *data, AS_INF *inf, BITS mode,
	     NUM house_mode, DATA_PACKET *dpk, int count )
{
 char fname[150];
 FARPROC lpFunc;

 lpFunc = get_custom_func("NatalExport");
 if ( lpFunc == (FARPROC) NULL ) {
    if ( hLibrary > 32 )
       DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 if ( get_custom_file( fname ) == NULL ) {
    DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 lpFunc( data, inf, mode, house_mode, dpk, count, fname );
 DeleteLibrary( hLibrary );
 hLibrary = 0;
}

void write_cust_compos( BIRTH_DB *data, BIRTH_DB *pdata,
      AS_INF *inf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
 char fname[150];
 FARPROC lpFunc;

 lpFunc = get_custom_func("CompositeExport");
 if ( lpFunc == (FARPROC) NULL ) {
    if ( hLibrary > 32 )
       DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 if ( get_custom_file( fname ) == NULL ) {
    DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 lpFunc( data, pdata, inf, mode, house_mode, dpk, fname  );
 DeleteLibrary( hLibrary );
 hLibrary = 0;

}

void write_cust_compat( BIRTH_DB *data, BIRTH_DB *pdata,
     AS_INF *inf, AS_INF *pinf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
 char fname[150];
 FARPROC lpFunc;

 lpFunc = get_custom_func("CompatExport");
 if ( lpFunc == (FARPROC) NULL ) {
    if ( hLibrary > 32 )
       DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 if ( get_custom_file( fname ) == NULL ) {
    DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 lpFunc( data, pdata, inf, pinf, mode, house_mode, dpk, fname );
 DeleteLibrary( hLibrary );
 hLibrary = 0;

}

void write_cust_prog( BIRTH_DB *data, AS_INF *inf, BITS mode,
				 NUM house_mode, DATA_PACKET *dpk )
{
 char fname[150];
 FARPROC lpFunc;

 lpFunc = get_custom_func("ProgrExport");
 if ( lpFunc == (FARPROC) NULL ) {
    if ( hLibrary > 32 )
       DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 if ( get_custom_file( fname ) == NULL ) {
    DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 lpFunc( data, inf, mode, house_mode, dpk, fname );
 DeleteLibrary( hLibrary );
 hLibrary = 0;

}

void write_cust_trans( BIRTH_DB *data, AS_INF *inf, BITS mode,
	       BIRTH_DB *tr_data, NUM house_mode, DATA_PACKET *dpk )
{
 char fname[150];
 FARPROC lpFunc;

 lpFunc = get_custom_func("TransExport");
 if ( lpFunc == (FARPROC) NULL ) {
    if ( hLibrary > 32 )
       DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 if ( get_custom_file( fname ) == NULL ) {
    DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 lpFunc( data, inf, mode, tr_data, house_mode, dpk, fname );
 DeleteLibrary( hLibrary );
 hLibrary = 0;

}

void write_cust_cmtrans( BIRTH_DB *data, AS_INF *inf, BITS mode,
   BIRTH_DB *tr_data, BIRTH_DB *pa_data,NUM house_mode, DATA_PACKET *dpk )
{
 char fname[150];
 FARPROC lpFunc;

 lpFunc = get_custom_func("ComposTransExport");
 if ( lpFunc == (FARPROC) NULL ) {
    if ( hLibrary > 32 )
       DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 if ( get_custom_file( fname ) == NULL ) {
    DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 lpFunc( data, inf, mode, tr_data, pa_data, house_mode, dpk, fname );
 DeleteLibrary( hLibrary );
 hLibrary = 0;
}
