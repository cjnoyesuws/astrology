#pragma once


// CTransBase dialog

class CTransBase : public CDialog
{
	DECLARE_DYNAMIC(CTransBase)

public:
	CTransBase(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransBase();

// Dialog Data
	enum { IDD = IDD_TRANSBASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelect();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CString m_basedir;
};
