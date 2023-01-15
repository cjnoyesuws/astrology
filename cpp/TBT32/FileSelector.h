#if !defined(AFX_FILESELECTOR_H__AA924949_2A8F_4E4C_915E_8CE9C380056B__INCLUDED_)
#define AFX_FILESELECTOR_H__AA924949_2A8F_4E4C_915E_8CE9C380056B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileSelector.h : header file
//
#include <afxcoll.h>
/////////////////////////////////////////////////////////////////////////////
// CFileSelector dialog

class CFileSelector : public CDialog
{
// Construction
public:
	CFileSelector(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSelector)
	enum { IDD = IDD_SEL_FILE };
	CString	m_File;
	//}}AFX_DATA
   int m_type;
   CStringArray m_FileAry;
   CString m_import_dir;
   BOOL m_bExport;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSelector)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileSelector)
	afx_msg void OnSelchangeFiles();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImportDir();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESELECTOR_H__AA924949_2A8F_4E4C_915E_8CE9C380056B__INCLUDED_)
