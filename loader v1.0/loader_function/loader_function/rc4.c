#include "shellcodes.h"

#ifndef _WIN64

extern void __stdcall rc4_init_code(unsigned char *sbox, unsigned char *key, unsigned len);
extern void __cdecl rc4_init_end();
extern void __stdcall rc4_crypt_code(unsigned char *sbox, unsigned char *data, unsigned len);
extern void __cdecl rc4_crypt_end();

#pragma optimize("ts", on)

void __stdcall rc4_init_code(unsigned char *sbox, unsigned char *key, unsigned len) {
  unsigned char k[256];
  for (int i = 0; i < 256; i++) {
    sbox[i] = i;
    k[i] = key[i % len];
  }
  for (int i = 0, j = 0; i < 256; i++) {
    j = (j + sbox[i] + k[i]) % 256;
    unsigned char tmp = sbox[i];
    sbox[i] = sbox[j];
    sbox[j] = tmp;
  }
}

void __cdecl rc4_init_end() {
  printf(__FUNCTION__);
}

void __stdcall rc4_crypt_code(unsigned char *sbox, unsigned char *data, unsigned len) {
  int i = 0, j = 0;
  for (unsigned k = 0; k < len; k++) {
    i = (i + 1) % 256;
    j = (j + sbox[i]) % 256;
    unsigned char tmp = sbox[i];
    sbox[i] = sbox[j];
    sbox[j] = tmp;
    int t = (sbox[i] + sbox[j]) % 256;
    data[k] ^= sbox[t];
  }
}

void __cdecl rc4_crypt_end() {
  printf(__FUNCTION__);
};

void rc4_init_save(char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)rc4_init_code;
  end = (char *)rc4_init_end;

  printf("[*] rc4_init code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");
  fwrite(start, 1, end - start, f);

  fclose(f);
  printf("[*] save rc4_init to %s success.\n", filename);
}

void rc4_crypt_save(char *filename) {
  char *start, *end;
  FILE *f;

  start = (char *)rc4_crypt_code;
  end = (char *)rc4_crypt_end;

  printf("[*] rc4_crypt code size = 0x%X\n", end - start);

  f = fopen(filename, "wb");
  fwrite(start, 1, end - start, f);

  fclose(f);
  printf("[*] save rc4_crypt to %s success.\n", filename);
}

#pragma optimize("ts", off)

#endif