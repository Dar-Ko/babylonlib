/*$Workfile: KReal4IE.h$: header file
  $Revision: 5$ $Date: 04/04/2002 12:13:11 AM$
  $Author: Darko$

  Decompose 32-bit float number (IEEE 754)
  Copyright: CommonSoft Inc
  Mar. 2k D.Kolakovic
 */

#ifndef __KREAL4IE_H__
  //KReal4IE.h sentry
  #define __KREAL4IE_H__

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif
#include "KReal4Cv.h" //UReal4Conversion union

  //Number of bits in the exponent for IEEE 754 single precision real
const int REAL4_IE_ExpLEN = 8;
  //Number of bits in the mantissa for IEEE 754 single precision real
const int REAL4_IE_ManLEN = 23;
  //Exponent bias  for IEEE 754 single precision real
const int REAL4_IE_BIAS = 127;
  //Maximum exponent for IEEE 754 single precision real (next value is NaN/Inf).
const int REAL4_IE_ExpMAX = 254;
  //Mask used to extract sign of the IEEE 754 single precision real
const int REAL4_IE_SIGNMASK = 0x80000000L;

///////////////////////////////////////////////////////////////////////////////
/*CFloatIEEE class contains decomposed 32-bit floating point number given as
  described with IEEE Standard 754. According to this specification, floating 
  point numbers are represented in the following form, where exponent is the 
  binary exponent: 

      f = (-1**sign) * 1.Fraction * 2**(iExponent - bias)

  The mantissa is stored as a binary fraction of the form 1.mmmm... . This fraction
  has a value greater than or equal to 1 and less than 2. Real numbers are always 
  stored in normalized form, that is, the mantissa is left-shifted such that the 
  high-order bit of the mantissa is always 1. 
  For single precision floating point values are reserved 32 bits:
    {html:<BR><IMG SRC="Res/Real4IEEE.gif" BORDER="0">}

      High-order bit of the mantissa is always 1 and is not stored.
      sign bit representation:  0 is positive  and	1 is negative
      Exponent: Values are biased for 127. Values in range [1, 126] represents 
      negative exponents for base 2 and values in range [127, 255] are positive 
      exponents.


      Size               Range            Significant digits
     4 byte    8.43x10E-37 to 3.37x10E38          6-7

  See Also:
   {html: <A HREF="http://www.research.microsoft.com/~hollasch/cgindex/coding/ieeefloat.html">
    IEEE Standard 754 </A>}
 */
class CFloatIEEE
{
  //Construction
public:
  CFloatIEEE();
  CFloatIEEE(const float& fValue);
  //Data
public:
  int  iSign;     //sign: -1 for negative numbers, 0 for positive
  int  iExponent; //base 2 exponent
  long lMantissa; //fraction part of the real number


  //Operations
public:
  operator float();
  operator double();
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::CFloatIEEE()-------------------------------------------------------------------
/*Default constructor
 */
inline CFloatIEEE::CFloatIEEE():
iSign(0), iExponent(0), lMantissa(0)
{
}

/*Extract components form real number stored in IEEE 754 format.
  This is format of the number:

                  BYTE 3    BYTE 2    BYTE 1    BYTE 0 
      real*4    SEEE EEEE XMMM MMMM MMMM MMMM MMMM MMMM
      where S represents the sign bit, 
            E are the exponent bits, and 
            M are the mantissa bits.

  This constructor extracts sign and values of the mantissa and exponent.
 */
inline CFloatIEEE::CFloatIEEE(const float& fValue)
{
UReal4Conversion urcTemp(fValue);

iSign = ( (urcTemp.lDWord & REAL4_IE_SIGNMASK) == 0) ? 0 : -1;
iExponent = ((urcTemp.lDWord & 0x7F800000L ) >> REAL4_IE_ManLEN ) - REAL4_IE_BIAS;
lMantissa =  (urcTemp.lDWord & 0x007FFFFFL );
}

//::operator float()-----------------------------------------------------------
/*Returns IEEE 754 single precision real.
 */
inline CFloatIEEE::operator float()
{
UReal4Conversion urcResult;
  //Convert exponent
urcResult =  (iExponent + REAL4_IE_BIAS) << REAL4_IE_ManLEN;
  //Add mantissa
urcResult |= lMantissa;
  //Set sign
urcResult |= (iSign & REAL4_IE_SIGNMASK);
return (float)urcResult;
}

//::operator double()-----------------------------------------------------------
#include "KReal8Cv.h" //UReal8Conversion union
/*TODO: Next time
 */
inline CFloatIEEE::operator double()
{
UReal8Conversion urcResult;
  //Convert exponent
urcResult.lDWord[_ENDIAN_HIGH_INDEX] =  (iExponent + 1023) << (52-32);
  //Add mantissa
urcResult.lDWord[_ENDIAN_LOW_INDEX] = lMantissa;
  //Set sign
if (iSign < 0)
  urcResult.lDWord[_ENDIAN_HIGH_INDEX] |= REAL4_IE_SIGNMASK;
return (double)urcResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //__KREAL4IE_H__

/*
Floating Conversions
An object of a floating type can be safely converted to a more precise floating type — that is, the conversion causes no loss of significance. For example, conversions from float to double or from double to long double are safe, and the value is unchanged.

MBF double-precision values are stored in the following format:

     +--------------+----+-----------------------------+
     |              |    |                             |
     |8 Bit Exponent|Sign|   55 Bit Mantissa           |
     |              | Bit|                             |
     +--------------+----+-----------------------------+

IEEE double precision values are stored in the following format:

     +----+----------------+-+-------------------------+
     |    |                | |                         |
     |Sign| 11 Bit Exponent|1|  52 Bit Mantissa        |
     | Bit|                | |                         |
     +----+----------------+-+-------------------------+
                            ^
                            Implied Bit (always 1)


IEEE 754 specification 
Floating-point numbers are represented in the following form, where exponent is the binary exponent: 
X = Fraction * 2^(exponent - bias) 
Fraction is the normalized fractional part of the number, normalized because the exponent is adjusted so that the leading bit is always a 1. This way, it does not have to be stored, and you get one more bit of precision. This is why there is an implied bit. This is similar to scientific notation, where you manipulate the exponent to have one digit to the left of the decimal point; except in binary, you can always manipulate the exponent so that the first bit is a 1, because there are only 1s and 0s. 

Bias is the bias value used to avoid having to store negative exponents. 
The bias for single-precision numbers is 127 and 1,023 (decimal) for double-precision numbers. Excel stores numbers using double-precision. 


The exponents are biased as follows: 

   8-bit  (real*4)  exponents are biased by 127
   11-bit (real*8)  exponents are biased by 1023
   15-bit (real*10) exponents are biased by 16383 
These exponents are not powers of ten; they are powers of two, that is, 8-bit stored exponents can be 
up to 127. 2**127 is roughly equivalent to 10**38, which is the actual limit of real*4. 

The mantissa is stored as a binary fraction of the form 1.XXX... . 
This fraction has a value greater than or equal to 1 and less than 2. 
Note that real numbers are always stored in normalized form, that is, 
the mantissa is left-shifted such that the high-order bit of the mantissa is always 1.
Because this bit is always 1, it is assumed (not stored) in the real*4 and real*8 formats. 
The binary (not decimal) point is assumed to be just to the right of the leading 1. 

The format, then, for the various sizes is as follows: 

              BYTE 1    BYTE 2    BYTE 3    BYTE 4   ...  BYTE n
   real*4    SXXX XXXX XMMM MMMM MMMM MMMM MMMM MMMM
   real*8    SXXX XXXX XXXX MMMM MMMM MMMM MMMM MMMM ... MMMM MMMM
   real*10   SXXX XXXX XXXX XXXX 1MMM MMMM MMMM MMMM ... MMMM MMMM 
S represents the sign bit, the X's are the exponent bits, and the M's are the mantissa bits. 
Note that the leftmost bit is assumed in real*4 and real*8 formats, 
but present as "1" in BYTE 3 of the real*10 format. 

To shift the binary point properly, you first un-bias the exponent and then move the binary point 
to the right or left the appropriate number of bits. 


:float formats:floating point:real numbers
^Floating Point Formats

%	IEEE 4 byte real

	31 30	 23 22			      0
	---------------------------------------
	|s| 8 bits |msb   23 bit mantissa  lsb|
	---------------------------------------
	 |	|		 -----------------  mantissa
	 |	---------------------------------  biased exponent (7fh)
	 --------------------------------------  sign bit

%	IEEE 8 byte real

	63 62	   52 51				  0
	---------------------------------------------------
	|s|  11 bits |msb	 52 bit mantissa       lsb|
	---------------------------------------------------
	 |	|		 -----------------  mantissa
	 |	---------------------------------  biased exponent (3FFh)
	 --------------------------------------  sign bit

%	Microsoft 4 byte real

	31     24 23 22			      0
	---------------------------------------
	| 8 bits |s|msb  23 bit mantissa   lsb|
	---------------------------------------
	     |	  |		 -----------------  mantissa
	     |	  -----------------------------  sign bit
	     -------------------------------  biased exponent (81h)

%	Microsoft 8 byte real (see note below)

	63    56 55 54 				       0
	------------------------------------------------
	| 8bits |s|msb		52 bit mantissa	    lsb|
	------------------------------------------------
	    |	 |		      -------------  mantissa
	    |	 ------------------------------  sign bit
	    ----------------------------  biased exponent (401h, see below)

%	IEEE 10 byte real (temporary real)

	79 78	    64 63 62					 0
	----------------------------------------------------------
	|s|  15 bits  |1|msb	      63 bit mantissa	      lsb|
	----------------------------------------------------------
	 |	|      |		    ------  mantissa
	 |	|      -------------------------  first mantissa bit
	 |	------------------------------	biased exponent (3FFFh)
	 -----------------------------------  sign bit

%	Turbo Pascal 6 byte real

	47     40 39 38					0
	-------------------------------------------------
	| 8 bits |s|msb		39 bit mantissa	     lsb|
	-------------------------------------------------
	     |	  |		     -------------  mantissa
	     |	  ------------------------------  sign bit
	     ---------------------------------  biased exponent (80h)



	- sign bit representation:  0 is positive  and	1 is negative
	- in all float formats except the IEEE 10 byte real, the
	  mantissa is stored without most significant bit; since
	  the state of this bit is known to be set, it is not
	  included and the exponent is adjusted accordingly
	- all formats use binary float representation
	- memory representation uses 80x86 reverse byte/word order.
	- Microsoft languages use the IEEE real formats;  BASIC is the
	  only normal user of the Microsoft float format
	- Microsoft 8 byte real format has not been verified;  several
	  Microsoft publications show an 8 bit exponent instead of 11 bits
	  and state the BIAS is 401h;  the discrepancy is that 8 bits can't
	  hold the value 401h (requires 11 bits)


%	True exponent is the exponent value minus the following bias:

	81h for Microsoft 4 byte real
	401h for Microsoft 8 byte real
	7Fh for IEEE 4 byte real
	3FFh for IEEE 8 byte real
	80h for Turbo Pascal 6 byte real

%	     Size		   Range	     Significant digits

	4 byte real	  8.43x10E-37 to 3.37x10E38	    6-7
	8 byte real	 4.19x10E-307 to 1.67x10E308	   15-16
	10 byte real	 3.4x10E-4932 to 1.2x10E4932	     19

*/