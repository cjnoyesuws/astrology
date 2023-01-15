// OrbEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrbEdit dialog

class COrbEdit : public CDialog
{
// Construction
public:
	int context;
	COrbEdit(CWnd* pParent = NULL);   // standard constructor
    void SaveData();
	void GetData();
	void GetItem( CString &s, BOOL b, int index );
	void SetItem( CString &s, BOOL &b, int index );


// Dialog Data
	//{{AFX_DATA(COrbEdit)
	enum { IDD = IDD_ORB_EDIT };
	CString	m_dbiqui;
	CString	m_dconjunct;
	CString	m_ddecile;
	CString	m_dhscusp;
	CString	m_dnonplan;
	CString	m_doppose;
	CString	m_dquin;
	CString	m_dquintile;
	CString	m_dsesquiquq;
	CString	m_dssext;
	CString	m_dssquare;
	CString	m_dtredec;
	CString	m_dtrine;
	BOOL	m_ibiquint;
	BOOL	m_iconjunct;
	BOOL	m_idecile;
	BOOL	m_ihscusp;
	BOOL	m_ioppose;
	BOOL	m_iquincunx;
	BOOL	m_iquint;
	BOOL	m_isext;
	BOOL	m_isquare;
	BOOL	m_issesquiq;
	BOOL	m_issext;
	BOOL	m_issquare;
	BOOL	m_itredec;
	BOOL	m_itrine;
	CString	m_dsextile;
	CString	m_dsquare;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrbEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrbEdit)
	afx_msg void OnSelchangeAocontext();
	virtual void OnOK();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
