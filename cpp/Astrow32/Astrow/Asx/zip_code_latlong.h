// zip_code_latlong.h : Declaration of the Czip_code_latlong

#pragma once

// code generated on Friday, July 01, 2005, 1:03 AM

class Czip_code_latlong : public CDaoRecordset
{
public:
	Czip_code_latlong(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Czip_code_latlong)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	CString	m_zip_code;
	CString	m_longitude;
	CString	m_latitude;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultDBName();
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


