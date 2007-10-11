/*$Workfile: KPhysCst.h$: header file
  $Revision: 10$ $Date: 2007-05-28 17:04:56$
  $Author: Darko Kolakovic$

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
#define CST_0C2K     273.15
  //Speed of light in vacuum [m/s]
#define CST_c        299792458.
#define CST_G        6.67428e-14
 /*Planck's constant h [Js] describes quantization of certain physical
   properties of subatomic particles such as electrons and photons.
   It is estimated to value
   {html: &#x0210E; = (6.62606896 &plusmn; 0.00000033)E-34 Js}

   [named after Planck, Max (1858-04-23, 1947-10-04)]
  */
#define CST_h        6.62606896e-34
 /*Boltzmann's constant k [J/K] is proportional constant used to convert
   energy E to the temperature T: E = kT.
   It is estimated to value
   {html: k = k<sub>B</sub> = (1.3806504 &plusmn; 0.0000024)E-23 J/K}
   [named after Boltzmann, Ludwig Eduard (1844-02-20, 1906-09-05)]
  */
#define CST_kB        1.3806504e-23
 /*Avogadro constant is the number of atoms in 12 grams of carbon-12.
   Consequently, this is same as is the number of atoms of one mole of a substance.
   It is estimated to value
   {html: N<sub>A</sub> = ( 6.02214179 &plusmn; 0.0000003)E23 mole<sup>-1</sup>}
   [named after Avogadro, Lorenzo Romano Amedeo Carlo (1766-08-09, 1856-07-09)]
  */
#define CST_Na       6.02214179e+23
/*Stefan-Boltzmann constant {html: &sigma; [W/m<sup>2</sup>K<sup>4</sup>]} is
   the constant of proportionality relating total energy radiated per unit
   surface area of a black body and thermodynamic temperature in
   Stefan-Boltzmann law:
   &sigma; = 2&pi;^5kB^4/(15h^3c^2)

   It is estimated to value
   {html: (&sigma; = 5.6704 &plusmn; 0.00004)E-8 Wm<sup>-2</sup>K<sup>-4</sup>}
  */
#define CST_Sigma    5.6704e-8
 /*Elementary charge q [C] is the electric charge carried by a single proton or
   electron.
   It is estimated to value
   {html: (q = 1.602176487 &plusmn; 0.00000004)E-19 C}
  */
#define CST_Qe       1.602176487e-19

  //Acceleration g due to Earth's gravity at sea level, 45° latitude [m/s2]
#define CST_g        9.806194
  /*Universal Gravitational Constant G {html:[m<sup>3</sup>/g s<sup>2</sup>]} is
    the constant of proportionality relating force to mass and distance in
    Newton's law of gravitation. It is estimated to value
    {html: (G = 6.67428 &plusmn; 0.001)E-11 m<sup>3</sup>kg<sup>-1</sup>s<sup>-2</sup>}
    Newton's law of gravitation from 1666 states any two bodies attract each
    other with a force F that is directly proportional to the product of their
    masses m and inversely proportional to the square of the distance d between them.
    F= G(m1*m2/d^2).
    [named after Newton, Isaac (1643-01-04, 1727-03-31)]
   */

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

  //One one-hundredth part [%] See also: percent()
#define CST_PERCENT = 1.0/100.0;
  //One one-thousandth part[‰]=ANSI(TTF)137
#define CST_PERMILL = 1.0/1000.0;

  /*decibel per neper
          [dB]/[Np] = 20*log(e) = 20/ln(10).

    Neper is a unit for comparing of two amplitudes, equal to the logarithm
    of the ratio of the two amplitudes
          A[Np] = ln(V/Vref).
    [named after Napier, John (1550-1617)]

    See also: WpW2dB(), dB2Np()
   */
#define CST_dBpNp  8.6858896380650365530225783783321

  /*{html: The voltage reference for 0dB with standard line impedance of 600&Omega;
    0dB is defined as 1mW (P<sub>ref</sub> = 1mW) load on standard line
    impedance.
        P[W] = V<sup>2</sup>/R
        V<sub>ref</sub>=0.77459 ~ 0.775[V].

    See also: VpV2dB()
    }
   */
#define CST_Vref 0.775

  /*{html:
    Speed of sound in air at 20°C [m/s].
    Speed of sound in the air depends on the temperature:
      v<sub>sa</sub>[m/s]=0.6T[°C] + 331.
    }
   */
#define CST_Vsa  343
  //Speed of sound in water at 20°C [m/s]
#define CST_Vsw 1525

///////////////////////////////////////////////////////////////////////////////
// Template functions
// Group=

#ifdef __cplusplus

//VpV2dB()---------------------------------------------------------------------
/*Converts Voltage attenuation [V/V] to decibels [dB].

      P = V<sup>2</sup>/R
      A[B] = 10A[dB] = 10log(P/P<sub>ref</sub>) = 10log((V/V<sub>ref</sub>)<sup>2</sup>)
           = 20log(V/V<sub>ref</sub>)[dB]

  0dB is defined as 1mW (P<sub>ref</sub> = 1mW) load on standard line impedance
  R = 600&Omega; Therefore:
      V<sub>ref</sub>=0.77459 &cong; 0.775[V].
  In communication systems where standard line impedance is 50&Omega;,
  V<sub>ref</sub>=0.2236[V]. In RF/TV cable systems line impedance is 75&Omega;
  and V<sub>ref</sub>=0.27386[V].

  See also: WpW2dB(), dB2Vratio()
*/
template <class TYPE> inline TYPE VpV2dB(const TYPE& fV,const TYPE& fVref)
  {
  ASSERT(fVref != (TYPE)0);
  return (TYPE)(20. * log10((double)fV/(double)fVref) );
  };

//WpW2dB()---------------------------------------------------------------------
/*{html:
  Converts Power attenuation [W/W] to decibels [dB].

  decibel [dB] is relative unit of measurement on logarithimic scale.
  One dB is equal to ten times the logarithm of the ratio of the measured or
  calculated power (or sound intensity) and a reference power (for example
  before attenuation).

      A[B] = 10 A[dB] = 10 log<sub>10</sub>(P/P<sub>ref</sub>)[dB]
  [named after Bell, Alexander Graham]

  In standard audio systems 0dB is defined as 1mW measured on 600&Omega; load.
  A 600&Omega; balanced audio line is the standard for professional audio and
  telecommunication equipment.

  See also: dB2Wratio(), VpV2dB()
  }
 */
template <class TYPE> inline TYPE WpW2dB(const TYPE& fP,const TYPE& fPref)
  {
  ASSERT(fPref!= (TYPE)0);
  return (TYPE)(10. * log10((double)fP/(double)fPref) );
  };

//dB2Vratio()------------------------------------------------------------------
/*{html: Converts decibels [dB] to voltage attenuation V/V<sub>ref</sub>
  See also: VpV2dB()
  }
 */
template <class TYPE> inline TYPE dB2Vratio (const TYPE& fdB)
  {
  return (TYPE)pow(10.,((double)fdB/20.));
  };

//dB2Wratio()------------------------------------------------------------------
/*{html: Converts decibels [dB] to power attenuation P/P<sub>ref</sub>.
  See also: WpW2dB()
  }
  */
template <class TYPE> inline TYPE dB2Wratio (const TYPE& fdB)
  {
  return (TYPE)pow(10.,((double)fdB/10.));
  };

//dB2Np()----------------------------------------------------------------------
/*Converts signal attenuation given in decibels to signal ratio in nepers.
  Usually used in conjunction with hyperbolic trigonometric functions.

      A[Np] = A[dB]/CST_dBpNp = A[dB]/(20*log(e))

  See also: WpW2dB(), CST_dBpNp
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
