/*$Workfile: KDbgDaoFieldType.cpp$: implementation file
  $Revision: 2$ $Date: 2004-10-01 21:34:08$
  $Author: Darko$

  Dumps data access objects (DAO) properties
  Copyright: CommonSoft Inc.
  2001-04 Darko Kolakovic
 */ 

// Group=Diagnostic
#include "stdafx.h"
#ifndef __AFXDAO_H
  #include <afxdao.h>
#endif

//-----------------------------------------------------------------------------
/*Dump type of data access objects (DAO). 

  The value of this property can be one of the following: 

    dbBoolean   Yes/No, same as TRUE/FALSE 
    dbByte   Byte 
    dbInteger   Short 
    dbLong   Long 
    dbCurrency   Currency; see MFC class COleCurrency 
    dbSingle   Single 
    dbDouble   Double 
    dbDate   Date/Time; see MFC class COleDateTime 
    dbText   Text; see MFC class CString 
    dbLongBinary   Long Binary (OLE Object); you might want to use MFC class CByteArray instead of class CLongBinary as CByteArray is richer and easier to use. 
    dbMemo   Memo; see MFC class CString 
    dbGUID   A Globally Unique Identifier/Universally Unique Identifier used with remote procedure calls. For more information, see the topic "Type Property" in DAO Help. 

  See also: struct CDaoFieldInfo

  Note: uses Microsoft Fundation Library (MFC);
        Microsoft Windows specific (Win).
 */
LPCTSTR DumpDaoFieldType(const short sType //[in] type of data access objects
                        )
{
switch(sType)
  {
  case (dbBoolean):       return _T("Bool");
  case (dbByte):          return _T("Byte");
  case (dbInteger):       return _T("Integer");
  case (dbLong):          return _T("Long");
  case (dbCurrency):      return _T("Currency");
  case (dbSingle):        return _T("Single");
  case (dbDouble):        return _T("Double");
  case (dbDate):          return _T("Date");
  case (dbText):          return _T("Text");
  case (dbLongBinary):    return _T("Long Binary");
  case (dbMemo):          return _T("Memo");
  case (dbGUID):          return _T("GUID");
  }
return _T("<unknown>");
}

/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-10-01 21:34:08  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-13 16:36:30  Darko           
 * $
 *****************************************************************************/
