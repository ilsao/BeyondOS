# BeyondOS

A simple, modular operating system for the RISC-V 32-bit architecture. This repository extends from [OS in 1000 lines](https://1000os.seiya.me/) with improved clarity and extendability. 

## Features
- **Process Management**: Context switching and cooperative multitasking
- **Virtual Memory**: Page table for virtual address and physical address translation
- **System Calls**: User-kernel mode transitions
- **File System**: Simple file system in .tar with read/write operations via VirtIO disk

## Planned Features
- **Memory Allocator**: The memory allocator in BeyondOS currently support page allocation only, without release functionality. It's planned to design a more generalized allocator with buddy system
- **Scheduler**: BeyondOS supports cooperative multitasking. It's time for the operating system to support preemptive scheduling

## Project Organization

```
.
├── common.c
├── common.h
├── disk                # example disk
│   ├── hello.txt
│   └── meow.txt
├── kernel
│   ├── file.c          # file system
│   ├── file.h
│   ├── kernel.c        # kernel main
│   ├── kernel.h
│   ├── kernel.ld       # kernel linker script
│   ├── kio.c           # kernel input/output
│   ├── kio.h
│   ├── memory.c        # manage the memory allocate
│   ├── memory.h
│   ├── process.c       # process and context switching
│   ├── process.h
│   ├── syscall.c       # system call implementation
│   ├── syscall.h
│   ├── trap.c          # trap and exception handling
│   ├── trap.h
│   ├── virtio_disk.c   # VirtIO_disk driver
│   ├── virtio_disk.h
│   ├── vm.c            # page table management
│   └── vm.h
├── user
│   ├── shell.c         # simple shell implementation
│   ├── user.c          # user space library functions
│   ├── user.h
│   └── user.ld         # user program linker script
├── Makefile
└── README.md
```

## Getting Started

### Installation

1. Clone the repository

``` bash
git clone https://github.com/ilsao/BeyondOS.git
cd BeyondOS
```

2. Install dependencies

``` bash
sudo apt update && sudo apt install -y clang llvm lld qemu-system-riscv32 curl
curl -LO https://github.com/qemu/qemu/raw/v8.0.4/pc-bios/opensbi-riscv32-generic-fw_dynamic.bin
```

### Running

Build and run the OS:

```shell
make 
```

Clean build artifacts:
```bash
make clean
```

BeyondOS provides these commands:
- `hello` - Test printf functionality
- `readfile` - Read `hello.txt` from disk
- `writefile` - Write content to `hello.txt`
- `exit` - Exit the shell program
