#include "framework.h"


BEGIN_EXTERN_C


CLASS_DECL_AURA
int32_t
MultiByteToWideChar2(
UINT     CodePage,
DWORD    dwFlags,
LPCSTR   lpMultiByteStr,
int32_t      cbMultiByte,
LPWSTR  lpWideCharStr,
int32_t      cchWideChar)
{

   return MultiByteToWideChar(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);

}

CLASS_DECL_AURA
int32_t
WideCharToMultiByte2(
UINT     CodePage,
DWORD    dwFlags,
LPCWSTR  lpWideCharStr,
int32_t      cchWideChar,
LPSTR   lpMultiByteStr,
int32_t      cbMultiByte,
LPCSTR   lpDefaultChar,
LPBOOL  lpUsedDefaultChar)
{


   return WideCharToMultiByte(CodePage, dwFlags, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar);

}



END_EXTERN_C