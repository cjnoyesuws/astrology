#include "stdafx.h"
#include <stdlib.h>
#include <ctype.h>
#include "output.fns"
#include "attrib.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"

int TextConvDriver::op_make_printer_string( char *instring, FILE *outstream )
{
#ifdef _UNICODEVER
	if ( Unicode16LEFile )
       ::wc_op_make_printer_string( instring, outstream );
	else
	   ::op_make_printer_string( instring, outstream );
#else
	::op_make_printer_string( instring, outstream );
#endif
 return 1; 
}

int TextConvDriver::fputcs(char *s,FILE *out)
{
#ifdef _UNICODEVER
  
  if ( Unicode16LEFile ) {
	  wchar_t bf[5];
	  mbtowc(bf,s,1);
	  return ( fputwc(bf[0],out) );
    }
  else
	 return( fputc(*s,out) );
#else
	 return( fputc(*s,out) );
#endif
}

int TextConvDriver::fputcsw(char *s,FILE *out)
{
#ifdef _UNICODEVER
  
  if ( Unicode16LEFile ) {
	  int len = _mbslen((const unsigned char *)s);
	  wchar_t *bf;
      bf = new wchar_t[len+1];
	  mbtowc(bf,s,len);
	  bf[len] = L'\0';
	  int ret = fputws(bf,out);
	  delete bf;
	  return ret;
    }
  else
	 return( fputs(s,out) );
#else
	 return( fputs(s,out) );
#endif
}

int TextConvDriver::foreign(unsigned char the_char)
{
 unsigned char bf[10];
 if ( ansi && toOem ) {
    bf[0] = the_char;
    bf[1] = '\0';
    CharToOemBuff( (char *)bf, (char *)&bf[5], 1 );
    the_char = bf[5];
    }
 else if ( !ansi && !toOem ) {
    bf[0] = the_char;
    bf[1] = '\0';
    OemToCharBuff( (char *)bf, (char *)&bf[5], 1 );
    the_char = bf[5];
    }
 return( fputc( the_char, ostream ) ); 
}


void TextConvDriverXYW::initDriver( FIL_ATTRIB *a )
{
 atrb.head_on= "\xaeMDBO\xaf\xaeMDUL\xaf";
 atrb.head_off= "\xaeMDNM\xaf"; 
 atrb.bold_on= "\xaeMDBO\xaf";
 atrb.bold_off= "\xaeMDNM\xaf";
 atrb.uscore_on=  "\xaeMDUL\xaf";
 atrb.uscore_off= "\xaeMDNM\xaf";
}

void TextConvDriverPlainAscii::initDriver( FIL_ATTRIB *a )
{
 atrb.head_on= "";
 atrb.head_off= "";
 atrb.bold_on= "";
 atrb.bold_off= "";
 atrb.uscore_on=  "";
 atrb.uscore_off= "";
}

void TextConvDriver::initStringPrint(int left, int width, int version, int code )
{
 char mb[50];

 left /= 10;
 memset( mb, ' ', left );
 mb[left] = '\0';
 margin = strdup( mb );
 setCrs( "\n", "\n" );
 ul_mode = 0;
 bold_mode = 0;
 head_mode = 0;
 if ( left )
    fputcsw( margin, ostream );
}

int TextConvDriver::stringPrint( char *string )
{
 unsigned char l;
 char *cp = string;
 int v;

 do {
    switch( *cp ) {
	  case '@' :
		   if ( !strnicmp(cp,"@GF",3) ) {
			   GlyphFont( *(cp+3)-'0' );
			   cp+= 3;
		       }
		   else if ( !strnicmp(cp,"@GS",3) ) {
	           v = (*(cp+3)-'0')*10;
			   v += *(cp+4)-'0';
			   SignGlyph(v);
			   cp+=5;
		       }
           else if ( !strnicmp(cp,"@GP",3) ) {
	           v = (*(cp+3)-'0')*10;
			   v += *(cp+4)-'0';
			   PlanetGlyph(v);
			   cp+=5;
		       }
		   else
               fputcs(cp,ostream);
		   break;
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
		   //if ( bTableMode == TRUE )
			//   break;
	      if ( Unicode16LEFile ) { 
		     fputcsw( soft_crs, ostream );
	          if ( margin != NULL )
		         fputcsw( margin, ostream );
		  }
		  else {
			  fputs( soft_crs, ostream );
	          if ( margin != NULL )
		         fputs( margin, ostream );
		  }
	       break;
	  case F_HARDCR :
		   //if ( bTableMode == TRUE )
			//   break;
		  if ( Unicode16LEFile ) { 
		      fputcsw( hard_crs, ostream );
	          if ( margin != NULL )
		         fputcsw( margin, ostream );
		  }
		  else {
	          fputs( hard_crs, ostream );
	          if ( margin != NULL )
		         fputs( margin, ostream );
		  }
	       break;
	  case F_STARTUL :
	       ul_mode = 1;
	       op_make_printer_string( (char *)(LPCTSTR)atrb.uscore_on, ostream );
	       break;
	  case F_ENDUL :
	       ul_mode = 0;
	       op_make_printer_string( (char *)(LPCTSTR)atrb.uscore_off, ostream );
	       break;
	  case F_STARTBD :
	       bold_mode = 1;
	       op_make_printer_string( (char *)(LPCTSTR)atrb.bold_on, ostream );
	       break;
	  case F_ENDBD :
	       bold_mode = 0;
	       op_make_printer_string( (char *)(LPCTSTR)atrb.bold_off, ostream );
	       break;
	  case F_STARTHD :
	       head_mode = 1;
	       op_make_printer_string( (char *)(LPCTSTR)atrb.head_on, ostream );
	       break;
	  case F_ENDHD :
	       head_mode = 0;
	       cp +=4;
	       op_make_printer_string( (char *)(LPCTSTR)atrb.head_off, ostream );
	       break;
	  case F_TAB :
	       fputcs( " ", ostream );
	       break;
	  case '\0' :
	       return( ferror( ostream ) );
	       break;
	  default :
	       fputcs( cp, ostream );
	       break;
	  }
     } while ( *++cp );
 return( ferror( ostream ) );
}
