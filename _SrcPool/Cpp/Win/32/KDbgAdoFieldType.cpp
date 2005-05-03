/*$Workfile: S:\_SrcPool\Cpp\Win\32\KDbgAdoFieldType.cpp$: implementation file
  $Revision: 4$ $Date: 2005-04-26 11:28:36$
  $Author: Darko Kolakovic$

  Dumps data type of a Field, Parameter, or Property
  Copyright: CommonSoft Inc.
  2003-08 Darko Kolakovic
 */ 

// Group=Diagnostic
#include "stdafx.h"

/*KB259379 HOWTO: Develop with ADO Version 2.5 or Later and Install on 
  ADO Version 2.0
  Errors are caused by new ActiveX Data Objects (ADO) interfaces that are
  referenced in the ADO 2.5 or later-produced image and that are not found 
  in the Msado15.dll file on the target system. 
 */
#if defined(ADO2_OLD)
  #pragma message( "Using ADO2 TLB <msado20.tlb>" ) 
  #import <msado20.tlb> no_namespace rename("EOF", "adoEOF") 
#else
  #pragma message( "Using ADO 2.7 <msado15.dll>" )
  //Note: Add "C:\Program Files\Common Files\System\ADO" path to 
  //VisualStudio|Tools|Options|Projects|VC++ Directories|Executable files
  #import <msado15.dll> no_namespace rename("EOF", "adoEOF") 
#endif

//-----------------------------------------------------------------------------
/*Dump data type of a Field, Parameter, or Property.

  Returns: null-termeinated string describing data type

  Note: uses Microsoft Foundation Library (MFC);
        Microsoft ActiveX Data Objects (ADO).
        Microsoft Windows specific (Win).
 */
LPCTSTR DumpAdoFieldType(const DataTypeEnum& iType//[in] specifies the data 
                                       //type of a Field, Parameter, or Property.
                         )
{
if ((iType & adArray) == adArray)
  TRACE0("Array"); //TODO: glue array type at the end of resulting string D.K.

switch(iType)
  {
    case adBigInt:      return _T("adBigInt");
    case adBinary:      return _T("adBinary");
    case adBoolean:      return _T("adBoolean");
    case adBSTR:      return _T("adBSTR");
    case adChar:      return _T("adChar");
    case adCurrency:      return _T("adCurrency");
    case adDate:      return _T("adDate");
    case adDBDate:      return _T("adDBDate");
    case adDBTime:      return _T("adDBTime");
    case adDBTimeStamp:      return _T("adDBTimeStamp");
    case adDecimal:      return _T("adDecimal");
    case adDouble:      return _T("adDouble");
    case adEmpty:      return _T("adEmpty");
    case adError:      return _T("adError");
    case adGUID:      return _T("adGUID");
    case adIDispatch:      return _T("adIDispatch");
    case adInteger:      return _T("adInteger");
    case adIUnknown:      return _T("adIUnknown");
    case adLongVarBinary:      return _T("adLongVarBinary");
    case adLongVarChar:      return _T("adLongVarChar");
    case adLongVarWChar:      return _T("adLongVarWChar");
    case adNumeric:      return _T("adNumeric");
    case adSingle:      return _T("adSingle)");
    case adSmallInt:      return _T("adSmallInt");
    case adTinyInt:      return _T("adTinyInt");
    case adUnsignedBigInt:      return _T("adUnsignedBigInt");
    case adUnsignedInt:      return _T("adUnsignedInt");
    case adUnsignedSmallInt: return _T("adUnsignedSmallInt");
    case adUnsignedTinyInt:  return _T("adUnsignedTinyInt");
    case adUserDefined:      return _T("adUserDefined");
    case adVarBinary:        return _T("adVarBinary");
    case adVarChar:          return _T("adVarChar");
    case adVariant:          return _T("adVariant");
    case adVarWChar:         return _T("adVarWChar");
    case adWChar:            return _T("adWChar");
    default:                 return _T("<uknown>");
  }

}

/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-04-26 11:28:36  Darko Kolakovic Document groups
 *       and typo fixes
 *  3    Biblioteka1.2         2004-10-01 22:33:58  Darko           stdafx.h
 *  2    Biblioteka1.1         2003-08-17 02:10:48  Darko           fixed typo
 *  1    Biblioteka1.0         2003-08-13 17:36:16  Darko           
 * $
 *****************************************************************************/
