/*$Workfile: KDbgMemHeap.cpp$: header file
  $Revision: 3$ $Date: 2004-11-12 13:57:50$
  $Author: Darko Kolakovic$

  Dumps memory resource information
  Copyright: CommonSoft Inc.
  2004-11-05 Darko Kolakovic
 */

/* Group=Diagnostic                                                          */

#include <PalmOS.h>
#include <MemoryMgr.h>
#include <stdint.h>

void DumpMemHeap(void);

//-----------------------------------------------------------------------------
/*Dumps information about memory heap used by the system.

  Note: Palm OS specific (PalmOS).
 */
void DumpMemHeap(void)
{
#ifndef memHeapFlagReadOnly
  const uint16_t memHeapFlagReadOnly = 0x0001; //ROM-based heap bit mask
#endif

const uint16_t CARD_NO = 0; //the card number; either 0 or 1.
uint16_t nHeaps; //number of heaps available, including ROM and RAM heaps
uint16_t i = 0;

 //Get the number of heaps available on a particular card
nHeaps = MemNumHeaps(CARD_NO);

while(i < nHeaps)
  {
    //Get the heap ID for a heap, given its index and the card number
  const uint16_t nHeapId = MemHeapID(CARD_NO, i);
    /*Get the heap flags for a heap. The flags can be examined to determine
      if the heap is ROM based or not. ROM-based heaps have
      the memHeapFlagReadOnly = 0x01 bit set.
     */
  uint16_t nRom = MemHeapFlags(nHeapId) & memHeapFlagReadOnly;
    //Get the total size of a heap including the heap header
  uint32_t nSize = MemHeapSize(nHeapId);
    /*Get the total number of free bytes in a heap and the size of the largest
      free chunk in the heap.
     */
  uint32_t nAvailable;
  uint32_t nAvailableChunk;
  MemHeapFreeBytes(nHeapId, &nAvailable, &nAvailableChunk);

  TRACE3(_T("Heap %d: %s allocated %d,"),
         i,
         (nRom == 0) ? _T("RAM") : _T("ROM"),
         nSize
        );
  TRACE2(_T(" free %d (largest chunk %d) bytes.\n"),
         nAvailable,
         nAvailableChunk
        );
  i++;
  }
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-11-09 18:46:00  Darko Kolakovic implemented
 *       TsWriteToViewLn
 *  1    Biblioteka1.0         2004-11-05 12:25:09  Darko Kolakovic
 * $
 *****************************************************************************/
