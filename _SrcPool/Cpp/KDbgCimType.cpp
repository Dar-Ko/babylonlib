/*$RCSfile: KDbgCimType.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/02/04 23:31:29 $
  $Author: ddarko $

  Dumps the Common Information Model (CIM) data types.

  Copyright: babylonlib.sourceforge.net
  2010-02-02 Darko Kolakovic
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
  #if (WINVER > 0x040A)
    //Note: minimum requirement is Microsoft Windows 2000
    #include <wbemidl.h> //Web-based Enterprise Management (WBEM)
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
/*Dumps the Common Information Model (CIM) property data types.
  CIM property data types are limited to the intrinsic data types or arrays of
  such:
      - CIM_SINT8           8-bit signed integer.
      - CIM_UINT8           8-bit unsigned integer.
      - CIM_SINT16          16-bit signed integer.
      - CIM_UINT16          16-bit unsigned integer.
      - CIM_SINT32          32-bit signed integer.
      - CIM_UINT32          32-bit unsigned integer.
      - CIM_SINT64          64-bit signed integer.
      - CIM_UINT64          64-bit unsigned integer.
      - CIM_REAL32          32-bit real number.
      - CIM_REAL64          64-bit real number.
      - CIM_STRING          UCS-2 string value.
      - CIM_BOOLEAN         boolean value.
      - CIM_DATETIME        fixed length string containing a date and time (yyyymmddhhmmss.mmmmmmsutc)
      - CIM_REFERENCE       reference of another Object.
      - CIM_CHAR16          16-bit UCS-2 character value.
      - CIM_OBJECT          object value.
      - CIM_EMPTY           empty (null) value.
      - CIM_ILLEGAL         illegal value.
      - CIM_FLAG_ARRAY      an array value.

  Returns: zero-terminated string describing data type.

  See also: Common Information Model (CIM) Specification Version 2.2 by
  Distributed Management Task Force, Inc; 2.2 Property Data Types
  (http://www.dmtf.org/standards/cim/cim_spec_v22).
 */
LPCTSTR DumpCimType(CIMTYPE iData //[in] CIM property data type
                      )
{
LPCTSTR szResult = NULL;
switch (iData)
  {
  case CIM_EMPTY     : szResult = _T("CIM_EMPTY");      break; //    0  empty (null) value
  case CIM_SINT16    : szResult = _T("CIM_SINT16");     break; //    2
  case CIM_SINT32    : szResult = _T("CIM_SINT32");     break; //    3
  case CIM_REAL32    : szResult = _T("CIM_REAL32");     break; //    4
  case CIM_REAL64    : szResult = _T("CIM_REAL64");     break; //    5
  case CIM_STRING    : szResult = _T("CIM_STRING");     break; //    8
  case CIM_BOOLEAN   : szResult = _T("CIM_BOOLEAN ");   break; //   11
  case CIM_OBJECT    : szResult = _T("CIM_OBJECT");     break; //   13
  case CIM_SINT8     : szResult = _T("CIM_SINT8");      break; //   16
  case CIM_UINT8     : szResult = _T("CIM_UINT8");      break; //   17
  case CIM_UINT16    : szResult = _T("CIM_UINT16");     break; //   18
  case CIM_UINT32    : szResult = _T("CIM_UINT32");     break; //   19
  case CIM_SINT64    : szResult = _T("CIM_SINT64");     break; //   20
  case CIM_UINT64    : szResult = _T("CIM_UINT64");     break; //   21
  case CIM_DATETIME  : szResult = _T("CIM_DATETIME");   break; //  101
  case CIM_REFERENCE : szResult = _T("CIM_REFERENCE");  break; //  102
  case CIM_CHAR16    : szResult = _T("CIM_CHAR16");     break; //  103
  case CIM_ILLEGAL   : szResult = _T("CIM_ILLEGAL");    break; // 4095
  case CIM_FLAG_ARRAY: szResult = _T("CIM_FLAG_ARRAY"); break; // 8192
  case CIM_SINT16    | CIM_FLAG_ARRAY: szResult = _T("CIM_SINT16_ARRAY");    break;
  case CIM_SINT32    | CIM_FLAG_ARRAY: szResult = _T("CIM_SINT32_ARRAY");    break;
  case CIM_REAL32    | CIM_FLAG_ARRAY: szResult = _T("CIM_REAL32_ARRAY");    break;
  case CIM_REAL64    | CIM_FLAG_ARRAY: szResult = _T("CIM_REAL64_ARRAY");    break;
  case CIM_STRING    | CIM_FLAG_ARRAY: szResult = _T("CIM_STRING_ARRAY");    break;
  case CIM_BOOLEAN   | CIM_FLAG_ARRAY: szResult = _T("CIM_BOOLEAN_ARRAY");   break;
  case CIM_OBJECT    | CIM_FLAG_ARRAY: szResult = _T("CIM_OBJECT_ARRAY");    break;
  case CIM_SINT8     | CIM_FLAG_ARRAY: szResult = _T("CIM_SINT8_ARRAY");     break;
  case CIM_UINT8     | CIM_FLAG_ARRAY: szResult = _T("CIM_UINT8_ARRAY");     break;
  case CIM_UINT16    | CIM_FLAG_ARRAY: szResult = _T("CIM_UINT16_ARRAY");    break;
  case CIM_UINT32    | CIM_FLAG_ARRAY: szResult = _T("CIM_UINT32_ARRAY");    break;
  case CIM_SINT64    | CIM_FLAG_ARRAY: szResult = _T("CIM_SINT64_ARRAY");    break;
  case CIM_UINT64    | CIM_FLAG_ARRAY: szResult = _T("CIM_UINT64_ARRAY");    break;
  case CIM_DATETIME  | CIM_FLAG_ARRAY: szResult = _T("CIM_DATETIME_ARRAY");  break;
  case CIM_REFERENCE | CIM_FLAG_ARRAY: szResult = _T("CIM_REFERENCE_ARRAY"); break;

  default:
    TRACE1(_T("  CIM property type 0x%0.8X\n"), iData);
    szResult = _T("<unknown>");
  }
return szResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KDbgCimType.cpp,v $
 * Revision 1.1  2010/02/04 23:31:29  ddarko
 * Created
 *
 *****************************************************************************/
