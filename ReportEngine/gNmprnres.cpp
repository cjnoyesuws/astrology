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
#include "grids.h"

#define REPORT_NAME "NUMERICGRID"
#define SUMMARY_NAME    "SUMMARY"
/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas;

/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet */

int num_print_grid_entry( FILE *stream, AS_INF near *inf, NUM planet,
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
 else if ( mode & HOUSES )
    fputs("@NB|@NB", stream );
 return( 1 );
}

/* function to manage printing of results */

void num_print_grid( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
      AS_INF_EXT *aie_ptr, BITS mode, NUM house_mode, DATA_PACKET *dpk,
	char *comment, int type )
{
 COUNT i;
 int global, table;
 const char *report;
 AS_INF *inf;
 AS_INF_EXT *aiep;
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
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpas = get_report( table, global, CH__MID_ASPT );
 if ( rppl == NULL || rphs == NULL || rpas == NULL || rpah == NULL ) {
    er_close2:
    close_tables( table, global );
    return;
    }
 if ( ferror( stream ) ) {
    goto er_close2;
    }
 fprintf(stream,"@TB\x80");
 for ( i = 0, inf = inf_ptr, aiep = aie_ptr; i <= maxp; ++i, ++inf, aiep++ ) {
     if ( x_kb_check() ) {
        goto er_close2;
	}
     num_print_grid_entry( stream, inf, i, mode, aiep, data->name,
					  comment, table, global );
     if ( ferror( stream ) ) {
        goto er_close2;
        }
	 fputs("@TR\n",stream);
     }
fprintf(stream,"@tb\n\n");
if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, comment, "",
			      table, global, house_cusps, CH__HOUSE_HEAD );
    fputs("@TB\n", stream);
    }
if ( mode & ASPECTS ) {
	output_title( stream, data->name, comment, "", (char *)rpah );
	AspectGridStr *pGrid = new AspectGridStr(maxp,grddp, type,mode);
    pGrid->MakeGrid(inf_ptr,maxp);
	pGrid->SaveGrid(stream);
	delete pGrid;
}
#ifdef DELUXE
if ( mode & (BASE_MID|HALF_MID|FULL_MID)) {
	output_title( stream, data->name, comment, "", (char *)rpas );
	MidpointGridStr *pmGrid = new MidpointGridStr(maxp,grddp, type,mode);
    pmGrid->MakeGrid(inf_ptr,maxp+1);
	pmGrid->SaveGrid(stream);
	delete pmGrid;
	if ( mode & MID_ASPECT ) {
	   MidAspectGridStr *pmpas = new MidAspectGridStr(grddp,type,mode);
	   pmpas->MakeGrid(inf_ptr,maxp+1);
	   pmpas->SaveGrid(stream);
	   delete pmpas;
	   }
}
#endif
 table = get_tables( SUMMARY_NAME, &global );
 if ( table == -1 )
    return;
 unsigned short msk = 0xffff ^ TEXT;
 unsigned short xmd = mode & msk;
 if ( mode & SUMMARY )
    print_summary(stream, xmd, table, global, data->name, comment );
 close_tables( table, global );
}
