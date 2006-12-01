/*$Workfile: KRandomGauss.h$: implementation file
  $Revision: 8$ $Date: 2005-04-20 12:09:53$
  $Author: Darko Kolakovic$

  Random number generator with Gaussian distribution
  1992 ALGORITHM 712, ACM
  Mar 2k2 Darko Kolakovic
*/

#ifndef _KRANDOMGAUSS_H_
  //KRandomGauss.h sentry
  #define _KRANDOMGAUSS_H_

#include "KRandomUniform.h"  //CRandomGauss class

///////////////////////////////////////////////////////////////////////////////
/*{html:
  This class generates a normally (Gaussian) distributed random numbers.

  <img src="Images/graphGuassDistributionF.gif" alt="P(m,d*d)" border="0"> <br />

  The density and distribution of normal (Gaussian) variable are completely
  determined by the mean and variance (covariance).
  The standard deviation is defined as the square root of the variance.
  The Gaussian probability distribution with mean &mu; and standard
  deviation &delta; is a normalized Gaussian function of the form:
  <br /> <img src="Images/eqGuassDistribution.gif"
         alt="P(x)=(1/d*sqrt(2pi))exp(-(x-m)^2/(2d^2))" border="0"> <br />
  where <i>P(x)dx</i> gives the probability that a variate with
  a Gaussian distribution takes on a value in the range [<i>x,x+dx</i>].
  The distribution <i>P(x)</i> is properly normalized for
  <img src="Images/eqXeInfInf.gif"
    alt="x(-INF,INF)" border="0"> since
  <br /><img src="Images/eqIntGuassDistribution.gif"
            alt="S(P(x)dx)=1 for x(-INF,INF)" border="0"> <br />

  The algorithm uses the ratio of uniforms method of A.J. Kinderman and
  J.F. Monahan augmented with quadratic bounding curves.
  }
*/
class CRandomGauss
{
// Construction
public:
  CRandomGauss();
  CRandomGauss(double dMean, double dStdDev);
  virtual ~CRandomGauss();

// Attributes
private:
  double m_dStdDev; //standard deviation
  double m_dMean;   //mean value
  CRandomUniform m_dUniform; //uniform random number

// Operations
public:
  void Set(double dMean, double dStdDev);
  void SetSeed(unsigned short ulSeed1, unsigned short ulSeed2);

  double Get();
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::SetSeed()------------------------------------------------------------------
/*Initializes the uniform random number generator. By default the current time
  is used for the seed.
 */
inline void CRandomGauss::SetSeed(unsigned short ulSeed1, //[in] first random
                                  //number seed must be in range [0, 31328]
                                  unsigned short ulSeed2 //[in] second random
                                  //number seed must be in range [0, 30081]
                           )
{
m_dUniform.SetSeed(ulSeed1,ulSeed2);
}

///////////////////////////////////////////////////////////////////////////////
#endif // _KRANDOMGAUSS_H_
/******************************************************************************
 *$Log:
 * 7    Biblioteka1.6         2003-09-22 22:26:33  Darko           formatting
 * 6    Biblioteka1.5         2002-07-16 01:41:21  Darko           Fixed VSS Log
 *      tag
 * 5    Biblioteka1.4         2002-04-04 01:13:08  Darko           Documenation
 *      update
 * 4    Biblioteka1.3         2002-04-02 19:06:17  Darko Kolakovic
 * 3    Biblioteka1.2         2002-03-19 16:39:39  Darko Kolakovic Updated
 *      comments
 * 2    Biblioteka1.1         2002-03-18 17:33:41  Darko Kolakovic Added Gaussian
 *      Rand No
 * 1    Biblioteka1.0         2002-03-14 22:49:25  Darko
 *$
 * Algorithm 712, from ACM. Published in Transactions on Mathematical Software,
 * vol. 18, no. 4, XII 1992, pp. 434-435.
 *****************************************************************************/
