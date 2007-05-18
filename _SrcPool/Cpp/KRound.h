/*$Workfile: KRound.h$: header file
  $Revision: 2$ $Date: 2007-05-18 19:24:18$
  $Author: Darko Kolakovic$

  Rounding numbers

  D. Schemenauer Feb. 2000.	<dschemen@telus.net>
*/

#ifndef _KROUND_H_
  //$Workfile: KRound.h$ sentry
#define _KROUND_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////
/*Template function rounds a value by rate increments.
  Only absolute value of dRate is taken into account.

  Returns: a value closest to the multiple of the rate.

  Example:
      #include "KRound.h" //RoundBy()
      ...
      double dRes;
      //Round to the closest integer
      dRes = RoundBy (525.345, 1); //dRes = 525
      //Round to the closest increment of 1/8
      dRes = RoundBy (525.345, 0.125); //dRes = 525.375 = 525 + 3/8
      //Round with steps of 3/100
      dRes = RoundBy (525.345, 0.03); //dRes = 525.360
      //Currency rounding
      dRes = RoundBy (525.345, 0.01); //dRes = 525.35
      //Round by decrementing
      dRes = RoundBy (525.345, -.01); //dRes = 525.35
      //Round by thousands
      dRes = RoundBy (499.99, 1000);  //dRes = 0
*/
template <class TYPE>
TYPE RoundBy(const TYPE value, //[in] a number to be rounded
             double dRate = 1 //[in] = 1.0 rounding increment.
             //Default value 1.0 returns closest integer.
             )
{
if (dRate == 0)
  return 0; //Nothing todo: closest to 0 is 0
else if(dRate < 0)//Negative values of dRate cause error
  dRate *= -1; //Take abs(dRate)

int iIncrement;  //increment of the rate closest to the required value

if(value > 0)
  {
  iIncrement = (int)((value + dRate / 2) / dRate);
  return iIncrement * dRate;
  }
else if(value < 0)
  {
  iIncrement = (int)((value - dRate / 2) / dRate);
  return iIncrement * dRate;
  }
else
  return 0;
}
///////////////////////////////////////////////////////////////////////////////
#endif /* __cplusplus                                                        */
/* ///////////////////////////////////////////////////////////////////////// */
#endif /* _KROUND_H_                                                         */
/**********************NOTICE********************************
 This file is free for use or modification as required. If you
 improve upon it add your name, date & e-mail below.
 Then e-mail a copy to the previous authors.
 D. Schemenauer Feb. 2000.	<dschemen@telus.net>
************************************************************/
