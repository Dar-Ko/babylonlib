/*$Workfile: KFileTime.h$: header file
  $Revision: 4$ $Date: 2003-09-24 17:40:36$
  $Author: Darko$

  FILETIME creation time conversion helper
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */
/* Group=Time                                                                */

#ifndef _KFILETIME_H_
    //$Workfile: KFileTime.h$ sentry
  #define _KFILETIME_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

  //Number of FILETIME intervals per 1 s
#define CST_FT_SECOND ((__int64)10000000)
  //Number of FILETIME intervals per 1 min
#define CST_FT_MINUTE (60 * CST_FT_SECOND)
  //Number of FILETIME intervals per 1 h
#define CST_FT_HOUR   (60 * CST_FT_MINUTE)
  //Number of FILETIME intervals per day
#define CST_FT_DAY    (24 * CST_FT_HOUR)

#include "KFileTimeCm.h"  //FILETIME comparasion operators


///////////////////////////////////////////////////////////////////////////////
/*CFiletime class encapsulates the FILETIME data structure adding number of
  conversions between different time formats. The file time is based on
  coordinated universal time (UTC). UTC-based time is loosely defined as
  the current date and time of day in Greenwich, England. The FILETIME
  structure is a 64-bit value representing the number of 0.1 microsecond
  intervals since January 1, 1601.

    typedef struct _FILETIME
      {
      DWORD dwLowDateTime;   //Specifies the low 32 bits of the file time.
      DWORD dwHighDateTime;  //Specifies the high 32 bits of the file time.
      } FILETIME, *PFILETIME, *LPFILETIME;

  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win).

  See also: YEAR_EPOCH_WINFILETIME, PTM, date, time, DATE
*/
class CFiletime : public _FILETIME
{
// Construction
public:
  CFiletime();
  CFiletime(const CFiletime& cfrTime);
  CFiletime(const WORD& wFatDate,const WORD& wFatTime);
  CFiletime(const LPFILETIME lpftTime);
  CFiletime(const LPSYSTEMTIME lpstTime);

// Attributes
public:

// Operations
public:
  CFiletime& GetSystemTime();
  CFiletime& Normalize();
  operator LONGLONG();
  CFiletime& operator=(const LONGLONG& ll_100ns);
  CFiletime& operator=(const int& iSec);
  CFiletime& operator=(const unsigned __int64& ull_100ns);
  CFiletime& operator=(const FILETIME& Param2);
  CFiletime& operator=(const SYSTEMTIME& Param2);
  CFiletime& operator=(const time_t& Param2);
  CFiletime  operator+(const CFiletime& cftTime);
  CFiletime& operator+=(CFiletime const& cftTime);
  CFiletime& operator+=(const LONGLONG& ll_100ns);
  CFiletime& operator+=(const int& iSec);

// Overrides
public:
  virtual void GetDateFormat(CString& strDate, CString& strTime,
                             BOOL bLocalTime = TRUE) const;
  #ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
  #endif
  #ifndef _AFX_NO_OLE_SUPPORT
    virtual operator COleDateTime();
    virtual CFiletime& operator=(const COleDateTime& Param2);
  #endif
  virtual operator CTime();
  virtual operator SYSTEMTIME();
  virtual CFiletime& operator=(const CTime& Param2);
  virtual BOOL operator >  (const CFiletime& Param2) const;
  virtual BOOL operator >= (const CFiletime& Param2) const;
  virtual BOOL operator == (const CFiletime& Param2) const;
  virtual BOOL operator <= (const CFiletime& Param2) const;
  virtual BOOL operator <  (const CFiletime& Param2) const;

// Implementation
public:
  virtual ~CFiletime();

  // Generated message map functions
protected:
};

  // This makes ClassWizard happy
  //{{AFX_MSG(CFiletime)
  //}}AFX_MSG
  //{{AFX_VIRTUAL(CFiletime)
  //}}AFX_VIRTUAL
  //{{AFX_MSG_MAP(CFiletime)
  //}}AFX_MSG_MAP
///////////////////////////////////////////////////////////////////////////////
// Inlines

//::operator LONGLONG()--------------------------------------------------------
/*Converts FILETIME to the LONGLONG.
 */
inline CFiletime::operator LONGLONG()
{
LONGLONG llResult = (((LONGLONG) dwHighDateTime) << 32) + dwLowDateTime;
return llResult;
}

inline BOOL CFiletime::operator > (const CFiletime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2)  > 0)
  return TRUE;
return FALSE;
}

inline BOOL CFiletime::operator >= (const CFiletime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2) >= 0)
  return TRUE;
return FALSE;
}

inline BOOL CFiletime::operator == (const CFiletime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2)  == 0)
  return TRUE;
return FALSE;
}

inline BOOL CFiletime::operator <= (const CFiletime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2) <= 0)
  return TRUE;
return FALSE;
}

inline BOOL CFiletime::operator < (const CFiletime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2)  < 0)
  return TRUE;
return FALSE;
}

//::operator=()----------------------------------------------------------------
/*Assigns LONGLONG to FILETIME.
  Example:
      {
      CFiletime cftSystemTime;
      CString strDate, strTime;
      cftSystemTime = (LONGLONG)0x7fffffffffffffff;
      cftSystemTime.GetDateFormat(strDate,strTime,FALSE);
      TRACE2("%s %s\n",strDate,strTime);  //Output 9/14/30828 2:48:05 AM (UTC)

      cftSystemTime = 10*CST_FT_SECOND;
      cftSystemTime.GetDateFormat(strDate,strTime,FALSE);
      TRACE2("%s %s\n",strDate,strTime);  //Output 1/1/1601 12:00:10 AM (UNC)
      }
 */
inline CFiletime& CFiletime::operator=(const LONGLONG& ll_100ns  //[in] hundreds
                                                                 //of ns [0.1 µs]
                            )
{
dwLowDateTime = (DWORD)(ll_100ns);
dwHighDateTime =(DWORD)(ll_100ns >> 32);
return *this;
}

inline CFiletime& CFiletime::operator=(const unsigned __int64& ull_100ns //[in] 
                                                       //hundreds of ns [0.1 µs]
                            )
{
dwLowDateTime  = (DWORD) (ull_100ns & 0xFFFFFFFF);
dwHighDateTime = (DWORD) (ull_100ns >> 32);
return *this;
}

inline CFiletime& CFiletime::operator=(const FILETIME& Param2)
{
dwLowDateTime  = Param2.dwLowDateTime;
dwHighDateTime = Param2.dwHighDateTime;
return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Helpers
#ifdef _DEBUG
//operator<<()-----------------------------------------------------------------
/*Outputs the CFiletime object to the dump context.
 */
inline CDumpContext& AFXAPI operator<<(CDumpContext& dc, //[out] 
                                       const CFiletime& cftSource//[in] 
                                       )
  {
  cftSource.Dump(dc);
  return dc;
  }
#endif

//operator<<()-----------------------------------------------------------------
/*Stores the CFiletime object to the archive.
 */
inline CArchive& AFXAPI operator<<(CArchive& ar,//[out] 
                                   const CFiletime& cftData//[in] 
                                   )
{
ar << cftData.dwLowDateTime << cftData.dwHighDateTime;
return ar;
}

//operator>>()-----------------------------------------------------------------
/*Loads the CFiletime object from the archive.
 */
inline CArchive& AFXAPI operator>>(CArchive& ar,//[in] 
                                   CFiletime& cftData//[out] 
                                   )
{
ar >> cftData.dwLowDateTime >> cftData.dwHighDateTime;
return ar;
}

//operator<<()-----------------------------------------------------------------
/*Writes the CFiletime object to the CFile. Throws CFileException.
 */
inline CFile& AFXAPI operator<<(CFile& fileDestination, //[out] 
                                CFiletime& cftData//[in] 
                                )
{
ASSERT(fileDestination.m_hFile != CFile::hFileNull);
fileDestination.Write((PFILETIME)&cftData,sizeof(FILETIME));
return fileDestination;
}

//operator>>()-----------------------------------------------------------------
/*Reads a CFiletime object from the CFile.
  Note: To obtain the date and time when the file was created use CFile::GetStatus
 */
inline CFile& AFXAPI operator>>(CFile& fileSource,//[in] 
                                CFiletime& cftData//[out] 
                                )
{
ASSERT(fileSource.m_hFile != CFile::hFileNull);
fileSource.Read((PFILETIME)&cftData,sizeof(FILETIME));
return fileSource;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_KFILETIME_H_
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2003-09-24 17:40:36  Darko           Fixed VC++ .Net
 *       7.1 (2003) compilation
 *  3    Biblioteka1.2         2003-09-24 11:27:48  Darko           formatting
 *  2    Biblioteka1.1         2002-08-02 21:26:23  Darko Kolakovic 
 *  1    Biblioteka1.0         2002-03-12 23:40:42  Darko           
 * $
 *  0 Dec 98 Darko Kolakovic
 *****************************************************************************/

