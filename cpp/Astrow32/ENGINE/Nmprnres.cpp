#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "textptr.h"
#include "output.fns"
#include "charcons.h"
#include "dataext.h"
#include "utlduad.h"
#include "report.h"
#include "oututil.h"
#include "outfunc.fns"
#include "aspect.h"

#define REPORT_NAME "NUMERIC"

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas;

/* function to print out a single aspect entry each on a single line */

int num_print_aspect_entry( FILE *stream, NUM planet, ASPEC *ptr, char *name, char *rpt )
{
 return( output_aspects( stream, name, planet, ptr, rpt ) );
}

#ifdef DELUXE
int num_print_midpoint_entry( FILE *stream, NUM planet, MIDPT *ptr,
     BITS mode, char *name, int table, int global )
{
 COUNT x;
 ASPEC *as;
 const char *rpm;

 if ( ptr->total_minutes == -1 )
    return( 0 );
 rpm = get_report( table, global, CH__MID_PLANET );
 if ( rpm == NULL )
    return( 1 );
 if ( output_midpoint_sign( stream, planet, ptr, name, (char *)rpm ) )
    return( 1 );
 if ( mode & HOUSES ) {
    rpm = get_report( table, global, CH__MID_HOUSE );
    if ( rpm == NULL )
       return( 1 );
    if ( output_midpoint_house( stream, planet, ptr, name, (char *)rpm ) )
       return( 1 );
    }
 else
    fprintf( stream, "\n" );
 if ( ptr->no_aspect > 0 ) {
    rpm = get_report( table, global, CH__MID_ASPT );
    if ( rpm == NULL )
       return( 1 );
    if ( output_title( stream, name, "", "", (char *)rpm ) )
       return( 1 );
    if ( ptr->no_aspect ) {
       rpm = get_report( table, global, CH__MID_ASPE );
       if ( rpm == NULL )
	  return( 1 );
       for ( x = 1, as = ptr->aspectr; x <= ptr->no_aspect; ++x, ++as ) {
	   if ( num_print_aspect_entry( stream, planet, as, name, (char *)rpm ) )
	      return( 1 );
	   }
       }
    fprintf( stream, "\n" );
    }
 return( 1 );
}

#endif
/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet */

int num_print_entry( FILE *stream, AS_INF near *inf, NUM planet,
     BITS mode, AS_INF_EXT *aie, char *name, char *comment, int table, int global )
{
 int i;
 MIDPT *mid;
 ASPEC *as;
 const char *rps;

 if ( output_planet_sign( stream, planet, inf,
			-1, NULL, mode, name, comment, (char *)rppl ) )
    return( 1 );
 if ( mode & EXT_CALCS ) {
    rps = get_report( table, global, CH__PLAN_EXT );
    if ( rps == NULL )
       return( 1 );
    if ( output_planet_sign_ext( stream, planet, aie, name, (char *)rps ) )
       return( 1 );
    }
 if ( mode & HOUSES && planet != ASCEND && planet != MED_COELI &&
	  planet != IM_COELI ) {
    if ( output_planet_house( stream, planet, inf, name, comment, (char *)rphs ) )
       return( 1 );
    }
 if ( inf->no_aspects > 0 ) {
    if ( output_title( stream, name, "", "", (char *)rpah ) )
       return( 1 );
    for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as )
	if ( num_print_aspect_entry( stream, planet, as, name, (char *)rpas ) )
	   return( 1 );
    }
#ifdef DELUXE 
 if ( inf->no_midpt > 0 ) {
    rps = get_report( table, global, CH__MIDPT_HD );
    if ( rps == NULL )
       return( 1 );
    if ( output_title( stream, name, comment, "", (char *)rps ) )
       return( 1 );
    for ( mid = inf->midptr, i = 1; i <= inf->no_midpt; ++i, ++mid )
	num_print_midpoint_entry( stream, planet, mid, mode, name, table, global );
    }
#endif
 return( 1 );
}

/* function to manage printing of results */

void num_print_results( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
      AS_INF_EXT *aie_ptr, BITS mode, NUM house_mode, DATA_PACKET *dpk,
	char *comment )
{
 COUNT i;
 int global, table;
 const char *report;
 AS_INF *inf;
 AS_INF_EXT *aiep;
 NUM maxp;

 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST  )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;

 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( REPORT_NAME, &global );
 if ( table == -1 )
    return;
  if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    close_tables( table, global );
    return;
    }
 else
    output_title( stream, data->name, comment, "", (char *)report );
 if ( output_birth_head_group( stream, mode, data, table, house_mode,
						comment, dpk, global ) ) {
    close_tables( table, global );
    return;
    }
 fputs("\n\n", stream );
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpas = get_report( table, global, CH__ASPECT );
 if ( rppl == NULL || rphs == NULL || rpas == NULL || rpah == NULL ) {
    er_close2:
    close_tables( table, global );
    return;
    }
 if ( ferror( stream ) ) {
    goto er_close2;
    }
 for ( i = 0, inf = inf_ptr, aiep = aie_ptr; i <= maxp; ++i, ++inf, aiep++ ) {
	 if (!inf->calced )
		 continue;
	 if ( x_kb_check() ) {
        goto er_close2;
	}
     num_print_entry( stream, inf, i, mode, aiep, data->name,
					  comment, table, global );
     if ( ferror( stream ) ) {
        goto er_close2;
        }
     }

if ( mode & HOUSES )
    out_do_house_cusps(stream,data->name, comment, "",
			      table, global, house_cusps, CH__HOUSE_HEAD );
 close_tables( table, global );
 fputs("\n\n", stream );
}
