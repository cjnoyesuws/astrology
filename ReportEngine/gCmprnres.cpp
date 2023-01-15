#include "stdafx.h"
#include "ASTRO.H"
#include <io.h>
#include "useri.h"
#include "flags.h"
#include "output.fns"
#include "textptr.h"
#include "charcons.h"
#include "dataext.h"
#include "utlduad.h"
#include "report.h"
#include "oututil.h"
#include "outfunc.fns"
#include "grids.h"

/* 09/15/92  Modified for C++ Windows */

#define REPORT_NAME     "COMPOSGRID"
#define SUMMARY_NAME    "SUMMARY"

extern void do_house_sign( DEGR minutes, int *minor, int *sign, int *cusp );

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas, *rpmsc;

/* function to print out a single aspect entry each on a single line */


/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet */

int cm_print_grid_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
    AS_INF_EXT *aie, char *name, char *name2, int table, int global )
{
 static char fmt5[] = { "<%s:>\x80" };
 static char st8[] = { "@TR" };
 COUNT i;
 ASPEC *as;
 const char *rps;

 if ( output_planet_sign( stream, planet, inf,
			-1, NULL, mode, name, name2, (char *)rppl ) )
    return( 1 );
 if ( mode & MISCELL ) {
    if ( output_planet_sign( stream, planet, inf,
			   -1, NULL, mode, name, name2, (char *)rpmsc ) )
       return( 1 );
    }
 if ( mode & HOUSES && planet != ASCEND && planet != MED_COELI &&
	  planet != IM_COELI ) {
    if ( output_planet_house( stream, planet, inf, name, name2, (char *)rphs ) )
       return( 1 );
     }
 if ( mode & EXT_CALCS ) {
    rps = get_report( table, global, CH__PLAN_EXT );
    if ( rps == NULL )
       return( 1 );
    if ( output_planet_sign_ext( stream, planet, aie, name, (char *)rps ) )
       return( 1 );
    }
 fprintf( stream, st8 );
 return( 1 );
}

/* function to manage printing out compatibility resuts. Works much like
   print_results, but handles two sets of data */

static struct BIRTH_DB *pa_data;

void setup_composg( struct BIRTH_DB *_pa_data )
{
  pa_data = _pa_data;
}

void compos_print_grid( FILE *stream, struct AS_INF *inf_ptr,
      struct AS_INF_EXT *aie_ptr, struct BIRTH_DB *data, unsigned short mode,
      short house_mode, struct DATA_PACKET *dpk, char *comment, int type )
{
 COUNT i;
 AS_INF  *inf;
 AS_INF_EXT  *aiep;
 NUM maxp, file = -1, hsfile = -1, aspfile = -1;
 const char *report;
 int sign, cusp, global, table;
 static char fmt8[] = { "<%s:>\x80" };
 int grddp;
  if ( mode & ASTEROID )
	 grddp = HOUSE_12;
 else
	 grddp = HOUSE_12 - (HOUSE_1-CUPIDO);
 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;

 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( REPORT_NAME, &global );
 if ( table == -1 ) {
    er_close1:
    close_tables( table, global );
    return;
    }
 if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    goto er_close1;
    }
 else
    output_title( stream, data->name, pa_data->name, comment, (char *)report );
 if ( output_comp_head_group( stream, mode, data, pa_data, table, house_mode,
					   comment, dpk, global ) ) {
    goto er_close1;
    }
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpmsc = get_report( table, global, CH__MISC );
 if ( rppl == NULL || rphs == NULL || rpah == NULL || rpmsc == NULL ) {
    er_close2:
    close_tables( table, global );
    return;
    }
 if ( ferror( stream ) ) {
    goto er_close2;
    }
 fputs("@TB\x80", stream);
 for ( i = 0, aiep = aie_ptr, inf = inf_ptr; i <= maxp; ++i, ++inf, ++aiep ) {
	if ( x_kb_check() )
	   break;
     cm_print_grid_entry( stream, inf, i, mode, aiep,
	       data->name, pa_data->name, table, global );
     if ( ferror( stream ) ) {
        goto er_close2;
	}
     }
 fputs("@TB\n\n", stream);
 if ( x_kb_check() )
    return;
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, comment, "",
			    table, global, house_cusps, CH__HOUSE_HEAD  );
 fputs("@tb\n\n", stream );
 }

	if ( mode & ASPECTS ) {
	output_title( stream, data->name, comment, "", (char *)rpah );
	AspectGridStr *pGrid = new AspectGridStr(maxp,grddp, type,mode);
    pGrid->MakeGrid(inf_ptr,maxp);
	pGrid->SaveGrid(stream);
	delete pGrid;
}
 if ( x_kb_check() ) {
    close_tables( table, global );
    return;
    }
 close_tables( table, global );
 table = get_tables( SUMMARY_NAME, &global );
 if ( table == -1 )
    return;
 unsigned short msk = 0xffff ^ TEXT;
 unsigned short xmd = mode & msk;
 if ( mode & SUMMARY )
    print_summary(stream, xmd, table, global, data->name, comment );
 close_tables( table, global );
}
