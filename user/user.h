#pragma once
#include "../common.h"
#include "../kernel/syscall.h"

__attribute__((noreturn)) void exit(void);
void putchar(char ch);
long getchar(void);