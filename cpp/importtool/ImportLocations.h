// ImportLocations.h: interface for the CImportLocations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTLOCATIONS_H__07CA7B66_5627_4447_95BF_09C6D5DD8B36__INCLUDED_)
#define AFX_IMPORTLOCATIONS_H__07CA7B66_5627_4447_95BF_09C6D5DD8B36__INCLUDED_

#ifndef DEGR
#include "ASTRO.h"
#include "useri.h"
#include "Dbstruct.h"	// Added by ClassView
#endif
#include "progress.h"
#include "dlocationset.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImportLocations  
{
public:
	D_LOC_DB locbuffer;
	LOC_DB loc;
	CString mDir;
	char *pBuf;
	ImporterData *m_pImporterData;
	CDLocationset theSet;
	CImportLocations();
	CImportLocations( CString dir, char *p, ImporterData *pimp ) { mDir = dir; pBuf=p; m_pImporterData=pimp; }
	virtual ~CImportLocations();
    void process();
	int checkRow();
    int doDbRow( int bAdd = 0 );


};

#endif // !defined(AFX_IMPORTLOCATIONS_H__07CA7B66_5627_4447_95BF_09C6D5DD8B36__INCLUDED_)
