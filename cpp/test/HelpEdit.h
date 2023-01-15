//{{AFX_INCLUDES()
#include "wspell.h"
//}}AFX_INCLUDES
#if !defined(AFX_HELPEDIT_H__DFEF6522_A7CD_4216_A964_2F296401E3E3__INCLUDED_)
#define AFX_HELPEDIT_H__DFEF6522_A7CD_4216_A964_2F296401E3E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HelpEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHelpEdit dialog
#include "dhelptxt1.h"
#include "rtffuncs.h"
#include "tabctrlctrl1.h"
class CHelpEdit : public CDialog
{
// Construction
public:
	CHelpEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHelpEdit)
	enum { IDD = IDD_HELPTXT };
	CString	m_Text;
	CWSpell	m_ctrl;
	//}}AFX_DATA
   BOOL     m_bModified;
   CDHelpTxt theSet;
   CString  m_TextType;
   RTFFuncs *pFuncs;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpEdit)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
   void DoSave();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHelpEdit)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClear();
	afx_msg void OnUpdateClear(CCmdUI* pCmdUI);
	afx_msg void OnCopy();
	afx_msg void OnUpdateCopy(CCmdUI* pCmdUI);
	afx_msg void OnCut();
	afx_msg void OnUpdateCut(CCmdUI* pCmdUI);
	afx_msg void OnPaste();
	afx_msg void OnUpdatePaste(CCmdUI* pCmdUI);
	afx_msg void OnChangeEdit1();
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEdit1();
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
	CTabctrlctrl1 m_tabctrl;
	afx_msg void OnBnClickedPrior();
	afx_msg void OnBnClickedNext();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	DECLARE_EVENTSINK_MAP()
	void DoClickTabctrlctrl1(long xpos);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPEDIT_H__DFEF6522_A7CD_4216_A964_2F296401E3E3__INCLUDED_)
