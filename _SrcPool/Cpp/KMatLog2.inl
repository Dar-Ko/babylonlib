/*$Workfile: KMatLog2.inl$: header file
  $Revision: 5$ $Date: 1/29/02 3:40:46 PM$
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
 *  5    Biblioteka1.4         1/29/02 3:40:46 PM   Darko           Tag update
 *  4    Biblioteka1.3         7/20/01 12:58:20 AM  Darko           VSS tags
 *  3    Biblioteka1.2         7/11/01 10:51:53 PM  Darko           
 *  2    Biblioteka1.1         6/8/01 11:51:03 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:56:47 PM   Darko           
 * $
 *****************************************************************************/
