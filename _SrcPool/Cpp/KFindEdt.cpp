/*$Workfile: KFindEdt.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $
 
  Find child Edit control
  Copyright: CommonSoft Inc.
  Darko Kolakovic Dec '97
 */
 
#include "StdAfx.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

static BOOL CALLBACK EnumEditCtrl(HWND hWnd, LPARAM lResult);

//GetEditControl()-------------------------------------------------------------
/*Enumerator function for child edit controls.
  Returns: handle of the first child edit control, or NULL if givn window has not
  any edit controls.

  Note: Microsoft Windows specific (Win).
 */
HWND GetEditControl(HWND hParent //handle of  parent window
                   )
{
TRACE1("GetEditControl(parent = %x)\n",hParent);

HWND hwndEdit = NULL;
EnumChildWindows(hParent, EnumEditCtrl, (LPARAM)&hwndEdit);
return hwndEdit; 
}

//EnumEditCtrl()---------------------------------------------------------------
/*Callback function of the WNDENUMPROC type used with the EnumChildWindows.
  This function searches for the child edit control. 
  Returns: TRUE to continue enumeration; to abort enumeration, function will return
  FALSE.

  Note: Microsoft Windows specific (Win). 
 */
static BOOL CALLBACK EnumEditCtrl(HWND hWnd, //handle to a child window of 
                                             //the parent window specified in 
                                             //EnumChildWindows. 
                                  LPARAM lResult //application-defined value 
                                                 //given in EnumChildWindows
                                  )
{
HWND* phwndResult = (HWND*)lResult;

TCHAR szTemp[MAX_PATH] ;

// Get the class name of this child window.
if (GetClassName(hWnd, szTemp, MAX_PATH )!= 0 )
{
    // Is it an edit control?
if (_tcscmp(szTemp, _T("Edit")) == 0)
  {
  *phwndResult = hWnd ;
  return FALSE; //A child window is an edit control
  }
}

return TRUE; //Proceed
}
