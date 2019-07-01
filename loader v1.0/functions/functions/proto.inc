int __cdecl send_packet(global_data_t *global_data, SOCKET s, uint8_t cmd, const char *buf, size_t size) {
  packet_header_t ph;

  zero_memory(&ph, sizeof(ph));
  ph.random = xGetTickCount();
  ph.signature = PACKET_HEADER_SIGNATURE;
  ph.cmd = cmd;

  if (buf == 0) {
    rc4_crypt(global_data->send_sbox, (char *)&ph, sizeof(packet_header_t));
    if (send_data(s, (char *)&ph, sizeof(ph)) == SOCKET_ERROR) return SOCKET_ERROR;
  }
  else {
    ph.packet_unpacked_size = size;

    char *send_buf = alloc_memory(size);
    uint32_t compressed_size;

    if (size >= MIN_COMPRESS_DATA_SIZE) {
      compressed_size = compress((char *)buf, size, send_buf, size);
    }
    else {
      copy_memory(send_buf, buf, size);
      compressed_size = size;
    }

    if (compressed_size < 0) {
      free_memory(send_buf);
      return SOCKET_ERROR;
    }

    ph.packet_size = compressed_size;

    rc4_crypt(global_data->send_sbox, (char *)&ph, sizeof(packet_header_t));
    rc4_crypt(global_data->send_sbox, (char *)send_buf, compressed_size);

    if (send_data(s, (char *)&ph, sizeof(ph)) == SOCKET_ERROR) return SOCKET_ERROR;
    if (send_data(s, (char *)send_buf, compressed_size) == SOCKET_ERROR) return SOCKET_ERROR;
  }

  return 0;
}

int __cdecl recv_packet(global_data_t *global_data, SOCKET s, uint8_t *cmd, void **buf, size_t *size) {
  packet_header_t ph;

  *buf = 0;
  *size = 0;

  if (recv_data(s, (char *)&ph, sizeof(packet_header_t)) == SOCKET_ERROR) {
    return SOCKET_ERROR;
  }

  rc4_crypt(global_data->recv_sbox, (char *)&ph, sizeof(ph));

  if (ph.signature != PACKET_HEADER_SIGNATURE) {
    return SOCKET_ERROR;
  }

  *cmd = ph.cmd;

  if (ph.packet_size == 0) return 0;

  void *encrypt_data = alloc_memory(ph.packet_size);

  if (recv_data(s, encrypt_data, ph.packet_size) == SOCKET_ERROR) {
    free_memory(encrypt_data);
    return SOCKET_ERROR;
  }

  rc4_crypt(global_data->recv_sbox, (char *)encrypt_data, ph.packet_size);

  if (ph.packet_size == ph.packet_unpacked_size) {
    *buf = encrypt_data;
    *size = ph.packet_size;

    return 0;
  }

  void *decompress_data = alloc_memory(ph.packet_unpacked_size);
  size_t decompress_size = decompress(encrypt_data, ph.packet_size, decompress_data, ph.packet_unpacked_size);

  if (decompress_size != ph.packet_unpacked_size) {
    free_memory(encrypt_data);
    free_memory(decompress_data);
    return SOCKET_ERROR;
  }

  free_memory(encrypt_data);

  *buf = decompress_data;
  *size = ph.packet_unpacked_size;

  return 0;
};