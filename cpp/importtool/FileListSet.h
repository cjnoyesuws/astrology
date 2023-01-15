// FileListSet.h : Declaration of the CFileListSet

#pragma once

// code generated on Friday, July 01, 2005, 1:05 AM

class CFileListSet : public CDaoRecordset
{
public:
	CFileListSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFileListSet)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	CString	m_name;
	CString	m_comments;
	CString	m_filename;
	short	m_filenum;
	BOOL	m_IsTextReport;
	BYTE	m_FileType;
	long	m_counter;
	BOOL	m_has_cover;
	BOOL	m_has_comments;
	CString	m_ListType;
	short	m_Folder;

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


