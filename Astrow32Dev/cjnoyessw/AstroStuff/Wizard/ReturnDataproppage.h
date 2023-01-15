// ReturnDataPropPage.h : header file
//
#pragma once
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CReturnDataPropPage dialog

class CReturnDataPropPage : public CPropertyPage
{
 DECLARE_DYNAMIC(CReturnDataPropPage)
// Construction
public:
	CReturnDataPropPage();   // standard constructor
	virtual ~CReturnDataPropPage() {}
	void SetData(RETURN_DATA &rd );
	void GetData(RETURN_DATA &rd );


// Dialog Data
	//{{AFX_DATA(CReturnDataPropPage)
	enum { IDD = IDD_RETURN_DATA_PROP_PAGE };
	int		m_body;
	short	m_eday;
	short	m_emo;
	short	m_eyear;
	short	m_pday;
	short	m_pmo;
	BOOL	m_prog;
	int		m_progsys;
	short	m_pyear;
	short	m_sday;
	short	m_smo;
	short	m_syear;
	BOOL	m_target;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReturnDataPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReturnDataPropPage)
	afx_msg void onProg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual LRESULT OnWizardNext();
    virtual BOOL OnWizardFinish();
    virtual LRESULT OnWizardBack();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual void OnOK();
};
