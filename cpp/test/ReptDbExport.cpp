#include "stdafx.h"
#include "reptdbexport.h"
#include "errors.fns"

CReptDbExport::~CReptDbExport(void)
{
 if ( set.IsOpen() ) set.Close(); 
}


void CReptDbExport::Process(void)
{
 TCHAR errbuf[500];
 CString type;
 CString h2 = "", h3 = "", plu = "+";
 try {
    CString strSort = "texttype,textkey,iIndex";
    CString strFilter = "";
	if ( m_Lang.GetLength() ) {
	    strFilter = "Lang='" + m_Lang + "'";
       }
    CString strTable = "ReportText";
	set.Open(dbOpenDynaset,MakeSQL(strTable,strFilter,strSort));
	while ( set.IsEOF() == FALSE ) {
	    if ( type != set.m_texttype ) {
		   if ( m_stream != NULL )
			   CloseFile();
		   OpenFile("1-" + set.m_texttype + ".AST");
		}
	    if ( set.m_iIndex == 0 )
           WriteHeader(set.m_textkey,h2,h3);
		else
		   WriteHeader(plu,h2,h3);
		set.m_text += "\n";
		WriteText(set.m_text);
		type = set.m_texttype;
		set.MoveNext();
	}
	set.Close();
	fclose(m_stream);
 }
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
   return;
  }
}
