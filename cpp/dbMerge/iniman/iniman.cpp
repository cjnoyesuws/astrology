// iniman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "astro.h"
#include "dataext.h"
#include "flags.h"

void saveToIni( char *p, int interp )
{
 char buf[25];
 int flags, house, charts, chart_code, datafile;
 strcpy( buf, "0 0 0 0 0");
 GetPrivateProfileString("ChartSetup",p,buf,buf,25,"ASTROW.INI");
 sscanf( buf, "%u %d %d %d %d", &flags, &house,
      &charts, &chart_code, &datafile );
 charts |= GRIDF;
 charts |= interp;
 sprintf( buf, "%u %d %d %d %d", flags, house,
      charts, chart_code, datafile );
 WritePrivateProfileString("ChartSetup",p,buf,"ASTROW.INI");
}


int _tmain(int argc, _TCHAR* argv[])
{
	char buf[256];
	if ( !strcmpi(argv[1], "-new" ) ) {
		strcpy(buf, "C:\\Program Files\\Astro For Windows\\" );
		saveToIni( "Birth", INTRP );
        saveToIni( "Compat", INTRP );
        saveToIni( "Trans", INTRP );
        saveToIni( "Progr", INTRP );
        saveToIni( "Numer", 0 );
        saveToIni( "Reloc", INTRP );
        saveToIni( "Compos", INTRP );
        saveToIni( "FixStar", INTRP );
        saveToIni( "ArabPt", INTRP );
        saveToIni( "CompTr", INTRP );
        saveToIni( "Solar", INTRP );
        saveToIni( "Harmonic", INTRP );
	}
	else if ( !strcmpi(argv[1], "-old" ) ) {
		strcpy(buf, "C:\\ASTROW\\");
	}
	else {
		strcpy( buf, argv[1] );
	}
	WritePrivateProfileString("Directories", "Main", buf, "ASTROW.INI" );
    WritePrivateProfileString("Directories", "Data", buf, "ASTROW.INI" );
	WritePrivateProfileString("Directories", "DB", buf, "ASTROW.INI" );
	WritePrivateProfileString("Directories", "User", buf, "ASTROW.INI" );
	WritePrivateProfileString("Directories", "Help", buf, "ASTROW.INI" );
   
	return 0;
}

