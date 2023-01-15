#include <Windows.h>
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


//File New
InitTkn( 0 );
SendTkn( WP_FileNew );
FreeTkn( );
//File Dlg
InitTkn( 0 );
SendTkn( WP_FileSaveAsDlg );
FreeTkn( );
//Reg font
InitTkn( 8 );
lpwzBuf = (LPWZ)AllocPtr( (int)32, GHND );
lpfnW6azTowz( (LPSTR)"Times New Roman", lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
AddTknParm( 1, eParmEnumeration, 0x0000, (PARAMETER)2304 );
AddTknParm( 2, eParmEnumeration, 0x0000, (PARAMETER)0 );
AddTknParm( 3, eParmEnumeration, 0x0000, (PARAMETER)96 );
AddTknParm( 4, eParmEnumeration, 0x0000, (PARAMETER)112 );
AddTknParm( 5, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 6, eParmEnumeration, 0x0000, (PARAMETER)139 );
AddTknParm( 7, eParmEnumeration, 0x0000, (PARAMETER)0 );
SendTkn( WP_Font );
FreeTkn( );
//Regular Font
InitTkn( 8 );
lpwzBuf = (LPWZ)AllocPtr( (int)32, GHND );
lpfnW6azTowz( (LPSTR)"Times New Roman", lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
AddTknParm( 1, eParmEnumeration, 0x0000, (PARAMETER)2304 );
AddTknParm( 2, eParmEnumeration, 0x0000, (PARAMETER)1 );
AddTknParm( 3, eParmEnumeration, 0x0000, (PARAMETER)96 );
AddTknParm( 4, eParmEnumeration, 0x0000, (PARAMETER)112 );
AddTknParm( 5, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 6, eParmEnumeration, 0x0000, (PARAMETER)139 );
AddTknParm( 7, eParmEnumeration, 0x0000, (PARAMETER)0 );
SendTkn( WP_Font );
FreeTkn( );
//Bold
InitTkn( 8 );
lpwzBuf = (LPWZ)AllocPtr( (int)32, GHND );
lpfnW6azTowz( (LPSTR)"Times New Roman", lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
AddTknParm( 1, eParmEnumeration, 0x0000, (PARAMETER)2304 );
AddTknParm( 2, eParmEnumeration, 0x0000, (PARAMETER)1 );
AddTknParm( 3, eParmEnumeration, 0x0000, (PARAMETER)144 );
AddTknParm( 4, eParmEnumeration, 0x0000, (PARAMETER)112 );
AddTknParm( 5, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 6, eParmEnumeration, 0x0000, (PARAMETER)139 );
AddTknParm( 7, eParmEnumeration, 0x0000, (PARAMETER)0 );
SendTkn( WP_Font );
FreeTkn( );
//Italic
InitTkn( 8 );
lpwzBuf = (LPWZ)AllocPtr( (int)32, GHND );
lpfnW6azTowz( (LPSTR)"Times New Roman", lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
AddTknParm( 1, eParmEnumeration, 0x0000, (PARAMETER)2304 );
AddTknParm( 2, eParmEnumeration, 0x0000, (PARAMETER)1 );
AddTknParm( 3, eParmEnumeration, 0x0000, (PARAMETER)96 );
AddTknParm( 4, eParmEnumeration, 0x0000, (PARAMETER)112 );
AddTknParm( 5, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 6, eParmEnumeration, 0x0000, (PARAMETER)139 );
AddTknParm( 7, eParmEnumeration, 0x0000, (PARAMETER)0 );
SendTkn( WP_Font );
FreeTkn( );
//Headline
InitTkn( 8 );
lpwzBuf = (LPWZ)AllocPtr( (int)32, GHND );
lpfnW6azTowz( (LPSTR)"Arial New Roman", lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
AddTknParm( 1, eParmEnumeration, 0x0000, (PARAMETER)16640 );
AddTknParm( 2, eParmEnumeration, 0x0000, (PARAMETER)1 );
AddTknParm( 3, eParmEnumeration, 0x0000, (PARAMETER)144 );
AddTknParm( 4, eParmEnumeration, 0x0000, (PARAMETER)112 );
AddTknParm( 5, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 6, eParmEnumeration, 0x0000, (PARAMETER)139 );
AddTknParm( 7, eParmEnumeration, 0x0000, (PARAMETER)0 );
SendTkn( WP_Font );
FreeTkn( );
//Insert Tab
TextInitTkn( 0 );
SendTkn( WP_TabInsert );
FreeTkn( );
//Insert Text
InitTkn( 1 );
lpwzBuf = (LPWZ)AllocPtr( (int)34, GHND );
lpfnW6azTowz( (LPSTR)"This is the text", lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
SendTkn( WP_Type );
FreeTkn( );
//Hard Return;
InitTkn( 0 );
SendTkn( WP_HardReturn );
FreeTkn( );

//Clear Tabs
InitTkn( 0 );
SendTkn( WP_TabClearAll );
FreeTkn( );
//Insert Tab
InitTkn( 3 );
AddTknParm( 0, eParmWPUUnsigned, 0x0000, (PARAMETER)1800 );
AddTknParm( 1, eParmEnumeration, 0x0000, (PARAMETER)0 );
AddTknParm( 2, eParmWPUUnsigned, 0x0000, (PARAMETER)0 );
SendTkn( WP_TabAdd );
FreeTkn( );
//font no family
InitTkn( 8 );
lpwzBuf = (LPWZ)AllocPtr( (int)32, GHND );
lpfnW6azTowz( (LPSTR)"Times New Roman", lpwzBuf );
AddTknParm( 0, eParmStringWord, 0x0000, (PARAMETER)lpwzBuf );
FreePtr( lpwzBuf );
AddTknParm( 1, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 2, eParmEnumeration, 0x0000, (PARAMETER)0 );
AddTknParm( 3, eParmEnumeration, 0x0000, (PARAMETER)96 );
AddTknParm( 4, eParmEnumeration, 0x0000, (PARAMETER)112 );
AddTknParm( 5, eParmEnumeration, 0x8000, (PARAMETER)0 );
AddTknParm( 6, eParmEnumeration, 0x0000, (PARAMETER)139 );
AddTknParm( 7, eParmEnumeration, 0x0000, (PARAMETER)0 );
SendTkn( WP_Font );
FreeTkn( );
