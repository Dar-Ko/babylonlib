/*$Workfile: KFileNam.h$: header file
  $Revision: 1$ $Date: 27/08/2002 4:04:52 PM$
  $Author: Darko Kolakovic$

  File Name handler
  Copyright: CommonSoft Inc.
  May 98 Darko Kolakovic
 */

#ifndef _KFILENAME_H_
    //KFileNam.h sentry
  #define _KFILENAME_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef LDID_
/* List of the logical disk identifiers (LDID) used in Device Information File (.INF): 
    00 Null LDID; this LDID can be used to create a new LDID
    01 Source drive:\ pathname
    02 Temporary Setup directory; this is valid only during Windows 95 Setup 
    03 Uninstall directory 
    04 Backup directory 
    10 Windows directory 
    11 SYSTEM directory 
    12 IOSUBSYS directory  
    13 COMMAND directory 
    14 Control Panel directory 
    15 Printers directory 
    16 Workgroup directory 
    17 INF directory 
    18 Help directory 
    19 Administration 
    20 Fonts 
    21 Viewers 
    22 VMN32 
    23 Color directory 
    25 Shared directory 
    26 Winboot 
    27 Machine specific 
    28 Host Winboot 
    30 Root directory of the boot drive 
    31 Root directory for host drive of a virtual boot drive 
    32 Old Windows directory if it exists 
    33 Old MS-DOS directory if it exists
*/
typedef enum LDID_
  {
   LDID$NULL     = 00, //Null LDID; this LDID can be used to create a new LDID
   LDID$SOURCE   = 01, //Source drive:\ pathname
   LDID$TMPSET   = 02, //Temporary Setup directory; this is valid only during Windows 95 Setup 
   LDID$UNISTT   = 03, //Uninstall directory 
   LDID$BACKUP   = 04, //Backup directory 
   LDID_WIN      = 10, //Windows directory 
   LDID_SYS      = 11, //SYSTEM directory 
   LDID_IOS      = 12, //IOSUBSYS directory  
   LDID$COMMD    = 13, //COMMAND directory 
   LDID$CTRLP    = 14, //Control Panel directory 
   LDID$PRINT    = 15, //Printers directory 
   LDID$WGP      = 16, //Workgroup directory 
   LDID$INF      = 17, //INF directory 
   LDID$HELP     = 18, //Help directory 
   LDID$ADMIN    = 19, //Administration 
   LDID$FONTS    = 20, //Fonts 
   LDID$VIEWERS  = 21, //Viewers 
   LDID$VMN      = 22, //VMN32 
   LDID$COLOR    = 23, //Color directory 
   LDID_SHARED   = 25, //Shared directory 
   LDID$WINBOOT  = 26, //Winboot 
   LDID_MACHINE  = 27, //Machine specific 
   LDID$WINBOOTH = 28, //Host Winboot 
   LDID_BOOT     = 30, //Root directory of the boot drive 
   LDID_BOOTHOST = 31, //Root directory for host drive of a virtual boot drive 
   LDID$OLDWIN   = 32, //Old Windows directory if it exists 
   LDID$OLDDOS   = 33  //Old MS-DOS directory if it exists
  };

  #define LDID_ LDID_
#endif  //LDID_
///////////////////////////////////////////////////////////////////////////////
//CFileName class creates and parses file names.
class CFileName
{
  // Construction
public:
  CFileName(LPCTSTR szFileName = NULL);
  CFileName(const CFileName& cfnFileName);

// Attributes
private:
    //Parts of the UNC file name
  enum  FILENAMEITEM
    {
    Server    = 0x1,  //server name
    Sharename = 0x2,  //sharename or logical device
    Path      = 0x4,  //directory path to the file
    File      = 0x8,  //file name
    Ext       = 0xF   //filename extension
    };

  //Stock file names
  enum FILENAMESTOCK 
    {
    dirOS        = LDID_WIN,     //home directory for OS
    dirOSSys     = LDID_SYS,     //directory with OS system files
    dirOSBoot    = LDID_BOOT,    //root directory of boot drive
    dirOSShared  = LDID_SHARED,  //shared home directory for OS
    dirMachine   = LDID_MACHINE, //directory with machine specific files
    dirCurrent   = 80, //current working directory if any
    dirTemp,           //directory with temporary files
    nameTempFile,      //a name of the temporary file
    nameMachine,       //a computer name
    };

protected:
    bool    m_bUNC;         //'UNC file name' flag
    CString m_strServer;    //server name
    CString m_strSharename; //sharename or logical device
    CString m_strPath;      //directory path to the file
    CString m_strFile;      //file name
    CString m_strExt;       //filename extension

  // Operations
public:
  CFileName(FILENAMESTOCK StockType);
  operator LPCTSTR() const;
  CFileName& operator =(const CFileName& cfnFileName);
  CFileName& operator =(LPCTSTR szFileName);
  bool operator ==(const CFileName& cfnFileName) const;

  LPCTSTR Canonical(bool bUNC = FALSE) const;
  static CString Canonical(LPCSTR szFilename, bool bUNC);
  LPCTSTR ShortName(bool bUNC = FALSE) const;
  LPCTSTR FileTitle(int iMaxLen = _MAX_PATH) const;

  bool IsFileFound() const;
  bool IsValid() const; 
  bool IsUNC() const;
  bool CreateDirectory() const;
  bool ChangeDirectory() const;

  void Remove() const;
  void CopyFile(LPCTSTR lpNewFileName, bool bFailIfExists) const;
  #ifdef WIN32    //Windows 32b application 
    bool IsShortcut() const;
  #endif

protected:
  void Parse(LPCTSTR szFileName);

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

#ifdef WIN32    //Windows 32b application
  #include "KFileN32.inl"
#else
  #include "KFileN16.inl"
#endif

//::IsUNC()--------------------------------------------------------------------
/*Returns TRUE if file name is in the UNC format.
  UNC is a universal form of a path identifies a network resource in an 
  unambiguous, computer-independent manner. The path can then be passed to 
  processes on other computers, allowing those processes to obtain access to 
  the network resource. Universal Naming Convention (UNC) names look like this:
 
    \\servername\sharename\path\file 

 */
inline bool CFileName::IsUNC() const
{
return m_bUNC;
}

//::operator ==()--------------------------------------------------------------
/*Returns TRUE if file names are equal.
 */
inline bool CFileName::operator ==(const CFileName& cfnFileName) const
{
  //MBCS/Unicode aware
return (_tcscmp(Canonical(),cfnFileName.Canonical()) == 0);
}

//::operator const LPTSTR()----------------------------------------------------
/*Returns a null-terminated string that is the file name.
 */
inline CFileName::operator LPCTSTR() const
{
return Canonical();
}

//::operator =()---------------------------------------------------------------
/*Assign a new filename string to this filename object
 */
inline CFileName& CFileName::operator =(LPCTSTR szFileName)
{
Parse(szFileName);
return *this;
}

//::FindData()-----------------------------------------------------------------
/*UNC is a universal form of a path identifies a network resource in an 
  unambiguous, computer-independent manner. The path can then be passed to 
  processes on other computers, allowing those processes to obtain access to 
  the network resource. Universal Naming Convention (UNC) names look like this:
 
    \\servername\sharename\path\file 

  TODO:
 * /
inline const WIN32_FIND_DATA& CFileNameBrowser::FindData() const
{
return m_FindData;
}*/

///////////////////////////////////////////////////////////////////////////////
#endif  //_KFILENAME_H_
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         27/08/2002 4:04:52 PMDarko Kolakovic 
 * $
 *****************************************************************************/

