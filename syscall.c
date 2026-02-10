#include "syscall.h"

typedef int (*syscall_handler) (int arg0, int arg1, int arg2);

int syscall_unimp(int arg0, int arg1, int arg2);
int syscall_putchar(int arg0, int arg1, int arg2);

syscall_handler syscall_table[] = {
    [SYS_UNIMP] = syscall_unimp,
    [SYS_PUTCHAR] = syscall_putchar
};

void handle_syscall(struct trap_frame *f)
{
    int sysno = f->a3;
    size_t table_size = sizeof(syscall_table) / sizeof(syscall_table[0]);

    if (sysno >= table_size) {
        PANIC("unexpected syscall sysno = %x\n", sysno);
    }

    syscall_handler handler = syscall_table[sysno];
    if (handler == NULL)
        PANIC("syscall syno = %x has not implemented yet\n", sysno);
        
    int arg0, arg1, arg2;
    arg0 = f->a0;
    arg2 = f->a1;
    arg2 = f->a2;
    handler(arg0, arg1, arg2);
}

int syscall_unimp(int arg0, int arg1, int arg2)
{
    PANIC("this is syscal unimp\n");
}

int syscall_putchar(int arg0, int arg1, int arg2)
{
    putchar(arg0);
}