// SelectFolder.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "SelectFolder.h"
#include ".\selectfolder.h"
#include "folders.h"
#include "afxcoll.h"
#include "astro.h"
#include "useri.h" 
#include "paths.hpp"
#include "filelst.hpp"
// CSelectFolder dialog

IMPLEMENT_DYNAMIC(CSelectFolder, CDialog)
CSelectFolder::CSelectFolder(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectFolder::IDD, pParent)
	, m_folder(0)
{
}

CSelectFolder::~CSelectFolder()
{
}

void CSelectFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_FOLDER, m_folder);
}


BEGIN_MESSAGE_MAP(CSelectFolder, CDialog)
END_MESSAGE_MAP()


// CSelectFolder message handlers

BOOL CSelectFolder::OnInitDialog()
{
	CDialog::OnInitDialog();
    CComboBox* p = (CComboBox *)GetDlgItem(IDC_FOLDER);
	theFolders.toCombo(p);
	// TODO:  Add extra initialization here
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectFolder::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	m_folder += DEFAULT_FLD;
	theFolders.ChangeFolder(m_folder);
	AstFileList.GetCurFolder() = m_folder;
	FlistDoUpdate(ALL_F);
	FlistDoUpdate(GRA_F);
	FlistDoUpdate(NON_GRA);
	FlistDoUpdate(GRIDFX);

	CDialog::OnOK();
}
