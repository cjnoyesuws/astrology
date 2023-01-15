#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "asfrmdlg.hpp"
#include "tdirec.hpp"
#include "paths.hpp"

char *set_path( char *name, int type )
{
 static char buf[170];

 switch( type ) {
       case PROGRAM_F :
	    strcpy( buf, theTbtDirectories.getMain() );
	    break;
       case DATA_F:
	    strcpy( buf, theTbtDirectories.getData() );
	    break;
       case HELP_F:
	    strcpy( buf, theTbtDirectories.getHelp() );
	    break;
       case TEXT_F:
	    strcpy( buf, theTbtDirectories.getSource() );
	    break;
       case EDIT_F:
	    strcpy( buf, theTbtDirectories.getEdit() );
	    break;
       default :
	    strcpy( buf, name );
            return( buf );
	    break;
       }
 int l = strlen( buf );
 if ( !l ) {
    strcpy( buf, theTbtDirectories.getMain() );
    l = strlen( buf );
    }
 if ( buf[l-1] != '\\' )
    strcat( buf, "\\" );
 strcat( buf, name );
 return( buf );
}
