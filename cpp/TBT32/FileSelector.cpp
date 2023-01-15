// FileSelector.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "FileSelector.h"
#include "fileary.hpp"
#include "DirectorySelect.h"
#include "texttypeary.hpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSelector dialog


CFileSelector::CFileSelector(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSelector::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSelector)
	m_File = _T("");
	m_import_dir = _T("");
	m_bExport = FALSE;
	//}}AFX_DATA_INIT
}


void CFileSelector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSelector)
	DDX_LBString(pDX, IDC_FILES, m_File);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSelector, CDialog)
	//{{AFX_MSG_MAP(CFileSelector)
	ON_LBN_SELCHANGE(IDC_FILES, OnSelchangeFiles)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_IMPORT_DIR, OnBnClickedImportDir)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSelector message handlers

void CFileSelector::OnSelchangeFiles() 
{
	// TODO: Add your control notification handler code here
   CListBox *pbox = (CListBox *)GetDlgItem(IDC_FILES);
   int sel=pbox->GetCurSel();
   pbox->GetText(sel,m_File);
}

void CFileSelector::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CFileSelector::OnOK() 
{
	// TODO: Add extra validation here
	TCHAR buf[100];
	CListBox *pbox = (CListBox *)GetDlgItem(IDC_FILES);
	int cnt = pbox->GetSelCount();
	m_FileAry.SetSize(cnt);
	int *ar = new int[cnt];
	pbox->GetSelItems(cnt,ar);
    for ( int i = 0; i < cnt; i++ ) {
	    pbox->GetText(ar[i],buf);
		m_FileAry.SetAt(i,buf);	
	}
    delete ar;
	CDialog::OnOK();
}

BOOL CFileSelector::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CListBox *pbox = (CListBox *)GetDlgItem(IDC_FILES);
    if ( m_bExport ) 
		pATextTypes->toListBox(pbox,m_type);
	else
	    pFileList->toListBox(pbox,m_type);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CFileSelector::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

void CFileSelector::OnBnClickedImportDir()
{
	/*CFileDialog fdlg(TRUE, NULL, NULL, OFN_EXPLORER, NULL, this);
	if ( fdlg.DoModal() == IDOK ) {
		m_import_dir = fdlg.GetPathName();
		int pos = m_import_dir.ReverseFind(_T('\\'));
		m_import_dir = m_import_dir.Left(pos);
	}*/
	CDirectorySelect sel(TRUE);
	// TODO: Add your control notification handler code here
	if ( sel.DoModal() == IDOK ) 
	   m_import_dir = sel.GetDirectory();
}
