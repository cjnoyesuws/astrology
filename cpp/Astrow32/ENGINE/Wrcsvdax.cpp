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

char *strclip( char *s );
extern char *angles[];
extern const char *cp_str(int planet, int cht);


/* 09/10/92  Modified for C++ Windows  Zapp */

FILE *check_csvx_name( char *name )
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
       r = alert_box_ext( "Warning!", MB_ICONQUESTION|MB_YESNOCANCEL, "File %s Exists! Do You Want to Overwrite the "
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


char *get_csvx_file( char *name )
{
 char *p;
 char fname[250];
 char types[] = {"Comma Delimited (*.CSV)|*.CSV|Data Files (*.DAT)|*.DAT|All Files (*.*)|*.*||" };

 memset( fname, 0, 250 );
 strcpy( name, "CHART.CSV" );
 CFileDialog cfd(TRUE, ".TAB", name, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,types);
 cfd.m_ofn.lpstrTitle = "File Name For Comma Delimited File";
 if ( cfd.DoModal() == IDOK ) 
    strcpy( name, (LPCTSTR)cfd.GetPathName() );
 else 
   return( NULL );
 return( name );
}

void write_csvx_rect_data( FILE *stream, RECT_DATA *rd )
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

void write_csvx_rect_data_hd( FILE *stream, RECT_DATA *rd )
{
 char buf[25];

 fprintf( stream, "\"" "Rect System\",\"Trial Time\","  );
 if ( rd->rect_system == KNOWN_ANGL ) {
    fprintf( stream, "\"" "Angle\",\"" "Degrees\"," );
    }
}



void write_csvx_header( FILE *stream, BIRTH_DB *data, BITS mode, int count,
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
 if ( count &&( dpk->chart_code == COMPA_CH || dpk->chart_code == COMPO_CH ) )
    write_csvx_rect_data( stream, dpk->crdp );
 else
    write_csvx_rect_data( stream, dpk->rdp );
 fprintf( stream, "\"%s\",\"%s\"", (( mode & SIDEREAL ) ? siderealstr : tropicstr ),
	  housmod[house_mode] );
 if ( dpk->chart_code == RELOC_CH ) {
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

void write_csvx_header_hd( FILE *stream, BIRTH_DB *data, BITS mode, int count,
	 NUM house_mode, DATA_PACKET *dpk )
 {
 fprintf( stream, "\"Name\",");
 fprintf( stream, "\"Birth date\",\"Birth Time\"," );
 fprintf( stream, "\"Country\",\"State\",\"Location\"," );
 fprintf( stream, "\"Long\",\"Lat\",\"Time Zone\",\"Spec Code\",\"GMT\"," );
 fprintf( stream, "\"Sidereal Time\"," );
 if ( count &&( dpk->chart_code == COMPA_CH || dpk->chart_code == COMPO_CH ) )
    write_csvx_rect_data_hd( stream, dpk->crdp );
 else
    write_csvx_rect_data_hd( stream, dpk->rdp );
 fprintf( stream, "\"Side/Trop\",\"House Mode\"" );
 if ( dpk->chart_code == RELOC_CH ) {
    fprintf( stream, ",\"Country\",\"State\",\"Location\"," );
    fprintf( stream, "\"Long\",\"lat\",\"Time Zone\",\"Spec Code\",\"GMT\"");
    }
}


void write_csvx_trans_header_hd( FILE *stream, BIRTH_DB *tr_data, DATA_PACKET *dpk )
{
 fprintf( stream, "\"Country\",\"State\",\"Location\"," );
 fprintf( stream, "\"Long\",\"Lat\",\"Time Zone\",\"Spec Code\",\"GMT\"," );
 fprintf( stream, "\"# Transits\",\"Start\",\"End\",\"Interval\"\n" );
}


void write_csvx_trans_header( FILE *stream, BIRTH_DB *tr_data, DATA_PACKET *dpk )
{
 fprintf( stream, ",\"%s\",\"%s\",\"%s\",", strclip(tr_data->country),
    strclip(tr_data->state), strclip(tr_data->location) );
 fprintf( stream, "\"%02d%c%02d\",\"%03d%c%02d\",\"%s\",\"%s\",\"%02d:%02d\"",
    tr_data->birth_data.latitude.degrees, tr_data->birth_data.latitude.minutes,
    tr_data->birth_data.latitude.dir,  tr_data->birth_data.longitude.degrees,
    tr_data->birth_data.longitude.minutes, tr_data->birth_data.longitude.dir,
    timezones[tr_data->time_zone], speccodes[tr_data->special_code],
    tr_data->birth_data.local_adjust, tr_data->birth_data.local_minutes );
 fprintf( stream, "%d,%d,%d,\"%s\"\n",
    dpk->tdp->num_transits, dpk->tdp->start_planet, dpk->tdp->end_planet,
    make_date( &dpk->tdp->interval_date ) );
}


void write_csvx_prog_header_hd( FILE *stream, DATA_PACKET *dpk )
{
 fprintf( stream, ",\"Offset\",\"System\"" );
}

void write_csvx_solar_header_hd( FILE *stream, DATA_PACKET *dpk )
{
 fprintf( stream, ",\"Direction\",\"System\"" );
}


void write_csvx_prog_header( FILE *stream, DATA_PACKET *dpk )
{
 static char st1[] = { "Secondary (Day for a Year)" };
 static char st2[] = { "Tertiary (Day for a Lunar Month)" };
 static char st3[] = { "Minor (Lunar Month for a Year)" };
 static char far *prog_list[] = { st1, st2, st3, ERROR2 };
 int sys = dpk->pdp->progress_system;
 if ( sys >= 100 )
    sys -= 100;
 fprintf( stream, ",\"%s\"", make_date( &dpk->ddp->direction ) );
 fprintf( stream, ",\"%s\"", prog_list[dpk->ddp->direct_system] );
}

void write_csvx_solar_header( FILE *stream, DATA_PACKET *dpk )
{
 static char st1[] = { "Day for a Year" };
 static char st2[] = { "Degree for a Year" };
 static char st3[] = { "Nabod System" };
 static char far *solar_list[] = { st1, st2, st3, ERROR2 };
 int sys = dpk->ddp->direct_system;
 fprintf( stream, ",\"%s\"", make_date( &dpk->ddp->direction ) );
 fprintf( stream, ",\"%s\"", solar_list[dpk->ddp->direct_system] );
}

void write_csvx_aspect_entry( FILE *stream, NUM planet, ASPEC *aptr, int count, int ch, char *key )
{
 int i;
 ASPEC *ptr;

 for ( i = 0, ptr = aptr; i < count; ++i, ++ptr )
     fprintf( stream, "\"%s\",\"%s\",\"%s\",\"%s\",%d\n", key, cp_str( planet, ch ),
	 aspect_str( ptr->aspect ), planet_str( ptr->planet ), ptr->orb );
}

void write_csvx_aspects( FILE *stream, AS_INF *inf, int count, int cht, char *key, char *title )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "\n*** %s Aspects ***\n", title );
 fprintf( stream, "\"Key\",\"Planet\",\"Aspect\",\"Second Planet\",\"Orb\"\n" );
 for ( i = 0, ip = inf; i < count; ++ip, ++i ) {
     if ( ip->no_aspects )
	write_csvx_aspect_entry( stream, i, ip->aspectr, ip->no_aspects, cht, key );
     }
}

void write_csvx_tr_aspects( FILE *stream, AS_INF *inf, int end, int cht, int start, char *key, char *title )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "\n*** %s Transit Aspects ***\n", title );
 fprintf( stream, "\"Key\",\"Planet\",\"Aspect\",\"Second Planet\",\"Orb\"\n" );
 for ( i = start, ip = inf; i < end; ++ip, ++i ) {
     if ( ip->no_aspects )
	write_csvx_aspect_entry( stream, i, ip->aspectr, ip->no_aspects, cht, key );
     }
}

void write_csvx_planet_entry( FILE *stream, AS_INF *inf, NUM planet, int cht, char *key )
{
 char buf[15];
 static char inter[] = { "Not On House Cusp" }, cusps[] = { "On House Cusp" };

 fprintf( stream, "\"%s\",\"%s\",\"%s\",%d,\"%s\",", key,
    cp_str( planet, cht ), format_degs( inf->minutes_total, buf ),
    inf->misc_code & 3, motion_str( inf->retrograde ) );
 fprintf( stream, "\"%s\",\"%s\",", ( inf->misc_code & CRITICAL?"Critical":"---" ),
    ( inf->misc_code & ANARET_DEG?"Anaretic":"---" ) );
 fprintf( stream, "%d,\"%s\",\"%s\",", inf->house,
   ( (inf->house_cusp) ? (char *) cusps : (char *) inter ),
   (( inf->intercepted ) ? "Intercepted Sign":"---" ) );
 fprintf( stream, "%lf, %lf, %d, %d, %d\n", inf->longitude, inf->declination, inf->dec_minutes_total,
	 inf->dec_degrees, inf->dec_minutes_minor );
}

void write_csvx_planets( FILE *stream, AS_INF *inf, int count, int cht, char *key )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "\"Key\",\"Planet\",\"Degree\", Decan,\"Retrog\"," );
 fprintf( stream, "\"Critical\",\"Anaretic\"," );
 fprintf( stream, "\"House\",\"Cusp\",\"intercepted\"" );
 fprintf( stream, "\"longitude\",\"declination\"," );
 fprintf( stream, "\"dec_minutes_total\",\"dec_degrees\",\"dec_minor_minutes\"\n");
 for ( i = 0, ip = inf; i < count; ++ip, ++i )
     write_csvx_planet_entry( stream, ip, i, cht, key );
}

void write_csvx_tr_planets( FILE *stream, AS_INF *inf, int end, int cht, int start, char *key, char *title )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "\n*** %s Transits ***\n", title );
 fprintf( stream, "\"Key\",\"Planet\",\"Degree\", Decan,\"Retrog\"," );
 fprintf( stream, "\"Critical\",\"Anaretic\"," );
 fprintf( stream, "\"House\",\"Cusp\",\"intercepted\"\n" );
 fprintf( stream, "\"longitude\",\"declination\",\",");
 fprintf( stream, "\"dec_minutes_total\",\"dec_degrees\",\"dec_minor_minutes\"\n");
 for ( i = start, ip = inf; i < end; ++ip, ++i )
     write_csvx_planet_entry( stream, ip, i, cht, key );
}



void write_csvx_helio_entry( FILE *stream, AS_INF *inf, NUM planet, char *key )
{
 char buf[16];

 fprintf( stream, "\"%s\",\"%s\",\"%s\",%lf\n", key,
    (planet==SUN?"Earth":planet_str( planet )), format_degs( inf->minutes_total, buf ),
    inf->declination );
}

void write_csvx_helio( FILE *stream, AS_INF *inf, int count, char *key )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "\"Key\",\"Planet\",\"Degree\",\"declination\"\n" );
 for ( i = 0, ip = inf; i < count; ++ip, ++i )
     if ( i != MOON )
	write_csvx_helio_entry( stream, ip, i, key );
}


void write_csvx_midpoint_data( FILE *stream, MIDPT *inf, NUM planet, char *key )

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

void write_csvx_midpoints( FILE *stream, AS_INF *inf, int count, char *key, char *title )
{
 int i, j;
 AS_INF *ip;
 MIDPT *ptr;

 fprintf( stream, "\n*** %s Midpoints ***\n", title );
 fprintf( stream, "\"Key\",\"Planet\",\"Planet 2\",\"Degree\"," );
 fprintf( stream, "\"House\",\"Cusp\",\"Intercepted\"\n" );
 for ( i = 0, ip = inf; i < count; ++ip, ++i ) {
     for ( j = 0, ptr = ip->midptr; j < ip->no_midpt; ++j, ++ptr )
	 write_csvx_midpoint_data( stream, ptr, i, key );
     }
}

void write_csvx_houses( FILE *stream, short *cusps, char *key, char *title )
{
 char buf[10];
 short i, *ip;

 fprintf( stream, "\n*** %s Houses ***\n", title );
 fprintf( stream, "\"Key\",\'House\",\"Degree\"\n" );
 for ( i = 1, ip = cusps+1; i <= 12; ++i, ++ip )
     fprintf( stream, "\"%s\",%d,\"%s\"\n", key, i, format_degs( *ip, buf ) );
}


void write_csvx_planets_file( FILE *stream, AS_INF *inf, int count, int ch, char *key, char *title )
{
 fprintf( stream, "\n*** %s Planets ***\n", title );
 if ( ch != HELIO_CH )
     write_csvx_planets( stream, inf, count, ch, key );
  else
     write_csvx_helio( stream, inf, count, key );
}


void write_csvx_natal( BIRTH_DB *data, AS_INF *inf, BITS mode,
	     NUM house_mode, DATA_PACKET *dpk, int count )
{
  FILE *stream;
  char buf[150];
  char name[250];
 
  check_csvx_name( NULL );
  if ( get_csvx_file( name ) == NULL )
     return;
  if ( ( stream = check_csvx_name( name ) ) == NULL )
     return;
  fprintf( stream, "\"Key\"," );
  write_csvx_header_hd( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csvx_header_hd( stream, data, mode, 1, house_mode, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_csvx_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "\"%s\",", data->name );
  write_csvx_header( stream, data, mode, 0, house_mode, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_csvx_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  write_csvx_planets_file( stream, inf, count, dpk->chart_code, data->name, data->name );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csvx_houses( stream, house_cusps, data->name, data->name );
     }
  if ( mode & ASPECTS && dpk->chart_code != HELIO_CH ) {
     fprintf( stream, "\nAspects\n" );
	 write_csvx_aspects( stream, inf, count, dpk->chart_code, data->name, data->name );
     }
  if ( mode & (BASE_MID | HALF_MID | FULL_MID) && dpk->chart_code == NATAL_CH) {
     fprintf( stream, "\nMidpoints\n" );
	 write_csvx_midpoints( stream, inf, count, data->name, data->name );
     }
 fclose( stream );
}

void write_csvx_compos( BIRTH_DB *data, BIRTH_DB *pdata,
      AS_INF *inf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char key[100];
  char name[250];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csvx_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pdata->name );
  if ( get_csvx_file( name ) == NULL )
     return;
  if ( ( stream = check_csvx_name( name ) ) == NULL )
     return;
  fprintf( stream, "\"Key\"," );
  write_csvx_header_hd( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csvx_header_hd( stream, pdata, mode, 1, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH ) 
     write_csvx_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "\"%s\",", data->name);
  write_csvx_header( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csvx_header( stream, pdata, mode, 1, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH )
     write_csvx_prog_header( stream, dpk );
  fputc( '\n', stream );
  write_csvx_planets_file( stream, inf, end, NATAL_CH, key, key );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csvx_houses( stream, house_cusps, key, key );
     }
  if ( mode & ASPECTS && dpk->chart_code != HELIO_CH ) {
     write_csvx_aspects( stream, inf, end, NATAL_CH, key, key );
     }
 fclose( stream );
}

void write_csvx_compat( BIRTH_DB *data, BIRTH_DB *pdata,
     AS_INF *inf, AS_INF *pinf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[250];
  char key[100];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csvx_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pdata->name );
  if ( get_csvx_file( name ) == NULL )
     return;
  if ( ( stream = check_csvx_name( name ) ) == NULL )
     return;
  fprintf( stream, "\"Key\"," );
  write_csvx_header_hd( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csvx_header_hd( stream, pdata, mode, 1, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH ) 
     write_csvx_prog_header_hd( stream, dpk );
     fputc( '\n', stream );
  
  fprintf( stream, "\"%s\",", data->name, key );
  write_csvx_header( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csvx_header( stream, pdata, mode, 1, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH ) 
	  write_csvx_prog_header( stream, dpk );
  fputc( '\n', stream );
  
  write_csvx_planets_file( stream, inf, end, NATAL_CH, data->name, data->name );
  write_csvx_planets_file( stream, pinf, end, NATAL_CH, pdata->name, pdata->name );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csvx_houses( stream, house_cusps, data->name, data->name );
     write_csvx_houses( stream, alt_cusps, pdata->name, pdata->name );
     }
  if ( mode & ASPECTS  ) {
     write_csvx_aspects( stream, inf, end, NATAL_CH, data->name, data->name );
     write_csvx_aspects( stream, pinf, end, NATAL_CH, pdata->name, pdata->name );
     }
 fclose( stream );
}

void write_csvx_solar( BIRTH_DB *data,
     AS_INF *inf, AS_INF *sinf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[250];
  char key[100];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csvx_name( NULL );
  strcpy( key, data->name );
  if ( get_csvx_file( name ) == NULL )
     return;
  if ( ( stream = check_csvx_name( name ) ) == NULL )
     return;
  fprintf( stream, "\"Key\"," );
  write_csvx_header_hd( stream, data, mode, 0, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH ) 
     write_csvx_prog_header_hd( stream, dpk );
  write_csvx_solar_header_hd( stream, dpk );
  fputc( '\n', stream );
  
  fprintf( stream, "\"%s\",", data->name, key );
  write_csvx_header( stream, data, mode, 0, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH ) 
	  write_csvx_prog_header( stream, dpk );
  write_csvx_solar_header( stream, dpk );
  fputc( '\n', stream );
  
  write_csvx_planets_file( stream, inf, end, NATAL_CH, data->name, data->name );
  write_csvx_planets_file( stream, sinf, end, NATAL_CH, "Solar", "Solar" );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csvx_houses( stream, house_cusps, data->name, data->name );
     write_csvx_houses( stream, alt_cusps, "Solar","Solar" );
     }
  if ( mode & ASPECTS  ) {
     write_csvx_aspects( stream, inf, end, NATAL_CH, data->name, data->name );
     write_csvx_aspects( stream, sinf, end, NATAL_CH, "Solar","Solar" );
     }
 fclose( stream );
}

void write_csvx_harmonic( BIRTH_DB *data,
     AS_INF *inf, AS_INF *hinf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[250];
  char key[100];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csvx_name( NULL );
  strcpy( key, data->name );
  if ( get_csvx_file( name ) == NULL )
     return;
  if ( ( stream = check_csvx_name( name ) ) == NULL )
     return;
  fprintf( stream, "\"Key\"," );
  write_csvx_header_hd( stream, data, mode, 0, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH ) 
     write_csvx_prog_header_hd( stream, dpk );
  fprintf(stream,",\"harmonic\"\n");
  
  fprintf( stream, "\"%s\",", data->name, key );
  write_csvx_header( stream, data, mode, 0, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH ) 
	  write_csvx_prog_header( stream, dpk );
  fprintf(stream,",%d\n", *dpk->harmonic );
  
  write_csvx_planets_file( stream, inf, end, NATAL_CH, data->name, data->name );
  write_csvx_planets_file( stream, hinf, end, NATAL_CH, "Harmonic", "Harmonic" );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     write_csvx_houses( stream, house_cusps, data->name, data->name );
     }
  if ( mode & ASPECTS  ) {
     write_csvx_aspects( stream, inf, end, NATAL_CH, data->name, data->name );
     write_csvx_aspects( stream, hinf, end, NATAL_CH, "Harmonic","Harmonic" );
     }
 fclose( stream );
}


void write_csvx_prog( BIRTH_DB *data, AS_INF *inf, BITS mode,
				 NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[250];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_csvx_name( NULL );
  if ( get_csvx_file( name ) == NULL )
     return;
  if ( ( stream = check_csvx_name( name ) ) == NULL )
     return;
  fprintf( stream, "\"Key\"," );
  write_csvx_header_hd( stream, data, mode, 0, house_mode, dpk );
  write_csvx_prog_header_hd( stream, dpk  );
  fputc( '\n', stream );
  fprintf( stream, "\"%s\",", data->name );
  write_csvx_header( stream, data, mode, 0, house_mode, dpk );
  write_csvx_prog_header( stream, dpk  );
  fputc( '\n', stream );
  write_csvx_planets_file( stream, inf, end, NATAL_CH, data->name, data->name );
  write_csvx_planets_file( stream, prog, end, NATAL_CH, data->name, "Progressed" );
  write_csvx_planets_file( stream, moon_series, 16, -1, data->name, "Moon Series" );
  write_csvx_planets_file( stream, prog_moon_series, 16, -1, data->name, "Progressed Moon Series" );
  if ( mode & HOUSES ) {
     write_csvx_houses( stream, house_cusps, data->name, "Natal" );
     write_csvx_houses( stream, alt_cusps, data->name, "Progressed" );
     }
  if ( mode & ASPECTS ) {
     write_csvx_aspects( stream, prog, end, NATAL_CH, data->name, "Progressed" );
     write_csvx_aspects( stream, moon_series, 16, -1, data->name, "Moon series" );
     write_csvx_aspects( stream, prog_moon_series, 16, -1, data->name, "Progressed Moon Series" );
     }
 fclose( stream );
}

void write_csvx_trans( BIRTH_DB *data, AS_INF *inf, BITS mode,
	       BIRTH_DB *tr_data, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  int i, ep;
  DATES *dp;
  AS_INF **tp;
  TRANS_DATA *td = dpk->tdp;
  char buf[75];
  char key[100];
  char key2[100];
  char name[250];
  extern DATES *date_ptr;
  if ( mode & ASTEROID )
	  ep = CHIRON;
  else
	  ep = EAST_POINT;
  check_csvx_name( NULL );
  if ( get_csvx_file( name ) == NULL )
     return;
  if ( ( stream = check_csvx_name( name ) ) == NULL )
     return;
  fprintf( stream, "\"Key\"," );
  write_csvx_header_hd( stream, data, mode, 0, house_mode, dpk );
  write_csvx_trans_header_hd( stream, tr_data, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_csvx_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "\"%s\",", data->name );
  write_csvx_header( stream, data, mode, 0, house_mode, dpk );
  write_csvx_trans_header( stream, tr_data, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_csvx_prog_header( stream, dpk );
  fputc( '\n', stream );
  if ( mode & HOUSES && dpk->chart_code ) {
     write_csvx_houses( stream, house_cusps, data->name, data->name );
     }
  for ( i = 0, tp = trans_ptr, dp = date_ptr; i < td->num_transits; ++i, ++tp, ++dp ) {
      strcpy( key, data->name );
      strcat( key, "\",\"" );
      strcat( key, make_date( dp ) );
      strcpy( key2, data->name );
      strcat( key2, "--" );
      strcat( key2, make_date( dp ) );
      write_csvx_tr_planets( stream, *tp, (td->end_planet),
	     NATAL_CH, (td->start_planet), key, key2 );
      if ( mode & ASPECTS ) {
	     write_csvx_tr_aspects( stream, *tp, (td->end_planet),
	       NATAL_CH, (td->start_planet), key, key2 );
	     }
      }
 fclose( stream );
}

void write_csvx_cmtrans( BIRTH_DB *data, AS_INF *inf, BITS mode,
   BIRTH_DB *tr_data, BIRTH_DB *pa_data,NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  int i, ep;
  DATES *dp;
  AS_INF **tp;
  TRANS_DATA *td = dpk->tdp;
  char buf[75];
  char name[250];
  extern DATES *date_ptr;
  char key[100];
  char key2[100];
  char xkey[120];
  if ( mode & ASTEROID )
	 ep = CHIRON;
  else
	 ep = EAST_POINT;
  check_csvx_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pa_data->name );
  if ( get_csvx_file( name ) == NULL )
     return;
  if ( ( stream = check_csvx_name( name ) ) == NULL )
     return;
  fprintf( stream, "\"Key\"," );
  write_csvx_header_hd( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csvx_header_hd( stream, pa_data, mode, 1, house_mode, dpk );
  write_csvx_trans_header_hd( stream, tr_data, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_csvx_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "\"%s\",", key );
  write_csvx_header( stream, data, mode, 0, house_mode, dpk );
  fputc( ',', stream );
  write_csvx_header( stream, pa_data, mode, 1, house_mode, dpk );
  write_csvx_trans_header( stream, tr_data, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_csvx_prog_header( stream, dpk );
  fputc( '\n', stream );
  if ( mode & HOUSES && dpk->chart_code ) {
     write_csvx_houses( stream, house_cusps, key, key );
     }
  for ( i = 0, tp = trans_ptr, dp = date_ptr; i < td->num_transits; ++i, ++tp, ++dp ) {
      strcpy( xkey, key );
      strcat( xkey, "\",\"" );
      strcat( xkey, make_date( dp ) );
      strcpy( key2, key );
      strcat( key2, "--" );
      strcat( key2, make_date( dp ) );
      write_csvx_tr_planets( stream, *tp, (td->end_planet),
	    NATAL_CH, (td->start_planet), xkey, key2 );
      if ( mode & ASPECTS ) {
	 write_csvx_tr_aspects( stream, *tp, (td->end_planet),
	    NATAL_CH, (td->start_planet), xkey, key2 );
	 }
      }
 fclose( stream );
}
