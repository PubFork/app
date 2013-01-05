#pragma once

#include <Winsvc.h>
#include "WinIoCtl.h"

#define IOCTL_LISTDRV_BUFFERED_IO		\
        CTL_CODE(FILE_DEVICE_UNKNOWN,	\
        0x802,							\
        METHOD_BUFFERED,	            \
        FILE_READ_DATA | FILE_WRITE_DATA)

#define VISTA_FILETYPE  25
#define XP_FILETYPE 28

typedef struct _HANDLE_INFO
{	
	USHORT tcDeviceName[260];
	USHORT tcFileName[260];
    ULONG uType;
}HANDLE_INFO;

typedef struct _ADDRESS_INFO
{
	PVOID pAddress;
}ADDRESS_INFO;

typedef LONG NTSTATUS;

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

typedef struct _SYSTEM_HANDLE
{
    uint32_t       dwProcessId;
    BYTE		bObjectType;
    BYTE		bFlags;
    WORD		wValue;
	PVOID       pAddress;
	uint32_t GrantedAccess;
}SYSTEM_HANDLE;

#ifndef METROWIN

typedef struct _SYSTEM_HANDLE_INFORMATION
{
    uint32_t         dwCount;
    SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION, **PPSYSTEM_HANDLE_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemHandleInformation = 0X10,
} SYSTEM_INFORMATION_CLASS;

#endif

typedef NTSTATUS ( WINAPI *PNtQuerySystemInformation)
				 ( IN	SYSTEM_INFORMATION_CLASS SystemInformationClass,
				   OUT	PVOID					 SystemInformation,
				   IN	ULONG					 SystemInformationLength,
				   OUT	PULONG					 ReturnLength OPTIONAL );



// 
// typedef enum OF_FILE_INFO_BY_HANDLE_CLASS
// {
// 	OF_FileNameInfo  = 2,
// 	OF_FileStreamInfo = 7
// };
// 
// struct OF_FILE_NAME_INFO
// {
// 	uint32_t  FileNameLength;
// 	WCHAR FileName[MAX_PATH];
// };
// 
// struct OF_FILE_STREAM_INFO
// {  
// 	uint32_t NextEntryOffset;
// 	uint32_t StreamNameLength;
// 	LARGE_INTEGER StreamSize;
// 	LARGE_INTEGER StreamAllocationSize; 
// 	WCHAR StreamName[MAX_PATH];
// };
// 
// 
// typedef bool (WINAPI *PGetFileInformationByHandleEx)(
// 	HANDLE hFile,
// 	OF_FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
// 	LPVOID lpFileInformation,
// 	uint32_t dwBufferSize);

typedef uint32_t (WINAPI* GetFinalPathNameByHandleDef)(
	HANDLE hFile,
	LPWSTR lpszFilePath,
	uint32_t cchFilePath,
	uint32_t dwFlags	);
	


bool StopAndUninstallDrv( HANDLE hDrvHandle );

HANDLE ExtractAndInstallDrv();

bool GetDrive( LPCTSTR lpDeviceFileName, string & fsFileName, bool bDriveLetterOnly );

bool EnableTokenPrivilege(LPCTSTR pszPrivilege);
