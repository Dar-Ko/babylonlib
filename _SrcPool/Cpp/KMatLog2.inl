/*$Workfile: KMatLog2.inl$: header file
  $Revision: 6$ $Date: 2003-08-22 15:59:00$
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
inline TYPE log2(TYPE n //[in] argument can be any valid numeric expression
                        //greater than 0
                 )
{
return log((double)n) / CST_LN2;
}

/*If n is  negative, the function returns -1.
 */
inline int log2(int n //[in] argument can be any valid numeric expression
                      //greater than 0
                )
{
int iLog = -1;
while(true)
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
 *  6    Biblioteka1.5         2003-08-22 15:59:00  Darko           comment
 *  5    Biblioteka1.4         2002-01-29 14:40:46  Darko           Tag update
 *  4    Biblioteka1.3         2001-07-19 23:58:20  Darko           VSS tags
 *  3    Biblioteka1.2         2001-07-11 21:51:53  Darko           
 *  2    Biblioteka1.1         2001-06-08 22:51:03  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 14:56:47  Darko           
 * $
 *****************************************************************************/
