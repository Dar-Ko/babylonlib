/*$Workfile: KComplex.h$: header file
  $Revision: 14$ $Date: 2007-05-29 16:40:36$
  $Author: Darko Kolakovic$

  TComplex Numbers: extension to the template std::complex
  Copyright: CommonSoft Inc.
  May 94 Darko Kolakovic
*/
// Group=Mathematics

#ifndef _KCOMPLEX_H_
    //$Workfile: KComplex.h$ sentry
  #define _KCOMPLEX_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef BOOL
  #include "KTypedef.h" //BOOL
#endif

///////////////////////////////////////////////////////////////////////////////
//Define base class for TComplex<TYPE>
#if _MSC_VER >= 1100 //if Visual C++ 5.0 (or bigger), include std::complex D.K.
  #include <complex>

    //Use complex template
  #define TComplexBase std::complex

  using namespace std;
#endif  //_MSC_VER

#ifdef _STLP_INTERNAL_COMPLEX //STLport library
  #ifndef _USE_STLPORT
    #define _USE_STLPORT 445
  #endif
  #ifndef __STD_COMPLEX
    //Do not include "KComplxB.h"
    #define __STD_COMPLEX 445
  #endif

    //Use complex template
  #define TComplexBase std::complex
#endif

#ifndef __STD_COMPLEX //if template std::complex is not included,
                      //define new base class
  #include "KComplxB.h"  //TComplexBase template
#endif  //__STD_COMPLEX


///////////////////////////////////////////////////////////////////////////////
/*TComplex template class handles numbers in complex domain |Z| = R + jI.
  Real and imaginary parts are stored in _Re and _Im members.
    {html:<br /><img src="Images/graphComplexNo.gif" border="0"
               alt="complex number">

          <br /><img src="Images/eqPhasorCiS.gif" border="0"
               alt="z=abs(z)(cos(&phi;)+i*sin(&phi;))">
    }

  See also:
    I, exp10, asin, acos, tan, atan, tanh, atanh, acosh, asinh, asech, acoth

  Note: If Standard Template Library (STL) is included, base class for TComplex
  is std::complex
 */
template<class TYPE> class TComplex : public TComplexBase<TYPE>
{
//Construction
public:
  TComplex(const TYPE& x = 0, const TYPE& y = 0);
  TComplex(const TComplexBase<TYPE>& complexNo);

  //Microsoft's MFC Utility functions
  #ifdef __AFXWIN_H__
    TComplex(CPoint const& complexNo);
    TComplex(CSize const& complexNo);
  #endif //__AFXWIN_H__
  #ifdef  _COMPLEX_DEFINED
    TComplex(_complex const& complexNo);
  #endif //_COMPLEX_DEFINED
  //Attributes
public:
  TComplex<TYPE> I();
  //Operations
  bool IsFinite() const;
  bool IsNan() const;
public:

  //Overrides
public:
  virtual TYPE Rho()   const;
  virtual TYPE Angle() const;
};

///////////////////////////////////////////////////////////////////////////////
//CComplex class handles numbers in complex domain |Z| = R + jI. Real and
//imaginary parts are stored in _Re and _Im members with double precision.
typedef TComplex<double> CComplex;

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::TComplex()-----------------------------------------------------------------
/*Default constructor |Z| = x + j*y
 */
template<class TYPE>
inline TComplex<TYPE>::TComplex(const TYPE& x, //= 0 real part of the complex number
                                const TYPE& y  //= 0 imaginary part of the complex number
                                ):
  TComplexBase<TYPE>(x,y)
  {
  }

/*Assignment constructor |Z| = |Y|
 */
template<class TYPE>
inline TComplex<TYPE>::TComplex(const TComplexBase<TYPE>& complexNo) :
  TComplexBase<TYPE>((TYPE)complexNo.real(),(TYPE)complexNo.imag())
  {
  }

#ifdef __AFXWIN_H__ //Microsoft's MFC Utility functions

  /*Assignment constructor |Z| = x + j*y
    x   Specifies the x-coordinate of a point.
    y   Specifies the y-coordinate of a point.
   */
  template<class TYPE>
  inline TComplex<TYPE>::TComplex(CPoint const& complexNo) :
  TComplexBase<TYPE>((TYPE)complexNo.x,(TYPE)complexNo.y)
    {
    }

  /*Assignment constructor |Z| = cx + j*cy
    cx   Specifies the x-extent.
    cy   Specifies the y-extent.
   */
  template<class TYPE>
  inline TComplex<TYPE>::TComplex(CSize const& complexNo) :
  TComplexBase<TYPE>((TYPE)complexNo.cx,(TYPE)complexNo.cy)
    {
    }
#endif  //__AFXWIN_H__
#ifdef  _COMPLEX_DEFINED //<math.h>
  /*Assignment constructor |Z| = x + j*y
    x   Specifies the real part of the complex number
    y   Specifies the imaginary part of the complex number.
   */
  template<class TYPE>
  inline TComplex<TYPE>::TComplex(_complex const& complexNo) :
  TComplexBase<TYPE>((TYPE)complexNo.x,(TYPE)complexNo.y)
    {
    }
#endif //_COMPLEX_DEFINED

//::Angle()--------------------------------------------------------------------
/*Calculates an phase angle in radians of a complex number in the polar form.
    {html:<br /><img src="Images/graphComplexNo.gif" border="0"
               alt="complex number">
          <br /><img src="Images/eqComplexArg.gif" border="0"
                  alt="&phi;=atan(y/x)">
    }

 */
template<class TYPE>
inline TYPE TComplex<TYPE>::Angle() const
{
return (TYPE)atan2((double)imag(), (double)real());
}

//::Rho()----------------------------------------------------------------------
/*Returns a radius of a complex number in the polar form.
  Radius is equal to the magnitude of the phasor represented by complex number
  and it is calulated as complex norm (absolute value of the complex number).
  Phasor is a rotating vector vector representing a periodical quantity.
    {html:<br /><img src="Images/graphComplexNo.gif" border="0"
               alt="complex number">
          <br /><img src="Images/eqPhasorCiS.gif" border="0"
               alt="z=abs(z)(cos(&phi;)+i*sin(&phi;))">
    }

             z1 = x + iy
             Rho(z1) = |z1| = sqrt(x**2+y**2)

  Example:
      int main()
        {
        CComplex z1(3, 4);
        cout << '(' << z1.real() << ',' << z1.imag() << ')' << endl;
        cout << '(' << z1.Rho() << ',' << z1.Angle() << ')' << endl;
        return 0;
        }

 */
template<class TYPE>
inline TYPE TComplex<TYPE>::Rho() const
{
return (abs(*this));
}

//::I()------------------------------------------------------------------------
/*Multiplies complex number with i.

      Z= x +i*y
      i*Z = -y +i*x
 */
template<class TYPE>
inline TComplex<TYPE> TComplex<TYPE>::I()
{
TYPE oldR = real();
real() = - imag();
imag() = oldR;
return (*this);
}

//-----------------------------------------------------------------------------
/*Determines whether the complex number is finite.

  Returns: true if both real and imaginary part of the complex number are
  between (–INF, +INF). Returns false if any component is infinite or a NaN.
 */
template<class TYPE>
inline bool TComplex<TYPE>::IsFinite() const
{
return ( (finite((double) real()) != 0) &&
         (finite((double) imag()) != 0) );
}

//-----------------------------------------------------------------------------
/*Determines whether the complex number is not a number (NaN).
  A NaN is generated when the result of a floating-point operation cannot be
  represented in Institute of Electrical and Electronics Engineers (IEEE) format.

  Returns: true if real or imaginary part of the complex number is not a number.
  Returns false if both components are valid numbers.
 */
template<class TYPE>
inline bool TComplex<TYPE>::IsNan() const
{
return ( (isnan((double) real()) != 0) ||
         (isnan((double) imag()) != 0) );
}

///////////////////////////////////////////////////////////////////////////////
//Template functions

#include "KMathCst.h" //Constants

//::I()------------------------------------------------------------------------
/*Multiplies complex number with i.

  {html:<br /><img src="Images/eqComplexNo.gif" border="0"
               alt="Z= x +i*y">
        <br />
  }

      i*Z = -y +i*x
 */
template<class TYPE>
inline TComplex<TYPE> I(const TComplex<TYPE>& complexNo)
{
return (TComplex<TYPE>(-complexNo.imag(),complexNo.real()));
}

//exp10()----------------------------------------------------------------------
/*Returns the number 10 raised to the power of a complexNo.
 */
template<class TYPE>
TComplex<TYPE> exp10(const TComplex<TYPE>& complexNo)
  {
  return TComplex<TYPE>((TYPE)(exp(complexNo.real() * CST_LN10) + cos(complexNo.imag() * CST_LN10)),
                        (TYPE)(exp(complexNo.real() * CST_LN10) + sin(complexNo.imag() * CST_LN10)) );
  }

//_GetAR()---------------------------------------------------------------------
/*Helper function for asin and acos. Returns half angle and square root of
  magnitude.
 */
template<class TYPE>
inline void _GetAR(const TComplex<TYPE>& complexNo, TYPE& Angle, TYPE&R)
  {
  TComplex<TYPE> ccV(1 - SQUARE(complexNo.real()) + SQUARE(complexNo.imag()),
                     -2*complexNo.real()*complexNo.imag());
  Angle = arg(ccV)/2;
  R = sqrt(abs(ccV));
  }

//acos()-----------------------------------------------------------------------
/*Returns the arcus cosine of complexNo in radians.

      acos(Z) = -i *ln(Z [+/-] i*sqrt(Z**2 -1))
 */
template<class TYPE>
TComplex<TYPE> acos(const TComplex<TYPE>& complexNo)
{
/*
const TComplex<TYPE> i(0,1);
return -i * log(complexNo + i*sqrt(TComplex<TYPE>(1,0) - SQUARE(complexNo)));
*/
TYPE Angle;
TYPE R    ;
_GetAR(complexNo,Angle,R);
TComplex<TYPE> ccW(complexNo.real() - R*sin(Angle), complexNo.imag() + R*cos(Angle));
return TComplex<TYPE>(arg(ccW), -log(abs(ccW)));
}

//asin()-----------------------------------------------------------------------
/*Returns the arcus sine of complexNo in radians.

      asin(Z)=-i*ln(i*Z+sqrt(1-Z**2))
 */
template<class TYPE>
TComplex<TYPE> asin(const TComplex<TYPE>& complexNo)
{
/*
const TComplex<TYPE> i(0,1);
return i * log(i*complexNo + sqrt(TComplex<TYPE>(1,0) - SQUARE(complexNo)));
*/
TYPE Angle;
TYPE R    ;
_GetAR(complexNo,Angle,R);
TComplex<TYPE> ccW(-complexNo.imag() + R*cos(Angle), complexNo.real() + R*sin(Angle));
return TComplex<TYPE>(arg(ccW), -log(abs(ccW)));
}

//tan()------------------------------------------------------------------------
/*Returns the tangent of complexNo.

      tan(Z) = sin(Z)/cos(Z)
 */
template<class TYPE>
TComplex<TYPE> tan(const TComplex<TYPE>& complexNo)
{
TYPE SinR = (TYPE)sin(complexNo.real());
TYPE CosR = (TYPE)cos(complexNo.real());
TYPE eI   = (TYPE)exp(complexNo.imag());
TYPE e_negI = 1 / eI;
TYPE eDelta = e_negI - eI;
TYPE eSigma = e_negI + eI;
return TComplex<TYPE>(4*SinR*CosR, -eDelta*eSigma) /
    (SQUARE(CosR*eSigma) + SQUARE(SinR*eDelta));
}

//atan()-----------------------------------------------------------------------
/*Returns arctangent of complexNo.

  {html:<br /><img src="Images/eqComplexNo.gif" border="0"
               alt="Z= x +i*y">
        <br />
  }
      atan(Z)=i/2*ln((1-i*z)/(1+i*z))
      atan(Z)=atan(2x/(1-x**2-y**2))/2 + i*ln((x**2+(y+1)**2)/(x**2+(y-1)**2))/4 +k*PI
 */
template<class TYPE>
TComplex<TYPE> atan(const TComplex<TYPE>& complexNo)
{
/*
const TComplex<TYPE> i(0,1);
return i/2 * log((i+complexNo)/(i-complexNo));
*/
const TComplexBase<TYPE> _ccZero(0,0);
if (complexNo == _ccZero)
  return  TComplexBase<TYPE>(0,0);

TYPE Iplus1 = 1 + complexNo.imag();      //i(1+Y)
TYPE RSquare = SQUARE(complexNo.real()); //x^2
TYPE Znorm = SQUARE(Iplus1) + RSquare; //norm(Z+i)
TComplex<TYPE> ccW(((1-complexNo.imag())*Iplus1 - RSquare)/Znorm, 2*complexNo.real()/Znorm);

return TComplex<TYPE>((TYPE)(arg(ccW)/2),(TYPE)( -log(abs(ccW))/2));
}

//tanh()-----------------------------------------------------------------------
/*Returns hyperbolic tangent of a complex number. All angles are in radians.
    {html:<br />
    <img src="Images/eqPhasorej.gif" border="0">
                   alt="z=abs(z)e**(i&phi;)"><br />

     <img src="Images/eqTanhZ.gif" border="0">
                   alt="tanh(z) = sinh(Z)/cosh(Z)"><br />
    }
 */
template<class TYPE>
TComplex<TYPE> tanh(const TComplex<TYPE>& complexNo)
{
TYPE SinI = (TYPE)sin(complexNo.imag());
TYPE CosI = (TYPE)cos(complexNo.imag());
TYPE eR   = (TYPE)exp(complexNo.real());
TYPE e_negR = 1 / eR;
TYPE eDelta = eR - e_negR;
TYPE eSigma = eR + e_negR;
TYPE div = (SQUARE(CosI*eSigma) + SQUARE(SinI*eDelta));

return TComplex<TYPE>((eDelta/div)*eSigma, (4*SinI*CosI)/div);
}

//atanh()----------------------------------------------------------------------
/*Returns the hyperbolic arcus tangent of complexNo.
    {html:<br /><img src="Images/eqPhasorej.gif" border="0">
                   alt="z=abs(z)e**(i&phi;)">
       <br />
  }

      atanh(Z)=-i*atan(iZ) ; Z = iY
      atanh(Z)=1/2*ln((1+Z)/(1-Z))
 */
template<class TYPE>
TComplex<TYPE> _cdecl atanh(const TComplex<TYPE>& complexNo)
{
if( complexNo.real() == (TYPE)0 && complexNo.imag() == (TYPE)0)
  return TComplex<TYPE> ((TYPE)0,(TYPE)0);
else if (complexNo.real() == (TYPE)0)
  return TComplex<TYPE> ((TYPE)0,(TYPE)atan(complexNo.imag()));
else
  {
  return log(((TYPE)1 + complexNo)/((TYPE)1 - complexNo))/(TYPE)2;
  }

}
//acosh()----------------------------------------------------------------------
/*Returns inverse hyperbolic cosine (arccosine).
    {html:<br /><img src="Images/eqPhasorej.gif" border="0">
                   alt="z=abs(z)e**(i&phi;)">
        <br />
  }

      acosh(Z)=i*acos(Z)
      acosh(Z)=ln(Z [+/-] sqrt(Z**2-1))
 */
template<class TYPE>
TComplex<TYPE> acosh(const TComplex<TYPE>& complexNo)
{
return (log(sqrt (SQUARE(complexNo) - (TYPE)1) + complexNo));
}

//asinh()----------------------------------------------------------------------
/*Returns inverse hyperbolic sine (arcsine).
    {html:<br /><img src="Images/eqPhasorej.gif" border="0">
                   alt="z=abs(z)e**(i&phi;)">
        <br />
  }

      asinh(Z)= -i*asin(i*Z)
      asinh(Z)= ln(Z+sqrt(Z**2+1))
 */
template<class TYPE>
TComplex<TYPE> asinh(const TComplex<TYPE>& complexNo)
{
return (log(sqrt (SQUARE(complexNo)+ (TYPE)1) + complexNo));
}

//asech()----------------------------------------------------------------------
/*Returns inverse hyperbolic secant (arcsech).
    {html:<br /><img src="Images/eqPhasorej.gif" border="0">
                   alt="z=abs(z)e**(i&phi;)">
        <br />
  }

        asech(Z) = ln( (1 [+/-] sqrt(1 - Z**2)) / Z)
 */
template<class TYPE>
TComplex<TYPE> asech(const TComplex<TYPE>& complexNo)
{
return (log((sqrt ((TYPE)1 - SQUARE(complexNo)) + (TYPE)1) / complexNo));
}

//acoth()----------------------------------------------------------------------
/*Returns inverse hyperbolic cosecant (arccoth).
    {html:<br /><img src="Images/eqPhasorej.gif" border="0">
                   alt="z=abs(z)e**(i&phi;)"
        <br />
  }

      acoth(Z) = ln((Z+1)/(Z-1))/2
 */
template<class TYPE>
TComplex<TYPE> acoth(const TComplex<TYPE>& complexNo)
{
return (log((complexNo+(TYPE)1) / (complexNo-(TYPE)1))/(TYPE)2);
}

//-----------------------------------------------------------------------------
/*Returns the base 2 logarithm of a complex number.
 */
template<class TYPE>
TComplex<TYPE> log2(const TComplex<TYPE>& complexNo)
{
return (log(complexNo) / log(2.0));
}

//operator<<()-----------------------------------------------------------------
#ifdef __STD_COMPLEX
  /*Assigns value of real and imaginary part of _complex structure (defined in
    Math.h) to std::complex class (defined in complex).
  */
  template<class TYPE>
  inline std::complex<TYPE>& operator <<(std::complex<TYPE>& Z,_complex Y)
 {
  return (Z = std::complex<TYPE>((TYPE)Y.x,(TYPE)Y.y));
  }
#endif  //__STD_COMPLEX

///////////////////////////////////////////////////////////////////////////////
#endif  //_KCOMPLEX_H_

/*///////////////////////////////////////////////////////////////////////////*/
/******************************************************************************
 * $Log:
 *  5    Biblioteka1.4         22/12/2001 11:40:40 PMDarko           header changed
 *  4    Biblioteka1.3         19/07/2001 11:52:50 PMDarko           VSS tags
 *  3    Biblioteka1.2         11/07/2001 9:50:18 PMDarko
 *  2    Biblioteka1.1         08/06/2001 10:49:17 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:55:38 PMDarko
 * $
 *  Jan 2k Base class replaced with std::complex D.K.
 *  Jul 95 class replaced with template TComplex D.K.
 *  May 94 CComplex class created Darko Kolakovic
 *****************************************************************************/
