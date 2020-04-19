// 该loader.s文件有两个作用。一个是设置mutiboot setion，告诉引导程序，这是一个kernel。
// 其次是，函数调用需要使用stack，所以需要在这里初始化栈的内存地址空间

.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


.section .text
.extern kernelMain
.global loader


loader:
    mov $kernel_stack, %esp # 初始化栈空间
    push %eax
    push %ebx
    call kernelMain     # 调用kernel的入口函数


_stop:
    cli
    hlt
    jmp _stop


.section .bss
.space 2*1024*1024; # 2 MiB
kernel_stack:

