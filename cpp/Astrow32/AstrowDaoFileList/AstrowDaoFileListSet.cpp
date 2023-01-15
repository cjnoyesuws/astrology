// AstrowDaoFileListSet.cpp : implementation of the CAstrowDaoFileListSet class
//

#include "stdafx.h"
#include "AstrowDaoFileList.h"
#include "AstrowDaoFileListSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListSet implementation

IMPLEMENT_DYNAMIC(CAstrowDaoFileListSet, CDaoRecordset)

CAstrowDaoFileListSet::CAstrowDaoFileListSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAstrowDaoFileListSet)
	m_name = _T("");
	m_comments = _T("");
	m_filename = _T("");
	m_filenum = 0;
	m_IsTextReport = FALSE;
	m_FileType = 0;
	m_counter = 0;
	m_has_cover = FALSE;
	m_has_comments = FALSE;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CAstrowDaoFileListSet::GetDefaultDBName()
{
	return _T("D:\\Astrow32\\DB\\astrow972a.mdb");
}


CString CAstrowDaoFileListSet::GetDefaultSQL()
{
	return _T("[FileList]");
}

void CAstrowDaoFileListSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAstrowDaoFileListSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[name]"), m_name);
	DFX_Text(pFX, _T("[comments]"), m_comments);
	DFX_Text(pFX, _T("[filename]"), m_filename);
	DFX_Short(pFX, _T("[filenum]"), m_filenum);
	DFX_Bool(pFX, _T("[IsTextReport]"), m_IsTextReport);
	DFX_Byte(pFX, _T("[FileType]"), m_FileType);
	DFX_Long(pFX, _T("[counter]"), m_counter);
	DFX_Bool(pFX, _T("[has_cover]"), m_has_cover);
	DFX_Bool(pFX, _T("[has_comments]"), m_has_comments);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListSet diagnostics

#ifdef _DEBUG
void CAstrowDaoFileListSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CAstrowDaoFileListSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
