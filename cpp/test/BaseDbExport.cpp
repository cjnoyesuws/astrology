#include "stdafx.h"
#include "basedbexport.h"
#include "strtransform.h"
#include "errors.fns"

CBaseDbExport::CBaseDbExport(CString &dir, CProgress *prog, int items, CString &lang)
{
 m_stream = 0;
 m_Directory = dir;
 m_pProgress = prog;
 SetProgCount(items);
 m_Lang = lang;
 m_pFiles = NULL;
}

CBaseDbExport::~CBaseDbExport(void)
{
  if ( m_stream != NULL )
     fclose( m_stream );
}

void CBaseDbExport::SetProgCount(int cnt)
{
  m_pProgress->SetMax(cnt);
}

BOOL CBaseDbExport::OpenFile(CString &fil) 
{
 char buf[255];
 m_pProgress->SetFile(fil);
#ifdef _UNICODE
   wcstombs(buf, m_Directory, m_Directory.GetLength() );
   buf[m_Directory.GetLength()] = '\0';
   if ( buf[strlen(buf)-1] != '\\' )
	   strcat(buf,"\\");
   int l = strlen(buf) + fil.GetLength();
   wcstombs(buf+strlen(buf),fil,fil.GetLength());
   buf[l] = '\0';
#else
   strcpy( buf, (LPCTSTR)m_Directory);
   if (buf[m_Directory.GetLength()-1] != '\\' )
	   strcat(buf,"\\");
   strcat(buf,(LPCTSTR)fil);
#endif
   m_stream = fopen(buf,"wt");
   if ( m_stream == NULL) {
       do_error(buf); 
       return( FALSE );
   }
   if ( m_pFiles != NULL ) {
	   CString str = buf;
	   m_pFiles->Add(str);
   }
   return(TRUE);
}

void CBaseDbExport::CloseFile()
{
  if ( m_stream != NULL )
    fclose( m_stream );
  m_stream = NULL;
  m_pProgress->IncProgress();
}

void CBaseDbExport::WriteHeader(CString &h1, CString &h2, CString &h3)
{
 char buf[35], buf2[35], buf3[35];
	if ( h2.GetLength() > 0 )
		h1 += " ";
	if ( h3.GetLength() > 0 )
		h2 += " ";
#ifdef _UNICODE
	wcstombs(buf, h1, h1.GetLength() );
	buf[h1.GetLength()] = '\0';
	wcstombs(buf2, h2, h2.GetLength() );
	buf2[h2.GetLength()] = '\0';
	wcstombs(buf3, h3, h3.GetLength() );
	buf3[h3.GetLength()] = '\0';
#else
	strcpy(buf, (LPCTSTR)h1);
	strcpy(buf2, (LPCTSTR)h2);
	strcpy(buf3, (LPCTSTR)h3);
#endif
	fprintf(m_stream,"# %s%s%s\n", buf, buf2, buf3);
}


void CBaseDbExport::WriteText( CString &txt ) 
{
 txt = pTransformers->ToSymbols(txt);
 #ifdef _UNICODE
 char *buf = new char[txt.GetLength()*2];
 memset(buf,0,txt.GetLength()*2);
 BOOL def=FALSE;
 WideCharToMultiByte(CP_UTF8,0,(LPCTSTR)txt,txt.GetLength(),buf,txt.GetLength()*2,NULL,NULL);
 fputs(buf,m_stream);
 delete buf;
#else
 fputs((LPCTSTR)txt,m_stream);
#endif
}

void CBaseDbExport::Process()
{
}

CString CBaseDbExport::MakeSQL( CString &table, CString &where, CString &order)
{
  CString str = "SELECT * FROM " + table;
  if (where.GetLength()>0)
	  str += " WHERE " + where;
  str += " ORDER BY " + order;
  return str;
}