/*$Workfile: KTString.h$: header file
  $Revision: 1$ $Date: 2004-12-20 14:26:32$
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


///////////////////////////////////////////////////////////////////////////////
#endif  //_KTSTRING_H_

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-12-20 14:26:32  Darko Kolakovic 
 * $
 *****************************************************************************/
