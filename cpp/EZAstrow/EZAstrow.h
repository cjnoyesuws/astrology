// EZAstrow.h : main header file for the EZAstrow application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CEZAstrowApp:
// See EZAstrow.cpp for the implementation of this class
//

class CEZAstrowApp : public CWinApp
{
public:
	CEZAstrowApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEZAstrowApp theApp;