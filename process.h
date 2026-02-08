#pragma once

#define PROCS_MAX       8
#define PROC_UNUSED     0
#define PROC_RUNNABLE   1   

struct process {
    int pid;
    int state;              // PROC_UNUSED, PROC_RUNNABLE
    vaddr_t sp;
    uint8_t stack[8192];    // kernel stack
};