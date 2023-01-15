// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__8B611B57_2E27_4E6A_AEED_303F19E4A58A__INCLUDED_)
#define AFX_MAINFRM_H__8B611B57_2E27_4E6A_AEED_303F19E4A58A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CChildView    m_wndView;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnAspecttext();
	afx_msg void OnImportImportahelpfile();
	afx_msg void OnUpdateImportImportahelpfile(CCmdUI* pCmdUI);
	afx_msg void OnImportImportaspecttext();
	afx_msg void OnUpdateImportImportaspecttext(CCmdUI* pCmdUI);
	afx_msg void OnImportImportplanethousetext();
	afx_msg void OnUpdateImportImportplanethousetext(CCmdUI* pCmdUI);
	afx_msg void OnImportImportreporttext();
	afx_msg void OnUpdateImportImportreporttext(CCmdUI* pCmdUI);
	afx_msg void OnRegulartxt();
	afx_msg void OnUpdateRegulartxt(CCmdUI* pCmdUI);
	afx_msg void OnHelptxt();
	afx_msg void OnUpdateHelptxt(CCmdUI* pCmdUI);
	afx_msg void OnEdittextsourcesReporttextsources();
	afx_msg void OnUpdateEdittextsourcesReporttextsources(CCmdUI* pCmdUI);
	afx_msg void OnOptionsSetup();
	afx_msg void OnUpdateOptionsSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAspecttext(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnArraytext();
	afx_msg void OnUpdateArraytext(CCmdUI *pCmdUI);
	afx_msg void OnAddlanguage();
	afx_msg void OnUpdateAddlanguage(CCmdUI *pCmdUI);
	afx_msg void OnSetLanguage();
	afx_msg void OnUpdateSetLanguage(CCmdUI *pCmdUI);
	afx_msg void OnExportExportaspecttext();
	afx_msg void OnUpdateExportExportaspecttext(CCmdUI *pCmdUI);
	afx_msg void OnExportExporthelp();
	afx_msg void OnUpdateExportExporthelp(CCmdUI *pCmdUI);
	afx_msg void OnExportExportregulartext();
	afx_msg void OnUpdateExportExportregulartext(CCmdUI *pCmdUI);
	afx_msg void OnExportExportreports();
	afx_msg void OnUpdateExportExportreports(CCmdUI *pCmdUI);
	afx_msg void OnImportImportexportedaspectfile();
	afx_msg void OnUpdateImportImportexportedaspectfile(CCmdUI *pCmdUI);
	afx_msg void OnImportImportexportedhelpfile();
	afx_msg void OnUpdateImportImportexportedhelpfile(CCmdUI *pCmdUI);
	afx_msg void OnImportImportexportedplanet();
	afx_msg void OnUpdateImportImportexportedplanet(CCmdUI *pCmdUI);
	afx_msg void OnImportImportexportedreportfile();
	afx_msg void OnUpdateImportImportexportedreportfile(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8B611B57_2E27_4E6A_AEED_303F19E4A58A__INCLUDED_)
