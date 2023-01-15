// NumerowCalcer.h : Declaration of the CNumerowCalcer

#pragma once
#include "resource.h"       // main symbols


// INumerowCalcer
[
	object,
	uuid("B480AEC1-0F33-49B2-AF97-C89DBD206D32"),
	dual,	helpstring("INumerowCalcer Interface"),
	pointer_default(unique)
]
__interface INumerowCalcer : IDispatch
{
	[propput, id(1), helpstring("property Index")] HRESULT Index([in] SHORT newVal);
	[propput, id(2), helpstring("property FirstName")] HRESULT FirstName([in] BSTR newVal);
	[propput, id(3), helpstring("property MiddleName")] HRESULT MiddleName([in] BSTR newVal);
	[propput, id(4), helpstring("property LastName")] HRESULT LastName([in] BSTR newVal);
	[propput, id(5), helpstring("property BirthDate")] HRESULT BirthDate([in] DATE newVal);
	[id(6), helpstring("method CalcChart")] HRESULT CalcChart([in] CHAR* file, [in] CHAR* person, [in] CHAR* comments, CHAR* type, [in] SHORT typecode);
	[propput, id(7), helpstring("property TranStart")] HRESULT TransStart([in] SHORT newVal);
	[propput, id(8), helpstring("property TransEnd")] HRESULT TransEnd([in] SHORT newVal);
	[propput, id(9), helpstring("property FontName")] HRESULT FontName([in] BSTR newVal);
	[propput, id(10), helpstring("property FontSize")] HRESULT FontSize([in] SHORT newVal);
	[propput, id(11), helpstring("property FontCodes")] HRESULT FontCodes([in] SHORT newVal);
	[propput, id(12), helpstring("property FontColor")] HRESULT FontColor([in] ULONG newVal);
	[propput, id(13), helpstring("property LeftMargin")] HRESULT LeftMargin([in] SHORT newVal);
	[propput, id(14), helpstring("property TextWidth")] HRESULT TextWidth([in] SHORT newVal);
	[propput, id(15), helpstring("property DemoMode")] HRESULT DemoMode([in] SHORT newVal);
	[id(16), helpstring("method ConvertFile")] HRESULT ConvertFile([in] CHAR* in_name, [in] CHAR* out_name, SHORT type);
};



// CNumerowCalcer

[
	coclass,
	threading("apartment"),
	vi_progid("numerocalc.NumerowCalcer"),
	progid("numerocalc.NumerowCalcer.1"),
	version(1.0),
	uuid("C2875FFB-F20C-46D6-8701-3FC4E1AC2FA2"),
	helpstring("NumerowCalcer Class")
]
class ATL_NO_VTABLE CNumerowCalcer : 
	public INumerowCalcer
{
public:
	CNumerowCalcer()
	{
	}
    
	CHART_INFO theChartInfo;
	FILE_ID theFileId;
	short start, end;
	FONT theFonts[4];
	ULONG theColors[4];
	short width;
	short left_offset;
	short demo_mode;
	short index;

    char *get_name_ptr(int which);

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
	STDMETHOD(put_FirstName)(BSTR newVal);
	STDMETHOD(put_MiddleName)(BSTR newVal);
	STDMETHOD(put_LastName)(BSTR newVal);
	STDMETHOD(put_BirthDate)(DATE newVal);
	STDMETHOD(CalcChart)(CHAR* file, CHAR* person, CHAR* comments, CHAR* type, SHORT typecode);
	STDMETHOD(put_TransStart)(SHORT newVal);
	STDMETHOD(put_TransEnd)(SHORT newVal);
	STDMETHOD(put_FontName)(BSTR newVal);
	STDMETHOD(put_FontSize)(SHORT newVal);
	STDMETHOD(put_FontCodes)(SHORT newVal);
	STDMETHOD(put_FontColor)(ULONG newVal);
	STDMETHOD(put_LeftMargin)(SHORT newVal);
	STDMETHOD(put_TextWidth)(SHORT newVal);
	STDMETHOD(put_DemoMode)(SHORT newVal);
	STDMETHOD(ConvertFile)(CHAR* in_name, CHAR* out_name, SHORT type);
};

