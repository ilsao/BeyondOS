#include "kernel.h"
#include "common.h"
#include "memory.h"
#include "process.h"
#include "exception.h"

/* import symbols from the linker */
extern char __bss[], __bss_end[], __stack_top[];

struct process *proc_a, *proc_b;
void proc_a_entry()
{
    printf("starting process A\n");
    while (1) {
        putchar('A');
        // buggy here, incorrectly store regs from a to main stack
        switch_context(&proc_a->sp, &proc_b->sp);
        delay();
    }
}

void proc_b_entry()
{
    printf("starting process B\n");
    while (1) {
        putchar('B');
        // buggy here, incorrectly store regs from a to main stack
        switch_context(&proc_b->sp, &proc_a->sp);
        delay();
    }
}

/* kernel main */
void kernel_main(void)
{
    // clear bss for uninitialized global and static variables
    memset((void *)__bss, 0, (size_t)__bss_end - (size_t)__bss);

    printf("\n\nHello, World!\n");

    proc_a = create_process((uint32_t) proc_a_entry);
    proc_b = create_process((uint32_t) proc_b_entry);
    proc_a_entry();

    paddr_t paddr0 = alloc_pages(2);
    paddr_t paddr1 = alloc_pages(1);
    printf("alloc_page test paddr0 = %x\n", paddr0);
    printf("alloc_page test paddr1 = %x\n", paddr1);

    // register exception entry
    WRITE_CSR(stvec, (uint32_t) kernel_entry);
    
    printf("1 + 2 = %d, %x\n", 1 + 2, (1 << 31) >> 31);

    PANIC("booted! ");
}

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