#pragma once

// CSetLanguage dialog


class CSetLanguage : public CDialog
{
	DECLARE_DYNAMIC(CSetLanguage)

public:
	CSetLanguage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetLanguage();

// Dialog Data
	enum { IDD = IDD_SET_LANGUAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_language;
	CString m_langcode;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnCbnSelchangeLanguage();
    
};

