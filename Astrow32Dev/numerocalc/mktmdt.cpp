#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include "chartinf.h"
#include "output.fns"

char *make_date( DATES *dp )
{
 static char buf[30];
 char date_fmt[25], *df, *bp = buf;

 GetProfileString("intl", "sShortDate", "M/d/yy", date_fmt, 14 );
 for ( df = date_fmt; *df; df++ ) {
     switch( *df ) {
	   case 'M' :
		if ( *(df+1) == 'M' ) {
		   df++;
		   bp += sprintf( bp, "%02d", dp->month );
		   }
		else
		   bp += sprintf( bp, "%d", dp->month );
		break;
	   case 'd' :
		if ( *(df+1) == 'd' ) {
		   df++;
		   bp += sprintf( bp, "%02d", dp->day );
		   }
		else
		   bp += sprintf( bp, "%d", dp->day );
		break;
	   case 'y' :
		while (*(df+1) == 'y')
		      df++;
		   bp += sprintf( bp, "%04d", dp->year );
		break;
	   default :
		*bp++ = *df;
		break;
	   }

     }
 return( buf );
}

