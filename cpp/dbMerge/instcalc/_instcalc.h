

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sat Jul 22 21:30:02 2006
 */
/* Compiler settings for _instcalc.idl:
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___instcalc_h__
#define ___instcalc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAstInstCalc_FWD_DEFINED__
#define __IAstInstCalc_FWD_DEFINED__
typedef interface IAstInstCalc IAstInstCalc;
#endif 	/* __IAstInstCalc_FWD_DEFINED__ */


#ifndef __CAstInstCalc_FWD_DEFINED__
#define __CAstInstCalc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAstInstCalc CAstInstCalc;
#else
typedef struct CAstInstCalc CAstInstCalc;
#endif /* __cplusplus */

#endif 	/* __CAstInstCalc_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IAstInstCalc_INTERFACE_DEFINED__
#define __IAstInstCalc_INTERFACE_DEFINED__

/* interface IAstInstCalc */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAstInstCalc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE6B81CB-38A6-4171-B2F2-A1F47658EEE4")
    IAstInstCalc : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Index( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartAt( 
            /* [in] */ LONG month,
            /* [in] */ LONG day,
            /* [in] */ LONG year,
            /* [in] */ LONG hour) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAstInstCalcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAstInstCalc * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAstInstCalc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAstInstCalc * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAstInstCalc * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAstInstCalc * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAstInstCalc * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAstInstCalc * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IAstInstCalc * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Index )( 
            IAstInstCalc * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartAt )( 
            IAstInstCalc * This,
            /* [in] */ LONG month,
            /* [in] */ LONG day,
            /* [in] */ LONG year,
            /* [in] */ LONG hour);
        
        END_INTERFACE
    } IAstInstCalcVtbl;

    interface IAstInstCalc
    {
        CONST_VTBL struct IAstInstCalcVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAstInstCalc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAstInstCalc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAstInstCalc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAstInstCalc_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAstInstCalc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAstInstCalc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAstInstCalc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAstInstCalc_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define IAstInstCalc_put_Index(This,newVal)	\
    (This)->lpVtbl -> put_Index(This,newVal)

#define IAstInstCalc_StartAt(This,month,day,year,hour)	\
    (This)->lpVtbl -> StartAt(This,month,day,year,hour)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAstInstCalc_get_Value_Proxy( 
    IAstInstCalc * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IAstInstCalc_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAstInstCalc_put_Index_Proxy( 
    IAstInstCalc * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAstInstCalc_put_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAstInstCalc_StartAt_Proxy( 
    IAstInstCalc * This,
    /* [in] */ LONG month,
    /* [in] */ LONG day,
    /* [in] */ LONG year,
    /* [in] */ LONG hour);


void __RPC_STUB IAstInstCalc_StartAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAstInstCalc_INTERFACE_DEFINED__ */



#ifndef __instcalc_LIBRARY_DEFINED__
#define __instcalc_LIBRARY_DEFINED__

/* library instcalc */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_instcalc;

EXTERN_C const CLSID CLSID_CAstInstCalc;

#ifdef __cplusplus

class DECLSPEC_UUID("53F0DCB8-C083-4931-B261-2D15BE63035D")
CAstInstCalc;
#endif
#endif /* __instcalc_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


