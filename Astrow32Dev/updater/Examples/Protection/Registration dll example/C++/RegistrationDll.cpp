// RegistrationDll.cpp : Defines the entry point for the DLL application.
//

//*********************************************************************
// INCLUDES
//*********************************************************************

#include "stdafx.h"

//*********************************************************************
// DEFINES
//*********************************************************************

#define DllExport   __declspec( dllexport ) 

//*********************************************************************
// MAIN
//*********************************************************************

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

//*********************************************************************
// EXPORTED FUNCTIONS
//*********************************************************************

extern "C" __declspec( dllexport ) bool CheckLicense()
{
	Sleep (3000);
	return true;
}