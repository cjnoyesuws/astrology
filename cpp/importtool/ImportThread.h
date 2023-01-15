#if !defined(AFX_IMPORTTHREAD_H__E843270C_8FCD_4296_876F_B0AB8BAC2EDF__INCLUDED_)
#define AFX_IMPORTTHREAD_H__E843270C_8FCD_4296_876F_B0AB8BAC2EDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CImportThread thread

class CImportThread : public CWinThread
{
	DECLARE_DYNCREATE(CImportThread)
protected:
	CImportThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CImportThread();

	// Generated message map functions
	//{{AFX_MSG(CImportThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTTHREAD_H__E843270C_8FCD_4296_876F_B0AB8BAC2EDF__INCLUDED_)
