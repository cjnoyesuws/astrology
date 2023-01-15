// FileListMgr.cpp: implementation of the CFileListMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Astrow.h"
#include <afxcoll.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "FileListSet.h"
#include "FileListCounterSet.h"
#include "FileListMgr.h"
#include "errors.fns"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileListMgr::CFileListMgr(short type)
{
	if ( type==ALL_F ) {
		m_bAll = TRUE;
		m_bIsTextReport=TRUE;
	}
	else if ( type==GRA_F ) {
		m_bAll=FALSE;
		m_bIsTextReport=FALSE;
	}
	else {
		m_bAll=FALSE;
		m_bIsTextReport=TRUE;
	}
m_strSort = "filenum";
DoOpen();
FillArrays();
}

CFileListMgr::~CFileListMgr()
{
 if (theSet.IsOpen() )
	 theSet.Close();
 if (theCounterSet.IsOpen() )
	 theCounterSet.Close();
 CounterArray.RemoveAll();
 SelectedArray.RemoveAll();
}

void CFileListMgr::FillArrays()
{

 char erbuf[500];
 int iCount = 0, iGrabCount;
 if ( m_bErrorState == TRUE )
	 return;
 CounterArray.RemoveAll();
 SelectedArray.RemoveAll();
 SelectedArray.SetSize(25);
 CounterArray.SetSize(25);
 try {
     theCounterSet.MoveFirst();
	 do {
	    iGrabCount=theCounterSet.GetRowsFetched();
        for ( int i = 0; i < iGrabCount; i++ ) {
		    CounterArray.Add(theCounterSet.m_pCounters[i]);
			SelectedArray.Add(0);
			iCount++;
			}
		if ( iGrabCount == 25 )
			theCounterSet.MoveNext();
	 } while( !theCounterSet.IsEOF() );
 }
 catch ( CDBException *e ) {
	 e->GetErrorMessage(erbuf,499);    
	 alert_box("Error", erbuf );
     m_bErrorState = TRUE;;
 }
 SelectedArray.FreeExtra();
 CounterArray.FreeExtra();
 m_nRecords=iCount;
}


void CFileListMgr::RefillArrays()
{
  
 char erbuf[500];
 int iCount = 0, iGrabCount;
  if ( m_bErrorState == TRUE )
	 return;
 CByteArray *pSel = new CByteArray();
 CDWordArray *pCnt = new CDWordArray();
 pSel->SetSize(25);
 pCnt->SetSize(25);
 try {
     theCounterSet.MoveFirst();
	 do {
	    iGrabCount=theCounterSet.GetRowsFetched();
        for ( int i = 0; i < iGrabCount; i++ ) {
		    pCnt->Add(theCounterSet.m_pCounters[i]);
			pSel->Add(0);
			iCount++;
			}
		if ( iGrabCount == 25 )
			theCounterSet.MoveNext();
	 } while( !theCounterSet.IsEOF() );
 }
 catch ( CDBException *e ) {
	 e->GetErrorMessage(erbuf,499);    
	 alert_box("Error", erbuf );
     m_bErrorState = TRUE;;
 }
 for ( int i = 0; i < pSel->GetSize(); i++ ) {
	int ct = IndexOfCounter((*pCnt)[i]);
	if ( ct != -1 )
		(*pSel)[i]=SelectedArray[ct];
	}
 for ( i = 0; i < pSel->GetSize(); i++ ) {
    CounterArray.SetAtGrow(i,(*pCnt)[i]);
	SelectedArray.SetAtGrow(i,(*pSel)[i]);
	}
 CounterArray.SetSize(i);
 SelectedArray.SetSize(i);
 m_nRecords = iCount;
 delete pSel;
 delete pCnt;
}

void CFileListMgr::DoOpen()
{
 char erbuf[500];
 
 m_bErrorState=FALSE;
 
 try {
	 if (theSet.IsOpen() )
		 theSet.Close();
	 if (theCounterSet.IsOpen() )
        theCounterSet.Close();
	 theSet.m_strSort = m_strSort;
	theCounterSet.m_strSort = m_strSort;
	if ( m_bAll==FALSE && m_bIsTextReport==TRUE ) {
		theSet.m_IsTextReportParam = m_bIsTextReport;
		theSet.m_strFilter = "IsTextReport=?";
		theSet.m_nParams = 1;
		theCounterSet.m_IsTextReportParam=m_bIsTextReport;
		theCounterSet.m_nParams=1;
		theCounterSet.m_strFilter="IsTextReport=?";
		}
	else {
		theSet.m_nParams = 0;
		theCounterSet.m_nParams=0;
		theSet.m_strFilter="";
		theCounterSet.m_strFilter="";
		}
	 theSet.Open();
	 theCounterSet.Open();
 }
 catch ( CDBException *e ) {
	 e->GetErrorMessage(erbuf,499);    
	 alert_box("Error", erbuf );
     m_bErrorState = TRUE;;
 }

}

void CFileListMgr::ChangeSort( CString &srt )
{
  m_strSort=srt;
  DoOpen();
  RefillArrays();
}

BOOL CFileListMgr::Add( FILE_DB &db )
{
  char erbuf[500];
	try {
		if ( m_nRecords==0)
			theSet.AddNew();
		else
			theSet.Edit();
		theSet.m_comments=db.comment;
		theSet.m_filename=db.file_name;
		theSet.m_filenum=db.file_num;
		theSet.m_FileType=db.type;
		theSet.m_has_comments=(db.has_comments?TRUE:FALSE);
		theSet.m_has_cover=(db.has_cover?TRUE:FALSE);
		theSet.m_IsTextReport=(db.type<=LAST_NON_GRAPH?TRUE:FALSE);
		theSet.Update();
		if ( m_strSort=="filenum" ) {
		    theSet.MoveLast();
			CounterArray.Add(theSet.m_counter);
			SelectedArray.Add(0);
			m_nRecords++;
			theSet.SetAbsolutePosition(m_iRecNum+1);
			}
		else {
			RefillArrays();
			}
		}
	catch ( CDBException *e ) {
		e->GetErrorMessage(erbuf,499);    
		alert_box("Error", erbuf );
		m_bErrorState = TRUE;;
	}
}

CFileListMgr::GetSelected(CDWordArray &ar)
{
  int count=0, i;
  for ( i = 0; i < SelectedArray.GetSize(); i++ ) {
	  if ( SelectedArray[i] )
		  count++;
	}
  ar.SetSize(count);
  i=0;
  for (  int j=0; i < SelectedArray.GetSize(); i++ ) {
	  if ( SelectedArray[i] )
		  ar[j++]=i
	}
}

BOOL CFileListMgr::DeleteItem( int it )
{
 char erbuf[500], *file_name, *p;
 try {
		theSet.SetAbsolutePosition(it);
        theSet.Delete();
		theSet.SetAbsolutePosition(m_iRecNum);
        CounterArray.RemoveAt(it);
		SelectedArray.RemoveAt(it);
		file_name = (char *)set_path( ptr->file_name, TEMP_F );
      unlink( file_name );
      p = strchr( file_name, '.' );        /* Support for future Comment file */
      if ( p != NULL && ptr->has_comments  ) {       /* and Cover Page files. */
         strcpy( p, ".CMT" );
         unlink( file_name );
			}
		if ( p != NULL && ptr->has_cover  ) {
		   strcpy( p, ".CPG" );
		   unlink( file_name );
			}
		}
	catch ( CDBException *e ) {
		e->GetErrorMessage(erbuf,499);    
		alert_box("Error", erbuf );
		m_bErrorState = TRUE;;
	}


}

int CFileListMgr::IndexOfCounter(long ctr)
{
	for ( int i = 0; i < CounterArray.GetSize(); i++ ) {
	    if ( CounterArray[i] == ctr ) 
			return( i );
	}
    return ( -1 );
}

BOOL CFileListMgr::MoveFirst()
{  
	BOOL ret;
	if ( m_bErrorState )
		return FALSE;
	if ( theSet.IsBOF() )
		return( FALSE );
	theSet.MoveFirst();
	m_iRecNum = 1;
	return (TRUE);
}

BOOL CFileListMgr::MoveLast()
{ 
  if ( m_bErrorState )
	  return FALSE;
  if ( theSet.IsBOF() )
	  return FALSE;
  theSet.MoveLast();
  m_iRecNum = theSet.GetRecordCount();
  return ( TRUE );
 }

BOOL CFileListMgr::MoveNext()
{ 
  if (m_bErrorState)
	  return( FALSE );
  if ( theSet.IsBOF() || theSet.IsEOF() )
	  return( FALSE );
  theSet.MoveNext();
  m_iRecNum++;
  return( TRUE );
 }

BOOL CFileListMgr::MovePrior()
{ 
  if (m_bErrorState)
	  return( FALSE );
  if ( theSet.IsBOF() )
	 return( FALSE );
  theSet.MovePrev();
  m_iRecNum--;
  return( TRUE );
 }



BOOL CFileListMgr::MoveRelative(int rows)
{ 
 if ( m_bErrorState )
	 return ( FALSE );
 if ( m_iRecNum+rows>m_nRecords || m_iRecNum+rows<1)
	 return ( FALSE );
 theSet.Move(rows);
 m_iRecNum+=rows;
 return( TRUE );
 }

BOOL CFileListMgr::SetAbsolutePosition( int r )
{
 if ( m_bErrorState )
	 return( FALSE );
 if ( r > m_nRecords || r < 0 )
	 return (FALSE );
 theSet.SetAbsolutePosition( r );
 m_iRecNum = r;
 return ( r );
}

FILE_DB &CFileListMgr::ToFDB()
{
  strcpy( filedb.name, (const char *)theSet.m_name);
  strcpy( filedb.comment, (const char *)theSet.m_comments);
  strcpy( filedb.file_name, (const char *)theSet.m_filename);
  filedb.file_num = theSet.m_filenum;
  filedb.type = theSet.m_FileType;
  filedb.has_comments = theSet.m_has_comments;
  filedb.has_cover = theSet.m_has_cover;
  return( filedb );
}

BOOL CFileListMgr::PopPosition()
{
  int r = RecNumStack.Pop();
  if ( r != -1 ) 
	 return( SetAbsolutePosition(r) );
  else
     return( FALSE );
}

BOOL CFileListMgr::PushPosition(int pos) 
{
  RecNumStack.Push(m_iRecNum);
  return( SetAbsolutePosition(pos));  
}


int CFileListMgr::SelCount()
{
 int c=0; 
 for ( int i=0; i < SelectedArray.GetSize(); i++ ) {
	  if ( SelectedArray[i] )
  		  c++:
	}
  return ( c );	
}

int CFileListMgr::getFileList( CStringArray &sar, CDWordArray &war, int n, int sz, int b4, int cmt, int cvr )
{
}