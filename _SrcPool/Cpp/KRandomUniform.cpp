/*$Workfile: KRandomUniform.cpp$: implementation file
  $Revision: 6$ $Date: 7/12/02 6:23:44 PM$
  $Author: Darko Kolakovic$

  Uniform random number generator
  1987 G. Marsaglia, A. Zaman
  Mar 2k2 Aleksandar Janicijevic
*/
#include <Limits.h> //UINT_MAX macro
#include "KRandomUniform.h" //CRandomUniform class

///////////////////////////////////////////////////////////////////////////////

const int CRandomUniform::LAG_A = 97;
const int CRandomUniform::LAG_B = 33;

CRandomUniform::CRandomUniform()
{
m_dDecrement    = 362436.0 / 16777216.0;
m_nIndexA  = LAG_A - 1;
m_nIndexB  = LAG_B - 1;
SetSeed(); //Use current time as a seed(s)
}

CRandomUniform::CRandomUniform(unsigned long ulSeed)
{
SetSeed(ulSeed);
}

CRandomUniform::CRandomUniform (unsigned short ulSeed1, unsigned short ulSeed2)
{
m_dDecrement    = 362436.0 / 16777216.0;
m_nIndexA  = LAG_A - 1;
m_nIndexB  = LAG_B - 1;
SetSeed (ulSeed1, ulSeed2);
}

CRandomUniform::~CRandomUniform ()
{
}

//::SetSeed()------------------------------------------------------------------
/*This is the initialization routine for the random number generator.

  The random number sequences created by these two seeds are of sufficient
  length to complete an entire calculation with. For example, if several
  different groups are working on different parts of the same calculation,
  each group could be assigned its own ulSeed1 seed. This would leave each group
  with 30000 choices for the second seed. That is to say, this random
  number generator can create 900 million different subsequences - with
  each subsequence having a length of approximately 10^30.
 */
void CRandomUniform::SetSeed(unsigned short ulSeed1, //[in] first random
                                  //number seed must be in range [0, 31328]
                             unsigned short ulSeed2 //[in] second random
                                  //number seed must be in range [0, 30081]
                            )
{
double s,t;
int ii,i,j,k,l,jj,m;

//Validate the seed range
if (ulSeed1 > 31328 || ulSeed2 > 30081)
  {
  ulSeed1 = 1802; //Set test values
  ulSeed2 = 9373;
  }

i = (ulSeed1 / 177) % 177 + 2;
j = (ulSeed1 % 177)       + 2;
k = (ulSeed2 / 169) % 178 + 1;
l = (ulSeed2 % 169);

//Create the seed table
for (ii = 0; ii < LAG_A; ii++) 
  {
  s = 0.0;
  t = 0.5;
  for ( jj =0; jj < 24; jj++)
    {
    m = (((i * j) % 179) * k) % 179;
    i = j;
    j = k;
    k = m;
    l = (53 * l + 1) % 169;
    if (((l * m % 64)) >= 32 )
      s += t;
    t *= 0.5;
    }
  m_dTable[ii] = s;
  }
}

//::Get()----------------------------------------------------------------------
/*This is the random number generator proposed by George Marsaglia in
  Florida State University Report: FSU-SCRI-87-50
  
  Returns: independent random number from the interval [0,1).
 */
double CRandomUniform::Get()
{
  double dResult;
  const double cd   = 7654321.0 / 16777216.0;
  const double cm   = 16777213.0 / 16777216.0;

  dResult = m_dTable[m_nIndexA] - m_dTable[m_nIndexB];
  if (dResult <= 0.0)
    dResult++;

  m_dTable[m_nIndexA] = dResult;
  if (m_nIndexA == 0)
    m_nIndexA = LAG_A - 1;
  else
    m_nIndexA--;

  if (m_nIndexB == 0)
    m_nIndexB = LAG_A - 1;
  else
    m_nIndexB--;

  m_dDecrement -= cd;
  if (m_dDecrement < 0.0)
    m_dDecrement += cm;

  dResult -= m_dDecrement;
  if (dResult < 0.0)
    dResult++;

  return dResult;
}

///////////////////////////////////////////////////////////////////////////////
/* 
 *$Log: 
 * 6    Biblioteka1.5         7/12/02 6:23:44 PM   Darko Kolakovic Log added
 * 5    Biblioteka1.4         7/12/02 6:21:59 PM   Darko Kolakovic VSS tag
 * 4    Biblioteka1.3         4/3/02 4:30:19 PM    Darko Kolakovic Fixed bug in
 *      Get(): wrong index of m_dTable
 * 3    Biblioteka1.2         4/2/02 7:06:21 PM    Darko Kolakovic 
 * 2    Biblioteka1.1         3/14/02 10:50:20 PM  Darko           Comments
 * 1    Biblioteka1.0         3/14/02 6:55:08 PM   Aleksandar Janicijevic 
 *$
 *****************************************************************************/
