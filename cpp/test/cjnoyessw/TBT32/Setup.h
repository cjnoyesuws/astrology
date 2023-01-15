#if !defined(AFX_SETUP_H__AC953A6E_C0FE_4537_9E3A_6C8AD0670B7D__INCLUDED_)
#define AFX_SETUP_H__AC953A6E_C0FE_4537_9E3A_6C8AD0670B7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetup dialog

class CSetup : public CDialog
{
// Construction
public:
	CSetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetup)
	enum { IDD = IDD_SETUP };
	CString	m_Dir;
	CString	m_dbdir;
	CString	m_database;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetup)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

extern CString GetDatabaseName();
extern CString GetSrcDir();
extern CString GetDatabasePath();
extern CString GetDatabaseNamePath();
extern CString quote(CString &s);
extern CString &GetCurLanguage();
#endif // !defined(AFX_SETUP_H__AC953A6E_C0FE_4537_9E3A_6C8AD0670B7D__INCLUDED_)
