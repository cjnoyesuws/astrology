// PseudoStyle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPseudoStyle dialog

class CPseudoStyle : public CDialog
{
// Construction
public:
	CPseudoStyle(CWnd* pParent = NULL);   // standard constructor
	void SetData(FIL_ATTRIB &f);
	void GetData(FIL_ATTRIB &f);
	

// Dialog Data
	//{{AFX_DATA(CPseudoStyle)
	enum { IDD = IDD_PSEUDO };
	CString	m_ebold;
	CString	m_ehead;
	CString	m_escore;
	CString	m_sbold;
	CString	m_shead;
	CString	m_sscore;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPseudoStyle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPseudoStyle)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
