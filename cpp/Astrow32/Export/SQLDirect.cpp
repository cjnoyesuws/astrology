#include "stdafx.h"
#include "dataarray.h"
#include "SQLDirect.h"


bool SQLDirect::ExecInsert( char *pTable ) // throws CDBException 
{
 CString str = "INSERT INTO ";
 str += pTable;
 str += " ";
 if ( mpFlds == NULL )
	 return false;
 str += mpFlds->GetFieldList();
 str += " VALUES ";
 str += mpFlds->GetAsValuesClause();
 m_Str = str; 
 mp_db->ExecuteSQL(str);
 return true;
}

bool SQLDirect::ExecUpdate( char *pTable )	// throws CDBException 
{
 CString str = "UPDATE ";
 str += pTable;
 if ( mpSet == NULL )
	 return false;
 str += mpSet->GetAsSetList();
 str += " "; 
 if ( mpWhere == NULL )
	 return false;
 str += mpWhere->GetAsWhereClause();
 m_Str = str; 
 mp_db->ExecuteSQL(str);
 return true;
}
