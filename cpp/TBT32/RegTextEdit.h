//{{AFX_INCLUDES()
#include "wspell.h"
//}}AFX_INCLUDES
#if !defined(AFX_REGTEXTEDIT_H__665ADF44_E0FE_4366_B63A_DED253FAFE76__INCLUDED_)
#define AFX_REGTEXTEDIT_H__665ADF44_E0FE_4366_B63A_DED253FAFE76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegTextEdit.h : header file
//
#include "dregtext1.h"
#include "rtffuncs.h"
/////////////////////////////////////////////////////////////////////////////
// CRegTextEdit dialog

class CRegTextEdit : public CDialog
{
// Construction
public:
	CRegTextEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegTextEdit)
	enum { IDD = IDD_REGTEXT };
	int		m_Key1;
	CString	m_Key2;
	CString	m_Text;
	CWSpell	m_ctrl;
	//}}AFX_DATA
   CString  m_TextType;
   CString  m_Key1Str;
   CString  m_Key2Str;
   CDregText theSet;
   BOOL     m_bModified; 
   RTFFuncs *pFuncs;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegTextEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	BOOL Find();
	BOOL Save();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegTextEdit)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeKey1();
	afx_msg void OnSelchangeKey2();
	afx_msg void OnClear();
	afx_msg void OnUpdateClear(CCmdUI* pCmdUI);
	afx_msg void OnCopy();
	afx_msg void OnUpdateCopy(CCmdUI* pCmdUI);
	afx_msg void OnCut();
	afx_msg void OnUpdateCut(CCmdUI* pCmdUI);
	afx_msg void OnPaste();
	afx_msg void OnUpdatePaste(CCmdUI* pCmdUI);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeText();
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateText();
	afx_msg void OnBold();
	afx_msg void OnUpdateBold(CCmdUI* pCmdUI);
	afx_msg void OnHead();
	afx_msg void OnUpdateHead(CCmdUI* pCmdUI);
	afx_msg void OnItal();
	afx_msg void OnUpdateItal(CCmdUI* pCmdUI);
	afx_msg void OnUnbold();
	afx_msg void OnUpdateUnbold(CCmdUI* pCmdUI);
	afx_msg void OnUnheading();
	afx_msg void OnUpdateUnheading(CCmdUI* pCmdUI);
	afx_msg void OnUnitalic();
	afx_msg void OnUpdateUnitalic(CCmdUI* pCmdUI);
	afx_msg void OnSpell();
	afx_msg void OnUpdateSpell(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGTEXTEDIT_H__665ADF44_E0FE_4366_B63A_DED253FAFE76__INCLUDED_)
