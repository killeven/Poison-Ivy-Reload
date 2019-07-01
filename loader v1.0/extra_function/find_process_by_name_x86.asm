include '../include/global.inc'
include 'win32a.inc'

use32

FUNCTION_DATA_BEGIN find_process_by_name_x86

proc find_process_by_name_x86 stdcall uses ebx esi edi, global_data: dword, name: dword
	locals
		pe32	PROCESSENTRY32W	?
		pid		_DWORD			?
	endl

	mov esi, [global_data]

	assume esi: global_data_t

	mov [pid], 0
	mov [pe32.dwSize], sizeof.PROCESSENTRY32W

	invoke esi.CreateToolhelp32Snapshot, TH32CS_SNAPALL, 0
	cmp eax, -1
	je .ret

	mov edi, eax

	lea ebx, [pe32]
	invoke esi.Process32FirstW, edi, ebx

	.while eax <> 0
		lea eax, [pe32.szExeFile]
		invoke esi.lstrcmpiW, eax, [name]
		.if eax = 0
			push [pe32.th32ProcessID]
			pop [pid]
			jmp .close_ret
		.endif

		invoke esi.Process32NextW, edi, ebx
	.endw

.close_ret:
	invoke esi.CloseHandle, edi

.ret:
	mov eax, [pid]
	ret
endp

FUNCTION_DATA_END find_process_by_name_x86