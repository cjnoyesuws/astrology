// zip_code_latlong.h : Declaration of the Czip_code_latlong

#pragma once

// code generated on Friday, July 01, 2005, 1:56 AM

[
	#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
db_source(L"Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=C:\\Astrow32Dev\\Astrow32\\DB\\astrow.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False"),
	db_command(L" \
	SELECT \
		latitude, \
		longitude, \
		zip_code \
		FROM zip_code_latlong")
]
class Czip_code_latlong
{
public:

	// In order to fix several issues with some providers, the code below may bind
	// columns in a different order than reported by the provider

	[ db_column(1, status=m_dwlatitudeStatus, length=m_dwlatitudeLength) ] TCHAR m_latitude[11];
	[ db_column(2, status=m_dwlongitudeStatus, length=m_dwlongitudeLength) ] TCHAR m_longitude[11];
	[ db_column(3, status=m_dwzip_codeStatus, length=m_dwzip_codeLength) ] TCHAR m_zip_code[6];

	// The following wizard-generated data members contain status
	// values for the corresponding fields. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwlatitudeStatus;
	DBSTATUS m_dwlongitudeStatus;
	DBSTATUS m_dwzip_codeStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwlatitudeLength;
	DBLENGTH m_dwlongitudeLength;
	DBLENGTH m_dwzip_codeLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}
};


