// TransInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransInfo dialog

class CTransInfo : public CDialog
{
// Construction
public:
	CTransInfo(CWnd* pParent = NULL);   // standard constructor
   DaoLocDatabase *pLocDb;
	DaoTransitDatabase *pTransitDb;
	CMenu *pMenu;
	void SetData( LOC_DB &l );
	void GetData( LOC_DB &l );
	void SetData( BIRTH_DB &l);
	void GetData( BIRTH_DB &l);
	void preAdjustTime();
	void adjustTime();
	void updateCombos();
	int bTransModified;
	int bLocModified;
	void showGmtCtl(int bShow);
	void doClipboard();

// Dialog Data
	//{{AFX_DATA(CTransInfo)
	enum { IDD = IDD_TRANS_INFO };
	int		m_ampm;
	int	m_day;
	int	m_hr;
	int	m_min;
	int	m_mo;
	CString	m_name;
	int	m_year;
	CString	m_country;
	int		m_eastwest;
	int	m_gmthr;
	int	m_gmtmin;
	int	m_ladeg;
	int	m_lamin;
	CString	m_location;
	int	m_lodeg;
	int	m_lomin;
	int		m_northsouth;
	int		m_speccode;
	CString	m_state;
	int		m_timezone;
	//}}AFX_DATA
    int m_cdp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransInfo)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransInfo)
	afx_msg void OnEditchangeBiname();
	afx_msg void OnSelchangeBiname();
	afx_msg void OnEditchangeRlcountry();
	afx_msg void OnKillfocusRlcountry();
	afx_msg void OnSelchangeRlcountry();
	afx_msg void OnEditchangeRllocation();
	afx_msg void OnSelchangeRllocation();
	afx_msg void OnRlmenu();
	afx_msg void OnEditchangeRlstate();
	afx_msg void OnKillfocusRlstate();
	afx_msg void OnSelchangeRlstate();
	afx_msg void OnSelchangeRltimezone();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
