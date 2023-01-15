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

static char prtrdrv[100];

static short textdriver = CVTHTML;
static short left, width;
static char buf[100];


astroFileToText::astroFileToText()
{
 switch ( textdriver ) {
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

int astroFileToText::convert( char *infile, FILE *outstream )
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
 am = drvr->getOpenMode();
 drvr->setupName(infile);
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
		return( 0 );
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


int convert( char *in, FILE *out )	 
{
 int r;
 astroFileToText *aftt = new astroFileToText();
 TextConvDriver *drv = aftt->getDriver();
 r = aftt->convert( in, out );
 delete aftt;
 return( r );
}

 