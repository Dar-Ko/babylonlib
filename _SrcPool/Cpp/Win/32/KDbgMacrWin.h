/*$RCSfile: KDbgMacrWin.h,v $: header file
  $Revision: 1.2 $ $Date: 2011/06/07 21:26:34 $
  $Author: ddarko $

  Dumps values of some predefined macros specifying Microsoft Windows platform.
  Copyright: CommonSoft Inc.
  Darko Kolakovic April 1988, 2008-07
*/
/* Group=Diagnostic                                                          */

#ifndef _KDBGMACRWIN_H_
    /*$RCSfile: KDbgMacrWin.h,v $ sentry */
  #define _KDBGMACRWIN_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __GNUC__  /*GNU C/C++ Compiler                                        */
  /*GNU-Specific macros ---------------------------------------------------- */      
  #ifdef _WIN32
    #warning "Target OS is Windows 32b."
  #endif
  #ifdef WIN32
    #warning "Target OS is Windows 32b."
  #endif
  #ifdef _WIN64
    #warning "Target OS is Windows 64b."
  #endif
#endif /*__GNUC__
    
  /*Microsoft-Specific macros ---------------------------------------------- */
  #ifdef WIN16
    #pragma message ("Target OS is Win16.")
  #endif
  #ifdef _WINDOWS
    #pragma message ("Target OS is Windows.")
  #endif
  #ifdef _WIN95
    #pragma message ("Target OS is Win95.")
  #endif
  #ifdef _WINNT
    #pragma message ("Target OS is WinNT.")
  #endif
  #ifdef _WIN32
    #pragma message ("Target OS is Win32.")
  #endif
  #ifdef _WIN64
    #pragma message ("Target OS is Win64.")
  #endif

  #ifdef WINVER
    /*Windows Target Version Macros

     +---------------------+-------------------------------------+
     |   Macros to Define  |   Minimum System Required           |
     +---------------------+-------------------------------------+
     | WINVER=0x030A       |Windows 3.1                          |
     |                     |                                     |
     | WINVER=0x0400       |Windows 95 and Windows NT 4.0        |
     |                     |                                     |
     |_WIN32_WINDOWS=0x0410|Windows 98 and Windows NT 4.0        |
     |WINVER=0x0400        |                                     |
     |                     |                                     |
     |_WIN32_WINNT=0x0400  |Windows NT 4.0                       |
     |WINVER=0x0400        |                                     |
     |                     |                                     |
     |_WIN32_WINDOWS=0x0410|Windows 98                           |
     |                     |                                     |
     |_WIN32_WINDOWS=0x0490|Windows Millenium                    |
     |                     |                                     |
     |WINVER=0x040A        |Windows 98 4.10                      |
     |                     |                                     |
     |WINVER=0x045A        |Windows Millenium 4.90               |
     |                     |                                     |
     |WINVER=0x0500        |Windows 98 and Windows 2000          |
     |                     |                                     |
     |_WIN32_WINNT=0x0500  |Windows 2000                         |
     |WINVER=0x0500        |                                     |
     |                     |                                     |
     |_WIN32_WINNT=0x0501  |Windows XP, Windows Server 2003      |
     |WINVER=0x0501        |                                     |
     |                     |                                     |
     |_WIN32_WINNT=0x0502  |Windows XP SP2,                      |
     |                     |Windows Server 2003 SP1              |
     |                     |                                     |
     |_WIN32_WINNT=0x0600  |Windows Vista, Windows Server 2008   |
     |WINVER=0x0600        |                                     |
     |                     |                                     |
     |_WIN32_WINNT=0x0601  |Windows 7                            |
     |WINVER=0x0601        |                                     |
     |                     |                                     |
     |_WIN64               |                                     |
     +---------------------+-------------------------------------+
     |_WIN32_IE=0x0300     |Internet Explorer 3.0, 3.01, 3.02    |
     |_WIN32_IE=0x0400     |Internet Explorer 4.0                |
     |_WIN32_IE=0x0401     |Internet Explorer 4.01               |
     |_WIN32_IE=0x0500     |Internet Explorer 5.0, 5.0a, 5.0b    |
     |_WIN32_IE=0x0501     |Internet Explorer 5.01               |
     |_WIN32_IE=0x0532     |Internet Explorer 5.5                |
     |_WIN32_IE=0x0600     |Internet Explorer 6.00               |
     |_WIN32_IE=0x0700     |Internet Explorer 7.00               |
     |_WIN32_IE=0x0800     |Internet Explorer 8.00               |
     +---------------------+-------------------------------------+

     Note: Setting WINVER to 0x0500 implies _WIN32_IE=0x0400
     */
    const WORD g__WINVER = WINVER;

    #if WINVER == 0x0300
      #pragma message ("Target OS is MS Windows 3.0.")
    #elif WINVER == 0x030a
      #pragma message ("Target OS is MS Windows 3.1.")
    #elif WINVER == 0x0400
      #pragma message ("Target OS is MS Windows NT 4.0.")
    #elif WINVER == 0x040A
      #pragma message ("Target OS is MS Windows 98 4.10.")
    #elif WINVER == 0x045A
      #pragma message ("Target OS is MS Windows Millenium 4.90.")
    #elif WINVER == 0x0500
      #pragma message ("Target OS is MS Windows 2000 or 98.")
    #elif WINVER == 0x0501
      #pragma message ("Target OS is MS Windows XP or 2003.")
    #elif WINVER == 0x0502
      #pragma message ("Target OS is MS Windows 2003 SP1 or XP SP2")
    #elif WINVER == 0x0600
      #pragma message ("Target OS is MS Windows Vista or 2008.")
    #elif WINVER == 0x0601
      #pragma message ("Target OS is MS Windows 7.")
    #else
      #pragma message ("Target OS is MS Windows ?.?.")
    #endif
  #endif
 
  #ifdef _WIN32_WINNT
    #if _WIN32_WINNT == 0x0400
      #pragma message ("Target OS is MS Windows NT 4.0 (WINNT).")
    #elif _WIN32_WINNT == 0x0500
      #pragma message ("Target OS is MS Windows 2000 (WINNT).")
    #elif _WIN32_WINNT == 0x0501
      #pragma message ("Target OS is MS Windows XP (WINNT).")
    #elif _WIN32_WINNT == 0x0502
      #pragma message ("Target OS is MS Windows Server 2003 family.")
    #elif _WIN32_WINNT == 0x0600
      #pragma message ("Target OS is MS Windows Vista.")
    #elif _WIN32_WINNT == 0x0601
      #pragma message ("Target OS is MS Windows 7.")
    #else
      #pragma message ("Target OS is MS Windows ?? (WINNT).")
    #endif
  #endif

  
   #if defined (_WIN32_WCE) || defined (UNDER_CE)
    #ifdef _WIN32_WCE
    /*Microsoft eMbedded Visual C++ Compiler defines OS version as
      variable $(CEVersion) value:
         \D _WIN32_WCE=$(CEVersion), \D  UNDER_CE=$(CEVersion), ...
     */
      const unsigned int g__WIN32_WCE = _WIN32_WCE;
    #else
      const unsigned int g__WIN32_WCE = UNDER_CE;
    #endif //_WIN32_WCE

    #if (_WIN32_WCE == 201) || (UNDER_CE == 201) /*Windows CE 2.01*/
      #pragma message ("Target OS is MS Windows CE 2.01.")
    #elif (_WIN32_WCE == 211) || (UNDER_CE == 211) /*Windows CE 2.11*/
      #pragma message ("Target OS is MS Windows CE 2.11.")
    #elif (_WIN32_WCE == 300) || (UNDER_CE == 300) /* Windows CE 3.0*/
      #pragma message ("Target OS is MS Windows CE 3.0.")
    #elif (_WIN32_WCE == 400) || (UNDER_CE == 400) /*Windows CE 4.0*/
      #pragma message ("Target OS is MS Windows CE 4.0.")
    #elif (_WIN32_WCE == 410) || (UNDER_CE == 410) /*Windows CE 4.10*/
      #pragma message ("Target OS is MS Windows CE 4.10.")
    #elif (_WIN32_WCE == 420) || (UNDER_CE == 420) /*Windows CE 4.20*/
      #pragma message ("Target OS is MS Windows CE 4.20.")
    #else
      #pragma message ("Target OS is MS Windows CE ?.??.")
    #endif

  #endif /*_WIN32_WCE*/
   
/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KDBGMACRWIN_H_                                                     */
/*****************************************************************************
 * $Log: KDbgMacrWin.h,v $
 * Revision 1.2  2011/06/07 21:26:34  ddarko
 * Added Win7
 *
 * Revision 1.1  2011/06/07 20:33:09  ddarko
 * Extracted Windows macros from KDbgmacr.h
 *
 *****************************************************************************/
