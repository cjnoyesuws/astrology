#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "fieldrng.hpp"
#include "paths.hpp"
#include "symbol.hpp"
#include "textbloc.hpp"
#include "fileary.hpp"
#include "resource.h"
#include "tfilelst.hpp"
#include "reprtedt.hpp"
#include "rtextedt.hpp"
#include "atextedt.hpp"
#include "textedit.hpp"
#include "tbtoptn.hpp"
#include "tbtframe.hpp"
#include "errors.fns"

int convertEditorFile( char *, char *, int);

extern char *replace_ext( char *buf, char *name, char *ext );

void restore_file( char *file )
{
 char buf2[150];
 char buf[150];

 replace_ext( buf2, file, ".B$$" );
 replace_ext( buf, file, ".BAK" );
 if ( !access( buf, 0 ) ) {
    rename( file, buf2 );
    rename( buf, file );
    rename( buf2, buf );
    alert_box( "TBT", "Backup File %s Restored", file );
    }
 else
    alert_box( "TBT", "Backup File %s Does Not Exist", buf );
}

int TbtAppFrame::fileCmd( zCommandEvt *e )
{
 char buf[100];
 switch( e->cmd() ) {
       case ID_FILES_OPEN_ASCIITEXTFILE :
	    {
	    TextEditor *te = new TextEditor(this);
	    te->show();
	    }
	    break;
       case ID_FILES_OPEN_HELPSOURCEFILE :
	    {
	    char *pFile;
	    zString fileName;
	    CAsFile *pF;
	    FileListDlgf *fd = new FileListDlgf(this, 0);
	    if ( fd->completed() ) {
	       pF = fd->toFile();
	       fileName = pF->name() & theTbtOptions.getTextSourceExt();
		   fileName = set_path( (char *)fileName, EDIT_F );
		   TextEditor *te = new TextEditor(this, (char *)fileName, 1 );
	       te->show();
	       }
	    delete fd;
	    return( 1 );
	    }
	    break;
       case ID_FILES_OPEN_REPORTSOURCEFILE :
	    {
	    zString fileName;
	    CAsFile *pF;
	    FileListDlgf *fd = new FileListDlgf(this, 1);
	    if ( fd->completed() ) {
	       pF = fd->toFile();
	       delete fd;
	       fileName = pF->name() & theTbtOptions.getTextSourceExt();
	       fileName = set_path( (char *)fileName, EDIT_F );
	       ReportEditorDlg *red = new ReportEditorDlg(this,
		     (char *)fileName, pF->symbols() );
	       red->run();
	       delete red;
	       }
	    else
	       delete fd;
	    return( 1 );
	    }
	    break;
       case ID_FILES_OPEN_2IDTEXTFILE :
	    {
	    char *pFile;
	    zString fileName;
	    FileListDlgf *fd = new FileListDlgf(this, 2);
	    CAsFile *pF;
	    if ( fd->completed() ) {
	        pF = fd->toFile();
	       delete fd;
	       fileName = pF->name() & theTbtOptions.getTextSourceExt();
	       fileName = set_path( (char *)fileName, EDIT_F );
	       RegTextEditorDlg *rted = new RegTextEditorDlg(this,
		     (char *)fileName, pF->symbols() );
	       rted->run();
	       delete rted;
	       }
	    else
	       delete fd;
	    return( 1 );
	    }
	    break;
       case ID_FILES_OPEN_3IDTEXTSOURCEFILE:
	    {
	    char *pFile;
	    zString fileName;
	    CAsFile *pF;
	    FileListDlgf *fd = new FileListDlgf(this, 3);
	    if ( fd->completed() ) {
	       pF = fd->toFile();
	       delete fd;
	       fileName = pF->name() & theTbtOptions.getTextSourceExt();
	       fileName = set_path( (char *)fileName, EDIT_F );
	       AspTextEditorDlg *ated = new AspTextEditorDlg(this,
		     (char *)fileName, pF->symbols() );
	       delete ated;
	       }
	    else
	       delete fd;
	    return( 1 );
	    }
	    break;
       case ID_FILES_RESTORE :
	    {
	    char *pFile;
	    zString fileName;
	    CAsFile *pF;
	    FileListDlgf *fd = new FileListDlgf(this, -1);
	    if ( fd->completed() ) {
	       pF = fd->toFile();
	       fileName = pF->name() & theTbtOptions.getTextSourceExt();
		   fileName = set_path( (char *)fileName, EDIT_F );
	       restore_file( (char *) fileName );
	       }
	    delete fd;
	    return( 1 );
	    }
	    break;

       default :
	    return( 0 );
	    break;
       }
 return( 1 );
}
