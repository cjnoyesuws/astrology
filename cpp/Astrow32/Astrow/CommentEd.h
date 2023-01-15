#if !defined(AFX_COMMENTED_H__99D0F661_DE15_11D1_9DB6_0000C00DEE96__INCLUDED_)
#define AFX_COMMENTED_H__99D0F661_DE15_11D1_9DB6_0000C00DEE96__INCLUDED_

#include "Fptr.h"	// Added by ClassView
#include "rtffuncs.h"
#include "tabctrlctrl1.h"
#include "wspell.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommentEd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommentEd dialog

class CCommentEd : public CDialog
{
// Construction
public:
	XPFILE_DB *m_fdb;
	void SetFileNameFdb( char *fileName, XPFILE_DB *fdp);
	CCommentEd(CWnd* pParent = NULL);   // standard constructor
    CString m_fname;
	RTFFuncs *pFuncs;
// Dialog Data
	//{{AFX_DATA(CCommentEd)
	enum { IDD = IDD_COMMENT };
	CString	m_edit;
	//}}AFX_DATA
     
    void load();
	void save();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommentEd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommentEd)
	virtual void OnOK();
	afx_msg void OnHelp();
	virtual BOOL OnInitDialog();
   afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnItalic();
	afx_msg void OnUpdateItalic(CCmdUI* pCmdUI);
	afx_msg void OnNormal();
	afx_msg void OnUpdateNormal(CCmdUI* pCmdUI);
	afx_msg void OnHeading();
	afx_msg void OnUpdateHeading(CCmdUI* pCmdUI);
	afx_msg void OnBold();
	afx_msg void OnUpdateBold(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnSpell();
	afx_msg void OnUpdateSpell(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    CTabctrlctrl1 m_tabctrl;
	CWSpell	m_ctrl;
public:
	afx_msg void OnEnChangeEdit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMENTED_H__99D0F661_DE15_11D1_9DB6_0000C00DEE96__INCLUDED_)
