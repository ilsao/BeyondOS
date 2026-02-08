#include "kernel.h"
#include "common.h"
#include "memory.h"
#include "process.h"
#include "exception.h"

/* import symbols from the linker */
extern char __bss[], __bss_end[], __stack_top[];

/* kernel main */
void kernel_main(void)
{
    // clear bss for uninitialized global and static variables
    memset((void *)__bss, 0, (size_t)__bss_end - (size_t)__bss);

    printf("\n\nHello, World!\n");

    paddr_t paddr0 = alloc_pages(2);
    paddr_t paddr1 = alloc_pages(1);
    printf("alloc_page test paddr0 = %x\n", paddr0);
    printf("alloc_page test paddr1 = %x\n", paddr1);

    // register exception entry
    WRITE_CSR(stvec, (uint32_t) kernel_entry);
    __asm__ __volatile__("unimp");   
    
    printf("1 + 2 = %d, %x\n", 1 + 2, (1 << 31) >> 31);

    PANIC("booted! ");

    PANIC("Oops! \n");
    printf("NOT REACHABLE! ");

    for (;;)
        __asm__ __volatile__("wfi");    // wait for interruption
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