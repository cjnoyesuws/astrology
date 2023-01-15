// Wizard.h : main header file for the Wizard application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CWizardApp:
// See Wizard.cpp for the implementation of this class
//

class CWizardApp : public CWinApp
{
public:
	CWizardApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWizardApp theApp;