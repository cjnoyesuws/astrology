#include "stdafx.h"
#include <io.h>
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "textptr.h"
#include "charcons.h"
#include "dataext.h"
#include "output.fns"
#include "report_def.h"
#include "oututil.h"
#include "outfunc.fns"
#include "datetime.fns"
#include "paths.hpp"
#include "aspect.h"

/* 09/15/92  Modified for C++ Windows */
extern char *sign_rulers;
#define REPORT_NAME     "PROGRESS"

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
	m = birth->month;
	m += prog->month;
    m -= 4;
    if ( m < 1 )
       m += 12;
	if ( m > 11 )
		m -= 12;
    return( m-1 );
    }
}

/* functions to do basic printing of results to screen/file */


/* function to print out a single aspect entry each on a single line */

int prog_print_aspect_entry( FILE *stream, NUM planet,
            ASPEC *ptr, int aspfil, char *name, int na_pr, char *rpt )
{
 int e, p = planet;

 if ( planet && !na_pr )
    p = -planet;
 else if ( !planet && !na_pr )
    p = -100;
 e = output_aspects( stream, name,p, ptr, rpt );
 if ( aspfil != -1 ) { /* show the text */
    if ( get_transfer_text_asp( ptr->planet, planet, ptr->aspect, aspfil, stream ) )
       get_transfer_text_asp( planet, ptr->planet, ptr->aspect, aspfil, stream );
    }
 return( e );
}

/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet. */

int prog_print_entry( FILE *stream, AS_INF *alt, NUM planet,
	BITS mode, AS_INF *inf, int fil, int hsfil, int aspfil,
                   char *name, char *comment, int table, int global  )
{
 COUNT i, ruler;
 ASPEC *as;
 static char fmt5[] = { "<%s:>\x80" };

 if ( output_planet_sign( stream, planet, inf,
			-1, NULL, mode, name, comment, (char *)rppl ) )
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
			   -1, NULL, mode, name, comment, (char *)rpmsc ) )
       return( 1 );
    if ( mode & TEXT )
       get_transfer_text( inf->sign, (inf->misc_code & 3)+29, fil, stream );
    }
 if ( mode & HOUSES && planet != ASCEND && planet != MED_COELI &&
	  planet != IM_COELI ) {
    if ( output_planet_house( stream, planet, inf, name, comment, (char *)rphs ) )
       return( 1 );
    if ( mode & TEXT )
       get_transfer_text( inf->house, planet, hsfil, stream );
    }
 if ( mode & ASPECTS ) {
    if ( inf->no_aspects > 0 ) {
       if ( output_title( stream, name, comment, "", (char *)rpah ) )
	  return( 1 );
       for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as )
	   if ( prog_print_aspect_entry( stream, planet, as, ((mode & TEXT)?aspfil:-1), name, 1,  (char *)rpas ) )
	      return( 1 );
       }
    if ( alt->no_aspects > 0 ) {
       if ( output_title( stream, name, comment, "", (char *)rppah ) )
	  return( 1 );
       for ( as = alt->aspectr, i = 1; i <= alt->no_aspects; ++i, ++as )
	   if ( prog_print_aspect_entry( stream, planet, as, ((mode & TEXT)?aspfil:-1), name, 0, (char *)rpas ) )
	      return( 1 );
       }
    }
  fputc( '\n', stream );
  return( 1 );
}

/* function to print out each moon series entry. Takes pointer to block,
and number of block entry as planet.  */

int print_moon_series_entry( FILE *stream, AS_INF *pinf, NUM month,
    AS_INF *inf, BITS mode, int fil, int hsfil, int aspfil,
                   char *name, char *comment, int table, int global )
{
 COUNT i;
 ASPEC *as;
 static char fmt5[] = { "<%s:>\x80" };

 if ( output_planet_sign( stream, MOON, inf,
        MONTH_DI, (void *)month, mode, name, comment, (char *)rppl ) )
    return( 1 );
 if ( mode & TEXT ) {
    if ( inf->cusp == -1 ) {
       get_transfer_text( inf->sign, MOON, fil, stream );
       }
    else {
       fprintf( stream, fmt5, sign_str( inf->sign ) );
       get_transfer_text( inf->sign, MOON, fil, stream );
       fprintf( stream, fmt5, sign_str( inf->cusp ) );
       get_transfer_text( inf->cusp, MOON, fil, stream );
       }
    }
 if ( mode & MISCELL ) {
    if ( output_planet_sign( stream, MOON, inf,
		   MONTH_DI, (void *)month, mode, name, comment, (char *)rpmsc ) )
       return( 1 );
    if ( mode & TEXT )
       get_transfer_text( inf->sign, (inf->misc_code & 3)+29, fil, stream );
    }
 if ( mode & HOUSES ) {
    if ( output_planet_house( stream, MOON, inf, name, comment, (char *)rphs ) )
       return( 1 );
    if ( mode & TEXT )
       get_transfer_text( inf->house, MOON, hsfil, stream );
    }
 if ( mode & ASPECTS ) {
    if ( inf->no_aspects > 0 ) {
       if ( output_title( stream, name, comment, "", (char *)rpah ) )
	  return( 1 );
       for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as )
	   if ( prog_print_aspect_entry( stream, MOON, as, ((mode & TEXT)?aspfil:-1), name, 1,  (char *)rpas ) )
	      return( 1 );
       }
    if ( pinf->no_aspects > 0 ) {
       if ( output_title( stream, name, comment, "", (char *)rppah ) )
	  return( 1 );
       for ( as = pinf->aspectr, i = 1; i <= pinf->no_aspects; ++i, ++as )
	   if ( prog_print_aspect_entry( stream, MOON, as, ((mode & TEXT)?aspfil:-1), name, 0, (char *)rpas ) )
	      return( 1 );
       }
    }
 fputc( '\n', stream );
 return( 1 );
}


/* function to manage printing of results */

void prog_print_results( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
	  BITS mode, NUM house_mode, DATA_PACKET *dpk, char *comment, int interp  )
{
 COUNT i, m;
 char buf[15], rptname[30];;
 const char *report;
 AS_INF * inf, * alt, * prgr;
 int file = -1, hsfile = -1, aspfile = -1;
 NUM maxp;
 //extern FILE *teststream;
 int global, table;
 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;
 strcpy( rptname, REPORT_NAME );
 if ( !interp )
	 strcat( rptname, "NUM");
 if ( mode & TEXT ) {
    if ( mode & ASPECTS )
	   aspfile = open_asp_files( PROGRESS_ASPECTS );
    file = open_files( PLANET_FILE );
    if ( mode & HOUSES )
	   hsfile = open_files( HOUSE_FILE );
    }

 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
	 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( rptname, &global );
 if ( table == -1 ) {
    goto er_close2;
    }
 if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    er_close2 :
    close_tables( table, global );
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
    return;
    }
 else
    output_title( stream, data->name, comment, "", (char *)report );
 if ( output_birth_head_group( stream, mode, data, table, house_mode,
						comment, dpk, global ) ) {
    goto er_close2;
    }
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rppah = get_report( table, global, CHP_ASPECT_PRHD );
 rpas = get_report( table, global, CH__ASPECT );
 rpmsc = get_report( table, global, CH__MISC );
 if ( rppl == NULL || rphs == NULL || rpas == NULL ||
      rppah == NULL || rpah == NULL || rpmsc == NULL ) {
    er_exit:
    close_tables( table, global );
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
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
 //fputs("1",teststream);
 for ( i = 0, inf = inf_ptr, alt = prog; i < maxp; ++i, ++inf, ++alt ) {
	 if ( !inf->calced )
		 continue;
	 if ( x_kb_check() )
	break;
    //fputs("e",teststream);
	prog_print_entry( stream, alt, i, mode, inf, file, hsfile, aspfile,
                                   data->name, comment, table, global );
     if ( ferror( stream ) ) {
        goto er_exit;
        }
     }
  if ( ( report = get_report( table, global, CHP_MS_HEAD ) ) == NULL ) {
     goto er_exit;
     }
 else
    output_title( stream, data->name, comment, "", (char *)report );
 rppl = get_report( table, global, CHP_MS_PLANET );
 rphs = get_report( table, global, CHP_PLAN_HOUSE );
 //fputs("2",teststream);
 if ( rppl == NULL || rphs == NULL ) {
    goto er_exit;
    }
 for ( i = 0, m = calc_new_month( &data->birth_data.birth_date,
	  &dpk->pdp->offset, dpk->pdp->progress_system  ), alt = moon_series, prgr = prog_moon_series;
		     i <= 15; ++i, ++alt, ++prgr, ++m ) {

	if ( x_kb_check() )
	break;
     if ( m < 0 )
	m += 12;
     if ( m > 11 )
	m = 0;
    //fputs("m",teststream);
	print_moon_series_entry( stream, prgr, m, alt, mode, file,
                  hsfile, aspfile, data->name, comment, table, global );
     if ( ferror( stream ) ) {
        goto er_exit;
        }
    }
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, comment, "",
			table, global, house_cusps, CH__HOUSE_HEAD );
    fputc( '\n', stream );
    out_do_house_cusps(stream,data->name, comment, "",
			table, global, alt_cusps, CHP_PRHOUSE_HEAD );
    }
 if ( mode & TEXT ) {
    close_files( file );
    close_files_asp( aspfile );
    close_files( hsfile );
    }
 close_tables( table, global );
 fputs("\n\n", stream );
}
