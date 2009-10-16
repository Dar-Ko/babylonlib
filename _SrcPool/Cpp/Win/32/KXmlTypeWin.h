/*$Workfile: KXmlTypeWin.h$: header file
  $Revision: 17$ $Date: 2007-05-22 17:41:20$
  $Author: Darko Kolakovic$

  Type definitions for the XML content handler
  Copyright: CommonSoft Inc
  2005-04-01 Darko Kolakovic
 */
// Group=Windows

#ifndef _KXMLTYPEDEFWIN32_H_
    //$Workfile: KXmlTypeWin.h$ sentry
  #define _KXMLTYPEDEFWIN32_H_

#if !defined(_WIN32)
  #error 'Microsoft Windows 32-bit is required platform'
#endif

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _MSC_VER //Microsoft Visual Studio C++ compiler
  #ifdef _UNICODE
    #ifndef UNICODE
      //To enable Unicode for some Microsoft Visual C/C++ header files,
      //the UNICODE definition is required
      #define UNICODE
    #endif
  #endif

  #if _MSC_VER < 1300
    //Visual C++, 32-bit, version 6.0 or less
    //Disable warning C4786: identifier was truncated to '255' characters in
    //the browser information
    #pragma warning( disable : 4786 )
  #endif
#endif  //_MSC_VER

#define _USE_STL //TODO: Replace STL/KXmlElementVector.h with ATL Array D.K.

#include "KXmlStringData.h" //CXmlStringData class

//-----------------------------------------------------------------------------
#ifndef CXmlString
  #if _MSC_VER >= 1300
    //Visual C++ .Net 2002, 32-bit, version 7.0
    #include <atlstr.h> //Non-MFC string objects
    //ATL CStringT template class is used as string handler (ATL v7.1)
    //include <atlstr.h> for non-MFC string objects or <cstringt.h> for
    //MFC-only string objects.

      //ATL wide-character string handler
    typedef CStringT< wchar_t, StrTraitATL<wchar_t> > CXmlString;
    //!todo: CStringT can't convert to LPCTSTR under build with Multi-Byte Character Set (MCBS) (MSVC.Net)
  #else
    //Visual C++, 32-bit, version 6.0-
    #if defined (_AFXDLL) || defined (_AFX) || defined (USE_MFC)
      //Microsoft Foundation Class Library (MFC) is required for the CString
      #include <afxwin.h>
    #else
      //Windows Template Library (WTL) is required for the CString
      #include <atlbase.h>
      #include <atlapp.h> //Requires Windows Template Library (WTL v7.1) 
      #if (_ATL_VER < 0x0700)
        //Windows Template Library (WTL) main module. See <atlmisc.h>
        extern CAppModule _Module;
      #endif
      #include <atlmisc.h>
    #endif
      //WTL wide-character string handler
    typedef CString CXmlString;
  #endif

  //XML wide-character string handler type
  #define CXmlString CXmlString
#endif


//-----------------------------------------------------------------------------
#ifndef CXmlStringArray
  #if _MSC_VER >= 1300
    //Visual C++ .Net 2002, 32-bit, version 7.0
    #include <atlcoll.h> //CAtlList template
    //ATL CAtlList template class is used as string collection (ATL v7.1)

      //ATL string collection used in XML processing
    typedef CAtlArray< CXmlString > CXmlStringArray;
  #else
    //Visual C++, 32-bit, version 6.0-
    #if defined (_AFXDLL) || defined (USE_MFC)
      #include <afxcoll.h>
      class CXmlStringArray: public CStringArray
        {
        public:
          //Returns the number of array elements.
        INT_PTR GetCount()
          {
          return GetSize();
          }
        };
    #else
      //Windows Template Library (WTL) is required for the CSimpleArray
      #include <atlbase.h>
      //WTL string collection used in XML proccessing
      class CXmlStringArray: public CSimpleArray< CXmlString >
        {
        public:
          //Returns the number of array elements.
        int GetCount()
          {
          return GetSize();
          }
        CXmlString& GetAt(unsigned int nIndex)
          {
          return (*this)[nIndex];
          }
        };
    #endif
  #endif
      //XML string collection type
  #define CXmlStringArray CXmlStringArray
#endif

//-----------------------------------------------------------------------------
#ifndef CXmlAttributeList
  #include "KXmlAttribute.h"  //CXmlAttribute class

  #if defined(_STL) || defined(_USE_STL)
      //TODO: make an ATL implementation for TXmlElementList instead STL
      //STL element collection used in XML processing
    #include  "STL/KXmlAttributeVector.h"
  #else
    #error 'Current implementation requires _USE_STL definition.'
  #endif //_STL

      //XML attribute collection type
  #define CXmlAttributeList CXmlAttributeList
#endif

//-----------------------------------------------------------------------------
#ifndef TXmlElementList
  /*Interface for the XML Element Collection
  template<typename XMLNODE> class IXmlElementList
    {
    public:
      virtual bool Find(const CXmlString& strElementName) = 0;
      //bool GetItem(const CXmlString& strElementName, XMLNODE& xmlResult) = 0;
      virtual XMLNODE& GetItem(const CXmlString& strElementName,
                        unsigned int nIndex = 0) = 0;
      virtual void RemoveItem(const CXmlString& strElementName,
                      unsigned int nIndex = 0) = 0;
      virtual XMLNODE& Append(XMLNODE& xmlElement) = 0;
      virtual size_t Enumerate(const wchar_t* szElementName = NULL) = 0;
      virtual int GetCount() = 0;
      virtual XMLNODE& GetAt(const size_t nIndex) = 0;
    };
*/
  class CXmlNode; //Forward reference
  #if defined(_STL) || defined (_USE_STL)
      //TODO: make an ATL implementation for TXmlElementList instead STL
      //STL element collection used in XML processing
    #include  "STL/KXmlElementVector.h"
    //XML element collection used in XML processing.
    //Note: implementation depends of the compiling environment
    typedef TXmlElementListVector< CXmlNode, int > CXmlElementList;
  #else
    #error 'Current implementation requires _USE_STL definition.'
  #endif //_STL || _USE_STL

      //XML element collection type
  #define TXmlElementList TXmlElementList
#endif

///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLTYPEDEFWIN32_H_
/*****************************************************************************
 * $Log:
 *  8    Biblioteka1.7         2005-04-19 00:16:35  Darko           GetAt()
 *  7    Biblioteka1.6         2005-04-18 01:19:46  Darko           modified
 *       GetItem()
 *  6    Biblioteka1.5         2005-04-14 09:02:55  Darko           (int)size_t
 *  5    Biblioteka1.4         2005-04-13 15:08:23  Darko Kolakovic fixed
 *       CXmlAttributeList method access
 *  4    Biblioteka1.3         2005-04-12 17:47:13  Darko Kolakovic TRACE fix
 *  3    Biblioteka1.2         2005-04-08 12:32:33  Darko Kolakovic TXmlElementList
 *  2    Biblioteka1.1         2005-04-07 12:39:51  Darko Kolakovic _ATL_VER <
 *       0x0700 dependency
 *  1    Biblioteka1.0         2005-04-06 14:48:20  Darko Kolakovic
 * $
 *****************************************************************************/
