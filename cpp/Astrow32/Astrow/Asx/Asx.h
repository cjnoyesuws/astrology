// Asx.h : main header file for the Asx application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CAsxApp:
// See Asx.cpp for the implementation of this class
//

class CAsxApp : public CWinApp
{
public:
	CAsxApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAsxApp theApp;