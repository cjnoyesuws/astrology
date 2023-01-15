#include "stdafx.h"
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "astro.h"
#include "useri.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "virttext.hpp"
#include "errors.fns"
#include "fptr.h"
#include "paths.hpp"


void VirtualTextBuffer::setupSearch( char *bufu, char *bufl, char *search )
{
#ifdef PRO
 char *b;
 unsigned char *p;

 for ( p = (unsigned char *)search, b = bufu; *p != '\0'; p++, b++ ) {
     if ( *p > 128 || *p < ' ' ) {
	*b++ = '~';
	*b = *p;
	}
     else
	*b = *p;
     }
 *b++ = '\0';
 AnsiUpper(bufu);
 strcpy( bufl, bufu );
 AnsiLower(bufl);
#endif
}


int VirtualTextBuffer::matchText(char *buf, int len, char *searchu, char *searchl)
{
#ifdef PRO
 char cb[5];
 char *p, c, c2;
 int i, l, j;


 for ( i = 0, p = buf; i < len; i++, p++ ) {
     if ( searchl[0] == *p || searchu[0] == *p  )
	break;
     }
 if ( i >= len )
    return( 0 );
 l = strlen( searchl );
 if ( len - i < l )
    return( 0 );
 j = 1;
 p++;
 for ( j = 1; i < len && j < l; i++, p++, j++ ) {
     if ( strchr( "<>{}[]^\n\x80|", *p) != NULL ) {
	p++;
	continue;
	}
     if ( searchl[j] != *p && searchu[j] != *p  )
	return( 0 );
     }
#endif
 return( 1 );
}

int VirtualTextBuffer::findFirst(char *find)
{
 return( findCont(find, 0 ) );
}

int VirtualTextBuffer::findCont(char *find, int paraStart)
{
#ifdef PRO
 char bufu[100], bufl[100];
 int par, len, count = getParaCount();
 unsigned char dummy;
 char *text;

 setupSearch( bufu, bufl, find );
 for ( par = paraStart; par < count; par++ ) {
     text = getText( par, len, dummy );
     if ( matchText( text, len, bufu, bufl ) )
	return( par );
     }
#endif
 return( -1 );
}

