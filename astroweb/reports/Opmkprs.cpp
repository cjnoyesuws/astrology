#error "don't include OPMKPRS from engine"
#include "stdafx.h"
#include <stdlib.h>
#include <ctype.h>
#include "astro.h"
#include "useri.h"
#include "output.fns"
#include "attrib.h"
#include "prtrdrv.h"
#include "basedcs.h"
#include "prtrdrv.fns"
#include "charcons.h"
#include "astro.fns"

FIL_ATTRIB global_attribs;

int def_foreign( FILE *stream, unsigned char the_char )
{
 return( fputc( the_char, stream ) );
}

int op_make_printer_string( char *instring, FILE *outstream )
{
 char *inptr;
 int  val, count;

 if ( outstream == NULL )
    return( -1 );
 count = 0;
 if ( *instring == '\0' ) {
    return( count );
    }
 for ( inptr = instring; *inptr; inptr++ ) {
     if ( *inptr != '<' && *inptr != '>' ) {
	if ( fputc( *inptr, outstream ) == EOF )
	   return( -1 );
	++count;
	}
     else if ( *inptr != '>' ) {
	val = atoi( inptr+1 );
	if ( fputc( (char) val, outstream ) == EOF )
	   return( -1 );
	++inptr;
	++count;
	while ( *inptr && isdigit( *inptr ) )
	      ++inptr;
	}
     }
 if ( fflush( outstream ) == EOF )
    return( -1 );
 return( count );
}

void init_driver( struct OUTP_DRV *d, FIL_ATTRIB *a )
{
 d->atrb = &global_attribs;
}

void init_driver_set( struct OUTP_DRV *d, FIL_ATTRIB *a )
{
 d->atrb = a;
}

void init_driver_none( struct OUTP_DRV *d, FIL_ATTRIB *a )
{
 memset( &global_attribs, 0, sizeof( FIL_ATTRIB ) );
 d->atrb = &global_attribs;
}

#define WD_PR 16

int def_prn_head( FILE *stream, FILE_DB *ptr, int page, int ff,
						     int left, int width )
{
 extern char far types[][15];
 static char BCS pf1[] = { "%s%sName: %s%s    Page: %d%s" };
 static char BCS pf2[] = {   "%sComments: %s%sType: %s%s%s" };
 static char BCS pf3[] = { " NOW PRINTING PAGE %d...Press ESC to Quit! " };
 int nw, cw, tw;
 char spaces[200];
 char margin[40];

 left *= print_setup_dat.hp_font.dot_pitch;
 left /= 100;
 width *= print_setup_dat.hp_font.dot_pitch;
 width /= 100;
 if ( left ) {
    memset( margin, ' ', left );
    margin[left] = '\0';
    }
 else
    margin[0] = '\0';
 tw = strlen(types[ptr->type]);
 cw = strlen( ptr->comment ) + tw + WD_PR;
 nw = strlen( ptr->name ) + tw + WD_PR;

 if ( ff )
    fputc( 12, stream );
 if ( width - nw > 0 ) {
    memset( spaces, ' ', width-nw );
    spaces[width-nw] = '\0';
    }
 else
    spaces[0] = '\0';
 fprintf( stream, (char _far *) pf1, lfcr[print_setup_dat.lfcr], margin,
    ptr->name, spaces, page,  lfcr[print_setup_dat.lfcr] );
 if ( width - cw > 0 ) {
    memset( spaces, ' ', width-cw );
    spaces[width-cw] = '\0';
    }
 else
    spaces[0] = '\0';
 fprintf( stream, (char _far *) pf2, margin, ptr->comment, spaces,
    types[ptr->type], lfcr[print_setup_dat.lfcr], margin );
 memset( spaces, '_', width );
 spaces[width] = 0;
 fputs( spaces, stream );
 fputs( lfcr[print_setup_dat.lfcr], stream );
 fputs( lfcr[print_setup_dat.lfcr], stream );
 fputs( margin, stream );
 fflush( stream );
 do_msg( (char _far *) pf3, page );
 return( 5 );
}
