PBITMAPINFO __cdecl bitmap_create_info(global_data_t *global_data, HDC dc, int bit_count, int width, int height, int *bi_size) {
  /*
  bit_count 为1 (黑白二色图) 、4 (16 色图) 、8 (256 色图) 时由颜色表项数指出颜色表大小
  bit_count 为16 (16 位色图) 、24 (真彩色图, 不支持) 、32 (32 位色图) 时没有颜色表
  */
  int color_num;

  color_num = bit_count <= 8 ? 1 << bit_count : 0;
  *bi_size = sizeof(BITMAPINFOHEADER) + (color_num * sizeof(RGBQUAD));

  BITMAPINFO *bmp_info;
  BITMAPINFOHEADER *bmp_info_header;

  bmp_info = (BITMAPINFO *)alloc_memory(*bi_size);
  bmp_info_header = &bmp_info->bmiHeader;

  bmp_info_header->biSize = sizeof(BITMAPINFOHEADER);
  bmp_info_header->biWidth = width;
  bmp_info_header->biHeight = height;
  bmp_info_header->biPlanes = 1;
  bmp_info_header->biBitCount = bit_count;
  bmp_info_header->biCompression = BI_RGB;
  bmp_info_header->biXPelsPerMeter = 0;
  bmp_info_header->biYPelsPerMeter = 0;
  bmp_info_header->biClrUsed = 0;
  bmp_info_header->biClrImportant = 0;
  // Compute the number of bytes in the array of color 
  // indices and store the result in biSizeImage. 
  // For Windows NT, the width must be DWORD aligned unless 
  // the bitmap is RLE compressed. This example shows this. 
  // For Windows 95/98/Me, the width must be WORD aligned unless the 
  // bitmap is RLE compressed.
  bmp_info_header->biSizeImage = (((width * bit_count + 31) & ~31) >> 3) * bmp_info_header->biHeight;

  // 16位和以后的没有颜色表，直接返回
  if (bit_count >= 16) return bmp_info;

  /*
  Windows 95和Windows 98：如果lpvBits参数为NULL并且GetDIBits成功地填充了BITMAPINFO结构，那么返回值为位图中总共的扫描线数。

  Windows NT：如果lpvBits参数为NULL并且GetDIBits成功地填充了BITMAPINFO结构，那么返回值为非0。如果函数执行失败，那么将返回0值。Windows NT：若想获得更多错误信息，请调用callGetLastError函数。
  */
  HBITMAP bmp;

  // 宽高不能为0
  bmp = xCreateCompatibleBitmap(dc, 1, 1);
  // 获取color table
  xGetDIBits(dc, bmp, 0, 0, 0, bmp_info, DIB_RGB_COLORS);

  xDeleteObject(bmp);

  return bmp_info;
}

bitmap_t * __cdecl bitmap_new(global_data_t *global_data, HDC src_dc, int bit_count, int width, int height) {
  switch (bit_count) {
  case 1:
  case 4:
  case 8:
  case 16:
  case 32:
    break;
  default:
    bit_count = 8;
    break;
  }

  bitmap_t *ret = alloc_memory(sizeof(bitmap_t));

  ret->global_data = global_data;
  ret->width = width;
  ret->height = height;
  ret->bit_count = bit_count;
  ret->info = bitmap_create_info(global_data, src_dc, bit_count, width, height, &ret->info_size);
  ret->bitmap = xCreateDIBSection(src_dc, ret->info, DIB_RGB_COLORS, &ret->bits, 0, 0);
  ret->dc = xCreateCompatibleDC(src_dc);
  ret->file_header.bfType = 0x4d42;
  ret->file_header.bfSize = ret->info->bmiHeader.biSize + ret->info->bmiHeader.biSizeImage;
  ret->file_header.bfOffBits = sizeof(BITMAPFILEHEADER) + ret->info->bmiHeader.biSize;
  ret->file_header.bfReserved1 = 0;
  ret->file_header.bfReserved2 = 0;
  ret->bitmap_file_size = sizeof(BITMAPFILEHEADER) + ret->info_size + ret->info->bmiHeader.biSizeImage;
  xSelectObject(ret->dc, ret->bitmap);

  return ret;
}

#define global_data bmp->global_data

void __cdecl bitmap_free(bitmap_t *bmp) {
  xDeleteDC(bmp->dc);
  xDeleteObject(bmp->bitmap);

  free_memory(bmp->info);
}

void * __cdecl bitmap_scan_line(bitmap_t *bmp, int line) {
  if (bmp->height == 0) {
    return (void *)bmp->bits;
  }

  //  bmp的扫描顺序是从下到上的
  int perline_size = bmp->info->bmiHeader.biSizeImage / bmp->height;

  return (void *)((uint8_t *)bmp->bits + perline_size * (bmp->height - 1 - line));
}

void __cdecl bitmap_save(bitmap_t *bmp, buffer_t *buf) {
  buffer_write(buf, &bmp->file_header, sizeof(BITMAPFILEHEADER));
  buffer_write(buf, bmp->info, bmp->info_size);
  buffer_write(buf, bmp->bits, bmp->info->bmiHeader.biSizeImage);
}

#undef global_data