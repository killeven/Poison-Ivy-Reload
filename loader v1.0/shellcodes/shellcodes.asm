format MS COFF

;include 'global.inc'

macro export_function [function] {
    forward
        public get_#function#_ptr
        public get_#function#_size
        
        function:
        	file `function#'.bin'
        function#_size = $ - function

        get_#function#_ptr:
            lea eax, [function]
            ret
            
        get_#function#_size:
            mov eax, function#_size
            ret
}

section '.text' readable executable

export_function main, cmd_shell, information, process, screenspy, thumbnail