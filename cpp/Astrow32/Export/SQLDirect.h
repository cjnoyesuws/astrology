#ifndef _SQLDIRECT_H_
#define _SQLDIRECT_H_

class SQLDirect {
private:
CDatabase *mp_db;
DataArray *mpWhere;
DataArray *mpSet;
DataArray *mpFlds;
CString m_Str;
public:
	~SQLDirect() {}
	SQLDirect( CDatabase &db ) { mp_db = &db; mpWhere = NULL; mpSet = NULL; mpFlds = NULL; }
	void SetWhereKeys( DataArray &p ) { mpWhere = &p; }		
    void SetInsertFields( DataArray &p ) { mpFlds = &p; }		
	void SetUpdateFields( DataArray &p ) { mpSet = &p; }		
	bool ExecInsert( char *pTable ); // throws CDBException 
	bool ExecUpdate( char *pTable );	// throws CDBException 
	CString GetExecStr() { return m_Str; }
};








#endif /* _SQLDIRECT_H_ */