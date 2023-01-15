#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "textptr.h"
#include "output.fns"
#include "dataext.h"
#include "charcons.h"

const char *hel_pla_str( int planet )
{
  if ( planet == SUN )
     return( "Earth" );
  else
     return( planet_str( planet ) );
}


/* function to print out a single aspect entry each on a single line */

/* function to print out each entry. Takes pointer to block, and number
   of block entry as planet */

void hel_print_entry( FILE *stream, AS_INF *inf, NUM planet, BITS mode )
{
 char ps[35];
 static char fmt1[] = { "\n{YOUR %s:}\x80" };
 static char fmt2[] = { "\nYour %s sign is %d.%d degrees %s and is in %s motion.\x80" };
 static char fmt3[] = { "\nYour %s sign is %d.%d degrees on the cusp between %s and " };
 static char fmt4[] = { "%s and is in %s motion.\x80" };
 static char fmt5[] = { "<%s:>\x80" };

 strcpy( ps, hel_pla_str( planet ) );
 fprintf( stream, (char *)fmt1, strupr(ps) );
 if ( inf->cusp == -1 ) {
    fprintf( stream, (char *)fmt2,
     hel_pla_str( planet ), inf->degree_minor,
         inf->minutes_minor, sign_str( inf->sign ),
     motion_str( inf->retrograde ) );
    }
 else {
    fprintf( stream, (char *)fmt3,
     hel_pla_str( planet ), inf->degree_minor, inf->minutes_minor,
         sign_str( (( inf->sign > inf->cusp ) ? inf->cusp : inf->sign )) );
    fprintf( stream, (char *)fmt4,
          sign_str( (( inf->sign > inf->cusp ) ? inf->sign : inf->cusp ) ), 
      motion_str( inf->retrograde ) );
    }
 if ( mode & MISCELL ) {
    fprintf( stream, decanstr, number_str( inf->misc_code & 3 ) );
    }
 fprintf( stream, "\n" );
}

/* function to manage printing of results */

void helio_print_results( FILE *stream, AS_INF *inf_ptr, BIRTH_DB *data,
              BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
 COUNT i;
 AS_INF *inf;
 char buf1[60];
 NUM maxp;
 static char fmt1[] = { "Natal Heliocentric Printout For: {%s}, " };

 if ( mode & VERT_EAST )
    maxp = EAST_POINT;
 else
    maxp = PART_FORTU;

 if ( mode & NOBIRTHTIM && ( dpk->rdp->rect_system == SOLARCHART ||
         dpk->rdp->rect_system == FLATCHART ) )
    house_mode = EQUAL;
 fprintf( stream, (char *)fmt1, enquote_strclip(data->name, (unsigned char *)buf1) );
 print_birth_header( stream, mode, data, house_mode, dpk );
 print_ts_house_mode( stream,  mode, house_mode );
 if ( dpk->chart_code & PROGR_CH )
    print_prog_header( stream, dpk );

 for ( i = 0, inf = inf_ptr; i <= maxp; ++i, ++inf ) {
    if ( x_kb_check() )
       break;
     if ( i != MOON )
    hel_print_entry( stream, inf, i, mode );
     if ( ferror( stream ) ) {
    return;
        }
     }
}
