// AstrographDoc.cpp : implementation of the CAstrographDoc class
//

#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "errors.fns"
#include "graphdat.hpp"
#include "paths.hpp"
#include "aspect.h"
#include "Astrow.h"
#include "AstrographDoc.h"
#include "vicdefs.h"
#include <io.h>
#include <math.h>
#include "errors.fns"
#include "radius.h"
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "dataext.h"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "plotslin.hpp"
#include "tickcirc.hpp"
#include "graspgrd.hpp"
#include "graspcir.hpp"
#include "key.hpp"
#include "datakey.hpp"
#include "plotgrtp.hpp"
#include "graopt.hpp"
#include "inifile.hpp"
#include "grafont.hpp"
#include "AstrographView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstrographDoc

IMPLEMENT_DYNCREATE(CAstrographDoc, CDocument)

BEGIN_MESSAGE_MAP(CAstrographDoc, CDocument)
	//{{AFX_MSG_MAP(CAstrographDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrographDoc construction/destruction

CAstrographDoc::CAstrographDoc()
{
	// TODO: add one-time construction code here
CanClose = 1;
file_no = 1;
num_files = 1;
_isOk = 0;
theDataPtr = new GraphData();
pStringArray = NULL;
}

CAstrographDoc::~CAstrographDoc()
{
 if ( theDataPtr != 0 )
	delete theDataPtr;
 // don't delete pStringArray as it is a pointer to a local variable	
}

BOOL CAstrographDoc::OnNewDocument()
{
 if ( theDataPtr != 0 ) {
	delete theDataPtr;
	theDataPtr = new GraphData();
	_isOk = 0;
	theFileName = "";
    }

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAstrographDoc serialization

void CAstrographDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CAstrographDoc diagnostics

#ifdef _DEBUG
void CAstrographDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAstrographDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstrographDoc commands


BOOL CAstrographDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    if ( !strcmpi(lpszPathName,".ASGRA") )
		return( TRUE );
	if ( theDataPtr != 0 ) {
	   delete theDataPtr;
	   theDataPtr = new GraphData();
	   _isOk = 0;
	   theFileName = lpszPathName;
       }
	
	if ( !theDataPtr->read( (char *)lpszPathName, -1 ) )
	   return FALSE;
	_isOk = 1;
	UpdateAllViews(NULL);
	return TRUE;

}

void CAstrographDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( !strcmpi(lpszPathName,".ASGRA") )
		return;
	CDocument::SetPathName(lpszPathName, bAddToMRU);
}

void CAstrographDoc::SetFileDB( XPFILE_DB *ptr )
{
 if ( theDataPtr != 0 ) {
    delete theDataPtr;
    theDataPtr = new GraphData();
    _isOk = 0;
    theFileName = ptr->file_name;
    }
 if ( !theDataPtr->read( ptr->file_name, ptr->folder ) )
   return;
_isOk = 1;
UpdateAllViews(NULL);
}

BOOL CAstrographDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CanClose;
}


void CAstrographDoc::DoNextFile()
{
ASSERT(pStringArray != NULL);
ASSERT(file_no+1<=num_files);
OnOpenDocument((*pStringArray)[file_no++]);
}

void CAstrographDoc::DoPrint()
{
#ifndef GRAVIEWER
 POSITION pos = GetFirstViewPosition();
 CView* pFirstView = GetNextView( pos );
 ((CAstrographView *)pFirstView)->DoPrint();
#endif
}

void CAstrographDoc::DoExport()
{
 int cont=0;

 CanClose = 0;	
 do {
    POSITION pos = GetFirstViewPosition();
	CView* pFirstView = GetNextView( pos );
    ((CAstrographView *)pFirstView)->DoExport();
	if ( HasMoreFiles() ) {
		cont = 1;
		DoNextFile();
		}
	else 
		cont = 0;
	} while ( cont );
 CanClose = 1;
}

