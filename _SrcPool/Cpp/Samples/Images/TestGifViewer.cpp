/*$Workfile: H:\_SrcPool\Cpp\Samples\Images\TestGifViewer.cpp$: implementation file
  $Revision: 4$ $Date: 8/5/02 11:33:46 AM$
  $Author: Darko$

  Test of GIF image decoder
  Mar 2k2 D. Kolakovic
*/

// Group=Examples

#include <iostream>
#include <iomanip.h>
#include "KGifViewer.h" //CGifViewer class
#include "KTrace.h"     //TRACE macros

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//TestGifViewer()---------------------------------------------------------------
/*Test of GIF image decoder

  Returns: true if successful, otherwise returns false
 */
bool TestGifViewer(char* szImageFileName, 
                   int iColors //[in] number of colors in the test image 
                                    //palette or -1 to skip testing of palette
                                    //size
                   )
{
cout << "TestGifViewer(" << szImageFileName << ')' <<endl;
bool bRes = false;
//Create empty GIF object
cout << "  Read GIF file" << endl;
CGifViewer gifImage;

if (gifImage.Load(szImageFileName))
  {
  gifImage.Dump();

  if (gifImage.HasGlobalColorTable())
    {
    if ( (iColors < 0) ||  //Skip test
         (gifImage.GetGlobalColorTable().GetSize() == (uint32)iColors) )
      bRes = true;
    }
  }

cout << endl << "======================" << endl;
return bRes;
}


 // Get File Size
long GetFileSize(char* pszFile) 
{	
long lRes = 0;
FILE* fileStream; 

#ifdef __MSDOS__
  #define OPEN_FLAGS "rb"
#else
  #define OPEN_FLAGS "r"
#endif

if( (fileStream=fopen(pszFile, OPEN_FLAGS)) != NULL ) 
  { 
  fseek(fileStream,0,SEEK_END);  //Move pointer to end of file
  lRes = ftell(fileStream);      //Get current file position
  fclose(fileStream);
  }

return lRes;
}


//caller deletest the buffer
BYTE* Load(char* pszFile)
{
BYTE* pResult = NULL;
long lSize = GetFileSize(pszFile);

if (lSize > 0)
  {
  FILE* fileStream = fopen(pszFile, "rb");
  if (fileStream != NULL)
    {
    pResult = new BYTE[lSize];
    if(pResult != NULL)
      {
        //Copy the filr to the buffer
      if(fread(pResult, sizeof(BYTE), lSize, fileStream) != (size_t)lSize)
        {
          //Failure
        delete[] pResult;
        pResult = NULL;
        perror(pszFile);
        }
      }
    fclose (fileStream);
    }
   else
     perror(pszFile);
  }
return pResult;
}


//TestGifDecoder()-------------------------------------------------------------
/*Test of decoding a GIF image. An image is stored complete in a continuous 
  block in memory.

  Returns: true if successful, otherwise returns false
 */
bool TestGifDecoder(char* szImageFileName)
{
cout << "TestGifDecoder(" << szImageFileName << ')' <<endl;

BYTE* pGifStream = Load(szImageFileName);
if (pGifStream == NULL)
  return false; //Failed to open or read the file
long lSize = GetFileSize(szImageFileName);

CGifViewer gifDecoder;
bool bRes = gifDecoder.Decode(pGifStream, lSize);

delete pGifStream; //Free allocated memory

cout << endl << "======================" << endl;
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 4    Biblioteka1.3         8/5/02 11:33:46 AM   Darko           Fixed bug in
 *      SeekImagePos
 * 3    Biblioteka1.2         7/31/02 5:30:21 PM   Darko Kolakovic
 *      SeekImageDescriptor inserted
 * 2    Biblioteka1.1         7/16/02 8:57:08 PM   Darko Kolakovic Added
 *      TestGifCreate()
 * 1    Biblioteka1.0         7/16/02 1:48:21 AM   Darko           
 *$
 *****************************************************************************/
