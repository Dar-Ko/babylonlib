/*$RCSfile: KWmi.h,v $: header file
  $Revision: 1.2 $ $Date: 2010/01/26 22:47:05 $
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


/////////////////////////////////////////////////////////////////////////////
// CWmi is generic client to the Microsoft Windows Management Instrumentation
// (WMI) COM service. WMI provides a standardized system management 
// infrastructure on Windows-based operating systems that can be leveraged by
// a number of different clients.
// WMI is based on the Common Information Model (CIM) schema class developed
// by Desktop Management Task Force (DMTF). All the WMI interfaces are based
// on the Component Object Model (COM).
//
// Note: Microsoft Windows 2000 specific (Win2k).
//       Requires the .NET Framework Redistributable.
//       Windows 2000 requires also  WMI Redistributable Components version 1.0.
//
// See also: {html: <a href = "http://msdn.microsoft.com/en-us/library/aa394582%28VS.85%29.aspx">
// MSDN: Windows Management Instrumentation</a>, 
class CWmi
{
// Construction
public:
  CWmi();
  virtual ~CWmi();

// Attributes
public:

private:

// Operations
public:
  bool Init(LPCTSTR lpstrDevice = NULL);
  bool IsConnected();
  bool Disconnect();

// Implementation
public:

// Overrides
public:
};

/////////////////////////////////////////////////////////////////////////////
// Inlines

/////////////////////////////////////////////////////////////////////////////
#endif  //_KWMI_H_
/*****************************************************************************
 * $Log: KWmi.h,v $
 * Revision 1.2  2010/01/26 22:47:05  ddarko
 * Initialization of WMI
 *
 * Revision 1.1  2010/01/25 20:02:29  ddarko
 * Created
 *
 *****************************************************************************/
