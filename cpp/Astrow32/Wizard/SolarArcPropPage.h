

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SolarArcPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSolarArc dialog

class CSolarArcPropPage : public CPropertyPage
{
 DECLARE_DYNAMIC(CSolarArcPropPage)
// Construction
public:
	CSolarArcPropPage();   // standard constructor
	virtual ~CSolarArcPropPage() {}

// Dialog Data
	//{{AFX_DATA(CSolarArcPropPage)
	enum { IDD = IDD_SOLARARC_PROP_PAGE };
	int		m_Day;
	int		m_month;
	int		m_system;
	BOOL	m_target;
	int		m_year;
	//}}AFX_DATA
    void SetData(DIREC_DATA &d);
	void GetData(DIREC_DATA &d);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSolarArcPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSolarArcPropPage)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

