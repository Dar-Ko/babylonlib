/*$RCSfile: TestXmlDocument.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/10/02 16:29:53 $
  $Author: ddarko $

  Test simple XML reader
  2009-09-01 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KXmlDocument.h" //CXmlDocument class


#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);

//-----------------------------------------------------------------------------
/*Function validates XML parser framework.

  Returns: true if successful, otherwise returns false.
 */
bool TestXmlDocument(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                       TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                       )
{
TsWriteToView(_T("TestXmlDocument()\r\n"));
bool bRes = true;
TESTENTRY logEntry =
{_T("CXmlDocument:Read()()"), _T("KXmlDocument.cpp"), bRes};

if (argc > 0)
  {
  TsWriteToView(_T("Application "));
  TsWriteToView(argv[0]);
  TsWriteToView(_T(" has "));
  TsWriteToView(argc);
  TsWriteToViewLn(_T(" argument(s)"));
  }

//Create XML reader
CXmlDocument xmlDocument;
//TODO: test parsing doc from buffer

//Test reading from a file
xmlDocument.Read(argv[1]);

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: TestXmlDocument.cpp,v $
 * Revision 1.1  2009/10/02 16:29:53  ddarko
 * Created
 *
 *****************************************************************************/
