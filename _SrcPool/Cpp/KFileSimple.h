/*$RCSfile: KFileSimple.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/05/07 21:18:21 $
  $Author: ddarko $

  Basic file-handling API wrapper.
  Copyright: CommonSoft Inc.
  2008-12-12 Darko Kolakovic
 */

#ifndef _KFILESIMPLE_H_
    //$RCSfile: KFileSimple.h,v $ sentry
  #define _KFILESIMPLE_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
/*This is base class for the number of file-handling classes. It directly
  provides unbuffered, binary disk input/output services.
  Normally, a disk file is opened on construction and closed on destruction.
  Use this class for general-purpose disk I/O,  when file-handling needs are
  relatively simple.
 */
class CFileSimple
{
public:
  CFileSimple(LPCTSTR szFilename);
  virtual ~CFileSimple();

  void Read();
  void Write();

};

///////////////////////////////////////////////////////////////////////////////
#endif //_KFILESIMPLE_H_
/*****************************************************************************
 * $Log: KFileSimple.h,v $
 * Revision 1.1  2009/05/07 21:18:21  ddarko
 * Added basic file handling
 *
 *****************************************************************************/
