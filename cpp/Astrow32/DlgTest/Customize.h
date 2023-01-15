// Customize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomize dialog

class CCustomize : public CDialog
{
// Construction
public:
	CCustomize(CWnd* pParent = NULL);   // standard constructor
char *cap;
OPTIONS op;
void SetCaption( char *c ) { cap = c; }
void SetData(OPTIONS &o);
void GetData(OPTIONS &o);

// Dialog Data
	//{{AFX_DATA(CCustomize)
	enum { IDD = IDD_CUSTOM };
	BOOL	m_reloc;
	BOOL	m_text;
	BOOL	m_progress;
	BOOL	m_progr_cusps;
	BOOL	m_graph;
	BOOL	m_datafile;
	BOOL    m_interpret;
	BOOL    m_gridfile;
	int		m_datafiletype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomize)
	afx_msg void OnCscustom();
	virtual BOOL OnInitDialog();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
