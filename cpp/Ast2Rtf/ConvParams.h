// ConvParams.h : Declaration of the CConvParams

#pragma once
#include "resource.h"       // main symbols


// IConvParams
[
	object,
	uuid("263B7908-77D1-4312-BCBE-BF288ACBC50E"),
	dual,	helpstring("IConvParams Interface"),
	pointer_default(unique)
]
__interface IConvParams : IDispatch
{
	[propput, id(1), helpstring("property Index")] HRESULT Index([in] SHORT newVal);
	[propget, id(2), helpstring("property Name")] HRESULT Name([out, retval] BSTR* pVal);
	[propget, id(3), helpstring("property Color")] HRESULT Color([out, retval] ULONG* pVal);
	[propget, id(4), helpstring("property Size")] HRESULT Size([out, retval] SHORT* pVal);
	[propget, id(5), helpstring("property Styles")] HRESULT Styles([out, retval] LONG* pVal);
};



// CConvParams

[
	coclass,
	threading("apartment"),
	vi_progid("Ast2Rtf.ConvParams"),
	progid("Ast2Rtf.ConvParams.1"),
	version(1.0),
	uuid("C7C39095-C728-4AA9-B7CA-6959B9EDE50E"),
	helpstring("ConvParams Class")
]
class ATL_NO_VTABLE CConvParams : 
	public IConvParams
{
public:
	CConvParams()
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

	STDMETHOD(put_Index)(SHORT newVal);
	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(get_Color)(ULONG* pVal);
	STDMETHOD(get_Size)(SHORT* pVal);
	STDMETHOD(get_Styles)(LONG* pVal);
};

