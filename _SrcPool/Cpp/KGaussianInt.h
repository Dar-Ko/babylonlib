/*$Workfile: KGaussianInt.h$: header file
  $Revision: 1$ $Date: 2005-06-21 16:46:35$
  $Author: Darko Kolakovic$

  Gaussian Integer class
  Copyright: CommonSoft Inc.
  2005-06-20 Darko Kolakovic
 */
// Group=Mathematics

#ifndef _KGAUSSIANINT_H_
    //$Workfile: KGaussianInt.h$ sentry
  #define _KGAUSSIANINT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#if !defined(_STL) && !defined (_USE_STL)
  #include "KComplxB.h"  //TComplexBase template

///////////////////////////////////////////////////////////////////////////////
/*{html:
  Gaussian integer is a complex number <i>x+iy</i> whose real and imaginary parts
  are integers <img src="Images/eqGaussIntSet.gif" alt="{x+iy|x, y E Z}">.
  Gaussian integers form a ring often denoted <i><b>Z</b>[i]</i>.
  The sum, difference, and product of two Gaussian integers are also Gaussian
  integers. Division of two Gaussian integers A/B is a Gaussian integer only if
  there is an Gaussian integer C such that AC=B.
  }
  History: Gauss, Carl Friedrich [1777-1855]
 */
typedef template <> class TComplexBase<int> CGausssianInt;

#else //Use Standard Template Library (STL)
  #include <complex>

///////////////////////////////////////////////////////////////////////////////
/*{html:
  Gaussian integer is a complex number <i>x+iy</i> whose real and imaginary parts
  are integers <img src="Images/eqGaussIntSet.gif" alt="{x+iy|x, y E Z}">.
  Gaussian integers form a ring often denoted <i><b>Z</b>[i]</i>.
  The sum, difference, and product of two Gaussian integers are also Gaussian
  integers. Division of two Gaussian integers A/B is a Gaussian integer only if
  there is an Gaussian integer C such that AC=B.
  }
  History: Gauss, Carl Friedrich [1777-1855]
 */
typedef template <> class std::complex<int> CGausssianInt;

#endif //_STL_
///////////////////////////////////////////////////////////////////////////////
#endif  //_KGAUSSIANINT_H_

/*///////////////////////////////////////////////////////////////////////////*/
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-06-21 16:46:35  Darko Kolakovic 
 * $
 *****************************************************************************/
