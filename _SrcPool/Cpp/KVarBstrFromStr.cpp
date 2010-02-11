#include "stdafx.h"
#include <oleauto.h>
#pragma comment(lib, "oleaut32")

extern "C"
  {
  //------------------------------------------------------------------------------
  /*
  Allocates an Automation-compatible string of the type BSTR and copies the contents of the CStringT object into it, including the terminating null character.
  requires the caller to free the string. This can be done by using SysFreeString,

  If successful, returns a BSTR containing the string. If sz is a zero-length string, returns a zero-length BSTR. If sz is NULL or insufficient memory exists, returns NULL

    Note: LPWSTR, OLECHAR*, WCHAR*, BSTR are synonyms in the Microsoft OLE / COM
    framework.

    Example:
        wchar_t* wszSource = L"Example";
        VARIANT varResult;
        varResult = StrToVariant(wszSource);

{

   SysFreeString(m_bstrMsg);   // Free previous string, if any.

   m_bstrMsg = SysAllocString(sz);

   // Caller should check to see if m_bstrMsg is null after calling this method.

}
   */
  VARIANT VarBstrFromStr(LPCWSTR szSource //[in]
                       )
    {
    VARIANT varResult;
    VariantInit(&varResult); //Initialize to VT_EMPTY.
    V_BSTR(&varResult) = SysAllocString(szSource);
    V_VT(&varResult) = VT_BSTR;
    return varResult;
    }
}

//------------------------------------------------------------------------------
/*
free strings created with SysAllocString using SysFreeString.
 */
VARIANT VarBstrFromStr(CString strSource//[in]
                     )
{
VARIANT varResult;
VariantInit(&varResult); //Initialize to VT_EMPTY.
V_BSTR(&varResult) = strSource.AllocSysString();
V_VT(&varResult) = VT_BSTR;
return varResult;
}
