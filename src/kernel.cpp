#include "types.h"
#include "io.h"
#include "gdt.h"

void clearScreen()
{
    int8_t x = 0, y = 0;
    int8_t* VideoMemory =  (int8_t *)0xB8000;
    for (y = 0; y < 25; y++)
    {
        for (x = 0; x < 80; x++)
        {
            *(VideoMemory + (x + y * 80) * 2) = ' ';
        }
    }
}

void print(const int8_t* str)
{
    /** 屏幕分辨率为80 x 25 **/

    static int8_t x = 0, y = 0;

    static int8_t* VideoMemory = (int8_t *)0xB8000;

    for (int8_t i = 0; str[i] != '\0'; i++)
    {
        switch (str[i])
        {
        case '\n':
            x = 0;
            y++;
            break;
        
        default:
            *(VideoMemory + (x + y * 80) * 2) = str[i];
            x++;
            break;
        }

        if (x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            y = 0;
        }
    }
}

// loader.s 通过kernelMain符号来调用该函数。
// c++为了实现函数重载,在编译过程中会使用自己的符号命名规则将该函数符号重命名
// 所以为了保持该函数符号不变，需要使用extern "C" 声明符，即使用C的编译规则去命名该函数符号
extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    clearScreen();
    print("Hello World!\n");
    print("Hello World!!!!!!!!!!\n");
    GlobalDescriptorTable gdt;
    while(1);   // 为了防止程序执行一些无意义的指令
}

/**
 * 调用c++全局变量的构造函数
 */
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}
