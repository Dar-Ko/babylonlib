/*$Workfile: KRandomGauss.h$: implementation file
  $Revision: 6$ $Date: 7/16/02 1:41:21 AM$
  $Author: Darko$

  Random number generator with Gaussian distribution
  1992 ALGORITHM 712, ACM
  Mar 2k2 Darko Kolakovic
*/

#ifndef _KRANDOMGAUSS_H_
  //KRandomGauss.h sentry
  #define _KRANDOMGAUSS_H_

#include "KRandomUniform.h"	//CRandomGauss class

///////////////////////////////////////////////////////////////////////////////
/*This class generates a normally (Gaussian) distributed random numbers.

  {html: <IMG SRC="Res/graphGuassDistributionF.gif" ALT="P(m,d*d)" BORDER="0"> <BR>}

  The density and distribution of normal (Gaussian) variable are completely 
  determined by the mean and variance (covariance).
  The standard deviation is defined as the square root of the variance.
  The Gaussian probability distribution with mean {html: <IMG SRC="Res/muon.gif" ALT="m" BORDER="0">}
  and standard deviation {html: <IMG SRC="Res/delta.gif" ALT="d" BORDER="0">} is a 
  normalized Gaussian function of the form:
  {html:<BR> <IMG SRC="Res/eqGuassDistribution.gif" ALT="P(x)=(1/d*sqrt(2pi))exp(-(x-m)^2/(2d^2))" BORDER="0"> <BR>}
  where {html:<i>}P(x)dx{html:</i>} gives the probability that a variate with 
  a Gaussian distribution takes on a value in the range [{html:<i>}x,x+dx{html:</i>}].
  The distribution {html:<i>}P(x){html:</i>} is properly normalized for 
  {html: <IMG SRC="Res/eqXeInfInf.gif" ALT="x(-INF,INF)" BORDER="0">} since 
  {html: <BR><IMG SRC="Res/eqIntGuassDistribution.gif" ALT="S(P(x)dx)=1 for x(-INF,INF)" BORDER="0"> <BR>}
  

  The algorithm uses the ratio of uniforms method of A.J. Kinderman and 
  J.F. Monahan augmented with quadratic bounding curves.
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
 * 6    Biblioteka1.5         7/16/02 1:41:21 AM   Darko           Fixed VSS Log 
 *      tag
 * 5    Biblioteka1.4         4/4/02 1:13:08 AM    Darko           Documenation
 *      update
 * 4    Biblioteka1.3         4/2/02 7:06:17 PM    Darko Kolakovic 
 * 3    Biblioteka1.2         3/19/02 4:39:39 PM   Darko Kolakovic Updated
 *      comments
 * 2    Biblioteka1.1         3/18/02 5:33:41 PM   Darko Kolakovic Added Gaussian
 *      Rand No
 * 1    Biblioteka1.0         3/14/02 10:49:25 PM  Darko           
 *$
 * Algorithm 712, from ACM. Published in Transactions on Mathematical Software,
 * vol. 18, no. 4, XII 1992, pp. 434-435.
 *****************************************************************************/
