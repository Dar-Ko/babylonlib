/*$Workfile: KfKepler.cpp$: implementation file
  $Revision: 2$ $Date: 2004-06-01 16:55:01$
  $Author: Darko$

  Solves a quadratic equation
  CommonSoft Inc.
  Mar 2k1. D.Kolakovic
*/

/* Group=Mathematics                                                         */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include  "KProgCst.inl"  //IsZero()

//funcKepler()-----------------------------------------------------------------
/*Solves Kepler's equation of a body orbiting on an ellipse:

    M = E -e*sin(E);
    where M is mean anomaly, E is eccentric anomaly and e is eccentricity of 
    an ellipse.

  The ellipse eccentricity is the fraction of the distance to the semimajor axis
  at which the focus lies and has range 0 < e < 1.

  Returns: eccentric anomaly within rounding error [rad]  
 */
double funcKeplerEq(double dMeanAnomaly, //[in] mean anomaly [rad]
                    double dEllipseEccentricity //[in] eccentricity of a body orbiting
                    //on an ellipse [0, 1]
                  )
{
double dEccentricAnomaly; 
double dError;

dEccentricAnomaly = dMeanAnomaly; //initialize [rad]
do
  {
  // E - e*sin(E) - M = 0;
  dError = dEccentricAnomaly - 
           dEllipseEccentricity * sin(dEccentricAnomaly) - dMeanAnomaly;
  dEccentricAnomaly -= dError / (1 - dEllipseEccentricity * cos(dEccentricAnomaly));
  } while (!IsZero(dError));
return dEccentricAnomaly;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-06-01 16:55:01  Darko           StdAfx changed
 *       to stdafx
 *  1    Biblioteka1.0         2002-09-05 21:22:28  Darko           
 * $
 *****************************************************************************/
