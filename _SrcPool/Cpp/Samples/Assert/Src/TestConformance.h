/*$Workfile: TestConformance.h$: header file
  $Revision: 2$ $Date: 2004-11-23 13:05:20$
  $Author: Darko Kolakovic$

  Validates the conformance of a C++ compiler
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/
/* Group=Examples                                                            */

#ifndef _TESTCONFORMANCE_H_
    /*$Workfile: TestConformance.h$ sentry */
  #define _TESTCONFORMANCE_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/* ////////////////////////////////////////////////////////////////////////// */
#ifdef __cplusplus /*C++ compilation                                          */

  #undef HAS_NO_CONST_CAST        //operator const_cast is supported
  #undef HAS_NO_STATIC_CAST       //operator static_cast is supported
  #undef HAS_NO_REINTERPRET_CAST  //operator reinterpret_cast is supported
  #undef HAS_NO_DYNAMIC_CAST      //operator dynamic_cast is supported
  #undef HAS_NO_NAMESPACE_KEYWORD //keyword namespace is supported
  #undef HAS_NO_TYPENAME_KEYWORD  //keyword typename is supported
  #undef HAS_NO_EXPLICIT_KEYWORD  //keyword explicit is supported
  #undef HAS_NO_MUTABLE_KEYWORD   //keyword mutable is supported

////////////////////////////////////////////////////////////////////////////////
#else /*!_cplusplus  C compilation                                            */
  #pragma message ("   C compilation " __FILE__ )
#endif /*_cplusplus                                                           */


/* ////////////////////////////////////////////////////////////////////////// */
#endif /*_TESTCONFORMANCE_H_ */
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-22 16:47:13  Darko Kolakovic
 * $
 *****************************************************************************/
