// Schdule.h : Declaration of the CSchdule

#ifndef __SCHDULE_H_
#define __SCHDULE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSchdule
class ATL_NO_VTABLE CSchdule : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSchdule, &CLSID_Schdule>,
	public IDispatchImpl<ISchdule, &IID_ISchdule, &LIBID_TESTERLib>
{
public:
	CSchdule()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SCHDULE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSchdule)
	COM_INTERFACE_ENTRY(ISchdule)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISchdule
public:
	STDMETHOD(GetSchedule)(char  *id, char *date, int max, SCHED *pSched);
};

#endif //__SCHDULE_H_
