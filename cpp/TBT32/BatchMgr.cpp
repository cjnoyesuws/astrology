#include "stdafx.h"
#include "batchmgr.h"
#include "strsafe.h"
#ifdef _UNICODE

CBatchMgr::CBatchMgr(CString &id, CString &dir)
{
  m_id = id;
  m_dir = dir;
}

void CBatchMgr::Read()
{
  TCHAR buf[20];
  TCHAR fbuf[100];
  CString file = m_dir;
  if ( file.Right(1) != _T("\\") )
     file += _T("\\");
  file += _T("batch.ini");
  _ltow(GetSize(),buf,10);
  int len = GetPrivateProfileInt((LPCTSTR)m_id,_T("count"),0,(LPCTSTR)file);
  RemoveAll();
  for ( int i = 0; i < len; i++ ) {
      StringCbPrintf(buf,40,_T("file_%d"), i );
	  memset(fbuf,0,sizeof(fbuf));
	  GetPrivateProfileString((LPCTSTR)m_id,_T(""),buf,fbuf,200,(LPCTSTR)file);
      if ( lstrlen(fbuf) )
	     Add(fbuf);
  }
}


void CBatchMgr::Write()
{
  TCHAR buf[20];
  CString file = m_dir;
  if ( file.Right(1) != _T("\\") )
     file += _T("\\");
  file += _T("batch.ini");
  _itow(GetSize(),buf,10);
  WritePrivateProfileString((LPCTSTR)m_id,_T("count"),buf,(LPCTSTR)file);
  for ( int i = 0; i < GetSize(); i++ ) {
      StringCbPrintf(buf,40,_T("file_%d"), i );
	  WritePrivateProfileString((LPCTSTR)m_id,buf,(LPCTSTR)GetAt(i),(LPCTSTR)file);
  }
}
#endif