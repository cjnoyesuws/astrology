

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_INumerowCalcer,0xB480AEC1,0x0F33,0x49B2,0xAF,0x97,0xC8,0x9D,0xBD,0x20,0x6D,0x32);


MIDL_DEFINE_GUID(IID, IID_ITextGetter,0x74EAD860,0x7971,0x4E4D,0xB7,0xCD,0x1C,0x9C,0x9F,0x96,0xB8,0x54);


MIDL_DEFINE_GUID(IID, LIBID_numerocalc,0x96EE2450,0x3081,0x450C,0xB9,0x9C,0x71,0x9A,0xB1,0xA7,0x84,0xF7);


MIDL_DEFINE_GUID(CLSID, CLSID_CNumerowCalcer,0xC2875FFB,0xF20C,0x46D6,0x87,0x01,0x3F,0xC4,0xE1,0xAC,0x2F,0xA2);


MIDL_DEFINE_GUID(CLSID, CLSID_CTextGetter,0x9654336F,0x86B5,0x4970,0x82,0x1A,0x4D,0xDF,0xDE,0x04,0xEB,0x0E);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

