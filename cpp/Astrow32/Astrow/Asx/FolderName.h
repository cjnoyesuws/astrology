#pragma once


// CFolderName dialog

class CFolderName : public CDialog
{
	DECLARE_DYNAMIC(CFolderName)

public:
	CFolderName(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFolderName();

// Dialog Data
	enum { IDD = IDD_FOLDERNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	CString m_folder;
	int m_newmode;
};
