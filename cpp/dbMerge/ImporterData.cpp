// ImporterData.cpp: implementation of the ImporterData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ado.h"
#include "dbmerge.h"
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
: m_dest(_T("")), m_source(_T("")), m_table(_T("")), m_pkeys(_T(""))
{
    memset(buffer,0,500);
}

ImporterData::~ImporterData()
{

}

