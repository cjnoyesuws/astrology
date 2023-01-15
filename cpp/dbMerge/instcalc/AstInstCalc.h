// AstInstCalc.h : Declaration of the CAstInstCalc

#pragma once
#include "resource.h"       // main symbols


// IAstInstCalc
[
	object,
	uuid("31428BBB-C9D7-49C8-986C-567F74005392"),
	dual,	helpstring("IAstInstCalc Interface"),
	pointer_default(unique)
]
__interface IAstInstCalc : IDispatch
{
};



// CAstInstCalc

[
	coclass,
	threading("apartment"),
	vi_progid("instcalc.AstInstCalc"),
	progid("instcalc.AstInstCalc.1"),
	version(1.0),
	uuid("95D3FA90-AC05-438E-B5DF-AC1126C82815"),
	helpstring("AstInstCalc Class")
]
class ATL_NO_VTABLE CAstInstCalc : 
	public IAstInstCalc
{
public:
	CAstInstCalc()
	{
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

};

