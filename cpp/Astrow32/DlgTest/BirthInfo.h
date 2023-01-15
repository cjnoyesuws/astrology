// BirthInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBirthInfo dialog

class CBirthInfo : public CDialog
{
// Construction
public:
	CBirthInfo(CWnd* pParent=NULL );   // standard constructor
   DaoLocDatabase *pLocDb;
	DaoBirthDatabase *pBirthDb;
	CMenu *pMenu;
	RECT_DATA rect;
	void SetData( LOC_DB &l );
	void GetData( LOC_DB &l );
	void SetData( BIRTH_DB &l, RECT_DATA &r );
	void GetData( BIRTH_DB &l, RECT_DATA &r );
	void preAdjustTime();
	void adjustTime();
	void updateCombos();
	int bWithRect;
	int bBirthModified;
	int bLocModified;

// Dialog Data
	//{{AFX_DATA(CBirthInfo)
	enum { IDD = IDD_BIRTH_INF };
	CString	m_country;
	int		m_eastwest;
	int	m_gmthr;
	int	m_gmtmin;
	int	m_ladeg;
	int	m_lamin;
	CString	m_location;
	int	m_lodeg;
	int		m_ampm;
	int	m_day;
	int	m_hr;
	int	m_min;
	int	m_mo;
	CString	m_name;
	int		m_sex;
	int	m_year;
	int	m_lomin;
	int		m_northsouth;
	int		m_speccode;
	CString	m_state;
	int		m_timezone;
	//}}AFX_DATA
    int     m_cdp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBirthInfo)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBirthInfo)
	afx_msg void OnBimenu();
	afx_msg void OnSelchangeBiname();
	afx_msg void OnBirect();
	afx_msg void OnEditchangeRlcountry();
	afx_msg void OnKillfocusRlcountry();
	afx_msg void OnEditchangeRllocation();
	afx_msg void OnSelchangeRllocation();
	afx_msg void OnEditchangeRlstate();
	afx_msg void OnSelchangeRlstate();
	afx_msg void OnSelchangeRltimezone();
	afx_msg void OnRlmenu();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeBiname();
	virtual void OnOK();
	afx_msg void OnKillfocusRlstate();
	afx_msg void OnSelchangeRlcountry();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void showGmtCtl(int bShow);
	void doClipboard();
};
