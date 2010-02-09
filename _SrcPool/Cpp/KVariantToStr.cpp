/*$RCSfile: KVariantToStr.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2010/02/09 22:28:44 $
  $Author: ddarko $

  Converts a variant value of a VARIANT structure to a string.
  Copyright: babylonlib.sourceforge.net
  2010-02-02 Darko Kolakovic
*/

/* Group=Strings                               */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)     */

#ifdef _MSC_VER //Microsoft C++ compiler
  #ifdef _UNICODE
    #ifndef UNICODE
      //To enable Unicode for some Microsoft Visual C/C++ header files,
      //the UNICODE definition is required
      #define UNICODE
    #endif
    #pragma message("Unicode literals")
  #endif

  /*Replace library header file names with the compiler's aliases*/
  #pragma include_alias("KTChar.h", "wtypes.h")
  #if _MSC_VER < 1300
    #pragma include_alias("KTrace.h", "trace.h")
  #endif
  #pragma include_alias(<stdint.h>, <KType32.h>)
#endif

#ifdef _WIN32
  #ifdef _USE_WINSEARCH
    /*Note: Requires Windows XP Service Pack 2 (SP2) with Windows Desktop Search (WDS) 3.0 or
      Windows Vista or Windows 7

      See also: Windows Search 4.0
      (http://www.microsoft.com/windows/products/winfamily/desktopsearch/default.mspx);
     */
    #include <propvarutil.h>
    #pragma comment(lib, "propsys")
  #else //~_USE_WINSEARCH
    #define _KVARINATTOSTRING 20100201 //Supplement Windows Desktop Search (WDS) SDK

    #include <OAIdl.h> //REFVARIANT typedef
    #ifndef _REFVARIANT_DEFINED
      //Note: REFVARINAT is defined in Windows 7 Platform SDK
      #define _REFVARIANT_DEFINED
      #ifdef __cplusplus
        #define REFVARIANT const VARIANT&
      #else
        #define REFVARIANT const VARIANT* const
      #endif
    #endif

  #include <atlstr.h> //CString used with VT_CY, VT_DATE; TODO native replacement
  #include <strsafe.h> //StringCbCopyW() See TODO
  #ifdef _USE_ATL
    #include <atlcur.h> //CComCurrency class
  #endif
  #pragma comment(lib, "strsafe")

  HRESULT VariantToStringAlloc(REFVARIANT varIn, PWSTR* ppszBuf);
  //extern HRESULT VariantToString(REFVARIANT varIn, PWSTR pszBuf, UINT cchBuf);
  #endif //~_USE_WINSEARCH
#else //Other than Windows 32b
  #define _KVARINATTOSTRING 20100202
#endif

///////////////////////////////////////////////////////////////////////////////
//Implementation
#ifdef _KVARINATTOSTRING

#include <stdint.h> //ISO C99 type definitions
#include "KTrace.h" /*ASSERT macro */
#include "KTChar.h" /*LPCTSTR typedef*/
#include "KStrLimits.h" //number representation limits

extern "C" long VariantToStringAlloc(const VARIANT* const varIn, wchar_t** ppszBuf);

//-----------------------------------------------------------------------------
/*Converts a variant value of a VARIANT structure to a string.
  If no value can be extracted, then an empty string is is assigned to the result.
  Resulting string is stored in a dynamically allocated buffer and it is caller's
  responsibility to free memory resource after usage by calling free().

  Returns: a pointer to zero-terminated string and the error code..

  See also: VARIANT, Windows Desktop Search (WDS) SDK: VariantToString,
  VariantToStringAlloc, propvarutil.h
  (http://msdn.microsoft.com/en-us/library/bb776617%28VS.85%29.aspx);
  Microsoft MFC Library: COleVariant; Microsoft ATL: CComVariant;
  Microsoft COM Framework: _variant_t, comutil.h;
 */
long VariantToStringAlloc(const VARIANT& varIn, //[in] variant data source.
                          LPWSTR* ppszBuf   //[out] pointer to converted
                          //property value if one exists or empty string if not.
                          )
{
long lError = S_OK;
int iValue = 0;
if (ppszBuf != NULL)
  {
  switch (varIn.vt)
    {
    case VT_EMPTY: //nothing
      {
      *ppszBuf = _wcsdup(L"<empty>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_NULL: //SQL style Null
      {
      *ppszBuf = _wcsdup(L"<null>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_I2: //2 byte signed int
      {
      *ppszBuf = (LPWSTR)malloc((INT16_LEN + 1) * sizeof(wchar_t));
      if (*ppszBuf != NULL)
        {
        lError = _itow_s((int16_t)varIn.iVal, *ppszBuf, INT16_LEN + 1, 10);
        }
      else
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_I4: //4 byte signed int
      {
      *ppszBuf = (LPWSTR)malloc((INT32_LEN + 1) * sizeof(wchar_t));
      if (*ppszBuf != NULL)
        {
        lError = _itow_s((int32_t)varIn.lVal, *ppszBuf, INT32_LEN + 1, 10);
        }
      else
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_R4: //4 byte real
      {
      *ppszBuf = (LPWSTR)malloc((REAL32_LEN +1) * sizeof(WCHAR));
      if (*ppszBuf != NULL)
        {
        ASSERT(STRSAFE_MAX_CCH > (REAL32_LEN +1));
        lError = StringCbPrintfW(*ppszBuf, (REAL32_LEN +1) * sizeof(WCHAR), L"%10.4f",
                       (float)varIn.fltVal); //TODO: replace Win API
        }
      break;
      }

    case VT_R8: //8 byte real
      {
      *ppszBuf = (LPWSTR)malloc((REAL64_LEN +1) * sizeof(WCHAR));
      if (*ppszBuf != NULL)
        {
        ASSERT(STRSAFE_MAX_CCH > (REAL64_LEN +1));
        lError = StringCbPrintfW(*ppszBuf, (REAL64_LEN +1) * sizeof(WCHAR), L"%10.4f",
                       (double)varIn.dblVal); //TODO: replace Win API
        }
      break;
      }

    case VT_CY: //currency
      {
      *ppszBuf = (LPWSTR)malloc((CURRENCY_LEN +1) * sizeof(WCHAR));
      if (*ppszBuf != NULL)
        {
        ASSERT(STRSAFE_MAX_CCH > (CURRENCY_LEN +1));
        if (varIn.cyVal.int64 != 0)
          lError = StringCbPrintfW(*ppszBuf, (CURRENCY_LEN +1) * sizeof(WCHAR), L"%I64d.%I64d",
                (__int64)varIn.cyVal.int64 / 10000, (__int64)varIn.cyVal.int64 % 10000 ); //TODO: replace Win API
        else
          {
          *ppszBuf[0] = L'0'; //Fix me
          *ppszBuf[1] = L'\0';
          }
        #ifdef _DEBUG
          #if defined( _USE_MFC )
            CString strDbg = COleCurrency(varIn.cyVal).Format();
            TRACE(strDbg);
          #enlif defined( _USE_ATL )
            CComCurrency cyTemp(varIn.cyVal);
            CAtlStringW strDbg;
            strDbg.Format("%I64d.%I64d", cyTemp.GetInteger(), cyTemp.GetFraction());
            TRACE(strDbg);
          #endif
        #endif
        }
      break;
      }

    case VT_DATE: //date
      {
      #if defined( _USE_MFC )
        CString strTemp = COleDateTime((DATE)varIn.date).Format( L"%Y-%m-%dT%H:%M:%S");
      #else
        LPWSTR strTemp = L"TODO ISO 1900-01-01T00:00:00";
      #endif
      *ppszBuf = _wcsdup((LPCWSTR)strTemp);
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_BSTR: //OLE Automation string
      {
      *ppszBuf = _wcsdup((LPWSTR)varIn.bstrVal);
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_DISPATCH: //IDispatch*
      {
      *ppszBuf = (LPWSTR)malloc((INT32_LEN + 1 + 1) * sizeof(wchar_t));
      if (*ppszBuf != NULL)
        {
        *ppszBuf[0] = L'H'; //Fix me
        lError = _itow_s((int32_t)(varIn.pdispVal), ppszBuf[1], INT32_LEN + 1, 16);
        }
      else
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_ERROR: //error code SCODE
      {
      *ppszBuf = (LPWSTR)malloc((INT32_LEN + 1) * sizeof(wchar_t));
      if (*ppszBuf != NULL)
        {
        lError = _itow_s((int32_t)varIn.scode, *ppszBuf, INT32_LEN + 1, 10);
        }
      else
        lError = ERROR_NOT_ENOUGH_MEMORY;

      #ifdef _DEBUG
        SCODE errDbg = varIn.scode;
        TRACE1(_T("  VT_ERROR error = 0x%8.0x"), errDbg);
      #endif

      break;
      }

     case VT_BOOL: //boolean as short int where true=-1 and false=0
      {
      *ppszBuf = (LPWSTR)malloc((1 + 1) * sizeof(wchar_t));
      if (*ppszBuf != NULL)
        {
        if (varIn.boolVal == 0)
          *ppszBuf[0] = L'0'; //Fix me
        else
          *ppszBuf[0] = L'1'; //Fix me
       *ppszBuf[1] = L'\0';
        }
      else
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_VARIANT: //VARIANT* pvarVal
      {
      if (varIn.pvarVal == NULL)
        {
        *ppszBuf = (LPWSTR)malloc((2 + 1) * sizeof(wchar_t));
        if (*ppszBuf != NULL)
          {
          *ppszBuf[0] = L'H'; //Fix me
          *ppszBuf[1] = L'0'; //Fix me
          *ppszBuf[2] = L'\0';
          }
        else
          lError = ERROR_NOT_ENOUGH_MEMORY;
        }
      else
        {
        const int SANITY_CHECK = 5;
        static int iSanity = 0;
        if (iSanity < SANITY_CHECK)
          {
          //Recursive loop up to SANITY_CHECK iterations
          iSanity++;
          lError = VariantToStringAlloc(*varIn.pvarVal, ppszBuf);
          }
        else
          {
          lError = ERROR_INVALID_DATA;
          }
        }

      break;
      }

    default:
      *ppszBuf = _wcsdup(L"<unknown>");
      lError = E_FAIL;
    }
  }
else
  {
  lError = E_INVALIDARG;
  }
return lError;
}

//-----------------------------------------------------------------------------
/*
 */
long VariantToStringAlloc(const VARIANT* const varIn, //[in] variant data source.
                          wchar_t** ppszBuf //[out] pointer to converted
                          //property value
                          )
{
if(ppszBuf != NULL)
  {
  if (varIn != NULL)
    {
    const VARIANT& varValue = *varIn;
    return VariantToStringAlloc(varValue, ppszBuf);
    }
  *ppszBuf = (wchar_t*)calloc(1, sizeof(wchar_t));
  }
return E_INVALIDARG;
}
/* ///////////////////////////////////////////////////////////////////////// */
#endif //_KVARINATTOSTRING
/******************************************************************************
 *$Log: KVariantToStr.cpp,v $
 *Revision 1.3  2010/02/09 22:28:44  ddarko
 **** empty log message ***
 *
 *Revision 1.2  2010/02/08 22:30:05  ddarko
 *added double precision
 *
 *Revision 1.1  2010/02/05 22:39:14  ddarko
 *Created
 *
 *****************************************************************************/

/* VARIANT STRUCTURE (OAIdl.h)
 *  {
 *  VARTYPE vt;
 *  WORD wReserved1;
 *  WORD wReserved2;
 *  WORD wReserved3;
 *  union {
 *    LONGLONG       VT_I8
 *    LONG           VT_I4
 *    BYTE           VT_UI1
 *    SHORT          VT_I2
 *    FLOAT          VT_R4
 *    DOUBLE         VT_R8
 *    VARIANT_BOOL   VT_BOOL
 *    SCODE          VT_ERROR
 *    CY             VT_CY
 *    DATE           VT_DATE
 *    BSTR           VT_BSTR
 *    IUnknown *     VT_UNKNOWN
 *    IDispatch *    VT_DISPATCH
 *    SAFEARRAY *    VT_ARRAY
 *    BYTE *         VT_BYREF|VT_UI1
 *    SHORT *        VT_BYREF|VT_I2
 *    LONG *         VT_BYREF|VT_I4
 *    LONGLONG *     VT_BYREF|VT_I8
 *    FLOAT *        VT_BYREF|VT_R4
 *    DOUBLE *       VT_BYREF|VT_R8
 *    VARIANT_BOOL * VT_BYREF|VT_BOOL
 *    SCODE *        VT_BYREF|VT_ERROR
 *    CY *           VT_BYREF|VT_CY
 *    DATE *         VT_BYREF|VT_DATE
 *    BSTR *         VT_BYREF|VT_BSTR
 *    IUnknown **    VT_BYREF|VT_UNKNOWN
 *    IDispatch **   VT_BYREF|VT_DISPATCH
 *    SAFEARRAY **   VT_BYREF|VT_ARRAY
 *    VARIANT *      VT_BYREF|VT_VARIANT
 *    PVOID          VT_BYREF (Generic ByRef)
 *    CHAR           VT_I1
 *    USHORT         VT_UI2
 *    ULONG          VT_UI4
 *    ULONGLONG      VT_UI8
 *    INT            VT_INT
 *    UINT           VT_UINT
 *    DECIMAL *      VT_BYREF|VT_DECIMAL
 *    CHAR *         VT_BYREF|VT_I1
 *    USHORT *       VT_BYREF|VT_UI2
 *    ULONG *        VT_BYREF|VT_UI4
 *    ULONGLONG *    VT_BYREF|VT_UI8
 *    INT *          VT_BYREF|VT_INT
 *    UINT *         VT_BYREF|VT_UINT
 *  }
 */


 /*
 * VARENUM usage key (wtypes.h), (comutil.h)
 *
 * * [V] - may appear in a VARIANT
 * * [T] - may appear in a TYPEDESC
 * * [P] - may appear in an OLE property set
 * * [S] - may appear in a Safe Array
 *
 *
 *  VT_EMPTY            [V]   [P]     nothing
 *  VT_NULL             [V]   [P]     SQL style Null
 *  VT_I2               [V][T][P][S]  2 byte signed int
 *  VT_I4               [V][T][P][S]  4 byte signed int
 *  VT_R4               [V][T][P][S]  4 byte real
 *  VT_R8               [V][T][P][S]  8 byte real
 *  VT_CY               [V][T][P][S]  currency
 *  VT_DATE             [V][T][P][S]  date
 *  VT_BSTR             [V][T][P][S]  OLE Automation string
 *  VT_DISPATCH         [V][T][P][S]  IDispatch *
 *  VT_ERROR            [V][T][P][S]  SCODE
 *  VT_BOOL             [V][T][P][S]  True=-1, False=0
 *  VT_VARIANT          [V][T][P][S]  VARIANT *
 *  VT_UNKNOWN          [V][T]   [S]  IUnknown *
 *  VT_DECIMAL          [V][T]   [S]  16 byte fixed point
 *  VT_RECORD           [V]   [P][S]  user defined type
 *  VT_I1               [V][T][P][s]  signed char
 *  VT_UI1              [V][T][P][S]  unsigned char
 *  VT_UI2              [V][T][P][S]  unsigned short
 *  VT_UI4              [V][T][P][S]  unsigned short
 *  VT_I8                  [T][P]     signed 64-bit int
 *  VT_UI8                 [T][P]     unsigned 64-bit int
 *  VT_INT              [V][T][P][S]  signed machine int
 *  VT_UINT             [V][T]   [S]  unsigned machine int
 *  VT_VOID                [T]        C style void
 *  VT_HRESULT             [T]        Standard return type
 *  VT_PTR                 [T]        pointer type
 *  VT_SAFEARRAY           [T]        (use VT_ARRAY in VARIANT)
 *  VT_CARRAY              [T]        C style array
 *  VT_USERDEFINED         [T]        user defined type
 *  VT_LPSTR               [T][P]     null terminated string
 *  VT_LPWSTR              [T][P]     wide null terminated string
 *  VT_FILETIME               [P]     FILETIME
 *  VT_BLOB                   [P]     Length prefixed bytes
 *  VT_STREAM                 [P]     Name of the stream follows
 *  VT_STORAGE                [P]     Name of the storage follows
 *  VT_STREAMED_OBJECT        [P]     Stream contains an object
 *  VT_STORED_OBJECT          [P]     Storage contains an object
 *  VT_VERSIONED_STREAM       [P]     Stream with a GUID version
 *  VT_BLOB_OBJECT            [P]     Blob contains an object
 *  VT_CF                     [P]     Clipboard format
 *  VT_CLSID                  [P]     A Class ID
 *  VT_VECTOR                 [P]     simple counted array
 *  VT_ARRAY            [V]           SAFEARRAY*
 *  VT_BYREF            [V]           void* for local use
 *  VT_BSTR_BLOB                      Reserved for system use
 */