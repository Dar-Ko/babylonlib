/*$Workfile: H:\_SrcPool\Cpp\KFileTime.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:14:10 $
  $Author: ddarko $

  FILETIME creation time conversion helper
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef WIN32 //Microsoft Win32 platform dependant

#include "KFileTime.h" //CFileTime class
#pragma hdrstop

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTime

CFileTime::CFileTime()
{
dwLowDateTime  = 0;
dwHighDateTime = 0;
}

//::CFileTime()----------------------------------------------------------------
/*Converts MS-DOS date and time values to a FILETIME. If fails, throws CFileException.

  The MS-DOS date is a packed 16-bit value with the following format:
    Bits
    0-4	          Day of the month (1-31)
    5-8	          Month (1 = January, 2 = February, and so on)
    9-15	        Year offset from 1980 (add 1980 to get actual year)

  The MS-DOS time is a packed 16-bit value with the following format:
    Bits
    0-4	          Second divided by 2
    5-10	        Minute (0-59)
    11-15	        Hour (0-23 on a 24-hour clock)

  Example:
    {
    ...
    CFileTime Time(56,458);
    afxDump << Time;
    }
    Output:
      CFileTime @ $6AEFFC
	        {L:2985252352,H:27851188}

 */
CFileTime::CFileTime(const WORD& wFatDate, 	// 16-bit MS-DOS date
                     const WORD& wFatTime    // 16-bit MS-DOS time
                     )
{
if (::DosDateTimeToFileTime(wFatDate,wFatTime, this) == FALSE)
  CFileException::ThrowOsError((LONG)::GetLastError());
}

CFileTime::CFileTime(const CFileTime& cfrTime)
{
*this = (FILETIME)cfrTime;
}

CFileTime::CFileTime(const LPFILETIME lpftTime)
{
*this = *lpftTime;
}

CFileTime::CFileTime(const LPSYSTEMTIME lpstTime)
{
*this = *lpstTime;
}

CFileTime::~CFileTime()
{
}

///////////////////////////////////////////////////////////////////////////////
// Diagnostic
#if defined( _DEBUG )

void CFileTime::Dump(CDumpContext& dc) const
{
dc << _T("CFileTime @ ") << (VOID *) this
   << _T("\n\t{L:") << dwLowDateTime
   << _T(",H:")     << dwHighDateTime
   << _T("}\n");
}

#endif // _DEBUG

//::operator=()----------------------------------------------------------------
/*Assigns CTime to UTC FILETIME. If fails, throws CFileException.
 */
CFileTime& CFileTime::operator=(const CTime& Param2)
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
    #include "UFileTme.h" //CFileTime class
      {
      ...
      CFileTime   cftSystemTime;
      SYSTEMTIME  stSystemTime ;
      ::GetSystemTime(&stSystemTime);
      CString strDate, strTime;
      cftSystemTime = stSystemTime;
        //Get locale date
      cftSystemTime.GetDateFormat(strDate,strTime);
      TRACE2("%s %s\n",strDate,strTime);
      }
 */
CFileTime& CFileTime::operator=(const SYSTEMTIME& Param2)
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
CFileTime& CFileTime::operator=(const time_t& Param2)
{
LONGLONG llTemp = Int32x32To64(Param2, CST_FT_SECOND) + (__int64)134774*CST_FT_DAY;
return (*this = llTemp);
}

//::operator=()----------------------------------------------------------------
/*Assigns int to FILETIME.
 */
CFileTime& CFileTime::operator=(const int& iSec  //seconds
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
CFileTime::operator COleDateTime()
{
COleDateTime odtTemp = *(PFILETIME)this;
return odtTemp;
}

//::operator=()----------------------------------------------------------------
/*Assigns COleDateTime to UTC FILETIME. If fails, throws CFileException.
 */
CFileTime& CFileTime::operator=(const COleDateTime& Param2)
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
CFileTime::operator CTime()
{
CTime ctTemp = *(PFILETIME)this;
return ctTemp;
}

//::operator SYSTEMTIME()-----------------------------------------------------------
/*Converts FILETIME to the SYSTEMTIME. If fails, throws CFileException.
 */
CFileTime::operator SYSTEMTIME()
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
      CFileTime cftSystemTime;
      CString strDate, strTime;
      cftSystemTime.GetSystemTime();  //Get current UTC time
      cftSystemTime.GetDateFormat(strDate,strTime);//Get locale date
      TRACE2("%s %s\n",strDate,strTime); //Output 3/10/1999 7:51:56 PM (Local)
      cftSystemTime += 60;  //[s]
      cftSystemTime.GetDateFormat(strDate,strTime);
      TRACE2("%s %s\n",strDate,strTime); //Output 3/10/1999 7:52:56 PM (Local)
      }
 */
CFileTime& CFileTime::operator+= (const int& iSec //[in] period to add in
                                                  //seconds
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
      CFileTime cftSystemTime;
      CString strDate, strTime;
      cftSystemTime.GetSystemTime();  //Get current UTC time
      cftSystemTime.GetDateFormat(strDate,strTime);//Get locale date
      TRACE2("%s %s\n",strDate,strTime); //Output 3/10/1999 7:52:56 PM (Local)
      cftSystemTime += 50*365*CST_FT_DAY;//0.1*[ns]
      cftSystemTime.GetDateFormat(strDate,strTime);
      TRACE2("%s %s\n",strDate,strTime); //Output 2/25/2049 7:52:56 PM (Local)
      }
 */
CFileTime& CFileTime::operator+=(const LONGLONG& ll_100ns  //[in] period to add in
                                                           //hundreds of ns
                                 )
{
LONGLONG llResult = (LONGLONG)*this + ll_100ns;
return (*this = llResult);
}

CFileTime CFileTime::operator+(const CFileTime& cftTime)
{
CFileTime cftResult;
LONGLONG llResult = (((LONGLONG) dwHighDateTime) << 32) + dwLowDateTime +
                    (((LONGLONG) cftTime.dwHighDateTime) << 32) + cftTime.dwLowDateTime ;
cftResult = llResult;
return cftResult;
}

CFileTime& CFileTime::operator+=(CFileTime const& cftTime)
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
    #include "UFileTme.h" //CFileTime class
      {
      ...
      CFileTime cftSystemTime;
      cftSystemTime.GetSystemTime();
      CString strDate, strTime;
        //Get locale date
      cftSystemTime.GetDateFormat(strDate,strTime);
      TRACE2("%s %s\n",strDate,strTime);
      }
 */
void CFileTime::GetDateFormat(CString& strDate,//[out] resulting date
                              CString& strTime,//[out] resulting time
                              BOOL bLocalTime //[in]= TRUE local or UNC time
                              ) const
{
CFileTime cftLocalTime;
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
CFileTime& CFileTime::GetSystemTime()
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
CFileTime& CFileTime::Normalize()
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
 * 2    Biblioteka1.1         7/16/02 1:41:06 AM   Darko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         3/13/02 12:40:40 AM  Darko           
 *$
 *****************************************************************************/
