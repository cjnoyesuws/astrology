// GraphFileOpts.h : header file	 +
//

/////////////////////////////////////////////////////////////////////////////
// CGraphFileOpts dialog

class CGraphFileOpts : public CDialog
{
// Construction
public:
	CGraphFileOpts(CWnd* pParent = NULL);   // standard constructor
	void GetData( GraphFileData &p );
	void SetData( GraphFileData &p );

// Dialog Data
	//{{AFX_DATA(CGraphFileOpts)
	enum { IDD = IDD_GRA_FIL_OP };
	int		m_format;
	float	m_height;
	int		m_units;
	int		m_resolution;
	BOOL	m_reversgra;
	float	m_width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphFileOpts)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphFileOpts)
	virtual void OnOK();
	afx_msg void OnSelchangeGfunits();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
