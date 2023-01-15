// xtest.h : main header file for the XTEST application
//

#if !defined(AFX_XTEST_H__55100987_843B_11D1_9D9B_0000C00DEE96__INCLUDED_)
#define AFX_XTEST_H__55100987_843B_11D1_9D9B_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXtestApp:
// See xtest.cpp for the implementation of this class
//

class CXtestApp : public CWinApp
{
public:
	CXtestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXtestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CXtestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTEST_H__55100987_843B_11D1_9D9B_0000C00DEE96__INCLUDED_)
