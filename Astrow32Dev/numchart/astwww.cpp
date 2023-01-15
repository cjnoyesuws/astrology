#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <share.h>
#include "chartinf.h"
#include "attrib.h"
#include "output.fns"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"
#include "errors.fns"

static char *accents[128] = {"&iexcl;","&cent;","&pound;","&curren;","&yen;","&brvbar;","&sect;","&uml;","&COPY;","&ordf;","&laquo;","&SHY;","&REG;","&hibar;","&deg;","&plusmn;","&sup2;","&sup3;","&acute;","&micro;","&para;","&cedil;","&sup1;","&ordm;","&raquo;","&frac14;","&frac12;","&frac34;","&iquest;","&Agrave;","&Aacute;","&Acirc;","&Atilde;","&Auml;","&Aring;","&AElig;","&Ccedil;","&Egrave;","&Eacute;","&Ecirc;","&Euml;","&Igrave;","&Iacute;","&Icirc;","&Iuml;","&ETH;","&Ntilde;","&Ograve;","&Oacute;","&Ocirc;","&Otilde;","&Ouml;","&times;","&Oslash;","&Ugrave;","&Uacute;","&Ucirc;","&Uuml;","&Yacute;","&THORN;","&szlig;","&agrave;","&aacute;","&acirc;","&atilde;","&auml;","&aring;","&aelig;","&ccedil;","&egrave;","&eacute;","&ecirc;","&euml;","&igrave;","&iacute;","&icirc;","&iuml;","&eth;","&ntilde;","&ograve;","&oacute;","&ocirc;","&otilde;","&ouml;","&divide;","&oslash;","&ugrave;","&uacute;","&ucirc;","&uuml;","&yacute;","&thorn;","&yuml;" };

char titlebuf[200];

void settitle( char *p )
{
strcpy(titlebuf,p);
}


void TextConvDriverHTML::finishUpJob()
{
fprintf(ostream,"</DIV></BODY>\n</HTML>\n" );
}


void TextConvDriverHTML::initDriver( FIL_ATTRIB *a )
{
 atrb.head_on[0] = '\0';
 atrb.head_off[0] = '\0';
 strcat( atrb.head_on, "<60>/DIV<62><60>center<62><60>H2<62>" );
 strcat( atrb.head_off, "<60>/H2<62><60>/center<62><60>DIV<62>" );
 strcpy( atrb.bold_on, "<60>B<62>" );
 strcpy( atrb.bold_off, "<60>/B<62>" );
 strcpy( atrb.uscore_on, "<60>U<62>" );
 strcpy( atrb.uscore_off, "<60>/U<62>" );
 setCrs("<P>", " ");
}



int TextConvDriverHTML::foreign( unsigned char c )
{
 if ( c == 32 )
	 fputc(' ', ostream );
 else if ( c < 255 && c > 160 )
	 fprintf( ostream, "%s", accents[c-161] );
 else	
     fprintf( ostream, "&#%d", (int) c );
 return( 0 );
}



void TextConvDriverHTML::initStringPrint( int left, int width )
{
 FILE *hs;
 int c;
 char buf[202];
 margin = "";
 fprintf(ostream,"<HTML>\n<HEAD><TITLE>%s</TITLE>", titlebuf);
 hs = fopen("./numero.css","rt");
 if ( hs != NULL ) {
	 do {
		 c = fgetc(hs);
		 if ( c != EOF )
			 fputc(c,ostream);
	 } while ( c != EOF );
	 fclose (hs);
 }
 fprintf(ostream,"</HEAD>\n<BODY><DIV>" );
}



