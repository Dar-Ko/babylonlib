/*$Workfile: KDbgBtnS.cpp$: implementation file
  $Revision: 11$ $Date: 2004-10-01 22:34:05$
  $Author: Darko$

  Dumps the style of the button control
  Copyright: CommonSoft Inc.
  Aug. 97 Darko Kolakovic
 */
 
// Group=Diagnostic

#include "stdafx.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

#ifndef _WINUSER_
  #if _MSC_VER < 1300
    #include <winuser.h>
  #else
    #include <WinUser.h>
  #endif
#endif

#if _MSC_VER < 1310 //Compilers older than Microsoft Visual C/C++ .Net v7.1
                    //See also: winuser.h
  #ifndef BS_PUSHBOX
    #define BS_PUSHBOX          0x0000000AL
  #endif
  #ifndef BS_TYPEMASK
    #define BS_TYPEMASK         0x0000000FL
  #endif
#endif

///////////////////////////////////////////////////////////////////////////////

//DumpButtonStyle()------------------------------------------------------------
/*Dumps the type and style of a button control.

  Button Control Types are mutually exclusive. Button's type could be changed
  with SetButtonStyle() to the one of following values:

              Button Control Types
              BS_PUSHBUTTON       0x00L
              BS_DEFPUSHBUTTON    0x01L
              BS_CHECKBOX         0x02L
              BS_AUTOCHECKBOX     0x03L
              BS_RADIOBUTTON      0x04L
              BS_3STATE           0x05L
              BS_AUTO3STATE       0x06L
              BS_GROUPBOX         0x07L
              BS_USERBUTTON       0x08L
              BS_AUTORADIOBUTTON  0x09L
              BS_PUSHBOX          0x0AL
              BS_OWNERDRAW        0x0BL

              Button Control Type bitmask
              BS_TYPEMASK         0x0FL

  A Button Control control created with the CreateWindow() or CreateWindowEx()
  function could have a combination of the following button styles:

              Button Control Styles
              BS_LEFTTEXT         0x20L
              Windows 95 and Windows NT 4.0 or greater (WINVER >= 0x0400)
              BS_TEXT             0x0000L
              BS_ICON             0x0040L
              BS_BITMAP           0x0080L
              BS_LEFT             0x0100L
              BS_RIGHT            0x0200L
              BS_CENTER           0x0300L
              BS_TOP              0x0400L
              BS_BOTTOM           0x0800L
              BS_VCENTER          0x0C00L
              BS_PUSHLIKE         0x1000L
              BS_MULTILINE        0x2000L
              BS_NOTIFY           0x4000L
              BS_FLAT             0x8000L
              BS_RIGHTBUTTON      BS_LEFTTEXT

  Note: CButton::SetButtonStyle() could change only button's type.
        CButton::GetButtonStyle() returns only first 8 bits (OXFF mask is used on
        actual style; see afxwin2.inl)

  Note: Microsoft Windows specific (Win).

  Example:
    ...
    {
    CButton btn;
    btn.Create(...);
    ...
    #ifdef _DEBUG
      DumpButtonStyle(btn.GetButtonStyle()); //Dumps flags lesser than 0xFF 
                                             //(from BS_PUSHBUTTON to BS_BITMAP)
      DumpButtonStyle((UINT)GetWindowLong(btn.m_hWnd, GWL_STYLE));

    #endif
    }

  See also: winuser.h, afxwin2.inl, CButton::GetButtonStyle(), CButton::Create()
 */
void DumpButtonStyle(UINT nBtnStyle //[in] style of a button control
                    )
{
CString strFlags;

  //Dump Button Control Type
switch (nBtnStyle & BS_TYPEMASK)
  {
  case BS_PUSHBUTTON     : strFlags += _T("BS_PUSHBUTTON ")     ; break; //0x00L
  case BS_DEFPUSHBUTTON  : strFlags += _T("BS_DEFPUSHBUTTON ")  ; break; //0x01L
  case BS_CHECKBOX       : strFlags += _T("BS_CHECKBOX ")       ; break; //0x02L
  case BS_AUTOCHECKBOX   : strFlags += _T("BS_AUTOCHECKBOX ")   ; break; //0x03L
  case BS_RADIOBUTTON    : strFlags += _T("BS_RADIOBUTTON ")    ; break; //0x04L
  case BS_3STATE         : strFlags += _T("BS_3STATE ")         ; break; //0x05L
  case BS_AUTO3STATE     : strFlags += _T("BS_AUTO3STATE ")     ; break; //0x06L
  case BS_GROUPBOX       : strFlags += _T("BS_GROUPBOX ")       ; break; //0x07L
  case BS_USERBUTTON     : strFlags += _T("BS_USERBUTTON ")     ; break; //0x08L
  case BS_AUTORADIOBUTTON: strFlags += _T("BS_AUTORADIOBUTTON "); break; //0x09L
  case BS_PUSHBOX        : strFlags += _T("BS_PUSHBOX ")        ; break; //0x0AL
  case BS_OWNERDRAW      : strFlags += _T("BS_OWNERDRAW ")      ; break; //0x0BL
  default: strFlags += _T("<unknown type> ");
  }

  //Dump Button Control Style

  /*Note: MSDN July 2003 BS_TYPEMASK 
    Microsoft Windows 2000: A composite style bit that results from using the
    OR operator on BS_* style bits. It can be used to mask out valid BS_* bits
    from a given bitmask. Note that this is out of date and does not correctly
    include all valid styles. Thus, you should not use this style.
   */
UINT nStyle = nBtnStyle & ~BS_TYPEMASK;    //Clear button's type bits

if (nStyle & BS_LEFTTEXT)                  //0x00000020L
  strFlags += "BS_LEFTTEXT ";

#if (WINVER >= 0x0400)
  if (nStyle & BS_TEXT)                    //0x00000000L
    strFlags += "BS_TEXT ";

    if (nStyle & BS_ICON)                  //0x00000040L
    strFlags += "BS_ICON ";
  if (nStyle & BS_BITMAP)                  //0x00000080L
    strFlags += "BS_BITMAP ";

  if ((nStyle & BS_CENTER) == BS_CENTER)   //0x00000300L
    strFlags += "BS_CENTER ";
  else
    {
    if (nStyle & BS_LEFT)                  //0x00000100L
      strFlags += "BS_LEFT ";
    if (nStyle & BS_RIGHT)                 //0x00000200L
      strFlags += "BS_RIGHT ";
    }

  if ((nStyle & BS_VCENTER) == BS_VCENTER) //0x00000C00L
    strFlags += "BS_VCENTER ";
  else
    {
    if (nStyle & BS_TOP)                   //0x00000400L
      strFlags += "BS_TOP ";
    if (nStyle & BS_BOTTOM)                //0x00000800L
      strFlags += "BS_BOTTOM ";
    }

  if (nStyle & BS_PUSHLIKE)                //0x00001000L
    strFlags += "BS_PUSHLIKE ";
  if (nStyle & BS_MULTILINE)               //0x00002000L
    strFlags += "BS_MULTILINE ";
  if (nStyle & BS_NOTIFY)                  //0x00004000L
    strFlags += "BS_NOTIFY ";
  if (nStyle & BS_RIGHTBUTTON)             //BS_LEFTTEXT
    strFlags += "BS_RIGHTBUTTON ";
    if (nStyle & BS_FLAT)                  //0x00008000L
      strFlags += "BS_FLAT ";
#endif

TRACE2("Button style %Xh:\n\t%s\n",nBtnStyle,strFlags);
}

//-----------------------------------------------------------------------------
/*Dumps the type and style of a button control.

  Note: Microsoft Windows specific (Win).

  Example:
    class CAboutDlg : public CDialog
    {
    ...
    }

    BOOL CAboutDlg::OnInitDialog()
    {
    ...
    CWnd* pBtn = GetDlgItem(IDOK);
    #ifdef _DEBUG
      DumpButtonStyle(pBtn->GetSafeHwnd());
    #endif
    ...
    }

*/
void DumpButtonStyle(HWND hButton //[in] button control handle
                    )
{
ASSERT(::IsWindow(hButton));
DumpButtonStyle((UINT)GetWindowLong(hButton, GWL_STYLE));
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
/*----------------------------------------------------------------------------
  <winuser.h>                               Button Control Types and Styles

  Microsoft              v2.0                v4.0, 4.2, 5.0, 6.0
  Visual C/C++
  _MSC_VER                900               1000, 1020, 1100, 1200

  Microsoft                                        v7.0(2002)           v7.1(2003)
  Visual C++.NET
  _MSC_VER                                         1300                    1310
                        #if(WINVER <= 0x030A)
  0x0000                 BS_PUSHBUTTON          BS_PUSHBUTTON          BS_PUSHBUTTON          
  0x0001                 BS_DEFPUSHBUTTON       BS_DEFPUSHBUTTON       BS_DEFPUSHBUTTON       
  0x0002                 BS_CHECKBOX            BS_CHECKBOX            BS_CHECKBOX            
  0x0003                 BS_AUTOCHECKBOX        BS_AUTOCHECKBOX        BS_AUTOCHECKBOX        
  0x0004                 BS_RADIOBUTTON         BS_RADIOBUTTON         BS_RADIOBUTTON         
  0x0005                 BS_3STATE              BS_3STATE              BS_3STATE              
  0x0006                 BS_AUTO3STATE          BS_AUTO3STATE          BS_AUTO3STATE          
  0x0007                 BS_GROUPBOX            BS_GROUPBOX            BS_GROUPBOX            
  0x0008                 BS_USERBUTTON          BS_USERBUTTON          BS_USERBUTTON          
  0x0009                 BS_AUTORADIOBUTTON     BS_AUTORADIOBUTTON     BS_AUTORADIOBUTTON     
  0x000A                                                               BS_PUSHBOX             
  0x000B                 BS_OWNERDRAW           BS_OWNERDRAW           BS_OWNERDRAW           
  0x000F                                                               BS_TYPEMASK            
  0x0020                 BS_LEFTTEXT            BS_LEFTTEXT            BS_LEFTTEXT            
                        #end                   #if(WINVER >= 0x0400)  #if(WINVER >= 0x0400)  
  0x0000                                        BS_TEXT                BS_TEXT                
  0x0040                                        BS_ICON                BS_ICON                
  0x0080                                        BS_BITMAP              BS_BITMAP              
  0x0100                                        BS_LEFT                BS_LEFT                
  0x0200                                        BS_RIGHT               BS_RIGHT               
  0x0300                                        BS_CENTER              BS_CENTER              
  0x0400                                        BS_TOP                 BS_TOP                 
  0x0800                                        BS_BOTTOM              BS_BOTTOM              
  0x0C00                                        BS_VCENTER             BS_VCENTER             
  0x1000                                        BS_PUSHLIKE            BS_PUSHLIKE            
  0x2000                                        BS_MULTILINE           BS_MULTILINE           
  0x4000                                        BS_NOTIFY              BS_NOTIFY              
  0x8000                                        BS_FLAT                BS_FLAT                
  0x0020=BS_LEFTTEXT                            BS_RIGHTBUTTON         BS_RIGHTBUTTON         
                                               #end                   #end                   
  Resource file:
  DEFPUSHBUTTON,”Defpushbutton",<ID>, <Dimension>
  DEFPUSHBUTTON,”Defpushbutton",<ID>, <Dimension>, BS_FLAT 
  PUSHBUTTON   ,”Pushbutton"   ,<ID>, <Dimension>
  PUSHBUTTON   ,”Pushbutton"   ,<ID>, <Dimension>, WS_DISABLED 
  PUSHBUTTON   ,”Pushbutton"   ,<ID>, <Dimension>, BS_FLAT 
  PUSHBUTTON   ,”Pushbutton"   ,<ID>, <Dimension>, BS_FLAT|WS_DISABLED 
  RADIOBUTTON  ,”Radio"        ,<ID>, <Dimension>
  RADIOBUTTON  ,”Radio"        ,<ID>, <Dimension>, BS_FLAT 
  RADIOBUTTON  ,”Radio"        ,<ID>, <Dimension>, BS_PUSHLIKE 
  GROUPBOX     ,”GroupBox"     ,<ID>, <Dimension>
  CHECKBOX     ,”Checkbox"     ,<ID>, <Dimension>
  CHECKBOX     ,”Checkbox"     ,<ID>, <Dimension>, BS_FLAT 
  CONTROL      ,”Checkbox"     ,<ID>, "Button"   , BS_AUTOCHECKBOX                    , <Dimension>
  CONTROL      ,”Checkbox"     ,<ID>, "Button"   , BS_AUTOCHECKBOX|BS_FLAT            , <Dimension>
  CONTROL      ,”Checkbox"     ,<ID>, "Button"   , BS_AUTOCHECKBOX|BS_PUSHLIKE        , <Dimension>
  CONTROL      ,”Checkbox"     ,<ID>, "Button"   , BS_AUTOCHECKBOX|BS_PUSHLIKE|BS_FLAT, <Dimension>
  CONTROL      ,”Tristate"     ,<ID>, "Button"   , BS_3STATE                          , <Dimension>
  CONTROL      ,”Tristate"     ,<ID>, "Button"   , BS_AUTO3STATE                      , <Dimension>
  CONTROL      ,”Tristate"     ,<ID>, "Button"   , BS_AUTO3STATE|BS_PUSHLIKE          , <Dimension>
  CONTROL      ,”AutoRadio"    ,<ID>, "Button"   , BS_AUTORADIOBUTTON                 , <Dimension>
  CONTROL      ,”AutoRadio"    ,<ID>, "Button"   , BS_AUTORADIOBUTTON|BS_FLAT         , <Dimension>
  CONTROL      ,”AutoRadio"    ,<ID>, "Button"   , BS_AUTORADIOBUTTON|BS_PUSHLIKE     , <Dimension>
  CONTROL      ,”Pushbox"      ,<ID>, "Button"   , BS_PUSHBOX                         , <Dimension>
  CONTROL      ,”Ownerdraw"    ,<ID>, "Button"   , BS_OWNERDRAW                       , <Dimension>
  CONTROL      ,"Button"       ,<ID>, "Button",    BS_PUSHBOX                         , <Dimension>
 */
/*****************************************************************************
 * $Log: 
 *  11   Biblioteka1.10        2004-10-01 22:34:05  Darko           stdafx.h
 *  10   Biblioteka1.9         2003-08-29 08:50:02  Darko           comment
 *  9    Biblioteka1.8         2003-08-27 15:30:34  Darko           fixed new
 *       _MSC_VER =1310 styles 
 *  8    Biblioteka1.7         2003-08-27 11:50:02  Darko           Replaced
 *       else-if with switch
 *  7    Biblioteka1.6         2003-08-25 01:17:14  Darko           excluded
 *       BS_FLAT  for MSVC 5.0
 *  6    Biblioteka1.5         2003-08-21 15:27:07  Darko           formatting
 *  5    Biblioteka1.4         2002-01-29 23:20:07  Darko           Used libraries
 *       notes 
 *  4    Biblioteka1.3         2002-01-29 15:38:32  Darko           Tag update
 *  3    Biblioteka1.2         2001-07-11 22:50:25  Darko           
 *  2    Biblioteka1.1         2001-06-08 23:49:26  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:55:49  Darko           
 * $
 *  0                          Aug. 97 Darko Kolakovic
 *****************************************************************************/
