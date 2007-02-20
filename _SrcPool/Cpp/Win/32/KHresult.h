/*$Workfile: $: header file
  $Revision: 1.1 $ $Date: 2007/02/20 22:51:25 $
  $Author: ddarko $

  Handles HRESULT error codes
  2005-09-18 Wanderley Caloni Jr <wanderley@caloni.com.br>
*/

#ifndef _KHRESULT_H_
  //$Workfile: $ sentry
  #define _KHRESULT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
    #pragma message ("   #include " __FILE__ )
#endif

#include <winerror.h>
#include <atlbase.h>
#include <atlexcept.h>

///////////////////////////////////////////////////////////////////////////////
/*The CHresult class stores the status code indicating the reason for the 
  failure, trowing an exception to signal an error based on a HRESULT status 
  code.

  HRESULT is the data type used to indicate the status of operations in 
  Microsoft's Component Object Model (COM).
  HRESULT is a 32-bit value, divided into three different fields: 
  a severity code, a facility code, and an error code. 
  The severity code indicates whether the return value represents information, 
  warning, or error. 
  The facility code identifies the area of the system responsible for the error. 
  The error code is a unique number that is assigned to represent the exception.

  Example:
      #include "KHresult.h" //CHresult class
      ...
      std::_tcout << _T("Creating COM object...") << std::endl;
      try
        {
        CHresult hResult(CoInitialize(NULL)); //Initialize COM
        IMyAtlObj* pcomObj = NULL;
        hResult = CoCreateInstance( CLSID_, 
                                    NULL, 
                                    CLSCTX_INPROC_SERVER,
                                    IID_IMyAtlObj, 
                                    (void**)& pcomObj);        
        pcomObj->MyMethod();
        ...
        pcomTest->Release(); 
        std::_tcout << _T("Fin") << std::endl;
        }
      catch(...) //HRESULT Failure
        {
        std::_tcout << _T("Failure!") << std::endl;
        }
       
  Note:  Microsoft Windows specific (Win32).
  
  See also: <winerror.h>, CAtlException class members, AtlThrow
*/
class CHresult
{
public:
  CHresult();
  CHresult(const HRESULT hResult);
  CHresult(const bool bResult);
  CHresult(const CHresult& hResult);
  virtual ~CHresult();
  
  //Operations
  CHresult &operator= (const HRESULT hResult);
  CHresult &operator= (const bool bResult);
  CHresult &operator= (const DWORD dwResult);
  operator HRESULT() const;
  virtual Throw();
  virtual HRESULT SetErrorInfo(LPCTSTR szSource, LPCTSTR szDescription);
  
  //Attributes
protected:
   HRESULT m_hr; //variable of type HRESULT created by the object and used 
                 //to store the error condition.
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor initializes status to the calling thread's last-error 
  code value.
  Function failure is typically indicated by a return value error code such 
  as zero, NULL, or –1. Error codes are 32-bit values (bit 31 is the most 
  significant bit). Bit 29 is reserved for application-defined error codes.

  See also: GetLastError()
 */
inline CHresult::CHresult() throw(...) : m_hr(HRESULT_FROM_WIN32(::GetLastError()))
{
if( FAILED(m_hr) )
  Throw();
}

//-----------------------------------------------------------------------------
/*Converts the result of an operation to HRESULT.
 */
inline CHresult::CHresult(const bool bResult //[in] error value
                         ) throw(...) : m_hr (bResult ? S_OK: E_FAIL)
{
if( FAILED(m_hr) )
  Throw();
}
  
//-----------------------------------------------------------------------------
/*Assign the result of an operation to the object.
*/
inline CHresult::CHresult(const HRESULT hResult //[in] error value
                         ) throw(...) : m_hr(hResult)
{
if( FAILED(m_hr) )
  Throw();
}

//-----------------------------------------------------------------------------
/*Copy an object with result of an operation.
 */
inline CHresult::CHresult(const CHresult& hResult //[in] error value
                         ) throw(...)
{
if (this != hResult.this)
  {
  m_hr = hResult.m_hr;
  if( FAILED(m_hr) )
    Throw();
  }
}

//-----------------------------------------------------------------------------
/*Destructor
 */
inline CHresult::~CHresult()
{
}

//-----------------------------------------------------------------------------
/*Conversion assignment.
 */
inline CHresult& CHresult::operator= (const HRESULT hResult) throw(...)
{
m_hr = hResult;
if( FAILED(m_hr) )
  Throw();
return *this;
}

inline CHresult& CHresult::operator= (const bool bResult) throw(...)
{
m_hr = (bResult ? S_OK: E_FAIL);
if( FAILED(m_hr) )
  Throw();
return *this;
}

inline CHresult& CHresult::operator= (const DWORD dwResult) throw(...)
{
m_hr = HRESULT_FROM_WIN32(dwResult);S
if( FAILED(m_hr) )
  Throw();
return *this;
}

//-----------------------------------------------------------------------------
/*Conversion assignment.
 */
inline HRESULT CHresult::operator HRESULT() const
{ 
return m_hr; 
}

//-----------------------------------------------------------------------------
/*Throws an exception
 */
inline void CHresult::Throw() throw(...) 
{
AtlThrow(m_hr);
}

#include <oleauto.h>
//-----------------------------------------------------------------------------
/*Sets the error information object for the current logical thread of execution
  in applications that return rich error information.
  
  Returns: S_OK ina case of success or E_OUTOFMEMORY if memory to complete 
  the operation is insufficient.
  
  See also: IErrorInfo
 */
inline HRESULT CHresult::SetErrorInfo(LPCTSTR szSource, //[in] ProgId or name of 
                     //the class or application that is the source of the error.
                     //ProgId should be in the form progname.objectname
                     LPCTSTR szDescription //[in] description of the error
                     )
{
CComPtr<ICreateErrorInfo> piCreateErrorInfo; //error information
HRESULT hr = CreateErrorInfo(&piCreateErrorInfo);
if (SUCCEEDED(hr))
  {
  hr = piCreateErrorInfo->SetSource(T2BSTR(szSource));
  if (SUCCEEDED(hr))
    {
    hr = piCreateErrorInfo->SetDescription(T2BSTR(szDescription));
    if (SUCCEEDED(hr))
      {
      hr = piCreateErrorInfo->SetHelpContext(0);
      if (SUCCEEDED(hr))
        {
        hr = piCreateErrorInfo->SetHelpFile(NULL);
        if (SUCCEEDED(hr))
          {
          hr = piCreateErrorInfo->SetGUID(IID_NULL);
          if (SUCCEEDED(hr))
            {
             //Set the error information IErrorInfo record for the current 
             //logical thread of execution
             SetErrorInfo(0, //reserved for future use
                         (IErrorInfo *)((IUnknown *)piCreateErrorInfo) //error object
                          );
            }
          }
        }
      }
    }
  }
return hr;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: KHresult.h,v $
* Revision 1.1  2007/02/20 22:51:25  ddarko
* Created
*
*****************************************************************************/
