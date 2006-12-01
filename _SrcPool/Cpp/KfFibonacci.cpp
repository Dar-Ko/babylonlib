/*$Workfile: KfFibonacci.cpp$: header file
  $Revision: 3$ $Date: 2005-04-20 12:09:55$
  $Author: Darko Kolakovic$

  Fibonacci sequence
  Copyright: CommonSoft Inc.
  1996-04 Darko Kolakovic
 */

// Group=Mathematics

#include <math.h>
#include "KMathCst.h" //Golden Mean

//-----------------------------------------------------------------------------
/*{html:
  Computes the n-th Fibonacci number. Fibonacci numbers form a sequence defined
  recursively by:

    <br /><img src="Images/eqFibonacci.gif"
     alt="F(n) = F(n-2) + F(n-1); F(0) = 0; F(1) = F(2) = 1;" border="0">,<br/>
  The size of the sequence is limited with with the biggest representable number.

  The simplified de Moivre's (aka Binet's) formula is used to calculate the
  n-th Fibonacci number:
  <pre>
        F(n) = round( &Phi;<sup>n</sup> / &radic;5 )
        provided n &ge; 0.
  </pre>

  The first few Fibonacci numbers for n = 0, 1, 2, 3,... are
    0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597,
    2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418,
    317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465,
    14930352, 24157817, 39088169

  Returns: F(n) = F(n-1) + F(n-2), F(0) = 0, F(1) = 1, F(2) = 1, ...

  See also: Golden Mean, CST_PHI, Abraham de Moivre (1667-1754)
  }
 */
double funcFibonnaci(unsigned int nValue //[in] positive integer in range[0, M]
                   )
{
double dResult;
const double PHI = CST_PHI;             /*Golden Mean PHI = (1+sqrt(5))/2 */
const double ROOT_5 = 2.23606797749979; /*constant = sqrt(5);             */

/*de Moivre's (aka Binet's) formula is used to calculate a Fibonacci number */
dResult = pow(PHI, (double)nValue) / ROOT_5;

return Round(dResult);
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-07-09 01:40:17  Darko
 * $
 *****************************************************************************/

