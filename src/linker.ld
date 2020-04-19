/* 
 * linker script, 一是为了指定程序入口，而是为了配置目标文件的内存布局，
 * 为了让grub知道这是一个kernel程序。
*/

ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
  . = 0x0100000;

  .text :
  {
    *(.multiboot)
    *(.text*)
    *(.rodata)
  }

  .data  :
  {
    *(.data)
  }

  .bss  :
  {
    *(.bss)
  }
}
