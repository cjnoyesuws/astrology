#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "charcons.h"
#include "flistscr.hpp"
#include "uflstscr.hpp"
#include "asframe.hpp"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "virttext.hpp"
#include "fview.hpp"
#include "asdrawbs.hpp"
#include "graphdat.hpp"
#include "dib.hpp"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "grappane.hpp"
#include "astromn.h"
#include "errors.fns"
#include "mrufile.hpp"
#include "inifile.hpp"
#include "dataext.h"
#include "astromn.h"
#include "utlduad.h"
#include "msg.hpp"
#include "setup.hpp"
#include "compile.hpp"
#include <dos.h>
#include "asfrmdlg.hpp"
#include "qdtopt.hpp"
#include "resstr.hpp"
#include "charcons.h"

extern int doConvText( zWindow *pPar, FILE_DB *f );
extern int doPrintFile( FILE_DB *f, zWindow *pPar );
extern int read_birth_data(char *file);
extern int doConvGraph( zWindow *pPar, FILE_DB *pFd );
extern int write_birth_data(char *file);

int AstroAppFrame::CheckQdt( char *c )
{
 struct dosdate_t date;
 struct dostime_t time;
 QdtData qdt;
 char *p;
 
 qdtMode = 0;
 if ( c == NULL ) 
    return( 1 );
 if ( strlen(c)==0) 
    return( 1 );
 if ( ( p = strchr( c, '-' ) ) == NULL )
    p = strchr( c, '/' );
 if ( p == NULL ) 
    return( 1 );
 else if ( strnicmp(p, "qdt", 3)  ) { 
 	qdt.getFromIni();
 	_dos_getdate( &date );
 	_dos_gettime( &time );
 	if ( qdt.getRunOnce() && date.day == qdt.getLastDay()
		      && date.month == qdt.getLastMonth() ) {
    		return( -1 );
    	}
    else if ( qdt.getRestrictTime() ) {
   	  if ( qdt.getFirstHours() < qdt.getLastHours() ) {
    	   if ( (time.hour < qdt.getFirstHours() || time.hour > qdt.getLastHours() ) ||
	    	(qdt.getFirstHours() == time.hour && time.minute < qdt.getFirstMin() ) ||
	    	(qdt.getLastHours() == time.hour && time.minute > qdt.getLastMin() )  ) {
	  	    return(-1);
	  	    }
      	}
    	else {
       	int l = qdt.getLastHours()+24;
       	if ( qdt.getLastHours() == time.hour )
	  		time.hour += 24;
       	else if ( time.hour < qdt.getLastHours() )
	  		time.hour += 24;
       	if ( (time.hour < qdt.getFirstHours() || time.hour > l ) ||
	     	(qdt.getFirstHours() == time.hour && time.minute < qdt.getFirstMin() ) ||
	    	(l == time.hour && time.minute > qdt.getLastMin() )  ) {
	  	   return(-1);
       	   }
       	}
      }
  	qdtMode = 1;
  	return( 0 );
    }
 else
    return( 1 );
}


void AstroAppFrame::doQdtView(FILE_DB *out_fp, FILE_DB *gra_fp)
{
 AstGraphicsFrame *fgf = new AstGraphicsFrame(this, gra_fp->file_name, USER_F);
 fgf->show();
 FileViewFrame *fv = new FileViewFrame(this,out_fp->file_name, USER_F);
 fv->show();
 fv->setFocus();
 qdtMode = 0;
}

void AstroAppFrame::doQdtComp()
{
 char buf[10];
 char file[150];
 struct dosdate_t date;
 struct dostime_t time;
 QdtData qdt;

 qdt.getFromIni();
 _dos_getdate( &date );
 _dos_gettime( &time );
 trans_rec.birth_data.birth_date.day = date.day;
 trans_rec.birth_data.birth_date.month = date.month;
 trans_rec.birth_data.birth_date.year = date.year;
 transit_data.num_transits = 1;
 qdt.getLastMonth() = date.month;
 qdt.getLastDay() = date.day;
 qdt.saveToIni();
 ChartCompiler *cc = new TransChartCompiler( this, Transits );
 cc->runChart();
 write_birth_data( set_path( "QDTRADAT.HIS", USER_F ) );
 doQdtView(cc->getOutFp(), cc->getGraphFp());
 delete cc;
 strcpy( file, set_path( "QDTRADAT.2nd", USER_F ) ); 
 if ( !access( file, 04 ) ) {
    read_birth_data( set_path( "QDTRADAT.2nd", USER_F ) );
    trans_rec.birth_data.birth_date.day = date.day;
    trans_rec.birth_data.birth_date.month = date.month;
    trans_rec.birth_data.birth_date.year = date.year;
    transit_data.num_transits = 1;
    ChartCompiler *cc = new TransChartCompiler( this, Transits );
    cc->runChart();
    write_birth_data( set_path( "QDTRADAT.HIS", USER_F ) );
    doQdtView(cc->getOutFp(), cc->getGraphFp());
    delete cc;
    }
 read_birth_data( set_path( "ASTRODAT.HIS", USER_F ) );
}


int AstroAppFrame::mruCmd(zCommandEvt *e)
{
#ifdef PRO
 switch( e->cmd() ) {
       case IDM_F1 :
       case IDM_F2 :
       case IDM_F3 :
       case IDM_F4 :
       case IDM_F5 :
       case IDM_F6 :
	    {
	    char t, *name;
	    name = AstMruList.get(e->cmd(),t);
	    if ( name != NULL ) {
	       switch(t) {
		  case _BDATA_ :
		       read_birth_data( name );
		       break;
		  case _FLIST_ :
		       {
		       UserFileListFrame *muflfo = new UserFileListFrame(this, name );
		       muflfo->show();
		       }
		       break;
		  case _GRAPH_ :
		       {
		       AstGraphicsFrame *agf = new AstGraphicsFrame(this, name, -1);
		       agf->show();
		       agf->setFocus();
		       }
		       break;
		  case _TEXT_ :
		       {
		       FileViewFrame *fvf = new FileViewFrame(this, name, -1);
		       fvf->show();
		       fvf->setFocus();
		       }
		       break;
		  default:
		       break;
		       }
	       }
	    }
	   break;
      }
 #endif
 return( 1 );
}


int AstroAppFrame::processCommandLine( char *cmd )
{

 char *p, *px;
 FILE_DB db;

 if ( ( p = strchr( cmd, '-' ) ) == NULL ) {
    if ( ( p = strchr( cmd, '/' ) ) == NULL ) {
       return( 0 );
       }
    }
 p++;
 if ( !strnicmp(p, "pt ", 3)  ) {
    // print text file.
    px = strrchr( p+3, '\\' );
    if ( px == NULL )
       strcpy( db.file_name, p+3 );
    else
       strcpy( db.file_name, px+1 );
    doPrintFile( &db, this );
    }
#ifdef PRO
 else if ( !strnicmp(p, "ou ", 3)  ) {
    // print graph file.
     UserFileListFrame *uflf = new UserFileListFrame( this,  p+3 );
     uflf->show();
     uflf->setFocus();
     }
#endif
 else if ( !strnicmp(p, "pg ", 3)  ) {
    // print graph file.
     AstGraphicsPane *agp = new AstGraphicsPane( p+3,
		this, -1);
     agp->doPrint(0);
     delete agp;
    }
 else if ( !strnicmp(p, "vt ", 3)  ) {
    // view text file.
    FileViewFrame *fvf = new FileViewFrame(this, p+3, -1);
    fvf->show();
    fvf->setFocus();
    }
 else if ( !strnicmp(p, "vg ", 3)  ) {
    // view graph file.
    AstGraphicsFrame *agf = new AstGraphicsFrame(this, p+3, -1);
    agf->show();
    agf->setFocus();
    }
 else if ( !strnicmp(p, "ct ", 3)  ) {
    // convert text.
    px = strrchr( p+3, '\\' );
    if ( px == NULL )
       strcpy( db.file_name, p+3 );
    else
       strcpy( db.file_name, px+1 );
    return( doConvText( this, &db ) );
    }
#ifdef PRO
 else if ( !strnicmp(p, "cg ", 3)  ) {
    px = strrchr( p+3, '\\' );
    if ( px == NULL )
       strcpy( db.file_name, p+3 );
    else
       strcpy( db.file_name, p+3 );
    return( doConvGraph( this, &db ) );
    }
 else if ( !strnicmp(p, "rb ", 3)  ) {
    // run batch Not Implemented Yet.
    }
 else if ( !strnicmp(p, "pl ", 3)  ) {
    // print from list of files Not Implemented yet.
    }
 else if ( !strnicmp(p, "qdt", 3) ) {
    // qdt startup, nothing special here
    }
 else {
    alert_box( ERROR1, CResStr(_ER_CMDLIN)/*"Illegal Command Line Argument %s"*/, p );
    return( 0 );
    }
#endif
 return( 1 );
}
