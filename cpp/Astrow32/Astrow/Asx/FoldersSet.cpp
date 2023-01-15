// FoldersSet.h : Implementation of the CFoldersSet class



// CFoldersSet implementation

// code generated on Friday, July 01, 2005, 1:05 AM

#include "stdafx.h"
#include "FoldersSet.h"
#include "direc.hpp"
IMPLEMENT_DYNAMIC(CFoldersSet, CDaoRecordset)

CFoldersSet::CFoldersSet(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pDatabase))
{
	m_folder_num = 0;
	m_folder_name = _T("");
	m_nFields = 2;
	m_nDefaultType = dbOpenDynaset;
}

CString CFoldersSet::GetDefaultConnect()
{
	return _T("DSN=Astrow;DBQ=C:\\Astrow32Dev\\Astrow32\\DB\\astrow.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CFoldersSet::GetDefaultSQL()
{
	return _T("[Folders]");
}

void CFoldersSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	DFX_Short(pFX, _T("[folder_num]"), m_folder_num);
	DFX_Text(pFX, _T("[folder_name]"), m_folder_name);

}
/////////////////////////////////////////////////////////////////////////////
// CFoldersSet diagnostics

#ifdef _DEBUG
void CFoldersSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CFoldersSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

CString CFoldersSet::GetDefaultDBName()
{
	return GetDatabaseName();
}

