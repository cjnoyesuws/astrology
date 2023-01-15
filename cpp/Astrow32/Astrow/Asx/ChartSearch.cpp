// ChartSearch.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "ChartSearch.h"



// CChartSearch dialog

IMPLEMENT_DYNAMIC(CChartSearch, CDialog)
CChartSearch::CChartSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CChartSearch::IDD, pParent)
	, m_name(_T(""))
	, m_comments(_T(""))
{
}

CChartSearch::~CChartSearch()
{
}

void CChartSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_COMMENTS, m_comments);
	DDV_MaxChars(pDX, m_comments, 50);
	DDV_MaxChars(pDX, m_name, 50);
}


BEGIN_MESSAGE_MAP(CChartSearch, CDialog)
END_MESSAGE_MAP()


// CChartSearch message handlers

void CChartSearch::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	CDialog::OnOK();
}
