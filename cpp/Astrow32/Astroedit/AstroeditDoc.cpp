// AstroeditDoc.cpp : implementation of the CAstroeditDoc class
//

#include "stdafx.h"
#include "afxrich.h"
#include "Astroedit.h"
#include "AstroeditDoc.h"
#include "astro.h"
#include "useri.h"
#include "attrib.h"
#include "convopt.hpp"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "repstyle.hpp"
#include "prtrdrv.hpp"
#include "coverdat.hpp"
#include "asfil2tx.hpp"
#include <stdio.h>
#include <io.h>
//#include <strstrea.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern int CompressStrstreamFile(strstream &in, FILE *out );
//extern int RichTextToAstro( char *file, strstream &out);
extern int RichTextToAstro( char *file, FILE *out);
extern FILE *re_save_header( char *iname, char *oname );



/////////////////////////////////////////////////////////////////////////////
// CAstroeditDoc

IMPLEMENT_DYNCREATE(CAstroeditDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CAstroeditDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CAstroeditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstroeditDoc construction/destruction

CAstroeditDoc::CAstroeditDoc()
{
	// TODO: add one-time construction code here

}
 
CAstroeditDoc::~CAstroeditDoc()
{
unlink( VirtualFile );
}

BOOL CAstroeditDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	UpdateAllViews(NULL);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAstroeditDoc serialization

void CAstroeditDoc::Serialize(CArchive& ar)
{
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CAstroeditDoc diagnostics

#ifdef _DEBUG
void CAstroeditDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CAstroeditDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstroeditDoc commands	CDocument 

BOOL CAstroeditDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if ( !access( VirtualFile, 04 ) ) {
	   unlink( VirtualFile );
	   VirtualFile = "";
	   }
	
	ActualFile = lpszPathName;
	astroFileToTextSimple *pSimp = new astroFileToTextSimple(-1);
	pSimp->doConvert((char *)lpszPathName);
	VirtualFile = pSimp->getOutFile();
	delete pSimp;
	if (!CRichEditDoc::OnOpenDocument(VirtualFile))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	SetTitle(lpszPathName);
	UpdateAllViews(NULL);
	return TRUE;
}


BOOL CAstroeditDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRichEditDoc::OnSaveDocument(VirtualFile);
	SaveFile(ActualFile,VirtualFile);
	return( TRUE );
}

int CAstroeditDoc::SaveFile( CString &act, CString &virt )
{
 NFP xfpt;
// strstream string;
 long at;
 FILE *stream;
 char buf[100];
 
 GetTempFileName( ".", "AST", 0, buf );
 stream = re_save_header( (char *)(LPCTSTR)act, buf );
 RichTextToAstro( (char *)(LPCTSTR)virt, stream);
 fclose(stream);
 unlink(act);
 rename(buf,act);
 return( 1 );
}  									
