/*$Workfile: KGetLines.cpp$: implementation file
  $Revision: 7$ $Date: 2004-10-07 12:56:23$
  $Author: Darko$

  Read a line of text from a stream
  CommonSoft Inc.
  Jan 2002 Darko Kolakovic
*/
/* Group=Strings                                                             */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER /*MS VC/C++ - Disable warning */
    //Fix for the warning(4786) cannot debug code with symbols longer
    //than 255 characters
  #pragma warning (disable: 4786)
#endif

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif


#include <vector>
#include <fstream>
#include <string>
#include "STL/KOStream.h" //streams with generic character mapping

bool GetLines(tifstream& fileSource,
              std::vector<tstring>& arrayLine,
              int iCount = -1);
//GetLines()--------------------------------------------------------------------
/*Functions scans a stream until the end of line (EOL) or the end of file (EOF).
  Up to iCount lines are stored in the given vector. If iCount is negative
  number, the entire file is parsed and stored in the arrayLine.

  Returns: true if more lines are to be read, or false if end-of-file has been
  reached.

  Note: uses Standard Template Library (STL).

  Example:
    #include <string>
    #include <vector>
    #include <iostream>
    #include <fstream>
    int main(int   argc,  char* argv[] )
      {
      std::string strFileName;

      if(argc == 2) //Get file name from command line
        strFileName = argv[1];
      else
        {
        std::cout << "Enter File Name: ";
        std::cin  >> strFileName;
        }

      std::vector<std::string> arrayLine;
      //Open source file
      std::ifstream fileSource(strFileName.c_str());
      if(fileSource != NULL)
        {
        GetLines(fileSource, arrayLine));
        //Do something with array
        fileSource.close();
        return EXIT_SUCCESS;
        }
      std::cout << "Cannot open file " << strFileName << std::endl;
      return EXIT_FAILURE; //Failed to open source file
      }

 */
bool GetLines(tifstream& fileSource,   //[in/out] file stream to parse
             std::vector<tstring>& arrayLine,  //[out] resulting array
                                                   //with text lines
             int iCount //[in] = -1 number of lines to read; if iCount is -1
                        //entire file would be stored in the arrayLine
             )
{
bool bResult;
while((bResult = !fileSource.eof()) && (iCount != 0))
  {
  tstring strLine;
  std::getline(fileSource, strLine);
  arrayLine.push_back(strLine);
  iCount --;
  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         8/12/2003 2:02:41 PM Darko           comment
 *  1    Biblioteka1.0         2/17/2002 3:15:51 AM Darko
 * $
 *****************************************************************************/
