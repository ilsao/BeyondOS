#pragma once

typedef int                 bool;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef uint32_t            size_t;
typedef uint32_t            paddr_t;    // physical addr
typedef uint32_t            vaddr_t;    // virtual addr

#define true  1
#define false 0
#define NULL ((void *) 0)

#define PAGE_SIZE 4096

#define va_list  __builtin_va_list
#define va_start __builtin_va_start
#define va_end   __builtin_va_end
#define va_arg   __builtin_va_arg
#define align_up(value, align)   __builtin_align_up(value, align)
#define is_aligned(value, align) __builtin_is_aligned(value, align)
#define offsetof(type, member)   __builtin_offsetof(type, member)

#define PANIC(fmt, ...) \
    do {                \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);  \
        while (1) {}    \
    } while (0);

#define READ_CSR(reg)                                           \
    ({                                                          \
        unsigned long __tmp;                                    \
        __asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp));   \
        __tmp;                                                  \
    })

#define WRITE_CSR(reg, value)                                   \
    do {                                                        \
       uint32_t __tmp = (value);                                \
       __asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp));  \
    } while(0)

struct sbiret {
    long err;
    long value;
};

void delay(void);
void putchar(char ch);
void *memset(void *buf, char c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
void *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
void printf(const char *fmt, ...);