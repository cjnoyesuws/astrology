#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <share.h>
#include "attrib.h"
#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"
#include "errors.fns"



void TextConvDriverHTML::finishUpJob()
{
fprintf(ostream,"</BODY>\n</HTML>\n" );
}


void TextConvDriverHTML::initDriver( FIL_ATTRIB *a )
{
 atrb.head_on[0] = '\0';
 atrb.head_off[0] = '\0';
 strcat( atrb.head_on, "<60>H2<62>" );
 strcat( atrb.head_off, "<60>/H2<62>" );
 strcpy( atrb.bold_on, "<60>B<62>" );
 strcpy( atrb.bold_off, "<60>/B<62>" );
 strcpy( atrb.uscore_on, "<60>U<62>" );
 strcpy( atrb.uscore_off, "<60>/U<62>" );
 setCrs("<P>", " ");
}



int TextConvDriverHTML::foreign( unsigned char c )
{
 fprintf( ostream, "&#%d", (int) c );
 return( 0 );
}



void TextConvDriverHTML::initStringPrint( int left, int width )
{
 FILE *hs;
 char buf[202];
 margin = "";
 fprintf(ostream,"<HTML>\n<HEAD><TITLE>%s</TITLE></HEAD>\n", name);
 fprintf(ostream,"<BODY>" );
}



