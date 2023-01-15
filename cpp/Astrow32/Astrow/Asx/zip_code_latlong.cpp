// zip_code_latlong.h : Implementation of the Czip_code_latlong class



// Czip_code_latlong implementation

// code generated on Friday, July 01, 2005, 1:03 AM

#include "stdafx.h"
#include "zip_code_latlong.h"
#include "direc.hpp"
IMPLEMENT_DYNAMIC(Czip_code_latlong, CDaoRecordset)

Czip_code_latlong::Czip_code_latlong(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pDatabase))
{
	m_zip_code = _T("");
	m_longitude = _T("");
	m_latitude = _T("");
	m_nFields = 3;
	m_nDefaultType = dbOpenDynaset;
}

CString Czip_code_latlong::GetDefaultConnect()
{
	return _T("DSN=Astrow;DBQ=C:\\Astrow32Dev\\Astrow32\\DB\\astrow.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString Czip_code_latlong::GetDefaultSQL()
{
	return _T("[zip_code_latlong]");
}

void Czip_code_latlong::DoFieldExchange(CDaoFieldExchange* pFX)
{
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	DFX_Text(pFX, _T("[zip_code]"), m_zip_code);
	DFX_Text(pFX, _T("[longitude]"), m_longitude);
	DFX_Text(pFX, _T("[latitude]"), m_latitude);

}

CString Czip_code_latlong::GetDefaultDBName()
{
	return GetDatabaseName();
}
/////////////////////////////////////////////////////////////////////////////
// Czip_code_latlong diagnostics

#ifdef _DEBUG
void Czip_code_latlong::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void Czip_code_latlong::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}



#endif //_DEBUG


