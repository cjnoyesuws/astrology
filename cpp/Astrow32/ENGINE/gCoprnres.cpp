#include "stdafx.h"
#include "ASTRO.H"
#include "useri.h"
#include "flags.h"
#include <io.h>
#include "output.fns"
#include "textptr.h"
#include "charcons.h"
#include "dataext.h"
#include "report.h"
#include "oututil.h"
#include "outfunc.fns"
#include "paths.hpp"
#include "aspect.h"
#include "grids.h"

/* 09/15/92  Modified for C++ Windows */


#define REPORT_NAME "COMPATGRID"
#define SUMMARY_NAME "COSUMMR"

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rphs, *rpah, *rppl;
/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet. Yst is string for "Your" or "Your Companion",
   pst is the oposite, mode refers to items that will be printed out. */

int comp_print_grid_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
     char *name, char *name2, int table, int global, char *comments )
{
 COUNT i;
 ASPEC *as;
 char ps[25];
 
 if ( output_planet_sign( stream, planet, inf,
			-1, NULL, mode, name, comments, (char *)rppl ) )
    return( 1 );
 if ( mode & HOUSES ) {
    if ( output_planet_house( stream, planet, inf, name, name2, (char *)rphs ) )
       return( 1 );
 }
 fputs( "@tr\n", stream );
 return( 1 );
}

/* function to manage printing out compatibility resuts. Works much like
   print_results, but handles two sets of data */

void comp_print_grid( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
              BITS mode,  AS_INF *pa_info, BIRTH_DB *pa_data,
                           NUM house_mode, DATA_PACKET *dpk, char *comment, int type )
{
 COUNT i;
 AS_INF *inf;
 NUM maxp, file = -1, apfile = -1, k = 0;
 int table, global;
 char buf[60];
 const char *report;
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
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rppl = get_report( table, global, CH__PLANET );
 if ( rphs == NULL || rppl == NULL || rpah == NULL || ferror( stream ) ) {
    er_close2:
    close_tables( table, global );
    return;
    }
  if ( ( report = get_report( table, global, CH__COMP_REL ) ) == NULL ) {
    goto er_close2;
    }
 else
    output_title( stream, data->name, pa_data->name, comment, (char *)report );
 fprintf(stream, "@tb\x80");
 for ( i = 0, inf = inf_ptr; i <= maxp; ++i, ++inf ) {
     if ( x_kb_check() )
	   break;
     comp_print_grid_entry( stream, inf, i, mode, data->name, pa_data->name,
                                             table, global, comment );
     if ( ferror( stream ) ) {
        goto er_close2;
        }
     }
 fprintf(stream, "@tb\n\n");
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, pa_data->name, comment,
			    table, global, house_cusps, CH__HOUSE_HEAD  );
	fputs("@TB\n", stream);
    }
 if ( mode & ASPECTS ) {
	output_title( stream, data->name, pa_data->name, comment, (char *)rpah );
	AspectGridStr *pGrid = new AspectGridStr(maxp,grddp, type,mode);
    pGrid->MakeGrid(inf_ptr,maxp);
	pGrid->SaveGrid(stream);
	delete pGrid;
}
 report = tb_get_text( table, CHH_MALE,0 );
 if ( report == NULL ) {
    output_sex_codes( stream, pa_data->sex, 1, global );
    output_sex_codes( stream, data->sex, 2, global );
    }
 else {
    output_sex_codes( stream, pa_data->sex, 1, table );
    output_sex_codes( stream, data->sex, 2, table );
    }
  if ( ( report = get_report( table, global, CH__COMP_REL ) ) == NULL ) {
    er_close3:
    close_tables( table, global );
    return;
    }
 else
    output_title( stream, pa_data->name, data->name, comment, (char *)report );
 fprintf(stream,"@tb\x80");
 for ( i = 0, inf = pa_info; i <= maxp; ++i, ++inf ) {
     if ( x_kb_check() )
	break;
     comp_print_grid_entry( stream, inf, i, mode, pa_data->name, data->name,
                                         table, global, comment );
     if ( ferror( stream ) ) {
        goto er_close3;
        }
     }
 fprintf(stream,"@tb\n");
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,pa_data->name, data->name, comment,
			    table, global, alt_cusps, CH__HOUSE_HEAD  );
	fputs("@TB\n", stream);
    }
 if ( mode & ASPECTS ) {
	output_title( stream, pa_data->name, data->name, comment, (char *)rpah );
	AspectGridStr *pGrid2 = new AspectGridStr(maxp,grddp, type,mode);
    pGrid2->MakeGrid(pa_info,maxp);
	pGrid2->SaveGrid(stream);
	delete pGrid2;
}
 if ( mode & (BASE_MID|HALF_MID|FULL_MID)) {
	 fprintf( stream, "{Midpoints}\x80");
	MidpointGridStr *pmGrid = new MidpointGridStr(maxp,grddp, type,mode);
    pmGrid->MakeGrid(inf_ptr,maxp);
	pmGrid->SaveGrid(stream);
	delete pmGrid;
	if ( mode & MID_ASPECT ) {
		fprintf(stream, "\n\n{Midpoint Aspects}\x80");
		MidAspectGridStr *pmpas = new MidAspectGridStr(grddp,type,mode);
	    pmpas->MakeGrid(inf_ptr,maxp);
	    pmpas->SaveGrid(stream);
	    delete pmpas;
	   }
	fprintf(stream, "\n");
}
 close_tables( table, global );
 table = get_tables( SUMMARY_NAME, &global );
 if ( table == -1 ) {
    return;
    }
 unsigned short msk = 0xffff ^ TEXT;
 unsigned short xmd = mode & msk;
 if ( mode & SUMMARY )
    comp_print_summary(stream, xmd, table, global, data->name, pa_data->name, comment );
 close_tables( table, global );
}
