/*$Workfile: KRandomGauss.cpp$: implementation file
  $Revision: 3$ $Date: 16/07/2002 12:41:18 AM$
  $Author: Darko$

  Random number generator with Gauss distribution
  1992 ALGORITHM 712, ACM
  Mar 2k2 Darko Kolakovic
*/
#include <math.h> //log()
#include "KRandomGauss.h" //CRandomGauss class

///////////////////////////////////////////////////////////////////////////////

//::CRandomGauss()-------------------------------------------------------------
/*Default constructor creates a standard normal distribution.
  Standard normal random process is defined as:

          z = (x - m(x))/D(x)

  with mean{html: <IMG SRC="Res/muon.gif" ALT="m" BORDER="0">} equal to zero 
  and variance equal to 1.( D(z)^2 = 1)
 */
CRandomGauss::CRandomGauss()
{
m_dStdDev = 1.0;
m_dMean   = 0.0;
}

CRandomGauss::CRandomGauss(double dMean,  //[in] mean value
                           double dStdDev //[in] standard deviation
                          )
{
m_dStdDev = dStdDev; //standard deviation
m_dMean   = dMean;   //mean value
}

CRandomGauss::~CRandomGauss ()
{
}

//::Set()----------------------------------------------------------------------
/*Set density and distribution of the random numbers.
  The density and distribution are determined by the mean and standard deviation.
 */
void CRandomGauss::Set(double dMean,  //[in] mean value
                       double dStdDev //[in] standard deviation
                      )
{
m_dStdDev = dStdDev; //standard deviation
m_dMean   = dMean;   //mean value
}

//::Get()----------------------------------------------------------------------
/*The method returns a normally distributed pseudo-random number
  with a given mean and standard devaiation.

  Returns: a normally distributed random number.
 */
double CRandomGauss::Get()
{
 /*Algorithm 712, from ACM. Published in Transactions on Mathematical Software,
   vol. 18, no. 4, XII 1992, pp. 434-435.
  */
double  q,u,v,x,y;

do
  {
  //Get P = (u,v) uniform in rectangle enclosing acceptance region 
  u = m_dUniform.Get();
  v = m_dUniform.Get();
  //Get only positive numbers > 0, required by the algorithm
  if (u <= 0.0 || v <= 0.0)
    {
    u = 1.0;
    v = 1.0;
    }
  v = 1.7156 * (v - 0.5);

  /*Evaluate the quadratic form */
  x = u - 0.449871;
  y = fabs(v) + 0.386595;
  q = x * x + y * (0.19600 * y - 0.25472 * x);

  /*Accept P if inside inner ellipse */
  if (q < 0.27597)
    break;

   /* Reject P if outside outer ellipse, or outside acceptance region */
  } while ((q > 0.27846) || (v * v > -4.0 * log(u) * u * u));

/*  Return ratio of P's coordinates as the normal deviate */
return (m_dMean + m_dStdDev * v / u);
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 3    Biblioteka1.2         16/07/2002 12:41:18 AMDarko           Fixed VSS Log 
 *      tag
 * 2    Biblioteka1.1         02/04/2002 6:06:11 PMDarko Kolakovic 
 * 1    Biblioteka1.0         14/03/2002 9:49:23 PMDarko           
 *$
 *****************************************************************************/
