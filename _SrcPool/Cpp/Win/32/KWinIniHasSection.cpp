/*$RCSfile: KWinIniHasSection.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/09/17 21:27:59 $
  $Author: ddarko $

  Browse section names in a configuration file (.INI format)
  Copyright: CommonSoft Inc.
  2005-05-05  Darko Kolakovic
 */

// Group=Windows

#include "stdafx.h" // MFC/ATL core and standard components
#include "KWinStrArray.h" //CStringArray class

#ifdef _USE_ATL
  #pragma warning(disable: 4127) //warning C4127: conditional expression is constant
//  #include <atlfile.h> //CAtlFile class
  #pragma warning(default: 4127)
#endif

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE ATLTRACE
  #endif
  #ifndef TRACE1
    #define TRACE1 ATLTRACE
  #endif
  #ifndef ASSERT
    #define ASSERT ATLASSERT
  #endif

#endif

//-----------------------------------------------------------------------------
/*Verifies if the initialization file contains the specified configuration
  section.
  The function is not case-sensitive; the section name can be a combination
  of uppercase and lowercase letters.

  Initialization file have following format:
     [Section1]
     Key1=Value1
     Key2=Value2
     ...
     [Section2]
     Key3=Value3
     ...

  Returns true if the file have at least one section paragraph with specified name,
  otherwise returns false.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win16, Win32).
 */
bool HasIniSection(LPCTSTR szFilename, //[in] name of the initialization file.
                    //If this parameter does not contain a full path to the file,
                    //the system searches for the file in the Windows directory.
                   LPCTSTR szSection   //[in] null-terminated string that
                    //specifies the name of the section containing the key name.
                   )
{
#ifdef _UNICODE
  TRACE1(_T("HasIniSection(%ws)\n"), szSection);
#else
  TRACE1(_T("HasIniSection(%s)\n"), szSection);
#endif

bool bResult = false;
extern int GetIniSectionList(CStringArray& strResult,
                             LPCTSTR szFilename,
                             LPCTSTR szFilter,
                             const int nPosition  = -1);
CStringArray listSections;
if((szSection != NULL) && (szSection[0] != _T('\0')) )
  {
  if (GetIniSectionList(listSections, szFilename, szSection, 0) > 0)
    {
    int i = 0;
    while (i < listSections.GetSize())
      {
      if (listSections[i] == szSection)
        {
        bResult = true;
        break;
        }
      i++;
      }
    }
  }
return bResult;
}
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 $Log: KWinIniHasSection.cpp,v $
 Revision 1.2  2009/09/17 21:27:59  ddarko
 Changed declaration

 Revision 1.1  2009/09/16 21:29:36  ddarko
 Created

 ******************************************************************************/
