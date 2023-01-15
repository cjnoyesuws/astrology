// QdtOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQdtOptions dialog

class CQdtOptions : public CDialog
{
// Construction
public:
	CQdtOptions(CWnd* pParent = NULL);   // standard constructor
	void GetData(QdtData &d);
	void SetData(QdtData &d);



// Dialog Data
	//{{AFX_DATA(CQdtOptions)
	enum { IDD = IDD_QDT_OPTIONS };
	int		m_fampm;
	short	m_fhr;
	short	m_fmin;
	int		m_lampm;
	short	m_lhr;
	short	m_lmin;
	BOOL	m_once;
	BOOL	m_restrict;
	//}}AFX_DATA
   CString m_name;
   CString m_event;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQdtOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQdtOptions)
	afx_msg void OnQdrestricttim();
	afx_msg void OnHelp();
   afx_msg void OnSelchangeName();
   afx_msg void OnSelchangeEvent();
   virtual BOOL OnInitDialog();   
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
