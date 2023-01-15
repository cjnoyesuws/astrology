// RectifyData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRectifyData dialog

class CRectifyData : public CDialog
{
// Construction
public:
	CRectifyData(CWnd* pParent = NULL);   // standard constructor
	void SetData(RECT_DATA &d, TIM &bth, int btham);
	void GetData(RECT_DATA &d);

// Dialog Data
	//{{AFX_DATA(CRectifyData)
	enum { IDD = IDD_RECT_DATA };
	int		m_ampm;
	BOOL	m_check;
	short	m_deg;
	short	m_min;
	int		m_angle;
	int		m_sign;
	int		m_method;
	short	m_tmin;
	short	m_thrs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectifyData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRectifyData)
	afx_msg void OnSelchangeMethod();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
