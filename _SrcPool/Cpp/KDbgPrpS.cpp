/*$Workfile: KDbgPrpS.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:35:50 $
  $Author: ddarko $

  Dumps property sheet header
  Copyright: CommonSoft Inc.
  Apr 2000 Darko Kolakovic
 */

#include "StdAfx.h"
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

#define _INCLUDE_KGETSHEL_CPP_
#include "KGetShel.cpp"  //GetShellVersion()
#include "KDbgMacr.h"    //Dump predefined macros

#if _MFC_VER >= 0x600
    //Name has been changed; See AfxDlgs.h(487) D.K.
  #define _KDBGPROPSHEETHEADER AFX_OLDPROPSHEETHEADER
#else
  #pragma message ("MFC 4.2")
  #define _KDBGPROPSHEETHEADER PROPSHEETHEADER
#endif
///////////////////////////////////////////////////////////////////////////////


//operator<<()----------------------------------------------------------------
/*Outputs the PROPSHEETHEADER structure to the dump context.
  In case of failure throws CFileException;

      typedef struct _PROPSHEETHEADER
        {
        DWORD dwSize;         //Size, in bytes, of this structure
        DWORD dwFlags;        //options used when creating the property sheet page
        HWND  hwndParent;     //property sheet's owner window
        HINSTANCE hInstance;  //instance from which to load the icon or title string resource
        union
          {
          HICON hIcon;        //the small icon in the title bar of the property sheet dialog
          LPCTSTR pszIcon;
          };
        LPCTSTR pszCaption;   //title of the property sheet dialog box
        UINT nPages;          //number of pages
        union
          {
          UINT nStartPage;    //index of the initial page
          LPCTSTR pStartPage; //name of the initial page
          };
        union
          {
          LPCPROPSHEETPAGE ppsp;       //an array of PROPSHEETPAGE structures
          HPROPSHEETPAGE FAR *phpage;  //an array of handles to the property sheet pages
          };
        PFNPROPSHEETCALLBACK pfnCallback; //an application-defined callback function that is called when the property sheet is initialized

        } PROPSHEETHEADER;

        //Following are additional members of CPropertySheetEx
        #if (_WIN32_IE >= 0x0500)
          union
            {
            HBITMAP hbmWatermark;  //handle to the watermark bitmap
            LPCTSTR pszbmWatermark;
            };
          HPALETTE hplWatermark;  //HPALETTE structure used for drawing the watermark bitmap
          union
            {
            HBITMAP hbmHeader;    //handle to the header bitmap
            LPCSTR pszbmHeader;
            };
        #endif

  See Also: \include\PrSht.h Interface for the Windows Property Sheet Pages

  Note: uses Microsoft Fundation Library (MFC).
  Note: Microsoft Windows specific (Win).

  Bug fix: PropertySheet Fails When Changing from VC++ 5.0 to VC++ 6.0 ID: Q197631
  PROPSHEETHEADER and PROPSHEETPAGE structures depending on what the _WIN32_IE
  preprocessor directive is defined as. If _WIN32_IE is not defined, it is defined
  as 0x0400 by default. Having _WIN32_IE defined as 0x0400 causes the new members
  of the PROPSHEETHEADER and PROPSHEETPAGE structures to be included.
  PropertySheet API will fail on systems that have the original Comctl32.dll file.
  These systems include Windows 95 and Windows NT 4.0 with no Internet Explorer or
  Internet Explorer version 3.0x installed.
  Solution is to add the following directive in the Preprocessor Definitions edit
  box: _WIN32_IE=0x0200. Setting the _WIN32_IE value in an MFC project prevents
  the project from building becouse MFC handles this problem correctly.
  
  Group=Diagnostic  
*/
CDumpContext& AFXAPI operator <<(CDumpContext& dc,_KDBGPROPSHEETHEADER const& pshSrc)
{
DWORD dwVer = GetShellVersion(_T("comctl32.dll"));
dc << _T("PROPSHEETHEADER @ ") << &pshSrc
   << _T("\n\t{\n\tdwSize = ") << pshSrc.dwSize << _T(" as in ComCtl32.dll ver. ");
if ((pshSrc.dwSize == PROPSHEETHEADER_V1_SIZE) || (dwVer == 0))
  dc <<  _T("less than 4.71");
else
  dc << LOWORD(dwVer) << _T(".") << HIWORD(dwVer);

dc << _T("\n\tdwFlags = ") << pshSrc.dwFlags << _T("\n\t\t");


if ((pshSrc.dwFlags & PSH_DEFAULT )          == PSH_DEFAULT)
  dc << _T("PSH_DEFAULT ");
if ((pshSrc.dwFlags & PSH_HASHELP )          == PSH_HASHELP)
  dc << _T("PSH_HASHELP ");
if ((pshSrc.dwFlags & PSH_HEADER )           == PSH_HEADER )
  dc << _T("PSH_HEADER ");
if ((pshSrc.dwFlags & PSH_MODELESS  )        == PSH_MODELESS )
  dc << _T("PSH_MODELESS ");
if ((pshSrc.dwFlags & PSH_NOAPPLYNOW )       == PSH_NOAPPLYNOW )
  dc << _T("PSH_NOAPPLYNOW ");

#if (_WIN32_IE >= 0x0500)
  if ((pshSrc.dwFlags & PSH_NOCONTEXTHELP )    == PSH_NOCONTEXTHELP )
    dc << _T("PSH_NOCONTEXTHELP ");
#endif

if ((pshSrc.dwFlags & PSH_PROPSHEETPAGE )    == PSH_PROPSHEETPAGE )
  dc << _T("PSH_PROPSHEETPAGE ");
if ((pshSrc.dwFlags & PSH_PROPTITLE )        == PSH_PROPTITLE )
  dc << _T("PSH_PROPTITLE ");
if ((pshSrc.dwFlags & PSH_RTLREADING )       == PSH_RTLREADING )
  dc << _T("PSH_RTLREADING ");
if ((pshSrc.dwFlags & PSH_STRETCHWATERMARK ) == PSH_STRETCHWATERMARK )
  dc << _T("PSH_STRETCHWATERMARK ");
if ((pshSrc.dwFlags & PSH_USECALLBACK )      == PSH_USECALLBACK )
  dc << _T("PSH_USECALLBACK ");
if ((pshSrc.dwFlags & PSH_USEHBMHEADER )     == PSH_USEHBMHEADER )
  dc << _T("PSH_USEHBMHEADER ");
if ((pshSrc.dwFlags & PSH_USEHBMWATERMARK )  == PSH_USEHBMWATERMARK )
  dc << _T("PSH_USEHBMWATERMARK ");
if ((pshSrc.dwFlags & PSH_USEHICON )         == PSH_USEHICON )
  dc << _T("PSH_USEHICON ");
if ((pshSrc.dwFlags & PSH_USEHPLWATERMARK )  == PSH_USEHPLWATERMARK )
  dc << _T("PSH_USEHPLWATERMARK ");
if ((pshSrc.dwFlags & PSH_USEICONID )        == PSH_USEICONID )
  dc << _T("PSH_USEICONID ");
if ((pshSrc.dwFlags & PSH_USEPAGELANG )      == PSH_USEPAGELANG )
  dc << _T("PSH_USEPAGELANG ");
if ((pshSrc.dwFlags & PSH_USEPSTARTPAGE )    == PSH_USEPSTARTPAGE )
  dc << _T("PSH_USEPSTARTPAGE ");
if ((pshSrc.dwFlags & PSH_WATERMARK )        == PSH_WATERMARK )
  dc << _T("PSH_WATERMARK ");
if ((pshSrc.dwFlags & PSH_WIZARD )           == PSH_WIZARD )
  dc << _T("PSH_WIZARD ");
if ((pshSrc.dwFlags & PSH_WIZARD97 )         == PSH_WIZARD97 )
  dc << _T("PSH_WIZARD97 ");
if ((pshSrc.dwFlags & PSH_WIZARDCONTEXTHELP )== PSH_WIZARDCONTEXTHELP )
  dc << _T("PSH_WIZARDCONTEXTHELP ");
if ((pshSrc.dwFlags & PSH_WIZARDHASFINISH )  == PSH_WIZARDHASFINISH )
  dc << _T("PSH_WIZARDHASFINISH ");

#if (_WIN32_IE >= 0x0500)
  if ((pshSrc.dwFlags & PSH_WIZARD_LITE )      == PSH_WIZARD_LITE )
    dc << _T("PSH_WIZARD_LITE ");
#endif


dc << _T("\n\thwndParent = ") << pshSrc.hwndParent
   << _T("\n\thInstance = ") << pshSrc.hInstance;

if ((pshSrc.dwFlags & PSH_USEHICON ) == PSH_USEHICON)
  {
  dc << _T("\n\thIcon = ") << (void*)pshSrc.hIcon
     << _T("\n\tpszIcon = ") << pshSrc.pszIcon;
  }
else
  {
  dc << _T("\n\thIcon = ") << _T("ignored")
     << _T("\n\tpszIcon = ") << _T("ignored");
  }

dc << _T("\n\tpszCaption = ");

if ( ((pshSrc.dwFlags & PSH_WIZARD )    == PSH_WIZARD ) ||
     ((pshSrc.dwFlags & PSH_WIZARD97 )  == PSH_WIZARD97)
     #if (_WIN32_IE >= 0x0500)
       || ((pshSrc.dwFlags & PSH_WIZARD_LITE)== PSH_WIZARD_LITE)
     #endif
      )
  dc << _T("ignored");
else if ((pshSrc.dwFlags & PSH_PROPTITLE ) == PSH_PROPTITLE )
  dc << _T("Properties for ") << pshSrc.pszCaption;
else
  dc << pshSrc.pszCaption;

dc << _T("\n\tnPages = ") << pshSrc.nPages
   << _T("\n\tnStartPage  = ") << pshSrc.nStartPage
   << _T("\n\tpStartPage  = ") << pshSrc.pStartPage ;
if ((pshSrc.dwFlags & PSH_PROPSHEETPAGE ) == PSH_PROPSHEETPAGE)
  dc << _T("\n\tppsp = ") << (void*)pshSrc.ppsp;
else
  dc << _T("\n\tppsp = ") << _T("ignored");

dc << _T("\n\tphpage  = ") << pshSrc.phpage; //Should be NULL if ~PSH_PROPSHEETPAGE
if ((pshSrc.dwFlags & PSH_USECALLBACK ) == PSH_USECALLBACK )
  dc << _T("\n\tpfnCallback  = ") << (void*)pshSrc.pfnCallback;
else
  dc << _T("\n\tpfnCallback  = ") << _T("ignored");

dc << _T("\n\t}\n");


return dc;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         17/08/2001 12:37:26 AMDarko           Update
 *  3    Biblioteka1.2         08/07/2001 12:10:23 AMDarko           $Revision: 1.3 $
 *       inserted
 *  2    Biblioteka1.1         08/06/2001 11:50:07 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:56:00 PMDarko
 * $
 *****************************************************************************/
