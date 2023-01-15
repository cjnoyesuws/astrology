#include "stdafx.h"
#include "regdbexport.h"
#include "errors.fns"

CRegDbExport::~CRegDbExport(void)
{
 if ( set.IsOpen() ) set.Close(); 
}


void CRegDbExport::Process(void)
{
 TCHAR errbuf[500];
 CString type;
 CString h3 = "";
 try {
    CString strSort = "TextType,key1,key2";
    CString strFilter = "";
	if ( m_Lang.GetLength() ) {
	    strFilter = "Lang='" + m_Lang + "'";
       }
	CString strTable = "RegularText";
    set.Open(dbOpenDynaset,MakeSQL(strTable,strFilter,strSort));
	while ( set.IsEOF() == FALSE ) {
	    if ( type != set.m_TextType ) {
		   if ( m_stream != NULL )
			   CloseFile();
		   OpenFile("2-" +set.m_TextType + ".AST");
		}
		WriteHeader(set.m_Key1,set.m_key2,h3);
		WriteText(set.m_Text);
		type = set.m_TextType;
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
