#include <stdlib.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "compute.fns"
#include "errors.fns"
#include "charcons.h"
#include "fptr.h"
#include <math.h>
#include "utlduad.h"
#include "fixstar.h"
#include "arabpt.h"
#include "oututil.h"
#include <cstring>
#include "setup.hpp"
#include "options.hpp"
#include "paths.hpp"
#include "Compile.hpp"
#include "orbs.h"

#define debugLogOut(p)

extern void mem_reclaim( AS_INF *aptr, AS_INF *alt_ptr, TRANS_DATA *td, BITS mode );
extern int write_demo_message( FILE *stream, char *file );

static int _break;


int x_kb_check()
{
 if ( _break )
    return( 1 );
 else
    return( 0 );
}

int ChartCompiler::doSetup()
{
 out_file_ptr=0;
 graph_ptr=0;
 grid_ptr=0;
 debugLogOut("doSetup1");
 memset(&birth_inf,0,sizeof(AS_INF)*CHIRON);
 memset(&alt_inf,0,sizeof(AS_INF)*CHIRON);
 if ( !dp.rdp->birth_time_known )
    op.getFlags() |= NOBIRTHTIM;
 if ( bWizard==TRUE ) {
	 if ( makeFile( ftype, op.getCharts() & GRAPH, wizfileinfo.name, wizfileinfo.comment, wizfileinfo.folder ) )
       return( 0 );
   }
 else {
    if ( makeFile( ftype, op.getCharts() & GRAPH, birth_rec.name, (char *)types[ftype], -1) )
       return( 0 );
 }

 debugLogOut("dosetup2");
 return( 1 );
}


FILE *ChartCompiler::openFile( char *file, int rpt)
{

 FILE *stream;
 debugLogOut("OpenFile1");
 return( stream );
}

/* Function to test the value of errno, Basically as a function to
   reduce redundant code */

int ChartCompiler::testErrno()
{
 debugLogOut("TestErrno");
 int e = errno;
 if ( e && e != ENOENT ) {
    do_error( ast_file );
    debugLogOut("TestErrno2");
	return( 1 );
    }
 else {
    debugLogOut("TestErrno3");
    return( 0 );
    }
}

int ChartCompiler::makeFile( int type, int grsave, char *name, char *cmt, int folder )
{
  return 0;
}


int ChartCompiler::hasGraphFile( int type )
{
 return 0;
}


int ChartCompiler::customizeScreen( char *tit )
{
  return 0;
}



int ChartCompiler::runChart()
{

 if ( !doSetup() || _break ) {
    cleanUp(0);
    return( 0 );
    }
 if ( !compile() || _break ) {
    cleanUp(0);
    return( 0 );
    }
 if ( op.getCharts() & TEXTF ) {
    if ( !doReport() || _break ) {
       cleanUp(0);
       return( 0 );
       }
    }
 if ( op.getCharts() & GRIDF ) {
   	if ( _break ) {
       cleanUp(0);
       return( 0 );
       }
    fclose(stream);
    }

 if ( op.getCharts() & DATAF ) {
    writeData();
    }
 cleanUp(1);
 return(1);
}

void ChartCompiler::disclaim()
{
}

int ChartCompiler::cleanUp( int ok )
{
 return( 1 );
}
