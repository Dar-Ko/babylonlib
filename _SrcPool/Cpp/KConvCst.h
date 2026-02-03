/*$Workfile: KConvCst.h$: header file
  $Revision: 2$ $Date: 2003-09-22 21:25:45$
  $Author: Darko$

  Physics - Constants
  Conversion constant factors - SI ('metric') and  ASTM E 380 (U.S.) units
  Copyright: CommonSoft Inc
  Jan. 97  D. Kolakovic
 */
#ifndef _KCONVCST_H_
    //$Workfile: KConvCst.h$ sentry
  #define _KCONVCST_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//-----------------------------------------------------------------------------
/*Conversion factors between different SI (System International) units and
  U.S. customary units (ASTM E 380).
 */

// Group=Constants

  //Mass

const double CST_KGpLB = 0.45359237;  //kilogram per pound
const double CST_LBpKIP= 1000.0    ;  //pound per kip

  //Length

const double CST_MpIN  =  0.0254;     //meter per inch
const double CST_MpML  =  1.609344E3; //meter per US Statute mile
const double CST_MpNML =  1.852000E3; //meter per international nautical mile

const double CST_INpFT  =   12.0;//inch per foot
const double CST_FTpYD  =    3.0;//foot per yard
const double CST_YDpML  = 1760.0;//yard per mile
const double CST_FTpFM  =    6.0;//foot per fathom
const double CST_FTpKNUS= 6080.2;//foot per knot (US nautical mile)
const double CST_FTpKNUK= 6080.0;//foot per knot (UK nautical mile)

  //Temperature

const double CST_oCoF1 =5.0/9.0; //�Fahrenheit to �Celsius coef.Tc = 5(Tf-32)/9
const double CST_oCoF2 =   32.0; //�Fahrenheit to �Celsius part.
const double CST_oF2oRk= 459.67; //difference between �Fahrenheit and �Rankine
const double CST_oCoR  =4.0/5.0; //�Reaumur to �Celsius coef

  //Force

const double CST_NpKP  =9.80665; //newton per kilopond(kilogram-force)

  //Power

const double CST_KPMpHP  = 75.0; //(kp*m)/s per horsepower(metric)
const double CST_FTLBFpHP=550.0; //(ft*lb-force)/s  per horsepower(US)

  //Energy

const double CST_JpBTU =1055.06; //joule per British thermal unit

  //Pressure

const double CST_PApATM=101325.;  //pascal per standard atmosphere
const double CST_TORRpATM= 760.;  //torr(almost as mmHg) per standard atmosphere
const double CST_PApBAR=    1e5;  //pascal per bar
const double CST_PApINH2O=249.089;//pascal per inch of water at 4�C


///////////////////////////////////////////////////////////////////////////////
#endif //_KCONVCST_H_
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2003-09-22 21:25:45  Darko           formatting
 *  1    Biblioteka1.0         2003-09-11 15:51:49  Darko           Extracted from
 *       U_Conv.h
 * $
 *  0   Jan. 97 created  D. Kolakovic
 *****************************************************************************/
