
Notes:
Configuring Mingw-w64 compiler, https://code.visualstudio.com/docs/cpp/config-mingw 
    # Following instructions in the link, install the tools for 64-bit support. ("pacman -S mingw-w64-ucrt-x86_64-gcc")
    # "pacman -S mingw-w64-i686-toolchain"  Run this command on MSYS prompt to install the 32-bit version support. 
        # Basically the tools can be downloaded from websites like, Sourceforge, msys2, WinLibs, mingw-builds etc.,
-> Refer OS-concepts/synchronization, .bat file to understand how to build 32-bit and 64-bit bins using mingw-w64 toolchain.

Initially I was using an old compiler and switched to this new one.

Tips:
-> To learn the assembly implementation, use 'gcc -S' flag and refer generated .ass