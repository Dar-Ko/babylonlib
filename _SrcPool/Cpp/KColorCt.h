/*$Workfile: KColorCt.h$: header file
  $Revision: 9$ $Date: 1/29/02 11:19:54 PM$
  $Author: Darko$

  Predefined Color Codes
  Copyright: CommonSoft Inc.
  D.Kolakovic  Jun '95
 */

#ifndef _KCOLORCT_H_
    /*KColorCt.h sentry                                                      */
  #define _KCOLORCT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/*---------------------------------------------------------------------------*/
/*{html:<A HREF="Res/KColorCt.htm">}
  Index table for the  16 colors palette
  {html:</A>}
 */
enum COLOR
  {
  black       =0x0,
  blue        =0x1,
  green       =0x2,
  cyan        =0x3,
  red         =0x4,
  magenta     =0x5,
  brown       =0x6,
  white       =0x7,
  grey        =0x8,
  lightblue   =0x9,
  lightgreen  =0xA,
  lightcyan   =0xB,
  lightred    =0xC,
  lightmagenta=0xD,
  yellow      =0xE,
  brightwhite =0xF,
  error       =0xFFFF
  };

/* Group=Color Constants                                                     */

/* {html:<A HREF="Res/KColorCt.htm">}            */
/* 16 Colors Palette                             */
/* {html:</A>}                                   */
/*      Color Name             Red Green Blue    */
#define BLACK               RGB(  0,  0,  0) /*0*/
#define BLUE                RGB(  0,  0,128) /*1*/
#define GREEN               RGB(  0,128,  0) /*2*/
#define CYAN                RGB(  0,128,128) /*3*/
#define RED                 RGB(128,  0,  0) /*4*/
#define MAGENTA             RGB(128,  0,128) /*5*/
#define BROWN               RGB(128,128,  0) /*6*/
#define WHITE               RGB(200,200,200) /*7*/
#define GREY                RGB(128,128,128) /*8*/
#define LIGHTBLUE           RGB(  0,  0,255) /*9*/
#define LIGHTGREEN          RGB(  0,255,  0) /*A*/
#define LIGHTCYAN           RGB(  0,255,255) /*B*/
#define LIGHTRED            RGB(255,  0,  0) /*C*/
#define LIGHTMAGENTA        RGB(255,  0,255) /*D*/
#define YELLOW              RGB(255,255,  0) /*E*/
#define BRIGHTWHITE         RGB(255,255,255) /*F*/

/* -------------------------------------------------------------------------- */
/*{html:<A HREF="Res/KColorCt_256_colors_palette.htm">}                                          */
/*  256 Colors Palette                                                        */
/*{html:</A>}                                                                 */
/*      Color Name               Red Green Blue                               */
#define ALICEBLUE             RGB(240,248,255)
#define ANTIQUEWHITE          RGB(255,239,219)
#define AQUAMARINE            RGB(127,255,212)
#define AZURE                 RGB(240,255,255)
#define BACKGROUND            RGB(  0,  0,  1)
#define BEIGE                 RGB(245,245,220)
#define BISQUE                RGB(255,228,196)
//      BLACK
#define BLANCHEDALMOND        RGB(255,235,205)
//      BLUE
#define BLUEVIOLET            RGB(138, 43,226)
#define BURLYWOOD             RGB(255,211,155)
#define CADETBLUE             RGB(152,245,255)
#define CHARTREUSE            RGB(127,255,  0)
#define CHARTREUSELIMESALMON  RGB(144,200, 52)
#define CHOCOLATE             RGB(255,127, 36)
#define CORAL                 RGB(255,127, 80)
#define CORNFLOWERBLUE        RGB(100,149,237)
#define CORNSILK              RGB(255,248,220)
//      CYAN
#define DARKGOLDENROD         RGB(255,185, 15)
#define DARKGREEN             RGB(  0,100,  0)
#define DARKKHAKI             RGB(189,183,107)
#define DARKOLIVEGREEN        RGB(202,255,112)
#define DARKORANGE            RGB(255,140,  0)
#define DARKORCHID            RGB(191, 62,255)
#define DARKSALMON            RGB(233,150,122)
#define DARKSEAGREEN          RGB(193,255,193)
#define DARKSLATEBLUE         RGB( 72, 61,139)
#define DARKSLATEGRAY         RGB(151,255,255)
#define DARKSLATEGREY         RGB(151,255,255)
#define DARKTURQUOISE         RGB(  0,206,209)
#define DARKVIOLET            RGB(148,  0,211)
#define DEEPPINK              RGB(255, 20,147)
#define DEEPSKYBLUE           RGB(  0,191,255)
#define DEFAULT_COLOR         RGB(253,  3,130)
#define DIMGREY               RGB(105,105,105)
#define DODGERBLUE            RGB( 30,144,255)
#define FIREBRICK             RGB(255, 48, 48)
#define FLORALWHITE           RGB(255,250,240)
#define FORESTGREEN           RGB( 34,139, 34)
#define GAINSBORO             RGB(220,220,220)
#define GHOSTWHITE            RGB(248,248,255)
#define GOLD                  RGB(255,215,  0)
#define GOLDENROD             RGB(255,193, 37)
//      GREY
//      GREEN
#define GREENYELLOW           RGB(173,255, 47)
#define HONEYDEW              RGB(240,255,240)
#define HOTPINK               RGB(255,110,180)
#define INDIANRED             RGB(255,106,106)
#define IVORY                 RGB(255,255,240)
#define KHAKI                 RGB(255,246,143)
#define LAVENDER              RGB(230,230,250)
#define LAVENDERBLUSH         RGB(255,240,245)
#define LAWNGREEN             RGB(124,252,  0)
#define LEMONCHIFFON          RGB(255,250,205)
#define LIGHTCORAL            RGB(240,128,128)
#define LIGHTGOLDENROD        RGB(255,236,139)
#define LIGHTGOLDENRODYELLOW  RGB(250,250,210)
#define LIGHTGREY             RGB(192,192,192)
#define LIGHTPINK             RGB(255,182,193)
#define LIGHTSALMON           RGB(255,160,122)
#define LIGHTSEAGREEN         RGB( 32,178,170)
#define LIGHTSKYBLUE          RGB(176,226,255)
#define LIGHTSLATEBLUE        RGB(132,112,255)
#define LIGHTSLATEGRAY        RGB(119,136,153)
#define LIGHTSLATEGREY        RGB(119,136,153)
#define LIGHTSTEELBLUE        RGB(202,225,255)
#define LIGHTYELLOW           RGB(255,255,224)
#define LIMECYAN              RGB(224,255,255)
#define LIMEGREEN             RGB( 50,205, 50)
#define LINEN                 RGB(250,240,230)
//      MAGENTA
#define MAROON                RGB(255, 52,179)
#define MEDIUMAQUAMARINE      RGB(102,205,170)
#define MEDIUMBLUE            RGB(  0,  0,205)
#define MEDIUMORCHID          RGB(224,102,255)
#define MEDIUMPURPLE          RGB(171,130,255)
#define MEDIUMSEAGREEN        RGB( 60,179,113)
#define MEDIUMSLATEBLUE       RGB(123,104,238)
#define MEDIUMSPRINGGREEN     RGB(  0,250,154)
#define MEDIUMTURQUOISE       RGB( 72,209,204)
#define MEDIUMVIOLETRED       RGB(199, 21,133)
#define MIDNIGHTBLUE          RGB( 25, 25,112)
#define MINTCREAM             RGB(245,255,250)
#define MISTYROSE             RGB(255,228,225)
#define MOCCASIN              RGB(255,228,181)
#define NAVAJOWHITE           RGB(255,222,173)
#define NAVY                  BLUE
#define OLDLACE               RGB(253,245,230)
#define OLIVEDRAB             RGB(192,255, 62)
#define ORANGE                RGB(255,165,  0)
#define ORANGERED             RGB(255, 69,  0)
#define ORCHID                RGB(255,131,250)
#define PALEGOLDENROD         RGB(238,232,170)
#define PALEGREEN             RGB(154,255,154)
#define PALETURQUOISE         RGB(187,255,255)
#define PALEVIOLETRED         RGB(255,130,171)
#define PAPAYAWHIP            RGB(255,239,213)
#define PEACHPUFF             RGB(255,218,185)
#define PERU                  RGB(205,133, 63)
#define PINK                  RGB(255,192,203)
#define PLUM                  RGB(255,187,255)
#define POWDERBLUE            RGB(176,224,230)
#define PURPLE                RGB(155, 48,255)
//      RED
#define ROSYBROWN             RGB(255,193,193)
#define ROYALBLUE             RGB( 72,118,255)
#define SADDLEBROWN           RGB(139, 69, 19)
#define SALMON                RGB(255,140,105)
#define SANDYBLUE             RGB(191,239,255)
#define SANDYBROWN            RGB(244,164, 96)
#define SEAGREEN              RGB( 84,255,159)
#define SEASHELL              RGB(255,245,238)
#define SIENNA                RGB(255,130, 71)
#define SKYBLUE               RGB(135,206,255)
#define SLATEBLUE             RGB(131,111,255)
#define SLATEGREY             RGB(198,226,255)
#define SNOW                  RGB(255,250,250)
#define STORMGREY             RGB(211,211,211)
#define SPRINGGREEN           RGB(  0,255,127)
#define STEELBLUE             RGB( 99,184,255)
#define TAN                   RGB(255,165, 79)
#define THISTLE               RGB(238,210,238)
#define TOMATO                RGB(255, 99, 71)
#define TURQUOISE             RGB(  0,245,255)
#define VIOLET                RGB(238,130,238)
#define VIOLETRED             RGB(255, 62,150)
#define WHEAT                 RGB(255,231,186)
//      WHITE
#define WHITESMOKE            RGB(245,245,245)
#define WOODBROWN             RGB(255, 64, 64)
//      YELLOW
#define YELLOWGREEN           RGB(154,205, 50)

/*----------------------------------------------------------------------------*/
/* Helpers                                                                    */

/* Group=External Functions                                                   */

#ifdef _AFXDLL
  #include <AfxWin.h>
#else
  #include <Windows.h>
#endif


#ifdef __cplusplus
  #ifdef __AFXWIN_H__           //Microsoft's MFC
  //operator<<()---------------------------------------------------------------
    #ifdef _DEBUG
    // Group=Diagnostic
    /*Outputs the COLORREF object to the dump context.
      The COLORREF value is a 32-bit value used to specify an RGB color.
      When specifying an explicit RGB color, the COLORREF value has the
      following hexadecimal form: 0x00BBGGRR
      
      Note: uses Microsoft Fundation Library (MFC).

      See also: {html:<A HREF="Res/KColorCt_256_colors_palette.htm">}
      256 Colors Palette{html:</A>}  
      */
    inline CDumpContext& AFXAPI operator<<(CDumpContext& dc, const LPCOLORREF pclrData)
      {
      dc <<  _T("(")
         << (LONG)*pclrData
         << _T("(R:") << GetRValue(*pclrData)
         << _T(",G:") << GetGValue(*pclrData)
         << _T(",B:") << GetBValue(*pclrData)
         << _T("))");
      return dc;
      }
    #endif  //_DEBUG
  #endif  //__AFXWIN_H__
#endif  /*_cplusplus                                                         */

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*_KCOLORCT_H_*/
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         18/07/2001 11:32:49 PMDarko           VSS tags
 *  3    Biblioteka1.2         25/06/2001 11:49:45 PMDarko           comments
 *  2    Biblioteka1.1         08/06/2001 11:49:15 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:55:37 PMDarko
 * $
 *****************************************************************************/
