#include "syscall.h"

typedef int (*syscall_handler) (int arg0, int arg1, int arg2);

int syscall_unimp(int arg0, int arg1, int arg2);
int syscall_putchar(int arg0, int arg1, int arg2);
int syscall_getchar(int arg0, int arg1, int arg2);
int syscall_exit(int arg0, int arg1, int arg2);

syscall_handler syscall_table[] = {
    [SYS_UNIMP]     = syscall_unimp,
    [SYS_PUTCHAR]   = syscall_putchar,
    [SYS_GETCHAR]   = syscall_getchar,
    [SYS_EXIT]      = syscall_exit
};

void handle_syscall(struct trap_frame *f)
{
    int sysno = f->a3;
    size_t table_size = sizeof(syscall_table) / sizeof(syscall_table[0]);

    if ((size_t) sysno >= table_size) {
        PANIC("unexpected syscall sysno = %x\n", sysno);
    }

    syscall_handler handler = syscall_table[sysno];
    if (handler == NULL)
        PANIC("syscall syno = %x has not implemented yet\n", sysno);
        
    int arg0, arg1, arg2;
    arg0 = f->a0;
    arg1 = f->a1;
    arg2 = f->a2;
    f->a0 = handler(arg0, arg1, arg2);
}

int syscall_unimp(int arg0, int arg1, int arg2)
{
    PANIC("this is syscal unimp\n");
}

int syscall_putchar(int arg0, int arg1, int arg2)
{
    putchar(arg0);
    return arg0;
}

int syscall_getchar(int arg0, int arg1, int arg2)
{
    while (1) {
        long ch = getchar();
        if (ch > 0) 
            return ch;
        
        yield();
    }
}


int syscall_exit(int arg0, int arg1, int arg2)
{
    exit_proc();
    return arg0;
}