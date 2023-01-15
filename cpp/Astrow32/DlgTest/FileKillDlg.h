// FileKillDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileKillDlg dialog

class CFileKillDlg : public CDialog
{
// Construction
public:
	CFileKillDlg(CWnd* pParent = NULL);   // standard constructor
	void SetData(XPFILE_DB &db);
	void GetData(int &c);


// Dialog Data
	//{{AFX_DATA(CFileKillDlg)
	enum { IDD = IDD_FILE_KILL };
	CString	m_comment;
	BOOL	m_continue;
	CString	m_filename;
	CString	m_name;
	CString	m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileKillDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileKillDlg)
	afx_msg void OnNo();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
