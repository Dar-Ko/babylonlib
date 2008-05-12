/*$Workfile: TsWriteTxt.cpp$: implementation file
  $Revision: 12$ $Date: 22/08/2007 7:24:04 PM$
  $Author: Darko Kolakovic$

  Outputs text to stdout stream
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/

// Group=Examples

#ifndef LPCTSTR
  #include "KTChar.h"
#endif

#ifdef _STLP_IOSTREAM //STLport library
  #if !defined KSTL_IO
    #define KSTL_IO 1100
  #endif
#endif

#ifdef _INC_IOSTREAM //MSVC v6.0 iostream.h
  #ifndef KSTL_IO
    #define KSTL_IO 1301
  #endif
#endif

#ifdef _IOSTREAM_ //MSVC v6.0 iostream
  #ifndef KSTL_IO
    #define KSTL_IO 1300
  #endif
#endif

#ifndef KSTL_IO
  #include "STL/KOStream.h"
#endif

#ifdef _CONSOLE
  #ifndef KSTL_IO
    //Note: include standard IO streams
    #pragma KMESSAGE(Warning : Include standard IO streams)
  #endif

  #ifdef KSTL_IO

//TsWriteToView()--------------------------------------------------------------
/*Writes a character string at the console standard output stream.

  Returns: true always.

  Note: uses Standard Template Library (STL).
 */
bool TsWriteToView(LPCTSTR lszText //[in] text to output or NULL
                   )
{
if (lszText != NULL)
  std::_tcout << lszText;
else
  std::_tcout << _T("<null>");
std::_tcout.flush();
return true;
}

//TsWriteToViewLn()------------------------------------------------------------
/*Writes a line of the text at the console standard output stream. New line
  delimiter (EOL) is appended to the end of the text.

  Returns: true always.

  Note: uses Standard Template Library (STL).
 */
bool TsWriteToViewLn(LPCTSTR lszText //[in] line of text to output
                     )
{
if(!TsWriteToView(lszText))
  return false;

std::_tcout << std::endl;
return true;
}

#include "KTime.h"  //_DATE_FORMAT_STD

bool TsWriteToViewLn(const tm& tmTime  //[in] date and time to output
                     )
{
std::_tcout << tmTime.tm_year + YEAR_EPOCH_TM << _T('-')
            << tmTime.tm_mon + 1 << _T('-')
            << tmTime.tm_mday << _T('T')
            << tmTime.tm_hour << _T(':')
            << tmTime.tm_min << _T(':')
            << tmTime.tm_sec << std::endl;
return true;
}

bool TsWriteToViewLn(const double& dValue  //[in] real number to output
                     )
{
std::_tcout << dValue << std::endl;
return true;
}

bool TsWriteToView(const double& dValue  //[in] real number to output
                     )
{
std::_tcout << dValue;
return true;
}

bool TsWriteToViewLn(const int& iValue  //[in] integer number to output
                     )
{
std::_tcout << iValue << std::endl;
return true;
}

bool TsWriteToView(const int& iValue  //[in] integer number to output
                     )
{
std::_tcout << iValue;
return true;
}

bool TsWriteToViewLn(const unsigned int& nValue  //[in] integer number to output
                     )
{
std::_tcout << nValue << std::endl;
return true;
}

bool TsWriteToView(const unsigned int& nValue  //[in] integer number to output
                     )
{
std::_tcout << nValue;
return true;
}

bool TsWriteToViewLn(const bool& bValue  //[in] boolean value to output
                     )
  {
  std::_tcout << (bValue ? _T("T") : _T("F")) << std::endl;
  return true;
  }

bool TsWriteToView(const bool& bValue  //[in] boolean value to output
                   )
  {
  std::_tcout << (bValue ? _T("T") : _T("F"));
  return true;
  }
  
  #endif //#ifndef KSTL_IO
#endif //_CONSOLE
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2004-10-04 22:07:10  Darko           Copied
 *       TsWriteToViewLn(const int&) from old version
 *  4    Biblioteka1.3         2004-10-01 15:49:09  Darko           fixed MSVC6
 *       SBCS build
 *  3    Biblioteka1.2         2004-08-23 17:59:36  Darko           Unicode build
 *  2    Biblioteka1.1         2004-06-03 14:30:54  Darko
 *       TsWrteText(TIME)
 *  1    Biblioteka1.0         2004-06-03 14:29:29  Darko
 * $
 *****************************************************************************/
