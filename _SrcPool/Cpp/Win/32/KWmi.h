/*$RCSfile: KWmi.h,v $: header file
  $Revision: 1.8 $ $Date: 2010/02/04 23:31:10 $
  $Author: ddarko $

  Microsoft Windows Management Instrumentation (WMI) client.
  Copyright: Darko Kolakovic
  Darko Kolakovic  2010-01-15
*/
// Group=Windows

#ifndef _KWMI_H_
  //$RCSfile: KWmi.h,v $ sentry
  #define _KWMI_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <wbemidl.h> //Web-based Enterprise Management (WBEM) interfaces

/*WMI namespace part of the uniform resource identifier (URI).object path of
  the correct WMI namespace.

  See also: {html: <a href="http://msdn.microsoft.com/en-us/library/aa390342%28VS.85%29.aspx">
  MSDN: Describing a WMI Namespace Object Path</a> }
 */
#define NS_WMICIM     _T("root\\cimv2")
//Default WMI namespace used to construct uniform resource identifier (URI).object path.
//Note: Microsoft Windows NT 4.0 and Windows 98 are using this as default space
//for management
#define NS_WMIDEFAULT _T("root\\default")

///////////////////////////////////////////////////////////////////////////////
//Common WMI queries
//See also:   See also: Common Information Model (CIM) Specification Version 2.2 by
//Distributed Management Task Force, Inc; A.2 SQL Reserved Words 
//(http://www.dmtf.org/standards/cim/cim_spec_v22)


#define WQL_HWSYS _T("SELECT * FROM Win32_ComputerSystem") //ComputerSystem WMI class
#define WQL_OS    _T("SELECT * FROM Win32_OperatingSystem") //OperatingSystem WMI class
#define WQL_CPU   _T("SELECT * FROM Win32_Processor") //Processor WMI class
#define WQL_RAM   _T("SELECT * FROM Win32_PhysicalMemory") //PhysicalMemory WMI class
#define WQL_HDD   _T("SELECT * FROM Win32_DiskDrive") //DiskDrive WMI class
#define WQL_CDROM _T("SELECT * FROM Win32_CDROMDrive") //CDROMDrive WMI class (CD/DVD/BR ROM Drives)
#define WQL_TAPE  _T("SELECT * FROM Win32_TapeDrive") //TapeDrive WMI class
#define WQL_NET   _T("SELECT * FROM Win32_NetworkAdapter") //NetworkAdapter WMI class
#define WQL_SWAPP _T("SELECT * FROM Win32_Product") //Product WMI class
          //class (software applications which are accessible through Windows
          //'Control Panel'|'Add/Remove Programs' applet)
#define WQL_NET   _T("SELECT * FROM Win32_NetworkAdapter") //NetworkAdapter WMI class

/////////////////////////////////////////////////////////////////////////////
// CWmi is generic client to the Microsoft Windows Management Instrumentation
// (WMI) COM service. WMI provides a standardized system management
// infrastructure on Windows-based operating systems that can be leveraged by
// a number of different clients.
// WMI is based on the Common Information Model (CIM) schema class developed
// by Desktop Management Task Force (DMTF). All the WMI interfaces are based
// on the Component Object Model (COM).
//
// WMI will use Remote Procedure Call (RPC) service when accessing objects 
// remotely. RPC itself uses TCP ports 135 and 445. In addition to those, a 
// firewall have allow other ports allocated by DCOM dynamically.
//
// Note: Microsoft Windows 2000 specific (Win2k).
//       Requires the .NET Framework Redistributable.
//       Windows 2000 requires also  WMI Redistributable Components version 1.0.
//
// See also: {html: <a href = "http://msdn.microsoft.com/en-us/library/aa394582%28VS.85%29.aspx">
// MSDN: Windows Management Instrumentation</a>;<br />
// <a href="http://technet.microsoft.com/en-us/library/ee692772.aspx">
// Microsoft TechNet: Windows Management Instrumentation (WMI): Frequently Asked Questions</a>;<br />
// <a href="http://www.dmtf.org/standards/cim/">
// DMTF: Common Information Model (CIM) Standards</a> }
class CWmi
{
// Construction
public:
  CWmi();
  virtual ~CWmi();

// Attributes
public:

private:
  HRESULT m_hInitializeRes; //result of initialization of the COM library
  IWbemServices* m_pIWbemServices; //interface to WMI services

// Operations
public:
  bool IsConnected();
  bool Disconnect();
  bool Query(LPCTSTR szWqlQuery, const long nTimeOut = WBEM_INFINITE);

// Implementation
private:
  bool IsCoInitialized();

// Overrides
public:
  virtual bool Init(LPCTSTR szDeviceUri = NULL, 
                    LPCTSTR szUserName = NULL, 
                    LPCTSTR szPassword = NULL,
                    LPCTSTR szDomain = NULL);

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Validates if the COM library is initialized properly for use by the calling
  thread.
  Returns true if the COM library was initialized successfully on this thread.
 */
inline bool CWmi::IsCoInitialized()
{
//The COM library was initialized successfully on this thread or
//the COM library is already initialized on this thread.
//Note: Error RPC_E_CHANGED_MODE indicates that a previous call to CoInitializeEx
//set the concurrency model as multithread apartment (MTA), indicating change to
//single-threaded apartment.
return ((m_hInitializeRes == S_OK) ||
        (m_hInitializeRes == S_FALSE) );
}
///////////////////////////////////////////////////////////////////////////////
#endif  //_KWMI_H_
/*****************************************************************************
 * $Log: KWmi.h,v $
 * Revision 1.8  2010/02/04 23:31:10  ddarko
 * Update
 *
 * Revision 1.7  2010/02/03 23:21:11  ddarko
 * browse CIM properties
 *
 * Revision 1.6  2010/02/02 19:19:30  ddarko
 * WQL constats
 *
 * Revision 1.5  2010/02/01 22:28:07  ddarko
 * ExecQuery
 *
 * Revision 1.4  2010/01/29 22:47:47  ddarko
 * Query (simple)
 *
 * Revision 1.3  2010/01/27 22:41:27  ddarko
 * *** empty log message ***
 *
 * Revision 1.2  2010/01/26 22:47:05  ddarko
 * Initialization of WMI
 *
 * Revision 1.1  2010/01/25 20:02:29  ddarko
 * Created
 *
 *****************************************************************************/
