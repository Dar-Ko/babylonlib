/*$Workfile: KfQuadEq.cpp$: implementation file
  $Revision: 10$ $Date: 2004-06-01 16:55:13$
  $Author: Darko$

  Solves a quadratic equation
  CommonSoft Inc.
  Mar 2k1. D.Kolakovic
*/

/* Group=Mathematics                                                         */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER //Microsoft C/C++ compiler
  #pragma warning( push, 3 )
    //warning C4514: unreferenced inline function has been removed
    //unreferenced inline function are in <math.h> 
  #pragma warning(disable: 4514)
#endif

#include <math.h>
#ifndef bool
  #include "KTypedef.h" //bool
#endif
#include "KMathCst.inl"
#include "KProgCst.inl" //NaN constants

//funcQuadratic()--------------------------------------------------------------
/*Calculates solutions of a quadratic equation.

  For the second-order polynomial equation:
  {html:<BR><IMG SRC="Res/eqQuadratic.gif"
    ALT="a*(X**2) + b*X + c = 0" BORDER="0">}


  Solutions are:

    1. a != 0; b != 0; c != 0

  {html:<BR><IMG SRC="Res/eqQuadraticRoots.gif"
    ALT="x*0.5 = (-b +\- sqrt(D))\(2*a)" BORDER="0"><BR>}
  where D is discriminant:

      D = b**2  - 4*a*c
      if D < 0 solutions are complex numbers:
       X1 = R + iI = -b/(2*a) + i(sqrt(-D))/(2*a)
       X2 = R - iI = -b/(2*a) - i(sqrt(-D))/(2*a)

    2. a != 0; b != 0; c = 0
       x1 = 0
       x2 = -b/a

    3. a != 0; b = 0; c != 0
       x1 =  sqrt(-c/a)
       x2 = -sqrt(-c/a)
      if D < 0 solutions are complex numbers:
       X1 =  iI = i(sqrt(c/a))
       X2 = -iI = -i(sqrt(c/a))

    4. a = 0; b != 0; c != 0
       x1 = -c/b
       x2 = -c/b
      (becomes linear equation)

  Note: Numerical method implemented gives in some circumstances somewhat
        unreliable solutions due limited precision, overflow and underflow,
        and some boundary conditions.

  Returns true if equation solutions are real numbers. If solutions are complex
  numbers returns false and real part as x1 , absolute value of imaginary part
  as x2 :

       X1 = R + iI = x1 + i*x2
       X1 = R - iI = x1 - i*x2

  Returns: false and signaling NaN as solution if failed to divide by zero.

  Example:

    #include <IOStream>
    #include <IOManip.h>
    #include "KProgCst.inl" //IsNaN()
    void main()
      {
      double x1,x2;
      const double A =   1.0;
      const double B =   0.0;
      const double C = -25.0;
      if (funcQuadratic(A, B, C, x1, x2))
        cout << "f(x*x + C) = 0 for x1 = " << x1 << ", x2 = " << x2 << endl;
      else
        {
        if (IsNaN(x1))
          cout << "Failed to find roots" << endl;
        else //Solutions are complex numbers
          cout << "f(z*z + C) = 0 for z = " << x1
               << " +/- i(" << x2 << ")" << endl;
        }
      }

 */
bool funcQuadratic(double a,   //[in] coefficient 2
                   double b,   //[in] coefficient 1
                   double c,   //[in] coefficient 0
                   double& x1, //[out] first root or real part of the complex root
                   double& x2  //[out] second root or absolute value of imaginary
                               //      part of the complex root
                   )
{
if(a == 0) //Linear equation
  {
  if (b != 0)
    {
    x1 = x2 = - (c/b);
    return true;
    }
  else
    {
    x1 = x2 = NaN_DSIGNAL; //signaling NaN (not a number) -1.#INF
    return false;
    }
  }
else
  {
  if (c == 0)
    {
    x1 = 0.0;
    x2 = - (b/a);
    return true;
    }
  if (b == 0)
    {
    x1 = c/a;
    if (x1 <= 0)
      {
      x1 = sqrt(-x1);
      x2 = - x1;
      return true;
      }
    else //Solutions are complex numbers
      {
      x2 = sqrt(x1);  //Absolute value of imaginary part
      x1 = 0.0;       //Real part
      return false;
      }
    }

  x1 = (SQUARE(b)) - 4*a*c; //Discriminant
  if (x1 > 0)    //Roots are unequal real numbers
    {
    //If a or c are very small numbers, then discriminant becomes close to b.
    //In that case first root is  (-b+ b')/2a and this may be within rounding
    //error. To avoid this roots are calculated as:
    //x1 = T/a ; x2 = c/T where T = (b + sgn(b)sqrt(b**2-4ac))/(-2)

    x2 = (Sign(b)*sqrt(x1)+b)*(-0.5);
    x1 = x2/a;
    x2 = c/x2;
    return true;
    }
  else if (x1 == 0) //Roots are equal real numbers
    {
    x1 = x2 = -b/(a*2);
    return true;
    }
  else     //Roots are complex numbers
    {
    a *= 2;
    x2 = sqrt(-x1)/a;   //Absolute value of imaginary part
    x1 =  -b/a;         //Real part
    return false;
    }
  }

}

///////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER //Microsoft C/C++ compiler
    //warning C4514: unreferenced inline function has been removed
    //unreferenced inline function are in <math.h> 
  #pragma warning(default: 4514)
  #pragma warning( pop )
#endif
/******************************************************************************
 *$Log:
 * 3    Biblioteka1.2         18/07/2001 11:33:03 PMDarko           VSS tags
 * 2    Biblioteka1.1         11/07/2001 10:31:24 PMDarko           Roots if
 *      coeff. are small
 * 1    Biblioteka1.0         10/07/2001 12:47:03 AMDarko
 * $
 * Jul 2k1 Roots if coeff. are small D.K.
 * Mar 2k1. D.Kolakovic
 *****************************************************************************/
