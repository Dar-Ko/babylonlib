/*$Workfile: KDbgLimits.cpp$: header file
  $Revision: 2$ $Date: 2004-11-05 13:26:41$
  $Author: Darko Kolakovic$

  Dumps values of some constants defined in <limits>
  Copyright: CommonSoft Inc.
  2004-08-31 Darko Kolakovic
 */

#include "KOStream.h" //ostream template. See <iostream>
#include <limits>
#include <string>

#ifndef __cplusplus
  #error STL requires C++ compilation (use a .cpp suffix)
#endif

/* Group=Diagnostic                                                          */

//-----------------------------------------------------------------------------
/*Dumps values of some flags and prototype limits used in STL. Requires
  <limits> header file.

  Note: uses Standard Template Library (STL).
 */
void DumpLimits()
{
typedef _tcerr DbgOut;

/*The boolalpha flag defines the format used to read or to write Boolean
  values. The flag is not set by default and values are represented using
  as the value 0 for false and the value 1 for true.
  If the flag is set, values are written or read as stream's locale text
  representing.true or false.
  The standard "C" locale object uses the strings "true" and "false" as
  representations of the Boolean values.

  The special manipulators boolalpha and noboolalpha forces textual or
  numeric representation.

  Example:

        bool bValue;
        cout << noboolalpha << bValue<< " == " << boolalpha << bValue << endl;
 */

DbgOut << _T("Boolean representation: ") << (boolalpha ? _T("numeric") :
                                                         _T("text"))
                                         << std::endl;
DbgOut << boolalpha << 1 << _T(" == ") << noboolalpha << 1<< endl;
DbgOut << boolalpha << 0 << _T(" == ") << noboolalpha << 0<< endl;

 //Prototype limits
DbgOut << _T("short:      [") << numeric_limits<short>::min()       << _T(',')
                              << numeric_limits<short>::max()       << _T(']')
                              << endl;
DbgOut << _T("int:        [") << numeric_limits<int>::min()         << _T(',')
                              << numeric_limits<int>::max()         << _T(']')
                              << endl;
DbgOut << _T("long:       [") << numeric_limits<long>::min()        << _T(',')
                              << numeric_limits<long>::max()        << _T(']')
                              << endl;
DbgOut << _T("float:      [") << numeric_limits<float>::min()       << _T(',')
                              << numeric_limits<float>::max()       << _T(']')
                              << endl;
DbgOut << _T("double:     [") << numeric_limits<double>::min()      << _T(',')
                              << numeric_limits<double>::max()      << _T(']')
                              << endl;
DbgOut << _T("long double:[") << numeric_limits<long double>::min() << _T(',')
                              << numeric_limits<long double>::max() << _T(']')
                              << endl;
DbgOut << endl;

//char type
DbgOut << _T("char: ") << (numeric_limits<char>::is_signed ? _T(" signed") :
                                                             _T(" not signed") )
                       << endl;
DbgOut << endl;

//string size limit
DbgOut << "string: " << (numeric_limits<string>::is_specialized ?
                                  _T(" size is limited") :
                                  _T(" size is not limited") )
       << endl;
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-09-07 15:48:48  Darko
 * $
 *****************************************************************************/
