#pragma once
#include "common.h"

#define PROCS_MAX       8
#define PROC_UNUSED     0
#define PROC_RUNNABLE   1   

struct process {
    int pid;
    int state;              // PROC_UNUSED, PROC_RUNNABLE
    vaddr_t sp;
    uint8_t stack[8192];    // kernel stack
};

void switch_context(uint32_t *prev_sp, uint32_t *next_sp);
struct process *create_process(uint32_t pc);
struct process *create_idle_process(void);
void yield(void);