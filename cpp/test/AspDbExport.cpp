#include "stdafx.h"
#include "aspdbexport.h"
#include "errors.fns"

CAspDbExport::~CAspDbExport(void)
{
 if ( set.IsOpen() ) set.Close(); 
}


void CAspDbExport::Process(void)
{
 TCHAR errbuf[500];
 CString type;
 try {
    CString strSort = "TextType,Planet1,Planet2,Aspect";
    CString strFilter = "";
	if ( m_Lang.GetLength() ) {
	   strFilter = "Lang='" + m_Lang + "'";
       }
	CString strTable = "AspectText";
    set.Open(dbOpenDynaset,MakeSQL(strTable,strFilter,strSort));
	while ( set.IsEOF() == FALSE ) {
	    if ( type != set.m_TextType ) {
		   if ( m_stream != NULL )
			   CloseFile();
		   OpenFile("3-" + set.m_TextType + ".AST");
		}
		WriteHeader(set.m_Planet1,set.m_Planet2,set.m_Aspect);
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