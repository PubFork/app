/**
 * WinPR: Windows Portable Runtime
 * Process Environment Functions
 *
 * Copyright 2012 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 * Copyright 2013 Thincast Technologies GmbH
 * Copyright 2013 DI (FH) Martin Haimberger <martin.haimberger@thincast.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WINPR_ENVIRONMENT_H
#define WINPR_ENVIRONMENT_H

#include <winpr/winpr.h>
#include <winpr/wtypes.h>

#ifndef _WIN32

#ifdef __cplusplus
extern "C" {
#endif

WINPR_API DWORD GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer);
WINPR_API DWORD GetCurrentDirectoryW(DWORD nBufferLength, LPWSTR lpBuffer);

WINPR_API WINBOOL SetCurrentDirectoryA(LPCSTR lpPathName);
WINPR_API WINBOOL SetCurrentDirectoryW(LPCWSTR lpPathName);

WINPR_API DWORD SearchPathA(LPCSTR lpPath, LPCSTR lpFileName, LPCSTR lpExtension, DWORD nBufferLength, LPSTR lpBuffer, LPSTR* lpFilePart);
WINPR_API DWORD SearchPathW(LPCWSTR lpPath, LPCWSTR lpFileName, LPCWSTR lpExtension, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR* lpFilePart);

WINPR_API HANDLE GetStdHandle(DWORD nStdHandle);
WINPR_API WINBOOL SetStdHandle(DWORD nStdHandle, HANDLE hHandle);
WINPR_API WINBOOL SetStdHandleEx(DWORD dwStdHandle, HANDLE hNewHandle, HANDLE* phOldHandle);

WINPR_API LPSTR GetCommandLineA(VOID);
WINPR_API LPWSTR GetCommandLineW(VOID);

WINPR_API WINBOOL NeedCurrentDirectoryForExePathA(LPCSTR ExeName);
WINPR_API WINBOOL NeedCurrentDirectoryForExePathW(LPCWSTR ExeName);

WINPR_API DWORD GetEnvironmentVariableA(LPCSTR lpName, LPSTR lpBuffer, DWORD nSize);
WINPR_API DWORD GetEnvironmentVariableW(LPCWSTR lpName, LPWSTR lpBuffer, DWORD nSize);

WINPR_API WINBOOL SetEnvironmentVariableA(LPCSTR lpName, LPCSTR lpValue);
WINPR_API WINBOOL SetEnvironmentVariableW(LPCWSTR lpName, LPCWSTR lpValue);

/**
 * A brief history of the GetEnvironmentStrings functions:
 * http://blogs.msdn.com/b/oldnewthing/archive/2013/01/17/10385718.aspx
 */

WINPR_API char * GetEnvironmentStrings(VOID);
WINPR_API LPWSTR GetEnvironmentStringsW(VOID);

WINPR_API WINBOOL SetEnvironmentStringsA(LPCH NewEnvironment);
WINPR_API WINBOOL SetEnvironmentStringsW(LPWCH NewEnvironment);

WINPR_API DWORD ExpandEnvironmentStringsA(LPCSTR lpSrc, LPSTR lpDst, DWORD nSize);
WINPR_API DWORD ExpandEnvironmentStringsW(LPCWSTR lpSrc, LPWSTR lpDst, DWORD nSize);

WINPR_API WINBOOL FreeEnvironmentStringsA(LPCH lpszEnvironmentBlock);
WINPR_API WINBOOL FreeEnvironmentStringsW(LPWCH lpszEnvironmentBlock);

WINPR_API LPCH MergeEnvironmentStrings(PCSTR original, PCSTR merge);

WINPR_API DWORD GetEnvironmentVariableEBA(LPCSTR envBlock, LPCSTR lpName, LPSTR lpBuffer, DWORD nSize);
WINPR_API WINBOOL SetEnvironmentVariableEBA(LPSTR * envBlock,LPCSTR lpName, LPCSTR lpValue);

#ifdef __cplusplus
}
#endif


#ifdef BYEWINDOWS_UNICODE
#define GetCurrentDirectory		GetCurrentDirectoryW
#define SetCurrentDirectory		SetCurrentDirectoryW
#define SearchPath			SearchPathW
#define GetCommandLine			GetCommandLineW
#define NeedCurrentDirectoryForExePath	NeedCurrentDirectoryForExePathW
#define GetEnvironmentVariable		GetEnvironmentVariableW
#define SetEnvironmentVariable		SetEnvironmentVariableW
#define GetEnvironmentStrings		GetEnvironmentStringsW
#define SetEnvironmentStrings		SetEnvironmentStringsW
#define ExpandEnvironmentStrings	ExpandEnvironmentStringsW
#define FreeEnvironmentStrings		FreeEnvironmentStringsW
#else
#define GetCurrentDirectory		GetCurrentDirectoryA
#define SetCurrentDirectory		SetCurrentDirectoryA
#define SearchPath			SearchPathA
#define GetCommandLine			GetCommandLineA
#define NeedCurrentDirectoryForExePath	NeedCurrentDirectoryForExePathA
#define GetEnvironmentVariable		GetEnvironmentVariableA
#define SetEnvironmentVariable		SetEnvironmentVariableA
x//#define GetEnvironmentStringsA		GetEnvironmentStrings
#define SetEnvironmentStrings		SetEnvironmentStringsA
#define ExpandEnvironmentStrings	ExpandEnvironmentStringsA
#define FreeEnvironmentStrings		FreeEnvironmentStringsA
#endif

#endif

#endif /* WINPR_ENVIRONMENT_H */

