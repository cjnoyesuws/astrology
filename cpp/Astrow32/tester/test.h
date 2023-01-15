#if !defined(AFX_TEST_H__13A3B171_4EA5_11D3_9DE7_0000C00DEE96__INCLUDED_)
#define AFX_TEST_H__13A3B171_4EA5_11D3_9DE7_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// test.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// test command target

class test : public CCmdTarget
{
	DECLARE_DYNCREATE(test)

	test();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(test)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~test();

	// Generated message map functions
	//{{AFX_MSG(test)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(test)
	afx_msg short GetSchedule(LPCTSTR Id, LPCTSTR Date, short maxSched, LPUNKNOWN FAR* pSched);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_H__13A3B171_4EA5_11D3_9DE7_0000C00DEE96__INCLUDED_)
