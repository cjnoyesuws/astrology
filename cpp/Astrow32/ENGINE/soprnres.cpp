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

/* 09/15/92  Modified for C++ Windows */


#define REPORT_NAME "SOLAR"

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rphs, *rpah, *rpas, *rppl, *rpmsc, *rpsasp;


int solar_text( int fl, int sfl, int k1, int k2, int k3, FILE *stream )
{
	if ( sfl == -1 ) {
	  if ( fl != -1 && k3 != -1 )
		return( get_transfer_text_asp( k1, k2, k3, fl, stream ) );
	  else
        return( get_transfer_text( k1, k2, fl, stream ) );
	}
	else {
		if ( k3 != -1 ) {
		   if (get_transfer_text_asp( k1, k2, k3, sfl, stream ))
			 return( get_transfer_text_asp( k1, k2, k3, fl, stream ) );
           else
             return( 0 );
		}
		else {
		   if (get_transfer_text( k1, k2, sfl, stream ))
			 return( get_transfer_text( k1, k2, fl, stream ) );
           else
             return( 0 );
		}

	}

}

/* function to print out a single aspect entry each on a single line */

int solar_print_aspect_entry( FILE *stream, NUM planet, ASPEC *ptr,
        char *name, int file, int sfile, char *rpt )
{
 int e;
 e = output_aspects2( stream, name, name, planet, ptr, rpt );
 if ( file != -1 )
    solar_text(file,sfile,ptr->planet, planet, ptr->aspect, stream );
 return( e );
}


int solar_print_midpoint_entry( FILE *stream, NUM planet, MIDPT *ptr,
		 BITS mode, int file, char *name, int table, int global )
{
 const char *rpm;
 COUNT x;
 ASPEC *as;
 if ( ptr->total_minutes == -1 )
    return( 1 );
 rpm = get_report( table, global, CH__MID_PLANET );
 if ( rpm == NULL )
    return( 1 );
 if ( output_midpoint_sign( stream, planet, ptr, name, (char *)rpm ) )
    return( 1 );
 if ( file != -1 ) /* show the text */
    get_transfer_text_asp( planet, ptr->second_planet, ptr->sign, file, stream );
 if ( mode & HOUSES ) {
    rpm = get_report( table, global, CH__MID_HOUSE );
    if ( rpm == NULL )
       return( 1 );
    if ( output_midpoint_house( stream, planet, ptr, name, (char *)rpm ) )
       return( 1 );
    }
 else
    fputc( '\n', stream );
 if ( ptr->no_aspect > 0 ) {
    rpm = get_report( table, global, CH__MID_ASPT );
    if ( rpm == NULL )
       return( 1 );
    if ( output_title( stream, name, "", "", (char *)rpm ) )
       return( 1 );
    if ( ptr->no_aspect ) {
       rpm = get_report( table, global, CH__MID_ASPE );
       if ( rpm == NULL )
	  return( 1 );
       for ( x = 1, as = ptr->aspectr; x <= ptr->no_aspect; ++x, ++as ) {
	   if ( solar_print_aspect_entry( stream, planet, as, name, -1, -1, (char *)rpm ) )
	      return( 1 );
	   }
       }
    fputc( '\n', stream );
    }
return( 1 );
}

/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet. Yst is string for "Your" or "Your Companion",
   pst is the oposite, mode refers to items that will be printed out. */

int solar_print_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
     char *name, int fil, int sfil, int hsfil, int apfil, int shsfil, int sapfile,
	 int table, int global, char *aprep, char *which)
{
 COUNT i;
 ASPEC *as;
 MIDPT *mid;
 char ps[25];
 const char *rps;
 static char fmt5[] = { "<%s:>\x80" };

 if ( output_planet_sign( stream, planet, inf,
			-1, NULL, mode, name, which, (char *)rppl ) )
    return( 1 );
 if ( mode & TEXT ) {
    if ( inf->cusp == -1 ) {
       solar_text( fil, sfil, inf->sign, planet, -1, stream );
       if ( inf->retrograde )
	   solar_text( fil, sfil, 12, planet, -1, stream );
       }
    else {
       fprintf( stream, (char *)fmt5, sign_str( inf->sign ) );
       solar_text( fil, sfil, inf->sign, planet, -1, stream );
       fprintf( stream, (char *)fmt5, sign_str( inf->cusp ) );
       solar_text( fil, sfil, inf->cusp, planet, -1, stream );
       if ( inf->retrograde )
	     solar_text( fil, sfil, 12, planet, -1, stream );
       }
    }
 if ( mode & MISCELL ) {
    if ( output_planet_sign( stream, planet, inf,
			   -1, NULL, mode, name, name, (char *)rpmsc ) )
       return( 1 );
    if ( mode & TEXT )
       solar_text( fil, sfil,inf->sign, (inf->misc_code & 3)+29, -1, stream );
    }
 if ( mode & HOUSES ) {
    if ( output_planet_house( stream, planet, inf, name, name, (char *)rphs ) )
       return( 1 );
    if ( mode & TEXT )
       solar_text( hsfil, shsfil, inf->house-1, planet, -1, stream );
    }
  if ( mode & ASPECTS ) {
    if ( inf->no_aspects > 0 ) {
       if ( output_title( stream, name, name, which, (char *)rpah ) )
	  return( 1 );
	for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as )
	  if ( solar_print_aspect_entry( stream, planet, as, name, apfil, sapfile, aprep ) )
	      return( 1 );
       }
    }
  if ( inf->no_midpt > 0 ) {
      rps = get_report( table, global, CH__MIDPT_HD );
      if ( rps == NULL )
         return( 1 );
      if ( output_title( stream, name, "", "", (char *)rps ) )
         return( 1 );
      for ( mid = inf->midptr, i = 1; i <= inf->no_midpt; ++i, ++mid )
  	solar_print_midpoint_entry( stream, planet, mid, mode, -1, name, table, global );
    }
 fputc( '\n', stream );
 return( 1 );
}

/* function to manage printing out compatibility resuts. Works much like
   print_results, but handles two sets of data */

void solar_print_results( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
              BITS mode,  AS_INF *sinfo,
                           NUM house_mode, DATA_PACKET *dpk, char *comment, int interp )
{
 COUNT i;
 AS_INF *inf, *sinf;
 NUM maxp, pfile = -1, hfile = -1, apfile = -1, spfile=-1, shfile=-1, sapfile=-1, k = 0;
 int table, global;
 char buf[60], rptname[25];
 const char *report;
 const char *rpshd, *rpsrad;
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
      sapfile = open_asp_files( ASPECT_FILE );
    pfile = open_files( PLANET_FILE );
    if ( mode & HOUSES )
       hfile = open_files( HOUSE_FILE );
    if ( mode & ASPECTS )
       sapfile = open_asp_files( SOLAR_ASPECT );
    spfile = open_files( SOLAR_PLANET );
    if ( mode & HOUSES )
       shfile = open_files( SOLAR_HOUSE );

 }
 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( rptname, &global );
 if ( table == -1 ) {
    er_close1:
    close_tables( table, global );
    close_files( pfile );
    close_files( hfile );
	close_files_asp( apfile );
	close_files( spfile );
    close_files( shfile );
	close_files_asp( sapfile );
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
 fputs("\n\n", stream );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpas = get_report( table, global, CH__ASPECT );
 rppl = get_report( table, global, CH__PLANET );
 rpmsc = get_report( table, global, CH__MISC );
 //rpshd = get_report( table, global, CHSO_HEAD );
// rpsrad = get_report( table, global, CHSO_RADIX );
 rpsasp = get_report( table, global, CHSO_ASPECT );
 if ( rphs == NULL || rpas == NULL || rpah == NULL || rppl==NULL || rpmsc==NULL || ferror( stream ) ) {
    er_close2:
    close_tables( table, global );
    close_files( pfile );
    close_files_asp( apfile );
    close_files( spfile );
    close_files( shfile );
	close_files_asp( sapfile );
	return;
    }
  for ( i = 0, inf = inf_ptr, sinf = sinfo; i <= maxp; ++i, ++inf, ++sinf ) {
	  if ( !inf->calced )
		  continue;
	  if ( x_kb_check() )
	   break;
     //output_title( stream, data->name, data->name, comment, (char *)rppl );
	 solar_print_entry( stream, inf, i, mode, data->name, pfile, -1, hfile, apfile, -1,-1, table, global, (char *)rpas, "Birth" );
     //output_title( stream, data->name, data->name, comment, (char *)rppl );
	 //output_title( stream, data->name, data->name, comment, (char *)rpshd );
	 solar_print_entry( stream, sinf, i, mode, "Solar Directed", pfile, spfile, hfile, apfile, shfile, sapfile, table, global, (char *)rpsasp, "Solar Directed" );
     if ( ferror( stream ) ) {
        goto er_close2;
        }
     }
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream,data->name, data->name, comment,
			    table, global, house_cusps, CH__HOUSE_HEAD  );
    }
 if ( mode & TEXT ) {
    close_tables( table, global );
    close_files( pfile );
    close_files_asp( apfile );
	close_files( spfile );
    close_files( shfile );
	close_files_asp( sapfile );
	}
  close_tables( table, global );
  fputs("\n\n", stream );
 }
