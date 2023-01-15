// ImporterData.h: interface for the ImporterData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTERDATA_H__EABDC1F2_EBD5_435B_A0C9_EF19AD1CC5AD__INCLUDED_)
#define AFX_IMPORTERDATA_H__EABDC1F2_EBD5_435B_A0C9_EF19AD1CC5AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ImporterData  
{
public:
	ImporterData();
	virtual ~ImporterData();
	CString m_source;
	CString m_table;
	CString m_sort;
	CString m_pkeys;
    CProgressCtrl *m_pProgress;
    char buffer[500];
	CString m_dest;
	CADODatabase *m_pSourceDb;
	CADODatabase *m_pDestDb;
};

#endif // !defined(AFX_IMPORTERDATA_H__EABDC1F2_EBD5_435B_A0C9_EF19AD1CC5AD__INCLUDED_)
