include '../include/global.inc'

use64

; get_proc_from_hash_x64
; 调用例子
; sub rsp, 0x20
; mov rcx, module_base
; mov edx, hash
; mov r8, GetProcAddress

FUNCTION_DATA_BEGIN get_proc_from_hash_x64
get_proc_from_hash_x64:
	mov rax, rsp
	mov [rax + 0x8], rbx
	mov [rax + 0x10], rbp
	mov [rax + 0x18], rsi
	mov [rax + 0x20], rdi
	push r14
	sub rsp, 0x20
	movsxd rax, dword [rcx + 0x3C]
	mov r9, rcx
	mov rbx, r8
	mov ecx, dword[rax + rcx + 0x88]
	mov ebp, edx
	test ecx, ecx
	jz .error_exit

	cmp dword [rax + r9 + 0x8C], 0x0
	je .error_exit

	lea rax, [r9 + rcx]
	mov r11d, dword [rax + 0x18]
	test r11d, r11d
	jz .error_exit

	mov r8d, dword [rax + 0x20]
	mov edi, dword [rax + 0x1C]
	mov esi, dword [rax + 0x24]
	add r8, r9
	add rdi, r9
	add rsi, r9
	xor edx, edx
	test r11d, r11d
	jz .error_exit

.next:
	mov r10d, dword [r8]
	add r10, r9
	xor ecx, ecx
	mov al, byte [r10]
	mov r14, r10
	jmp .calc_hash_check

.calc_hash:
	imul ecx, ecx, 0x83
	movsx eax, al
	add ecx, eax
	inc r14
	mov al, byte [r14]

.calc_hash_check:
	test al, al
	jnz .calc_hash
	btr ecx, 0x1F
	cmp ecx, ebp
	je .found

	inc edx
	add r8, 4
	cmp edx, r11d
	jb .next

.error_exit:
	xor eax, eax

.ret:
	mov rbx, [rsp + 0x30]
	mov rbp, [rsp + 0x38]
	mov rsi, [rsp + 0x40]
	mov rdi, [rsp + 0x48]
	add rsp, 0x20
	pop r14
	ret

.found:
	test rbx, rbx
	jnz .get_proc
	movzx ecx, word [rsi + rdx*2]
	mov eax, dword [rdi + rcx*4]
	add rax, r9
	jmp .ret

.get_proc:
	mov rdx, r10
	mov rcx, r9
	call rbx
	jmp .ret
FUNCTION_DATA_END get_proc_from_hash_x64