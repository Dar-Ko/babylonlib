/*$RCSfile: TestTemplateTypedef.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/03/11 22:56:28 $
  $Author: ddarko $

  Test C++ compiler conformance of yypedef templates.
  Copyright: babylonlin.sourceforge.net
  2010-03-1 Darko Kolakovic
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

#ifdef _MSC_VER
  #ifndef HAS_NO_TYPEDEF_TEMPLATE
    //Microsoft Visual C++ error C2823: a typedef template is illegal
    #define HAS_NO_TYPEDEF_TEMPLATE 2010
  #endif
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);

////////////////////////////////////////////////////////////////////////////////
// Test typedef templates

/*typedefs to create a synonym for another type, including a synonym for
  a template specialization with all actual template arguments specified
 */
template<class T, int N>
class Q
{
public:
    Q();
    void Out();
    T oValue;
};

template<class T, int N>
Q<T, N>::Q() :
  oValue((T)N)
{
}

template <class T, int N>
void Q<T, N>::Out()
{
TRACE2(_T("Q<T, %d>::Out() = %d.\n"), N, (int)oValue);
}

#ifndef HAS_NO_TYPEDEF_TEMPLATE_SPECIALIZED
  /*Synonym for a template specialization with all actual template arguments
    specified.

    Example:
        qTrue i;
   */
  typedef Q<bool, 1> qTrue;
#endif

#ifndef HAS_NO_TYPEDEF_INSIDE_TEMPLATE
/*Test if classes can contain typedefs.
  This is often used as workaround to typedef template classes.

  Example:
      TSynonymPartial<unsigned int>::Type nOne;
 */
template<class U>
struct TSynonymPartial
{
  typedef Q<U, 1> Type;
};

/*Test if classes can contain typedefs.
  This is often used as workaround to typedef template classes.

  Example:
      TSynonymGeneral<long, 4>:Type    lValue;
 */
template<class U, int W>
struct TSynonymGeneral
{
  typedef Q<U, W> Type;
};
#endif

#ifndef HAS_NO_TYPEDEF_TEMPLATE
  /*synonym for a template.

    Example:
        QType<int, 2> m;
   */
template<typename T, typename S>
typedef Q<T, S> QType;

#endif

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error
  if typedef templates is not supported.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestTemplateTypedef()
{
bool bResult = false;
Q<long, 4> x;
x.Out();

#ifndef HAS_NO_TYPEDEF_TEMPLATE_SPECIALIZED
  qTrue b;
  b.Out();
  bResult = (b.oValue == 1);
#else
  TRACE(_T("HAS_NO_TYPEDEF_TEMPLATE_SPECIALIZED\n"));
  TsWriteToViewLn(_T("HAS_NO_TYPEDEF_TEMPLATE_SPECIALIZED\n"));
  bResult = true;
#endif //HAS_NO_TYPEDEF_TEMPLATE_SPECIALIZED

#ifndef HAS_NO_TYPEDEF_INSIDE_TEMPLATE
  TSynonymPartial<unsigned int>::Type nOne;
  TSynonymGeneral<long, 4>::Type    lValue;
  nOne.Out();
  bResult = bResult && (lValue.oValue == 4);
#else
  TRACE(_T("HAS_NO_TYPEDEF_INSIDE_TEMPLATE\n"));
  TsWriteToViewLn(_T("HAS_NO_TYPEDEF_INSIDE_TEMPLATE\n"));
#endif //HAS_NO_TYPEDEF_TEMPLATE_SPECIALIZED

#ifndef HAS_NO_TYPEDEF_TEMPLATE
  QType<int, 2> m;
  m.Out();
  bResult = bResult && (m.oValue == 2);
#else
  TRACE(_T("HAS_NO_TYPEDEF_TEMPLATE\n"));
  TsWriteToViewLn(_T("HAS_NO_TYPEDEF_TEMPLATE\n"));
#endif //HAS_NO_TYPEDEF_TEMPLATE

return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: TestTemplateTypedef.cpp,v $
 * Revision 1.1  2010/03/11 22:56:28  ddarko
 * Created template typedef test
 *
 *****************************************************************************/
