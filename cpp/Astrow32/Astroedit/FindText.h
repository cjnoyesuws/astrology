// FindText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindText dialog

class CFindText : public CDialog
{
// Construction
public:
	void SetData(CString &t, BOOL &mcase, BOOL &wword);
	CFindText(CWnd* pParent = NULL);   // standard constructor
	void GetData(CString &buf, BOOL &mcase, BOOL &wword);

// Dialog Data
	//{{AFX_DATA(CFindText)
	enum { IDD = IDD_FINDTEXT };
	CString	m_text;
	BOOL	m_matchcase;
	BOOL	m_wholeword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindText)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
