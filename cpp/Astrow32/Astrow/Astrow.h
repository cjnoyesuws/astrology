// Astrow.h : main header file for the ASTROW application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "NewMultDocTmpl.h"

/////////////////////////////////////////////////////////////////////////////
// CAstrowApp:
// See Astrow.cpp for the implementation of this class
//
typedef enum filetype { GraphTypeFile, NewGraphTypeFile, TextTypeFile, NewTextTypeFile, HelpTypeFile, GridTypeFile };

class CAstrowApp : public CWinApp
{
public:
	CNewMultiDocTemplate *pGraph;
	CNewMultiDocTemplate *pText;
	CNewMultiDocTemplate *pNewGraph;
	CNewMultiDocTemplate *pNewText;
	CNewMultiDocTemplate *pHelp;
	CNewMultiDocTemplate *pFlist;
	CNewMultiDocTemplate *pGrid;
	int OpenDocSendCmdWait(enum filetype type, LPCTSTR lpszDoc, UINT cmd );
	int OpenDocBatchSendCmdWait(enum filetype type, LPCTSTR lpszDoc, UINT cmd, CStringArray *pAr, int cnt );
	BOOL checkQdt();
	CAstrowApp();
	int  _Yield(int n = 1);
	CDocument *NewUserFileList() { return( ((CDocTemplate *)pFlist)->OpenDocumentFile(NULL) ); }
    void OpenFlists();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstrowApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAstrowApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
