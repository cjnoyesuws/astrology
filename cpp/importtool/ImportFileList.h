// ImportBirths.h: interface for the CImportBirths class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTFILELIST_H__EE50EFAE_9BFB_48B9_9F1B_B556BFBEB286__INCLUDED_)
#define AFX_IMPORTFILELIST_H__EE50EFAE_9BFB_48B9_9F1B_B556BFBEB286__INCLUDED_

#ifndef DEGR
#include "astro.h"
#include "Useri.h"	// Added by ClassView
#include "Dataext.h"	// Added by ClassView
#include "Dbstruct.h"	// Added by ClassView
#endif
#include "importerdata.h"
#include "importtooldlg.h"
#include "filelistset.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImportFileList  
{
public:
	XPFILE_DB filedb, *ptr;
    FILE_DB w32;
    W16_FILE_DB w16;
	CString mDir;
	char *pBuf;
	ImporterData *m_pImporterData;
    CFileListSet theSet;
	CImportFileList( CString dir, char *p, ImporterData *pimp ) { mDir=dir; pBuf=p; m_pImporterData = pimp;}
	CImportFileList();
	virtual ~CImportFileList();
    void process();
	int checkRow();
    int doDbRow( int bAdd);
	void LoadFolders();


};

#endif // !defined(AFX_IMPORTFILELIST_H__EE50EFAE_9BFB_48B9_9F1B_B556BFBEB286__INCLUDED_)
