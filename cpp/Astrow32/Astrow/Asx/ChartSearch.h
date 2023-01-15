#pragma once


// CChartSearch dialog

class CChartSearch : public CDialog
{
	DECLARE_DYNAMIC(CChartSearch)

public:
	CChartSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChartSearch();

// Dialog Data
	enum { IDD = IDD_CHART_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_name;
	CString m_comments;
};
