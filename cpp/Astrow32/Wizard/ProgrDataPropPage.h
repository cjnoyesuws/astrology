// ProgrDataPropPage.h : header file
//
#pragma once
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CProgrDataPropPage dialog

class CProgrDataPropPage : public CPropertyPage
{
 DECLARE_DYNAMIC(CProgrDataPropPage)
// Construction
public:
	CProgrDataPropPage();   // standard constructor
	virtual ~CProgrDataPropPage() {}
	void SetData( PROGR_DATA &p);
	void GetData( PROGR_DATA &p);

// Dialog Data
	//{{AFX_DATA(CProgrDataPropPage)
	enum { IDD = IDD_PROGRESS_DATA_PROP_PAGE };
	int		m_system;
	BOOL	m_target;
	short	m_day;
	short	m_month;
	short	m_year;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgrDataPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgrDataPropPage)
	//}}AFX_MSG
public:
    virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	DECLARE_MESSAGE_MAP()
};
