/*$Workfile: S:\_SrcPool\Cpp\KMatAcosC.cpp$: implementation file
  $Revision: 1$ $Date: 2007-06-08 17:52:49$
  $Author: Darko Kolakovic$

  arccos of  complex number
  Copyright: CommonSoft Inc.
  2007-06-03 Darko Kolakovic
 */

// Group=Mathematics

#include <math.h> //_complex structure
#include <float.h>//_finite()

//-----------------------------------------------------------------------------
/*Computes acos.

  acos(Z) = ln(Z + i*sqrt(1-Z*Z))/i = pi/2 - asin(Z)
  Returns: acos(Z) = -i*ln[Z + i*sqrt(1 - Z*Z)]
  
  FixMe!
 */
_complex acos(const _complex& zValue //[in] complex number Z = x + iy
             )
{
_complex zRes;

if (zValue.y == 0.0) //Z is a real number
  {
  zRes.x = ::acos(zValue.x); //for x = 0, acos(x) = 3.14/2
  zRes.y = 0.0;
  }
else
  {
  _complex zTemp;
  //1-Z^2 = 1 - x^2 + y^2 -2ixy
  zTemp.x = 1.0 - zValue.x*zValue.x + zValue.y*zValue.y; //1-(x^2 - y^2)
  if (zValue.x != 0.0)
    {
    zTemp.y = -zValue.x*zValue.y;
    zTemp.y -= zTemp.y; //-2ixy

    //sqrt(1 - Z^2) = sqrt(zTemp)
    zRes.y = _cabs(zTemp); //mag(Z) = |Z|=sqrt(x*x + y*y)
    zRes.x = sqrt(0.5*(zRes.y + zTemp.x)); //sqrt[(|Z| + x)/2]
    zRes.y = sqrt(0.5*(zRes.y - zTemp.x)); //sqrt[(|Z| - x)/2]
    if (zTemp.y < 0.0) //Im(sqrt(W)) = sign(W.y)*sqrt[(|W| - W.x)/2]
      zRes.y = -zRes.y;
    }
  else
    {
    //sqrt(1 - Z^2) = sqrt(Re(zTemp))
    zRes.y = 0.0;
    zRes.x = ::sqrt(zTemp.x);
    }

  //Z + i*sqrt(1 - Z*Z)
  if(_finite(zRes.x) == 0)
    zTemp.x = (zRes.x*0.0); //1.IND
  else
    zTemp.x = (zValue.x - zRes.y); //Re(Z + iW)

  if(_finite(zRes.y) == 0)
    zTemp.y = (zRes.y*0.0); //1.IND
  else
    zTemp.y = (zValue.y + zRes.x);//Im(Z + iW)

  //ln(W) = ln|W| + i(W.theta)
  zRes.x = log(_cabs(zTemp));
  zRes.y = ::atan2(zTemp.y, zTemp.x);
  //acos(Z) = -i*ln(W)
  zTemp.x = zRes.y;
  zTemp.y = -zRes.x;
  }

return zRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-06-08 17:52:49  Darko Kolakovic 
 * $
 *****************************************************************************/
