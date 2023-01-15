// ArchiveData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArchiveData dialog

class CArchiveData : public CDialog
{
// Construction
public:
	CArchiveData(CWnd* pParent = NULL);   // standard constructor
	int Program;
	int &getProgram() { return Program; }
	BOOL &getDelete() { return m_del; }
	CString &getCmd() { return m_cmd; }
	CString &getName() { return m_name; }
		
// Dialog Data
	//{{AFX_DATA(CArchiveData)
	enum { IDD = IDD_ARCHIVE_DAT };
	CString	m_cmd;
	CString	m_name;
	BOOL	m_del;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchiveData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArchiveData)
	afx_msg void OnZip();
	afx_msg void OnLha();
	afx_msg void OnWzip();
	virtual BOOL OnInitDialog();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
