/*$Workfile: KGetDomainName2k.cpp$: implementation file
  $Revision: 2$ $Date: 2004-10-01 22:34:55$
  $Author: Darko$

  Get Windows 2000 domain name
  Copyright: CommonSoft Inc.
  2003-08 Darko Kolakovic
 */

#include "stdafx.h"

#ifndef __iads_h__
  #include <Iads.h>
#endif

//-----------------------------------------------------------------------------
/*Retrieves the DNS name of the local computer's domain, such as
  "domainName.companyName.com".
  The property methods of the IADsADSystemInfo interface get or set the
  properties described in the following table.

  Returns: true if successful. otherwise reurns false.

  See also: Interface Property Methods.

  Note: Microsoft Windows specific (Win2k, WinXP).
 */
bool GetDomainName(BSTR* bstrDomainName //[out] DNS name of the local computer's domain
                   )
{
HRESULT hResult;
IADsADSystemInfo *pADsys;
hResult = CoCreateInstance(CLSID_ADSystemInfo,
                      NULL,
                      CLSCTX_INPROC_SERVER,
                      IID_IADsADSystemInfo,
                      (void**)&pADsys);
if (SUCCEEDED(hResult))
  {
  hResult = pADsys->get_DomainDNSName(bstrDomainName);

  if (pADsys)
    pADsys->Release();
  if (SUCCEEDED(hResult))
    return true;
  }
return false;
}

/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-10-01 22:34:55  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-17 02:16:42  Darko
 * $
 *****************************************************************************/

/*IADsADSystemInfo Property Methods
  The property methods of the IADsADSystemInfo interface get or set the
  properties described in the following table. For more information, see
  Interface Property Methods.


  Properties
  UserName
  Access: Read-only
  DataType: BSTR
  Retrieves the Active Directory distinguished name of the current user, which
  is the logged-on user or the user impersonated by the calling thread.

  ComputerName
  Access: Read-only
  DataType: BSTR
  Retrieves the distinguished name of the local computer.

  SiteName
  Access: Read-only
  DataType: BSTR
  Retrieves the site name of the local computer.

  DomainShortName
  Access: Read-only
  DataType: BSTR
  Retrieves the short name of the local computer's domain, such as "domainName".

  DomainDNSName
  Access: Read-only
  DataType: BSTR
  Retrieves the DNS name of the local computer's domain, such as "domainName.companyName.com".

  ForestDNSName
  Access: Read-only
  DataType: BSTR
  Retrieves the DNS name of the local computer's forest.

  PDCRoleOwner
  Access: Read-only
  DataType: BSTR
  Retrieves the distinguished name of the directory service agent (DSA) object
  for the DC that owns the primary domain controller role in the local computer's domain.

  SchemaRoleOwner
  Access: Read-only
  Retrieves the distinguished name of the directory service agent (DSA) object for the
  DC that owns the schema master role in the local computer's forest.

  IsNativeMode
  Access: Read-only
  DataType: Variant Boolean
  Determines whether the local computer's domain is in native or mixed mode.
 */