/*$Workfile: KSerialIo.cpp$: implementation file
  $Revision: 1$ $Date: 2007-03-18 21:55:39$
  $Author: Darko$

  Serial Port I/O
  Copyright: CommonSoft Inc.
  2007-02 Darko Kolakovic
  1997 Blazimir Radovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KSerialIo.h"
#ifndef TRACE
  #include "KTrace.h"
#endif

#ifdef _WIN32
//-----------------------------------------------------------------------------
/*Default constructor
 */
CSerialIo::CSerialIo(void) : m_hPort (INVALID_HANDLE_VALUE)
{
TRACE("CSerialIo::CSerialIo()\n");
}
#endif
#ifdef KSIOUNIX
//-----------------------------------------------------------------------------
/*Default constructor
 */
CSerialIo::CSerialIo(void) : m_hPort (-1)
{
TRACE("CSerialIo::CSerialIo()\n");
}
#endif

//-----------------------------------------------------------------------------
/*
 */
CSerialIo::~CSerialIo(void)
{
TRACE("CSerialIo::~CSerialIo()\n");
}

//-----------------------------------------------------------------------------
/*Opens the serial communication device.

  Returns: If the function succeeds, the return value is zero(ERROR_SUCCESS).
  If the function fails, the return value is error information.
 */
#ifdef _WIN32
unsigned int CSerialIo::Open(LPCTSTR szDeviceName //[in] null-terminated string
                        //that specifies the name of the serial port to be open
                            )
{
TRACE1(_T("CSerialIo::Open(%s)\n"), szDeviceName);

ASSERT(szDeviceName != NULL);
ASSERT(_tcslen(szDeviceName) < 16);
if (szDeviceName==NULL)
  return ERROR_INVALID_PARAMETER;

if ((0 != _tcsnicmp(TEXT("COM"), szDeviceName, 3)) || _tcslen(szDeviceName)>16)
  return ERROR_INVALID_PARAMETER;

if (IsOpen())
  return ERROR_ALREADY_EXISTS;

// Create the overlapped event structures.
// No security, explicit reset request, initial event reset, no name.
ASSERT(m_olRead.hEvent==NULL);
m_olRead.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
if (m_olRead.hEvent == NULL)
  return ::GetLastError();

ASSERT(m_olWrite.hEvent==NULL);
m_olWrite.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
if (m_olWrite.hEvent == NULL)
  {
  ::CloseHandle(m_olRead.hEvent);
  m_olRead.hEvent = NULL;
  return ::GetLastError();
  }

ASSERT(m_olWait.hEvent==NULL);
m_olWait.hEvent  = ::CreateEvent(NULL, TRUE, FALSE, NULL);
if (m_olWait.hEvent == NULL)
  {
  ::CloseHandle(m_olRead.hEvent);
  m_olRead.hEvent = NULL;
  ::CloseHandle(m_olWrite.hEvent);
  m_olWrite.hEvent = NULL;
  return ::GetLastError();
  }

// Open the port. The device must exist and must be opened for
// exclusive access (no sharing). No security is used, overlapped
// I/O is enabled.
TCHAR szBuffer[32];
::wsprintf(szBuffer, TEXT("\\\\.\\%s"), szDeviceName);
m_hPort = ::CreateFile(
           szBuffer,
           GENERIC_READ|GENERIC_WRITE,
           0,
           NULL,
           OPEN_EXISTING,
           FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_OVERLAPPED,
           NULL
           );
if (m_hPort == INVALID_HANDLE_VALUE)
  {
  ::CloseHandle(m_olRead.hEvent);
  m_olRead.hEvent = NULL;
  ::CloseHandle(m_olWrite.hEvent);
  m_olWrite.hEvent = NULL;
  ::CloseHandle(m_olWait.hEvent);
  m_olWait.hEvent = NULL;
  return ::GetLastError();
  }

return ERROR_SUCCESS;
}
#endif

#ifdef KSIOUNIX
  #include <termios.h> //POSIX terminal IO
  #include <fcntl.h>   //File control
/*
  QNX1 device "//1/dev/ser1"
  Linux       "/dev/ttyd"
 */
unsigned int CSerialIo::Open(LPCTSTR szDeviceName //[in]
                            )
{
TRACE1("CSerialIo::Open(%s)\n", szDeviceName);
ASSERT(szDeviceName != NULL);
nStatus = FAILURE; //-1
m_hPort = ::open(szDeviceName, O_RDWR | O_NOCTTY | O_NDELAY);

if (IsOpen())
  {
  struct termios sConfig; //Ioctl control packet
  //Get current settings
  if (tcgetattr(m_hPort , &sConfig) == 0)
    {
    sConfig.c_cflag |= (CLOCAL | CREAD);
    sConfig.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    //Set the port configuration
    if (tcsetattr(m_hPort , TCSANOW, &sConfig) == 0)
      {
      fcntl(fd, F_SETFL, 0);
      nStatus = OK; //1
      }
    }
  }
return nStatus;
}
#endif

//-----------------------------------------------------------------------------
/*Closes the serial communication device.

  Returns: If the function succeeds, the return value is zero(ERROR_SUCCESS).
  If the function fails, the return value is error information.
 */
#ifdef _WIN32
unsigned int CSerialIo::Close()
{
TRACE("CSerialIo::Close()\n");
if (!IsOpen())
  return ERROR_SUCCESS;

//Stop any running comm thread
StopCommThread(INFINITE);

//Purge any outstanding reads/writes
::PurgeComm(m_hPort,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);

// Dispose of the overlapped I/O structures and close the port
DWORD dwError = ERROR_SUCCESS;
if (m_olRead.hEvent != NULL)
  {
  if (::CloseHandle(m_olRead.hEvent))
     m_olRead.hEvent = NULL;
  else
     dwError = ::GetLastError();
  }

if (m_olWrite.hEvent != NULL)
  {
  if (::CloseHandle(m_olWrite.hEvent))
     m_olWrite.hEvent = NULL;
  else
     dwError = ::GetLastError();
  }

if (m_olWait.hEvent != NULL)
  {
  if (::CloseHandle(m_olWait.hEvent))
     m_olWait.hEvent = NULL;
  else
     dwError = ::GetLastError();
  }

if (::CloseHandle(m_hPort))
  m_hPort = INVALID_HANDLE_VALUE;
else
  dwError = ::GetLastError();
return dwError;
}
#endif

#ifdef KSIOUNIX
unsigned int CSerialIo::Close()
{
TRACE("CSerialIo::Close()\n");
if (IsOpen())
  return ::close(m_hPort);
return OK;
}
#endif

//-----------------------------------------------------------------------------
/*
 */
#ifdef _WIN32
unsigned int CSerialIo::Write(uint8_t* pData, //[in]
                              const unsigned int nLenght  //[in]
                              )
{
TRACE1("CSerialIo::Write(%d bytes)\n", nLenght);
}
#endif

#ifdef KSIOUNIX
unsigned int CSerialIo::Write(uint8_t* pData, //[in]
                              const unsigned int nLenght  //[in]
                              )
{
TRACE1("CSerialIo::Write(%d bytes)\n", nLenght);
ASSERT(IsOpen));
return ::write(m_hPort, pData, nLenght);
}
#endif

//-----------------------------------------------------------------------------
/*
 */
#ifdef _WIN32
uint8_t* CSerialIo::Read(const unsigned int nLenght  //[in]
                             )
{
TRACE1("CSerialIo::Read(%d bytes)\n", nLenght);
}
#endif
#ifdef KSIOUNIX
//Read and free data allocated with malloc
uint8_t* CSerialIo::Read(const unsigned int nLenght  //[in]
                        )
{
TRACE1("CSerialIo::Read(%d bytes)\n", nLenght);
ASSERT(IsOpen));
uint8_t* pData =  (uint8_t*) malloc(nLenght);
int iCount = ::read(m_hPort, pData, nLenght);
if (nLenght != (unsigned int)iCount)
  {
  status = READ_MORE;
  }
return buffer;
}
#endif

//-----------------------------------------------------------------------------
/*
 */
#ifdef _WIN32
uint8_t CSerialIo::Read()
{
TRACE1("CSerialIo::Read(1 byte)\n");
}
#endif
#ifdef KSIOUNIX

uint8_t CSerialIo::Read()
{
TRACE1("CSerialIo::Read(1 byte)\n");
ASSERT(IsOpen));
char cResult;

int iCount = read(m_hPort, &cResult, sizeof(cResult));
if (iCount == sizeof(character))
  {
  return uint8_t(cResult);
  }
return 0;
}
#endif

//-----------------------------------------------------------------------------
/*
 */
#ifdef KSIOUNIX
#include <sys/ioctl.h>

int CSerialIo::HasDataWaiting()
{
ASSERT(IsOpen));
int iCount;

ioctl(m_hPort, FIONREAD, &iCount);
return iCount;
}
#endif

#ifdef _WIN32
///////////////////////////////////////////////////////////////////////////////
// Initialization/configuration functions

//-----------------------------------------------------------------------------
/*
 */
int  CSerialIo::SetStopBits(const usigned int nNoofBits //[in]
                           )
{
}
//-----------------------------------------------------------------------------
/*Change parity, data bits, stop bit settings.

  Returns: If the function succeeds, the return value is zero(ERROR_SUCCESS).
  If the function fails, the return value is error information.
 */
enum Parity CSerialIo::SetParity(const Parity eParity//[in]
                           )
{
  /*
   int nParity   / *=NOPARITY* /,
   int nDataBits / *=Dat8Bits* /,
   int nStopBits / *=ONESTOPBIT* /
*/
DCB   sConfig;

sConfig.DCBlength = sizeof(DCB);
if (!::GetCommState(m_hPort, &sConfig))
  return ::GetLastError();

sConfig.Parity   = (BYTE)((UINT)nParity);
sConfig.ByteSize = (BYTE)((UINT)nDataBits);
sConfig.StopBits = (BYTE)((UINT)nStopBits);
sConfig.fParity  = TRUE;        // Parity errors are reported

// Enable the options
if (!::SetCommState(m_hPort, &sConfig))
  return ::GetLastError();

return ERROR_SUCCESS;
}
//-----------------------------------------------------------------------------
/*Sets the baud rate [bps].

  Returns: If the function succeeds, the return value is zero(ERROR_SUCCESS).
  If the function fails, the return value is error information.
 */
enum BaudRate CSerialIo::SetBaudRate(const BaudRate eBaud //=eBAUD9600 [in]
                                    )
{
DCB   sConfig;

// Always retrieve the current state before modifying it
sConfig.DCBlength = sizeof(DCB);
if (!::GetCommState(m_hPort, &sConfig))
  return ::GetLastError();

sConfig.BaudRate = nBaudRate;
if (!::SetCommState(m_hPort, &sConfig))
  return ::GetLastError();

return ERROR_SUCCESS;
}

//-----------------------------------------------------------------------------
/*
 */
enum DataSize CSerialIo::SetDataSize(const DataSize eSize//[in]
                           )
{
}
//-----------------------------------------------------------------------------
/*
  Returns: If the function succeeds, the return value is zero(ERROR_SUCCESS).
  If the function fails, the return value is error information.
 */
enum FlowControl CSerialIo::SetFlowControl(const FlowControl eFlowCtrl//[in]
                           )
{
/*
   int  nFlowCtrl,  //=PCF_DTRDSR | PCF_RTSCTS
   int  nXOnLimit,  //=100
   int  nXOffLimit, //=100
   char chXOnChar,  //=ASCII_XON
   char chXOffChar  //=ASCII_XOFF
  */
//Setting flow control can get a little involved.  This function takes
//care of all the necessary details based upon the parameters passed.
DCB   sConfig;
BYTE  byOnOff;

sConfig.DCBlength = sizeof(DCB);
if (!::GetCommState(m_hPort, &sConfig))
  return ::GetLastError();

// Set hardware flow control options
byOnOff = (BYTE)((nFlowCtrl & PCF_DTRDSR) != 0);
sConfig.fOutxDsrFlow = byOnOff;
if (byOnOff)
  sConfig.fDtrControl = DTR_CONTROL_HANDSHAKE;
else
  sConfig.fDtrControl = DTR_CONTROL_ENABLE;

byOnOff = (BYTE)((nFlowCtrl & PCF_RTSCTS) != 0);
sConfig.fOutxCtsFlow = byOnOff;
if (byOnOff)
  sConfig.fRtsControl = RTS_CONTROL_HANDSHAKE;
else
  sConfig.fRtsControl = RTS_CONTROL_ENABLE;

//Set software flow control options
byOnOff = (BYTE)((nFlowCtrl & PCF_XONXOFF) != 0);
sConfig.fInX = sConfig.fOutX = byOnOff;

sConfig.XonChar  = chXOnChar;
sConfig.XoffChar = chXOffChar;
sConfig.XonLim   = (WORD)((UINT)nXOnLimit);
sConfig.XoffLim  = (WORD)((UINT)nXOffLimit);

// Miscellaneous
sConfig.fBinary = TRUE;     //Must always be TRUE for NT
sConfig.fNull   = FALSE;    //Keep received null bytes

// Enable the options
if (!::SetCommState(m_hPort, &sConfig))
  return ::GetLastError();

return ERROR_SUCCESS;
}
#endif

#ifdef KSIOUNIX

///////////////////////////////////////////////////////////////////////////////
// Initialization/configuration functions

//-----------------------------------------------------------------------------
/*
 */
StopBits CSerialIo::SetStopBits(const StopBits eNoofBits //[in]
                           )
{
if (IsOpen() && (eBaud != eSTOPBITERR))
  {
  struct termios sConfig;

  //Get current settings
  if (tcgetattr(m_hPort, &sConfig) == 0)
    {
    switch(eNoofBits)
      {
    case eSTOPBIT1:
      m_hPort.c_cflag &= ~CSTOPB;
      break;
    case eSTOPBITS2:
      m_hPort.c_cflag |= CSTOPB;
      break;
    default:
      return eSTOPBITERR;
    }
    if (tcsetattr(m_hPort, TCSANOW, &sConfig) == 0)
      return eNoofBits;
    }

  }
return eSTOPBITERR;
}

//-----------------------------------------------------------------------------
/*
 */
enum Parity CSerialIo::SetParity(const Parity eParity//[in]
                           )
{
if (IsOpen() && (eBaud != ePARITYERR))
  {
  struct termios sConfig;

  //Get current settings
  if (tcgetattr(m_hPort, &sConfig) == 0)
    {
    switch (eParity)
      {
      case PARITY_EVEN:
        m_hPort.c_cflag |= PARENB ;
        m_hPort.c_cflag &= ~PARODD;
        break ;
      case PARITY_ODD:
        m_hPort.c_cflag |= PARENB;
        m_hPort.c_cflag |= PARODD;
        break ;
      case PARITY_NONE:
        m_hPort.c_cflag &= ~PARENB;
        break ;
      default:
        return ePARITYERR;
      }

    if (tcsetattr(m_hPort, TCSANOW, &sConfig) == 0)
      return eParity;
    }

  }
return ePARITYERR;
}
//-----------------------------------------------------------------------------
/*
 */
enum BaudRate CSerialIo::SetBaudRate(const BaudRate eBaud //=eBAUD9600 [in]
                           )
{
if (IsOpen() && (eBaud != eBAUDERR))
  {
  struct termios sConfig;

  //Get current settings
  if (tcgetattr(m_hPort, &sConfig) == 0)
    {
    //Set new sped for the port I/O operations
    if (cfsetispeed(&sConfig, baud) == 0)
      {
      if (cfsetospeed(&sConfig, baud) == 0)
        return eBaud;
      }
    }
  }
return eBAUDERR;
}
//-----------------------------------------------------------------------------
/*
 */
enum DataSize CSerialIo::SetDataSize(const DataSize eSize//[in]
                                    )
{
if ((IsOpen()) && (eBaud != eDATASIZEERR))
  {
  struct termios sConfig;

  //Get current settings
  if (tcgetattr(m_hPort, &sConfig) == 0)
    {
    if(eSize == eDATASIZE8)
      m_hPort.c_iflag &= ~ISTRIP ; //Clear the ISTRIP flag.
    else
      m_hPort.c_iflag |= ISTRIP ;  //Set the ISTRIP flag.
    m_hPort.c_cflag &= ~CSIZE;
    m_hPort.c_cflag |= (int)eSize;

    if (tcsetattr(m_hPort, TCSANOW, &sConfig) == 0)
      return eSize;
    }

  }
return eDATASIZEERR;
}
//-----------------------------------------------------------------------------
/*
 */
enum FlowControl CSerialIo::SetFlowControl(const FlowControl eFlowCtrl//[in]
                           )
{
if ((IsOpen()) && (eBaud != eFLOWCTRLERR))
  {
  struct termios sConfig;

  //Get current settings
  if (tcgetattr(m_hPort, &sConfig) == 0)
    {
    switch(eFlowCtrl)
      {
      case eFLOWCTRLHW:
        m_hPort.c_iflag &= ~ (IXON|IXOFF);
        m_hPort.c_cflag |= CRTSCTS;
        m_hPort.c_cc[VSTART] = _POSIX_VDISABLE;
        m_hPort.c_cc[VSTOP] = _POSIX_VDISABLE;
        break;
      case eFLOWCTRLSW:
        m_hPort.c_iflag |= IXON|IXOFF;
        m_hPort.c_cflag &= ~CRTSCTS;
        m_hPort.c_cc[VSTART] = ASCII_XON;  // 0x11 (021) ^q
        m_hPort.c_cc[VSTOP]  = ASCII_XOFF; // 0x13 (023) ^s
        break;
      case eFLOWCTRLNONE:
        m_hPort.c_iflag &= ~(IXON|IXOFF);
        m_hPort.c_cflag &= ~CRTSCTS;
        break;
      default:
        return eFLOWCTRLERR;
      }
    if (tcsetattr(m_hPort, TCSANOW, &sConfig) == 0)
      return eFlowCtrl;
    }

  }
return eFLOWCTRLERR;
}
#endif
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-03-18 21:55:39  Darko           
 * $
 *****************************************************************************/
