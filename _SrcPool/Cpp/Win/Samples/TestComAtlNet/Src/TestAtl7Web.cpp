/*$Workfile: TestAtl7Web.cpp$: implementation file
  $Revision: 3$ $Date: 2007-03-01 20:09:51$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2006-08-30 Darko Kolakovic
 */

#include "stdafx.h"
#include "TestAtl7Web.h"
extern uint32_t g_nDBgBreak;

////////////////////////////////////////////////////////////////////////////////
// CTestAtl7Web

//-----------------------------------------------------------------------------
/*Default constructor
 */
CTestAtl7Web::CTestAtl7Web()
: m_lTestCount(0)
{
}

//-----------------------------------------------------------------------------
/*Initializes the object instantiated with CoCreateInstance(). The method is
  called immediately after the most derived class is fully constructed if
  the reference count is zero, allowing you to call virtual functions and
  use the reference-counting implementation provided by ATL.

  Returns: S_OK on success or one of the standard error HRESULT values.
*/
HRESULT CTestAtl7Web::FinalConstruct()
{
//Inserted by the MSVC ATL Wizard
ATLTRACE("CTestAtl7Web::FinalConstruct()\n");
return S_OK;
}

//-----------------------------------------------------------------------------
/*Deletes the object. Called during object destruction when the last client
  has called IUnknown::Release() on the object, this method frees
  the m_contained member.
*/
void CTestAtl7Web::FinalRelease()
{
//Inserted by the MSVC ATL Wizard
ATLTRACE("CTestAtl7Web::FinalRelease()\n");
}

//-----------------------------------------------------------------------------
STDMETHODIMP CTestAtl7Web::InterfaceSupportsErrorInfo(REFIID riid)
{
//Inserted by the MSVC ATL Wizard
static const IID* arr[] =
  {
  &IID_ITestAtl7Web
  };

for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
  {
  if (InlineIsEqualGUID(*arr[i],riid))
    return S_OK;
  }
return S_FALSE;
}

//-----------------------------------------------------------------------------
/*Maps a single member and an optional set of argument names to 
  a corresponding set of integer DISPIDs, which can be used on subsequent 
  calls to IDispatch::Invoke. 
  This method invokes base class implementation with additional debugging 
  information.
  
  Returns: S_OK or one of following errors: ERROR_INVALID_DATA, E_OUTOFMEMORY, 
  DISP_E_UNKNOWNNAME, DISP_E_UNKNOWNLCID.
 */
HRESULT STDMETHODCALLTYPE CTestAtl7Web::GetIDsOfNames(REFIID riid, //Reserved 
                                             //for future use. Must be IID_NULL. 
                                                LPOLESTR *rgszNames, //[in] array 
                                             //of names to be mapped.
                                                UINT cNames, //[in]count of 
                                             //the names to be mapped. 
                                                LCID lcid, //[in] locale context 
                                                DISPID *rgDispId //[in] caller-allocated
                                             //array with ids of names to be mapped
                                                ) 
{
ATLASSERT(g_nDBgBreak == 0); //Convinient way to set breakpoint;

HRESULT hRes = S_OK;
try
  {
  ATLTRACE("CTestAtl7Web::GetIDsOfNames()\n");
  //Call base class implementation
  hRes = IDispatchImpl<ITestAtl7Web, 
                        &IID_ITestAtl7Web, 
                        &LIBID_TestComAtlNetLib, 
                        1, 0>::GetIDsOfNames(riid, rgszNames, cNames, lcid, rgDispId);
  #ifdef _UNICODE
    #define EXPFORMAT "  Export Count %d; 0.[%ws, ID =  %d]\n"
  #else
    #define EXPFORMAT "  Export Count %d; 0.[%s, ID =  %d]\n"
  #endif
  ATLTRACE(EXPFORMAT, cNames, rgszNames[0], rgDispId[0]);
  }
catch(...)
  {
  ATLTRACE("CTestAtl7Web::GetIDsOfNames() Failed!\n");
  hRes = ERROR_INVALID_DATA;
  }
return hRes;
}

//-----------------------------------------------------------------------------
/*Test method increments the test count by one.

  Returns: S_OK.
*/
STDMETHODIMP CTestAtl7Web::TestMethod(void)
{
ATLASSERT(g_nDBgBreak < 2); //debugger breakpoint
//Increase test count
m_lTestCount++;
ATLTRACE("CTestAtl7Web::TestMethod(count = %d)", m_lTestCount);

return S_OK;
}

//-----------------------------------------------------------------------------
/*Obtains value of the test counter.

  Returns: S_OK or E_POINTER and test counter value.
*/
STDMETHODIMP CTestAtl7Web::GetMethod(LONG* pVal //[out] test count
                                    )
{
ATLASSERT(g_nDBgBreak < 2); //debugger breakpoint
ATLTRACE("CTestAtl7Web::GetMethod(count = %d)\n", m_lTestCount);

if (NULL == pVal) 
  return E_POINTER;

*pVal = m_lTestCount; //Return counter value
return S_OK;
}

//-----------------------------------------------------------------------------
/*Returns Test count multiplied by lInput.
  This method has [propget] attribute in the IDL file and it is mapped to the
  TestCounter interface method through MIDL generated files.
  
  Returns: S_OK or E_POINTER and multiplied counter value.
*/
STDMETHODIMP CTestAtl7Web::get_TestCounter(long lInput, //[in] multiplier
                                           LONG* pResult //[out]
                                          )
{
ATLASSERT(g_nDBgBreak < 2); //debugger breakpoint
ATLTRACE("CTestAtl7Web::get_TestCounter(lInput = %d)\n", lInput);

if (NULL == pResult) 
  return E_POINTER;
  
*pResult = m_lTestCount * lInput; //Return counter value
return S_OK;
}

//-----------------------------------------------------------------------------
/*Test of returning a long value.

  Returns: S_OK or E_POINTER and test counter value.
 */
STDMETHODIMP CTestAtl7Web::Long(LONG* pVal //[out] result
                               )
{
ATLASSERT(g_nDBgBreak < 2); //debugger breakpoint
ATLTRACE("CTestAtl7Web::Long()\n");

if (NULL == pVal) 
  return E_POINTER;

*pVal = m_lTestCount; //Return counter value
return S_OK;
}

//-----------------------------------------------------------------------------
/*Test of returning a string property.

  Note: [propget] attribute specifies a property accessor function. The last 
  parameter of the method with this attribute have to be a pointer type with 
  the [out, retval] attributes.

  Returns: S_OK and test message or E_POINTER, E_OUTOFMEMORY.
*/
STDMETHODIMP CTestAtl7Web::get_String(BSTR* pVal//[out]
                                     )
{
ATLASSERT(g_nDBgBreak < 2); //debugger breakpoint
ATLTRACE("CTestAtl7Web::get_String()\n");

if (NULL == pVal) 
  return E_POINTER;
HRESULT hRes = S_OK;
try
  {
  CComBSTR bstrTemp;

  if (m_bstrTestText == NULL)
    bstrTemp = (L"<NULL>");
  else
    bstrTemp = m_bstrTestText;

  hRes = bstrTemp.CopyTo(pVal);
  bstrTemp.Detach();
  }
catch(CAtlException e)
  {
  return e;
  }
return hRes;
}

/*Test of setting a string property.

  Note: [propput] attribute specifies a property-setting function.
  
  Returns: S_OK or E_POINTER and test counter value.
*/
STDMETHODIMP CTestAtl7Web::put_String(BSTR newVal //[in]
                                     )
{
ATLASSERT(g_nDBgBreak < 2); //debugger breakpoint
ATLTRACE("CTestAtl7Web::put_String(%ws)\n", newVal);
try
  {
  m_bstrTestText = newVal; //Throws CAtlException (ATL project) or
                           //CMemoryException/COleException (MFC Project)
  }
catch(CAtlException e)
  {
  return e;
  }
catch (...) 
  {
  return E_OUTOFMEMORY;
  }
return S_OK;
}

STDMETHODIMP CTestAtl7Web::GetString(BSTR* pVal//[out]
                                    )
{
return get_String(pVal);
}

STDMETHODIMP CTestAtl7Web::SetString(BSTR newVal //[in]
                                    )
{
return put_String(newVal);
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: 
*  3    Biblioteka1.2         2007-03-01 20:09:51  Darko Kolakovic Test setting a
*       property
*  2    Biblioteka1.1         2007-03-01 00:10:11  Darko Kolakovic TestCounter
*       property
*  1    Biblioteka1.0         2007-02-26 18:16:13  Darko Kolakovic 
* $
*****************************************************************************/
