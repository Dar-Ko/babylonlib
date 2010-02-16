/*$RCSfile: KDbgVariantType.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/02/16 22:22:39 $
  $Author: ddarko $

  Dumps the VARIANT data types.

  Copyright: babylonlib.sourceforge.net
  2010-02-04 Darko Kolakovic
 */

// Group=Diagnostic
#if defined(_WIN32)
  //Microsoft Windows OS
  #if defined _USE_ATL || defined _USE_MFC
    //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
    //or preprocessor reports unpaired #endif directive

    #include "stdafx.h" //Standard system header files

  #else
    #include <windows.h>
  #endif

  #if defined _ATL_VER
    #ifndef TRACE
      #define TRACE ATLTRACE
      #define TRACE1 ATLTRACE
      #define TRACE2 ATLTRACE
    #endif
  #endif
#endif //_WIN32

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


//-----------------------------------------------------------------------------
/*Dumps the VARIANT data types.
  Following types are used in various Microsoft data types:

           0 VT_EMPTY            [V]   [P]     nothing
           1 VT_NULL             [V]   [P]     SQL style Null
           2 VT_I2               [V][T][P][S]  2 byte signed int
           3 VT_I4               [V][T][P][S]  4 byte signed int
           4 VT_R4               [V][T][P][S]  4 byte real
           5 VT_R8               [V][T][P][S]  8 byte real
           6 VT_CY               [V][T][P][S]  currency
           7 VT_DATE             [V][T][P][S]  date
           8 VT_BSTR             [V][T][P][S]  OLE Automation string
           9 VT_DISPATCH         [V][T][P][S]  IDispatch *
          10 VT_ERROR            [V][T][P][S]  SCODE
          11 VT_BOOL             [V][T][P][S]  True=-1, False=0
          12 VT_VARIANT          [V][T][P][S]  VARIANT *
          13 VT_UNKNOWN          [V][T]   [S]  IUnknown *
          14 VT_DECIMAL          [V][T]   [S]  16 byte fixed point
          16 VT_I1               [V][T][P][s]  signed char
          17 VT_UI1              [V][T][P][S]  unsigned char
          18 VT_UI2              [V][T][P][S]  unsigned short
          19 VT_UI4              [V][T][P][S]  unsigned short
          20 VT_I8                  [T][P]     signed 64-bit int
          21 VT_UI8                 [T][P]     unsigned 64-bit int
          22 VT_INT              [V][T][P][S]  signed machine int
          23 VT_UINT             [V][T]   [S]  unsigned machine int
          24 VT_VOID                [T]        C style void
          25 VT_HRESULT             [T]        Standard return type (SCODE)
          26 VT_PTR                 [T]        pointer type
          27 VT_SAFEARRAY           [T]        (use VT_ARRAY in VARIANT)
         28 VT_CARRAY              [T]        C style array
          29 VT_USERDEFINED         [T]        user defined type
          30 VT_LPSTR               [T][P]     null terminated string
          31 VT_LPWSTR              [T][P]     wide null terminated string
          36 VT_RECORD           [V]   [P][S]  user defined type
          64 VT_FILETIME               [P]     FILETIME
          65 VT_BLOB                   [P]     Length prefixed bytes
          66 VT_STREAM                 [P]     Name of the stream follows
          67 VT_STORAGE                [P]     Name of the storage follows
          68 VT_STREAMED_OBJECT        [P]     Stream contains an object
          69 VT_STORED_OBJECT          [P]     Storage contains an object
          70 VT_BLOB_OBJECT            [P]     Blob contains an object
          71 VT_CF                     [P]     Clipboard format
          72 VT_CLSID                  [P]     A Class ID
          73 VT_VERSIONED_STREAM       [P]     Stream with a GUID version
      0x1000 VT_VECTOR                 [P]     simple counted array
      0x2000 VT_ARRAY            [V]           SAFEARRAY*
      0x4000 VT_BYREF            [V]           void* for local use
      0x8000 VT_RESERVED
      0xFFFF VT_ILLEGAL
             VT_BSTR_BLOB                      Reserved for system use
      0X0FFF VT_ILLEGALMASKED
      0X0FFF VT_TYPEMASK
      where
        [V] - is a VARIANT type
        [T] - is a TYPEDESC type
        [P] - is an OLE property set
        [S] - is a Safe Array

  Returns: zero-terminated string describing data type.

  See also: Microsoft Visual Studio header files wtypes.h, comutil.h, OAIdl.h.
 */
LPCTSTR DumpVariantType(VARIANT varData //[in] varinat data type
                       )
{
LPCTSTR szResult = NULL;
switch (varData.vt)
  {
  case  VT_EMPTY           : szResult = _T("VT_EMPTY");           break; // 0
  case  VT_NULL            : szResult = _T("VT_NULL");            break; // 1
  case  VT_I2              : szResult = _T("VT_I2");              break; // 2
  case  VT_I4              : szResult = _T("VT_I4");              break; // 3
  case  VT_R4              : szResult = _T("VT_R4");              break; // 4
  case  VT_R8              : szResult = _T("VT_R8");              break; // 5
  case  VT_CY              : szResult = _T("VT_CY");              break; // 6
  case  VT_DATE            : szResult = _T("VT_DATE");            break; // 7
  case  VT_BSTR            : szResult = _T("VT_BSTR");            break; // 8
  case  VT_DISPATCH        : szResult = _T("VT_DISPATCH");        break; // 9
  case  VT_ERROR           : szResult = _T("VT_ERROR");           break; //10
  case  VT_BOOL            : szResult = _T("VT_BOOL");            break; //11
  case  VT_VARIANT         : szResult = _T("VT_VARIANT");         break; //12
  case  VT_UNKNOWN         : szResult = _T("VT_UNKNOWN");         break; //13
  case  VT_DECIMAL         : szResult = _T("VT_DECIMAL");         break; //14
  case  VT_I1              : szResult = _T("VT_I1");              break; //16
  case  VT_UI1             : szResult = _T("VT_UI1");             break; //17
  case  VT_UI2             : szResult = _T("VT_UI2");             break; //18
  case  VT_UI4             : szResult = _T("VT_UI4");             break; //19
  case  VT_I8              : szResult = _T("VT_I8");              break; //20
  case  VT_UI8             : szResult = _T("VT_UI8");             break; //21
  case  VT_INT             : szResult = _T("VT_INT");             break; //22
  case  VT_UINT            : szResult = _T("VT_UINT");            break; //23
  case  VT_VOID            : szResult = _T("VT_VOID");            break; //24
  case  VT_HRESULT         : szResult = _T("VT_HRESULT");         break; //25
  case  VT_PTR             : szResult = _T("VT_PTR");             break; //26
  case  VT_SAFEARRAY       : szResult = _T("VT_SAFEARRAY");       break; //27
  case  VT_CARRAY          : szResult = _T("VT_CARRAY");          break; //28
  case  VT_USERDEFINED     : szResult = _T("VT_USERDEFINED");     break; //29
  case  VT_LPSTR           : szResult = _T("VT_LPSTR");           break; //30
  case  VT_LPWSTR          : szResult = _T("VT_LPWSTR");          break; //31
  case  VT_RECORD          : szResult = _T("VT_RECORD");          break; //36
  case  VT_FILETIME        : szResult = _T("VT_FILETIME");        break; //64
  case  VT_BLOB            : szResult = _T("VT_BLOB");            break; //65
  case  VT_STREAM          : szResult = _T("VT_STREAM");          break; //66
  case  VT_STORAGE         : szResult = _T("VT_STORAGE");         break; //67
  case  VT_STREAMED_OBJECT : szResult = _T("VT_STREAMED_OBJECT"); break; //68
  case  VT_STORED_OBJECT   : szResult = _T("VT_STORED_OBJECT");   break; //69
  case  VT_BLOB_OBJECT     : szResult = _T("VT_BLOB_OBJECT");     break; //70
  case  VT_CF              : szResult = _T("VT_CF");              break; //71
  case  VT_CLSID           : szResult = _T("VT_CLSID");           break; //72
  case  VT_VERSIONED_STREAM: szResult = _T("VT_VERSIONED_STREAM");break; //73
  case  VT_VECTOR          : szResult = _T("VT_VECTOR");          break; //0x1000
  case  VT_ARRAY           : szResult = _T("VT_ARRAY");           break; //0x2000
  case  VT_BYREF           : szResult = _T("VT_BYREF");           break; //0x4000
  case  VT_RESERVED        : szResult = _T("VT_RESERVED");        break; //0x8000
  case  VT_ILLEGAL         : szResult = _T("VT_ILLEGAL");         break; //0xFFFF
  case  VT_BSTR_BLOB       : szResult = _T("VT_BSTR_BLOB");       break; //

  default:
    {
    const int BUFF_SIZE = (19 + 3+  9 + 1);
    static TCHAR szResultEx[BUFF_SIZE];
    int i = 0;
    if(V_ISVECTOR(&varData))
      {
      szResult = _T("VT_VECTOR");
      varData.vt = varData.vt & ~VT_VECTOR;
      }
    else if(V_ISARRAY(&varData))
      {
      szResult = _T("VT_ARRAY");
      varData.vt = varData.vt & ~VT_ARRAY;
      }
    else if(V_ISBYREF(&varData))
      {
      szResult = _T("VT_BYREF");
      varData.vt = varData.vt & ~VT_BYREF;
      }
    else
      {
      TRACE1(_T("  VARIANT type 0x%0.8X\n"), varData.vt);
      szResult = _T("<unknown>");
      return szResult;
      }

    while( i < (BUFF_SIZE -1))
      {
      if (szResult[i] == _T('\0'))
        break;
      szResultEx[i] = szResult[i];
      i++;
      }
     szResultEx[i++] = _T(',');
     szResultEx[i++] = _T(' ');

    szResult = DumpVariantType(varData);
    while( i < (BUFF_SIZE -1))
      {
      szResultEx[i] = szResult[i];
      if (szResult[i] == _T('\0'))
        break;
      i++;
      }
    //Terminate string in the case of buffer overflow
    szResultEx[BUFF_SIZE -1] = _T('\0');
    szResult = szResultEx;
    }
  }
return szResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KDbgVariantType.cpp,v $
 * Revision 1.1  2010/02/16 22:22:39  ddarko
 * Created
 *
 *****************************************************************************/
