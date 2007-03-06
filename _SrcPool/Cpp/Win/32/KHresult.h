/*$Workfile: KHresult.h$: header file
  $Revision: 1.3 $ $Date: 2007/03/06 23:07:29 $
  $Author: ddarko $

  Handles HRESULT error codes
  2005-09-18 Wanderley Caloni Jr <wanderley@caloni.com.br>
 */

#ifndef _KHRESULT_H_
  //$Workfile: KHresult.h$ sentry
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
  virtual void Throw();
  virtual HRESULT SetErrorInfo(LPCTSTR szSource, LPCTSTR szDescription);
  virtual LPCTSTR ErrorMessage() const;

  //Attributes
protected:
   HRESULT m_hr; //variable of type HRESULT created by the object and used
                 //to store the error condition.
   mutable LPTSTR m_pszMsg; //error description
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
inline CHresult::CHresult() throw(...) : 
  m_hr(HRESULT_FROM_WIN32(::GetLastError())),
  m_pszMsg(NULL)
{
if( FAILED(m_hr) )
  Throw();
}

//-----------------------------------------------------------------------------
/*Converts the result of an operation to HRESULT.
 */
inline CHresult::CHresult(const bool bResult //[in] error value
                         ) throw(...) : 
  m_hr (bResult ? S_OK: E_FAIL),
  m_pszMsg(NULL)
{
if( FAILED(m_hr) )
  Throw();
}

//-----------------------------------------------------------------------------
/*Assign the result of an operation to the object.
*/
inline CHresult::CHresult(const HRESULT hResult //[in] error value
                          ) throw(...) :
  m_hr(hResult),
  m_pszMsg(NULL)
{
if( FAILED(m_hr) )
  Throw();
}

//-----------------------------------------------------------------------------
/*Copy an object with result of an operation.
 */
inline CHresult::CHresult(const CHresult& hResult //[in] error value
                         ) throw(...) : 
  m_hr (hResult.m_hr),
  m_pszMsg(NULL)
{
if( FAILED(m_hr) )
  Throw();
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
m_hr = HRESULT_FROM_WIN32(dwResult);
if( FAILED(m_hr) )
  Throw();
return *this;
}

//-----------------------------------------------------------------------------
/*Conversion assignment.
 */
inline CHresult::operator HRESULT() const
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

//-----------------------------------------------------------------------------
/*Retrieves the error desription of the HRESULT member.

  Returns: string message for the HRESULT.
 */
inline LPCTSTR CHresult::ErrorMessage() const
{
//Borrowed from <comdef.h>
if (m_pszMsg == NULL) //Create new error message
  {
    //TODO: support locale
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                m_hr,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&m_pszMsg,
                0,
                NULL);

  if (m_pszMsg != NULL)  //Annex CRLF to the message
    {
    int nLen = lstrlen(m_pszMsg);
    if (nLen > 1 && m_pszMsg[nLen - 1] == '\n') 
      {
      m_pszMsg[nLen - 1] = 0;
      if (m_pszMsg[nLen - 2] == '\r') 
        {
        m_pszMsg[nLen - 2] = 0;
        }
      }
    } 
  else //if HRESULT is without a description, provide one
    {
    const int ERRMSG_MAXSIZE = 32;
    m_pszMsg = (LPTSTR)LocalAlloc(0, ERRMSG_MAXSIZE * sizeof(TCHAR));
    if (m_pszMsg != NULL) 
      {
      //Check errors for Custom Interfaces Facility of FACILITY_ITF (see winerror.h)
      //Error codes for this facility could have duplicate descriptions (see MSDN Q183216)
      const unsigned short E_ITF_FIRST = 0x200; //first error in the range
      const HRESULT WCODE_HRESULT_FIRST = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, E_ITF_FIRST);
      const HRESULT WCODE_HRESULT_LAST  = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF+1, 0);
      if (m_hr >= WCODE_HRESULT_FIRST &&  m_hr < WCODE_HRESULT_LAST) 
        wsprintf(m_pszMsg, TEXT("COM Interface error 0x%0lX"), m_hr);
      else
        wsprintf(m_pszMsg, TEXT("Unknown COM error 0x%0lX"), m_hr);
      }
    }
  }
return m_pszMsg;
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
             ::SetErrorInfo(0, //reserved for future use
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
#endif //_KHRESULT_H_
/*****************************************************************************
* $Log: 
*  3    Biblioteka1.2         2007-03-06 18:02:30  Darko Kolakovic virtual
*       ErrorMessage
*  2    Biblioteka1.1         2007-03-05 09:17:12  Darko Kolakovic ErrorMessage()
*  1    Biblioteka1.0         2007-02-21 09:09:12  Darko Kolakovic 
* $
* Revision 1.1  2007/02/20 22:51:25  ddarko
* Created
*
*****************************************************************************/
