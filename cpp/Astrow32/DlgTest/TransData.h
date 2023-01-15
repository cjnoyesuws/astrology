// TransData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransData dialog

class CTransData : public CDialog
{
// Construction
public:
	CTransData(CWnd* pParent = NULL);   // standard constructor
	void SetData(TRANS_DATA &t);
	void GetData(TRANS_DATA &t);



// Dialog Data
	//{{AFX_DATA(CTransData)
	enum { IDD = IDD_TRANS_DATA };
	short	m_day;
	int		m_end;
	short	m_mo;
	short	m_num;
	int		m_start;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransData)
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
