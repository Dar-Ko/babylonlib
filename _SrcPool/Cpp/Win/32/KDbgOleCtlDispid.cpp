/*$RCSfile: KDbgOleCtlDispid.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2008/07/24 19:05:40 $
  $Author: ddarko $

  Dumps the OLE Control Dispatch Event Ids.

  Note: Microsoft Windows specific (Win32).

  Copyright: babylonlib.sourceforge.net
  2008-07-24 Darko Kolakovic
 */

// Group=Diagnostic

#include "stdafx.h"
#include "OleCtl.h" //OLE Control Dispatch Events (Platform SDK header file)

#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
    #define TRACE2 ATLTRACE
  #endif
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

//-----------------------------------------------------------------------------
/*Dumps the OLE Control Dispatch Event Identifier.

  A COM object's methods and properties collectively make up its dispatch
  interface (or dispinterface). Each method and property is identified by a
  unique dispatch identifier (or DispID).
  Event dispatch ID is compiled into the component's type library and then
  used by the host application to bind to events.
  The DISPID for OLE Control events are defined in OleCtl.h.

  Note: Microsoft Windows specific (Win32);

  Returns: zero-terminated string describing IExplorer dispatch event.

  See also: ActiveX, Component Object Model (COM) interfaces. IDispatch::Invoke(),
  OleCtl.h
 */
LPCTSTR DumpOleCtlDispatchId(const DISPID nDispId //[in] dispatch event identifier
                            )
{
LPCTSTR szResult;
switch(nDispId)
  {
  case DISPID_AUTOSIZE                 : szResult = _T(" DISPID_AUTOSIZE(-500)")                 ; break;  //-500 = 4294966796 = 0xFFFFFE0C
  case DISPID_BACKCOLOR                : szResult = _T(" DISPID_BACKCOLOR(-501)")                ; break;  //-501 = 4294966795 = 0xFFFFFE0B
  case DISPID_BACKSTYLE                : szResult = _T(" DISPID_BACKSTYLE(-502)")                ; break;  //-502 = 4294966794 = 0xFFFFFE0A
  case DISPID_BORDERCOLOR              : szResult = _T(" DISPID_BORDERCOLOR(-503)")              ; break;  //-503 = 4294966793 = 0xFFFFFE09
  case DISPID_BORDERSTYLE              : szResult = _T(" DISPID_BORDERSTYLE(-504)")              ; break;  //-504 = 4294966792 = 0xFFFFFE08
  case DISPID_BORDERWIDTH              : szResult = _T(" DISPID_BORDERWIDTH(-505)")              ; break;  //-505 = 4294966791 = 0xFFFFFE07

  case DISPID_DRAWMODE                 : szResult = _T(" DISPID_DRAWMODE(-507)")                 ; break;  //-507 = 4294966789 = 0xFFFFFE05
  case DISPID_DRAWSTYLE                : szResult = _T(" DISPID_DRAWSTYLE(-508)")                ; break;  //-508 = 4294966788 = 0xFFFFFE04
  case DISPID_DRAWWIDTH                : szResult = _T(" DISPID_DRAWWIDTH(-509)")                ; break;  //-509 = 4294966797 = 0xFFFFFE03
  case DISPID_FILLCOLOR                : szResult = _T(" DISPID_FILLCOLOR(-510)")                ; break;  //-510 = 4294966786 = 0xFFFFFE02
  case DISPID_FILLSTYLE                : szResult = _T(" DISPID_FILLSTYLE(-511)")                ; break;  //-511 = 4294966785 = 0xFFFFFE01
  case DISPID_FONT                     : szResult = _T(" DISPID_FONT(-512)")                     ; break;  //-512 = 4294966784 = 0xFFFFFE00
  case DISPID_FORECOLOR                : szResult = _T(" DISPID_FORECOLOR(-513)")                ; break;  //-513 = 4294966783 = 0xFFFFFDFF
  case DISPID_ENABLED                  : szResult = _T(" DISPID_ENABLED(-514)")                  ; break;  //-514 = 4294966782 = 0xFFFFFDFE
  case DISPID_HWND                     : szResult = _T(" DISPID_HWND(-515)")                     ; break;  //-515 = 4294966781 = 0xFFFFFDFD
  case DISPID_TABSTOP                  : szResult = _T(" DISPID_TABSTOP(-516)")                  ; break;  //-516 = 4294966780 = 0xFFFFFDFC
  case DISPID_TEXT                     : szResult = _T(" DISPID_TEXT(-517)")                     ; break;  //-517 = 4294966779 = 0xFFFFFDFB
  case DISPID_CAPTION                  : szResult = _T(" DISPID_CAPTION(-518)")                  ; break;  //-518 = 4294966778 = 0xFFFFFDFA
  case DISPID_BORDERVISIBLE            : szResult = _T(" DISPID_BORDERVISIBLE(-519)")            ; break;  //-519 = 4294966777 = 0xFFFFFDF9
  case DISPID_APPEARANCE               : szResult = _T(" DISPID_APPEARANCE(-520)")               ; break;  //-520 = 4294966776 = 0xFFFFFDF8
  case DISPID_MOUSEPOINTER             : szResult = _T(" DISPID_MOUSEPOINTER(-521)")             ; break;  //-521 = 4294966775 = 0xFFFFFDF7
  case DISPID_MOUSEICON                : szResult = _T(" DISPID_MOUSEICON(-522)")                ; break;  //-522 = 4294966774 = 0xFFFFFDF6
  case DISPID_PICTURE                  : szResult = _T(" DISPID_PICTURE(-523)")                  ; break;  //-523 = 4294966773 = 0xFFFFFDF5
  case DISPID_VALID                    : szResult = _T(" DISPID_VALID(-524)")                    ; break;  //-524 = 4294966772 = 0xFFFFFDF4
  case DISPID_READYSTATE               : szResult = _T(" DISPID_READYSTATE(-525)")               ; break;  //-525 = 4294966771 = 0xFFFFFDF3
  case DISPID_LISTINDEX                : szResult = _T(" DISPID_LISTINDEX(-526)")                ; break;  //-526 = 4294966770 = 0xFFFFFDF2
  case DISPID_SELECTED                 : szResult = _T(" DISPID_SELECTED(-527)")                 ; break;  //-527 = 4294966769 = 0xFFFFFDF1
  case DISPID_LIST                     : szResult = _T(" DISPID_LIST(-528)")                     ; break;  //-528 = 4294966768 = 0xFFFFFDF0
  case DISPID_COLUMN                   : szResult = _T(" DISPID_COLUMN(-529)")                   ; break;  //-529 = 4294966767 = 0xFFFFFDEF

  case DISPID_LISTCOUNT                : szResult = _T(" DISPID_LISTCOUNT(-531)")                ; break;  //-531 = 4294966765 = 0xFFFFFDED
  case DISPID_MULTISELECT              : szResult = _T(" DISPID_MULTISELECT(-532)")              ; break;  //-532 = 4294966764 = 0xFFFFFDEC
  case DISPID_MAXLENGTH                : szResult = _T(" DISPID_MAXLENGTH(-533)")                ; break;  //-533 = 4294966763 = 0xFFFFFDEB
  case DISPID_PASSWORDCHAR             : szResult = _T(" DISPID_PASSWORDCHAR(-534)")             ; break;  //-534 = 4294966762 = 0xFFFFFDEA
  case DISPID_SCROLLBARS               : szResult = _T(" DISPID_SCROLLBARS(-535)")               ; break;  //-535 = 4294966761 = 0xFFFFFDE9
  case DISPID_WORDWRAP                 : szResult = _T(" DISPID_WORDWRAP(-536)")                 ; break;  //-536 = 4294966760 = 0xFFFFFDE8
  case DISPID_MULTILINE                : szResult = _T(" DISPID_MULTILINE(-537)")                ; break;  //-537 = 4294966759 = 0xFFFFFDE7
  case DISPID_NUMBEROFROWS             : szResult = _T(" DISPID_NUMBEROFROWS(-538)")             ; break;  //-538 = 4294966758 = 0xFFFFFDE6
  case DISPID_NUMBEROFCOLUMNS          : szResult = _T(" DISPID_NUMBEROFCOLUMNS(-539)")          ; break;  //-539 = 4294966757 = 0xFFFFFDE5
  case DISPID_DISPLAYSTYLE             : szResult = _T(" DISPID_DISPLAYSTYLE(-540)")             ; break;  //-540 = 4294966756 = 0xFFFFFDE4
  case DISPID_GROUPNAME                : szResult = _T(" DISPID_GROUPNAME(-541)")                ; break;  //-541 = 4294966755 = 0xFFFFFDE3
  case DISPID_IMEMODE                  : szResult = _T(" DISPID_IMEMODE(-542)")                  ; break;  //-542 = 4294966754 = 0xFFFFFDE2
  case DISPID_ACCELERATOR              : szResult = _T(" DISPID_ACCELERATOR(-543)")              ; break;  //-543 = 4294966753 = 0xFFFFFDE1
  case DISPID_ENTERKEYBEHAVIOR         : szResult = _T(" DISPID_ENTERKEYBEHAVIOR(-544)")         ; break;  //-544 = 4294966752 = 0xFFFFFDE0
  case DISPID_TABKEYBEHAVIOR           : szResult = _T(" DISPID_TABKEYBEHAVIOR(-545)")           ; break;  //-545 = 4294966751 = 0xFFFFFDEF
  case DISPID_SELTEXT                  : szResult = _T(" DISPID_SELTEXT(-546)")                  ; break;  //-546 = 4294966750 = 0xFFFFFDDE
  case DISPID_SELSTART                 : szResult = _T(" DISPID_SELSTART(-547)")                 ; break;  //-547 = 4294966749 = 0xFFFFFDDD
  case DISPID_SELLENGTH                : szResult = _T(" DISPID_SELLENGTH(-548)")                ; break;  //-548 = 4294966748 = 0xFFFFFDDC

  case DISPID_REFRESH                  : szResult = _T(" DISPID_REFRESH(-550)")                  ; break;  //-550 = 4294966746 = 0xFFFFFDDA
  case DISPID_DOCLICK                  : szResult = _T(" DISPID_DOCLICK(-551)")                  ; break;  //-551 = 4294966745 = 0xFFFFFDD9
  case DISPID_ABOUTBOX                 : szResult = _T(" DISPID_ABOUTBOX(-552)")                 ; break;  //-552 = 4294966744 = 0xFFFFFDD8
  case DISPID_ADDITEM                  : szResult = _T(" DISPID_ADDITEM(-553)")                  ; break;  //-553 = 4294966743 = 0xFFFFFDD7
  case DISPID_CLEAR                    : szResult = _T(" DISPID_CLEAR(-554)")                    ; break;  //-554 = 4294966742 = 0xFFFFFDD6
  case DISPID_REMOVEITEM               : szResult = _T(" DISPID_REMOVEITEM(-555)")               ; break;  //-555 = 4294966741 = 0xFFFFFDD5

  case DISPID_CLICK                    : szResult = _T(" DISPID_CLICK(-600)")                    ; break;  //-600 = 4294966696 = 0xFFFFFDA8
  case DISPID_DBLCLICK                 : szResult = _T(" DISPID_DBLCLICK(-601)")                 ; break;  //-601 = 4294966695 = 0xFFFFFDA7
  case DISPID_KEYDOWN                  : szResult = _T(" DISPID_KEYDOWN(-602)")                  ; break;  //-602 = 4294966694 = 0xFFFFFDA6
  case DISPID_KEYPRESS                 : szResult = _T(" DISPID_KEYPRESS(-603)")                 ; break;  //-603 = 4294966693 = 0xFFFFFDA5
  case DISPID_KEYUP                    : szResult = _T(" DISPID_KEYUP(-604)")                    ; break;  //-604 = 4294966692 = 0xFFFFFDA4
  case DISPID_MOUSEDOWN                : szResult = _T(" DISPID_MOUSEDOWN(-605)")                ; break;  //-605 = 4294966691 = 0xFFFFFDA3
  case DISPID_MOUSEMOVE                : szResult = _T(" DISPID_MOUSEMOVE(-606)")                ; break;  //-606 = 4294966690 = 0xFFFFFDA2
  case DISPID_MOUSEUP                  : szResult = _T(" DISPID_MOUSEUP(-607)")                  ; break;  //-607 = 4294966689 = 0xFFFFFDA1
  case DISPID_ERROREVENT               : szResult = _T(" DISPID_ERROREVENT(-608)")               ; break;  //-608 = 4294966688 = 0xFFFFFDA0
  case DISPID_READYSTATECHANGE         : szResult = _T(" DISPID_READYSTATECHANGE(-609)")         ; break;  //-609 = 4294966687 = 0xFFFFFD9F
  case DISPID_CLICK_VALUE              : szResult = _T(" DISPID_CLICK_VALUE(-610)")              ; break;  //-610 = 4294966686 = 0xFFFFFD9E
  case DISPID_RIGHTTOLEFT              : szResult = _T(" DISPID_RIGHTTOLEFT(-611)")              ; break;  //-611 = 4294966685 = 0xFFFFFD9D
  case DISPID_TOPTOBOTTOM              : szResult = _T(" DISPID_TOPTOBOTTOM(-612)")              ; break;  //-612 = 4294966684 = 0xFFFFFD9C
  case DISPID_THIS                     : szResult = _T(" DISPID_THIS-613)")                      ; break;  //-613 = 4294966683 = 0xFFFFFD9B

  case DISPID_AMBIENT_BACKCOLOR        : szResult = _T(" DISPID_AMBIENT_BACKCOLOR(-701)")        ; break;  //-701 = 4294966595 = 0xFFFFFD43
  case DISPID_AMBIENT_DISPLAYNAME      : szResult = _T(" DISPID_AMBIENT_DISPLAYNAME(-702)")      ; break;  //-702 = 4294966594 = 0xFFFFFD42
  case DISPID_AMBIENT_FONT             : szResult = _T(" DISPID_AMBIENT_FONT(-703)")             ; break;  //-703 = 4294966593 = 0xFFFFFD41
  case DISPID_AMBIENT_FORECOLOR        : szResult = _T(" DISPID_AMBIENT_FORECOLOR(-704)")        ; break;  //-704 = 4294966592 = 0xFFFFFD40
  case DISPID_AMBIENT_LOCALEID         : szResult = _T(" DISPID_AMBIENT_LOCALEID (-705)")        ; break;  //-705 = 4294966591 = 0xFFFFFD3F
  case DISPID_AMBIENT_MESSAGEREFLECT   : szResult = _T(" DISPID_AMBIENT_MESSAGEREFLECT(-706)")   ; break;  //-706 = 4294966590 = 0xFFFFFD3E
  case DISPID_AMBIENT_SCALEUNITS       : szResult = _T(" DISPID_AMBIENT_SCALEUNITS(-707)")       ; break;  //-707 = 4294966589 = 0xFFFFFD3D
  case DISPID_AMBIENT_TEXTALIGN        : szResult = _T(" DISPID_AMBIENT_TEXTALIGN(-708)")        ; break;  //-708 = 4294966588 = 0xFFFFFD3C
  case DISPID_AMBIENT_USERMODE         : szResult = _T(" DISPID_AMBIENT_USERMODE(-709)")         ; break;  //-709 = 4294966587 = 0xFFFFFD3B
  case DISPID_AMBIENT_UIDEAD           : szResult = _T(" DISPID_AMBIENT_UIDEAD(-710)")           ; break;  //-710 = 4294966586 = 0xFFFFFD3A
  case DISPID_AMBIENT_SHOWGRABHANDLES  : szResult = _T(" DISPID_AMBIENT_SHOWGRABHANDLES(-711)")  ; break;  //-711 = 4294966585 = 0xFFFFFD39
  case DISPID_AMBIENT_SHOWHATCHING     : szResult = _T(" DISPID_AMBIENT_SHOWHATCHING(-712)")     ; break;  //-712 = 4294966584 = 0xFFFFFD38
  case DISPID_AMBIENT_DISPLAYASDEFAULT : szResult = _T(" DISPID_AMBIENT_DISPLAYASDEFAULT(-713)") ; break;  //-713 = 4294966583 = 0xFFFFFD37
  case DISPID_AMBIENT_SUPPORTSMNEMONICS: szResult = _T(" DISPID_AMBIENT_SUPPORTSMNEMONICS(-714)"); break;  //-714 = 4294966582 = 0xFFFFFD36
  case DISPID_AMBIENT_AUTOCLIP         : szResult = _T(" DISPID_AMBIENT_AUTOCLIP(-715)")         ; break;  //-715 = 4294966581 = 0xFFFFFD35
  case DISPID_AMBIENT_APPEARANCE       : szResult = _T(" DISPID_AMBIENT_APPEARANCE(-716)")       ; break;  //-716 = 4294966580 = 0xFFFFFD34

  case DISPID_AMBIENT_CODEPAGE         : szResult = _T(" DISPID_AMBIENT_CODEPAGE(-725)")         ; break;  //-725 = 4294966571 = 0xFFFFFD2B
  case DISPID_AMBIENT_PALETTE          : szResult = _T(" DISPID_AMBIENT_PALETTE(-726)")          ; break;  //-726 = 4294966570 = 0xFFFFFD2A
  case DISPID_AMBIENT_CHARSET          : szResult = _T(" DISPID_AMBIENT_CHARSET(-727)")          ; break;  //-727 = 4294966569 = 0xFFFFFD29
  case DISPID_AMBIENT_TRANSFERPRIORITY : szResult = _T(" DISPID_AMBIENT_TRANSFERPRIORITY(-728)") ; break;  //-728 = 4294966568 = 0xFFFFFD28

  case DISPID_AMBIENT_RIGHTTOLEFT      : szResult = _T(" DISPID_AMBIENT_RIGHTTOLEFT(-732)")      ; break;  //-732 = 4294966564 = 0xFFFFFD24
  case DISPID_AMBIENT_TOPTOBOTTOM      : szResult = _T(" DISPID_AMBIENT_TOPTOBOTTOM(-733)")      ; break;  //-733 = 4294966563 = 0xFFFFFD23

  case DISPID_Name                     : szResult = _T(" DISPID_Name(-800)")                     ; break;  //-800 = 4294966496 = 0xFFFFFCE0
  case DISPID_Delete                   : szResult = _T(" DISPID_Delete(-801)")                   ; break;  //-801 = 4294966495 = 0xFFFFFCDF
  case DISPID_Object                   : szResult = _T(" DISPID_Object(-802)")                   ; break;  //-802 = 4294966494 = 0xFFFFFCDE
  case DISPID_Parent                   : szResult = _T(" DISPID_Parent(-803)")                   ; break;  //-803 = 4294966493 = 0xFFFFFCDD

  default:
    {
    TRACE(_T(" Dispatch event (%u = %d) "), nDispId, nDispId);
    szResult = _T(" Unknown OLE Ctrl event");
    }
  }
return szResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG

/******************************************************************************
 * $Log: KDbgOleCtlDispid.cpp,v $
 * Revision 1.1  2008/07/24 19:05:40  ddarko
 * Created
 *
 ******************************************************************************/

/*Dispatch Ids for other interfaces:

// Dispatch ID constants for font and picture types

#define DISPID_FONT_NAME    0
#define DISPID_FONT_SIZE    2
#define DISPID_FONT_BOLD    3
#define DISPID_FONT_ITALIC  4
#define DISPID_FONT_UNDER   5
#define DISPID_FONT_STRIKE  6
#define DISPID_FONT_WEIGHT  7
#define DISPID_FONT_CHARSET 8
#define DISPID_FONT_CHANGED 9

#define DISPID_PICT_HANDLE  0
#define DISPID_PICT_HPAL    2
#define DISPID_PICT_TYPE    3
#define DISPID_PICT_WIDTH   4
#define DISPID_PICT_HEIGHT  5
#define DISPID_PICT_RENDER  6

*/
