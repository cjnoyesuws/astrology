// ChartEdit.h : main header file for the CHARTEDIT application
//

#if !defined(AFX_CHARTEDIT_H__A63EC40D_DB51_417B_91AC_A6CDCD9C145A__INCLUDED_)
#define AFX_CHARTEDIT_H__A63EC40D_DB51_417B_91AC_A6CDCD9C145A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChartEditApp:
// See ChartEdit.cpp for the implementation of this class
//

class CChartEditApp : public CWinApp
{
public:
	CChartEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CChartEditApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTEDIT_H__A63EC40D_DB51_417B_91AC_A6CDCD9C145A__INCLUDED_)
