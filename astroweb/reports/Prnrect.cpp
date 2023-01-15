#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "output.fns"
#include "charcons.h"
#include "dataext.h"

extern char *angles[];

void print_rect_data( FILE *stream, RECT_DATA *rd )
{
 char buf[25];

 if ( rd->birth_time_known )
    return;
 fprintf( stream, btunknownstr, rectstr[rd->rect_system] );
 fprintf( stream, "\x80Trial Birth Time: {%s}.\x80",
    make_time( &rd->trial, rd->am_pm ) );
#ifndef LITE
 if ( rd->rect_system == KNOWN_ANGL ) {
    fprintf( stream, "Based on Angle {%s} using {%s}.\n\n",
	angles[rd->angle-1], format_degs( rd->total_minutes, buf ) );
    }
#endif
}
