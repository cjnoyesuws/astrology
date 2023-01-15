// schecd.cpp : Implementation of CTesterApp and DLL registration.

#include "stdafx.h"
#include "tester.h"
#include "schecd.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP schecd::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_Ischecd,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
