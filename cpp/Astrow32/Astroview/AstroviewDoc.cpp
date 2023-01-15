// AstroviewDoc.cpp : implementation of the CAstroviewDoc class
//

#include "stdafx.h"
#include "Astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "tabs.hpp"
#include "virttext.hpp"
#include "paths.hpp"
#include "coverdat.hpp"
#include "AstroviewDoc.h"
#include "paths.hpp"
#include "astroviewview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstroviewDoc

IMPLEMENT_DYNCREATE(CAstroviewDoc, CDocument)

BEGIN_MESSAGE_MAP(CAstroviewDoc, CDocument)
	//{{AFX_MSG_MAP(CAstroviewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstroviewDoc construction/destruction

CAstroviewDoc::CAstroviewDoc()
{
	// TODO: add one-time construction code here
CanClose = 1;
pVTBuf = NULL;
file_no = 1;
num_files = 1;
pStringArray = NULL;
#ifdef PRO
cover = NULL;
#endif
}

CAstroviewDoc::~CAstroviewDoc()
{
 if ( pVTBuf != NULL )
   delete pVTBuf;
 // don't delete string array it's an address of a local variable
#ifdef PRO
 if ( cover != NULL ) {
    delete cover;
	cover = NULL;
	}
#endif
}

BOOL CAstroviewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAstroviewDoc serialization

void CAstroviewDoc::Serialize(CArchive& ar)
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
// CAstroviewDoc diagnostics

#ifdef _DEBUG
void CAstroviewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAstroviewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstroviewDoc commands

BOOL CAstroviewDoc::OnOpenDocument(LPCTSTR lpszPathName) 

{
 char *p;
 if ( pVTBuf != NULL ) {
    delete pVTBuf;
	pVTBuf = NULL;
	}
#ifdef PRO
 if ( cover != NULL ) {
    delete cover;
	cover = NULL;
	}
#endif
 if (!CDocument::OnOpenDocument(lpszPathName))
	return FALSE;
 p = strchr(lpszPathName,'.' );
 if ( p != NULL ) {
	if ( !strcmpi( p, ".CPG" ) ) {
#ifdef PRO
		cover = new CoverPageData;
		cover->load((char *)lpszPathName);
		pVTBuf = new VirtualTextBuffer();
		isCover = 1;
#endif		
		}
	else { 
		isCover = 0;
#ifdef PRO
		cover = NULL;
#endif
		pVTBuf = new VirtualTextBuffer();
		pVTBuf->tab_init(62);
		pVTBuf->virtualizeFile((char *)lpszPathName, -1);
		pVTBuf->openVbuf();
		}
	
	}
 
 // TODO: Add your specialized creation code here
 if ( !isCover )
    UpdateAllViews(NULL);
 return TRUE;
}

VirtualTextBuffer * CAstroviewDoc::GetVirtBuf()
{
 return pVTBuf;
}

BOOL CAstroviewDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
 CDocument::OnSaveDocument(lpszPathName);
#ifdef PRO
 pVTBuf->saveFile();
#endif 
 return( TRUE );
}


void CAstroviewDoc::SetFileDB( XPFILE_DB *ptr )
{
 char buf[300];
 strcpy(buf,set_path(ptr->file_name,ptr->folder));
 if ( pVTBuf != NULL )
    delete pVTBuf;
 if (!CDocument::OnOpenDocument(buf))
 	return;
 pVTBuf = new VirtualTextBuffer();
 pVTBuf->tab_init(62);
 if (!strcmpi(ptr->comment,"ASTRO-Helper File"))
	 pVTBuf->virtualizeFile(ptr->file_name, HELP_F);
 else
	 pVTBuf->virtualizeFile(ptr->file_name, ptr->folder);
 pVTBuf->openVbuf();
 UpdateAllViews(NULL);
}

BOOL CAstroviewDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( !CanClose )
	   return CanClose;
#ifdef PRO
	else if (!IsModified())
       return TRUE;
	else {
       int ret =  MessageBox(NULL, "This File Has Been Saved. Do You Want To Save It?", 
		   "ASTRO for Windows",MB_ICONSTOP|MB_YESNOCANCEL );
       if ( ret == IDYES ) {
		  pVTBuf->saveFile();	 
		  return TRUE;
	      }
	   else if ( ret == IDNO )
		  return TRUE;	
	   else return FALSE;
	   }
#endif 

}


void CAstroviewDoc::DoNextFile()
{
ASSERT(pStringArray != NULL);
ASSERT(file_no+1<=num_files);
OnOpenDocument((*pStringArray)[file_no++]);
}

void CAstroviewDoc::DoPrint()
{
 POSITION pos = GetFirstViewPosition();
 CView* pFirstView = GetNextView( pos );
 ((CAstroviewView *)pFirstView)->DoPrint();
}

