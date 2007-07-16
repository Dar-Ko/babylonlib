/*$Workfile: KTString.h$: header file
  $Revision: 3$ $Date: 2007-07-16 18:04:23$
  $Author: Darko Kolakovic$

  STL string helper functions
  Copyright: CommonSoft Inc.
  2004-12-20 Darko Kolakovic
*/

/* Group=Strings                                                             */
#ifndef _KTSTRING_H_
    //$Workfile: KTString.h$ sentry
  #define _KTSTRING_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#ifndef TCHAR
  #include "KTChar.h"  //TCHAR definition
#endif

/*The class based for handling TCHAR string objects.

  Note: uses Standard Template Library (STL).

  See also: TCHAR, KTChar.h, std::string
 */
typedef std::basic_string<TCHAR> tstring;

/*Single byte character set
 */
typedef std::basic_string<UCS1> ucs1string;
/*Universal Character Set UCS-2 string.
  UCS-2 characters are the subset of Unicode set equal to the Basic Multilingual 
  Plane. Characters are 16 bit wide
  See also: ISO 10646-1:1993
 */
typedef std::basic_string<UCS2> ucs2string;
/*Universal Character Set UCS-4 string has characters 32-bit wide.
  See also: ISO 10646
*/
typedef std::basic_string<UCS4> ucs4string;

///////////////////////////////////////////////////////////////////////////////
#endif  //_KTSTRING_H_

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2007-07-16 18:04:23  Darko Kolakovic Universal
 *       Character Set format
 *  2    Biblioteka1.1         2007-06-15 17:25:47  Darko Kolakovic  
 *  1    Biblioteka1.0         2004-12-20 15:26:32  Darko Kolakovic 
 * $
 *****************************************************************************/
