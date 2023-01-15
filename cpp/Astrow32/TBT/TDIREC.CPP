#include "zapp.hpp"
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "dialogs.h"
#include "asfrmdlg.hpp"
#include "tdirec.hpp"
#include <io.h>
#include <stdlib.h>
#ifdef _MSC_VER
#include <direct.h>
#else
#include <dir.h>
#endif
#include "basedcs.h"
#include "inifile.hpp"
#include "acombbox.hpp"
#include "resource.h"
#include "helpid.h"

// Useage of these classes
// Classes for group of directories, and
// dialog for getting directories
//
//
//   Directories theDirectories;
//
//   TbtDirectForm *df = new DirectForm(
//      new TbtDirectDlgf( out), &theTbtDirectories );
//   if ( df->completed() ) {
//      out->printf("Main Dir = %s\n", theDirectories.getMain() );
//      out->printf("Source Dir = %s\n", theDirectories.getSource() );
//      out->printf("Help Dir = %s\n", theDirectories.getHelp()  );
//      out->printf("Text Dir = %s\n", theDirectories.getText()  );
//      out->printf("Data Dir = %s\n", theDirectories.getData()  );
//      out->printf("Edit Dir = %s\n", theDirectories.getEdit()  );
//      }
//   delete df;


int TbtDirectories::saveToIni()
{
 int f;

 f = WritePrivateProfileString( "TBT Directories", "Main", main, APPNAME );
 if ( !f )
    return( 0 );
 WritePrivateProfileString( "TBT Directories", "Source", source, APPNAME );
 WritePrivateProfileString( "TBT Directories", "Help", help, APPNAME );
 WritePrivateProfileString( "TBT Directories", "Text", text, APPNAME );
 WritePrivateProfileString( "TBT Directories", "Data", data, APPNAME );
 return(  WritePrivateProfileString( "TBT Directories", "Edit", edit, APPNAME ) );
}


int TbtDirectories::getFromIni()
{
 zString def((unsigned int)160);
 zString buf((unsigned int)150);
 zString tmp, xmain;

 char *p;
 int e;

 e = GetPrivateProfileString( "Directories", "Main", "", (char *)def, 149, APPNAME );
 xmain = def;
 if ( def[def.length()-1]=='\\' )
    def &= "TEXT";
 else
    def &= "\\TEXT";
 e = GetPrivateProfileString( "TBT Directories", "Main", (char *)def, (char *)buf, 149, APPNAME );
 if ( !e )
    return( 0 );
 main = buf;
#ifndef NUMEROWTBT
 GetPrivateProfileString( "Directories", "Help", (char *)xmain, buf, 149, APPNAME );
 if ( !strlen(buf) )
    help = xmain;
 else
    help = buf;
 GetPrivateProfileString( "TBT Directories", "Help", (char *)help, buf, 149, APPNAME );
 if ( !strlen(buf) )
    help = xmain;
 else
    help = buf;
#endif 
 GetPrivateProfileString( "TBT Directories", "Edit", (char *)main, buf,  149, APPNAME );
 if ( !strlen(buf) )
    edit = main;
 else
    edit = buf;
 GetPrivateProfileString( "Directories", "Data", (char *)xmain, buf, 149, APPNAME );
 if ( !strlen(buf) )
    data = xmain;
 else
    data = buf;
 GetPrivateProfileString( "TBT Directories", "Data", (char *)data, buf, 149, APPNAME );
 if ( !strlen(buf) )
    data = xmain;
 else
    data = buf;
 GetPrivateProfileString( "TBT Directories", "Text", (char *)main, buf, 149, APPNAME );
 if ( !strlen(buf) )
    text = main;
 else
    text = buf;
 GetPrivateProfileString( "TBT Directories", "Source", (char *)main, buf, 149, APPNAME );
 if ( !strlen(buf) )
    source = main;
 else
    source = buf;
 return( 1 );
}



TbtDirectDlgf::TbtDirectDlgf( zWindow *pPar, TbtDirectories *d ) :
		    FormDlgf(pPar,zResId(IDD_DIRECT), HELPID_DLG_DIRECT )
{
 static char BCS pict[] = "X(145)";
 new zStringEdit(this, IDC_EDIT_MAIN, &d->getMain(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
 new zStringEdit(this, IDC_EDIT_SOURCE, &d->getSource(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
 new zStringEdit(this, IDC_EDIT_DATA, &d->getData(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
 new zStringEdit(this, IDC_EDIT_EDIT, &d->getEdit(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
#ifndef NUMEROWTBT  
 new zStringEdit(this, IDC_EDIT_HELP, &d->getHelp(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
#endif
 run();
}




