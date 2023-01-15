

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Fri Jan 21 23:30:57 2005
 */
/* Compiler settings for .\TabCtrl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __TabCtrlidl_h__
#define __TabCtrlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DTabCtrl_FWD_DEFINED__
#define ___DTabCtrl_FWD_DEFINED__
typedef interface _DTabCtrl _DTabCtrl;
#endif 	/* ___DTabCtrl_FWD_DEFINED__ */


#ifndef ___DTabCtrlEvents_FWD_DEFINED__
#define ___DTabCtrlEvents_FWD_DEFINED__
typedef interface _DTabCtrlEvents _DTabCtrlEvents;
#endif 	/* ___DTabCtrlEvents_FWD_DEFINED__ */


#ifndef __TabCtrl_FWD_DEFINED__
#define __TabCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TabCtrl TabCtrl;
#else
typedef struct TabCtrl TabCtrl;
#endif /* __cplusplus */

#endif 	/* __TabCtrl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __TabCtrlLib_LIBRARY_DEFINED__
#define __TabCtrlLib_LIBRARY_DEFINED__

/* library TabCtrlLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_TabCtrlLib;

#ifndef ___DTabCtrl_DISPINTERFACE_DEFINED__
#define ___DTabCtrl_DISPINTERFACE_DEFINED__

/* dispinterface _DTabCtrl */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DTabCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D1F60DF7-733E-4C91-8643-7A0C49B3ABE6")
    _DTabCtrl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DTabCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DTabCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DTabCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DTabCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DTabCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DTabCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DTabCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DTabCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DTabCtrlVtbl;

    interface _DTabCtrl
    {
        CONST_VTBL struct _DTabCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DTabCtrl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DTabCtrl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DTabCtrl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DTabCtrl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DTabCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DTabCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DTabCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DTabCtrl_DISPINTERFACE_DEFINED__ */


#ifndef ___DTabCtrlEvents_DISPINTERFACE_DEFINED__
#define ___DTabCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DTabCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DTabCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11CFF31B-719B-440F-9363-7DFD7CD822BD")
    _DTabCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DTabCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DTabCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DTabCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DTabCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DTabCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DTabCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DTabCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DTabCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DTabCtrlEventsVtbl;

    interface _DTabCtrlEvents
    {
        CONST_VTBL struct _DTabCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DTabCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DTabCtrlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DTabCtrlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DTabCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DTabCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DTabCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DTabCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DTabCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TabCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("5230206E-3E6A-454C-9999-EADA11AE4F32")
TabCtrl;
#endif
#endif /* __TabCtrlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


