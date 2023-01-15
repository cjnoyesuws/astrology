// OpenFiles.h : main header file for the OpenFiles application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// COpenFilesApp:
// See OpenFiles.cpp for the implementation of this class
//

class COpenFilesApp : public CWinApp
{
public:
	COpenFilesApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenFilesApp theApp;