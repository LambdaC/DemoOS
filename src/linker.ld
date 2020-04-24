/* 
 * linker script, 一是为了指定程序入口，而是为了配置目标文件的内存布局，
 * 为了让grub知道这是一个kernel程序。
*/

ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
  . = 0x0100000; /*此位置是有讲究的，刚好是real mode最大内存空间的下一个字节*/

  .text :
  {
    *(.multiboot)
    *(.text*)
    *(.rodata)
  }

  .data  :
  {
    start_ctors = .;
    KEEP(*( .init_array ));
    KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
    end_ctors = .;

    *(.data)
  }

  .bss  :
  {
    *(.bss)   /* 这里是栈开始的地方 */
  }
}
