// ProgrData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgrData dialog

class CProgrData : public CDialog
{
// Construction
public:
	CProgrData(CWnd* pParent = NULL);   // standard constructor
	void SetData( PROGR_DATA &p);
	void GetData( PROGR_DATA &p);

// Dialog Data
	//{{AFX_DATA(CProgrData)
	enum { IDD = IDD_PROGRESS_DATA };
	int		m_system;
	BOOL	m_target;
	short	m_day;
	short	m_month;
	short	m_year;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgrData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgrData)
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
