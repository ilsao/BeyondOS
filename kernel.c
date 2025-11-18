/* type define */
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef unsigned long   uint64_t;
typedef uint32_t        size_t;

/* import symbols from the linker */
extern char __bss[], __bss_end[], __stack_top[];

/* C-like function implementations */
void *memset(void *buf, int value, size_t n)
{
    uint8_t *p = (uint8_t *)buf;
    while (n > 0) {
        *p++ = value;
        n--;
    }
    return buf;
}

/* kernel main */
void kernel_main(void)
{
    // clear bss for uninitialized global and static variables
    memset((void *)__bss, 0, (size_t)__bss_end - (size_t)__bss);

    for (;;);
}

/* booter */
__attribute__((section(".text.boot"), naked));  // func boot -> .text.boot = 0x80200000
void boot(void)
{
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n"
        "j kernel_main\n"
        :
        : [stack_top] "r" (__stack_top)
    );
}