del *.bin
@for /f "delims=" %%i in ('dir *.asm /b') do fasm %%i