/*$Workfile: KMathCst.inl$: header file
  $Revision: 18$ $Date: 2004-10-04 23:40:22$
  $Author: Darko$

  Simple mathematical functions
  Copyright: CommonSoft Inc.
  Apr. 95 D. Kolakovic
 */

/* Group=Mathematics                                                         */

#ifndef _KMATHCST_INL_
    //$Workfile: KMathCst.inl$ sentry
  #define _KMATHCST_INL_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <math.h>

#ifndef _KMATHCST_H_
  #include "KMathCst.h" //Constants
#endif  //_KMATHCST_H_

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//Constants-------------------------------------------------------------------
const double CSTd_PI = (double)CST_PI;     //Pi

#ifndef CST_ROUNDOFF
  extern const double CST_ROUNDOFF; //Rounding error constant (see KProgCst.h)
  extern const float  CST_fROUNDOFF;//Rounding error constant
#endif


///////////////////////////////////////////////////////////////////////////////
// Template functions

//SQUARE()-------------------------------------------------------------------
/*Returns the square of the given expression
 */
template <class TYPE> inline TYPE SQUARE(TYPE x //[in]
                                         )
{
return x*x;
}

//CUBE()-------------------------------------------------------------------
/*Returns the cube of the given expression
 */
template <class TYPE> inline TYPE CUBE(TYPE x //[in]
                                       )
{
return x*x*x;
}

//logN()-------------------------------------------------------------------
/*Returns the logarithm to base n.

  logN(x) = log(x) / log(n)
 */
template <class TYPE, class BASE> inline TYPE logN(TYPE x, //[in]
                                                   BASE n //[in]
                                                   )
{
if ( n == (BASE) 0)
  return (TYPE)0;
return log(x)/log(n);
}

//Absolute()-----------------------------------------------------------------
/*Returns the absolute value

  Absolute(x) = |x| = x  if x >= 0 or
  Absolute(x) = |x| = -x if x <  0
 */
template <class TYPE> inline TYPE Absolute(TYPE x //[in]
                                           )
{
return( x >= (TYPE)0 ? x : -x );
}
inline int Absolute(int x //[in]
                    )
{
return abs(x);
}
inline long Absolute(long x //[in]
                     )
{
return labs(x);
}
inline double Absolute(double x //[in]
                       )
{
return fabs(x);
}
#ifdef  _COMPLEX_DEFINED  //included <Math.h>
  //Returns the absolute value as the real part of _complex structure
  //      {html:<BR><IMG SRC="Res/eqVectorNorm.gif" BORDER="0">}
  inline _complex Absolute(_complex x //[in]
                          )
  {
  _complex Temp;
  Temp.x =_cabs(x);
  Temp.y = 0.0;
  return Temp;
  }
#endif
#ifdef  __STD_COMPLEX //included <complex>
  /*Returns the magnitude (or Euclidean norm) of a complex number.
    {html:<BR><IMG SRC="Res/eqVectorNorm.gif" BORDER="0">}


             Z = x + iy
             Absolute(Z) = |Z| = sqrt(x**2+y**2)
  */
  template <class TYPE> inline TYPE Absolute(std::complex<TYPE> x //[in]
                                            )
  {
  return std::abs(x);
  }
#endif

//Sign()-----------------------------------------------------------------------
/*Tests if a value is positive number, zero (0), or negative number.

  Returns: sign of the given expression.

    If value < 0 result is -1,
    if value = 0 result is  0,
    if value > 0 result is  1.
 */
template <class TYPE> int Sign(const TYPE& value //[in] value to be evaluated
                              )
{
return value == 0 ? 0 : (value < 0 ? -1 : 1);
}


//DegMinSec2Rad()--------------------------------------------------------------
/*Converts arc degrees, minutes and seconds to radians.

  Returns: arc [rad]
 */
template<class TYPE>
inline double DegMinSec2Rad(const TYPE& Degrees,//[in] arc degrees [°]
                            const TYPE& Minutes,//[in] arc minutes [']
                            const TYPE& Seconds //[in] arc seconds ["]
                            )
{
return ( ((Degrees*60.0 + Minutes)*60.0 + Seconds)*CST_SEC2RAD );
}

//Rad2DegMinSec()--------------------------------------------------------------
/*Converts radians to degrees, minutes and seconds.
 */
template <class radType>
void Rad2DegMinSec(const radType& fRadian, //[in] value to convert [rad]
                   radType& nDeg,          //[out] result in range[0,60][°]
                   radType& nMin,          //[out] result in range[0,60][']
                   radType& dSec           //[out] result in range[0,60]["]
                   )
{
double dDeg = Rad2Deg((double)fRadian);
nDeg = (radType)(int)dDeg;  //Get integer part [°]
dDeg *= 60.0;
nMin = (radType)((int)dDeg % 60); //Get reminder ["]
dDeg *= 60.0;
dSec = (radType)(fmod(dDeg,60.0)); //Get reminder [']
}

//Rad2Deg()--------------------------------------------------------------------
/*Converts radians to degrees
 */
template <class radType>
inline radType Rad2Deg(radType fRadian //[in] angle [rad]
                       )
{
return (const radType)((double)fRadian*(180.0/CSTd_PI));
};

//Deg2Rad()--------------------------------------------------------------------
/*Converts degrees to radians.
 */
template <class degType>
inline degType Deg2Rad(degType fDegree //[in] angle [o]
                       )
{
return (const degType)((double)fDegree*(CSTd_PI/180.0));
};

///////////////////////////////////////////////////////////////////////////////
// Helpers

//SWAP()----------------------------------------------------------------------==
/*Exchanges contents of two variables.
 */
template<class TYPE> inline void SWAP(TYPE& a, //[in] a value to be replaced with second
                                      TYPE& b  //[in] a value to be replaced with first
                                      )
{
TYPE Tmp = a;
a = b;
b =Tmp;
}

template<> inline void SWAP(int& a, //[in] a value to be replaced with second
                            int& b  //[in] a value to be replaced with first
                            )
{
  //Swaping values without a temporary value
a ^= b;
b ^= a;
a ^= b;
}

template<> inline void SWAP(unsigned int& a, //[in] a value to be replaced with second
                            unsigned int& b  //[in] a value to be replaced with first
                            )
{
  //Swaping values without a temporary value
a ^= b;
b ^= a;
a ^= b;
}

//-----------------------------------------------------------------------------
/*Verifies if a number is an even number.
  An even number is an integer of the form n = 2k, where k is an integer.

  Example:
        ..., -4, -2, 0, 2, 4, 6, 8, 10, ...  are even numbers

  Returns: true if a number is an even number or false if a number is
  an odd number.
 */
inline bool IsEven(int iNumber)
{
return ((iNumber % 2) == 0);
}

//GetNoOfDigits()--------------------------------------------------------------
/*Get number of digits before decimal point.

  Note: in somewhat rare occasions rounding errors in the log function can
        cause the wrong number of digits.

  Example:
    //Returns 1 as number of digits
    int iResult = GetNoOfDigits(0.345);
    ASSERT(iResult == 1);

 */
template <class T> int GetNoOfDigits(T dNumber //[in]
                                     )
{
double dValue = fabs((double)dNumber);
if(dNumber < 10.0)
  return 1;
return (int)floor(log10(dValue));
}

//Round()----------------------------------------------------------------------
/*Rounds a double float number within given precision.
  Following alorithm is used:

      y = floor(x * 10^n + 0.5) / 10^n;

  where x is number to be rounded and n is number of decimal places.

  Returns: real number with given precision
 */
inline double Round(double x, //[in] a number to be rounded
                    unsigned int nNoofDecimals //[in] number of decimal places
                    )
{
//ASSERT(x >= 0.0);
return floor(x * pow(10.0, (int)nNoofDecimals) + 0.5) /
                 pow(10.0, (int)nNoofDecimals);
}

#include <float.h>  //DBL_EPSILON
inline double Round(const double x //[in] a number to be rounded
                   )
{
  //Absolute value
double dResult = (x < 0.0) ? -x : x;

dResult += 1.0 / DBL_EPSILON;
dResult -= 1.0 / DBL_EPSILON;
return ((x < 0.0) ? -dResult : dResult);
}

//Float2Long()-----------------------------------------------------------------
/*Rounding float numbers
 */
inline long Float2Long(float x //[in]
                       )
{
return ((long)((x<0) ? (x-0.5) : (x+0.5)));
};

//Double2Long()----------------------------------------------------------------
/*Rounding double float numbers
 */
inline long Double2Long(double x //[in]
                        )
{
return (long)floor(x + 0.5);
};

//Double2Int()-----------------------------------------------------------------
/*Rounding double float numbers
 */
inline int Double2Int(double x //[in]
                      )
{
return (int)floor(x + 0.5);
};

///////////////////////////////////////////////////////////////////////////////
  #endif  //__cplusplus
#endif  //_KMATHCST_INL_

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  11   Biblioteka1.10        08/07/2002 9:56:57 PMDarko           SWAP
 *       specialization for unsigned int
 *  10   Biblioteka1.9         08/07/2002 9:51:04 PMDarko           SWAP
 *       specialization for int
 *  9    Biblioteka1.8         04/04/2002 1:12:53 AMDarko           Documenation
 *       update
 *  8    Biblioteka1.7         08/03/2002 3:04:43 PMDarko Kolakovic Updated comment
 *  7    Biblioteka1.6         29/01/2002 11:21:29 PMDarko           Used lbraries
 *       notes
 *  6    Biblioteka1.5         29/01/2002 3:40:51 PMDarko           Tag update
 *  5    Biblioteka1.4         17/08/2001 12:37:44 AMDarko           Update
 *  4    Biblioteka1.3         20/07/2001 12:58:28 AMDarko           VSS tags
 *  3    Biblioteka1.2         08/07/2001 12:10:27 AMDarko           $Revision: 18$
 *       inserted
 *  2    Biblioteka1.1         08/06/2001 11:51:07 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:56:50 PMDarko
 * $
 *****************************************************************************/
