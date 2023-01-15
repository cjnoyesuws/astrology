#pragma once

// CSetTransDir dialog

class CSetTransDir : public CDialog
{
	DECLARE_DYNAMIC(CSetTransDir)

public:
	CSetTransDir(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetTransDir();

// Dialog Data
	enum { IDD = IDD_SETTRANSDIR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_transdir;
	afx_msg void OnBnClickedSelect();
protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
