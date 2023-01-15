#include "stdafx.h"
#include <ctype.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "errors.fns"

/* import data record types */

#define BDATA 0   /* BD */
#define BLOC  1   /* BL */
#define BRECT 2   /* BR */
#define BREXT 3   /* BX */
#define CDATA 4   /* CD */
#define CLOC  5   /* CL */
#define CRECT 6   /* CR */
#define CREXT 7   /* CX */
#define TDATA 8   /* TD */
#define TLOC  9   /* TL */
#define TRDT  10  /* TA */
#define RDATA 11  /* RD */
#define RLOC  12  /* RL */
#define RPRG  13  /* RP */
#define PDATA 14  /* PD */

static char spec_vals[] = { 0, -1, -1, -2, -1, 1, 0 };
static char tim_vals[] = { 3, 4, 5, 6, 7, 8, 10, 0, -1, -2, -3, -8, -9, -7, -12,
		   -10, -8, -8, 5, 11, 12, 0 };

int import_trans( FILE *stream, TRANS_DATA *tdp )
{
 int i;

 i = fscanf( stream, "%d, %d, %d, %d, %d", &tdp->num_transits,
   &tdp->start_planet, &tdp->end_planet, &tdp->interval_date.month,
   &tdp->interval_date.day );
 return( i == 5 );
}

int import_prog( FILE *stream, PROGR_DATA *pdp )
{
 int i;

 i = fscanf( stream, "%d, %d, %d, %d", &pdp->progress_system,
    &pdp->offset.year, &pdp->offset.month, &pdp->offset.day );
 return( i == 4 );
}

int import_basic_rect( FILE *stream, RECT_DATA *rdp )
{
 char am[3], yn[4];
 int i;

 i = fscanf( stream, " %[^,], %d, %d:%d %s", yn, &rdp->rect_system,
     &rdp->trial.hours, &rdp->trial.minutes, am );
 if ( yn[0] == 'Y' || yn[0] == 'y' )
    rdp->birth_time_known = 1;
 else
    rdp->birth_time_known = 0;
 if ( am[0] == 'A' || yn[0] == 'A' )
    rdp->am_pm = 0;
 else
    rdp->am_pm = 1;
 return( i == 5 );
}

int import_ext_rect( FILE *stream, RECT_DATA *rdp )
{
 int i;

 i = fscanf( stream, "%d, %d, %d, %d", &rdp->angle, &rdp->sign,
      &rdp->degree.degrees, &rdp->degree.minutes );
 rdp->total_minutes = (((rdp->sign * 30 ) + rdp->degree.degrees) * 60 ) + rdp->degree.minutes;
 return( i == 4 );
}

int import_return_data( FILE *stream, RETURN_DATA *rdp )
{
 char yn[7];
 int i;

 i = fscanf( stream, "%d, %d/%d/%d, %d/%d/%d, %s", &rdp->planet,
    &rdp->start.month, &rdp->start.day, &rdp->start.year,
    &rdp->end.month, &rdp->end.day, &rdp->end.year, yn );
 if ( yn[0] == 'Y' || yn[0] == 'y' )
    rdp->is_prog = 1;
 else
    rdp->is_prog = 0;
 return( i == 8 );
}

void loc_to_birth( LOC_DB *ldp, BIRTH_DB *bdp )
{
 memcpy( bdp->country, ldp->country, COUNTRY_WIDTH );
 memcpy( bdp->state, ldp->state, STATE_WIDTH );
 memcpy( bdp->location, ldp->location, LOCATION_WIDTH );
 bdp->time_zone = ldp->time_zone;
 bdp->special_code = ldp->special_code;
 memcpy( &bdp->birth_data.longitude, &ldp->longitude, sizeof(DEG_MIN) );
 memcpy( &bdp->birth_data.latitude, &ldp->latitude, sizeof(DEG_MIN) );
 bdp->birth_data.local_adjust = ldp->hrs_offset;
 bdp->birth_data.local_minutes = ldp->min_offset;
}

int import_loc_data( FILE *stream, LOC_DB *ldp )
{
 int i, z;

 i = fscanf( stream, " \"%15[^\"]\", \"%15[^\"]\", \"%25[^\"]\",", ldp->country,
     ldp->state, ldp->location );
 i += fscanf( stream, "%d%c%d, %d%c%d, ", &ldp->longitude.degrees,
     &ldp->longitude.dir, &ldp->longitude.minutes,  &ldp->latitude.degrees,
      &ldp->latitude.dir, &ldp->latitude.minutes );
 ldp->latitude.dir = toupper( ldp->latitude.dir );
 ldp->longitude.dir = toupper( ldp->longitude.dir );
 i += fscanf( stream, " %d, ", &z );
 if ( z ) {
    i += fscanf( stream, "%d, %d", &ldp->time_zone, &ldp->special_code );
    ldp->hrs_offset =
	tim_vals[ldp->time_zone] + spec_vals[ldp->special_code];
    ldp->min_offset =
	(( ldp->time_zone == 16 || ldp->time_zone == 18 ) ? 30 : 0 );
    }
 else {
    i += fscanf( stream, "%d, %d", &ldp->hrs_offset, &ldp->min_offset );
    ldp->time_zone = 21;
    ldp->special_code = 6;
    }
 return( i == 12 );
}

int import_birth_data( FILE *stream, BIRTH_DB *bdp )
{
 int i;
 char sx[9], ampm[4];

 i = fscanf( stream, " \"%33[^\"]\", %[^,], %d/%d/%d, %d:%d %2s", bdp->name,
      sx, &bdp->birth_data.birth_date.month, &bdp->birth_data.birth_date.day,
      &bdp->birth_data.birth_date.year, &bdp->birth_data.birth_time.hours,
      &bdp->birth_data.birth_time.minutes, ampm );
 if ( sx[0] == 'M' || sx[0] == 'm' )
    bdp->sex = 0;
 else
    bdp->sex = 1;
 if ( ampm[0] == 'a' || ampm[0] == 'A' ) {
    bdp->am_pm = 0;
    }
 else {
    bdp->am_pm = 1;
    if ( bdp->am_pm && bdp->birth_data.birth_time.hours != 12 )
       bdp->birth_data.birth_time.hours += 12;
    else if ( !bdp->am_pm && bdp->birth_data.birth_time.hours == 12 )
       bdp->birth_data.birth_time.hours = 0;
    }
 return( i == 8 );
}


int import_record_code_type( char *code )
{
 switch( code[0] ) {
       case 'b' :
       case 'B' :
	    switch( code[1] ) {
		  case 'd' :
		  case 'D' :
		       return( BDATA );
		       break;
		  case 'l' :
		  case 'L' :
		       return( BLOC );
		       break;
		  case 'r' :
		  case 'R' :
		       return( BRECT );
		       break;
		  case 'x' :
		  case 'X' :
		       return( BREXT );
		       break;
		  default :
		       break;
		  }
	    break;
       case 't' :
       case 'T' :
	    switch( code[1] ) {
		  case 'd' :
		  case 'D' :
		       return( TDATA );
		       break;
		  case 'l' :
		  case 'L' :
		       return( TLOC );
		       break;
		  case 'a' :
		  case 'A' :
		       return( TRDT );
		       break;
		  default :
		       break;
		  }
	    break;
       case 'C' :
       case 'c' :
	    switch( code[1] ) {
		  case 'd' :
		  case 'D' :
		       return( CDATA );
		       break;
		  case 'l' :
		  case 'L' :
		       return( CLOC );
		       break;
		  case 'r' :
		  case 'R' :
		       return( CRECT );
		       break;
		  case 'x' :
		  case 'X' :
		       return( CREXT );
		       break;
		  default :
		       break;
		  }
	    break;
       case 'R' :
       case 'r' :
	    switch( code[1] ) {
		  case 'd' :
		  case 'D' :
		       return( RDATA );
		       break;
		  case 'l' :
		  case 'L' :
		       return( RLOC );
		       break;
		  case 'p' :
		  case 'P' :
		       return( RPRG );
		       break;
		  default :
		       break;
		  }
	    break;
       case 'p' :
       case 'P' :
	    return( PDATA );
	    break;
       default :
	    return( -1 );
	    break;
       }
 return( -1 );
}

int import_data_record( int type, FILE *stream )
{
 int i;
 LOC_DB ld;

 switch( type ) {
       case  BDATA :
	     return( import_birth_data( stream, &birth_rec ) );
	     break;
       case  BLOC :
	     i = import_loc_data( stream, &ld );
	     loc_to_birth( &ld, &birth_rec );
	     return( i );
	     break;
       case  BRECT :
	     return( import_basic_rect( stream, &birth_rectd ) );
	     break;
       case  BREXT :
	     return( import_ext_rect( stream, &birth_rectd ) );
	     break;
       case  CDATA :
	     return( import_birth_data( stream, &comp_rec ) );
	     break;
       case  CLOC :
	     i = import_loc_data( stream, &ld );
	     loc_to_birth( &ld, &comp_rec );
	     return( i );
	     break;
       case  CRECT :
	     return( import_basic_rect( stream, &comp_rectd ) );
	     break;
       case  CREXT :
	     return( import_ext_rect( stream, &comp_rectd ) );
	     break;
       case  TDATA :
	     return( import_birth_data( stream, &trans_rec ) );
	     break;
       case  TLOC :
	     i = import_loc_data( stream, &ld );
	     loc_to_birth( &ld, &trans_rec );
	     return( i );
	     break;
       case  TRDT :
	     return( import_trans( stream, &transit_data ) );
	     break;
       case  RDATA :
	     return( import_return_data( stream, &return_data ) );
	     break;
       case  RLOC  :
	     return( import_loc_data( stream, &reloc_data ) );
	     break;
       case  RPRG :
	     return( import_prog( stream, &return_data.prog ) );
	     break;
       case  PDATA :
	     return( import_prog( stream, &progress_data ) );
	     break;
       default :
	     return( 0 );
	     break;
       }
 return( 0 );
}

int import_file( char *file )
{
 int res, type;
 char code[5];
 FILE *stream;

 if ( ( stream = fopen( file, "rt" ) ) == NULL ) {
    do_error( file );
    return( 1 );
    }
 do {
    strcpy( code, "" );
    res = fscanf( stream, "%s", code );
    if ( res ) {
       type = import_record_code_type( code );
       res = import_data_record( type, stream );
       }
    } while( res && !feof( stream ) && !ferror( stream )  );
 if ( ferror( stream ) ) {
    do_error( file );
    res = 1;
    }
 else
    res = 0;
 fclose( stream );
 return( res );
}
