// DataTest.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "DataTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataTest

IMPLEMENT_DYNCREATE(CDataTest, CCmdTarget)

CDataTest::CDataTest()
{
	EnableAutomation();
}

CDataTest::~CDataTest()
{
}


void CDataTest::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CDataTest, CCmdTarget)
	//{{AFX_MSG_MAP(CDataTest)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDataTest, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CDataTest)
	DISP_PROPERTY_EX(CDataTest, "Name", GetName, SetName, VT_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDataTest to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {7C0054D0-D3D8-11D1-9DAC-0000C00DEE96}
static const IID IID_IDataTest =
{ 0x7c0054d0, 0xd3d8, 0x11d1, { 0x9d, 0xac, 0x0, 0x0, 0xc0, 0xd, 0xee, 0x96 } };

BEGIN_INTERFACE_MAP(CDataTest, CCmdTarget)
	INTERFACE_PART(CDataTest, IID_IDataTest, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataTest message handlers

BSTR CDataTest::GetName() 
{
	CString strResult;
	// TODO: Add your property handler here

	return strResult.AllocSysString();
}

void CDataTest::SetName(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

}
