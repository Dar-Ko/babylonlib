/*$Workfile: H:\_SrcPool\Cpp\Samples\Numeric\TestNewtonRaphson.cpp$: implementation file
  $Revision: 4$ $Date: 8/3/02 7:27:44 PM$
  $Author: Darko$

  Test of solving equations
  CommonSoft Inc.
  Mar 2k1. D.Kolakovic
*/
// Group=Examples

#include <IOStream>   //std::cout
#include <IOManip.h>  //std::endl

#define BOOL int
//#define FALSE false
//#define TRUE true
#include "KProgCst.inl" //IsNaN()

 //type definition of function y = f(x) used in numerical analyses
typedef double (*PFUNC_Y_OF_X) (double);


///////////////////////////////////////////////////////////////////////////////
// Equatations to solve

const double A1 = 5.;

//eqtLin()-------------------------------------------------------------------
/*Return values of linear equation y = f(x) = (x - A1).
  y = 0 for x =  A1 = 5.
 */
double eqtLin(double x) 
{
return  x - A1;
}

/*Derivative of function y = (x - A1) 
  y' = f'(x) = 1
 */ 
double eqtDerivativeLin(double x)
{
return 1.0;
}

//eqtCube()-------------------------------------------------------------------
const double A = 2.0;
const double B = 7.0;
/*Return values of cube equation y = f(x) = (x^3 + A*exp(x) + B).
  If A = 2 and B = 7, one of solutions is y = 0 for x = -1.9387.
 */
double eqtCube(double x) 
{
return x*x*x + A * exp(x) + B;
}

/*Derivative of function y = (x^3 + A*exp(x) + B)
  y' = f'(x) = (3*x^2 + A*exp(x))
 */ 
double eqtDerivativeCube(double x)
{
return x*x*3.0 + A * exp(x);
}

//eqtSqrt()-------------------------------------------------------------------
/*Find square root of a constant. To find a root following function is defined:
   y = f(x) = X*X - A1. If  f(x) = 0, then x = sqrt(A1).
   If A1 = 5, X = sqrt(5) = 2.23606707
 */
double eqtSqrt(double x) 
{
return x*x - A1;
}

/*Derivative of function y = (X*X - A1)
  y' = f'(x) = 2*x.
 */ 
double eqtDerivativeSqrt(double x)
{
return x * 2.0;
}

//eqtCos()--------------------------------------------------------------------
/*Return values of trigonometric equation y = f(x) = (cos(x) - x).
  One of solutions is: y = 0 for x = 0.7390851.
 */
double eqtCos(double x)
{
return cos(x) -x;
} 

/*Derivative of function y = (cos(x) - x)
  y' = f'(x) = -sin(x) - 1.
 */ 
double eqtDerivativeCos(double x)
{
return -sin(x) - 1.0;
}

//eqtSquare()-----------------------------------------------------------------
double C = -6.0;
/*Return values of square equation y = f(x) = (x*x + C).
  Solutions are: y = 0 for  x = +/- 2.44949 and  C < 0 ;
                            x = +/- i*2.44949 and  C > 0  where i = sqrt(-1)
 */
double eqtSquare(double x)
{
return x*x + C;  
}

/*Derivative of function y = (x*x + C) = (x + 0)*x + 1 * C
  y' = f'(x) = 2*x + 0. (Horner's method)
 */ 
double eqtDerivativeSquare(double x)  
{
return 2*x;
}

///////////////////////////////////////////////////////////////////////////////


extern BOOL funcNewtonRaphson(PFUNC_Y_OF_X funcX,     //[in] function y = f(x) 
                       PFUNC_Y_OF_X funcdy_dx, //[in] first derivative function y' = f(dy/dx); y = f(x).
                       double dEstimate,       //[in] initial approximation x(0)
                       const double dError,    //[in] allowed absolute error
                       int iMaxIter,   //[in] maximum number of iterations
                       double& dResult //[out] an approximate value of the root f(x) = 0
                       );
BOOL funcNewtonRaphson(PFUNC_Y_OF_X funcX,     //[in] function y = f(x) 
                       const double Dx,        //[in] estimate increment Dx = x[n+1] - x[n].
                       double dEstimate,       //[in] initial approximation x(0)
                       const double dError,    //[in] allowed absolute error
                       int iMaxIter,   //[in] maximum number of iterations n
                       double& dResult //[out] an approximate value of the root f(x) = 0
                       );

extern BOOL funcQuadratic(double a,   //[in] coefficient 2
                   double b,   //[in] coefficient 1
                   double c,   //[in] coefficient 0
                   double& x1, //[out] first root or real part of the complex root
                   double& x2  //[out] second root or absolute value of imaginary
                               //      part of the complex root
                   );

///////////////////////////////////////////////////////////////////////////////
//TestNewtonRaphson()----------------------------------------------------------
/*Use the Newton-Raphson method to find solutions. For quadratic equations roots
  found are comapred with results of funcQuadratic function.
 */
void TestNewtonRaphson()
{
cout << "\nTestNewtonRaphson()" << endl;
double dEstimate;//[in] initial approximation x(0)
double dError;   //[in] allowed absolute error
int    iMaxIter; //[in] maximum number of iterations
double dResult;  //[out] an approximate value of the root f(x) = 0


dEstimate = -10.0;
dError    = 0.00001;   
iMaxIter  = 20; 

//f(x-A1)=0 -------------------------------------------------------------------
cout << "f(x - "<< A1 << ") = 0 ";
if (funcNewtonRaphson(eqtLin, eqtDerivativeLin, dEstimate, dError, iMaxIter, dResult))
  cout << "for x = " << dResult << endl;   
else
  cout << "Failed to find root" << endl;

//f(x^3+A*exp(x)+B)=0 ---------------------------------------------------------
cout << "f(x^3 + " << A << "*exp(x) + " << B << ") = 0 ";
if (funcNewtonRaphson(eqtCube, eqtDerivativeCube, dEstimate, dError, iMaxIter, dResult))
  cout << "for x = " << dResult << endl;   
else
  cout << "Failed to find root" << endl;

//f(cos(x)-x) = 0 -------------------------------------------------------------
cout << "f(cos(x) - x) = 0 ";
dEstimate = 0.7;
if (funcNewtonRaphson(eqtCos, eqtDerivativeCos, dEstimate, dError, iMaxIter, dResult))
  cout << "for x = " << dResult << endl;   
else
  cout << "Failed to find root" << endl;

//f(x*x - A1) = 0 -------------------------------------------------------------
cout << "f(x*x - " << A1 << ") = 0 ";
if (funcNewtonRaphson(eqtSqrt, eqtDerivativeSqrt, dEstimate, dError, iMaxIter, dResult))
  {
  cout << "for x = " << dResult << endl;   
  cout << "sqrt(" << A1 << ") = " << sqrt(A1) << endl;
  }
else
  cout << "Failed to find root" << endl;

//f(x*x + C) = 0 --------------------------------------------------------------
do
  {
  cout << "f(x*x + " << C << ") = 0" << endl;
  if (funcNewtonRaphson(eqtSquare, eqtDerivativeSquare, dEstimate, 
	                    dError, iMaxIter, dResult))
    cout << "for x = " << dResult << " (Newton-Raphson)" << endl;   
  else
    cout << "Failed to find root (Newton-Raphson)" << endl;

  double x1,x2;
  if (funcQuadratic(1.0, 0.0, C, x1, x2))
    cout << "for x1 = " << x1 << ", x2 = " << x2 << " (Square Eq)" << endl;
  else
    {
    if (IsNaN(x1))
      cout << "Failed to find roots (Square Eq)" << endl;
    else //Solutions are complex numbers
      cout << "f(z*z + "<< C << ") = 0 for z = " << x1 << " +/- i(" << x2 << ")" 
	       << " (Square Eq)" << endl;
    }

  C *= -1.0; //Get complex roots
  if ( C > 0)
    cout << endl << "Get complex roots" << endl;
  } while (C > 0);

cout << "============================" << endl;

//Incremental method ==========================================================
cout << "Newton-Raphson with increments method" << endl;

//f(x-A1)=0 -------------------------------------------------------------------
cout << "f(x - "<< A1 << ") = 0 ";
const double dIncrement = 0.1;
if (funcNewtonRaphson(eqtLin, dIncrement, dEstimate, dError, iMaxIter, dResult))
  cout << "x = " << dResult << endl;   
else
  cout << "Failed to find root" << endl;

//f(x^3+A*exp(x)+B)=0 ---------------------------------------------------------
cout << "f(x^3 + " << A << "*exp(x) + " << B << ") = 0 ";
if (funcNewtonRaphson(eqtCube, dIncrement, dEstimate, dError, iMaxIter, dResult))
  cout << "for x = " << dResult << endl;   
else
  cout << "Failed to find root" << endl;  

//f(cos(x)-x) = 0 -------------------------------------------------------------
cout << "f(cos(x) - x) = 0 ";
dEstimate = 0.7;
if (funcNewtonRaphson(eqtCos, dIncrement, dEstimate, dError, iMaxIter, dResult))
  cout << "for x = " << dResult << endl;   
else
  cout << "Failed to find root" << endl;  

//f(x*x - A1) = 0 -------------------------------------------------------------
cout << "f(x*x - " << A1 << ") = 0 ";
if (funcNewtonRaphson(eqtSqrt, dIncrement, dEstimate, dError, iMaxIter, dResult))
  cout << "for x = " << dResult << endl;
else
  cout << "Failed to find root" << endl;  

cout << "============================" << endl;
}
