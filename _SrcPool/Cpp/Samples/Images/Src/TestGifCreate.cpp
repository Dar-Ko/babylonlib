/*$Workfile: TestGifCreate.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2003/01/31 03:14:23 $
  $Author: ddarko $

  Test GIF object initialization
  Mar 2k2 D. Kolakovic
*/

// Group=Examples

#include "KGif.h" //CGif class
#include "KTrace.h" //TRACE macros

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//TestGifCreate()---------------------------------------------------------------
/*Test of GIF object initialization

  Returns: true if successful, otherwise returns false
 */
bool TestGifCreate()
{
TRACE0("TestGifCreate()\n");
bool bRes = false;
//Create empty GIF object
TRACE0("  Create empty GIF container\n");
CGif gifImage;
if (gifImage.IsValid())
  {
  if (!gifImage.HasGlobalColorTable())
    {
    if (gifImage.GetGlobalColorTable().GetSize() == 0)
      bRes = true;
    }
  }


if (!bRes)
  gifImage.Dump();


return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         16/07/2002 7:55:57 PMDarko Kolakovic 
 *$
 *****************************************************************************/
