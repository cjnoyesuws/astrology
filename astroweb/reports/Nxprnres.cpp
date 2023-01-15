#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "textptr.h"
#include "output.fns"
#include "charcons.h"
#include "dataext.h"
#include "report_def.h"
#include "oututil.h"
#include "outfunc.fns"
#include "aspect.h"

/* 09/15/92  Modified for C++ Windows */

/* Semi-global purely so we don't have to get these more than 1x */
static const char *rppl, *rphs, *rpah, *rpas;
static int signf=-1, housef=-1, aspf=-1;

extern char *enquote_strclip( char *, char * );

extern int report_table;

/* function to print out a single aspect entry each on a single line */

int nx_print_aspect_entry( FILE *stream, NUM planet, ASPEC *ptr, char *name, unsigned short mode, int type )
{
 int r =output_aspects( stream, name, planet, ptr, (char *)rpas, type );
 if ( mode & TEXT )
    get_transfer_text_asp( planet, ptr->planet, ptr->aspect, aspf, stream );
 return ( r );
}


int nxprint_midpoint_entry( FILE *stream, NUM planet, MIDPT *ptr,
		 BITS mode, int file, char *name, int table, int global, int type )
{
 const char *rpm;
 COUNT x;
 ASPEC *as;
 if ( ptr->total_minutes == -1 )
    return( 1 );
 rpm = get_report( table, global, CH__MID_PLANET );
 if ( rpm == NULL )
    return( 1 );
 if ( output_midpoint_sign( stream, planet, ptr, name, (char *)rpm ), type )
    return( 1 );
 if ( file != -1 ) /* show the text */
    get_transfer_text_asp( planet, ptr->second_planet, ptr->sign, file, stream );
 if ( mode & HOUSES ) {
    rpm = get_report( table, global, CH__MID_HOUSE );
    if ( rpm == NULL )
       return( 1 );
    if ( output_midpoint_house( stream, planet, ptr, name, (char *)rpm ), type )
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
	   if ( nx_print_aspect_entry( stream, planet, as, name, mode, type ) )
	      return( 1 );
	   }
       }
    fputc( '\n', stream );
    }
return( 1 );
}




/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet */

int nx_print_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode,
     int type, char *name, char *comment, int table, int global  )
{
 int i;
 ASPEC *as;
 const char *rps;
 MIDPT *mid;


 int rs =output_planet_sign( stream, planet, inf, type, (void *)planet, mode, name, comment, (char *)rppl );
 if ( mode & TEXT )
    get_transfer_text(planet, inf->sign, signf, stream );
 if ( rs )
    return( 1 );
 if ( mode & HOUSES ) {
    int rh= output_planet_house( stream, planet, inf, name, comment, (char *)rphs, type );
    if ( mode & TEXT )
	   get_transfer_text(planet,inf->house,housef,stream);
    if ( rh )
       return( 1 );
    }
 if ( output_title( stream, name, "", "", (char *)rpah ) )
    return( 1 );
 if ( inf->no_aspects > 0 ) {
    for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as )
	if ( nx_print_aspect_entry( stream, planet, as, name, mode, type ) )
	   return( 1 );
    }
 if ( inf->no_midpt > 0 ) {
     rps = get_report( table, global, CH__MIDPT_HD );
     if ( rps == NULL )
        return( 1 );
     if ( output_title( stream, name, comment, "", (char *)rps ) )
        return( 1 );
     for ( mid = inf->midptr, i = 1; i <= inf->no_midpt; ++i, ++mid )
 	nxprint_midpoint_entry( stream, planet, mid, mode, -1, name, table, global, type );
    }
 return( 0 );
}

/* function to manage printing of results */

void nx_print_results( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
 BITS mode, NUM house_mode, int type, int maxp, DATA_PACKET *dpk, char *tps,
     char *comment, char **texts )
{
 COUNT i;
 int global, table;
 const char *report;
 AS_INF *inf;

 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 table = get_tables( tps, &global );
 if ( table == -1 )
    return;
 if ( texts != NULL ) {
    signf =open_files(texts[0]);
    housef =open_files(texts[1]);
    aspf =open_asp_files(texts[2]);
    }
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
 fputs("\n\n",stream);
 rppl = get_report( table, global, CH__PLANET );
 rphs = get_report( table, global, CH__PLAN_HOUSE );
 rpah = get_report( table, global, CH__ASPECT_HD );
 rpas = get_report( table, global, CH__ASPECT );
 if ( rppl == NULL || rphs == NULL || rpas == NULL || rpah == NULL ) {
    er_close:
    close_tables( table, global );
    close_files( signf );
    close_files( housef );
    close_files_asp(aspf);
	fputs("\n\n", stream );
    return;
    }
 for ( i = 0, inf = inf_ptr; i < maxp; ++i, ++inf ) {
	 if ( !inf->calced )
		 continue;
	 if ( x_kb_check() )
        goto er_close;
     nx_print_entry( stream, inf, i, mode, type, data->name, comment, table, global );
     if ( ferror( stream ) ) {
        goto er_close;
        }
     }
 if ( mode & HOUSES )
    out_do_house_cusps(stream,data->name, comment, "",
			    table, global, house_cusps, CH__HOUSE_HEAD );
 goto er_close;
}
