/*$Workfile: KDbgDlgErrorCode.cpp$: implementation file
  $Revision: 4$ $Date: 2005-04-26 11:29:01$
  $Author: Darko Kolakovic$

  Dumps dialog error return codes
  Copyright: CommonSoft Inc.
  2003-08-05 Darko Kolakovic
 */

// Group=Diagnostic

#include "stdafx.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

  #ifndef _INC_CDERR
    #include <cderr.h>  //Common dialog error return codes
  #endif

///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*Dumps the most recent common dialog box error occured during the execution of
  one of the common dialog box functions. These error codes are defined in cderr.h.

  The following general error codes can be returned for any of the common dialog
  box functions:

      Value                 Meaning
      CDERR_DIALOGFAILURE   The dialog box could not be created. The common
                            dialog box function's call to the DialogBox function
                            failed. For example, this error occurs if the common
                            dialog box call specifies an invalid window handle.
      CDERR_FINDRESFAILURE  The common dialog box function failed to find
                            a specified resource.
      CDERR_INITIALIZATION  The common dialog box function failed during
                            initialization. This error often occurs when
                            sufficient memory is not available.
      CDERR_LOADRESFAILURE  The common dialog box function failed to load
                            a specified resource.
      CDERR_LOADSTRFAILURE  The common dialog box function failed to load
                            a specified string.
      CDERR_LOCKRESFAILURE  The common dialog box function failed to lock
                            a specified resource.
      CDERR_MEMALLOCFAILURE The common dialog box function was unable to
                            allocate memory for internal structures.
      CDERR_MEMLOCKFAILURE  The common dialog box function was unable to lock
                            the memory associated with a handle.
      CDERR_NOHINSTANCE     The ENABLETEMPLATE flag was set in the Flags member
                            of the initialization structure for the corresponding
                            common dialog box, but you failed to provide
                            a corresponding instance handle.
      CDERR_NOHOOK          The ENABLEHOOK flag was set in the Flags member of
                            the initialization structure for the corresponding
                            common dialog box, but you failed to provide
                            a pointer to a corresponding hook procedure.
      CDERR_NOTEMPLATE      The ENABLETEMPLATE flag was set in the Flags member
                            of the initialization structure for the corresponding
                            common dialog box, but you failed to provide
                            a corresponding template.
      CDERR_REGISTERMSGFAIL The RegisterWindowMessage function returned
                            an error code when it was called by the common
                            dialog box function.
      CDERR_STRUCTSIZE      The lStructSize member of the initialization
                            structure for the corresponding common dialog box
                            is invalid.

  The following error codes can be returned for the PrintDlg function:

      Value                  Meaning
      PDERR_CREATEICFAILURE  The PrintDlg function failed when it attempted to
                             create an information context.
      PDERR_DEFAULTDIFFERENT You called the PrintDlg function with
                             the DN_DEFAULTPRN flag specified in the wDefault
                             member of the DEVNAMES structure, but the printer
                             described by the other structure members did not
                             match the current default printer. (This error
                             occurs when you store the DEVNAMES structure and
                             the user changes the default printer by using
                             the Control Panel.)
                             To use the printer described by the DEVNAMES
                             structure, clear the DN_DEFAULTPRN flag and
                             call PrintDlg again.
                             To use the default printer, replace the DEVNAMES
                             structure (and the structure, if one exists) with
                             NULL; and call PrintDlg again.
      PDERR_DNDMMISMATCH     The data in the DEVMODE and DEVNAMES structures
                             describes two different printers.
      PDERR_GETDEVMODEFAIL   The printer driver failed to initialize
                             a DEVMODE structure.
      PDERR_INITFAILURE      The PrintDlg function failed during initialization
                             and there is no more specific extended error code
                             to describe the failure. This is the generic default
                             error code for the function.
      PDERR_LOADDRVFAILURE   The PrintDlg function failed to load the device
                             driver for the specified printer.
      PDERR_NODEFAULTPRN     A default printer does not exist.
      PDERR_NODEVICES        No printer drivers were found.
      PDERR_PARSEFAILURE     The PrintDlg function failed to parse the strings
                             in the [devices] section of the WIN.INI file.
      PDERR_PRINTERNOTFOUND  The [devices] section of the WIN.INI file did not
                             contain an entry for the requested printer.
      PDERR_RETDEFFAILURE    The PD_RETURNDEFAULT flag was specified in the Flags
                             member of the PRINTDLG structure, but the hDevMode
                             or hDevNames member was not NULL.
      PDERR_SETUPFAILURE     The PrintDlg function failed to load the required
                             resources.

  The following error codes can be returned for the ChooseFont function:

      Value                Meaning
      CFERR_MAXLESSTHANMIN The size specified in the nSizeMax member of
                           the CHOOSEFONT structure is less than the size
                           specified in the nSizeMin member.
      CFERR_NOFONTS        No fonts exist.

  The following error codes can be returned for the GetOpenFileName and
  GetSaveFileName functions:

      Value                 Meaning
      FNERR_BUFFERTOOSMALL  The buffer pointed to by the lpstrFile member of
                            the OPENFILENAME structure is too small for the file
                            name specified by the user. The first two bytes of
                            the lpstrFile buffer contain an integer value
                            specifying the size, in TCHARs, required to receive
                            the full name.
      FNERR_INVALIDFILENAME A file name is invalid.
      FNERR_SUBCLASSFAILURE An attempt to subclass a list box failed because
                            sufficient memory was not available.

  The following error code can be returned for the FindText and ReplaceText
  functions;

      Value                   Meaning
      FRERR_BUFFERLENGTHZERO A member of the FINDREPLACE structure points to
                             an invalid buffer.


  See also: CommDlgExtendedError(), cderr.h - Common dialog error return codes

  Note: uses Microsoft Foundation Library (MFC).
        Microsoft Windows specific (Win).
 */
void DumpDlgErrorCode()
{
afxDump << _T("Common dialog box returned error ");
switch (CommDlgExtendedError())
  {
  case CDERR_GENERALCODES    : afxDump << _T("CDERR_GENERALCODES\n"    ); break; //0x0000
  case CDERR_STRUCTSIZE      : afxDump << _T("CDERR_STRUCTSIZE\n"      ); break; //0x0001
  case CDERR_INITIALIZATION  : afxDump << _T("CDERR_INITIALIZATION\n"  ); break; //0x0002
  case CDERR_NOTEMPLATE      : afxDump << _T("CDERR_NOTEMPLATE\n"      ); break; //0x0003
  case CDERR_NOHINSTANCE     : afxDump << _T("CDERR_NOHINSTANCE\n"     ); break; //0x0004
  case CDERR_LOADSTRFAILURE  : afxDump << _T("CDERR_LOADSTRFAILURE\n"  ); break; //0x0005
  case CDERR_FINDRESFAILURE  : afxDump << _T("CDERR_FINDRESFAILURE\n"  ); break; //0x0006
  case CDERR_LOADRESFAILURE  : afxDump << _T("CDERR_LOADRESFAILURE\n"  ); break; //0x0007
  case CDERR_LOCKRESFAILURE  : afxDump << _T("CDERR_LOCKRESFAILURE\n"  ); break; //0x0008
  case CDERR_MEMALLOCFAILURE : afxDump << _T("CDERR_MEMALLOCFAILURE\n" ); break; //0x0009
  case CDERR_MEMLOCKFAILURE  : afxDump << _T("CDERR_MEMLOCKFAILURE\n"  ); break; //0x000A
  case CDERR_NOHOOK          : afxDump << _T("CDERR_NOHOOK\n"          ); break; //0x000B
  case CDERR_REGISTERMSGFAIL : afxDump << _T("CDERR_REGISTERMSGFAIL\n" ); break; //0x000C

  case PDERR_PRINTERCODES    : afxDump << _T("PDERR_PRINTERCODES\n"    ); break; //0x1000
  case PDERR_SETUPFAILURE    : afxDump << _T("PDERR_SETUPFAILURE\n"    ); break; //0x1001
  case PDERR_PARSEFAILURE    : afxDump << _T("PDERR_PARSEFAILURE\n"    ); break; //0x1002
  case PDERR_RETDEFFAILURE   : afxDump << _T("PDERR_RETDEFFAILURE\n"   ); break; //0x1003
  case PDERR_LOADDRVFAILURE  : afxDump << _T("PDERR_LOADDRVFAILURE\n"  ); break; //0x1004
  case PDERR_GETDEVMODEFAIL  : afxDump << _T("PDERR_GETDEVMODEFAIL\n"  ); break; //0x1005
  case PDERR_INITFAILURE     : afxDump << _T("PDERR_INITFAILURE\n"     ); break; //0x1006
  case PDERR_NODEVICES       : afxDump << _T("PDERR_NODEVICES\n"       ); break; //0x1007
  case PDERR_NODEFAULTPRN    : afxDump << _T("PDERR_NODEFAULTPRN\n"    ); break; //0x1008
  case PDERR_DNDMMISMATCH    : afxDump << _T("PDERR_DNDMMISMATCH\n"    ); break; //0x1009
  case PDERR_CREATEICFAILURE : afxDump << _T("PDERR_CREATEICFAILURE\n" ); break; //0x100A
  case PDERR_PRINTERNOTFOUND : afxDump << _T("PDERR_PRINTERNOTFOUND\n" ); break; //0x100B
  case PDERR_DEFAULTDIFFERENT: afxDump << _T("PDERR_DEFAULTDIFFERENT\n"); break; //0x100C

  case CFERR_CHOOSEFONTCODES : afxDump << _T("CFERR_CHOOSEFONTCODES\n" ); break; //0x2000
  case CFERR_NOFONTS         : afxDump << _T("CFERR_NOFONTS        \n" ); break; //0x2001
  case CFERR_MAXLESSTHANMIN  : afxDump << _T("CFERR_MAXLESSTHANMIN \n" ); break; //0x2002

  case FNERR_FILENAMECODES   : afxDump << _T("FNERR_FILENAMECODES  \n" ); break; //0x3000
  case FNERR_SUBCLASSFAILURE : afxDump << _T("FNERR_SUBCLASSFAILURE\n" ); break; //0x3001
  case FNERR_INVALIDFILENAME : afxDump << _T("FNERR_INVALIDFILENAME\n" ); break; //0x3002
  case FNERR_BUFFERTOOSMALL  : afxDump << _T("FNERR_BUFFERTOOSMALL \n" ); break; //0x3003

  case FRERR_FINDREPLACECODES: afxDump << _T("FRERR_FINDREPLACECODES\n"); break; //0x4000
  case FRERR_BUFFERLENGTHZERO: afxDump << _T("FRERR_BUFFERLENGTHZERO\n"); break; //0x4001

  case CCERR_CHOOSECOLORCODES: afxDump << _T("CCERR_CHOOSECOLORCODES\n"); break; //0x5000

  case CDERR_DIALOGFAILURE   : afxDump << _T("CDERR_DIALOGFAILURE\n"   ); break; //0xFFFF
  default: afxDump << _T("Unknown error\n"   );
  }
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2005-04-26 11:29:01  Darko Kolakovic Document groups
 *       and typo fixes
 *  3    Biblioteka1.2         2004-10-01 22:34:12  Darko           stdafx.h
 *  2    Biblioteka1.1         2003-08-13 14:39:32  Darko           formatting
 *  1    Biblioteka1.0         2003-08-06 14:58:58  Darko
 * $
 *****************************************************************************/
