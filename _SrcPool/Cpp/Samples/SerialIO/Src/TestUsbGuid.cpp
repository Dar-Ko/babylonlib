/*$Workfile: S:\_SrcPool\Cpp\Samples\SerialIO\Src\TestUsb.cpp$: implementation file
  $Revision: 1$ $Date: 2007-08-24 17:31:10$
  $Author: Darko Kolakovic$

  Initialize GUID constants.
  Copyright: CommonSoft Inc.
  2007-08-02 Darko Kolakovic
*/

// Group=Examples

/*Initialize GUID constants by by using DEFINE_GUID.
  Macro INITGUID have to be defined before OBJBASE.H (OBJBASE.H is 
  included by OLE2.H). 
  Note: the INITGUID.H header file is not used becouse the precompiled header
  is not included with USB handlers.

  See also: MSDN Article ID: 130869 "How to avoid error 'LNK2001 unresolved
  external'by using DEFINE_GUID"
*/
#define INITGUID

#include <objbase.h>

#include <usbiodef.h> //Initialization of the USB specific GUID; Windows DDK
#include <devguid.h>  //Initialization of the USB specific GUID; Windows DDK
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-08-24 17:31:10  Darko Kolakovic 
 * $
 *****************************************************************************/
