/*$Workfile: KGetLines.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:36:18 $
  $Author: ddarko $

  Read a line of text from a stream
  CommonSoft Inc.
  Jan 2002 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */


#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

  #ifdef _MSC_VER /*MS VC/C++ - Disable warning */
    //Fix for the warning(4786) cannot debug code with symbols longer 
    //than 255 characters
  #pragma warning (disable: 4786)
  #endif
#endif

#include <vector>
#include <fstream>
#include <string>

bool GetLines(std::ifstream& fileSource, 
              std::vector<std::string>& arrayLine,
              int iCount = -1);
//GetLines()--------------------------------------------------------------------
/*Functions scans in a stream until finds end of line characters or end of 
  file. Up to iCount lines are stored in the given vector. If iCount is negative
  number, the entire file is parsed and stored in the arrayLine.

  Returns: true if more lines are to be read, or false if end-of-file has been 
  reached. Lines
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
        GetLines(fileSource,arrayLine));
        //Do something with array
        fileSource.close();
        return EXIT_SUCCESS;
        }
      std::cout << "Cannot open file " << strFileName << std::endl;
      return EXIT_FAILURE; //Failed to open source file
      }

 */
bool GetLines(std::ifstream& fileSource,   //[in/out] file stream to parse
             std::vector<std::string>& arrayLine,  //[out] resulting array
                                                   //with text lines
             int iCount //[in] = -1 number of lines to read; if iCount is -1
                        //entire file would be stored in the arrayLine
             )
{
bool bResult;
while((bResult = !fileSource.eof()) && (iCount != 0))
  {
  std::string strLine;
  std::getline(fileSource, strLine);
  arrayLine.push_back(strLine);
  iCount --;
  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         17/02/2002 2:15:51 AMDarko           
 * $
 *****************************************************************************/
