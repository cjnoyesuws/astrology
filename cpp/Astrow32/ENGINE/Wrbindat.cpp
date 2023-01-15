#include "stdafx.h"
#include <share.h>
#include "errors.fns"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "arabpt.h"
#include "fixstar.h"
#include "output.fns"
#include "flags.h"

/* 09/10/92  Modified for C++ Windows  Zapp */

int bin_write_header( FILE *stream, short mode, short ch_code, BIRTH_DB *d, RECT_DATA *rd, PROGR_DATA *pd, DIREC_DATA *dd )
{
 fwrite( &mode, sizeof( short ), 1, stream );
 fwrite( &ch_code, sizeof( short ), 1, stream );
 fwrite( d, sizeof( struct BIRTH_DB ), 1, stream );
 fwrite( rd, sizeof( struct RECT_DATA ), 1, stream);
 fwrite( pd, sizeof( struct PROGR_DATA ), 1, stream);
 fwrite( dd, sizeof( struct DIREC_DATA ), 1, stream);
 return ( 0 );
}


int bin_write_aspects( FILE *stream, int count, AS_INF *infp )
{
 AS_INF *inf;
 int i, e;

 for ( i = 0, inf = infp; i < count; ++i, ++infp ) {
     if ( infp->aspectr != NULL )
	e = fwrite( inf->aspectr, sizeof( struct ASPEC ), inf->no_aspects, stream );
     }
 return( e );
}

int bin_write_midpoint( FILE *stream, int count, AS_INF *inf )
{
 int i, j, k;
 AS_INF *as;
 MIDPT *md, *m;

 for ( i = 0, as = inf; i < count; ++i, ++as ) {
     if ( as->midptr != NULL )
	fwrite( as->midptr, sizeof( struct MIDPT ), as->no_midpt, stream );
     }
 for ( i = 0, as = inf; i < count; ++i, ++as ) {
     if ( as->midptr != NULL ) {
	md = as->midptr;
	j = as->no_midpt;
	for ( k = 0, m = md; k < j; ++k, ++m ) {
	    if ( m->aspectr != NULL )
	       fwrite( m->aspectr, sizeof( struct ASPEC ),
			  m->no_aspect, stream );
	    }
	}
     }
 return( ferror( stream ) );
}

FILE *get_bin_file( char **n )
{
 FILE *stream;
 static char name[250];
 char types[] = { "Data Files (*.DAT)|*.DAT|Binary Files (*.BIN)|*.BIN|"
   "All Files (*.*)|*.*||\0\0" };

 *n = NULL;
 memset( name, 0,  150);
 strcpy( name, "chart.dat" );
 CFileDialog cfd(TRUE, ".DAT", name, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, types);
 cfd.m_ofn.lpstrTitle = "Binary File To Write To:";
 if ( cfd.DoModal() == IDOK ) 
	strcpy( name, cfd.GetPathName() );
 else 
	return NULL;
 *n = name;
 if ( ( stream = fopen( name, "wb" ) ) == NULL ) {
    do_error( name );
    return( NULL );
    }
 return( stream );
}


void bin_write_natal_chart( AS_INF *ast, BIRTH_DB *asd,
					BITS mode, DATA_PACKET *dpk )
{
 char *name;
 FILE *stream;

 int end;
 if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 fwrite( dpk->relocp, sizeof( struct LOC_DB ), 1, stream );
 fwrite( ast, sizeof( struct AS_INF ), end, stream );
 fwrite( house_cusps, 2, 13, stream );
 bin_write_aspects( stream, end, ast );
 bin_write_midpoint( stream, end, ast );
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_compat_chart( AS_INF *ast, AS_INF *pai,
	 BIRTH_DB *asd, BIRTH_DB *pad, BITS mode, DATA_PACKET *dpk )
{
 char *name;
 FILE *stream;
 int end;
 if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 bin_write_header( stream, mode, dpk->chart_code, pad, dpk->crdp, dpk->pdp, dpk->ddp );
 fwrite( ast, sizeof( struct AS_INF ), end, stream );
 fwrite( pai, sizeof( struct AS_INF ), end, stream );
 fwrite( house_cusps, 2, 13, stream );
 fwrite( alt_cusps, 2, 13, stream );
 bin_write_aspects( stream, end, ast );
 bin_write_aspects( stream, end, pai );
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_compos_chart( AS_INF *ast, BIRTH_DB *asd,
      BIRTH_DB *pad, BITS mode, DATA_PACKET *dpk )
{
 char *name;
 FILE *stream;
 int end;
 if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 bin_write_header( stream, mode, dpk->chart_code, pad, dpk->crdp, dpk->pdp, dpk->ddp );
 fwrite( ast, sizeof( struct AS_INF ), end, stream );
 fwrite( house_cusps, 2, 13, stream );
 bin_write_aspects( stream, end, ast );
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_solar_chart( AS_INF *ast, AS_INF *sinf, BIRTH_DB *asd,
     BITS mode, DATA_PACKET *dpk )
{
 char *name;
 FILE *stream;
 int end;
 if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 fwrite( ast, sizeof( struct AS_INF ), end, stream );
 fwrite( sinf, sizeof( struct AS_INF ), end, stream );
 fwrite( house_cusps, 2, 13, stream );
 fwrite( alt_cusps, 2, 13, stream );
 bin_write_aspects( stream, end, ast );
 bin_write_aspects( stream, end, sinf );
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_harmonic_chart( AS_INF *ast, AS_INF *hinf, BIRTH_DB *asd,
     BITS mode, DATA_PACKET *dpk )
{
 char *name;
 FILE *stream;
 int end;
 if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 fwrite(dpk->harmonic,4,1,stream);
 fwrite( ast, sizeof( struct AS_INF ), end, stream );
 fwrite( hinf, sizeof( struct AS_INF ), end, stream );
 fwrite( house_cusps, 2, 13, stream );
 fwrite( alt_cusps, 2, 13, stream );
 bin_write_aspects( stream, end, ast );
 bin_write_aspects( stream, end, hinf );
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_trans_chart( AS_INF *ast, BIRTH_DB *asd, BIRTH_DB *trd,
		 BITS mode, DATA_PACKET *dpk )
{
 int i, j, k, ep;
 char *name;
 AS_INF **ip;
 FILE *stream;
 if ( mode & ASTEROID )
	 ep = CHIRON;
 else
	 ep = EAST_POINT;
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 fwrite( trd, sizeof( struct BIRTH_DB ), 1, stream );
 fwrite( dpk->tdp, sizeof( struct TRANS_DATA ), 1, stream );
 fwrite( date_ptr, sizeof( struct DATES ), dpk->tdp->num_transits, stream );
 
 fwrite( ast, sizeof( struct AS_INF ), ep, stream );
 fwrite( house_cusps, 2, 13, stream );
 fwrite( alt_cusps, 2, 13, stream );
 k = dpk->tdp->end_planet - dpk->tdp->start_planet +1;
 fwrite( *trans_ptr, sizeof( struct AS_INF ), ep-SUN, stream );
 for ( i = 2, ip = trans_ptr+1; i <= dpk->tdp->num_transits; i++, ip++ )  {
     fwrite( *ip, sizeof( struct AS_INF ), k, stream );
     }
 bin_write_aspects( stream, ep-SUN, *trans_ptr );
 for ( i = 1, ip = trans_ptr+1; i <= dpk->tdp->num_transits; i++, ip++ )  {
     for ( j = dpk->tdp->start_planet;
			 j <= dpk->tdp->end_planet; j++ )
	 bin_write_aspects( stream, k, *ip );
     }
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_prog_chart( AS_INF *ast, BIRTH_DB *asd,
					BITS mode, DATA_PACKET *dpk )
{
 char *name;
 FILE *stream;
 int end;
 if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 

 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 fwrite( dpk->pdp, sizeof( struct PROGR_DATA ), 1, stream );
 fwrite( ast, sizeof( struct AS_INF ), end, stream );
 fwrite( prog, sizeof( struct AS_INF ), end, stream );
 fwrite( moon_series, sizeof( struct AS_INF ), 16, stream );
 fwrite( prog_moon_series, sizeof( struct AS_INF ), 16, stream );
 fwrite( house_cusps, 2, 13, stream );
 fwrite( alt_cusps, 2, 13, stream );
 bin_write_aspects( stream, end, ast );
 bin_write_aspects( stream, end, prog );
 bin_write_aspects( stream, 16, prog_moon_series );
 bin_write_aspects( stream, 16, moon_series );
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_arabic_chart( AS_INF *ast, BIRTH_DB *asd,
					BITS mode, DATA_PACKET *dpk )
{
 char *name;
 FILE *stream;
 int end;
 if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 fwrite( dpk->relocp, sizeof( struct LOC_DB ), 1, stream );
 fwrite( ast, sizeof( struct AS_INF ), end, stream );
 fwrite( house_cusps, 2, 13, stream );
 bin_write_aspects( stream, end, ast );

 int ac = getArabicCount();
 AS_INF far *app = getArabicParts();

 fwrite( &ac, sizeof( int ), 1, stream );
 fwrite( app, sizeof( struct AS_INF ), ac, stream );
 bin_write_aspects( stream, ac, app );
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_fixed_chart( AS_INF *ast, BIRTH_DB *asd,
					BITS mode, DATA_PACKET *dpk )
{
 char *name;
 FILE *stream;
 int end;
 if ( mode & ASTEROID )
	 end = CHIRON;
 else
	 end = EAST_POINT;
 
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header(stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 fwrite( dpk->relocp, sizeof( struct LOC_DB ), 1, stream );
 fwrite( ast, sizeof( struct AS_INF ), end, stream );
 fwrite( house_cusps, 2, 13, stream );
 bin_write_aspects( stream, end, ast );

 int fc = getFixedStarCount();
 AS_INF far *fsp = getFixedStars();

 fwrite( &fc, sizeof( int ), 1, stream );
 fwrite( fsp, sizeof( struct AS_INF ), fc, stream );
 bin_write_aspects( stream, fc, fsp  );
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}

void bin_write_cmtrans_chart( AS_INF *ast, BIRTH_DB *asd, BIRTH_DB *trd,
       BIRTH_DB *cmd, BITS mode, DATA_PACKET *dpk )
{
 int i, j, k, ep;
 char *name;
 AS_INF **ip;
 FILE *stream;
 if ( mode & ASTEROID )
	 ep = CHIRON;
 else
	 ep = EAST_POINT;
 if ( ( stream = get_bin_file( &name ) ) == NULL ) {
    return;
    }
 bin_write_header( stream, mode, dpk->chart_code, asd, dpk->rdp, dpk->pdp, dpk->ddp );
 bin_write_header( stream, mode, dpk->chart_code, cmd, dpk->crdp, dpk->pdp, dpk->ddp );
 fwrite( trd, sizeof( struct BIRTH_DB ), 1, stream );
 fwrite( dpk->tdp, sizeof( struct TRANS_DATA ), 1, stream );
 fwrite( date_ptr, sizeof( struct DATES ), dpk->tdp->num_transits, stream );
 fwrite( ast, sizeof( struct AS_INF ), ep, stream );
 fwrite( house_cusps, 2, 13, stream );
 fwrite( alt_cusps, 2, 13, stream );
 k = dpk->tdp->end_planet - dpk->tdp->start_planet +1;
 fwrite( *trans_ptr, sizeof( struct AS_INF ), ep-SUN, stream );
 for ( i = 2, ip = trans_ptr+1; i <= dpk->tdp->num_transits; i++, ip++ )  {
     fwrite( *ip, sizeof( struct AS_INF ), k, stream );
     }
 bin_write_aspects( stream, ep-SUN, *trans_ptr );
 for ( i = 2, ip = trans_ptr+1; i <= dpk->tdp->num_transits; i++, ip++ )  {
     for ( j = dpk->tdp->start_planet;
			 j <= dpk->tdp->end_planet; j++ )
	 bin_write_aspects( stream, k, *ip );
     }
 if ( ferror( stream ) )
    do_error( name );
 fclose( stream );
}
