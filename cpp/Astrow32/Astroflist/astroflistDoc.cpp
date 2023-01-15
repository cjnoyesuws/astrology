// astroflistDoc.cpp : implementation of the CAstroflistDoc class
//

#include "stdafx.h"

#include "astrow.h"
#include "astro.h"
#include "useri.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "astroflistDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int fIsQuitting;

/////////////////////////////////////////////////////////////////////////////
// CAstroflistDoc

IMPLEMENT_DYNCREATE(CAstroflistDoc, CDocument)

BEGIN_MESSAGE_MAP(CAstroflistDoc, CDocument)
	//{{AFX_MSG_MAP(CAstroflistDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstroflistDoc construction/destruction

CAstroflistDoc::CAstroflistDoc()
{
	// TODO: add one-time construction code here
	GetFileListPtrAndType( &flary, type, this );
	Reset();
	newAble = 0;
	UpdateAllViews(NULL);
}

CAstroflistDoc::~CAstroflistDoc()
{
  PutBackFileListPtrAndType( flary, type );
}

BOOL CAstroflistDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if ( type == GRA_F )
	   SetTitle("ASTRO Graphic Files");
	else if (type == NON_GRA )
	   SetTitle("ASTRO Report Files");
	else if (type == GRIDFX )
	   SetTitle("ASTRO Grid Files");
	else
	   SetTitle("ASTRO Files");
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	UpdateAllViews(NULL);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAstroflistDoc serialization

void CAstroflistDoc::Serialize(CArchive& ar)
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
// CAstroflistDoc diagnostics

#ifdef _DEBUG
void CAstroflistDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAstroflistDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstroflistDoc commands

BOOL CAstroflistDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	if ( flary != &AstFileList ) {
	   flary->setName((char *)lpszPathName,-1);
	   if ( strcmpi(lpszPathName,"UNTITLED.AFL" ) ) {
		  flary->inMem(0); 		      
		  flary->read();
	      }
	   }
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

BOOL CAstroflistDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	
	// TODO: Add your specialized code here and/or call the base class
	if ( flary != &AstFileList ) {
	   flary->setName((char *)lpszPathName,-1);
	   if ( strcmpi(lpszPathName,"UNTITLED.AFL" ) )
	      flary->write();
	   else {
		  CFileDialog cfo(FALSE, ".AFL", "MyFileList.AFL", 
			  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
			  "ASTRO File List (*.AFL)|*.AFL|All Files (*.*)|*.*||");
		  cfo.m_ofn.lpstrTitle="User File List File To Save To:";
		  if ( cfo.DoModal() == IDOK ) {
			 flary->setName((char *)(LPCTSTR)cfo.GetPathName());
           	 flary->write();
			}
	   }
	}
	return(1);
}

BOOL CAstroflistDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class

	     return CDocument::CanCloseFrame(pFrame);
}

void CAstroflistDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
  if ( fIsQuitting ) {
	 CDocument::OnCloseDocument(); 
	 return;
     }
  int ret =  MessageBox(NULL, "Are You Sure You Want to Close This Window? You Will Need it to Access ASTRO's Reports and Graphics.", 
		   "ASTRO for Windows",MB_ICONSTOP|MB_YESNOCANCEL );
  if ( ret == IDYES ) 
	  CDocument::OnCloseDocument(); 
  else
	 return;
 
}
