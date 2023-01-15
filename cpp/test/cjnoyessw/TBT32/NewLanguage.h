#pragma once


// CNewLanguage dialog

class CNewLanguage : public CDialog
{
	DECLARE_DYNAMIC(CNewLanguage)

public:
	CNewLanguage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewLanguage();

// Dialog Data
	enum { IDD = IDD_NEWLANG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Description;
	CString m_langcode;
protected:
	virtual void OnOK();
};
