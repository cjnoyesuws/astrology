#include "stdafx.h"
#include "astrow.h"
#include <stdlib.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "output.fns"
#include "compute.fns"
#include "errors.fns"
#include "charcons.h"
#include "fptr.h"
#include <math.h>
#include "utlduad.h"
#include "fixstar.h"
#include "arabpt.h"
#include "oututil.h"
#include "inifile.hpp"
#include "setup.hpp"
#include "options.hpp"
#include "paths.hpp"
#include "filelst.hpp"
#include "procmsg.h"
#include "compile.hpp"
#include "orbs.h"
#include "chartoptions.h"
#include "customize.h"
#include "io.h"

#define debugLogOut(p) 

extern void mem_reclaim( AS_INF *aptr, AS_INF *alt_ptr, TRANS_DATA *td, BITS mode );
extern int write_demo_message( FILE *stream, char *file );

static int _break;

/*
void debugLogOut( char *p )
{
 char buf[100];
 FILE *stream;

 stream = fopen( "C:\\debugtest.txt", "at" );
 strcpy( buf, p );
 strcat( buf, "\n");
 fputs( buf, stream );
 fclose( stream );
}
*/

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
    if ( makeFile( ftype, op.getCharts() & GRAPH, birth_rec.name, types[ftype], -1) )
       return( 0 );
 }

 debugLogOut("dosetup2");
 return( 1 );
}


FILE *ChartCompiler::openFile( char *file, int rpt)
{
 FILE *fx;
 int code;
 if ( rpt )
#ifdef _UNICODEVER
     code = _WINXP_CHARTUNI;
#else
	 code = _WINXP_CHART;
#endif
 else
	 code = _WINXP_GRID;
 debugLogOut("OpenFile1");
 if ( rpt ) {
    if ( ( stream = fwrite_fptr( file, (NFDB *)out_file_ptr, code ) ) == NULL ) {
       do_error( file );
       AstFileList.remFile( file );
       return( NULL );
       }
 }
 else {
	if ( ( stream = fwrite_fptr( file, (NFDB *)grid_ptr, code ) ) == NULL ) {
       do_error( file );
       AstFileList.remFile( file );
       return( NULL );
       }
 }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	  setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 debugLogOut("OpenFile2");
 fdata_write( stream, dp.chart_code );
 write_demo_message( stream, file );
 #ifdef DELUXE
      if ( ( fx = fopen( "HEADER.TXT", "rb" ) ) != NULL ) {
	  char *bh = new char[1000];
	  int lh = fread( bh, 1, 1000, fx );
	  fwrite( bh, 1, lh, stream );
	  fclose( fx );
	  delete bh;
	  }
#endif
 debugLogOut("OpenFile3");
 if ( ferror(stream) ) {
    do_error( file );
    AstFileList.remFile( file );
    fclose( stream );
    return( NULL );
    }
 debugLogOut("OpenFile3");
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
	AstFileList.remFile(ast_file);
    if ( strcmp( graph_file, "" ) )
       AstFileList.remFile( graph_file );
    if ( strcmp( grid_file, "" ) )
       AstFileList.remFile( grid_file );
    debugLogOut("TestErrno2");
	return( 1 );
    }
 else
   debugLogOut("TestErrno3");
   return( 0 );

}

int ChartCompiler::makeFile( int type, int grsave, char *name, char *cmt, int folder )
{
 char ast[250], graph[250], grid[250];

 debugLogOut("MakeFile1");
 memset( graph, 0, 250 );
 memset( ast, 0, 250 );
 memset( grid, 0, 250 );
 if ( !hasGraphFile(type) && grsave )
    grsave = 0;
 strcpy( comment_buf, cmt );
 debugLogOut("MakeFile1");
 if ( AstFileList.doAddFile( pParw, type, grsave, name, op.getCharts()&GRIDF,
       comment_buf, ast, graph, grid, &graph_ptr, &out_file_ptr, &grid_ptr, folder, bAutoOpen ) ) {
    return( 1 );
    }
 debugLogOut("MakeFile2");
 strcpy( comment_buf, out_file_ptr->comment );
 assert( strlen( ast ) < sizeof( ast ) );
 if ( grsave )
    assert( strlen( graph) < sizeof( graph ) );
 strcpy( ast_file, set_path( ast, out_file_ptr->folder ) );
 assert( strlen( ast_file ) < sizeof( ast_file ) );
 if ( grsave )
	 strcpy( graph_file, set_path( graph, graph_ptr->folder ) );
 else
   strcpy( graph_file, "" );
 assert( strlen( graph_file ) < sizeof( graph_file ) );
 if ( op.getCharts() & GRIDF ) {
	 strcpy( grid_file, set_path( grid, grid_ptr->folder ) );
    assert( strlen( grid_file ) < sizeof( grid_file ) );
    }
 AstFileList.keep(0);
 AstFileList.release();
 debugLogOut("MakeFile3");
 return( 0 );
}


int ChartCompiler::hasGraphFile( int type )
{
 static char hgf[] = { 1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1 };

 return( (int)hgf[type-1] );
}


int ChartCompiler::customizeScreen( char *tit )
{
#ifdef PRO
 int r;
 debugLogOut("Customize1"); 
 CCustomize cust;
 cust.SetData(op.getOpt());
 cust.SetCaption(tit);
 if ( cust.DoModal() == IDOK ) {
 	cust.GetData( op.getOpt() );
    r = 1;
    }
 else
    r = 0;
 debugLogOut("Customize2"); 
 return( r );
#else
 return( 1 );
#endif
}



int ChartCompiler::runChart()
{
#ifdef DELUXE
 FILE *fx;
#endif
 //extern FILE *teststream;
 
 debugLogOut("RunChart1"); 
 pm = new ProcMsg( "...COMPILING YOUR CHART...", &_break );
 ReleaseCapture();
 if ( !doSetup() || _break ) {
    cleanUp(0);
    return( 0 );
    }
 debugLogOut("RunChart2"); 
 AfxGetApp()->LoadStandardCursor( IDC_WAIT );
 pm->SetCapture();
 pm->Invalidate(TRUE);
 ((CAstrowApp *)AfxGetApp())->_Yield(2);
 //teststream = fopen("c:\\asp.log","wt");
 //setvbuf( teststream, NULL, _IONBF, 0 );
 if ( !compile() || _break ) {
    cleanUp(0);
	//fclose(teststream);
    return( 0 );
    }
 //fclose(teststream);
 debugLogOut("RunChart3"); 
 if ( op.getCharts() & GRAPH && hasGraphFile(ftype) ) {
    pm->setText("...GENERATING GRAPHICS DATA...");
    if ( !writeGraph() || _break ) {
       cleanUp(0);
       return( 0 );
       }
    }
 debugLogOut("RunChart4"); 
 if ( op.getCharts() & TEXTF ) {
    pm->setText("...GENERATING REPORTS...");
    if ( !doReport() || _break ) {
       cleanUp(0);
       return( 0 );
       }
    }
 disclaim();
 if ( op.getCharts() & GRIDF ) {
    pm->setText("...GENERATING GRID...");
   	if ( !writeGrid() || _break ) {
       cleanUp(0);
       return( 0 );
       }
    fclose(stream);
    }

debugLogOut("RunChart4"); 
#ifdef PRO
 if ( op.getCharts() & DATAF ) {
    pm->setText("...WRITING DATA FILES...");
    writeData();
    }
#endif
 debugLogOut("RunChart5"); 
 cleanUp(1);
 if ( bAutoOpen == TRUE ) {
    XPFILE_DB *pFile2;
    char buf2[250];
    pFile2 = getOutFp();
	if ( pFile2 != NULL ) {
	   strcpy( buf2, set_path(pFile2->file_name,pFile2->folder));
	   if ( _access(buf2,0) == 0 )
	     ((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf2);
	    }
    pFile2 = getGraphFp();
    if ( pFile2 != NULL ) {
	   strcpy( buf2, set_path(pFile2->file_name,pFile2->folder));
	   if ( _access(buf2,0) == 0 )
	     ((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf2);
	   }
	pFile2 = getGridFp();
    if ( pFile2 != NULL ) {
	   strcpy( buf2, set_path(pFile2->file_name,pFile2->folder));
	   if ( _access(buf2,0) == 0 )
	     ((CAstrowApp *)AfxGetApp())->OpenDocumentFile(buf2);
	   }
	}
 return(1);
}

void ChartCompiler::disclaim()
{
  FILE *fx;
  if ( stream != NULL ) {
#ifdef DELUXE
   if ( ( fx = fopen( "DISCLAIM.TXT", "rb" ) ) != NULL ) {
	  char *bd = new char[1000];
	  int ld = fread( bd, 1, 800, fx );
	  fwrite( bd, 1, ld, stream );
	  fclose( fx );
	  delete bd;
	  }
#endif
    fclose( stream );
    }
  }

int ChartCompiler::cleanUp( int ok )
{
 static int runs;

 debugLogOut("Cleanup1"); 
 load_orbs(NATAL_ORB);
 
 mem_reclaim( birth_inf, alt_inf, &transit_data, op.getFlags() );
debugLogOut("Cleanup2"); 
#ifdef DEMO
#ifdef DELUXE 
 runs++;
 if (runs > 3 )
    alert_box("","How About Buying ASTRO For Windows?" );
#endif
#endif
debugLogOut("Cleanup3"); 
 AfxGetApp()->LoadStandardCursor( IDC_ARROW );
 delete pm;
debugLogOut("Cleanup4");  
 return( 1 );
}
