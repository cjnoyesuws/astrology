// Astrograph.h : main header file for the ASTROGRAPH application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "\astrow32Dev\astrow32\astrow\resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAstrographApp:
// See Astrograph.cpp for the implementation of this class
//

class CAstrographApp : public CWinApp
{
public:
	CAstrographApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrographApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAstrographApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
