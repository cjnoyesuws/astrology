#pragma once


// CTranslateWiz dialog

class CTranslateWiz : public CDialog
{
	DECLARE_DYNAMIC(CTranslateWiz)

public:
	CTranslateWiz(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTranslateWiz();

// Dialog Data
	enum { IDD = IDD_TRANSLATEWIZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
