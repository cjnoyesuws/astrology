// ReturnData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReturnData dialog

class CReturnData : public CDialog
{
// Construction
public:
	CReturnData(CWnd* pParent = NULL);   // standard constructor
	void SetData(RETURN_DATA &rd );
	void GetData(RETURN_DATA &rd );


// Dialog Data
	//{{AFX_DATA(CReturnData)
	enum { IDD = IDD_RETURN_DATA };
	int		m_body;
	short	m_eday;
	short	m_emo;
	short	m_eyear;
	short	m_pday;
	short	m_pmo;
	BOOL	m_prog;
	int		m_progsys;
	short	m_pyear;
	short	m_sday;
	short	m_smo;
	short	m_syear;
	BOOL	m_target;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReturnData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReturnData)
	afx_msg void onProg();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
