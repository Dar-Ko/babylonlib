/*$Workfile: KfNewtRp.cpp$: implementation file
  $Revision: 7$ $Date: 2004-06-01 16:55:06$
  $Author: Darko$

  Solve an equation using Newton-Raphson iteration method
  Jul 99 Darko Kolakovic
*/

/* Group=Mathematics                                                         */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifndef __cplusplus
  #error requires C++ compilation (use a .cpp suffix)
#endif

#ifndef ASSERT
  #include "KTrace.h" //ASSERT macro
#endif


#include <Math.h>       //fabs()
#ifndef bool
  #include "KTypedef.h" //bool
#endif
#include "KProgCst.inl" //IsZero()

#ifdef _MSC_VER //Microsoft C/C++ compiler
  #pragma warning( push, 3 )
    //warning C4127: conditional expression is constant
  #pragma warning(disable: 4217)
#endif

 //type definition of function y = f(x) used in numerical analyses
typedef double (*PFUNC_Y_OF_X) (double);

//funcNewtonRaphson()----------------------------------------------------------
/*Calculates the root of a differentiable function
  {html: <IMG SRC="Res/eqFuncXis0.gif" ALT="f(x) = 0" BORDER="0"> <BR>}
  The method requires the evaluation of both the function f(x), and the
  derivative y' = f'(x), at arbitrary points x.
  The Newton-Rahson method approximates the function f(x) with the tangent line
  at arbitrary point x[n]. By extending the line until it crosses the abscissa,
  we are getting an approximation of the root r = f(x) = 0.
  {html: <BR><IMG SRC="Res/graphdYdX.gif" ALT="f'(x[n]) = dy/dx[n] = 0" BORDER="0"> <BR>}

  Assuming that {html: <BR><IMG SRC="Res/eqFuncRdiff0.gif" ALT="f'(r) != 0" BORDER="0">,<BR>}
  The better approximation of the root is the zero of the tangent line at the
  first approximation x[1].
  {html: <BR><IMG SRC="Res/eqFuncx2isx1-y.gif" ALT="x[2] = x[1] - f(x[1]) / f'(x[1])" BORDER="0">,<BR>}
  In n successive approximations we will get the root
  {html: <BR><IMG SRC="Res/eqFuncXis0.gif" ALT="f(x) = 0" BORDER="0"> <BR>}
  The general iterative formula for this method would be:
  {html: <BR><IMG SRC="Res/eqFuncxN1isxN-y.gif" ALT="x[n+1] = x[n] - f(x[n]) / f'(x[n])" BORDER="0">,<BR>}

  The Newton-Raphson method converge quadratically to the root r.

  Returns: true and approximation of the function's root or false if the root
  could not be found in iMaxIter iterations.
 */
bool funcNewtonRaphson(PFUNC_Y_OF_X funcX,     //[in] function y = f(x)
                       PFUNC_Y_OF_X funcdy_dx, //[in] first derivative function y' = f(dy/dx); y = f(x).
                       double dEstimate,       //[in] initial approximation x(0)
                       const double dError,    //[in] allowed absolute error
                       int iMaxIter,   //[in] maximum number of iterations
                       double& dResult //[out] an approximate value of the root f(x) = 0
                       )
{
ASSERT(funcX != NULL);
ASSERT(funcdy_dx != NULL);
ASSERT(dError > 0); //absolute distance from the root


  //Calculate the root in iMaxIter iterations
while(iMaxIter > 0)
  {
  dResult = funcX(dEstimate); //Get y = f(x)
  //Check if the result is close enough
  if(fabs(dResult) <= dError)
      {
      dResult = dEstimate;
      return true;
      }

  double dy = funcdy_dx(dEstimate); //Get y' = f'(x) = dy/dx
  if(!IsZero(dy)) //Get new starting point
    //Calculate x[n+1] = x[n] - f(x[n]) / f'(x[n])
    dEstimate -= dResult/dy;
  else
    {
      //y' is 0 and dEstimate have to be changed
    break;
    }
  iMaxIter--;
  }

return false; //failed after iMaxIter iterations
}

/*The derivative dy/dx is aproximated with:

     (y[n+1] - y[n])/(x[n+1] - x[n]) = (y[n+1] - y[n])/Dx
 */
bool funcNewtonRaphson(PFUNC_Y_OF_X funcX,     //[in] function y = f(x)
                       const double Dx,        //[in] estimate increment Dx = x[n+1] - x[n].
                       double dEstimate,       //[in] initial approximation x(0)
                       const double dError,    //[in] allowed absolute error
                       int iMaxIter,   //[in] maximum number of iterations n
                       double& dResult //[out] an approximate value of the root f(x) = 0
                       )
{
ASSERT(funcX != NULL);
ASSERT(Dx > 0);
ASSERT(dError > 0); //absolute distance from the root


  //Calculate the root in iMaxIter iterations
while(iMaxIter > 0)
  {
  dResult = funcX(dEstimate); //Get y = f(x)
  //Check if the result is close enough
  if(fabs(dResult) <= dError)
      {
      dResult = dEstimate;
      return true;
      }

  double dy = dResult - funcX(dEstimate-Dx); //Get y[n+1] = f(x[n+1]) = f(x[n] - Dx)
  if(!IsZero(dy)) //Get new starting point
    //Calculate x[n+1] = x[n] - f(x[n]) / {(f(x[n+1])-f(x[n]))/(x[n+1]-x[n])}
    dEstimate -= dResult*Dx/dy;
  else
    {
      //y' is 0 and dEstimate have to be changed
    break;
    }
  iMaxIter--;
  }

return false; //failed after iMaxIter iterations
}

///////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER //Microsoft C/C++ compiler
    //warning C4127: conditional expression is constant
  #pragma warning(default: 4217)
  #pragma warning( pop )
#endif

/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         26/07/2001 9:34:39 PMDarko           Comment
 *  1    Biblioteka1.0         20/07/2001 12:51:23 AMDarko
 * $
 *****************************************************************************/
