#include "stdafx.h"
#include "direc.hpp"
#include <io.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#include "inifile.hpp"
#include <shlobj.h>

CString CurLang;

int Directories::saveToIni()
{
 CWinApp *app = AfxGetApp();


 app->WriteProfileString( "Directories", "Main", main );
 app->WriteProfileString( "Directories", "Help", help );
 app->WriteProfileString( "Directories", "DB", db );
 app->WriteProfileString( "Directories", "Data", data );
 app->WriteProfileString( "Directories", "User", user );
 app->WriteProfileString( "Database", "DatabaseName", dbName );
  app->WriteProfileString( "Database", "TextDatabaseName", txtdbName );
 app->WriteProfileString( "Database", "Access97", (bAccess97?"Y":"N"));
 app->WriteProfileString( "Database", "DatabaseText", (bDatabaseText?"Y":"N"));
 return( 1 );
}

// Find the default ASTROW directory

CString Directories::getDataDefDir()
{
 int off; 
 char buf[200];
 if (!SHGetSpecialFolderPath( NULL, buf, CSIDL_COMMON_DOCUMENTS, 1)) {
	 CString ret = "C:\\ASTROW";
	 return ret;
 }
 strcat( buf, "\\Astro For Windows");
 if ( _access(buf, 0 ) )
	 mkdir(buf);
 CString def = buf;
 return( def );
}

CString Directories::getProgDefDir()
{
 int off; 
 char buf[200];
 if (!SHGetSpecialFolderPath( NULL, buf, CSIDL_PROGRAM_FILES, 0)) {
	 CString ret = "C:\\ASTROW";
	 return ret;
 }
 strcat( buf, "\\Astro For Windows");
 if ( _access(buf, 0 ) )
	 mkdir(buf);
 CString def = buf;
 return( def );
}

int Directories::getFromIni()
{
 CWinApp *app;
 CString buf;
 CString def;
 CString tmp;

 app = AfxGetApp();
 def = getProgDefDir();
 buf = app->GetProfileString( "Directories", "Main", def );
 main = buf;
 buf = app->GetProfileString( "Directories", "Help", main );
 if ( buf.IsEmpty() )
    help = main;
 else
    help = buf;
 
 buf = app->GetProfileString( "Directories", "Data", main );
 if ( buf.IsEmpty() )
    data = main;
 else
    data = buf;
 def = getDataDefDir();
 buf = app->GetProfileString( "Directories", "DB", def );
 if ( buf.IsEmpty() )
    db = def;
 else
    db = buf;
 buf = app->GetProfileString( "Directories", "User", def );
 if ( buf.IsEmpty() )
    user = def;
 else
    user = buf;
 temp = user;
 buf = app->GetProfileString( "Database", "DatabaseName", dbName );
 if ( buf.IsEmpty() )
    dbName = "astrow.mdb";
 else
    dbName = buf;
 buf = app->GetProfileString( "Database", "TextDatabaseName", txtdbName );
 if ( buf.IsEmpty() )
    txtdbName = "astrow.mdb";
 else
    txtdbName = buf;
 buf = app->GetProfileString( "Database", "Access97", "N" );
 if ( buf=="Y" )
    bAccess97 = TRUE;
 else 
    bAccess97 = FALSE;
 buf = app->GetProfileString( "Directories", "DatabaseText", "Y" );
 if ( buf=="Y" )
    bDatabaseText = TRUE;
 else
    bDatabaseText = FALSE;
 m_workspace.Open();
 m_pDatabase = new CDaoDatabase(&m_workspace);
 m_pDatabase->Open(GetDatabaseName());
 if ( dbName != txtdbName ) {
	 m_pTextDatabase = new CDaoDatabase(&m_workspace);
     m_pDatabase->Open(GetDatabaseName());
 }
 else
	m_pTextDatabase = m_pDatabase;
 return( 1 );
}


Directories::~Directories()
{
 //m_workspace.Close();
 //delete m_pDatabase;
 //if ( m_pDatabase != m_pTextDatabase )
 //	 delete m_pTextDatabase;
}

void Directories::CloseDb()
{
  m_pDatabase->Close();
 if ( m_pDatabase != m_pTextDatabase )
	 m_pTextDatabase->Close();
 m_workspace.Close();
}

void Directories::ReopenDb()
{
 m_workspace.Open();
 m_pDatabase->Open(GetDatabaseName());
 if ( dbName != txtdbName )
     m_pDatabase->Open(GetDatabaseName());
}

CString GetDatabaseName() 
{
  CString st = theDirectories.getDB();
  if ( st.Right(1) != "\\" )
     st += "\\";
  st += theDirectories.getDbName();
  return ( st );
}

CString GetTextDatabaseName() 
{
  CString st = theDirectories.getDB();
  if ( st.Right(1) != "\\" )
     st += "\\";
  st += theDirectories.getTxtDbName();
  return ( st );
}

CString &GetCurLanguage()
{
    if ( !CurLang.GetLength() )	
	   CurLang= AfxGetApp()->GetProfileString(_T("TBT"),_T("CurrLanguage"),_T("English"));
	return CurLang;
}


/*
DirectDlgf::DirectDlgf( zWindow *pPar, Directories *d ) :
		    FormDlgf(pPar,zResId("DIRECTORIES"), HELPID_DLG_DIRECT )
{
 static char BCS pict[] = "X(145)";
 new zStringEdit(this, IDC_DSMAIN, &d->getMain(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
 new zStringEdit(this, IDC_DSHELP, &d->getHelp(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
 new zStringEdit(this, IDC_DSDB, &d->getDB(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
 new zStringEdit(this, IDC_DSDATA, &d->getData(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
 new zStringEdit(this, IDC_DSUSER, &d->getUser(),
		pict, FLD_ALPHANUMERIC|FLD_TOUPPER);
 run();
}


*/

