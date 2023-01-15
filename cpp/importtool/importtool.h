// importtool.h : main header file for the IMPORTTOOL application
//

#if !defined(AFX_IMPORTTOOL_H__C259834D_3B9C_4C94_AAB8_A17F953543F3__INCLUDED_)
#define AFX_IMPORTTOOL_H__C259834D_3B9C_4C94_AAB8_A17F953543F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImporttoolApp:
// See importtool.cpp for the implementation of this class
//

class CImporttoolApp : public CWinApp
{
public:
	CImporttoolApp();
    int _Yield(int no);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImporttoolApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL InitApplication();
	//}}AFX_VIRTUAL
  
// Implementation

	//{{AFX_MSG(CImporttoolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTTOOL_H__C259834D_3B9C_4C94_AAB8_A17F953543F3__INCLUDED_)
