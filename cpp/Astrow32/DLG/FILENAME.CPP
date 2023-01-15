#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "astro.h"
#include "useri.h"
#include "dialogs.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "asfrmdlg.hpp"
#include "filename.hpp"
#include "charcons.h"
#include "acombbox.hpp"
#include "resstr.hpp"

// Screens for Person On file.
// several classes which are used for UI related to FILE_DB
// data structures.
//
// Useasge for Class to Get Person and Comment.
//
// /* fd contains the initial data */
// FileNameDlgf *fn = new FileNameDlgf(
//   parwnd, &fd, typestring );
// if ( fn->completed() )
//    toFileDB();
// /* fd now contains all of the final data */
// /* else Cancel was Pressed */
//
// Useage for Class to Edit Person and Comment. 
//
// /* fd contains the initial data */
// FileEditDlgf *fn = new FileEditDlgf(
//   parwnd, &fd, typestring, fd.file_name );
// if ( fn->completed() )
//    toFileDB();
// /* fd now contains all of the final data */
// /* else Cancel was Pressed */
//
//  Useage for Class to see if we want to delete a file.
//
//  FileKillDlgf *fk = new FileKillDlgf(out, "Natal Report", &f );
//  if ( fk->continueAsk() )
//     out->printf( "Continue To Ask\n" );
//  else
//     out->printf( "Don't Ask\n" );
//  if ( fk->okKill() )
//     out->printf( "Kill this File\n" );
//  else
//     out->printf( "Don't Kill This File\n" );
//  delete fk;
//
//
    

FileNameDlgf::FileNameDlgf(zWindow *par, FILE_DB *pF, char *type,
	  char *res) : FormDlgf(par,zResId(res), HELPID_DLG_ENFNAMEC )
{
 pDb = pF;
 pST= new zStaticText(this, IDC_FTYPE );
 pST->text( zString(type) );
 _name = pF->name;
 _comment = pF->comment;
 new zStringEdit(this, IDC_FNAME, &_name, FLD_NOTREQUIRED );
 new zStringEdit(this, IDC_FCOMMENT, &_comment, FLD_NOTREQUIRED );
}

FileEditDlgf::FileEditDlgf(zWindow *par, FILE_DB *db,  char *type,
	  char *file) : FileNameDlgf(par,db, type, "FILE_EDIT")
{
 pST2 = new zStaticText(this, IDC_FFNAME );
 pST2->text( zString(file) );
 setId(HELPID_DLG_EDFNAMEC);
 run();
}


FileKillDlgf::FileKillDlgf( zWindow *par, FILE_DB **ppD, int nIt,
       FileListArray *pFl) : FormDlgf(par,zResId("FILE_KILL"), HELPID_DLG_KLFNAMEC )
{
 pSTname = new zStaticText(this, IDC_FNAME );
 pSTname->text( zString((*ppD)->name) );
 pSTcomment = new zStaticText(this, IDC_FCOMMENT );
 pSTcomment->text( zString((*ppD)->comment) );
 pSTtype = new zStaticText(this, IDC_FTYPE );
 pSTtype->text( zString(types((*ppD)->type)) );
 pSTfname = new zStaticText(this, IDC_FFNAME );
 pSTfname->text( zString((*ppD)->file_name) );
 pCBask = new zCheckBox(this, IDC_FKASK );
 _ask = 1;
 pCBask->check( 1 );
 pCBask->setNotifyClicked(this,(NotifyProc)&FileKillDlgf::askChecked );
 ppData = ppD;
 pFla = pFl;
 zDefPushButton *pbtno = new zDefPushButton(this, IDOK );
 pbtno->setNotifyClicked(this,(NotifyProc)&FileKillDlgf::doOkButton );
 zDefPushButton *pbtnn = new zDefPushButton(this, IDC_NO );
 pbtnn->setNotifyClicked(this,(NotifyProc)&FileKillDlgf::doNoButton );

 nItems = nIt;
 run();
}

int FileKillDlgf::askChecked( zEvent *e )
{
 if ( pCBask->check() )
    _ask = TRUE;
 else
    _ask = FALSE;
 return( 1 );
}

void FileKillDlgf::setText(FILE_DB *pF )
{
 pSTname->text( zString(pF->name) );
 pSTcomment->text( zString(pF->comment) );
 pSTtype->text( zString(types(pF->type)) );
 pSTfname->text( zString(pF->file_name) );
 pCBask->check( 1 );
}



int FileKillDlgf::doOkButton( zEvent *e )
{
 pFla->killFile( *ppData );
 ppData--;
 nItems--;
 if ( !nItems )
    shutdown();
 else if ( !_ask ) {
    do {
       pFla->killFile( *ppData );
       ppData--;
       --nItems;
       } while ( nItems );
    endOk(e);
    }
 else
    setText( *ppData );
 return( 1 );
}

int FileKillDlgf::doNoButton( zEvent *e )
{
 ppData--;
 nItems--;
 if ( !nItems )
    endOk(e);
 else if ( !_ask )
    endOk(e);
 else
    setText( *ppData );
 return( 1 );
}



void FileNameDlgf::toFileDB()
{
 memset( pDb->name, 0, NAME_WIDTH+1 );
 memset( pDb->comment, 0, COMMENT_WIDTH+1 );
 strncpy( pDb->name, _name, NAME_WIDTH );
 strncpy( pDb->comment, _comment, COMMENT_WIDTH );
}
