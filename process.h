#pragma once
#include "common.h"
#include "vm.h"

#define SSTATUS_SPIE (1 << 5)   // enable interuption after trap

#define PROCS_MAX       8
#define PROC_UNUSED     0
#define PROC_RUNNABLE   1   
#define PROC_EXITED     2

#define USER_BASE 0x1000000

struct process {
    int pid;
    int state;              // PROC_UNUSED, PROC_RUNNABLE
    vaddr_t sp;
    uint32_t *page_table;
    uint8_t stack[8192];    // kernel stack
};

__attribute__((naked))
void switch_context(uint32_t *prev_sp, uint32_t *next_sp);
void yield(void);
struct process *create_process(const void *image, size_t image_size);
struct process *create_idle_process(void);
void exit_proc(void);