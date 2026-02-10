#include "vm.h"

/*
* map_page: given table1, map vaddr to paddr with flags
*/
void map_page(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags)
{
    if (!is_aligned(vaddr, PAGE_SIZE))
        PANIC("unaligned vaddr %x\n", vaddr);

    if (!is_aligned(paddr, PAGE_SIZE))
        PANIC("unaligned paddr %x\n", paddr);

    uint32_t vpn1 = (uint32_t) (vaddr >> 22) & 0x3ff;
    // corresponding vpn is not valid, create table
    if ((table1[vpn1] & PAGE_V) == 0) {
        uint32_t pt_paddr = alloc_pages(1);
        // pt_paddr / PAGE to make sure the alignment
        table1[vpn1] = ((pt_paddr / PAGE_SIZE) << 10) | PAGE_V;
    }

    uint32_t vpn0 = (vaddr >> 12) & 0x3ff;
    uint32_t *table0 = (uint32_t *) ((table1[vpn1] >> 10) * PAGE_SIZE);
    table0[vpn0] = ((paddr / PAGE_SIZE) << 10) | flags | PAGE_V;
}