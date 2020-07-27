#define global_data buf->global_data  // define globaldata for other

#pragma warning(push)
#pragma warning(disable:4244) // 去除转换可能丢失数据的警告

// windows都是little endian而msgpack是big endian所以这里只处理小端序
#define _store16(p, x) *(uint16_t *)p = (uint16_t)((((x) >> 8) & 0x0ff) | (x) << 8)

#define _store32(p, x)                    \
  *(uint32_t *)p =                        \
    ((uint32_t)(((uint32_t)(x)) >> 24)) | \
    (((uint32_t)(x) & 0x00ff0000) >> 8) | \
    (((uint32_t)(x) & 0x0000ff00) << 8) | \
    ((uint32_t)(((uint32_t)(x)) << 24));

#define _store64(p, x)                                      \
    *(uint64_t*)p =                                         \
        ((uint64_t)(                                        \
        (((((uint64_t)(x)) >> 40) |                         \
        (((uint64_t)(x)) << 24)) & 0x0000ff000000ff00ULL) | \
        (((((uint64_t)(x)) >> 24) |                         \
        (((uint64_t)(x)) << 40)) & 0x00ff000000ff0000ULL) | \
        (((uint64_t)(x) & 0x000000ff00000000ULL) >>  8) |   \
        (((uint64_t)(x) & 0x00000000ff000000ULL) <<  8) |   \
        (((uint64_t)(x)) >> 56) |                           \
        (((uint64_t)(x)) << 56)));

#define _load16(p, d)                   \
    d = *(uint16_t *)(p);               \
    d = (uint16_t)((d << 8) | (d >> 8))

#define _load32(p, d)                         \
    d = *(uint32_t *)(p);                     \
    d = (d << 24) | ((d & 0xff00) << 8) |     \
            ((d & 0xff0000) >> 8) | (d >> 24)

#define _load64(p, d)                         \
    d = *(uint64_t *)(p);                     \
    d = ((((d >> 40) |                        \
        (d << 24)) & 0x0000ff000000ff00ULL) | \
        (((d >> 24) |                         \
        (d << 40)) & 0x00ff000000ff0000ULL) | \
        ((d & 0x000000ff00000000ULL) >>  8) | \
        ((d & 0x00000000ff000000ULL) <<  8) | \
        (d >> 56) |                           \
        (d << 56))

#define move0(d) {   \
    buffer_checkspace(buf, sizeof(uint8_t)); \
    uint8_t *s = buf->data + buf->size; \
    *s = d;         \
    buf->size += sizeof(uint8_t);  \
    return; \
  }

#define move1(t, d) {     \
    buffer_checkspace(buf, sizeof(uint8_t) + sizeof(uint8_t)); \
    uint8_t *s = buf->data + buf->size; \
    *s++ = (uint8_t)t;  \
    *s++ = (uint8_t)d;  \
    buf->size += sizeof(uint8_t) + sizeof(uint8_t);  \
    return; \
  }

#define move2(t, d) {           \
    buffer_checkspace(buf, sizeof(uint8_t) + sizeof(uint16_t)); \
    uint8_t *s = buf->data + buf->size; \
    *s++ = (uint8_t)t;        \
    _store16(s, (uint16_t)d); \
    buf->size += sizeof(uint8_t) + sizeof(uint16_t);    \
    return; \
  }

#define move4(t, d) {           \
    buffer_checkspace(buf, sizeof(uint8_t) + sizeof(uint32_t)); \
    uint8_t *s = buf->data + buf->size; \
    *s++ = (uint8_t)t;        \
    _store32(s, (uint32_t)d); \
    buf->size += sizeof(uint8_t) + sizeof(uint32_t);    \
    return; \
  }

#define move8(t, d) {           \
    buffer_checkspace(buf, sizeof(uint8_t) + sizeof(uint64_t)); \
    uint8_t *s = buf->data + buf->size; \
    *s++ = (uint8_t)t;        \
    _store64(s, (uint64_t)d); \
    buf->size += sizeof(uint8_t) + sizeof(uint64_t);    \
    return; \
  }

void __cdecl msgpack_lite_pack_nil(buffer_t *buf) {
  move0(0xc0);
};

void __cdecl msgpack_lite_pack_boolean(buffer_t *buf, bool b) {
  if (b)
    move0(0xc3)
  else
  move0(0xc2);
};

void __cdecl msgpack_lite_pack_signed(buffer_t *buf, int64_t i) {
  if (i > 0x7f) {
    if (i < 0x100)
      move1(0xcc, i);

    if (i < 0x10000L)
      move2(0xcd, i);

    if (i < 0x100000000LL)
      move4(0xce, i);

    move8(0xcf, i);
  }

  if (i >= -32)
    move0(i);

  if (i >= -128)
    move1(0xd0, i);

  if (i >= -32768)
    move2(0xd1, i);

  if (i >= (int64_t)0xffffffff80000000LL)
    move4(0xd2, i);

  move8(0xd3, i);
};

void __cdecl msgpack_lite_pack_unsigned(buffer_t *buf, uint64_t i) {
  if (i < 0x80)
    move0(i);

  if (i < 0x100)
    move1(0xcc, i);

  if (i < 0x10000L)
    move2(0xcd, i);

  if (i < 0x100000000LL)
    move4(0xce, i);

  move8(0xcf, i);
};

void __cdecl msgpack_lite_pack_float(buffer_t *buf, float f) {
  uint32_t tmp = *((uint32_t *)&f);
  move4(0xca, tmp);
};

void __cdecl msgpack_lite_pack_double(buffer_t *buf, double d) {
  uint64_t tmp = *((uint64_t*)&d);
  move8(0xcb, tmp);
};

void __cdecl msgpack_lite_pack_real(buffer_t *buf, double d) {
  float f = (float)d;
  double df = f;
  if (df == d)
    msgpack_lite_pack_float(buf, f);
  else
    msgpack_lite_pack_double(buf, d);
};

void __cdecl msgpack_lite_pack_map_size(buffer_t *buf, uint32_t n) {
  if (n < 0x10)
    move0(0x80 | n);

  if (n < 0x10000)
    move2(0xde, n);

  move4(0xdf, n);
};

void __cdecl msgpack_lite_pack_str(buffer_t *buf, const char *v) {
  size_t l = xlstrlenA(v);
  buffer_checkspace(buf, l + sizeof(uint8_t) + sizeof(uint32_t));
  uint8_t *s = buf->data + buf->size;
  if (l < 0x20) {   // Fixstr
    *s++ = (uint8_t)(0xa0 + l);
    buf->size += sizeof(uint8_t);
  }
  else if (l < 0x100) {   // Str 8
    *s++ = 0xd9;
    *s++ = l;
    buf->size += sizeof(uint8_t) + sizeof(uint8_t);
  }
  else if (l < 0x10000) {
    *s++ = 0xda;
    _store16(s, (uint16_t)l);
    s += sizeof(uint16_t);
    buf->size += sizeof(uint8_t) + sizeof(uint16_t);
  }
  else {
    *s++ = 0xdb;
    _store32(s, (uint32_t)l);
    s += sizeof(uint32_t);
    buf->size += sizeof(uint8_t) + sizeof(uint32_t);
  }

  copy_memory(s, v, l);
  buf->size += l;
};

void __cdecl msgpack_lite_pack_widestr(buffer_t *buf, const wchar_t *v) {
  int l = xWideCharToMultiByte(CP_UTF8, 0, v, -1, 0, 0, 0, 0);
  buffer_checkspace(buf, l + sizeof(uint8_t) + sizeof(uint32_t));
  /*
  如果函数运行成功，并且cchMultiByte不为零，返回值是由 lpMultiByteStr指向的缓冲区中写入的字节数；如果函数运行成功，
  并且cchMultiByte为零，返回值是接收到待转换字符串的缓冲区所必需的字节数包括末尾的0。如果函数运行失败，返回值为零
  */
  l -= 1;
  uint8_t *s = buf->data + buf->size;
  if (l < 0x20) {   // Fixstr
    *s++ = (uint8_t)(0xa0 + l);
    buf->size += sizeof(uint8_t);
  }
  else if (l < 0x100) {   // Str 8
    *s++ = 0xd9;
    *s++ = l;
    buf->size += sizeof(uint8_t) + sizeof(uint8_t);
  }
  else if (l < 0x10000) {
    *s++ = 0xda;
    _store16(s, (uint16_t)l);
    s += sizeof(uint16_t);
    buf->size += sizeof(uint8_t) + sizeof(uint16_t);
  }
  else {
    *s++ = 0xdb;
    _store32(s, (uint32_t)l);
    s += sizeof(uint32_t);
    buf->size += sizeof(uint8_t) + sizeof(uint32_t);
  }
  xWideCharToMultiByte(CP_UTF8, 0, v, -1, s, l, 0, 0);
  buf->size += l;
};

void __cdecl msgpack_lite_pack_bin_size(buffer_t *buf, uint32_t n) {
  buffer_checkspace(buf, sizeof(uint8_t) + sizeof(uint32_t));
  uint8_t *s = buf->data + buf->size;
  if (n < 0x100)  { // Bin 8
    *s++ = 0xc4;
    *s++ = (uint8_t)n;
    buf->size += sizeof(uint8_t) + sizeof(uint8_t);
  }
  else if (n < 0x10000) { // Bin 16
    *s++ = 0xc5;
    _store16(s, (uint16_t)n);
    s += sizeof(uint16_t);
    buf->size += sizeof(uint8_t) + sizeof(uint16_t);
  }
  else {  // Bin32
    *s++ = 0xc6;
    _store32(s, (uint32_t)n);
    s += sizeof(uint32_t);
    buf->size += sizeof(uint8_t) + sizeof(uint32_t);
  }
};

void __cdecl msgpack_lite_pack_bin(buffer_t *buf, const void* v, uint32_t l) {
  buffer_checkspace(buf, l + sizeof(uint8_t) + sizeof(uint32_t));
  uint8_t *s = buf->data + buf->size;
  if (l < 0x100)  { // Bin 8
    *s++ = 0xc4;
    *s++ = (uint8_t)l;
    buf->size += sizeof(uint8_t) + sizeof(uint8_t);
  }
  else if (l < 0x10000) { // Bin 16
    *s++ = 0xc5;
    _store16(s, (uint16_t)l);
    s += sizeof(uint16_t);
    buf->size += sizeof(uint8_t) + sizeof(uint16_t);
  }
  else {  // Bin32
    *s++ = 0xc6;
    _store32(s, (uint32_t)l);
    s += sizeof(uint32_t);
    buf->size += sizeof(uint8_t) + sizeof(uint32_t);
  }

  copy_memory(s, v, l);
  buf->size += l;
};

void __cdecl msgpack_lite_pack_array_size(buffer_t *buf, uint32_t n) {
  if (n < 0x10)
    move0(0x90 | n);

  if (n < 0x10000)
    move2(0xdc, n);

  move4(0xdd, n);
};

void __cdecl msgpack_lite_pack_insert(buffer_t *buf, const void *v, uint32_t l) {
  buffer_write(buf, v, l);
};

#pragma warning(pop)  // warning pop
#undef global_data  // undef global_data
