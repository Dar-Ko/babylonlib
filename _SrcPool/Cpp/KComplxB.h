/*$Workfile: KComplxB.h$: header file
  $Revision: 9$ $Date: 2003-09-22 22:25:37$
  $Author: Darko$

  Base class for complex numbers
  Copyright: CommonSoft Inc.
  May 94 Darko Kolakovic
 */ 
// Group=Mathematics

#ifndef _KCOMPLXB_H_
    //$Workfile: KComplxB.h$ sentry
  #define _KCOMPLXB_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <Math.h>

///////////////////////////////////////////////////////////////////////////////
//Base class for complex numbers
template <class TYPE> class TComplexBase
{
  //Construction
public:
  TComplexBase(const TYPE& dR = 0, const TYPE& dI = 0);
  TComplexBase(const TComplexBase<TYPE>& complexNo);

  //Data
protected:
  TYPE _ccR; //real part of the complex number
  TYPE _ccI; //imaginary part of the complex number

  //Operations
public:
  TComplexBase& operator = (const TComplexBase<TYPE>& complexNo);
  TComplexBase& operator = (const TYPE& dReal);
  TComplexBase& operator +=(const TComplexBase<TYPE>& complexNo);
  TComplexBase& operator +=(const TYPE& dReal);
  TComplexBase& operator -=(const TComplexBase<TYPE>& complexNo);
  TComplexBase& operator -=(const TYPE& dReal);
  TComplexBase& operator *=(const TComplexBase<TYPE>& complexNo);
  TComplexBase& operator *=(const TYPE& dReal);
  TComplexBase& operator /=(const TComplexBase<TYPE>& complexNo);
  TComplexBase& operator /=(const TYPE& dReal);
  #ifdef _DOCBROwSER //Dummy elif
  #else
  TComplexBase operator +() const;
  TComplexBase operator -() const;
  #endif
  TYPE real() const;
  TYPE imag() const;
  TYPE real(const TYPE& Re);
  TYPE imag(const TYPE& Im);

  TYPE Rho()  const;

public:
  friend TYPE  abs(const TComplexBase<TYPE>& complexNo);                    // magnitude of vector
  friend TYPE  arg(const TComplexBase<TYPE>& complexNo);                    // angle of vector
  friend TYPE norm(const TComplexBase<TYPE>& complexNo);
  friend TComplexBase<TYPE> conj (const TComplexBase<TYPE>& complexNo);
  friend TComplexBase<TYPE> polar(const TYPE& Rho,const TYPE Angle);   
  friend TComplexBase<TYPE> polar(const TYPE& Rho);   
  friend TComplexBase<TYPE> cos  (const TComplexBase<TYPE>& complexNo);     // cosine
  friend TComplexBase<TYPE> cosh (const TComplexBase<TYPE>& complexNo);     // hyperbolic cosine
  friend TComplexBase<TYPE> exp  (const TComplexBase<TYPE>& complexNo);     // e raised to a power
  friend TComplexBase<TYPE> log  (const TComplexBase<TYPE>& complexNo);     // log base e
  friend TComplexBase<TYPE> log10(const TComplexBase<TYPE>& complexNo);     // log base 10
  friend TComplexBase<TYPE> pow  (const TComplexBase<TYPE>& complexNo,      // Z**Y
                                  const TComplexBase<TYPE>& Power);
  friend TComplexBase<TYPE> pow  (const TComplexBase<TYPE>& complexNo,      // Z**a
                                  const TYPE& Power);
  friend TComplexBase<TYPE> pow  (const TYPE& dReal,                        // a**Z
                                  const TComplexBase<TYPE> &Power );
  friend TComplexBase<TYPE> pow  (const TComplexBase<TYPE>& complexNo,      // Z**int
                                  const int& Power);
  friend TComplexBase<TYPE> sin  (const TComplexBase<TYPE>& complexNo);     // sin
  friend TComplexBase<TYPE> sinh (const TComplexBase<TYPE>& complexNo);     // hyperbolic sin
  friend TComplexBase<TYPE> sqrt (const TComplexBase<TYPE>& complexNo);     // square root

  friend TComplexBase<TYPE> operator+(const TComplexBase<TYPE>&, const TComplexBase<TYPE>&);
  friend TComplexBase<TYPE> operator+(const TYPE&,               const TComplexBase<TYPE>&);
  friend TComplexBase<TYPE> operator+(const TComplexBase<TYPE>&, const TYPE&);
  friend TComplexBase<TYPE> operator-(const TComplexBase<TYPE>&, const TComplexBase<TYPE>&);
  friend TComplexBase<TYPE> operator-(const TYPE&,               const TComplexBase<TYPE>&);
  friend TComplexBase<TYPE> operator-(const TComplexBase<TYPE>&, const TYPE&);
  friend TComplexBase<TYPE> operator*(const TComplexBase<TYPE>&, const TComplexBase<TYPE>&);
  friend TComplexBase<TYPE> operator*(const TComplexBase<TYPE>&, const TYPE&);
  friend TComplexBase<TYPE> operator*(const TYPE&,               const TComplexBase<TYPE>&);
  friend TComplexBase<TYPE> operator/(const TComplexBase<TYPE>&, const TComplexBase<TYPE>&);
  friend TComplexBase<TYPE> operator/(const TComplexBase<TYPE>&, const TYPE&);
  friend TComplexBase<TYPE> operator/(const TYPE&,               const TComplexBase<TYPE>&);
  friend BOOL               operator==(const TComplexBase<TYPE>&, const TComplexBase<TYPE>&);
  friend BOOL               operator!=(const TComplexBase<TYPE>&, const TComplexBase<TYPE>&);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::TComplexBase()-------------------------------------------------------------
/*Default constructor initializes complex number to 0 |Z| = 0 +j0
 */
template<class TYPE>
inline TComplexBase<TYPE>::TComplexBase(const TYPE& dR,//= 0 real part of the complex number       
                                        const TYPE& dI //= 0 imaginary part of the complex number  
                                        ) :
   _ccR(dR),_ccI(dI)
{
}

/*Copy constructor
 */
template<class TYPE>
inline TComplexBase<TYPE>::TComplexBase(const TComplexBase<TYPE>& complexNo) :
   _ccR(complexNo._ccR),_ccI(complexNo._ccI)
{
}

//::real()------------------------------------------------------------------------
/*Returns real part of the complex number.

   |Z| = R +jI   R(Z) = R
 */
template<class TYPE>
inline TYPE TComplexBase<TYPE>::real() const
{
return _ccR;
}

/*Assigns and returns real part of the complex number.
 */
template<class TYPE>
inline TYPE TComplexBase<TYPE>::real(const TYPE& Re)
{
return (_ccR = Re);
}

//::imag()------------------------------------------------------------------------
/*Returns imaginary part of the complex number.

   |Z| = R +jI   I(Z) = I
 */
template<class TYPE>
inline TYPE TComplexBase<TYPE>::imag() const
{
return _ccI;
}

/*Assigns and returns imaginary part of the complex number.
 */
template<class TYPE>
inline TYPE TComplexBase<TYPE>::imag(const TYPE& Im)
{
return (_ccI = Im);
}

//::Rho()----------------------------------------------------------------------
#include "KMathCst.inl" //Absolute()
/*Returns a radius of complex number in the polar form.
  Radius is equal to the magnitide of the phasor represented by complex number.
  Phasor is a rotating vector vector representing a periodical quantity. 

             Z = x + jy
             Rho(Z) = |Z| = sqrt(x**2+y**2)

  Example:
    int main()
      {
      CComplex z1(3, 4);
      cout << '(' << z1.real() << ',' << z1.imag() << ')' << endl;
      cout << '(' << z1.Rho() << ')' << endl;
      return 0;
      }
 */
template<class TYPE>
inline TYPE TComplexBase<TYPE>::Rho() const
{
if (_ccI == (TYPE)0)
  return Absolute(_ccR);
if (_ccR == (TYPE)0)
  return Absolute(_ccI);
return (TYPE)sqrt(norm(*this));
}

//::operator=()----------------------------------------------------------------
/*Assignment operator
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator =(const TComplexBase<TYPE>& complexNo)
{
_ccR =complexNo._ccR;
_ccI =complexNo._ccI;
return (*this);
}

/*Assigns real part of the complex number. Imaginary part is set to zero,
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator =(const TYPE& dReal)
{
_ccR = dReal;
_ccI =(TYPE)0;
return (*this);
}

//::operator+=()---------------------------------------------------------------
/*Increments the complex number
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator +=(const TComplexBase<TYPE>& complexNo)
{
_ccR +=complexNo._ccR;
_ccI +=complexNo._ccI;
return(*this);
}

/*Increments the real part of the complex number
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator +=(const TYPE& dReal)
{
_ccR += dReal;
return( *this );
}

//::operator-=()---------------------------------------------------------------
/*Decrements the complex number
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator -=(const TComplexBase<TYPE>& complexNo)
{
_ccR -=complexNo._ccR;
_ccI -=complexNo._ccI;
return( *this );
}

/*Decrements the real part of the complex number
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator -=(const TYPE& dReal)
{
_ccR -= dReal;
return( *this );
}

//::operator*=()---------------------------------------------------------------
/*Multiplies complex number with a complex number
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator *=(const TComplexBase<TYPE>& complexNo)
{
TYPE R = _ccR*complexNo.real() - _ccI*complexNo.imag();
_ccI = _ccI*complexNo.real() + _ccR*complexNo.imag();
_ccR = R;
return *this;
}

/*Multiplies complex number with a real number
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator *=(const TYPE& dReal)
{
_ccR *= dReal;
_ccI *= dReal;
return(*this);
}

//::operator/=()---------------------------------------------------------------
/*Divides complex number with a complex number
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator /=(const TComplexBase<TYPE>& complexNo)
{
TYPE sum_sqrs = norm(complexNo);
*this *= conj(complexNo);
_ccR /= sum_sqrs;
_ccI /= sum_sqrs;
return *this;
}

/*Divides complex number with a real number
 */
template<class TYPE>
inline TComplexBase<TYPE>& TComplexBase<TYPE>::operator /=(const TYPE& dReal)
{
_ccR /= dReal;
_ccI /= dReal;
return (*this);
}

//::operator+()----------------------------------------------------------------
/*+ sign operator returns copy of the complex number 
 */
template<class TYPE>
inline TComplexBase<TYPE> TComplexBase<TYPE>::operator + () const
{
return (*this);
}

//::operator-()----------------------------------------------------------------
/*- sign unary operator returns a value whose real part is -real(Z) and whose 
  imaginary part is -imag(Z).
 */
template<class TYPE>
inline TComplexBase<TYPE> TComplexBase<TYPE>::operator - () const
{
return TComplexBase<TYPE>(-_ccR,-_ccI);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Template functions

//norm()-----------------------------------------------------------------------
/*Returns the squared magnitude of the complexNo

    norm(Z) = SQUARE(|Z|) = R^2 +I^2
 */
template<class TYPE>
inline TYPE norm(const TComplexBase<TYPE>& complexNo)
{
return (SQUARE(complexNo._ccR) + SQUARE(complexNo._ccI));
}

//conj()-----------------------------------------------------------------------
/*Function changes the sign of the imaginary part.

    conj(Z) = R -jI
 */ 
template<class TYPE>
inline TComplexBase<TYPE> conj(const TComplexBase<TYPE>& complexNo)
{
return TComplexBase<TYPE>(complexNo.real(), -complexNo.imag());
}

//polar()----------------------------------------------------------------------
/*Converts polar coordinates into complex domain
    {html:<BR><IMG SRC="Res/eqComplexArg.gif" BORDER="0">}
 */
template <class TYPE>
inline TComplexBase<TYPE> polar(const TYPE& Rho,   //magnitude
                                const TYPE  Angle  //=0 phase angle [rad]
                               )
{
return  (Angle ==  (TYPE)0) ?
        TComplexBase<TYPE>(Rho, (TYPE)0) :
        TComplexBase<TYPE>(Rho * ::cos(Angle), Rho * ::sin(Angle));
}

template <class TYPE>
inline TComplexBase<TYPE> polar(const TYPE& Rho   //magnitude
                               )
{
return  TComplexBase<TYPE>(Rho, (TYPE)0);
}

//abs()------------------------------------------------------------------------
/*The function returns the magnitude of the phasor represented by complexNo
  and it is calulated as Euclidean norm.
    {html:<BR><IMG SRC="Res/eqVectorNorm.gif" BORDER="0">}

             Z = x + iy
             Absolute(Z) = |Z| = sqrt(x**2+y**2)
 */
template <class TYPE>
TYPE abs(const TComplexBase<TYPE>& complexNo)
{
return complexNo.Rho();
}

//arg()------------------------------------------------------------------------
/*The function returns the phase angle of complexNo
    {html:<BR><IMG SRC="Res/eqComplexArg.gif" BORDER="0">}
 */
template <class TYPE>
TYPE arg(const TComplexBase<TYPE>& complexNo)
{
const TComplexBase<TYPE> _ccZero(0,0);
return complexNo == _ccZero ? (TYPE)0 : (TYPE)atan2(complexNo._ccI, complexNo._ccR);
}

//cos()------------------------------------------------------------------------
/*Returns cosine of the complex number.

    Z = x + iy
    cos(Z) = cos(x) * cosh(y) - i * sin(x) * sinh(y)
 */
template <class TYPE>
TComplexBase<TYPE> cos(const TComplexBase<TYPE>& complexNo)
{
TYPE eI  = exp(complexNo._ccI);
TYPE e_negI = 1 / eI;
return TComplexBase<TYPE>(cos(complexNo._ccR)*(e_negI+eI)/2, 
                          sin(complexNo._ccR)*(e_negI-eI)/2);
}

//cosh()-----------------------------------------------------------------------
/*Returns hyperbolic cosine of the complex number.

    Z = x + iy
    cosh(Z) = (e**Z + e**(-Z)) / 2  = cosh(x) * cos(y) + i * sinh(x) * sin(y)
 */
template <class TYPE>
TComplexBase<TYPE> cosh(const TComplexBase<TYPE>& complexNo)
{
TYPE eR = exp(complexNo._ccR);
TYPE e_negR = 1 / eR;
return TComplexBase<TYPE>(cos(complexNo._ccI)*(eR + e_negR)/2, 
                          sin(complexNo._ccI)*(eR - e_negR)/2);
}

//exp()------------------------------------------------------------------------
/*Returns the exponential value of the complex number, if successful.
    {html:<BR><IMG SRC="Res/eqPhasorCiS.gif" BORDER="0">}

    Z = x + iy
    exp(z) = e**Z
    exp(Z) = exp(x) * (cos(y) + i * sin(y))
 */
template <class TYPE>
TComplexBase<TYPE> exp(const TComplexBase<TYPE>& complexNo)
{
return polar(exp(complexNo._ccR),complexNo._ccI);
}

//log()------------------------------------------------------------------------
/*Calculates the natural logarithm of complex number. Throws exception if 
  complexNo = 0 + j0.
    {html:<BR><IMG SRC="Res/eqPhasorej.gif" BORDER="0">}

    Z = r * e**(ia)
    log(Z) = log(r) + ia

  Example:
    #include "KComplxB.h"
    void main() 
      {
      TComplexBase<double> Z(24, 27);
      cout << "The natural logarithm of" << Z << " = " << log(Z) << endl;
      }
 */
template <class TYPE>
TComplexBase<TYPE> log(const TComplexBase<TYPE>& complexNo)
{
return TComplexBase<TYPE>(log(abs(complexNo)), arg(complexNo));
}

//log10()----------------------------------------------------------------------
/*Calculates the base 10 logarithm of complex number.

  Example:
    #include "KComplxB.h"
    void main() 
      {
      TComplexBase<double> Z(24, 27);
      cout << "The base 10 logarithm of " << Z << " = " << log10(Z) << endl;
      }
 */
template <class TYPE>
TComplexBase<TYPE> log10(const TComplexBase<TYPE>& complexNo)
{
return log(complexNo) * CST_LOG10E;
}

//pow()------------------------------------------------------------------------
/*Returns the complex number X raised to the power of Y. 

    X = r*e**(ia)
    Y = u + iv
    X**Y = {(r**u) * exp (-v*a)} * {cos(v*log(r) + u*a) + i*sin(v*log(r) + u*a)}
 */
template <class TYPE>
TComplexBase<TYPE> pow(const TComplexBase<TYPE>& complexNo, TComplexBase<TYPE> const& Power)
{
const TComplexBase<TYPE> _ccZero(0,0);

if (Power == _ccZero)
  return TComplexBase<TYPE>(1,0);
else
  if (complexNo == _ccZero)
    return _ccZero;

return exp(Power * log(complexNo));
}

/*Complex number raised to a real power

    X = r*e**(ia)
    X**y = exp(y * log(X))
 */
template <class TYPE>
TComplexBase<TYPE> pow(const TComplexBase<TYPE>& complexNo, const TYPE& Power)
{
const TComplexBase<TYPE> _ccZero(0,0);

if (Power == _ccZero)
  return TComplexBase<TYPE>(1,0);
else
  if (complexNo == _ccZero)
    return _ccZero;

return polar(pow(abs(complexNo), Power), Power*arg(complexNo));
}

/*A number raised to a complex power

    Y = r*e**(ia)
    x**Y = exp(Y * log(x))
 */
template <class TYPE>
TComplexBase<TYPE> pow(const TYPE& dReal, TComplexBase<TYPE> const& Power)
{
const TComplexBase<TYPE> _ccZero(0,0);

if (dReal == 0 && real(Power) > 0) 
  return _ccZero;

TYPE logX = log(fabs(dReal));
if (dReal > (TYPE)0)
  {
  return exp(Power * logX);
  }
return exp(Power * TComplexBase<TYPE>(logX,CST_PI));
}

/*Complex number raised to an integer power

    X = r*e**(ia)
    X**y = (r**y) * (cos(y*a) + i*sin(y*a))
 */
template <class TYPE>
TComplexBase<TYPE> pow(const TComplexBase<TYPE>& complexNo,const int& Power)
{
const TComplexBase<TYPE> _ccZero(0,0);

if (complexNo == _ccZero)  //X**0 = 1;  0**y = 0
  return Power == 0 ? TComplexBase<TYPE>(1,0) : _ccZero;

if (complexNo.imag() == 0)
  {
  if (complexNo.real() < 0)
    return pow(complexNo, TComplexBase<TYPE>(Power,0));
  else
    return TComplexBase<TYPE>(::pow(complexNo.real(),(TYPE)Power), 0);
  }

TYPE Rho  = (TYPE)::pow(abs(complexNo),Power);
TYPE Angle = (TYPE)Power * arg(complexNo);

return TComplexBase<TYPE>(Rho * ::cos(Angle), Rho * ::sin(Angle));
}

//sin()------------------------------------------------------------------------
/*Returns the sine of a complex number.
    {html:<BR><IMG SRC="Res/eqPhasorCiS.gif" BORDER="0">}

    Z = x +iy
    sin(Z) = sin(x)*cosh(y) + i*cos(y)*sinh(x)
 */
template <class TYPE>
TComplexBase<TYPE> sin(const TComplexBase<TYPE>& complexNo)
{
TYPE eI  = exp(complexNo._ccI);
TYPE e_negI = 1 / eI;
return TComplexBase<TYPE>(sin(complexNo._ccR)*(e_negI+eI)/2, cos(complexNo._ccR)*(e_negI-eI)/(-2));
}

//sinh()-----------------------------------------------------------------------
/*Returns the hyperbolic sine of a complex number.

    Z = x +iy
    sinh(Z) = (e**Z - e**(-Z)) / 2  = sinh(x)*cos(y) + i*cosh(x)*sin(y)
 */
template <class TYPE>
TComplexBase<TYPE> sinh(const TComplexBase<TYPE>& complexNo)
{
TYPE eR = exp(complexNo._ccR);
TYPE e_negR = 1 / eR;
return TComplexBase<TYPE>(cos(complexNo._ccI)*(eR - e_negR)/2, sin(complexNo._ccI)*(eR + e_negR)/2);
}

//sqrt()-----------------------------------------------------------------------
/*Returns the square root of complex number Z
    {html:<BR><IMG SRC="Res/eqPhasorej.gif" BORDER="0">}

    Z = |Z|*e**(ia) 
    sqrt(Z) = sqrt(|Z|)*e(ia/2) = sqrt(|Z|) * ( cos(a/2) + i*sin(a/2) )
 */
template <class TYPE>
TComplexBase<TYPE> sqrt(const TComplexBase<TYPE>& complexNo)
{
return polar(sqrt(abs(complexNo)), arg(complexNo) / 2);
}

///////////////////////////////////////////////////////////////////////////////
// Mathematical and logical operators with two complex numbers

//operator+()------------------------------------------------------------------
/*Sums two complex numbers

  Example:
    #include "KComplxB.h"
    #include <IOManip.h>
    int main()
      {
      TComplexBase<int> z1(3, 4);
      cout << '(' << z1.real() << ',' << z1.imag() << ')' << endl;
      TComplexBase<int> z2(1, 1);
      cout << '(' << z2.real() << ',' << z2.imag() << ')' << endl;
      z1 = z1 + z2;
      cout << '(' << z1.real() << ',' << z1.imag() << ')' << endl;
      return 0;
      }
   */
template<class TYPE>
inline TComplexBase<TYPE> operator + (const TComplexBase<TYPE>& X, 
                                      const TComplexBase<TYPE>& Y
                                      )
{
return TComplexBase<TYPE>( X._ccR + Y._ccR, X.imag() + Y.imag() );
}

template<class TYPE>
inline TComplexBase<TYPE> operator + (const TComplexBase<TYPE>& complexNo, 
                                      const TYPE& dReal)
{
return TComplexBase<TYPE>(complexNo._ccR + dReal,complexNo.imag() );
}

template<class TYPE>
inline TComplexBase<TYPE> operator + (const TYPE& dReal,        //real number
                            const TComplexBase<TYPE>& complexNo //complex number
                            )
{
return TComplexBase<TYPE>(dReal+complexNo._ccR,complexNo.imag());
}

//operator-()------------------------------------------------------------------
/*Subtracts two complex numbers
 */
template<class TYPE>
inline TComplexBase<TYPE> operator - (const TComplexBase<TYPE>& X,
                                      const TComplexBase<TYPE>& Y)
{
return TComplexBase<TYPE>(X._ccR - Y._ccR, X.imag() - Y.imag());
}

template<class TYPE>
inline TComplexBase<TYPE> operator - (const TComplexBase<TYPE>& complexNo, 
                                      const TYPE& dReal)
{
return TComplexBase<TYPE>(complexNo._ccR - dReal,complexNo.imag());
}

template<class TYPE>
inline TComplexBase<TYPE> operator - (const TYPE& dReal,        //real number
                            const TComplexBase<TYPE>& complexNo //complex number
                            )
{
return TComplexBase<TYPE>( dReal-complexNo._ccR, -complexNo.imag() );
}

//operator*()------------------------------------------------------------------
/*Multiplies two complex numbers. Returns Z = X * Y
 */
template<class TYPE>
inline TComplexBase<TYPE> operator * (const TComplexBase<TYPE>& X,
                                      const TComplexBase<TYPE>& Y)
{
return TComplexBase<TYPE>( X._ccR*Y._ccR - X.imag()*Y.imag(), X.imag()*Y._ccR + X._ccR*Y.imag());
}

template<class TYPE>
inline TComplexBase<TYPE> operator * (const TComplexBase<TYPE>& complexNo, 
                                      const TYPE& dReal)
{
return TComplexBase<TYPE>(complexNo._ccR * dReal,complexNo.imag() * dReal);
}

template<class TYPE>
inline TComplexBase<TYPE> operator * (const TYPE& dReal,        //real number
                            const TComplexBase<TYPE>& complexNo //complex number
                            )
{
return TComplexBase<TYPE>( dReal*complexNo._ccR, dReal*complexNo.imag() );
}

//operator/()------------------------------------------------------------------
/*Divides two complex numbers. Returns Z = X / Y
 */
template<class TYPE>
TComplexBase<TYPE> operator / (const TComplexBase<TYPE>& X, 
                               const TComplexBase<TYPE>& Y)
{
return TComplexBase<TYPE>(X)/=Y;
}

template<class TYPE>
inline TComplexBase<TYPE> operator / (const TComplexBase<TYPE>& complexNo, 
                                      const TYPE& dReal)
{
return TComplexBase<TYPE>(complexNo.real() / dReal,complexNo.imag() / dReal);
}

template<class TYPE>
TComplexBase<TYPE> operator / (const TYPE& dReal,
                               const TComplexBase<TYPE>& complexNo)
{
dReal /= norm(complexNo);
return TComplexBase<TYPE>(dReal * complexNo.real(), - dReal * complexNo.imag());
}

///////////////////////////////////////////////////////////////////////////////
// Comparison

//operator==()-----------------------------------------------------------------
/*Returns nonzero if equal; otherwise 0.
 */
template<class TYPE>
inline BOOL operator == (const TComplexBase<TYPE>& X,const TComplexBase<TYPE>& Y)
{
return (X.real() == Y.real()  &&  X.imag() == Y.imag());
}

template<class TYPE>
inline BOOL operator == (const TComplexBase<TYPE>& complexNo, TYPE dReal)
{
return(complexNo.imag() == (TYPE)0  && complexNo.real() == dReal);
}

template<class TYPE>
inline BOOL operator == (TYPE dReal,const TComplexBase<TYPE>& complexNo)
{
return(complexNo.imag() == (TYPE)0  &&  dReal==complexNo.real() );
}

//operator!=()-----------------------------------------------------------------
/*Returns nonzero if not equal; otherwise 0.
 */
template<class TYPE>
inline BOOL operator != (const TComplexBase<TYPE>& X,const TComplexBase<TYPE>& Y)
{
return (X.real() != Y.real()  ||  X.imag() != Y.imag());
}

template<class TYPE>
inline BOOL operator != (const TComplexBase<TYPE>& complexNo, TYPE dReal)
{
return (complexNo.imag() != (TYPE)0  || complexNo.real() != dReal);
}

template<class TYPE>
inline BOOL operator != ( TYPE dReal,const TComplexBase<TYPE>& complexNo )
{
return(complexNo.imag() != (TYPE)0  ||  dReal!=complexNo.real());
}

///////////////////////////////////////////////////////////////////////////////
// Stream I/O operators

#ifdef _STL_ //Use Standard Template Library (STL)

  #include "KOStream.h"  //ostream template

  //operator<<()---------------------------------------------------------------
  /*Writes the complexNo to the output stream.

    Note: uses Standard Template Library (STL).
  */
  template<class TYPE>
  ostream & operator<<(ostream& outStream, //[out] output stream
                      TComplexBase<TYPE>& complexNo //[in] value to write
                      )
  {
  return Stream << "(" << complexNo.real() << ", " << complexNo.imag() << ")";
  }

  //operator>>()---------------------------------------------------------------
  /*Reads a complexNo from the input stream. Expected format of the complex
    number is: 
    
      (real_part,imaginary_part).
      
    Note: uses Standard Template Library (STL).  
  */
  template<class TYPE>
  istream& operator>>(istream& Stream, //[in] input stream
                      TComplexBase<TYPE>& complexNo //[out] extracted value
                      )
  {
  TYPE dReal = 0, dImag = 0;
  char ch = 0;

  Stream >> ch;
  if (ch == '(') 
    {
    Stream >> dReal >> ch;
    if (ch == ',') 
      Stream >> dImag >> ch;
    if (ch != ')') 
      Stream.clear(ios::badbit | Stream.rdstate());
    }
  else 
    {
    Stream.putback(ch);
    Stream >> dReal;
    }

  if (Stream)
    { 
    complexNo.real(dReal);
    complexNo.imag(dImag);
    }
  return Stream;
  }

#endif //_STL_
///////////////////////////////////////////////////////////////////////////////
#endif  //_KCOMPLXB_H_

/*///////////////////////////////////////////////////////////////////////////*/
/******************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         7/19/01 11:52:57 PM  Darko           VSS tags
 *  3    Biblioteka1.2         7/7/01 11:10:11 PM   Darko           $Revision: 9$
 *       inserted
 *  2    Biblioteka1.1         6/8/01 10:49:19 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:55:42 PM   Darko           
 * $
 *****************************************************************************/
