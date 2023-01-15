#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "fdecomp.hpp"
#include "fprint.hpp"
#include "coverdat.hpp"
#include "fcovrprt.hpp"
#include "direc.hpp"
#include "paths.hpp"


class CoverPrintFrame : public zAppFrame {
CoverPagePrinter *printer;
public:
      CoverPrintFrame(char *pName);
      ~CoverPrintFrame();
      char *prepareCover( char *fname );
      int print();
      };

CoverPrintFrame::CoverPrintFrame(char *pName):zAppFrame(0,new zSizer,zSTDFRAME,"View A File")
{
 static char *types[] = { "ASTRO Reports (*.OUT)", "*.OUT",
                 "ASTRO Cover Pages (*.CPG)", "*.CPG", 0, 0 };

 if ( pName == NULL ) {
    zFileOpenForm *fof = new zFileOpenForm(this, "File to View", "*.out", types );
    if ( fof->completed() )
       printer=new CoverPagePrinter(prepareCover(fof->name()));
    delete fof;
    }
 else
    printer=new CoverPagePrinter(pName);
}

CoverPrintFrame::print()
{
 return( printer->doPrint() );
}

CoverPrintFrame::~CoverPrintFrame()
{
 delete printer;
}


char *CoverPrintFrame::prepareCover( char *name )
{
 FILE *stream;
 char *dot;
 FILE_DB fd;
 static char cover[100];

 strcpy( cover, name );
 dot = strchr( cover, '.' );
 if ( dot == NULL )
    strcat( cover, ".CPG" );
 else
    strcpy( dot, ".CPG" );
 if ( !access( cover, 6 ) )
    return( cover );
 stream = fopen( name, "rb" );
 if ( stream == NULL )
    return( cover );
 fseek(stream, 10L, SEEK_SET );
 fread( &fd, sizeof(FILE_DB), 1, stream );
 fclose( stream );
 CoverPageEditor *cpe = new CoverPageEditor((zWindow *) this, &fd );
 delete cpe;
 return( cover );
}

void zApp::main()
{
   debugOn(1);
   theDirectories.getFromIni("TEST.INI");
   CoverPrintFrame* pCPrintFrame=new CoverPrintFrame(NULL);
   pCPrintFrame->show();
   pCPrintFrame->print();
   go();
   delete pCPrintFrame;
}
