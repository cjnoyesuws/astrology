//{{AFX_INCLUDES()
#include "wspell.h"
//}}AFX_INCLUDES
#if !defined(AFX_REPORTEDIT_H__E48C440B_C5D6_45C4_BCBD_A85DD5832DBA__INCLUDED_)
#define AFX_REPORTEDIT_H__E48C440B_C5D6_45C4_BCBD_A85DD5832DBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportEdit.h : header file
//
#include "dreporttext1.h"
#include "rtffuncs.h"
#include "tabctrlctrl1.h"
#include "wspell.h"
/////////////////////////////////////////////////////////////////////////////
// CReportEdit dialog

class CReportEdit : public CDialog
{
// Construction
public:
	CReportEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportEdit)
	enum { IDD = IDD_REPORTTEXT };
	int		m_Index;
	CString	m_Text;
	int		m_TextId;
	CWSpell	m_ctrl;
	//}}AFX_DATA
   CDReportText theSet;
   CString  m_TextIdStr;
   CString  m_TextType;
   BOOL     m_bModified; 
   RTFFuncs *pFuncs;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportEdit)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	BOOL Find();
	BOOL Save();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportEdit)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeTextid();
	afx_msg void OnChangeIndex();
	afx_msg void OnPaste();
	afx_msg void OnUpdatePaste(CCmdUI* pCmdUI);
	afx_msg void OnCut();
	afx_msg void OnUpdateCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopy(CCmdUI* pCmdUI);
	afx_msg void OnCopy();
	afx_msg void OnClear();
	afx_msg void OnUpdateClear(CCmdUI* pCmdUI);
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
	CTabctrlctrl1 m_tabctrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTEDIT_H__E48C440B_C5D6_45C4_BCBD_A85DD5832DBA__INCLUDED_)
