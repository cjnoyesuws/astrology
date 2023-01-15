// Harmonic.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include ".\harmonicx.h"


// CHarmonic dialog

IMPLEMENT_DYNAMIC(CHarmonic, CDialog)
CHarmonic::CHarmonic(CWnd* pParent /*=NULL*/)
	: CDialog(CHarmonic::IDD, pParent)
	, m_harmonic(0)
{
}

CHarmonic::~CHarmonic()
{
}

void CHarmonic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HARM, m_harmonic);
	DDV_MinMaxInt(pDX, m_harmonic, 1, 30);
}


BEGIN_MESSAGE_MAP(CHarmonic, CDialog)
END_MESSAGE_MAP()


// CHarmonic message handlers

int CHarmonic::GetValue(void)
{
	return m_harmonic;
}

void CHarmonic::SetValue(int m_Value)
{
 m_harmonic = m_Value;
}
