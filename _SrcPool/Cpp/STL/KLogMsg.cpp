/*$RCSfile: KLogMsg.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2011/11/11 22:01:40 $
  $Author: ddarko $

  Log a message to the file
  Copyright (c) GPL
 */

#include "stdafx.h"
#include "resource.h"
#if _MSC_VER < 1200
  #include <iostream.h>
  #include <iomanip.h>  //std::endl
#endif

#if _MSC_VER >= 1200
  #include <iostream>
  #include <iomanip>    //std::endl
#endif

//-----------------------------------------------------------------------------
/*Kludge for logging text messages
 */
void LogMsg(LPCTSTR szLogName, LPCTSTR szMsg)
{
time_t now = time(0);
struct tm* tm = localtime(&now);
std::ofstream out(szLogName,ios::ate);
#ifdef CASE1
out << tm->tm_year << '-' << 
       tm->tm_mon  << '-' << 
       tm->tm_mday << ' ' << 
       tm->tm_hour << ':' << tm->tm_min << ':' << tm->tm_sec;
 #endif
 
 #ifdef CASE2
   out << _tasctime(tm);
 #else
  #ifdef _LINUX
     // under linux %z is the hour offset and %Z is the timezone name
     const char *RFC822   = "%a, %d %b %Y %H:%M:%S %z (%Z) +#9ld nsec";
     const char *ISO8601  = "%Y-%m-%d %H:%M:%S.#9.9ld%z";
     const char *ISO8601Z = "%Y-%m-%d %H:%M:%S.#9.9ldZ";
  #else
     // otherwise only %Z is guarenteed to be defined
     //"Mon, 02 Jan 2001 18:11:12 +0000 (GMT) +999999999 nsec"
     const char *RFC822   = "%a, %d %b %Y %H:%M:%S %Z +#9ld nsec";
     //"2001-01-02 10:11:12.9999999999-0800"
     const char *ISO8601  = "%Y-%m-%d %H:%M:%S.#9.9ld%Z";
     //"2001-01-02 18:11:12.9999999999Z"
     const char *ISO8601Z = "%Y-%m-%d %H:%M:%S.#9.9ldZ";
  #endif
  LPCSTR SQL = "%Y-%m-%d %H:%M:%S";
  const int SQLBUFFSIZE = 20 +1; //zero-terminated string

  char szTime[SQLBUFFSIZE];  // strftime fields substituted
  strftime(szTime, sizeof(szTime), SQL, tm);
  out << szTime;
 #endif
out  << ": " << msg << std::endl;
out.close();
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KLogMsg.cpp,v $
 * Revision 1.2  2011/11/11 22:01:40  ddarko
 * Added formating
 *
 * Revision 1.1  2011/11/11 20:26:49  ddarko
 * Created
 *
 *****************************************************************************/
