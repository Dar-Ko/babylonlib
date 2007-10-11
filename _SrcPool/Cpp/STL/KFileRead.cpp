/*$Workfile: KFileRead.cpp$: implementation file
  $Revision: 4$ $Date: 2002-08-19 10:44:35$
  $Author: Darko Kolakovic$

  Reads text files.
  Copyright: CommonSoft Inc.
  Feb. 2k2 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTypedef.h"  //LPCTSTR typedef
#include "KTrace.h"

#include <new>      //std::nothrow
#include <fstream>  //std::ifstream or wifstream
#include "KOStream.h"
using namespace std;

LPTSTR FileRead(LPCTSTR szFileName,LPTSTR szBuffer = NULL,int iCount = -1);

//FileRead()-------------------------------------------------------------------
/*Reads text from an existing file. If szBuffer is NULL, new buffer will be
  reserved to hold data and it is caller responsibility to delete buffer and
  release memory resource before program exits. 

  Returns: pointer to zero-terminated string holding data read from the given
  file, or NULL if parameters are invalid, or file could not be open.

  Note: uses Standard Template Library (STL).

  Example:
    bool ReadText(LPCTSTR szFileName)
      {
      using namespace std;
        //Read text
      char* szText = FileRead(szFileName);
      if(szText == NULL)
        {
        cout << "Cannot open file " << szFileName << std::endl;
        return false;
        }

      cout << szText;
      delete szText;
      return true;
      }
 */
LPTSTR FileRead(LPCTSTR szFileName, //[in] zero-terminated string containing
                                    //a file path
               LPTSTR szBuffer,     //[in] = NULL; pointer to space reserved 
               //for data. If NULL function will allocate space for entire file.
               int iCount           //[in] = -1 number of bytes to read from
               //file. If szBuffer is NULL and iCount is -1, entire file will be
               //stored in the memory. If szBuffer is pointer to previously 
               //allocated buffer, iCount have to be a positive number less or 
               //equal to buffer size. The terminating zero is included 
               //in iCount.
               ) 
{
ASSERT(!((szBuffer != NULL) && (iCount < 0)));
if ((szBuffer != NULL) && (iCount < 0))
  return NULL; //Parameters are not valid
if(iCount == 0)
  return szBuffer; //Nothing to do

if (szFileName != NULL)
  {
  tifstream fileInput;  //Input stream

  #ifdef _UNICODE
    //Convert file name to SBCS text
    /*Note: wide characters STL streams does not have a constructor 
      with wide character file name.
     */
    extern std::string WtoChar(const wchar_t* lpWideCharStr, int iLen = -1);
    string strFileName = WtoChar(szFileName);
    fileInput.open(strFileName.c_str(), ios::in | ios::binary );
  #else //ASCII file
    fileInput.open(szFileName, ios::in | ios::binary );
  #endif

  if(fileInput.is_open())
    {
    if (iCount < 0) //Get length of file
      {
      fileInput.seekg (0, ios::end);
      iCount = fileInput.tellg();
      fileInput.seekg (0, ios::beg);
      }
    if(szBuffer == NULL) //Allocate memory for data and terminating zero
      szBuffer = new(nothrow) TCHAR[iCount+1];
    else
      iCount--; //Make last byte available for terminating zero.

    if(szBuffer != NULL)
      {
        //Read data block
      fileInput.read (szBuffer,iCount);
      szBuffer[iCount] = '\0'; //Set terminating zero
      }
    fileInput.close();
    return szBuffer;
    }
  }
return NULL;
}

///////////////////////////////////////////////////////////////////////////////
