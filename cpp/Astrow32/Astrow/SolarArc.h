#if !defined(AFX_SOLARARC_H__23AA441F_6D3F_4D28_97DF_46A49C15177F__INCLUDED_)
#define AFX_SOLARARC_H__23AA441F_6D3F_4D28_97DF_46A49C15177F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SolarArc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSolarArc dialog

class CSolarArc : public CDialog
{
// Construction
public:
	CSolarArc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSolarArc)
	enum { IDD = IDD_SOLARARC };
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
	//{{AFX_VIRTUAL(CSolarArc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSolarArc)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLARARC_H__23AA441F_6D3F_4D28_97DF_46A49C15177F__INCLUDED_)
