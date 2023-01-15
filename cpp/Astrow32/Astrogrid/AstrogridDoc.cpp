// AstrogridDoc.cpp : implementation of the CAstrogridDoc class
//

#include "stdafx.h"
#ifdef CHARTVIEW
#include "Astrogrid.h"
#else 
#include "Astrow.h"
#endif
#include "ASTRO.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include <afxhtml.h>
#include "AstrogridDoc.h"
#include "attrib.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "txtdrv.h"
#include "convopt.hpp"
#include "repstyle.hpp"
#include "paths.hpp"
#include "coverdat.hpp"
#include "prtrdrv.hpp"
#include "asfil2tx.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAstrogridDoc

IMPLEMENT_DYNCREATE(CAstrogridDoc, CDocument)

#ifdef CHARTVIEW
BEGIN_MESSAGE_MAP(CAstrogridDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
END_MESSAGE_MAP()
#else
BEGIN_MESSAGE_MAP(CAstrogridDoc, CDocument)
	ON_COMMAND(ID_FILE_EXPORT, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFileSaveAs)
END_MESSAGE_MAP()
#endif

// CAstrogridDoc construction/destruction

CAstrogridDoc::CAstrogridDoc()
{
	// TODO: add one-time construction code here
CanClose = 1;
file_no = 1;
num_files = 1;
pStringArray = NULL;
}

CAstrogridDoc::~CAstrogridDoc()
{
}

BOOL CAstrogridDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CAstrogridDoc serialization

void CAstrogridDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CAstrogridDoc diagnostics

#ifdef _DEBUG
void CAstrogridDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAstrogridDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAstrogridDoc commands

BOOL CAstrogridDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
 char buf[_MAX_DIR];
	if ( !strcmpi(".ASRPT",lpszPathName) )
		return( TRUE );
	GetTempPath(_MAX_DIR,buf);
    GetTempFileName(buf,"AST", 0, buf );
	char *p = strrchr(buf,'.');
	if ( p != NULL )
		strcpy(p+1,"html");
	else
		strcat(buf,".html");
	m_strTemp = buf;
	m_strDoc = lpszPathName;
    astroFileToTextSimple *pConv = new astroFileToTextSimple(-1);
    pConv->setOutFile(buf);
	if ( !pConv->doConvert(lpszPathName) ) {
	   delete pConv;
       return( FALSE );
	   }
	db = pConv->fptr.x.fpt;
	delete pConv;
	m_strTemp = buf;
	makeURL(CString(buf));
	m_strName = db.name;
	SetTitle(m_strName);
	UpdateAllViews(NULL);
	return TRUE;
}

void CAstrogridDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU)
{
 if ( !strcmpi(lpszPathName,".ASGRD") )
		return;
	CDocument::SetPathName(lpszPathName, bAddToMRU);
}

void CAstrogridDoc::SetTitle(LPCTSTR lpszTitle)
{
 CDocument::SetTitle(lpszTitle);
}

void CAstrogridDoc::OnCloseDocument(void)
{
    unlink((const char *)m_strTemp);
	int off = m_strTemp.Find('.');
    if ( off != 0 )
		m_strTemp = m_strTemp.Left(off);
	m_strTemp += ".tmp";
	unlink((const char *)m_strTemp);
	CDocument::OnCloseDocument();
}

void CAstrogridDoc::makeURL(CString &s)
{
 s.Replace('\\','/');
 m_strHTML = "file:///" + s;

}

void CAstrogridDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
int n=0;
 char nbuf[200], nbuf2[200];
 static CStringArray ar;
 astroFileToText *txt;
 ConvData *pcd;
 ar.SetSize(2,1);
 txt = new astroFileToText(-1);
 if ( !txt->getSetup(&pcd ) ) {
    delete txt;					
    return;
    }
 ar[n] = m_strDoc;
 n++;
 ar[n] = "NULL";
 txt->setFiles( &ar, 0 );
 txt->doConvert(NULL);
 delete txt;

	
}

void CAstrogridDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  if ( m_strDoc.GetLength() > 0 )
	  pCmdUI->Enable();
  else
	  pCmdUI->Enable(FALSE);
}

void CAstrogridDoc::DoNextFile()
{
ASSERT(pStringArray != NULL);
ASSERT(file_no+1<=num_files);
OnOpenDocument((*pStringArray)[file_no++]);
}

void CAstrogridDoc::DoPrint()
{
 POSITION pos = GetFirstViewPosition();
 CView* pFirstView = GetNextView( pos );
 ((CHtmlView *)pFirstView)->OnFilePrint();
}

