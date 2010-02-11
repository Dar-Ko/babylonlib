/*$RCSfile: KVariantToStr.cpp,v $: implementation file
  $Revision: 1.5 $ $Date: 2010/02/11 22:41:15 $
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

///////////////////////////////////////////////////////////////////////////////
// Variant access macros. See also: <OleAuto.h>

#ifndef V_ISBYREF
  //Returns true if VARIANT is a reference to an object
  #define V_ISBYREF(pvtVar)     ((pvtVar->pvtVar & VT_BYREF) == VT_BYREF)
#endif
#ifndef V_ISARRAY
  //Returns true if VARIANT is an array of objects
  #define V_ISARRAY(pvtVar)     ((pvtVar->pvtVar & VT_ARRAY) ==VT_ARRAY)
#endif
#ifndef V_ISVECTOR
  //Returns true if VARIANT is an vector of objects
  #define V_ISVECTOR(pvtVar)    ((pvtVar->pvtVar & VT_VECTOR) == VT_VECTOR)
#endif

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
  Microsoft COM Framework: _variant_t, comutil.h; V_ISARRAY(), OleAuto.h;
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

    case VT_CY: //currency 8 byte fixed point
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
        //TODO: copy str to the resulting BSTR
      #elif defined ( _OLEAUTO_H_ )
        //Note: Requiress Oleaut32.dll (for 32-bit systems) or Ole2disp.dll
        //(for 16-bit systems) 
         
        *ppszBuf = (LPWSTR)malloc((255 + 1) * sizeof(WCHAR));
        if (*ppszBuf != NULL)
          {
          (*ppszBuf)[255] = L'\0';
          lError = VarBstrFromDate((static_cast <VARIANT>(varIn)).date,
                                    LOCALE_USER_DEFAULT,
                                    VAR_FOURDIGITYEARS, //flags
                                    (BSTR*)*ppszBuf
                                   );
          ASSERT((*ppszBuf)[255] == L'\0'); //Check for the overflow
          }
      #else
        LPWSTR strTemp = L"ISO 1900-01-01T00:00:00";
        *ppszBuf = _wcsdup((LPCWSTR)strTemp);
      #endif
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
      #if !defined( _OLEAUTO_H_ )
        *ppszBuf = (LPWSTR)malloc((INT32_LEN + 1 + 1) * sizeof(wchar_t));
        if (*ppszBuf != NULL)
          {
          *ppszBuf[0] = L'H'; //Fix me
          lError = _itow_s((int)(int64_t)(varIn.pdispVal), ppszBuf[1], INT32_LEN + 1, 16);
          }
      #else
        *ppszBuf = (LPWSTR)malloc((255 + 1) * sizeof(WCHAR));
        if (*ppszBuf != NULL)
          {
          (*ppszBuf)[255] = L'\0';
          //Converts the default property of an IDispatch instance to a BSTR value.
          lError = VarBstrFromDisp((static_cast <VARIANT>(varIn)).pdispVal,
                                    LOCALE_USER_DEFAULT,
                                    0, //flags
                                    (BSTR*)*ppszBuf
                                   );
          ASSERT((*ppszBuf)[255] == L'\0'); //Check for the overflow
          }
      #endif
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

    case VT_VARIANT: //VARIANT*
      {
      *ppszBuf = (LPWSTR)malloc((INT32_LEN + 1 + 1) * sizeof(wchar_t));
      if (*ppszBuf != NULL)
        {
        *ppszBuf[0] = L'H'; //Fix me
        lError = _itow_s((int)(int64_t)(varIn.pvarVal), ppszBuf[1], INT32_LEN + 1, 16);
        }
      else
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_UNKNOWN: //IUnknown*
      {
      *ppszBuf = (LPWSTR)malloc((INT32_LEN + 1 + 1) * sizeof(wchar_t));
      if (*ppszBuf != NULL)
        {
        *ppszBuf[0] = L'H'; //Fix me
        lError = _itow_s((int)(int64_t)(varIn.ppunkVal), ppszBuf[1], INT32_LEN + 1, 16);
        }
      else
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_DECIMAL: //16 byte decimal number
      {
      *ppszBuf = (LPWSTR)malloc((DECIMAL_LEN + 1) * sizeof(WCHAR));
      if (*ppszBuf != NULL)
        {
        ASSERT(STRSAFE_MAX_CCH > (DECIMAL_LEN + 1));
        if ((varIn.decVal.Lo64 == 0) &&
            (varIn.decVal.Hi32 == 0) )
          {
          *ppszBuf[0] = L'0'; //Fix me
          *ppszBuf[1] = L'\0';
          }
        else
          {
          lError = VarBstrFromDec(&(static_cast <VARIANT>(varIn)).decVal,
                                  LOCALE_USER_DEFAULT,
                                  0, //flags
                                  (BSTR*)*ppszBuf
                                 );
          //TODO: requires 96bit integer 2 string conversion FixMe
//          lError = StringCbPrintfW(*ppszBuf, (DECIMAL_LEN +1) * sizeof(WCHAR), L"Fix me%d.%d%I64dE%d",
//                varIn.decVal.Hi32 / 100000 * (char)varIn.decVal.sign,
//                varIn.decVal.Hi32 % 100000,
//                (__int64)varIn.decVal.Hi32,
//                varIn.decVal.scale
//                ); //TODO: replace Win API
          }
        }
      break;
      }

    case VT_RECORD: //user defined type
      {
      *ppszBuf = _wcsdup(L"<VT_RECORD>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_I1: //signed char
      {
      *ppszBuf = _wcsdup(L"<VT_I1>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_UI1: //unsigned char
      {
      *ppszBuf = _wcsdup(L"<VT_UI1>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_UI2: //unsigned short
      {
      *ppszBuf = _wcsdup(L"<VT_UI2>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_UI4: //unsigned short
      {
      *ppszBuf = _wcsdup(L"<VT_UI4>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_I8: //signed 64-bit int
      {
      *ppszBuf = _wcsdup(L"<VT_I8>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_UI8: //unsigned 64-bit int
      {
      *ppszBuf = _wcsdup(L"<VT_UI8>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_INT: //signed machine int
      {
      *ppszBuf = _wcsdup(L"<VT_INT>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_UINT: //unsigned machine int
      {
      *ppszBuf = _wcsdup(L"<VT_UINT>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_VOID: //C style void
      {
      *ppszBuf = _wcsdup(L"<VT_VOID>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_HRESULT: //Standard return type
      {
      *ppszBuf = _wcsdup(L"<VT_HRESULT>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_PTR: //pointer type
      {
      *ppszBuf = _wcsdup(L"<VT_PTR>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_SAFEARRAY: //TYPEDESC array (use VT_ARRAY in VARIANT)
      {
      *ppszBuf = _wcsdup(L"<VT_SAFEARRAY>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_CARRAY: //C style array
      {
      *ppszBuf = _wcsdup(L"<VT_CARRAY>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_USERDEFINED: //user defined type
      {
      *ppszBuf = _wcsdup(L"<VT_USERDEFINED>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_LPSTR: //null terminated string
      {
      *ppszBuf = _wcsdup(L"<VT_LPSTR>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_LPWSTR: //wide null terminated string
      {
      *ppszBuf = _wcsdup(L"<VT_LPWSTR>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_FILETIME: //FILETIME
      {
      *ppszBuf = _wcsdup(L"<VT_FILETIME>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_BLOB: //Length prefixed bytes
      {
      *ppszBuf = _wcsdup(L"<VT_BLOB>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_STREAM: //Name of the stream follows
      {
      *ppszBuf = _wcsdup(L"<VT_STREAM>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_STORAGE: //Name of the storage follows
      {
      *ppszBuf = _wcsdup(L"<VT_STORAGE>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_STREAMED_OBJECT: //Stream contains an object
      {
      *ppszBuf = _wcsdup(L"<VT_STREAMED_OBJECT>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_STORED_OBJECT: //Storage contains an object
      {
      *ppszBuf = _wcsdup(L"<VT_STORED_OBJECT>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_BLOB_OBJECT: // Blob contains an object
      {
      *ppszBuf = _wcsdup(L"<VT_BLOB_OBJECT>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_CF: //Clipboard format
      {
      *ppszBuf = _wcsdup(L"<VT_CF>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_CLSID: // Class ID
      {
      *ppszBuf = _wcsdup(L"<VT_CLSID>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    case VT_VERSIONED_STREAM: //Stream with a GUID version
      {
      *ppszBuf = _wcsdup(L"<VT_VERSIONED_STREAM>");
      if (*ppszBuf == NULL)
        lError = ERROR_NOT_ENOUGH_MEMORY;
      break;
      }

    default:
      if(V_ISARRAY(&varIn))
        TRACE(_T("  V_ISARRAY\n"));
        //TODO;
      if(V_ISVECTOR(&varIn))
        TRACE(_T("  V_ISVECTOR\n"));
        //TODO;
      if(V_ISBYREF(&varIn))
        TRACE(_T("  V_ISBYREF\n"));
        //TODO;

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
 *Revision 1.5  2010/02/11 22:41:15  ddarko
 **** empty log message ***
 *
 *Revision 1.4  2010/02/10 22:28:23  ddarko
 *added DECIMAL number
 *
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
 *
 * VT_RECORD        struct __tagBRECORD
 *                    {
 *                    PVOID        pvRecord;
 *                    IRecordInfo* pRecInfo;
 *                    } __VARIANT_NAME_4;
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
 *      0 VT_EMPTY            [V]   [P]     nothing
 *      1 VT_NULL             [V]   [P]     SQL style Null
 *      2 VT_I2               [V][T][P][S]  2 byte signed int
 *      3 VT_I4               [V][T][P][S]  4 byte signed int
 *      4 VT_R4               [V][T][P][S]  4 byte real
 *      5 VT_R8               [V][T][P][S]  8 byte real
 *      6 VT_CY               [V][T][P][S]  currency
 *      7 VT_DATE             [V][T][P][S]  date
 *      8 VT_BSTR             [V][T][P][S]  OLE Automation string
 *      9 VT_DISPATCH         [V][T][P][S]  IDispatch *
 *     10 VT_ERROR            [V][T][P][S]  SCODE
 *     11 VT_BOOL             [V][T][P][S]  True=-1, False=0
 *     12 VT_VARIANT          [V][T][P][S]  VARIANT *
 *     13 VT_UNKNOWN          [V][T]   [S]  IUnknown *
 *     14 VT_DECIMAL          [V][T]   [S]  16 byte fixed point
 *        VT_RECORD           [V]   [P][S]  user defined type
 *     16 VT_I1               [V][T][P][s]  signed char
 *     17 VT_UI1              [V][T][P][S]  unsigned char
 *     18 VT_UI2              [V][T][P][S]  unsigned short
 *     19 VT_UI4              [V][T][P][S]  unsigned short
 *     20 VT_I8                  [T][P]     signed 64-bit int
 *     21 VT_UI8                 [T][P]     unsigned 64-bit int
 *     22 VT_INT              [V][T][P][S]  signed machine int
 *     23 VT_UINT             [V][T]   [S]  unsigned machine int
 *     24 VT_VOID                [T]        C style void
 *     25 VT_HRESULT             [T]        Standard return type
 *     26 VT_PTR                 [T]        pointer type
 *     27 VT_SAFEARRAY           [T]        (use VT_ARRAY in VARIANT)
 *     28 VT_CARRAY              [T]        C style array
 *     29 VT_USERDEFINED         [T]        user defined type
 *     30 VT_LPSTR               [T][P]     null terminated string
 *     31 VT_LPWSTR              [T][P]     wide null terminated string
 *     64 VT_FILETIME               [P]     FILETIME
 *     65 VT_BLOB                   [P]     Length prefixed bytes
 *     66 VT_STREAM                 [P]     Name of the stream follows
 *     67 VT_STORAGE                [P]     Name of the storage follows
 *     68 VT_STREAMED_OBJECT        [P]     Stream contains an object
 *     69 VT_STORED_OBJECT          [P]     Storage contains an object
 *     70 VT_BLOB_OBJECT            [P]     Blob contains an object
 *     71 VT_CF                     [P]     Clipboard format
 *     72 VT_CLSID                  [P]     A Class ID
 *        VT_VERSIONED_STREAM       [P]     Stream with a GUID version
 * 0x1000 VT_VECTOR                 [P]     simple counted array
 * 0x2000 VT_ARRAY            [V]           SAFEARRAY*
 * 0x4000 VT_BYREF            [V]           void* for local use
 * 0x8000 VT_RESERVED
 * 0xFFFF VT_ILLEGAL
 *        VT_BSTR_BLOB                      Reserved for system use
 * 0X0FFF VT_ILLEGALMASKED
 * 0X0FFF VT_TYPEMASK
 */