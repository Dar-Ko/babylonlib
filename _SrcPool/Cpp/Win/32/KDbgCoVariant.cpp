/*$Workfile: S:\_SrcPool\Cpp\Win\32\KDbgCoVariant.cpp$: implementation file
  $Revision: 5$ $Date: 2005-04-26 11:28:48$
  $Author: Darko Kolakovic$

  Dumps variant data type
  Copyright: CommonSoft Inc.
  2003-08 Darko Kolakovic
 */ 

// Group=Diagnostic
#include "stdafx.h"

//-----------------------------------------------------------------------------
/*Dumps VARIANT data type.
  A _variant_t object encapsulates the VARIANT data type. The class manages
  resource allocation and deallocation and makes function calls to VariantInit
  and VariantClear as appropriate.
  Requires comutil.h and  comsupp.lib.

  Note: uses Microsoft Foundation Library (MFC),
        Microsoft Windows specific (Win).
 */
void DumpComVariant(CDumpContext& dc, //[in] dump context
                    const VARIANT& comVariant //[in] variant data
                    )
{
CString strValue;
strValue = _T("Value = ");
WORD vt = comVariant.vt;

if(vt & VT_ARRAY)
  {
  vt = (WORD)(vt & ~VT_ARRAY);
  dc << _T("VT_ARRAY ");
  }

if(vt & VT_BYREF)
  {
  vt = (WORD)(vt & ~VT_BYREF);
  strValue += _T("& ");
  dc << _T("VT_BYREF ");
  }

switch(vt)
  {
  case VT_EMPTY:
    strValue += _T("(\"\"')");
    dc << _T("VT_EMPTY ")     << strValue;    break;
  case VT_NULL:
    strValue += _T("(null)");
    dc << _T("VT_NULL (null)") << strValue;    break;
  case VT_I2:
    strValue.Format(_T("Value =  %hd"),V_I2(&comVariant));
    dc << _T("VT_I2 ") << strValue;    break;
  case VT_I4:
    strValue.Format(_T("Value = %d"),V_I4(&comVariant));
    dc << _T("VT_I4 ") << strValue;    break;
  case VT_R4:
    strValue.Format(_T("Value = %e"),(double)V_R4(&comVariant));
    dc << _T("VT_R4 ") << strValue;    break;
  case VT_R8:
    strValue.Format(_T("Value = %e"),V_R8(&comVariant));
    dc << _T("VT_R8 ") << strValue;    break;
  case VT_CY:
    strValue += COleCurrency(comVariant).Format();
    dc << _T("VT_CY ") << strValue;    break;
  case VT_DATE:
    strValue += COleDateTime(comVariant).Format(_T("%Y-%m-%d"));
    dc << _T("VT_DATE ") << strValue;    break;
  case VT_BSTR:
    strValue += V_BSTR( &comVariant );
    dc << _T("VT_BSTR ") << strValue;
    break;
  case VT_DISPATCH:
    strValue += _T("TO DO:");     dc << _T("VT_DISPATCH ") << strValue;     break;
  case VT_ERROR:
    strValue += _T("TO DO:");     dc << _T("VT_ERROR ") << strValue;    break;
  case VT_BOOL:
    dc << _T("VT_I2 ") 
            << strValue 
            << (V_BOOL(&comVariant) ? _T("TRUE") : _T("FALSE"));
    return ;
  case VT_VARIANT:
    strValue += _T("TO DO:");    dc << _T("VT_VARIANT ") << strValue;    break;
  case VT_UNKNOWN:
    strValue += _T("TO DO:");    dc << _T("VT_UNKNOWN ") << strValue;    break;
  case VT_I1:
    strValue += _T("TO DO:");   dc << _T("VT_I1 ") << strValue;    break;
  case VT_UI1:
    strValue.Format(_T("Value = 0x%02hX"),(unsigned short)V_UI1(&comVariant));
    dc << _T("VT_UI1 ") << strValue;    break;
  case VT_UI2:
    strValue += _T("TO DO:");    dc << _T("VT_UI2 ") << strValue;    break;
  case VT_UI4:
    strValue += _T("TO DO:");    dc << _T("VT_UI4 ") << strValue;    break;
  case VT_I8:
    strValue += _T("TO DO:");    dc << _T("VT_I8 ") << strValue;    break;
  case VT_UI8:
    strValue += _T("TO DO:");    dc << _T("VT_UI8 ") << strValue;    break;
  case VT_INT:
    strValue += _T("TO DO:");    dc << _T("VT_INT ") << strValue;    break;
  case VT_UINT:
    strValue += _T("TO DO:");    dc << _T("VT_UINT ") << strValue;    break;
  case VT_VOID:
    strValue += _T("TO DO:");    dc << _T("VT_VOID ") << strValue;    break;
  case VT_HRESULT:
    strValue += _T("TO DO:");    dc << _T("VT_HRESULT ") << strValue;    break;
  case VT_PTR:
    strValue += _T("TO DO:");    dc << _T("VT_PTR ") << strValue;    break;
  case VT_SAFEARRAY:
    strValue += _T("TO DO:");    dc << _T("VT_SAFEARRAY ") << strValue;    break;
  case VT_CARRAY:
    strValue += _T("TO DO:");    dc << _T("VT_CARRAY ") << strValue;    break;
  case VT_USERDEFINED:
    strValue += _T("<user>");
    dc << _T("VT_USERDEFINED ") << strValue;    break;
  case VT_LPSTR:
    strValue += _T("TO DO:");    dc << _T("VT_LPSTR ") << strValue;    break;
  case VT_LPWSTR:
    strValue += _T("TO DO:");    dc << _T("VT_LPWSTR ") << strValue;    break;
  case VT_FILETIME:
    strValue += _T("TO DO:");    dc << _T("VT_FILETIME ") << strValue;    break;
  case VT_BLOB:
    strValue += _T("TO DO:");    dc << _T("VT_BLOB ") << strValue;    break;
  case VT_STREAM:
    strValue += _T("TO DO:");    dc << _T("VT_STREAM ") << strValue;    break;
  case VT_STORAGE:
    strValue += _T("TO DO:");    dc << _T("VT_STORAGE ") << strValue;    break;
  case VT_STREAMED_OBJECT:
    strValue += _T("TO DO:");    dc << _T("VT_STREAMED_OBJECT ") << strValue;    break;
  case VT_STORED_OBJECT:
    strValue += _T("TO DO:");    dc << _T("VT_STORED_OBJECT ") << strValue;    break;
  case VT_BLOB_OBJECT:
    strValue += _T("TO DO:");    dc << _T("VT_BLOB_OBJECT ") << strValue;    break;
  case VT_CF:
    strValue += _T("TO DO:");    dc << _T("VT_CF ") << strValue;    break;
  case VT_CLSID:
    strValue += _T("TO DO:");    dc << _T("VT_CLSID ") << strValue;    break;
  default:
    dc << _T("Unknown! ");
  }

dc << _T("\n");
}

//-----------------------------------------------------------------------------
/*Dumps variant data type of the COleVariant class.
  A COleVariant object encapsulates the VARIANT data type. This data type is 
  used in OLE automation.

  Note: uses Microsoft Foundation Library (MFC),
        Microsoft Windows specific (Win).
 */
void DumpComVariant(CDumpContext& dc, //[in] dump context
                    const COleVariant& comVariant //[in] variant data
                    )
{
DumpComVariant(dc, (VARIANT) comVariant);
}

//-----------------------------------------------------------------------------
#ifndef _INC_COMUTIL
  #include <comutil.h>  //_variant_t
#endif
/*Dumps variant data type of the _variant_t class.
  A _variant_t object encapsulates the VARIANT data type.

  Note: uses Microsoft Foundation Library (MFC),
        Microsoft Windows specific (Win).
 */
void DumpComVariant(CDumpContext& dc, //[in] dump context
                    const _variant_t& comVariant //[in] variant data
                    )
{
DumpComVariant(dc, (VARIANT) comVariant);
}

///////////////////////////////////////////////////////////////////////////////

/*The following definition of VARIANT is described in OAIDL.H automation
  header file:

    typedef struct tagVARIANT VARIANT;
    typedef struct tagVARIANT VARIANTARG;
    struct tagVARIANT
        {
        union 
            {
            struct __tagVARIANT
                {
                VARTYPE vt;
                WORD wReserved1;
                WORD wReserved2;
                WORD wReserved3;
                union 
                    {
                    LONGLONG llVal;
                    LONG lVal;
                    BYTE bVal;
                    SHORT iVal;
                    FLOAT fltVal;
                    DOUBLE dblVal;
                    VARIANT_BOOL boolVal;
                    _VARIANT_BOOL bool;
                    SCODE scode;
                    CY cyVal;
                    DATE date;
                    BSTR bstrVal;
                    IUnknown *punkVal;
                    IDispatch *pdispVal;
                    SAFEARRAY *parray;
                    BYTE *pbVal;
                    SHORT *piVal;
                    LONG *plVal;
                    LONGLONG *pllVal;
                    FLOAT *pfltVal;
                    DOUBLE *pdblVal;
                    VARIANT_BOOL *pboolVal;
                    _VARIANT_BOOL *pbool;
                    SCODE *pscode;
                    CY *pcyVal;
                    DATE *pdate;
                    BSTR *pbstrVal;
                    IUnknown **ppunkVal;
                    IDispatch **ppdispVal;
                    SAFEARRAY **pparray;
                    VARIANT *pvarVal;
                    PVOID byref;
                    CHAR cVal;
                    USHORT uiVal;
                    ULONG ulVal;
                    ULONGLONG ullVal;
                    INT intVal;
                    UINT uintVal;
                    DECIMAL *pdecVal;
                    CHAR *pcVal;
                    USHORT *puiVal;
                    ULONG *pulVal;
                    ULONGLONG *pullVal;
                    INT *pintVal;
                    UINT *puintVal;
                    struct __tagBRECORD
                        {
                        PVOID pvRecord;
                        IRecordInfo *pRecInfo;
                        }    __VARIANT_NAME_4;
                    }    __VARIANT_NAME_3;
                }    __VARIANT_NAME_2;
            DECIMAL decVal;
            }    __VARIANT_NAME_1;
    struct tagVARIANT  
      {
        union 
          {
          struct __tagVARIANT
          {
              VARTYPE vt;
              WORD wReserved1;
              WORD wReserved2;
              WORD wReserved3;
      union {
          LONGLONG                llval;             // VT_I8. 
          LONG                    lVal;              // VT_I4.
          BYTE                    bVal;              // VT_UI1.
          SHORT                   iVal;              // VT_I2.
          FLOAT                   fltVal;            // VT_R4.
          DOUBLE                  dblVal;            // VT_R8.
          VARIANT_BOOL            boolVal;           // VT_BOOL.
          _VARIANT_BOOL           bool;
          SCODE                   scode;             // VT_ERROR.
          CY                      cyVal;             // VT_CY.
          DATE                    date;              // VT_DATE.
          BSTR                    bstrVal;           // VT_BSTR.
          IUnknown                * punkVal;         // VT_UNKNOWN.
          IDispatch               * pdispVal;        // VT_DISPATCH.
          SAFEARRAY               * parray;          // VT_ARRAY|*.
          BYTE                    * pbVal;           // VT_BYREF|VT_UI1.
          SHORT                   * piVal;           // VT_BYREF|VT_I2.
          LONG                    * plVal;           // VT_BYREF|VT_I4.
          LONGLONG                * pllVal;          // VT_BYREF|VT_I8.
          FLOAT                   * pfltVal;         // VT_BYREF|VT_R4.
          DOUBLE                  * pdblVal;         // VT_BYREF|VT_R8.
          VARIANT_BOOL            * pboolVal;        // VT_BYREF|VT_BOOL.
          _VARIANT_BOOL           * pbool;
          SCODE                   * pscode;          // VT_BYREF|VT_ERROR.
          CY                      * pcyVal;          // VT_BYREF|VT_CY.
          DATE                    * pdate;           // VT_BYREF|VT_DATE.
          BSTR                    * pbstrVal;        // VT_BYREF|VT_BSTR.
          IUnknown                ** ppunkVal;       // VT_BYREF|VT_UNKNOWN.
          IDispatch               ** ppdispVal;      // VT_BYREF|VT_DISPATCH.
          SAFEARRAY               ** pparray;        // VT_ARRAY|*.
          VARIANT                 * pvarVal;         // VT_BYREF|VT_VARIANT.
          PVOID                   * byref;           // Generic ByRef.
          CHAR                    cVal;              // VT_I1.
          USHORT                  uiVal;             // VT_UI2.
          ULONG                   ulVal;             // VT_UI4.
          ULONGLONG               ullVal;            // VT_UI8.
          INT                     intVal;            // VT_INT.
          UINT                    uintVal;           // VT_UINT.
          DECIMAL                 * pdecVal          // VT_BYREF|VT_DECIMAL.
          CHAR                    * pcVal;           // VT_BYREF|VT_I1.
          USHORT                  * puiVal;          // VT_BYREF|VT_UI2.
          ULONG                   * pulVal;          // VT_BYREF|VT_UI4.
          ULONGLONG               * pullVal;         // VT_BYREF|VT_UI8.
          INT                     * pintVal;         // VT_BYREF|VT_INT.
          UINT                    * puintVal;        // VT_BYREF|VT_UINT.
          struct __tagBRECORD
          {
          PVOID                   pvRecord;
          IRecordInfo             *pRecInfo;
          }    __VARIANT_NAME_4;
      }    __VARIANT_NAME_3;
      }    __VARIANT_NAME_2;
      DECIMAL decVal;
    }    __VARIANT_NAME_1;

      };
    };
 
*/
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2005-04-26 11:28:48  Darko Kolakovic Document groups
 *       and typo fixes
 *  4    Biblioteka1.3         2003-09-22 22:25:52  Darko           formatting
 *  3    Biblioteka1.2         2003-08-17 02:11:41  Darko           fixed type cast
 *       warning
 *  2    Biblioteka1.1         2003-08-13 14:39:29  Darko           formatting
 *  1    Biblioteka1.0         2003-08-12 13:56:53  Darko           
 * $
 *****************************************************************************/
