/*$RCSfile: TestXml.c,v $: implementation file
  $Revision: 1.4 $ $Date: 2009/10/09 17:56:27 $
  $Author: ddarko $

  Global test samples
  2009-09-30 Darko Kolakovic
*/

/* Group=Examples
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"

/*XML document test sample
 */
TCHAR g_szTestXml[] =
_T("<?xml version=\"1.0\"?>\n\
<?xml-stylesheet type=\"text/xsl\" href=\"myfile.xsl\"?>\n\
<!-- example XML document -->\n\
<parentNode description=\"Well formed element\">\n\
\t<!-- Well formed element -->\n\
\t<intNode>10</intNode>\n\
\t<strNode>string</strNode>\n\
\t<boolNode>true</boolNode>\n\
\t<floatNode>0.3</floatNode>\n\
\t<emptyNode />\n\
\tParent title comes here.\n\
</parentNode>\n\
\n\
 <!-- Long element's names -->\n\
 <!-- 0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF -->\n\
     <parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz>\n\
     \t1st long node name\n\
     \t<parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmn_2ndLONGNAME>\n\
     \t\t2nd long node name\n\
     \t</parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmn_2ndLONGNAME>\n\
     </parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz>\r\n\
</> <!-- Erroneous element -->\r\n\
<parentNode description=\"other element\">\
\t<!-- 2nd well formed element -->\
\t 2nd well formed element\
\t<intNode>20</intNode>\
\t<strNode></strNode>\
\t<boolNode>any value</boolNode>\
\t<floatNode>-45E5</floatNode>\
</parentNode>\
");

/*Wide-character XML Element test sample.
 */
const wchar_t* g_wszTestXmlElement =
    L"  <magazine style=\"glossy\" frequency=\"monthly\">\n"
    L"    <title>Road and Track</title>\n"
    L"    <price>3.50</price>\n"
    L"    <subscription price=\"24\" per=\"year\"/>\n"
    L"    <subscription price=\"11.50\" per=\"halfyear\"/>\n"
    L"    <special_edition per_year=\"1\">Yes</special_edition>\n"
    L"  </magazine>";

/*Test sample of raw text to be convrted to the XML document.
 */
TCHAR g_szTestXmlEscape[]=
_T("do\n\
  {\n\
  nDigit = iValue & 7;\n\
  iValue = (iValue >> 3) & 0x1FFF;\n\
  *pTemp++ = (TCHAR)(nDigit + _T('0'));\n\
  }\n\
  while(iValue > 0);\n\
\n\
*pTemp = _T('\\0');\n\
\n\
/*Reverse string in place*/\n\
pTemp--; /*Pointer to the last character*/\n\
while(pBuffer < pTemp)\n\
  {\n\
  int cTemp = *pBuffer;\n\
  *pBuffer++ = *pTemp;\n\
  *pTemp-- = (TCHAR)cTemp;\n\
  }\n\
  _tcout << _T(\"converted number: \") << pBuffer;\n\
");

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: TestXml.c,v $
 * Revision 1.4  2009/10/09 17:56:27  ddarko
 * Unit test
 *
 * Revision 1.3  2009/10/08 21:37:07  ddarko
 * Test XML escape
 *
 * Revision 1.2  2009/10/07 21:42:17  ddarko
 * Test tag names
 *
 * Revision 1.1  2009/10/07 14:09:17  ddarko
 * Created
 *
 *****************************************************************************/
