/*$RCSfile: KDbgMsHtmlDispid.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2008/07/25 16:11:08 $
  $Author: ddarko $

  Dumps the Microsoft Web Browser Control Dispatch Event Ids.

  Note: Microsoft Windows specific (Win32).

  Copyright: babylonlib.sourceforge.net
  2008-07-24 Darko Kolakovic
 */

// Group=Diagnostic

#include "stdafx.h"
#include "MsHtmdid.h" //Microsoft Web Browser Control Dispatch Events
                      //(Platform SDK header file)

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

//-----------------------------------------------------------------------------
/*Dumps the Microsoft Web Browser Control Dispatch Event Identifier.
  Ids used by controls are from the range
  [DISPID_XOBJ_MIN = 0x80010000, DISPID_XOBJ_MAX = 0x8001FFFF].

  A COM object's methods and properties collectively make up its dispatch
  interface (or dispinterface). Each method and property is identified by a
  unique dispatch identifier (or DispID).
  Event dispatch ID is compiled into the component's type library and then
  used by the host application to bind to events.
  The DISPID for OLE Control events are defined in OleCtl.h.

  Note: Microsoft Windows specific (Win32);

  Returns: zero-terminated string describing IExplorer dispatch event.

  See also: ActiveX, Component Object Model (COM) interfaces. IDispatch::Invoke(),
  MsHtmdid.h
 */
LPCTSTR DumpMsHtmlDispatchId(const DISPID nDispId //[in] dispatch event identifier
                            )
{
LPCTSTR szResult;

switch(nDispId)
  {
  //Semi-standard x-object properties. These are events that are fired for all sites
  case STDDISPID_XOBJ_ONBLUR           : szResult = _T(" STDDISPID_XOBJ_ONBLUR(0x80010000)")             ; break;  //(DISPID_XOBJ_BASE = DISPID_XOBJ_MIN)
  case STDDISPID_XOBJ_ONFOCUS          : szResult = _T(" STDDISPID_XOBJ_ONFOCUS((0x80010001)")           ; break;  //(DISPID_XOBJ_BASE +  1)
  case STDDISPID_XOBJ_BEFOREUPDATE     : szResult = _T(" STDDISPID_XOBJ_BEFOREUPDATE(0x80010004)")       ; break;  //(DISPID_XOBJ_BASE +  4)
  case STDDISPID_XOBJ_AFTERUPDATE      : szResult = _T(" STDDISPID_XOBJ_AFTERUPDATE(0x80010005)")        ; break;  //(DISPID_XOBJ_BASE +  5)
  case STDDISPID_XOBJ_ONROWEXIT        : szResult = _T(" STDDISPID_XOBJ_ONROWEXIT(0x80010006)")          ; break;  //(DISPID_XOBJ_BASE +  6)
  case STDDISPID_XOBJ_ONROWENTER       : szResult = _T(" STDDISPID_XOBJ_ONROWENTER(0x80010007)")         ; break;  //(DISPID_XOBJ_BASE +  7)
  case STDDISPID_XOBJ_ONMOUSEOVER      : szResult = _T(" STDDISPID_XOBJ_ONMOUSEOVER(0x80010008)")        ; break;  //(DISPID_XOBJ_BASE +  8)
  case STDDISPID_XOBJ_ONMOUSEOUT       : szResult = _T(" STDDISPID_XOBJ_ONMOUSEOUT(0x80010009)")         ; break;  //(DISPID_XOBJ_BASE +  9)
  case STDDISPID_XOBJ_ONHELP           : szResult = _T(" STDDISPID_XOBJ_ONHELP(0x8001000A)")             ; break;  //(DISPID_XOBJ_BASE + 10)
  case STDDISPID_XOBJ_ONDRAGSTART      : szResult = _T(" STDDISPID_XOBJ_ONDRAGSTART(0x8001000B)")        ; break;  //(DISPID_XOBJ_BASE + 11)
  case STDDISPID_XOBJ_ONSELECTSTART    : szResult = _T(" STDDISPID_XOBJ_ONSELECTSTART(0x8001000C)")      ; break;  //(DISPID_XOBJ_BASE + 12)
  case STDDISPID_XOBJ_ERRORUPDATE      : szResult = _T(" STDDISPID_XOBJ_ERRORUPDATE(0x8001000D)")        ; break;  //(DISPID_XOBJ_BASE + 13)
  case STDDISPID_XOBJ_ONDATASETCHANGED : szResult = _T(" STDDISPID_XOBJ_ONDATASETCHANGED(0x8001000E)")   ; break;  //(DISPID_XOBJ_BASE + 14)
  case STDDISPID_XOBJ_ONDATAAVAILABLE  : szResult = _T(" STDDISPID_XOBJ_ONDATAAVAILABLE(0x8001000F)")    ; break;  //(DISPID_XOBJ_BASE + 15)
  case STDDISPID_XOBJ_ONDATASETCOMPLETE: szResult = _T(" STDDISPID_XOBJ_ONDATASETCOMPLETE(0x80010010)")  ; break;  //(DISPID_XOBJ_BASE + 16)
  case STDDISPID_XOBJ_ONFILTER         : szResult = _T(" STDDISPID_XOBJ_ONFILTER(0x80010011)")           ; break;  //(DISPID_XOBJ_BASE + 17)
  case STDDISPID_XOBJ_ONLOSECAPTURE    : szResult = _T(" STDDISPID_XOBJ_ONLOSECAPTURE(0x80010012)")      ; break;  //(DISPID_XOBJ_BASE + 18)
  case STDDISPID_XOBJ_ONPROPERTYCHANGE : szResult = _T(" STDDISPID_XOBJ_ONPROPERTYCHANGE(0x80010013)")   ; break;  //(DISPID_XOBJ_BASE + 19)
  case STDDISPID_XOBJ_ONDRAG           : szResult = _T(" STDDISPID_XOBJ_ONDRAG(0x80010014)")             ; break;  //(DISPID_XOBJ_BASE + 20)
  case STDDISPID_XOBJ_ONDRAGEND        : szResult = _T(" STDDISPID_XOBJ_ONDRAGEND(0x80010015)")          ; break;  //(DISPID_XOBJ_BASE + 21)
  case STDDISPID_XOBJ_ONDRAGENTER      : szResult = _T(" STDDISPID_XOBJ_ONDRAGENTER(0x80010016)")        ; break;  //(DISPID_XOBJ_BASE + 22)
  case STDDISPID_XOBJ_ONDRAGOVER       : szResult = _T(" STDDISPID_XOBJ_ONDRAGOVER(0x80010017)")         ; break;  //(DISPID_XOBJ_BASE + 23)
  case STDDISPID_XOBJ_ONDRAGLEAVE      : szResult = _T(" STDDISPID_XOBJ_ONDRAGLEAVE(0x80010018)")        ; break;  //(DISPID_XOBJ_BASE + 24)
  case STDDISPID_XOBJ_ONDROP           : szResult = _T(" STDDISPID_XOBJ_ONDROP(0x80010019)")             ; break;  //(DISPID_XOBJ_BASE + 25)
  case STDDISPID_XOBJ_ONCUT            : szResult = _T(" STDDISPID_XOBJ_ONCUT(0x8001001A)")              ; break;  //(DISPID_XOBJ_BASE + 26)
  case STDDISPID_XOBJ_ONCOPY           : szResult = _T(" STDDISPID_XOBJ_ONCOPY(0x8001001B)")             ; break;  //(DISPID_XOBJ_BASE + 27)
  case STDDISPID_XOBJ_ONPASTE          : szResult = _T(" STDDISPID_XOBJ_ONPASTE(0x8001001C)")            ; break;  //(DISPID_XOBJ_BASE + 28)
  case STDDISPID_XOBJ_ONBEFORECUT      : szResult = _T(" STDDISPID_XOBJ_ONBEFORECUT(0x8001001D)")        ; break;  //(DISPID_XOBJ_BASE + 29)
  case STDDISPID_XOBJ_ONBEFORECOPY     : szResult = _T(" STDDISPID_XOBJ_ONBEFORECOPY(0x8001001E)")       ; break;  //(DISPID_XOBJ_BASE + 30)
  case STDDISPID_XOBJ_ONBEFOREPASTE    : szResult = _T(" STDDISPID_XOBJ_ONBEFOREPASTE(0x8001001F)")      ; break;  //(DISPID_XOBJ_BASE + 31)
  case STDDISPID_XOBJ_ONROWSDELETE     : szResult = _T(" STDDISPID_XOBJ_ONROWSDELETE(0x80010020)")       ; break;  //(DISPID_XOBJ_BASE + 32)
  case STDDISPID_XOBJ_ONROWSINSERTED   : szResult = _T(" STDDISPID_XOBJ_ONROWSINSERTED(0x80010021)")     ; break;  //(DISPID_XOBJ_BASE + 33)
  case STDDISPID_XOBJ_ONCELLCHANGE     : szResult = _T(" STDDISPID_XOBJ_ONCELLCHANGE(0x80010022)")       ; break;  //(DISPID_XOBJ_BASE + 34)

  default:
    {
    const int LEN_DISPID = 8; //length of hexadecimal presentation of
                              //32-bit dispatch event identifier
    const int SIZE_MSHTMDISPID = 39; //size including terminating zero
    static TCHAR szDumpDispId[SIZE_MSHTMDISPID];

    if ((nDispId >= DISPID_XOBJ_MIN) && (nDispId <= DISPID_XOBJ_MAX))
      {
      const int POSITION_MSHTMDISPID = 29;
      //Note: number of copied characters could be reduced for LEN_DISPID. It is
      //not big issue as it is now.
      _tcsncpy(szDumpDispId, _T(" MS Web Browser Ctrl event(0x80010000)"), SIZE_MSHTMDISPID);
      //Hexadecimal presentation of dispatch event identifier
      _itoa((int)nDispId, &szDumpDispId[POSITION_MSHTMDISPID], 16);
      szDumpDispId[POSITION_MSHTMDISPID + LEN_DISPID] = _T(')');
      }
    else
      {
      const int SIZE_DEFDISPID = 28; //size including terminating zero
      const int POSITION_DEFDISPID = 18;
      ASSERT(SIZE_DEFDISPID <= sizeof(szDumpDispId)/sizeof(TCHAR));
      _tcsncpy(szDumpDispId, _T(" Dispatch event(0x80010000)"), SIZE_DEFDISPID);
      _itoa((int)nDispId, &szDumpDispId[POSITION_DEFDISPID], 16);
      szDumpDispId[POSITION_DEFDISPID + LEN_DISPID] = _T(')');
      }
    szResult = szDumpDispId;
    }
  }
return szResult;
}

///////////////////////////////////////////////////////////////////////////////
#else
  #define DumpMsHtmlDispatchId(x)
#endif //_DEBUG

/******************************************************************************
 * $Log: KDbgMsHtmlDispid.cpp,v $
 * Revision 1.1  2008/07/25 16:11:08  ddarko
 * Created
 *
  ******************************************************************************/
