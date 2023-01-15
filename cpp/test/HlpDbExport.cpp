#include "stdafx.h"
#include "hlpdbexport.h"
#include "errors.fns"

CHlpDbExport::~CHlpDbExport(void)
{
 if ( set.IsOpen() ) set.Close(); 
}


void CHlpDbExport::Process(void)
{
 TCHAR errbuf[500];
 CString type;
 CString h1="0", h2="0", h3="";
 try {
    CString strSort = "texttype,iChunk";
    CString strFilter ="";
	if ( m_Lang.GetLength() ) {
	   strFilter = "Lang='" + m_Lang + "'";
       }
    CString strTable = "HelpText";
	set.Open(dbOpenDynaset,MakeSQL(strTable,strFilter,strSort));
	while ( set.IsEOF() == FALSE ) {
	    if ( type != set.m_texttype ) {
		   if ( m_stream != NULL )
			   CloseFile();
		   OpenFile("0-" +set.m_texttype + ".AST");
		   WriteHeader(h1,h2,h3);
		}
		WriteText(set.m_Text);
		type = set.m_texttype;
		set.MoveNext();
	}
	set.Close();
	if ( m_stream != NULL )
	   fclose(m_stream);
 }
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
   return;
  }
}