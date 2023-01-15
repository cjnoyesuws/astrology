#ifndef _DATAARRAY_H_
#define _DATAARRAY_H_

#include "datatypeholder.h"

class DataArray {
private:
	CPtrArray array;
	int size;
	int count;
	CString FieldRep( int i );
public:
	virtual ~DataArray();
	DataArray() { array.SetSize(20,10); size = 20; count = 0; }
	DataArray(int s, int inc = 10 ) { array.SetSize(s,inc); size = s; count = 0;}
	void AddIntField( int data, char *field );
    void AddStrField( CString &data, char *field );
	void AddDateField( COleDateTime &data, char *field );
	void AddDoubleField( double &data, char *field );
	CString GetFieldList();
    char *GetFieldName( int i );
	CString GetAsSetList();
	CString GetAsWhereClause();
	CString GetAsValuesClause();

};

#endif /* _DATAARRAY_H_ */