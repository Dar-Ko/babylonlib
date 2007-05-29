/*$Workfile: KMathCst.h$: header file
  $Revision: 20$ $Date: 2007-05-28 17:05:15$
  $Author: Darko Kolakovic$

  Constants
  Copyright: CommonSoft Inc
  Apr. 94 D. Kolakovic
 */

#ifndef _KMATHCST_H_
    /*$Workfile: KMathCst.h$ sentry  */
  #define _KMATHCST_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* Group=Constants                                                           */


  //log2(e)
#define CST_LOG2E     1.4426950408889634074
  //log(e)
#define CST_LOG10E    0.434294481903251827651128918916605
 /*The Natural Logarithmic Base, e  = 10**(1/ln(10))
   {html:<br /><img src="Images/eqNaturalLogarithmicBase.gif"
   alt="x-&gt;0; lim((1+x)exp(1/x))-&gt;e" border="0">}
  */
#define CST_E         2.71828182845904523536028747135266
  //ln(10)
#define CST_LN10      2.30258509299404568401799145468436
  //1/ln(10) = log(e)
#define CST_INVLN10   CST_LOG10E
  //ln(2)
#define CST_LN2       0.6931471805599453094172321214581765680754
 /*{html: Archimedes' Constant &pi; is an irrational number defined as the area
   enclosed by a circle of radius 1.
     <br /><img src="Images/graphUnitCircle.gif"
     alt="Area=Pi * r^2; r = 1" border="0"> }
  */
#define CST_PI        3.1415926535897932384626433832795028841971693993751058209749445923078164
  //{html: &pi;/2}
#define CST_PI_2      1.570796326794896619231322
  //{html: &pi;/4}
#define CST_PI_4      0.7853981633974483096156608
  //{html: 1/&pi;}
#define CST_1_PI      0.318309886183790671538

   //sqrt(2)
#define CST_SQRT2     1.4142135623730950488016887242097
  //{html: 1/sqrt(&pi;) }
#define CST_INVSQRTPI 0.5641895835477562869480795
  //1/sqrt(2)
#define CST_INVSQRT2  0.70710678118654752440
  //1/sqrt(3)
#define CST_INVSQRT3  0.57735026918962576451
  //{html: sin(&pi;/4) }
#define CST_SINPI_4   CST_INVSQRT2
  //{html: cos(&pi;/4) }
#define CST_COSPI_4   CST_INVSQRT2
  //{html: Arc second in radians 1" = &pi;/(180*60*60) [rad] }
#define CST_SEC2RAD   4.84813681109535993589914102357948e-6
/*{html: Euler-Mascheroni (also known as gamma) constant &gamma; is deifined
  as:
     <br /><img src="Images/eqGammaConst.gif"
     alt="&gamma; = lim(Sum(1/k - ln(n))); k[1,n];  x-&gt;INF;" border="0"> }
  */
#define CST_GAMMA     0.577215664901532860606512090082402431042
/*{html: ln(&gamma;)
  See also: CST_GAMMA, CST_E_GAMMA
  }
  */
#define CST_LNGAMMA  -0.549539312981644822337662
/*{html: e<sup>(&gamma;)</sup>
  See also: CST_GAMMA, CST_LNGAMMA
  }
  */
#define CST_E_GAMMA   1.7810724179901979852
/*{html: Golden Mean &Phi; is the positive solution to the quadratic equation:
    <br /><img src="Images/eqGoldenMean.gif"
    alt="Phi^2 - Phi - 1 = 0; Phi > 0" border="0">
  which is
    <br /><img src="Images/eqGoldenRatio.gif"
    alt="Phi = (1+sqrt(5))/2;" border="0"><br />

  Euclid, in "The Elements", says that the line AC is divided in extreme
  and mean ratio by B if AC/AB = AB/BC.
    <br /><img src="Images/eqSectioAurea.gif"
    alt="AC/AB = AB/BC = Phi" border="0"><br />
  This definition is equivalent to the dimensions of a rectangle such that
  dividing it into a square creates a new rectangle having the same proportions.
  Such a rectangle is known as a golden rectangle.
    <br /><img src="Images/graphGoldenRect.gif"
    alt="AC/AB = AB/BC = Phi" border="0"><br />
    <br /><img src="Images/eqGoldenRect.gif"
    alt="AC/AB = AB/BC = Phi" border="0"><br />
  Ratio of two consecutive Fibonacci numbers converges to Golden Mean:
    <br /><img src="Images/eqFibonacciLim.gif"
    alt="AC/AB = AB/BC = Phi" border="0"><br />
  }
 */
#define CST_PHI       1.6180339887498948482045868343656381177203091798057
/*{html: Laplace limit constant is a value for which Laplace's solution of
  Kepler's equation begins diverging.
  The constant <i><b>e</b></i> is defined as:
    <br /><img src="Images/eqLaplaceConst.gif"
  alt="f(e) = (e * exp(sqrt(1+e^2))) / (1 + sqrt(1+e^2)) = 1" border="0"><br />
  Kepler's equation gives the relation between the polar coordinates of
  a celestial body and the time elapsed from a given initial point.
  }
*/
#define CST_LAPLACE_LIM 0.6627434193


/* ////////////////////////////////////////////////////////////////////////  */
#ifndef __cplusplus
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

  /*Verifies if a number is an odd number.                                   */
  #define IsOdd(n)         (((n)/2)*2 != (n))
  /*Verifies if an integer is an odd number.                                 */
  #define IsOddInt(n)      ((((int)n) & 1) == 1)
  /*Verifies if a number is an even number.                                  */
  #define IsEven(n)        (((n)/2)*2 == (n))
  /*Verifies if an integer is an even number.                                */
  #define IsEvenInt(n)     ((((int)n) & 1) == 0)

#else /*__cplusplus                                                          */
  /////////////////////////////////////////////////////////////////////////////
  //Templates

  #ifndef _KMATHCST_INL_
    #include "KMathCst.inl" //Simple mathematical functions
  #endif  //_KMATHCST_INL_
#endif /*__cplusplus                                                         */

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*_KMATHCST_H_                                                       */

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  17   Biblioteka1.16        2005-04-19 20:56:49  Darko Kolakovic Comments
 *  16   Biblioteka1.15        2005-04-19 19:29:14  Darko Kolakovic Comments
 *  15   Biblioteka1.14        2005-04-19 18:59:51  Darko Kolakovic comments
 *  14   Biblioteka1.13        2004-12-06 17:22:40  Darko Kolakovic comments
 *  13   Biblioteka1.12        2004-07-09 02:41:59  Darko           Golden ratio
 *  12   Biblioteka1.11        2004-07-07 17:50:46  Darko           sentry
 *  11   Biblioteka1.10        2003-09-22 22:26:23  Darko           formatting
 *  10   Biblioteka1.9         2003-01-20 04:09:28  Darko           Fixed
 *       CST_INVSQRT3
 *  9    Biblioteka1.8         2002-09-09 23:18:23  Darko           CST_LNGAMMA
 *  8    Biblioteka1.7         2002-03-08 02:45:52  Darko Kolakovic Laplace limit
 *       constant
 *  7    Biblioteka1.6         2002-02-12 10:45:51  Darko           CST_GAMMA
 *  6    Biblioteka1.5         2002-01-25 16:57:14  Darko           Updated
 *       comments
 *  5    Biblioteka1.4         2001-08-17 00:37:40  Darko           Update
 *  4    Biblioteka1.3         2001-07-20 00:58:23  Darko           VSS tags
 *  3    Biblioteka1.2         2001-07-11 22:51:56  Darko
 *  2    Biblioteka1.1         2001-06-08 23:51:05  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:56:48  Darko
 * $
 * 0 Apr. 94 D. Kolakovic
 *****************************************************************************/
