/*$Workfile: KMatPerc.cpp$: implementation file
  $Revision: 3$ $Date: 2005-06-08 16:14:44$
  $Author: Darko Kolakovic$

  percent
  Copyright: CommonSoft Inc.
  May 89 C Version Darko Kolakovic
 */


/* Group=Mathematics                                                          */


/*percent()-------------------------------------------------------------------*/


/*Computes the percentage of total value. Percentage is a fraction or ratio
  expressed in hundredths. The symbol % used to indicate percent.

        percentage[%] = (dAmount/dTotal)* 100

  Note: this implementation calculates percentage of absolute values.

  Returns: proportion of dAmount and dTotal value, multiplied by 100.
  The range of the number returned is [0.0, 100.0]%.
 */
double percent(double dAmount, /*[in] portion of the whole*/
               double dTotal   /*[in] whole amount*/
              )
{
if(dTotal < 0.0)
  dTotal = -dTotal;
if(dAmount < 0.0)
  dAmount = -dAmount;

return (dAmount/dTotal) * 100.0;

}


/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-04-19 19:00:07  Darko Kolakovic
 * $
 *  0   May 89 "C" Version D.K.
 *****************************************************************************/
