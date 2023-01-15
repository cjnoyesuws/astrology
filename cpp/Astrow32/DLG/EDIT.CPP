#include "stdafx.h"
#include "astrow.h"
#include "edit.hpp"
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include "inifile.hpp"

int EditSetup::saveToIni()
{
 AfxGetApp()->WriteProfileString( "Edit", "Path", path );
 AfxGetApp()->WriteProfileString( "Edit", "Opt", opt );
 AfxGetApp()->WriteProfileString( "Edit", "UseShell", _useShell?"1":"0" );
 return( 1 );
}


int EditSetup::getFromIni()
{
 CString buf;
 int e;

 path = AfxGetApp()->GetProfileString( "Edit", "Path", (char *)(LPCTSTR)path );
 opt = AfxGetApp()->GetProfileString( "Edit", "Opt", (char *)(LPCTSTR)opt );
 _useShell = (int)AfxGetApp()->GetProfileInt("Edit", "UseShell", 1 );
 
 return( 1 );
}
/*
EditSetupDlgf::EditSetupDlgf( zWindow *pPar, EditSetup *d ) :
		    FormDlgf(pPar,zResId("EDIT_DAT"), HELPID_DLG_EDITOPT )
{
 static char BCS pict[] = "X(145)";
 static char BCS pict2[] = "X(60)";
 new zStringEdit(this, IDC_EDNAME, &d->getPath(),
		pict, FLD_ALPHANUMERIC);
 new zStringEdit(this, IDC_EDOPT, &d->getOpt(),
		pict2, FLD_ALPHANUMERIC);
 run();
}

*/


