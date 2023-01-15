// test.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// test

IMPLEMENT_DYNCREATE(test, CCmdTarget)

test::test()
{
	EnableAutomation();
}

test::~test()
{
}


void test::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(test, CCmdTarget)
	//{{AFX_MSG_MAP(test)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(test, CCmdTarget)
	//{{AFX_DISPATCH_MAP(test)
	DISP_FUNCTION(test, "GetSchedule", GetSchedule, VT_I2, VTS_BSTR VTS_BSTR VTS_I2 VTS_PUNKNOWN)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_Itest to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {13A3B170-4EA5-11D3-9DE7-0000C00DEE96}
static const IID IID_Itest =
{ 0x13a3b170, 0x4ea5, 0x11d3, { 0x9d, 0xe7, 0x0, 0x0, 0xc0, 0xd, 0xee, 0x96 } };

BEGIN_INTERFACE_MAP(test, CCmdTarget)
	INTERFACE_PART(test, IID_Itest, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// test message handlers

void test::GetSchedule() 
{
	// TODO: Add your dispatch handler code here

}

short test::GetSchedule(LPCTSTR Id, LPCTSTR Date, short maxSched, LPUNKNOWN FAR* pSched) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}
