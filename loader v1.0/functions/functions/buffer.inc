buffer_t * __cdecl buffer_new(global_data_t *global_data) {
  buffer_t *ret;
  
  ret = (buffer_t *)alloc_memory(sizeof(buffer_t));
  zero_memory(ret, sizeof(buffer_t));
  ret->global_data = global_data;

  return ret;
};

#define global_data buf->global_data  // define globaldata for other

void __cdecl buffer_free(buffer_t *buf) {
  if (buf->data != 0)
    free_memory(buf->data);
  free_memory(buf);
};

void __cdecl buffer_checkspace(buffer_t *buf, size_t l) {
  if (buf->alloc - buf->size < l) {
    size_t nsize = (buf->alloc) ? buf->alloc * 2 : BUFFER_INIT_SIZE;

    while (nsize < buf->size + l) {
      size_t tmp = nsize * 2;
      if (tmp <= nsize) {
        nsize = buf->size + l;
        break;
      }
      nsize = tmp;
    }

    void *tmp;

    if (buf->data == 0)
      tmp = alloc_memory(nsize);
    else
      tmp = realloc_memory(buf->data, nsize);

    buf->data = (uint8_t *)tmp;
    buf->alloc = nsize;
  }
};

void __cdecl buffer_write(buffer_t *buf, const void *v, size_t l) {
  buffer_checkspace(buf, l);
  copy_memory(buf->data + buf->size, v, l);
  buf->size += l;
};

void __cdecl buffer_clear(buffer_t *buf) {
  buf->size = 0;
};

#undef global_data  // undef global_data