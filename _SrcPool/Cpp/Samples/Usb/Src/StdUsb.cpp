/*$RCSfile: StdUsb.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/07/02 21:44:37 $
  $Author: ddarko $

  Source file that intializes USB specific GUID.
 */

// Group=Examples

#include "stdafx.h"

#ifdef _WIN32
  #include <initguid.h>
  //See also: MSDN Article ID: 130869 "How to avoid error 'LNK2001 unresolved external'
  //by using DEFINE_GUID"
  #define INITGUID 20090702

  #ifdef _USE_MSWINDDK
    //USB specific GUID; Microsoft Windows DDK
    #pragma include_alias( "UsbGuid.h", "wxp/usbiodef" )
  #endif

  #include "UsbGuid.h" //USB specific GUID
#endif //_WIN32
