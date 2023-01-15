// TranslateWiz.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "TranslateWiz.h"
#include ".\translatewiz.h"


// CTranslateWiz dialog

IMPLEMENT_DYNAMIC(CTranslateWiz, CDialog)
CTranslateWiz::CTranslateWiz(CWnd* pParent /*=NULL*/)
	: CDialog(CTranslateWiz::IDD, pParent)
{
}

CTranslateWiz::~CTranslateWiz()
{
}

void CTranslateWiz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTranslateWiz, CDialog)
END_MESSAGE_MAP()


// CTranslateWiz message handlers

BOOL CTranslateWiz::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
