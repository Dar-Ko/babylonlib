/*$Workfile: KPhysCst.h$: header file
  $Revision: 5$ $Date: 1/25/02 3:57:29 PM$
  $Author: Darko$

  Physics Constants
  Copyright: CommonSoft Inc
  Jan. 96  D. Kolakovic
 */

#ifndef _KPHYSCST_H_
    //KPhysCst.h sentry
  #define _KPHYSCST_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//-----------------------------------------------------------------------------
// Group=Constants

  //Temperature of 0°C in [K]
#define CST_0C_TO_K  273.15
  //Speed of light in vacuum [m/s]
#define CST_c        299792458.
  //Acceleration due to gravity at sea level, 45° latitude [m/s2]
#define CST_g        9.806194

//Conversion factors-----------------------------------------------------------

  //decibel per neper
  //      [dB]/[Np] = 20*log(e) = 20/ln(10).
  //Neper is a unit for comparing of two amplitudes, equal to the logarithm
  //of the ratio of the two amplitudes
  //      A[Np] = ln(V/Vref).
  //[named after John Napier(1550-1617)]
#define CST_dBpNp  8.6858896380650365530225783783321
///////////////////////////////////////////////////////////////////////////////
// Template functions
// Group=

#ifdef __cplusplus

//VpV2dB()---------------------------------------------------------------------
/*Converts Voltage attenuation [V/V] to decibels.

    A[B] = 10*A[dB] = 10*log(P/Pref) = 10*log((V/Vref)**2) = 20*log(V/Vref)[dB]
*/
template <class TYPE> inline TYPE VpV2dB(const TYPE& fV,const TYPE& fVref)
  {
  ASSERT(fVref != (TYPE)0);
  return (TYPE)(20. * log10((double)fV/(double)fVref) );
  };

//WpW2dB()---------------------------------------------------------------------
/*Converts Power attenuation [W/W] to decibels [dB].
  One dB is equal to ten times the logarithm of the ratio of the power
  (or sound intensity) measured after and before attenuator.

  A[B] = 10*A[dB] = 10*log(P/Pref)[dB]
 */
template <class TYPE> inline TYPE WpW2dB(const TYPE& fP,const TYPE& fPref)
  {
  ASSERT(fPref!= (TYPE)0);
  return (TYPE)(10. * log10((double)fP/(double)fPref) );
  };

//dB2Vratio()------------------------------------------------------------------
/*Converts decibels to voltage attenuation*/
template <class TYPE> inline TYPE dB2Vratio (const TYPE& fdB)
  {
  return (TYPE)pow(10.,((double)fdB/20.));
  };

//dB2Wratio()------------------------------------------------------------------
/*Converts decibels to power attenuation*/
template <class TYPE> inline TYPE dB2Wratio (const TYPE& fdB)
  {
  return (TYPE)pow(10.,((double)fdB/10.));
  };

//dB2Np()----------------------------------------------------------------------
/*Converts signal attenuation given in decibels to signal ratio in nepers.
  Usually  used in conjunction with hyperbolic trigonometric functions.

  A[Np] = A[dB]/CST_dBpNp = A[dB]/(20* log(e))
 */
template <class TYPE> inline TYPE dB2Np (const TYPE& fdB //attenuation [dB]
                                        )
  {
  return (fdB/CST_dBpNp);
  };


#endif  //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KPHYSCST_H_
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         1/25/02 3:57:29 PM   Darko           Updated
 *       comments
 *  4    Biblioteka1.3         8/19/01 10:54:11 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 9:51:59 PM   Darko           
 *  2    Biblioteka1.1         6/8/01 10:51:12 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:56:55 PM   Darko           
 * $
 *****************************************************************************/
