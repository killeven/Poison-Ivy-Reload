pushad_eax		equ (7*4)
pushad_ecx		equ (6*4)
pushad_edx		equ (5*4)
pushad_ebx		equ (4*4)
pushad_esp		equ (3*4)
pushad_ebp		equ (2*4)
pushad_esi		equ (1*4)
pushad_edi		equ (0*4)

; PUSH HASH
macro PUSH_HASH v* {
    common
        local ..c, ..hash
        virtual at 0
            db  `v
            ..hash = 0
            repeat $
                load ..c from $$+%-1
                ..hash = ..hash * 131 + ..c
                ..hash = ..hash and 0xffffffff
            end repeat
            ..hash = ..hash and 0x7fffffff
        end virtual
    common
        push ..hash
}

; dd hash
macro DD_HASH v* {
    common
        local ..c, ..hash
        virtual at 0
            db  `v
            ..hash = 0
            repeat $
                load ..c from $$+%-1
                ..hash = ..hash * 131 + ..c
                ..hash = ..hash and 0xffffffff
            end repeat
            ..hash = ..hash and 0x7fffffff
        end virtual
    common
        dd ..hash   
}

; 声明hash
macro DEFINE_HASH v* {
    common
        local ..c, ..hash
        virtual at 0
            db  `v
            ..hash = 0
            repeat $
                load ..c from $$+%-1
                ..hash = ..hash * 131 + ..c
                ..hash = ..hash and 0xffffffff
            end repeat
            ..hash = ..hash and 0x7fffffff
        end virtual
    common
        v#_hash = ..hash
}

; 拷贝hash到寄存器
macro MOV_HASH reg*, v* {
    common
        local ..c, ..hash
        virtual at 0
            db  `v
            ..hash = 0
            repeat $
                load ..c from $$+%-1
                ..hash = ..hash * 131 + ..c
                ..hash = ..hash and 0xffffffff
            end repeat
            ..hash = ..hash and 0x7fffffff
        end virtual
    common
        mov reg, ..hash
}

; 批量声明api hash
macro API_HASH_TABLE library, [funcname] {
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
		api_hash_t	..hash, global_data_t#.#library, global_data_t#.#funcname    
}

macro API_HASH_TABLE_END {
	common
		_WORD	0    
}

; 用于global_data中声明api
macro API_DECLARE library, [funcname] {
    common
        library     _DWORD  ?
    forward
        funcname    _DWORD  ?
}

macro PUSH_ANSI_STRING str {
    common
        call @F
        db  str, 0
        @@:
}

macro PUSH_WIDE_STRING str {
    common
        call @F
        du  str, 0
        @@:
}

; 基本函数声明
macro BASE_FUNCTION [funcname] {
    common
        BASE_FUNCTION_COUNT = 0
    forward
        funcname    _DWORD  ?
        BASE_FUNCTION_COUNT = BASE_FUNCTION_COUNT + 1
}

; 用于global_data中声明额外的函数
; 为了兼容x64，所有的额外附加函数都被扩充成了qword
; 不影响x86 code的使用
macro EXTRA_FUNCTION [funcname] {
    common
        EXTRA_FUNCTION_COUNT = 0
    forward
        funcname        _DWORD  ?
                        _DWORD  ?   ; dummy for x64 code
        funcname#_size  _WORD   ?
        EXTRA_FUNCTION_COUNT = EXTRA_FUNCTION_COUNT + 1
}

macro FUNCTION_DATA_BEGIN funcname {
    common
        function_data_t global_data_t#.#funcname, funcname#_#size
}

macro FUNCTION_DATA_END funcname {
    common
        funcname#_#size = $ - funcname
}

; 测试用
macro CONFIG_BEGIN name {
    common
        config_t global_data_t#.#name, name#_size
        name##_code_begin:
}

macro CONFIG_END name {
    common
        name#_size = $ - name##_code_begin
}

macro BASE_FUNCTION_TABLE [funcname] {
    forward
        local ..delta
        dw funcname - ..delta
        ..delta:
}