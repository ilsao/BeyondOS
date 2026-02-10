#pragma once
#include "kio.h"
#include "trap.h"
#include "kernel.h"
#include "process.h"
#include "../common.h"

#define SYS_UNIMP   0
#define SYS_PUTCHAR 1
#define SYS_GETCHAR 2
#define SYS_EXIT    3

void handle_syscall(struct trap_frame *f);