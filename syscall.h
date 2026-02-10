#pragma once
#include "common.h"
#include "kernel.h"

#define SYS_UNIMP   0
#define SYS_PUTCHAR 1

void handle_syscall(struct trap_frame *f);