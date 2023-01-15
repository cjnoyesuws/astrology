#include "stdafx.h"
#include <afxcoll.h>
#include "datatypeholder.h"
#include "dataarray.h"




CString DataArray::FieldRep( int i )
{
 CString str;
 if ( i >= count )
	 return str;
 DataTypeHolder *pHolder = (DataTypeHolder*)array.ElementAt(i);
 if ( pHolder == NULL )
 switch( pHolder->data_type ) {
	case STRTYPE:
    	str = "\'"+*pHolder->data.str_data+"\'";
		break;
	case DATETYPE:
#ifdef ORACLE
		str = pHolder->data.date_data->Format("\'%d-%b-%y\'");
#else
		str = pHolder->data.date_data->Format("\'%m/%d/%Y\'");
#endif
		break;
	case INTTYPE:
		str.Format("\'%d\'",pHolder->data.int_data);
		break;
    case DBLTYPE:
		str.Format("\'%lf\'",pHolder->data.dbl_data);
		break;
	default:
		break;
		}
	 return str;
}

void DataArray::AddIntField( int data, char *field )
{
 DataTypeHolder *pHolder = new DataTypeHolder;
 pHolder->field_name = field;
 pHolder->data_type =INTTYPE;
 pHolder->data.int_data = data;
 array.SetAtGrow(count++,pHolder);
}

void DataArray::AddStrField( CString &data, char *field )
{
 DataTypeHolder *pHolder = new DataTypeHolder;
 pHolder->field_name = field;
 pHolder->data_type =STRTYPE;
 CString *pStr = new CString(data);
 pHolder->data.str_data = pStr;
 array.SetAtGrow(count++,pHolder);
}

void DataArray::AddDateField( COleDateTime &data, char *field )
{
 DataTypeHolder *pHolder = new DataTypeHolder;
 pHolder->field_name = field;
 pHolder->data_type =DATETYPE;
 COleDateTime *pDate = new COleDateTime(data);
 pHolder->data.date_data = pDate;
 array.SetAtGrow(count++,pHolder);
}

void DataArray::AddDoubleField( double &data, char *field )
{
 DataTypeHolder *pHolder = new DataTypeHolder;
 pHolder->field_name = field;
 pHolder->data_type =DBLTYPE;
 pHolder->data.dbl_data = data;
 array.SetAtGrow(count++,pHolder);
}

CString DataArray::GetFieldList()
{
 CString str = "(";
 for ( int i = 0; i < count; i++ ) {
	 char *p = GetFieldName(i);
	 str += p;
	 if ( i < count-1 )
	 str += ",";
	 }
 str += ")";
 return str;	
}

char *DataArray::GetFieldName( int i )
{
 if ( i >= count )
	 return NULL;
 DataTypeHolder *pHolder = (DataTypeHolder*)array.ElementAt(i);
 if ( pHolder == NULL )
	 return NULL;
 return pHolder->field_name;
}

CString DataArray::GetAsSetList()
{
 CString str = "SET ";
 for ( int i = 0; i < count; i++ ) {
	 char *p = GetFieldName(i);
	 CString fld = FieldRep(i);
	 str += p;
	 str += "=";
	 str += fld;
	 if ( i < count-1 )
	 str += ",";
	 }
 return str;
}

CString DataArray::GetAsWhereClause()
{
  CString str = "WHERE ";
  for ( int i = 0; i < count; i++ ) {
	 char *p = GetFieldName(i);
	 CString fld = FieldRep(i);
	 str += p;
	 str += "=";
	 str += fld;
	 if ( i < count-1 )
	 str += " AND ";
	 }
 return str;
}

CString DataArray::GetAsValuesClause()
{
 CString str = "(";
 for ( int i = 0; i < count; i++ ) {
	 CString fld = FieldRep(i);
	 str += fld;
	 if ( i < count-1 )
	 str += ",";
	 }
 str += ")";
 return str;	
}

DataArray::~DataArray()
{
  for ( int i = 0; i < count; i++ ) {
      DataTypeHolder *pHolder = (DataTypeHolder*)array.ElementAt(i);
	  if ( pHolder != NULL ) {
		switch( pHolder->data_type ) {
		case STRTYPE:
			delete pHolder->data.str_data;
			break;
		case DATETYPE:
			delete pHolder->data.date_data;
			break;
		default:
			break;
			}
		delete pHolder;		
		}
			
	}
     
}
