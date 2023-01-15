// TabCtrl.cpp : Implementation of CTabCtrlApp and DLL registration.

#include "stdafx.h"
#include "TabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTabCtrlApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xD4912B41, 0x111, 0x42D0, { 0x86, 0xF4, 0x16, 0xEB, 0xE, 0x2D, 0xBF, 0x4D } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CTabCtrlApp::InitInstance - DLL initialization

BOOL CTabCtrlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CTabCtrlApp::ExitInstance - DLL termination

int CTabCtrlApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
