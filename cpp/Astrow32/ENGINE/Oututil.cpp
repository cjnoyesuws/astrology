#include "stdafx.h"
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "dataext.h"
#include "charcons.h"
#include "utlduad.h"
#include "oututil.h"
#include "outfunc.fns"
#include "output.fns"

void _opecaps(FILE *f, const char *s, char *b, int &cap)
{
 if ( s == NULL )
	 return;
 if ( cap ) {
    fputs( xstrupr(enquote_strclip((unsigned char *)s,(unsigned char *)b)), f);
    cap = 0;
    }
 else
    fputs( enquote_strclip((unsigned char *)s, (unsigned char *)b), f );
}

void _opcaps( FILE *f, const char *s, char *b, int &cap)
{
 if ( s == NULL )
	 return;
 if ( cap ) {
    strcpy(b, s);
    fputs( xstrupr(b), f);
    cap = 0;
    }
 else
    fputs( s, f );
}

void _opnum( FILE *f, int n, int v, int &cap)
{
 if ( cap ) {
    fprintf( f, "%*d", n, v );
    cap = 0;
    }
 else fprintf( f, "%d", v );
}


void _opnum0( FILE *f, int n, int v, int &cap)
{
 if ( cap ) {
    fprintf( f, "%0*d", n, v );
    cap = 0;
    }
 else
    fprintf( f, "%d", v );
}
