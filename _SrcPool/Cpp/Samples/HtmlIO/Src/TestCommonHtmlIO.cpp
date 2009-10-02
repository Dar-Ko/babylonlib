/*$Workfile: TestCommonHtmlIO.cpp$: implementation file
  $Revision: 5$ $Date: 2007-02-02 13:23:49$
  $Author: Darko Kolakovic$

  Test HTML and XML parsing.
  Copyright: CommonSoft Inc.
  2005-03-16 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

extern bool TestXmlString();
extern bool TestXmlNode();
extern bool TestXmlDocument(int argc, TCHAR* argv[]);
extern bool TestXmlParser(int argc, TCHAR* argv[]);
extern bool TestXmlFinder(int argc, TCHAR* argv[]);

int TestCommonHtmlIO(int argc, TCHAR* argv[]);
int TestCommonHtmlIO();

//-----------------------------------------------------------------------------
/*validates HTML and XML parsing.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonHtmlIO()
{
return TestCommonHtmlIO(0, NULL);
}

//-----------------------------------------------------------------------------
/*validates HTML and XML parsing.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonHtmlIO(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                      TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                      )
{
TsWriteToViewLn(_T("Validation of HTML and XML parsers"));
TsWriteToViewLn(_T(""));

int iTestCount = 0;

//Test basic string handling
if (TestXmlString())
  {
  TsWriteToViewLn(LOG_SUCCESS);
  TsWriteToViewLn(_T(""));
  }
else
  {
  TsWriteToViewLn(LOG_FAILURE);
  return EXIT_FAILURE + 1 + iTestCount++;
  }

//Test XML Node manipulation
if (TestXmlNode())
  {
  TsWriteToViewLn(LOG_SUCCESS);
  TsWriteToViewLn(_T(""));
  }
else
  {
  TsWriteToViewLn(LOG_FAILURE);
  return EXIT_FAILURE + 1 + iTestCount++;
  }

//Test simple document reader
if (TestXmlDocument(argc, argv))
  {
  TsWriteToViewLn(LOG_SUCCESS);
  TsWriteToViewLn(_T(""));
  }
else
  {
  TsWriteToViewLn(LOG_FAILURE);
  return EXIT_FAILURE + 1 + iTestCount++;
  }

//Test parser creation
if (TestXmlParser(argc, argv))
  {
  TsWriteToViewLn(LOG_SUCCESS);
  TsWriteToViewLn(_T(""));
  }
else
  {
  TsWriteToViewLn(LOG_FAILURE);
  return EXIT_FAILURE + 1 + iTestCount++;
  }

//Test finding XML elements
if (TestXmlFinder(argc, argv))
  {
  TsWriteToViewLn(LOG_SUCCESS);
  TsWriteToViewLn(_T(""));
  }
else
  {
  TsWriteToViewLn(LOG_FAILURE);
  return EXIT_FAILURE + 1 + iTestCount++;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-03-11 16:17:25  Darko Kolakovic Added Console
 *       project
 *  1    Biblioteka1.0         2005-03-11 02:13:52  Darko
 * $
 *****************************************************************************/
