/*$Workfile: KFileTime.h$: header file
  $Revision: 1.1 $ $Date: 2002/09/06 22:14:10 $
  $Author: ddarko $

  FILETIME creation time conversion helper
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */

#ifndef _KFILETIME_H_
    //KFileTime.h sentry
  #define _KFILETIME_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif
  //Enable / disable OLE support
#define _AFX_NO_OLE_SUPPORT

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif

#ifdef _INC_TIME
  #include <Time.h> //time_t structure
#endif

#ifndef _AFX_NO_OLE_SUPPORT
  #ifndef __AFXDISP_H__
    #include <AfxDisp.h>  //COleDateTime class
  #endif
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
/*CFileTime class encapsulates the FILETIME data structure adding number of
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
*/
class CFileTime : public _FILETIME
{
// Construction
public:
  CFileTime();
  CFileTime(const CFileTime& cfrTime);
  CFileTime(const WORD& wFatDate,const WORD& wFatTime);
  CFileTime(const LPFILETIME lpftTime);
  CFileTime(const LPSYSTEMTIME lpstTime);

// Attributes
public:

// Operations
public:
  CFileTime& GetSystemTime();
  CFileTime& Normalize();
  operator LONGLONG();
  CFileTime& operator=(const LONGLONG& ll_100ns);
  CFileTime& operator=(const int& iSec);
  CFileTime& operator=(const unsigned __int64& ull_100ns);
  CFileTime& operator=(const FILETIME& Param2);
  CFileTime& operator=(const SYSTEMTIME& Param2);
  CFileTime& operator=(const time_t& Param2);
  CFileTime  operator+(const CFileTime& cftTime);
  CFileTime& operator+=(CFileTime const& cftTime);
  CFileTime& operator+=(const LONGLONG& ll_100ns);
  CFileTime& operator+=(const int& iSec);

// Overrides
public:
  virtual void GetDateFormat(CString& strDate, CString& strTime,
                             BOOL bLocalTime = TRUE) const;
  #ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
  #endif
  #ifndef _AFX_NO_OLE_SUPPORT
    virtual operator COleDateTime();
    virtual CFileTime& operator=(const COleDateTime& Param2);
  #endif
  virtual operator CTime();
  virtual operator SYSTEMTIME();
  virtual CFileTime& operator=(const CTime& Param2);
  virtual BOOL operator >  (const CFileTime& Param2) const;
  virtual BOOL operator >= (const CFileTime& Param2) const;
  virtual BOOL operator == (const CFileTime& Param2) const;
  virtual BOOL operator <= (const CFileTime& Param2) const;
  virtual BOOL operator <  (const CFileTime& Param2) const;

// Implementation
public:
	virtual ~CFileTime();

	// Generated message map functions
protected:
};

	// This makes ClassWizard happy
	//{{AFX_MSG(CFileTime)
	//}}AFX_MSG
	//{{AFX_VIRTUAL(CFileTime)
	//}}AFX_VIRTUAL
	//{{AFX_MSG_MAP(CFileTime)
	//}}AFX_MSG_MAP
///////////////////////////////////////////////////////////////////////////////
// Inlines

//::operator LONGLONG()--------------------------------------------------------
/*Converts FILETIME to the LONGLONG.
 */
inline CFileTime::operator LONGLONG()
{
LONGLONG llResult = (((LONGLONG) dwHighDateTime) << 32) + dwLowDateTime;
return llResult;
}

inline BOOL CFileTime::operator > (const CFileTime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2)  > 0)
  return TRUE;
return FALSE;
}

inline BOOL CFileTime::operator >= (const CFileTime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2) >= 0)
  return TRUE;
return FALSE;
}

inline BOOL CFileTime::operator == (const CFileTime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2)  == 0)
  return TRUE;
return FALSE;
}

inline BOOL CFileTime::operator <= (const CFileTime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2) <= 0)
  return TRUE;
return FALSE;
}

inline BOOL CFileTime::operator < (const CFileTime& Param2) const
{
if (::CompareFileTime((const FILETIME*)this,(const FILETIME*)&Param2)  < 0)
  return TRUE;
return FALSE;
}

//::operator=()----------------------------------------------------------------
/*Assigns LONGLONG to FILETIME.
  Example:
      {
      CFileTime cftSystemTime;
      CString strDate, strTime;
      cftSystemTime = (LONGLONG)0x7fffffffffffffff;
      cftSystemTime.GetDateFormat(strDate,strTime,FALSE);
      TRACE2("%s %s\n",strDate,strTime);  //Output 9/14/30828 2:48:05 AM (UTC)

      cftSystemTime = 10*CST_FT_SECOND;
      cftSystemTime.GetDateFormat(strDate,strTime,FALSE);
      TRACE2("%s %s\n",strDate,strTime);  //Output 1/1/1601 12:00:10 AM (UNC)
      }
 */
inline CFileTime& CFileTime::operator=(const LONGLONG& ll_100ns  //hundreds of ns
                            )
{
dwLowDateTime = (DWORD)(ll_100ns);
dwHighDateTime =(DWORD)(ll_100ns >> 32);
return *this;
}

inline CFileTime& CFileTime::operator=(const unsigned __int64& ull_100ns //hundreds of ns
                            )
{
dwLowDateTime  = (DWORD) (ull_100ns & 0xFFFFFFFF);
dwHighDateTime = (DWORD) (ull_100ns >> 32);
return *this;
}

inline CFileTime& CFileTime::operator=(const FILETIME& Param2)
{
dwLowDateTime  = Param2.dwLowDateTime;
dwHighDateTime = Param2.dwHighDateTime;
return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Helpers
#ifdef _DEBUG
//operator<<()-----------------------------------------------------------------
/*Outputs the CFileTime object to the dump context.
 */
inline CDumpContext& AFXAPI operator<<(CDumpContext& dc, const CFileTime& cftSource)
  {
  cftSource.Dump(dc);
  return dc;
  }
#endif

//operator<<()-----------------------------------------------------------------
/*Stores the CFileTime object to the archive.
 */
inline CArchive& AFXAPI operator<<(CArchive& ar, const CFileTime& cftData)
{
ar << cftData.dwLowDateTime << cftData.dwHighDateTime;
return ar;
}

//operator>>()-----------------------------------------------------------------
/*Loads the CFileTime object from the archive.
 */
inline CArchive& AFXAPI operator>>(CArchive& ar, CFileTime& cftData)
{
ar >> cftData.dwLowDateTime >> cftData.dwHighDateTime;
return ar;
}

//operator<<()-----------------------------------------------------------------
/*Writes the CFileTime object to the CFile. Throws CFileException.
 */
inline CFile& AFXAPI operator<<(CFile& fileDestination, CFileTime& cftData)
{
ASSERT(fileDestination.m_hFile != CFile::hFileNull);
fileDestination.Write((PFILETIME)&cftData,sizeof(FILETIME));
return fileDestination;
}

//operator>>()-----------------------------------------------------------------
/*Reads a CFileTime object from the CFile.
  Note: To obtain the date and time when the file was created use CFile::GetStatus
 */
inline CFile& AFXAPI operator>>(CFile& fileSource, CFileTime& cftData)
{
ASSERT(fileSource.m_hFile != CFile::hFileNull);
fileSource.Read((PFILETIME)&cftData,sizeof(FILETIME));
return fileSource;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_KFILETIME_H_

