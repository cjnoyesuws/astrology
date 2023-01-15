#pragma once


// CSelectFolder dialog

class CSelectFolder : public CDialog
{
	DECLARE_DYNAMIC(CSelectFolder)

public:
	CSelectFolder(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectFolder();

// Dialog Data
	enum { IDD = IDD_SELFOLDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_folder;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
