/*$Workfile: ImagesTest.cpp$: implementation file
  $Revision: 8$ $Date: 8/19/02 10:45:15 AM$
  $Author: Darko Kolakovic$

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
 * 8    Biblioteka1.7         8/19/02 10:45:15 AM  Darko Kolakovic 
 * 7    Biblioteka1.6         8/13/02 9:12:42 AM   Darko Kolakovic 
 * 6    Biblioteka1.5         8/6/02 4:36:10 PM    Darko Kolakovic Added more
 *      diagnostic information
 * 5    Biblioteka1.4         8/5/02 11:33:30 AM   Darko           Fixed bug in
 *      SeekImagePos
 * 4    Biblioteka1.3         8/2/02 10:26:14 PM   Darko Kolakovic 
 * 3    Biblioteka1.2         7/31/02 5:30:02 PM   Darko Kolakovic
 *      SeekImageDescriptor inserted
 * 2    Biblioteka1.1         7/16/02 8:57:04 PM   Darko Kolakovic Added
 *      TestGifCreate()
 * 1    Biblioteka1.0         7/16/02 1:48:19 AM   Darko           
 *$
 *****************************************************************************/
