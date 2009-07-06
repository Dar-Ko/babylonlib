/*$RCSfile: StdUsb.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/07/06 19:00:10 $
  $Author: ddarko $

  Source file that intializes USB specific GUID.
 */

// Group=Examples

#include "stdafx.h"

#ifdef _WIN32
  #include <initguid.h> //INITGUID definition.
  //See also: MSDN Article ID: 130869 "How to avoid error 'LNK2001 unresolved external'
  //by using DEFINE_GUID"

  #ifdef _USE_MSWINDDK
    //USB specific GUID; Microsoft Windows DDK
    #pragma include_alias( "UsbGuid.h", "wxp/usbiodef" )
  #endif

  #include "UsbGuid.h" //USB specific GUID
#endif //_WIN32
