/*$Workfile: KCharCst.h$: header file
  $Revision: 12$ $Date: 2007-05-18 15:47:42$
  $Author: Darko Kolakovic$

  ASCII Control Characters Table
  Copyright: CommonSoft Inc. GPL
  D. Kolakovic 4.6.92
*/
/* Group=Strings                                                             */

#ifndef _KCHARCST_H_
    /*$Workfile: KCharCst.h$ sentry */
  #define _KCHARCST_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef NUL
  #define NUL 0x00  /*NULL character                                          */
#endif

#ifndef __cplusplus /*C compilation                                           */
  #pragma message ("   C compilation " __FILE__ )
  /*See also: {html: <a href="../Html/KASCIICharTable.htm">
    ASCII Character Table</a>}
   */
  #define SOH  0x01 /*start of heading                                       */
  #define STX  0x02 /*start of text                                          */
  #define ETX  0x03 /*end of text                                            */
  #define EOT  0x04 /*end of transmission                                    */
  #define ENQ  0x05 /*enquiry                                                */
  #define ACK  0x06 /*acknowledge                                            */
  #define BEL  0x07 /*alert/bell      \a                                     */
  #define BS   0x08 /*backspace       \b                                     */
  #define HT   0x09 /*horizontal tab  \t                                     */
  #define TAB  0x09 /*horizontal tab  \t                                     */
  #define LF   0x0A /*line feed       \n                                     */
  #define NL   0x0A /*new line        \n                                     */
  #define VT   0x0B /*vertical tab    \v                                     */
  #define FF   0x0C /*form feed       \f                                     */
  #define NP   0x0C /*new page        \f                                     */
  #define CR   0x0D /*carriage return \r                                     */
  #define SO   0x0E /*shift out                                              */
  #define SI   0x0F /*shift in                                               */
  #define DLE  0x10 /*data link escape                                       */
  #define DC1  0x11 /*Device control 1                                       */
  #define XON  0x11 /*handshaking                                            */
  #define DC2  0x12 /*device control 2                                       */
  #define DC3  0x13 /*device control 3                                       */
  #define XOFF 0x13 /*handshaking                                            */
  #define DC4  0x14 /*device control 4                                       */
  #define NAK  0x15 /*negative acknowledge                                   */
  #define SYN  0x16 /*synchronous/ Idle                                      */
  #define ETB  0x17 /*end of transmission block                              */
  #define CAN  0x18 /*cancel                                                 */
  #define EM   0x19 /*end of medium                                          */
  #define SUB  0x1A /*substitute                                             */
  #define ESC  0x1B /*escape                                                 */
  #define FS   0x1C /*file separator                                         */
  #define GS   0x1D /*group separator                                        */
  #define RS   0x1E /*record separator                                       */
  #define US   0x1F /*unit separator                                         */
  #define DEL  0x7F /*delete                                                 */

  /*Box Drawing Characters.CP437 IBM PC Code Page

        BOXD-R-   BOXH- BOXD-H-  BOXD-L-
                +---------+-----+
          BOXV- �  BOXV-H-�     |BOXV-
        BOXV-R- +---------+-----+BOXV-L-
                +---------+-----+
        BOXU-R-         BOXU-H-  BOXU-L-

    See also: {html: <a href="../Html/KASCIIOem.htm.htm#BoxChar">
      Box Drawing Characters Table</a>
   */
  #define BOXVS    0xB3 /*Vertical Single, B3, U+2502, Box Drawings Light Vertical*/
  #define BOXVSLS  0xB4 /*Single Vertical And Left, B4, U+2524, Box Drawings Light Vertical And Left*/
  #define BOXVSLD  0xB5 /*Vertical Single And Left Double, B5, U+2561, Box Drawings Vertical Single And Left Double*/
  #define BOXVDLS  0xB6 /*Vertical Double And Left Single, B6, U+2562, Box Drawings Vertical Double And Left Single*/
  #define BOXDDLS  0xB7 /*Down Double And Left Single, B7, U+2556, Box Drawings Down Double And Left Single*/
  #define BOXDSLD  0xB8 /*Down Single And Left Double, B8, 184, U+2555, Box Drawings Down Single And Left Double*/
  #define BOXVDLD  0xB9 /*Double Vertical And Left, B9, U+2563, Box Drawings Double Vertical And Left*/
  #define BOXVD    0xBA /*Double Vertical, BA, U+2551, Box Drawings Double Vertical*/
  #define BOXDDLD  0xBB /*Double Down And Left, BB, U+2557, Box Drawings Double Down And Left*/
  #define BOXUDLD  0xBC /*Double Up And Left, BC, U+255D, Box Drawings Double Up And Left*/
  #define BOXUDLS  0xBD /*Up Double And Left Single, BD, U+255C, Box Drawings Up Double And Left Single*/
  #define BOXUSLD  0xBE /*Up Single And Left Double, BE, U+255B, Box Drawings Up Single And Left Double*/
  #define BOXDSLS  0xBF /*Single Down And Left, BF, U+2510, Box Drawings Light Down And Left*/
  #define BOXUSRS  0xC0 /*Single Up And Right, 192, C0, U+2514, Box Drawings Light Up And Right*/
  #define BOXUSHS  0xC1 /*Single Up And Horizontal, C1, U+2534, Box Drawings Light Up And Horizontal*/
  #define BOXDSHS  0xC2 /*Singlet Down And Horizontal, C2, U+252C, Box Drawings Light Down And Horizontal*/
  #define BOXVSRS  0xC3 /*Single Vertical And Right, C3, U+251C, Box Drawings Light Vertical And Right*/
  #define BOXHS    0xC4 /*Single Horizontal, C4, U+2500, Box Drawings Light Horizontal*/
  #define BOXVSHS  0xC5 /*Single Vertical And Horizontal, C5, U+253C, Box Drawings Light Vertical And Horizontal*/
  #define BOXVSRD  0xC6 /*Vertical Single And Right Double, C6, U+255E, Box Drawings Vertical Single And Right Double*/
  #define BOXVDRS  0xC7 /*Vertical Double And Right Single, C7, U+255F, Box Drawings Vertical Double And Right Single*/
  #define BOXUDRD  0xC8 /*Double Up And Right, 200, C8, U+255A, Box Drawings Double Up And Right*/
  #define BOXDDRD  0xC9 /*Double Down And Right, C9, U+2554, Box Drawings Double Down And Right*/
  #define BOXUDHD  0xCA /*Double Up And Horizontal, CA, U+2569, Box Drawings Double Up And Horizontal*/
  #define BOXDDHD  0xCB /*Double Down And Horizontal, CB, U+2566, Box Drawings Double Down And Horizontal*/
  #define BOXVDRD  0xCC /*Double Vertical And Right, CC, U+2560, Box Drawings Double Vertical And Right*/
  #define BOXHD    0xCD /*Double Horizontal, CD, U+2550, Box Drawings Double Horizontal*/
  #define BOXVDHD  0xCE /*Double Vertical And Horizontal, CE, U+256C, Box Drawings Double Vertical And Horizontal*/
  #define BOXUSHD  0xCF /*Up Single And Horizontal Double, CF, U+2567, Box Drawings Up Single And Horizontal Double*/
  #define BOXUDHS  0xD0 /*Up Double And Horizontal Single, 208, D0, U+2568, Box Drawings Up Double And Horizontal Single*/
  #define BOXDSHD  0xD1 /*Down Single And Horizontal Double, D1, U+2564, Box Drawings Down Single And Horizontal Double*/
  #define BOXDDHS  0xD2 /*Down Double And Horizontal Single, D2, U+2565, Box Drawings Down Double And Horizontal Single*/
  #define BOXUDRS  0xD3 /*Up Double And Right Single, D3, U+2559, Box Drawings Up Double And Right Single*/
  #define BOXUSRD  0xD4 /*Up Single And Right Double, D4, U+2558, Box Drawings Up Single And Right Double*/
  #define BOXDSRD  0xD5 /*Down Single And Right Double, D5, U+2552, Box Drawings Down Single And Right Double*/
  #define BOXDDRS  0xD6 /*Down Double And Right Single, D6, U+2553, Box Drawings Down Double And Right Single*/
  #define BOXVDHS  0xD7 /*Vertical Double And Horizontal Single, D7, U+256B, Box Drawings Vertical Double And Horizontal Single*/
  #define BOXVSHD  0xD8 /*Vertical Single And Horizontal Double, 216, D8, U+256A, Box Drawings Vertical Single And Horizontal Double*/
  #define BOXUSLS  0xD9 /*Single Up And Left, D9, U+2518, Box Drawings Light Up And Left*/
  #define BOXDSRS  0xDA /*Single Down And Right, DA, U+250C, Box Drawings Light Down And Right*/

  /*See also: {html: <a href="../Html/KASCIICharTable.htm#End-of-line_Characters">
    ASCII Character Table</a>}
   */
  #define EOLMAC  CR /*end of line in MacOS                                  */
  #define EOLUNIX LF /*end of line in Unix, Linux, QNX                       */
  #define EOLDOS  "\r\n" /*CR LF pair is end of line in DOS, MS Windows      */
  #define EOLWIN EOLDOS  /*CR LF pair is end of line in DOS, MS Windows      */

  #ifdef _WIN32
    #define EOL LF; /*end of line (previous character is CR)                 */
  #endif
  #ifdef WIN16
    #define EOL LF; /*end of line (previous character is CR)                 */
  #endif
  #ifdef _MSDOS
    #define EOL LF; /*end of line (previous character is CR)                 */
  #endif
  #ifdef _MAC
    #define EOL EOLMAC /*end of line (MacOS)                                 */
  #endif

  #ifndef NULL
    #define NULL 0 /*zero pointer                                             */
  #endif

#else /*_cplusplus  C++ compilation                                           */
  #pragma message ("   C++ compilation " __FILE__ )
  /*See also: {html: <a href="../Html/KASCIICharTable.htm">
    ASCII Character Table</a>}
   */
  const int SOH  = 0x01; //start of heading
  const int STX  = 0x02; //start of text
  const int ETX  = 0x03; //end of text
  const int EOT  = 0x04; //end of transmission
  const int ENQ  = 0x05; //enquiry
  const int ACK  = 0x06; //acknowledge
  const int BEL  = 0x07; //alert/bell      \a
  const int BS   = 0x08; //backspace       \b
  const int HT   = 0x09; //horizontal tab  \t
  const int TAB  = 0x09; //horizontal tab  \t
  const int LF   = 0x0A; //line feed       \n
  const int NL   = 0x0A; //new line        \n
  const int VT   = 0x0B; //vertical tab    \v
  const int FF   = 0x0C; //form feed       \f
  const int NP   = 0x0C; //new page        \f
  const int CR   = 0x0D; //carriage return \r
  const int SO   = 0x0E; //shift out
  const int SI   = 0x0F; //shift in
  const int DLE  = 0x10; //data link escape
  const int DC1  = 0x11; //Device control 1
  const int XON  = 0x11; //handshaking
  const int DC2  = 0x12; //device control 2
  const int DC3  = 0x13; //device control 3
  const int XOFF = 0x13; //handshaking
  const int DC4  = 0x14; //device control 4
  const int NAK  = 0x15; //negative acknowledge
  const int SYN  = 0x16; //synchronous/ Idle
  const int ETB  = 0x17; //end of transmission block
  const int CAN  = 0x18; //cancel
  const int EM   = 0x19; //end of medium
  const int SUB  = 0x1A; //substitute
  const int ESC  = 0x1B; //escape
  const int FS   = 0x1C; //file separator
  const int GS   = 0x1D; //group separator
  const int RS   = 0x1E; //record separator
  const int US   = 0x1F; //unit separator
  const int DEL  = 0x7F; //delete

  /*Box Drawing Characters.CP437 IBM PC Code Page

    See also: {html: <a href="../Html/KASCIIOem.htm.htm#BoxChar">
      Box Drawing Characters Table</a>
   */

  const int BOXVS   = 0xB3; //Vertical Single, B3, U+2502, Box Drawings Light Vertical
  const int BOXVSLS = 0xB4; //Single Vertical And Left, B4, U+2524, Box Drawings Light Vertical And Left
  const int BOXVSLD = 0xB5; //Vertical Single And Left Double, B5, U+2561, Box Drawings Vertical Single And Left Double
  const int BOXVDLS = 0xB6; //Vertical Double And Left Single, B6, U+2562, Box Drawings Vertical Double And Left Single
  const int BOXDDLS = 0xB7; //Down Double And Left Single, B7, U+2556, Box Drawings Down Double And Left Single
  const int BOXDSLD = 0xB8; //Down Single And Left Double, B8, 184, U+2555, Box Drawings Down Single And Left Double
  const int BOXVDLD = 0xB9; //Double Vertical And Left, B9, U+2563, Box Drawings Double Vertical And Left
  const int BOXVD   = 0xBA; //Double Vertical, BA, U+2551, Box Drawings Double Vertical
  const int BOXDDLD = 0xBB; //Double Down And Left, BB, U+2557, Box Drawings Double Down And Left
  const int BOXUDLD = 0xBC; //Double Up And Left, BC, U+255D, Box Drawings Double Up And Left
  const int BOXUDLS = 0xBD; //Up Double And Left Single, BD, U+255C, Box Drawings Up Double And Left Single
  const int BOXUSLD = 0xBE; //Up Single And Left Double, BE, U+255B, Box Drawings Up Single And Left Double
  const int BOXDSLS = 0xBF; //Single Down And Left, BF, U+2510, Box Drawings Light Down And Left
  const int BOXUSRS = 0xC0; //Single Up And Right, 192, C0, U+2514, Box Drawings Light Up And Right
  const int BOXUSHS = 0xC1; //Single Up And Horizontal, C1, U+2534, Box Drawings Light Up And Horizontal
  const int BOXDSHS = 0xC2; //Singlet Down And Horizontal, C2, U+252C, Box Drawings Light Down And Horizontal
  const int BOXVSRS = 0xC3; //Single Vertical And Right, C3, U+251C, Box Drawings Light Vertical And Right
  const int BOXHS   = 0xC4; //Single Horizontal, C4, U+2500, Box Drawings Light Horizontal
  const int BOXVSHS = 0xC5; //Single Vertical And Horizontal, C5, U+253C, Box Drawings Light Vertical And Horizontal
  const int BOXVSRD = 0xC6; //Vertical Single And Right Double, C6, U+255E, Box Drawings Vertical Single And Right Double
  const int BOXVDRS = 0xC7; //Vertical Double And Right Single, C7, U+255F, Box Drawings Vertical Double And Right Single
  const int BOXUDRD = 0xC8; //Double Up And Right, 200, C8, U+255A, Box Drawings Double Up And Right
  const int BOXDDRD = 0xC9; //Double Down And Right, C9, U+2554, Box Drawings Double Down And Right
  const int BOXUDHD = 0xCA; //Double Up And Horizontal, CA, U+2569, Box Drawings Double Up And Horizontal
  const int BOXDDHD = 0xCB; //Double Down And Horizontal, CB, U+2566, Box Drawings Double Down And Horizontal
  const int BOXVDRD = 0xCC; //Double Vertical And Right, CC, U+2560, Box Drawings Double Vertical And Right
  const int BOXHD   = 0xCD; //Double Horizontal, CD, U+2550, Box Drawings Double Horizontal
  const int BOXVDHD = 0xCE; //Double Vertical And Horizontal, CE, U+256C, Box Drawings Double Vertical And Horizontal
  const int BOXUSHD = 0xCF; //Up Single And Horizontal Double, CF, U+2567, Box Drawings Up Single And Horizontal Double
  const int BOXUDHS = 0xD0; //Up Double And Horizontal Single, 208, D0, U+2568, Box Drawings Up Double And Horizontal Single
  const int BOXDSHD = 0xD1; //Down Single And Horizontal Double, D1, U+2564, Box Drawings Down Single And Horizontal Double
  const int BOXDDHS = 0xD2; //Down Double And Horizontal Single, D2, U+2565, Box Drawings Down Double And Horizontal Single
  const int BOXUDRS = 0xD3; //Up Double And Right Single, D3, U+2559, Box Drawings Up Double And Right Single
  const int BOXUSRD = 0xD4; //Up Single And Right Double, D4, U+2558, Box Drawings Up Single And Right Double
  const int BOXDSRD = 0xD5; //Down Single And Right Double, D5, U+2552, Box Drawings Down Single And Right Double
  const int BOXDDRS = 0xD6; //Down Double And Right Single, D6, U+2553, Box Drawings Down Double And Right Single
  const int BOXVDHS = 0xD7; //Vertical Double And Horizontal Single, D7, U+256B, Box Drawings Vertical Double And Horizontal Single
  const int BOXVSHD = 0xD8; //Vertical Single And Horizontal Double, 216, D8, U+256A, Box Drawings Vertical Single And Horizontal Double
  const int BOXUSLS = 0xD9; //Single Up And Left, D9, U+2518, Box Drawings Light Up And Left
  const int BOXDSRS = 0xDA; //Single Down And Right, DA, U+250C, Box Drawings Light Down And Right

  /*See also: {html: <a href="../Html/KASCIICharTable.htm#End-of-line_Characters">
    ASCII Character Table</a>}
   */
  const int EOLMAC  = CR;//end of line in MacOS
  const int EOLUNIX = LF;//end of line in Unix, Linux, QNX
  const char* const EOLDOSA = "\r\n"; //CR LF pair is end of line in DOS
  const char* const EOLWINA = "\r\n"; //CR LF pair is end of line in MS Windows
  #ifdef _UNICODE
    #ifndef _WCHAR_T_DEFINED
      typedef unsigned short wchar_t;
      #define wchar_t wchar_t
      #define _WCHAR_T_DEFINED
    #endif
    const wchar_t* const EOLDOSW = L"\r\n"; //CR LF pair is end of line in DOS
    const wchar_t* const EOLWINW = L"\r\n"; //CR LF pair is end of line in MS Windows
    #define EOLDOS EOLDOSW
    #define EOLWIN EOLWINW
  #else
    #define EOLDOS EOLDOSA
    #define EOLWIN EOLWINA
  #endif

  #ifdef _MAC
    const int EOL = EOLMAC; //end of line (MacOS)
  #else
     const int EOL = LF;    //end of line
     //Note: EOL is pair of characters CR, LF; Microsoft Windows
     //specific (Win, DOS).
  #endif

#endif /*!_cplusplus                                                          */


/* ////////////////////////////////////////////////////////////////////////// */
#endif /*_KCHARCST_H_                                                         */
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         02/08/2001 10:07:48 PMDarko
 * $
 *****************************************************************************/
