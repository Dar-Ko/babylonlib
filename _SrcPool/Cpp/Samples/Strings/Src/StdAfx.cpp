// StdAfx.cpp : source file that includes just the standard includes
//	stings.pch will be the pre-compiled header
//	StdAfx.obj will contain the pre-compiled type information

#include "StdAfx.h"
#include "KCharCst.h" //ASCII table

///////////////////////////////////////////////////////////////////////////////
// Globals

#ifdef _AFXDLL
   //Name of default text file used to test string functions
  CString     g_strTestFile = "../../Res/TomSawyer.txt";
#else
  #include <string>
  std::string g_strTestFile = "../../Res/TomSawyer.txt";
#endif