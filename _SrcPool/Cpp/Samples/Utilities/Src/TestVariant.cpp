/*$RCSfile: TestVariant.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/02/12 22:47:37 $
  $Author: ddarko $

  Test VARIANT conversion routines.
  2010-01-05 Darko Kolakovic
 */

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "stdafx.h"
#ifdef _WIN32
  #include <oleauto.h> //VarBstrFromDate()
  #pragma comment(lib, "oleaut32")
#endif
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern "C" VARIANT VarBstrFromStr(LPCWSTR szSource);

#ifdef _USE_WINSEARCH
  /*Note: Requires Windows XP Service Pack 2 (SP2) with Windows Desktop Search (WDS) 3.0 or
    Windows Vista or Windows 7

    See also: Windows Search 4.0
    (http://www.microsoft.com/windows/products/winfamily/desktopsearch/default.mspx);
   */
  #include <propvarutil.h> //VariantToStringAlloc()
  #pragma comment(lib, "propsys")
#else //~_USE_WINSEARCH
  extern long VariantToStringAlloc(const VARIANT& varIn, LPWSTR* ppszBuf);
#endif //_USE_WINSEARCH
//-----------------------------------------------------------------------------
/*Testing generating and handling Universally Unique Identifier (UUID /GUID).

  Returns: true if successful, otherwise returns false.
 */
bool TestVariant()
{
TRACE(_T("TestVariant()\n"));
bool bResult = false;
VARIANT    varIn; //test input
LPWSTR     wszResult = NULL; //resulting string
HRESULT    lError = E_FAIL;  //error code

//Test LPWSTR to VT_BSTR conversion
varIn = VarBstrFromStr(NULL);
bResult = (varIn.vt == VT_NULL) && (varIn.bstrVal == NULL);
ASSERT(bResult);
#ifdef _WIN32
  SysFreeString(varIn.bstrVal);
#endif

if(bResult)
  {
  varIn = VarBstrFromStr(L""); //Intialize with the empty string
  bResult = (varIn.vt == VT_BSTR) && (varIn.bstrVal[0] == L'\0');
  ASSERT(bResult);
  #ifdef _WIN32
    SysFreeString(varIn.bstrVal);
  #else
    if(varIn.bstrVal != NULL)
      free(varIn.bstrVal);
  #endif
  }

//Test VT_DATE to LPWSTR conversion.
#ifdef _WIN32
  //Set initial values for some variables.
  VariantInit(&varIn); //Initialize VARIANT::vt to VT_EMPTY. Other 
                       //members are not set.
  SYSTEMTIME timeNow;
  GetSystemTime(&timeNow);
  bResult = (::SystemTimeToVariantTime(&timeNow, &varIn.date) != 0);
  if(bResult)
    {
    //Sample Microsoft Component Automation functions (OLE)
    varIn.vt = VT_DATE;
    LPWSTR bstrTemp = NULL;
    lError = VarBstrFromDate((static_cast <VARIANT>(varIn)).date,
                            LOCALE_USER_DEFAULT,
                            VAR_FOURDIGITYEARS, //flags
                            &bstrTemp
                           );
    bResult = SUCCEEDED(lError);
    if(bResult)
      {
      #ifdef _UNICODE
        TsWriteToViewLn(bstrTemp);
      #else
        //TODO: conversion to ASCII
      #endif
      //Free allocated resource (using free or delete produce exception).
      SysFreeString(bstrTemp);
      }
    }
#endif

lError = VariantToStringAlloc(varIn, &wszResult);
bResult = (lError == S_OK);
if (bResult)
  {
  ASSERT(wszResult != NULL);
  #ifdef _UNICODE
    TsWriteToViewLn(wszResult);
  #else
    //TODO: conversion to ASCII
  #endif
  free(wszResult);
  wszResult = NULL;
  }

//Test VT_BSTR to LPWSTR conversion.
varIn = VarBstrFromStr(L"Conlige suspectos semper habitos");
lError = VariantToStringAlloc(varIn, &wszResult);
bResult = (lError == S_OK);
if (bResult)
  {
  ASSERT(wszResult != NULL);
  #ifdef _UNICODE
    TsWriteToViewLn(wszResult);
  #else
    //TODO: conversion to ASCII
  #endif
  free(wszResult);
  wszResult = NULL;
  #ifdef _WIN32
    SysFreeString(varIn.bstrVal);
  #else
    if(varIn.bstrVal != NULL)
      free(varIn.bstrVal);
  #endif
  }

if (bResult)
  {
  const unsigned nTestCount = 40;
  VARIANT vtTest[nTestCount];
  vtTest[ 0].vt = VT_EMPTY;
  vtTest[ 1].vt = VT_I2;              vtTest[ 1].dblVal = 0.0;
  vtTest[ 2].vt = VT_I4;              vtTest[ 1].dblVal = 0.0;
  vtTest[ 3].vt = VT_R4;              vtTest[ 1].dblVal = 0.0;
  vtTest[ 4].vt = VT_R8;              vtTest[ 1].dblVal = 0.0;
  vtTest[ 5].vt = VT_CY;              vtTest[ 1].dblVal = 0.0;
  vtTest[ 6].vt = VT_DATE;            vtTest[ 1].dblVal = 0.0;
  vtTest[ 7].vt = VT_BSTR;            vtTest[ 1].dblVal = 0.0;
  vtTest[ 8].vt = VT_DISPATCH;        vtTest[ 1].dblVal = 0.0;
  vtTest[ 9].vt = VT_ERROR;           vtTest[ 1].dblVal = 0.0;
  vtTest[10].vt = VT_BOOL;            vtTest[ 1].dblVal = 0.0;
  vtTest[11].vt = VT_VARIANT;         vtTest[ 1].dblVal = 0.0;
  vtTest[12].vt = VT_UNKNOWN;         vtTest[ 1].dblVal = 0.0;
  vtTest[13].vt = VT_DECIMAL;         vtTest[ 1].dblVal = 0.0;
  vtTest[14].vt = VT_I1;              vtTest[ 1].dblVal = 0.0;
  vtTest[15].vt = VT_UI1;             vtTest[ 1].dblVal = 0.0;
  vtTest[16].vt = VT_UI4;             vtTest[ 1].dblVal = 0.0;
  vtTest[17].vt = VT_I8;              vtTest[ 1].dblVal = 0.0;
  vtTest[18].vt = VT_UI8;             vtTest[ 1].dblVal = 0.0;
  vtTest[19].vt = VT_INT;             vtTest[ 1].dblVal = 0.0;
  vtTest[20].vt = VT_UINT;            vtTest[ 1].dblVal = 0.0;
  vtTest[21].vt = VT_VOID;            vtTest[ 1].dblVal = 0.0;
  vtTest[22].vt = VT_HRESULT;         vtTest[ 1].dblVal = 0.0;
  vtTest[23].vt = VT_PTR;             vtTest[ 1].dblVal = 0.0;
  vtTest[24].vt = VT_SAFEARRAY;       vtTest[ 1].dblVal = 0.0;
  vtTest[25].vt = VT_CARRAY;          vtTest[ 1].dblVal = 0.0;
  vtTest[26].vt = VT_USERDEFINED;     vtTest[ 1].dblVal = 0.0;
  vtTest[27].vt = VT_LPSTR;           vtTest[ 1].dblVal = 0.0;
  vtTest[28].vt = VT_LPWSTR;          vtTest[ 1].dblVal = 0.0;
  vtTest[29].vt = VT_FILETIME;        vtTest[ 1].dblVal = 0.0;
  vtTest[30].vt = VT_BLOB;            vtTest[ 1].dblVal = 0.0;
  vtTest[31].vt = VT_STREAM;          vtTest[ 1].dblVal = 0.0;
  vtTest[32].vt = VT_STORAGE;         vtTest[ 1].dblVal = 0.0;
  vtTest[33].vt = VT_STREAMED_OBJECT; vtTest[ 1].dblVal = 0.0;
  vtTest[34].vt = VT_STORED_OBJECT;   vtTest[ 1].dblVal = 0.0;
  vtTest[35].vt = VT_BLOB_OBJECT;     vtTest[ 1].dblVal = 0.0;
  vtTest[36].vt = VT_CLSID;           vtTest[ 1].dblVal = 0.0;
  vtTest[37].vt = VT_VECTOR;          vtTest[ 1].dblVal = 0.0;
  vtTest[38].vt = VT_ARRAY;           vtTest[ 1].dblVal = 0.0;
  //Leave the last element vtTest[39] unitialized

  int i;
  for(i = 0; i < nTestCount; i++)
    {
    lError = VariantToStringAlloc(vtTest[i], &wszResult);
    bResult = (lError == S_OK);
    if (bResult)
      {
      ASSERT(wszResult != NULL);
      #ifdef _UNICODE
        TsWriteToViewLn(wszResult);
      #else
        //TODO: conversion to ASCII
      #endif
      free(wszResult);
      wszResult = NULL;
      }

    }


  }

TsWriteToViewLn(LOG_EOT);
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestVariant.cpp,v $
 * Revision 1.1  2010/02/12 22:47:37  ddarko
 * TestVariant
 *
 ******************************************************************************/
