/*$RCSfile: KLinBase.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/01/30 23:43:43 $
  $Author: ddarko $

  Constants used in conjuncture with Linux environment
  Copyright: D. Kolakovic
  2012-01-17
 */

#ifndef __KLINBASE_H__
  /*$RCSfile: KLinBase.h,v $ sentry */
  #define __KLINBASE_H__

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
    #warning ("   #include " __FILE__ )
  #endif

 #ifdef _UNICODE
   //TODO:
 #else  //single-byte
   #ifndef FillMemory
    /*Fills a block of memory with a specified value.
      Requires <string.h> header file.
      
      Example:
        #include <string.h>
        ...
        char array[256];
        FillMemory(array, 256, 'A');
     */
    #define FillMemory(dest, count, fill)    memset((dest),(fill),(count))
  #endif
  #ifndef ZeroMemory
    /*Fills a block of memory with zeros.
      Requires <string.h> header file.
      
      Example:
        #include <string.h>
        ...
        char array[256];
        ZeroMemory(array, 256);
     */
    #define ZeroMemory(dest, count)          memset((dest), 0, (count))
  #endif
  #ifndef MoveMemory
    /*Moves a copies of memory from one location to another. If some regions of 
      the source area and the destination overlap, it is ensured that the original
      source characters in the overlapping region are copied before being
      overwritten.
      Requires <string.h> header file.
      Parameters:
      - dest  Destination object. 
      - src   Source object. 
      - count Number of characters to copy. 
      
      Example:
        #include <string.h>
        ...
        char array[256];
        MoveMemory(array, &array[10], 20);
     */
    #define MoveMemory(dest, src, count)     memmove((dest), (src), (count))
  #endif
  #ifndef CopyMemory
    /*Copies a block of memory from one location to another.
      If the source and destination overlap, this function does not ensure that
      the original source characters in the overlapping region are copied before
      being overwritten. 
      Requires <string.h> header file.
     */
    #define CopyMemory(dest, src, count)     memcpy((dest), (src), (count))
  #endif
  #ifndef EqualMemory
    /*Compares content of two blocks of memory.
      Returns true if content is indetical, otherwise returns false.
      Requires <string.h> header file.
     */
    #define EqualMemory(dest, src, count)    (memcmp((dest), (src), (count)) == 0)
  #endif
#endif //_UNICODE

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*__KLINBASE_H__*/
/*****************************************************************************
 * $Log: KLinBase.h,v $
 * Revision 1.1  2012/01/30 23:43:43  ddarko
 * Created
 *
 *****************************************************************************/
