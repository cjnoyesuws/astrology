// ChartOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartOptions dialog

class CChartOptions : public CDialog
{
// Construction
public:
	CChartOptions(CWnd* pParent = NULL);   // standard constructor
char *cap;
void SetData(OPTIONS &o);
void GetData(OPTIONS &o);
void SetCaption( char *c ) { cap = c; }
int m_sidereal;
int	m_tropical;

// Dialog Data
	//{{AFX_DATA(CChartOptions)
	enum { IDD = IDD_OPTIONS };
	BOOL	m_aspects;
	BOOL	m_extaspects;
	BOOL	m_extmisc;
	int		m_houseproc;
	BOOL	m_houses;
	BOOL	m_fullmid;
	BOOL	m_halfmid;
	BOOL	m_misc;
	BOOL	m_aspmid;
	BOOL	m_summary;
	BOOL	m_text;
	BOOL	m_verteast;
	BOOL	m_basemid;
	BOOL    m_asteroids;
	BOOL    m_swap;
	BOOL    m_keep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartOptions)
	afx_msg void OnOpsidereal();
	afx_msg void OnOptropical();
	virtual BOOL OnInitDialog();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_def_rectmethod;
};


