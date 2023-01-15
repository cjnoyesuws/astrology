// TransDataPropPage.h : header file
//
#pragma once
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CTransDataPropPage dialog

class CTransDataPropPage : public CPropertyPage
{
 DECLARE_DYNAMIC(CTransDataPropPage)
// Construction
public:
	CTransDataPropPage();   // standard constructor
	virtual ~CTransDataPropPage() {}
	void SetData(TRANS_DATA &t);
	void GetData(TRANS_DATA &t);



// Dialog Data
	//{{AFX_DATA(CTransDataPropPage)
	enum { IDD = IDD_TRANS_DATA_PROP_PAGE };
	short	m_day;
	int		m_end;
	short	m_mo;
	short	m_num;
	int		m_start;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransDataPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransDataPropPage)
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
