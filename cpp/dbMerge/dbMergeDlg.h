// dbMergeDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CdbMergeDlg dialog
class CdbMergeDlg : public CDialog
{
// Construction
public:
	CdbMergeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DBMERGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    CADODatabase m_sourceDb;
	CADODatabase m_destDb;
	CStringArray m_tables;
	CStringArray m_sorts;
	int m_table_count;
	CStringArray m_pkeys;
	CStringArray m_descrip;
	ImporterData m_data;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_source;
	CString m_dest;
	CListBox m_list;
	afx_msg void OnBnClickedDestlocate();
	afx_msg void OnBnClickedSrclocate();
protected:
	virtual void OnOK();
public:
	CProgressCtrl m_progress;
	CProgressCtrl m_curr_item;
};
