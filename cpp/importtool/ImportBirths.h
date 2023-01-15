// ImportBirths.h: interface for the CImportBirths class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTBIRTHS_H__EE50EFAE_9BFB_48B9_9F1B_B556BFBEB286__INCLUDED_)
#define AFX_IMPORTBIRTHS_H__EE50EFAE_9BFB_48B9_9F1B_B556BFBEB286__INCLUDED_

#ifndef DEGR
#include "astro.h"
#include "Useri.h"	// Added by ClassView
#include "Dataext.h"	// Added by ClassView
#include "Dbstruct.h"	// Added by ClassView
#endif
#include "progress.h"
#include "dbirthset.h"
#include "drectification.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImportBirths  
{
public:
	RECT_DATA rect;
	BIRTH_DB birthdata;
	D_RBIRTH_DB birthrec;
	CString mDir;
	char *pBuf;
	ImporterData *m_pImporterData;
    CDBirthset birthset;
	CDRectification rectset;
	CImportBirths( CString dir, char *p, ImporterData *pimp ) { mDir=dir; pBuf=p; m_pImporterData=pimp; }
	CImportBirths();
	virtual ~CImportBirths();
    void process();
	int checkRow(int which=0);
    int doDbRow( int bAdd, int bAddRel );


};

#endif // !defined(AFX_IMPORTBIRTHS_H__EE50EFAE_9BFB_48B9_9F1B_B556BFBEB286__INCLUDED_)
