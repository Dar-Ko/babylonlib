/*$Workfile: KDbgStlA.h$: header file
  $Revision: 2$ $Date: 2003-08-07 17:19:30$
  $Author: Darko$

  Dumps values of every element of an STL array
  Copyright: CommonSoft Inc.
  Darko Kolakovic 2003-02
*/
/* Group=Diagnostic                                                          */

#ifndef __KDBGSTLA_H__
    //KDbgStlA.h sentry
  #define __KDBGSTLA_H__

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#include "KTrace.h" //TRACE macro

//DumpStlArray()---------------------------------------------------------------
/*Dumps all elements of an array.

  Note: uses Standard Template Library (STL).
 */
template<class STLARRAY>
void DumpStlArray(const STLARRAY& Array //[in] An array inherited from STL
                 )
{
typename STLARRAY::const_iterator itEnd = Array.end();
typename STLARRAY::const_iterator itPos = Array.begin();

while (itPos != itEnd)
  {
  TRACE0(to_string(*itPos).c_str());
  itPos++;
  }
}

///////////////////////////////////////////////////////////////////////////////
#endif //__KDBGSTLA_H__
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2003-08-07 17:19:30  Darko           Comment
 *  1    Biblioteka1.0         2003-01-30 22:38:44  Darko           
 * $
 *****************************************************************************/
