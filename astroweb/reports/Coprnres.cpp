#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
//#include <io.h>
#include "output.fns"
#include "textptr.h"
#include "charcons.h"
#include "dataext.h"
#include "report_def.h"
#include "oututil.h"
#include "outfunc.fns"
#include "paths.hpp"
#include "aspect.h"
#include <cstring>
/* 09/15/92  Modified for C++ Windows */


#define REPORT_NAME "COMPAT"
#define SUMMARY_NAME "COSUMMR"

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rphs, *rpah, *rpas;


/* function to print out a single aspect entry each on a single line */

int comp_print_aspect_entry( FILE *stream, NUM planet, ASPEC *ptr,
        char *name, char *name2, int file, char *rpt )
{
 int e;
 e = output_aspects2( stream, name, name2, planet, ptr, rpt );
 if ( file != -1 )
    get_transfer_text_asp( ptr->planet, planet, ptr->aspect, file, stream );
 return( e );
}

/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet. Yst is string for "Your" or "Your Companion",
   pst is the oposite, mode refers to items that will be printed out. */

int comp_print_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
     char *name, char *name2, int hsfil, int apfil, int table, int global )
{
 COUNT i;
 ASPEC *as;
 char ps[25];

 if ( mode & HOUSES ) {
    if ( output_planet_house( stream, planet, inf, name, name2, (char *)rphs ) )
       return( 1 );
    if ( mode & TEXT )
       get_transfer_text( inf->house-1, planet, hsfil, stream );
    }
  if ( mode & ASPECTS ) {
    if ( inf->no_aspects > 0 ) {
       if ( output_title( stream, name, name2, "", (char *)rpah ) )
	  return( 1 );
	for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as )
	  if ( comp_print_aspect_entry( stream, planet, as, name, name2, ((mode & TEXT)?apfil:-1), (char *)rpas ) )
	      return( 1 );
       }
    }
 fputc( '\n', stream );
 return( 1 );
}

/* function to manage printing out compatibility resuts. Works much like
   print_results, but handles two sets of data */

void comp_print_results( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
              BITS mode,  AS_INF *pa_info, BIRTH_DB *pa_data,
                           NUM house_mode, DATA_PACKET *dpk, char *comment, int interp )
{
 COUNT i;
 AS_INF *inf;
 NUM maxp, file = -1, apfile = -1, k = 0;
 int table, global;
 char buf[60], rptname[25];
 const char *report;

 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;

 if ( mode & TEXT ) {
    if ( ( file = open_files( COMPAT_HOUSES ) ) == -1 )
       mode &= ( 0xffff ^ TEXT );
	apfile = open_asp_files( COMPAT_ASPECTS );
    }
 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 strcpy(rptname, REPORT_NAME );
 if ( !interp )
	 strcat( rptname, "NUM");
 table = get_tables( rptname, &global );
 if ( table == -1 ) {
    er_close1:
    close_tables( table, global );
    close_files( file );
    close_files_asp( apfile );
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
 fputs("\n\n", stream );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpas = get_report( table, global, CH__ASPECT );
 if ( rphs == NULL || rpas == NULL || rpah == NULL || ferror( stream ) ) {
    er_close2:
    close_tables( table, global );
    close_files( file );
    close_files_asp( apfile );
    return;
    }
  if ( ( report = get_report( table, global, CH__COMP_REL ) ) == NULL ) {
    goto er_close2;
    }
 else
    output_title( stream, data->name, pa_data->name, comment, (char *)report );
 for ( i = 0, inf = inf_ptr; i <= maxp; ++i, ++inf ) {
     if ( x_kb_check() )
	   break;
     comp_print_entry( stream, inf, i, mode, data->name, pa_data->name,
                                            file, apfile, table, global );
     if ( ferror( stream ) ) {
        goto er_close2;
        }
     }
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, pa_data->name, comment,
			    table, global, house_cusps, CH__HOUSE_HEAD  );
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
    close_files( file );
    close_files_asp( apfile );
    return;
    }
 else
    output_title( stream, pa_data->name, data->name, comment, (char *)report );
 for ( i = 0, inf = pa_info; i <= maxp; ++i, ++inf ) {
     if ( x_kb_check() )
	break;
     comp_print_entry( stream, inf, i, mode, pa_data->name, data->name,
                                         file, apfile, table, global );
     if ( ferror( stream ) ) {
        goto er_close3;
        }
     }
 if ( mode & TEXT ) {
    close_files( file );
    close_files_asp( apfile );
    }
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,pa_data->name, data->name, comment,
			    table, global, alt_cusps, CH__HOUSE_HEAD  );
    }
 close_tables( table, global );
 table = get_tables( SUMMARY_NAME, &global );
 if ( table == -1 ) {
    return;
    }
 if ( mode & SUMMARY )
    comp_print_summary(stream, mode, table, global, data->name, pa_data->name, comment );
 close_tables( table, global );
}
