/*$Workfile: KCoProviderErrors.cpp$: implementation file
  $Revision: 4$ $Date: 2005-04-26 16:42:10$
  $Author: Darko Kolakovic$

  Displays Provider Error description
  Copyright: CommonSoft Inc.
  2003-08-09 Darko Kolakovic
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
/*Obtains a list of Provider Errors from Connection object.

  Returns: constant pointer to the list of errors strResult or NULL.

  Example:
      extern LPCTSTR ComProviderErrors(_ConnectionPtr ptrConnection, CString& s);
      CString strMessage;
      if (ComtProviderError(m_pConnection, strMessage) != NULL)
        AfxMessageBox( strMessage, MB_OK | MB_ICONERROR );

  Note: uses Active Template Library (ATL);
        Microsoft Windows specific (Win).

  See also: ComErrorShow(), DisplayError()
 */
LPCTSTR  ComProviderErrors(_ConnectionPtr ptrConnection, //[in] active COM
                                                          //connection
                           CString& strResult //[out] list of errors
                          )
{

if(ptrConnection != NULL)
  {
  long lCount;
  if ((lCount = ptrConnection->Errors->Count) > 0)
    {
    strResult.Empty();
    ErrorPtr ptrError = NULL; //record object in the Connection's Error collection
    CString strDescription;
    long i = 0;
    while(i < lCount)
      {
      ptrError = ptrConnection->Errors->GetItem(i);
      strDescription.Format(_T("%s\n%s\n%s, 0x%08lx\n"),
                            (LPCTSTR)ptrError->Source,
                            (LPCTSTR)ptrError->Description,
                            (LPCTSTR)ptrError->SQLState,
                            ptrError->NativeError); //ptrError->Number //TODO: check ptrError->Numberformat D.K.
      strResult += (LPCTSTR)strDescription;
      i++;
      }
    if(!strResult.IsEmpty())
      {
      strResult = strResult.Left(strDescription.GetLength()-2);
      return (LPCTSTR)strResult;
      }
    }
  }
return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-10-01 22:33:55  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-14 13:54:42  Darko
 * $
 *****************************************************************************/
