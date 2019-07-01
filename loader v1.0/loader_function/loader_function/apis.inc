typedef HMODULE(WINAPI *_LoadLibraryA)(__in LPCSTR lpLibFileName);
typedef HMODULE(WINAPI *_LoadLibraryW)(__in LPCWSTR lpLibFileName);
typedef PROC(WINAPI *_GetProcAddress)(__in HMODULE hModule,
                                      __in LPCSTR lpProcName);
typedef HANDLE(WINAPI *_GetCurrentProcess)(VOID);
typedef BOOL(WINAPI *_CloseHandle)(__in HANDLE hObject);
typedef HANDLE(WINAPI *_OpenProcess)(__in DWORD dwDesiredAccess,
                                     __in BOOL bInheritHandle,
                                     __in DWORD dwProcessId);
typedef int(WINAPI *_lstrlenA)(__in LPCSTR lpString);
typedef int(WINAPI *_lstrlenW)(__in LPCWSTR lpString);
typedef int(WINAPI *_lstrcmpiW)(__in LPCWSTR lpString1, __in LPCWSTR lpString2);
typedef LPVOID(WINAPI *_HeapAlloc)(__in HANDLE hHeap, __in DWORD dwFlags,
                                   __in SIZE_T dwBytes);
typedef LPVOID(WINAPI *_HeapReAlloc)(__inout HANDLE hHeap, __in DWORD dwFlags,
                                     __deref LPVOID lpMem, __in SIZE_T dwBytes);
typedef BOOL(WINAPI *_HeapFree)(__inout HANDLE hHeap, __in DWORD dwFlags,
                                __drv_freesMem(Mem)
                                    __post __notvalid __deref LPVOID lpMem);
typedef HANDLE(WINAPI *_GetProcessHeap)(VOID);
typedef HMODULE(WINAPI *_GetModuleHandleA)(__in LPCSTR lpModuleName);
typedef DWORD(WINAPI *_GetModuleFileNameW)(__in HMODULE hModule,
                                           LPWSTR lpFilename, __in DWORD nSize);
typedef HANDLE(WINAPI *_CreateMutexA)(
    __in LPSECURITY_ATTRIBUTES lpMutexAttributes, __in BOOL bInitialOwner,
    __in LPCSTR lpName);
typedef DWORD(WINAPI *_GetLastError)(VOID);
typedef VOID(WINAPI *_Sleep)(__in DWORD dwMilliseconds);
typedef LPVOID(WINAPI *_VirtualAllocEx)(__in HANDLE hProcess,
                                        __in LPVOID lpAddress,
                                        __in SIZE_T dwSize,
                                        __in DWORD flAllocationType,
                                        __in DWORD flProtect);
typedef BOOL(WINAPI *_VirtualFreeEx)(__in HANDLE hProcess,
                                     __in LPVOID lpAddress, __in SIZE_T dwSize,
                                     __in DWORD dwFreeType);
typedef BOOL(WINAPI *_WriteProcessMemory)(__in HANDLE hProcess,
                                          __in LPVOID lpBaseAddress,
                                          __in_bcount(nSize) LPCVOID lpBuffer,
                                          __in SIZE_T nSize,
                                          SIZE_T *lpNumberOfBytesWritten);
typedef DWORD(WINAPI *_WaitForSingleObject)(__in HANDLE hHandle,
                                            __in DWORD dwMilliseconds);
typedef HANDLE(WINAPI *_CreateToolhelp32Snapshot)(DWORD dwFlags,
                                                  DWORD th32ProcessID);
typedef BOOL(WINAPI *_Process32FirstW)(HANDLE hSnapshot,
                                       LPPROCESSENTRY32W lppe);
typedef BOOL(WINAPI *_Process32NextW)(HANDLE hSnapshot, LPPROCESSENTRY32W lppe);
typedef DWORD(WINAPI *_ExpandEnvironmentStringsW)(__in LPCWSTR lpSrc,
                                                  LPWSTR lpDst,
                                                  __in DWORD nSize);
typedef BOOL(WINAPI *_CreateProcessW)(
    __in LPCWSTR lpApplicationName, __inout LPWSTR lpCommandLine,
    __in LPSECURITY_ATTRIBUTES lpProcessAttributes,
    __in LPSECURITY_ATTRIBUTES lpThreadAttributes, __in BOOL bInheritHandles,
    __in DWORD dwCreationFlags, __in LPVOID lpEnvironment,
    __in LPCWSTR lpCurrentDirectory, __in LPSTARTUPINFOW lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation);
typedef HANDLE(WINAPI *_CreateRemoteThread)(
    __in HANDLE hProcess, __in LPSECURITY_ATTRIBUTES lpThreadAttributes,
    __in SIZE_T dwStackSize, __in LPTHREAD_START_ROUTINE lpStartAddress,
    __in LPVOID lpParameter, __in DWORD dwCreationFlags, LPDWORD lpThreadId);
typedef VOID(WINAPI *_RtlZeroMemory)(IN VOID UNALIGNED *Destination,
                                     IN SIZE_T Length);
typedef VOID(WINAPI *_RtlMoveMemory)(IN VOID UNALIGNED *Destination,
                                     IN CONST VOID UNALIGNED *Source,
                                     IN SIZE_T Length);
typedef NTSTATUS(WINAPI *_RtlCompressBuffer)(
    USHORT CompressionFormatAndEngine, PUCHAR UncompressedBuffer,
    ULONG UncompressedBufferSize, PUCHAR CompressedBuffer,
    ULONG CompressedBufferSize, ULONG UncompressedChunkSize,
    PULONG FinalCompressedSize, PVOID WorkSpace);
typedef NTSTATUS(WINAPI *_RtlGetCompressionWorkSpaceSize)(
    USHORT CompressionFormatAndEngine, PULONG CompressBufferWorkSpaceSize,
    PULONG CompressFragmentWorkSpaceSize);
typedef NTSTATUS(WINAPI *_RtlDecompressBuffer)(USHORT CompressionFormat,
                                               PUCHAR UncompressedBuffer,
                                               ULONG UncompressedBufferSize,
                                               PUCHAR CompressedBuffer,
                                               ULONG CompressedBufferSize,
                                               PULONG FinalUncompressedSize);
typedef BOOL(WINAPI *_OpenProcessToken)(__in HANDLE ProcessHandle,
                                        __in DWORD DesiredAccess,
                                        __deref_out PHANDLE TokenHandle);
typedef BOOL(WINAPI *_LookupPrivilegeValueA)(__in LPCSTR lpSystemName,
                                             __in LPCSTR lpName, PLUID lpLuid);
typedef BOOL(WINAPI *_AdjustTokenPrivileges)(__in HANDLE TokenHandle,
                                             __in BOOL DisableAllPrivileges,
                                             __in PTOKEN_PRIVILEGES NewState,
                                             __in DWORD BufferLength,
                                             PTOKEN_PRIVILEGES PreviousState,
                                             PDWORD ReturnLength);
typedef LSTATUS(APIENTRY *_RegOpenKeyExA)(__in HKEY hKey, __in LPCSTR lpSubKey,
                                          __in DWORD ulOptions,
                                          __in REGSAM samDesired,
                                          PHKEY phkResult);
typedef LSTATUS(APIENTRY *_RegCreateKeyExW)(
    __in HKEY hKey, __in LPCWSTR lpSubKey, __reserved DWORD Reserved,
    __in LPWSTR lpClass, __in DWORD dwOptions, __in REGSAM samDesired,
    __in CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult,
    LPDWORD lpdwDisposition);
typedef LSTATUS(APIENTRY *_RegSetValueExW)(
    __in HKEY hKey, __in LPCWSTR lpValueName, __reserved DWORD Reserved,
    __in DWORD dwType, __in_bcount(cbData) CONST BYTE *lpData,
    __in DWORD cbData);
typedef LSTATUS(APIENTRY *_RegQueryValueExW)(__in HKEY hKey,
                                             __in LPCWSTR lpValueName,
                                             __reserved LPDWORD lpReserved,
                                             LPDWORD lpType, LPBYTE lpData,
                                             __inout LPDWORD lpcbData);
typedef LSTATUS(APIENTRY *_RegCloseKey)(__in HKEY hKey);
typedef int(PASCAL *_WSAStartup)(__in WORD wVersionRequired,
                                 LPWSADATA lpWSAData);
typedef int(PASCAL *_WSACleanup)(void);
typedef u_short(PASCAL *_htons)(__in u_short hostshort);
typedef u_long(PASCAL *_inet_addr)(__in const char *cp);
typedef struct hostent *(PASCAL *_gethostbyname)(__in_z const char *name);
typedef SOCKET(PASCAL *_socket)(__in int af, __in int type, __in int protocol);
typedef int(PASCAL *_closesocket)(IN SOCKET s);
typedef int(PASCAL *_connect)(__in SOCKET s,
                              __in_bcount(namelen) const struct sockaddr *name,
                              __in int namelen);
typedef int(PASCAL *_setsockopt)(__in SOCKET s, __in int level,
                                 __in int optname,
                                 __in_bcount(optlen) const char *optval,
                                 __in int optlen);
typedef int(PASCAL *_send)(__in SOCKET s, __in_bcount(len) const char *buf,
                           __in int len, __in int flags);
typedef int(PASCAL *_recv)(__in SOCKET s, char *buf, __in int len,
                           __in int flags);
typedef int(PASCAL *_select)(__in int nfds, __inout fd_set *readfds,
                             __inout fd_set *writefds,
                             __inout fd_set *exceptfds,
                             __in const struct timeval *timeout);
typedef LPWSTR(WINAPI *_lstrcpyW)(LPWSTR lpString1, LPCWSTR lpString2);
typedef LPSTR(WINAPI *_lstrcpyA)(LPSTR lpString1, LPCSTR lpString2);
typedef int(WINAPI *_MessageBoxA)(__in_opt HWND hWnd, __in_opt LPCSTR lpText,
                                  __in_opt LPCSTR lpCaption, __in UINT uType);
typedef int(WINAPI *_WideCharToMultiByte)(
    __in UINT CodePage, __in DWORD dwFlags,
    __in_ecount(cchWideChar) LPCWSTR lpWideCharStr, __in int cchWideChar,
    __out_bcount_opt(cbMultiByte) __transfer(lpWideCharStr)
        LPSTR lpMultiByteStr,
    __in int cbMultiByte, __in_opt LPCSTR lpDefaultChar,
    __out_opt LPBOOL lpUsedDefaultChar);
typedef DWORD(WINAPI *_GetTickCount)(VOID);

typedef int(PASCAL *_gethostname)(__out_bcount_part(namelen,
                                                    return ) char FAR *name,
                                  __in int namelen);
typedef char *(PASCAL *_inet_ntoa)(__in struct in_addr in);
typedef UINT(WINAPI *_GetSystemDirectoryA)(
    __out_ecount_part_opt(uSize, return +1) LPSTR lpBuffer, __in UINT uSize);
typedef UINT(WINAPI *_GetSystemDirectoryW)(
    __out_ecount_part_opt(uSize, return +1) LPWSTR lpBuffer, __in UINT uSize);
typedef DWORD(APIENTRY *_GetFileVersionInfoSizeA)(
    __in LPCSTR lptstrFilename,  /* Filename of version stamped file */
    __out_opt LPDWORD lpdwHandle /* Information for use by GetFileVersionInfo */
);
typedef BOOL(APIENTRY *_GetFileVersionInfoA)(
    __in LPCSTR lptstrFilename,       /* Filename of version stamped file */
    __reserved DWORD dwHandle,        /* Information from GetFileVersionSize */
    __in DWORD dwLen,                 /* Length of buffer for info */
    __out_bcount(dwLen) LPVOID lpData /* Buffer to place the data structure */
);
typedef BOOL(APIENTRY *_VerQueryValueA)(__in LPCVOID pBlock,
                                        __in LPCSTR lpSubBlock,
                                        LPVOID *lplpBuffer, __out PUINT puLen);
typedef int(__cdecl *_wnsprintfA)(__out_ecount(cchDest) LPSTR pszDest,
                                  __in int cchDest,
                                  __in __format_string LPCSTR pszFmt, ...);
typedef BOOL(WINAPI *_GetComputerNameW)(__out_ecount_part_opt(*nSize,
                                                              *nSize + 1)
                                            LPWSTR lpBuffer,
                                        __inout LPDWORD nSize);
typedef BOOL(WINAPI *_GetUserNameW)(__out_ecount_part_opt(*pcbBuffer,
                                                          *pcbBuffer)
                                        LPWSTR lpBuffer,
                                    __inout LPDWORD pcbBuffer);
typedef BOOL(WINAPI *_GlobalMemoryStatusEx)(__out LPMEMORYSTATUSEX lpBuffer);
typedef int(WINAPI *_GetLocaleInfoA)(__in LCID     Locale,
									 __in LCTYPE   LCType,
									 __out_ecount_opt(cchData) LPSTR  lpLCData,
									 __in int      cchData);
typedef int(WINAPI *_GetLocaleInfoW)(__in LCID Locale, __in LCTYPE LCType,
                                     __out_ecount_opt(cchData) LPWSTR lpLCData,
                                     __in int cchData);
typedef LPSTR(WINAPI *_lstrcatA)(__inout LPSTR lpString1,
								__in    LPCSTR lpString2
								);
typedef LPSTR(WINAPI *_lstrcatW)(__inout LPWSTR lpString1,
								__in    LPCWSTR lpString2
								);
typedef LSTATUS(APIENTRY *_RegQueryValueExA)(__in HKEY hKey,
											 __in_opt LPCSTR lpValueName,
											 __reserved LPDWORD lpReserved,
											 __out_opt LPDWORD lpType,
											 __out_bcount_part_opt(*lpcbData, *lpcbData) __out_data_source(REGISTRY) LPBYTE lpData,
											 __inout_opt LPDWORD lpcbData
											 );
typedef BOOL(WINAPI *_CreatePipe)(__out_ecount_full(1) PHANDLE hReadPipe,
								  __out_ecount_full(1) PHANDLE hWritePipe,
								  __in_opt LPSECURITY_ATTRIBUTES lpPipeAttributes,
								  __in     DWORD nSize
								  );
typedef BOOL(WINAPI *_GetExitCodeProcess)(__in  HANDLE hProcess, __out LPDWORD lpExitCode);
typedef BOOL(WINAPI *_PeekNamedPipe)(__in      HANDLE hNamedPipe,
									 __out_bcount_part_opt(nBufferSize, *lpBytesRead) LPVOID lpBuffer,
									 __in      DWORD nBufferSize,
									 __out_opt LPDWORD lpBytesRead,
									 __out_opt LPDWORD lpTotalBytesAvail,
									 __out_opt LPDWORD lpBytesLeftThisMessage
									 );
typedef BOOL(WINAPI *_ReadFile)(
    __in        HANDLE hFile,
    __out_bcount_part_opt(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID lpBuffer,
    __in        DWORD nNumberOfBytesToRead,
    __out_opt   LPDWORD lpNumberOfBytesRead,
    __inout_opt LPOVERLAPPED lpOverlapped
    );
typedef BOOL (WINAPI *_WriteFile)(
    __in        HANDLE hFile,
    __in_bcount_opt(nNumberOfBytesToWrite) LPCVOID lpBuffer,
    __in        DWORD nNumberOfBytesToWrite,
    __out_opt   LPDWORD lpNumberOfBytesWritten,
    __inout_opt LPOVERLAPPED lpOverlapped
    );
typedef BOOL(WINAPI *_TerminateProcess)(
    __in HANDLE hProcess,
    __in UINT uExitCode
    );
typedef HBITMAP(WINAPI *_CreateCompatibleBitmap)( __in HDC hdc, __in int cx, __in int cy);
typedef int(WINAPI *_GetDIBits)( __in HDC hdc, __in HBITMAP hbm, __in UINT start, __in UINT cLines,  __out_opt LPVOID lpvBits, __inout_xcount(sizeof(BITMAPINFOHEADER)) LPBITMAPINFO lpbmi, __in UINT usage);  // SAL actual size of lpbmi is computed from structure elements
typedef BOOL(WINAPI *_DeleteObject)( __in HGDIOBJ ho);
typedef HBITMAP(WINAPI *_CreateDIBSection)(__in_opt HDC hdc, __in CONST BITMAPINFO *lpbmi, __in UINT usage, __deref_opt_out VOID **ppvBits, __in_opt HANDLE hSection, __in DWORD offset);
typedef HDC(WINAPI *_CreateCompatibleDC)( __in_opt HDC hdc);
typedef HGDIOBJ(WINAPI *_SelectObject)(__in HDC hdc, __in HGDIOBJ h);
typedef BOOL(WINAPI *_DeleteDC)( __in HDC hdc);
typedef BOOL(WINAPI *_SetRect)(
    __out LPRECT lprc,
    __in int xLeft,
    __in int yTop,
    __in int xRight,
    __in int yBottom);
typedef DWORD(WINAPI *_GetCurrentThreadId)(
    VOID
    );
typedef BOOL(WINAPI *_GetUserObjectInformationA)(
    __in HANDLE hObj,
    __in int nIndex,
    __out_bcount_opt(nLength) PVOID pvInfo,
    __in DWORD nLength,
    __out_opt LPDWORD lpnLengthNeeded);
typedef int(WINAPI *_lstrcmpiA)(
    __in LPCSTR lpString1,
    __in LPCSTR lpString2
    );
typedef BOOL(WINAPI *_SetThreadDesktop)(
     __in HDESK hDesktop);
typedef BOOL(WINAPI *_CloseDesktop)(
    __in HDESK hDesktop);
typedef int(WINAPI *_GetSystemMetrics)(
    __in int nIndex);
typedef HWND(WINAPI *_GetDesktopWindow)(
    VOID);
typedef HDC(WINAPI *_GetDC)(
    __in_opt HWND hWnd);
typedef int(WINAPI *_ReleaseDC)(
    __in_opt HWND hWnd,
    __in HDC hDC);
typedef BOOL(WINAPI *_SetRectEmpty)(
    __out LPRECT lprc);
typedef BOOL(WINAPI *_BitBlt)( __in HDC hdc, __in int x, __in int y, __in int cx, __in int cy, __in_opt HDC hdcSrc, __in int x1, __in int y1, __in DWORD rop);
typedef BOOL(WINAPI *_GetCursorPos)(
    __out LPPOINT lpPoint);
typedef BOOL(WINAPI *_StretchBlt)(__in HDC hdcDest, __in int xDest, __in int yDest, __in int wDest, __in int hDest, __in_opt HDC hdcSrc, __in int xSrc, __in int ySrc, __in int wSrc, __in int hSrc, __in DWORD rop);
typedef HDESK(WINAPI *_GetThreadDesktop)(
    __in DWORD dwThreadId);
typedef HDESK(WINAPI *_OpenInputDesktop)(
    __in DWORD dwFlags,
    __in BOOL fInherit,
    __in ACCESS_MASK dwDesiredAccess);
typedef UINT(WINAPI *_GetSystemDirectoryA)(
    LPSTR lpBuffer,
    __in UINT uSize
    );
	UINT
typedef (WINAPI *_GetWindowsDirectoryW)(
    LPWSTR lpBuffer,
    __in UINT uSize
    );
typedef BOOL(WINAPI *_CopyFileW)(
    __in LPCWSTR lpExistingFileName,
    __in LPCWSTR lpNewFileName,
    __in BOOL bFailIfExists
    );
typedef BOOL(WINAPI *_DeleteFileW)(
    _In_ LPCWSTR lpFileName
    );