// CoverPage.h : header file
//
#include "wspell.h"
#include "rtffuncs.h"
#include "tabctrlctrl1.h"
/////////////////////////////////////////////////////////////////////////////
// CCoverPage dialog

class CCoverPage : public CDialog
{
// Construction
public:
	CCoverPage(CWnd* pParent = NULL);   // standard constructor
	void SetData(CoverPageData &d);
	void GetData(CoverPageData &d);

// Dialog Data
	//{{AFX_DATA(CCoverPage)
	enum { IDD = IDD_COVER_DAT };
	CString	m_Subject;
	CString	m_astrologer;
	CString	m_comment;
	int		m_font;
	CString	m_graphic;
	int		m_image;
	CString	m_title;
	CWSpell	m_ctrl;
	CTabctrlctrl1 m_tabctrl;
	//}}AFX_DATA

   RTFFuncs *pFuncs;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoverPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCoverPage)
	afx_msg void OnHelp();
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
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnSpell();
	afx_msg void OnUpdateSpell(CCmdUI* pCmdUI);
	afx_msg void OnBnClickedSelectFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

};
