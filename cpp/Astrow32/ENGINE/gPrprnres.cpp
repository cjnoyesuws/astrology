#include "stdafx.h"
#include <io.h>
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "textptr.h"
#include "charcons.h"
#include "dataext.h"
#include "output.fns"
#include "report.h"
#include "oututil.h"
#include "outfunc.fns"
#include "datetime.fns"
#include "paths.hpp"
#include "aspect.h"
#include "Grids.h"

/* 09/15/92  Modified for C++ Windows */

#define REPORT_NAME     "PROGRESSGRID"

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas, *rpmsc, *rppah;
extern int global_table;

static int calc_new_month( DATES *birth, DATES *prog, int method )
{
 int m;
 DATES d = *birth;

 if ( method > 100 ) {
    d.year += prog->year;
    d.month += prog->month - 4;
    d.day += prog->day;
    adj_date( &d );
    return( d.month -1 );
    }
 else {
    m = prog->month;
    m -= 4;
    if ( m < 1 )
       m += 12;
    return( m-1 );
    }
}



/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet. */

int prog_print_grid_entry( FILE *stream, AS_INF *alt, NUM planet,
	BITS mode, AS_INF *inf, char *name, char *comment, int table, 
	int global  )
{
 COUNT i;
 ASPEC *as;
 static char fmt5[] = { "<%s:>\x80" };

 if ( output_planet_sign( stream, planet, inf,
			-1, NULL, mode, name, comment, (char *)rppl ) )
    return( 1 );
 if ( mode & MISCELL ) {
    if ( output_planet_sign( stream, planet, inf,
			   -1, NULL, mode, name, comment, (char *)rpmsc ) )
       return( 1 );
     }
 if ( mode & HOUSES && planet != ASCEND && planet != MED_COELI &&
	  planet != IM_COELI ) {
    if ( output_planet_house( stream, planet, inf, name, comment, (char *)rphs ) )
       return( 1 );
     }
  fputs( "@TR\n", stream );
  return( 1 );
}

/* function to print out each moon series entry. Takes pointer to block, 
and number of block entry as planet.  */

int print_moon_series_grid_entry( FILE *stream, AS_INF *pinf, NUM month,
    AS_INF *inf, BITS mode, char *name, char *comment, int table, 
	int global  )
{
 COUNT i;
 ASPEC *as;
 static char fmt5[] = { "<%s:>\x80" };

 if ( output_planet_sign( stream, MOON, inf,
        MONTH_DI, (void *)month, mode, name, comment, (char *)rppl ) )
    return( 1 );
 if ( mode & MISCELL ) {
    if ( output_planet_sign( stream, MOON, inf,
		   MONTH_DI, (void *)month, mode, name, comment, (char *)rpmsc ) )
       return( 1 );
     }
 if ( mode & HOUSES ) {
    if ( output_planet_house( stream, MOON, inf, name, comment, (char *)rphs ) )
       return( 1 );
     }
 fputs( "@TR", stream );
 return( 1 );
}


/* function to manage printing of results */

void prog_print_grid( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
	 BITS mode, NUM house_mode, DATA_PACKET *dpk, char *comment,
	 int type )
{
 COUNT i, m;
 char buf[15];
 const char *report;
 AS_INF * inf, * alt, * prgr;
 int file = -1, hsfile = -1, aspfile = -1;
 NUM maxp;
 int global, table;
 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;
 int grddp;
 if ( mode & ASTEROID )
	 grddp = HOUSE_12;
 else
	 grddp = HOUSE_12 - (HOUSE_1-CUPIDO);

 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
	 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( REPORT_NAME, &global );
 if ( table == -1 ) {
    goto er_close2;
    }
 if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    er_close2 :
    close_tables( table, global );
    return;
    }
 else
    output_title( stream, data->name, comment, "", (char *)report );
 if ( output_birth_head_group( stream, mode, data, table, house_mode,
						comment, dpk, global ) ) {
    goto er_close2;
    }
 fputs("\n\n", stream );
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rppah = get_report( table, global, CHP_ASPECT_PRHD );
 rpmsc = get_report( table, global, CH__MISC );
 if ( rppl == NULL || rphs == NULL || 
      rppah == NULL || rpah == NULL || rpmsc == NULL ) {
    er_exit:
    close_tables( table, global );
    return;
    }
 if ( ferror( stream ) ) {
    goto er_exit;
    }
  if ( ( report = get_report( table, global, CHP_PROG_NOTE ) ) == NULL ) {
    goto er_exit;
    }
 else
    output_title( stream, data->name, comment, "", (char *)report );
  fputs("@TB\x80", stream);
 for ( i = 0, inf = inf_ptr, alt = prog; i <= maxp; ++i, ++inf, ++alt ) {
     if ( x_kb_check() )
	break;
     prog_print_grid_entry( stream, alt, i, mode, inf, 
                                   data->name, comment, table, global );
     if ( ferror( stream ) ) {
        goto er_exit;
        }
     }
  fputs("@TB\n\n", stream);
  if ( mode & ASPECTS ) {
	output_title( stream, data->name, comment, "", (char *)rpah );
	AspectGridStr *pGrid = new AspectGridStr(maxp,grddp,0,mode);
    pGrid->MakeGrid(inf_ptr,maxp);
	pGrid->SaveGrid(stream);
}
  if ( ( report = get_report( table, global, CHP_MS_HEAD ) ) == NULL ) {
     goto er_exit;
     }
 else
    output_title( stream, data->name, comment, "", (char *)report );
 rppl = get_report( table, global, CHP_MS_PLANET );
 rphs = get_report( table, global, CHP_PLAN_HOUSE );
 if ( rppl == NULL || rphs == NULL ) {
    goto er_exit;
    }
 for ( i = 0, m = calc_new_month( &data->birth_data.birth_date,
	  &dpk->pdp->offset, dpk->pdp->progress_system  ), alt = moon_series, prgr = prog_moon_series;
		     i <= 15; ++i, ++alt, ++prgr, ++m ) {
     if ( x_kb_check() )
	break;
     if ( m < 0 )
	m += 11;
     if ( m > 11 )
	m = 0;
     print_moon_series_grid_entry( stream, alt, m, prgr, mode,
          data->name, comment, table, global );
     if ( ferror( stream ) ) {
        fputs("@tb\n\n", stream );
		goto er_exit;
        }
    }
 fputs("@tb\n\n", stream );
 if ( mode & ASPECTS ) {
	output_title( stream, data->name, comment, "Moon Series", (char *)rpah );
	ProgMoonAspectGridStr *pGrid2 = new ProgMoonAspectGridStr(maxp,16,0,mode);
    pGrid2->MakeGrid(moon_series,16);
	pGrid2->SaveGrid(stream);
}
 if ( mode & ASPECTS ) {
	output_title( stream, data->name, comment, "Progressed Moon Series", (char *)rpah );
	ProgMoonAspectGridStr *pGrid2 = new ProgMoonAspectGridStr(maxp,16,0,mode);
    pGrid2->MakeGrid(prog_moon_series,16);
	pGrid2->SaveGrid(stream);
}
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, comment, "",
			table, global, house_cusps, CH__HOUSE_HEAD );
	fputs("@TB\n", stream);
    out_do_house_cusps(stream,data->name, comment, "",
			table, global, alt_cusps, CHP_PRHOUSE_HEAD );
	fputs("@TB\n", stream);
    }
 close_tables( table, global );
}
