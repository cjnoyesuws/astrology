// GraColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraColor dialog

class CGraColor : public CDialog
{
// Construction
public:
	void SetGraphicColors(GraphicColors *p);
	CGraColor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraColor)
	enum { IDD = IDD_GRACOLORS };
	BOOL	m_RevBack;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraColor)
	afx_msg void OnGcascend();
	afx_msg void OnGcback();
	afx_msg void OnGcbhouse();
	afx_msg void OnGcbplan();
	afx_msg void OnGcbsign();
	afx_msg void OnGccirc();
	afx_msg void OnGchouse();
	afx_msg void OnGcsign();
	afx_msg void OnGcplan();
	virtual void OnOK();
	afx_msg void OnHelp();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	GraphicColors *pgc;
public:
	afx_msg void OnBnClickedRevback();
};
