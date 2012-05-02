/*$RCSfile: KVersion.c,v $: implementation file
  $Revision: 1.3 $ $Date: 2012/05/02 13:57:27 $
  $Author: ddarko $

  Module version information.
  Copyright: CommonSoft Inc.
  2008-12-12 Darko Kolakovic
 */
#if defined (__linux) || defined (_LINUX) || defined (LINUX)
#include "version.h"
#ifndef _KEXPORTDECL
  #include "KProgCstLin.h"
#endif
#ifndef lint
  #ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wunused-variable"
  #endif
  static char *rcsid = "@(#)$Id: KVersion.c,v 1.3 2012/05/02 13:57:27 ddarko Exp $";
#endif /* not lint */

const char* g_szVersion = _VERSION_STR; //descriptive version number

//-----------------------------------------------------------------------------
/*Returns module version number in following format:
   release number, minor release number, build  release number, patch release number.
 */
_KEXPORTDECL const char* GetVersion()
{
return g_szVersion;
}

//-----------------------------------------------------------------------------
/*Returns module version number in following format:
   release number, minor release number, build  release number, patch release number.
 */
_KEXPORTDECL unsigned int GetVersionNumber()
{
//major release number, minor release number, build  release number, patch release number
//Note: architecture dependant
#define MAKEVER(d, c, b, a)  \
               (((unsigned int) ((unsigned char)((unsigned int)(a) & 0xff))      ) |\
                ((unsigned int) ((unsigned char)((unsigned int)(b) & 0xff)) <<  8) |\
                ((unsigned int) ((unsigned char)((unsigned int)(c) & 0xff)) << 16) |\
                ((unsigned int) ((unsigned char)((unsigned int)(d) & 0xff)) << 24))
                            

unsigned int nVersion;
nVersion = MAKEVER(_VER_MAJ, _VER_MIN, _BUILDMAJ, _BUILDMIN);
return nVersion;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_LINUX
/*****************************************************************************
 * $Log: KVersion.c,v $
 * Revision 1.3  2012/05/02 13:57:27  ddarko
 * *** empty log message ***
 *
 * Revision 1.2  2012/03/09 20:29:23  ddarko
 * GNU C++
 *
 * Revision 1.1  2012/02/02 18:14:10  ddarko
 * Retrieved form defunct repository
 *
 *****************************************************************************/
