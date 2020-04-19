#include "types.h"

void printf(const int8_t* str)
{
    int8_t* VideoMemory = (int8_t *)0xB8000;
    while(*str != '\0')
    {
        *VideoMemory = *str;
        VideoMemory += 2;
        str++;
    }
}

// loader.s 通过kernelMain符号来调用该函数。
// c++为了实现函数重载,在编译过程中会使用自己的符号命名规则将该函数符号重命名
// 所以为了保持该函数符号不变，需要使用extern "C" 声明符，即使用C的编译规则去命名该函数符号
extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    printf("Hello, World");
    while(1);   // 为了防止程序执行一些无意义的指令
}

