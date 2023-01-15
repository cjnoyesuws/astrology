

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sat Oct 27 14:32:12 2007
 */
/* Compiler settings for _biocalc.idl:
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

#ifndef ___biocalc_h__
#define ___biocalc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBioDataCalc_FWD_DEFINED__
#define __IBioDataCalc_FWD_DEFINED__
typedef interface IBioDataCalc IBioDataCalc;
#endif 	/* __IBioDataCalc_FWD_DEFINED__ */


#ifndef __CBioDataCalc_FWD_DEFINED__
#define __CBioDataCalc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CBioDataCalc CBioDataCalc;
#else
typedef struct CBioDataCalc CBioDataCalc;
#endif /* __cplusplus */

#endif 	/* __CBioDataCalc_FWD_DEFINED__ */


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

#ifndef __IBioDataCalc_INTERFACE_DEFINED__
#define __IBioDataCalc_INTERFACE_DEFINED__

/* interface IBioDataCalc */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBioDataCalc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("18B41BCD-EA9C-48FD-B6BC-EE8C411C4073")
    IBioDataCalc : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PersName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BirthDate( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartDate( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Index( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Physical( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Emotional( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Intellectual( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmotionalDesc( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PhysicalDesc( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IntellectualDesc( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Calc( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveData( 
            /* [in] */ BSTR file) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadData( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Export( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Days( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Critical( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CriticalDesc( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PersName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BirthDate( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartDate( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CSS( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CSS( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBioDataCalcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBioDataCalc * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBioDataCalc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBioDataCalc * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBioDataCalc * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBioDataCalc * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBioDataCalc * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBioDataCalc * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PersName )( 
            IBioDataCalc * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BirthDate )( 
            IBioDataCalc * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartDate )( 
            IBioDataCalc * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Index )( 
            IBioDataCalc * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Physical )( 
            IBioDataCalc * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Emotional )( 
            IBioDataCalc * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Intellectual )( 
            IBioDataCalc * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EmotionalDesc )( 
            IBioDataCalc * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PhysicalDesc )( 
            IBioDataCalc * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IntellectualDesc )( 
            IBioDataCalc * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Calc )( 
            IBioDataCalc * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveData )( 
            IBioDataCalc * This,
            /* [in] */ BSTR file);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadData )( 
            IBioDataCalc * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Export )( 
            IBioDataCalc * This,
            /* [in] */ BSTR name);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Days )( 
            IBioDataCalc * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Critical )( 
            IBioDataCalc * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CriticalDesc )( 
            IBioDataCalc * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PersName )( 
            IBioDataCalc * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BirthDate )( 
            IBioDataCalc * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartDate )( 
            IBioDataCalc * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CSS )( 
            IBioDataCalc * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CSS )( 
            IBioDataCalc * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IBioDataCalcVtbl;

    interface IBioDataCalc
    {
        CONST_VTBL struct IBioDataCalcVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBioDataCalc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBioDataCalc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBioDataCalc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBioDataCalc_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBioDataCalc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBioDataCalc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBioDataCalc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBioDataCalc_put_PersName(This,newVal)	\
    (This)->lpVtbl -> put_PersName(This,newVal)

#define IBioDataCalc_put_BirthDate(This,newVal)	\
    (This)->lpVtbl -> put_BirthDate(This,newVal)

#define IBioDataCalc_put_StartDate(This,newVal)	\
    (This)->lpVtbl -> put_StartDate(This,newVal)

#define IBioDataCalc_put_Index(This,newVal)	\
    (This)->lpVtbl -> put_Index(This,newVal)

#define IBioDataCalc_get_Physical(This,pVal)	\
    (This)->lpVtbl -> get_Physical(This,pVal)

#define IBioDataCalc_get_Emotional(This,pVal)	\
    (This)->lpVtbl -> get_Emotional(This,pVal)

#define IBioDataCalc_get_Intellectual(This,pVal)	\
    (This)->lpVtbl -> get_Intellectual(This,pVal)

#define IBioDataCalc_get_EmotionalDesc(This,pVal)	\
    (This)->lpVtbl -> get_EmotionalDesc(This,pVal)

#define IBioDataCalc_get_PhysicalDesc(This,pVal)	\
    (This)->lpVtbl -> get_PhysicalDesc(This,pVal)

#define IBioDataCalc_get_IntellectualDesc(This,pVal)	\
    (This)->lpVtbl -> get_IntellectualDesc(This,pVal)

#define IBioDataCalc_Calc(This)	\
    (This)->lpVtbl -> Calc(This)

#define IBioDataCalc_SaveData(This,file)	\
    (This)->lpVtbl -> SaveData(This,file)

#define IBioDataCalc_LoadData(This,name)	\
    (This)->lpVtbl -> LoadData(This,name)

#define IBioDataCalc_Export(This,name)	\
    (This)->lpVtbl -> Export(This,name)

#define IBioDataCalc_get_Days(This,pVal)	\
    (This)->lpVtbl -> get_Days(This,pVal)

#define IBioDataCalc_get_Critical(This,pVal)	\
    (This)->lpVtbl -> get_Critical(This,pVal)

#define IBioDataCalc_get_CriticalDesc(This,pVal)	\
    (This)->lpVtbl -> get_CriticalDesc(This,pVal)

#define IBioDataCalc_get_PersName(This,pVal)	\
    (This)->lpVtbl -> get_PersName(This,pVal)

#define IBioDataCalc_get_BirthDate(This,pVal)	\
    (This)->lpVtbl -> get_BirthDate(This,pVal)

#define IBioDataCalc_get_StartDate(This,pVal)	\
    (This)->lpVtbl -> get_StartDate(This,pVal)

#define IBioDataCalc_get_CSS(This,pVal)	\
    (This)->lpVtbl -> get_CSS(This,pVal)

#define IBioDataCalc_put_CSS(This,newVal)	\
    (This)->lpVtbl -> put_CSS(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_put_PersName_Proxy( 
    IBioDataCalc * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBioDataCalc_put_PersName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_put_BirthDate_Proxy( 
    IBioDataCalc * This,
    /* [in] */ DATE newVal);


void __RPC_STUB IBioDataCalc_put_BirthDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_put_StartDate_Proxy( 
    IBioDataCalc * This,
    /* [in] */ DATE newVal);


void __RPC_STUB IBioDataCalc_put_StartDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_put_Index_Proxy( 
    IBioDataCalc * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB IBioDataCalc_put_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_Physical_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IBioDataCalc_get_Physical_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_Emotional_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IBioDataCalc_get_Emotional_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_Intellectual_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IBioDataCalc_get_Intellectual_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_EmotionalDesc_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IBioDataCalc_get_EmotionalDesc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_PhysicalDesc_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IBioDataCalc_get_PhysicalDesc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_IntellectualDesc_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IBioDataCalc_get_IntellectualDesc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_Calc_Proxy( 
    IBioDataCalc * This);


void __RPC_STUB IBioDataCalc_Calc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_SaveData_Proxy( 
    IBioDataCalc * This,
    /* [in] */ BSTR file);


void __RPC_STUB IBioDataCalc_SaveData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_LoadData_Proxy( 
    IBioDataCalc * This,
    /* [in] */ BSTR name);


void __RPC_STUB IBioDataCalc_LoadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_Export_Proxy( 
    IBioDataCalc * This,
    /* [in] */ BSTR name);


void __RPC_STUB IBioDataCalc_Export_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_Days_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ SHORT *pVal);


void __RPC_STUB IBioDataCalc_get_Days_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_Critical_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IBioDataCalc_get_Critical_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_CriticalDesc_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IBioDataCalc_get_CriticalDesc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_PersName_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IBioDataCalc_get_PersName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_BirthDate_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB IBioDataCalc_get_BirthDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_StartDate_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB IBioDataCalc_get_StartDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_get_CSS_Proxy( 
    IBioDataCalc * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IBioDataCalc_get_CSS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IBioDataCalc_put_CSS_Proxy( 
    IBioDataCalc * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IBioDataCalc_put_CSS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBioDataCalc_INTERFACE_DEFINED__ */



#ifndef __biocalc_LIBRARY_DEFINED__
#define __biocalc_LIBRARY_DEFINED__

/* library biocalc */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_biocalc;

EXTERN_C const CLSID CLSID_CBioDataCalc;

#ifdef __cplusplus

class DECLSPEC_UUID("37A3EB90-807D-4CA1-921D-BCAC087ED99C")
CBioDataCalc;
#endif
#endif /* __biocalc_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


