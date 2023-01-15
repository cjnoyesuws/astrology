// importtoolDlg.h : header file
//

#if !defined(AFX_IMPORTTOOLDLG_H__76E301B7_31CA_4336_95DC_E9B73B6104FE__INCLUDED_)
#define AFX_IMPORTTOOLDLG_H__76E301B7_31CA_4336_95DC_E9B73B6104FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImporttoolDlg dialog


class CImporttoolDlg : public CDialog
{
// Construction
public:
	CImporttoolDlg(CWnd* pParent = NULL);	// standard constructor
    ImporterData m_data;
	CProgressCtrl m_tasks;
	CProgressCtrl m_records;

// Dialog Data
	//{{AFX_DATA(CImporttoolDlg)
	enum { IDD = IDD_IMPORTTOOL_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImporttoolDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImporttoolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_olddir;
	afx_msg void OnBnClickedSelect();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTTOOLDLG_H__76E301B7_31CA_4336_95DC_E9B73B6104FE__INCLUDED_)
