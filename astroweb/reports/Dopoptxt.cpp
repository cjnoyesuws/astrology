#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "textptr.h"
#include <assert.h>
#include "errors.fns"
#include "output.fns"
#include <string.h>
#include "errors.fns"
#include <assert.h>
#include "charcons.h"
#include "paths.hpp"
#include "astro.h"
#include "useri.h"
#include <stdlib.h>
#include "outfunc.fns"
#include "aspect.h"
#include "textptr.h"

static short table;
static short init;

void init_popup_text_report()
{
 if ( table == -1 || !init ) {
    table = tb_open_file( "GLOBAL" );
    init++;
    }
 else
    init++;
}

void close_text_report()
{
 if ( init > 1 )
    init--;
 else if ( table != -1 ) {
    init--;
    tb_close_table(table);
    table = -1;
    }
 else if ( table == -1 && init )
    init = 0;
}

char *get_aspect_text_file( int type )
{
 char *files[] = {"", ASPECT_FILE, COMPAT_ASPECTS, TRANSITS_ASPECTS, PROGRESS_ASPECTS, ASPECT_FILE, ASPECT_FILE, ASPECT_FILE, ASPECT_FILE };
 type -= LAST_NON_GRAPH;

 return( files[type] );
}

static int mapAspect(int a)
{
 int map[] = { OPPOSITION, TRINE, SEXTILE, CONJUNCT, SQUARED };

 if ( a < 5 )
    return( map[a] );
 else
    return( a );
}


int get_aspect_text( char *file, int first, int second, int aspect, int type )
{
 char *p;
 FILE *stream;
 int f, r = 0;

 if ( ( stream = fopen( file, "wb" ) ) == NULL ) {
    do_error( file );
    return( 0 );
    }
 p = get_aspect_text_file( type );
 std::string str(p);
 if ( ( f = open_asp_files( str ) ) == -1 ) {
    do_error( p );
    fclose( stream );
    return( 0 );
    }
 output_sex_codes( stream, 0, 1, table );
 output_sex_codes( stream, 0, 2, table );
 fprintf( stream, "Planet: %s, Aspect: %s, Planet: %s.\r\n",
	  planet_str(first), aspect_str(aspect), planet_str(second) );
 if ( get_transfer_text_asp( second, first, aspect, f, stream ) ) {
    r = get_transfer_text_asp( first, second, aspect, f, stream );
    if ( r && (first == IM_COELI || first == SOUTH_NODE) )
       r = get_transfer_text_asp( first-1, second, mapAspect(aspect), f, stream );
    else if ( r && (second == IM_COELI || second == SOUTH_NODE) )
       r = get_transfer_text_asp( second-1, first, mapAspect(aspect), f, stream );
    if ( r ) {
       close_files( f );
       fclose( stream );
       remove( file );
       return(0);
       }
    }
 fputc( '\r', stream );
 fputc( '\n', stream );
 close_files_asp( f );
 fclose( stream );
 return( 1 );
}

char *get_house_text_file_name( int type )
{
 type -= LAST_NON_GRAPH;

 char *files[] = {"", HOUSE_FILE, COMPAT_HOUSES, TRANSITS_HOUSES, HOUSE_FILE, HOUSE_FILE, HOUSE_FILE, HOUSE_FILE, HOUSE_FILE  };

 return( files[type] );
}

int get_text( char *file, int planet, int house, int sign, int psign, int min, int type )
{
 FILE *stream;
 char buf[10], *p;
 int fps=-1, fhn=-1, fhs=-1;

 if ( (planet == -1 && house < 0 ) ||
	(planet == -1 && house < 0 && sign == -1) )
    return( 0 );
 if ( ( stream = fopen( file, "wb" ) ) == NULL ) {
    do_error( file );
    return( 0 );
    }
 if ( planet != -1 ) {
    format_degs( abs(min), buf );
    if ( min < 0 )
       strcat( buf, "R" );
    if ( (fps = open_files( PLANET_FILE ) ) == -1 ) {
       do_error( PLANET_FILE );
       fclose( stream );
       unlink( file );
       return( 0 );
       }
    if ( house > 0 ) {
       p = get_house_text_file_name( type );
       if ( (fhn = open_files( p ) ) == -1 ) {
	  do_error( p );
	  fclose( stream );
	  unlink( file );
	  return( 0 );
	  }
       }
    }
 if ( sign != -1 ) {
    if ( (fhs = open_files( SIGN_HOUSE_FILE ) ) == -1 ) {
       do_error( SIGN_HOUSE_FILE );
       fclose( stream );
       unlink( file );
       return( 0 );
       }
    }
 output_sex_codes( stream, 0, 1, table );
 output_sex_codes( stream, 0, 2, table );
 if ( planet != -1 ) {
    fprintf( stream, "Your %s is in the Sign %s.\r\n", planet_str(planet),
	 sign_str(psign) );
    fprintf( stream, "Position: %s\r\n", buf );
    if ( type == TRANSITS_GRAPH_FILE ) {
       get_transfer_text( 12, planet, fhn, stream );
       }
    else {
       get_transfer_text( psign, planet, fps, stream );
       }
    if ( house > 0 ) {
       fprintf( stream, "\r\nYour %s is in House # %d.\r\n", planet_str(planet),
	   house );
       if ( type == TRANSITS_GRAPH_FILE ) {
	  get_transfer_text( house-1, planet, fhn, stream );
	  }
       else
	  get_transfer_text( house, planet, fhn, stream );
       }
    }
 fputc( '\r', stream );
 fputc( '\n', stream );
 if ( house > 0 ) {
    fprintf( stream, "Your House # %d is in the Sign %s.\r\n", house,
	sign_str(sign) );
    get_transfer_text( sign, house, fhs, stream );
    }
 if ( house == -2 )
    fprintf( stream, "Select the Other Set of house Cusps to see the House information." );
 fputc( '\r', stream );
 fputc( '\n', stream );
 if ( fhn != -1 )
    close_files( fhn );
 if ( fhs != -1 )
    close_files( fhs );
 if ( fps != -1 )
    close_files( fps );
 fclose( stream );
 return( 1 );
}

