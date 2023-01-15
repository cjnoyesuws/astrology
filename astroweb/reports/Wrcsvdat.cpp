#include "stdafx.h"
#include <share.h>
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "dataext.h"
#include "errors.fns"
#include "arabpt.h"
#include "fixstar.h"
#include "output.fns"
#include "charcons.h"
#include "paths.hpp"
#include <io.h>
#include <string.h>

FILE *log_stream;

char *strclip( char *s );
extern char *angles[];

/* 09/10/92  Modified for C++ Windows  Zapp */

char *make_csv_fds( DATA_PACKET *dpk )
{
 static char buf[10];

 strcpy( buf, "B" );
 if ( dpk->chart_code & COMPA_CH && dpk->chart_code & COMPO_CH  )
    strcat( buf, "C" );
 if ( dpk->chart_code & RELOC_CH )
    strcat( buf, "L" );
 if ( dpk->chart_code & PROGR_CH )
    strcat( buf, "P" );
 if ( dpk->chart_code & TRANS_CH )
    strcat( buf, "T" );
 return buf;
}

FILE *check_csv_name( char *name )
{
 int r;
 FILE *stream;
 static char *am;

 if ( name == NULL ) {
    am = NULL;
    return( NULL );
    }
 if ( access( name, 0 ) == -1 && am == NULL )
    am = "wt";
 else {
    if ( am == NULL ) {
       r = alert_box_ext( warn1, MB_ICONQUESTION|MB_YESNOCANCEL, "File %s Exists! Do You Want to Overwrite the "
	   "Existing File!", name );
       if ( r == IDCANCEL )
	  return( NULL );
       else if ( r == IDYES )
	  am = "wt";
       else
	  am = "at";
       }
    else
       am = "at";
    }
 if ( (stream = fopen( name, am  )) == NULL ) {
    do_error( name );
    return( NULL );
    }
 return( stream );

}


const char *cp_str( int planet, int cht )
{
 switch( cht ) {
       case NATAL_CH :
       case RELOC_CH :
	    return( planet_str( planet ) );
	    break;
       case FIXED_CH :
	    return( fixed_star_str( planet ) );
	    break;
       case ARABP_CH :
	    return( arabic_part_str( planet ) );
	    break;
       case -1 :
	    return( "Moon" );
	    break;
       default :
	    return( "" );
	    break;
       }
 return( "" );
}

void write_csv_rect_data( FILE *stream, RECT_DATA *rd )
{
 char buf[25];

 fprintf( stream, "\"%s\",", rectstr[rd->rect_system] );
 fprintf( stream, "\"%s\",",
    make_time( &rd->trial, rd->am_pm ) );
 if ( rd->rect_system == KNOWN_ANGL ) {
    fprintf( stream, "\"%s\",\"%s\",",
	angles[rd->angle-1], format_degs( rd->total_minutes, buf ) );
    }
}


void write_csv_header( FILE *stream, BIRTH_DB *data, BITS mode, int count,
	 NUM house_mode, DATA_PACKET *dpk )
 {
 fprintf( stream, "\"%s\",", strclip(data->name) );
 fprintf( stream, "\"%s\",\"%s\",",
    make_date( &data->birth_data.birth_date ),
    make_time( &data->birth_data.birth_time, data->am_pm ) );
 fprintf( stream, "\"%s\",\"%s\",\"%s\",", strclip(data->country),
    strclip(data->state), strclip(data->location) );
 fprintf( stream, "%02d%c%02d,%03d%c%02d,\"%s\",\"%s\",\"%02d:%02d\",",
    data->birth_data.latitude.degrees, data->birth_data.latitude.dir,
    data->birth_data.latitude.minutes, data->birth_data.longitude.degrees,
    data->birth_data.longitude.dir, data->birth_data.longitude.minutes,
    timezones[data->time_zone], speccodes[data->special_code],
    data->birth_data.local_adjust, data->birth_data.local_minutes );
 fprintf( stream, "\"%02d:%02d:%02d\",",
       data->birth_data.sidereal.hours, data->birth_data.sidereal.minutes,
       data->birth_data.sidereal.seconds );
 if ( count &&( dpk->chart_code & COMPA_CH || dpk->chart_code & COMPO_CH ) )
    write_csv_rect_data( stream, dpk->crdp );
 else
    write_csv_rect_data( stream, dpk->rdp );
 fprintf( stream, "\"%s\",\"%s\"", (( mode & SIDEREAL ) ? siderealstr : tropicstr ),
	  housmod[house_mode] );
 if ( dpk->chart_code & RELOC_CH ) {
    fprintf( stream, ",\"%s\",\"%s\",\"%s\",",
       dpk->relocp->country,
       dpk->relocp->state,
       dpk->relocp->location );
    fprintf( stream, "\"%02d%c%02d\",\"%03d%c%02d\",\"%s\",\"%s\",\"%02d:%02d\"",
       dpk->relocp->latitude.degrees, dpk->relocp->latitude.dir,
       dpk->relocp->latitude.minutes, dpk->relocp->longitude.degrees,
       dpk->relocp->longitude.dir, dpk->relocp->longitude.minutes,
       timezones[dpk->relocp->time_zone], speccodes[dpk->relocp->special_code],
       dpk->relocp->hrs_offset, dpk->relocp->min_offset );
    }
}

void write_csv_trans_header( FILE *stream, BIRTH_DB *tr_data, DATA_PACKET *dpk )
{
 fprintf( stream, ",\"%s\",\"%s\",\"%s\",", strclip(tr_data->country),
    strclip(tr_data->state), strclip(tr_data->location) );
 fprintf( stream, "\"%02d%c%02d\",\"%03d%c%02d\",\"%s\",\"%s\",\"%02d:%02d\",",
    tr_data->birth_data.latitude.degrees, tr_data->birth_data.latitude.minutes, 
    tr_data->birth_data.latitude.dir, tr_data->birth_data.longitude.degrees,
    tr_data->birth_data.longitude.minutes, tr_data->birth_data.longitude.dir,
    timezones[tr_data->time_zone], speccodes[tr_data->special_code],
    tr_data->birth_data.local_adjust, tr_data->birth_data.local_minutes );
 fprintf( stream, "%d,%d,%d,\"%s\"\n",
    dpk->tdp->num_transits, dpk->tdp->start_planet, dpk->tdp->end_planet,
    make_date( &dpk->tdp->interval_date ) );
}



void write_csv_prog_header( FILE *stream, DATA_PACKET *dpk )
{
 static char st1[] = { "Secondary (Day for a Year)" };
 static char st2[] = { "Tertiary (Day for a Lunar Month)" };
 static char st3[] = { "Minor (Lunar Month for a Year)" };
 static char far *prog_list[] = { st1, st2, st3, "Error!!" };

 fprintf( stream, ",\"%s\"", make_date( &dpk->pdp->offset ) );
 fprintf( stream, ",\"%s\"", prog_list[dpk->pdp->progress_system] );
}

void write_csv_solar_header( FILE *stream, DATA_PACKET *dpk )
{
 static char st1[] = { "Day for a Year" };
 static char st2[] = { "Degree for a Year" };
 static char st3[] = { "Nabod System" };
 static char far *solar_list[] = { st1, st2, st3, "Error!!" };

 fprintf( stream, ",\"%s\"", make_date( &dpk->ddp->direction ) );
 fprintf( stream, ",\"%s\"", solar_list[dpk->ddp->direct_system] );
}


void write_csv_aspect_entry( FILE *stream, NUM planet, ASPEC *aptr, int count, int ch, char *key )
{
 int i;
 ASPEC *ptr;

 for ( i = 0, ptr = aptr; i < count; ++i, ++ptr )
     fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d\n", key, cp_str( planet, ch ),
	 aspect_str( ptr->aspect ), planet_str( ptr->planet ), ptr->orb );
}

int write_csv_aspects( FILE *stream, AS_INF *inf, int count, int cht, char *key )
{
 int i, ct = 0;
 AS_INF *ip;

 for ( i = 0, ip = inf; i < count; ++ip, ++i ) {
     ct += ip->no_aspects;
     if ( ip->no_aspects )
	write_csv_aspect_entry( stream, i, ip->aspectr, ip->no_aspects, cht, key );
     }
 return ct;
}

int write_csv_tr_aspects( FILE *stream, AS_INF *inf, int end, int cht, int start, char *key )
{
 int i, ct = 0;
 AS_INF *ip;

 for ( i = start, ip = inf; i < end; ++ip, ++i ) {
     ct += ip->no_aspects;
     if ( ip->no_aspects )
	write_csv_aspect_entry( stream, i, ip->aspectr, ip->no_aspects, cht, key );
     }
 return ct;
}

void write_csv_planet_entry( FILE *stream, AS_INF *inf, NUM planet, int cht, char *key )
{
 char buf[15];
 static char inter[] = { "Not On House Cusp" }, cusps[] = { "On House Cusp" };

 fprintf( stream, "\"%s\",\"%s\",\"%s\",%d,\"%s\",", key,
    cp_str( planet, cht ), format_degs( inf->minutes_total, buf ),
    inf->misc_code & 3, motion_str( inf->retrograde ) );
 fprintf( stream, "\"%s\",\"%s\",", ( inf->misc_code & CRITICAL?"Critical":"---" ),
    ( inf->misc_code & ANARET_DEG?"Anaretic":"---" ) );
 fprintf( stream, "%d,\"%s\",\"%s\"\n", inf->house,
   ( (inf->house_cusp) ? (char *) cusps : (char *) inter ),
   (( inf->intercepted ) ? "Intercepted Sign":"---" ) );
 fprintf( stream, "%lf, %lf, %d, %d, %d\n", inf->longitude, inf->declination, inf->dec_minutes_total,
	 inf->dec_degrees, inf->dec_minutes_minor );
}

void write_csv_planets( FILE *stream, AS_INF *inf, int count, int cht, char *key )
{
 int i;
 AS_INF *ip;

 for ( i = 0, ip = inf; i < count; ++ip, ++i )
     write_csv_planet_entry( stream, ip, i, cht, key );
}

void write_csv_tr_planets( FILE *stream, AS_INF *inf, int end, int cht, int start, char *key )
{
 int i;
 AS_INF *ip;

 for ( i = start, ip = inf; i < end; ++ip, ++i )
     write_csv_planet_entry( stream, ip, i, cht, key );
}



void write_csv_helio_entry( FILE *stream, AS_INF *inf, NUM planet, char *key )
{
 char buf[16];

 fprintf( stream, "\"%s\",\"%s\",\"%s\", %lf\n", key,
    (planet==SUN?"Earth":planet_str( planet )), format_degs( inf->minutes_total, buf ),
    inf->declination );
}

void write_csv_helio( FILE *stream, AS_INF *inf, int count, char *key )
{
 int i;
 AS_INF *ip;

 for ( i = 0, ip = inf; i < count; ++ip, ++i )
     if ( i != MOON )
	write_csv_helio_entry( stream, ip, i, key );
}


void write_csv_midpoint_data( FILE *stream, MIDPT *inf, NUM planet, char *key )

{
 static char inter[] = { "Not On House Cusp" }, cusps[] = { "On House Cusp" };
 char buf[15];

 fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",", key,
    planet_str( planet ), planet_str( inf->second_planet),
    format_degs( inf->total_minutes, buf ) );
 fprintf( stream, "%d,\"%s\",\"%s\"\n", inf->house,
   ( (inf->house_cusp) ? (char *) cusps : (char *) inter ),
   ( inf->intercepted ) ? "Intercepted Sign":"---" );
}

void write_csv_midpoints( FILE *stream, AS_INF *inf, int count, char *key )
{
 int i, j;
 AS_INF *ip;
 MIDPT *ptr;

 for ( i = 0, ip = inf; i < count; ++ip, ++i ) {
     for ( j = 0, ptr = ip->midptr; j < ip->no_midpt; ++j, ++ptr )
	 write_csv_midpoint_data( stream, ptr, i, key );
     }
}

void write_csv_houses( FILE *stream, short *cusps, char *key )
{
 char buf[10];
 short i, *ip;

 for ( i = 1, ip = cusps+1; i <= 12; ++i, ++ip )
     fprintf( stream, "\"%s\",%d,\"%s\"\n", key, i, format_degs( *ip, buf ) );
}

char *get_csv_file( char *name )
{
 char *p;
 char fname[150];
 char types[] = "Comma Delimited (*.)|*.||";

 memset( fname, 0, 150 );
 strcpy( name, "CHART." );
 CFileDialog fof(FALSE, ".", name, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,types );
 fof.m_ofn.lpstrTitle = "File Name For Comma Delimited File";
 if ( fof.DoModal() == IDOK )
    strcpy( name, (LPCTSTR)fof.GetFileName() );
 else 
    return( NULL );
 if ( ( p = strrchr( name, '.' ) ) != NULL )
    *p = '\0';
 return( name );
}


void write_csv_house_file( char *name, char *ext, short *cusps, char *key )
{
  FILE *stream;
  char buf[150];

  strcpy( buf, name );
  strcat( buf, ext );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  write_csv_houses( stream, cusps, key );
  fclose( stream );
  fprintf( log_stream, "%s%s,%d,H\n", name, ext, 12 );
}


void write_csv_planets_file( char *name, char *ext, AS_INF *inf, int count, int ch, char *key )
{
  FILE *stream;
  char buf[150];

  strcpy( buf, name );
  strcat( buf, ext );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  if ( ch != HELIO_CH )
     write_csv_planets( stream, inf, count, ch, key );
  else
     write_csv_helio( stream, inf, count, key );
  fclose( stream );
  fprintf( log_stream, "%s%s,%d,P\n", name, ext, count );
}


void write_csv_aspects_file( char *name, char *ext, AS_INF *inf, int count, int ch, char *key )
{
  int ct = 0;
  FILE *stream;
  char buf[150];

  strcpy( buf, name );
  strcat( buf, ext );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  ct = write_csv_aspects( stream, inf, count, ch, key );
  fclose( stream );
  fprintf( log_stream, "%s%s,%d,A\n", name, ext, ct );
}



void write_csv_natal( BIRTH_DB *data, AS_INF *inf, BITS mode,
	     NUM house_mode, DATA_PACKET *dpk, int count )
{
  FILE *stream;
  char buf[150];
  char name[150];

  check_csv_name( NULL );
  if ( get_csv_file( name ) == NULL )
     return;
  strcpy( buf, name );
  strcat( buf, ".FIL" );
  log_stream = fopen( buf, "wt" );
  fprintf( log_stream, "%s\n", data->name );
  strcpy( buf, name );
  strcat( buf, ".DAT" );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  fprintf( stream, "\"%s\",\"%s\",", make_csv_fds(dpk), data->name );
  write_csv_header( stream, data, mode, 0, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH )
     write_csv_prog_header( stream, dpk );
  fputc( '\n', stream );
  fclose( stream );
  fprintf( log_stream, "%s,1,D\n", buf );
  write_csv_planets_file( name, ".POS", inf, count, dpk->chart_code, data->name );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csv_house_file( name, ".HOS", house_cusps, data->name  );
     }
  if ( mode & ASPECTS && dpk->chart_code != HELIO_CH ) {
     write_csv_aspects_file( name, ".ASP", inf, count, dpk->chart_code, data->name  );
     }
  if ( mode & (BASE_MID | HALF_MID | FULL_MID) && dpk->chart_code & NATAL_CH) {
     strcpy( buf, name );
     strcat( buf, ".MID" );
     if ( ( stream = check_csv_name( buf ) ) == NULL )
	return;
     write_csv_midpoints( stream, inf, count, data->name  );
     fprintf( log_stream, "%s,%d,M\n", buf, count );
     fclose( stream );
     }
 fclose( log_stream );
}

void write_csv_compos( BIRTH_DB *data, BIRTH_DB *pdata,
      AS_INF *inf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char key[100];
  char name[150];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 
  check_csv_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pdata->name );
  if ( get_csv_file( name ) == NULL )
     return;
  strcpy( buf, name );
  strcat( buf, ".FIL" );
  log_stream = fopen( buf, "wt" );
  fprintf( log_stream, "%s\n", data->name );
  strcpy( buf, name );
  strcat( buf, ".DAT" );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  fprintf( stream, "\"%s\",\"%s\",", make_csv_fds(dpk), key );
  write_csv_header( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csv_header( stream, pdata, mode, 1, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH )
     write_csv_prog_header( stream, dpk );
  fputc( '\n', stream );
  fclose( stream );
  fprintf( log_stream, "%s,1,D\n", buf );
  write_csv_planets_file( name, ".POS", inf, end, NATAL_CH, key );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csv_house_file( name, ".HOS", house_cusps, key );
     }
  if ( mode & ASPECTS && dpk->chart_code != HELIO_CH ) {
     write_csv_aspects_file( name, ".ASP", inf, end, NATAL_CH, key );
     }
 fclose( log_stream );
}

void write_csv_compat( BIRTH_DB *data, BIRTH_DB *pdata,
     AS_INF *inf, AS_INF *pinf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[75];
  char key[100];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csv_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pdata->name );
  if ( get_csv_file( name ) == NULL )
     return;
  strcpy( buf, name );
  strcat( buf, ".FIL" );
  log_stream = fopen( buf, "wt" );
  fprintf( log_stream, "%s\n", data->name );
  strcpy( buf, name );
  strcat( buf, ".DAT" );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  fprintf( stream, "\"%s\",\"%s\",", make_csv_fds(dpk), key );
  write_csv_header( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csv_header( stream, pdata, mode, 1, house_mode, dpk );
  fputc( '\n', stream );
  fclose( stream );
  fprintf( log_stream, "%s,1,D\n", buf );
  write_csv_planets_file( name, ".POS", inf, end, NATAL_CH, data->name );
  write_csv_planets_file( name, ".CPS", pinf, end, NATAL_CH, pdata->name );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csv_house_file( name, ".HOS", house_cusps, data->name );
     write_csv_house_file( name, ".CHS", alt_cusps, pdata->name );
     }
  if ( mode & ASPECTS  ) {
     write_csv_aspects_file( name, ".ASP", inf, end, NATAL_CH, data->name );
     write_csv_aspects_file( name, ".ACP", pinf, end, NATAL_CH, pdata->name );
     }
 fclose( log_stream );
}

void write_csv_solar( BIRTH_DB *data,
     AS_INF *inf, AS_INF *sinf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[75];
  char key[100];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csv_name( NULL );
  strcpy( key, data->name );
  if ( get_csv_file( name ) == NULL )
     return;
  strcpy( buf, name );
  strcat( buf, ".FIL" );
  log_stream = fopen( buf, "wt" );
  fprintf( log_stream, "%s\n", data->name );
  strcpy( buf, name );
  strcat( buf, ".DAT" );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  fprintf( stream, "\"%s\",\"%s\",", make_csv_fds(dpk), key );
  write_csv_header( stream, data, mode, 0, house_mode, dpk );
  write_csv_solar_header( stream, dpk  );
  fputc( '\n', stream );
  fclose( stream );
  fprintf( log_stream, "%s,1,D\n", buf );
  write_csv_planets_file( name, ".POS", inf, end, NATAL_CH, data->name );
  write_csv_planets_file( name, ".SPS", sinf, end, NATAL_CH, data->name );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csv_house_file( name, ".HOS", house_cusps, data->name );
     }
  if ( mode & ASPECTS  ) {
     write_csv_aspects_file( name, ".ASP", inf, end, NATAL_CH, data->name );
     write_csv_aspects_file( name, ".SSP", sinf, end, NATAL_CH, data->name );
     }
 fclose( log_stream );
}

void write_csv_harmonic( BIRTH_DB *data,
     AS_INF *inf, AS_INF *hinf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[75];
  char key[100];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csv_name( NULL );
  strcpy( key, data->name );
  if ( get_csv_file( name ) == NULL )
     return;
  strcpy( buf, name );
  strcat( buf, ".FIL" );
  log_stream = fopen( buf, "wt" );
  fprintf( log_stream, "%s\n", data->name );
  strcpy( buf, name );
  strcat( buf, ".DAT" );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  fprintf( stream, "\"%s\",\"%s\",", make_csv_fds(dpk), key );
  write_csv_header( stream, data, mode, 0, house_mode, dpk );
  fprintf( stream, ",%d\n", *dpk->harmonic );
  fclose( stream );
  fprintf( log_stream, "%s,1,D\n", buf );
  write_csv_planets_file( name, ".POS", inf, end, NATAL_CH, data->name );
  write_csv_planets_file( name, ".HPS", hinf, end, NATAL_CH, data->name );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csv_house_file( name, ".HOS", house_cusps, data->name );
     }
  if ( mode & ASPECTS  ) {
     write_csv_aspects_file( name, ".ASP", inf, end, NATAL_CH, data->name );
     write_csv_aspects_file( name, ".HSP", hinf, end, NATAL_CH, data->name );
     }
 fclose( log_stream );
}


void write_csv_prog( BIRTH_DB *data, AS_INF *inf, BITS mode,
				 NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[75];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csv_name( NULL );
  if ( get_csv_file( name ) == NULL )
     return;
  strcpy( buf, name );
  strcat( buf, ".FIL" );
  log_stream = fopen( buf, "wt" );
  fprintf( log_stream, "%s\n", data->name );
  strcpy( buf, name );
  strcat( buf, ".DAT" );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  fprintf( stream, "\"%s\",\"%s\",", make_csv_fds(dpk), data->name );
  write_csv_header( stream, data, mode, 0, house_mode, dpk );
  write_csv_prog_header( stream, dpk  );
  fputc( '\n', stream );
  fclose( stream );
  fprintf( log_stream, "%s,1,D\n", buf );
  write_csv_planets_file( name, ".POS", inf, end, NATAL_CH, data->name );
  write_csv_planets_file( name, ".PPS", prog, end, NATAL_CH, data->name );
  write_csv_planets_file( name, ".PMS", moon_series, 16, -1, data->name );
  write_csv_planets_file( name, ".PPM", prog_moon_series, 16, -1, data->name );
  if ( mode & HOUSES ) {
     write_csv_house_file( name, ".HOS", house_cusps, data->name );
     write_csv_house_file( name, ".HPS", alt_cusps, data->name );
     }
  if ( mode & ASPECTS ) {
     write_csv_aspects_file( name, ".APP", prog, end, NATAL_CH, data->name );
     write_csv_aspects_file( name, ".AMS", moon_series, 16, -1, data->name );
     write_csv_aspects_file( name, ".APM", prog_moon_series, 16, -1, data->name );
     }
 fclose( log_stream );
}

void write_csv_trans( BIRTH_DB *data, AS_INF *inf, BITS mode,
	       BIRTH_DB *tr_data, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  int i, ep;
  DATES *dp;
  AS_INF **tp;
  TRANS_DATA *td = dpk->tdp;
  char buf[75];
  char key[100];
  char name[75];
  extern DATES *date_ptr;
  if ( mode & ASTEROID )
	 ep = CHIRON;
 else
	 ep = EAST_POINT;

  check_csv_name( NULL );
  if ( get_csv_file( name ) == NULL )
     return;
  strcpy( buf, name );
  strcat( buf, ".FIL" );
  log_stream = fopen( buf, "wt" );
  fprintf( log_stream, "%s\n", data->name );
  strcpy( buf, name );
  strcat( buf, ".DAT" );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  fprintf( stream, "\"%s\",\"%s\",", make_csv_fds(dpk), data->name );
  write_csv_header( stream, data, mode, 0, house_mode, dpk );
  write_csv_trans_header( stream, tr_data, dpk );
  if ( dpk->chart_code & PROGR_CH )
     write_csv_prog_header( stream, dpk );
  fputc( '\n', stream );
  fclose( stream );
  fprintf( log_stream, "%s,1,D\n", buf );
  if ( mode & HOUSES && dpk->chart_code ) {
     write_csv_house_file( name, ".HOS", house_cusps, data->name  );
     }
  int cnt = 0, acnt = 0;
  for ( i = 0, tp = trans_ptr, dp = date_ptr; i < td->num_transits; ++i, ++tp, ++dp ) {
      strcpy( key, data->name );
      strcat( key, "\",\"" );
      strcat( key, make_date( dp ) );
      strcpy( buf, name );
      strcat( buf, ".PTS" );
      if ( ( stream = check_csv_name( buf ) ) == NULL )
	 return;
      cnt += (td->end_planet-td->start_planet);
      write_csv_tr_planets( stream, *tp, (td->end_planet),
	    NATAL_CH, (td->start_planet), key );
      fclose( stream );
      if ( mode & ASPECTS ) {
	 strcpy( buf, name );
	 strcat( buf, ".ATS" );
	 if ( ( stream = check_csv_name( buf ) ) == NULL )
	    return;
	 acnt += write_csv_tr_aspects( stream, *tp, (td->end_planet),
	    NATAL_CH, (td->start_planet), key );
	 fclose( stream );
	 }
      }
 fprintf( log_stream, "%s%s,%d,T\n", buf, ".PTS", cnt );
 fprintf( log_stream, "%s%s,%d,X\n", buf, ".ATS", acnt );
 fclose( log_stream );
}

void write_csv_cmtrans( BIRTH_DB *data, AS_INF *inf, BITS mode,
   BIRTH_DB *tr_data, BIRTH_DB *pa_data,NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  int i, ep;
  DATES *dp;
  AS_INF **tp;
  TRANS_DATA *td = dpk->tdp;
  char buf[75];
  char name[75];
  extern DATES *date_ptr;
  char key[100];
  char xkey[120];
  if ( mode & ASTEROID )
	 ep = CHIRON;
  else
	 ep = EAST_POINT;
  check_csv_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pa_data->name );
  if ( get_csv_file( name ) == NULL )
     return;
  strcpy( buf, name );
  strcat( buf, ".FIL" );
  log_stream = fopen( buf, "wt" );
  fprintf( log_stream, "%s\n", data->name );
  strcpy( buf, name );
  strcat( buf, ".DAT" );
  if ( ( stream = check_csv_name( buf ) ) == NULL )
     return;
  fprintf( stream, "\"%s\",\"%s\",", make_csv_fds(dpk), key );
  write_csv_header( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csv_header( stream, pa_data, mode, 1, house_mode, dpk );
  write_csv_trans_header( stream, tr_data, dpk );
  if ( dpk->chart_code & PROGR_CH )
     write_csv_prog_header( stream, dpk );
  fputc( '\n', stream );
  fclose( stream );
  fprintf( log_stream, "%s,1,D\n", buf );
  if ( mode & HOUSES && dpk->chart_code ) {
     write_csv_house_file( name, ".HOS", house_cusps, key );
     }
  fclose( stream );
  int cnt = 0, acnt = 0;
  for ( i = 0, tp = trans_ptr, dp = date_ptr; i < td->num_transits; ++i, ++tp, ++dp ) {
      strcpy( xkey, key );
      strcat( xkey, "\",\"" );
      strcat( xkey, make_date( dp ) );
      strcpy( buf, name );
      strcat( buf, ".PTS" );
      if ( ( stream = check_csv_name( buf ) ) == NULL )
	 return;
      cnt += ((td->end_planet)-(td->start_planet));
      write_csv_tr_planets( stream, *tp, (td->end_planet),
	    NATAL_CH, (td->start_planet), xkey );
      fclose( stream );
      if ( mode & ASPECTS ) {
	 strcpy( buf, name );
	 strcat( buf, ".ATS" );
	 if ( ( stream = check_csv_name( buf ) ) == NULL )
	    return;
	 acnt += write_csv_tr_aspects( stream, *tp, (td->end_planet),
	    NATAL_CH, (td->start_planet), xkey );
	 fclose( stream );
	 }
      }
 fprintf( log_stream, "%s%s,%d,T\n", buf, ".PTS", cnt );
 fprintf( log_stream, "%s%s,%d,X\n", buf, ".ATS", acnt );
 fclose( log_stream );
}
