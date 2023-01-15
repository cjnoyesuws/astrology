// ConvertData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvertData dialog

class CConvertData : public CDialog
{
// Construction
public:
	CConvertData(CWnd* pParent = NULL);   // standard constructor
	void SetData( ConvData &c, ReportStyles &r );
	void GetData( ConvData &c );
	
// Dialog Data
	//{{AFX_DATA(CConvertData)
	enum { IDD = IDD_CONVOPT };
	BOOL	m_cb4;
	BOOL	m_cmt;
	BOOL	m_cpg;
	int		m_format;
	int  	m_left;
	int 	m_width;
	BOOL    m_bGlyph;
	int     m_glyphFont;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvertData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvertData)
	afx_msg void OnSelchangeCoformat();
	afx_msg void OnCopseudo();
	afx_msg void OnCostyles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    ReportStyles *styles;
    ConvData *opts;
};
