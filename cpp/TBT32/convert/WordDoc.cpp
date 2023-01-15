// WordDoc.cpp : implementation file
//

#include "stdafx.h"
#include "convert.h"
#include "WordDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordDoc

IMPLEMENT_DYNCREATE(CWordDoc, COleDocument)

CWordDoc::CWordDoc()
{
	EnableAutomation();
}

BOOL CWordDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CWordDoc::~CWordDoc()
{
}

void CWordDoc::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	COleDocument::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CWordDoc, COleDocument)
	//{{AFX_MSG_MAP(CWordDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CWordDoc, COleDocument)
	//{{AFX_DISPATCH_MAP(CWordDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IWordDoc to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {E776BB73-165A-465B-95D0-BF566B2164DC}
static const IID IID_IWordDoc =
{ 0xe776bb73, 0x165a, 0x465b, { 0x95, 0xd0, 0xbf, 0x56, 0x6b, 0x21, 0x64, 0xdc } };

BEGIN_INTERFACE_MAP(CWordDoc, COleDocument)
	INTERFACE_PART(CWordDoc, IID_IWordDoc, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordDoc diagnostics

#ifdef _DEBUG
void CWordDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CWordDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWordDoc serialization

void CWordDoc::Serialize(CArchive& ar)
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
// CWordDoc commands
