// BioDataCalc.h : Declaration of the CBioDataCalc

#pragma once
#include "resource.h"       // main symbols


// IBioDataCalc
[
	object,
	uuid("18B41BCD-EA9C-48FD-B6BC-EE8C411C4073"),
	dual,	helpstring("IBioDataCalc Interface"),
	pointer_default(unique)
]
__interface IBioDataCalc : IDispatch
{
	[propput, id(1), helpstring("property PersName")] HRESULT PersName([in] BSTR newVal);
	[propput, id(2), helpstring("property BirthDate")] HRESULT BirthDate([in] DATE newVal);
	[propput, id(3), helpstring("property StartDate")] HRESULT StartDate([in] DATE newVal);
	[propput, id(4), helpstring("property Index")] HRESULT Index([in] SHORT newVal);
	[propget, id(5), helpstring("property Physical")] HRESULT Physical([out, retval] DOUBLE* pVal);
	[propget, id(6), helpstring("property Emotional")] HRESULT Emotional([out, retval] DOUBLE* pVal);
	[propget, id(7), helpstring("property Intellectual")] HRESULT Intellectual([out, retval] DOUBLE* pVal);
	[propget, id(8), helpstring("property EmotionalDesc")] HRESULT EmotionalDesc([out, retval] BSTR* pVal);
	[propget, id(9), helpstring("property PhysicalDesc")] HRESULT PhysicalDesc([out, retval] BSTR* pVal);
	[propget, id(10), helpstring("property IntellectualDesc")] HRESULT IntellectualDesc([out, retval] BSTR* pVal);
	[id(11), helpstring("method Calc")] HRESULT Calc(void);
	[id(12), helpstring("method SaveData")] HRESULT SaveData([in] BSTR file);
	[id(13), helpstring("method LoadData")] HRESULT LoadData([in] BSTR name);
	[id(14), helpstring("method Export")] HRESULT Export([in] BSTR name);
	[propget, id(15), helpstring("property Days")] HRESULT Days([out, retval] SHORT* pVal);
	[propget, id(16), helpstring("property Critical")] HRESULT Critical([out, retval] DOUBLE* pVal);
	[propget, id(17), helpstring("property CriticalDesc")] HRESULT CriticalDesc([out, retval] BSTR* pVal);
	[propget, id(1), helpstring("property PersName")] HRESULT PersName([out, retval] BSTR* pVal);
	[propget, id(2), helpstring("property BirthDate")] HRESULT BirthDate([out, retval] DATE* pVal);
	[propget, id(3), helpstring("property StartDate")] HRESULT StartDate([out, retval] DATE* pVal);
	[propget, id(18), helpstring("property CSS")] HRESULT CSS([out, retval] BSTR* pVal);
	[propput, id(18), helpstring("property CSS")] HRESULT CSS([in] BSTR newVal);
};



// CBioDataCalc

[
	coclass,
	threading("apartment"),
	vi_progid("biocalc.BioDataCalc"),
	progid("biocalc.BioDataCalc.1"),
	version(1.0),
	uuid("37A3EB90-807D-4CA1-921D-BCAC087ED99C"),
	helpstring("BioDataCalc Class")
]
class ATL_NO_VTABLE CBioDataCalc : 
	public IBioDataCalc
{
public:
	CBioDataCalc()
	{
		pDayData = NULL;
		memset(&theChartData,0,sizeof(BiorythmChartData));
	    memset(&theData,0,sizeof(BiorythmData));
		memset(css,0,200);
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
    BiorythmChartData theChartData;
	BiorythmData theData;
	DayData *pDayData;
	char css[200];
	STDMETHOD(put_PersName)(BSTR newVal);
	STDMETHOD(put_BirthDate)(DATE newVal);
	STDMETHOD(put_StartDate)(DATE newVal);
	STDMETHOD(put_Index)(SHORT newVal);
	STDMETHOD(get_Physical)(DOUBLE* pVal);
	STDMETHOD(get_Emotional)(DOUBLE* pVal);
	STDMETHOD(get_Intellectual)(DOUBLE* pVal);
	STDMETHOD(get_EmotionalDesc)(BSTR* pVal);
	STDMETHOD(get_PhysicalDesc)(BSTR* pVal);
	STDMETHOD(get_IntellectualDesc)(BSTR* pVal);
	STDMETHOD(Calc)(void);
	STDMETHOD(SaveData)(BSTR file);
	STDMETHOD(LoadData)(BSTR name);
	STDMETHOD(Export)(BSTR name);
	STDMETHOD(get_Days)(SHORT* pVal);
	STDMETHOD(get_Critical)(DOUBLE* pVal);
	STDMETHOD(get_CriticalDesc)(BSTR* pVal);
	STDMETHOD(get_PersName)(BSTR* pVal);
	STDMETHOD(get_BirthDate)(DATE* pVal);
	STDMETHOD(get_StartDate)(DATE* pVal);
	STDMETHOD(get_CSS)(BSTR* pVal);
	STDMETHOD(put_CSS)(BSTR newVal);
};

