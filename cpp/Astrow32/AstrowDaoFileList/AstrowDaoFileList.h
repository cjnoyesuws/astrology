// AstrowDaoFileList.h : main header file for the ASTROWDAOFILELIST application
//

#if !defined(AFX_ASTROWDAOFILELIST_H__D57F404B_0A7C_4363_91DF_28A59C377D56__INCLUDED_)
#define AFX_ASTROWDAOFILELIST_H__D57F404B_0A7C_4363_91DF_28A59C377D56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListApp:
// See AstrowDaoFileList.cpp for the implementation of this class
//

class CAstrowDaoFileListApp : public CWinApp
{
public:
	CAstrowDaoFileListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrowDaoFileListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CAstrowDaoFileListApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASTROWDAOFILELIST_H__D57F404B_0A7C_4363_91DF_28A59C377D56__INCLUDED_)
