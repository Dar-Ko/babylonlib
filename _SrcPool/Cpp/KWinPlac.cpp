/*$Workfile: KWinPlac.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:39:56 $
  $Author: ddarko $

  Encapsulates the WINDOWPLACEMENT structure
  Copyright: CommonSoft Inc
  July '95 Darko Kolakovic
  Apr. '97 C replaced with C++ D.K.
  Dec. '97 Encapsulated in class  D.K.
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KWinPlac.h" //CWindowPlacement class
#include <String.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

    //Format string used to write WINDOWPLACEMENT
static LPCTSTR s_lpszFormat = "%u,%u,%d,%d,%d,%d,%d,%d,%d,%d";

///////////////////////////////////////////////////////////////////////////////

/*The WINDOWPLACEMENT structure contains information about the placement of
  a window on the screen.
  Section and entry names are set to the default values.
 */
CWindowPlacement::CWindowPlacement() :
  m_strEntry  ("WindowPos"),//Registry entry containing the window placement
  m_strSection("Settings")  //Registry section containing the entry
{
TRACE0("CWindowPlacement::CWindowPlacement()\n");
Empty();
}

/*Retrieves the show state and the normal (restored), minimized, and maximized
  positions of a window.

  Section name is set to the default value. Runtime class object pWnd is used
  to create entry name .
 */
CWindowPlacement::CWindowPlacement(CWnd* pWnd //pointer to window
                                   ):
  m_strSection("Settings")  //Registry section containing the entry
{
ASSERT(pWnd != NULL);
ASSERT(::IsWindow(pWnd->m_hWnd));
TRACE1("CWindowPlacement::CWindowPlacement(%s)\n",pWnd->GetRuntimeClass()->m_lpszClassName);

length = sizeof(tagWINDOWPLACEMENT); //length, in bytes, of the structure
m_strEntry.Format("Pos%s",pWnd->GetRuntimeClass()->m_lpszClassName);
pWnd->GetWindowPlacement((tagWINDOWPLACEMENT*)this);
}

//::operator =()---------------------------------------------------------------
/*Assignment operator
 */
CWindowPlacement& CWindowPlacement::operator=(const tagWINDOWPLACEMENT& Source //structure
                                              //with window's state and size
                                              )
{
if (this != &Source)  //If operator is not applied on object itself
  {
  length                 =Source.length                 ;//length, in bytes, of the structure
  flags                  =Source.flags                  ;//flags that control the position
  showCmd                =Source.showCmd                ;//current show state of the window
  ptMinPosition.x        =Source.ptMinPosition.x        ;//the position of the windows
  ptMinPosition.y        =Source.ptMinPosition.y        ;//top-left corner when the window is minimized
  ptMaxPosition.x        =Source.ptMaxPosition.x        ;//the position of the windows
  ptMaxPosition.y        =Source.ptMaxPosition.y        ;//top-left corner when the window is maximized
  rcNormalPosition.left  =Source.rcNormalPosition.left  ;//the window’s coordinates when
  rcNormalPosition.top   =Source.rcNormalPosition.top   ;//the window is in the normal position.
  rcNormalPosition.right =Source.rcNormalPosition.right ;
  rcNormalPosition.bottom=Source.rcNormalPosition.bottom;
  }
return (*this);
}

//::Dump()---------------------------------------------------------------------
#ifdef _DEBUG
/*CWindowPlacement diagnostics
 */
void CWindowPlacement::Dump(CDumpContext& dc //diagnostic dump context for dumping
                            ) const
{
dc << TEXT( " a CWindowPlacement at " ) << (void *) this
   << TEXT( "\n\t{\n\tlength                  = " ) << length
   << TEXT( "\n\tflags                   = " ) << flags
   << TEXT( " (" );

if (flags & WPF_SETMINPOSITION )
  dc << TEXT( " WPF_SETMINPOSITION" );
if (flags & WPF_RESTORETOMAXIMIZED )
  dc << TEXT( " WPF_RESTORETOMAXIMIZED" );

#if (_WIN32_WINNT == 0x0500)  //Win2k
  if (flags & WPF_ASYNCWINDOWPLACEMENT )
    dc << TEXT( " WPF_ASYNCWINDOWPLACEMENT" );
#endif //Win2k

dc <<   TEXT( ")\n\tshowCmd                 = " ) << showCmd
   << TEXT( " (" );
switch( showCmd )
  {
  case SW_HIDE:           dc << TEXT( "SW_HIDE" );           break;
  case SW_MINIMIZE:       dc << TEXT( "SW_MINIMIZE" );       break;
  case SW_RESTORE:        dc << TEXT( "SW_RESTORE" );        break;
  case SW_SHOW:           dc << TEXT( "SW_SHOW" );           break;
  case SW_SHOWMAXIMIZED:  dc << TEXT( "SW_SHOWMAXIMIZED" );  break;
  case SW_SHOWMINIMIZED:  dc << TEXT( "SW_SHOWMINIMIZED" );  break;
  case SW_SHOWMINNOACTIVE:dc << TEXT( "SW_SHOWMINNOACTIVE" );break;
  case SW_SHOWNA:         dc << TEXT( "SW_SHOWNA" );         break;
  case SW_SHOWNOACTIVATE: dc << TEXT( "SW_SHOWNOACTIVATE" ); break;
  case SW_SHOWNORMAL:     dc << TEXT( "SW_SHOWNORMAL" );     break;
  }

dc << TEXT( ")\n\tptMinPosition.x         = " ) << ptMinPosition.x
   <<  TEXT( "\n\tptMinPosition.y         = " ) << ptMinPosition.y
   <<  TEXT( "\n\tptMaxPosition.x         = " ) << ptMaxPosition.x
   <<  TEXT( "\n\tptMaxPosition.y         = " ) << ptMaxPosition.y
   <<  TEXT( "\n\trcNormalPosition.left   = " ) << rcNormalPosition.left
   <<  TEXT( "\n\trcNormalPosition.top    = " ) << rcNormalPosition.top
   <<  TEXT( "\n\trcNormalPosition.right  = " ) << rcNormalPosition.right
   <<  TEXT( "\n\trcNormalPosition.bottom = " ) << rcNormalPosition.bottom
   <<  TEXT( "\n\t}\n" );
}
#endif // _DEBUG

//LoadSettings()---------------------------------------------------------------
#include <StdIO.h>                     /*_stscanf.            */
/*Read the window placement from the settings section of the application's .INI file.
  If the function succeeds, the return value is TRUE.
  If the function fails, the return value is FALSE.

  Example:
    #include "KWinPlac.h" //CWindowPlacement class
    void CMainFrame::InitialShowWindow(UINT nCmdShow)
      {
      CWindowPlacement wpPos(this);
      //Read window placement
      if (!wpPos.LoadSettings())
        {
        ShowWindow(nCmdShow);
        return;
        }
      if (nCmdShow != SW_SHOWNORMAL)
        wpPos.showCmd = nCmdShow;
      SetWindowPlacement(&wpPos);
      ShowWindow(wpPos.showCmd);
      }
*/
BOOL CWindowPlacement::LoadSettings(
       LPCTSTR lpszEntry,  //= NULL the entry name of the value to be retrieved
       LPCTSTR lpszSection //= NULL the section containing the entry
       )
{
try
  {
  CString strSection;
  CString strKey;
  CString strValue;
  if (lpszEntry != NULL)
    {
    ASSERT(lpszEntry[0] !='\0'); //Empty string
    strKey = lpszEntry;
    }
  else
    strKey = m_strEntry;
  if (lpszSection != NULL)
    {
    ASSERT(lpszSection[0] !='\0'); //Empty string
    strSection = lpszSection;
    }
  else
    strSection = m_strSection;

  TRACE2("CWindowPlacement::LoadSettings( %s\\%s )\n",(LPCTSTR)strSection,
                                                    (LPCTSTR)strKey);

  CString strBuffer = AfxGetApp()->GetProfileString((LPCTSTR)strSection,
                                                    (LPCTSTR)strKey);
  if (strBuffer.IsEmpty())
    return FALSE;

  if ( _stscanf(strBuffer, s_lpszFormat,
                &flags, &showCmd,
                &ptMinPosition.x, &ptMinPosition.y,
                &ptMaxPosition.x, &ptMaxPosition.y,
                &rcNormalPosition.left,  &rcNormalPosition.top,
                &rcNormalPosition.right, &rcNormalPosition.bottom) == 10)
    {
    length = sizeof tagWINDOWPLACEMENT;   //Fill rest of the placement structure
    return TRUE;
    }

  Empty();
  return FALSE; //Insufficient data
  }
catch (...)
  {
  TRACE2("%s %d CWindowPlacement failure.\n",THIS_FILE, __LINE__);
  Empty();
  return FALSE;
  }
}

//SaveSettings()---------------------------------------------------------------
/*Store the window placement to the registry (or profile) file.
  If the function succeeds, the return value is TRUE.
  If the function fails, the return value is FALSE.
  To get extended error information, call GetLastError.

  Example:
    void CMainFrame::OnClose()
      {
        //Before it is destroyed, save the position of the window
      CWindowPlacement wpPos(this);
      wpPos.SaveSettings(); //write it to the .INI file

      CMDIFrameWnd::OnClose();
      }
*/
BOOL CWindowPlacement::SaveSettings(
       LPCTSTR lpszEntry, //= NULL the entry into which the value is to be written
       LPCTSTR lpszSection//= NULL the section containing the entry
       )
{
try
  {
  CString strSection;
  CString strKey;
  CString strValue;
  if (lpszEntry != NULL)
    {
    ASSERT(lpszEntry[0] !='\0'); //Empty string
    strKey = lpszEntry;
    }
  else
    strKey = m_strEntry;
  if (lpszSection != NULL)
    {
    ASSERT(lpszSection[0] !='\0'); //Empty string
    strSection = lpszSection;
    }
  else
    strSection = m_strSection;

  TRACE2("CWindowPlacement::SaveSettings( %s\\%s )\n",(LPCTSTR)strSection,
                                                    (LPCTSTR)strKey);
  strValue.Format(s_lpszFormat,
    (showCmd == SW_SHOWMAXIMIZED) ? WPF_RESTORETOMAXIMIZED : 0,
           showCmd,
           ptMinPosition.x, ptMinPosition.y,
           ptMaxPosition.x, ptMaxPosition.y,
           rcNormalPosition.left , rcNormalPosition.top,
          rcNormalPosition.right, rcNormalPosition.bottom);

  return AfxGetApp()->WriteProfileString((LPCTSTR)strSection,
                                       (LPCTSTR)strKey,
                                       (LPCTSTR)strValue);
  }
catch (...)
  {
  TRACE2("%s %d CWindowPlacement failure.\n",__FILE__, __LINE__);
  return FALSE;
  }
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         25/01/2002 3:59:32 PMDarko           Updated
 *       comments
 *  4    Biblioteka1.3         19/08/2001 10:56:14 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:53:30 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:52:27 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:04:11 PMDarko           
 * $
 *****************************************************************************/
