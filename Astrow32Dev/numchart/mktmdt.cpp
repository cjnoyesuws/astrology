#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chartinf.h"
#include "output.fns"

char *make_date( DATES *dp )
{
 static char buf[30];
 sprintf( buf, "%02d/%02d/%04d", dp->month, dp->day, dp->year );
 return( buf );
}

