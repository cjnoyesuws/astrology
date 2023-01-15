#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "textptr.h"
#include "output.fns"
#include "charcons.h"
#include "dataext.h"
#include "report_def.h"
#include "oututil.h"
#include "outfunc.fns"
#include "textptr.h"

/* 09/10/92  Modified for C++ Windows */

#define REPORT_NAME "HELIO"

extern int global_table;

const char *nh_pla_str( int planet )
{
if ( planet == SUN ) {
   const char *p =  tb_get_text( global_table, ST__EARTH, 0 );
   if ( p == NULL )
      return ( "Earth" );
   else
      return ( p );
   }
  else
     return( planet_str( planet ) );
}


/* function to manage printing of results */

void nh_print_results( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
    BITS mode, NUM house_mode, DATA_PACKET *dpk, char *comment )
{
 int table, global;
 COUNT i;
 const char *report;
 AS_INF *inf;

 table = get_tables( REPORT_NAME, &global );
 if ( table == -1 )
    return;
  if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_title( stream, data->name, comment, "",  (char *)report );
 if ( output_birth_head_group( stream, mode, data, table, -1,
						comment, dpk, global ) ) {
    close_tables( table, global );
    return;
    }
 if ( ferror( stream ) ) {
    close_tables( table, global );
    return;
    }
 if ( ( report = get_report( table, global, CH__PLANET ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 fputs("\n\n", stream );
 for ( i = SUN, inf = inf_ptr+SUN; i <= PLUTO; ++i, ++inf ) {
     if ( x_kb_check())
	return;
     if ( output_planet_sign( stream, i, inf,
	    HELIO_DI, (void *)i, mode, data->name, comment, (char *)report ) ) {
	close_tables( table, global );
	return;
        }
     }
 close_tables( table, global );
 fputs("\n\n", stream );
}