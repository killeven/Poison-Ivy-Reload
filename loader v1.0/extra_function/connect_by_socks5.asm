include '../include/global.inc'
include 'win32a.inc'

use32

; 定义socks5相关结构
struct socks5req1
    Ver         _CHAR  ?
    nMethods    _CHAR  ?
    Methods     _CHAR  2   dup(?)
ends

struct socks5ans1
    Ver     _CHAR  ?
    Method  _CHAR  ?
ends

struct socks5req2
    Ver     _CHAR   ?
    Cmd     _CHAR   ?
    Rsv     _CHAR   ?
    Atyp    _CHAR   ?
    IPAddr  _ULONG  ?
    Port    _USHORT ?
ends

struct socks5ans2
    Ver     _CHAR   ?
    _Rep    _CHAR   ?
    Rsv     _CHAR   ?
    Atyp    _CHAR   ?
    Other   _CHAR   ?
ends

struct authreq
    Ver         _CHAR   ?
    ULen        _CHAR   ?
    NamePass    _CHAR   256 dup(?)
ends

struct authans
    Ver     _CHAR   ?
    Status  _CHAR   ?
ends

FUNCTION_DATA_BEGIN connect_by_socks5

; 通过socks连接server
proc connect_by_socks5 stdcall server: dword, port: dword
    locals
        s               _SOCKET     ?
        proxyreq1       socks5req1  ?
        proxyreq2       socks5req2  ?
        _authreq        authreq     ?     
        buf             _BYTE       600 dup(?)
        user_len    	_BYTE       ?
        pass_len    	_BYTE       ?
    endl
    
    assume esi: global_data_t
    
    lea eax, [esi.socks5_dns]
    movzx ecx, [esi.socks5_port]
    invoke esi.connect_server, eax, ecx
    cmp eax, SOCKET_ERROR
    je .ret
    
    mov [s], eax
    mov byte [proxyreq1.Ver], 5
    mov byte [proxyreq1.nMethods], 2
    mov byte [proxyreq1.Methods], 0
    mov byte [proxyreq1.Methods + 1], 2
    
    lea ecx, [proxyreq1]
    invoke esi.send_data, esi, [s], ecx, sizeof.socks5req1
    cmp eax, SOCKET_ERROR
    je .close_and_ret_error
    
    invoke esi.wait_buffer, esi, [s], 3, 0
    cmp eax, 0
    jle .close_and_ret_error
    
    
    lea edi, [buf]
    invoke esi.RtlZeroMemory, edi, 600
    invoke esi.recv, [s], edi, 600, 0
    
    assume edi: socks5ans1
    
    .if ([edi.Ver] <> 5) | (([edi.Method] <> 0) & ([edi.Method] <> 2))
        jmp .close_and_ret_error    
    .endif
    
    lea eax, [esi.socks5_user]
    invoke esi.lstrlenA, eax
    mov [user_len], al
    
    .if ([edi.Method] = 2) & ([user_len] > 0)
        lea eax, [esi.socks5_pass]
        invoke esi.lstrlenA, eax
        mov [pass_len], al

        lea ecx, [_authreq]                
        invoke esi.RtlZeroMemory, ecx, sizeof.authreq
        
        mov byte [_authreq.Ver], 5
        mov al, byte [user_len]
        mov [_authreq.ULen], al
        
        lea eax, [esi.socks5_user]
        lea edi, [_authreq.NamePass]
        invoke esi.lstrcpyA, edi, eax
        
        xor eax, eax
        mov al, byte [user_len]
        add edi, eax
        
        mov al, byte [pass_len]
        mov byte [edi], al
        add edi, 1
        
        lea eax, [esi.socks5_pass]
        invoke esi.lstrcpyA, edi, eax
        
        xor eax, eax
        mov al, byte [pass_len]                 
        add edi, eax
        
        lea ecx, [_authreq]
        sub edi, ecx
                      
        invoke esi.send_data, esi, [s], ecx, edi
        
        invoke esi.wait_buffer, esi, [s], 3, 0
        cmp eax, 0
        jle .close_and_ret_error
        
        lea edi, [buf]
        invoke esi.RtlZeroMemory, edi, 600
        invoke esi.recv, [s], edi, 600, 0
        
        assume edi: authans
        
        .if ([edi.Ver] <> 5) | ([edi.Status] <> 0)
            jmp .close_and_ret_error
        .endif
        
    .endif
    
    mov byte [proxyreq2.Ver], 5
    mov byte [proxyreq2.Cmd], 1
    mov byte [proxyreq2.Rsv], 0
    mov byte [proxyreq2.Atyp], 1
    invoke esi.htons, [port]
    mov word [proxyreq2.Port], ax
    
    invoke esi.inet_addr, [server]
    mov [proxyreq2.IPAddr], eax
    
    .if (eax = INADDR_NONE)
        invoke esi.gethostbyname, [server]
        test eax, eax
        jz .close_and_ret_error
        
        assume eax: hostent
        
        mov eax, [eax.h_addr_list]
        mov eax, [eax]
        push dword [eax]
        pop dword [proxyreq2.IPAddr]
    .endif
    
    lea ecx, [proxyreq2]
    invoke esi.send_data, esi, [s], ecx, sizeof.socks5req2
    
    invoke esi.wait_buffer, esi, [s], 3, 0
    cmp eax, 0
    jle .close_and_ret_error
    
    lea edi, [buf]
    invoke esi.RtlZeroMemory, edi, 600
    invoke esi.recv, [s], edi, 600, 0
    
    assume edi: socks5ans2
    
    .if ([edi.Ver] <> 5) | ([edi._Rep] <> 0)
        jmp .close_and_ret_error
    .endif
    
    mov eax, [s]
    
.ret:
    ret

.close_and_ret_error:
    invoke esi.closesocket, [s]
    mov eax, SOCKET_ERROR
    jmp .ret
endp

FUNCTION_DATA_END connect_by_socks5