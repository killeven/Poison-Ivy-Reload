macro typedef [statement*] {
	common
		; 匹配基类型以及目标类型
		match gs@base gs@type, statement \{
			; 遍历目标类型
			irp type, gs@type \\{
				; 定义struc, 这里参数支持默认值所以不需要额外进行匹配，否则需要 match any, v与 match , v来进行匹配
				struc type [v=?] \\\{
					\\\common
						.	gs@base	v
				\\\}
				; 定义目标类型macro
				macro type [v=?] \\\{
					\\\common
						gs@base	v
				\\\}		
				; 定义size
				virtual at 0
					gs@base	?
					sizeof.\\#type = $
				end virtual
			\\}
		\}
}

typedef db _BYTE, _CHAR, _UCHAR, _BOOL
typedef dw _WORD, _SHORT, _USHORT, _WCHAR
typedef dd _LONG, _ULONG, _DWORD, _HANDLE, _HKEY, _SOCKET, _ULONG_PTR
typedef dq _LONGLONG, _ULONGLONG

struct LUID
	LowPart    _DWORD	?
	HighPart	_LONG	?
ends

struct LUID_AND_ATTRIBUTES
	Luid		LUID		?
	Attributes	_DWORD	?
ends

struct TOKEN_PRIVILEGES
	PrivilegeCount	_DWORD	?
	Privileges		LUID_AND_ATTRIBUTES	?
ends

struct IMAGE_DOS_HEADER
	e_magic		_WORD	?
	e_cblp		_WORD	?
	e_cp			_WORD	?
	e_crlc		_WORD	?
	e_cparhdr		_WORD	?
	e_minalloc	_WORD	?
	e_maxalloc	_WORD	?
	e_ss			_WORD	?
	e_sp			_WORD	?
	e_csum		_WORD	?
	e_ip			_WORD	?
	e_cs			_WORD	?
	e_lfarlc		_WORD	?
	e_ovno		_WORD	?
	e_res		_WORD	4	dup(?)
	e_oemid		_WORD	?
	e_oeminfo		_WORD	?
	e_res2		_WORD	10	dup(?)
	e_lfanew		_LONG	?
ends

struct IMAGE_FILE_HEADER
	Machine                 _WORD    		?
	NumberOfSections        _WORD    		?
	TimeDateStamp           _DWORD   		?
	PointerToSymbolTable    _DWORD   		?
	NumberOfSymbols         _DWORD   		?
	SizeOfOptionalHeader    _WORD    		?
	Characteristics         _WORD    		?
ends

struct IMAGE_DATA_DIRECTORY
    VirtualAddress		_DWORD	?
    Size		_DWORD	?
ends

struct IMAGE_OPTIONAL_HEADER64
	Magic                             _WORD         ?
	MajorLinkerVersion                _BYTE         ?
	MinorLinkerVersion                _BYTE         ?
	SizeOfCode                        _DWORD        ?
	SizeOfInitializedData             _DWORD        ?
	SizeOfUninitializedData           _DWORD        ?
	AddressOfEntryPoint               _DWORD        ?
	BaseOfCode                        _DWORD        ?
	ImageBase                         _ULONGLONG    ?
	SectionAlignment                  _DWORD        ?
	FileAlignment                     _DWORD        ?
	MajorOperatingSystemVersion       _WORD         ?
	MinorOperatingSystemVersion       _WORD         ?
	MajorImageVersion                 _WORD         ?
	MinorImageVersion                 _WORD         ?
	MajorSubsystemVersion             _WORD         ?
	MinorSubsystemVersion             _WORD         ?
	Win32VersionValue                 _DWORD        ?
	SizeOfImage                       _DWORD        ?
	SizeOfHeaders                     _DWORD        ?
	CheckSum                          _DWORD        ?
	Subsystem                         _WORD         ?
	DllCharacteristics                _WORD         ?
	SizeOfStackReserve                _ULONGLONG    ?
	SizeOfStackCommit                 _ULONGLONG    ?
	SizeOfHeapReserve                 _ULONGLONG    ?
	SizeOfHeapCommit                  _ULONGLONG    ?
	LoaderFlags                       _DWORD        ?
	NumberOfRvaAndSizes               _DWORD        ?
	IMAGE_DIRECTORY_ENTRY_EXPORT         IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_IMPORT         IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_RESOURCE       IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_EXCEPTION      IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_SECURITY       IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_BASERELOC      IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_DEBUG          IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_COPYRIGHT      IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_ARCHITECTURE   IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_GLOBALPTR      IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_TLS            IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_IAT            IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   IMAGE_DATA_DIRECTORY	?
	IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR IMAGE_DATA_DIRECTORY	?
ends

struct IMAGE_NT_HEADERS64
	Signature	_DWORD	?
	FileHeader	IMAGE_FILE_HEADER	?
	OptionalHeader	IMAGE_OPTIONAL_HEADER64	?
ends

struct IMAGE_EXPORT_DIRECTORY
	Characteristics           _DWORD       ?
	TimeDateStamp             _DWORD       ?
	MajorVersion              _WORD        ?
	MinorVersion              _WORD        ?
	Name                      _DWORD       ?
	Base                      _DWORD       ?
	NumberOfFunctions         _DWORD       ?
	NumberOfNames             _DWORD       ?
	AddressOfFunctions        _DWORD       ?
	AddressOfNames            _DWORD       ?
	AddressOfNameOrdinals     _DWORD       ?
ends

struct PROCESSENTRY32W
    dwSize              _DWORD  ?
    cntUsage            _DWORD  ?
    th32ProcessID       _DWORD  ?
    th32DefaultHeapID   _ULONG_PTR  ?
    th32ModuleID        _DWORD  ?
    cntThreads          _DWORD  ?
    th32ParentProcessID _DWORD  ?
    pcPriClassBase      _LONG   ?
    dwFlags             _DWORD  ?
    szExeFile           _WCHAR      260 dup(?)
ends

struct FD_SET
    fd_count    _DWORD  ?
    fd_array    _SOCKET  64 dup(?) 
ends

struct TIMEVAL
    tv_sec  _LONG   ?
    tv_usec _LONG   ?
ends

TOKEN_ADJUST_PRIVILEGES = 0x0020
TOKEN_QUERY = 0x0008
SE_PRIVILEGE_ENABLED = 0x00000002

true = 1
false = 0

SOCKET_ERROR = -1
INADDR_NONE = 0xffffffff

SOL_SOCKET = 0xffff
SO_RCVBUF = 0x1002
SO_RCVTIMEO = 0x1006
SO_SNDTIMEO = 0x1005
COMPRESSION_FORMAT_LZNT1 = 0x0002
COMPRESSION_ENGINE_STANDARD = 0x0000
ERROR_ALREADY_EXISTS = 183


TH32CS_SNAPHEAPLIST = 0x00000001
TH32CS_SNAPPROCESS  = 0x00000002
TH32CS_SNAPTHREAD   = 0x00000004
TH32CS_SNAPMODULE   = 0x00000008
TH32CS_SNAPMODULE32 = 0x00000010
TH32CS_SNAPALL      = TH32CS_SNAPHEAPLIST or TH32CS_SNAPPROCESS or TH32CS_SNAPTHREAD or TH32CS_SNAPMODULE
TH32CS_INHERIT      = 0x80000000