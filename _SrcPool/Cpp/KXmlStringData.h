/*$Workfile: KXmlStringData.h$: header file
  $Revision: 4$ $Date: 2005-04-06 14:45:32$
  $Author: Darko Kolakovic$

  file description
  Copyright: CommonSoft Inc
  2005-03-16 Darko Kolakovic
 */
/* Group=Strings                                                            */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KXMLSTRINGDATA_H_
    //$Workfile: KXmlStringData.h$ sentry
  #define _KXMLSTRINGDATA_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KStrConvert.h" //CWideToStr class

///////////////////////////////////////////////////////////////////////////////
/*CXmlStringData class is used in processing XML documents to translate character
  arrays to wide character strings required by the XML standard.

  See also: CStrToWide, CWideToStr
 */
class CXmlStringData
{
public:
  CXmlStringData();
  CXmlStringData(const char*    strSource, int iLength = -1);
  CXmlStringData(const wchar_t* strSource, int iLength = -1);
  CXmlStringData(const CXmlStringData& dtValue);

  virtual ~CXmlStringData();
  CXmlStringData& operator=(const CXmlStringData& strValue);
  operator const wchar_t* ();
  operator const char* ();

protected:
  wchar_t* m_wszData; //text data container

private:
  char*    m_szData;  //translated text data
};

///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLSTRINGDATA_H_
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-04-06 14:45:32  Darko Kolakovic Renamed class
 *       to avoid colision with other xml types
 *  3    Biblioteka1.2         2005-04-06 14:44:26  Darko Kolakovic 
 *  2    Biblioteka1.1         2005-03-27 02:17:42  Darko           operator const
 *       char*()
 *  1    Biblioteka1.0         2005-03-26 01:10:10  Darko           
 * $
 *****************************************************************************/
