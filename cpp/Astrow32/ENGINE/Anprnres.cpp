#error "don't use ANPRNRES"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "textptr.h"
#include "output.fns"
#include "charcons.h"
#include "basedcs.h"
#include "dataext.h"
#include <cscape.h>
#include <scancode.h>

#include <conio.h>
#define x_kb_Check() kbhit()


char *alt_num_ps_str( int plan )
{


}


extern char *strclip( char * );

/* function to print out a single aspect entry each on a single line */

void alt_num_print_aspect_entry( FILE *stream, NUM planet, ASPEC *ptr )
{
 static char BCS fmt[] = { "%-14.14s |%-22.22s |Orb: %d.\n" };

 fprintf( stream, (char _far *) fmt ,
	aspect_str( ptr->aspect ), planet_str( ptr->planet ), ptr->orb );
}


void num_print_midpoint_entry( FILE *stream, NUM planet, MIDPT *ptr, BITS mode )
{
 COUNT x;
 ASPEC *as;
 char buf[9];
 static char BCS inter[] = { "Intercepted" }, BCS cusps[] = { "on a House Cusp" };
 static char BCS fmt1[] = { "%-7.7s   |%-15.15s " };
 static char BCS fmt2[] = { "|House: %2d, %s.\n" };
 static char BCS fmt3[] = { "\n<Aspects to Midpoint:>\x80" };
 static char BCS fmt4[] = { "%-14.14s  |%-22.22s  |Orb: %d.\n" };

 if ( ptr->total_minutes == -1 )
    return;
 fprintf( stream, (char _far *) fmt1,
      format_degs( ptr->total_minutes, buf ),
      planet_str( ptr->second_planet) );
 if ( mode & HOUSES ) {
    fprintf( stream, (char _far *) fmt2, ptr->house,
	( (ptr->intercepted) ? (char _far *) cusps : (char _far *) inter ) );
    }
 else
    fprintf( stream, "\n" );
 if ( ptr->no_aspect > 0 ) {
    fprintf( stream, (char _far *) fmt3 );
    for ( x = 1, as = ptr->aspectr; x <= ptr->no_aspect; ++x, ++as ) {
	 fprintf( stream, (char _far *) fmt4,
             aspect_str( as->aspect ), planet_str( as->planet ), as->orb );
	}
    fprintf( stream, "\n" );
    }
}


/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet */

void num_print_entry( FILE *stream, AS_INF near *inf, NUM planet, BITS mode )
{
 COUNT i;
 ASPEC *as;
 MIDPT *mid;
 char ps[25], buf[9];
 static char BCS inter[] = { "Not On a House Cusp" }, BCS cusps[] = { "On a House Cusp" };
 static char BCS fmt1[] = { "\n\n{YOUR %s:}\x80" };
 static char BCS fmt2[] = { "\x80%-7s   |%s. " };
 static char BCS fmt3[] = { "  |Decan: %d" };
 static char BCS fmt4[] = { ", Critical Degree" };
 static char BCS fmt5[] = { ", Anaretic Degree" };
 static char BCS fmt6[] = { "House: %2d, %s.\n" };
 static char BCS fmt7[] = { "\n{ASPECTS:}\x80\x80" };
 static char BCS fmt8[] = { "\n{MIDPOINTS:}\x80\x80" };
 static char BCS fmt9[] = { " Sign is Intercepted." };

 strcpy( ps, planet_str( planet ) );
 fprintf( stream, (char _far *) fmt1, strupr(ps) );
 fprintf( stream, (char _far *) fmt2, format_degs( inf->minutes_total, buf ),
	motion_str( inf->retrograde ) );
 if ( mode & MISCELL ) {
    fprintf( stream, (char _far *) fmt3, inf->misc_code & 3  );
    if ( inf->misc_code & CRITICAL )
       fprintf( stream, (char _far *) fmt4 );
    if ( inf->misc_code & ANARET_DEG ) {
       fprintf( stream, (char _far *) fmt5  );
       }
    fprintf( stream, ".\n" );
    }
 else
    fprintf( stream, "\n" );
 if ( mode & HOUSES && planet != ASCEND && planet != MED_COELI
	    && planet != IM_COELI ) {
    fprintf( stream, (char _far *) fmt6, inf->house,
	 ( (inf->house_cusp) ? (char _far *) cusps : (char _far *) inter ) );
    if ( inf->intercepted )
       fprintf( stream, fmt9 );
    }
 if ( inf->no_aspects > 0 ) {
    fprintf( stream, (char _far *) fmt7 );
    for ( as = inf->aspectr, i = 1; i <= inf->no_aspects; ++i, ++as )
	num_print_aspect_entry( stream, planet, as );
    }
 if ( inf->no_midpt > 0 ) {
    fprintf( stream, (char _far *) fmt8 );
    for ( mid = inf->midptr, i = 1; i <= inf->no_midpt; ++i, ++mid )
	num_print_midpoint_entry( stream, planet, mid, mode );
    }

}

/* function to manage printing of results */

void num_print_results( FILE *stream, AS_INF near *inf_ptr, BIRTH_DB *data,
		      BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
 COUNT i;
 AS_INF near *inf;
 NUM maxp;
 static char BCS fmt1[] = { "Natal Numeric Zodiac Printout For: {%s}, " };
 static char BCS fmt2[] = { "Date: {%s}, Time: {%s}. " };
 static char BCS fmt3[] = { "\n\n{YOUR HOUSE CUSPS ARE:}\x80\x80" };

 if ( mode & VERT_EAST  )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;

 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
		 dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 fprintf( stream, (char _far *) fmt1, strclip(data->name) );
 fprintf( stream, (char _far *) fmt2,
    make_date( &data->birth_data.birth_date ),
    make_time( &data->birth_data.birth_time, data->am_pm ) );
 fprintf( stream, countrystatelocstr,
    strclip(data->country), strclip(data->state), strclip(data->location) );
 fprintf( stream, geogcoordstr,
    data->birth_data.latitude.degrees, data->birth_data.latitude.minutes, 
    data->birth_data.latitude.dir,  data->birth_data.longitude.degrees, 
    data->birth_data.longitude.minutes, data->birth_data.longitude.dir,
    data->birth_data.local_adjust, data->birth_data.local_minutes );
 fprintf( stream, sidtim4calc,
    data->birth_data.sidereal.hours, data->birth_data.sidereal.minutes,
    data->birth_data.sidereal.seconds );
 if ( mode & NOBIRTHTIM )
    print_rect_data( stream, dpk->rdp );

 fprintf( stream, zodhsmethstr,
    (( mode & SIDEREAL ) ? siderealstr : tropicstr ),
    housmod[house_mode] );

 if ( ferror( stream ) ) {
    return;
    }
 for ( i = 0, inf = inf_ptr; i <= maxp; ++i, ++inf ) {
     if ( x_kb_Check() == ESC )
	return;
     num_print_entry( stream, inf, i, mode );
     if ( ferror( stream ) ) {
	return;
        }
     }
 if ( mode & HOUSES ) {
    fprintf( stream, (char _far *) fmt3 );
    print_cusps(stream, house_cusps);
    }
}
