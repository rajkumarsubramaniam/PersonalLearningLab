/*
 * This file implements mechanism to understand the compilation and execution 
 * environment we use.
 * 
 * Ref: https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html
*/

#include <stdio.h>

void PrintCompilerAndTargetSettings() {

    //
    // Compiler check
    //
    #ifdef _MSC_VER
    // code specific to Visual Studio compiler
    printf("MSVC Visual Studio compiler is used\n");
    #endif

    #ifdef __GNUC__
    printf("GCC compiler\n");
    //Also, you can run 'gcc -v' to know more information.
    #endif

    #ifdef __clang__
    printf("clang compiler \n");
    #endif

    #ifdef __MINGW32__
    printf("Compiler: MinGW-w64 32bit  or MinGW32, sizet:%d\n", sizeof(size_t));
    #endif

    #ifdef __MINGW64__
    printf("Compiler: MinGW-w64 64bit, sizet:%d\n", sizeof(size_t));
    #endif

    //
    // OS Platforms
    //
    #ifdef __linux__
    printf("OS platform: Linux and Linux derived\n");
    #endif 

    #ifdef __ANDROID__
    printf("OS platform: Android (implies Linux too)\n");
    #endif

    #ifdef __APPLE__
    printf("OS platform: Darwin (Mac OS X and iOS)\n");
    #endif

    #ifdef _WIN32
    printf("OS platform: Windows 32-bit, sizet:%d\n", sizeof(size_t));
    #endif

    #ifdef _WIN64 
    printf("OS platform: Windows 64 bit (implies _WIN32), sizet:%d\n", sizeof(size_t));
    #endif

    return;
}