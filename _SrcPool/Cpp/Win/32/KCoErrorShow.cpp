/*$Workfile: KCoErrorShow.cpp$: implementation file
  $Revision: 8$ $Date: 2005-04-26 11:28:31$
  $Author: Darko Kolakovic$

  Displays COM Error description
  Copyright: CommonSoft Inc.
  2003-08-09 Darko Kolakovic
 */
// Group=Diagnostic

#include "stdafx.h"
#include "Resource.h" //IDS_FILENOTFOUND
#ifndef _INC_COMDEF
  #include <comdef.h> //_com_error class
#endif

#ifndef __HTMLHELP_H__
  #include <Htmlhelp.h> //HtmlHelp()
#endif
#pragma comment(lib, "HTMLHELP")  //Linking project with the HTMLHELP.LIB file.

#ifdef _DEBUG_TO_LOGFILE
  #include <iostream>  //ofstream
#endif

#ifndef IDS_FILENOTFOUND
  #pragma message("Add IDS_FILENOTFOUND string to the resource")
    //Replacement for IDS_FILENOTFOUND resource string
#define __FILENOTFOUNDSTR__ _T("%s: File Not Found.")
#endif

void ComErrorShow(_com_error& cee,
                  LPCTSTR szHelpFile = NULL, UINT nHelpContext = 0);
extern CString GetFileExt(CString& strFileName);

//-----------------------------------------------------------------------------
/*Displays an error message box with captured COM error description.
  A _com_error object represents an exception condition detected by the
  error-handling wrapper functions in the header files generated from the type
  library or by one of the COM support classes. The _com_error class
  encapsulates the HRESULT error code and any associated IErrorInfo object.

  Note: uses Microsoft Foundation Library (MFC);
        Active Template Library (ATL)
        Microsoft Windows specific (Win).

  See also: DisplayError(), ComProviderErrors()
 */
void ComErrorShow(_com_error& cee, //[in] COM Error exception
                  LPCTSTR szHelpFile, //[in]=NULL fully qualified path
                      //of the Help file .hlp to be used if cee does not have help
                      //on error
                  UINT nHelpContext //[in]=0 Help context identifier for
                      //the error to be used if cee does not have help on error
                  )
{
TRACE(_T("ComErrorShow(%s)\n"), (LPTSTR)cee.Source());
CString strMessage;

if (((LPCTSTR)cee.HelpFile() != NULL ) || (szHelpFile != NULL))
  {
  strMessage.Format( _T("%s\nError 0x%08lx %s\n%s\nMore Help?"), //TODO: Localization D.K.
                    (((LPTSTR)cee.Source() != NULL) ? (LPTSTR)cee.Source() : _T("")),
                    cee.Error(),
                    (LPTSTR)cee.ErrorMessage(),
                    (((LPTSTR)cee.Description() != NULL) ? (LPTSTR)cee.Description() : _T(""))
                    );
  if (AfxMessageBox( strMessage, MB_OKCANCEL | MB_ICONERROR | MB_DEFBUTTON2 ) == IDOK)
    {
    IErrorInfo* piErrorInfo;
    if ( (piErrorInfo = cee.ErrorInfo()) != NULL )
      {
      #ifdef _DEBUG_TO_LOGFILE
        ofstream ofsLog(_T("C:\\CoError.log"), ios::out|ios::app);
        if ( (LPTSTR)cee.Source() )
          ofsLog << _T("Source      = ") << (LPTSTR)cee.Source() << _T('\n');
        if ( (LPTSTR)cee.Description() )
          ofsLog << _T("Description = ") << (LPTSTR)cee.Description() << _T('\n');
      #endif


      BSTR bstrHelpFile;
      if(SUCCEEDED(piErrorInfo->GetHelpFile(&bstrHelpFile)) &&
                  (bstrHelpFile != NULL))
        {
        _bstr_t bstrTmp( bstrHelpFile, false );
        DWORD dwHelpContext;
        piErrorInfo->GetHelpContext(&dwHelpContext);
        TRACE(_T("  Open help %s @ %d\n"),(LPTSTR)bstrTmp, dwHelpContext);
        CString strExt = (LPTSTR)bstrHelpFile;
        strExt = GetFileExt(strExt);
        if (strExt.CompareNoCase(_T("hlp")) == 0)
          {
          ::WinHelp(GetDesktopWindow(),
                  (LPTSTR)bstrTmp,
                  ((dwHelpContext == 0)? HELP_CONTENTS : HELP_CONTEXT),
                  dwHelpContext);
          }
        if (strExt.CompareNoCase(_T("chm")) == 0)
          {
          if(::HtmlHelp(GetDesktopWindow(),
                        (LPTSTR)bstrTmp,
                        ((dwHelpContext == 0)? HH_DISPLAY_TOC : HH_HELP_CONTEXT),
                        dwHelpContext) == NULL)
            {
            #ifdef IDS_FILENOTFOUND
              AfxFormatString1( strMessage, IDS_FILENOTFOUND, (LPTSTR)bstrTmp);
            #else
              strMessage.Format(__FILENOTFOUNDSTR__,(LPTSTR)bstrTmp);
            #endif
            AfxMessageBox(strMessage, MB_OK | MB_ICONERROR );
            }
          }
        }
      else
        {
        if (szHelpFile != NULL)
          {
          if(::HtmlHelp(GetDesktopWindow(),
                        szHelpFile,
                        HH_HELP_CONTEXT,
                        nHelpContext) == NULL)
            if(!::WinHelp(GetDesktopWindow(),
                          szHelpFile,
                          HELP_CONTEXT,
                          nHelpContext))
              {
              #ifdef IDS_FILENOTFOUND
                AfxFormatString1( strMessage, IDS_FILENOTFOUND, szHelpFile);
              #else
                strMessage.Format(__FILENOTFOUNDSTR__, szHelpFile);
              #endif
              AfxMessageBox(strMessage, MB_OK | MB_ICONERROR );
              }
          }
        #ifdef _DEBUG
        else
          {
          if(::HtmlHelp(GetDesktopWindow(),
                        _T("JETERR40.CHM"), //Microsoft Jet Error Message Reference
                        HH_DISPLAY_TOC,
                        0) == NULL)
            {
            #ifdef IDS_FILENOTFOUND
              AfxFormatString1( strMessage, IDS_FILENOTFOUND, _T("JETERR40.CHM"));
            #else
              strMessage.Format(__FILENOTFOUNDSTR__,_T("JETERR40.CHM"));
            #endif
            AfxMessageBox(strMessage, MB_OK | MB_ICONERROR );
            }
          }
        #endif
        }
      piErrorInfo->Release();
      }
    }
  }
else
  {
  strMessage.Format( _T("%s\nError 0x%08lx %s\n%s"), //TODO: Localization D.K.
                    (((LPTSTR)cee.Source() != NULL) ? (LPTSTR)cee.Source() : _T("")),
                    cee.Error(),
                    (LPTSTR)cee.ErrorMessage(),
                    (((LPTSTR)cee.Description() != NULL) ? (LPTSTR)cee.Description() : _T(""))
                    );
  AfxMessageBox( strMessage, MB_OK | MB_ICONERROR );
  }
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  7    Biblioteka1.6         2004-10-01 22:33:50  Darko           stdafx.h
 *  6    Biblioteka1.5         2003-08-19 16:16:34  Darko           Text help file
 *       for exyension .chm
 *  5    Biblioteka1.4         2003-08-14 14:18:00  Darko           removed
 *       OpenHelpChm
 *  4    Biblioteka1.3         2003-08-13 10:53:08  Darko           HtmlHelp()
 *  3    Biblioteka1.2         2003-08-12 13:59:05  Darko           WinHelp for Jet
 *       errors
 *  2    Biblioteka1.1         2003-08-10 05:02:21  Darko           Added
 *       ComProviderErrors()
 *  1    Biblioteka1.0         2003-08-09 17:42:05  Darko
 * $
 *****************************************************************************/

/*-----------------------------------------------------------------------------
#ifndef __AFXDAO_H
  #include <afxdao.h> // MFC DAO Database support
#endif

/ *Depreciated
 * /
void DaoExceptionShow(CDaoException& cde)
{
CString strMessage;
if (cde.m_pErrorInfo != NULL)
  {
  strMessage.Format(_T("Error 0x%08lx %s\n%s\nMore Help?"),
                    cde.m_pErrorInfo->m_lErrorCode
                    (LPCTSTR)cde.m_pErrorInfo->m_strDescription,
                   );

  if (AfxMessageBox(strMessage, MB_OKCANCEL | MB_ICONERROR | MB_DEFBUTTON2 ) == IDOK)
    {
    WinHelp(GetDesktopWindow(),
        cde.m_pErrorInfo->m_strHelpFile,
        HELP_CONTEXT,
        cde.m_pErrorInfo->m_lHelpContext);
    }
  }
else
  {
  strMessage.Format(_T("ERROR:CDaoException\n\n")
                _T("SCODE_CODE      =%d\n")
                _T("SCODE_FACILITY  =%d\n")
                _T("SCODE_SEVERITY  =%d\n")
                _T("ResultFromScode =%d\n"),
                SCODE_CODE      (cde.m_scode),
                SCODE_FACILITY  (cde.m_scode),
                SCODE_SEVERITY  (cde.m_scode),
                ResultFromScode (cde.m_scode));
  AfxMessageBox(strMessage);
  }
}
*/

