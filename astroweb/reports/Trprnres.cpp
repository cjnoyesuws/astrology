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
#include "textptr.h"

#ifdef _QDTRAN_
int report_table= -1;
#endif

/* 09/15/92  Modified for C++ Windows */

#define REPORT_NAME     "TRANSITR"

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas, *rppah, *rpid;
extern int report_table;

static int ep;
/* file to print out transits */

/* function to return a pointer to a string showing the affect of
   a certain house. */

#define N_AFFECT 13

static const char *affect_str( int house )
{
  return( tb_get_text( report_table,  TR__AFFECTS, house - 1 ) );
}

/* function to verify if an aspect exists in an array of aspects */

static int aspect_exist( ASPEC *ap, ASPEC *list, int count )
{
 int i;
 ASPEC *p = list;

 if ( !count )
    return( 0 );
 for ( i = 0; i < count; i++, p++ ) {
     if ( p->aspect == ap->aspect && p->planet == ap->planet )
	return( 1 );
     }
 return( 0 );
}

int mapAspect(int a)
{
 int map[] = { OPPOSITION, TRINE, SEXTILE, CONJUNCT, SQUARED };

 if ( a < 5 )
    return( map[a] );
 else
    return( a );
}

/* function to print out a single aspect entry each on a single line */

int trans_print_aspect_entry( FILE *stream, NUM planet, ASPEC *ptr, int file, int text, char *name, char *rpt, int interp )
{
 int e, r;
 e = output_aspects( stream, name, planet, ptr, rpt );
 if ( file != -1 && !text ) { /* mode & TEXT */
    r = 0;
    if ( get_transfer_text_asp( planet, ptr->planet, ptr->aspect, file, stream ) )
       r = get_transfer_text_asp( ptr->planet, planet, ptr->aspect, file, stream );
    if ( r && (planet == IM_COELI || planet == SOUTH_NODE) )
       r = get_transfer_text_asp( planet-1, ptr->planet, mapAspect(ptr->aspect), file, stream );
    else if ( r && (ptr->planet == IM_COELI || ptr->planet == SOUTH_NODE) )
       r = get_transfer_text_asp( ptr->planet-1, planet, mapAspect(ptr->aspect), file, stream );
    if ( r && (planet == IM_COELI || planet == SOUTH_NODE) && interp )
       fprintf( stream, "<See Prior Planet For Aspect Text...>\n" );
    else if ( r && (ptr->planet == IM_COELI || ptr->planet == SOUTH_NODE) && interp )
       fprintf( stream, "<See Prior Aspect For Text...>\n" );
    }
 else if ( text )
    fprintf( stream, "...\n" );
 return( e );
}

/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet. */

int trans_print_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
     int file, int asfile, int tno, AS_INF *old, DATES *dp, char *name,
                         char *comment, int table, int global, int interp )
{
 COUNT i, rx;
 ASPEC *as;

 if ( output_planet_sign( stream, planet, inf,
		DATES_DP, dp, mode, name, comment, (char *)rppl ) )
    return( 1 );
 if ( old == NULL )
    get_transfer_text( 12, planet, file, stream );
 fputc( '\n', stream );
 if ( mode & HOUSES ) {
    if ( output_planet_house( stream, planet, inf, name, comment, (char *)rphs ) )
       return( 1 );
    if ( old == NULL || ( old != NULL && old->house != inf->house) ) {
       if ( mode & TEXT ) {
	  rx = get_transfer_text( inf->house-1, planet, file, stream );
	  if ( rx ) {
	     fprintf( stream, affect_str( inf->house ) );
	     fputc( '\n', stream );
	     }
	  }
       }
    else if ( interp && old != NULL && old->house == inf->house )
       fprintf( stream, "...\n" );
    else
       fputc( '\n', stream );
    }
 if ( mode & ASPECTS ) {
    if ( inf->no_aspects > 0 ) {
       if ( output_title( stream, name, comment, "", (char *)rpah ) )
	  return( 1 );
       for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as ) {
           trans_print_aspect_entry( stream, planet, as,
	       ((mode & TEXT)?asfile:-1), (old == NULL ? 0 :
	       aspect_exist( as, old->aspectr, old->no_aspects ) ), name, (char *)rpas, interp ) ;
           }
       }
    }
 fputc( '\n', stream );
 return( 0 );
}

/* function to manage printing out Transits resuts. Works much like
   print_results, but handles two sets of data */

void trans_print_results( FILE *stream, AS_INF *inf_ptr,
	BIRTH_DB *data, BITS mode, AS_INF *tr_info,
	BIRTH_DB *tr_data, NUM house_mode, DATA_PACKET *dpk, char *comment, int interp )
{
 const char *report;
 COUNT i, trn, maxp, sp, ep;
 AS_INF *inf, **ip, *oldi;
 DATES *dp;
 int file = -1, asfile = -1, k = 0, global, table;
 char rptname[25];
 if ( mode & ASTEROID )
	 maxp = CHIRON;
 if ( mode & VERT_EAST && !(mode & NOBIRTHTIM) )
    maxp = EAST_POINT;
 else if ( !(mode & NOBIRTHTIM) )
    maxp = PART_FORTU;
 else
    maxp = SOUTH_NODE;
 if ( mode & TEXT ) {
    file = open_files(TRANSITS_HOUSES );
    asfile = open_asp_files( TRANSITS_ASPECTS );
    }
 strcpy(rptname, REPORT_NAME );
 if ( !interp )
	 strcat( rptname, "NUM");
 table = get_tables( rptname, &global );
 if ( table == -1 )
    return;
 report_table = table;
 if ( ( report = get_report( table, global, CHH_TITLE ) ) == NULL ) {
    er_close1:
    close_files( file );
    close_files_asp( asfile );
    close_tables( table, global );
    return;
    }
 else
    output_title( stream, data->name, tr_data->name, comment, (char *)report );
 if ( output_birth_head_group( stream, mode, data, table, house_mode,
						comment, dpk, global ) ) {
    goto er_close1;
    }
 if ( output_trans_head_group( stream, mode, tr_data, comment,
           table, house_mode, data->name, dpk, global ) )
    goto er_close1;
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpas = get_report( table, global, CH__ASPECT );
 rpid = get_report( table, global, CHT_TRANS_ID );
 if ( rppl == NULL || rphs == NULL || rpas == NULL || rpah == NULL
      || rpid == NULL || ferror( stream ) ) {
    er_close2:
    close_tables( table, global );
    close_files( file );
    close_files_asp( asfile );
    close_files( file );
    //close_files( asfile );
    return;
    }
  fputs("\n\n", stream );
  if ( ( report = get_report( table, global, CHT_TRANS_NOTE ) ) == NULL ) {
     goto er_close2;
     }
 else
    output_title( stream, data->name, comment, "", (char *)report );

 if ( ferror( stream ) ) {
    goto er_close1;
    }
 oldi = NULL;
 sp = dpk->tdp->start_planet;
 ep = dpk->tdp->end_planet;
 if ( ep > maxp )
	 ep = maxp;
 for ( trn = 1, ip = trans_ptr, dp = date_ptr;
	 trn <= dpk->tdp->num_transits; trn++, dp++, ip++ )  {
     if ( x_kb_check() )
	break;
     if ( trn > 1 ) {
	sp = dpk->tdp->start_planet;
	ep = dpk->tdp->end_planet;
	if ( ep > maxp )
	   ep = maxp;
	}
     if ( output_trans_id( stream, trn, dp,
				       data->name, comment, (char *)rpid ) ) {
        goto er_close1;
        }
     fputs("\n\n", stream );
     for ( i = sp, inf = *ip;
			 i <= ep; i++, inf++ ) {
	 if ( x_kb_check() )
	    break;
	 if ( !inf->calced )
		 continue;
	 if ( trans_print_entry( stream, inf, i, mode, file, asfile, trn, oldi,
            dp, data->name, comment, table, global, interp  ) ) {
            goto er_close1;
            }
	 if ( oldi != NULL )
	    oldi++;
         }
     oldi = *ip;
     }
 if ( mode & TEXT ) {
    close_files( file );
    close_files_asp( asfile );
    }
 if ( mode & HOUSES ) {
    out_do_house_cusps(stream, data->name, comment, "",
		table, global, house_cusps, CH__HOUSE_HEAD );
    }
 fputs("\n\n", stream);
 close_tables( table, global );
}
