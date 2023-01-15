// Astrogrid.h : main header file for the Astrogrid application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CAstrogridApp:
// See Astrogrid.cpp for the implementation of this class
//

class CAstrogridApp : public CWinApp
{
public:
	CAstrogridApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAstrogridApp theApp;