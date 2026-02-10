#pragma once
#include "syscall.h"
#include "../common.h"

#define SCAUSE_ECALL 8

void kernel_entry(void);