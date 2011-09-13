/*$RCSfile: KVersion.h,v $: header file
  $Revision: 1.1 $ $Date: 2011/09/13 15:11:05 $
  $Author: ddarko $

  Module version number
 */

#ifndef _KVERSION_H_
  #define _KVERSION_H_

#ifndef _VER_MAJ
  #define _VER_MAJ   1
#endif
#ifndef _VER_MIN
  #define _VER_MIN   0
#endif
#ifndef _BUILDMAJ
  #define _BUILDMAJ  0
#endif
#ifndef _BUILDMIN
  #define _BUILDMIN  0
#endif

#define _KVERSIONSTR1_(V1, V2, V3, V4) #V1 "." #V2 "." #V3 "." #V4
#define _KVERSIONSTR_(V1, V2, V3, V4) _KVERSIONSTR1_(V1, V2, V3, V4)

#define _VERSION_STR _KVERSIONSTR_(_VER_MAJ, _VER_MIN, _BUILDMAJ, _BUILDMIN)
/*Note: Add target platform and build to Resources|General|Preprocessor Definitions
  (MSVC specific)
 */
#ifdef _DEBUG
  #ifdef _M_IX64
    #define _VERSION_SPECBUILD "Debug x64"
  #else
    #define _VERSION_SPECBUILD "Debug x86"
  #endif
#else
  #ifdef _M_IX64
    #define _VERSION_SPECBUILD "Release x64"
  #else
    #define _VERSION_SPECBUILD "Release x86"
  #endif
#endif

#endif /* _KVERSION_H_ */
