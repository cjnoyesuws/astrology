#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "errors.fns"
#include "tabs.hpp"

void Tabs::init( short total_width, short mul, short div, short left )
{
 tabs.total_width = total_width * mul;
 tabs.unit_mul = mul;
 tabs.unit_div = div;
 tabs.tab_no = 0;
 tabs.left_ofs = left;
}

short Tabs::get_short( FILE *stream, char delim  )
{
 char buf[40], c;
 short i = 0;

 while ( ( c = getc(stream) ) != delim && i < 39 )
       buf[i++] = c;
 buf[i++] = '\0';
 return( atoi( buf ) );
}

short Tabs::get_short( char **p, char delim  )
{
 char buf[40], c;
 short i = 0;

 while ( ( c = *(*p)++ ) != delim && i < 39 )
       buf[i++] = c;
 buf[i++] = '\0';
 return( atoi( buf ) );
}


short Tabs::to_units( short val )
{
 if ( tabs.unit_div == 1 && tabs.unit_mul == 1 )
    return( val );
 val *= tabs.unit_mul;
 if ( tabs.unit_div && tabs.unit_div != 1 )
    val /= tabs.unit_div;
 return( val );
}

char *Tabs::read( FILE *stream )
{
 static short xr[] = { 1,3,6,10,15,21,28,36,45,55,1,1,1,1,1,1,1,1,1 };
 short i, rem, qt;
 short delim = getc( stream );

 tabs.tab_width = to_units( get_short( stream, delim ) );
 if ( tabs.tab_width < 20 )
    alert_box( "Warning!","Tab Width Set to %d?", tabs.tab_width );
 tabs.tab_count = get_short( stream, delim  );
 if ( tabs.tab_count > 20 ) {
    alert_box( "Warning!","Too Many Tabs, Tab Count = %d",
					tabs.tab_count );
    tabs.tab_count = 20;
    }
 for ( i = 0; i < tabs.tab_count; ++i ) {
     tabs.tabs[i] = to_units( get_short( stream, delim  ) );
     if ( tabs.tabs[i] < 0 ) {
	tabs.fill[i] = 1;
	tabs.tabs[i] = abs(tabs.tabs[i]);
	}
     else
	tabs.fill[i] = 0;
     }
 if ( tabs.total_width > 20000 )
    return( (char *)tabs.tab_count );
 rem = tabs.total_width - tabs.tab_width;
 if ( xr[tabs.tab_count-1] != 0 && tabs.tab_count && tabs.tab_count < 11 && rem > 0 ) {
    tabs.space_add_qt = rem / xr[tabs.tab_count-1];
    tabs.space_add_rem = rem % xr[tabs.tab_count-1];
    if ( tabs.space_add_qt ) {
       qt = tabs.space_add_qt;
       for ( i = 0; i < tabs.tab_count; ++i ) {
	   tabs.tabs[i] += qt * (i+1);
	   }
       }
    rem = tabs.space_add_rem;
    while ( rem ) {
       for ( i = tabs.tab_count-1; i >= 0; i-- ) {
	   if ( rem == 1 ) {
	      tabs.tabs[i] ++;
	      rem = 0;
	      break;
	      }
	   else {
	      tabs.tabs[i] ++;
	      rem --;
	      }
	   }
       }
    }
 else {
    tabs.space_add_qt = 0;
    tabs.space_add_rem = 0;
    }
 return( (char *)tabs.tab_count );
}


char *Tabs::read( char **p )
{
 static short xr[] = { 1,3,6,10,15,21,28,36,45,55 };
 short i, rem, qt;
 short delim = *(*p)++;

 tabs.tab_width = to_units( get_short( p, delim ) );
 if ( tabs.tab_width < 20 )
    alert_box( "Warning!","Tab Width Set to %d?", tabs.tab_width );
 tabs.tab_count = get_short( p, delim  );
 if ( tabs.tab_count > 20 ) {
    alert_box( "Warning!","Too Many Tabs, Tab Count = %d",
					tabs.tab_count );
    tabs.tab_count = 20;
    }
 for ( i = 0; i < tabs.tab_count; ++i ) {
     tabs.tabs[i] = to_units( get_short( p, delim  ) );
     if ( tabs.tabs[i] < 0 ) {
	tabs.fill[i] = 1;
	tabs.tabs[i] = abs(tabs.tabs[i]);
	}
     else
	tabs.fill[i] = 0;
     }
 if ( tabs.total_width > 20000 )
    return( (char *)tabs.tab_count );
 rem = tabs.total_width - tabs.tab_width;
 if ( xr[tabs.tab_count-1] != 0 && tabs.tab_count && tabs.tab_count < 11 && rem > 0 ) {
    tabs.space_add_qt = rem / xr[tabs.tab_count-1];
    tabs.space_add_rem = rem % xr[tabs.tab_count-1];
    if ( tabs.space_add_qt ) {
       qt = tabs.space_add_qt;
       for ( i = 0; i < tabs.tab_count; ++i ) {
	   tabs.tabs[i] += qt * (i+1);
	   }
       }
    rem = tabs.space_add_rem;
    while ( rem ) {
       for ( i = tabs.tab_count-1; i >= 0; i-- ) {
	   if ( rem == 1 ) {
	      tabs.tabs[i] ++;
	      rem = 0;
	      break;
	      }
	   else {
	      tabs.tabs[i] ++;
	      rem --;
	      }
	   }
       }
    }
 else {
    tabs.space_add_qt = 0;
    tabs.space_add_rem = 0;
    }
 return( (char *)tabs.tab_count );
}
