// ImportBirths.cpp: implementation of the CImportBirths class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "importtool.h"
#include "Importfilelist.h"
#include "errors.fns"
#include "uicvt.fns"
#include <share.h>
#include <stdlib.h>
#include "foldersset.h"
#include "paths.hpp"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define oldflg 0xfedc
#define newflg 0xfedf
extern CString &quote( char *pChar, CString & str );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 void CImportFileList::LoadFolders()
 {
  char buf[200];
  
  GetPrivateProfileString("Folders","FolderCount","0", buf, 200, "ASTROW.INI" );
  int cnt = atoi(buf);
  for ( int i = 0; i < cnt; i++ ) {
	char fdbuf[20];
	char sqlbuf[150];
	sprintf( fdbuf, "Folder%d", i );
	GetPrivateProfileString("Folders",fdbuf,"", buf, 200, "ASTROW.INI" );
	CFoldersSet fldset;
    sprintf(sqlbuf,"select * from folders where folder_num=%d", i );
	try {
	   fldset.Open(-1,sqlbuf);
	   if ( fldset.IsBOF() )
		   fldset.AddNew();
	   else 
		   fldset.Edit();
	   fldset.m_folder_num = i;
	   fldset.m_folder_name = buf;
	   fldset.Update();
	   fldset.Close();
	}
	catch ( CDaoException *e ) {
		char erbuf[500];
		e->GetErrorMessage(erbuf, 499);
	    alert_box("Error", erbuf );
		}
    }
 }
 
 
CImportFileList::CImportFileList()
{

}

CImportFileList::~CImportFileList()
{
 if ( theSet.IsOpen() )
	 theSet.Close();

}

void CImportFileList::process()
{
 unsigned short flg = 0xfedf;
 FILE * stream;
 char buf[200];
 short count;
 int addupd;
 
 //LoadFolders();
 ptr = &filedb;
 strcpy( buf, (const char * )mDir );
 if ( buf[strlen(buf)-1] != '\\' )
	 strcat( buf, "\\" );
 strcat(buf,"nastfil.lst");
 if ( ( stream = _fsopen( buf, "rb", SH_DENYWR ) ) == NULL ) {
    do_error( buf );
    return;
    }
 if ( setvbuf( stream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( stream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( stream, NULL, _IOFBF, 1024 ) )
	      setvbuf( stream, NULL, _IOFBF, 256 );
       }
    }
 fread(&flg,2,1,stream);
 if ( flg == oldflg || flg==newflg ) {
	 if ( fread( (char *) &count, sizeof( COUNT ), 1, stream ) != 1 ) {
       do_error( buf );
       fclose( stream );
       return;
       }
    }
 else
	count = flg;
 //fread(&count,2,1,stream);
 m_pImporterData->m_progress->m_records.SetRange(0,count);
 m_pImporterData->m_progress->m_records.SetStep(1);
 while ( !feof(stream ) ) {
    if ( flg == oldflg ) {
	    if ( fread( &w32, sizeof(FILE_DB), 1, stream) != 1 ) {
           do_error( buf );
           fclose( stream );
           return;
           }
		strcpy( ptr->name, w32.name );
		strcpy( ptr->comment, w32.comment );
		strcpy( ptr->file_name, w32.file_name );
		ptr->file_num = w32.file_num;
		ptr->has_comments = w32.has_comments;
		ptr->has_cover = w32.has_cover;
		ptr->type = w32.type;
		ptr->folder = DEFAULT_FLD;
        if ( ptr->type >= LAST_NON_GRAPH_OLD )
           ptr->type += NEW_GRA_DIFF;
	 }
	 else if ( flg == newflg ) {
		 if ( fread( ptr, sizeof(XPFILE_DB), 1, stream) != 1 ) {
           do_error( buf );
           fclose( stream );
           return;
           }
	 }
	 else {
	    if ( fread( &w16, sizeof(W16_FILE_DB), 1, stream) != 1 ) {
           do_error( buf );
           fclose( stream );
           return;
           }				 
		strcpy( ptr->name, w16.name );
		strcpy( ptr->comment, w16.comment );
		strcpy( ptr->file_name, w16.file_name );
		ptr->file_num = w16.file_num;
		ptr->has_comments = w16.has_comments;
		ptr->has_cover = w16.has_cover;
		ptr->type = w16.type;
		ptr->folder = DEFAULT_FLD;
		if ( ptr->type > LAST_NON_GRAPH_OLD )
			ptr->type += NEW_GRA_DIFF;
	 }
    if ( !feof( stream ) ) {
        addupd = checkRow();
        doDbRow(addupd);
		}
	m_pImporterData->m_progress->m_records.StepIt();  
   }
 fclose( stream );
 try {
      if ( theSet.IsOpen() )
	     theSet.Close();
	} catch ( CDaoException *e ) {
      char erbuf[500];
	  e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	}
}

int CImportFileList::checkRow()
{
char msgbuf[100];
char sqlbuf[500];
char erbuf[500];
 CString n;
 sprintf( msgbuf, "Importing %s", filedb.file_name );
 strcpy(pBuf,(const char *)msgbuf);
 if ( 1 ) {
	sprintf( sqlbuf,"select * from FileList where filename=%s", quote(filedb.file_name,n) ); 	
    try {
      if ( theSet.IsOpen() )
	     theSet.Close();
	   theSet.Open( -1, sqlbuf );
	   if ( !theSet.IsOpen() || theSet.IsBOF() )
	    	return( 1 );
	   else
	    	return( 0 );
	} catch ( CDaoException *e ) {
      e->GetErrorMessage(erbuf,499);    
	  alert_box("Error", erbuf );
	  return( 1 );
	}
 }
 
 return ( 0 );
}

int CImportFileList::doDbRow( int bAdd ) 
{
	char erbuf[500];

	try {
	   if ( bAdd ) 
	     theSet.AddNew();
	   else {
	     theSet.Edit();
	   }
       theSet.m_name = filedb.name;
	   theSet.m_comments=filedb.comment;
	   theSet.m_filename=filedb.file_name;
	   theSet.m_filenum = filedb.file_num;
	   theSet.m_has_comments = filedb.has_comments;
	   theSet.m_has_cover = filedb.has_cover;
       theSet.m_FileType = filedb.type;
	   theSet.m_Folder = filedb.folder;
       if (filedb.type<=LAST_NON_GRAPH)
		   theSet.m_ListType = "OUT";
	   else if (filedb.type>LAST_GRAPH)
		   theSet.m_ListType = "GRD";
	   else
		   theSet.m_ListType = "GRA";
	   theSet.m_IsTextReport = (filedb.type<=LAST_NON_GRAPH?TRUE:FALSE);
   	   theSet.Update();
	}
	catch ( CDaoException * e ) {
	  e->GetErrorMessage(erbuf, 499);
	  alert_box("Error", erbuf );
	}
   return( 0 );
}

