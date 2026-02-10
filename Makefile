# Tools and flags
QEMU := qemu-system-riscv32
OBJCOPY := /usr/bin/llvm-objcopy
CC := clang
CFLAGS := -std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf \
          -fuse-ld=lld -fno-stack-protector -ffreestanding -nostdlib \
          -Wno-unused-parameter

# Directories
KERNEL_DIR := kernel
USER_DIR   := user

# Source files
COMMON_SRCS := common.c
SHELL_SRCS := $(addprefix $(USER_DIR)/, shell.c user.c)
KERNEL_SRCS := $(addprefix $(KERNEL_DIR)/, kernel.c memory.c trap.c process.c vm.c syscall.c kio.c)

# Linker scripts
KERNEL_LD := $(KERNEL_DIR)/kernel.ld
USER_LD := $(USER_DIR)/user.ld

# Output files
SHELL_ELF := shell.elf
SHELL_BIN := shell.bin
SHELL_OBJ := shell.bin.o
KERNEL_ELF := kernel.elf

# QEMU flags
QEMU_FLAGS := -machine virt -bios default -nographic -serial mon:stdio \
              --no-reboot -d unimp,guest_errors,int,cpu_reset -D qemu.log

.PHONY: all clean run

all: run

# Build and run
run: $(KERNEL_ELF)
	$(QEMU) $(QEMU_FLAGS) -kernel $(KERNEL_ELF)

# Build the kernel
$(KERNEL_ELF): $(KERNEL_SRCS) $(COMMON_SRCS) $(SHELL_OBJ) $(KERNEL_LD)
	$(CC) $(CFLAGS) -Wl,-T$(KERNEL_LD) -Wl,-Map=kernel.map -o $@ \
		$(KERNEL_SRCS) $(COMMON_SRCS) $(SHELL_OBJ)

# Convert shell binary to object file
$(SHELL_OBJ): $(SHELL_BIN)
	$(OBJCOPY) -Ibinary -Oelf32-littleriscv $< $@

# Convert shell ELF to raw binary
$(SHELL_BIN): $(SHELL_ELF)
	$(OBJCOPY) --set-section-flags .bss=alloc,contents -O binary $< $@

# Build the shell (application)
$(SHELL_ELF): $(SHELL_SRCS) $(COMMON_SRCS) $(USER_LD)
	$(CC) $(CFLAGS) -Wl,-T$(USER_LD) -Wl,-Map=shell.map -o $@ $(SHELL_SRCS) $(COMMON_SRCS)

clean:
	rm -f $(SHELL_ELF) $(SHELL_BIN) $(SHELL_OBJ) $(KERNEL_ELF) \
		shell.map kernel.map qemu.log