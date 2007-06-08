/*$Workfile: TestComplex.h$: header file
  $Revision: 6$ $Date: 2007-06-08 17:56:11$
  $Author: Darko Kolakovic$

  Complex Numbers
  Copyright (C) 1995-2004, Rene Brun and Fons Rademakers
  Federico Carminati   22/04/2004
  Darko Kolakovic 2007-06-07 additional functions
*/

// Group=Examples

#ifndef _TESTCOMPLEX_H_
  //$Workfile: TestComplex.h$ sentry
  #define _TESTCOMPLEX_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <ostream>
#include <iomanip>    //std::endl

#include <float.h> //finite(), isnan()

#ifndef M_LOG2E
  #define M_LOG2E   1.4426950408889634073599246810018922
#endif

////////////////////////////////////////////////////////////////////////////////
// Helper functions
inline double TsSign(double a, double b)
  {
  return (b >= 0) ? abs(a) : -abs(a);
  }

inline double TsAbs(double d)
  {
  return (d >= 0) ? d : -d;
  }

inline double TsPi()
  {
  return 3.14159265358979323846;
  }

inline double TsMin(double a, double b)
  {
  return a <= b ? a : b;
  }

inline double TsMax(double a, double b)
  {
  return a >= b ? a : b;
  }

inline double TsATan2(double y, double x)
  {
  if (x != 0)
    return  ::atan2(y, x);
  if (y == 0)
    return  0;
  if (y >  0)
    return  TsPi()/2;
  else
    return -TsPi()/2;
  }

////////////////////////////////////////////////////////////////////////////////
//TsComplexD class handles numbers in complex domain |Z| = R + jI. Real and
//imaginary parts are stored with double precision.
//This class is used to validate results of complex number arithmetic.
class TsComplexD
{
public:
  double m_fRe;    //real part
  double m_fIm;    //imaginary part

public:
  // ctors and dtors
  TsComplexD();
  TsComplexD(double re, double im=0, bool polar = false);
  virtual ~TsComplexD();

  // constants
  static TsComplexD I();
  static TsComplexD One();

  // getters and setters
  double Re() const;
  double Im() const;
  double Rho() const;
  double Rho2() const;
  double Theta() const;

  // Simple operators complex - complex
  TsComplexD operator *(const TsComplexD & c) const;
  TsComplexD operator +(const TsComplexD & c) const;
  TsComplexD operator /(const TsComplexD & c) const;
  TsComplexD operator -(const TsComplexD & c) const;

  TsComplexD operator *=(const TsComplexD & c);
  TsComplexD operator +=(const TsComplexD & c);
  TsComplexD operator /=(const TsComplexD & c);
  TsComplexD operator -=(const TsComplexD & c);

  TsComplexD operator -();
  TsComplexD operator +();

  // Simple operators complex - double
  TsComplexD operator *(double c) const;
  TsComplexD operator +(double c) const;
  TsComplexD operator /(double c) const;
  TsComplexD operator -(double c) const;

  // Simple operators double - complex
  friend TsComplexD operator *(double d, const TsComplexD & c);
  friend TsComplexD operator +(double d, const TsComplexD & c);
  friend TsComplexD operator /(double d, const TsComplexD & c);
  friend TsComplexD operator -(double d, const TsComplexD & c);

  // Convertors
  operator double () const;
  operator float  () const;
  operator int    () const;

  static double Abs(const TsComplexD &c);

  static TsComplexD Sqrt(const TsComplexD &c);

  static TsComplexD Exp(const TsComplexD &c);
  static TsComplexD Exp10(const TsComplexD &c);
  static TsComplexD Log(const TsComplexD &c);
  static TsComplexD Log2(const TsComplexD &c);
  static TsComplexD Log10(const TsComplexD &c);

  static TsComplexD Sin(const TsComplexD &c);
  static TsComplexD Cos(const TsComplexD &c);
  static TsComplexD Tan(const TsComplexD &c);

  static TsComplexD ASin(const TsComplexD &c);
  static TsComplexD ACos(const TsComplexD &c);
  static TsComplexD ATan(const TsComplexD &c);

  static TsComplexD SinH(const TsComplexD &c);
  static TsComplexD CosH(const TsComplexD &c);
  static TsComplexD TanH(const TsComplexD &c);

  static TsComplexD ASinH(const TsComplexD &c);
  static TsComplexD ACosH(const TsComplexD &c);
  static TsComplexD ATanH(const TsComplexD &c);

  static TsComplexD Power(const TsComplexD& x, const TsComplexD& y);
  static TsComplexD Power(const TsComplexD& x, double y);
  static TsComplexD Power(double x, const TsComplexD& y);
  static TsComplexD Power(const TsComplexD& x, int y);

  static bool Finite(const TsComplexD& c);
  static bool IsNaN(const TsComplexD& c);

  static TsComplexD Min(const TsComplexD &a, const TsComplexD &b);
  static TsComplexD Max(const TsComplexD &a, const TsComplexD &b);
  static TsComplexD Normalize(const TsComplexD &c);
  static TsComplexD Conjugate(const TsComplexD &c);
  static TsComplexD Range(const TsComplexD &lb, const TsComplexD &ub, const TsComplexD &c);
  
  static TsComplexD CstI(const TsComplexD &c);
  static TsComplexD log2(const TsComplexD &c);
  static TsComplexD cot(const TsComplexD& z);
  static TsComplexD arccot(const TsComplexD& z);
  static TsComplexD arsech(const TsComplexD& z);
  static TsComplexD coth(const TsComplexD& z);
  static TsComplexD arcoth(const TsComplexD& z);
  static TsComplexD polar(const double mag, const double ang);
  
  // I/O
  #if defined (_STL) || defined (_USE_STL)
    //friend ostream& operator<<(ostream& out, const TsComplexD& c);
    //friend istream& operator>>(istream& in, TsComplexD& c);
    //friend wostream& operator<<(wostream& out, const TsComplexD& c);
    //friend wistream& operator>>(wistream& in, TsComplexD& c);
  #endif //_STL
};
////////////////////////////////////////////////////////////////////////////////
// Inlines

inline TsComplexD::TsComplexD():
  m_fRe(0), m_fIm(0)
  {
  }

//TsComplexD::TsComplexD(double re, double im=0, bool polar/*=false*/)

inline TsComplexD::~TsComplexD()
  {
  }

  // constants
inline TsComplexD TsComplexD::I()
  {
  return TsComplexD(0,1);
  }

inline TsComplexD TsComplexD::One()
  {
  return TsComplexD(1,0);
  }

// getters and setters
inline double TsComplexD::Re() const
  {
  return m_fRe;
  }

inline double TsComplexD::Im() const
  {
  return m_fIm;
  }

inline double TsComplexD::Rho() const
  {
  return sqrt(m_fRe*m_fRe+m_fIm*m_fIm);
  }

inline double TsComplexD::Rho2() const
  {
  return m_fRe*m_fRe+m_fIm*m_fIm;
  }

//The template function returns the phase angle of x.
inline double TsComplexD::Theta() const
  {
  return (m_fIm != 0.0 || m_fRe != 0.0) ? TsATan2(m_fIm, m_fRe) : 0;
  }

inline TsComplexD::TsComplexD(double x, double y, bool polar /*=false*/)
  {
  if (polar)
    {
    m_fRe = x*cos(y);
    m_fIm = x*sin(y);
    }
  else
    {
    m_fRe = x;
    m_fIm = y;
    }
  }

inline TsComplexD::operator double () const
  {
  return m_fRe;
  }
inline TsComplexD::operator float  () const
  {
  return static_cast<float>(m_fRe);
  }
inline TsComplexD::operator int    () const
  {
  return static_cast<int>(m_fRe);
  }

// Simple operators complex - complex
inline TsComplexD TsComplexD::operator *(const TsComplexD & c) const
  {
  return TsComplexD(m_fRe*c.m_fRe - m_fIm*c.m_fIm, 
                    m_fRe*c.m_fIm + m_fIm*c.m_fRe);
  }

inline TsComplexD TsComplexD::operator +(const TsComplexD & c) const
  {
  return TsComplexD(m_fRe+c.m_fRe, m_fIm+c.m_fIm);
  }

inline TsComplexD TsComplexD::operator /(const TsComplexD & c) const
  {
  return TsComplexD(m_fRe*c.m_fRe+m_fIm*c.m_fIm,
                    -m_fRe*c.m_fIm+m_fIm*c.m_fRe) / c.Rho2();
  }

inline TsComplexD TsComplexD::operator -(const TsComplexD & c) const
  {
  return TsComplexD(m_fRe-c.m_fRe, m_fIm-c.m_fIm);
  }

inline TsComplexD TsComplexD::operator *=(const TsComplexD & c)
  {
  return ((*this) = (*this) * c);
  }

inline TsComplexD TsComplexD::operator +=(const TsComplexD & c)
  {
  return ((*this) = (*this) + c);
  }

inline TsComplexD TsComplexD::operator /=(const TsComplexD & c)
  {
  return ((*this) = (*this) / c);
  }

inline TsComplexD TsComplexD::operator -=(const TsComplexD & c)
  {
  return ((*this) = (*this) - c);
  }


inline TsComplexD TsComplexD::operator -()
  {
  return TsComplexD(-m_fRe,-m_fIm);
  }

inline TsComplexD TsComplexD::operator +()
  {
  return *this;
  }

// Simple operators complex - double
inline TsComplexD TsComplexD::operator *(double c) const
  {
  return TsComplexD(m_fRe*c,m_fIm*c);
  }

inline TsComplexD TsComplexD::operator +(double c) const
  {
  return TsComplexD(m_fRe+c, m_fIm);
  }

inline TsComplexD TsComplexD::operator /(double c) const
  {
  return TsComplexD(m_fRe/c,m_fIm/c);
  }

inline TsComplexD TsComplexD::operator -(double c) const
  {
  return TsComplexD(m_fRe-c, m_fIm);
  }

inline double TsComplexD::Abs(const TsComplexD &c)
  {
  return c.Rho();
  }
  //The function returns the square root of x, with phase angle in the half-open interval (-pi/2,
  //pi/2]. The branch cuts are along the negative real axis.
inline TsComplexD TsComplexD::Sqrt(const TsComplexD &c)
  {
  return TsComplexD(sqrt(c.Rho()),0.5*c.Theta(),true);
  }

//The function returns the exponential of c e^c
inline TsComplexD TsComplexD::Exp(const TsComplexD &c)
  {
  return TsComplexD(exp(c.m_fRe), c.m_fIm,true);
  }

//The template function returns the logarithm of x. 
//The branch cuts are along the negative real axis.
inline TsComplexD TsComplexD::Log(const TsComplexD &c)
  {
  return TsComplexD(0.5*log(c.Rho2()),c.Theta());
  }

inline TsComplexD TsComplexD::Log2(const TsComplexD &c)
  {
  return Log(c)/::log(2.);
  }

//The template function returns the base 10 logarithm of x.
//The branch cuts are along the negative real axis.
inline TsComplexD TsComplexD::Log10(const TsComplexD &c)
  {
  return Log(c)/::log(10.);
  }

//The function returns the imaginary sine of x.
inline TsComplexD TsComplexD::Sin(const TsComplexD &c)
  {
  return TsComplexD(sin(c.m_fRe)*::cosh(c.m_fIm),
                    cos(c.m_fRe)*::sinh(c.m_fIm));
  }

//The function returns the cosine of x.
inline TsComplexD TsComplexD::Cos(const TsComplexD &c)
  {
  return TsComplexD(cos(c.m_fRe)*::cosh(c.m_fIm),
                    -sin(c.m_fRe)*::sinh(c.m_fIm));
  }

inline TsComplexD TsComplexD::Tan(const TsComplexD &c)
  {
  TsComplexD cc=Cos(c);
  return Sin(c) * TsComplexD::Conjugate(cc)/cc.Rho2();
  }


inline TsComplexD TsComplexD::ASin(const TsComplexD &c)
  {
  return -TsComplexD::I()*Log(TsComplexD::I()*c+ TsSign(1.,c.Im())*Sqrt(1.-c*c));
  }

inline TsComplexD TsComplexD::ACos(const TsComplexD &c)
  {
  return -TsComplexD::I()*Log(c+TsSign(1.,c.Im())*Sqrt(c*c-1.));
  }

inline TsComplexD TsComplexD::ATan(const TsComplexD &c)
  {
  return -0.5*TsComplexD::I()*Log((1.+TsComplexD::I()*c)/(1.-TsComplexD::I()*c));
  }

//The function returns the hyperbolic sine of x.
inline TsComplexD TsComplexD::SinH(const TsComplexD &c)
  {
  return TsComplexD(::sinh(c.m_fRe)*cos(c.m_fIm),
                     ::cosh(c.m_fRe)*sin(c.m_fIm));
  }
  
//The function returns the hyperbolic cosine of x.
inline TsComplexD TsComplexD::CosH(const TsComplexD &c)
  {
  return TsComplexD(::cosh(c.m_fRe)*cos(c.m_fIm),
                     ::sinh(c.m_fRe)*sin(c.m_fIm));
  }

inline TsComplexD TsComplexD::TanH(const TsComplexD &c)
  {
  TsComplexD cc=CosH(c);
  return SinH(c)*TsComplexD::Conjugate(cc)/cc.Rho2();
  }


inline TsComplexD TsComplexD::ASinH(const TsComplexD &c)
  {
  return Log(c+TsSign(1.,c.Im())*Sqrt(c*c+1.));
  }

inline TsComplexD TsComplexD::ACosH(const TsComplexD &c)
  {
  return Log(c+TsSign(1.,c.Im())*Sqrt(c*c-1.));
  }

inline TsComplexD TsComplexD::ATanH(const TsComplexD &c)
  {
  return 0.5*Log((1.+c)/(1.-c));
  }

//complex number X raised to the power of complex Y.
inline TsComplexD TsComplexD::Power(const TsComplexD& x, const TsComplexD& y)
  {
  double lrho=log(x.Rho());
  double theta=x.Theta();
  return TsComplexD(exp(lrho*y.Re()-theta*y.Im()),
                     lrho*y.Im()+theta*y.Re(),true);
  }
//Complex number raised to a real power
inline TsComplexD TsComplexD::Power(const TsComplexD& x, double y)
  {
  return TsComplexD(::pow(x.Rho(),y),x.Theta()*y,true);
  }
//A number raised to a complex power
inline TsComplexD TsComplexD::Power(double x, const TsComplexD& y)
  {
  double lrho=log(TsAbs(x));
  double theta=(x>0)?0:TsPi();
  return TsComplexD(exp(lrho*y.Re()-theta*y.Im()),
                     lrho*y.Im()+theta*y.Re(),true);
  }
//Complex number raised to an integer power
inline TsComplexD TsComplexD::Power(const TsComplexD& x, int y)
  {
  return TsComplexD(::pow(x.Rho(),y),x.Theta()*y,true);
  }


inline bool TsComplexD::Finite(const TsComplexD& c)
  {
  return (::_finite(c.Re()) && ::_finite(c.Im()));
  }

inline bool TsComplexD::IsNaN(const TsComplexD& c)
  {
  return (::_isnan(c.Re()) || ::_isnan(c.Im()));
  }


inline TsComplexD TsComplexD::Min(const TsComplexD &a, const TsComplexD &b)
  {
  return a.Rho()<=b.Rho()?a:b;
  }

inline TsComplexD TsComplexD::Max(const TsComplexD &a, const TsComplexD &b)
  {
  return a.Rho()>=b.Rho()?a:b;
  }

//The function returns the squared magnitude of x.
inline TsComplexD TsComplexD::Normalize(const TsComplexD &c)
  {
  return TsComplexD(1.,c.Theta(),true);
  }

//The function returns the conjugate of x.
inline TsComplexD TsComplexD::Conjugate(const TsComplexD &c)
  {
  return TsComplexD(c.Re(),-c.Im());
  }

inline TsComplexD TsComplexD::Range(const TsComplexD &lb, const TsComplexD &ub, const TsComplexD &c)
  {
  return Max(lb,Min(c,ub));
  }
  
  //Multiplies complex number with constant Z = 0 + i;
inline TsComplexD TsComplexD::CstI(const TsComplexD &c)
  {
  return TsComplexD::I() * c;
  }

inline double arg(const TsComplexD& z) 
  {
  return z.Theta();
  }
  
//Returns the first result of binary logarithm z
inline TsComplexD TsComplexD::log2(const TsComplexD& z) 
  {
  double phi = arg(z);
  return TsComplexD (log(TsComplexD::Abs(z)) * M_LOG2E, phi * M_LOG2E);
  }

//The function returns the complex value whose magnitude is rho and whose phase angle is theta.
inline TsComplexD TsComplexD::polar(const double mag, const double ang) 
  {
  return TsComplexD(mag * cos(ang), mag * sin(ang));
  }
  
inline TsComplexD TsComplexD::cot(const TsComplexD& z) 
  {
  double r = 2.0 * z.Re();
  double i = 2.0 * z.Im();
  return TsComplexD(0.0, 1.0) + 
         TsComplexD(0.0, 2.0) / (TsComplexD::polar(exp(-i), r) - 1.0);
  }

inline TsComplexD TsComplexD::arccot(const TsComplexD& z) 
  {
  return TsComplexD(0.0, -0.5) * 
         TsComplexD::Log(TsComplexD(0.0, 2.0) / (z - TsComplexD(0.0, 1.0)) + 1.0);
  }

inline TsComplexD TsComplexD::arsech(const TsComplexD& z) 
  {
  return TsComplexD::Log((1.0 - TsComplexD::Sqrt(1.0 - z * z)) / z);
  }

inline TsComplexD TsComplexD::coth(const TsComplexD& z) 
  {
  double r = 2.0 * z.Re();
  double i = 2.0 * z.Im();
  return 1.0 + 2.0 / (TsComplexD::polar(exp(r), i) - 1.0);
  }

inline TsComplexD TsComplexD::arcoth(const TsComplexD& z) 
  {
  return 0.5 * TsComplexD::Log(2.0 / (z - 1.0) + 1.0);
  }

inline TsComplexD TsComplexD::Exp10(const TsComplexD &c)
  {
  return TsComplexD::Power(10.0, c);
  }
  
//______________________________________________________________________________
inline TsComplexD operator *(double d, const TsComplexD & c)
  {
  return TsComplexD(d*c.m_fRe,d*c.m_fIm);
  }
inline TsComplexD operator +(double d, const TsComplexD & c)
  {
  return TsComplexD(d+c.m_fRe, c.m_fIm);
  }
inline TsComplexD operator /(double d, const TsComplexD & c)
  {
  return TsComplexD(d*c.m_fRe,-d*c.m_fIm)/c.Rho2();
  }
inline TsComplexD operator -(double d, const TsComplexD & c)
  {
  return TsComplexD(d-c.m_fRe, -c.m_fIm);
  }

//______________________________________________________________________________
#if defined (_STL) || defined (_USE_STL)

  //inline ostream& operator<<(ostream& out, const TsComplexD& c)
  inline int& operator<<(int& out, const TsComplexD& c)
    {
    //out << "(" << c.m_fRe << "," << c.m_fIm << "i)";
    return out;
    }
/*
  inline istream& operator>>(istream& in, TsComplexD& c)
    {
    in >> c.m_fRe >> c.m_fIm;
    return in;
    }

  inline wostream& operator<<(wostream& out, const TsComplexD& c)
    {
    out << "(" << c.m_fRe << "," << c.m_fIm << "i)";
    return out;
    }

  inline wistream& operator>>(wistream& in, TsComplexD& c)
    {
    in >> c.m_fRe >> c.m_fIm;
    return in;
    }*/
#endif //_STL

#endif //_TESTCOMPLEX_H_
////////////////////////////////////////////////////////////////////////////////
/*$Log: 
/* 6    Biblioteka1.5         2007-06-08 17:56:11  Darko Kolakovic New test cases
/* 5    Biblioteka1.4         2007-06-04 16:58:00  Darko Kolakovic Fixed
/*      validation of NaNs
/* 4    Biblioteka1.3         2007-06-01 17:34:53  Darko Kolakovic Test cases
/* 3    Biblioteka1.2         2007-05-31 16:41:23  Darko Kolakovic Test NaN
/* 2    Biblioteka1.1         2007-05-29 16:37:38  Darko Kolakovic Inserted
/*      complex number validation
/* 1    Biblioteka1.0         2007-05-29 11:59:25  Darko Kolakovic 
/*$
 */
/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *      GNU LESSER GENERAL PUBLIC LICENSE                                *
 *         Version 2.1, February 1999                                    *
 *************************************************************************/
/*CERN ROOT Object Oriented Framework For Large Scale Data Analysis
  http://root.cern.ch/
 */