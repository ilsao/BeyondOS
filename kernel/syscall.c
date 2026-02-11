#include "syscall.h"

typedef int (*syscall_handler) (int arg0, int arg1, int arg2);

static int syscall_unimp(int arg0, int arg1, int arg2);
static int syscall_putchar(int arg0, int arg1, int arg2);
static int syscall_getchar(int arg0, int arg1, int arg2);
static int syscall_exit(int arg0, int arg1, int arg2);
static int syscall_readfile(int arg0, int arg1, int arg2);
static int syscall_writefile(int arg0, int arg1, int arg2);

syscall_handler syscall_table[] = {
    [SYS_UNIMP]     = syscall_unimp,
    [SYS_PUTCHAR]   = syscall_putchar,
    [SYS_GETCHAR]   = syscall_getchar,
    [SYS_EXIT]      = syscall_exit,
    [SYS_READFILE]  = syscall_readfile,
    [SYS_WRITEFILE] = syscall_writefile
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

static int syscall_unimp(int arg0, int arg1, int arg2)
{
    PANIC("this is syscal unimp\n");
}

static int syscall_putchar(int arg0, int arg1, int arg2)
{
    putchar(arg0);
    return arg0;
}

static int syscall_getchar(int arg0, int arg1, int arg2)
{
    while (1) {
        long ch = getchar();
        if (ch > 0) 
            return ch;
        
        yield();
    }
}

static int syscall_exit(int arg0, int arg1, int arg2)
{
    exit_proc();
    return arg0;
}

static int syscall_readfile(int arg0, int arg1, int arg2)
{
    const char *filename = (const char *) arg0;
    char *buf = (char *) arg1;
    size_t len = arg2;

    struct file *file = fs_lookup(filename);
    if (!file) {
        printf("file: %s not found\n", filename);
        return -1;
    }

    if (len > sizeof(file->data))
        len = sizeof(file->data);

    memcpy(buf, file->data, len);        

    return len;
}

static int syscall_writefile(int arg0, int arg1, int arg2)
{
    const char *filename = (const char *) arg0;
    char *buf = (char *) arg1;
    size_t len = arg2;

    struct file *file = fs_lookup(filename);
    if (!file) {
        printf("file: %s not found\n", filename);
        return -1;
    }

    if (len > sizeof(file->data))
        len = sizeof(file->data);

    memcpy(file->data, buf, len);
    file->size = len;
    fs_flush();
    
    return len;
}