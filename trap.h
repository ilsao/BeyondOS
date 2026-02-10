#pragma once
#include "common.h"
#include "syscall.h"

#define SCAUSE_ECALL 8

void kernel_entry(void);