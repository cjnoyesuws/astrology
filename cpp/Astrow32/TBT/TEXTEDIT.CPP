#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "paths.hpp"
#include "textedit.hpp"
#include "astromn.h"
#include "errors.fns"
#include "menuutl.hpp"
#include "d:\msvc\mfc\include\afxres.h"
#include "resource.h"
#include "tbtoptn.hpp"
#include "paths.hpp"
#include "tbtframe.hpp"
#include "ctype.h"
#include "direct.h"
#include "helpid.h"
#include "tbtutil.h"

static char *types[] = { "ASTRO Source (*.AST)","*.AST",
			 "Text Files (*.TXT)","*.TXT",
			 "ASCII Files (*.ASC)","*.ASC",
			 "DOC Files (*.DOC)","*.DOC",
			 "All Files (*.*)", "*.*", 0, 0 };

int convertEditorFile( char *, char *, int);

static int feditms[] = {ID_FILES_SAVE, ID_FILES_SAVEAS, ID_FILES_CLOSE, 0 };
static int ceditms[] = {ID_EDIT_COPY, ID_EDIT_CUT, ID_EDIT_DELETE, 0 };
static int cdeditms[] = {ID_EDIT_COPY, ID_EDIT_CUT, ID_EDIT_PASTE, ID_EDIT_UNDO, ID_EDIT_DELETE, 0 };

TextEditor::~TextEditor() 
{ 
 delete edit; 
 if ( doCvt && theTbtOptions.getTextFormatKey() != (const char *)"AST" ) {
    if ( !access((char *)ename, 0))
       unlink((char *)ename);
    }
}

int TextEditor::onUpdate(zEvent *e)
{
 updateEditMenu();
 return( 1 );
}

int TextEditor::updateEditMenu()
{
 if ( edit->canUndo() )
    enableMenuItems( pMenu, ID_EDIT_UNDO );
 else
    disableMenuItems( pMenu ,ID_EDIT_UNDO );
 if ( ((TbtAppFrame *)app->rootWindow())->getClipboard()->isTextAvail() )
    enableMenuItems( pMenu, ID_EDIT_PASTE );
 else
    disableMenuItems( pMenu, ID_EDIT_PASTE );
 enableMenuItems( pMenu, ceditms );
 pMenu->update();   
 return( 1 );
}

int TextEditor::command( zCommandEvt *e )
{
 if ( (HWND)*this != GetFocus() && (HWND)*edit != GetFocus() )
    return( 0 );
 switch( e->cmd() ) {
      case ID_FILES_SAVE :
	   save();
	   break;
      case ID_FILES_SAVEAS :
	   {
	   zFileSaveAsForm *fsaf = new zFileSaveAsForm( this,
		  "File To Save To.", name, types );
	   if ( !fsaf->completed() ) {
	      delete fsaf;
	      break;
	      }
	   strcpy( ename, fsaf->name() );
	   strcpy( name, fsaf->name() );
	   delete fsaf;
	   char *p = set_path("",PROGRAM_F);
	   _chdrive((toupper(*p)-'A')+1);
	   if ( p[strlen(p)-1] == '\\' )
	      p[strlen(p)-1] = '\0';
	   _chdir(p);
	   save();
	   }
	   break;
      case ID_EDIT_COPY:
	   edit->copy();
	   break;
      case ID_EDIT_DELETE:
       edit->replaceSelection("");
       break;
      case ID_EDIT_CUT:
	   edit->cut();
	   break;
      case ID_EDIT_PASTE:
	   edit->paste();
	   break;
      case ID_EDIT_UNDO:
	   if ( edit->canUndo() )
	      edit->undo();
	   break;
      case IDC_HELP:
	   WinHelp(*this, set_path("TBT.HLP", TEXT_F ),
					  HELP_CONTEXT, HELPID_DLG_EDIT );
	   break;
      case ID_FILES_CLOSE :
	   PostMessage((HWND)(*this),WM_CLOSE,0,0L);
	   break;
      case ID_UTILITIES_SPELLCHECKFILE :
       break;
      default :
	   return( 0 );
	   break;
      }
 updateEditMenu();
 return( 1 );
}

TextEditor::focus(zFocusEvt *focEvt)
{
 char buf[150];

 if ( (focEvt->gainFocus()) && (edit != 0) ) {
    edit->setFocus();
    strcpy( buf, "Edit File: " );
    strcat( buf, name );
    caption( zString( buf ) );
    }
   return 0;
}


int TextEditor::MDIActivate(zActivateEvt *actEvt)
{
 if ( (actEvt->active()) && (edit!=0) ) {
    edit->setFocus();
    enableMenuItems(pMenu, feditms );
    pMenu->update();
    updateEditMenu();
    }
 if ( (!actEvt->active()) && (edit!=0) ) {
    disableMenuItems(pMenu, feditms );
    disableMenuItems(pMenu, cdeditms );
    pMenu->update();
    }
 return 0;
}


TextEditor::TextEditor(zFrameWin *pPar, char *file, int dCvt ) :
	     zMDIChildFrame(pPar,new zSizer,zSTDFRAME,"Edit File")
{
 zString c;
 doCvt = dCvt;
 if ( file != NULL )
    strcpy( name, file );
 else {
      strcpy( name, set_path( "TEXT.AST", EDIT_F) );
      zFileOpenForm *fof = new zFileOpenForm( pPar,
		"File To Open.", name, types );
      if ( !fof->completed() ) 
	     strcpy( name, "" );
	  else
         strcpy( name, fof->name() );
      char *p = set_path("",PROGRAM_F);
      _chdrive((toupper(*p)-'A')+1);
      if ( p[strlen(p)-1] == '\\' )
         p[strlen(p)-1] = '\0';
      _chdir(p);
      delete fof;
      }
 c = caption();
 c &= " : ";
 c &= name;
 caption(c);
 edit = new zEditBox(this,new zSizeWithParent,zSCROLLV|ES_WANTRETURN, "", 101 );
 edit->setStoreAddr(&buf);
 load();
 edit->show();
 edit->setNotifyChange(this,(NotifyProc)&TextEditor::onUpdate);
 deleteOnClose(TRUE);
 setIcon(new zIcon(zResId(IDI_TEXTICON)));
 edit->selection(0,0);
 pPar->menu()->setCommand(this,(CommandProc)&TextEditor::command,
   ID_EDIT_UNDO, ID_EDIT_DELETE );
 pPar->menu()->setCommand(this,(CommandProc)&TextEditor::command,
    ID_FILES_SAVE );
 pPar->menu()->setCommand(this,(CommandProc)&TextEditor::command,
    ID_FILES_CLOSE );
 pPar->menu()->setCommand(this,(CommandProc)&TextEditor::command,
    ID_FILES_SAVEAS );
 pPar->menu()->setCommand(this,(CommandProc)&TextEditor::command,
    ID_UTILITIES_SPELLCHECKFILE );
 pClip = new zClipboard( app->rootWindow() );
 pMenu = pPar->menu();
}


int TextEditor::load()
{
 unsigned int len, nlen;
 FILE *stream;
 char *bf, *p;
 
 if ( !strlen(name) || access( name, 6 ) == -1 ) {
    buf = "";
    edit->setToDefault();
    edit->hasChanged( 0 );
    return( 1 );
    }
 if ( doCvt && theTbtOptions.getTextFormatKey() != (const char *)"AST" ) {
    strcpy( ename, name );
    replace_ext( ename, name, ".$$$" );
    convertEditorFile( name, ename, 1 );
    }
 else
    strcpy( ename, name );
 stream = fopen( ename, "rb" );
 if ( stream == NULL ) {
    do_error( ename );
    return( 0 );
    }
 len = (int)filelength(fileno(stream));
 buf.reSize(len+1);
 if ( (len = fread((char *)buf, 1, len, stream)) < len ) {
    do_error( ename );
    fclose( stream );
    return( 0 );
    }
 if ( doCvt )
    doConvertText( (char *)buf, 4, 5, 1 );
 buf.reSize(len);
 fclose( stream );
 edit->setToDefault();
 edit->hasChanged( 0 );
 return( 1 );
}

int TextEditor::save()
{
 FILE *stream;

 backup();
 stream = fopen( ename, "wb" );
 if ( stream == NULL ) {
    do_error( ename );
    return( 0 );
    }
 edit->storeData();
 if ( doCvt )
    doConvertText( (char *)buf, 5, 1 );
 fwrite((char *)buf, 1, buf.length(), stream);
 edit->hasChanged( 0 );
 fclose( stream );
 if ( doCvt && theTbtOptions.getTextFormatKey() != (const char *)"AST" ) {
    convertEditorFile( ename, name, 0 );
    unlink( ename );
    }
 return( 1 );
}

int TextEditor::backup()
{
 int len;
 FILE *stream;
 char n[100];

 if ( access( name, 4 ) == -1 )
    return( 0 );
 replace_ext( n, name, ".BAK" );
 unlink( n );
 rename( name, n );
 return( 1 );
}



int TextEditor::kill(zEvent *e)
{
 if ( edit->hasChanged() ) {
    zMessage *mp = new zMessage(this, "Text Has Changed, OK to Quit.",
	name, MB_OK|MB_ICONINFORMATION|MB_YESNOCANCEL );
    if ( mp->isNo() || mp->isCancel() ) {
       delete mp;
       return( 1 );
       }
    delete mp;          
    }
 pMenu->removeCommand(this,(CommandProc)&TextEditor::command );
 disableMenuItems(pMenu, feditms );
 pMenu->update();
 return( 0 );
}


