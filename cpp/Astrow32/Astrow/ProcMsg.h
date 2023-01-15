#pragma once
// ProcMsg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ProcMsg dialog

class ProcMsg : public CDialog
{
// Construction
public:
	ProcMsg(CWnd* pParent = NULL);
	ProcMsg(char *t, int *brk,  CWnd* pParent = NULL);   // standard constructor
	void setText( char *t );
	~ProcMsg();
// Dialog Data
	//{{AFX_DATA(ProcMsg)
	enum { IDD = IDD_MSG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProcMsg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
   int *notify;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ProcMsg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
