/*$Workfile: H:\_SrcPool\Cpp\KDbgBtnS.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:10:21 $
  $Author: ddarko $

  Dumps the style of the button control
  Copyright: CommonSoft Inc.
  Aug. 97 Darko Kolakovic
 */
 
// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include <AfxWin.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

///////////////////////////////////////////////////////////////////////////////

//DumpButtonStyle()------------------------------------------------------------
/*Dumps the style of a button control. Values for the style flags are from
  WinRes.h header file.

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
 */
void DumpButtonStyle(UINT nBtnStyle //[in] style of a button control
                    )
{
CString strFlags;
if (nBtnStyle == BS_PUSHBUTTON)         //0x00000000L
	strFlags += "BS_PUSHBUTTON ";
else if ((nBtnStyle & 0xF) == BS_DEFPUSHBUTTON)       //0x00000001L
	strFlags += "BS_DEFPUSHBUTTON ";
else if ((nBtnStyle & 0xF) == BS_CHECKBOX)            //0x00000002L
	strFlags += "BS_CHECKBOX ";
else if ((nBtnStyle & 0xF) == BS_AUTOCHECKBOX)        //0x00000003L
	strFlags += "BS_AUTOCHECKBOX ";
else if ((nBtnStyle & 0xF) == BS_RADIOBUTTON)         //0x00000004L
	strFlags += "BS_RADIOBUTTON ";
else if ((nBtnStyle & 0xF) == BS_3STATE)              //0x00000005L
	strFlags += "BS_3STATE ";
else if ((nBtnStyle & 0xF) == BS_AUTO3STATE)          //0x00000006L
	strFlags += "BS_AUTO3STATE ";
else if ((nBtnStyle & 0xF) == BS_GROUPBOX)            //0x00000007L
	strFlags += "BS_GROUPBOX ";
else if ((nBtnStyle & 0xF) == BS_USERBUTTON)          //0x00000008L
	strFlags += "BS_USERBUTTON ";
else if ((nBtnStyle & 0xF) == BS_AUTORADIOBUTTON)     //0x00000009L
	strFlags += "BS_AUTORADIOBUTTON ";
else if ((nBtnStyle & 0xF) == BS_OWNERDRAW)           //0x0000000BL
	strFlags += "BS_OWNERDRAW ";
if (nBtnStyle & BS_LEFTTEXT)            //0x00000020L
	strFlags += "BS_LEFTTEXT ";

#if (WINVER >= 0x0400)
if (nBtnStyle == BS_TEXT)                //0x00000000L
	strFlags += "BS_TEXT ";
if (nBtnStyle & BS_ICON)                //0x00000040L
	strFlags += "BS_ICON ";
if (nBtnStyle & BS_BITMAP)              //0x00000080L
	strFlags += "BS_BITMAP ";

if ((nBtnStyle & BS_CENTER) == BS_CENTER)//0x00000300L
	strFlags += "BS_CENTER ";
else
  {
  if (nBtnStyle & BS_LEFT)                //0x00000100L
	  strFlags += "BS_LEFT ";
  if (nBtnStyle & BS_RIGHT)               //0x00000200L
	  strFlags += "BS_RIGHT ";
  }

if ((nBtnStyle & BS_VCENTER) == BS_VCENTER)//0x00000C00L
	strFlags += "BS_VCENTER ";
else
  {
  if (nBtnStyle & BS_TOP)                 //0x00000400L
	  strFlags += "BS_TOP ";
  if (nBtnStyle & BS_BOTTOM)              //0x00000800L
	  strFlags += "BS_BOTTOM ";
  }

if (nBtnStyle & BS_PUSHLIKE)            //0x00001000L
	strFlags += "BS_PUSHLIKE ";
if (nBtnStyle & BS_MULTILINE)           //0x00002000L
	strFlags += "BS_MULTILINE ";
if (nBtnStyle & BS_NOTIFY)              //0x00004000L
	strFlags += "BS_NOTIFY ";
if (nBtnStyle & BS_FLAT)                //0x00008000L
	strFlags += "BS_FLAT ";
if (nBtnStyle & BS_RIGHTBUTTON)         //BS_LEFTTEXT
	strFlags += "BS_RIGHTBUTTON ";
#endif

TRACE2("Button style %Xh:\n\t%s\n",nBtnStyle,strFlags);
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
