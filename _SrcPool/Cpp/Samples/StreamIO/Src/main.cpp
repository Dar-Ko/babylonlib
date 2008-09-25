/*$Workfile: main.cpp$: implementation file
  $Revision: 11$ $Date: 2007-02-02 13:30:43$
  $Author: Darko Kolakovic$

  Illustrates how to use the getline function to read a line of text from the stream.
  Compile options needed: /GX
  Copyright: CommonSoft Inc
  May '97 Darko Kolakovic
*/

// Group=Examples

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

  #ifdef _MSC_VER /*MS VC/C++ - Disable warning */
    //Fix for the warning(4786) cannot debug code with symbols longer
    //than 255 characters
  #pragma warning (disable: 4786)
  #endif
#endif

#include "stdafx.h"

extern int TestCommonStreamIO();
extern int TestCommonStreamIO(LPCTSTR szFileName);

//main()-----------------------------------------------------------------------
/*Test stream manipulation routines.

  Returns: EXIT_SUCCESS if succesful, otherwise returns EXIT_FAILURE.
 */
int main(int argc,     //[in] specifies how many arguments are passed to the
                       //program from the command line. The value of argc is
                       //at least one: the program name.
         TCHAR* argv[]  //[in] the program arguments as an array of pointers
                       //to null-terminated strings. The first string 
                       //  - (argv[0]) is the program name.
                       //  - (argv[1]) file name
                       //The end of the array (argv[argc]) is indicated by 
                       //a NULL pointer.
         )
{
tstring strFileName;

if(argc == 2) //Get file name from command line
  strFileName = argv[1];
else
  {
  //Get file name from the user or skip it with CR character
  std::_tcout << _T("Enter File Name: ");
  TCHAR ch;
  while (std::_tcin.get(ch) && (ch != _T('\n')))
    {
    std::_tcout.put(ch);
    strFileName += ch;
    }
  }

if (strFileName.empty())
  return TestCommonStreamIO(); //Test predefined samples
else
  return TestCommonStreamIO(strFileName.c_str());

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  10   Biblioteka1.9         2004-10-06 23:42:43  Darko           deleted old
 *       headers
 *  9    Biblioteka1.8         2004-10-06 16:01:46  Darko           Unicode mapping
 *  8    Biblioteka1.7         2004-10-04 12:49:14  Darko           Renamed  test
 *       script to TestCommonStreamIO
 *  7    Biblioteka1.6         2004-09-29 13:23:31  Darko           improved tests
 *  6    Biblioteka1.5         2004-09-28 14:01:40  Darko           Moved test
 *       cases to TestStreamIOCommon.cpp
 *  5    Biblioteka1.4         2004-09-27 13:42:46  Darko           fixed
 *       preprocessor bug
 *  4    Biblioteka1.3         2002-09-16 17:57:53  Darko Kolakovic
 *  3    Biblioteka1.2         2002-07-16 01:39:21  Darko           Updated comment
 *  2    Biblioteka1.1         2002-02-17 03:17:41  Darko           GetLines()
 *  1    Biblioteka1.0         2002-02-04 19:46:46  Darko
 * $
 *****************************************************************************/
