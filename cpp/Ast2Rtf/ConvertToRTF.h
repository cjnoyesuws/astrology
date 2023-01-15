// ConvertToRTF.h : Declaration of the CConvertToRTF

#pragma once
#include "resource.h"       // main symbols


// IConvertToRTF
[
	object,
	uuid("7AA4E393-8C1B-409C-AA5B-D8778C3A5EE9"),
	dual,	helpstring("IConvertToRTF Interface"),
	pointer_default(unique)
]
__interface IConvertToRTF : IDispatch
{
	[propput, id(1), helpstring("property SourceFile")] HRESULT SourceFile([in] BSTR newVal);
	[propput, id(2), helpstring("property DestFile")] HRESULT DestFile([in] BSTR newVal);
	[id(3), helpstring("method Convert")] HRESULT Convert(void);
};



// CConvertToRTF

[
	coclass,
	threading("apartment"),
	vi_progid("Ast2Rtf.ConvertToRTF"),
	progid("Ast2Rtf.ConvertToRTF.1"),
	version(1.0),
	uuid("2EF5FE38-C5AB-4F26-8979-9A8468D2E416"),
	helpstring("ConvertToRTF Class")
]
class ATL_NO_VTABLE CConvertToRTF : 
	public IConvertToRTF
{
public:
	CConvertToRTF()
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

	STDMETHOD(put_SourceFile)(BSTR newVal);
	STDMETHOD(put_DestFile)(BSTR newVal);
	STDMETHOD(Convert)(void);
};

