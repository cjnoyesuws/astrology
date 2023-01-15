#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "paths.hpp"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "comment.hpp"
#include "astromn.h"
#include "errors.fns"
#include "menuutl.hpp"
#include "dialogs.h"
#include "basedcs.h"
#include "charcons.h"
#include "resstr.hpp"


extern int decompress( char *inbuf, char **outbuf, int in_size, int *out_size );
extern int compress_string( char *in_str, char *out_str );
static int editms[] = {IDM_FSAVECFL, IDM_ECOPY, IDM_ECUT, IDM_EPASTE, IDM_EUNDO, IDM_EDEL, 0 };
static char tabline[] ="^@|60|5|10|20|30|40|50|";

int CommentEditor::command( zCommandEvt *e )
{
 if ( (HWND)*this != GetFocus() && (HWND)*edit != GetFocus() )
    return( 0 );
 switch( e->cmd() ) {
      case IDM_FSAVECFL :
	   save();
	   break;
      case IDM_ECOPY:
	   edit->copy();
	   break;
      case IDM_EDEL:
      case IDM_ECUT:
	   edit->cut();
	   break;
      case IDM_EPASTE:
	   edit->paste();
	   break;
      case IDM_EUNDO:
	   if ( edit->canUndo() )
	      edit->undo();
	   break;
      case IDC_HELP:
	   WinHelp(*this, set_path("ASTROW.HLP", HELP_F ),
					  HELP_CONTEXT, HELPID_COMMENT );
      default :
	   return( 0 );
	   break;
      }
return( 1 );
}

CommentEditor::focus(zFocusEvt *focEvt)
{
 char buf[150];

 if ( (focEvt->gainFocus()) && (edit != 0) ) {
    edit->setFocus();
    strcpy( buf, CResStr(_EDIT_CMT1)/*"Edit Comments: "*/ );
    strcat( buf, pDb->name );
    strcat( buf, " , " );
    strcat( buf, pDb->comment );
    caption( zString( buf ) );
    }
   return 0;
}


int CommentEditor::MDIActivate(zActivateEvt *actEvt)
{
 if ( (actEvt->active()) && (edit!=0) ) {
    edit->setFocus();
    enableMenuItems(pMenu, editms );
    pMenu->update();
    }
 if ( (!actEvt->active()) && (edit!=0) ) {
    disableMenuItems(pMenu, editms );
    pMenu->update();
    }
 return 0;
}


CommentEditor::CommentEditor(zFrameWin *pPar, FILE_DB *db) :
	     zMDIChildFrame(pPar,new zSizer,zSTDFRAME,CResStr(_EDIT_CMT2)/*"Edit Comments"*/)
{
 pDb = db;
 replace_ext( name, set_path(db->file_name, USER_F ), ".CMT" );
 edit = new zEditBox(this,new zSizeWithParent,zSCROLLV|ES_WANTRETURN, "", 101 );
 edit->setStoreAddr(&buf);
 load();
 edit->show();
 deleteOnClose(TRUE);
 setIcon(new zIcon(zResId("TextIcon")));
 pPar->menu()->setCommand(this,(CommandProc)&CommentEditor::command,
   IDM_EUNDO, IDM_EDEL );
 pPar->menu()->setCommand(this,(CommandProc)&CommentEditor::command,
   IDM_FSAVECFL );
 pMenu = pPar->menu();
}


int CommentEditor::load()
{
 unsigned int len, nlen;
 FILE *stream;
 char *bf, *p;

 if ( access( name, 6 ) == -1 ) {
    buf = "";
    return( 1 );
    }
 if ( (stream = freadx_fptr( name, NULL, 0 )) == NULL ) {
    do_error(name);
    return( 0 );
    }
 len = (int)filelength(fileno(stream));
 char *rb = new char[len+2];
 if (rb == NULL) {
    do_mem_error(0);
    fclose( stream );
    return( 0 );
    }
 if ( (len = fread(rb, 1, len, stream)) < len ) {
    do_error( name );
    fclose( stream );
    return( 0 );
    }
 nlen = len * 2;
 buf.reSize(nlen);
 bf = (char *)buf;
 if ( !memcmp(rb, tabline, strlen(tabline)) )
    p = rb + strlen(tabline);
 else
    p = rb;
 decompress( p, (char **)&bf, len, &nlen );
 delete rb;
 fclose( stream );
 edit->setToDefault();
 edit->hasChanged( 0 );
 return( 1 );
}

int CommentEditor::save()
{
 NFDB x;
 int len;
 FILE *stream;
 char *bf;

 x.n = *pDb;
 x.n.type = -2;
 if ( (stream = fwrite_fptr( name, &x, 4 )) == NULL ) {
    do_error(name);
    return( 0 );
    }
 len = 0;
 fwrite(&len, 2, 1, stream );
 fwrite(&len, 2, 1, stream );
 edit->storeData();
 char *rb = new char[buf.length()];
 if (rb == NULL) {
    do_mem_error(0);
    fclose( stream );
    return( 0 );
    }
 compress_string( (char *)buf, rb );
 len = strlen(rb)+1;
 fwrite(tabline, 1, strlen(tabline), stream);
 if ( (fwrite(rb, 1, len, stream)) < len ) {
    do_error( name );
    fclose( stream );
    return( 0 );
    }
 edit->hasChanged( 0 );
 delete rb;
 fclose( stream );
 pDb->has_comments = 1;
 return( 1 );
}


int CommentEditor::kill(zEvent *e)
{
 if ( edit->hasChanged() ) {
    zMessage *mp = new zMessage(this, CResStr(_SAVE_CMT1) 
    /*"Comment Has Changed, OK to Quit."*/,
	CResStr(_SAVE_CMT2)/*"Comment File"*/, 
	MB_OK|MB_ICONINFORMATION|MB_YESNOCANCEL );
    if ( mp->isNo() || mp->isCancel() ) {
       delete mp;
       return( 1 );
       }
    if ( mp->isYes() ) {
       delete mp;
       disableMenuItems(pMenu, IDM_FSAVECFL );
       pMenu->update();
       return( 0 );
       }
    }
 return( 0 );
}


