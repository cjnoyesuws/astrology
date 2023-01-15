// Directories.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirectories dialog

class CDirectories : public CDialog
{
// Construction
public:
	void GetData( Directories &p );
	void SetData(Directories &p);
	CDirectories(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirectories)
	enum { IDD = IDD_DIRECTORIES };
	CString	m_data;
	CString	m_database;
	CString	m_help;
	CString	m_main;
	CString	m_user;
   CString  m_dbName;
   CString m_txtdbname;
   BOOL     m_DatabaseText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectories)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirectories)
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
public:
	afx_msg void OnEnChangeTxtdbname();

protected:
	virtual void OnOK();
};
