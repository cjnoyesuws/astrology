#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "textptr.h"
#include "output.fns"
#include "charcons.h"
#include "dataext.h"
#include "report.h"
#include "oututil.h"
#include "outfunc.fns"
#include "aspect.h"
#include "grids.h"

/* 09/15/92  Modified for C++ Windows */

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas;
static int signf=-1, housef=-1, aspf=-1;

extern char *enquote_strclip( char *, char * );

extern int report_table;
#define SUMMARY_NAME "SUMMARY"

/* function to print out a single aspect entry each on a single line */


/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet */

int nx_print_grid_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
     int type, char *name, char *comment  )
{
 int i;
 ASPEC *as;


 int rs =output_planet_sign( stream, planet, inf, type, (void *)planet, mode, name, comment, (char *)rppl );
 if ( rs )
    return( 1 );
 if ( mode & HOUSES ) {
    int rh= output_planet_house( stream, planet, inf, name, comment, (char *)rphs, type );
    if ( rh )
       return( 1 );
    }
 return( 0 );
}

/* function to manage printing of results */

void nx_print_grid( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
 BITS mode, NUM house_mode, int type, int maxp, DATA_PACKET *dpk, char *tps,
     char *comment)
{
 COUNT i;
 int global, table;
 const char *report;
 AS_INF *inf;
 int grddp;
 if ( mode & ASTEROID )
	 grddp = HOUSE_12;
 else
	 grddp = HOUSE_12 - (HOUSE_1-CUPIDO);
 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( tps, &global );
 if ( table == -1 )
    return;
 if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    goto er_close;
    return;
    }
 else
    output_title( stream, data->name, comment, "", (char *)report );
 report_table = table;
 if ( output_birth_head_group( stream, mode, data, table, -1,
						comment, dpk, global ) ) {
    goto er_close;
    return;
    }
 if ( ferror( stream ) ) {
    goto er_close;
    }
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 if ( rppl == NULL || rphs == NULL || rpah == NULL ) {
    er_close:
    close_tables( table, global );
    return;
    }
 fputs("@TB\x80", stream );
 for ( i = 0, inf = inf_ptr; i < maxp; ++i, ++inf ) {
     if ( x_kb_check() )
        goto er_close;
     nx_print_grid_entry( stream, inf, i, mode, type, data->name, comment );
     if ( ferror( stream ) ) {
        goto er_close;
        }
	 fputs("@TR\n",stream);
     }
 fputs("@TB\r", stream );
 if ( mode & ASPECTS ) {
	output_title( stream, data->name, comment, "", (char *)rpah );
	AspectGridStr *pGrid = new AspectGridStr(maxp,grddp, type,mode);
    pGrid->MakeGrid(inf_ptr,maxp);
	pGrid->SaveGrid(stream);
	delete pGrid;
}
 if ( mode & (BASE_MID|HALF_MID|FULL_MID)) {
	 fprintf( stream, "{Midpoints}\x80");
	MidpointGridStr *pmGrid = new MidpointGridStr(maxp,grddp, type,mode);
    pmGrid->MakeGrid(inf_ptr,maxp);
	pmGrid->SaveGrid(stream);
	delete pmGrid;
	if ( mode & MID_ASPECT ) {
	   fprintf(stream, "\n\n{Natal Midpoint Aspects}\x80");
	   MidAspectGridStr *pmpas = new MidAspectGridStr(grddp,type,mode);
	   pmpas->MakeGrid(inf_ptr,maxp);
	   pmpas->SaveGrid(stream);
	   delete pmpas;
	   fprintf(stream, "\n\n{Other Midpoint Aspects}\x80");
	   pmpas = new MidAspectGridStr(grddp,type,mode);
	   pmpas->MakeGrid(inf_ptr,maxp,0,0);
	   pmpas->SaveGrid(stream);
	   delete pmpas;
	   }
	 }
	fprintf(stream, "\n");
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, comment, "",
			    table, global, house_cusps, CH__HOUSE_HEAD );
    fputs("@TB\n", stream);
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
