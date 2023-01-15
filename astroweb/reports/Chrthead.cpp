#include "stdafx.h"
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "charcons.h"
#include "output.fns"
#include "charcons.h"
extern char *enquote_strclip( char *, char * );


int print_birth_header( FILE *stream, BITS mode, BIRTH_DB *data,
				     int house_mode, DATA_PACKET *dpk )
{
 int e;
 char buf1[60], buf2[60], buf3[60];
 static char fmt2[] = { "Birth Date: {%s}, Time: {%s}. " };

 fprintf( stream, (char *)fmt2,
    make_date( &data->birth_data.birth_date ),
    make_time( &data->birth_data.birth_time, data->am_pm ) );
    fprintf( stream, countrystatelocstr,
    enquote_strclip(data->country, buf1),
    enquote_strclip(data->state, buf2),
    enquote_strclip(data->location, buf3) );
 return( fprintf( stream, geogcoordstr,
       data->birth_data.latitude.degrees, data->birth_data.latitude.minutes,
       data->birth_data.latitude.dir,  data->birth_data.longitude.degrees,
       data->birth_data.longitude.minutes, data->birth_data.longitude.dir,
       timezones[data->time_zone],
       speccodes[data->special_code],
       data->birth_data.local_adjust, data->birth_data.local_minutes ) );
 e = fprintf( stream, sidtim4calc,
       data->birth_data.sidereal.hours, data->birth_data.sidereal.minutes,
       data->birth_data.sidereal.seconds );
 if ( dpk == NULL )
    return( e );
 if ( mode & NOBIRTHTIM )
    print_rect_data( stream, dpk->rdp );
 return( 1 );
}


int print_ts_house_mode( FILE *stream, int mode, int house_mode )
{
 return( fprintf( stream, zodhsmethstr,
	  (( mode & SIDEREAL ) ? siderealstr : tropicstr ),
					 housmod[house_mode] ) );
}

int print_reloc_header( FILE *stream, DATA_PACKET *dpk )
{
    char buf1[60], buf2[60], buf3[60];
    static char fmt3[] = { "Chart is Relocated to: "  };

    fprintf( stream, (char *)fmt3);
    fprintf( stream, countrystatelocstr,
       enquote_strclip(dpk->relocp->country, buf1),
       enquote_strclip(dpk->relocp->state, buf2),
       enquote_strclip(dpk->relocp->location, buf3) );
    return( fprintf( stream, geogcoordstr,
       dpk->relocp->latitude.degrees, dpk->relocp->latitude.minutes,
       dpk->relocp->latitude.dir,  dpk->relocp->longitude.degrees,
       dpk->relocp->longitude.minutes, dpk->relocp->longitude.dir,
       timezones[dpk->relocp->time_zone],
       speccodes[dpk->relocp->special_code],
       dpk->relocp->hrs_offset, dpk->relocp->min_offset ) );
}

int print_prog_header( FILE *stream, DATA_PACKET *dpk )
{
 static char  fmt3[] = { "Progressed {%d} Years, {%d} Months and {%d} days. " };
 static char  fmt3a[] = { "Progression System: {\"%s\"}.\n\n" };
 static char  st1[] = { "Secondary (Day for a Year)" };
 static char  st2[] = { "Tertiary (Day for a Lunar Month)" };
 static char  st3[] = { "Minor (Lunar Month for a Year)" };
 static char *prog_list[] = { st1, st2, st3, ERROR2 };

 fprintf( stream, (char  *) fmt3,
    dpk->pdp->offset.year, dpk->pdp->offset.month, dpk->pdp->offset.day );
 return( fprintf( stream, (char *) fmt3a,
	     prog_list[dpk->pdp->progress_system] ) );
}
