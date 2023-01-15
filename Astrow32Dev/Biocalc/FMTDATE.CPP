#include "stdafx.h"
#include <stdlib.h>
#include <atlcomtime.h>
#include "date.hpp"

char *Date::format()
{
 static char buf[20];
 char date_fmt[15], *df, *bp = buf;

 GetProfileString("intl", "sShortDate", "M/d/yy", date_fmt, 14 );
 for ( df = date_fmt; *df; df++ ) {
     switch( *df ) {
	   case 'M' :
		if ( *(df+1) == 'M' ) {
		   df++;
		   bp += sprintf( bp, "%02d", month );
		   }
		else
		   bp += sprintf( bp, "%2d", month );
		break;
	   case 'd' :
		if ( *(df+1) == 'd' ) {
		   df++;
		   bp += sprintf( bp, "%02d", day );
		   }
		else
		   bp += sprintf( bp, "%-2d", day );
		break;
	   case 'y' :
		while (*(df+1) == 'y')
		      df++;
		   bp += sprintf( bp, "%04d", year );
		break;
	   default :
		*bp++ = *df;
		break;
	   }
     }
 return( buf );
}

