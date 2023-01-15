// FolderName.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "FolderName.h"
#include ".\foldername.h"
#include "paths.hpp"
#include "folders.h"

// CFolderName dialog

IMPLEMENT_DYNAMIC(CFolderName, CDialog)
CFolderName::CFolderName(CWnd* pParent /*=NULL*/)
	: CDialog(CFolderName::IDD, pParent)
	, m_folder(_T(""))
{
 m_newmode = 1;
}

CFolderName::~CFolderName()
{
}

void CFolderName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_folder);
}


BEGIN_MESSAGE_MAP(CFolderName, CDialog)
END_MESSAGE_MAP()


// CFolderName message handlers

void CFolderName::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	if ( m_newmode )
		theFolders.AddFolder(m_folder);
	else
		theFolders.RenameFolder(m_folder);
	theFolders.SaveToIni();
	CDialog::OnOK();
}

BOOL CFolderName::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
