/*$Workfile: KHresult.h$: header file
  $Revision: 1.5 $ $Date: 2007/03/11 06:16:01 $
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
/*{group=Windows}
  The CHresult class stores the status code indicating the reason for the
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

  See also: <winerror.h>, CAtlException class members, AtlThrow, TESTHR()
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
  virtual void Throw(LPCTSTR szFilename = NULL, unsigned int iLine = 0);
  virtual LPCTSTR ErrorMessage(LPCTSTR szFilename = NULL, unsigned int iLine = 0) const;
  virtual HRESULT SetErrorInfo(LPCTSTR szSource, LPCTSTR szDescription);

  //Attributes
protected:
   HRESULT m_hr; //variable of type HRESULT created by the object and used
                 //to store the error condition.
   mutable LPTSTR m_pszMsg; //buffer allocated with LocalAlloc() that receives
                            //the error description,
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
if (m_pszMsg != NULL)
  LocalFree(m_pszMsg);
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
inline void CHresult::Throw(LPCTSTR szFilename,// = NULL [in]
                            unsigned int iLine // = 0 [in]
                            ) throw(...)
{
AtlThrow(m_hr);
}

//-----------------------------------------------------------------------------
/*Retrieves the error desription of the HRESULT member.
  If szFilename is not null, the following will be appended to the description:
        szFilename(iLine).

  Returns: string message for the HRESULT.
 */
inline LPCTSTR CHresult::ErrorMessage(LPCTSTR szFilename,// = NULL [in] source
                                      //file name or module name
                                      unsigned int iLine // = 0 [in] line number
                                      //or custom identifier
                                      ) const
{
//Borrowed from <comdef.h>
/*The function allocates a buffer large enough to hold the formatted message
  and places a pointer to the allocated buffer at the address specified by m_pszMsg.
  The caller should use the LocalFree function to free the buffer when it is no
  longer needed or leave cleaning to the destructor.
 */
if (m_pszMsg != NULL) //Create new error message
  {
  LocalFree(m_pszMsg);
  m_pszMsg = NULL;
  }

/*Note: If error description is formatted similar to "file: %1!s!, line: %2!d!",
    the arguments will be inserted in the output message
      va_list vaArgList;
      va_start(vaArgList, szFilename);
      ...
      FormatMessage(..., &vaArgList);
  */
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
              FORMAT_MESSAGE_FROM_SYSTEM,
              NULL,
              m_hr, //message identifier
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
  const unsigned int ERRMSG_FIXEDSIZE = 32;
  unsigned int nLen = (szFilename == NULL) ?
      0 : (ERRMSG_FIXEDSIZE + _tcslen(szFilename) + 8 + 16);

  m_pszMsg = (LPTSTR)LocalAlloc(0, nLen * sizeof(TCHAR));
  if (m_pszMsg != NULL)
    {
    LPTSTR szFormat;
    //Check errors for Custom Interfaces Facility of FACILITY_ITF (see winerror.h)
    //Error codes for this facility could have duplicate descriptions (see MSDN Q183216)
    const unsigned short E_ITF_FIRST = 0x200; //first error in the range
    const HRESULT WCODE_HRESULT_FIRST = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, E_ITF_FIRST);
    const HRESULT WCODE_HRESULT_LAST  = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF+1, 0);
    if (m_hr >= WCODE_HRESULT_FIRST &&  m_hr < WCODE_HRESULT_LAST)
      szFormat = (szFilename == NULL) ?
        _T("COM Interface error 0x%0lX") : _T("COM Interface error 0x%0lX\n%s (%d)");
    else
      szFormat = (szFilename == NULL) ?
        _T("Unknown COM error 0x%0lX") : _T("Unknown COM error 0x%0lX\n%s (%d)");

    wsprintf(m_pszMsg, szFormat, m_hr, szFilename, iLine);
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

#include <comdef.h> //Native C++ compiler COM support
//-----------------------------------------------------------------------------
/*{group=Diagnostic}
  Validates the result returned by a COM object operation. If hResult is not
  S_OK, throws _com_error exception.

  Note: Microsoft Windows specific (Win).
        and uses Active Template Library (ATL).

  History: Microsoft MSDN Sample

  See also: CHresult
 */
inline void TESTHR(HRESULT hResult //[in] result of COM Objects operation
                  ) throw(...)
{
if (FAILED(hResult))
  _com_issue_error(hResult);
};

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
