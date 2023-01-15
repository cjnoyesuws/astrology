// AdvancedOpt.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "AdvancedOpt.h"
#include "inifile.hpp"


// CAdvancedOpt dialog

IMPLEMENT_DYNAMIC(CAdvancedOpt, CDialog)
CAdvancedOpt::CAdvancedOpt(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedOpt::IDD, pParent)
	, m_astrologer(_T(""))
	, m_header(_T(""))
	, m_label1(_T(""))
	, m_label2(_T(""))
	, m_label3(_T(""))
	, m_label4(_T(""))
	, m_trailer(_T(""))
{
}

CAdvancedOpt::~CAdvancedOpt()
{
}

void CAdvancedOpt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ASTROLOGER, m_astrologer);
	DDX_Text(pDX, IDC_HEADER, m_header);
	DDX_Text(pDX, IDC_LABELTXT1, m_label1);
	DDX_Text(pDX, IDC_LABELTXT2, m_label2);
	DDX_Text(pDX, IDC_LABELTXT3, m_label3);
	DDX_Text(pDX, IDC_LABELTXT4, m_label4);
	DDX_Text(pDX, IDC_TRAILER, m_trailer);
}


BEGIN_MESSAGE_MAP(CAdvancedOpt, CDialog)
END_MESSAGE_MAP()


// CAdvancedOpt message handlers

BOOL CAdvancedOpt::OnInitDialog()
{
	CDialog::OnInitDialog();
    CWinApp * app = AfxGetApp();
	m_trailer = app->GetProfileString( "wwwconvert", "trailer", "" );
	m_header = app->GetProfileString( "wwwconvert", "header", "" );
	m_astrologer = app->GetProfileString( Cover_SEC, "Astrologer", "" );
	int label_lines = (int) app->GetProfileInt( GraphPrintOpt_SEC, "LabelLines", 0 );
	m_label1 = app->GetProfileString( GraphPrintOpt_SEC, "Label1", "" );
	m_label2 = app->GetProfileString( GraphPrintOpt_SEC, "Label2", "" );
	m_label3 = app->GetProfileString( GraphPrintOpt_SEC, "Label3", "" );
	m_label4 = app->GetProfileString( GraphPrintOpt_SEC, "Label4", "" );
	UpdateData(FALSE);	
	
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAdvancedOpt::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	CWinApp *app = AfxGetApp();
	app->WriteProfileString( "wwwconvert", "trailer", m_trailer );
	app->WriteProfileString( "wwwconvert", "header", m_header );
	app->GetProfileString( Cover_SEC, "Astrologer", m_astrologer );
	int label_lines = 0; 
	app->GetProfileString( GraphPrintOpt_SEC, "Label1", m_label1);
	if ( m_label1.GetLength()> 0 )
		label_lines++;
	app->GetProfileString( GraphPrintOpt_SEC, "Label2", m_label2 );
	if ( m_label2.GetLength()> 0 )
		label_lines++;
	app->GetProfileString( GraphPrintOpt_SEC, "Label3", m_label3 );
	if ( m_label3.GetLength()> 0 )
		label_lines++;
	app->GetProfileString( GraphPrintOpt_SEC, "Label4", m_label4 );
    if ( m_label4.GetLength()> 0 )
		label_lines++;
	app->WriteProfileInt( GraphPrintOpt_SEC, "LabelLines", label_lines );
	CDialog::OnOK();
}

