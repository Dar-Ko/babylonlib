/*$RCSfile: TestSet.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2011/03/13 07:10:47 $
  $Author: ddarko $

  Test basic set class
  Copyright: CommonSoft Inc.
  2004-08-14 Darko Kolakovic
*/

// Group=Examples

#include "KSet.h" //TSet template

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);
extern bool TsWriteToView(const double& dValue);
extern bool TsWriteToViewLn(const double& dValue);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif
  
  //
//    Copyright 1995 by Scott Robert Ladd
//=============================================================

#include "charset.h"
#include "limits.h"
#include "strstrea.h"
#include "iomanip.h"
#include "randgen.h"
#include "objset.h"

//---------------------------
// test the TSet<I,T> template
//---------------------------

//-----------------------------------------------------------------------------
/*Validates TSet template methods.
  Returns: true if successful, otherwise returns false.
 */
bool TestSet(strstream & buffer)
{
TsWriteToView(_T("TestRound()\r\n"));

  //Test rounding to the integer
TESTENTRY logEntry = 
  {_T("TSet<unsigned char>()"), _T("KSet.h"), false};
bool bRes& = logEntry.m_bResult;

  size_t n;

  buffer << "TSet Test!\r\n==========\r\n\r\n";

  const size_t TEST_SIZE = 128;
  unsigned char ch;
  TSet<unsigned char> set1, set5;
  RandGen gen;
  RandGen op;

  // set values in set1
  for (n = 0; n < TEST_SIZE; ++n)
    {
    // perform operation on set1
    ch = (char)gen(UCHAR_MAX);

    if (op(2) == 1)
      {
      buffer << "\tSet 1: Incl " << setw(4) << int(ch)
           << " (" << (set1[ch] ? "1" : "0");
      set1.Incl(ch);
      buffer << " -> " << (set1[ch] ? "1)" : "0)");
      }
    else
      {
      buffer << "\tSet 1: Excl " << setw(4) << int(ch)
           << " (" << (set1[ch] ? "1" : "0");
      set1.Excl(ch);
      buffer << " -> " << (set1[ch] ? "1)" : "0)");
      }

    // perform operation on set5
    ch = (char)gen(UCHAR_MAX);

    if (op(2) == 1)
      {
      buffer << "\tSet 5: Incl " << setw(4) << int(ch)
           << " (" << (set5[ch] ? "1" : "0");
      set5.Incl(ch);
      buffer << " -> " << (set5[ch] ? "1)" : "0)");
      }
    else
      {
      buffer << "\tSet 5: Excl " << setw(4) << int(ch)
           << " (" << (set5[ch] ? "1" : "0");
      set5.Excl(ch);
      buffer << " -> " << (set5[ch] ? "1)" : "0)");
      }

    buffer << "\r\n";
    }

  TSet<unsigned char> set2, set3, set4;

  // test basic operations
  set2 = set1;
  set3 = ~set1;
  set4.AllOn();

  buffer << "\r\nset1:        " << set1
       << "\r\nset5:        " << set5
       << "\r\nset2 = set1:     " << set2
       << "\r\nset3 = ~set1:    " << set3
       << "\r\nset4.AllOn():    " << set4;

  // test union operations
  set4 = set1 | set3;
  buffer << "\r\nset4 = set1 | set3:  " << set4;
  set4 = set3 | set1;
  buffer << "\r\nset4 = set3 | set1:  " << set4;
  set4 = set1 | set2;
  buffer << "\r\nset4 = set1 | set2:  " << set4;
  set4 = set2 | set1;
  buffer << "\r\nset4 = set2 | set1:  " << set4;
  set4 = set1 | set5;
  buffer << "\r\nset4 = set1 | set5:  " << set4;
  set4 = set5 | set1;
  buffer << "\r\nset4 = set5 | set1:  " << set4;

  // test intersection operations
  set4 = set1 & set3;
  buffer << "\r\nset4 = set1 & set3:  " << set4;
  set4 = set3 & set1;
  buffer << "\r\nset4 = set3 & set1:  " << set4;
  set4 = set1 & set2;
  buffer << "\r\nset4 = set1 & set2:  " << set4;
  set4 = set2 & set1;
  buffer << "\r\nset4 = set2 & set1:  " << set4;
  set4 = set1 & set5;
  buffer << "\r\nset4 = set1 & set5:  " << set4;
  set4 = set5 & set1;
  buffer << "\r\nset4 = set5 & set1:  " << set4;

  // test difference operations
  set4 = set1 ^ set3;
  buffer << "\r\nset4 = set1 ^ set3:  " << set4;
  set4 = set3 ^ set1;
  buffer << "\r\nset4 = set3 ^ set1:  " << set4;
  set4 = set1 ^ set2;
  buffer << "\r\nset4 = set1 ^ set2:  " << set4;
  set4 = set2 ^ set1;
  buffer << "\r\nset4 = set2 ^ set1:  " << set4;
  set4 = set1 ^ set5;
  buffer << "\r\nset4 = set1 ^ set5:  " << set4;
  set4 = set5 ^ set1;
  buffer << "\r\nset4 = set5 ^ set1:  " << set4;

  // test difference operations
  set4 = set1 - set3;
  buffer << "\r\nset4 = set1 - set3:  " << set4;
  set4 = set3 - set1;
  buffer << "\r\nset4 = set3 - set1:  " << set4;
  set4 = set1 - set2;
  buffer << "\r\nset4 = set1 - set2:  " << set4;
  set4 = set2 - set1;
  buffer << "\r\nset4 = set2 - set1:  " << set4;
  set4 = set1 - set5;
  buffer << "\r\nset4 = set1 - set5:  " << set4;
  set4 = set5 - set1;
  buffer << "\r\nset4 = set5 - set1:  " << set4 << "\r\n";

  // test unary operators
  set4 = set5; // save set5
  set5 |= set1;
  buffer << "\r\n    set5 |= set1:  " << set5;
  set5 = set4;
  set5 &= set1;
  buffer << "\r\n    set5 &= set1:  " << set5;
  set5 = set4;
  set5 ^= set1;
  buffer << "\r\n    set5 ^= set1:  " << set5;
  set5 = set4;
  set5 -= set1;
  buffer << "\r\n    set5 -= set1:  " << set5 << "\r\n";

  // test comparison operators
  set5 = set4;

  if (set5 == set4)
    buffer << "\r\nCORRECT! set5 equals set4\r\n";
  else
    buffer << "\r\nWRONG! set5 should equal set4\r\n";

  if (set5 != set1)
    buffer << "CORRECT! set5 does not equal set1\r\n";
  else
    buffer << "WRONG! set5 should not equal set1\r\n";

  set5.AllOn();
  buffer << "after  AllOn, set5 contains " << set5.Cardinality()
       << " elements\r\n";

  set5.AllOff();
  buffer << "after AllOff, set5 contains " << set5.Cardinality()
       << " elements\r\n";

  set5.Incl(1);
  set5.Incl(11);
  set5.Incl(13);
  set5.Incl(32);
  set5.Incl(99);
  set5.Incl(1);
  set5.Excl(13);
  buffer << "after 6 includes and 1 exclude, set5 contains "
       << set5.Cardinality() << " elements (should be 4)\r\n";

  set4 = set5;
  buffer << "set4 now equals set5\r\n";

  buffer << "set4 cardinality = "  << set4.Cardinality()
       << " set5 cardinality = " << set5.Cardinality()
       << "\r\n";

  if (set4.Disjoint(set5))
    buffer << "WRONG! (sets not disjoint)\r\n";
  else
    buffer << "RIGHT! (sets not disjoint)\r\n";

  if (set4.SubsetOf(set5))
    buffer << "RIGHT! (is a subset)\r\n";
  else
    buffer << "WRONG! (is a subset)\r\n";

  if (set4.ProperSubsetOf(set5))
    buffer << "WRONG! (not a proper subset)\r\n";
  else
    buffer << "RIGHT! (not a proper subset)\r\n";

  set4.Excl(99);
  buffer << "set4 now lacks an element in set5\r\n";

  buffer << "set4 cardinality = "  << set4.Cardinality()
       << " set5 cardinality = " << set5.Cardinality()
       << "\r\n";

  if (set4.Disjoint(set5))
    buffer << "WRONG! (sets not disjoint)\r\n";
  else
    buffer << "RIGHT! (sets not disjoint)\r\n";

  if (set4.SubsetOf(set5))
    buffer << "RIGHT! (is a subset)\r\n";
  else
    buffer << "WRONG! (is a subset)\r\n";

  if (set4.ProperSubsetOf(set5))
    buffer << "RIGHT! (ia a proper subset)\r\n";
  else
    buffer << "WRONG! (is a proper subset)\r\n";

  set4.Incl(66);
  buffer << "set4 now includes an element not in set5\r\n";

  buffer << "set4 cardinality = "  << set4.Cardinality()
       << " set5 cardinality = " << set5.Cardinality()
       << "\r\n";

  if (set4.Disjoint(set5))
    buffer << "WRONG! (sets not disjoint)\r\n";
  else
    buffer << "RIGHT! (sets not disjoint)\r\n";

  if (set4.SubsetOf(set5))
    buffer << "WRONG! (not a subset)\r\n";
  else
    buffer << "RIGHT! (not a subset)\r\n";

  if (set4.ProperSubsetOf(set5))
    buffer << "WRONG! (not a proper subset)\r\n";
  else
    buffer << "RIGHT! (not a proper subset)\r\n";

  set4.AllOff();
  set4.Incl(4);
  set4.Incl(8);
  buffer << "set4 has no common elements with set5\r\n";

  buffer << "set4 cardinality = "  << set4.Cardinality()
       << " set5 cardinality = " << set5.Cardinality()
       << "\r\n";

  if (set4.Disjoint(set5))
    buffer << "RIGHT! (should be disjoint)\r\n";
  else
    buffer << "WRONG! (should be disjoint)\r\n";

  if (set4.SubsetOf(set5))
    buffer << "WRONG! (not a subset)\r\n";
  else
    buffer << "RIGHT! (not a subset)\r\n";

  if (set4.ProperSubsetOf(set5))
    buffer << "WRONG! (not a proper subset)\r\n";
  else
    buffer << "RIGHT! (not a proper subset)\r\n";

  // test a BIG set
  const size_t TEST6_SIZE = 1701;
  RandGen gen6;
  unsigned short init6[TEST6_SIZE];

  for (n = 0; n < TEST6_SIZE; ++n)
    init6[n] = size_t(gen6(UINT_MAX));

  TSet<unsigned short> set6(init6,TEST6_SIZE);

  // integrity check!
  for (n = 0; n < TEST6_SIZE; ++n)
    {
    if (!set6[init6[n]])
      {
      buffer << "\r\nTest 6 FAILED!\r\n";
      return;
      }
    }

  buffer << "\r\nTest 6 SUCCEEDED\r\n";
  }

//-------------------
// test CharSet class
//-------------------

void TestCharSet
  (
  strstream & buffer
  )
  {
  buffer << "Character TSet Test\r\n\r\n";

  buffer << "   Uppercase: " << CS_Uppercase  << "\r\n";
  buffer << "   Lowercase: " << CS_Lowercase  << "\r\n";
  buffer << "   Letters: " << CS_Letters    << "\r\n";
  buffer << "   Numbers: " << CS_Numbers    << "\r\n";
  buffer << "AlphaNumeric: " << CS_AlphaNumeric << "\r\n";
  buffer << " Punctuation: " << CS_Punctuation  << "\r\n";
  buffer << "    Symbol: " << CS_Symbol     << "\r\n";
  buffer << "  Whitespace: " << CS_Whitespace   << "\r\n";
  buffer << "     Words: " << CS_Words    << "\r\n";
  buffer << "   Operators: " << CS_Operators  << "\r\n";
  buffer << "   Printable: " << CS_Printable  << "\r\n";
  }

//-------------------------------
// Test sets with bounding ranges
//-------------------------------

enum TestEnum {A, B, C, D, E, F, G, H, I, J, K, L, M,
           N, O, P, Q, R, S, T, U, V, W, X, Y, Z};

void TestLimitedSet
  (
  strstream & buffer
  )
  {
  buffer << "Bounded TSet Test\r\n\r\n";

  TSet<unsigned char> set1(12,0);
  TSet<int>       set2(1995,1980);


  TSet<TestEnum> vowels(Z,A);

  set1.Incl(0);
  set1.Incl(2);
  set1.Incl(11);

  set2.Incl(1980);
  set2.Incl(1995);

  vowels.Incl(A);
  vowels.Incl(E);
  vowels.Incl(I);
  vowels.Incl(O);
  vowels.Incl(U);
  vowels.Incl(Y);

  buffer << "  set1 = " << set1   << "\r\n";
  buffer << "  set2 = " << set2   << "\r\n";
  buffer << "vowels = " << vowels << "\r\n";
  }

//-------------------------------
// Test sets with bounding ranges
//-------------------------------

template <class K, class D>
  void ShowObjectSet
    (
    strstream & buffer,
    const ObjectSet<K,D> & oset
    )
    {
    size_t i = 0;
    ObjSetIterator<K,D> osi(oset);

    do  {
      ++i;
      buffer << "\titem " << setw(2) << i << " = ("
           << setw(2) << (osi.GetKey()) << ","
           << setw(2) << (osi.GetData()) << ")\r\n";
      }
    while (++osi);
    }

static ObjectSet<int,int> oset1, oset2, inter1,
              union1, diff1, xor1;

void TestObjectSet
  (
  strstream & buffer
  )
  {
  buffer << "Object TSet Tests\r\n"
        "----------------\r\n\r\n";

  oset1.Erase();
  oset2.Erase();
  inter1.Erase();
  union1.Erase();
  diff1.Erase();
  xor1.Erase();

  const size_t TEST_SIZE = 20;
  size_t i;
  for (i = 1; i <= TEST_SIZE; ++i)
    {
    oset1.Incl(i * 3,i * 3);
    oset2.Incl(i * 4,i * 4);
    }


  buffer << "object list 1:\r\n\r\n";
  ShowObjectSet(buffer,oset1);

  buffer << "\r\nobject list 2:\r\n\r\n";
  ShowObjectSet(buffer,oset2);

  inter1 = oset1 & oset2;
  union1 = oset1 | oset2;
  xor1   = oset1 ^ oset2;
  diff1  = oset1 - oset2;

  buffer << "\r\nintersection:\r\n\r\n";
  ShowObjectSet(buffer,inter1);

  buffer << "\r\nunion:\r\n\r\n";
  ShowObjectSet(buffer,union1);

  buffer << "\r\nexclusive or:\r\n\r\n";
  ShowObjectSet(buffer,xor1);

  buffer << "\r\ndifference:\r\n\r\n";
  ShowObjectSet(buffer,diff1);

//Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: TestSet.cpp,v $
 * Revision 1.1  2011/03/13 07:10:47  ddarko
 * MSVC 2008 v9
 *
 *****************************************************************************/
