#if !defined(AFX_DATATEST_H__7C0054D1_D3D8_11D1_9DAC_0000C00DEE96__INCLUDED_)
#define AFX_DATATEST_H__7C0054D1_D3D8_11D1_9DAC_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataTest.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDataTest command target

class CDataTest : public CCmdTarget
{
	DECLARE_DYNCREATE(CDataTest)

	CDataTest();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataTest)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDataTest();

	// Generated message map functions
	//{{AFX_MSG(CDataTest)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDataTest)
	afx_msg BSTR GetName();
	afx_msg void SetName(LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATEST_H__7C0054D1_D3D8_11D1_9DAC_0000C00DEE96__INCLUDED_)
