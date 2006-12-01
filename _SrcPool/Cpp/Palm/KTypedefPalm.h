/*$Workfile: KTypedefPalm.h$: header file
  $Revision: 4$ $Date: 2004-11-09 14:11:55$
  $Author: Darko Kolakovic$

  PalmOS type definitions
  Copyright: CommonSoft Inc
  2004-11-04 Darko Kolakovic
 */

#ifndef _KTYPEDEFPALM_H_
  /*$Workfile: KTypedefPalm.h$ sentry*/
  #define _KTYPEDEFPALM_H_

#if __MWERKS__ >= 0x3000
  #pragma once
#endif //__MWERKS__ >= 0x3000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* // PalmOS 32-bit                                                          */

#if defined(__PALMOS__) || defined (__PALMOS_H__)
  #include <PalmTypes.h>

  #if !defined(_PALMOS)
    #define _PALMOS PALMOS_SDK_VERSION      /*Palm OS */
  #endif

  #ifdef CPU_TYPE
    #if (CPU_TYPE == CPU_68K)
      #define __NATIVE_32_BIT__ CPU_TYPE
    #elif (CPU_TYPE == CPU_PPC)
      #define __NATIVE_32_BIT__ CPU_TYPE
    #elif (CPU_TYPE == CPU_ARM)
      #define __NATIVE_32_BIT__ CPU_TYPE
    #elif (CPU_TYPE == CPU_x86)
      #define __NATIVE_32_BIT__ CPU_TYPE
    #else
       #error "Not a 32-bit system, update stdint.h"
    #endif
  #endif

  #if defined(__IRLIB_H__)
    #define BOOL BOOL      /*PalmOS has typedef int BOOL in IrLib.h,    */
  #endif

  #include "KTCharPalm.h"

/* ///////////////////////////////////////////////////////////////////////// */
#else
  #error "Included PalmOS specfic header file."
#endif /*__PALMOS__*/

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KTYPEDEFPALM_H_*/
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-04 16:45:14  Darko Kolakovic
 * $
 *****************************************************************************/
