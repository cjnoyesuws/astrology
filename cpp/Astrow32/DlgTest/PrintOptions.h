// PrintOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintOptions dialog

class CPrintOptions : public CDialog
{
// Construction
public:
	CPrintOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintOptions)
	enum { IDD = IDD_PRINT_OPT };
	BOOL	m_cmtbeforetext;
	BOOL	m_comment;
	BOOL	m_cover;
	BOOL	m_ctrhead;
	BOOL	m_headp1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintOptions)
	afx_msg void OnPostyles();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
