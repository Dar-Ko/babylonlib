/*$Workfile: KCharCst.h$: header file
  $Revision: 6$ $Date: 19/08/2002 9:45:01 AM$
  $Author: Darko Kolakovic$

  ASCII Character Table
  CommonSoft Inc.
  D. Kolakovic 4.6.92
*/
/* Group=Strings                                                             */

#ifndef _KCHARCST_H_
    /*KCharCst.h sentry */
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
  /*See also: {HTML: <A HREF ="Res/ASCIICharTable.htm"> ASCII Character Table </A>} */
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

  /*See also: {HTML: <A HREF ="Res/ASCIICharTable.htm#End-of-line_Characters">
    ASCII Character Table </A>}
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
  /*See also: {HTML: <A HREF ="Res/ASCIICharTable.htm"> ASCII Character Table </A>} */
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

  /*See also: {HTML: <A HREF ="Res/ASCIICharTable.htm#End-of-line_Characters">
    ASCII Character Table </A>}
   */
  const int EOLMAC  = CR;//end of line in MacOS
  const int EOLUNIX = LF;//end of line in Unix, Linux, QNX
  const char * const EOLDOS = "\r\n"; //CR LF pair is end of line in DOS, MS Windows
  const char * const EOLWIN = "\r\n"; //CR LF pair is end of line in DOS, MS Windows

  #ifdef _WIN32
    const int EOL = LF; //end of line (previous character is CR)
  #endif
  #ifdef WIN16
    const int EOL = LF; //end of line (previous character is CR)
  #endif
  #ifdef _MSDOS
    const int EOL = LF; //end of line (previous character is CR)
  #endif
  #ifdef _MAC
    const int EOL = EOLMAC; //end of line (MacOS)
  #endif

#endif /*!_cplusplus                                                          */


/* ////////////////////////////////////////////////////////////////////////// */
#endif /*_KCHARCST_H_                                                         */
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         02/08/2001 10:07:48 PMDarko
 * $
 *****************************************************************************/
