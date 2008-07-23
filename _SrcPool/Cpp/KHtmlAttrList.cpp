/*$RCSfile: KHtmlAttrList.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2008/07/23 19:41:12 $
  $Author: ddarko $

  List of HTML attribute names.
  Darko Kolakovic 2008-07-22
*/
/* Group=Strings                                                             */

//-----------------------------------------------------------------------------
/*List of HTML attribute names.
  The last element in the list is equal to NULL.

  See also: XmlEscape(), VB Function XmlEscape, Function XmlUnescape,
  Boost STL class xml_escape,class xml_unescape
  {html:
  <a href="http://www.w3.org/TR/html4/index/elements.html">HTML 4.01 Elements</a>,
  <a href="http://www.w3.org/TR/html4/index/attributes.html">HTML 4.01 Attributes</a>,
  }
 */
LPCTSTR g_listHtmlAttr[] =
  {
    {_T("align")       },  //00
    {_T("alink")       },  //01
    {_T("alt")         },  //02
    {_T("append")      },  //03
    {_T("asrc")        },  //04
    {_T("background")  },  //05
    {_T("bgcolor")     },  //06
    {_T("border")      },  //07
    {_T("cancel")      },  //08
    {_T("cellpadding") },  //09
    {_T("cellspacing") },  //10
    {_T("checked")     },  //11
    {_T("clear")       },  //12
    {_T("code")        },  //13
    {_T("codebase")    },  //14
    {_T("color")       },  //15
    {_T("cols")        },  //16
    {_T("colspan")     },  //17
    {_T("compact")     },  //18
    {_T("continue")    },  //19
    {_T("coords")      },  //20
    {_T("dp")          },  //21
    {_T("face")        },  //22
    {_T("fadein")      },  //23
    {_T("fadeout")     },  //24
    {_T("height")      },  //25
    {_T("hlink")       },  //26
    {_T("href")        },  //27
    {_T("hspace")      },  //28
    {_T("hsrc")        },  //29
    {_T("id")          },  //30
    {_T("indent")      },  //31
    {_T("interrupt")   },  //32
    {_T("ismap")       },  //33
    {_T("layer")       },  //34
    {_T("link")        },  //35
    {_T("maxlength")   },  //36
    {_T("multiple")    },  //37
    {_T("name")        },  //38
    {_T("noenter")     },  //39
    {_T("nohref")      },  //40
    {_T("noshade")     },  //41
    {_T("nowrap")      },  //42
    {_T("plain")       },  //43
    {_T("random")      },  //44
    {_T("rel")         },  //45
    {_T("remove")      },  //46
    {_T("removeall")   },  //47
    {_T("repeat")      },  //48
    {_T("rev")         },  //49
    {_T("rows")        },  //50
    {_T("rowspan")     },  //51
    {_T("selected")    },  //52
    {_T("seqnum")      },  //53
    {_T("sequence")    },  //54
    {_T("shape")       },  //55
    {_T("size")        },  //56
    {_T("src")         },  //57
    {_T("start")       },  //58
    {_T("text")        },  //59
    {_T("title")       },  //60
    {_T("to")          },  //61
    {_T("type")        },  //62
    {_T("usemap")      },  //63
    {_T("valign")      },  //64
    {_T("value")       },  //65
    {_T("vlink")       },  //66
    {_T("vspace")      },  //67
    {_T("width")       },  //68
    { 0 }    //End of list   69
  };

//------------------------------------------------------------------------------
/*List of possible value keywords for HTML attributes.
  The last element in the list is equal to NULL.

  See also:
  {html:
  <a href="http://www.w3.org/TR/html4/index/elements.html">HTML 4.01 Elements</a>,
  <a href="http://www.w3.org/TR/html4/index/attributes.html">HTML 4.01 Attributes</a>,
  }
 */
LPCTSTR g_listHtmlAttrValue[] =
  {
    {_T("alink")       },  //00
    {_T("all")         },  //01
    {_T("ambient")     },  //02
    {_T("aqua")        },  //03
    {_T("background")  },  //04
    {_T("bgambient")   },  //05
    {_T("bgcolor")     },  //06
    {_T("black")       },  //07
    {_T("blue")        },  //08
    {_T("border")      },  //09
    {_T("bottom")      },  //10
    {_T("cancel")      },  //11
    {_T("center")      },  //12
    {_T("checkbox")    },  //13
    {_T("circle")      },  //14
    {_T("cycle")       },  //15
    {_T("decimal")     },  //16
    {_T("disc")        },  //17
    {_T("file")        },  //18
    {_T("foreground")  },  //19
    {_T("fuchsia")     },  //20
    {_T("gray")        },  //21
    {_T("green")       },  //22
    {_T("hidden")      },  //23
    {_T("hlink")       },  //24
    {_T("image")       },  //25
    {_T("justify")     },  //26
    {_T("left")        },  //27
    {_T("lime")        },  //28
    {_T("link")        },  //29
    {_T("loop")        },  //30
    {_T("maroon")      },  //31
    {_T("middle")      },  //32
    {_T("navy")        },  //33
    {_T("olive")       },  //34
    {_T("password")    },  //35
    {_T("poly")        },  //36
    {_T("previous")    },  //37
    {_T("purple")      },  //38
    {_T("radio")       },  //39
    {_T("random")      },  //40
    {_T("rect")        },  //41
    {_T("red")         },  //42
    {_T("replace")     },  //43
    {_T("reset")       },  //44
    {_T("right")       },  //45
    {_T("silver")      },  //46
    {_T("square")      },  //47
    {_T("statusbg")    },  //48
    {_T("statustext")  },  //49
    {_T("submit")      },  //50
    {_T("teal")        },  //51
    {_T("text")        },  //52
    {_T("top")         },  //53
    {_T("white")       },  //54
    {_T("yellow")      },  //55
    { 0 }    //End of list   56
  };

//-----------------------------------------------------------------------------
/*HTML 4.01 - Character entities http://www.w3.org/tr/html401/sgml/entities.html

HTML 4 Character Entities ../../Doc/Html/KHtmlCharEntity.htm
 */
struct SHtmlChEntity
  {
  uint32_t  m_nUnicode; //Unicode value
  LPCTSTR   m_szEntity; //HTML character entity name
  };


/*
  Arrow: arrows
  glyph: ?
  Greek: Greek letters
  HTML 4.0 character extensions
  HTML4: HTML 4.0 character extensions
  Lat_B: Latin-extended B
  MathL: letter-like symbols
  MathO: mathematical operators
  punct: general punctuation marks
  shape: geometric shapes
  Symbl: miscellaneous symbols

 */
const struct SHtmlChEntity g_listHtmlChEntity[] =
  {
    {0x0022, _T("quot")    /*, Html3, 034 */ },//000 " quotation mark = APL quote
    {0x0026, _T("amp")     /*, Html3, 038 */ },//001 & ampersand
    {0x003C, _T("lt")      /*, Html3, 060 */ },//002 < less-than sign
    {0x003E, _T("gt")      /*, Html3, 062 */ },//003 > greater-than sign
    {0x00A0, _T("nbsp")    /*, Html3, 160 */ },//004   non-breaking space
    {0x00A1, _T("iexcl")   /*, Html3, 161 */ },//005 ¡ inverted exclamation mark
    {0x00A2, _T("cent")    /*, Html3, 162 */ },//006 ¢ cent sign
    {0x00A3, _T("pound")   /*, Html3, 163 */ },//007 £ pound sign
    {0x00A4, _T("curren")  /*, Html3, 164 */ },//008 ¤ currency sign
    {0x00A5, _T("yen")     /*, Html3, 165 */ },//009 ¥ yen sign = yuan sign
    {0x00A6, _T("brvbar")  /*, Html3, 166 */ },//010 ¦ broken bar = broken vertical bar
    {0x00A7, _T("sect")    /*, Html3, 167 */ },//011 § section sign
    {0x00A8, _T("uml")     /*, Html3, 168 */ },//012 ¨ diaeresis = spacing diaeresis
    {0x00A9, _T("copy")    /*, Html3, 169 */ },//013 © copyright sign
    {0x00AA, _T("ordf")    /*, Html3, 170 */ },//014 ª feminine ordinal indicator
    {0x00AB, _T("laquo")   /*, Html3, 171 */ },//015 « left-pointing double angle quotation mark = left guillemet
    {0x00AC, _T("not")     /*, Html3, 172 */ },//016 ¬ not sign
    {0x00AD, _T("shy")     /*, Html3, 173 */ },//017 ­ soft hyphen = discretionary hyphen
    {0x00AE, _T("reg")     /*, Html3, 174 */ },//018 ® registered sign = registered trade mark sign
    {0x00AF, _T("macr")    /*, Html3, 175 */ },//019 ¯ macron = spacing macron = overline = APL overbar
    {0x00B0, _T("deg")     /*, Html3, 176 */ },//020 ° degree sign
    {0x00B1, _T("plusmn")  /*, Html3, 177 */ },//021 ± plus-minus sign = plus-or-minus sign
    {0x00B2, _T("sup2")    /*, Html3, 178 */ },//022 ² superscript two = superscript digit two = squared
    {0x00B3, _T("sup3")    /*, Html3, 179 */ },//023 ³ superscript three = superscript digit three = cubed
    {0x00B4, _T("acute")   /*, Html3, 180 */ },//024 ´ acute accent = spacing acute
    {0x00B5, _T("micro")   /*, Html3, 181 */ },//025 µ micro sign
    {0x00B6, _T("para")    /*, Html3, 182 */ },//026 ¶ pilcrow sign = paragraph sign
    {0x00B7, _T("middot")  /*, Html3, 183 */ },//027 · middle dot = Georgian comma = Greek middle dot
    {0x00B8, _T("cedil")   /*, Html3, 184 */ },//028 ¸ cedilla = spacing cedilla
    {0x00B9, _T("sup1")    /*, Html3, 185 */ },//029 ¹ superscript one = superscript digit one
    {0x00BA, _T("ordm")    /*, Html3, 186 */ },//030 º masculine ordinal indicator
    {0x00BB, _T("raquo")   /*, Html3, 187 */ },//031 » right-pointing double angle quotation mark = right guillemet
    {0x00BC, _T("frac14")  /*, Html3, 188 */ },//032 ¼ vulgar fraction one quarter
    {0x00BD, _T("frac12")  /*, Html3, 189 */ },//033 ½ vulgar fraction one half
    {0x00BE, _T("frac34")  /*, Html3, 190 */ },//034 ¾ vulgar fraction three quarters
    {0x00BF, _T("iquest")  /*, Html3, 191 */ },//035 ¿ inverted question mark
    {0x00C0, _T("Agrave")  /*, Html3, 192 */ },//036 À latin capital letter A with grave
    {0x00C1, _T("Aacute")  /*, Html3, 193 */ },//037 Á latin capital letter A with acute
    {0x00C2, _T("Acirc")   /*, Html3, 194 */ },//038 Â latin capital letter A with circumflex
    {0x00C3, _T("Atilde")  /*, Html3, 195 */ },//039 Ã latin capital letter A with tilde
    {0x00C4, _T("Auml")    /*, Html3, 196 */ },//040 Ä latin capital letter A with diaeresis
    {0x00C5, _T("Aring")   /*, Html3, 197 */ },//041 Å latin capital letter A with ring above.
    {0x00C6, _T("AElig")   /*, Html3, 198 */ },//042 Æ latin capital ligature AE
    {0x00C7, _T("Ccedil")  /*, Html3, 199 */ },//043 Ç latin capital letter C with cedilla
    {0x00C8, _T("Egrave")  /*, Html3, 200 */ },//044 È latin capital letter E with grave
    {0x00C9, _T("Eacute")  /*, Html3, 201 */ },//045 É latin capital letter E with acute
    {0x00CA, _T("Ecirc")   /*, Html3, 202 */ },//046 Ê latin capital letter E with circumflex
    {0x00CB, _T("Euml")    /*, Html3, 203 */ },//047 Ë latin capital letter E with diaeresis
    {0x00CC, _T("Igrave")  /*, Html3, 204 */ },//048 Ì latin capital letter I with grave
    {0x00CD, _T("Iacute")  /*, Html3, 205 */ },//049 Í latin capital letter I with acute
    {0x00CE, _T("Icirc")   /*, Html3, 206 */ },//050 Î latin capital letter I with circumflex
    {0x00CF, _T("Iuml")    /*, Html3, 207 */ },//051 Ï latin capital letter I with diaeresis
    {0x00D0, _T("ETH")     /*, Html3, 208 */ },//052 Ð latin capital letter ETH
    {0x00D1, _T("Ntilde")  /*, Html3, 209 */ },//053 Ñ latin capital letter N with tilde
    {0x00D2, _T("Ograve")  /*, Html3, 210 */ },//054 Ò latin capital letter O with grave
    {0x00D3, _T("Oacute")  /*, Html3, 211 */ },//055 Ó latin capital letter O with acute
    {0x00D4, _T("Ocirc")   /*, Html3, 212 */ },//056 Ô latin capital letter O with circumflex
    {0x00D5, _T("Otilde")  /*, Html3, 213 */ },//057 Õ latin capital letter O with tilde
    {0x00D6, _T("Ouml")    /*, Html3, 214 */ },//058 Ö latin capital letter O with diaeresis
    {0x00D7, _T("times")   /*, Html3, 215 */ },//059 × multiplication sign
    {0x00D8, _T("Oslash")  /*, Html3, 216 */ },//060 Ø latin capital letter O with stroke
    {0x00D9, _T("Ugrave")  /*, Html3, 217 */ },//061 Ù latin capital letter U with grave
    {0x00DA, _T("Uacute")  /*, Html3, 218 */ },//062 Ú latin capital letter U with acute
    {0x00DB, _T("Ucirc")   /*, Html3, 219 */ },//063 Û latin capital letter U with circumflex
    {0x00DC, _T("Uuml")    /*, Html3, 220 */ },//064 Ü latin capital letter U with diaeresis
    {0x00DD, _T("Yacute")  /*, Html3, 221 */ },//065 Ý latin capital letter Y with acute
    {0x00DE, _T("THORN")   /*, Html3, 222 */ },//066 Þ latin capital letter THORN
    {0x00DF, _T("szlig")   /*, Html3, 223 */ },//067 ß latin small letter sharp s
    {0x00E0, _T("agrave")  /*, Html3, 224 */ },//068 à latin small letter a with grave
    {0x00E1, _T("aacute")  /*, Html3, 225 */ },//069 á latin small letter a with acute
    {0x00E2, _T("acirc")   /*, Html3, 226 */ },//070 â latin small letter a with circumflex
    {0x00E3, _T("atilde")  /*, Html3, 227 */ },//071 ã latin small letter a with tilde
    {0x00E4, _T("auml")    /*, Html3, 228 */ },//072 ä latin small letter a with diaeresis
    {0x00E5, _T("aring")   /*, Html3, 229 */ },//073 å latin small letter a with ring above
    {0x00E6, _T("aelig")   /*, Html3, 230 */ },//074 æ latin small ligature ae
    {0x00E7, _T("ccedil")  /*, Html3, 231 */ },//075 ç latin small letter c with cedilla
    {0x00E8, _T("egrave")  /*, Html3, 232 */ },//076 è latin small letter e with grave
    {0x00E9, _T("eacute")  /*, Html3, 233 */ },//077 é latin small letter e with acute
    {0x00EA, _T("ecirc")   /*, Html3, 234 */ },//078 ê latin small letter e with circumflex
    {0x00EB, _T("euml")    /*, Html3, 235 */ },//079 ë latin small letter e with diaeresis
    {0x00EC, _T("igrave")  /*, Html3, 236 */ },//080 ì latin small letter i with grave
    {0x00ED, _T("iacute")  /*, Html3, 237 */ },//081 í latin small letter i with acute
    {0x00EE, _T("icirc")   /*, Html3, 238 */ },//082 î latin small letter i with circumflex
    {0x00EF, _T("iuml")    /*, Html3, 239 */ },//083 ï latin small letter i with diaeresis
    {0x00F0, _T("eth")     /*, Html3, 240 */ },//084 ð latin small letter eth
    {0x00F1, _T("ntilde")  /*, Html3, 241 */ },//085 ñ latin small letter n with tilde
    {0x00F2, _T("ograve")  /*, Html3, 242 */ },//086 ò latin small letter o with grave
    {0x00F3, _T("oacute")  /*, Html3, 243 */ },//087 ó latin small letter o with acute
    {0x00F4, _T("ocirc")   /*, Html3, 244 */ },//088 ô latin small letter o with circumflex
    {0x00F5, _T("otilde")  /*, Html3, 245 */ },//089 õ latin small letter o with tilde
    {0x00F6, _T("ouml")    /*, Html3, 246 */ },//090 ö latin small letter o with diaeresis
    {0x00F7, _T("divide")  /*, Html3, 247 */ },//091 ÷ division sign
    {0x00F8, _T("oslash")  /*, Html3, 248 */ },//092 ø latin small letter o with stroke
    {0x00F9, _T("ugrave")  /*, Html3, 249 */ },//093 ù latin small letter u with grave
    {0x00FA, _T("uacute")  /*, Html3, 250 */ },//094 ú latin small letter u with acute
    {0x00FB, _T("ucirc")   /*, Html3, 251 */ },//095 û latin small letter u with circumflex
    {0x00FC, _T("uuml")    /*, Html3, 252 */ },//096 ü latin small letter u with diaeresis
    {0x00FD, _T("yacute")  /*, Html3, 253 */ },//097 ý latin small letter y with acute
    {0x00FE, _T("thorn")   /*, Html3, 254 */ },//098 þ latin small letter thorn
    {0x00FF, _T("yuml")    /*, Html3, 255 */ },//099 ÿ latin small letter y with diaeresis
    {0x0152, _T("OElig")   /*, HTML4, 338 */ },//100 Œ latin capital ligature OE
    {0x0153, _T("oelig")   /*, HTML4, 339 */ },//101 œ latin small ligature oe
    {0x0160, _T("Scaron")  /*, HTML4, 352 */ },//102 Š latin capital letter S with caron
    {0x0161, _T("scaron")  /*, HTML4, 353 */ },//103 š latin small letter s with caron
    {0x0178, _T("Yuml")    /*, HTML4, 376 */ },//104 Ÿ latin capital letter Y with diaeresis
    {0x0192, _T("fnof")    /*, Lat_B, 402 */ },//105 ƒ latin small f with hook = function = florin
    {0x02C6, _T("circ")    /*, HTML4, 710 */ },//106 ˆ modifier letter circumflex accent
    {0x02DC, _T("tilde")   /*, HTML4, 732 */ },//107 ˜ small tilde
    {0x0391, _T("Alpha")   /*, Greek, 913 */ },//108 ? greek capital letter alpha
    {0x0392, _T("Beta")    /*, Greek, 914 */ },//109 ? greek capital letter beta
    {0x0393, _T("Gamma")   /*, Greek, 915 */ },//110 G greek capital letter gamma
    {0x0394, _T("Delta")   /*, Greek, 916 */ },//111 ? greek capital letter delta
    {0x0395, _T("Epsilon") /*, Greek, 917 */ },//112 ? greek capital letter epsilon
    {0x0396, _T("Zeta")    /*, Greek, 918 */ },//113 ? greek capital letter zeta
    {0x0397, _T("Eta")     /*, Greek, 919 */ },//114 ? greek capital letter eta
    {0x0398, _T("Theta")   /*, Greek, 920 */ },//115 T greek capital letter theta
    {0x0399, _T("Iota")    /*, Greek, 921 */ },//116 ? greek capital letter iota
    {0x039A, _T("Kappa")   /*, Greek, 922 */ },//117 ? greek capital letter kappa
    {0x039B, _T("Lambda")  /*, Greek, 923 */ },//118 ? greek capital letter lambda
    {0x039C, _T("Mu")      /*, Greek, 924 */ },//119 ? greek capital letter mu
    {0x039D, _T("Nu")      /*, Greek, 925 */ },//120 ? greek capital letter nu
    {0x039E, _T("Xi")      /*, Greek, 926 */ },//121 ? greek capital letter xi
    {0x039F, _T("Omicron") /*, Greek, 927 */ },//122 ? greek capital letter omicron
    {0x03A0, _T("Pi")      /*, Greek, 928 */ },//123 ? greek capital letter pi
    {0x03A1, _T("Rho")     /*, Greek, 929 */ },//124 ? greek capital letter rho
    {0x03A3, _T("Sigma")   /*, Greek, 931 */ },//125 S greek capital letter sigma
    {0x03A4, _T("Tau")     /*, Greek, 932 */ },//126 ? greek capital letter tau
    {0x03A5, _T("Upsilon") /*, Greek, 933 */ },//127 ? greek capital letter upsilon
    {0x03A6, _T("Phi")     /*, Greek, 934 */ },//128 F greek capital letter phi
    {0x03A7, _T("Chi")     /*, Greek, 935 */ },//129 ? greek capital letter chi
    {0x03A8, _T("Psi")     /*, Greek, 936 */ },//130 ? greek capital letter psi
    {0x03A9, _T("Omega")   /*, Greek, 937 */ },//131 O greek capital letter omega
    {0x03B1, _T("alpha")   /*, Greek, 945 */ },//132 a greek small letter alpha
    {0x03B2, _T("beta")    /*, Greek, 946 */ },//133 ß greek small letter beta
    {0x03B3, _T("gamma")   /*, Greek, 947 */ },//134 ? greek small letter gamma
    {0x03B4, _T("delta")   /*, Greek, 948 */ },//135 d greek small letter delta
    {0x03B5, _T("epsilon") /*, Greek, 949 */ },//136 e greek small letter epsilon
    {0x03B6, _T("zeta")    /*, Greek, 950 */ },//137 ? greek small letter zeta
    {0x03B7, _T("eta")     /*, Greek, 951 */ },//138 ? greek small letter eta
    {0x03B8, _T("theta")   /*, Greek, 952 */ },//139 ? greek small letter theta
    {0x03B9, _T("iota")    /*, Greek, 953 */ },//140 ? greek small letter iota
    {0x03BA, _T("kappa")   /*, Greek, 954 */ },//141 ? greek small letter kappa
    {0x03BB, _T("lambda")  /*, Greek, 955 */ },//142 ? greek small letter lambda
    {0x03BC, _T("mu")      /*, Greek, 956 */ },//143 µ greek small letter mu
    {0x03BD, _T("nu")      /*, Greek, 957 */ },//144 ? greek small letter nu
    {0x03BE, _T("xi")      /*, Greek, 958 */ },//145 ? greek small letter xi
    {0x03BF, _T("omicron") /*, Greek, 959 */ },//146 ? greek small letter omicron
    {0x03C0, _T("pi")      /*, Greek, 960 */ },//147 p greek small letter pi
    {0x03C1, _T("rho")     /*, Greek, 961 */ },//148 ? greek small letter rho
    {0x03C2, _T("sigmaf")  /*, Greek, 962 */ },//149 ? greek small letter final sigma
    {0x03C3, _T("sigma")   /*, Greek, 963 */ },//150 s greek small letter sigma
    {0x03C4, _T("tau")     /*, Greek, 964 */ },//151 t greek small letter tau
    {0x03C5, _T("upsilon") /*, Greek, 965 */ },//152 ? greek small letter upsilon
    {0x03C6, _T("phi")     /*, Greek, 966 */ },//153 f greek small letter phi
    {0x03C7, _T("chi")     /*, Greek, 967 */ },//154 ? greek small letter chi
    {0x03C8, _T("psi")     /*, Greek, 968 */ },//155 ? greek small letter psi
    {0x03C9, _T("omega")   /*, Greek, 969 */ },//156 ? greek small letter omega
    {0x03D1, _T("thetasym")/*, Greek, 977 */ },//157 ? greek small letter theta symbol
    {0x03D2, _T("upsih")   /*, Greek, 978 */ },//158 ? greek upsilon with hook symbol
    {0x03D6, _T("piv")     /*, Greek, 982 */ },//159 ? greek pi symbol
    {0x2002, _T("ensp")    /*, glyph, */ },//160   en space, ½ em, nut
    {0x2003, _T("emsp")    /*, glyph, */ },//161   em space. mutton, equal to type size in points
    {0x2009, _T("thinsp")  /*, glyph, */ },//162 ? thin space, 1/5 em
    {0x200C, _T("zwnj")    /*, glyph, */ },//163 ? zero width non-joiner (formatting)
    {0x200D, _T("zwj")     /*, glyph, */ },//164 ? zero width joiner (formatting)
    {0x200E, _T("lrm")     /*, glyph, */ },//165 ? left-to-right mark (formatting)
    {0x200F, _T("rlm")     /*, glyph, */ },//166 ? right-to-left mark (formatting)
    {0x2013, _T("ndash")   /*, HTML4,8211 */ },//167 – en dash
    {0x2014, _T("mdash")   /*, HTML4,8212 */ },//168 — em dash
    {0x2018, _T("lsquo")   /*, HTML4,8216 */ },//169 ‘ left single quotation mark
    {0x2019, _T("rsquo")   /*, HTML4,8217 */ },//170 ’ right single quotation mark
    {0x201A, _T("sbquo")   /*, HTML4,8218 */ },//171 ‚ single low-9 quotation mark
    {0x201C, _T("ldquo")   /*, HTML4,8220 */ },//172 “ left double quotation mark
    {0x201D, _T("rdquo")   /*, HTML4,8221 */ },//173 ” right double quotation mark
    {0x201E, _T("bdquo")   /*, HTML4,8222 */ },//174 „ double low-9 quotation mark
    {0x2020, _T("dagger")  /*, HTML4,8224 */ },//175 † dagger
    {0x2021, _T("Dagger")  /*, HTML4,8225 */ },//176 ‡ double dagger
    {0x2022, _T("bull")    /*, punct,8226 */ },//177 • bullet = black small circle
    {0x2026, _T("hellip")  /*, punct,8230 */ },//178 … horizontal ellipsis = three dot leader
    {0x2030, _T("permil")  /*, HTML4,8240 */ },//179 ‰ per mille sign
    {0x2032, _T("prime")   /*, MathO,8242 */ },//180 ' prime = minutes = feet unit
    {0x2033, _T("Prime")   /*, MathO,8243 */ },//181 ? double prime = seconds = inches
    {0x2039, _T("lsaquo")  /*, HTML4,8249 */ },//182 ‹ single left-pointing angle quotation mark
    {0x203A, _T("rsaquo")  /*, HTML4,8250 */ },//183 › single right-pointing angle quotation mark
    {0x203E, _T("oline")   /*, punct,8254 */ },//184 ? overline = spacing overscore
    {0x2044, _T("frasl")   /*, MathO,8260 */ },//185 / fraction slash
    {0x20AC, _T("euro")    /*, glyph, */ },//186 € euro sign
    {0x2111, _T("image")   /*, MathL,8465 */ },//187 I blackletter capital I = imaginary part symbol
    {0x2118, _T("weierp")  /*, MathL,8472 */ },//188 P script capital P = power set = Weierstraß elliptic function
    {0x211C, _T("real")    /*, MathL,8476 */ },//189 R blackletter capital R = real part symbol
    {0x2122, _T("trade")   /*, glyph, */ },//190 ™ trade mark sign
    {0x2135, _T("alefsym") /*, MathL,8501 */ },//191 ? alef symbol = first transfinite cardinal - countable
    {0x2190, _T("larr")    /*, Arrow,8592 */ },//192 ? leftwards arrow
    {0x2191, _T("uarr")    /*, Arrow,8593 */ },//193 ? upwards arrow
    {0x2192, _T("rarr")    /*, Arrow,8594 */ },//194 ? rightwards arrow
    {0x2193, _T("darr")    /*, Arrow,8595 */ },//195 ? downwards arrow
    {0x2194, _T("harr")    /*, Arrow,8596 */ },//196 ? left right arrow
    {0x21B5, _T("crarr")   /*, Arrow,8629 */ },//197 ? downwards arrow with corner leftwards = carriage return
    {0x21D0, _T("lArr")    /*, Arrow,8656 */ },//198 ? leftwards double arrow
    {0x21D1, _T("uArr")    /*, Arrow,8657 */ },//199 ? upwards double arrow
    {0x21D2, _T("rArr")    /*, Arrow,8658 */ },//200 ? rightwards double arrow
    {0x21D3, _T("dArr")    /*, Arrow,8659 */ },//201 ? downwards double arrow
    {0x21D4, _T("hArr")    /*, Arrow,8660 */ },//202 ? left right double arrow
    {0x2200, _T("forall")  /*, MathO,8704 */ },//203 ? for all
    {0x2202, _T("part")    /*, MathO,8706 */ },//204 ? partial differential
    {0x2203, _T("exist")   /*, MathO,8707 */ },//205 ? existential quantifier, there exists
    {0x2205, _T("empty")   /*, MathO,8709 */ },//206 Ø empty set = null set = diameter
    {0x2207, _T("nabla")   /*, MathO,8711 */ },//207 ? nabla = backward difference = gradient, del
    {0x2208, _T("isin")    /*, MathO,8712 */ },//208 ? element of set
    {0x2209, _T("notin")   /*, MathO,8713 */ },//209 ? not an element of set
    {0x220B, _T("ni")      /*, MathO,8715 */ },//210 ? contains as member of set, such that, owns
    {0x220F, _T("prod")    /*, MathO,8719 */ },//211 ? n-ary product = product sign
    {0x2211, _T("sum")     /*, MathO,8721 */ },//212 ? n-ary sumation
    {0x2212, _T("minus")   /*, MathO,8722 */ },//213 - minus sign
    {0x2217, _T("lowast")  /*, MathO,8727 */ },//214 * asterisk operator
    {0x221A, _T("radic")   /*, MathO,8730 */ },//215 v square root = radical sign
    {0x221D, _T("prop")    /*, MathO,8733 */ },//216 ? proportional to
    {0x221E, _T("infin")   /*, MathO,8734 */ },//217 8 infinity
    {0x2220, _T("ang")     /*, MathO,8736 */ },//218 ? angle
    {0x2227, _T("and")     /*, MathO,8743 */ },//219 ? logical and = conjunction = wedge
    {0x2228, _T("or")      /*, MathO,8744 */ },//220 ? logical or = disjunction = vee
    {0x2229, _T("cap")     /*, MathO,8745 */ },//221 n intersection = cap
    {0x222A, _T("cup")     /*, MathO,8746 */ },//222 ? union = cup
    {0x222B, _T("int")     /*, MathO,8747 */ },//223 ? integral
    {0x2234, _T("there4")  /*, MathO,8756 */ },//224 ? therefore
    {0x223C, _T("sim")     /*, MathO,8764 */ },//225 ~ tilde operator = varies with = similar to
    {0x2245, _T("cong")    /*, MathO,8773 */ },//226 ? approximately equal to
    {0x2248, _T("asymp")   /*, MathO,8776 */ },//227 ˜ almost equal to = asymptotic to
    {0x2260, _T("ne")      /*, MathO,8800 */ },//228 ? not equal to
    {0x2261, _T("equiv")   /*, MathO,8801 */ },//229 = identical to
    {0x2264, _T("le")      /*, MathO,8804 */ },//230 = less-than or equal to
    {0x2265, _T("ge")      /*, MathO,8805 */ },//231 = greater-than or equal to
    {0x2282, _T("sub")     /*, MathO,8834 */ },//232 ? subset of, included in set
    {0x2283, _T("sup")     /*, MathO,8835 */ },//233 ? superset of, includes in set
    {0x2284, _T("nsub")    /*, MathO,8836 */ },//234 ? not a subset of
    {0x2286, _T("sube")    /*, MathO,8838 */ },//235 ? subset of or equal to
    {0x2287, _T("supe")    /*, MathO,8839 */ },//236 ? superset of or equal to
    {0x2295, _T("oplus")   /*, MathO,8853 */ },//237 ? circled plus = direct sum
    {0x2297, _T("otimes")  /*, MathO,8855 */ },//238 ? circled times = vector product
    {0x22A5, _T("perp")    /*, MathO,8869 */ },//239 ? up tack = orthogonal to = perpendicular
    {0x22C5, _T("sdot")    /*, MathO,8901 */ },//240 · dot operator
    {0x2308, _T("lceil")   /*, MathO,8968 */ },//241 ? left ceiling = apl upstile
    {0x2309, _T("rceil")   /*, MathO,8969 */ },//242 ? right ceiling
    {0x230A, _T("lfloor")  /*, MathO,8970 */ },//243 ? left floor = apl downstile
    {0x230B, _T("rfloor")  /*, MathO,8971 */ },//244 ? right floor
    {0x2329, _T("lang")    /*, MathO,9001 */ },//245 < left-pointing angle bracket
    {0x232A, _T("rang")    /*, MathO,9002 */ },//246 > right-pointing angle bracket
    {0x25CA, _T("loz")     /*, shape,9674 */ },//247 ? lozenge
    {0x2660, _T("spades")  /*, Symbl,9824 */ },//248 ? black spade suit
    {0x2663, _T("clubs")   /*, Symbl,9827 */ },//249 ? black club suit
    {0x2665, _T("hearts")  /*, Symbl,9829 */ },//250 ? black heart suit
    {0x2666, _T("diams")   /*, Symbl,9830 */ },//251 ? black diamond suit
    (0x0   , _T('\0')     //End of list   252
 */ };

/* Latin-2 characters*/
const struct SHtmlChEntity g_listHtmlChEntityLat2[] =
  {
    {258 , _T("Abreve")},
    {259 , _T("abreve")},
    {260 , _T("Aogon") },
    {261 , _T("aogon") },
    {262 , _T("Cacute")},
    {263 , _T("cacute")},
    {268 , _T("Ccaron")},
    {269 , _T("ccaron")},
    {270 , _T("Dcaron")},
    {271 , _T("dcaron")},
    {272 , _T("Dstrok")},
    {273 , _T("dstrok")},
    {280 , _T("Eogon") },
    {281 , _T("eogon") },
    {282 , _T("Ecaron")},
    {283 , _T("ecaron")},
    {313 , _T("Lacute")},
    {314 , _T("lacute")},
    {317 , _T("Lcaron")},
    {318 , _T("lcaron")},
    {321 , _T("Lstrok")},
    {322 , _T("lstrok")},
    {323 , _T("Nacute")},
    {324 , _T("nacute")},
    {327 , _T("Ncaron")},
    {328 , _T("ncaron")},
    {336 , _T("Odblac")},
    {337 , _T("odblac")},
    {340 , _T("Racute")},
    {341 , _T("racute")},
    {344 , _T("Rcaron")},
    {345 , _T("rcaron")},
    {346 , _T("Sacute")},
    {347 , _T("sacute")},
    {350 , _T("Scedil")},
    {351 , _T("scedil")},
    {354 , _T("Tcedil")},
    {355 , _T("tcedil")},
    {356 , _T("Tcaron")},
    {357 , _T("tcaron")},
    {366 , _T("Uring") },
    {367 , _T("uring") },
    {368 , _T("Udblac")},
    {369 , _T("udblac")},
    {377 , _T("Zacute")},
    {378 , _T("zacute")},
    {379 , _T("Zdot")  },
    {380 , _T("zdot")  },
    {381 , _T("Zcaron")},
    {382 , _T("zcaron")},
    {711 , _T("caron") },
    {728 , _T("breve") },
    {729   _T("dot")   },
    {731 , _T("ogon")  },
    {733 , _T("dblac") }
  };
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KHtmlAttrList.cpp,v $
 * Revision 1.1  2008/07/23 19:41:12  ddarko
 * Created
 *
 *****************************************************************************/

