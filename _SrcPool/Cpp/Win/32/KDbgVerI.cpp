/*$Workfile: KDbgVerI.cpp$: implementation file
  $Revision: 6$ $Date: 2004-10-01 21:34:36$
  $Author: Darko$

  Dumps fixed file information from version resource
  Copyright: CommonSoft Inc.
  Jan 2000 Darko Kolakovic
 */

#include "stdafx.h"
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

///////////////////////////////////////////////////////////////////////////////


//operator<<()----------------------------------------------------------------
/*Outputs the VS_FIXEDFILEINFO data to the dump context.
  In case of failure throws CFileException;

    struct VS_FIXEDFILEINFO
      {
      DWORD dwSignature;        //contains the value 0xFEEFO4BD
      DWORD dwStrucVersion;     //the version number of this structure (high-order word
                                // is major number, low-order word is minor number)
      DWORD dwFileVersionMS;    //the most significant 32 bits of the file's version number
      DWORD dwFileVersionLS;    //the least significant 32 bits of the file's version number
      DWORD dwProductVersionMS; //the most significant 32 bits of the version number of
                                //the product with which this file was distributed.
      DWORD dwProductVersionLS; //the least significant 32 bits of the version number of
                                //the product with which this file was distributed.
      DWORD dwFileFlagsMask;    //a bitmask that specifies the valid bits in dwFileFlags
      DWORD dwFileFlags;        //a bitmask that specifies the Boolean attributes of the file
      DWORD dwFileOS;           //the operating system for which this file was designed
      DWORD dwFileType;         //specifies the general type of file.
      DWORD dwFileSubtype;      //Specifies the function of the file
      DWORD dwFileDateMS;       //the most significant 32 bits of the file's 64-bit
                                //creation date and time stamp
      DWORD dwFileDateLS;       //the least significant 32 bits of the file's 64-bit
                                //creation date and time stamp
      };
      
  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win).

Group=Diagnostic 
*/
CDumpContext& AFXAPI operator <<(CDumpContext& dc,VS_FIXEDFILEINFO const& vffiSrc)
{
DWORD dwTemp = vffiSrc.dwFileFlagsMask&vffiSrc.dwFileFlags;

dc << _T("VS_FIXEDFILEINFO\n\t{")
   << _T("\n\tdwSignature        = ") << vffiSrc.dwSignature
   << _T("\n\tdwStrucVersion     = ") << HIWORD(vffiSrc.dwStrucVersion)
   << _T(".")                         << LOWORD(vffiSrc.dwStrucVersion)
   << _T("\n\tdwFileVersionMS    = ") << vffiSrc.dwFileVersionMS
   << _T("\n\tdwFileVersionLS    = ") << vffiSrc.dwFileVersionLS
   << _T("\n\tdwProductVersionMS = ") << vffiSrc.dwProductVersionMS
   << _T("\n\tdwProductVersionLS = ") << vffiSrc.dwProductVersionLS
   << _T("\n\tdwFileFlagsMask    = ") << vffiSrc.dwFileFlagsMask
   << _T("\n\tdwFileFlags        = ") << vffiSrc.dwFileFlags
   << _T("\n\tvalid flags        = ") << dwTemp
   << _T(":");
if ((dwTemp & VS_FF_DEBUG) == VS_FF_DEBUG)
  dc  << _T(" VS_FF_DEBUG");
if ((dwTemp & VS_FF_INFOINFERRED) == VS_FF_INFOINFERRED)
  dc  << _T(" VS_FF_INFOINFERRED");
if ((dwTemp & VS_FF_PATCHED) == VS_FF_PATCHED)
  dc  << _T(" VS_FF_PATCHED");
if ((dwTemp & VS_FF_PRERELEASE) == VS_FF_PRERELEASE)
  dc  << _T(" VS_FF_PRERELEASE");
if ((dwTemp & VS_FF_PRIVATEBUILD) == VS_FF_PRIVATEBUILD)
  dc  << _T(" VS_FF_PRIVATEBUILD");
if ((dwTemp & VS_FF_SPECIALBUILD) == VS_FF_SPECIALBUILD)
  dc  << _T(" VS_FF_SPECIALBUILD");

dc << _T("\n\tdwFileOS           = ") << vffiSrc.dwFileOS
   << _T(":");
if (vffiSrc.dwFileOS == VOS_UNKNOWN)
  dc  << _T(" VOS_UNKNOWN");
else
  {
  if ((vffiSrc.dwFileOS & VOS_DOS) == VOS_DOS)
    dc  << _T(" VOS_DOS");
  if ((vffiSrc.dwFileOS & VOS_NT) == VOS_NT)
    dc  << _T(" VOS_NT");
  if ((vffiSrc.dwFileOS & VOS__WINDOWS16) == VOS__WINDOWS16)
    dc  << _T(" VOS__WINDOWS16");
  if ((vffiSrc.dwFileOS & VOS__WINDOWS32) == VOS__WINDOWS32)
    dc  << _T(" VOS__WINDOWS32");
  if ((vffiSrc.dwFileOS & VOS_OS216) == VOS_OS216)
    dc  << _T(" VOS_OS216");
  if ((vffiSrc.dwFileOS & VOS_OS232) == VOS_OS232)
    dc  << _T(" VOS_OS232");
  if ((vffiSrc.dwFileOS & VOS__PM16) == VOS__PM16)
    dc  << _T(" VOS__PM16");
  if ((vffiSrc.dwFileOS & VOS__PM32) == VOS__PM32)
    dc  << _T(" VOS__PM32");
  }
dc << _T("\n\tdwFileType         = ") << vffiSrc.dwFileType
   << _T(":");
if (vffiSrc.dwFileType == VFT_UNKNOWN)
  dc  << _T(" VFT_UNKNOWN");
if (vffiSrc.dwFileType == VFT_APP)
  dc  << _T(" VFT_APP");
if (vffiSrc.dwFileType == VFT_DLL)
  dc  << _T(" VFT_DLL");
if (vffiSrc.dwFileType == VFT_DRV)
  dc  << _T(" VType_DType");
if (vffiSrc.dwFileType == VFT_FONT)
  dc  << _T(" VFT_FONT");
if (vffiSrc.dwFileType == VFT_VXD)
  dc  << _T(" VFT_VXD");
if (vffiSrc.dwFileType == VFT_STATIC_LIB)
  dc  << _T(" VFT_STATIC_LIB");

dc << _T("\n\tdwFileSubtype      = ") << vffiSrc.dwFileSubtype;
if (vffiSrc.dwFileType == VFT_DRV)
  {
  dc << _T(":");
  if (vffiSrc.dwFileSubtype == VFT2_UNKNOWN)
    dc  << _T(" VFT2_UNKNOWN");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_COMM)
    dc  << _T(" VFT2_DRV_COMM");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_PRINTER)
    dc  << _T(" VFT2_DRV_PRINTER");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_KEYBOARD)
    dc  << _T(" VFT2_DRV_KEYBOARD");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_LANGUAGE)
    dc  << _T(" VFT2_DRV_LANGUAGE");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_DISPLAY)
    dc  << _T(" VFT2_DRV_DISPLAY");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_MOUSE)
    dc  << _T(" VFT2_DRV_MOUSE");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_NETWORK)
    dc  << _T(" VFT2_DRV_NETWORK");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_SYSTEM)
    dc  << _T(" VFT2_DRV_SYSTEM");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_INSTALLABLE)
    dc  << _T(" VFT2_DRV_INSTALLABLE");
  if (vffiSrc.dwFileSubtype == VFT2_DRV_SOUND)
    dc  << _T(" VFT2_DRV_SOUND");
  }
if (vffiSrc.dwFileType == VFT_FONT)
  {
  dc << _T(":");
  if (vffiSrc.dwFileSubtype == VFT2_UNKNOWN)
    dc  << _T(" VFT2_UNKNOWN");
  if (vffiSrc.dwFileSubtype == VFT2_FONT_RASTER)
    dc  << _T(" VFT2_FONT_RASTER");
  if (vffiSrc.dwFileSubtype == VFT2_FONT_VECTOR)
    dc  << _T(" VFT2_FONT_VECTOR");
  if (vffiSrc.dwFileSubtype == VFT2_FONT_TRUETYPE)
    dc  << _T(" VFT2_FONT_TRUETYPE");
  }
if (vffiSrc.dwFileType == VFT_VXD)
  {
  dc << _T(": virtual device identifier");
  }
dc << _T("\n\tdwFileDateMS       = ") << vffiSrc.dwFileDateMS
   << _T("\n\tdwFileDateLS       = ") << vffiSrc.dwFileDateLS
   << _T("\n\t}\n");

return dc;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
