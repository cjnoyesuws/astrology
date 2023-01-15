#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <io.h>
#include "direc.hpp"
#include "shlobj.h"

char *data_name( char *name )
{
 int off; 
 static TCHAR buf[200];
 if (!SHGetSpecialFolderPath( NULL, buf, CSIDL_PROGRAM_FILES, 0)) {
	strcpy( buf, "C:\\ASTROW" );
 }
 strcat( buf, "\\Astro For Windows");
 if ( _access(buf, 0 ) )
	 mkdir(buf);
 if ( buf[strlen(buf)-1] != '\\' )
    strcat( buf, "\\" );
 strcat( buf, name );
 return( buf );
}
