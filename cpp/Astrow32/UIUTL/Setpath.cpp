#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "direc.hpp"
#include "folders.h"

void removeDots( char *buf )
{

}


char *set_path( char *name, int type )
{
 static char buf[350];
 char buf2[150];
 if ( name[0] != '\0' && (name[0] == '\\' || name[1] == ':') )
	type = -1;
 if ( type > DEFAULT_FLD ) {
    strcpy(buf,set_path((char *)(const char *)theFolders.GetFolder(type),USER_F));
    }
 else {
    switch( type ) {
       case PROGRAM_F :
       case UTILITY_F :
	    strcpy( buf, theDirectories.getMain() );
	    break;
       case TEMP_F :
	    strcpy( buf, theDirectories.getTemp() );
	    break;
       case DATA_F:
	    strcpy( buf, theDirectories.getData() );
	    break;
       case HELP_F:
	    strcpy( buf, theDirectories.getHelp() );
	    break;
	   case DEFAULT_FLD:
       case USER_F:
	    strcpy( buf, theDirectories.getUser() );
	    break;
       case DATABASE_F :
	    strcpy( buf, theDirectories.getDB() );
	    break;
       case CURRENT_F :
        strcpy( buf, set_path((char *)(const char *)theFolders.GetCurFolderName(),USER_F));
       break;
	   default :
	    strcpy( buf, name );
            return( buf );
	    break;
       }
    }
 int l = strlen( buf );
 if ( !l ) {
    strcpy( buf, theDirectories.getMain() );
    l = strlen( buf );
    }
 if ( buf[l-1] != '\\' )
    strcat( buf, "\\" );
 if (strlen(name))
    strcat( buf, name );
 return( buf );
}
