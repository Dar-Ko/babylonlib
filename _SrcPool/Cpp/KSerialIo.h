/*$Workfile: KSerialIo.h$: header file
  $Revision: 1$ $Date: 2007-03-18 21:55:40$
  $Author: Darko$

  Serial Port I/O
  Copyright: CommonSoft Inc.
  2007-02-02 Darko Kolakovic
  1997 Blazimir Radovic
 */

#ifndef _KSERIALIO_H_
  //$Workfile: KSerialIo.h$ sentry
  #define _KSERIALIO_H_

#ifdef _LINUX
  #define KSIOUNIX 20070201
#endif
#ifdef _UNIX
  #define KSIOUNIX 20070202
#endif

#include "KType32.h" //ISO C99 type definitions
#ifndef LPCTSTR
  #include "KTChar.h"
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef KSIOUNIX
typedef HANDLE int;
#endif
   // Serial I/O definitions
   // The standard serial I/O definitions can be found in WINBASE.H
   // (i.e. CBR_xxxx, PCF_xxx, EV_xxx, CE_xxx, etc).


///////////////////////////////////////////////////////////////////////////////
/*
 */
class CSerialIo
{
public:
  CSerialIo(void);
  virtual ~CSerialIo(void);

  enum BaudRate
    {
    eBAUD50     = 50,
    eBAUD75     = 75,
    eBAUD110    = 110,
    eBAUD134    = 134,
    eBAUD150    = 150,
    eBAUD200    = 200,
    eBAUD300    = 300,
    eBAUD600    = 600,
    eBAUD1200   = 1200,
    eBAUD1800   = 1800,
    eBAUD2400   = 2400,
    eBAUD4800   = 4800,
    eBAUD9600   = 9600, //CBR_9600
    eBAUD19200  = 19200,
    eBAUD38400  = 38400,
    eBAUD57600  = 57600,
    eBAUD115200 = 115200,
    eBAUD153600 = 153600,
    eBAUD230400 = 230400,
    eBAUD307200 = 307200,
    eBAUD460800 = 460800,
    eBAUDERR    = -1
    };

  enum DataSize
    {
    eDATASIZE5 = 5, //data size is 5 bits (pseudo)
    eDATASIZE6 = 6, //data size is 6 bits
    eDATASIZE7 = 7, //data size is 7 bits
    eDATASIZE8 = 8, //data size is 8 bits
    eDATASIZEERR = -1
    };

  enum Parity
    {
    ePARITYEVEN,
    ePARITYODD,
    ePARITYNONE,
    ePARITYERR
    };

  enum StopBits
    {
    eSTOPBIT1,
    eSTOPBITS2,
    eSTOPBITERR = -1
    };

  enum FlowControl
    {
    eFLOWCTRLHW,
    eFLOWCTRLSW,
    eFLOWCTRLNONE,
    eFLOWCTRLERR
    };
//Properties
protected:
  //unsigned int     m_nStatus;
  //unsigned int     m_nStopBits;
  //enum Parity      m_eParity;
  //enum DataSize    m_eDataSize;
  //enum BaudRate    m_eSpeed;
  //enum FlowControl m_eFlow;
  volatile HANDLE m_hPort;

public:
  StopBits SetStopBits(const StopBits eNoofBits);
  enum Parity SetParity(const Parity eParity);
  enum BaudRate SetBaudRate(const BaudRate eBaud = eBAUD9600);
  enum DataSize SetDataSize(const DataSize eSize);
  enum FlowControl SetFlowControl(const FlowControl eFlowCtrl);

//Operations
public:
  //unsigned int GetStatus() const;
  unsigned int Open(LPCTSTR szDeviceName);
  unsigned int Close();
  unsigned int Write(uint8_t* pData, const unsigned int nLenght);
  uint8_t* Read(const unsigned int nLenght);
  uint8_t  Read();
  bool IsOpen() const;
};
///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Return: true if port is open.
 */
#ifdef _WIN32
inline bool CSerialIo::IsOpen() const
{
return (m_hPort != INVALID_HANDLE_VALUE);
}
#endif
#ifdef KSIOUNIX
inline bool CSerialIo::IsOpen() const
{
return (m_hPort != -1);
}
#endif
///////////////////////////////////////////////////////////////////////////////
#endif //_KSERIALIO_H_
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-03-18 21:55:40  Darko           
 * $
 *****************************************************************************/