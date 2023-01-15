//{{AFX_INCLUDES()
#include "wspell.h"
//}}AFX_INCLUDES
#if !defined(AFX_ASPTEXTEDIT_H__2B1A0EF2_46C4_4760_8E9F_770353EC95AC__INCLUDED_)
#define AFX_ASPTEXTEDIT_H__2B1A0EF2_46C4_4760_8E9F_770353EC95AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AspTextEdit.h : header file
//
#include "daspecttext1.h"
#include "rtffuncs.h"
/////////////////////////////////////////////////////////////////////////////
// CAspTextEdit dialog

class CAspTextEdit : public CDialog
{
// Construction
public:
	CAspTextEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAspTextEdit)
	enum { IDD = IDD_ASPTEXT };
	CString	m_Text;
	int		m_Aspect;
	int		m_Plan1;
	int		m_Plan2;
	CWSpell	m_ctrl;
	//}}AFX_DATA
   CString  m_AspectStr;
   CString  m_Plan1Str;
   CString  m_Plan2Str;
   CString  m_TextType;
   BOOL     m_bModified; 
   CDAspectText theSet;
   RTFFuncs *pFuncs;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAspTextEdit)
	public:
//	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	BOOL Find();
	BOOL Save();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAspTextEdit)
	afx_msg void OnSelchangeAspect();
	afx_msg void OnSelchangePlan1();
	afx_msg void OnSelchangePlan2();
	afx_msg void OnClear();
	afx_msg void OnUpdateClear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopy(CCmdUI* pCmdUI);
	afx_msg void OnCopy();
	afx_msg void OnCut();
	afx_msg void OnUpdateCut(CCmdUI* pCmdUI);
	afx_msg void OnPaste();
	afx_msg void OnUpdatePaste(CCmdUI* pCmdUI);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASPTEXTEDIT_H__2B1A0EF2_46C4_4760_8E9F_770353EC95AC__INCLUDED_)
