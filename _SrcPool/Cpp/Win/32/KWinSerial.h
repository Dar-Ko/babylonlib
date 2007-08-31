/*$Workfile: KWinSerial.h$: header file
  $Revision: 4$ $Date: 2007-08-24 18:15:44$
  $Author: Darko Kolakovic$

  Constants related to Windows platform version
  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2006-01-11 Darko Kolakovic
 */
// Group=Windows

#ifndef _KWINSERIAL_H_
    //$Workfile: KWinSerial.h$ sentry
  #define _KWINSERIAL_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32 //Windows 32-bit platform

#ifndef _USE_ATL
  #include <windows.h>
#endif

#ifndef SYMBOLICLINK_COM
  #ifndef _UNICODE
  /*Symbolic name for Serial Communications (COM) port have following
    form:
        \\.\COMn
        where n (0,...,k) is COM port number.

    Note: Unicode version of the name have prefix "\\?\" .
    Note: Microsoft Windows specific (Win32).

    Example: 
       char* szComName = "\\\\.\\COM10";
       char szCom[MAX_PATH];
       sprintf(szCom, SYMBOLICLINK_COM, 10);
       
    See also: CreateFile(), CreateSymbolicLink().
  */
    #define SYMBOLICLINK_COM "\\\\.\\COM%d"
  #else
    #define SYMBOLICLINK_COM L"\\\\?\\COM%d"
  #endif
#endif

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////
/*
  Note: Microsoft Windows specific (Win32).

  See also: 
 */

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
}

///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
#endif  //_KWINSERIAL_H_
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
