// FileListSet.cpp : implementation file
//

#include "stdafx.h"
#include "importtool.h"
#include "FileListSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileListSet

IMPLEMENT_DYNAMIC(CFileListSet, CRecordset)

CFileListSet::CFileListSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CFileListSet)
	m_name = _T("");
	m_comments = _T("");
	m_filename = _T("");
	m_filenum = 0;
	m_IsTextReport = FALSE;
	m_FileType = 0;
	m_counter = 0;
	m_has_comments = FALSE;
	m_has_cover = FALSE;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CFileListSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=astrow");
}

CString CFileListSet::GetDefaultSQL()
{
	return _T("[FileList]");
}

void CFileListSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CFileListSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[comments]"), m_comments);
	RFX_Text(pFX, _T("[filename]"), m_filename);
	RFX_Int(pFX, _T("[filenum]"), m_filenum);
	RFX_Bool(pFX, _T("[IsTextReport]"), m_IsTextReport);
	RFX_Byte(pFX, _T("[FileType]"), m_FileType);
	RFX_Long(pFX, _T("[counter]"), m_counter);
	RFX_Bool(pFX, _T("[has_comments]"), m_has_comments);
	RFX_Bool(pFX, _T("[has_cover]"), m_has_cover);
	if ( m_nParams > 0 ) {
		pFX->SetFieldType(CFieldExchange::inputParam);
		RFX_Bool(pFX, _T("[IsTextReportParam]"), m_IsTextReportParam);
		if ( m_nParams > 1 )
			RFX_Long(pFX, _T("[counterParam]"), m_counterParam);
       }
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFileListSet diagnostics

#ifdef _DEBUG
void CFileListSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFileListSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
