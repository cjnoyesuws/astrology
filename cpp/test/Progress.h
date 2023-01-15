#if !defined(AFX_PROGRESS_H__A4209545_B8C0_4B4F_9397_D0935FECEC4D__INCLUDED_)
#define AFX_PROGRESS_H__A4209545_B8C0_4B4F_9397_D0935FECEC4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Progress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgress dialog

class CProgress : public CDialog
{
// Construction
public:
	CProgress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgress)
	enum { IDD = IDD_PROGRESS };
	CProgressCtrl	m_Ctrl;
	CString	m_File;
	//}}AFX_DATA
    void SetFile(CString &s);
    void SetMax(int m);
	void IncProgress();
    void Reset();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgress)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESS_H__A4209545_B8C0_4B4F_9397_D0935FECEC4D__INCLUDED_)
