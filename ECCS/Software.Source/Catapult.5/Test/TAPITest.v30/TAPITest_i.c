
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Feb 06 16:52:35 2002
 */
/* Compiler settings for C:\Working_Area\TestArea\C++\TAPITest\TAPITest.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

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

MIDL_DEFINE_GUID(IID, IID_IMainTAPICtr,0xD294F373,0x4AB3,0x42D6,0x85,0x11,0xA8,0xA5,0x47,0x64,0xD6,0xC4);


MIDL_DEFINE_GUID(IID, LIBID_TAPITESTLib,0xBE9560D1,0x23CE,0x4FD3,0xB3,0xF2,0xA4,0x67,0x5E,0xF4,0x91,0x2F);


MIDL_DEFINE_GUID(IID, DIID__IMainTAPICtrEvents,0xBDF1241C,0x0000,0x4D1A,0xA5,0x74,0x09,0x86,0x0A,0x83,0x5B,0x67);


MIDL_DEFINE_GUID(CLSID, CLSID_MainTAPICtr,0x076DC055,0xEF11,0x4F58,0x85,0xA9,0x7F,0x69,0x35,0xB9,0xC9,0x16);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Feb 06 16:52:35 2002
 */
/* Compiler settings for C:\Working_Area\TestArea\C++\TAPITest\TAPITest.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)

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

MIDL_DEFINE_GUID(IID, IID_IMainTAPICtr,0xD294F373,0x4AB3,0x42D6,0x85,0x11,0xA8,0xA5,0x47,0x64,0xD6,0xC4);


MIDL_DEFINE_GUID(IID, LIBID_TAPITESTLib,0xBE9560D1,0x23CE,0x4FD3,0xB3,0xF2,0xA4,0x67,0x5E,0xF4,0x91,0x2F);


MIDL_DEFINE_GUID(IID, DIID__IMainTAPICtrEvents,0xBDF1241C,0x0000,0x4D1A,0xA5,0x74,0x09,0x86,0x0A,0x83,0x5B,0x67);


MIDL_DEFINE_GUID(CLSID, CLSID_MainTAPICtr,0x076DC055,0xEF11,0x4F58,0x85,0xA9,0x7F,0x69,0x35,0xB9,0xC9,0x16);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

