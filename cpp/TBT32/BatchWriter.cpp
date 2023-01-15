

#include "stdafx.h"
#include ".\batchwriter.h"
#include "errors.fns"

#ifdef _UNICODE

CBatchWriter::~CBatchWriter(void)
{
}

CBatchWriter::CBatchWriter(CString &fil, CString &pth, CString &prg, CString &args, CStringArray *pArr)
{
  m_file = fil;
  m_path = pth;
  m_prog = prg;
  m_args = args;
  m_pFiles = pArr;
  if ( m_path.Right(1) != "\\" )
	  m_path += "\\";
}


void CBatchWriter::WriteOne(CString str)
{
 fprintf(stream,"%ls%ls %ls %ls\n", (LPCTSTR) m_path, (LPCTSTR)m_prog,
	 (LPCTSTR)str, (LPCTSTR)m_args );
}


void CBatchWriter::WriteBatch() 
{
	stream = _tfopen((LPCTSTR)m_file,_T("wt"));
	if ( stream == NULL ) {
	   do_error(m_file);
	   return;
	}
	for ( int i = 0; i < m_pFiles->GetSize(); i++ ) {
	   WriteOne(m_pFiles->GetAt(i));
	}
    fclose(stream);
}

#endif