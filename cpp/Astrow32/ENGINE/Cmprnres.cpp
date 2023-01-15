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


/* 09/15/92  Modified for C++ Windows */

#define REPORT_NAME     "COMPOS"
#define SUMMARY_NAME    "SUMMARY"

extern void do_house_sign( DEGR minutes, int *minor, int *sign, int *cusp );

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas, *rpmsc;

/* function to print out a single aspect entry each on a single line */

int cm_print_aspect_entry( FILE *stream, NUM planet, ASPEC *ptr, int aspfil, char *rpt, char *name )
{
 int e;

 e = output_aspects( stream, name, planet, ptr, rpt );
 if ( aspfil != -1 ) /* show the text */
    get_transfer_text_asp( ptr->planet, planet, ptr->aspect, aspfil, stream );
 return( e );
}

/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet */

int cm_print_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
		    int fil, int aspfil, int hsfil, AS_INF_EXT *aie,
			   char *name, char *name2, int table, int global )
{
 static char fmt5[] = { "<%s:>\x80" };
 static char st8[] = { "\n" };
 COUNT i;
 ASPEC *as;
 const char *rps;

 if ( output_planet_sign( stream, planet, inf,
			-1, NULL, mode, name, name2, (char *)rppl ) )
    return( 1 );
 if ( mode & TEXT ) {
    if ( inf->cusp == -1 ) {
       get_transfer_text( inf->sign, planet, fil, stream );
       if ( inf->retrograde )
	  get_transfer_text( 12, planet, fil, stream );
       }
    else {
       fprintf( stream, fmt5, sign_str( inf->sign ) );
       get_transfer_text( inf->sign, planet, fil, stream );
       fprintf( stream, fmt5, sign_str( inf->cusp ) );
       get_transfer_text( inf->cusp, planet, fil, stream );
       if ( inf->retrograde )
	  get_transfer_text( 12, planet, fil, stream );
       }
    }
 if ( mode & MISCELL ) {
    if ( output_planet_sign( stream, planet, inf,
			   -1, NULL, mode, name, name2, (char *)rpmsc ) )
       return( 1 );
    if ( mode & TEXT )
       get_transfer_text( inf->sign, (inf->misc_code & 3)+29, fil, stream );
    }
 if ( mode & HOUSES && planet != ASCEND && planet != MED_COELI &&
	  planet != IM_COELI ) {
    if ( output_planet_house( stream, planet, inf, name, name2, (char *)rphs ) )
       return( 1 );
    if ( mode & TEXT )
       get_transfer_text( inf->house, planet, hsfil, stream );
    }
 if ( mode & EXT_CALCS ) {
    rps = get_report( table, global, CH__PLAN_EXT );
    if ( rps == NULL )
       return( 1 );
    if ( output_planet_sign_ext( stream, planet, aie, name, (char *)rps ) )
       return( 1 );
    }
 if ( mode & ASPECTS ) {
    if ( inf->no_aspects > 0 ) {
       if ( output_title( stream, name, name2, "", (char *)rpah ) )
	  return( 1 );
	for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as )
	  if ( cm_print_aspect_entry( stream, planet, as, ((mode & TEXT)?aspfil:-1), (char *)rpas, name ) )
	      return( 1 );
       }
    }
 fprintf( stream, st8 );
 return( 1 );
}

/* function to manage printing out compatibility resuts. Works much like
   print_results, but handles two sets of data */

static struct BIRTH_DB *pa_data;

void setup_compos( struct BIRTH_DB *_pa_data )
{
  pa_data = _pa_data;
}

void compos_print_results( FILE *stream, struct AS_INF *inf_ptr,
      struct AS_INF_EXT *aie_ptr, struct BIRTH_DB *data, unsigned short mode,
      short house_mode, struct DATA_PACKET *dpk, char *comment, int interp )
{
 COUNT i;
 AS_INF  *inf;
 AS_INF_EXT  *aiep;
 NUM maxp, file = -1, hsfile = -1, aspfile = -1;
 const char *report;
 int sign, cusp, global, table;
 static char fmt8[] = { "<%s:>\x80" };
 char rptname[25];
 strcpy( rptname, REPORT_NAME );
 if ( !interp )
	 strcat( rptname, "NUM" );
 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;

 if ( mode & TEXT ) {
    if ( mode & ASPECTS )
       aspfile = open_asp_files( CM_ASPECT_FILE );
    file = open_files( CM_PLANET_FILE );
    if ( mode & HOUSES )
       hsfile = open_files( CM_HOUSE_FILE );
    }
 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( rptname, &global );
 if ( table == -1 ) {
    er_close1:
    close_tables( table, global );
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
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
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpas = get_report( table, global, CH__ASPECT );
 rpmsc = get_report( table, global, CH__MISC );
 if ( rppl == NULL || rphs == NULL || rpas == NULL || rpah == NULL || rpmsc == NULL ) {
    er_close2:
    close_tables( table, global );
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
    return;
    }
 if ( ferror( stream ) ) {
    goto er_close2;
    }
 for ( i = 0, aiep = aie_ptr, inf = inf_ptr; i <= maxp; ++i, ++inf, ++aiep ) {
	if ( x_kb_check() )
	   break;
     cm_print_entry( stream, inf, i, mode, file, aspfile, hsfile, aiep,
	       data->name, pa_data->name, table, global );
     if ( ferror( stream ) ) {
        goto er_close2;
	}
     }
 if ( mode & TEXT ) {
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
    }
 if ( x_kb_check() )
    return;
 if ( mode & HOUSES ) {
    if ( mode & TEXT ) {
       if ( ( hsfile = open_files( SIGN_HOUSE_FILE ) ) == -1 )
	  mode &= ( 0xffff ^ TEXT );
       }
    out_do_house_cusps(stream,data->name, comment, "",
			    table, global, house_cusps, CH__HOUSE_HEAD  );
    if ( ( report = get_report( table, global, CH__HS_SGN_HED ) ) == NULL ) {
       er_close3:
       close_tables( table, global );
       close_files( hsfile );
       return;
       }
    else
       output_title( stream, data->name, comment, "", (char *)report );
    if ( ( report = get_report( table, global, CH__HOUSE_SIGN ) ) == NULL ) {
       goto er_close3;
       }
    if ( ( rphs = strdup( report )) == NULL )
       goto er_close3;
    for ( i = 1; i <= 12; ++i ) {
	if ( x_kb_check() )
	   break;
	output_house_sign( stream, i, house_cusps[i], &cusp, &sign,
							data->name, (char *)rphs );
	if ( cusp == -1 ) {
	   if ( mode & TEXT )
	      get_transfer_text( sign, i, hsfile, stream );
	   }
	else {
	   if ( mode & TEXT ) {
	      fprintf( stream, fmt8, sign_str( sign ) );
	      get_transfer_text( sign, i, hsfile, stream );
	      fprintf( stream, fmt8, sign_str( cusp ) );
	      get_transfer_text( cusp, i, hsfile, stream );
	      }
	   }
	}
     if ( mode & TEXT )
	close_files( hsfile );
     }
 if ( x_kb_check() ) {
    close_tables( table, global );
    return;
    }
 close_tables( table, global );
 table = get_tables( SUMMARY_NAME, &global );
 if ( table == -1 )
    return;
 if ( mode & SUMMARY )
    print_summary(stream, mode, table, global, data->name, comment );
 close_tables( table, global );
 fputs("\n\n", stream);
}
