/*$Workfile: KStrGuidWin.cpp$: implementation file
  $Revision: 1$ $Date: 2005-05-13 16:40:35$
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
/*Converts Universally Unique Identifier (UUID) to a string.

  UUIDs are written in following hexadecimal format:
      {hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh}

  Example:
      {340BC870-A012-93BB-2039-84BD734D76E7}

  Note: GUID name is used for backward compatibility.

  Note:  Microsoft Windows specific (Win32).

  Returns: UUID as formatted string.

  See also: tagGUID, tagUUID
 */
CString GuidToStr(const UUID& iid //[in] 128-bit number representing UUID
                 )
{
CString strGUID;
LPTSTR szGUID;
if ( ::UuidToString( &iid, &szGUID ) == RPC_S_OK )
  {
  strGUID = szGUID;
  RpcStringFree( &szGUID );
  }
else  //RPC_S_OUT_OF_MEMORY The system is out of memory.
  strGUID.Empty();

return strGUID;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-05-13 16:40:35  Darko Kolakovic 
 * $
  ****************************************************************************/
