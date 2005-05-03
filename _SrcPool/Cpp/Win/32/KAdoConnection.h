/*$Workfile: KAdoConnection.h$: header file
  $Revision: 11$ $Date: 2005-04-26 11:28:13$
  $Author: Darko Kolakovic$

  Interface of the CAdoConnection class
  Copyright: CommonSoft Inc.
  2k3-08 Darko Kolakovic
 */
// Group=Windows

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KType32.h"  //ISO C99: 7.18 Integer types
#pragma warning( disable : 4290 )

/*KB259379 HOWTO: Develop with ADO Version 2.5 or Later and Install on
  ADO Version 2.0
  Errors are caused by new ActiveX Data Objects (ADO) interfaces that are
  referenced in the ADO 2.5 or later-produced image and that are not found
  in the Msado15.dll file on the target system.
 */
#if defined(ADO2_OLD)
  #pragma message( "Using ADO2 TLB <msado20.tlb>" )
  #import <msado20.tlb> no_namespace rename("EOF", "adoEOF")
#else
  #pragma message( "Using ADO 2.7 <msado15.dll>" )
  //Note: Add "C:\Program Files\Common Files\System\ADO" path to
  //VisualStudio|Tools|Options|Projects|VC++ Directories|Executable files
  #import <msado15.dll> no_namespace rename("EOF", "adoEOF")
#endif

///////////////////////////////////////////////////////////////////////////////
// List of ADO Connection Dynamic Property keywords
// ConnectionString Property indicates the information used to establish a
// connection to a data source.
// ADO supports five arguments for the ConnectionString property; any other
// arguments pass directly to the provider without any processing by ADO.
// The arguments ADO supports are as follows.
//
//      Argument         Description
//      Provider        - Specifies the name of a provider to use for
//                        the connection.
//      File Name       - Specifies the name of a provider-specific file
//                        (for example, a persisted data source object)
//                        containing preset connection information.
//      URL             - Specifies the connection string as an absolute URL
//                        identifying a resource, such as a file or directory.
//      Remote Provider - Specifies the name of a provider to use when opening
//                        a client-side connection. (Remote Data Service only.)
//      Remote Server   - Specifies the path name of the server to use when
//                        opening a client-side connection. (Remote Data Service
//                        only.)

//Specifies the name of a provider to use for the connection.
//Example:
//    _connection.Open("Provider=MS Remote;" \
//                     "Remote Provider=SQLOLEDB;" \
//                     "Remote Server=http://192.168.1.1;" \
//                     "Data Source=Products;" \
//                     "User Id=Admin;"\
//                     "Password=adminpswd;" );
#define ADO_CS_PROVIDER        _T("Provider=")
//Specifies the name of a provider to use when opening a client-side connection.
//(Remote Data Service only.)
#define ADO_CS_REMOTE_PROVIDER _T("Remote Provider=")
//Specifies the path name of the server to use when opening a client-side
//connection. (Remote Data Service only.)
#define ADO_CS_REMOTE_SERVER   _T("Remote Server=")
//Specifies the name of a provider-specific file (for example, a persisted
//data source object) containing preset connection information.
#define ADO_CS_FILE_NAME       _T("File Name=")
//Specifies the connection string as an absolute URL identifying a resource,
//such as a file or directory.
#define ADO_CS_URL             _T("URL=")

///////////////////////////////////////////////////////////////////////////////
//Microsoft OLE DB Provider for Microsoft Jet ConnectionString Property
//keywords list

//Specifies the OLE DB Provider for Microsoft Jet 4.0.
//Example:
//    _connection.Open("Provider=Microsoft.Jet.OLEDB.4.0;" \
//                     "Data Source=c:\test.mdb;" \
//                     "User Id=Admin;"\
//                     "Password=adminpswd;");
#define ADO_CS_PROVIDER_JET40     _T("Microsoft.Jet.OLEDB.4.0")
//Specifies the OLE DB Provider for Microsoft Jet 3.51.
#define ADO_CS_PROVIDER_JET351    _T("Microsoft.Jet.OLEDB.3.51")
//Specifies the database path and file name (for example, c:\test.mdb).
#define ADO_CSJET_FILE_NAME       _T("Data Source=")
//Specifies the user name. If this keyword is not specified, the string,
//"admin", is used by default.
#define ADO_CSJET_USER_ID         _T("User Id=")
//Specifies the user password. If this keyword is not specified, the empty string
//(""), is used by default.
#define ADO_CSJET_PASSWORD        _T("Password=")

///////////////////////////////////////////////////////////////////////////////
//Microsoft OLE DB Provider for ODBC ConnectionString Property
//keyword list

//Specifies the Microsoft OLE DB Provider for ODBC.
//Example:
//    _connection.Open(_T("Provider=MSDASQL;" \
//                        "DSN=TestDsnName;" \
//                        "UID=Admin;" \
//                        "PWD=adminpswd;");
#define ADO_CS_PROVIDER_ODBC_MSOLE   _T("MSDASQL")
//Specifies the Microsoft OLE DB Provider for Internet Publishing.
#define ADO_CS_PROVIDER_ODBC_MSOLEIP _T("MICROSOFT OLE DB PROVIDER FOR INTERNET PUBLISHING")
#define ADO_CS_PROVIDER_ODBC_MSDAIPP _T("MSDAIPP.DLL")
#define ADO_CS_PROVIDER_ODBC_JT      _T("ODBCJT32.DLL")

//Specifies the data source name (DSN).
#define ADO_CSODBC_DATA_SOURCE    _T("DSN=")
//Specifies the data source name (DSN).
#define ADO_CSODBC_FILE_NAME      _T("FileDSN=")
//Specifies the user name.
#define ADO_CSODBC_USER_ID        _T("UID=")
//Specifies the user password.
#define ADO_CSODBC_PASSWORD       _T("PWD=")
//Specifies the URL of a file or directory published in a Web folder.
#define ADO_CSODBC_URL            ADO_CS_URL
//Specifies the ODBC driver, if DNS is not to be used.
//Example:
//          "ODBC;" \
//          "DRIVER={Microsoft Access Driver (*.mdb)};" \
//          "DEFAULTDIR=%s;
//          "DBQ=%s
#define ADO_CSODBC_DRIVER       _T("DRIVER=")
//Specifies the server name, if DNS is not to be used.
#define ADO_CSODBC_SERVER       _T("SERVER=")
//Specifies the database name, if DNS is not to be used.
#define ADO_CSODBC_DATABASE       _T("DATABASE=")

//Microsoft Access ODBC driver name
#define ODBC_DRIVER_MSACCESS       _T("{Microsoft Access Driver (*.mdb)}")

//Specifies the database name
#define ADO_CSODBC_DATABASE_MSJET   _T("MS JET")
#define ADO_CSODBC_DATABASE_MSSQL   _T("MS SQL SERVER")
//Specifies Microsoft SQL Server database name
#define ADO_CSODBC_DATABASE_MSSQLS  _T("MICROSOFT SQL SERVER")
//Specifies Sybase SQL AnyWhere database name
#define ADO_CSODBC_DATABASE_SYSQL   _T("SYBASE SQL ANYWHERE")
//Specifies Adaptive Server AnyWhere database name
#define ADO_CSODBC_DATABASE_ADSER   _T("ADAPTIVE SERVER ANYWHERE")
//Specifies Sybase Open Server database name
#define ADO_CSODBC_DATABASE_SYOSER  _T("SQL SERVER")
//Specifies Oracle database name
#define ADO_CSODBC_DATABASE_ORACLE  _T("ORACLE")
//Specifies Visual FoxPro database name
#define ADO_CSODBC_DATABASE_VFOXPRO _T("VISUAL FOXPRO")

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Retrieves the 16-bit error code mapped into the encapsulated HRESULT.
  Result is ADO error code enum ErrorValueEnum.
  The Windows facility code for ADO error numbers is 0xA.

  Note: OLE DB errors with Windows facility code 0x4 may be passed to your
  ADO application.

  Note: Microsoft Windows specific (Win).

  Returns: ADO run-time error code, if the error number has ADO error facility
  code; otherwise, it returns zero.

  See also: ErrorValueEnum, ADO Error Codes, MAKE_HRESULT macro
 */
inline int GetAdoError(HRESULT hError //[in] error code
                                  )
{
return (int)(HRESULT_FACILITY(hError) != 0xA) ? 0 : (hError - 0x800A0000) ;
}

/*Retrieves the 16-bit error code mapped into the encapsulated _com_error error
  number.

  Returns: ADO run-time error code, if the error number has ADO error facility
  code; otherwise, it returns zero.

  Note: Microsoft Windows specific (Win32)

  See also: ADO API Reference:ErrorValueEnum
 */
inline int GetAdoError(_com_error& cee //[in] COM exception detected
                                   //by the error-handling functions
                                  )
{
return GetAdoError(cee.Error());
}

///////////////////////////////////////////////////////////////////////////////
//Class CAdoConnection creates a connection to a database using ActiveX Data
//Objects (ADO).
//ADO is a Microsoft data access technology that enables your client
//applications to access and manipulate data from a database server or any other
//data store through an OLE DB provider. ADO is a set of wrapper classes that
//are built on top of OLE DB interfaces.
//
//Creating a Connection String
//A connection string consists of a list of argument/value parameters:
//       ARG_KEYWORD=<value>;
//For example:
//      "arg1=val1; arg2=val2; ... argN=valN;"
//All the parameters must be recognized by either ADO or the specified provider.
//
//ADO recognizes the following five arguments in a connection string.
//      Provider        - Specifies the name of a provider to use for
//                        the connection.
//      File Name       - Specifies the name of a provider-specific file
//                        (for example, a persisted data source object)
//                        containing preset connection information.
//      URL             - Specifies the connection string as an absolute URL
//                        identifying a resource, such as a file or directory.
//      Remote Provider - Specifies the name of a provider to use when opening
//                        a client-side connection. (Remote Data Service only.)
//      Remote Server   - Specifies the path name of the server to use when
//                        opening a client-side connection. (Remote Data Service
//                        only.)
//
//Other arguments are passed to the provider named in the Provider argument,
//without any processing by ADO.
//
//Example:
//    m_strConnection = "Provider=SQLOLEDB;Data Source=MyServer;" \
//                       "Initial Catalog=Northwind;Integrated Security='SSPI';"
//    In this connection string, ADO recognizes only the "Provider=SQLOLEDB"
//    parameter, which specifies the Microsoft OLE DB Provider for SQL Server
//    as the ADO data source. The rest of the argument/value pairs,
//    "Data Source=MyServer; Initial Catalog=Northwind;Integrated Security='SSPI';",
//    are passed verbatim to this provider. The type and validity of such parameters
//    are provider-specific. For information on valid parameters that can be passed
//    in the connection string, consult the individual provider's documentation.
//
//According to the OLE DB Provider for SQL Server documentation, you can substitute
//"Server" for the Data Source parameter and "Database" for the Initial
//Catalog parameter.
//
//Note: uses Microsoft Foundation Library (MFC);
//      Microsoft ActiveX Data Objects (ADO).
//      Microsoft Windows specific (Win).
class CAdoConnection
{
public:
  CAdoConnection(void);
  virtual ~CAdoConnection(void);

  //TODO: Create constructor CAdoConnection(File, User, Pswd, enum Mode); D.K.
public:
  //the optional sharing and access modes.You can combine options listed below
  //by using the bitwise-OR (|) operator.
  enum Mode
    {
    modeRead      =0x01, //Opens the data source for reading only.
    modeWrite     =0x02, //Opens the data source for writing only.
    modeReadWrite =0x03, //Opens the data source for reading and writing.
    shareDenyRead =0x04, //Opens the data source and denies
                         //other processes read access to the data source.
    shareDenyWrite=0x08, //Opens the data source and denies
                         //other processes write access to the data source.
    shareExclusive=0x0C, //Opens the data source with
                         //exclusive mode, denying other processes both
                         //read and write access to the data source.
    shareDenyNone =0x10  //Opens the data source without denying
                         //other processes read or write
                         //access to the data source.
    };

public:
  //ADO dynamic properties
  static LPCTSTR m_szProvider;  //ADO dynamic property keyword for the name of
                                 //a provider used for the connection.
                                 //
                                 //Providers Example:
                                 //     MSDASQL     - Microsoft OLE DB Provider for ODBC
                                 //     MSDAORA     – Oracle
                                 //     SQLOLEDB    – Microsoft SQL Serve
                                 //     Microsoft.Jet.OLEDB.3.51
                                 //     Microsoft.Jet.OLEDB.4.0
                                 //     MS Remote

  static LPCTSTR m_szDataSource; //ADO dynamic property keyword for the
                                  //Data Source specifying the name of the
                                  //database to which to connect.
  static LPCTSTR m_szUserId;//ADO dynamic property keyword for user ID used
                             //when connecting to the data source.
  static LPCTSTR m_szPassword;//ADO dynamic property keyword for the Password
                               //used to set a password when connecting to
                               //a data source.
                               //Note: An application can also use the equivalent
                               //OLE DB Pwd keyword,
  static LPCTSTR m_szExtendedProperties; //ADO keyword for the
                    //Extended Properties dynamic property that sets or retrieves
                    //provider-specific connection information that cannot be
                    //explicitly described through the property mechanism.

  static LPCTSTR m_szMode;//OLE DB Initialization property keyword specifying
    //access permissions. A combination of zero or more
    //of the following property values:
    //
    //     OLE DB documented value  Short value
    //       DB_MODE_READ             Read              Read only.
    //       DB_MODE_WRITE            Write             Write only.
    //       DB_MODE_READWRITE        ReadWrite         Read and write.
    //       DB_MODE_SHARE_DENY_READ  Share Deny Read   Prevents others from opening in read mode.
    //       DB_MODE_SHARE_DENY_WRITE Share Deny Write  Prevents others from opening in write mode.
    //       DB_MODE_SHARE_EXCLUSIVE  Share Exclusive   Prevents others from opening in read/write mode.
    //       DB_MODE_SHARE_DENY_NONE  Share Deny None   Neither read nor write access can be denied to others.
    //

protected:
  CString m_strConnection; //A connection string consists of a list of
                           //argument/value pairs (that is, parameters),
                           //separated by semi-colons. For example:
                           //"arg1=val1; arg2=val2; ... argN=valN;"
                           //All the parameters must be recognized by
                           //either ADO or the specified provider.
  _ConnectionPtr m_pConnection; //Connection object representing a unique
                                //session with a data source

public:
  virtual bool Open(LPCTSTR szFileName,
            LPCTSTR szUserName = NULL,
            LPCTSTR szPassword = NULL,
            uint_fast32_t nOpenFlags = modeReadWrite | shareDenyNone);
  virtual bool Close();
  bool IsConnected() const;
  static int GetApartmentType();
  operator _ConnectionPtr();
  void SetTimeout(long lTimeout = 15);
  #ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
  #endif
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Validates connection status.

 Returns: true if Connection Object is connected to the data source; otherwise
 returns false.
 */
inline bool CAdoConnection::IsConnected() const
{
return ((m_pConnection != NULL) &&
        (m_pConnection->GetState() == adStateOpen));
}

//-----------------------------------------------------------------------------
/*Obtains the current Apartment type.

  Returns: current threading model (COINIT_MULTITHREADED or COINIT_APARTMENTTHREADED),
  or 0xFF if COM library is not initialized.
  Note: this is a static member

  See also: COINIT, PlatformSDK\Include\ObjBase.h
 */
inline int CAdoConnection::GetApartmentType()
{
const int COGET_NOT_INTIALIZED = 0xFF;

HRESULT hResult = CoInitialize(NULL);
if (SUCCEEDED(hResult))
  CoUninitialize();
if (hResult == S_FALSE)
  {
  return COINIT_APARTMENTTHREADED;
  }
  //Valid only on Windows NT 4.0+
#if ((_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) /*DCOM*/)
  else if (hResult == RPC_E_CHANGED_MODE)
    {
    return COINIT_MULTITHREADED;
    }
#endif
return COGET_NOT_INTIALIZED;
}

//-----------------------------------------------------------------------------
/*Cast operator.
 */
inline CAdoConnection::operator _ConnectionPtr()
{
return m_pConnection;
};

//-----------------------------------------------------------------------------
/*Sets value that indicates, in seconds, how long to wait for the connection
 to open. Use the ConnectionTimeout property on a Connection object if delays
 from network traffic or heavy server use make it necessary to abandon
 a connection attempt. If the time from the ConnectionTimeout property setting
 elapses prior to the opening of the connection, an error occurs and ADO cancels
 the attempt. If you set the property to zero, ADO will wait indefinitely until
 the connection is opened. Make sure the provider to which you are writing code
 supports the ConnectionTimeout functionality.

  The ConnectionTimeout property is read/write when the connection is closed and
  read-only when it is open.
 */
inline void CAdoConnection::SetTimeout(long lTimeout //[in]=15 period to wait for
                                                     //the connection to open [s]
                                       )
{
if (m_pConnection)
  {
  TRACE(_T("CAdoConnection::SetTimeout(%d[s])\n"),lTimeout);
  m_pConnection->PutConnectionTimeout(lTimeout);
  }
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  10   Biblioteka1.9         2003-11-03 13:16:01  Darko           Comment
 *  9    Biblioteka1.8         2003-09-11 16:57:10  Darko           comment
 *  8    Biblioteka1.7         2003-09-10 16:09:11  Darko           Added Dump()
 *  7    Biblioteka1.6         2003-08-24 14:03:19  Darko           GetAdoError()
 *  6    Biblioteka1.5         2003-08-19 16:18:40  Darko           renamed
 *       m_strMembers to m_szMembers
 *  5    Biblioteka1.4         2003-08-17 02:15:23  Darko           Open and Close
 *       are virtuals now
 *  4    Biblioteka1.3         2003-08-12 13:58:09  Darko           Error handling,
 *       Open(), Close()
 *  3    Biblioteka1.2         2003-08-09 17:42:37  Darko           Database names
 *  2    Biblioteka1.1         2003-08-07 17:16:26  Darko           Added draft
 *       Open()
 *  1    Biblioteka1.0         2003-08-05 18:12:13  Darko
 * $
 *****************************************************************************/
