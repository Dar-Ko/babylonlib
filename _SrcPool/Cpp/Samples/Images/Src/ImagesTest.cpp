/*$Workfile: ImagesTest.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2003/01/31 03:14:23 $
  $Author: ddarko $

  Test of image decoders and viewers
  Copyright: CommonSoft Inc
  Mar 2k2 D. Kolakovic
*/

// Group=Examples

#include <stdlib.h> //EXIT_SUCCESS definition
#include <fstream.h>

#include "KTrace.h" //TRACE0 macros

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TestGifCreate();
extern bool TestGifConversion();
extern bool TestGifViewer(char* szImageFileName, int iColors);
extern bool TestGifDecoder(char* szImageFileName);
extern "C" const char* gifscan (FILE* infp /*    infp = stdin;*/
                    );

  //Image Test results
struct TestImages
  {
  char* m_szImagePath;  //file directory
  int   m_iColorNo;     //number of colors in color palette, table or map;
                        //if -1, any number of colors is valid
  bool  m_bTestResult;  //result of successful test
  };

  //Table of test images
TestImages g_testImages[] =
  {
    {".\\Res\\TestBasicBars.gif"     ,  2,  true}, // 0
    {".\\Res\\TestRedWhite.gif"      ,  2,  true}, // 1
    {".\\Res\\TestTriangle.gif"      ,  2,  true}, // 2
    {".\\Res\\TestDiagonalGray.gif"  , 16,  true}, // 3
    {".\\Res\\TestDiagonal.gif"      , 16,  true}, // 4
    {".\\Res\\TestFourSeasons.gif"   ,  4,  true}, // 5
    {".\\Res\\TestInterlace.gif"     ,  4,  true}, // 6
    {".\\Res\\TestRainbow.gif"       ,256,  true}, // 7
    {".\\Res\\TestBars.gif"          , 16,  true}, // 8
    {".\\Res\\TestColor.gif"         ,256,  true}, // 9
    {".\\Res\\TestGlobeAni.gif"      ,256,  true}, //10
    {".\\Res\\TestTrueColor.gif"     ,256,  true}, //11
    {".\\Res\\TestCorruptedBlock.gif",  2, false}, //12
    {".\\Res\\TestAntialiasing.gif"  ,256,  true}, //13
    {NULL                            ,  0, false}  //end of automated test

  };

//main()-----------------------------------------------------------------------
/*Defines the entry point for the console application. Test of decoding and
  encoding various  image formats.

  Returns: EXIT_SUCCESS if successful, otherwise returns EXIT_FAILURE.
 */
int main(int argc, 
         char* argv[] //[in] 1st argument: file name
         )
{
cout << "Validation of image decoding and converting\n\n" << endl;     

const int ARG_FILENAME = 1; //index of 'file name' argument

if(argc <= ARG_FILENAME)
  {
  cerr << "Usage: Images [file_name]" << endl;
  cerr << "Proceeding with sample " << g_testImages[0].m_szImagePath << endl;
  }
else
  {
  g_testImages[0].m_szImagePath = argv[ARG_FILENAME];
  g_testImages[0].m_iColorNo = -1;
  g_testImages[1].m_szImagePath = NULL;
  g_testImages[1].m_iColorNo = 0;
  }

if(!TestGifCreate())
  {
  cout << "  Failure!" << endl;
  return EXIT_FAILURE;
  }
else
  cout << "  Success." << endl;

if(!TestGifConversion())
  {
  cout << "  Failure!" << endl;
  return EXIT_FAILURE;
  }
else
  cout << "  Success." << endl;

  //Test all images form a table
int i = 0;
while (g_testImages[i].m_szImagePath != NULL)
  {
  FILE *file;

  file = fopen(g_testImages[i].m_szImagePath, "rb");
  if (file == NULL)
    return EXIT_FAILURE;
  cout << endl << i << ". " 
       << g_testImages[i].m_szImagePath 
       << " -------------------------" << endl;

  gifscan(file);
  cout << i << ". -------------------------" << endl;

  fclose(file);

  if(TestGifViewer(g_testImages[i].m_szImagePath, g_testImages[i].m_iColorNo) !=
      true)
    {
    cout << "  Failure!" << endl;
    return EXIT_FAILURE;
    }
  else
    cout << "  Success." << endl;

  if( TestGifDecoder(g_testImages[i].m_szImagePath) !=
      g_testImages[i].m_bTestResult)
    {
    cout << "  Failure!" << endl;
    return EXIT_FAILURE;
    }
  else
    cout << "  Success." << endl;

  i++;
  }

cout << endl << "======================" << endl;
return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 8    Biblioteka1.7         19/08/2002 9:45:15 AMDarko Kolakovic 
 * 7    Biblioteka1.6         13/08/2002 8:12:42 AMDarko Kolakovic 
 * 6    Biblioteka1.5         06/08/2002 3:36:10 PMDarko Kolakovic Added more
 *      diagnostic information
 * 5    Biblioteka1.4         05/08/2002 10:33:30 AMDarko           Fixed bug in
 *      SeekImagePos
 * 4    Biblioteka1.3         02/08/2002 9:26:14 PMDarko Kolakovic 
 * 3    Biblioteka1.2         31/07/2002 4:30:02 PMDarko Kolakovic
 *      SeekImageDescriptor inserted
 * 2    Biblioteka1.1         16/07/2002 7:57:04 PMDarko Kolakovic Added
 *      TestGifCreate()
 * 1    Biblioteka1.0         16/07/2002 12:48:19 AMDarko           
 *$
 *****************************************************************************/
