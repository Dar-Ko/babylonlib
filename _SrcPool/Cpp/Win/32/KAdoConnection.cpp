/*$Workfile: KAdoConnection.cpp$: implementation file
  $Revision: 10$ $Date: 2005-04-26 11:28:11$
  $Author: Darko Kolakovic$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  2k3-08 Darko Kolakovic
 */

#include "stdafx.h"
#include "KAdoConnection.h" //class CAdoConnection
#include "KAtlExt.h" //TESTHR()

extern void ComErrorShow(_com_error& cee,
                         LPCTSTR szHelpFile = NULL,
                         UINT nHelpContext = 0);
extern LPCTSTR ComProviderErrors(_ConnectionPtr ptrConnection,
                                 CString& strResult);

LPCTSTR CAdoConnection::m_szProvider   = _T("Provider=Microsoft.Jet.OLEDB.4.0;");
LPCTSTR CAdoConnection::m_szDataSource = _T("Data Source=%s;");
LPCTSTR CAdoConnection::m_szUserId     = _T("User ID=Admin;");
LPCTSTR CAdoConnection::m_szPassword   = _T("Password=;");
LPCTSTR CAdoConnection::m_szExtendedProperties = _T("Extended Properties=;");
LPCTSTR CAdoConnection::m_szMode       = _T("Mode=ReadWrite;");

//-----------------------------------------------------------------------------
/*Default constructor. If COM library is not initialized, the constructor will
  use COINIT_MULTITHREADED for threading model.

  See also: COINIT, CoInitializeEx()
 */
CAdoConnection::CAdoConnection(void):
  m_pConnection(NULL)
{
m_strConnection.Empty();
//Initialize the COM library for use by the calling thread,
//set the thread's concurrency model
uint_least32_t coThreadingModel = GetApartmentType();
if (coThreadingModel == 0xFF)
  coThreadingModel = COINIT_MULTITHREADED; //COINIT_APARTMENTTHREADED
TESTHR(::CoInitializeEx(NULL, coThreadingModel));
}

//-----------------------------------------------------------------------------
/*Closses connection, if open.
 */
CAdoConnection::~CAdoConnection(void)
{
VERIFY(Close());

::CoUninitialize();
}

//-----------------------------------------------------------------------------
/*Opens a new ADO connection.
  This method is used in conjunction with the default  constructor as a safe
  method for opening a connection where a failure is a normal, expected condition.

  Returns:  true if the open was successful; otherwise returns false.
 */
bool CAdoConnection::Open(LPCTSTR szFileName, //[in]
                          LPCTSTR szUserName, //[in]= NULL
                          LPCTSTR szPassword, //[in]= NULL
                          uint_fast32_t nOpenFlags  //TODO: [in]= Mode::modeReadWrite | Mode::shareDenyNone
                          )
{
TRACE(_T("CAdoConnection::Open(%s,%s,0x%X)"),szFileName, szUserName, nOpenFlags);
if (!IsConnected())
  {
  m_strConnection =  CAdoConnection::m_szProvider;
  m_strConnection += ADO_CSJET_FILE_NAME;
  m_strConnection += szFileName;
  m_strConnection += _T(';');

  try
    {
      //Instantiating the Connection object
    HRESULT hResult = m_pConnection.CreateInstance(__uuidof(Connection));
    TESTHR(hResult); //Throws an exception if test faials

    m_pConnection->ConnectionString = _bstr_t((LPCTSTR)m_strConnection);
    m_pConnection->Open((LPCTSTR)m_strConnection, //ConnectionString
                        szUserName, //UserID
                        szPassword, //Password
                        adConnectUnspecified  //Options (-1)
                        );
    return true;
    }
  catch(_com_error& cee)
    {
    TRACE(_T("  Failed to open connection to %s!\n"), szFileName);
    CString strMessage;
    if (ComProviderErrors(m_pConnection, strMessage) != NULL)
      AfxMessageBox( strMessage, MB_OK | MB_ICONERROR );
    else
      ComErrorShow(cee);
    }
  }
return false;
}

//-----------------------------------------------------------------------------
/*Closes the open ADO connection. If connection is already closed, function
  does nothing. In case of COM exception, the error message box shows the
  error description.

  Returns: true if successful; otherwise returns false.
 */
bool CAdoConnection::Close()
{
TRACE("CAdoConnection::Close()\n");

HRESULT hReturn = S_FALSE;

if(IsConnected())
  {
  try
    {
    hReturn = m_pConnection->Close();
    TESTHR(hReturn);
    m_pConnection.Release();
    m_pConnection = NULL;
    }
  catch(_com_error& cee)
    {
    TRACE("  Failed to close Ado connection!\n");
    ComErrorShow(cee);
    return false;
    }
  }
return true;
}

#ifdef _DEBUG
  //---------------------------------------------------------------------------
  /*Call this method to confirm that this object is valid.
    This method is available only if _DEBUG is defined.
   */
  void CAdoConnection::AssertValid() const
  {
  ASSERT(this != NULL);
  }

  //-----------------------------------------------------------------------------
  /*Dumps the contents of CAdoField object to a CDumpContext object if
    _DEBUG macro is defined.
   */
  void CAdoConnection::Dump(CDumpContext& dc // dump context
                            ) const
  {
  dc << _T("CAdoConnection @ ") << this
     << _T("\n  {\n  ")
     << m_strConnection
     << _T("\n  }\n");

  UNUSED(dc); //Unused in release build
  }
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  9    Biblioteka1.8         2004-10-01 22:33:28  Darko           stdafx.h
 *  8    Biblioteka1.7         2003-09-10 16:09:08  Darko           Added Dump()
 *  7    Biblioteka1.6         2003-08-21 15:28:25  Darko           comment
 *  6    Biblioteka1.5         2003-08-21 15:27:32  Darko           comments
 *  5    Biblioteka1.4         2003-08-19 16:18:39  Darko           renamed
 *       m_strMembers to m_szMembers
 *  4    Biblioteka1.3         2003-08-17 02:16:01  Darko           Open() uses
 *       password
 *  3    Biblioteka1.2         2003-08-12 13:58:06  Darko           Error handling,
 *       Open(), Close()
 *  2    Biblioteka1.1         2003-08-07 17:16:24  Darko           Added draft
 *       Open()
 *  1    Biblioteka1.0         2003-08-05 18:12:11  Darko
 * $
 *****************************************************************************/
