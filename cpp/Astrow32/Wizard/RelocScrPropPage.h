// RelocScrPropPage.h : header file
//
#pragma once
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CRelocScrPropPage dialog

class CRelocScrPropPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRelocScrPropPage)
// Construction
public:
	CRelocScrPropPage(); // standard constructor
	virtual ~CRelocScrPropPage() { DestroyWindow(); }
	DaoLocDatabase *pLocDb;
	DaoRelocateDatabase *pRelocDb;
	CMenu *pMenu;
	void SetData( LOC_DB &l );
	void GetData( LOC_DB &l );
	int bLocModified;
	int bRelocModified;
    void showGmtCtl(int bShow);
	void doClipboard();
// Dialog Data
	//{{AFX_DATA(CRelocScrPropPage)
	enum { IDD = IDD_RELOC_DAT_PROP_PAGE };
	CString m_personal;
	CString	m_country;
	int		m_eastwest;
	CString	m_location;
	int		m_speccode;
	CString	m_state;
	int		m_timezone;
	int		m_northsouth;
	int	m_lomin;
	int	m_lodeg;
	int	m_ladeg;
	int	m_lamin;
	int	m_gmthr;
	int	m_gmtmin;
	//}}AFX_DATA
    int m_cdp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelocScrPropPage)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL DestroyWindow();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
    virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRelocScr)
	afx_msg void OnSelchangeRltimezone();
	afx_msg void OnSelchangeRlspeccode();
	afx_msg void OnKillfocusRlstate();
	afx_msg void OnKillfocusRlcountry();
	afx_msg void OnKillfocusRllocation();
	afx_msg void OnRlmenu();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRllocation();
	afx_msg void OnEditchangeRlcountry();
	afx_msg void OnSelchangeRlcountry();
	afx_msg void OnEditchangeRllocation();
	afx_msg void OnSelchangeRlstate();
	afx_msg void OnEditchangeRlstate();
	afx_msg void OnSelchangeRlpersonal();
	afx_msg void OnEditchangeRlpersonal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
};
