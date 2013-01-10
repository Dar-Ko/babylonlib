/*$RCSfile: KMemFind.c,v $: implementation file
  $Revision: 1.1 $ $Date: 2013/01/10 17:51:22 $
  $Author: ddarko $

  Find an array of bytes within another array
  1999-02 Darko Kolakovic
*/

#include <memory.h>
#ifndef NULL
  #define NULL 0
#endif

//-----------------------------------------------------------------------------
/*Finds the first occurrence of an byte array within a block of memory.

  Returns the pointer to the first occurrence of a byte pattern in given data
  buffer or NULL if match is not found.
 */
void* MemFind(void* pSrc,           //[in] pointer to the starting address of the block of memory 
              const unsigned long nSrcSize, //[in] size of the block of memory, in bytes
              const void* pPattern, //[in] array to search for
              const unsigned long PatternSize //[in] size of the array to search for, in bytes
              )
{
long i = 0;

while(i <= (nSrcSize - PatternSize))
{
  if(memcmp((unsigned char*)pSrc + i, pPattern, PatternSize) == 0)
    {
    return (unsigned char*)pSrc + i;
    }
  i++;
}
return NULL;
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: KMemFind.c,v $
 * Revision 1.1  2013/01/10 17:51:22  ddarko
 * Added to repository
 *
 ******************************************************************************/
