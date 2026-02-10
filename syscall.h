#pragma once
#include "kio.h"
#include "common.h"
#include "kernel.h"
#include "process.h"

#define SYS_UNIMP   0
#define SYS_PUTCHAR 1
#define SYS_GETCHAR 2
#define SYS_EXIT    3

void handle_syscall(struct trap_frame *f);