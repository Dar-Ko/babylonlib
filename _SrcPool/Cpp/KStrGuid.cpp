/*$Workfile: S:\_SrcPool\Cpp\KStrGuid.cpp$: implementation file
  $Revision: 4$ $Date: 2005-05-13 16:38:58$
  $Author: Darko Kolakovic$

  Converts globally unique identifier (GUID) to a string.
  Copyright: CommonSoft Inc.
  Nov '96 Darko Kolakovic
*/

/* Group=Strings                                                             */

#include "stdafx.h"

//GuidToStr()-----------------------------------------------------------------
/*Converts globally unique identifier (GUID) to a string.
  GUID is a pseudo-random number "statistically guaranteed" to be unique.
  Number of possible keys is 2^128 (3.4028e38). The possibility of the same
  number being generated twice is virtually zero.

  The GUID is a Microsoft implementation of an Universally Unique Identifier
  (UUID), specified by the Open Software Foundation (OSF).
  GUIDs are written in following hexadecimal format:
      {hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh}

  Example:
      {340BC870-A012-93BB-2039-84BD734D76E7}

  Returns: GUID as formatted string.

  See also: tagGUID, tagUUID
 */
CString GuidToStr(const GUID& iid //[in] 128-bit number representing GUID
                 )
{
CString strGUID;
strGUID.Format(_T("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}"),
    iid.Data1, iid.Data2, iid.Data3,
    iid.Data4[0], iid.Data4[1], iid.Data4[2], iid.Data4[3],
    iid.Data4[4], iid.Data4[5], iid.Data4[6], iid.Data4[7]);
return strGUID;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-05-11 22:32:15  Darko           Comment
 *  1    Biblioteka1.0         2005-05-11 01:44:41  Darko
 * $
 *  0    Biblioteka0           Darko Kolakovic  Nov '96
  ****************************************************************************/
