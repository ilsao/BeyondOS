#include "trap.h"
#include "kernel.h"
#include "common.h"
#include "memory.h"
#include "process.h"

extern char __bss[], __bss_end[], __stack_top[], __kernel_base[], __free_ram_end[];
extern char _binary_shell_bin_start[], _binary_shell_bin_size[];
extern struct process *current_proc, *idle_proc;

/* booter */
__attribute__((section(".text.boot"), naked))  // func boot -> .text.boot = 0x80200000
void boot(void)
{
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n"
        "j kernel_main\n"
        :
        : [stack_top] "r" (__stack_top)
    );
}

/* kernel main */
void kernel_main(void)
{
    // clear bss for uninitialized global and static variables
    memset((void *)__bss, 0, (size_t)__bss_end - (size_t)__bss);

    // register exception entry
    WRITE_CSR(stvec, (uint32_t) kernel_entry);

    printf("\n\nHello, World!\n");

    printf("\n__kernel_base: %x\n", __kernel_base);
    printf("__free_ram_end: %x\n\n", __free_ram_end);

    idle_proc = create_idle_process();
    current_proc = idle_proc;

    create_process(_binary_shell_bin_start, (size_t) _binary_shell_bin_size);

    yield();
    PANIC("switched to idle process");
}