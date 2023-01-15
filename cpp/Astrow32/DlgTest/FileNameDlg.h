// FileNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileNameDlg dialog

class CFileNameDlg : public CDialog
{
// Construction
public:
	CFileNameDlg(CWnd* pParent = NULL);   // standard constructor
	void SetData(XPFILE_DB &db );
	void GetData(XPFILE_DB &db );
    BOOL m_bFind;
// Dialog Data
	//{{AFX_DATA(CFileNameDlg)
	enum { IDD = IDD_FILE_NAME };
	CString	m_comment;
	CString	m_filename;
	CString	m_name;
	CString	m_type;
	int m_folder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileNameDlg)
	afx_msg void OnFnselfile();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
public:
	BOOL m_auto;
};
