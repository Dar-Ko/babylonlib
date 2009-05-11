/*$RCSfile: KFileSimple.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/05/11 14:29:50 $
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
  CFileSimple();
  CFileSimple(LPCTSTR szFilename);
  virtual ~CFileSimple();

  virtual bool Open(LPCTSTR szFilename,
                    UINT nOpenFlags,
                    unsigned int* pnError = NULL);
  virtual void Close();
  virtual void Flush();
  virtual void Read(void* pBuffer,
                    unsigned long nBufSize,
                    unsigned long& nBytesRead);
  virtual void Write(const void* pBuf, unsigned long nCount);
  void Seek(long nOffset);
  long GetPosition();
  long GetSize();
  void SetSize(unsigned long nNewLen);

  enum
    {
    //Creation Disposition
    FILE_EXIST     = 0x04, //opens exists file.
    FILE_CREATE   = 0x08, //creates a new file.
    FILE_TRUNCATE = 0x04
    //access rights
    FILE_R = 0x01, //opens  file for reading.
    FILE_A = 0x02, //opens file for appending.
    FILE_RA = FILE_R | FILE_A  //opens file for reading and appendig.

    };

protected:
  FILE* m_fileHandle; //
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*The default constructor does not open a file but rather initalizes file
  descriptor to null.
 */
inline CFileSimple::CFileSimple() :
  m_fileHandle(NULL)
{
}


///////////////////////////////////////////////////////////////////////////////
#endif //_KFILESIMPLE_H_
/*****************************************************************************
 * $Log: KFileSimple.h,v $
 * Revision 1.2  2009/05/11 14:29:50  ddarko
 * Added new interface
 *
 * Revision 1.1  2009/05/07 21:18:21  ddarko
 * Added basic file handling
 *
 *****************************************************************************/
