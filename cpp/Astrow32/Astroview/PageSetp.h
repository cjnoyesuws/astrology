// PageSetp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSetp dialog

class CPageSetp : public CDialog
{
// Construction
public:
	CPageSetp(CWnd* pParent = NULL);   // standard constructor
	void SetData( PageData &d );
	void GetData( PageData &d );


// Dialog Data
	//{{AFX_DATA(CPageSetp)
	enum { IDD = IDD_PAGESETP };
	int 	m_bottom;
	int 	m_left;
	int 	m_right;
	int 	m_top;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageSetp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageSetp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
