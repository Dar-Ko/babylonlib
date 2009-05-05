/*$RCSfile: main.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/05/05 20:15:34 $
  $Author: ddarko $

  Illustrates how to extract WMP tags.
  Copyright: CommonSoft Inc
  2009-05-04 Darko Kolakovic
*/

// Group=Examples

#ifdef _DEBUG
  #if _MSC_VER == 1200 /*MS VC/C++ 6.0*/
    //Fix for the warning(4786) cannot debug code with symbols longer
    //than 255 characters
  #pragma warning (disable: 4786)
  #endif
#endif

#include "stdafx.h"
#include "STL/KOStream.h"

extern int BrowseWmpTags(LPCTSTR szFileList);

//-----------------------------------------------------------------------------
/*
  Returns: EXIT_SUCCESS if succesful, otherwise returns EXIT_FAILURE.
 */
int _tmain(int argc,   //[in] specifies how many arguments are passed to the
                       //program from the command line. The value of argc is
                       //at least one: the program name.
           TCHAR* argv[]  //[in] the program arguments as an array of pointers
                       //to null-terminated strings. The first string
                       //  - (argv[0]) is the program name.
                       //  - (argv[1]) File name
                       //The end of the array (argv[argc]) is indicated by
                       //a NULL pointer.
         )
{
TRACE0(_T("_tmain()\n"));
//Parse command line input
const int CMDLINE_FILENAME = 1; //File Name command line argument index
#define PROMPT_FILENAME _T("Enter file name: ") //TODO: move strings to resource file

TCHAR ch = _T('\0'); //keyboard echo
CString strFilename;

if(argc >= (CMDLINE_FILENAME + 1)) //Get File Name
  {
  strFilename = argv[CMDLINE_FILENAME];
  }
else //Get VID from the user or skip it with CR character
  {
  std::_tcout << PROMPT_FILENAME;
  while (std::_tcin.get(ch) && (ch != _T('\n')))
    {
    std::_tcout.put(ch);
    strFilename += ch;
    }
  }

return BrowseWmpTags(strFilename); //Obtain tags
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: main.cpp,v $
 * Revision 1.1  2009/05/05 20:15:34  ddarko
 * *** empty log message ***
 *
 * Revision 1.3  2008/09/26 21:36:48  ddarko
 * Added new test case
 *
 * Revision 1.2  2008/09/25 21:31:36  ddarko
 * Fixed MSVC6 warnings
 *
 *****************************************************************************/
