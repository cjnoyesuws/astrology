#include "stdafx.h"
#include "ASTRO.H"
#include "useri.h"
#include "flags.h"
#include <io.h>
#include "output.fns"
#include "textptr.h"
#include "charcons.h"
#include "dataext.h"
#include "report_def.h"
#include "oututil.h"
#include "outfunc.fns"
#include "paths.hpp"
#include "aspect.h"
#include "grids.h"
/* 09/15/92  Modified for C++ Windows */


#define REPORT_NAME "HARMONICGRID"

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rphs, *rpah, *rpas, *rppl, *rpmsc, rpsasp;


/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet. Yst is string for "Your" or "Your Companion",
   pst is the oposite, mode refers to items that will be printed out. */

int harmonic_print_grid_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
     char *name, int table, int global )
{
 COUNT i;
 ASPEC *as;
 char ps[25];
 static char fmt5[] = { "<%s:>\x80" };

 if ( output_planet_sign( stream, planet, inf,
			-1, NULL, mode, name, "", (char *)rppl ) )
    return( 1 );

 if ( mode & MISCELL ) {
    if ( output_planet_sign( stream, planet, inf,
			   -1, NULL, mode, name, name, (char *)rpmsc ) )
       return( 1 );
       }
 if ( mode & HOUSES ) {
    if ( output_planet_house( stream, planet, inf, name, name, (char *)rphs ) )
       return( 1 );
      }

 fputs( "@tr\n", stream );
 return( 1 );
}

/* function to manage printing out compatibility resuts. Works much like
   print_results, but handles two sets of data */

void harmonic_print_grid( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
              BITS mode,  AS_INF *hinfo, int type,
                           NUM house_mode, DATA_PACKET *dpk, char *comment )
{
 COUNT i;
 AS_INF *inf, *hinf;
 NUM maxp, pfile = -1, hfile = -1, apfile = -1, k = 0;
 int table, global;
 char buf[60];
 const char *report;
 const char *rpshd, *rpsrad;
 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST )
    maxp = EAST_POINT;
 else
    maxp = SOUTH_NODE;
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
    er_close1:
    close_tables( table, global );
	return;
    }
 if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    goto er_close1;
    }
 else
    output_title( stream, data->name, data->name, comment, (char *)report );
 if ( output_birth_head_group( stream, mode, data, table, house_mode,
					   comment, dpk, global ) ) {
    goto er_close1;
    }
 rpshd = get_report( table, global, CH__HARMONIC );
 if ( rpshd == NULL )
	 goto er_close1;
 output_birth_header( stream, mode, data,
		 data->name, house_mode, dpk, (char *)rpshd  );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rppl = get_report( table, global, CH__PLANET );
 rpmsc = get_report( table, global, CH__MISC );
 if ( rphs == NULL  || rpah == NULL || rppl==NULL || rpmsc==NULL || ferror( stream ) ) {
    er_close2:
    close_tables( table, global );
    return;
    }
  fputs("[NATAL POSITIONS]@TB\x80", stream);
  for ( i = 0, inf = inf_ptr; i <= maxp; ++i, ++inf ) {
     if ( x_kb_check() )
	   break;
	 harmonic_print_grid_entry( stream, inf, i, mode, "Natal", table, global);
     if ( ferror( stream ) ) {
        goto er_close2;
        }
     }
  fputs("@TB\n\n", stream );
  if ( mode & ASPECTS ) {
	output_title( stream, data->name, "Natal", comment, (char *)rpah );
	AspectGridStr *pGrid = new AspectGridStr(maxp,grddp, type,mode);
    pGrid->MakeGrid(inf_ptr,maxp);
	pGrid->SaveGrid(stream);
	delete pGrid;
}
  fputs("[HARMONIC POSITIONS]", stream);
  fputs("@TB\x80", stream );
  for ( i = 0, hinf = hinfo; i <= maxp; ++i, ++hinf ) {
     if ( x_kb_check() )
	   break;
	 harmonic_print_grid_entry( stream, hinf, i, mode, "Harmonic", table, global);
     if ( ferror( stream ) ) {
        goto er_close2;
        }
     }
 fputs("@TB\n\n", stream );
 if ( mode & ASPECTS ) {
	output_title( stream, data->name, "Harmonic", comment, (char *)rpah );
	AspectGridStr *pGrid2 = new AspectGridStr(maxp,grddp, type,mode);
    pGrid2->MakeGrid(hinfo,maxp);
	pGrid2->SaveGrid(stream);
	delete pGrid2;
}
 if ( mode & (BASE_MID|HALF_MID|FULL_MID)) {
	fprintf( stream, "\n{Midpoints}\x80");
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
	fprintf(stream, "\n");
}
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, data->name, comment,
			    table, global, house_cusps, CH__HOUSE_HEAD  );
	fputs("@TB\n", stream);
    }
 if ( mode & TEXT ) {
    close_tables( table, global );
	}
  close_tables( table, global );
 }
