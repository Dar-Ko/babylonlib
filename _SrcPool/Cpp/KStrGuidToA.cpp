/*$Workfile: KStrGuidToA.cpp$: implementation file
  $Revision: 1$ $Date: 2007-06-19 16:29:02$
  $Author: Darko Kolakovic$

  Converts globally unique identifier (GUID) to a string.
  Copyright: CommonSoft Inc.
  2007-02-01 Darko Kolakovic
*/

/* Group=Strings                                                             */

//----------------------------------------------------------------------------
/*Converts globally unique identifier (GUID) to a string.

  The GUID is a Microsoft implementation of an Universally Unique Identifier
  (UUID), specified by the Open Software Foundation (OSF).
  GUIDs are written in following hexadecimal format:
      hhhhhhhh-hhhh-hhhh-hhhh-hhhhhhhhhhhh

  Example:
      #include <initguid.h> //Microsof specific GUID initialization
      TCHAR szGuid[37];
      DEFINE_GUID(guid, 0x340BC870, 0xA012, 37819,
                  0x20, 57, 132, 189, 0x73, 0x4D, 0x76, 0xE7);
      TRACE1(GuidToA(guid, szGuid, 37));
      Output:
      340BC870-A012-93BB-2039-84BD734D76E7

  Returns: GUID as zero-terminated string or NULL in case of invalid arguments.

  See also: tagGUID, tagUUID, GuidToStr(), CGuid
 */
TCHAR* GuidToA(const GUID iid,    //[in] 128-bit number representing GUID
               TCHAR* szGuid,     //[out] pointer to string buffer
               unsigned int nSize //[in] size of the resulting buffer in
                                  //characters
              )
{
TCHAR* szResult = NULL;
if ((szGuid != NULL) && (nSize > 0))
  {
  const unsigned int BUFFER_SIZE = 37;
  TCHAR szTmp[BUFFER_SIZE] = {0};
  sprintf(szTmp, _T("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"),
          iid.Data1, iid.Data2, iid.Data3,
          iid.Data4[0], iid.Data4[1], iid.Data4[2], iid.Data4[3],
          iid.Data4[4], iid.Data4[5], iid.Data4[6], iid.Data4[7]);

  if (nSize > BUFFER_SIZE)
    nSize = BUFFER_SIZE; //The result could fit in the given buffer
  else
    szTmp[nSize] = _T('\0'); //Terminate the result string
  //Copy the result string, including terminator, to the given buffer
  szResult = szGuid;
  memcpy(szResult, szTmp, nSize * sizeof(TCHAR));
  }
return szResult;
};
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: $
  ****************************************************************************/
