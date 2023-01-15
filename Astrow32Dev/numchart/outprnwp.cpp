#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "output.fns"
#include "attrib.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"

extern int op_make_printer_string( char *instring, FILE *outstream );

int TextConvDriver::stringPrint( char *string )
{
 unsigned char l;
 char *cp = string;

 do {
    switch( *cp ) {
	  case '~' :
	       cp++;
	       foreign( *cp );
	       break;
	  case F_BINARY :
	       cp++;
	       l = *cp++;
	       fwrite( cp, 1, (int)l, ostream );
               cp += l -1;
	       break;
	  case F_SOFTCR :
	       fputs( soft_crs, ostream );
	       if ( margin != NULL )
		  fputs( margin, ostream );
	       break;
	  case F_KEEPCR :
	       fputs( "\\keepn", ostream );
	       fputs( hard_crs, ostream );
	       if ( margin != NULL )
		  fputs( margin, ostream );
	       break;
	  case F_HARDCR :
	       fputs( hard_crs, ostream );
	       if ( margin != NULL )
		  fputs( margin, ostream );
	       break;
	  case F_STARTUL :
	       ul_mode = 1;
	       op_make_printer_string( atrb.uscore_on, ostream );
	       break;
	  case F_ENDUL :
	       ul_mode = 0;
	       op_make_printer_string( atrb.uscore_off, ostream );
	       break;
	  case F_STARTBD :
	       bold_mode = 1;
	       op_make_printer_string( atrb.bold_on, ostream );
	       break;
	  case F_ENDBD :
	       bold_mode = 0;
	       op_make_printer_string( atrb.bold_off, ostream );
	       break;
	  case F_STARTHD :
	       head_mode = 1;
	       op_make_printer_string( atrb.head_on, ostream );
	       break;
	  case F_ENDHD :
	       head_mode = 0;
	       cp +=4;
	       op_make_printer_string( atrb.head_off, ostream );
	       break;
	  case F_TAB :
	       fputc( ' ', ostream );
	       break;
	  case '\0' :
	       return( ferror( ostream ) );
	       break;
	  default :
	       fputc( *cp, ostream );
	       break;
	  }
     } while ( *++cp );
 return( ferror( ostream ) );
}
