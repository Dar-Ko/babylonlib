/*$RCSfile: TestVariant.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2010/02/17 21:52:18 $
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
extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToViewLn(const unsigned int& nValue);
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
  const unsigned nTestCount = 46;
  VARIANT vtTest[nTestCount];
  vtTest[ 0].vt = VT_EMPTY;
  vtTest[ 1].vt = VT_I2;              vtTest[ 1].iVal   = -4849; //'01'
  vtTest[ 2].vt = VT_I4;              vtTest[ 2].lVal   = -65666768; //'ABCD'
  vtTest[ 3].vt = VT_R4;              vtTest[ 3].fltVal =  3.14E-1f;
  vtTest[ 4].vt = VT_R8;              vtTest[ 4].dblVal = -2.78E60;
  //Currency = -91133225566.4477 units
  vtTest[ 5].vt = VT_CY;              vtTest[ 5].cyVal.Hi = 0xFFFCC325;
                                      vtTest[ 5].cyVal.Lo = 0xECA0F6A3;
  //date = 2010-02-16T16:52:30
  vtTest[ 6].vt = VT_DATE;            vtTest[ 6].date   = 40225.703125;
  vtTest[ 7].vt = VT_BSTR;            vtTest[ 7].bstrVal = L"Ipsa scientia potestas est.";
  vtTest[ 8].vt = VT_DISPATCH;        vtTest[ 8].dblVal = 0.0;//TODO:
  //status code = ERROR_OUTOFMEMORY = 14
  vtTest[ 9].vt = VT_ERROR;           vtTest[ 9].scode  = 14;
  vtTest[10].vt = VT_BOOL;            vtTest[10].boolVal= 11; //false = 0, true <> 0
  vtTest[11].vt = VT_VARIANT;         vtTest[11].dblVal = 0.110;//TODO:
  vtTest[12].vt = VT_UNKNOWN;         vtTest[12].dblVal = 0.0;//TODO:
  //decimal = -756175849799218897808.84976452
  vtTest[13].vt = VT_DECIMAL;         vtTest[13].decVal.Hi32  = 0xF4556677;
                                      vtTest[13].decVal.Mid32 = 0xAABBCCDD;
                                      vtTest[13].decVal.Lo32  = 0x11223344;
                                      vtTest[13].decVal.scale = 0x8; //10e-8
                                      vtTest[13].decVal.sign  = DECIMAL_NEG;//negative number
  vtTest[14].vt = VT_I1;              vtTest[14].cVal = 'Y';
  vtTest[15].vt = VT_UI1;             vtTest[15].bVal = 254;
  vtTest[16].vt = VT_UI2;             vtTest[16].uiVal = 54321;
  vtTest[17].vt = VT_UI4;             vtTest[17].ulVal = 1122334455;
  vtTest[18].vt = VT_I8;              vtTest[18].dblVal = 0.170;//TODO:
  vtTest[19].vt = VT_UI8;             vtTest[19].dblVal = 0.180;//TODO:
  vtTest[20].vt = VT_INT;             vtTest[10].dblVal = 0.190;//TODO:
  vtTest[21].vt = VT_UINT;            vtTest[21].dblVal = 0.200;//TODO:
  vtTest[22].vt = VT_VOID;            vtTest[22].dblVal = 0.210;//TODO:
  //hResult = E_OUTOFMEMORY = 0x80000002
  vtTest[23].vt = VT_HRESULT;         vtTest[23].scode= 0x80000002;
  vtTest[24].vt = VT_PTR;             vtTest[24].dblVal = 0.230;//TODO:
  vtTest[25].vt = VT_SAFEARRAY;       vtTest[25].dblVal = 0.240;//TODO:
  vtTest[26].vt = VT_CARRAY;          vtTest[26].dblVal = 0.250;//TODO:
  vtTest[27].vt = VT_USERDEFINED;     vtTest[27].dblVal = 0.260;//TODO:
  vtTest[28].vt = VT_LPSTR;           vtTest[28].dblVal = 0.270;//TODO:
  vtTest[29].vt = VT_LPWSTR;          vtTest[29].dblVal = 0.280;//TODO:
  vtTest[30].vt = VT_FILETIME;        vtTest[30].dblVal = 0.290;//TODO:
  vtTest[31].vt = VT_BLOB;            vtTest[31].dblVal = 0.300;//TODO:
  vtTest[32].vt = VT_STREAM;          vtTest[32].dblVal = 0.310;//TODO:
  vtTest[33].vt = VT_STORAGE;         vtTest[33].dblVal = 0.320;//TODO:
  vtTest[34].vt = VT_STREAMED_OBJECT; vtTest[34].dblVal = 0.330;//TODO:
  vtTest[35].vt = VT_STORED_OBJECT;   vtTest[35].dblVal = 0.340;//TODO:
  vtTest[36].vt = VT_BLOB_OBJECT;     vtTest[36].dblVal = 0.350;//TODO:
  vtTest[37].vt = VT_CLSID;           vtTest[37].dblVal = 0.360;//TODO:
  vtTest[38].vt = VT_VECTOR;          vtTest[38].dblVal = 0.370;//TODO:
  vtTest[39].vt = VT_ARRAY;           vtTest[39].dblVal = 0.380;//TODO:
  //Leave the last element vtTest[40] unitialized
  vtTest[41].vt = VT_BSTR;            vtTest[41].bstrVal = NULL;
  vtTest[42].vt = VT_BSTR;            vtTest[42].bstrVal = L"";
  //Note: if interface pointer is NULL, returned error is 
  //DISP_E_TYPEMISMATCH = 0x80020005
  vtTest[43].vt = VT_DISPATCH;        vtTest[43].pdispVal= NULL;
  vtTest[44].vt = VT_UNKNOWN;         vtTest[44].punkVal = NULL;
  vtTest[45].vt = VT_DECIMAL;         vtTest[45].decVal.Hi32  = 0;
                                      vtTest[45].decVal.Lo32  = 0;
                                      vtTest[45].decVal.Mid32 = 0;
                                      vtTest[45].decVal.scale = 0;//10e0
                                      vtTest[45].decVal.sign  = 0;//positive number


  int i;
  for(i = 0; i < nTestCount; i++)
    {
    lError = VariantToStringAlloc(vtTest[i], &wszResult);
    ASSERT(wszResult != NULL);
    extern LPCTSTR DumpVariantType(VARIANT varData);
    TsWriteToView(DumpVariantType(vtTest[i]));
    TsWriteToView(_T(": "));
    #ifdef _UNICODE
      TsWriteToViewLn(wszResult);
    #else
      //TODO: conversion to ASCII
    #endif
    free(wszResult);
    wszResult = NULL;
    bResult = (lError == S_OK);
    if (!bResult)
      {
      TsWriteToView(_T("  Error: "));
      TsWriteToViewLn((const unsigned int)lError);
      TRACE1(_T("  VariantToStringAlloc() failed (error 0x%0X).\n"), lError);
      }
    }


  }

TsWriteToViewLn(LOG_EOT);
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestVariant.cpp,v $
 * Revision 1.2  2010/02/17 21:52:18  ddarko
 * Added new test cases
 *
 * Revision 1.1  2010/02/12 22:47:37  ddarko
 * TestVariant
 *
 ******************************************************************************/
