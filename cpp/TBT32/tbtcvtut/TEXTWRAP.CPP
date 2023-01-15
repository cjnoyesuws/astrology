#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"

static unsigned char soft_cr = '\n';
static unsigned char hard_cr = '\r';

void setcrs( unsigned char scr, unsigned char hcr )
{
 if ( scr == 0 ) {
    soft_cr = '\n';
    hard_cr = '\n';
    return;
    }
 soft_cr = scr;
 hard_cr = hcr;
}

/* function to rag a string of text to the desired width. Does no
   hyphenation. Just replaces the space at the point just prior to
   the desired width with a '\n'. '\n's currently in text reset the
   the counter. Function alters the input string. Use strwrap() for
   situatons when input string should not be altered.
*/
   
int text_wrap( char *string, int width )
{
 char *space = NULL;
 unsigned char *str;
 int counter, lines = 0;

 for ( str = (unsigned char *)string, counter = 0; *str; ++str ) {
     if ( *str == ' ' ) {
        ++counter;
        space = (char *)str;
        }
     else
	counter++;
     if ( counter >= width && space != NULL ) {  /* wait for non-space */
	*space = soft_cr;
        counter = 0;
        ++lines;
        str = (unsigned char *)space;
        space = NULL; 
        }
     }
 *(str-1) = '\0';
 return( lines );
}
