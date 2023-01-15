// AstInstCalc2.h : Declaration of the CAstInstCalc

#pragma once
#include "resource.h"       // main symbols


// IAstInstCalc
[
	object,
	uuid("AE6B81CB-38A6-4171-B2F2-A1F47658EEE4"),
	dual,	helpstring("IAstInstCalc Interface"),
	pointer_default(unique)
]
__interface IAstInstCalc : IDispatch
{
	[propget, id(1), helpstring("property Value")] HRESULT Value([out, retval] VARIANT* pVal);
	[propput, id(2), helpstring("property Index")] HRESULT Index([in] LONG newVal);
	[id(3), helpstring("method StartAt")] HRESULT StartAt(LONG month, LONG day, LONG year, LONG hour);
};



// CAstInstCalc

[
	coclass,
	threading("apartment"),
	vi_progid("instcalc.AstInstCalc"),
	progid("instcalc.AstInstCalc.1"),
	version(1.0),
	uuid("53F0DCB8-C083-4931-B261-2D15BE63035D"),
	helpstring("AstInstCalc Class")
]
class ATL_NO_VTABLE CAstInstCalc : 
	public IAstInstCalc
{
public:
	STDMETHOD(get_Value)(VARIANT* pVal);
	STDMETHOD(put_Index)(LONG newVal);
	STDMETHOD(StartAt)(LONG month, LONG day, LONG year, LONG hour);

	SYSTEMTIME curr;
	DATES the_date;
	TIM the_time;
	DEG_MIN longitude, latitude;
	int gmt_hours, gmt_min;
	int index;
	char longbuf[20], latbuf[20], gmtbuf[10];
	short minutes[20];
	char *txtbuf[25];
	CAstInstCalc();
	
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

};

