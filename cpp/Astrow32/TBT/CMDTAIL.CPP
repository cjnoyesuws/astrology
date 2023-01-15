#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include <stdlib.h>
#include "asfrmdlg.hpp"
#include "acombbox.hpp"
#include "tdirec.hpp"
#include "tbtoptn.hpp"
#include "paths.hpp"
#include "tbtframe.hpp"
#include "tbtutil.h"
#include "errors.fns"
#include "resource.h"
#define _MAKEDECLONLY_
#include "make.h"

extern void zYield( int );

void make_cmd_tail( char *cmd_tail, int cvt, int help, int back, int copy )
{
 char copyb[150], *c, *p;
 char buf[5];

 if ( cvt && !back )
    sprintf( cmd_tail, "FMT=%s SRC=%s DST=%s EXT=%s%s all",
	 (char *)theTbtOptions.getTextFormatKey(),
	 (char *)theTbtDirectories.getSource(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtOptions.getTextSourceExt(),
	 (theTbtOptions.getEnableExtText()?" XTXT=YES":"") );
 else if (cvt && back)
    sprintf( cmd_tail, "FMT=%s SRC=%s DST=%s EXT=%s%s all",
	 (char *)theTbtOptions.getTextFormatKey(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtOptions.getTextSourceExt(),
	 (theTbtOptions.getEnableExtText()?" XTXT=YES":"")  );
 else if ( copy && !help ) {
    sprintf( cmd_tail, "FMT=%s SRC=%s DST=%s EXT=%s%s all",
	 (char *)theTbtOptions.getTextFormatKey(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtDirectories.getData(),
	 (char *)theTbtOptions.getTextSourceExt(),
	 (theTbtOptions.getEnableExtText()?" XTXT=YES":"")  );
	 }
 else if ( copy && help ) {
    sprintf( cmd_tail, "FMT=%s SRC=%s DST=%s EXT=%s all",
	 (char *)theTbtOptions.getTextFormatKey(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtDirectories.getHelp(),
	 (char *)theTbtOptions.getTextSourceExt() );
	 }
 else if ( help && !back )
    sprintf( cmd_tail, "FMT=%s SRC=%s DST=%s EXT=%s all",
	 (char *)theTbtOptions.getTextFormatKey(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtOptions.getTextSourceExt() );
 else if ( help && back )
    sprintf( cmd_tail, "FMT=%s SRC=%s DST=%s EXT=%s all",
	 (char *)theTbtOptions.getTextFormatKey(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtOptions.getTextSourceExt() );
 else
    sprintf( cmd_tail, "FMT=%s SRC=%s DST=%s EXT=%s%s all",
	 (char *)theTbtOptions.getTextFormatKey(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtDirectories.getEdit(),
	 (char *)theTbtOptions.getTextSourceExt(),
	 (theTbtOptions.getEnableExtText()?" XTXT=YES":"")  );
 for ( c = copyb, p = cmd_tail; *p; p++ ) {
     if ( *(p+1) != '\0' && *p == '\\' && *(p+1)==' ' )
	 ;
     else
	*c++ = *p;
     }
 *c++ = '\0';
 strcpy( cmd_tail, copyb );
}


int make_vlist( char *buf, char **p, char *makefile )
{
 int i;                           
 char *b, **pp = p;

 *pp++ = "MAKE";
 *pp++ = "-f";
 *pp++ = makefile;
 for ( *pp++ = buf, b = buf, i = 3; *b; b++ ) {
     if ( *b == ' ' ) {
	    *b++ = '\0';
	while ( *b && *b == ' ' )
	      b++;
	if ( *b ) {
	   *pp++ = b;
	   i++;
	   }
	else
	   break;
	}
     }
 *pp++ = NULL;
 return i;
}

int _pascal _export _loadds logFunc( LPVOID data, LPCSTR text )
{
 zTextPane *p = (zTextPane *)data;
 if ( data = NULL )
    return( 0 );
 p->put((char *)text);
 zYield(1);
 zYield(1);
 return( 1 );
}

void _pascal _export _loadds yieldFnc( int i )
{
 zYield(i);
}

int doExec( char *fnc, char *p1, char *p2 )
{
 SetYieldProc((YIELDPROC)yieldFnc);
 execFunction( fnc, fnc, p1, p2 );
 return( getFunctionRet() );
}



void do_build( char *cmd, int cvt, int help, int back, int copy )
{
 char cmd_tail[300];
 char *vlist[20];
 char buf[100];
 int cnt;

 zMDIChildFrame *child = new zMDIChildFrame(app->rootWindow(),
       new zSizer,zSTDFRAME,"TBT is Building...");
 zTextPane *pane = new zTextPane( child, new zSizeWithParent,zSCROLLV);
 SetupLog(pane);
 pane->addVertScrollBar();
 SetupLogProc((LOGPROC)logFunc);
 SetYieldProc((YIELDPROC)yieldFnc);
 child->deleteOnClose(TRUE);
 child->show();
 pane->show();
 make_cmd_tail( cmd_tail, cvt, help, back, copy );
 strcpy( buf, set_path(cmd, TEXT_F ) );
 cnt = make_vlist( cmd_tail, vlist, buf );
 make_main( cnt, vlist );
 MessageBeep(-1);
 cleanupmake();
 SetupLog(NULL);
}

int TbtAppFrame::compile( zCommandEvt *e )
{
 switch( e->cmd() ) {
       case ID_COMPILE_CHANGEDTEXTFILES :
	    do_build( "DOC2TEXT.MAK", 0, 0, 0, 0 );
	    break;
       case ID_COMPILE_CHANGEDHELPFILES :
	    do_build( "DOC2HELP.MAK", 0, 1, 0, 0 );
	    break;
       case ID_COMPILE_CHANGEDREPORTFILES :
	    do_build( "DOC2REPT.MAK", 0, 0, 0, 0 );
	    break;
       case ID_COMPILE_COPYCHANGEDTEXTFILES :
	    do_build( "TEXTCOPY.MAK", 0, 0, 0, 1 );
	    break;
       case ID_COMPILE_COPYCHANGEDHELPFILES :
	    do_build( "HELPCOPY.MAK", 0, 1, 0, 1 );
	    break;
       case ID_COMPILE_COPYCHANGEDREPORTFILES :
	    do_build( "REPTCOPY.MAK", 0, 0, 0, 1 );
	    break;
       default :
	    return( 0 );
	    break;
       }
 checkConvertSettings();
 return( 1 );
}

int TbtAppFrame::convert( zCommandEvt *e )
{
 switch( e->cmd() ) {
       case ID_CONVERT_TEXTFILESTOFORMAT :
	    do_build( "TEXTCONV.MAK", 1, 0, 0, 0 );
	    break;
       case ID_CONVERT_HELPFILESTOFORMAT :
	    do_build( "HELPCONV.MAK", 1, 0, 0, 0 );
	    break;
       case ID_CONVERT_REPORTFILESTOFORMAT :
	    do_build( "REPTCONV.MAK", 1, 0, 0, 0 );
	    break;
       case ID_CONVERT_OLDTEXTFILESTOFORMAT :
	    do_build( "ASCCONV.MAK", 1, 0, 0, 0 );
	    break;
       case ID_CONVERT_OLDHELPFILESTOFORMAT :
	    do_build( "HLPCONV.MAK", 1, 0, 0, 0 );
	    break;
       case ID_CONVERT_CONVERTTEXTFILESBACKTOAST :
	    do_build( "TEXTCVBK.MAK", 1, 0, 1, 0 );
	    break;
       case ID_CONVERT_CONVERTHELPFILESBAC :
	    do_build( "HELPCVBK.MAK", 1, 0, 1, 0 );
	    break;
       case ID_CONVERT_CONVERTEDREPORTSBACKTOAST :
	    do_build( "REPTCVBK.MAK", 1, 0, 1, 0 );
	    break;
       default :
	    break;
       }
 checkConvertSettings();
 return( 1 );
}





