/*$RCSfile: KLogMsg.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2011/11/11 20:26:49 $
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
out << tm->tm_year << '-' << 
       tm->tm_mon  << '-' << 
       tm->tm_mday << ' ' << 
       tm->tm_hour << ':' << tm->tm_min << ':' << tm->tm_sec;
out  << ": " << msg << "\n";
out.close();
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KLogMsg.cpp,v $
 * Revision 1.1  2011/11/11 20:26:49  ddarko
 * Created
 *
 *****************************************************************************/
