/*$Workfile: KStrGuidWin.cpp$: implementation file
  $Revision: 4$ $Date: 2005-05-16 14:28:55$
  $Author: Darko Kolakovic$

  Converts  Universally Unique Identifier (UUID) to a string.
  Copyright: CommonSoft Inc.
  2005-05-16 Darko Kolakovic
*/

/* Group=Strings                                                             */

#include "stdafx.h"
#include <rpcdce.h>
#pragma comment(lib, "rpcrt4")

//-----------------------------------------------------------------------------
/*Converts Universally Unique Identifier (UUID) to the string.

  UUIDs are written in following hexadecimal format:
      {hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh}

  Example:
      {340BC870-A012-93BB-2039-84BD734D76E7}

  Note: GUID name is used for backward compatibility.

  Note:  Microsoft Windows specific (Win32).

  Returns: UUID as formatted string.

  See also: tagGUID, tagUUID
 */
CString GuidToStr( const UUID& iid //[in] 128-bit number representing UUID
                 )
{
CString strGUID;

#ifdef _UNICODE
  unsigned short* szGUID;
#else //SBCS
  unsigned char* szGUID;
#endif //_UNICODE

if ( ::UuidToString( const_cast<UUID*>(&iid), &szGUID ) == RPC_S_OK )
  {
  strGUID = (TCHAR*)(szGUID);
  RpcStringFree( &szGUID );
  }
else  //RPC_S_OUT_OF_MEMORY The system is out of memory.
  strGUID.Empty();

return strGUID;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-05-14 01:33:00  Darko           Fixed Unicode
 *       build
 *  1    Biblioteka1.0         2005-05-13 16:40:35  Darko Kolakovic
 * $
  ****************************************************************************/
