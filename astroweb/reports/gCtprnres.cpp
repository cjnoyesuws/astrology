#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "output.fns"
#include "textptr.h"
#include "dataext.h"
#include "report_def.h"
#include "oututil.h"
#include "outfunc.fns"
#include "aspect.h"
//#include "grids.h"
/* 09/15/92  Modified for C++ Windows */

#define REPORT_NAME     "COTRANSGRID"

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas, *rppah, *rpid;

extern int report_table;
static int ep;

/* file to print out composite transits */
static const char *affect_str( int house )
{
 const char *p = tb_get_text( report_table, TR__AFFECTS, house - 1 );
 if ( p == NULL )
    return( "" );
 else
    return( p );
}


/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet. */

int cmtrans_print_grid_entry( FILE *stream, AS_INF *inf, NUM planet,
    BITS mode, int tno, AS_INF *old, DATES *dp,
                       char *name, char *comment, int table, int global )
{
 COUNT i, rx;
 ASPEC *as;

  if ( output_planet_sign( stream, planet, inf,
		DATES_DP, dp, mode, name, comment, (char *)rppl ) )
    return( 1 );
 if ( mode & HOUSES ) {
    if ( output_planet_house( stream, planet, inf, name, comment, (char *)rphs ) )
       return( 1 );

    }
 fputs( "@tr\n", stream );
 return( 0 );
}



/* function to manage printing out Transits resuts. Works much like
   print_results, but handles two sets of data */

void cmtrans_print_grid( FILE *stream, AS_INF *inf_ptr, int type,
	BIRTH_DB *data, BIRTH_DB *pa_data, BITS mode, AS_INF *tr_info,
	BIRTH_DB *tr_data, NUM house_mode, DATA_PACKET *dpk, char *comment )
{
 const char *report;
 COUNT i, trn;
 AS_INF *inf, **ip, *oldi;
 DATES *dp;
 int file = -1, asfile = -1, k = 0, table, global, sp = SUN;
 NUM maxp, grddp;

 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST  )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;
 if ( mode & ASTEROID )
	 grddp = HOUSE_12;
 else
	 grddp = HOUSE_12 - (HOUSE_1-CUPIDO);
 if ( mode & ASTEROID )
	 ep = CHIRON;
 else
    ep = SOUTH_NODE;
 table = get_tables( REPORT_NAME, &global );
 if ( table == -1 )
    return;
 report_table = table;
 if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    er_close1:
    close_tables( table, global );
    return;
    }
 else
    output_title( stream, data->name, pa_data->name, comment, (char *)report );
 if ( output_comp_head_group( stream, mode, data, pa_data, table, house_mode,
					   comment, dpk, global ) )
    goto er_close1;
 if ( output_trans_head_group( stream, mode, tr_data, pa_data->name,
           table, house_mode, data->name, dpk, global ) )
     goto er_close1;

 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpid = get_report( table, global, CHT_TRANS_ID );
 if ( rppl == NULL || rphs == NULL || rpah == NULL
      || rpid == NULL || ferror( stream ) ) {
    er_close2:
    close_tables( table, global );
    return;
    }
 if ( ferror( stream ) )
    goto er_close2;
 ep = dpk->tdp->end_planet;
 oldi = NULL;
 for ( trn = 1, ip = trans_ptr, dp = date_ptr;
	 trn <= dpk->tdp->num_transits; trn++, dp++, ip++ )  {
     if ( x_kb_check() )
	break;
     if ( trn > 1 ) {
	sp = dpk->tdp->start_planet;
	ep = dpk->tdp->end_planet;
	}
     if ( output_trans_id( stream, trn, dp,
		       data->name, comment, (char *)rpid ) )
        goto er_close2;
	 fputs("@TB\x80", stream );
     for ( i = sp, inf = *ip;
			 i <= ep; i++, inf++ ) {
	 if ( x_kb_check() )
	    break;

	 cmtrans_print_grid_entry( stream, inf, i, mode, trn, oldi,
                    dp, data->name, comment, table, global );
	 if ( ferror( stream ) )
            goto er_close2;
     }
  fputs( "@TB\n\n", stream );
  if ( mode & ASPECTS ) {
	output_title( stream, data->name, comment, "", (char *)rpah );
	AspectGridStr *pGrid = new AspectGridStr(maxp,grddp, type,mode);
    pGrid->MakeGrid(*ip,ep-sp,sp);
	pGrid->SaveGrid(stream);
	delete pGrid;
    }
  }

 if ( mode & HOUSES ) {
    out_do_house_cusps(stream, data->name, comment, "",
		table, global, house_cusps, CH__HOUSE_HEAD );
	fputs("@TB\n", stream);
    }
 close_tables( table, global );
}
