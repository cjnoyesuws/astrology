// FileListSet.h : Implementation of the CFileListSet class



// CFileListSet implementation

// code generated on Friday, July 01, 2005, 1:05 AM

#include "stdafx.h"
#include "FileListSet.h"
#include "direc.hpp"
IMPLEMENT_DYNAMIC(CFileListSet, CDaoRecordset)

CFileListSet::CFileListSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	m_name = _T("");
	m_comments = _T("");
	m_filename = _T("");
	m_filenum = 0;
	m_IsTextReport = FALSE;
	m_FileType = 0;
	m_counter = 0;
	m_has_cover = FALSE;
	m_has_comments = FALSE;
	m_ListType = _T("");
	m_Folder = 0;
	m_nFields = 11;
	m_nDefaultType = dbOpenDynaset;
}
CString CFileListSet::GetDefaultConnect()
{
	return _T("DSN=Astrow");
}

CString CFileListSet::GetDefaultSQL()
{
	return _T("[FileList]");
}

void CFileListSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	DFX_Text(pFX, _T("[name]"), m_name);
	DFX_Text(pFX, _T("[comments]"), m_comments);
	DFX_Text(pFX, _T("[filename]"), m_filename);
	DFX_Short(pFX, _T("[filenum]"), m_filenum);
	DFX_Bool(pFX, _T("[IsTextReport]"), m_IsTextReport);
	DFX_Byte(pFX, _T("[FileType]"), m_FileType);
	DFX_Long(pFX, _T("[counter]"), m_counter);
	DFX_Bool(pFX, _T("[has_cover]"), m_has_cover);
	DFX_Bool(pFX, _T("[has_comments]"), m_has_comments);
	DFX_Text(pFX, _T("[ListType]"), m_ListType);
	DFX_Short(pFX, _T("[Folder]"), m_Folder);
	if ( m_Folder > 200 )
		m_Folder = 0;

}
/////////////////////////////////////////////////////////////////////////////
// CFileListSet diagnostics

#ifdef _DEBUG
void CFileListSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CFileListSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

CString CFileListSet::GetDefaultDBName()
{
	return GetDatabaseName();
}


