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
#include "import.h"
#include "charcons.h"
#include <io.h>


#define APPNAME "ASTROW.INI"
static HINSTANCE hLibrary;

FARPROC get_import_func( char *func )
{
 char buf[100];

 GetPrivateProfileString( "Import", "ImportDLL", "CUSTOM.DLL", buf, 99 );
 hLibrary = LoadLibrary(buf);
 if ( hLibrary < 32 ) {
    ExecError( buf, hLibrary );
    return( NULL );
    }
 return( GetProcAddress( hLibrary, func ) );
}



char *get_import_file( char *name, char *ix )
{
 char *p;
 char fname[150];
 char type[50];
 char ext[5];
 char prompt[100];
 char *types[] = {type, ext, 0, 0 };

 memset( fname, 0, 150 );
 GetPrivateProfileString( "Import", "ImportType", "Text File (*.TXT)", type, 50 );
 GetPrivateProfileString( "Import", "ImportExt", ".TXT", ext, 5 );
 GetPrivateProfileString( "Import", ix, "File Name:", buf, 99 );
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


void import_export_birth_data( IMPORT_DATA_STRUCT *pImp, char *fnc, char *pr )
{
 char fname[150];
 FARPROC lpFunc;

 lpFunc = get_import_func(fnc);
 if ( lpFunc == (FARPROC) NULL ) {
    if ( hLibrary > 32 )
       DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 if ( get_import_file( fname, pr ) == NULL ) {
    DeleteLibrary( hLibrary );
    hLibrary = 0;
    return;
    }
 lpFunc( pImp, fname );
 DeleteLibrary( hLibrary );
 hLibrary = 0;
}

void import_birth_data( IMPORT_DATA_STRUCT *pImp )
{
 import_export_birth_data( pImp, "ImportBirthData", "ImportPrompt" )
}

void export_birth_data( IMPORT_DATA_STRUCT *pImp )
{
 import_export_birth_data( pImp, "ExportBirthData", "ImportExportPrompt" )
}
