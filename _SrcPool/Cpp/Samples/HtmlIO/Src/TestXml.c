
/*$RCSfile: TestXml.c,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/10/07 14:09:17 $
  $Author: ddarko $

  Global test samples
  2009-09-30 Darko Kolakovic
*/

/* Group=Examples
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"

/*XML document text sample
 */
TCHAR g_szTestXml[] =
_T("<?xml version=\"1.0\"?>\
<?xml-stylesheet type=\"text/xsl\" href=\"myfile.xsl\"?>\
<!-- example XML document -->\
<parentNode description=\"Well formed element\">\
\t<!-- Well formed element -->\
\t<intNode>10</intNode>\
\t<strNode>string</strNode>\
\t<boolNode>true</boolNode>\
\t<floatNode>0.3</floatNode>\
\t<emptyNode />\
\tParent title comes here.\
</parentNode>\
 \
 <!-- Long element's names -->\
 <!-- 0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF -->\
     <parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz>\
     \t1st long node name\
     \t<parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmn_2ndLONGNAME>\
     \t\t2nd long node name\
     \t</parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmn_2ndLONGNAME>\
     </parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz>\
</> <!-- Erroneous element -->\
");

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: TestXml.c,v $
 * Revision 1.1  2009/10/07 14:09:17  ddarko
 * Created
 *
 *****************************************************************************/
