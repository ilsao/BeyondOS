#include "kernel.h"
#include "common.h"
#include "memory.h"
#include "process.h"
#include "exception.h"

/* import symbols from the linker */
extern char __bss[], __bss_end[], __stack_top[];

extern struct process *current_proc, *idle_proc;

struct process *proc_a, *proc_b;
void proc_a_entry()
{
    printf("starting process A\n");
    __asm__ __volatile__("unimp");
    while (1) {
        putchar('A');
        yield();
        delay();
    }
}

void proc_b_entry()
{
    printf("starting process B\n");
    while (1) {
        putchar('B');
        yield();
        delay();
    }
}

/* kernel main */
void kernel_main(void)
{
    // clear bss for uninitialized global and static variables
    memset((void *)__bss, 0, (size_t)__bss_end - (size_t)__bss);

    // register exception entry
    WRITE_CSR(stvec, (uint32_t) kernel_entry);

    printf("\n\nHello, World!\n");

    idle_proc = create_idle_process();
    current_proc = idle_proc;

    proc_a = create_process((uint32_t) proc_a_entry);
    proc_b = create_process((uint32_t) proc_b_entry);

    yield();
    PANIC("switched to idle process");
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