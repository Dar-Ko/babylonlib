/*$RCSfile: MFC4MFil.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/09/01 15:11:50 $
  $Author: ddarko $

  Fix: "Out of Memory" Error When Saving to an Existing File
  Article: MSDN Q163253
  Darko Kolakovic
  Mar 99
 */

// Group=Windows

#ifndef _MFC_40MIRRORFILE_H_
  #define _MFC_40MIRRORFILE_H_

#define _MFC40 1 //Bug Fix in the MFC 4.0
#define _MFC41 1 //Bug Fix in the MFC 4.1
#define _MFC42 1 //Bug Fix in the MFC 4.2

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif

#ifndef __AFXPRIV_H__
  #include <AfxPriv.h>
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

// C++ Hack to access protected members in the mirrored file
// See AfxPriv.h, \MSDev\MFC\Src\AfxImpl.h
class CFixMirrorFile: public CMirrorFile
{
public:
  virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags,CFileException* pError = NULL);
};

///////////////////////////////////////////////////////////////////////////////

//MFCFixGetFile()--------------------------------------------------------------------
#pragma warning( disable : 4100 ) //Warning :unreferenced formal parameter (pDoc in Release v.)
/*FIX: "Out of Memory" Error When Saving to an Existing File ( MFC4.0 4.1 4.2 )
  When you save to an existing file in a Visual C++ MFC application, an
  "Out of memory" error occurs. The error occurs only when you save over an
  existing file on a non-NT platform, such as Windows 95, that is on a network.
  Article ID: Q163253

  Note: Override the CDocument::GetFile() member function and call this function
  rather than default function
 */
template <class FixCDocument> CFile* MFCFixGetFile(
               FixCDocument* pDoc,   //a pointer to the current document
               LPCTSTR lpszFileName, //a string that is the path to the desired file
               UINT nOpenFlags,      //sharing and access mode.
               CFileException* pError//a pointer to an existing file-exception object
               )
{
ASSERT(pDoc != NULL);
ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CDocument)));

CFixMirrorFile* pFile = new CFixMirrorFile;
ASSERT(pFile != NULL);
if (!pFile->Open(lpszFileName, nOpenFlags, pError))
  {
  delete pFile;
  pFile = NULL;
  }
return pFile;
}
#pragma warning( default : 4100 )//Warning :unreferenced formal parameter

///////////////////////////////////////////////////////////////////////////////
#endif //_MFC_40MIRRORFILE_H_
/*****************************************************************************
 * $Log: MFC4MFil.h,v $
 * Revision 1.2  2009/09/01 15:11:50  ddarko
 * Reformatted
 *
 *****************************************************************************/

