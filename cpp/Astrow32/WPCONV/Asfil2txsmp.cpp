#include "stdafx.h"
#include <stdio.h>
#include <share.h>
#include <stdlib.h>
#include <io.h>
#include "astro.h"     
#include "useri.h"
#include "attrib.h"     
#include "errors.fns"
#include "output.fns"
#include "charcons.h"
#include "fptr.h"
#include "inifile.hpp"
#include "convopt.hpp"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "paths.hpp"
#include <limits.h>
#include "coverdat.hpp"
#include "asfil2tx.hpp"

static char conv_file[_MAX_PATH];

astroFileToTextSimple::astroFileToTextSimple(int d, int drv)
{
 prs = 0;
 dir = d;
 ansi=1;
 rtfdrv = drv;
 buffer = new char[ 5000 ];
 if ( buffer == NULL ) {
    do_mem_error( 0 );
    exp_buf = NULL;
    return;
    }
 exp_buf = new char[ 10000 ];
 if ( exp_buf == NULL ) {
    do_mem_error( 0 );
    delete buffer;
    buffer = NULL;
    return;
    }
}


astroFileToTextSimple::~astroFileToTextSimple()
{
 if ( prs != 0 ) 
	delete prs;
 if ( buffer != NULL )
    delete buffer;
 if ( exp_buf != NULL )
    delete exp_buf;
}


TextConvDriver *astroFileToTextSimple::getDriver()
{
    if ( rtfdrv )
	   return((TextConvDriver *) new TextConvDriverRTF(ansi, 0));
	else
	   return((TextConvDriver *) new TextConvDriverHTML(1));
  
 }

int astroFileToTextSimple::getSetup()
{
 char pth[_MAX_DIR];
 if ( !strlen(outfile) ) {	
   GetTempPath(_MAX_DIR,pth);
   GetTempFileName(pth,"AST", 0, outfile );
 }
return( 0 );
}

void astroFileToTextSimple::setFiles(char *file)
{
 thefile = file;
}

int astroFileToTextSimple::convert( const char *infile, int code )
{
 FILE *instream;
 char *am, rtf[6], *ptr;
 unsigned int outsiz = 7000, s;
 long off;
 int err = 0, lines;
 TextConvDriver *drvr;
 NFP xfpt;
 int grid = 0;

 if ( !strnicmp(infile+strlen(infile)-5,"ASGRD", 5 ) )
    grid=1;
 outstream = NULL;
 if ( ( instream = freadx_fptr( (char *)infile, &xfpt, 0 ) ) == NULL ) {
    do_error( infile );
    return( 0 );
    }
 ansi = AfxGetApp()->GetProfileInt( Misc_SEC, "AnsiText", ansi );
 drvr = getDriver();
 drvr->setCenter(1);
 drvr->setJustify(0);
 CDC *dc = new CDC;
 dc->CreateIC("DISPLAY",0,0,0);	 
 prs = new ReportStyles(dc,0,grid);
 if ( grid )
     prs->getFromIni("GridView");
 else
     prs->getFromIni(ViewerData_SEC);
 delete dc;
  drvr->IsMbString = isafptr3wxu_file( &xfpt );
 drvr->setStyles(prs);
 if ( !code || code == -1 ) {
    am = drvr->getOpenMode();
    if ( ( outstream = fopen( outfile, am  ) ) == NULL ) {
       delete drvr;
       do_error( outfile );
       fclose( instream );
       return( 0 );
       }
    strcpy( conv_file, outfile );
    }
 drvr->setStreams( instream, outstream );
 drvr->initDriver( &cd.getFileAttribs() );
 drvr->initDecomp( 32000 );
 if ( rtfdrv )
    drvr->initStringPrint( 0, 32000, MS_RTFANS, code );
 else
    drvr->initStringPrint( 0, 32000, WWW_HTML, code );
 
 
 setvbuf(instream, buffer, _IOFBF, 4096 );
 off = ftell(instream);
 fread(rtf,5,1,instream);
 rtf[5] = '\0';
 if ( !strcmpi(rtf,"{\\rtf" ) ) {
    do { 
	   ptr = fgets(exp_buf, 9999, instream);
	   if ( ptr != NULL )
	      fputs(ptr,outstream);
	   } while ( !feof(instream ) );
       fclose( instream );
       delete drvr;
       return( 1 );
 
    }
 else
	fseek(instream, off, SEEK_SET );
 while( !feof(instream) && !ferror(instream) && err == 0 ) {
    s = drvr->decompress( exp_buf, outsiz, &lines, 0 );
    if ( ( err = drvr->stringPrint( exp_buf ) ) )
	 do_error( outfile );
    fflush( outstream );
    }
 if ( ferror( instream ) )
    do_error( infile );
 drvr->finishUpJob();
 drvr->finishUpFile();
 fclose( instream );
 delete drvr;
 return( 1 );
}


int astroFileToTextSimple::doConvert( const char *file )
{
 int ret; 
 char buf[_MAX_PATH];
  
  strcpy( buf, set_path( (char *)file, dir ) );
  getSetup();
  ret = convert( buf, -1 );
  if ( outstream != NULL )
     fclose( outstream );
  return( ret );
}


