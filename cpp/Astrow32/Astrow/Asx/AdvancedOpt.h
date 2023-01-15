#pragma once


// CAdvancedOpt dialog

class CAdvancedOpt : public CDialog
{
	DECLARE_DYNAMIC(CAdvancedOpt)

public:
	CAdvancedOpt(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdvancedOpt();

// Dialog Data
	enum { IDD = IDD_ADVANCEDOPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CString m_astrologer;
	CString m_header;
	CString m_label1;
	CString m_label2;
	CString m_label3;
	CString m_label4;
	CString m_trailer;

};
