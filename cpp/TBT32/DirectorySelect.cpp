// DirectorySelect.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "DirectorySelect.h"
#include ".\directoryselect.h"


// CDirectorySelect

IMPLEMENT_DYNAMIC(CDirectorySelect, CFileDialog)
CDirectorySelect::CDirectorySelect(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(FALSE, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
    if ( bOpenFileDialog )
	   m_pOFN->lpstrTitle = _T("Select a Directory to Import From");
	else
	   m_pOFN->lpstrTitle = _T("Select a Directory to Export To");
}

CDirectorySelect::~CDirectorySelect()
{
}


BEGIN_MESSAGE_MAP(CDirectorySelect, CFileDialog)
END_MESSAGE_MAP()



// CDirectorySelect message handlers


void CDirectorySelect::OnFolderChange()
{
	// TODO: Add your specialized code here and/or call the base class
    m_dir = GetFolderPath();
	CFileDialog::OnFolderChange();
}

BOOL CDirectorySelect::OnFileNameOK()
{
	// TODO: Add your specialized code here and/or call the base class
    
	return FALSE;
}

void CDirectorySelect::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CFileDialog::OnOK();
}

BOOL CDirectorySelect::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class

	return CFileDialog::OnNotify(wParam, lParam, pResult);
}

void CDirectorySelect::OnFileNameChange()
{
	// TODO: Add your specialized code here and/or call the base class

	CFileDialog::OnFileNameChange();
}
