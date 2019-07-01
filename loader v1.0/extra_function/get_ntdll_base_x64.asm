include '../include/global.inc'

use64

FUNCTION_DATA_BEGIN get_ntdll_base_x64
get_ntdll_base_x64:
	mov rax, 0x60
	mov rax, [gs:rax]
	mov rax, [rax + 0x18]
	mov rax, [rax + 0x30]
	mov rax, [rax + 0x10]
	ret	
FUNCTION_DATA_END get_ntdll_base_x64