#pragma once
#include "soStandardTools.h"
#include "soPlatformTypes.h"

/************************************************************************************************************************/
/* Funciones de conversión de WIDE a String y de String a WIDE          												*/
/************************************************************************************************************************/
//String
extern std::string ws2s(const std::wstring& _WideString);
extern std::wstring s2ws(const std::string& _String);
//Int
extern std::wstring int2ws(const int32& _int);
extern std::string int2s(const int32& _int);
extern int32 ws2int(const std::wstring& _WideString);
extern int32 s2int(const std::string& _String);
//uint32
extern std::wstring uint2ws(const uint32 &_uint);
extern std::string uint2s(const uint32 &_uint);
extern uint32 ws2uint(const std::wstring& _WideString);
extern uint32 s2uint(const std::string &_String);
//float
extern std::wstring float2ws(const float &_float);
extern std::string float2s(const float &_float);
extern float ws2float(const std::wstring& _WideString);
extern float s2float(const std::string &_String);
//String Utility
extern soString GetFileName(const soString& _FilePath);
extern soString GetFilePath(const soString& _FilePath);
extern bool CheckExtentionFile(const soString& _FilePath, soString _ExtentionFile);