/*$Workfile: KChecksum.h$: header file
  $Revision: 1.3 $ $Date: 2003/01/28 04:15:24 $
  $Author: ddarko $

  Calculates a checksum
  Copyright: CommonSoft Inc
  Apr. 2k2 D.Kolakovic
 */

#ifndef __KCHECKSUM_H__
  //KChecksum.h sentry
  #define __KCHECKSUM_H__

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Interface for calculating a checksum from given array of bytes.
class CChecksum
{
public:
    /**
     * Updates the current checksum with the specified byte.
     */
    void update(int b) = 0;

    /**
     * Updates the current checksum with the specified array of bytes.
     */
    void update(byte[] b, int off, int len) = 0;

    /**
     * Returns the current checksum value.
     */
    long getValue() = 0;

    /**
     * Resets the checksum to its initial value.
     */
    void reset() = 0;

};

///////////////////////////////////////////////////////////////////////////////
#endif  //__KCHECKSUM_H__
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         16/07/2002 12:40:50 AMDarko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         09/04/2002 12:18:27 PMDarko Kolakovic 
 *$
 *****************************************************************************/
