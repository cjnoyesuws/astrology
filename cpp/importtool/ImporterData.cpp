// ImporterData.cpp: implementation of the ImporterData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "importtool.h"
#include "progress.h"
#include "ImporterData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ImporterData::ImporterData()
: m_olddir(_T(""))
{
	m_dbdir = _T("");
	m_txtdir = _T("");
	m_userdir = _T("");
	m_olddir = _T("");
	m_text = TRUE;
	m_locs = TRUE;
	m_files = TRUE;
	m_births = TRUE;
    memset(buffer,0,500);
}

ImporterData::~ImporterData()
{

}

