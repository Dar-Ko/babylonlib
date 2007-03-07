
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __TAPITest_h__
#define __TAPITest_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMainTAPICtr_FWD_DEFINED__
#define __IMainTAPICtr_FWD_DEFINED__
typedef interface IMainTAPICtr IMainTAPICtr;
#endif 	/* __IMainTAPICtr_FWD_DEFINED__ */


#ifndef ___IMainTAPICtrEvents_FWD_DEFINED__
#define ___IMainTAPICtrEvents_FWD_DEFINED__
typedef interface _IMainTAPICtrEvents _IMainTAPICtrEvents;
#endif 	/* ___IMainTAPICtrEvents_FWD_DEFINED__ */


#ifndef __MainTAPICtr_FWD_DEFINED__
#define __MainTAPICtr_FWD_DEFINED__

#ifdef __cplusplus
typedef class MainTAPICtr MainTAPICtr;
#else
typedef struct MainTAPICtr MainTAPICtr;
#endif /* __cplusplus */

#endif 	/* __MainTAPICtr_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMainTAPICtr_INTERFACE_DEFINED__
#define __IMainTAPICtr_INTERFACE_DEFINED__

/* interface IMainTAPICtr */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMainTAPICtr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D294F373-4AB3-42D6-8511-A8A54764D6C4")
    IMainTAPICtr : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChooseModem( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MyMakeCall( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMainTAPICtrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMainTAPICtr * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMainTAPICtr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMainTAPICtr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMainTAPICtr * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMainTAPICtr * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMainTAPICtr * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMainTAPICtr * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChooseModem )( 
            IMainTAPICtr * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MyMakeCall )( 
            IMainTAPICtr * This);
        
        END_INTERFACE
    } IMainTAPICtrVtbl;

    interface IMainTAPICtr
    {
        CONST_VTBL struct IMainTAPICtrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMainTAPICtr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMainTAPICtr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMainTAPICtr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMainTAPICtr_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMainTAPICtr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMainTAPICtr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMainTAPICtr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMainTAPICtr_ChooseModem(This)	\
    (This)->lpVtbl -> ChooseModem(This)

#define IMainTAPICtr_MyMakeCall(This)	\
    (This)->lpVtbl -> MyMakeCall(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMainTAPICtr_ChooseModem_Proxy( 
    IMainTAPICtr * This);


void __RPC_STUB IMainTAPICtr_ChooseModem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMainTAPICtr_MyMakeCall_Proxy( 
    IMainTAPICtr * This);


void __RPC_STUB IMainTAPICtr_MyMakeCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMainTAPICtr_INTERFACE_DEFINED__ */



#ifndef __TAPITESTLib_LIBRARY_DEFINED__
#define __TAPITESTLib_LIBRARY_DEFINED__

/* library TAPITESTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TAPITESTLib;

#ifndef ___IMainTAPICtrEvents_DISPINTERFACE_DEFINED__
#define ___IMainTAPICtrEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IMainTAPICtrEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IMainTAPICtrEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BDF1241C-0000-4D1A-A574-09860A835B67")
    _IMainTAPICtrEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IMainTAPICtrEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IMainTAPICtrEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IMainTAPICtrEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IMainTAPICtrEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IMainTAPICtrEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IMainTAPICtrEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IMainTAPICtrEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IMainTAPICtrEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IMainTAPICtrEventsVtbl;

    interface _IMainTAPICtrEvents
    {
        CONST_VTBL struct _IMainTAPICtrEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IMainTAPICtrEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IMainTAPICtrEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IMainTAPICtrEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IMainTAPICtrEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IMainTAPICtrEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IMainTAPICtrEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IMainTAPICtrEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IMainTAPICtrEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MainTAPICtr;

#ifdef __cplusplus

class DECLSPEC_UUID("076DC055-EF11-4F58-85A9-7F6935B9C916")
MainTAPICtr;
#endif
#endif /* __TAPITESTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


