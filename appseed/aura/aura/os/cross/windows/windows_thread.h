// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//
// Emulates a subset of the Win32 threading API as a layer on top of WinRT threadpools.
//
// Supported features:
//
//    - CreateThread (returns a standard Win32 handle which can be waited on, then closed)
//    - CREATE_SUSPENDED and ResumeThread
//    - Partial support for SetThreadPriority (see below)
//    - Sleep
//    - Thread local storage (TlsAlloc, TlsFree, thread_get_data, thread_set_data)
//
// Differences from Win32:
//
//    - If using TLS other than from this CreateThread emulation, call TlsShutdown before thread/task exit
//    - No ExitThread or TerminateThread (just return from the thread function to exit)
//    - No SuspendThread, so ResumeThread is only useful in combination with CREATE_SUSPENDED
//    - SetThreadPriority is only available while a thread is in CREATE_SUSPENDED state
//    - SetThreadPriority only supports three priority levels (negative, zero, or positive)
//    - No thread identifier APIs (GetThreadId, GetCurrentThreadId, OpenThread)
//    - No affinity APIs
//    - No GetExitCodeThread
//    - Failure cases return error codes but do not always call SetLastError
#ifndef CA2_APP_AXIS_OS_CROSS_WINDOWS_THREAD_H
#define CA2_APP_AXIS_OS_CROSS_WINDOWS_THREAD_H


#ifndef CREATE_SUSPENDED
#define CREATE_SUSPENDED 0x00000004
#endif



//#if !defined(LINUX) && !defined(SOLARIS)
//typedef struct hthread * HTHREAD;
//#endif

#ifdef WINDOWS

typedef uint32_t IDTHREAD;

#else

typedef pthread_t IDTHREAD;

#endif

#ifndef METROWIN


CLASS_DECL_AURA DWORD WINAPI ResumeThread(HTHREAD hThread);
CLASS_DECL_AURA int_bool WINAPI SetThreadPriority(HTHREAD hThread, int32_t nPriority);
CLASS_DECL_AURA int32_t WINAPI GetThreadPriority(HTHREAD hThread);

CLASS_DECL_AURA VOID WINAPI Sleep(DWORD dwMilliseconds);


#endif




LPVOID WINAPI tls_get_value(DWORD dwIndex);


#if defined(METROWIN) && defined(__cplusplus_winrt)



#elif !defined(WINDOWS)

#define PM_NOREMOVE 0
#define PM_REMOVE 1

#endif


#define TLS_MESSAGE_QUEUE     127




#endif // CA2_APP_AXIS_OS_CROSS_WINDOWS_THREAD_H
