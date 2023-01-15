// schecd.h: Definition of the schecd class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHECD_H__C4B368C2_4EA8_11D3_9DE7_0000C00DEE96__INCLUDED_)
#define AFX_SCHECD_H__C4B368C2_4EA8_11D3_9DE7_0000C00DEE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// schecd

class schecd : 
	public IDispatchImpl<Ischecd, &IID_Ischecd, &LIBID_TESTERLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<schecd,&CLSID_schecd>
{
public:
	schecd() {}
BEGIN_COM_MAP(schecd)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(Ischecd)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(schecd) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_schecd)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// Ischecd
public:
};

#endif // !defined(AFX_SCHECD_H__C4B368C2_4EA8_11D3_9DE7_0000C00DEE96__INCLUDED_)
