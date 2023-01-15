// TextGetter.h : Declaration of the CTextGetter

#pragma once
#include "resource.h"       // main symbols


// ITextGetter
[
	object,
	uuid("74EAD860-7971-4E4D-B7CD-1C9C9F96B854"),
	dual,	helpstring("ITextGetter Interface"),
	pointer_default(unique)
]
__interface ITextGetter : IDispatch
{
	[propput, id(1), helpstring("property Row")] HRESULT Row([in] SHORT newVal);
	[propput, id(2), helpstring("property Col")] HRESULT Col([in] SHORT newVal);
	[propget, id(3), helpstring("property Text")] HRESULT Text([out, retval] BSTR* pVal);
};



// CTextGetter

[
	coclass,
	threading("apartment"),
	vi_progid("numerocalc.TextGetter"),
	progid("numerocalc.TextGetter.1"),
	version(1.0),
	uuid("9654336F-86B5-4970-821A-4DDFDE04EB0E"),
	helpstring("TextGetter Class")
]
class ATL_NO_VTABLE CTextGetter : 
	public ITextGetter
{
public:
	CTextGetter()
	{
	}
    int row;
	int col;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

	STDMETHOD(put_Row)(SHORT newVal);
	STDMETHOD(put_Col)(SHORT newVal);
	STDMETHOD(get_Text)(BSTR* pVal);
};

