

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Sep 05 23:15:08 2005
 */
/* Compiler settings for _numerocalc.idl:
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

#ifndef ___numerocalc_h__
#define ___numerocalc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __INumerowCalcer_FWD_DEFINED__
#define __INumerowCalcer_FWD_DEFINED__
typedef interface INumerowCalcer INumerowCalcer;
#endif 	/* __INumerowCalcer_FWD_DEFINED__ */


#ifndef __ITextGetter_FWD_DEFINED__
#define __ITextGetter_FWD_DEFINED__
typedef interface ITextGetter ITextGetter;
#endif 	/* __ITextGetter_FWD_DEFINED__ */


#ifndef __CNumerowCalcer_FWD_DEFINED__
#define __CNumerowCalcer_FWD_DEFINED__

#ifdef __cplusplus
typedef class CNumerowCalcer CNumerowCalcer;
#else
typedef struct CNumerowCalcer CNumerowCalcer;
#endif /* __cplusplus */

#endif 	/* __CNumerowCalcer_FWD_DEFINED__ */


#ifndef __CTextGetter_FWD_DEFINED__
#define __CTextGetter_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTextGetter CTextGetter;
#else
typedef struct CTextGetter CTextGetter;
#endif /* __cplusplus */

#endif 	/* __CTextGetter_FWD_DEFINED__ */


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

#ifndef __INumerowCalcer_INTERFACE_DEFINED__
#define __INumerowCalcer_INTERFACE_DEFINED__

/* interface INumerowCalcer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INumerowCalcer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B480AEC1-0F33-49B2-AF97-C89DBD206D32")
    INumerowCalcer : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Index( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FirstName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MiddleName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LastName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BirthDate( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CalcChart( 
            /* [in] */ CHAR *file,
            /* [in] */ CHAR *person,
            /* [in] */ CHAR *comments,
            /* [in] */ CHAR *type,
            /* [in] */ SHORT typecode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TransStart( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TransEnd( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FontName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FontSize( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FontCodes( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FontColor( 
            /* [in] */ ULONG newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeftMargin( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TextWidth( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DemoMode( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertFile( 
            /* [in] */ CHAR *in_name,
            /* [in] */ CHAR *out_name,
            /* [in] */ SHORT type) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INumerowCalcerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INumerowCalcer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INumerowCalcer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INumerowCalcer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            INumerowCalcer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            INumerowCalcer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            INumerowCalcer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            INumerowCalcer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Index )( 
            INumerowCalcer * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FirstName )( 
            INumerowCalcer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MiddleName )( 
            INumerowCalcer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LastName )( 
            INumerowCalcer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BirthDate )( 
            INumerowCalcer * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CalcChart )( 
            INumerowCalcer * This,
            /* [in] */ CHAR *file,
            /* [in] */ CHAR *person,
            /* [in] */ CHAR *comments,
            /* [in] */ CHAR *type,
            /* [in] */ SHORT typecode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransStart )( 
            INumerowCalcer * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransEnd )( 
            INumerowCalcer * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FontName )( 
            INumerowCalcer * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FontSize )( 
            INumerowCalcer * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FontCodes )( 
            INumerowCalcer * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FontColor )( 
            INumerowCalcer * This,
            /* [in] */ ULONG newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LeftMargin )( 
            INumerowCalcer * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextWidth )( 
            INumerowCalcer * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DemoMode )( 
            INumerowCalcer * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConvertFile )( 
            INumerowCalcer * This,
            /* [in] */ CHAR *in_name,
            /* [in] */ CHAR *out_name,
            /* [in] */ SHORT type);
        
        END_INTERFACE
    } INumerowCalcerVtbl;

    interface INumerowCalcer
    {
        CONST_VTBL struct INumerowCalcerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INumerowCalcer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INumerowCalcer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INumerowCalcer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INumerowCalcer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INumerowCalcer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INumerowCalcer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INumerowCalcer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INumerowCalcer_put_Index(This,newVal)	\
    (This)->lpVtbl -> put_Index(This,newVal)

#define INumerowCalcer_put_FirstName(This,newVal)	\
    (This)->lpVtbl -> put_FirstName(This,newVal)

#define INumerowCalcer_put_MiddleName(This,newVal)	\
    (This)->lpVtbl -> put_MiddleName(This,newVal)

#define INumerowCalcer_put_LastName(This,newVal)	\
    (This)->lpVtbl -> put_LastName(This,newVal)

#define INumerowCalcer_put_BirthDate(This,newVal)	\
    (This)->lpVtbl -> put_BirthDate(This,newVal)

#define INumerowCalcer_CalcChart(This,file,person,comments,type,typecode)	\
    (This)->lpVtbl -> CalcChart(This,file,person,comments,type,typecode)

#define INumerowCalcer_put_TransStart(This,newVal)	\
    (This)->lpVtbl -> put_TransStart(This,newVal)

#define INumerowCalcer_put_TransEnd(This,newVal)	\
    (This)->lpVtbl -> put_TransEnd(This,newVal)

#define INumerowCalcer_put_FontName(This,newVal)	\
    (This)->lpVtbl -> put_FontName(This,newVal)

#define INumerowCalcer_put_FontSize(This,newVal)	\
    (This)->lpVtbl -> put_FontSize(This,newVal)

#define INumerowCalcer_put_FontCodes(This,newVal)	\
    (This)->lpVtbl -> put_FontCodes(This,newVal)

#define INumerowCalcer_put_FontColor(This,newVal)	\
    (This)->lpVtbl -> put_FontColor(This,newVal)

#define INumerowCalcer_put_LeftMargin(This,newVal)	\
    (This)->lpVtbl -> put_LeftMargin(This,newVal)

#define INumerowCalcer_put_TextWidth(This,newVal)	\
    (This)->lpVtbl -> put_TextWidth(This,newVal)

#define INumerowCalcer_put_DemoMode(This,newVal)	\
    (This)->lpVtbl -> put_DemoMode(This,newVal)

#define INumerowCalcer_ConvertFile(This,in_name,out_name,type)	\
    (This)->lpVtbl -> ConvertFile(This,in_name,out_name,type)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_Index_Proxy( 
    INumerowCalcer * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB INumerowCalcer_put_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_FirstName_Proxy( 
    INumerowCalcer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INumerowCalcer_put_FirstName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_MiddleName_Proxy( 
    INumerowCalcer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INumerowCalcer_put_MiddleName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_LastName_Proxy( 
    INumerowCalcer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INumerowCalcer_put_LastName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_BirthDate_Proxy( 
    INumerowCalcer * This,
    /* [in] */ DATE newVal);


void __RPC_STUB INumerowCalcer_put_BirthDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_CalcChart_Proxy( 
    INumerowCalcer * This,
    /* [in] */ CHAR *file,
    /* [in] */ CHAR *person,
    /* [in] */ CHAR *comments,
    /* [in] */ CHAR *type,
    /* [in] */ SHORT typecode);


void __RPC_STUB INumerowCalcer_CalcChart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_TransStart_Proxy( 
    INumerowCalcer * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB INumerowCalcer_put_TransStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_TransEnd_Proxy( 
    INumerowCalcer * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB INumerowCalcer_put_TransEnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_FontName_Proxy( 
    INumerowCalcer * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INumerowCalcer_put_FontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_FontSize_Proxy( 
    INumerowCalcer * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB INumerowCalcer_put_FontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_FontCodes_Proxy( 
    INumerowCalcer * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB INumerowCalcer_put_FontCodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_FontColor_Proxy( 
    INumerowCalcer * This,
    /* [in] */ ULONG newVal);


void __RPC_STUB INumerowCalcer_put_FontColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_LeftMargin_Proxy( 
    INumerowCalcer * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB INumerowCalcer_put_LeftMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_TextWidth_Proxy( 
    INumerowCalcer * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB INumerowCalcer_put_TextWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_put_DemoMode_Proxy( 
    INumerowCalcer * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB INumerowCalcer_put_DemoMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INumerowCalcer_ConvertFile_Proxy( 
    INumerowCalcer * This,
    /* [in] */ CHAR *in_name,
    /* [in] */ CHAR *out_name,
    /* [in] */ SHORT type);


void __RPC_STUB INumerowCalcer_ConvertFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INumerowCalcer_INTERFACE_DEFINED__ */


#ifndef __ITextGetter_INTERFACE_DEFINED__
#define __ITextGetter_INTERFACE_DEFINED__

/* interface ITextGetter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITextGetter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74EAD860-7971-4E4D-B7CD-1C9C9F96B854")
    ITextGetter : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Row( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Col( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextGetterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextGetter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextGetter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextGetter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITextGetter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITextGetter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITextGetter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITextGetter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Row )( 
            ITextGetter * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Col )( 
            ITextGetter * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            ITextGetter * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ITextGetterVtbl;

    interface ITextGetter
    {
        CONST_VTBL struct ITextGetterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextGetter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextGetter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextGetter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextGetter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITextGetter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITextGetter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITextGetter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITextGetter_put_Row(This,newVal)	\
    (This)->lpVtbl -> put_Row(This,newVal)

#define ITextGetter_put_Col(This,newVal)	\
    (This)->lpVtbl -> put_Col(This,newVal)

#define ITextGetter_get_Text(This,pVal)	\
    (This)->lpVtbl -> get_Text(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextGetter_put_Row_Proxy( 
    ITextGetter * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB ITextGetter_put_Row_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITextGetter_put_Col_Proxy( 
    ITextGetter * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB ITextGetter_put_Col_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextGetter_get_Text_Proxy( 
    ITextGetter * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITextGetter_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextGetter_INTERFACE_DEFINED__ */



#ifndef __numerocalc_LIBRARY_DEFINED__
#define __numerocalc_LIBRARY_DEFINED__

/* library numerocalc */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_numerocalc;

EXTERN_C const CLSID CLSID_CNumerowCalcer;

#ifdef __cplusplus

class DECLSPEC_UUID("C2875FFB-F20C-46D6-8701-3FC4E1AC2FA2")
CNumerowCalcer;
#endif

EXTERN_C const CLSID CLSID_CTextGetter;

#ifdef __cplusplus

class DECLSPEC_UUID("9654336F-86B5-4970-821A-4DDFDE04EB0E")
CTextGetter;
#endif
#endif /* __numerocalc_LIBRARY_DEFINED__ */

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


