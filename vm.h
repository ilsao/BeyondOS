#pragma once
#include "common.h"
#include "memory.h"

#define SATP_SV32   (1u << 31)  // enable satp paging
#define PAGE_V      (1 << 0)    // valid bit
#define PAGE_R      (1 << 1)
#define PAGE_W      (1 << 2)
#define PAGE_X      (1 << 3)
#define PAGE_U      (1 << 4)    // can access on user mode

void map_page(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags);