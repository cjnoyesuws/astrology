#pragma once


// CDirectorySelect

class CDirectorySelect : public CFileDialog
{
	DECLARE_DYNAMIC(CDirectorySelect)

public:
	CDirectorySelect(BOOL bOpenFileDialog=FALSE, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = (LPCTSTR)_T(".Ast"),
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY,
		LPCTSTR lpszFilter = (LPCTSTR)_T("Text Files (*.ast)|*.ast|All Files (*.*)|*.*||"),
		CWnd* pParentWnd = NULL);
	virtual ~CDirectorySelect();
	CString GetDirectory() { return m_dir; }
protected:
	CString m_dir;
	DECLARE_MESSAGE_MAP()
	virtual void OnFolderChange();
	virtual BOOL OnFileNameOK();
	virtual void OnOK();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnFileNameChange();
};


