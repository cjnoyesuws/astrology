// FileEditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileEditDlg dialog

class CFileEditDlg : public CDialog
{
// Construction
public:
	CFileEditDlg(CWnd* pParent = NULL);   // standard constructor
	void SetData( XPFILE_DB &f ); 
	void GetData( XPFILE_DB &f );

// Dialog Data
	//{{AFX_DATA(CFileEditDlg)
	enum { IDD = IDD_FILE_EDIT };
	CString	m_comment;
	CString	m_filename;
	CString	m_name;
	CString	m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileEditDlg)
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
