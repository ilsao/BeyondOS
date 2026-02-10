#!/bin/bash
set -xue

QEMU=qemu-system-riscv32
OBJCOPY=/usr/bin/llvm-objcopy

CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib"

# Build the shell (application)
$CC $CFLAGS -Wl,-Tuser.ld -Wl,-Map=shell.map -o shell.elf shell.c user.c common.c
# Convert from elf to raw bin
$OBJCOPY --set-section-flags .bss=alloc,contents -O binary shell.elf shell.bin
# Convert from bin to C accetable format
$OBJCOPY -Ibinary -Oelf32-littleriscv shell.bin shell.bin.o

# Build the kernel
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
    kernel.c common.c memory.c trap.c process.c vm.c syscall.c shell.bin.o

$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
    -d unimp,guest_errors,int,cpu_reset -D qemu.log \
    -kernel kernel.elf
