// ReportStyles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportStyles dialog

class CReportStyles : public CDialog
{

// Construction
public:
	CReportStyles(CWnd* pParent = NULL);   // standard constructor
	void SetData( ReportStyles *rs ) { styles = rs; }
	

// Dialog Data
	//{{AFX_DATA(CReportStyles)
	enum { IDD = IDD_REPSTYLES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportStyles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportStyles)
	afx_msg void OnRsbold();
	afx_msg void OnRshead();
	afx_msg void OnRsreg();
	afx_msg void OnRsscore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ReportStyles *styles;

};
