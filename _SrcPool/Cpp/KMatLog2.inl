/*$Workfile: KMatLog2.inl$: header file
  $Revision: 5$ $Date: 29/01/2002 2:40:46 PM$
  $Author: Darko$

  Base 2 Logarithm
  Copyright: CommonSoft Inc.
  Nov 1990 D. Kolakovic
  May 95 C++ D.K.
 */
 
// Group=Mathematics

#ifndef _KMATLOG2_INL_
  //KMatLog2.inl sentry
  #define _KMATLOG2_INL_

#include "KMathCst.h" //CST_LN2
//log2()-----------------------------------------------------------------------
/*The log2 function return the logarithm of n for base 2 if successful. 
  If n is negative, function return an indefinite (IND). If n is 0, returns 
  infinite (INF). 
 */
template <class TYPE> 
inline TYPE log2(TYPE n //argument can be any valid numeric expression greater than 0
                 )
{
return log((double)n) / CST_LN2;
}

/*If n is  negative, the function returns -1.
 */
inline int log2(int n //argument can be any valid numeric expression greater than 0
                )
{
int iLog = -1;
while(TRUE)
	{
	if (n == 0)
    break;
	n = n >> 1;
	iLog++;
	}
return iLog;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_KMATLOG2_INL_

/*///////////////////////////////////////////////////////////////////////////*/
/******************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         29/01/2002 2:40:46 PMDarko           Tag update
 *  4    Biblioteka1.3         19/07/2001 11:58:20 PMDarko           VSS tags
 *  3    Biblioteka1.2         11/07/2001 9:51:53 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:51:03 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:56:47 PMDarko           
 * $
 *****************************************************************************/
