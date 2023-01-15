#pragma once
#include "afxwin.h"


// CChartTypePropPage dialog

class CChartTypePropPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CChartTypePropPage)

public:
	CChartTypePropPage();
	virtual ~CChartTypePropPage();

// Dialog Data
	enum { IDD = IDD_CHART_TYPE_PROPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardBack();
	virtual void OnOK();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	afx_msg void OnCbnSelchangeChartType();
	afx_msg void OnCbnSelchangeFolder();
	CString MakeFileName();
	int MakeFileType();
	CComboBox m_chart_type;
	int m_chart_type_val;
	int m_file_type_val;
	CString m_comments;
	CString m_name;
	CComboBox m_folder;
	int m_folder_no;
};
