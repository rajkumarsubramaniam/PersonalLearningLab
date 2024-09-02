@echo off
:: Compiling with GCC for .c files. 
:: Pass additonal flag in %1
gcc .\main.c .\mymutexlock.c -o locks.exe -I headers %1

:: *****Some Notes for future*****
:: To generate ASM file use, (conversts mymutexlocks.c to locskAsmOutput file)
:: gcc -S .\mymutexlock.c -o locksAsmOutput -I headers

:: Explore
:: gcc --help
:: gcc -v

:: To build 32-bit and 64-bit versions
:: Use the mingw32 shell (launch it from the msys64 folder mingw32.exe)
:: gcc ./main.c ./mymutexlock.c -o locks32Bit.exe -I headers
:: my default powershell gcc option uses mingw ucrt64 version. Use that to build 64-bit version.
:: There are multiple ways to build a 32-bit version bin, explore in msys2 website (or use google/chatgpt) 