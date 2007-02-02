/*$Workfile: KXmlSaxErrorHandler.cpp$: implementation file
  $Revision: 7$ $Date: 2005-04-26 01:21:00$
  $Author: Darko$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2005-03-27 Darko Kolakovic
 */

#include "stdafx.h"
//D.K. #include <atltrace.h> //ATLTRACE2 macro is in <atlbase.h>
#include <atlbase.h>
#include "Win/32/KXmlTypeWin.h"   //CXmlString typedef
#include "KXmlSaxErrorHandler.h"  //CXmlSaxErrorHandler class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CXmlSaxErrorHandler class
#include <atlconv.h>

//-----------------------------------------------------------------------------
/*Handlees notification of a recoverable error.

  Returns: S_OK when the error is handled and parsing may proceed or E_FAIL if 
  the parse operation should be aborted.
 */
HRESULT STDMETHODCALLTYPE  CXmlSaxErrorHandler::error (
                        struct ISAXLocator* pLocator,     //[in] line and column 
                                         //of the error
                        const wchar_t* pwchErrorMessage, //[in] error information
                        HRESULT hrErrorCode                //[in] error code 
                                         //identifying the reason for the error
                        )
{
ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlSaxErrorHandler::error()\n"));

int iLine, iCol; //line and column where the error occured
pLocator->getLineNumber(&iLine);
pLocator->getColumnNumber(&iCol);
//CStringT< TCHAR, StrTraitATL<TCHAR> > strError; !todo: D.K. Replaced TCHAR with wchar_t; test the benefits
CXmlString strError;
//!todo: Multi-Byte Character Set (MBCS) build for CXmlString can't convert _T("...") to PCXSTR ATL 7.1 - MSVC.Net) 
//#ifdef _UNICODE
  strError.Format(_T("line %4d,%3d (%08X): %ls "),
                  iLine, 
                  iCol, 
                  hrErrorCode,
                  (wchar_t*)(pwchErrorMessage)
                  );
/*#else //SBCS
  USES_CONVERSION;
  strError.Format(_T("line %4d,%3d (%08X): %s "),
                  iLine, 
                  iCol, 
                  hrErrorCode,
                  W2A(pwchErrorMessage)
                  );
#endif
*/
const wchar_t* pwchSystemId = NULL; //system identifier for the current document event
if (pLocator->getSystemId(&pwchSystemId) != S_OK)
  pwchSystemId = L"null";

const wchar_t* pwchPublicId = NULL; //public identifier for the current document event
if (pLocator->getPublicId(&pwchPublicId) != S_OK)
  pwchPublicId = L"null";

ATLTRACE2(atlTraceCOM, 0, _T("  SystemId <%s>, PublicId <%s>\n  %s"), 
          pwchSystemId, 
          pwchPublicId,
          (LPCTSTR)strError
          );

return S_OK;
}

//-----------------------------------------------------------------------------
/*Handles notification of a nonrecoverable error.
  This notification of a nonrecoverable error corresponds to the definition of 
  a fatal error in section 1.2 of the Worldwide Web Consortium (W3C) XML 1.0 
  Recommendation. For example, a parser would use this method to report the 
  violation of a well-formedness constraint. The application must assume that 
  the document is unusable after the parser has invoked this method. 
  Parsing should continue only to collect additional error messages. 
  In addition, the parser is free to stop reporting any other events once this 
  method has been invoked.

  Returns: S_OK when the error is handled, but parsing stops for fatal errors 
  or E_FAIL if the parse operation should be aborted.

  See also: http://www.w3.org/TR/REC-xml/#sec-terminology 
  Extensible Markup Language (XML) 1.0, W3C Recommendation, 1.2 Terminology
 */
HRESULT STDMETHODCALLTYPE  CXmlSaxErrorHandler::fatalError (
                        struct ISAXLocator* pLocator,     //[in] line and column 
                                         //of the error
                        const wchar_t* pwchErrorMessage, //[in] error information
                        HRESULT hrErrorCode                //[in] error code 
                                         //identifying the reason for the error
                        )
{
ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlSaxErrorHandler::fatalError()\n"));

int iLine, iCol; //line and column where the error occured
pLocator->getLineNumber(&iLine);
pLocator->getColumnNumber(&iCol);

//CStringT< TCHAR, StrTraitATL<TCHAR> > strError; !todo: D.K. Replaced TCHAR with wchar_t; test the benefits
CXmlString strError;

//!todo: Replace W2A macro with something more inteligent
//!todo: Multi-Byte Character Set (MBCS) build for CXmlString can't convert _T("...") to PCXSTR ATL 7.1 - MSVC.Net) 
//#ifdef _UNICODE
  strError.Format(_T("line %4d,%3d (%08X): %ls "),
                  iLine, 
                  iCol, 
                  hrErrorCode,
                  (wchar_t*)(pwchErrorMessage)
                  );
/*#else //SBCS
  #if _MFC_VER < 0x0700
    USES_CONVERSION;
    strError.Format(_T("line %4d,%3d (%08X): %s "),
                    iLine, 
                    iCol, 
                    hrErrorCode,
                    W2A(pwchErrorMessage)
                    );
  #else
    strError.Format(_T("line %4d,%3d (%08X): %s "),
                    iLine, 
                    iCol, 
                    hrErrorCode,
                    CW2A(pwchErrorMessage)
                    );
  #endif
#endif
*/

const wchar_t* pwchSystemId = NULL; //system identifier for the current document event
if (pLocator->getSystemId(&pwchSystemId) != S_OK)
  pwchSystemId = L"null";

const wchar_t* pwchPublicId = NULL; //public identifier for the current document event
if (pLocator->getPublicId(&pwchPublicId) != S_OK)
  pwchPublicId = L"null";

ATLTRACE2(atlTraceCOM, 0, _T("  SystemId <%s>, PublicId <%s>\n  %s"), 
          pwchSystemId, 
          pwchPublicId,
          (LPCTSTR)strError
          );

m_strError.Add(strError);

return S_OK;
}

//-----------------------------------------------------------------------------
/*Handles notification of a warning.
  The reader uses this method to report conditions that are not errors as 
  defined by the XML 1.0 Recommendation. The default behavior is to take no action. 
  The reader must continue to provide normal parsing events after invoking this 
  method. It should still be possible for the application to process the document 
  through to the end.

  Note: This method is not called in the MsXml 3.0/4.0 implementation of the 
        Simple API for XML (SAX2).

  Returns: S_OK when the error is handled and parsing may proceed or E_FAIL if 
  the parse operation should be aborted.
 */
HRESULT STDMETHODCALLTYPE  CXmlSaxErrorHandler::ignorableWarning (
                        struct ISAXLocator* pLocator,     //[in] line and column 
                                         //of the error
                        const wchar_t* pwchErrorMessage, //[in] error information
                        HRESULT hrErrorCode                //[in] error code 
                                         //identifying the reason for the error
                        )
{
ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlSaxErrorHandler::ignorableWarning()\n"));

return S_OK;
}

//-----------------------------------------------------------------------------
/*Gets number of gathered error messages.

  Returns: error count.
 */
unsigned int CXmlSaxErrorHandler::GetCount()
{
    //Gets number of elements in this array.
return (unsigned int)m_strError.GetCount();
}

//-----------------------------------------------------------------------------
/*Handles notification of a warning.
 */
LPCTSTR CXmlSaxErrorHandler::GetErrorMessage(unsigned int nIndex //[in] zero-based
                                            //index of the error message
                                            )
{
LPCTSTR szResult;
if (nIndex >= m_strError.GetCount())
  {
  ATLTRACE2(atlTraceCOM, 
            0, 
            _T("CXmlSaxErrorHandler::GetErrorMessage(nIndex = %d)\n  index out of the range\n"), 
            nIndex);
  szResult = _T("");
  }
else 
  {
  szResult = (LPCTSTR)(m_strError.GetAt(nIndex));
  }
return szResult;
}


///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2005-04-26 01:21:00  Darko           KXmlTypeWin.h
 *  6    Biblioteka1.5         2005-04-14 09:03:04  Darko           comment
 *  5    Biblioteka1.4         2005-04-06 14:51:32  Darko Kolakovic Compiled with
 *       MSVC6
 *  4    Biblioteka1.3         2005-04-04 21:58:39  Darko           return value of
 *       GetErrorMessage()
 *  3    Biblioteka1.2         2005-03-31 03:06:17  Darko           report error()
 *  2    Biblioteka1.1         2005-03-27 23:05:17  Darko           Store error
 *       messages
 *  1    Biblioteka1.0         2005-03-27 02:28:59  Darko           
 * $
 *****************************************************************************/
