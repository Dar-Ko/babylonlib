/*$Workfile: H:\_SrcPool\Cpp\KIsFileNameValid.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:16:05 $
  $Author: ddarko $

  Validates Windows filename. TODO:
  Copyright: CommonSoft Inc.
  Jan 2000 Darko Kolakovic
 */

#include <TChar.h>  //TCHAR

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////

/*
Overview of FAT, HPFS, and NTFS File Systems
ID: Q100108

FAT Naming Convention
  FAT uses the traditional 8.3 file naming convention and all filenames must be
  created with the ASCII character set. The name of a file or directory can be
  up to eight characters long, then a period (.) separator, and up to a three
  character extension. The name must start with either a letter or number and
  can contain any characters except for the following:



   . " / \ [ ] : ; | = ,


If any of these characters are used, unexpected results may occur. The name cannot contain any spaces.

The following names are reserved:



   CON, AUX, COM1, COM2, COM3, COM4, LPT1, LPT2, LPT3, PRN, NUL
   COM5, COM6, COM7, COM8, COM9 (WinNT)


All characters will be converted to uppercase.
*/

//g_szInvalidFATChar-----------------------------------------------------------
/*List of characters not allowed in FAT filenames.
  Filenames can contain any uppercase or lowercase characters except
  the following:

     32 34 43 43 44 46 47 58 59 60 61 62 63 91 92 93 124  code
     ---------------------------------------------------------
         "        ,  .  /  :  ;     =        [  \  ]   |  KB Q100108
         "  *           /  :     <     >  ?     \      |  WinNT, Win9x (long file names)
     sp  "  *  +  ,     /  :  ;  <  =  >  ?  [  \  ]   |  DOS (8.3 file names); space (sp)

  Note: Microsoft Windows specific (Win).

  See also: KB: Q100108 Overview of FAT, HPFS, and NTFS File Systems,
  Q120138 Errors Creating Files or Folders in the Root Directory
 */
LPCTSTR const g_szInvalidFATChar = _T("?\"<>*|:");

//g_listReservedFileNames------------------------------------------------------
/*List of reserved file names.
  The following names are reserved:

     CON, AUX, COM1, COM2, COM3, COM4, LPT1, LPT2, LPT3, PRN, NUL.

  Note: On WinNT names COM5, COM6, COM7, COM8, COM9 are also reserved.

  Note: Microsoft Windows specific (Win).

  See also: KB Q100108 Overview of FAT, HPFS, and NTFS File Systems
 */
LPCTSTR const g_listReservedFileNames[] =
  {
  "CON",
  "AUX",
  "COM1",
  "COM2",
  "COM3",
  "COM4",
  "LPT1",
  "LPT2",
  "LPT3",
  "PRN",
  "NUL",
  NULL
  };

/*Long Filename Support in Windows 95
  For every long filename, an alias entry is generated automatically that
  complies with the 8.3 filename rules for backward compatibility.
  Automatically generated aliases are composed of the first six characters
  of the filename plus ~n (where n is a number) and the first three characters
  after the last period. So the filename ThisIsALong.File.Name is associated
  with the automatically generated alias THISIS~1.NAM. If the alias name
  already exists, the algorithm increments n, where n begins with 2 until the
  system can find a unique filename.

  Note: Neither the user nor an application can control the name created by
        the automatic alias process. Related issues are discussed in
        "Long Filenames and Network Compatibility" later in this chapter.

  For the filename to comply with the 8.3 filename rules, it must use only
  the valid characters for an alias and it must be all uppercase. Short
  filenames are converted to uppercase by the IFSMGR before being passed to
  the file system driver. Valid characters for 8.3 filenames (and aliases) can
  be any combination of letters and numbers, a blank (ASCII 20H), ASCII
  characters greater than 127, and the following special characters:

    $ % ' - _ @  ~ ` ! ( ) ^ # &

  The following additional characters are valid in long filenames, but are
  not valid in alias names or 8.3 filenames:

   + , ; = [ ]

  The following rules also apply for Windows 95 file systems:
  - Maximum filename component length is 255 characters, including NULL
  - Maximum path length is 260 characters, including NULL (compared to 80
    characters for a short name)
  - The OEM character set can be specified by an application if the application
    is written for that character set
  - The long-filename directory entries use the Unicode character set to store
    the names
  - The filename and the alias are the same if the filename meets 8.3-filename
    rules (that is, if it contains only valid characters for an alias and it is
    all uppercase). This means that a filename using only valid characters for
    an alias and following the 8.3-filename format is still not the same as the
    alias name if it contains lowercase characters. However, in this case the
    alias is the uppercase version of the filename. For example, if the long
    filename is Examples.Txt, its alias is EXAMPLES.TXT. The case is preserved
    in the long filename. (Notice, though, that searches in the Windows 95 file
    system are not case-sensitive. So a search of the form "examples.txt" or
    "Examples.Txt" will find the same files.)

34 43 43 44 46 47 58 59 60 61 62 63 91 92 93 124
 "  *  +  ,  .  /  :  ;  <  =  >  ?  [  \  ]   |
---------------------------------------------
 "        ,  .  /  :  ;     =        [  \  ]   |  Q100108
 "  *           /  :     <     >  ?     \      |  WinNT
       +  ,           ;     =        [     ]      Win95


A short overview follows; problems are marked with SFN/LFN to indicate where they apply:
SFN means the issues are only relevant to plain DOS, not to DOS boxes under Windows,
while LFN identifies problems that exist even under Windows.

No multiple dots (SFN)
DOS cannot handle multiple dots in filenames.
No leading dot (SFN)
DOS cannot handle filenames that start with a dot.
Case insensitivity (LFN)
DOS is case insensitive, so you cannot, for example, have both a file called `INSTALL' and a directory called `install'.
The 8+3 limit (SFN)
Because the DOS file system only stores the first 8 characters of the filename and the first 3 of the extension, those must be unique. That means that `foobar-part1.c', `foobar-part2.c' and `foobar-prettybird.c' all resolve to the same filename (`FOOBAR-P.C'). The same goes for `foo.bar' and `foo.bartender'. Note: This is not usually a problem under Windows, as it uses numeric tails in the short version of filenames to make them unique. However, a registry setting can turn this behaviour off. While this makes it possible to share file trees containing long file names between SFN and LFN environments, it also means the above problem applies there as well.

Invalid characters
Some characters are invalid in DOS filenames, and should therefore be avoided.
In a LFN environment, these are
"  * / : < > ? \ |


In a SFN environment, other characters are also invalid. These include
+ , [ ].

 In Macintosh HFS filesystem the only invalid character for a filename is the colon ":", while in NT the following characters are invalid:
A space or a period at the end of a filename is not legal in the Win32 name space, but is common in Macintosh file naming practice.
In Unix / is a path delimter

Control characters in the ASCII range 0-31.
The following characters with special meaning for the filesystem: " * / \ < > ? |
Spaces and periods when they appear as the last character of a filename.

Invalid Characters in a DOS File Name:

   --------------------------------------------------
   Char  Description
   --------------------------------------------------
     ]
     [
     +   combine files
     /   qualifier
     *   wild card character (match any multiple characters)
     ?   wild card character (match any 1 character)
     <   direct screen input from a file
     >   direct screen output to a file
     ,   file separator
     .   file extension
     ;   parameter terminator
     :   disk drive
     "   literal quote
     =
     \   root directory, subdirectory separator
     |   pipe
   --------------------------------------------------



 */
/*
 * ap_os_is_filename_valid is given a filename, and returns 0 if the filename
 * is not valid for use on this system. On Windows, this means it fails any
 * of the tests below. Otherwise returns 1.
 *
 * Test for filename validity on Win32. This is of tests come in part from
 * the MSDN article at "Technical Articles, Windows Platform, Base Services,
 * Guidelines, Making Room for Long Filenames" although the information
 * in MSDN about filename testing is incomplete or conflicting. There is a
 * similar set of tests in "Technical Articles, Windows Platform, Base Services,
 * Guidelines, Moving Unix Applications to Windows NT".
 *
 * The tests are:
 *
 * 1) total path length greater than MAX_PATH
 *
 * 2) anything using the octets 0-31 or characters " < > | :
 *    (these are reserved for Windows use in filenames. In addition
 *     each file system has its own additional characters that are
 *     invalid. See KB article Q100108 for more details).
 *
 * 3) anything ending in "." (no matter how many)
 *    (filename doc, doc. and doc... all refer to the same file)
 *
 * 4) any segment in which the basename (before first period) matches
 *    one of the DOS device names
 *    (the list comes from KB article Q100108 although some people
 *     reports that additional names such as "COM5" are also special
 *     devices).
 *
 * If the path fails ANY of these tests, the result must be to deny access.
 */

BOOL IsPathNameValid(LPCTSTR szFilePath)
{
const char *segstart;
unsigned int seglength;
const char *pos;

/* Test 1 */
if (strlen(file) >= MAX_PATH) {
/* Path too long for Windows. Note that this test is not valid
 * if the path starts with //?/ or \\?\. */
return 0;
  }

pos = file;

/* Skip any leading non-path components. This can be either a
 * drive letter such as C:, or a UNC path such as \\SERVER\SHARE\.
 * We continue and check the rest of the path based on the rules above.
 * This means we could eliminate valid filenames from servers which
 * are not running NT (such as Samba).
 */

if (pos[0] && pos[1] == ':') {
/* Skip leading drive letter */
  pos += 2;
  }
else {
if ((pos[0] == '\\' || pos[0] == '/') &&
  (pos[1] == '\\' || pos[1] == '/')) {
  /* Is a UNC, so skip the server name and share name */
  pos += 2;
  while (*pos && *pos != '/' && *pos != '\\')
pos++;
  if (!*pos) {
/* No share name */
return 0;
  }
  pos++; /* Move to start of share name */
  while (*pos && *pos != '/' && *pos != '\\')
pos++;
  if (!*pos) {
/* No path information */
return 0;
  }
}
}

  while (*pos) {
unsigned int idx;
unsigned int baselength;

while (*pos == '/' || *pos == '\\') {
    pos++;
}
if (*pos == '\0') {
    break;
}
segstart = pos;	/* start of segment */
while (*pos && *pos != '/' && *pos != '\\') {
    pos++;
}
seglength = pos - segstart;
/*
 * Now we have a segment of the path, starting at position "segstart"
 * and length "seglength"
 */

/* Test 2 */
for (idx = 0; idx < seglength; idx++) {
    if ((segstart[idx] > 0 && segstart[idx] < 32) ||
strchr(g_szInvalidFATChar, segstart[idx])) {
return 0;
    }
}

/* Test 3 */
if (segstart[seglength-1] == '.') {
    return 0;
}

/* Test 4 */
for (baselength = 0; baselength < seglength; baselength++) {
    if (segstart[baselength] == '.') {
break;
    }
}

/* baselength is the number of characters in the base path of
 * the segment (which could be the same as the whole segment length,
 * if it does not include any dot characters). */
if (baselength == 3 || baselength == 4)
  {
    for (idx = 0; g_listReservedFileNames[idx]; idx++) {
if (strlen(g_listReservedFileNames[idx]) == baselength &&
    !strnicmp(g_listReservedFileNames[idx], segstart, baselength)) {
    return 0;
}
    }
}
  }

  return 1;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         29/01/2002 10:21:16 PMDarko           Used lbraries
 *       notes
 *  2    Biblioteka1.1         29/01/2002 2:40:28 PMDarko           Tag update
 *  1    Biblioteka1.0         04/10/2001 10:59:18 AMDarko
 * $
 * Jan 2000 Darko Kolakovic
 *****************************************************************************/
//
// Given a string as input, this routine does its best to try and extract
// a filename portion in the beginning.  A "filename" means that there's
// a ":\" near the beginning.  The function handles filenames in quotes.
// If the g_fBeRealistic variable is TRUE, it assumes that characters like
// '/' and '-' aren't part of the filename, although they're technically
// legal.
//
BOOL CheckForFilename( LPTSTR psz, LPTSTR szOutput, UINT cbOutput )
{
    if ( lstrlen(psz) <= 2 )        // toss out strings that are too short
        return FALSE;

    BOOL fBeginQuote = FALSE;
    LPTSTR pszStartFilename = psz;
    if ( *pszStartFilename == '"' ) // Does the string start with a quote?
    {                               // If so, adjust accordingly.  We'll
        fBeginQuote = TRUE;         // assume that there must be an end quote
        pszStartFilename++;         // for it to be a legal filename.
    }

    LPTSTR pszEndName;  // Pointer to one char past the end of the name

    if ( fBeginQuote )  // The string started with quotes.  Find the other one
    {
        pszEndName = _tcschr( pszStartFilename, '"' );
        if ( !pszEndName )
            return FALSE;

        pszEndName--;   // Strip off spaces at the end
        while ( (pszEndName > pszStartFilename) && (*pszEndName == ' ') )
            pszEndName--;

        pszEndName++;
    }
    else    // String didn't start with a quote
    {
        // Look for the first non-legal filename character
        pszEndName = _tcspbrk( psz, TEXT("<>|/\"") );

        if ( pszEndName )   // We found a non-legal character, so the
        {                   // filename must end before this
            // Now strip off any whitespace
            pszEndName--;
            while ( (pszEndName > pszStartFilename) && (*pszEndName == ' '))
                pszEndName--;

            pszEndName++;
        }
        else
            pszEndName = psz + lstrlen(psz);    // No non-legal chars found
    }

    // At this point, pszStartFilename points to the beginning of the possible
    // filename, and pszEndName points 1 character past the last character
    // of the possible filename.

    if ( pszEndName - pszStartFilename < 2 )    // Are the start and end far
        return FALSE;                           // enough apart to be legal?

    // Check to see if the 2nd and 3rd characters are ":\"
    if ( 0 != _tcsnicmp( pszStartFilename+1, TEXT(":\\"), 2 ) )
        return FALSE;

    if ( g_fBeRealistic )   // If set, toss out unlikely characters
    {
        LPTSTR pszSearch = _tcspbrk( pszStartFilename, TEXT("^/-%,;") );

        // Did we find something, and was it before what we're considering
        // the end of the filename to be?
        if ( pszSearch && (pszSearch < pszEndName) )
        {
            // Now strip off any whitespace
            pszSearch--;
            while ( (pszSearch > pszStartFilename) && (*pszSearch == ' ') )
                pszSearch--;

            pszEndName = pszSearch+1;
        }
    }

    // Make sure the string we found won't overflow the input buffer
    unsigned nameLen = pszEndName - pszStartFilename;
    if ( nameLen >= cbOutput )
        return FALSE;

    // copy the filename string to the input buffer
    memcpy( szOutput, pszStartFilename, nameLen * sizeof(TCHAR) );
    szOutput[ nameLen ] = 0;    // Null terminate it!

    return TRUE;
}
