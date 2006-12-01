/*$Workfile: KIsRASCo.cpp$: implementation file
  $Revision: 6$ $Date: 2005-05-03 11:16:07$
  $Author: Darko Kolakovic$

  Check RAS connection has been successfully established.
  BUG: Q200840 WinNT3.51 RasGetConnectStatus Does Not Report
       the Correct State
  Copyright: CommonSoft Inc.
  May 98 D. Kolakovic
 */
// Group=Windows

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <afxwin.h>
#ifndef __AFXWIN_H__
  #pragma message (__FILE__ " #include <Windows.h>")
  #include <windows.h>
  #ifdef WIN16
    #include <win16ext.h>           //Required only for win16 applications
  #endif
#endif
#pragma hdrstop

#ifdef _DEBUG
  #pragma message (__FILE__ " _DEBUG")
  #undef THIS_FILE
  #ifdef __AFXWIN_H__
    static char BASED_CODE THIS_FILE[] = __FILE__;
  #else
    #include <Assert.h>
    #ifndef ASSERT
      #define ASSERT(expression) assert(expression)
    #endif
  #endif
#else
  #ifndef __AFXWIN_H__
    #pragma message (__FILE__ " NODEBUG")
    #ifndef ASSERT
      #define ASSERT(e)  ((void)0)
    #endif
  #endif
#endif

#ifndef _RAS_H_
    #include <ras.h> //Remote Access external API
    #include <raserror.h> //ERROR_BUFFER_TOO_SMALL
#endif

    //Link with RAS API library
#pragma comment(lib, "rasapi32.lib")

//IsRASConnected()-------------------------------------------------------------
/*Retrieves information on the current status of a remote access connection.

      struct _RASCONNSTATUS
        {
        DWORD        dwSize; //structure size [byte]
        RASCONNSTATE rasconnstate; //current state of the RasDial connection
                                   //process
        DWORD        dwError; //if nonzero, indicates the reason for failure
        TCHAR        szDeviceType[RAS_MaxDeviceType + 1]; //type of the current
                                                          //device
        TCHAR        szDeviceName[RAS_MaxDeviceName + 1]; //name of the current
                                                          //device
        } RASCONNSTATUS;

  Two state values are especially significant:

        State                   Meaning
        RASCS_Connected         Indicates that the connection has been
                                successfully established.
        RASCS_Disconnected      Indicates that the connection has failed.

  Note: The general RAS functionality is contained in rasapi32.dll. To use
        the general RAS functions, you must link against rasapi32.lib and
        include ras.h. The RAS common dialogs, which are only supported on
        Windows NT® 4.0, are implemented in rasdlg.dll. To use this
        functionality, you must link against rasdlg.lib and include rasdlg.h.

  Note: Microsoft Windows specific (Win).

  Note: BUG: See Q200840 WinNT3.51 RasGetConnectStatus Does Not Report
        the Correct State

  Returns: FALSE if Dial-up phonebook is empty or none of RAS connections are not
  active. Returns TRUE if at least the one connection has been successfully
  established.

  See Also: Ras.h/RASCONNSTATE
 */
BOOL IsRASConnected()
{
  //Assuming only one active connetion
RASCONN rasCurrentConnection;
rasCurrentConnection.dwSize = sizeof(RASCONN); //structure size [byte]
DWORD dwSize = rasCurrentConnection.dwSize; //on input, contains the size of
  //the RASCONN array. On output, RasEnumConnections() sets this variable to
  //the number of bytes required to enumerate all RAS connections.

DWORD dwNoofRAS; //number of RASCONN structures written to the buffer
LPRASCONN lprasTemp = NULL; //List of active connections

    //List all active RAS connections.
DWORD dwRet = RasEnumConnections(&rasCurrentConnection,//array to receive RAS data
                      &dwSize,              //size in bytes of buffer
                      &dwNoofRAS            //number of connections written
                      );                    //to buffer
if(dwRet == ERROR_BUFFER_TOO_SMALL) //More than one active connection
  {
  lprasTemp = (LPRASCONN)new BYTE[dwSize];
  if(lprasTemp == NULL)
    dwRet = ERROR_NOT_ENOUGH_MEMORY;
  else //Try with bigger buffer
    {
    lprasTemp->dwSize = sizeof(RASCONN);
    dwRet = RasEnumConnections(lprasTemp, //array to receive RAS data
                               &dwSize,   //size in bytes of buffer
                               &dwNoofRAS //number of connections written
                               );         //to buffer
    }
  }

if (dwRet == 0) //Check if the connection has been successfully established
  {
  if(dwNoofRAS > 0) //One or more connections are currently active.
    {
    RASCONNSTATUS rasStatus;
    rasStatus.dwSize = sizeof(RASCONNSTATUS); //the structure size [byte]
    if (lprasTemp == NULL)
      {
        //Get the status of the remote access connection
      if((dwRet = RasGetConnectStatus(rasCurrentConnection.hrasconn, //handle to RAS
                                              //connection of interest
                        &rasStatus)) == 0)//buffer to receive status data
        return (rasStatus.rasconnstate == RASCS_Connected);
      }
    else //More than one connection are currently active
      {
      while(dwNoofRAS > 0)
        {
        if((dwRet = RasGetConnectStatus(lprasTemp[dwNoofRAS].hrasconn,
                                        &rasStatus)) == 0)
          if(rasStatus.rasconnstate == RASCS_Connected)
            {
            delete[] lprasTemp;
            return TRUE;
            }
        dwNoofRAS--;
        }

      delete[] lprasTemp;
      TRACE0("RasGetConnectStatus() failed!\n");
      ASSERT(FALSE);
      }
    }
  }

#ifdef _DEBUG
  if (dwRet != 0)  //Other RAS error
    {
    const int MESSAGE_SIZE = 256;
    TCHAR szMessage[MESSAGE_SIZE];
    if(RasGetErrorString((UINT)dwRet,         //error to get string for
                         szMessage,           //buffer to hold error string
                         MESSAGE_SIZE) != 0 ) //size of buffer [byte]
      TRACE(_T("Error %u: Undefined RAS Dial Error.\n"),dwRet);
    else
      TRACE(szMessage);
    ASSERT(FALSE);
    }
#endif

return FALSE; //No phonebook entries or active RAS connections
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2005-05-03 11:16:07  Darko Kolakovic Unicode build
 *  5    Biblioteka1.4         2005-05-03 01:46:20  Darko           comments, case
 *       of included files
 *  4    Biblioteka1.3         2005-04-28 20:46:41  Darko           Comments
 *  3    Biblioteka1.2         2002-01-29 23:21:23  Darko           Used lbraries
 *       notes 
 *  2    Biblioteka1.1         2002-01-29 15:40:37  Darko           Tag update
 *  1    Biblioteka1.0         2001-07-07 01:13:42  Darko           
 * $
 *****************************************************************************/
