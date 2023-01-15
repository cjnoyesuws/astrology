#if !defined(AFX_EDITDATA_H__AC727BA1_DA55_11D1_9DB4_0000C00DEE96__INCLUDED_)
#define AFX_EDITDATA_H__AC727BA1_DA55_11D1_9DB4_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditData dialog

class CEditData : public CDialog
{
// Construction
public:
	CEditData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditData)
	enum { IDD = IDD_EDITDAT };
	CString	m_options;
	CString	m_path;
	BOOL	m_useext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditData)
	afx_msg void OnUseext();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDATA_H__AC727BA1_DA55_11D1_9DB4_0000C00DEE96__INCLUDED_)
