// ImporterData.h: interface for the ImporterData class.
//
//////////////////////////////////////////////////////////////////////

#include "progress.h"
#if !defined(AFX_IMPORTERDATA_H__EABDC1F2_EBD5_435B_A0C9_EF19AD1CC5AD__INCLUDED_)
#define AFX_IMPORTERDATA_H__EABDC1F2_EBD5_435B_A0C9_EF19AD1CC5AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImporttoolDlg;

class ImporterData  
{
public:
	ImporterData();
	virtual ~ImporterData();
	CString m_dbdir;
	CString m_txtdir;
	CString m_userdir;
	BOOL m_text;
	BOOL m_locs;;
	BOOL m_files;
	BOOL m_births;
    HWND m_hWnd;
    char buffer[500];
	CString m_olddir;
	CImporttoolDlg *m_progress;
};

#endif // !defined(AFX_IMPORTERDATA_H__EABDC1F2_EBD5_435B_A0C9_EF19AD1CC5AD__INCLUDED_)
