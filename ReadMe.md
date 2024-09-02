Author github username: rajkumarsubramaniam

This repo is created for personal learning purposes. 

Initial idea is to create separate folders for different languages/projects I am trying to explore and create sub-folders within each based on simple tasks identified.

Plan is to use vscode for editing, compiling and running on a windows machine.

Rules:
Folder names are lower case, with no spaces.

Notes:
Configuring Mingw-w64 compiler, https://code.visualstudio.com/docs/cpp/config-mingw 
    # Following instructions in the link, install the tools for 64-bit support. ("pacman -S mingw-w64-ucrt-x86_64-gcc")
    # "pacman -S mingw-w64-i686-toolchain"  Run this command on MSYS prompt to install teh 32-bit version support. 
        # Basically the tools can be downloaded from websites like, Sourceforge, msys2, WinLibs, mingw-builds etc.,
# Refer OS-concepts/synchronization, .bat file to understand how to build 32-bit and 64-bit bins uisng mingw-w64 toolchain.
Initialy I was using an old compiler and switched to this new one.