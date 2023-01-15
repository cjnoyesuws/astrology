#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <stdlib.h>
#include <io.h>
#include "chartinf.h"
#include "name.h"
#include "namegraf.h"
#include "numbr.h"
#include "attrib.h"
#include "errors.fns"
#include "output.fns"
#include "charcons.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "prtrdrv.hpp"
#include "asfil2tx.hpp"

//FILE_ID file_info;

COLORREF colors[4];
COLORREF *pColors = colors;
FONT fonts[4];
FONT *pFonts = fonts;
static char prtrdrv[100];

static short textdriver = 8;
static short left, width;
static char buf[100];


astroFileToText::astroFileToText()
{
 switch ( textdriver ) {
        case PLASCIIANS:
             drvr = (TextConvDriver*) new TextConvDriverPlainAscii();
             break;
        case PLASCNBANS :
             drvr = (TextConvDriver*) new TextConvDriverPlainAscii();
             break;
        case MS_RTFANS_ :
             drvr = (TextConvDriver*) new TextConvDriverRTF();
             break;
        case AMIPRO :
             drvr = (TextConvDriver*) new TextConvDriverAmi();
             break;
        case WORDPFC5 :
             drvr = (TextConvDriver*) new TextConvDriverWP5();
             break;
        case WORDPFC6 :
             drvr = (TextConvDriver*) new TextConvDriverWP6();
             break;     
        case WORDPFC7 :
             drvr = (TextConvDriver*) new TextConvDriverWPint();
             break;
        case CVTHTML :
             drvr = (TextConvDriver*) new TextConvDriverHTML();
             break;
        }
 buffer = new char[ 5000 ];
 memset(buffer,0,5000);
 if ( buffer == NULL ) {
    do_mem_error( 0 );
    exp_buf = NULL;
    return;
    }
 exp_buf = new char[ 10000 ];
 memset(exp_buf,0,10000);
 if ( exp_buf == NULL ) {
    do_mem_error( 0 );
    delete buffer;
    buffer = NULL;
    return;
    }
}


astroFileToText::~astroFileToText()
{
 if ( buffer != NULL )
    delete buffer;
 if ( exp_buf != NULL )
    delete exp_buf;
 }

int astroFileToText::convert( char *infile, char *outfile )
{
 static FIL_ATTRIB atrib = {"","","","","",""};
 FILE *instream;
 char *am;
 unsigned int outsiz = 7000, s;
 int err = 0, lines;
 TextConvDriver *drvr;

 if ( (instream = fopen( infile, "rb" )) == NULL ) {
    do_error( infile );
    return( 0 );
    }
  ansi = 1;
 drvr = getDriver();
 drvr->setCenter(0);
 drvr->setJustify(0);
 am = drvr->getOpenMode();
 drvr->setupName(infile);
 if ( ( outstream = fopen( outfile, am ) ) == NULL ) {
    delete drvr;
    do_error( outfile );
    fclose( instream );
    return( 0 );
    }
 drvr->setStreams( instream, outstream );
 if ( textdriver == PLASCIIANS ) {
    drvr->initDecomp( 65 );
	left = 10;
	width = 65; 
    }
 else
   drvr->initDecomp( 32000 );
 drvr->initDriver( &atrib );
 drvr->initStringPrint( left, width );
 setvbuf(instream, buffer, _IOFBF, 4096 );
 fread( &file_info, sizeof( FILE_ID ), 1, instream );
 fseek(instream, file_info.text, SEEK_SET );
 
 while( !feof(instream) && !ferror(instream) && err == 0 ) {
    s = drvr->decompress( exp_buf, outsiz, &lines, 0 );
    if ( ( err = drvr->stringPrint( exp_buf ) ) )
	 do_error( outfile );
    fflush( outstream );
    }
 if ( ferror( instream ) )
    do_error( infile );
 drvr->finishUpJob();
 fclose( instream );
 fclose( outstream );
 delete drvr;
 return( 1 );
}

void DllExport SetupRTFConvert( FONT *pFnt, COLORREF *pClr, int lft, int wdt, int cvt, char *dev )
{
 int cvtary[] = {PLASCIIANS, PLASCNBANS, MS_RTFANS_, AMIPRO, WORDPFC5, WORDPFC6, CVTHTML, WORDPFC7 };
 memcpy(fonts, pFnt,(4 * sizeof(FONT)) );
 memcpy(colors, pClr, ( 4 * sizeof(COLORREF)) );
 left = lft;
 width = wdt;
 if ( cvt < 0 ) 
    textdriver = MS_RTFANS_;
 else 
	textdriver = cvtary[cvt];
 strcpy( prtrdrv, dev );
}

int DllExport ConvertToRTF( char *in, char *out )	 
{
 int r;
 astroFileToText *aftt = new astroFileToText();
 TextConvDriver *drv = aftt->getDriver();
 drv->setupPrinterDev( prtrdrv );
 drv->setupFonts( pFonts );
 drv->setupColors( pColors );
 r = aftt->convert( in, out );
 delete aftt;
 return( r );
}

 