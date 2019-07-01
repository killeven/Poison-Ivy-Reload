// loader_function.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "shellcodes.h"

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _WIN64
  x64_code_save();
#else
  inject_to_explorer_save("inject_to_explorer.bin");
  inject_to_explorer_code_x86_save("inject_to_explorer_code_x86.bin");
  rc4_init_save("rc4_init.bin");
  rc4_crypt_save("rc4_crypt.bin");
#endif
	return 0;
}
