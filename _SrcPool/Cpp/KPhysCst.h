/*$Workfile: KPhysCst.h$: header file
  $Revision: 7$ $Date: 2003-09-11 15:58:02$
  $Author: Darko$

  Physics - Constants
  Copyright: CommonSoft Inc
  Jan. 96  D. Kolakovic
 */

#ifndef _KPHYSCST_H_
    //$Workfile: KPhysCst.h$ sentry
  #define _KPHYSCST_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//-----------------------------------------------------------------------------
// Group=Constants

  //Temperature of 0°Celsius in [K]
#define CST_0C2K  273.15
  //Speed of light in vacuum [m/s]
#define CST_c        299792458.
  //Acceleration due to gravity at sea level, 45° latitude [m/s2]
#define CST_g        9.806194

//Astronomical constants

  //Radius of Earth [km]
#define CST_TERRADIAMETER           6378.16
  //Eccentricity of Earth's orbit
#define CST_TERRAECC                0.016718
  //Semi-major axis of Earth's orbit [km]
#define CST_TERRAORBITSEMIMAX       1.495985e8
  //Sun's angular size from Earth at semi-major axis distance[o]
#define CST_TERRASUNANGULARSIZE     0.533128
  //Moon's angular size from Earth
#define CST_TERRALUNAANGULARSIZE    0.5181
  //Moon's parallax from Earth
#define CST_TERALUNAPARALLAX        0.950700

  //Inclination of the Moon's orbit
#define CST_LUNAORBITINCLINATION    5.145396
  //Eccentricity of the Moon's orbit
#define CST_LUNAECC                 0.054900
  //Semi-major axis of Moon's orbit [km]
#define CST_LUNAORBITSEMIMAX        384401.0
  //Synodic month (new Moon to new Moon) [days]
#define CST_SYNODISMONTH            29.53058868

//Conversion factors-----------------------------------------------------------

  //Decimal multiples

#define CST_yotta   1.0e+24
#define CST_zetta   1.0e+21
#define CST_exa     1.0e+18
#define CST_peta    1.0e+15
#define CST_tera    1.0e+12
#define CST_giga    1.0e+09
#define CST_mega    1.0e+06
#define CST_kilo    1000
#define CST_hecto    100
#define CST_deka      10
#define CST_deci    1.0e-01
#define CST_centi   1.0e-02
#define CST_milli   1.0e-03
#define CST_micro   1.0e-06
#define CST_nano    1.0e-09
#define CST_pico    1.0e-12
#define CST_femto   1.0e-15
#define CST_atto    1.0e-18
#define CST_zepto   1.0e-21
#define CST_yocto   1.0e-24

  //No name units

#define CST_PERCENT = 1.0/100.0; //one one-hundredth part [%]
#define CST_PERMILL = 1.0/1000.0;//one one-thousandth part[‰]=ANSI(TTF)137

  //Time

const double CST_SpMIN = 60.0; //second per minute
const double CST_MINpH = 60.0; //minute per hour
const double CST_HpDAY = 24.0; //hours per day


  /*decibel per neper
          [dB]/[Np] = 20*log(e) = 20/ln(10).
    Neper is a unit for comparing of two amplitudes, equal to the logarithm
    of the ratio of the two amplitudes
          A[Np] = ln(V/Vref).
    [named after John Napier(1550-1617)]
   */
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
 *  5    Biblioteka1.4         25/01/2002 3:57:29 PMDarko           Updated
 *       comments
 *  4    Biblioteka1.3         19/08/2001 10:54:11 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:51:59 PMDarko
 *  2    Biblioteka1.1         08/06/2001 10:51:12 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:56:55 PMDarko
 * $
 *****************************************************************************/
