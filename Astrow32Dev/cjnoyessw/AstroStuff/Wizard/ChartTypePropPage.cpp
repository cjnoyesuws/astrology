// ChartTypePropPage.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard.h"
#include "ChartTypePropPage.h"
#include "ChartWizard.h"
#include "foldersset.h"
#include ".\charttypeproppage.h"
// CChartTypePropPage dialog

IMPLEMENT_DYNAMIC(CChartTypePropPage, CPropertyPage)
CChartTypePropPage::CChartTypePropPage()
	: CPropertyPage(CChartTypePropPage::IDD)
	, m_chart_type_val(0)
	, m_comments(_T(""))
	, m_name(_T(""))
	, m_folder_no(0)
{
	EnableActiveAccessibility();
}

CChartTypePropPage::~CChartTypePropPage()
{
}

void CChartTypePropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_TYPE, m_chart_type);
	DDX_Text(pDX, IDC_COMMENTS, m_comments);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Control(pDX, IDC_FOLDER, m_folder);
}


BEGIN_MESSAGE_MAP(CChartTypePropPage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_CHART_TYPE, OnCbnSelchangeChartType)
	ON_CBN_SELCHANGE(IDC_FOLDER, OnCbnSelchangeFolder)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChartTypePropPage message handlers

BOOL CChartTypePropPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	UpdateData(FALSE);
    CFoldersSet set;
	m_folder.ResetContent();
    int item =m_folder.AddString("Default Folder");
    m_folder.SetItemData(item, 10);
    set.Open();
    if ( !set.IsBOF() && !set.IsEOF() ) {
	  while ( !set.IsEOF() ) {
		  item =m_folder.AddString(set.m_folder_name);
		  m_folder.SetItemData(item, set.m_folder_num);
		  set.MoveNext();
	  }
  }

	m_folder.SetCurSel(0);
	m_chart_type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CChartTypePropPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	((CChartWizard *)GetParent())->DoAddPages();
	return CPropertyPage::OnWizardNext();
}

BOOL CChartTypePropPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	XPFILE_DB *ptr = ((CChartWizard *)GetParent())->fileinfo;
	strcpy(ptr->name,(LPCTSTR)m_name);
	strcpy(ptr->comment, (LPCTSTR)m_comments);
	ptr->folder = m_folder_no;
	strcpy(ptr->file_name,(LPCTSTR)MakeFileName());
	ptr->type = MakeFileType();
	return CPropertyPage::OnWizardFinish();
}

LRESULT CChartTypePropPage::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnWizardBack();
}

void CChartTypePropPage::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CPropertyPage::OnOK();
}

BOOL CChartTypePropPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(FALSE);
    ((CChartWizard *)GetParent())->HandleButtons();
	return CPropertyPage::OnSetActive();
}

BOOL CChartTypePropPage::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnKillActive();
}

void CChartTypePropPage::OnCbnSelchangeChartType()
{
	// TODO: Add your control notification handler code here
	m_chart_type_val = m_chart_type.GetCurSel();
	((CChartWizard *)GetParent())->GetChartType() = m_chart_type_val;
	((CChartWizard *)GetParent())->GetFileType() = MakeFileType();
}

void CChartTypePropPage::OnCbnSelchangeFolder()
{
	// TODO: Add your control notification handler code here
	int sel = m_folder.GetCurSel();
	m_folder_no = (int) m_folder.GetItemData(sel);
}

CString CChartTypePropPage::MakeFileName()
{
 char buf[200];
 sprintf(buf, "%s Chart.asrpt", (LPCTSTR)m_name);
 return ( CString(buf));
}
int CChartTypePropPage::MakeFileType()
{
 static int ftypes[15] = {NATAL_FILE,NATAL_FILE,NATAL_FILE,NATAL_FILE,NATAL_FILE,COMPATIBILITY_FILE,TRANSITS_FILE,
	 PROGRESSED_FILE,RELOCATION_FILE,SOLAR_RETURN_FILE,COMPOSITE_FILE,SOLARARC_FILE,
	 HARMONIC_FILE,COMPOTRAN_FILE,FIXED_FILE,ARABIC_FILE,HELIO_FILE,PROBLEM_FILE };
 return ftypes[m_chart_type_val];
}

