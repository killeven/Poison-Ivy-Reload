#ifndef SHELLCODES_H
#define SHELLCODES_H
#include "global_data.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN64
  void x64_code_save();
#else
  void inject_to_explorer_save(const char *filename);
  void inject_to_explorer_code_x86_save(const char *filename);
  void rc4_init_save(char *filename);
  void rc4_crypt_save(char *filename);
#endif
#ifdef __cplusplus
}
#endif

#endif  // SHELLCODES_H