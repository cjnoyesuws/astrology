// AstroHelper.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAstroHelper dialog

class CAstroHelper : public CDialog
{
// Construction
public:
	CAstroHelper(CWnd* pParent = NULL);   // standard constructor
	AstHelperArray HelpList;
	int *sel;
	~CAstroHelper() { delete sel;}
    CStringArray *makePrintList();
    CStringArray *makeTitleList();
    // Dialog Data
	//{{AFX_DATA(CAstroHelper)
	enum { IDD = IDD_AST_HELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAstroHelper)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAstroHelper)
	afx_msg void OnAhconvert();
	afx_msg void OnAhprint();
	afx_msg void OnAhview();
	afx_msg void OnDblclkAhlist();
	virtual BOOL OnInitDialog();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
