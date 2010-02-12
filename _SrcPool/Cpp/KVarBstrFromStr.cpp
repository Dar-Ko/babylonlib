/*$RCSfile: KVarBstrFromStr.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2010/02/12 22:46:07 $
  $Author: ddarko $

  Converts a string to the variant version of the string.
  Copyright: babylonlib.sourceforge.net
  2010-02-02 Darko Kolakovic
*/

/* Group=Strings                               */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)     */

#include "stdafx.h"
#ifdef _WIN32
  #include <oleauto.h>
  #pragma comment(lib, "oleaut32")
#endif

extern "C"
  {
  //------------------------------------------------------------------------------
  /*Converts a string to the variant version of the string.

  Allocates an Automation-compatible string of the type BSTR and copies the contents of the CStringT object into it, including the terminating null character.
  requires the caller to free the string. This can be done by using SysFreeString,

  If successful, returns a BSTR containing the string. If sz is a zero-length string, returns a zero-length BSTR. If sz is NULL or insufficient memory exists, returns NULL

    Note: LPWSTR, OLECHAR*, WCHAR*, BSTR are synonyms in the Microsoft OLE / COM
    framework.

    Example:
        wchar_t* wszSource = L"Example";
        VARIANT varResult;
        varResult = VarBstrFromStr(wszSource);

{
   SysFreeString(m_bstrMsg);   // Free previous string, if any.
   m_bstrMsg = SysAllocString(sz);
   //Caller should check to see if result is null after calling this method.
}
   */
  VARIANT VarBstrFromStr(LPCWSTR szSource //[in]
                       )
    {
    VARIANT varResult;
    #ifdef _WIN32
      varResult.bstrVal = SysAllocString(szSource);
      //Note: to free allocated resource call SysFreeString()
      //(using free or delete produce exception in Windows environment).
    #else
      if (szSource != NULL)
        {
        varResult.bstrVal = _wcsdup(szSource);
        //Note: to release allocated resource call free()
        }
      else
        {
        varResult.bstrVal == NULL;
        }
    #endif

    if (varResult.bstrVal != NULL)
      varResult.vt = VT_BSTR;
    else
      varResult.vt = VT_NULL;
    return varResult;
    }
}

//------------------------------------------------------------------------------
#if defined (_USE_MFC) || (_USE_ATL)
/*
free strings created with SysAllocString using SysFreeString.
 */
VARIANT VarBstrFromStr(CString strSource//[in]
                      )
{
VARIANT varResult;
varResult.bstrVal =  strSource.AllocSysString();
if (varResult.bstrVal != NULL)
  varResult.vt = VT_BSTR;
else
  varResult.vt = VT_NULL;

return varResult;
}
#endif //(_USE_MFC) || (_USE_ATL)

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 *$Log: KVarBstrFromStr.cpp,v $
 *Revision 1.2  2010/02/12 22:46:07  ddarko
 *Fixed VT_DATE, VT_BSTR (WIN32)
 *
 *****************************************************************************/
