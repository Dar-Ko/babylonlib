/*$Workfile: KMathCst.h$: header file
  $Revision: 14$ $Date: 2004-12-06 16:22:40$
  $Author: Darko Kolakovic$

  Constants
  Copyright: CommonSoft Inc
  Apr. 94 D. Kolakovic
 */
/* Group=Mathematics                                                          */

#ifndef _KMATHCST_H_
    /*$Workfile: KMathCst.h$ sentry                                                 */
  #define _KMATHCST_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/*---------------------------------------------------------------------------*/
/* Group=Constants                                                           */
  //log2(e)
#define CST_LOG2E     1.4426950408889634074
  //log(e)
#define CST_LOG10E    0.434294481903251827651128918916605
  //The Natural Logarithmic Base, e  = 10**(1/ln(10))
  //   {html:<br /><img src="Res/eqNaturalLogarithmicBase.gif"
  //    alt="x-&gt;0; lim((1+x)exp(1/x))-&gt;e" border="0">}
#define CST_E         2.71828182845904523536028747135266
  //ln(10)
#define CST_LN10      2.30258509299404568401799145468436
  //1/ln(10) = log(e)
#define CST_INVLN10   CST_LOG10E
  //ln(2)
#define CST_LN2       0.6931471805599453094172321214581765680754
  //Archimedes' Constant PI is the area enclosed by a circle of radius 1.
#define CST_PI        3.1415926535897932384626433832795028841971693993751058209749445923078164
  //PI/2
#define CST_PI_2      1.570796326794896619231322
  //PI/4
#define CST_PI_4      0.7853981633974483096156608

  //1/sqrt(PI)
#define CST_INVSQRTPI  0.5641895835477562869480795
  //1/sqrt(2)
#define CST_INVSQRT2  0.70710678118654752440
  //1/sqrt(3)
#define CST_INVSQRT3  0.57735026918962576451
  //sin(PI/4)
#define CST_SINPI_4   CST_INVSQRT2
  //cos(PI/4)
#define CST_COSPI_4   CST_INVSQRT2
  //Arc second in radians 1" = PI/(180*60*60) [rad]
#define CST_SEC2RAD   4.84813681109535993589914102357948e-6
  //Euler-Mascheroni (also known as gamma) constant
#define CST_GAMMA     0.577215664901532860606512090082402431042
  //ln(gamma)
#define CST_LNGAMMA  -0.549539312981644822337662
  //e^gamma
#define CST_E_GAMMA   1.7810724179901979852
  /*Golden Mean {html:&Phi;} is the positive solution to the quadratic equation:
     {html:<br /><img src="Images/eqGoldenMean.gif"
      alt="Phi^2 - Phi - 1 = 0; Phi > 0" border="0">}
     which is
     {html:<br /><img src="Images/eqGoldenRatio.gif"
      alt="Phi = (1+sqrt(5))/2;" border="0"><br />}

     Euclid, in "The Elements", says that the line AC is divided in extreme
     and mean ratio by B if AC/AB = AB/BC.
     {html:<br /><img src="Images/eqSectioAurea.gif"
      alt="AC/AB = AB/BC = Phi" border="0"><br />}
    This definition is equivalent to the dimensions of a rectangle such that
    dividing it into a square creates a new rectangle having the same proportions.
    Such a rectangle is known as a golden rectangle.
     {html:<br /><img src="Images/graphGoldenRect.gif"
      alt="AC/AB = AB/BC = Phi" border="0"><br />}
     {html:<br /><img src="Images/eqGoldenRect.gif"
      alt="AC/AB = AB/BC = Phi" border="0"><br />}
     Ratio of two consecutive Fibonacci numbers converges to Golden Mean:
     {html:<br /><img src="Images/eqFibonacciLim.gif"
      alt="AC/AB = AB/BC = Phi" border="0"><br />}
     Golden Mean is also known as golden section (sectio aurea), divine
     proportion (proportio divina), golden ratio and golden number.
   */
#define CST_PHI       1.6180339887498948482045868343656381177203091798057
  //Laplace limit constant
#define CST_LAPLACE_LIM 0.6627434193

#ifndef __cplusplus
  /*/////////////////////////////////////////////////////////////////////////*/
  /* Group=Macros                                                            */

  /*Returns the square of the given expression                               */
  #ifndef SQUARE
    #define SQUARE(x) (x*x)
  #endif
  /*Returns the cube of the given expression                                 */
  #ifndef CUBE
    #define CUBE(x) (x*x*x)
  #endif
  #ifndef max
    /*Compares two values. The data type can be any numeric data type, signed or
      unsigned. The data type of the arguments and the return value is the same.
      Returns the larger of two values.
      See also: KStdLib.h
     */
    #define max(a,b) (((a) > (b)) ? (a) : (b))
  #endif
  #ifndef min
    /*Compares two values. The data type can be any numeric data type, signed or
      unsigned. The data type of the arguments and the return value is the same.
      Returns the smaller of two values.
      See also: KStdLib.h
     */
    #define min(a,b) (((a) < (b)) ? (a) : (b))
  #endif
  #ifndef SWAP
    /*Exchanges contents of two integers.                                    */
    #define SWAP(a,b) {int iTmp = a; a = b; b = iTmp}
  #endif
    /*Exchanges contents of two variables.                                   */
  #define SWAP2(a,b,Tmp) {(Tmp)=(a);(a)=(b);(b)=(Tmp);}

  /*Returns the absolute value                                               */
  #define Absolute(x) (((x) >= 0) ? (x) : -(x))
  /*Converts arc degrees, minutes and seconds to radians                     */
  #define DegMinSec2Rad(Degrees,Minutes,Seconds) ( ((Degrees*60.0 + Minutes)*60.0 + Seconds)*CST_SEC2RAD )

#else /*__cplusplus                                                          */
  /////////////////////////////////////////////////////////////////////////////
  //Templates

  #ifndef _KMATHCST_INL_
    #include "KMathCst.inl" //Simple mathematical functions
  #endif  //_KMATHCST_INL_
#endif /*__cplusplus                                                         */

/*///////////////////////////////////////////////////////////////////////////*/
#endif  /*_KMATHCST_H_                                                       */

/*///////////////////////////////////////////////////////////////////////////*/
/******************************************************************************
 * $Log:
 *  4    Biblioteka1.3         20/07/2001 12:58:23 AMDarko           VSS tags
 *  3    Biblioteka1.2         11/07/2001 10:51:56 PMDarko
 *  2    Biblioteka1.1         08/06/2001 11:51:05 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:56:48 PMDarko
 * $
 *****************************************************************************/
