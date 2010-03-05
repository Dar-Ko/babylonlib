/*$RCSfile: TestTemplateNesting.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2010/03/05 22:31:41 $
  $Author: ddarko $

  Test C++ compiler conformance of nesting template classes.
  MSDN: http://msdn.microsoft.com/en-us/library/71dw8xzh.aspx
  2010-03-92 Darko Kolakovic
*/

/* Group=Examples                                                            */

#ifdef _USE_ATL
  #include <iostream>
  //Active Template Libaray (ATL)
  #include <atlbase.h>
  #include "KTraceAtl.h"
#endif

#include "TestConformance.h"
#ifndef _T
  #include "KTChar.h"
#endif
#ifndef LOG_EOT
  #include "KTestLog.h"
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);

#ifndef HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT
///////////////////////////////////////////////////////////////////////////////
// Nested template classes
//
template <class T>
class X
{
private:
  //Nested template class
  template <class U>
  class TNested
    {
      U m_uObj; //an object

    public:
      TNested();
      ~TNested();
      U&   Value();
      void Out();
    };

public:
  X(T t)
    {
    m_intTNested.Value() = t;
    }
  void Out()
    {
    m_intTNested.Out();
    }
  int GetValue()
    {
    return (int)m_intTNested.Value();
    }

protected:
  TNested<int> m_intTNested; //an integer object

};

//=============================================================================
/*When nested class templates are defined outside of their enclosing class,
  they must be prefaced by the template parameters for both the class template
  (if they are members of a class template) and template parameters for
  the member template.
  Local classes are not allowed to have member templates.
 */
template <class T>
template <class U>
X<T>::TNested<U>::TNested()
{
TRACE(_T("X<T>::TNested<U>::TNested()\n"));
m_uObj = (U)0xFFFF;
}

template <class T>
template <class U>
U& X<T>::TNested<U>::Value()
{
return m_uObj;
}

template <class T>
template <class U>
void X<T>::TNested<U>::Out()
{
TRACE1(_T("X<T>::TNested<U>::Out() = %d.\n"), (int)this->Value());
}

template <class T>
template <class U>
X<T>::TNested<U>::~TNested()
{
TRACE(_T("X<T>::TNested<U>::~TNested()\n"));
}

#endif //HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance on template classes nested inside of
  a template.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestTemplateNesting()
{
bool bResult = false;
#ifndef HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT
  X<int> xInt(101);
  xInt.Out();
  bResult = (xInt.GetValue() == 101);

  X<char> xChar('c');
  xChar.Out();
  bResult = bResult && (xChar.GetValue() == (int)'c');
#else
  TRACE(_T("HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT\n"));
  TsWriteToViewLn(_T("HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT\n"));
  bResult = true;
#endif //HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT

return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: TestTemplateNesting.cpp,v $
 * Revision 1.3  2010/03/05 22:31:41  ddarko
 * *** empty log message ***
 *
 * Revision 1.2  2010/03/03 00:07:01  ddarko
 * MSVC 2005 Cimpilation
 *
 * Revision 1.1  2010/03/02 23:02:15  ddarko
 * Nested template classes
 *
 *****************************************************************************/

