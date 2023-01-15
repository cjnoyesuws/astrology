// ParaEdit.h : header file
//
#include "rtffuncs.h"
#include "tabctrlctrl1.h"
#include "wspell.h"
class EditTextBlock {
CString buf;
int nsr;
int stickRet[25];
int nTabs;
unsigned char tabs[25];
char tabbuf[100];
public:
     EditTextBlock() { nsr=0; nTabs = 0; tabbuf[0] = '\0';}
     ~EditTextBlock() {}
     void preProcess();
     void postProcess();
     CString &get() { return buf; }
     void set( CString &t );
    };


/////////////////////////////////////////////////////////////////////////////
// CParaEdit dialog

class CParaEdit : public CDialog
{
// Construction
public:
	CParaEdit(CWnd* pParent = NULL);   // standard constructor
	EditTextBlock etb;
	void SetData(CString &tx);
	void GetData(CString &tx);
    RTFFuncs *pFuncs;

// Dialog Data
	//{{AFX_DATA(CParaEdit)
	enum { IDD = IDD_PARA };
	CString	m_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParaEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParaEdit)
	virtual void OnOK();
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
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    CTabctrlctrl1 m_tabctrl;
	CWSpell	m_ctrl;
};


