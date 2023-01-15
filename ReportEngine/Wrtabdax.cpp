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

/* 09/10/92  Modified for C++ Windows  Zapp */

FILE *check_tab_name( char *name )
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


const char *cp_tab_str( int planet, int cht )
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

void write_tab_rect_data( FILE *stream, RECT_DATA *rd )
{
 char buf[25];

 fprintf( stream, "%s\t", rectstr[rd->rect_system] );
 fprintf( stream, "%s\t",
    make_time( &rd->trial, rd->am_pm ) );
 if ( rd->rect_system == KNOWN_ANGL ) {
    fprintf( stream, "%s\t%s\t",
	angles[rd->angle-1], format_degs( rd->total_minutes, buf ) );
    }
}

void write_tab_rect_data_hd( FILE *stream, RECT_DATA *rd )
{
 char buf[25];

 fprintf( stream, "Rect System\t" );
 fprintf( stream, "Trial Time\t"  );
 if ( rd->rect_system == KNOWN_ANGL ) {
    fprintf( stream, "Angle\t""Degrees\t" );
    }
}



void write_tab_header( FILE *stream, BIRTH_DB *data, BITS mode, int count,
	 NUM house_mode, DATA_PACKET *dpk )
 {
 fprintf( stream, "%s\t", strclip(data->name) );
 fprintf( stream, "%s\t%s\t",
    make_date( &data->birth_data.birth_date ),
    make_time( &data->birth_data.birth_time, data->am_pm ) );
 fprintf( stream, "%s\t%s\t%s\t", strclip(data->country),
    strclip(data->state), strclip(data->location) );
 fprintf( stream, "%02d%c%02d\t%03d%c%02d\t%s\t%s\t%02d:%02d\t",
    data->birth_data.latitude.degrees, data->birth_data.latitude.dir,
    data->birth_data.latitude.minutes, data->birth_data.longitude.degrees,
    data->birth_data.longitude.dir, data->birth_data.longitude.minutes,
    timezones[data->time_zone], speccodes[data->special_code],
    data->birth_data.local_adjust, data->birth_data.local_minutes );
 fprintf( stream, "%02d:%02d:%02d\t",
       data->birth_data.sidereal.hours, data->birth_data.sidereal.minutes,
       data->birth_data.sidereal.seconds );
 if ( count &&( dpk->chart_code == COMPA_CH || dpk->chart_code == COMPO_CH ) )
    write_tab_rect_data( stream, dpk->crdp );
 else
    write_tab_rect_data( stream, dpk->rdp );
 fprintf( stream, "%s\t%s", (( mode & SIDEREAL ) ? siderealstr : tropicstr ),
	  housmod[house_mode] );
 if ( dpk->chart_code == RELOC_CH ) {
    fprintf( stream, "\t%s\t%s\t%s\t",
       dpk->relocp->country,
       dpk->relocp->state,
       dpk->relocp->location );
    fprintf( stream, "%02d%c%02d\t%03d%c%02d\t%s\t%s\t%02d:%02d",
       dpk->relocp->latitude.degrees, dpk->relocp->latitude.dir,
       dpk->relocp->latitude.minutes, dpk->relocp->longitude.degrees,
       dpk->relocp->longitude.dir, dpk->relocp->longitude.minutes,
       timezones[dpk->relocp->time_zone], speccodes[dpk->relocp->special_code],
       dpk->relocp->hrs_offset, dpk->relocp->min_offset );
    }
}

void write_tab_header_hd( FILE *stream, BIRTH_DB *data, BITS mode, int count,
	 NUM house_mode, DATA_PACKET *dpk )
 {
 fprintf( stream, "Name\t");
 fprintf( stream, "Birth date\t""Birth Time\t" );
 fprintf( stream, "Country\t""State\t""Location\t" );
 fprintf( stream, "Long\t""Lat\t""Time Zone\t""Spec Code\t""GMT\t" );
 fprintf( stream, "Sidereal Time\t" );
 if ( count &&( dpk->chart_code == COMPA_CH || dpk->chart_code == COMPO_CH ) )
    write_tab_rect_data_hd( stream, dpk->crdp );
 else
    write_tab_rect_data_hd( stream, dpk->rdp );
 fprintf( stream, "Side/Trop\t""House Mode" );
 if ( dpk->chart_code == RELOC_CH ) {
    fprintf( stream, "\tCountry\t""State\t""Location\t" );
    fprintf( stream, "Long\t""lat\t""Time Zone\t""Spec Code\t""GMT");
    }
}


void write_tab_trans_header_hd( FILE *stream, BIRTH_DB *tr_data, DATA_PACKET *dpk )
{
 fprintf( stream, "\tCountry\t""State\t""Location\t" );
 fprintf( stream, "Long\t""Lat\t""Time Zone\t""Spec Code\t""GMT\t" );
 fprintf( stream, "# Transits\t""Start\t""End\t""Interval\n" );
}



void write_tab_trans_header( FILE *stream, BIRTH_DB *tr_data, DATA_PACKET *dpk )
{
 fprintf( stream, "\t%s\t%s\t%s\t", strclip(tr_data->country),
    strclip(tr_data->state), strclip(tr_data->location) );
 fprintf( stream, "%02d%c%02d\t%03d%c%02d\t%s\t%s\t%02d:%02d",
    tr_data->birth_data.latitude.degrees, tr_data->birth_data.latitude.minutes,
    tr_data->birth_data.latitude.dir,  tr_data->birth_data.longitude.degrees,
    tr_data->birth_data.longitude.minutes, tr_data->birth_data.longitude.dir,
    timezones[tr_data->time_zone], speccodes[tr_data->special_code],
    tr_data->birth_data.local_adjust, tr_data->birth_data.local_minutes );
 fprintf( stream, "%d\t%d\t%d\t%s\n",
    dpk->tdp->num_transits, dpk->tdp->start_planet, dpk->tdp->end_planet,
    make_date( &dpk->tdp->interval_date ) );
}

void write_tab_prog_header_hd( FILE *stream, DATA_PACKET *dpk )
{
 fprintf( stream, "\tOffset" );
 fprintf( stream, "\tSystem" );
}


void write_tab_prog_header( FILE *stream, DATA_PACKET *dpk )
{
 static char st1[] = { "Secondary (Day for a Year)" };
 static char st2[] = { "Tertiary (Day for a Lunar Month)" };
 static char st3[] = { "Minor (Lunar Month for a Year)" };
 static char far *prog_list[] = { st1, st2, st3, ERROR2 };
 int sys = dpk->pdp->progress_system;
 if ( sys >= 100 )
    sys -= 100;
 fprintf( stream, "\t%s", make_date( &dpk->pdp->offset ) );
 fprintf( stream, "\t%s", prog_list[dpk->pdp->progress_system] );
}

void write_tab_solar_header( FILE *stream, DATA_PACKET *dpk )
{
 static char st1[] = { "Day for a Year" };
 static char st2[] = { "Degree for a Year" };
 static char st3[] = { "Nabod Method" };
 static char far *solar_list[] = { st1, st2, st3, ERROR2 };
 int sys = dpk->ddp->direct_system;
 if ( sys >= 100 )
    sys -= 100;
 fprintf( stream, "\t%s", make_date( &dpk->ddp->direction ) );
 fprintf( stream, "\t%s", solar_list[sys] );
}

void write_tab_aspect_entry( FILE *stream, NUM planet, ASPEC *aptr, int count, int ch, char *key )
{
 int i;
 ASPEC *ptr;

 for ( i = 0, ptr = aptr; i < count; ++i, ++ptr )
     fprintf( stream, "%s\t%s\t%s\t%s\t%d\n", key, cp_tab_str( planet, ch ),
	 aspect_str( ptr->aspect ), planet_str( ptr->planet ), ptr->orb );
}

void write_tab_aspects( FILE *stream, AS_INF *inf, int count, int cht, char *key )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "Key\t""Planet\t""Aspect\t""Second Planet\t""Orb\n" );
 for ( i = 0, ip = inf; i < count; ++ip, ++i ) {
     if ( ip->no_aspects )
	write_tab_aspect_entry( stream, i, ip->aspectr, ip->no_aspects, cht, key );
     }
}

void write_tab_tr_aspects( FILE *stream, AS_INF *inf, int end, int cht, int start, char *key )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "Key\t""Planet\t""Aspect\t""Second Planet\t""Orb\n" );
 for ( i = start, ip = inf; i < end; ++ip, ++i ) {
     if ( ip->no_aspects )
	write_tab_aspect_entry( stream, i, ip->aspectr, ip->no_aspects, cht, key );
     }
}



void write_tab_planet_entry( FILE *stream, AS_INF *inf, NUM planet, int cht, char *key )
{
 char buf[15];
 static char inter[] = { "Not On House Cusp" }, cusps[] = { "On House Cusp" };

 fprintf( stream, "%s\t%s\t%s\t%d\t%s\t", key,
    cp_tab_str( planet, cht ), format_degs( inf->minutes_total, buf ),
    inf->misc_code & 3, motion_str( inf->retrograde ) );
 fprintf( stream, "%s\t%s\t", ( inf->misc_code & CRITICAL?"Critical":"---" ),
    ( inf->misc_code & ANARET_DEG?"Anaretic":"---" ) );
 fprintf( stream, "%d\t%s\t%s\t", inf->house,
   ( (inf->house_cusp) ? (char *) cusps : (char *) inter ),
   (( inf->intercepted ) ? "Intercepted Sign":"---" ) );
 fprintf( stream, "%lf\t%lf\t%d\t%d\t%d\n", inf->longitude, inf->declination, inf->dec_minutes_total,
	 inf->dec_degrees, inf->dec_minutes_minor );
}

void write_tab_planets( FILE *stream, AS_INF *inf, int count, int cht, char *key )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "Key\tPlanet\tDegree\tDecan\tRetrog\t" );
 fprintf( stream, "Critical\tAnaretic\t" );
 fprintf( stream, "House\tCusp\tintercepted\t" );
 fprintf( stream, "longitude\tdeclination\t" );
 fprintf( stream, "dec_minutes_total\tdec_degrees\tdec_minor_minutes\n");

 for ( i = 0, ip = inf; i < count; ++ip, ++i )
     write_tab_planet_entry( stream, ip, i, cht, key );
}

void write_tab_tr_planets( FILE *stream, AS_INF *inf, int end, int cht, int start, char *key )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "Key\t""Planet\t""Degree\tDecan\tRetrog\t" );
 fprintf( stream, "Critical\t""Anaretic\t" );
 fprintf( stream, "House\t""Cusp\t""intercepted\n" );
 for ( i = start, ip = inf; i < end; ++ip, ++i )
     write_tab_planet_entry( stream, ip, i, cht, key );
}



void write_tab_helio_entry( FILE *stream, AS_INF *inf, NUM planet, char *key )
{
 char buf[16];

 fprintf( stream, "%s\t%s\t%s\n", key,
    (planet==SUN?"Earth":planet_str( planet )), format_degs( inf->minutes_total, buf ),
    inf->misc_code & 3 );
}

void write_tab_helio( FILE *stream, AS_INF *inf, int count, char *key )
{
 int i;
 AS_INF *ip;

 fprintf( stream, "Key\t""Planet\t""Degree\n" );
 for ( i = 0, ip = inf; i < count; ++ip, ++i )
     if ( i != MOON )
	write_tab_helio_entry( stream, ip, i, key );
}


void write_tab_midpoint_data( FILE *stream, MIDPT *inf, NUM planet, char *key )

{
 static char inter[] = { "Not On House Cusp" }, cusps[] = { "On House Cusp" };
 char buf[15];

 fprintf( stream, "%s\t%s\t%s\t%s\t", key,
    planet_str( planet ), planet_str( inf->second_planet),
    format_degs( inf->total_minutes, buf ) );
 fprintf( stream, "%d\t%s\t%s\n", inf->house,
   ( (inf->house_cusp) ? (char *) cusps : (char *) inter ),
   ( inf->intercepted ) ? "Intercepted Sign":"---" );
}

void write_tab_midpoints( FILE *stream, AS_INF *inf, int count, char *key )
{
 int i, j;
 AS_INF *ip;
 MIDPT *ptr;

 fprintf( stream, "Key\t""Planet\t""Planet 2\t""Degree\t" );
 fprintf( stream, "House\t""Cusp\t""Intercepted\n" );
 for ( i = 0, ip = inf; i < count; ++ip, ++i ) {
     for ( j = 0, ptr = ip->midptr; j < ip->no_midpt; ++j, ++ptr )
	 write_tab_midpoint_data( stream, ptr, i, key );
     }
}

void write_tab_houses( FILE *stream, short *cusps, char *key )
{
 char buf[10];
 short i, *ip;

 fprintf( stream, "Key\t""House\t""Degree\n" );
 for ( i = 1, ip = cusps+1; i <= 12; ++i, ++ip )
     fprintf( stream, "%s\t%d\t%s\n", key, i, format_degs( *ip, buf ) );
}

char *get_tab_file( char *name )
{
 char *p;
 char fname[250];
 char types[] = {"Tab Delimited (*.TAB)|*.TAB|Data Files (*.DAT)|*.DAT|All Files (*.*)|*.*||" };

 memset( fname, 0, 250 );
 strcpy( name, "CHART.TAB" );
 CFileDialog cfd(TRUE, ".TAB", name, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,types);
 cfd.m_ofn.lpstrTitle = "File Name For Tab Delimited File";
 if ( cfd.DoModal() == IDOK ) 
    strcpy( name, cfd.GetPathName() );
 else 
   return( NULL );
 return( name );
}


void write_tab_house_file( FILE *stream, short *cusps, char *key )
{
  write_tab_houses( stream, (short *)cusps, key );
}


void write_tab_planets_file( FILE *stream, AS_INF *inf, int count, int ch, char *key )
{
  if ( ch != HELIO_CH )
     write_tab_planets( stream, inf, count, ch, key );
  else
     write_tab_helio( stream, inf, count, key );
}


void write_tab_aspects_file( FILE *stream, AS_INF *inf, int count, int ch, char *key )
{
  write_tab_aspects( stream, inf, count, ch, key );
}



void write_tab_natal( BIRTH_DB *data, AS_INF *inf, BITS mode,
	     NUM house_mode, DATA_PACKET *dpk, int count )
{
  FILE *stream;
  char buf[250];
  char name[250];

  check_tab_name( NULL );
  if ( get_tab_file( name ) == NULL )
     return;
  strcpy( buf, name );
  if ( ( stream = check_tab_name( buf ) ) == NULL )
     return;
  fprintf( stream, "Key\t" );
  write_tab_header_hd( stream, data, mode, 0, house_mode, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_tab_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "%s\t", data->name );
  write_tab_header( stream, data, mode, 0, house_mode, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_tab_prog_header( stream, dpk );
  fputc( '\n', stream );  
  fputc( '\n', stream );
  fprintf( stream, "Planets\n" );
  write_tab_planets_file( stream, inf, count, dpk->chart_code, data->name );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     fprintf( stream, "\nHouses\n" );
	 write_tab_house_file( stream, house_cusps, data->name  );
     }
  if ( mode & ASPECTS && dpk->chart_code != HELIO_CH ) {
      fprintf( stream, "\nAspects\n" );
	  write_tab_aspects_file( stream, inf, count, dpk->chart_code, data->name  );
     }
  if ( mode & (BASE_MID | HALF_MID | FULL_MID) && dpk->chart_code == NATAL_CH) {
     fprintf( stream, "\nMidpoints\n" );    
	 write_tab_midpoints( stream, inf, count, data->name  );
     }
 fclose( stream );
}

void write_tab_compos( BIRTH_DB *data, BIRTH_DB *pdata,
      AS_INF *inf, BITS mode, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char key[130];
  char name[250];
  int end;
  if ( mode & ASTEROID )
	 end = CHIRON;
  else
	 end = EAST_POINT;
 
  check_tab_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pdata->name );
  if ( get_tab_file( name ) == NULL )
     return;
  if ( ( stream = check_tab_name( name ) ) == NULL )
     return;
  fprintf( stream, "Key\t" );
  write_tab_header_hd( stream, data, mode, 0, house_mode, dpk );
  fputc( '\t', stream );
  write_tab_header_hd( stream, pdata, mode, 1, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH )
     write_tab_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "%s\t", key );
  write_tab_header( stream, data, mode, 0, house_mode, dpk );
  fputc( '\t', stream );
  write_tab_header( stream, pdata, mode, 1, house_mode, dpk );
  if ( dpk->chart_code & PROGR_CH )
     write_tab_prog_header( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "\nPlanets\n" );
  write_tab_planets_file( stream, inf, end, NATAL_CH, key );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     fprintf( stream, "\nHouses\n" );
	 write_tab_house_file( stream, house_cusps, key );
     }
  if ( mode & ASPECTS && dpk->chart_code != HELIO_CH ) {
     fprintf( stream, "\nAspects\n" );
	 write_tab_aspects_file( stream, inf, end, NATAL_CH, key );
     }
 fclose( stream );
}

void write_tab_compat( BIRTH_DB *data, BIRTH_DB *pdata,
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
  check_tab_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pdata->name );
  if ( get_tab_file( name ) == NULL )
     return;
   if ( ( stream = check_tab_name( name ) ) == NULL )
     return;
  fprintf( stream, "Key\t" );
  write_tab_header_hd( stream, data, mode, 0, house_mode, dpk );
  fputc( '\t', stream );
  write_tab_header_hd( stream, pdata, mode, 1, house_mode, dpk );
  fputc( '\n', stream );
  fprintf( stream, "%s\t", data->name, key );
  write_tab_header( stream, data, mode, 0, house_mode, dpk );
  fputc( '\t', stream );
  write_tab_header( stream, pdata, mode, 1, house_mode, dpk );
  fputc( '\n', stream );
  fputc( '\n', stream );
  
  fprintf( stream, "\n%s's Planets\n", pdata->name );
  write_tab_planets_file( stream, inf, 18, NATAL_CH, data->name );
  fprintf( stream, "\n%s's Planets\n", pdata->name );
  write_tab_planets_file( stream, pinf, end, NATAL_CH, pdata->name );
  fputc( '\n', stream );
  if ( mode & HOUSES && dpk->chart_code != HELIO_CH ) {
     fprintf( stream, "\n%s's Houses\n", data->name );
     write_tab_house_file( stream, house_cusps, data->name );
     fputc( '\n', stream );
     fprintf( stream, "\n%s's Houses\n", pdata->name );
     write_tab_house_file( stream, house_cusps, pdata->name );
     }
  fputc( '\n', stream );
  if ( mode & ASPECTS  ) {
     fprintf( stream, "\n%s's Aspects\n", data->name );
     write_tab_aspects_file( stream, inf, end, NATAL_CH, data->name );
     fputc( '\n', stream );
     fprintf( stream,"\n%s's Aspects\n", pdata->name );
     write_tab_aspects_file( stream, pinf, end, NATAL_CH, data->name );
     }
 fclose( stream );
}

void write_tab_prog( BIRTH_DB *data, AS_INF *inf, BITS mode,
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
  check_tab_name( NULL );
  if ( get_tab_file( name ) == NULL )
     return;
  if ( ( stream = check_tab_name( name ) ) == NULL )
     return;
  fprintf( stream, "Key\t", data->name );
  write_tab_header_hd( stream, data, mode, 0, house_mode, dpk );
  write_tab_prog_header_hd( stream, dpk  );
  fputc( '\n', stream );
  fprintf( stream, "%s\t", data->name );
  write_tab_header( stream, data, mode, 0, house_mode, dpk );
  write_tab_prog_header( stream, dpk  );
  fputc( '\n', stream );
  fprintf( stream, "Planets\n" );
  write_tab_planets_file( stream, inf, end, NATAL_CH, data->name );
  fprintf( stream, "Progressed Planets\n" );
  write_tab_planets_file( stream, prog, 18, NATAL_CH, data->name );
  fputc( '\n', stream );
  fprintf( stream, "Moon Series\n" );
  write_tab_planets_file( stream, moon_series, 16, -1, data->name );
  fputc( '\n', stream );
  fprintf( stream, "Progressed Moon Series\n" );
  write_tab_planets_file( stream, prog_moon_series, 16, -1, data->name );
  fputc( '\n', stream );
  if ( mode & HOUSES ) {
     fprintf( stream, "Natal Houses\n" );
     write_tab_house_file( stream, house_cusps, data->name );
     fputc( '\n', stream );
	 fprintf( stream, "Progressed Houses\n" );
     write_tab_house_file( stream, alt_cusps, data->name );
     fputc( '\n', stream );
     }
  if ( mode & ASPECTS ) {
     fprintf( stream, "Aspects Progressed Planets\n" );
     write_tab_aspects_file( stream, prog, end, NATAL_CH, data->name );
     fputc( '\n', stream );
	 fprintf( stream, "Aspects to Moon Series\n" );
     write_tab_aspects_file( stream, moon_series, 16, -1, data->name );
     fputc( '\n', stream );
	 fprintf( stream, "Aspects to Progressed Moon Series\n" );
     write_tab_aspects_file( stream, prog_moon_series, 16, -1, data->name );
     fputc( '\n', stream );
     }
 fclose( stream );
}

void write_tab_solar_header_hd( FILE *stream, DATA_PACKET *dpk  )
{

   
}

void write_tab_Solar( BIRTH_DB *data, AS_INF *inf, AS_INF *so_inf, BITS mode,
				 NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[250];

  int end;
  if ( mode & ASTEROID )
     end = CHIRON;
  else if ( mode & VERT_EAST )
     end = EAST_POINT;
  else 
     end = SOUTH_NODE;
  check_tab_name( NULL );
  if ( get_tab_file( name ) == NULL )
     return;
  if ( ( stream = check_tab_name( name ) ) == NULL )
     return;
  fprintf( stream, "Key\t", data->name );
  write_tab_header_hd( stream, data, mode, 0, house_mode, dpk );
  write_tab_solar_header_hd( stream, dpk  );
  fputc( '\n', stream );
  fprintf( stream, "%s\t", data->name );
  write_tab_header( stream, data, mode, 0, house_mode, dpk );
  write_tab_solar_header( stream, dpk  );
  fputc( '\n', stream );
  fprintf( stream, "Planets\n" );
  write_tab_planets_file( stream, inf, end, NATAL_CH, data->name );
  fprintf( stream, "Solar Planets\n" );
  write_tab_planets_file( stream, so_inf, end, NATAL_CH, data->name );
  fputc( '\n', stream );
  if ( mode & HOUSES ) {
     fprintf( stream, "Natal Houses\n" );
     write_tab_house_file( stream, house_cusps, data->name );
     fputc( '\n', stream );
  }
 if ( mode & ASPECTS ) {
     fprintf( stream, "Natal Aspects\n" );
     write_tab_aspects_file( stream, inf, end, NATAL_CH, data->name );
     fputc( '\n', stream );
	 fprintf( stream, "Aspects to Solar\n" );
     write_tab_aspects_file( stream, so_inf, end, NATAL_CH, data->name );
     fputc( '\n', stream );
	  }
 fclose( stream );
}

void write_tab_Harmonic( BIRTH_DB *data, AS_INF *inf, AS_INF *h_inf, BITS mode,
				 NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  char buf[75];
  char name[250];

  int end;
  if ( mode & ASTEROID )
     end = CHIRON;
  else if ( mode & VERT_EAST )
     end = EAST_POINT;
  else 
     end = SOUTH_NODE;
  check_tab_name( NULL );
  if ( get_tab_file( name ) == NULL )
     return;
  if ( ( stream = check_tab_name( name ) ) == NULL )
     return;
  fprintf( stream, "Key\t", data->name );
  write_tab_header_hd( stream, data, mode, 0, house_mode, dpk );
  fprintf( stream, "\tHarmonic\n");
  fprintf( stream, "%s\t", data->name );
  write_tab_header( stream, data, mode, 0, house_mode, dpk );
  fprintf(stream, "\t%d\n", *dpk->harmonic );
  fprintf( stream, "Planets\n" );
  write_tab_planets_file( stream, inf, end, NATAL_CH, data->name );
  fprintf( stream, "Harmonic Planets\n" );
  write_tab_planets_file( stream, h_inf, end, NATAL_CH, data->name );
  fputc( '\n', stream );
  if ( mode & HOUSES ) {
     fprintf( stream, "Natal Houses\n" );
     write_tab_house_file( stream, house_cusps, data->name );
     fputc( '\n', stream );
  }
 if ( mode & ASPECTS ) {
     fprintf( stream, "Natal Aspects\n" );
     write_tab_aspects_file( stream, inf, end, NATAL_CH, data->name );
     fputc( '\n', stream );
	 fprintf( stream, "Aspects to Harmonic\n" );
     write_tab_aspects_file( stream, h_inf, end, NATAL_CH, data->name );
     fputc( '\n', stream );
	  }
 fclose( stream );
}

void write_tab_trans( BIRTH_DB *data, AS_INF *inf, BITS mode,
	       BIRTH_DB *tr_data, NUM house_mode, DATA_PACKET *dpk )
{
  FILE *stream;
  int i, ep;
  DATES *dp;
  AS_INF **tp;
  TRANS_DATA *td = dpk->tdp;
  char buf[75];
  char key[100];
  char name[250];
  extern DATES *date_ptr;
  if ( mode & ASTEROID )
	 ep = CHIRON;
  else
	 ep = EAST_POINT;
  check_tab_name( NULL );
  if ( get_tab_file( name ) == NULL )
     return;
  if ( ( stream = check_tab_name( name ) ) == NULL )
     return;
  fprintf( stream, "Key\t", data->name );
  write_tab_header_hd( stream, data, mode, 0, house_mode, dpk );
  write_tab_trans_header_hd( stream, tr_data, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_tab_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "%s\t", data->name );
  write_tab_header( stream, data, mode, 0, house_mode, dpk );
  write_tab_trans_header( stream, tr_data, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_tab_prog_header( stream, dpk );
  fputc( '\n', stream );
  fputc( '\n', stream );
  if ( mode & HOUSES && dpk->chart_code ) {
     fprintf(stream, "Houses\n");
     write_tab_house_file( stream, house_cusps, data->name  );
     fputc( '\n', stream );
     }
  for ( i = 0, tp = trans_ptr, dp = date_ptr; i < td->num_transits; ++i, ++tp, ++dp ) {
      fprintf(stream, "\n%s\t""%s\n", data->name, strcpy( key, make_date( dp ) ) );
      write_tab_tr_planets( stream, *tp, (td->end_planet),
	        NATAL_CH, (td->start_planet), key );
      if ( mode & ASPECTS ) {
	     fprintf(stream, "%s\t""%s\t""Aspects\n", data->name, strcpy( key, make_date( dp ) ) );
	     write_tab_tr_aspects( stream, *tp, (td->end_planet),
	        NATAL_CH, (td->start_planet), key );
	     fputc( '\n', stream );
	     }
      }
 fclose( stream );
}

void write_tab_cmtrans( BIRTH_DB *data, AS_INF *inf, BITS mode,
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
  char xkey[120];

  if ( mode & ASTEROID )
	 ep = CHIRON;
  else
	 ep = EAST_POINT;
 
  check_tab_name( NULL );
  strcpy( key, data->name );
  strcat( key, " & " );
  strcat( key, pa_data->name );
  if ( get_tab_file( name ) == NULL )
     return;
  if ( ( stream = check_tab_name( name ) ) == NULL )
     return;
  fprintf( stream, "Key\t", key );
  write_tab_header_hd( stream, data, mode, 0, house_mode, dpk );
  fputc( '\t', stream );
  write_tab_header_hd( stream, pa_data, mode, 1, house_mode, dpk );
  write_tab_trans_header_hd( stream, tr_data, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_tab_prog_header_hd( stream, dpk );
  fputc( '\n', stream );
  fprintf( stream, "%s\t", key );
  write_tab_header( stream, data, mode, 0, house_mode, dpk );
  fputc( '\t', stream );
  write_tab_header( stream, pa_data, mode, 1, house_mode, dpk );
  write_tab_trans_header( stream, tr_data, dpk );
  if ( dpk->chart_code == PROGR_CH )
     write_tab_prog_header( stream, dpk );
  fputc( '\n', stream );
  fputc( '\n', stream );
  if ( mode & HOUSES && dpk->chart_code ) {
     fprintf( stream, "Houses\n" );
     write_tab_house_file( stream, house_cusps, key );
     fputc( '\n', stream );
     }
  
  for ( i = 0, tp = trans_ptr, dp = date_ptr; i < td->num_transits; ++i, ++tp, ++dp ) {
      fprintf( stream, "\n%s\t""%s\t", key, make_date(dp) );
      write_tab_tr_planets( stream, *tp, (td->end_planet),
	     NATAL_CH, (td->start_planet), xkey );
      if ( mode & ASPECTS ) {
	     fprintf( stream, "\n%s\t""%s\t""Aspects\n", key, make_date(dp) );
	     write_tab_tr_aspects( stream, *tp, (td->end_planet),
	        NATAL_CH, (td->start_planet), xkey );
	     fputc( '\n', stream );
	     }
      }
 fclose( stream );
}
