/*$Workfile: KFileTime.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-01 22:34:50$
  $Author: Darko$

  FILETIME creation time conversion helper
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */
#ifdef WIN32 //Microsoft Win32 platform dependant

#if _MSC_VER == 1310
  //Warning fix Q314963: WINVER not defined. Visual C++ .Net 2003 v7.1
  //Defaulting to 0x0501 (Windows XP and Windows .NET Server)
  #define WINVER 0x0501
#endif // _MSC_VER > 1000


#define VC_EXTRALEAN    // Exclude rarely-used stuff from Windows headers
#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif

#ifndef _INC_TIME
  #include <time.h> //time_t structure
#endif

#ifndef _AFX_NO_OLE_SUPPORT
  #ifndef __AFXDISP_H__
    #include <AfxDisp.h>  //COleDateTime class
  #endif
#endif


#include "KFileTime.h" //CFiletime class

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFiletime

CFiletime::CFiletime()
{
dwLowDateTime  = 0;
dwHighDateTime = 0;
}

//::CFiletime()----------------------------------------------------------------
/*Converts MS-DOS date and time values to a FILETIME. If fails, throws CFileException.

  The MS-DOS date is a packed 16-bit value with the following format:
    Bits
    0-4           Day of the month (1-31)
    5-8           Month (1 = January, 2 = February, and so on)
    9-15          Year offset from 1980 (add 1980 to get actual year)

  The MS-DOS time is a packed 16-bit value with the following format:
    Bits
    0-4           Second divided by 2
    5-10          Minute (0-59)
    11-15         Hour (0-23 on a 24-hour clock)

  Example:
    {
    ...
    CFiletime Time(56,458);
    afxDump << Time;
    }
    Output:
      CFiletime @ $6AEFFC
          {L:2985252352,H:27851188}

 */
CFiletime::CFiletime(const WORD& wFatDate,   //[in] 16-bit MS-DOS date
                     const WORD& wFatTime    //[in] 16-bit MS-DOS time
                     )
{
if (::DosDateTimeToFileTime(wFatDate,wFatTime, this) == FALSE)
  CFileException::ThrowOsError((LONG)::GetLastError());
}

CFiletime::CFiletime(const CFiletime& cfrTime//[in]
                     )
{
*this = (FILETIME)cfrTime;
}

CFiletime::CFiletime(const LPFILETIME lpftTime//[in]
                     )
{
*this = *lpftTime;
}

CFiletime::CFiletime(const LPSYSTEMTIME lpstTime//[in]
                     )
{
*this = *lpstTime;
}

CFiletime::~CFiletime()
{
}

///////////////////////////////////////////////////////////////////////////////
// Diagnostic
#if defined( _DEBUG )

void CFiletime::Dump(CDumpContext& dc//[in]
                     ) const
{
dc << _T("CFiletime @ ") << (VOID *) this
   << _T("\n\t{L:") << dwLowDateTime
   << _T(",H:")     << dwHighDateTime
   << _T("}\n");
}

#endif // _DEBUG

//::operator=()----------------------------------------------------------------
/*Assigns CTime to UTC FILETIME. If fails, throws CFileException.
 */
CFiletime& CFiletime::operator=(const CTime& Param2//[in] value to assign
                                )
{
SYSTEMTIME sysTime;
sysTime.wYear         = (WORD)Param2.GetYear();
sysTime.wMonth        = (WORD)Param2.GetMonth();
sysTime.wDay          = (WORD)Param2.GetDay();
sysTime.wHour         = (WORD)Param2.GetHour();
sysTime.wMinute       = (WORD)Param2.GetMinute();
sysTime.wSecond       = (WORD)Param2.GetSecond();
sysTime.wMilliseconds = 0;

return (*this = sysTime);
}

//::operator=()----------------------------------------------------------------
/*Assigns SYSTEMTIME to FILETIME. If fails, throws CFileException.

  Example:
    #include "UFileTme.h" //CFiletime class
      {
      ...
      CFiletime   cftSystemTime;
      SYSTEMTIME  stSystemTime ;
      ::GetSystemTime(&stSystemTime);
      CString strDate, strTime;
      cftSystemTime = stSystemTime;
        //Get locale date
      cftSystemTime.GetDateFormat(strDate,strTime);
      TRACE2("%s %s\n",strDate,strTime);
      }
 */
CFiletime& CFiletime::operator=(const SYSTEMTIME& Param2//[in] value to assign
                                )
{
if (!SystemTimeToFileTime((LPSYSTEMTIME)&Param2, this))
  CFileException::ThrowOsError((LONG)::GetLastError());
return *this;
}

//::operator=()----------------------------------------------------------------
/*Assigns time_t to UTC FILETIME.
  Under UNIX platforms, file times are maintained in the form of a ANSI C
  run- time arithmetic type named 'time_t', which represents seconds since
  midnight January 1, 1970 UTC (coordinated universal time).

  History: Article Q167296
 */
CFiletime& CFiletime::operator=(const time_t& Param2//[in] value to assign
                                )
{
LONGLONG llTemp = Int32x32To64(Param2, CST_FT_SECOND) + (__int64)134774*CST_FT_DAY;
return (*this = llTemp);
}

//::operator=()----------------------------------------------------------------
/*Assigns int to FILETIME.
 */
CFiletime& CFiletime::operator=(const int& iSec  //[in] value to assign in
                                                 //seconds [s]
                                )
{
unsigned __int64 ullResult = iSec * CST_FT_SECOND;
return (*this = ullResult);
}

#ifndef _AFX_NO_OLE_SUPPORT
#pragma message (__FILE__ " included OLE support")
//::operator COleDateTime()----------------------------------------------------
/*Converts FILETIME to the COleDateTime.
 */
CFiletime::operator COleDateTime()
{
COleDateTime odtTemp = *(PFILETIME)this;
return odtTemp;
}

//::operator=()----------------------------------------------------------------
/*Assigns COleDateTime to UTC FILETIME. If fails, throws CFileException.
 */
CFiletime& CFiletime::operator=(const COleDateTime& Param2//[in] value to assign
                                )
{
SYSTEMTIME sysTime;
sysTime.wYear         = (WORD)Param2.GetYear();
sysTime.wMonth        = (WORD)Param2.GetMonth();
sysTime.wDay          = (WORD)Param2.GetDay();
sysTime.wHour         = (WORD)Param2.GetHour();
sysTime.wMinute       = (WORD)Param2.GetMinute();
sysTime.wSecond       = (WORD)Param2.GetSecond();
sysTime.wMilliseconds = 0;

return (*this = sysTime);
}
#endif

//::operator CTime()-----------------------------------------------------------
/*Converts FILETIME to the CTime.
 */
CFiletime::operator CTime()
{
CTime ctTemp = *(PFILETIME)this;
return ctTemp;
}

//::operator SYSTEMTIME()-----------------------------------------------------------
/*Converts FILETIME to the SYSTEMTIME. If fails, throws CFileException.
 */
CFiletime::operator SYSTEMTIME()
{
SYSTEMTIME stTime;
if(!FileTimeToSystemTime((PFILETIME)this, &stTime))
  {
  ZeroMemory(&stTime,sizeof(SYSTEMTIME));
  CFileException::ThrowOsError((LONG)::GetLastError());
  }

return stTime;
}

//::opperator +=()-------------------------------------------------------------
/*Addition assignment int to FILETIME.

  Example:
      {
      CFiletime cftSystemTime;
      CString strDate, strTime;
      cftSystemTime.GetSystemTime();  //Get current UTC time
      cftSystemTime.GetDateFormat(strDate,strTime);//Get locale date
      TRACE2("%s %s\n",strDate,strTime); //Output 3/10/1999 7:51:56 PM (Local)
      cftSystemTime += 60;  //[s]
      cftSystemTime.GetDateFormat(strDate,strTime);
      TRACE2("%s %s\n",strDate,strTime); //Output 3/10/1999 7:52:56 PM (Local)
      }
 */
CFiletime& CFiletime::operator+= (const int& iSec //[in] period to add in
                                                  //seconds [s]
                                  )
{
unsigned __int64 ullResult;
    //Copy the time into a longlong.
ullResult = (((unsigned __int64) dwHighDateTime) << 32) + dwLowDateTime;
ullResult += iSec * CST_FT_SECOND;
return (*this = ullResult);
}

//::opperator +=()-------------------------------------------------------------
/*Addition assignment LONGLONG to FILETIME.
  Example:
      {
      CFiletime cftSystemTime;
      CString strDate, strTime;
      cftSystemTime.GetSystemTime();  //Get current UTC time
      cftSystemTime.GetDateFormat(strDate,strTime);//Get locale date
      TRACE2("%s %s\n",strDate,strTime); //Output 3/10/1999 7:52:56 PM (Local)
      cftSystemTime += 50*365*CST_FT_DAY;//0.1*[ns]
      cftSystemTime.GetDateFormat(strDate,strTime);
      TRACE2("%s %s\n",strDate,strTime); //Output 2/25/2049 7:52:56 PM (Local)
      }
 */
CFiletime& CFiletime::operator+=(const LONGLONG& ll_100ns  //[in] period to add in
                                                           //hundreds of ns [0.1 µs]
                                 )
{
LONGLONG llResult = (LONGLONG)*this + ll_100ns;
return (*this = llResult);
}

CFiletime CFiletime::operator+(const CFiletime& cftTime)
{
CFiletime cftResult;
LONGLONG llResult = (((LONGLONG) dwHighDateTime) << 32) + dwLowDateTime +
                    (((LONGLONG) cftTime.dwHighDateTime) << 32) + cftTime.dwLowDateTime ;
cftResult = llResult;
return cftResult;
}

CFiletime& CFiletime::operator+=(CFiletime const& cftTime)
{
LONGLONG llResult = (((LONGLONG) dwHighDateTime) << 32) + dwLowDateTime +
                    (((LONGLONG) cftTime.dwHighDateTime) << 32) + cftTime.dwLowDateTime ;
return (*this = llResult);
}

//::GetDateFormat()------------------------------------------------------------
/*The function formats a date and time as a strings for a default
  user locale based on the Coordinated Universal Time (UTC).

  Returns: date and time as a strings for a default user locale based
  on the Coordinated Universal Time (UTC).

  Note: The FileTimeToSystemTime function only works with FILETIME
        values that are less than 0x8000000000000000. The function
       fails with values equal to or greater than that.

  Example:
    #include "UFileTme.h" //CFiletime class
      {
      ...
      CFiletime cftSystemTime;
      cftSystemTime.GetSystemTime();
      CString strDate, strTime;
        //Get locale date
      cftSystemTime.GetDateFormat(strDate,strTime);
      TRACE2("%s %s\n",strDate,strTime);
      }
 */
void CFiletime::GetDateFormat(CString& strDate,//[out] resulting date
                              CString& strTime,//[out] resulting time
                              BOOL bLocalTime //[in]= TRUE local or UNC time
                              ) const
{
CFiletime cftLocalTime;
  //Converts a file time based on the Coordinated Universal Time (UTC)
  //to a local file time.
if (bLocalTime)
  FileTimeToLocalFileTime((PFILETIME)this, (PFILETIME)&cftLocalTime);
else
  cftLocalTime = *this;

SYSTEMTIME stTime;
if(FileTimeToSystemTime((PFILETIME)&cftLocalTime, &stTime))
  {
  int iLen = ::GetDateFormat(LOCALE_USER_DEFAULT, 0, &stTime, NULL, NULL, 0);
  LPTSTR szBuf = strDate.GetBuffer(iLen);
  ::GetDateFormat(LOCALE_USER_DEFAULT, 0, &stTime, NULL, szBuf,iLen);
  strDate.ReleaseBuffer();
  iLen = ::GetTimeFormat(LOCALE_USER_DEFAULT, 0, &stTime, NULL, NULL, 0);
  szBuf = strTime.GetBuffer(iLen);
  ::GetTimeFormat(LOCALE_USER_DEFAULT, 0, &stTime, NULL, szBuf, iLen);
  strTime.ReleaseBuffer();
  }

}

//::GetSystemTime()------------------------------------------------------------
/*The function retrieves the current system date and time. The time is
  expressed in Coordinated Universal Time (UTC).
 */
CFiletime& CFiletime::GetSystemTime()
{
SYSTEMTIME stSystemTime ;
::GetSystemTime(&stSystemTime);
*this = stSystemTime;
return *this;
}

//::Normalize()----------------------------------------------------------------
/*Convert local time to a file time based on the Coordinated Universal Time (UTC).
  In case of a failure throws CFileException.
 */
CFiletime& CFiletime::Normalize()
{
FILETIME  ftFileTime; //the Coordinated Universal Time (UTC)
if (!LocalFileTimeToFileTime(this, &ftFileTime))
  CFileException::ThrowOsError((LONG)::GetLastError());
return (*this = ftFileTime);
}

///////////////////////////////////////////////////////////////////////////////
#endif //WIN32
/******************************************************************************
 *$Log:
 * 5    Biblioteka1.4         2004-10-01 22:34:50  Darko           stdafx.h
 * 4    Biblioteka1.3         2003-09-24 18:40:34  Darko           Fixed VC++ .Net
 *      7.1 (2003) compilation
 * 3    Biblioteka1.2         2003-09-24 12:27:45  Darko           formatting
 * 2    Biblioteka1.1         2002-07-16 01:41:06  Darko           Fixed VSS Log
 *      tag
 * 1    Biblioteka1.0         2002-03-13 00:40:40  Darko
 *$
 *****************************************************************************/
